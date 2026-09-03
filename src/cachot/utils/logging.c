#include "config.h"

#ifdef HAVE_STDDEF_H
#   include <stddef.h>
#endif /* def HAVE_STDDEF_H */

#ifdef HAVE_STDINT_H
#   include <stdint.h>
#endif /* def HAVE_STDINT_H */

#include <stdio.h>
#include <stdarg.h>

#include "cachot/cachot.h"
#include "cachot/utils/logging.h"

static const char *log_level_name( CCHLogLevel log_level ) {
    switch ( log_level ) {
    case CCHLogLevel_ERROR:
        return "ERROR";
    case CCHLogLevel_INFO:
        return "INFO";
    case CCHLogLevel_DEBUG:
        return "DEBUG";
    case CCHLogLevel_MONSTER:
        return "MONSTER";
    default:
        return "?";
    }
}

CCH_API void CCH_loggging_write( CCHLogLevel log_level, const SPHStr format, ... ) {
    va_list args;

    if ( log_level > The_settings.debug ) {
        // 現在の設定より詳細なログレベルは出力しません。
        return;
    }

    fprintf( stderr, "[%s] ", log_level_name( log_level ) );

    va_start( args, format );
    vfprintf( stderr, format, args );
    va_end( args );
}
