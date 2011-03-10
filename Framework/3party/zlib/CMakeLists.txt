#zlib build
MESSAGE(STATUS "Configuring zlib")
SET( Z_LIB_SOURCES
#headers
crc32.h
deflate.h
inffast.h
inffixed.h
inflate.h
inftrees.h
trees.h
zconf.h
zlib.h
zutil.h
#cfiles
adler32.c
compress.c
crc32.c
crc32.h
deflate.c
inffast.c
inflate.c
inftrees.c
trees.c
uncompr.c
zconf.h
zutil.c
)

ADD_LIBRARY( zlib STATIC ${Z_LIB_SOURCES} )
