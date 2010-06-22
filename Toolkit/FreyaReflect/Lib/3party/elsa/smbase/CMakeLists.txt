set(SMBASE_SOURCES
autofile.cc
bflatten.cc
bit2d.cc
boxprint.cc
flatten.cc
growbuf.cc
hashline.cc
hashtbl.cc
ofstreamts.cc
point.cc
pprint.cc
smregexp.cc
)

add_library(smbase STATIC ${SMBASE_SOURCES})