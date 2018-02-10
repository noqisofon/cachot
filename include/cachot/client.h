#pragma once

/*!
 *
 */
#define    CCH_MAX_SOCKET_BUFSIZE   (2 + 65535 + 1)


enum cch_ndi_colors {
    CCH_NDI_BLACK      =  0,
    CCH_NDI_WHITE      =  1,
    CCH_NDI_NAVY       =  2,
    CCH_NDI_RED        =  3,
    CCH_NDI_ORANGE     =  4,
    CCH_NDI_BLUE       =  5,
    CCH_NDI_DK_ORANGE  =  6,
    CCH_NDI_GREEN      =  7,
    CCH_NDI_LT_GREEN   =  8,
    CCH_NDI_GRAY       =  9,
    CCH_NDI_BROWN      = 10,
    CCH_NDI_GOLD       = 11,
    CCH_NDI_TAN        = 12,

    CCH_NDI_MAX_COLORS
};

/*!
 *
 */
#define    CCH_NDI_COLOR_MASK 0xff

/*!
 *
 */
#define    CCH_NDI_UNIQUE     0x100
/*!
 *
 */
#define    CCH_NDI_ALL        0x200
/*!
 *
 */
#define    CCH_NDI_ALL_DMS   0x400



enum cch_message_type {
    CCH_MSG_TYPE_BOOK      = 1,
    CCH_MSG_TYPE_CARD      = 2,
    CCH_MSG_TYPE_PAPER     = 3,
    
    CCH_MSG_TYPE_ADMIN     = 8
};


enum cch_message_admin_subtype {
    CCH_MSG_TYPE_ADMIN_LOGIN   = 7,
    CCH_MSG_TYPE_ADMIN_VERSION = 8,
    CCH_MSG_TYPE_ADMIN_PLAYER,
};
