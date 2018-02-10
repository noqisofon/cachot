#pragma once

#ifdef SPH_HAVE_STDBOOL_H
#   include <stdbool.h>
#endif  /* def SPH_HAVE_STDBOOL_H */

#ifdef __bool_true_false_are_defined
typedef    _Bool           SPHBool;
#else
typedef    signed char     SPHBool;

#   ifdef __cplusplus
#   else
#       undef  false
#       define false 0

#       undef  true
#       define true  1
#   endif  /* def __cplusplus */

#endif  /* def __bool_true_false_are_defined */
