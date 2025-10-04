#pragma once

#include "cachot/server/defines.h"
#include "cachot/domain/object.h"

// Forward declarations
struct CCHSocket;

enum cch_player_range {
    CCH_RANGE_GOREM,
    CCH_PLAYER_RANGE_MAX
};


typedef struct cch_player {
    struct CCHSocket     *socket;
    char                  maplevel[CCH_MAX_BUFSIZE];
    char                  spawn_map_name[CCH_MAX_BUFSIZE];

    int32_t               spawn_x;
    int32_t               spawn_y;

    CCHObject            *object;
    CCHObject            *ranges[CCH_PLAYER_RANGE_MAX];

    int32_t               language;
    uint32_t              ticks_played;
    int32_t               count;
    int32_t               gorem_count;

    struct cch_player    *_next;
} CCHPlayer;