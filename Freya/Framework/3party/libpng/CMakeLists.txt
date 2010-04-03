#libpng build file
MESSAGE(STATUS "Configuring libpng")
SET( LIB_PNG_SOURCES
png.h
pngconf.h

png.c
pngconf.h
pngerror.c
pnggccrd.c
pngget.c
pngmem.c
pngpread.c
pngread.c
pngrio.c
pngrtran.c
pngrutil.c
pngset.c
pngtrans.c
pngvcrd.c
pngwio.c
pngwrite.c
pngwtran.c
pngwutil.c
)

INCLUDE_DIRECTORIES( ../zlib )
ADD_DEFINITIONS( -DPNG_USER_MEM_SUPPORTED )
ADD_LIBRARY( png STATIC ${LIB_PNG_SOURCES} )
