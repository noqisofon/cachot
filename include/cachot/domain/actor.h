#pragma once

#include "cachot/cachot.h"


/*!
 * \struct cch_actor_ability
 * 
 */
struct cch_actor_ability {
    uint16_t           strength;        //!< 筋力
    uint16_t           dexterity;       //!< 敏捷
    uint16_t           consitution;     //!< 耐久
    uint16_t           intelligence;    //!< 知力
    uint16_t           wisdom;          //!< 判断
    uint16_t           charisma;        //!< 魅力
};

typedef struct cch_actor_ability CCHActorAbility;
