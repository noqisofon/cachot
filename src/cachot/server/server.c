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
#   include <unistd.h>
#endif  /* def HAVE_UNISTD_H */

#ifdef HAVE_ASSERT_H
#   include <assert.h>
#endif  /* def HAVE_ASSERT_H */

#include "cachot/cachot.h"
#include "cachot/client.h"
#include "cachot/version.h"

#include "cachot/utils/logging.h"

#include "cachot/global.h"

#include "cachot/server/init.h"
#include "cachot/server/info.h"
#include "cachot/server/loop.h"
#include "cachot/server/plugin.h"

#include "cachot/server/server.h"


static const SPHStr WeekDays[7] = {
    _("Sun"),
    _("Mon"),
    _("Tue"),
    _("Wed"),
    _("Thu"),
    _("Fri"),
    _("Sat")
};

/*!
 * 指定したプレイヤーを指定したマップに移動させます。
 *
 * \param [in,out] moving_player 移動するプレイヤーオブジェクト。
 * \param [in,out] next_map      移動先のマップ。
 * \param [in]     x             移動先のマップのタイルの X 座標。
 * \param [in]     y             移動先のマップのタイルの Y 座標。
 *
 * 
 *
 * \seealso 
 */
static void enter_map(CCHObject *moving_player, CCHMap *next_map, int32_t x, int32_t y);

/*!
 *
 */
static SPHStr clean_path(const SPHStr filename, SPHStr new_path, size_t size);

/*!
 * 
 */
static void perform_specials(void);


CCH_API void CCH_server_show_version(CCHObject *that) {
    CCH_info_draw_ext_format( CCH_NDI_UNIQUE, 0,
                              that,
                              CCH_MSG_TYPE_ADMIN, CCH_MSG_TYPE_ADMIN_VERSION,
                              _("This is Cachot v%s"), CCH_FULL_VERSION );
    CCH_info_draw_ext( CCH_NDI_UNIQUE, 0,
                       that,
                       CCH_MSG_TYPE_ADMIN, CCH_MSG_TYPE_ADMIN_VERSION,
                       _("The authors can be reached at ??????????????????????????????????????"));
}


CCH_API void CCH_server_start_info(CCHObject *that) {
    CCH_info_draw_ext_format( CCH_NDI_UNIQUE, 0,
                              that,
                              CCH_MSG_TYPE_ADMIN, CCH_MSG_TYPE_ADMIN_LOGIN,
                              _("Welcome to Cachot, v%s\nPress `?` for help\n"),
                              CCH_VERSION );

    CCH_info_draw_ext_format( CCH_NDI_UNIQUE | CCH_NDI_ALL | CCH_NDI_DK_ORANGE, 5,
                              that,
                              CCH_MSG_TYPE_ADMIN, CCH_MSG_TYPE_ADMIN_PLAYER,
                              _("$s entered the game."),
                              that->name );
}

#define SPH_PICK_ARRAY(_ary_, _len_)      _ary_[CCH_RANDOM() % (int32_t)_len_]

CCH_API const SPHStr CCH_server_crypt_string(const SPHStr str, const SPHStr salt) {
#if defined(CCH_PLATFORM_IS_WIN32) || ( defined(CCH_PLATFORM_IS_FREEBSD) && !defined(HAVE_LIBDES) )
    return str;
#else  /* defined(CCH_PLATFORM_IS_WIN32) || ( defined(CCH_PLATFORM_IS_FREEBSD) && !defined(HAVE_LIBDES) ) */
    static const SPHStr glyph_table        = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";

    size_t              glyph_table_length = SPH_str_length( glyph_table );

    char cs[2];

    if ( salt == NULL ) {
        cs[0] = SPH_PICK_ARRAY( glyph_table, glyph_table_length );
        cs[1] = SPH_PICK_ARRAY( glyph_table, glyph_table_length );
    } else {
        cs[0] = salt[0];
        cs[1] = salt[1];
    }
#   if defined(HAVE_LIBDES)
    return (SPHStr )des_crypt( str, cs );
#   else
    return (SPHStr )crypt( str, cs );
#   endif  /* defined(HAVE_LIBDES) */
#endif  
}

CCH_API int32_t CCH_server_check_password(const SPHStr typed, const SPHStr crypted) {
    if ( SPH_str_length( crypted ) == 0 ) {
        return SPH_str_length( typed ) == 0
            ? SPHOrder_More
            : SPHOrder_Same;
    }
    return SPH_str_compare( CCH_server_crypt_string( typed, crypted ), crypted );
}

static void enter_map(CCHObject *moving_player, CCHMap *next_map, int32_t x, int32_t y) {
    CCHMap *old_map = moving_player->map;

    if ( CCH_map_out_of( next_map, x, y ) ) {
        // 移動先マップから移動先ポイント(x, y)が外れていた場合:
        /*
           外れているというのは、マップのサイズから外れてたってやつ。
           移動可能なタイルじゃなかったというのはこの次にやる。
         */
        // 移動先マップの enter(x, y) にプレイヤーを移動させようとする。
        if ( moving_player->x == x ) {
            moving_player->x = CCH_MAP_ENTER_X(next_map);
        }
        if ( moving_player->y == y ) {
            moving_player->y = CCH_MAP_ENTER_Y(next_map);
        }

        x = CCH_MAP_ENTER_X(next_map);
        y = CCH_MAP_ENTER_Y(next_map);
        if ( CCH_map_out_of( next_map, x, y ) ) {
            // それでも外れてた:
            CCH_ERROR( _("enter_map(): map %s provides invalid default enter location (%d, %d) > (%d, %d)"),
                       next_map->path,
                       x, y,
                       CCH_MAP_WIDTH(next_map), CCH_MAP_HEIGHT(next_map) );
            
            CCH_info_draw_ext( CCH_NDI_UNIQUE, 0, moving_player,
                               CCH_MSG_TYPE_COMMAND, CCH_MSG_TYPE_COMMAND_FAILURE,
                               _("The exit is closed") );

            return ;
        }
    }

    // プレイヤーを置くことができるところ(free spot)かどうかを調べます。
    if ( CCH_map_blocked( next_map, moving_player, x, y ) ) {
        //
        int32_t i = CCH_object_find_free_spot( moving_player,
                                               next_map,
                                               x, y,
                                               1, CCH_SIZE_OFF_FREE1 + 1 );
        if ( i != CHH_NOT_FOUND ) {
            x += Free_area_x[i];
            y += Free_area_x[i];
        } else {
            CCH_INFO( _("enter_map(): Could not find free spot for player - will dump on top of object {%s => (%d, %d)}"), next_map->path, x, y );
        }
    }

    if ( !CCH_OBJECT_QUERY_FLAG( moving_player, CCH_OBJECT_FLAG_REMOVED ) ) {
        CCH_object_remove( moving_player );
    }
    if ( moving_player->map != NULL ) {
        // 移動前のマップでマップを離れた時のイベントを起こします。
        CCH_server_execute_global_event( CCH_EVENT_MAP_LEAVE,
                                         moving_player,
                                         moving_player->map );
    }

    // プレイヤーを移動先マップへ置きます。
    CCH_map_object_insert_in_location_at( next_map,
                                          moving_player,
                                          NULL,
                                          CCH_INSERT_WALK_ON, x, y );

    // マップに入った時のイベントを起こします。
    CCH_server_execute_global_event( CCH_EVENT_MAP_ENTER,
                                     moving_player,
                                     moving_player->map );

    if ( moving_player->controller ) {
        CCH_player_send_background_music( moving_player->controller, next_map->background_music );
    }

    next_map->timeout = 0;
    CCH_object_set_enemy( moving_player, NULL );

    if ( moving_player->controller ) {
        SPH_str_assign( moving_player->controller->map_level, next_map->path );
        moving_player->controller->count = 0;
    }

    // 幾つかのゴーレムを更新します。
    if ( moving_player->type == CCH_OBJECT_PLAYER && moving_player->controller->ranges[CCH_RANGE_GOREM] != NULL ) {
        int32_t i = CCH_object_find_free_spot( moving_player->controller->ranges[CCH_RANGE_GOREM],
                                               next_map,
                                               x, y,
                                               1,
                                               CCH_SIZE_OFF_FREE1 );
        CCH_object_remove( moving_player->controller->ranges[CCH_RANGE_GOREM] );
        if ( i == CHH_NOT_FOUND ) {
            CCH_object_remove_friendly_object( moving_player->controller->ranges[CCH_RANGE_GOREM] );

            CCH_object_free_drop_inventory( moving_player->controller->ranges[CCH_RANGE_GOREM] );

            moving_player->controller->ranges[CCH_RANGE_GOREM] = NULL;
            moving_player->controller->gorem_count = 0;
        } else {
            CCH_map_object_insert_in_location_at( next_map,
                                                  moving_player->controller->ranges[CCH_RANGE_GOREM],
                                                  NULL,
                                                  0,
                                                  x + Free_area_x[i], y +  + Free_area_x[i] );
            moving_player->controller->ranges[CCH_RANGE_GOREM]->direction = CCH_object_find_dir2( moving_player->x_object->controller->[RANGE_GOREM]->x,
                                                                                                  moving_player->x_object->controller->[RANGE_GOREM]->y );
        }
    }
    moving_player->direction = 0;

    CCH_pet_remove_all();

    if ( old_map != next_map ) {
        if ( old_map ) {
            if ( old_map->players <= 0 ) {
                CCH_map_set_timeout( old_map );
            }
        }
    }
    CCH_swap_below_max( next_map->path );

    if ( moving_player->type == CCH_OBJECT_TYPE_PLAYER ) {
        CCH_request_map_next_map_command( &moving_player->controller->socket );
    }
}


CCH_API void CCH_map_set_timeout(CCHMap *a_map) {
#if CCH_MAP_MAX_TIMEOUT
    a_map->timeout = CCH_MAP_TIMEOUT(a_map);

#   if CCH_MAP_MIN_TIMEOUT
    if ( a_map->timeout < CCH_MAP_MIN_TIMEOUT ) {
        a_map->timeout = CCH_MAP_MIN_TIMEOUT
    }
#   endif  /* CCH_MAP_MIN_TIMEOUT */
    
    if ( a_map->timeout > CCH_MAP_MAX_TIMEOUT ) {
        a_map->timeout = CCH_MAP_MAX_TIMEOUT
    }
#else
    CCH_swap_map( a_map );
#endif  /* CCH_MAP_MAX_TIMEOUT */
}

static SPHStr clean_path(const SPHStr filename, SPHStr new_path, size_t size) {
    SPHStr it;

    snprintf( new_path, size, "%s", filename );
    for ( it = new_path; *it != '\0'; ++ it ) {
        if ( *it == '/' ) {
            *it = '_';
        }
    }
    return new_path;
}

CCH_API void CCH_server_dispatch_event(void) {
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
            CCH_ERROR( _("BUG: CCH_server_dispatch_event(): Free object on list\n") );

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

            CCH_ERROR( _("BUG: CCH_server_dispatch_event(): Remove object on list\n") );
            buffer = SPH_string_buffer_new();

            CCH_object_store_on( that, buffer );
            diff   = SPH_string_buffer_finish( buffer );
            CCH_ERROR( _("%s\n"), diff );

            free( diff );
            CCH_object_free2( that, CCH_OBJECT_FREE_NO_DESTROY_CALLBACK );

            continue;
        }

        if ( !that->speed ) {
            CCH_ERROR( _("BUG: CCH_server_dispatch_event(): Object %s has no speed, but is on active list\n"), that->arch->name );

            CCH_object_update_speed( that );

            continue;
        }

        if ( that->map == NULL &&
             that->env == NULL &&
             that->name &&
             that->type != CCH_OBJECT_TYPE_MAP ) {
            CCH_ERROR( _("BUG: CCH_server_dispatch_event(): Object without map or inventory is on active list: %s (%d)\n"),
                       that->name,
                       that->count );

            that->speed = 0;
            CCH_object_update_speed( that );

            continue;
        }

        if ( that->map && that->map->in_memory != CCH_MAP_IN_MEMORY ) {
            CCH_ERROR( _("BUG: CCH_server_dispatch_event(): Processing object on swapped out map: %s (%d), map=%s"),
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

        if ( The_settings.casting_time == true && that->casting_time > 0 ) {
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

CCH_API int32_t CCH_server_main(int32_t argc, SPHStr *argv) {
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
