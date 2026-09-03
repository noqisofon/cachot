#pragma once

#include <errno.h>
#include <stddef.h>
#include <stdint.h>

#include "sapphire/internal.h"
#include "sapphire/str.h"

typedef enum sph_error_code {
    SPH_ERROR_NONE           = 0,
    SPH_ERROR_OUT_OF_MEMORY  = 1
} SPHErrorCode;

/*!
 *
 */
SPH_API SPHStr SPH_error_to_string(int32_t err, SPHStrIterator message, size_t message_size);

/*!
 * 回復不能なエラーを報告して、プロセスを終了させます。
 */
SPH_API void   SPH_fatal(int32_t err);
