set(ELK_SOURCES
asockind.cc
cyctimer.cc
emitcode.cc
forbid.gr.gen.cc
genml.cc
glr.cc
gramanl.cc
gramast.ast.gen.cc
gramexpl.cc
gramlex.yy.cc
grammar.cc
grampar.cc
grampar.tab.cc
mlsstr.cc
parsetables.cc
ptreeact.cc
ptreenode.cc
useract.cc
)

add_library(elkhound STATIC ${ELK_SOURCES})