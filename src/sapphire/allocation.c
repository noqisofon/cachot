#include <stdlib.h>
#ifdef _MSC_VER
#   include <crtdbg.h>
#endif  /* def _MSC_VER */
#include "sapphire/allocation.h"



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

#ifdef _MSC_VER
    ptr = _malloc_dbg( size, _NORMAL_BLOCK, filename, line_number );
#else
    (void)filename;
    (void)line_number;
    ptr = malloc( size );
#endif  /* def _MSC_VER */

    return ptr;
}

SPH_API void *SPH_realloc(void *ptr, size_t size) {
    if ( size == 0 ) {
        size = 1;
    }

    return realloc( ptr, size );
}

SPH_API void *SPH_realloc_debug(void *ptr, size_t size, const char *filename, int32_t line_number) {
    (void)filename;
    (void)line_number;

    return SPH_realloc( ptr, size );
}

SPH_API void SPH_dealloc(void *ptr) {
    free( ptr );
}

SPH_API void SPH_dealloc_debug(void *ptr, const char *filename, int32_t line_number) {
    (void)filename;
    (void)line_number;

    free( ptr );
}
