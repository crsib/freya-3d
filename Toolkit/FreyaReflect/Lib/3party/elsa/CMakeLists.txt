
include_directories( ../Include/elsa )

add_subdirectory( AST )
add_subdirectory( elkhound )
add_subdirectory( smbase )

set(ELSA_SOURCE 
./astvisit.cc
./ast_build.cc
./baselexer.cc
./bpprint.cc
./builtinops.cc
./cc.ast.gen.cc
./cc.gr.gen.cc
./cc2c.cc
./ccparse.cc
./cc_ast_aux.cc
./cc_elaborate.cc
./cc_env.cc
./cc_err.cc
./cc_flags.cc
./cc_lang.cc
./cc_print.cc
./cc_scope.cc
./cc_tcheck.cc
./cc_tokens.cc
./cc_type.cc
./cfg.cc
./const_eval.cc
./cppundolog.cc
./gnu.cc
./ia64mangle.cc
./id_obj_dict.cc
./implconv.cc
./implint.cc
./integrity.cc
./iptparse.cc
./iptree.cc
./kandr.cc
./lexer.cc
./lexer.yy.cc
./lookupset.cc
./mangle.cc
./mtype.cc
./notopt.cc
./overload.cc
./parssppt.cc
./serialno.cc
./sprint.cc
./stdconv.cc
./template.cc
./typelistiter.cc
./variable.cc
./xml_ast_reader.cc
./xml_do_read.cc
./xml_file_reader.cc
./xml_file_writer.cc
./xml_lex.gen.yy.cc
./xml_lexer.cc
./xml_reader.cc
./xml_type_reader.cc
./xml_type_writer.cc
./xml_writer.cc
)

add_library(elsa STATIC ${ELSA_SOURCE})
