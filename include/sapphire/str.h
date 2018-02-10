#pragma once


typedef   char   *SPHStr;
typedef   char   *SPHStrIterator;


#define   _(_literal_)    _literal_


/*!
 *
 */
SPH_API void            SPH_str_assign(SPHStr self, SPHStr another);

/*!
 *
 */
SPH_API void            SPH_str_init_with_size(SPHStr self, size_t size);

/*!
 *
 */
SPH_API SPHStr          SPH_str_clone(SPHStr self);

/*!
 *
 */
SPH_API uint32_t        SPH_str_to_uint32(SPHStr self, int32_t radix);

/*!
 *
 */
SPH_API uint64_t        SPH_str_to_uint64(SPHStr self, int32_t radix);

/*!
 *
 */
SPH_API int32_t         SPH_str_split(SPHStr self, char **result, size_t result_size, char separator);

/*!
 *
 */
SPH_API SPHStrIterator  SPH_str_find(SPHStr self, char ch);


/*!
 *
 */
SPH_API size_t           SPH_str_length(SPHStr self);


/*!
 *
 */
SPH_API SPHOrder         SPH_str_compare(SPHStr self, SPHStr other);


/*!
 *
 */
SPH_API SPHBool          SPH_str_equals(SPHStr self, SPHStr other);


/*!
 *
 */
SPH_API void             SPH_str_free(SPHStr self);
