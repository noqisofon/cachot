#include "config.h"

#ifdef HAVE_STDDEF_H
#   include <stddef.h>
#endif  /* def HAVE_STDDEF_H */

#ifdef HAVE_STDINT_H
#   include <stdint.h>
#endif  /* def HAVE_STDINT_H */

#ifdef HAVE_SYS_TYPES_H
#   include <sys/types.h>
#endif  /* def HAVE_SYS_TYPES_H */

#ifdef HAVE_UNISTD_H
#   include <unitsd.h>
#endif  /* def HAVE_UNISTD_H */

#ifdef HAVE_ASSERT_H
#   include <assert.h>
#endif  /* def HAVE_ASSERT_H */

#include "cachot/cachot.h"

#include "cachot/domain/object.h"
#include "cachot/domain/time.h"
#include "cachot/domain/player.h"
#include "cachot/domain/world.h"

#include "cachot/utils/logging.h"

#include "cachot/server/init.h"
#include "cachot/server/loop.h"
#include "cachot/server/plugin.h"

#include "cachot/server/server.h"


static const char WeekDays[7][] = {
    _("Sun"),
    _("Mon"),
    _("Tue"),
    _("Wed"),
    _("Thu"),
    _("Fri"),
    _("Sat")
};


/*!
 *
 */
static char *clean_path(const char *filename, char *new_path, size_t size) {
    char *it;

    snprintf( new_path, size, "%s", filename );
    for ( it = new_path; *it != '\0'; ++ it ) {
        if ( *it == '/' ) {
            *it = '_';
        }
    }
    return new_path;
}

void CCH_server_dispatch_event(void) {
    CCHObject *that;
    CCHObject  maker;

    CCHtag_t   tag;

    CCH_player_dispatch1();
    memset( &maker, 0, sizeof(CCHObject) );

    maker.active_next = The_active_objects;

    if ( maker.active_next ) {
        maker.active_next->active_prev = &maker;
    }
    maker.active_prev = NULL;

    The_active_objects = &maker;

    while ( maker.active_next ) {
        that = maker.active_next;
        tag  = that->count;

        // 
        that->active_prev = maker.active_prev;

        if ( that->active_prev ) {
            that->active_prev->active_prev = that;
        } else {
            The_active_objects             = that;
        }

        maker.active_next = that->active_next;

        if ( maker.active_next ) {
            maker.active_next->active_prev = &maker;
        }
        maker.active_prev = that;
        that->active_next = &maker;

        //
        if ( CCH_OBJECT_QUERY_FLAG( that, CCH_FLAG_FREED ) ) {
            CCH_ERROR( _("BUG: %s(): Free object on list\n"), __FUNCTION__ );

            that->speed = 0;
            CCH_object_update_speed( that );

            continue;
        }

        /*
         * 
         */
        if ( CCH_OBJECT_QUERY_FLAG( that, CCH_FLAG_REMOVED ) &&
             that->type != CCH_OBJECT_TYPE_PLAYER &&
             that->map &&
             that->map->in_memory != CCH_MAP_IN_MEMORY ) {
            SPHStringBuffer    *buffer;
            char               *diff;

            CCH_ERROR( _("BUG: %s(): Remove object on list\n"), __FUNCTION__ );
            buffer = SPH_string_buffer_new();

            CCH_object_store_on( that, buffer );
            diff   = SPH_string_buffer_finish( buffer );
            CCH_ERROR( _("%s\n"), diff );

            free( diff );
            CCH_object_free2( that, CCH_OBJECT_FREE_NO_DESTROY_CALLBACK );

            continue;
        }

        if ( !that->speed ) {
            CCH_ERROR( _("BUG: %s(): Object %s has no speed, but is on active list\n"), __FUNCTION__,
                       that->arch->name );

            CCH_object_update_speed( that );

            continue;
        }

        if ( that->map == NULL &&
             that->env == NULL &&
             that->name &&
             that->type != CCH_OBJECT_TYPE_MAP ) {
            CCH_ERROR( _("BUG: %s(): Object without map or inventory is on active list: %s (%d)\n"), __FUNCTION__,
                       that->name,
                       that->count );

            that->speed = 0;
            CCH_object_update_speed( that );

            continue;
        }

        if ( that->map && that->map->in_memory != CCH_MAP_IN_MEMORY ) {
            CCH_ERROR( _("BUG: %s(): Processing object on swapped out map: %s (%d), map=%s"), __FUNCTION__,
                       that->name,
                       that->count,
                       that->map->arch );
        }

        if ( ( that->anim_speed && that->last_anim >= that->anim_speed ) ||
             ( that->temp_animation_id && that->last_anim >= that->temp_anim_speed ) ) {
            ++ that->state;

            if ( that->type == CCH_OBJECT_TYPE_PLAYER || that->type == CCH_OBJECT_TYPE_MONSTER ) {
                CCH_object_animate( that, that->facing );
            } else {
                CCH_object_animate( that, that->direction );
            }

            that->last_anim = 1;

        } else {
            ++ that->last_anim;
        }

        if ( that->speed_left > 0 ) {
            -- that->speed_left;
            CCH_object_dispatch( that );

            if ( CCH_object_was_destroyed( that, tag ) ) {

                continue;
            }
        }

        if ( The_settings.casting_time == TRUE && that->casting_time > 0 ) {
            -- that->casting_time;
        }

        if ( that->speed_left <= 0 ) {
            that->speed_left += SPH_FLOAT_ABS( that->speed );
        }
        
    }

    if ( maker.active_prev != NULL ) {
        maker.active_prev->active_next = NULL;
    } else {
        The_active_objects = NULL;
    }

    CCH_player_dispatch2();
}

/*!
 *
 */
static void perform_specials(void) {
    uint32_t tick = CCH_time_ticks();

    if ( ! ( ticks %  10 ) ) {
        CCH_knowledge_incremental();
    }

#ifdef CCH_ALLOW_WATCHDOG
    if ( ! ( ticks % 503 ) ) {
        CCH_watchdog();
    }
#endif  /* def CCH_ALLOW_WATCHDOG */

    
}

int32_t CCH_server_main(int32_t argc, char **argv) {
#ifdef CCH_PLATFORM_ON_WIN32
    SPH_set_fmode( SPH_O_BINARY );
    is_running = true;
#endif  /* def CCH_PLATFORM_ON_WIN32 */

#ifndef CCH_PLATFORM_ON_WIN32
    // root で実行しようとしているかどうかチェックします。
    if ( SPH_get_user_id() == 0 || SPH_get_execution_user_id() == 0 ) {
        SPH_note( _("Running cachot-server as root is bad idea; aborting!\nPlease run it again as a normal, unprivileged user.\n") );

        return 1;
    }
#endif  /* ndef CCH_PLATFORM_ON_WIN32 */

#ifdef CCH_DEBUG_MALLOC_LEVEL
    SPH_set_malloc_debug_level( CCH_DEBUG_MALLOC_LEVEL );
#endif  /* def CCH_DEBUG_MALLOC_LEVEL */

    CCH_init( argc, argv );
    CCH_plugin_init();

    while ( is_running ) {
        CCH_reset_error_quantity();

        CCH_server_start();
        CCH_server_dispatch_event();
        CCH_world_tick_timers();
        CCH_world_check_active_maps();

        perform_specials();

        CCH_time_sleep_delta();
    }

    return 0;
}
