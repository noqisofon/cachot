#include "config.h"

#ifdef HAVE_STDDEF_H
#   include <stddef.h>
#endif /* def HAVE_STDDEF_H */

#ifdef HAVE_STDINT_H
#   include <stdint.h>
#endif /* def HAVE_STDINT_H */

#include "cachot/global.h"
#include "cachot/server/init.h"

/*!
 * サーバー設定。今のところデフォルト値のみです。
 */
CCHSettings   The_settings = { 0 };

/*!
 * 統計情報。今のところ未使用です。
 */
CCHStatistics The_statistics = { 0 };

/*!
 * メインループを継続するかどうかを表します。
 */
SPHBool       is_running = false;

/*!
 * アクティブなオブジェクトの連結リストの先頭。
 */
CCHObject    *The_active_objects = NULL;

/*!
 * ログイン中のプレイヤーの連結リストの先頭。
 */
CCHPlayer    *The_first_player = NULL;

CCH_API void CCH_init( int32_t argc, SPHStr *argv ) {
    (void)argc;
    (void)argv;

    // まだ設定ファイルの読み込みなどは実装されていないため、
    // デフォルト設定のまま起動できるようにするだけに留めます。
    is_running = true;
}
