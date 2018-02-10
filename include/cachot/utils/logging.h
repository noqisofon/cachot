#pragma once


typedef enum cch_log_level {
    CCHLogLevel_ERROR        = 0,
    CCHLogLevel_INFO         = 1,
    CCHLogLevel_DEBUG        = 2,
    CCHLogLevel_MONSTER      = 3
} CCHLogLevel;

/*!
 *
 */
#define CCH_ERROR(...)    CCH_loggging_write( CCHLogLevel_ERROR, __VA_ARGS__ )

/*!
 *
 */
#define CCH_INFO(...)     CCH_loggging_write( CCHLogLevel_INFO, __VA_ARGS__ )

/*!
 *
 */
#define CCH_DEBUG(...)    CCH_loggging_write( CCHLogLevel_DEBUG, __VA_ARGS__ )

/*!
 *
 */
SPH_API void CCH_loggging_write(CCHLogLevel log_level, const SPHStr format, ...);
