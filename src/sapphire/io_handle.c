#include "config.h"

#ifdef HAVE_STDDEF_H
#   include <stddef.h>
#endif  /* def HAVE_STDDEF_H */

#ifdef HAVE_STDINT_H
#   include <stdint.h>
#endif  /* def HAVE_STDINT_H */

#include <stdio.h>
#include <stdarg.h>

#include "sapphire/io_handle.h"
#include "sapphire/allocation.h"

struct sph_io_handle {
    FILE *file;
};

SPH_API SPHIO_Handle *SPH_open( const SPHStr path, SPHIO_FileMode filemode ) {
    const char   *mode = ( filemode == SPHIO_FileMode_WRITE ) ? "w" : "r";
    FILE         *file = fopen( path, mode );
    SPHIO_Handle *self;

    if ( file == NULL ) {
        return NULL;
    }

    self       = SPH_NEW( SPHIO_Handle );
    self->file = file;

    return self;
}

SPH_API void SPH_close( SPHIO_Handle *self ) {
    if ( self != NULL && self->file != NULL ) {
        fclose( self->file );
        self->file = NULL;
    }
}

SPH_API void SPH_io_handle_free( SPHIO_Handle *self ) {
    SPH_DELETE( self );
}

SPH_API SPHBool SPH_get_line( SPHIO_Handle *self, SPHStr line, size_t line_size ) {
    if ( self == NULL || self->file == NULL ) {
        return false;
    }

    return fgets( line, (int)line_size, self->file ) != NULL ? true : false;
}

SPH_API int32_t SPH_io_handle_printf( SPHIO_Handle *self, SPHStr format, ... ) {
    va_list args;
    int32_t result;

    if ( self == NULL || self->file == NULL ) {
        return -1;
    }

    va_start( args, format );
    result = vfprintf( self->file, format, args );
    va_end( args );

    return result;
}
