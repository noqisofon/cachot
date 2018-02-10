#pragma once

#if defined(__GNU__) || defined(SAPPHIRE_TARGET_OS_WIN32)
#   include <stddef.h>
#endif  /* defined(__GNU__) || defined(SAPPHIRE_TARGET_OS_WIN32) */

#ifndef SPH_EXTERN_C_BEGIN
#   define    SPH_EXTERN_C_BEGIN     extern "C" {
#   define    SPH_EXTERN_C_END       }
#else
#   define    SPH_EXTERN_C_BEGIN
#   define    SPH_EXTERN_C_END
#endif  /* ndef SPH_EXTERN_C_BEGIN */

#ifdef SAPPHIRE_TARGET_OS_WIN32

#   ifdef SAPPHIRE_DLL_BUINDING
#       define SPH_DECLSPEC     __declspec(dllexport)
#   else
#       define SPH_DECLSPEC     __declspec(dllimport)
#   endif  /* def SAPPHIRE_DLL_BUINDING */

#   ifndef SPH_EXTERN
#       if defined(__cplusplus)
#           define    SPH_EXTERN    extern "C"   SPH_DECLSPEC
#       elif !defined(__cplusplus)
#           define    SPH_EXTERN    extern       SPH_DECLSPEC
#       elif defined(__cplusplus)
#           define    SPH_EXTERN    extern       SPH_DECLSPEC
#       else
#           define    SPH_EXTERN
#       endif  /* defined(__cplusplus) */
#   endif  /* ndef SPH_EXTERN */
#else
#   define    SPH_EXTERN    extern
#endif  /* def SAPPHIRE_TARGET_OS_WIN32 */

#define    SPH_API    SPH_EXTERN



typedef enum sph_order {
    SPHOrder_Less        = -1,
    SPHOrder_Same        =  0,
    SPHOrder_More        =  1
} SPHOrder;
