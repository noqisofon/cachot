#include <stdlib.h>
#ifdef _MSC_VER
#   include <crtdbg.h>
#endif  /* def _MSC_VER */
#include "sappire/allocation.h"



SPH_API void *SPH_alloc(size_t size) {
    void *ptr          = NULL;
    
    if ( size == 0 ) {
        size = 1;
    }
    
    ptr = malloc( size );

    return ptr;
}

SPH_API void *SPH_alloc_debug(size_t size, const char *filename, int32_t line_number) {
    void *ptr = NULL;
    if ( size == 0 ) {
        size = 1;
    }
    
    ptr = _malloc_dbg( size, _NORMAL_BLOCK, filename, line_number );

    return ptr;
}
