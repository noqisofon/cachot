#pragma once

#ifdef HAVE_SYS_TYPES_H
#   include <sys/types.h>
#endif  /* def HAVE_SYS_TYPES_H */

#ifdef HAVE_STDINT_H
#   include <stdint.h>
#endif  /* def HAVE_STDINT_H */

#include "sapphire/internal.h"

#ifdef HAVE_SYS_TYPES_H
typedef uid_t SPHuser_id_t;
#else
typedef int32_t SPHuser_id_t;
#endif  /* def HAVE_SYS_TYPES_H */

/*!
 * 呼び出し元のプロセスの実ユーザー ID を取得します。
 */
SPH_API SPHuser_id_t SPH_get_user_id(void);

/*!
 * 呼び出し元のプロセスの実効ユーザー ID を取得します。
 */
SPH_API SPHuser_id_t SPH_get_execution_user_id(void);
