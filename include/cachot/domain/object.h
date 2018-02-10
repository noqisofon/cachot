#pragma once

#include "cachot/server/defines.h"

typedef    int32_t    CCHtag_t;

typedef struct cch_object {
    uint8_t                   type;
    int32_t                   state;

    struct cch_object        *env;
    struct cch_map_define    *map;
    SPHStr                    name;

    struct cch_object        *active_prev;
    struct cch_object        *active_next;

    double                    x;
    double                    y;

    uint32_t                  casting_time;
    double                    speed;
    double                    speed_left;

    uint32_t                  temp_animation_id;
    int32_t                   temp_anim_speed;

    int32_t                   anim_speed;
    int32_t                   last_anim;

    size_t                    count;
} CCHObject;


enum cch_object_free_type {
    CCH_OBJECT_FREE_NO_DESTROY_CALLBACK = 2,
};


#define CCH_OBJECT_QUERY_FLAG(_that_, _flag_)   \
    ((_that_)->flags[_p_ / 32] |= ( 1U << (_flag_ % 32) ))


/*!
 *
 */
void CCH_object_update_speed(CCHObject *self);


/*!
 *
 */
CCH_API void CCH_object_store_on(CCHObject *self, SPHStringBuffer *buffer);


/*!
 *
 */
CCH_API void CCH_object_animate(CCHObject *self, int32_t direction);


/*!
 *
 */
CCH_API void CCH_object_free2(CCHObject *self, int32_t flags);
