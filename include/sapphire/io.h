#pragma once


// SPH_EXTERN_C_BEGIN

/*!
 * \def SPH_O_TEXT
 */
#define    SPH_O_TEXT    _O_TEXT

/*!
 * \def SPH_O_BINARY
 */
#define    SPH_O_BINARY  _O_BINARY

typedef enum sph_io_file_mode {
    SPHIO_FileMode_READ  = 0,
    SPHIO_FileMode_WRITE = 1,
} SPHIO_FileMode;

typedef    struct sph_io_path      SPHIO_Path;

typedef    struct sph_io_handle    SPHIO_Handle;

/*!
 * \seealso SPH_O_TEXT SPH_O_BINARY
 */
SPH_API void          SPH_set_fmode(int32_t mode);

/*!
 *
 */
SPH_API int32_t       SPH_get_fmode(void);

/*!
 *
 */
SPH_API int32_t       SPH_note(const SPHStr format, ...);


// SPH_EXTERN_C_END
