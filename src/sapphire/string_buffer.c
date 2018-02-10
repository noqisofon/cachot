#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "sapphire/string_buffer.h"


#define DEFAULT_BUFFER_SIZE 256

struct sph_string_buffer {
    size_t    size;
    size_t    position;
    char     *buffer;
};


/*!
 *
 */
static SPHStringBuffer *string_buffer_alloc(void) {
    return SPH_NEW(SPHStringBuffer);
}

/*!
 *
 */
static void string_buffer_grow(SPHStringBuffer *self, size_t new_size) {
    char *tmp = SPH_REALLOC(self->buffer, new_size);
    if ( tmp == NULL ) {

        SPH_fatal( SPH_ERROR_OUT_OF_MEMORY );
    }

    self->buffer = tmp;
    self->size   = new_size;
}

/*!
 *
 */
static void string_buffer_ensure(SPHStringBuffer *self, size_t length) {
    if ( self->position + length <= self->size ) {

        return ;
    }

    string_buffer_grow( self, self->position + length + DEFAULT_BUFFER_SIZE );
}

SPH_API SPHStringBuffer *SPH_string_buffer_init(SPHStringBuffer *self) {
    self->size     = DEFAULT_BUFFER_SIZE;
    self->position =   0;
    self->buffer   = SPH_NEW_ARRAY( self->size );
}

SPH_API SPHStringBuffer *SPH_string_buffer_new(void) {
    return SPH_string_buffer_init( string_buffer_alloc() );
}

SPH_API void SPH_string_buffer_free(SPHStringBuffer *self) {
    SPH_DELETE(self->buffer);
    SPH_DELETE(self);
}

SPH_API char *SPH_string_buffer_finish(SPHStringBuffer *self) {
    char *result;

    self->buffer[self->position] = '\0';
    
    result = self->buffer;
    SPH_DELETE(self);

    return result;
}

SPH_API void SPH_string_buffer_append_string(SPHStringBuffer *self, const char *str) {
    size_t length;

    length = strlen( str );

    string_buffer_ensure( self, len + 1 );

    memcpy( self->buffer + self->position, str, length );

    self->position += length;
}

SPH_API void SPH_string_buffer_append_format(SPHStringBuffer *self, const char *format, ...) {
    size_t     size = DEFAULT_BUFFER_SIZE;

    for ( ;; ) {
        int32_t  n;
        va_list  args;

        string_buffer_ensure( self, size );

        va_start( args, format );
        n = vsnprintf( self->buffer + self->position, size, format, args );
        va_end( args );

        if ( n > -1 && (size_t)n < size ) {
            self->position += (size_t)n;

            break;
        }

        if ( n > -1 ) {
            size = n - 1;
        } else {
            size *= 2;
        }
    }
}

SPH_API size_t SPH_string_buffer_length(SPHStringBuffer *self) {
    return self->position;
}
