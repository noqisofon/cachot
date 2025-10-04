#pragma once

#include <stdint.h>
#include "cachot/server/defines.h"
#include "sapphire/str.h"

typedef struct cch_map {
    SPHStr              name;
    SPHStr              arch;
    SPHStr              background_music;

    char                path[CCH_MAX_HUGE_BUFSIZE];

    int32_t             timeout;
    int32_t             players;
    int32_t             in_memory;
    
    struct cch_map     *_next;
} CCHMap;