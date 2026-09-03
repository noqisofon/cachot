#include "config.h"

#ifdef HAVE_STDDEF_H
#   include <stddef.h>
#endif  /* def HAVE_STDDEF_H */

#ifdef HAVE_STDINT_H
#   include <stdint.h>
#endif  /* def HAVE_STDINT_H */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sapphire/error.h"

SPH_API SPHStr SPH_error_to_string(int32_t err, SPHStrIterator message, size_t message_size) {
    switch ( err ) {
    case SPH_ERROR_OUT_OF_MEMORY:
        snprintf( message, message_size, "out of memory" );
        break;
    default:
        snprintf( message, message_size, "unknown error (%d)", err );
        break;
    }

    return message;
}

SPH_API void SPH_fatal(int32_t err) {
    char message[256];

    SPH_error_to_string( err, message, sizeof( message ) );
    fprintf( stderr, "fatal: %s\n", message );

    abort();
}
