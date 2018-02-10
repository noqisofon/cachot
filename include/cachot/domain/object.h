#pragma once

#include "cachot/server/defines.h"

typedef    int32_t    CCHtag_t;

typedef struct cch_object {
    uint8_t                   type;
    int32_t                   state;

    struct cch_player        *controller;

    struct cch_object        *next;
    struct cch_object        *prev;
    struct cch_object        *active_next;
    struct cch_object        *active_prev;

    struct cch_object        *env;

    struct cch_object        *more;
    struct cch_object        *head;

    struct cch_map           *map;

    const SPHStr              name;
    SPHStr                    slaying;

    double                    x;
    double                    y;

    int32_t                   weight;

    struct cch_living_status  stats;

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
    CCH_OBJECT_FREETYPE_INVENTORY           = 1,
    CCH_OBJECT_FREETYPE_NO_DESTROY_CALLBACK = 2,
    CCH_OBJECT_FREETYPE_DROP_ABOVE_FLOOR    = 4
};


#define CCH_OBJECT_QUERY_FLAG(_that_, _flag_)   \
    ((_that_)->flags[_p_ / 32] |= ( 1U << (_flag_ % 32) ))

#define CCH_OBJECT_EXIT_PATH(_self_)  (_self_)->slaying
#define CCH_OBJECT_EXIT_LEVEL(_self_) (_self_)->stats.food
#define CCH_OBJECT_EXIT_X(_self_)     (_self_)->stats.hit_point
#define CCH_OBJECT_EXIT_Y(_self_)     (_self_)->stats.magic_point

/*!
 *
 */
CCH_API CCHObject *CCH_object_new(void);

/*!
 *
 */
CCH_API void       CCH_object_update_speed(CCHObject *self);


/*!
 *
 */
CCH_API void       CCH_object_store_on(CCHObject *self, SPHStringBuffer *buffer);


/*!
 *
 */
CCH_API void       CCH_object_animate(CCHObject *self, int32_t direction);


/*!
 *
 */
CCH_API void       CCH_object_free2(CCHObject *self, int32_t flags);
