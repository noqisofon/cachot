#include "config.h"

#ifdef HAVE_STDDEF_H
#   include <stddef.h>
#endif /* def HAVE_STDDEF_H */

#ifdef HAVE_STDINT_H
#   include <stdint.h>
#endif /* def HAVE_STDINT_H */

#include <string.h>

#include "cachot/global.h"
#include "sapphire/allocation.h"

CCH_API CCHObject *CCH_object_new( void ) {
    CCHObject *self = SPH_NEW( CCHObject );

    memset( self, 0, sizeof( CCHObject ) );

    return self;
}

CCH_API void CCH_object_update_speed( CCHObject *self ) {
    self->speed_left = self->speed;
}

CCH_API void CCH_object_store_on( CCHObject *self, SPHStringBuffer *buffer ) {
    SPH_string_buffer_append_format( buffer, "name %s\n", self->name != NULL ? self->name : "" );
}

CCH_API void CCH_object_animate( CCHObject *self, int32_t direction ) {
    (void)direction;

    self->state = 0;
}

CCH_API void CCH_object_free2( CCHObject *self, int32_t flags ) {
    (void)flags;

    SPH_DELETE( self );
}

CCH_API void CCH_object_dispatch( CCHObject *self ) {
    (void)self;

    // オブジェクトごとの行動 AI はまだ実装されていません。
}

CCH_API int32_t CCH_object_was_destroyed( CCHObject *self, CCHtag_t tag ) {
    return self->count != (size_t)tag;
}
