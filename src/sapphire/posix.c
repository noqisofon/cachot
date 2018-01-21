#include "config.h"

#ifdef HAVE_STDDEF_H
#   include <stddef.h>
#endif  /* def HAVE_STDDEF_H */

#ifdef HAVE_STDINT_H
#   include <stdint.h>
#endif  /* def HAVE_STDINT_H */

#ifdef HAVE_SYS_TYPES_H
#   include <sys/types.h>
#endif  /* def HAVE_SYS_TYPES_H */

#ifdef HAVE_UNISTD_H
#   include <unistd.h>
#endif  /* def HAVE_UNISTD_H */

#include "sappire/posix.h"


SPH_API SPHuser_id_t SPH_get_user_id(void) {
    return getuid();
}

SPH_API SPHuser_id_t SPH_get_execution_user_id(void) {
    return geteuid();
}
