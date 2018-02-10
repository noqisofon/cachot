#pragma once


typedef    struct cch_map {
    SPHStr              name;

    char                path[CCH_MAX_HUGE_BUFSIZE];
    
    struct cch_map     *_next;
} CCHMap;
