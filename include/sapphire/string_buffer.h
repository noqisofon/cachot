#pragma once


/*!
 *
 */
typedef    struct sph_string_buffer    SPHStringBuffer;


/*!
 *
 */
SPH_API SPHStringBuffer *SPH_string_buffer_init(SPHStringBuffer *self);


/*!
 *
 */
SPH_API SPHStringBuffer *SPH_string_buffer_new(void);


/*!
 *
 */
SPH_API void SPH_string_buffer_free(SPHStringBuffer *self);


/*!
 *
 */
SPH_API char *SPH_string_buffer_finish(SPHStringBuffer *self);


/*!
 *
 */
SPH_API void SPH_string_buffer_append_string(SPHStringBuffer *self, const char *str);


/*!
 *
 */
SPH_API void SPH_string_buffer_append_format(SPHStringBuffer *self, const char *format, ...);

/*!
 *
 */
SPH_API size_t SPH_string_buffer_length(SPHStringBuffer *self);
