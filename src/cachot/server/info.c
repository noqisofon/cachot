#include "config.h"

#ifdef HAVE_STDDEF_H
#   include <stddef.h>
#endif /* def HAVE_STDDEF_H */

#ifdef HAVE_STDINT_H
#   include <stdint.h>
#endif /* def HAVE_STDINT_H */

#include <stdio.h>
#include <stdarg.h>

#include "cachot/global.h"
#include "cachot/server/defines.h"
#include "cachot/server/info.h"

CCH_API void CCH_info_draw_ext( int32_t          flags,
                                int32_t          priority,
                                const CCHObject *a_player,
                                uint8_t          type,
                                uint8_t          subtype,
                                const SPHStr     message ) {
    (void)flags;
    (void)priority;
    (void)type;
    (void)subtype;

    // クライアントへのソケット送信はまだ実装されていないため、
    // 差し当たりサーバーのログへ出力するだけに留めます。
    CCH_INFO( _( "[%s] %s\n" ), ( a_player != NULL && a_player->name != NULL ) ? a_player->name : "?", message );
}

CCH_API void CCH_info_draw_ext_format( int32_t          flags,
                                       int32_t          priority,
                                       const CCHObject *a_player,
                                       uint8_t          type,
                                       uint8_t          subtype,
                                       const SPHStr     format,
                                       ... ) {
    char    buffer[CCH_MAX_VERY_BIG_BUFSIZE];
    va_list args;

    va_start( args, format );
    vsnprintf( buffer, sizeof( buffer ), format, args );
    va_end( args );

    CCH_info_draw_ext( flags, priority, a_player, type, subtype, buffer );
}
