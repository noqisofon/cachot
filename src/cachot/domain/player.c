



CCH_API void CCH_player_enter_spawn_point(CCHObject *a_player) {
    CCHObject *tmp     = NULL;
    CCHMap    *old_map = a_player->map;

    tmp = CCH_object_new();

    CCH_OBJECT_EXIT_PATH(tmp) = SPH_str_append( a_player->controller->spawn_map );
    CCH_OBJECT_EXIT_X(tmp)    = a_player->controller->spawn_x;
    CCH_OBJECT_EXIT_Y(tmp)    = a_player->controller->spawn_y;

    CCH_player_enter_exit( a_player, tmp );

    if ( old_map == a_player->map && SPH_str_compare( a_player->controller->spawn_map, old_map->path ) ) {
        CCH_DEBUG( _("Player %s spawn location %s is invalid - going to emergency location (%s)\n"),
                   a_player->name,
                   a_player->controller->spawn_map,
                   The_setting.emergency_map_name );

        SPH_str_copy( a_player->controller->spawn_map, The_setting.emergency_map_name );

        a_player->controller->spawn_x = The_setting.emergency_x;
        a_player->controller->spawn_y = The_setting.emergency_y;

        CCH_OBJECT_EXIT_PATH(tmp) = SPH_str_append( a_player->controller->spawn_map );
        CCH_OBJECT_EXIT_X(tmp)    = a_player->controller->spawn_x;
        CCH_OBJECT_EXIT_Y(tmp)    = a_player->controller->spawn_y;

        CCH_player_enter_exit( a_player, tmp );
    }

    CCH_object_free2( tmp, CCH_FREE_OBJECT_NO_DESTROY_CALLBACK );
}
