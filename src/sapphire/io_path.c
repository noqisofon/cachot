#include "config.h"

#ifdef HAVE_STDDEF_H
#   include <stddef.h>
#endif  /* def HAVE_STDDEF_H */

#ifdef HAVE_STDINT_H
#   include <stdint.h>
#endif  /* def HAVE_STDINT_H */

#include <stdlib.h>
#include <string.h>

#include "sapphire/io_path.h"
#include "sapphire/allocation.h"

struct sph_io_path {
    char   *buffer;
    size_t  length;
    size_t  capacity;
};

static void path_append_raw( SPHIO_Path *self, const char *text ) {
    size_t text_length = strlen( text );
    size_t needed       = self->length + text_length + 1;

    if ( needed > self->capacity ) {
        size_t new_capacity = needed * 2;

        self->buffer   = (char *)SPH_REALLOC( self->buffer, new_capacity );
        self->capacity = new_capacity;
    }

    memcpy( self->buffer + self->length, text, text_length + 1 );
    self->length += text_length;
}

SPH_API SPHIO_Path *SPH_io_path_new( const SPHStr path ) {
    SPHIO_Path *self = SPH_NEW( SPHIO_Path );

    self->buffer   = NULL;
    self->length   = 0;
    self->capacity = 0;

    path_append_raw( self, path != NULL ? path : "" );

    return self;
}

SPH_API SPHIO_Path *SPH_io_path_add( SPHIO_Path *self, const SPHStr path ) {
    if ( self->length > 0 && self->buffer[self->length - 1] != '/' ) {
        path_append_raw( self, "/" );
    }

    path_append_raw( self, path );

    return self;
}

SPH_API SPHStr SPH_io_path_to_str( SPHIO_Path *self ) {
    return self->buffer;
}

SPH_API void SPH_io_path_free( SPHIO_Path *self ) {
    SPH_DELETE( self->buffer );
    SPH_DELETE( self );
}
