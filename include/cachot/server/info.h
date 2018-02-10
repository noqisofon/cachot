#pragma once


/*!
 *
 */
CCH_API void CCH_info_draw_ext(int32_t          flags,
                               int32_t          priority,
                               const CCHObject *a_player,
                               uint8_t          type,
                               uint8_t          subtype,
                               const SPHStr     message);

/*!
 *
 */
CCH_API void CCH_info_draw_ext_format(int32_t          flags,
                                      int32_t          priority,
                                      const CCHObject *a_player,
                                      uint8_t          type,
                                      uint8_t          subtype,
                                      const SPHStr     format,
                                      ...);
