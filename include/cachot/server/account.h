#pragma once


/*!
 * \def CCH_ACCOUNT_FIELDS_QUANTITY
 *
 * アカウントファイルの各アカウントのフィールドの数を表します。
 */
#define    CCH_ACCOUNT_FIELDS_QUANTITY   6

/*!
 * \def CCH_ACCOUNT_FILENAME
 *
 * アカウントファイルの名前を表します。
 */
#define    CCH_ACCOUNT_FILENAME          "accounts"



typedef struct cch_account {
    char               *name;                  //!< アカウント名。
    char               *password;              //!< パスワードのハッシュ。
    time_t              last_login_at;         //!< 最後にログインした時刻。

    int32_t             character_quantity;    //!< このアカウントが持っているキャラクターの数。
    char               *character_names[CCH_MAX_CHARACTERS_PER_ACCOUNT + 1];    //!< このキャラクターが持っているアカウントの名前。

    time_t              created_at;            //!< このアカウントが作成された時刻。

    struct cch_account *_next;                 //!< 次のアカウント。
} CCHAccount;

/*!
 *
 */
void CCH_account_clear(void);

/*!
 *
 */
void CCH_account_load_entries(void);
