#pragma once


/*!
 *
 */
SPH_API SPHIO_Path   *SPH_io_path_new(const SPHStr path);


/*!
 *
 */
SPH_API SPHIO_Path   *SPH_io_path_add(SPHIO_Path *self, const SPHStr path);


/*!
 *
 */
SPH_API SPHStr        SPH_io_path_to_str(SPHIO_Path *self);


/*!
 *
 */
SPH_API void          SPH_io_path_free(SPHIO_Path *self);
