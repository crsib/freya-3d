// cc_tokens.cc
// do not edit; this file automatically generated by
//   make-token-files cc_tokens.tok gnu_ext.tok

#include "cc_tokens.h"     // this module; defines TokenFlag

char const * const tokenNameTable[] = {
  "<EOF>",                                 // TOK_EOF

  // non-keyword name
  "<name>",                                // TOK_NAME

  // classified name (for e.g. cdecl2)
  "<type name>",                           // TOK_TYPE_NAME
  "<variable name>",                       // TOK_VARIABLE_NAME

  // literals
  "<int literal>",                         // TOK_INT_LITERAL
  "<float literal>",                       // TOK_FLOAT_LITERAL
  "<string literal>",                      // TOK_STRING_LITERAL
  "<char literal>",                        // TOK_CHAR_LITERAL

  // keywords
  "asm",                                   // TOK_ASM
  "auto",                                  // TOK_AUTO
  "break",                                 // TOK_BREAK
  "bool",                                  // TOK_BOOL
  "case",                                  // TOK_CASE
  "catch",                                 // TOK_CATCH
  "cdecl",                                 // TOK_CDECL
  "char",                                  // TOK_CHAR
  "class",                                 // TOK_CLASS
  "const",                                 // TOK_CONST
  "const_cast",                            // TOK_CONST_CAST
  "continue",                              // TOK_CONTINUE
  "default",                               // TOK_DEFAULT
  "delete",                                // TOK_DELETE
  "do",                                    // TOK_DO
  "double",                                // TOK_DOUBLE
  "dynamic_cast",                          // TOK_DYNAMIC_CAST
  "else",                                  // TOK_ELSE
  "enum",                                  // TOK_ENUM
  "explicit",                              // TOK_EXPLICIT
  "export",                                // TOK_EXPORT
  "extern",                                // TOK_EXTERN
  "false",                                 // TOK_FALSE
  "float",                                 // TOK_FLOAT
  "for",                                   // TOK_FOR
  "friend",                                // TOK_FRIEND
  "goto",                                  // TOK_GOTO
  "if",                                    // TOK_IF
  "inline",                                // TOK_INLINE
  "int",                                   // TOK_INT
  "long",                                  // TOK_LONG
  "mutable",                               // TOK_MUTABLE
  "namespace",                             // TOK_NAMESPACE
  "new",                                   // TOK_NEW
  "operator",                              // TOK_OPERATOR
  "pascal",                                // TOK_PASCAL
  "private",                               // TOK_PRIVATE
  "protected",                             // TOK_PROTECTED
  "public",                                // TOK_PUBLIC
  "register",                              // TOK_REGISTER
  "reinterpret_cast",                      // TOK_REINTERPRET_CAST
  "return",                                // TOK_RETURN
  "short",                                 // TOK_SHORT
  "signed",                                // TOK_SIGNED
  "sizeof",                                // TOK_SIZEOF
  "static",                                // TOK_STATIC
  "static_cast",                           // TOK_STATIC_CAST
  "struct",                                // TOK_STRUCT
  "switch",                                // TOK_SWITCH
  "template",                              // TOK_TEMPLATE
  "this",                                  // TOK_THIS
  "throw",                                 // TOK_THROW
  "true",                                  // TOK_TRUE
  "try",                                   // TOK_TRY
  "typedef",                               // TOK_TYPEDEF
  "typeid",                                // TOK_TYPEID
  "typename",                              // TOK_TYPENAME
  "union",                                 // TOK_UNION
  "unsigned",                              // TOK_UNSIGNED
  "using",                                 // TOK_USING
  "virtual",                               // TOK_VIRTUAL
  "void",                                  // TOK_VOID
  "volatile",                              // TOK_VOLATILE
  "wchar_t",                               // TOK_WCHAR_T
  "while",                                 // TOK_WHILE

  // operators (I don't identify C++ operators because in C they're not identifiers)
  "(",                                     // TOK_LPAREN
  ")",                                     // TOK_RPAREN
  "[",                                     // TOK_LBRACKET
  "]",                                     // TOK_RBRACKET
  "->",                                    // TOK_ARROW
  "::",                                    // TOK_COLONCOLON
  ".",                                     // TOK_DOT
  "!",                                     // TOK_BANG
  "~",                                     // TOK_TILDE
  "+",                                     // TOK_PLUS
  "-",                                     // TOK_MINUS
  "++",                                    // TOK_PLUSPLUS
  "--",                                    // TOK_MINUSMINUS
  "&",                                     // TOK_AND
  "*",                                     // TOK_STAR
  ".*",                                    // TOK_DOTSTAR
  "->*",                                   // TOK_ARROWSTAR
  "/",                                     // TOK_SLASH
  "%",                                     // TOK_PERCENT
  "<<",                                    // TOK_LEFTSHIFT
  ">>",                                    // TOK_RIGHTSHIFT
  "<",                                     // TOK_LESSTHAN
  "<=",                                    // TOK_LESSEQ
  ">",                                     // TOK_GREATERTHAN
  ">=",                                    // TOK_GREATEREQ
  "==",                                    // TOK_EQUALEQUAL
  "!=",                                    // TOK_NOTEQUAL
  "^",                                     // TOK_XOR
  "|",                                     // TOK_OR
  "&&",                                    // TOK_ANDAND
  "||",                                    // TOK_OROR
  "?",                                     // TOK_QUESTION
  ":",                                     // TOK_COLON
  "=",                                     // TOK_EQUAL
  "*=",                                    // TOK_STAREQUAL
  "/=",                                    // TOK_SLASHEQUAL
  "%=",                                    // TOK_PERCENTEQUAL
  "+=",                                    // TOK_PLUSEQUAL
  "-=",                                    // TOK_MINUSEQUAL
  "&=",                                    // TOK_ANDEQUAL
  "^=",                                    // TOK_XOREQUAL
  "|=",                                    // TOK_OREQUAL
  "<<=",                                   // TOK_LEFTSHIFTEQUAL
  ">>=",                                   // TOK_RIGHTSHIFTEQUAL
  ",",                                     // TOK_COMMA
  "...",                                   // TOK_ELLIPSIS
  ";",                                     // TOK_SEMICOLON
  "{",                                     // TOK_LBRACE
  "}",                                     // TOK_RBRACE

  // dummy terminals used for precedence games
  "<prefer reduce>",                       // TOK_PREFER_REDUCE
  "<prefer shift>",                        // TOK_PREFER_SHIFT

  // gnu_ext.tok  -*- c++ -*-
  // extension to cc_tokens.tok, for GNU language extensions

  // flags:
  //   MS(m): token has multiple spellings
  //   NS(n): token is a nonseparator; nonseparators cannot be adjacent
  //   CP(p): token is a keyword only in C++; in C it's an identifier

  // enumeration name      description                  : MS NS CP
  // ----------------      ---------------------------  : -- -- --

  // GNU extensions
  "__builtin_constant_p",                  // TOK_BUILTIN_CONSTANT_P
  "__alignof__",                           // TOK___ALIGNOF__
  "__offsetof__",                          // TOK___OFFSETOF__
  "__builtin_offsetof",                    // TOK___BUILTIN_OFFSETOF
  "__attribute__",                         // TOK___ATTRIBUTE__
  "__FUNCTION__",                          // TOK___FUNCTION__
  "__label__",                             // TOK___LABEL__
  "__PRETTY_FUNCTION__",                   // TOK___PRETTY_FUNCTION__
  "__typeof__",                            // TOK___TYPEOF__
  "__extension__",                         // TOK___EXTENSION__
  "__builtin_expect",                      // TOK___BUILTIN_EXPECT

  // varargs; dsw: I think that we should make all of these their own
  // AST node, I just don't want to deal with the parsing ambiguity
  // with E_funCall right now
  // TOK___BUILTIN_VA_START,  "__builtin_va_start",        :    n
  // TOK___BUILTIN_VA_COPY,   "__builtin_va_copy",         :    n
  "__builtin_va_arg",                      // TOK___BUILTIN_VA_ARG
  // TOK___BUILTIN_VA_END,    "__builtin_va_end",          :    n

  "<?",                                    // TOK_MIN_OP
  ">?",                                    // TOK_MAX_OP
  "__real__",                              // TOK_REAL
  "__imag__",                              // TOK_IMAG

  // sm: these are C99 but I'm putting them here anyway..
  "restrict",                              // TOK_RESTRICT
  "_Complex",                              // TOK_COMPLEX
  "_Imaginary",                            // TOK_IMAGINARY
};  // tokenNameTable[]

// this is provided to allow a consistency check between the generated
// .h file and generated .cc file
int const tokenNameTableSize =
  sizeof(tokenNameTable) / sizeof(tokenNameTable[0]);


unsigned char tokenFlagTable[] = {
  0,                                       // TOK_EOF

  // non-keyword name
  0 | TF_MULTISPELL | TF_NONSEPARATOR,     // TOK_NAME

  // classified name (for e.g. cdecl2)
  0 | TF_MULTISPELL | TF_NONSEPARATOR,     // TOK_TYPE_NAME
  0 | TF_MULTISPELL | TF_NONSEPARATOR,     // TOK_VARIABLE_NAME

  // literals
  0 | TF_MULTISPELL | TF_NONSEPARATOR,     // TOK_INT_LITERAL
  0 | TF_MULTISPELL | TF_NONSEPARATOR,     // TOK_FLOAT_LITERAL
  0 | TF_MULTISPELL,                       // TOK_STRING_LITERAL
  0 | TF_MULTISPELL,                       // TOK_CHAR_LITERAL

  // keywords
  0 | TF_NONSEPARATOR,                     // TOK_ASM
  0 | TF_NONSEPARATOR,                     // TOK_AUTO
  0 | TF_NONSEPARATOR,                     // TOK_BREAK
  0 | TF_NONSEPARATOR | TF_CPLUSPLUS,      // TOK_BOOL
  0 | TF_NONSEPARATOR,                     // TOK_CASE
  0 | TF_NONSEPARATOR | TF_CPLUSPLUS,      // TOK_CATCH
  0 | TF_NONSEPARATOR,                     // TOK_CDECL
  0 | TF_NONSEPARATOR,                     // TOK_CHAR
  0 | TF_NONSEPARATOR | TF_CPLUSPLUS,      // TOK_CLASS
  0 | TF_NONSEPARATOR,                     // TOK_CONST
  0 | TF_NONSEPARATOR | TF_CPLUSPLUS,      // TOK_CONST_CAST
  0 | TF_NONSEPARATOR,                     // TOK_CONTINUE
  0 | TF_NONSEPARATOR,                     // TOK_DEFAULT
  0 | TF_NONSEPARATOR | TF_CPLUSPLUS,      // TOK_DELETE
  0 | TF_NONSEPARATOR,                     // TOK_DO
  0 | TF_NONSEPARATOR,                     // TOK_DOUBLE
  0 | TF_NONSEPARATOR | TF_CPLUSPLUS,      // TOK_DYNAMIC_CAST
  0 | TF_NONSEPARATOR,                     // TOK_ELSE
  0 | TF_NONSEPARATOR,                     // TOK_ENUM
  0 | TF_NONSEPARATOR | TF_CPLUSPLUS,      // TOK_EXPLICIT
  0 | TF_NONSEPARATOR | TF_CPLUSPLUS,      // TOK_EXPORT
  0 | TF_NONSEPARATOR,                     // TOK_EXTERN
  0 | TF_NONSEPARATOR | TF_CPLUSPLUS,      // TOK_FALSE
  0 | TF_NONSEPARATOR,                     // TOK_FLOAT
  0 | TF_NONSEPARATOR,                     // TOK_FOR
  0 | TF_NONSEPARATOR | TF_CPLUSPLUS,      // TOK_FRIEND
  0 | TF_NONSEPARATOR,                     // TOK_GOTO
  0 | TF_NONSEPARATOR,                     // TOK_IF
  0 | TF_NONSEPARATOR,                     // TOK_INLINE
  0 | TF_NONSEPARATOR,                     // TOK_INT
  0 | TF_NONSEPARATOR,                     // TOK_LONG
  0 | TF_NONSEPARATOR | TF_CPLUSPLUS,      // TOK_MUTABLE
  0 | TF_NONSEPARATOR | TF_CPLUSPLUS,      // TOK_NAMESPACE
  0 | TF_NONSEPARATOR | TF_CPLUSPLUS,      // TOK_NEW
  0 | TF_NONSEPARATOR | TF_CPLUSPLUS,      // TOK_OPERATOR
  0 | TF_NONSEPARATOR,                     // TOK_PASCAL
  0 | TF_NONSEPARATOR | TF_CPLUSPLUS,      // TOK_PRIVATE
  0 | TF_NONSEPARATOR | TF_CPLUSPLUS,      // TOK_PROTECTED
  0 | TF_NONSEPARATOR | TF_CPLUSPLUS,      // TOK_PUBLIC
  0 | TF_NONSEPARATOR,                     // TOK_REGISTER
  0 | TF_NONSEPARATOR | TF_CPLUSPLUS,      // TOK_REINTERPRET_CAST
  0 | TF_NONSEPARATOR,                     // TOK_RETURN
  0 | TF_NONSEPARATOR,                     // TOK_SHORT
  0 | TF_NONSEPARATOR,                     // TOK_SIGNED
  0 | TF_NONSEPARATOR,                     // TOK_SIZEOF
  0 | TF_NONSEPARATOR,                     // TOK_STATIC
  0 | TF_NONSEPARATOR | TF_CPLUSPLUS,      // TOK_STATIC_CAST
  0 | TF_NONSEPARATOR,                     // TOK_STRUCT
  0 | TF_NONSEPARATOR,                     // TOK_SWITCH
  0 | TF_NONSEPARATOR | TF_CPLUSPLUS,      // TOK_TEMPLATE
  0 | TF_NONSEPARATOR | TF_CPLUSPLUS,      // TOK_THIS
  0 | TF_NONSEPARATOR | TF_CPLUSPLUS,      // TOK_THROW
  0 | TF_NONSEPARATOR | TF_CPLUSPLUS,      // TOK_TRUE
  0 | TF_NONSEPARATOR | TF_CPLUSPLUS,      // TOK_TRY
  0 | TF_NONSEPARATOR,                     // TOK_TYPEDEF
  0 | TF_NONSEPARATOR | TF_CPLUSPLUS,      // TOK_TYPEID
  0 | TF_NONSEPARATOR | TF_CPLUSPLUS,      // TOK_TYPENAME
  0 | TF_NONSEPARATOR,                     // TOK_UNION
  0 | TF_NONSEPARATOR,                     // TOK_UNSIGNED
  0 | TF_NONSEPARATOR | TF_CPLUSPLUS,      // TOK_USING
  0 | TF_NONSEPARATOR | TF_CPLUSPLUS,      // TOK_VIRTUAL
  0 | TF_NONSEPARATOR,                     // TOK_VOID
  0 | TF_NONSEPARATOR,                     // TOK_VOLATILE
  0 | TF_NONSEPARATOR | TF_CPLUSPLUS,      // TOK_WCHAR_T
  0 | TF_NONSEPARATOR,                     // TOK_WHILE

  // operators (I don't identify C++ operators because in C they're not identifiers)
  0,                                       // TOK_LPAREN
  0,                                       // TOK_RPAREN
  0,                                       // TOK_LBRACKET
  0,                                       // TOK_RBRACKET
  0,                                       // TOK_ARROW
  0,                                       // TOK_COLONCOLON
  0,                                       // TOK_DOT
  0,                                       // TOK_BANG
  0,                                       // TOK_TILDE
  0,                                       // TOK_PLUS
  0,                                       // TOK_MINUS
  0,                                       // TOK_PLUSPLUS
  0,                                       // TOK_MINUSMINUS
  0,                                       // TOK_AND
  0,                                       // TOK_STAR
  0,                                       // TOK_DOTSTAR
  0,                                       // TOK_ARROWSTAR
  0,                                       // TOK_SLASH
  0,                                       // TOK_PERCENT
  0,                                       // TOK_LEFTSHIFT
  0,                                       // TOK_RIGHTSHIFT
  0,                                       // TOK_LESSTHAN
  0,                                       // TOK_LESSEQ
  0,                                       // TOK_GREATERTHAN
  0,                                       // TOK_GREATEREQ
  0,                                       // TOK_EQUALEQUAL
  0,                                       // TOK_NOTEQUAL
  0,                                       // TOK_XOR
  0,                                       // TOK_OR
  0,                                       // TOK_ANDAND
  0,                                       // TOK_OROR
  0,                                       // TOK_QUESTION
  0,                                       // TOK_COLON
  0,                                       // TOK_EQUAL
  0,                                       // TOK_STAREQUAL
  0,                                       // TOK_SLASHEQUAL
  0,                                       // TOK_PERCENTEQUAL
  0,                                       // TOK_PLUSEQUAL
  0,                                       // TOK_MINUSEQUAL
  0,                                       // TOK_ANDEQUAL
  0,                                       // TOK_XOREQUAL
  0,                                       // TOK_OREQUAL
  0,                                       // TOK_LEFTSHIFTEQUAL
  0,                                       // TOK_RIGHTSHIFTEQUAL
  0,                                       // TOK_COMMA
  0,                                       // TOK_ELLIPSIS
  0,                                       // TOK_SEMICOLON
  0,                                       // TOK_LBRACE
  0,                                       // TOK_RBRACE

  // dummy terminals used for precedence games
  0,                                       // TOK_PREFER_REDUCE
  0,                                       // TOK_PREFER_SHIFT

  // gnu_ext.tok  -*- c++ -*-
  // extension to cc_tokens.tok, for GNU language extensions

  // flags:
  //   MS(m): token has multiple spellings
  //   NS(n): token is a nonseparator; nonseparators cannot be adjacent
  //   CP(p): token is a keyword only in C++; in C it's an identifier

  // enumeration name      description                  : MS NS CP
  // ----------------      ---------------------------  : -- -- --

  // GNU extensions
  0 | TF_NONSEPARATOR,                     // TOK_BUILTIN_CONSTANT_P
  0 | TF_NONSEPARATOR,                     // TOK___ALIGNOF__
  0 | TF_NONSEPARATOR,                     // TOK___OFFSETOF__
  0 | TF_NONSEPARATOR,                     // TOK___BUILTIN_OFFSETOF
  0 | TF_NONSEPARATOR,                     // TOK___ATTRIBUTE__
  0 | TF_NONSEPARATOR,                     // TOK___FUNCTION__
  0 | TF_NONSEPARATOR,                     // TOK___LABEL__
  0 | TF_NONSEPARATOR,                     // TOK___PRETTY_FUNCTION__
  0 | TF_NONSEPARATOR,                     // TOK___TYPEOF__
  0 | TF_NONSEPARATOR,                     // TOK___EXTENSION__
  0 | TF_NONSEPARATOR,                     // TOK___BUILTIN_EXPECT

  // varargs; dsw: I think that we should make all of these their own
  // AST node, I just don't want to deal with the parsing ambiguity
  // with E_funCall right now
  // TOK___BUILTIN_VA_START,  "__builtin_va_start",        :    n
  // TOK___BUILTIN_VA_COPY,   "__builtin_va_copy",         :    n
  0 | TF_NONSEPARATOR,                     // TOK___BUILTIN_VA_ARG
  // TOK___BUILTIN_VA_END,    "__builtin_va_end",          :    n

  0,                                       // TOK_MIN_OP
  0,                                       // TOK_MAX_OP
  0 | TF_NONSEPARATOR,                     // TOK_REAL
  0 | TF_NONSEPARATOR,                     // TOK_IMAG

  // sm: these are C99 but I'm putting them here anyway..
  0 | TF_NONSEPARATOR,                     // TOK_RESTRICT
  0 | TF_NONSEPARATOR,                     // TOK_COMPLEX
  0 | TF_NONSEPARATOR,                     // TOK_IMAGINARY

};
