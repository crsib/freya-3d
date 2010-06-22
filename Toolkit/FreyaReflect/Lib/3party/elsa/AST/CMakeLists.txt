
set(AST_SOURCE
agramlex.yy.cc
agrampar.cc
agrampar.tab.cc
ast.ast.cc
astgen.cc
asthelp.cc
ccsstr.cc
embedded.cc
ext1.cc
gramlex.cc
locstr.cc
reporterr.cc
towner.cc
xmlhelp.cc
)
add_library(ast STATIC ${AST_SOURCE})