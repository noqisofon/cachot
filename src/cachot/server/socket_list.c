#include "config.h"

#ifdef HAVE_STDDEF_H
#   include <stddef.h>
#endif /* def HAVE_STDDEF_H */

#ifdef HAVE_STDINT_H
#   include <stdint.h>
#endif /* def HAVE_STDINT_H */

#include <string.h>

#include "cachot/server/socket_list.h"

CCH_API void CCH_socket_list_init( CCHSocketList *self ) {
    self->length = 0;
    memset( self->buffer, 0, sizeof( self->buffer ) );
}

CCH_API void CCH_socket_list_append_string( CCHSocketList *self, SPHStr value ) {
    size_t value_length = strlen( value );
    size_t remaining     = sizeof( self->buffer ) - self->length;

    if ( value_length >= remaining ) {
        value_length = remaining > 0 ? remaining - 1 : 0;
    }

    if ( value_length > 0 ) {
        memcpy( self->buffer + self->length, value, value_length );
        self->length += value_length;
    }
}
