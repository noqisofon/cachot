#pragma once

#include "cachot/cachot.h"


/*!
 * \struct cch_living_status
 * 
 */
typedef struct cch_living_status {
    uint16_t           strength;             //!< 筋力
    uint16_t           dexterity;            //!< 敏捷
    uint16_t           consitution;          //!< 耐久
    uint16_t           intelligence;         //!< 知力
    uint16_t           wisdom;               //!< 判断
    uint16_t           charisma;             //!< 魅力

    int16_t            weapon_class;         //!< ウェポン・クラス
    int16_t            armour_class;         //!< アーマー・クラス

    int16_t            luck;                 //!< 運

    int16_t            hit_point;            //!< 現在のヒットポイント
    int16_t            max_hit_point;        //!< 最大ヒットポイント

    int16_t            magic_point;          //!< 現在のマジックポイント
    int16_t            max_magic_point;      //!< マジックポイント

    int16_t            grace;
    int16_t            max_grace;

    int32_t            damage;
    int64_t            experience;           //!< 経験値。

    int32_t            food;
    
} CCHLivingStatus;
