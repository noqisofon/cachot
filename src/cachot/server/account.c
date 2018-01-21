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


void CCH_account_clear(void) {
    The_accounts        = NULL;
    The_accounts_loaded = false;
}

void CCH_account_load_entries(void) {
    SPHIO_Path      *filename                                    = SPH_io_path_new( The_settings.local_dir );
    SPHStr          *line        /* CCH_VERY_LARGE_BUFSIZE */;

    SPHIO_Handle    *output;
    
    CCHAccount      *account;
    CCHAccount      *last_account         = NULL;

    int32_t          field_quantity       = 0;

    if ( The_accounts != NULL ) {
        CCH_ERROR( _("%s(): Called when accounts has been set.\n"), __FUNCTION__ );

        return ;
    }

    SPH_io_path_add( filename, CCH_ACCOUNT_FILENAME );
    output = SPH_open( filename, SPHIO_FileMode_READ );
    if ( !output ) {
        char err_message[CCH_MAX_BUFSIZE];
        CCH_INFO( _("Waning: Unable to open %s [%s]"), filename, strerror_local( errno, err_message, sizeof(err_message) ) );

        return ;
    }

    while ( SPH_get_line( path, line, CCH_VERY_LARGE_BUFSIZE ) ) {
        char    *it;
        char    *fields[CCH_ACCOUNT_FIELDS_QUANTITY];

        int32_t  result;

        if ( line[0] == '#' ) {
            // '#' はコメントなので、無視します。
            continue;
        }

        it = strchr( line, '\n' );
        if ( it ) {
            // 改行を '\0'(文字列の終わり)で上書きします。
            *it = '\0';
        }

        field_quantity = SPH_string_split( line, fields, CCH_ACCOUNT_FIELDS_QUANTITY, ':' );

        account                = SPH_NEW(CCHAccount);
        account->name          = SPH_string_clone( fields[0] );
        account->password      = SPH_string_clone( fields[1] );
        account->last_login_at = SPH_string_to_unsiged( fields[2], 10 );

        if ( field_quantity > 4 ) {
            account->created_at = SPH_string_to_unsiged( fields[4], 10 );
        } else {
            account->created_at = account->last_login_at;
        }

        account->_next         = NULL;

        if ( fields[3][0] == '\0' ) {
            account->character_quantity = 0;
            for ( int32_t i = 0 i <= CCH_MAX_CHARACTERS_PER_ACCOUNT; ++ i ) {
                account->character_names[i] = NULL;
            }
        } else {
            account->character_quantity = 1;

            for ( it = fields[3]; *it != '\0'; ++ it ) {
            }
        }
    }
}
