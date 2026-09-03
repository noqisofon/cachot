#include "config.h"

#ifdef HAVE_STDDEF_H
#   include <stddef.h>
#endif /* def HAVE_STDDEF_H */

#ifdef HAVE_STDINT_H
#   include <stdint.h>
#endif /* def HAVE_STDINT_H */

#include <time.h>

#include "cachot/global.h"
#include "cachot/server/loop.h"

/*!
 * サーバーが起動してから経過したティック数。
 */
static uint32_t The_tick_counter = 0;

CCH_API void CCH_server_start( void ) {
    // ソケットの accept 処理はまだ実装されていません。
}

CCH_API void CCH_reset_error_quantity( void ) {
    // エラー数のカウントはまだ実装されていません。
}

CCH_API uint32_t CCH_time_ticks( void ) {
    return The_tick_counter;
}

CCH_API void CCH_time_sleep_delta( void ) {
    struct timespec delta = { 0, 100L * 1000L * 1000L }; // 100ms

    ++The_tick_counter;

    nanosleep( &delta, NULL );
}
