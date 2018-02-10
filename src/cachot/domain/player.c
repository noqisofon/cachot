#include "config.h"

#ifdef HAVE_STDDEF_H
#   include <stddef.h>
#endif  /* def HAVE_STDDEF_H */

#ifdef HAVE_STDINT_H
#   include <stdint.h>
#endif  /* def HAVE_STDINT_H */

#include <stdlib.h>

#include "cachot/global.h"

#include "cachot/domain/player.h"


CCH_API void CCH_player_enter_exit(CCHObject *a_player, CCHObject *exit_at) {
}

CCH_API void CCH_player_enter_spawn_point(CCHObject *a_player) {
    CCHObject *tmp     = NULL;
    CCHMap    *old_map = a_player->map;

    tmp = CCH_object_new();

    CCH_OBJECT_EXIT_PATH(tmp) = SPH_share_string_append( a_player->controller->spawn_map_name );
    CCH_OBJECT_EXIT_X(tmp)    = a_player->controller->spawn_x;
    CCH_OBJECT_EXIT_Y(tmp)    = a_player->controller->spawn_y;

    CCH_player_enter_exit( a_player, tmp );

    if ( old_map == a_player->map && SPH_str_compare( a_player->controller->spawn_map_name, old_map->path ) ) {
        CCH_DEBUG( _("Player %s spawn location %s is invalid - going to emergency location (%s)\n"),
                   a_player->name,
                   a_player->controller->spawn_map_name,
                   The_settings.emergency_map_name );

        SPH_str_assign( a_player->controller->spawn_map_name, The_settings.emergency_map_name );

        a_player->controller->spawn_x = The_settings.emergency_x;
        a_player->controller->spawn_y = The_settings.emergency_y;

        CCH_OBJECT_EXIT_PATH(tmp) = SPH_share_string_append( a_player->controller->spawn_map_name );
        CCH_OBJECT_EXIT_X(tmp)    = a_player->controller->spawn_x;
        CCH_OBJECT_EXIT_Y(tmp)    = a_player->controller->spawn_y;

        CCH_player_enter_exit( a_player, tmp );
    }

    CCH_object_free2( tmp, CCH_OBJECT_FREETYPE_NO_DESTROY_CALLBACK );
}
