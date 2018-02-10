#include "config.h"

#ifdef HAVE_STDDEF_H
#   include <stddef.h>
#endif  /* def HAVE_STDDEF_H */

#ifdef HAVE_STDINT_H
#   include <stdint.h>
#endif  /* def HAVE_STDINT_H */

#include <stdlib.h>

#include "cachot/global.h"

#include "cachot/domain/knowledge.h"


typedef struct cch_knwoledge_type {
    const SPHStr                    *type;
} CCHKnowledgeType;

typedef struct cch_knowledge_item {
    SPHStr                           item_code;         //!< 内部的なアイテムコード。
    CCHKnowledgeType                *handler;
} CCHKnowledgeItem;

typedef struct cch_knowledge_player {
    SPHStr                           player_name;       //!< プレイヤー名。
    CCHKnowledgeItem               **items;             //!< プレイヤーが知っているアイテム。
    int32_t                          item_quantity;
    int32_t                          item_allocated;
    int32_t                          sent_up_to;

    struct cch_knowledge_player     *_next;
} CCHKnowledgePlayer;

/*!
 *
 */
static CCHKnowledgePlayer* The_knowledge_global = NULL;

/*!
 *
 */
static void knowledge_items_free(CCHKnowledgePlayer *a_player) {
    for ( int32_t i = 0; i < a_player->item_quantity; ++ i ) {
        CCHKnowledgeItem   *item = a_player->items[i];

        SPH_str_free( item->item_code );
        free( item );
    }

    free( a_player->items );

    a_player->items          = NULL;
    a_player->item_quantity  = 0;
    a_player->item_allocated = 0;
}

/*!
 *
 */
static void knowledge_player_free(CCHKnowledgePlayer *a_player) {
    knowledge_items_free( a_player );
    SPH_str_free( a_player->player_name );
    free( a_player );
}

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

            knowledge_player_free( current );

            return ;
        }

        if ( current->sent_up_to == -1 || current->sent_up_to == current->item_quantity ) {
            prev    = current;
            current = prev->_next;

            continue;
        }

        last = SPH_MIN( current->sent_up_to + 50, current->item_quantity );
        CCH_socket_list_init( &sockets );
        CCH_socket_list_append_string( &sockets, "addknowledge " );
        for ( int32_t i = current->sent_up_to; i < last; ++ i ) {
            item = current->items[i];

            buffer = SPH_string_buffer_new();
        }
    }
}
