#pragma once


#define SPH_O_TEXT   _O_TEXT
#define SPH_O_BINARY _O_BINARY

typedef enum sph_io_file_mode {
    
} SPHIO_FileMode;

/*!
 *
 */
SPH_API void    SPH_set_fmode(int32_t mode);

/*!
 *
 */
SPH_API int32_t SPH_get_fmode(void);

/*!
 *
 */
SPH_API int32_t SPH_note(const SPHStr *format, ...);

/*!
 *
 */
SPH_API SPHIO_Handle *SPH_open(const SPHStr *path, SPHIO_FileMode filemode);

/*!
 *
 */
SPH_API SPHBool SPH_get_line(SPHIO *self, SPHStr *line, size_t line_size);
