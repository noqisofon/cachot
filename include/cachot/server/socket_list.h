#pragma once

typedef struct cch_socket_list {
#ifdef CACHOT_CLIENT_TYPES_H
    size_t      length;
    uint8_t    *buffer;
#else
    size_t      length;
    uint8_t     buffer[CCH_MAX_SOCKET_BUFSIZE];
#endif  /* def CACHOT_CLIENT_TYPES_H */
} CCHSocketList;


/*!
 *
 */
CCH_API void CCH_socket_list_init(CCHSocketList *self);

/*!
 *
 */
CCH_API void CCH_socket_list_append_string(CCHSocketList *self, SPHStr value);
