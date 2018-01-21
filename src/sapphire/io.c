#include "config.h"

#ifdef HAVE_STDDEF_H
#   include <stddef.h>
#endif  /* def HAVE_STDDEF_H */

#ifdef HAVE_STDINT_H
#   include <stdint.h>
#endif  /* def HAVE_STDINT_H */

#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdarg.h>


void SPH_set_fmode(int32_t mode) {
#ifdef _MSC_VER
    _set_fmode( mode );
#else
    _fmode = mode;
#endif  /* def _MSC_VER */
}

SPH_API int32_t SPH_get_fmode(void) {
    int32_t mode = 0;
#ifdef _MSC_VER
    _get_fmode( &mode );
#else
    mode = _fmode;
#endif  /* def _MSC_VER */
    return mode;
}

SPH_API int32_t SPH_note(const char *format, ...) {
    va_list  args;
    int32_t  answer = 0;

    va_start( args, format );
    answer = vfprintf( stderr, format, args );
    va_end( args );

    return answer;
}
