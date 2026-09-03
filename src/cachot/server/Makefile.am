
lib_LTLIBRARIES = libcachot_server.la

libcachot_server_la_SOURCES = account.c info.c init.c loop.c plugin.c server.c socket_list.c

bin_PROGRAMS = cachot-server

cachot_server_SOURCES = main.c

cachot_server_LDADD = libcachot_server.la \
                       ../domain/libcachot_domain.la \
                       ../utils/libcachot_utils.la \
                       ../../sapphire/libsapphire.la
