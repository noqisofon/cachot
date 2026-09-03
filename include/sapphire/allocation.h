#pragma once

#include <stddef.h>
#include <stdint.h>

#include "sapphire/internal.h"

#ifndef _DEBUG
#    define   SPH_NEW(_Type_)    SPH_alloc( sizeof(_Type_) )
#else
#    define   SPH_NEW(_Type_)    SPH_alloc_debug( sizeof(_Type_), __FILE__, __LINE__ )
#endif  /* def _DEBUG */

#ifndef _DEBUG
#    define   SPH_DELETE(_ptr_)    SPH_dealloc( _ptr_ )
#else
#    define   SPH_DELETE(_ptr_)    SPH_dealloc_debug( _ptr_, __FILE__, __LINE__ )
#endif  /* def _DEBUG */

#ifndef _DEBUG
#    define   SPH_NEW_ARRAY(_size_)    SPH_alloc( _size_ )
#else
#    define   SPH_NEW_ARRAY(_size_)    SPH_alloc_debug( _size_, __FILE__, __LINE__ )
#endif  /* def _DEBUG */

#ifndef _DEBUG
#    define   SPH_REALLOC(_ptr_, _size_)    SPH_realloc( _ptr_, _size_ )
#else
#    define   SPH_REALLOC(_ptr_, _size_)    SPH_realloc_debug( _ptr_, _size_, __FILE__, __LINE__ )
#endif  /* def _DEBUG */



/*!
 *
 */
SPH_API void *SPH_alloc(size_t size);

/*!
 *
 */
SPH_API void *SPH_alloc_debug(size_t size, const char *filename, int32_t line_number);

/*!
 *
 */
SPH_API void *SPH_realloc(void *ptr, size_t size);

/*!
 *
 */
SPH_API void *SPH_realloc_debug(void *ptr, size_t size, const char *filename, int32_t line_number);

/*!
 *
 */
SPH_API void  SPH_dealloc(void *ptr);

/*!
 *
 */
SPH_API void  SPH_dealloc_debug(void *ptr, const char *filename, int32_t line_number);
