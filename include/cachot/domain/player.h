#pragma once

#include "cachot/server/defines.h"


typedef struct cch_player {
//    CCHSocket            *socket;
    char                  maplevel[CCH_MAX_BUFSIZE];
    char                  spawn_map_name[CCH_MAX_BUFSIZE];

    int32_t               spawn_x;
    int32_t               spawn_y;

    CCHObject            *object;

    int32_t               language;
    uint32_t              ticks_played;

    struct cch_player    *_next;
} CCHPlayer;
