#include "config.h"

#ifdef HAVE_STDDEF_H
#   include <stddef.h>
#endif  /* def HAVE_STDDEF_H */

#ifdef HAVE_STDINT_H
#   include <stdint.h>
#endif  /* def HAVE_STDINT_H */

#include <stdlib.h>
#include <string.h>

#include "sapphire/str.h"
#include "sapphire/allocation.h"

SPH_API void SPH_str_assign( SPHStr self, SPHStr another ) {
    if ( self == another ) {
        return;
    }

    strcpy( self, another );
}

SPH_API void SPH_str_init_with_size( SPHStr self, size_t size ) {
    memset( self, 0, size );
}

SPH_API SPHStr SPH_str_clone( SPHStr self ) {
    size_t length = strlen( self );
    SPHStr result = (SPHStr)SPH_NEW_ARRAY( length + 1 );

    memcpy( result, self, length + 1 );

    return result;
}

SPH_API uint32_t SPH_str_to_uint32( SPHStr self, int32_t radix ) {
    return (uint32_t)strtoul( self, NULL, radix );
}

SPH_API uint64_t SPH_str_to_uint64( SPHStr self, int32_t radix ) {
    return (uint64_t)strtoull( self, NULL, radix );
}

SPH_API int32_t SPH_str_split( SPHStr self, char **result, size_t result_size, char separator ) {
    size_t          count = 0;
    SPHStrIterator  it;

    if ( result_size == 0 ) {
        return 0;
    }

    result[count++] = self;

    for ( it = self; *it != '\0' && count < result_size; ++it ) {
        if ( *it == separator ) {
            *it             = '\0';
            result[count++] = it + 1;
        }
    }

    return (int32_t)count;
}

SPH_API SPHStrIterator SPH_str_find( SPHStr self, char ch ) {
    return strchr( self, ch );
}

SPH_API size_t SPH_str_length( SPHStr self ) {
    return strlen( self );
}

SPH_API SPHOrder SPH_str_compare( SPHStr self, SPHStr other ) {
    int result = strcmp( self, other );

    if ( result < 0 ) {
        return SPHOrder_Less;
    }
    if ( result > 0 ) {
        return SPHOrder_More;
    }
    return SPHOrder_Same;
}

SPH_API SPHBool SPH_str_equals( SPHStr self, SPHStr other ) {
    return strcmp( self, other ) == 0 ? true : false;
}

SPH_API void SPH_str_free( SPHStr self ) {
    SPH_DELETE( self );
}
