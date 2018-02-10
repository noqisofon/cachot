#pragma once

#include <errno.h>




/*!
 *
 */
SPH_API SPHStr SPH_error_to_string(int32_t err, SPHStrIterator message, size_t message_size);
