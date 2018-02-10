#pragma once

#include "sapphire/sapphire.h"

#include "cachot/server/internal.h"
#include "cachot/utils/logging.h"


typedef struct cch_settings {
    const SPHStr               log_filename;
    uint16_t                   client_or_server_port;
    CCHLogLevel                debug;

    const SPHStr               local_dir;
    
} CCHSettings;

/*!
 *
 */
extern CCHSettings The_settings;


typedef struct cch_statistics {
    uint64_t                   merge_spell_quantity;
    uint64_t                   spell_hash_full;
    uint64_t                   spell_suppressions;
} CCHStatistics;

/*!
 *
 */
extern CCHStatistics The_statistics;
