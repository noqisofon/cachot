#pragma once


/*!
 *
 */
SPH_API SPHBool       SPH_get_line(SPHIO_Handle *self, SPHStr line, size_t line_size);

/*!
 *
 */
SPH_API void          SPH_io_handle_free(SPHIO_Handle *self);

/*!
 *
 */
SPH_API SPHIO_Handle *SPH_open(const SPHStr path, SPHIO_FileMode filemode);

/*!
 *
 */
SPH_API void          SPH_close(SPHIO_Handle *self);

/*!
 *
 */
SPH_API int32_t       SPH_io_handle_printf(SPHIO_Handle *self, SPHStr format, ...);
