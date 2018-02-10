#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT(cachot, 0.0.1, ned.rihine@gmai.com)
AC_CONFIG_AUX_DIR([build])
AC_CONFIG_MACRO_DIR([build/macros])
AC_CONFIG_SRCDIR([src/cachot/server/main.c])
AC_CONFIG_HEADERS([include/config.h])
AM_INIT_AUTOMAKE
LT_INIT

# Checks for programs.
AC_PROG_CC
AC_PROG_LIBTOOL

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADER_STDBOOL
AC_CHECK_HEADERS([fcntl.h stddef.h stdint.h stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_INT32_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memset])

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 src/cachot/server/Makefile
                 src/cachot/Makefile
                 src/sapphire/Makefile])

AC_OUTPUT
