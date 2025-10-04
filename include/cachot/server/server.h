#pragma once

#include "cachot/domain/object.h"
#include "cachot/domain/map.h"
#include "cachot/domain/player.h"

// Constants and Enums
#define CCH_RANDOM() rand()
#define CCH_MAP_ENTER_X(map) 0
#define CCH_MAP_ENTER_Y(map) 0
#define CCH_MAP_WIDTH(map) 0
#define CCH_MAP_HEIGHT(map) 0
#define CCH_MAP_IN_MEMORY 1

enum cch_event_type {
    CCH_EVENT_MAP_LEAVE,
    CCH_EVENT_MAP_ENTER
};

enum cch_insert_type {
    CCH_INSERT_WALK_ON
};

enum cch_object_type {
    CCH_OBJECT_PLAYER,
    CCH_OBJECT_TYPE_PLAYER,
    CCH_OBJECT_TYPE_MONSTER,
    CCH_OBJECT_TYPE_MAP
};

// Global Variables
extern const int Free_area_x[];
extern const int Free_area_y[];
extern SPHBool is_running;
extern CCHObject *The_active_objects;
extern CCHPlayer *The_first_player;
extern CCHSettings The_settings;

// Function Prototypes
CCH_API void CCH_server_show_version(CCHObject *that);
CCH_API void CCH_server_start_info(CCHObject *that);
CCH_API const SPHStr CCH_server_crypt_string(const SPHStr str, const SPHStr salt);
CCH_API int32_t CCH_server_check_password(const SPHStr typed, const SPHStr crypted);
CCH_API void CCH_map_set_timeout(CCHMap *a_map);
CCH_API void CCH_server_dispatch_event(void);
CCH_API int32_t CCH_server_main(int32_t argc, char **argv);

// Functions that should probably be in other headers but are needed by server.c
CCH_API int32_t CCH_map_out_of(CCHMap *map, double x, double y);
CCH_API int32_t CCH_map_blocked(CCHMap *map, CCHObject *obj, double x, double y);
CCH_API int32_t CCH_object_find_free_spot(CCHObject *obj, CCHMap *map, double x, double y, int32_t a, int32_t b);
CCH_API void CCH_object_remove(CCHObject *obj);
CCH_API void CCH_server_execute_global_event(int32_t event_type, CCHObject *obj, CCHMap *map);
CCH_API void CCH_map_object_insert_in_location_at(CCHMap *map, CCHObject *obj, void* null_ptr, int32_t insert_type, double x, double y);
CCH_API void CCH_player_send_background_music(CCHPlayer *player, const SPHStr music);
CCH_API void CCH_object_set_enemy(CCHObject *obj, void* null_ptr);
CCH_API int32_t CCH_object_find_dir2(CCHObject *from, CCHObject *to);
CCH_API void CCH_pet_remove_all(void);
CCH_API void CCH_swap_below_max(const SPHStr path);
CCH_API void CCH_request_map_next_map_command(struct CCHSocket **socket);
CCH_API void CCH_swap_map(CCHMap *map);
CCH_API void CCH_player_dispatch1(void);
CCH_API void CCH_object_dispatch(CCHObject *obj);
CCH_API int32_t CCH_object_was_destroyed(CCHObject *obj, CCHtag_t tag);
CCH_API void CCH_player_dispatch2(void);
CCH_API uint32_t CCH_time_ticks(void);
CCH_API void CCH_knowledge_incremental(void);
CCH_API void CCH_init(int32_t argc, SPHStr *argv);
CCH_API void CCH_plugin_init(void);
CCH_API void CCH_reset_error_quantity(void);
CCH_API void CCH_server_start(void);
CCH_API void CCH_world_tick_timers(void);
CCH_API void CCH_world_check_active_maps(void);
CCH_API void CCH_time_sleep_delta(void);
CCH_API void CCH_object_animate(CCHObject *self, int32_t direction);