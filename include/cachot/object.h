#pragma once

#include "sapphire/string_buffer.h"

typedef    int32_t    CCHtag_t;

typedef struct cch_object {
    uint8_t                   type;
    int32_t                   state;

    struct cch_object        *env;
    struct cch_map_define    *map;
    SPHStr                   *name;

    struct cch_object        *active_prev;
    struct cch_object        *active_next;

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


/*!
 *
 */
void CCH_object_update_speed(CCHObject *self);


/*!
 *
 */
void CCH_object_store_on(CCHObject *self, CPHStringBuffer *buffer);


/*!
 *
 */
void CCH_object_animate(CCHObject *self, );


/*!
 *
 */
void CCH_object_free2(CCHObject *self, int32_t flags);
