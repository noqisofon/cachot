#pragma once


/*!
 *
 */
CCH_API void CCH_server_show_version(CCHObject *that);


/*!
 *
 */
CCH_API void CCH_server_start_info(CCHObject *that);

/*!
 * 
 */
CCH_API void CCH_server_dispatch_event(void);


/*!
 *
 */
CCH_API int32_t CCH_server_main(int32_t argc, char **argv);
