#include "config.h"

#ifdef HAVE_STDDEF_H
#   include <stddef.h>
#endif /* def HAVE_STDDEF_H */

#ifdef HAVE_STDINT_H
#   include <stdint.h>
#endif /* def HAVE_STDINT_H */

#include "cachot/global.h"
#include "cachot/domain/world.h"

CCH_API void CCH_world_tick_timers( void ) {
    // マップのタイムアウト処理はまだ実装されていません。
}

CCH_API void CCH_world_check_active_maps( void ) {
    // マップのスワップ管理はまだ実装されていません。
}

CCH_API void CCH_swap_map( CCHMap *a_map ) {
    (void)a_map;

    // マップをディスクへスワップアウトする処理はまだ実装されていません。
}
