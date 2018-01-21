#include "config.h"

#ifdef HAVE_STDDEF_H
#   include <stddef.h>
#endif  /* def HAVE_STDDEF_H */

#ifdef HAVE_STDINT_H
#   include <stdint.h>
#endif  /* def HAVE_STDINT_H */

#ifdef HAVE_SYS_TYPES_H
#   include <sys/types.h>
#endif  /* def HAVE_SYS_TYPES_H */

#include <stdio.h>

#ifdef HAVE_UNISTD_H
#   include <unistd.h>
#endif  /* def HAVE_UNISTD_H */

#ifdef HAVE_ASSERT_H
#   include <assert.h>
#endif  /* def HAVE_ASSERT_H */

#include "cachot/cachot.h"

#include "cachot/server/account.h"

/*!
 * アカウントリストの先頭。
 */
static CCHAccount    *The_accounts           = NULL;

/*!
 * アカウントファイルを読み込んだことを示すフラグです。
 */
static bool           The_accounts_loaded    = false;


CCH_API void CCH_account_clear(void) {
    The_accounts        = NULL;
    The_accounts_loaded = false;
}

#define STRING_END              '\0'
#define NEWLINE                 '\n'
#define COMMENT                 '#'
#define FIELD_SEPARATOR         ';'
#define CHARACTERNAME_SEPARATOR ';'

CCH_API void CCH_account_load_entries(void) {
    SPHIO_Path      *filename = NULL;

    if ( The_accounts != NULL ) {
        CCH_ERROR( _("CCH_account_load_entries: Called when accounts has been set.\n") );

        return ;
    }

    filename = SPH_io_path_new( The_settings.local_dir );
    SPH_io_path_add( filename, CCH_ACCOUNT_FILENAME );

    SPHIO_Handle    *output = SPH_open( filename, SPHIO_FileMode_READ );
    if ( !output ) {
        char err_message[CCH_MAX_BUFSIZE];

        CCH_INFO( _("Waning: Unable to open %s [%s]"),
                  SPH_io_path_to_str( filename ),
                  SPH_error_to_string( errno, err_message, sizeof(err_message) ) );

        SPH_io_path_free( filename );

        return ;
    }

    int32_t          field_quantity       = 0;
    SPHStr           line                 = {0};
    
    CCHAccount      *account              = NULL;
    CCHAccount      *last_account         = NULL;

    SPH_string_init_with_size( &line, CCH_VERY_LARGE_BUFSIZE );

    while ( SPH_get_line( output, &line ) ) {
        SPHStrIterator    *it;
        char              *fields[CCH_ACCOUNT_FIELDS_QUANTITY];

        if ( line[0] == COMMENT ) {
            // '#' はコメントなので、無視します。
            continue;
        }

        it = SPH_string_find( line, NEWLINE );
        if ( it ) {
            // 改行を '\0'(文字列の終わり)で上書きします。
            *it = STRING_END;
        }

        field_quantity = SPH_string_split( line, fields, CCH_ACCOUNT_FIELDS_QUANTITY, FIELD_SEPARATOR );

        account                = SPH_NEW(CCHAccount);
        account->name          = SPH_string_clone( fields[0] );
        account->password      = SPH_string_clone( fields[1] );
        account->last_login_at = SPH_string_to_unsiged( fields[2], 10 );

        if ( field_quantity > 4 ) {
            account->created_at = SPH_string_to_uint32( fields[4], 10 );
        } else {
            account->created_at = account->last_login_at;
        }

        account->_next         = NULL;

        if ( fields[3][0] == STRING_END ) {
            account->character_quantity = 0;
            for ( int32_t i = 0 i <= CCH_MAX_CHARACTERS_PER_ACCOUNT; ++ i ) {
                account->character_names[i] = NULL;
            }
        } else {
            int32_t  result = 0;

            account->character_quantity = 1;

            for ( it = fields[3]; *it != STRING_END; ++ it ) {
                if ( *it == CHARACTERNAME_SEPARATOR ) {
                    ++ account->character_quantity;
                }
            }

            result = SPH_string_split( fields[3],
                                       account->character_names,
                                       account->character_quantity,
                                       CHARACTERNAME_SEPARATOR );

            if ( result != account->character_quantity ) {
                CCH_ERROR( _("CCH_account_load_entries: SPH_string_split() found different character quantity: %d != %d\n"),
                           result,
                           account->character_quantity );
            }

            if ( account->character_quantity > CCH_MAX_CHARACTERS_PER_ACCOUNT ) {
                CCH_ERROR( _("CCH_account_load_entries: Too many characters set for account %s - truncating to %d\n"),
                           account->name,
                           CCH_MAX_CHARACTERS_PER_ACCOUNT );

                account->character_quantity = CCH_MAX_CHARACTERS_PER_ACCOUNT;
            }

            for ( int32_t i = 0; i < account->character_quantity; ++ i ) {
                if ( account->character_names[i] == NULL ) {
                    account->character_quantity = i;

                    break;
                }
                // string#clone だと必要ない SPHStr インスタンスが 1 つ余計に出そう。
                // string#assign なら同じポインタの場合は何もしないか、中身の生文字列をコピーするだけ。
                SPH_string_assign( account->character_names[i], account->character_names[i] );
            }

            // 残りはしっかり NULL で塗りつぶす。
            for ( int32_t i = account->character_quantity; i <= CCH_MAX_CHARACTERS_PER_ACCOUNT; ++ i ) {
                account->character_names[i] = NULL;
            }
        }

        if ( last_account ) {
            last_account->_next = account;
        } else {
            The_accounts = account;
        }
        last_account = account;
    }

    SPH_io_path_free( filename );
    SPH_close( output );
    SPH_io_handle_free( output );

    The_accounts_loaded = true;
}

static void account_write_entry(SPHIO_Handle *input, const CCHAccount *an_account) {
    SPH_io_handle_printf( input, "%s:%s:u",
                          an_account->name,
                          an_account->password,
                          (uint32_t)an_account->last_login_at );
    for ( int32_t i = 0; i < an_account->character_quantity; ++ i ) {
        if ( i == 0 ) {
            SPH_io_handle_printf( input, "%s", an_account->character_names[i] );
        } else {
            SPH_io_handle_printf( input, ";%s", an_account->character_names[i] );
        }
    }
    SPH_io_handle_printf( input, ":%u\n", (uint32_t)an_account->created_at );
}


CCH_API void CCH_account_save(void) {
    if ( !The_accounts_loaded ) {

        return ;
    }
}
