




CCH_API void CCH_knowledge_incremental(void) {
    int32_t             last     = 0;

    CCHSocketList       sockets;
    size_t              size     = 0U;

    SPHStringBuffer    *buffer   = NULL;
    
    CCHKnowledgeItem   *item     = NULL;
    CCHKnowledgePlayer *current  = The_knowledge_global;
    CCHKnowledgePlayer *prev     = NULL;

    while ( current ) {
        CCHPlayer          *a_player = NULL;
        for ( a_player = The_first_player; a_player != NULL; a_player = a_player->_next ) {
            if ( SPH_str_equals( a_player->object->name, current->player_name )  ) {

                break;
            }
        }

        if ( a_player == NULL ) {
            if ( prev == NULL ) {
                The_knowledge_global = current->_next;
            } else {
                prev->_next          = current->_next;
            }

            CCH_knowledge_free_player( current );

            return ;
        }

        if ( current->sent_up_to == -1 || current->sent_up_to == current->item_count ) {
            prev    = current;
            current = prev->_next;

            continue;
        }

        last = SPH_MIN( current->sent_up_to + 50, current->item_count );
        CCH_socket_list_init( &sockets );
        CCH_socket_list_append_string( &sockets, "addknowledge " );
        for ( int32_t i = current->sent_up_to; i < last; +; i ) {
            item = current->items[i];

            buffer = SPH_string_buffer_new();
        }
    }
}
