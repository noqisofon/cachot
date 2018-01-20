#pragma once

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



/*!
 *
 */
SPH_API void *SPH_alloc(size_t size);

/*!
 *
 */
SPH_API void *SPH_alloc_debug(size_t size, const char *filename, int32_t line_number);
