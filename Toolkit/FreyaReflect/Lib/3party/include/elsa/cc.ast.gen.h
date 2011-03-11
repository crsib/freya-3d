// cc.ast.gen.h
// *** DO NOT EDIT ***
// generated automatically by astgen, from cc.ast
// active extension modules: cc_tcheck.ast cc_print.ast cfg.ast cc_elaborate.ast bpprint.ast cc2c.ast gnu.ast kandr.ast

#ifndef CC_AST_GEN_H
#define CC_AST_GEN_H

#include "asthelp.h"        // helpers for generated code
#include "sobjset.h"        // SObjSet

// fwd decls
class TranslationUnit;
class TopForm;
class TF_decl;
class TF_func;
class TF_template;
class TF_explicitInst;
class TF_linkage;
class TF_one_linkage;
class TF_asm;
class TF_namespaceDefn;
class TF_namespaceDecl;
class Function;
class MemberInit;
class Declaration;
class ASTTypeId;
class PQName;
class PQ_qualifier;
class PQ_name;
class PQ_operator;
class PQ_template;
class PQ_variable;
class TypeSpecifier;
class TS_name;
class TS_simple;
class TS_elaborated;
class TS_classSpec;
class TS_enumSpec;
class TS_type;
class TS_typeof;
class BaseClassSpec;
class Enumerator;
class MemberList;
class Member;
class MR_decl;
class MR_func;
class MR_access;
class MR_usingDecl;
class MR_template;
class Declarator;
class IDeclarator;
class D_name;
class D_pointer;
class D_reference;
class D_func;
class D_array;
class D_bitfield;
class D_ptrToMember;
class D_grouping;
class ExceptionSpec;
class OperatorName;
class ON_newDel;
class ON_operator;
class ON_conversion;
class Statement;
class S_skip;
class S_label;
class S_case;
class S_default;
class S_expr;
class S_compound;
class S_if;
class S_switch;
class S_while;
class S_doWhile;
class S_for;
class S_break;
class S_continue;
class S_return;
class S_goto;
class S_decl;
class S_try;
class S_asm;
class S_namespaceDecl;
class S_function;
class S_rangeCase;
class S_computedGoto;
class Condition;
class CN_expr;
class CN_decl;
class Handler;
class Expression;
class E_boolLit;
class E_intLit;
class E_floatLit;
class E_stringLit;
class E_charLit;
class E_this;
class E_variable;
class E_funCall;
class E_constructor;
class E_fieldAcc;
class E_sizeof;
class E_unary;
class E_effect;
class E_binary;
class E_addrOf;
class E_deref;
class E_cast;
class E_cond;
class E_sizeofType;
class E_assign;
class E_new;
class E_delete;
class E_throw;
class E_keywordCast;
class E_typeidExpr;
class E_typeidType;
class E_grouping;
class E_arrow;
class E_statement;
class E_compoundLit;
class E___builtin_constant_p;
class E___builtin_va_arg;
class E_alignofType;
class E_alignofExpr;
class E_gnuCond;
class E_addrOfLabel;
class FullExpression;
class ArgExpression;
class ArgExpressionListOpt;
class Initializer;
class IN_expr;
class IN_compound;
class IN_ctor;
class IN_designated;
class TemplateDeclaration;
class TD_func;
class TD_decl;
class TD_tmember;
class TemplateParameter;
class TP_type;
class TP_nontype;
class TP_template;
class TemplateArgument;
class TA_type;
class TA_nontype;
class TA_templateUsed;
class NamespaceDecl;
class ND_alias;
class ND_usingDecl;
class ND_usingDir;
class FullExpressionAnnot;
class ASTTypeof;
class TS_typeof_expr;
class TS_typeof_type;
class Designator;
class FieldDesignator;
class SubscriptDesignator;
class AttributeSpecifierList;
class AttributeSpecifier;
class Attribute;
class AT_empty;
class AT_word;
class AT_func;


// visitor interface class
class ASTVisitor;

// delegator-visitor interface class
class DelegatorASTVisitor;

// xml-visitor interface class
class XmlAstWriter_AstVisitor;

class IdentityManager;

enum DeclaratorContext {
  DC_UNKNOWN,
  DC_FUNCTION,
  DC_TF_DECL,
  DC_TF_EXPLICITINST,
  DC_MR_DECL,
  DC_S_DECL,
  DC_TD_DECL,
  DC_FEA,
  DC_D_FUNC,
  DC_EXCEPTIONSPEC,
  DC_ON_CONVERSION,
  DC_CN_DECL,
  DC_HANDLER,
  DC_E_CAST,
  DC_E_SIZEOFTYPE,
  DC_E_NEW,
  DC_E_KEYWORDCAST,
  DC_E_TYPEIDTYPE,
  DC_TP_TYPE,
  DC_TP_NONTYPE,
  DC_TA_TYPE,
  DC_TS_TYPEOF_TYPE,
  DC_E_COMPOUNDLIT,
  DC_E_ALIGNOFTYPE,
  DC_E_BUILTIN_VA_ARG,
};

char const *toString(DeclaratorContext);
inline char const *toXml(DeclaratorContext id)
  { return toString(id); }
void fromXml(DeclaratorContext &out, rostring str);


// *** DO NOT EDIT ***

  #include "cc_flags.h"         // CVFlags, DeclFlags, etc. (r)

  class CCLang;                 // cc_lang.h







// *** DO NOT EDIT ***

  #include "variable.h"      // Variable
  #include "cc_type.h"       // Type, FunctonType, CompoundType
  #include "template.h"      // STemplateArgument
  #include "const_eval.h"    // ConstEval
  #include "macros.h"        // Restorer

  class Env;                 // cc_env.h
  class ArgumentInfo;        // overload.h

// *** DO NOT EDIT ***

  class PrintEnv;               // cc_print.h
  class CodeOutStream;          // cc_print.h

// *** DO NOT EDIT ***

  #define CFG_EXTENSION   // this extension module is active

  #include "cfg.h"        // NextPtr

// *** DO NOT EDIT ***

  class ElabVisitor;             // cc_elaborate.h
  sm::string refersTo(Variable *v);  // cc_ast_aux.cc

// *** DO NOT EDIT ***

  class BPEnv;               // bpprint.h

// *** DO NOT EDIT ***

  class CC2CEnv;             // cc2c.h

// *** DO NOT EDIT ***

  #define GNU_EXTENSION         // this extension module is active

  #include <limits.h>           // INT_MIN

// *** DO NOT EDIT ***

  #define KANDR_EXTENSION         // this extension module is active

// *** DO NOT EDIT ***
class TranslationUnit {
  friend class XmlAstWriter_AstVisitor;
  friend class XmlAstReader;
public:      // data
  ASTList <TopForm > topForms;

public:      // funcs
  TranslationUnit(ASTList <TopForm > *_topForms) : topForms(_topForms), globalScope( NULL) {
  }
  ~TranslationUnit();

  char const *kindName() const { return "TranslationUnit"; }

  TranslationUnit *clone() const;

  void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  void traverse(ASTVisitor &vis);

  void gdb() const;

  public:  Scope *globalScope ;   // xml_TY
  public:  void tcheck(Env &env);
  public:  void print(PrintEnv &env);
  public:  void print(BPEnv &bp) const;
};



// *** DO NOT EDIT ***
class TopForm {
  friend class XmlAstWriter_AstVisitor;
  friend class XmlAstReader;
public:      // data
  SourceLoc loc;

public:      // funcs
  TopForm(SourceLoc _loc) : loc(_loc), ambiguity( NULL) {
  }
  virtual ~TopForm();

  enum Kind { TF_DECL, TF_FUNC, TF_TEMPLATE, TF_EXPLICITINST, TF_LINKAGE, TF_ONE_LINKAGE, TF_ASM, TF_NAMESPACEDEFN, TF_NAMESPACEDECL, NUM_KINDS };
  virtual Kind kind() const = 0;

  static char const * const kindNames[NUM_KINDS];
  char const *kindName() const { return kindNames[kind()]; }

  DECL_AST_DOWNCASTS(TF_decl, TF_DECL)
  DECL_AST_DOWNCASTS(TF_func, TF_FUNC)
  DECL_AST_DOWNCASTS(TF_template, TF_TEMPLATE)
  DECL_AST_DOWNCASTS(TF_explicitInst, TF_EXPLICITINST)
  DECL_AST_DOWNCASTS(TF_linkage, TF_LINKAGE)
  DECL_AST_DOWNCASTS(TF_one_linkage, TF_ONE_LINKAGE)
  DECL_AST_DOWNCASTS(TF_asm, TF_ASM)
  DECL_AST_DOWNCASTS(TF_namespaceDefn, TF_NAMESPACEDEFN)
  DECL_AST_DOWNCASTS(TF_namespaceDecl, TF_NAMESPACEDECL)

  virtual TopForm* clone() const=0;

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  void gdb() const;

  public:  TopForm * ambiguity ;
  public:  void addAmbiguity(TopForm *alt);
  public:  void printAmbiguities(std::ostream &os, int indent) const;
  public:  /*no_ignore*/ TopForm *tcheck(Env &env);
  public: virtual  void itcheck(Env &env)=0;
  public: virtual  void print(PrintEnv &env)=0;
  public: virtual  void print(BPEnv &bp) const=0;
  public:  void cc2c(CC2CEnv &env) const;
};

class TF_decl : public TopForm {
public:      // data
  Declaration *decl;

public:      // funcs
  TF_decl(SourceLoc _loc, Declaration *_decl) : TopForm(_loc), decl(_decl) {
  }
  virtual ~TF_decl();

  virtual Kind kind() const { return TF_DECL; }
  enum { TYPE_TAG = TF_DECL };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual TF_decl *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void print(PrintEnv &env);
  public: virtual  void print(BPEnv &bp) const;
};

class TF_func : public TopForm {
public:      // data
  Function *f;

public:      // funcs
  TF_func(SourceLoc _loc, Function *_f) : TopForm(_loc), f(_f) {
  }
  virtual ~TF_func();

  virtual Kind kind() const { return TF_FUNC; }
  enum { TYPE_TAG = TF_FUNC };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual TF_func *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void print(PrintEnv &env);
  public: virtual  void print(BPEnv &bp) const;
};

class TF_template : public TopForm {
public:      // data
  TemplateDeclaration *td;

public:      // funcs
  TF_template(SourceLoc _loc, TemplateDeclaration *_td) : TopForm(_loc), td(_td) {
  }
  virtual ~TF_template();

  virtual Kind kind() const { return TF_TEMPLATE; }
  enum { TYPE_TAG = TF_TEMPLATE };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual TF_template *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void print(PrintEnv &env);
  public: virtual  void print(BPEnv &bp) const;
};

class TF_explicitInst : public TopForm {
public:      // data
  DeclFlags instFlags;
  Declaration *d;

public:      // funcs
  TF_explicitInst(SourceLoc _loc, DeclFlags _instFlags, Declaration *_d) : TopForm(_loc), instFlags(_instFlags), d(_d) {
  }
  virtual ~TF_explicitInst();

  virtual Kind kind() const { return TF_EXPLICITINST; }
  enum { TYPE_TAG = TF_EXPLICITINST };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual TF_explicitInst *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void print(PrintEnv &env);
  public: virtual  void print(BPEnv &bp) const;
};

class TF_linkage : public TopForm {
public:      // data
  StringRef linkageType;
  TranslationUnit *forms;

public:      // funcs
  TF_linkage(SourceLoc _loc, StringRef _linkageType, TranslationUnit *_forms) : TopForm(_loc), linkageType(_linkageType), forms(_forms) {
  }
  virtual ~TF_linkage();

  virtual Kind kind() const { return TF_LINKAGE; }
  enum { TYPE_TAG = TF_LINKAGE };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual TF_linkage *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void print(PrintEnv &env);
  public: virtual  void print(BPEnv &bp) const;
};

class TF_one_linkage : public TopForm {
public:      // data
  StringRef linkageType;
  TopForm *form;

public:      // funcs
  TF_one_linkage(SourceLoc _loc, StringRef _linkageType, TopForm *_form) : TopForm(_loc), linkageType(_linkageType), form(_form) {
  }
  virtual ~TF_one_linkage();

  virtual Kind kind() const { return TF_ONE_LINKAGE; }
  enum { TYPE_TAG = TF_ONE_LINKAGE };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual TF_one_linkage *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void print(PrintEnv &env);
  public: virtual  void print(BPEnv &bp) const;
};

class TF_asm : public TopForm {
public:      // data
  E_stringLit *text;

public:      // funcs
  TF_asm(SourceLoc _loc, E_stringLit *_text) : TopForm(_loc), text(_text) {
  }
  virtual ~TF_asm();

  virtual Kind kind() const { return TF_ASM; }
  enum { TYPE_TAG = TF_ASM };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual TF_asm *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void print(PrintEnv &env);
  public: virtual  void print(BPEnv &bp) const;
};

class TF_namespaceDefn : public TopForm {
public:      // data
  StringRef name;
  ASTList <TopForm > forms;

public:      // funcs
  TF_namespaceDefn(SourceLoc _loc, StringRef _name, ASTList <TopForm > *_forms) : TopForm(_loc), name(_name), forms(_forms) {
  }
  virtual ~TF_namespaceDefn();

  virtual Kind kind() const { return TF_NAMESPACEDEFN; }
  enum { TYPE_TAG = TF_NAMESPACEDEFN };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual TF_namespaceDefn *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void print(PrintEnv &env);
  public: virtual  void print(BPEnv &bp) const;
};

class TF_namespaceDecl : public TopForm {
public:      // data
  NamespaceDecl *decl;

public:      // funcs
  TF_namespaceDecl(SourceLoc _loc, NamespaceDecl *_decl) : TopForm(_loc), decl(_decl) {
  }
  virtual ~TF_namespaceDecl();

  virtual Kind kind() const { return TF_NAMESPACEDECL; }
  enum { TYPE_TAG = TF_NAMESPACEDECL };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual TF_namespaceDecl *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void print(PrintEnv &env);
  public: virtual  void print(BPEnv &bp) const;
};



// *** DO NOT EDIT ***
class Function {
  friend class XmlAstWriter_AstVisitor;
  friend class XmlAstReader;
public:      // data
  DeclFlags dflags;
  TypeSpecifier *retspec;
  Declarator *nameAndParams;
  FakeList <MemberInit >* inits;
  S_compound *body;
  FakeList <Handler >* handlers;

public:      // funcs
  Function(DeclFlags _dflags, TypeSpecifier *_retspec, Declarator *_nameAndParams, FakeList <MemberInit >* _inits, S_compound *_body, FakeList <Handler >* _handlers) : dflags(_dflags), retspec(_retspec), nameAndParams(_nameAndParams), inits(_inits), body(_body), handlers(_handlers), funcType( NULL), receiver( NULL), cloneThunkSource( NULL), retVar( NULL), dtorStatement( NULL), implicitlyDefined( false) {
  }
  ~Function();

  char const *kindName() const { return "Function"; }

  Function *clone() const;

  void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  void traverse(ASTVisitor &vis);

  void gdb() const;

  public:  SourceLoc getLoc() const;
  public:  FunctionType *funcType ;   // xml_TY
  public:  Variable *receiver ;   // xml_TY xmlShouldSerialize
  public:  void printExtras(std::ostream &os, int indent) const;
  public:  Function const *cloneThunkSource ;
  public:  Function *shallowClone() const;
  public:  void finishClone();
  public:  void tcheck(Env &env, Variable *instV = NULL);
  public:  void tcheckBody(Env &env);
  private:  CompoundType *verifyIsCtor(Env &env, char const *context);
  private:  void tcheck_memberInits(Env &env);
  private:  void tcheck_handlers(Env &env);
  public:  bool instButNotTchecked() const;
  public:  bool isTemplate() const;
  public:  void print(PrintEnv &env);
  public:  Variable *retVar ;   // xml_TY xmlShouldSerialize
  public:  Statement *dtorStatement ;   // field xml_AST owner
  public:  bool implicitlyDefined ;   // field xml
  public:  void print(BPEnv &bp, bool inClassDefn = false) const;
  public:  Function *cc2c(CC2CEnv &env) const;
};



// *** DO NOT EDIT ***
class MemberInit {
  friend class XmlAstWriter_AstVisitor;
  friend class XmlAstReader;
public:      // data
  SourceLoc loc;
  SourceLoc endloc;
  PQName *name;
  FakeList <ArgExpression >* args;

public:      // funcs
  MemberInit(SourceLoc _loc, SourceLoc _endloc, PQName *_name, FakeList <ArgExpression >* _args) : loc(_loc), endloc(_endloc), name(_name), args(_args), next(NULL), member( NULL), base( NULL), ctorVar( NULL), annot( NULL), ctorStatement( NULL) {
  }
  ~MemberInit();

  char const *kindName() const { return "MemberInit"; }

  MemberInit *clone() const;

  void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  void traverse(ASTVisitor &vis);

  void gdb() const;

  public:  MemberInit *next;
  public:  Variable *member ;   // xml_TY xmlShouldSerialize
  public:  CompoundType *base ;   // xml_TY
  public:  Variable *ctorVar ;   // xml_TY xmlShouldSerialize
  public:  void printExtras(std::ostream &os, int indent) const;
  public:  void tcheck(Env &env, CompoundType *enclosing);
  private:  FullExpressionAnnot *annot ;   // xml_AST owner
  public:  bool hasAnnot();
  public:  FullExpressionAnnot *getAnnot();
  public:  Statement *ctorStatement ;   // field xml_AST owner
  public:  void print(BPEnv &bp) const;
};



// *** DO NOT EDIT ***
class Declaration {
  friend class XmlAstWriter_AstVisitor;
  friend class XmlAstReader;
public:      // data
  DeclFlags dflags;
  TypeSpecifier *spec;
  FakeList <Declarator >* decllist;

public:      // funcs
  Declaration(DeclFlags _dflags, TypeSpecifier *_spec, FakeList <Declarator >* _decllist) : dflags(_dflags), spec(_spec), decllist(_decllist) {
  }
  ~Declaration();

  char const *kindName() const { return "Declaration"; }

  Declaration *clone() const;

  void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  void traverse(ASTVisitor &vis);

  void gdb() const;

  public:  void tcheck(Env &env, DeclaratorContext context);
  public:  void print(PrintEnv &env);
  public:  void print(BPEnv &bp) const;
  public:  void cc2c(CC2CEnv &env) const;
};



// *** DO NOT EDIT ***
class ASTTypeId {
  friend class XmlAstWriter_AstVisitor;
  friend class XmlAstReader;
public:      // data
  TypeSpecifier *spec;
  Declarator *decl;

public:      // funcs
  ASTTypeId(TypeSpecifier *_spec, Declarator *_decl) : spec(_spec), decl(_decl), next( NULL), ambiguity( NULL) {
  }
  ~ASTTypeId();

  char const *kindName() const { return "ASTTypeId"; }

  ASTTypeId *clone() const;

  void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  void traverse(ASTVisitor &vis);

  void gdb() const;

  public:  ASTTypeId *next ;
  public:  void setNext(ASTTypeId *newNext);
  public:  ASTTypeId *ambiguity ;
  public:  void addAmbiguity(ASTTypeId *alternative);
  public:  void printAmbiguities(std::ostream &os, int indent) const;
  public:  struct Tcheck {
    // when non-NULL, we're in an E_new, and this points to an
    // Expression* which should be set to the expression which denotes
    // the number of elements for new[] to allocate
    Expression **newSizeExpr;

    // additional declflags to attach to the resulting Variable;
    // when this includes DF_PARAMETER, it's a function parameter,
    // which knowledge can be applied towards disambiguation
    DeclFlags dflags;

    // syntactic context
    DeclaratorContext context;

  public:
    Tcheck(DeclFlags df, DeclaratorContext dc)
      : newSizeExpr(NULL), dflags(df), context(dc) {}
  };
  public:  ASTTypeId *tcheck(Env &env, Tcheck &tc);
  public:  void mid_tcheck(Env &env, Tcheck &tc);
  public:  Type *getType() const;
  public:  void print(PrintEnv &env);
  public:  void print(BPEnv &bp) const;
};



// *** DO NOT EDIT ***
class PQName {
  friend class XmlAstWriter_AstVisitor;
  friend class XmlAstReader;
public:      // data
  SourceLoc loc;

public:      // funcs
  PQName(SourceLoc _loc) : loc(_loc) {
  }
  virtual ~PQName();

  enum Kind { PQ_QUALIFIER, PQ_NAME, PQ_OPERATOR, PQ_TEMPLATE, PQ_VARIABLE, NUM_KINDS };
  virtual Kind kind() const = 0;

  static char const * const kindNames[NUM_KINDS];
  char const *kindName() const { return kindNames[kind()]; }

  DECL_AST_DOWNCASTS(PQ_qualifier, PQ_QUALIFIER)
  DECL_AST_DOWNCASTS(PQ_name, PQ_NAME)
  DECL_AST_DOWNCASTS(PQ_operator, PQ_OPERATOR)
  DECL_AST_DOWNCASTS(PQ_template, PQ_TEMPLATE)
  DECL_AST_DOWNCASTS(PQ_variable, PQ_VARIABLE)

  virtual PQName* clone() const=0;

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  void gdb() const;

  public:  bool hasQualifiers() const { return isPQ_qualifier(); };
  public:  sm::string qualifierString() const;
  public:  sm::string toString() const;
  public:  sm::string toString_noTemplArgs() const;
  public:  friend stringBuilder& operator<< (stringBuilder &sb, PQName const &obj);
  public:  friend std::ostream& operator<< (std::ostream &os, PQName const &obj) { return os << obj.toString(); };
  public: virtual  StringRef getName() const=0;
  public: virtual  sm::string toComponentString() const=0;
  public:  PQName const *getUnqualifiedNameC() const;
  public:  PQName *getUnqualifiedName()
    { return const_cast<PQName*>(getUnqualifiedNameC()); };
  public:  bool templateUsed() const;
  public:  PQName *mergeAmbiguous(PQName *obj);
  public: virtual  void tcheck_pq(Env &env, Scope *scope = NULL,
                              LookupFlags lflags = LF_NONE)=0;
  public: virtual  void print(PrintEnv &env)=0;
  public: virtual  void print(BPEnv &bp) const=0;
};

class PQ_qualifier : public PQName {
public:      // data
  StringRef qualifier;
  TemplateArgument *templArgs;
  PQName *rest;

public:      // funcs
  PQ_qualifier(SourceLoc _loc, StringRef _qualifier, TemplateArgument *_templArgs, PQName *_rest) : PQName(_loc), qualifier(_qualifier), templArgs(_templArgs), rest(_rest), ambiguity( NULL), qualifierVar( NULL) {
  }
  virtual ~PQ_qualifier();

  virtual Kind kind() const { return PQ_QUALIFIER; }
  enum { TYPE_TAG = PQ_QUALIFIER };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual PQ_qualifier *clone() const;

  public:  PQName *ambiguity ;
  public:  void printAmbiguities(std::ostream &os, int indent) const;
  public:  Variable *qualifierVar ;   // xml_TY xmlShouldSerialize
  public:  ObjList<STemplateArgument> sargs;   // xml_OL xmlEmbed_List
  public: virtual  StringRef getName() const;
  public: virtual  sm::string toComponentString() const;
  public: virtual  void tcheck_pq(Env &env, Scope *scope = NULL,
                              LookupFlags lflags = LF_NONE);
  public: virtual  void print(PrintEnv &env);
  public: virtual  void print(BPEnv &bp) const;
};

class PQ_name : public PQName {
public:      // data
  StringRef name;

public:      // funcs
  PQ_name(SourceLoc _loc, StringRef _name) : PQName(_loc), name(_name), next( NULL) {
  }
  virtual ~PQ_name();

  virtual Kind kind() const { return PQ_NAME; }
  enum { TYPE_TAG = PQ_NAME };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual PQ_name *clone() const;

  public:  PQ_name *next ;
  public:  void setNext(PQ_name *newNext);
  public: virtual  StringRef getName() const;
  public: virtual  sm::string toComponentString() const;
  public: virtual  void tcheck_pq(Env &env, Scope *scope = NULL,
                              LookupFlags lflags = LF_NONE);
  public: virtual  void print(PrintEnv &env);
  public: virtual  void print(BPEnv &bp) const;
};

class PQ_operator : public PQName {
public:      // data
  OperatorName *o;
  StringRef fakeName;

public:      // funcs
  PQ_operator(SourceLoc _loc, OperatorName *_o, StringRef _fakeName) : PQName(_loc), o(_o), fakeName(_fakeName) {
  }
  virtual ~PQ_operator();

  virtual Kind kind() const { return PQ_OPERATOR; }
  enum { TYPE_TAG = PQ_OPERATOR };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual PQ_operator *clone() const;

  public: virtual  StringRef getName() const;
  public: virtual  sm::string toComponentString() const;
  public: virtual  void tcheck_pq(Env &env, Scope *scope = NULL,
                              LookupFlags lflags = LF_NONE);
  public: virtual  void print(PrintEnv &env);
  public: virtual  void print(BPEnv &bp) const;
};

class PQ_template : public PQName {
public:      // data
  StringRef name;
  TemplateArgument *templArgs;

public:      // funcs
  PQ_template(SourceLoc _loc, StringRef _name, TemplateArgument *_templArgs) : PQName(_loc), name(_name), templArgs(_templArgs) {
  }
  virtual ~PQ_template();

  virtual Kind kind() const { return PQ_TEMPLATE; }
  enum { TYPE_TAG = PQ_TEMPLATE };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual PQ_template *clone() const;

  public:  ObjList<STemplateArgument> sargs;   // xml_OL xmlEmbed_List
  public: virtual  StringRef getName() const;
  public: virtual  sm::string toComponentString() const;
  public: virtual  void tcheck_pq(Env &env, Scope *scope = NULL,
                              LookupFlags lflags = LF_NONE);
  public: virtual  void print(PrintEnv &env);
  public: virtual  void print(BPEnv &bp) const;
};

class PQ_variable : public PQName {
public:      // data
  Variable * var;

public:      // funcs
  PQ_variable(SourceLoc _loc, Variable * _var) : PQName(_loc), var(_var) {
  }
  virtual ~PQ_variable();

  virtual Kind kind() const { return PQ_VARIABLE; }
  enum { TYPE_TAG = PQ_VARIABLE };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual PQ_variable *clone() const;

  public: virtual  StringRef getName() const;
  public: virtual  sm::string toComponentString() const;
  public: virtual  void tcheck_pq(Env &env, Scope *scope = NULL,
                              LookupFlags lflags = LF_NONE);
  public: virtual  void print(PrintEnv &env);
  public: virtual  void print(BPEnv &bp) const;
};



// *** DO NOT EDIT ***
class TypeSpecifier {
  friend class XmlAstWriter_AstVisitor;
  friend class XmlAstReader;
public:      // data
  SourceLoc loc;

public:      // funcs
  TypeSpecifier(SourceLoc _loc) : loc(_loc), cv( CV_UNLOCKED) {
  }
  virtual ~TypeSpecifier();

  enum Kind { TS_NAME, TS_SIMPLE, TS_ELABORATED, TS_CLASSSPEC, TS_ENUMSPEC, TS_TYPE, TS_TYPEOF, NUM_KINDS };
  virtual Kind kind() const = 0;

  static char const * const kindNames[NUM_KINDS];
  char const *kindName() const { return kindNames[kind()]; }

  DECL_AST_DOWNCASTS(TS_name, TS_NAME)
  DECL_AST_DOWNCASTS(TS_simple, TS_SIMPLE)
  DECL_AST_DOWNCASTS(TS_elaborated, TS_ELABORATED)
  DECL_AST_DOWNCASTS(TS_classSpec, TS_CLASSSPEC)
  DECL_AST_DOWNCASTS(TS_enumSpec, TS_ENUMSPEC)
  DECL_AST_DOWNCASTS(TS_type, TS_TYPE)
  DECL_AST_DOWNCASTS(TS_typeof, TS_TYPEOF)

  virtual TypeSpecifier* clone() const=0;

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  void gdb() const;

  public:  CVFlags cv ;   // field xml
  public:  void printExtras(std::ostream &os, int indent) const;
  public:  bool canBeTypeParam() const;
  public:  void setCVOnce(CVFlags newCV);
  public:  Type *tcheck(Env &env, DeclFlags dflags, LookupFlags lflags);
  public: virtual  Type *itcheck(Env &env, DeclFlags dflags, LookupFlags lflags)=0;
  public: virtual  void print(PrintEnv &env)=0;
  public:  void print(BPEnv &bp) const;
  public: virtual  void iprint(BPEnv &bp) const=0;
};

class TS_name : public TypeSpecifier {
public:      // data
  PQName *name;
  bool typenameUsed;

public:      // funcs
  TS_name(SourceLoc _loc, PQName *_name, bool _typenameUsed) : TypeSpecifier(_loc), name(_name), typenameUsed(_typenameUsed), var( NULL), nondependentVar( NULL) {
  }
  virtual ~TS_name();

  virtual Kind kind() const { return TS_NAME; }
  enum { TYPE_TAG = TS_NAME };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual TS_name *clone() const;

  public:  Variable *var ;   // xml_TY xmlShouldSerialize
  public:  Variable *nondependentVar ;   // xml_TY xmlShouldSerialize
  public: virtual  Type *itcheck(Env &env, DeclFlags dflags, LookupFlags lflags);
  public: virtual  void print(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
};

class TS_simple : public TypeSpecifier {
public:      // data
  SimpleTypeId id;

public:      // funcs
  TS_simple(SourceLoc _loc, SimpleTypeId _id) : TypeSpecifier(_loc), id(_id) {
  }
  virtual ~TS_simple();

  virtual Kind kind() const { return TS_SIMPLE; }
  enum { TYPE_TAG = TS_SIMPLE };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual TS_simple *clone() const;

  public: virtual  Type *itcheck(Env &env, DeclFlags dflags, LookupFlags lflags);
  public: virtual  void print(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
};

class TS_elaborated : public TypeSpecifier {
public:      // data
  TypeIntr keyword;
  PQName *name;

public:      // funcs
  TS_elaborated(SourceLoc _loc, TypeIntr _keyword, PQName *_name) : TypeSpecifier(_loc), keyword(_keyword), name(_name), atype( NULL) {
  }
  virtual ~TS_elaborated();

  virtual Kind kind() const { return TS_ELABORATED; }
  enum { TYPE_TAG = TS_ELABORATED };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual TS_elaborated *clone() const;

  public:  NamedAtomicType *atype ;   // xml_TY
  public: virtual  Type *itcheck(Env &env, DeclFlags dflags, LookupFlags lflags);
  public: virtual  void print(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
};

class TS_classSpec : public TypeSpecifier {
public:      // data
  TypeIntr keyword;
  PQName *name;
  FakeList <BaseClassSpec >* bases;
  MemberList *members;

public:      // funcs
  TS_classSpec(SourceLoc _loc, TypeIntr _keyword, PQName *_name, FakeList <BaseClassSpec >* _bases, MemberList *_members) : TypeSpecifier(_loc), keyword(_keyword), name(_name), bases(_bases), members(_members), ctype( NULL), alist(NULL) {
  }
  virtual ~TS_classSpec();

  virtual Kind kind() const { return TS_CLASSSPEC; }
  enum { TYPE_TAG = TS_CLASSSPEC };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual TS_classSpec *clone() const;

  public:  CompoundType *ctype ;   // xml_TY
  public:  void tcheckIntoCompound(
           Env &env, DeclFlags dflags, CompoundType *ct, bool suppressErrors = false);
  private:  void tcheckFunctionBodies(Env &env);
  public:  void printExtras(std::ostream &os, int indent) const;
  public:  AttributeSpecifierList *alist;
  public: virtual  Type *itcheck(Env &env, DeclFlags dflags, LookupFlags lflags);
  public: virtual  void print(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
};

class TS_enumSpec : public TypeSpecifier {
public:      // data
  StringRef name;
  FakeList <Enumerator >* elts;

public:      // funcs
  TS_enumSpec(SourceLoc _loc, StringRef _name, FakeList <Enumerator >* _elts) : TypeSpecifier(_loc), name(_name), elts(_elts), etype( NULL) {
  }
  virtual ~TS_enumSpec();

  virtual Kind kind() const { return TS_ENUMSPEC; }
  enum { TYPE_TAG = TS_ENUMSPEC };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual TS_enumSpec *clone() const;

  public:  EnumType *etype ;   // xml_TY
  public: virtual  Type *itcheck(Env &env, DeclFlags dflags, LookupFlags lflags);
  public: virtual  void print(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
};

class TS_type : public TypeSpecifier {
public:      // data
  Type * type;

public:      // funcs
  TS_type(SourceLoc _loc, Type * _type) : TypeSpecifier(_loc), type(_type) {
  }
  virtual ~TS_type();

  virtual Kind kind() const { return TS_TYPE; }
  enum { TYPE_TAG = TS_TYPE };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual TS_type *clone() const;

  public: virtual  Type *itcheck(Env &env, DeclFlags dflags, LookupFlags lflags);
  public: virtual  void print(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
};

class TS_typeof : public TypeSpecifier {
public:      // data
  ASTTypeof *atype;

public:      // funcs
  TS_typeof(SourceLoc _loc, ASTTypeof *_atype) : TypeSpecifier(_loc), atype(_atype) {
  }
  virtual ~TS_typeof();

  virtual Kind kind() const { return TS_TYPEOF; }
  enum { TYPE_TAG = TS_TYPEOF };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual TS_typeof *clone() const;

  public: virtual  Type *itcheck(Env &env, DeclFlags dflags, LookupFlags lflags);
  public: virtual  void print(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
};



// *** DO NOT EDIT ***
class BaseClassSpec {
  friend class XmlAstWriter_AstVisitor;
  friend class XmlAstReader;
public:      // data
  bool isVirtual;
  AccessKeyword access;
  PQName *name;

public:      // funcs
  BaseClassSpec(bool _isVirtual, AccessKeyword _access, PQName *_name) : isVirtual(_isVirtual), access(_access), name(_name), next(NULL), type( NULL) {
  }
  ~BaseClassSpec();

  char const *kindName() const { return "BaseClassSpec"; }

  BaseClassSpec *clone() const;

  void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  void traverse(ASTVisitor &vis);

  void gdb() const;

  public:  BaseClassSpec *next;
  public:  void printExtras(std::ostream &os, int indent) const;
  public:  CompoundType *type ;   // xml_TY
  public:  void print(PrintEnv &env);
  public:  void print(BPEnv &bp) const;
};



// *** DO NOT EDIT ***
class Enumerator {
  friend class XmlAstWriter_AstVisitor;
  friend class XmlAstReader;
public:      // data
  SourceLoc loc;
  StringRef name;
  Expression *expr;

public:      // funcs
  Enumerator(SourceLoc _loc, StringRef _name, Expression *_expr) : loc(_loc), name(_name), expr(_expr), next(NULL) {
     var=NULL;
  }
  ~Enumerator();

  char const *kindName() const { return "Enumerator"; }

  Enumerator *clone() const;

  void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  void traverse(ASTVisitor &vis);

  void gdb() const;

  public:  Enumerator *next;
  public:  Variable *var;   // xml_TY xmlShouldSerialize
  public:  int enumValue;   // xml
  public:  void printExtras(std::ostream &os, int indent) const;
  public:  void tcheck(Env &env, EnumType *parentEnum, Type *parentType);
  public:  void print(PrintEnv &env);
  public:  void print(BPEnv &bp) const;
};



// *** DO NOT EDIT ***
class MemberList {
  friend class XmlAstWriter_AstVisitor;
  friend class XmlAstReader;
public:      // data
  ASTList <Member > list;

public:      // funcs
  MemberList(ASTList <Member > *_list) : list(_list) {
  }
  ~MemberList();

  char const *kindName() const { return "MemberList"; }

  MemberList *clone() const;

  void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  void traverse(ASTVisitor &vis);

  void gdb() const;

};



// *** DO NOT EDIT ***
class Member {
  friend class XmlAstWriter_AstVisitor;
  friend class XmlAstReader;
public:      // data
  SourceLoc loc;
  SourceLoc endloc;

public:      // funcs
  Member(SourceLoc _loc, SourceLoc _endloc) : loc(_loc), endloc(_endloc) {
  }
  virtual ~Member();

  enum Kind { MR_DECL, MR_FUNC, MR_ACCESS, MR_USINGDECL, MR_TEMPLATE, NUM_KINDS };
  virtual Kind kind() const = 0;

  static char const * const kindNames[NUM_KINDS];
  char const *kindName() const { return kindNames[kind()]; }

  DECL_AST_DOWNCASTS(MR_decl, MR_DECL)
  DECL_AST_DOWNCASTS(MR_func, MR_FUNC)
  DECL_AST_DOWNCASTS(MR_access, MR_ACCESS)
  DECL_AST_DOWNCASTS(MR_usingDecl, MR_USINGDECL)
  DECL_AST_DOWNCASTS(MR_template, MR_TEMPLATE)

  virtual Member* clone() const=0;

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  void gdb() const;

  public: virtual  void tcheck(Env &env)=0;
  public: virtual  void print(PrintEnv &env)=0;
  public: virtual  void print(BPEnv &bp) const=0;
};

class MR_decl : public Member {
public:      // data
  Declaration *d;

public:      // funcs
  MR_decl(SourceLoc _loc, SourceLoc _endloc, Declaration *_d) : Member(_loc, _endloc), d(_d) {
  }
  virtual ~MR_decl();

  virtual Kind kind() const { return MR_DECL; }
  enum { TYPE_TAG = MR_DECL };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual MR_decl *clone() const;

  public: virtual  void tcheck(Env &env);
  public: virtual  void print(PrintEnv &env);
  public: virtual  void print(BPEnv &bp) const;
};

class MR_func : public Member {
public:      // data
  Function *f;

public:      // funcs
  MR_func(SourceLoc _loc, SourceLoc _endloc, Function *_f) : Member(_loc, _endloc), f(_f) {
  }
  virtual ~MR_func();

  virtual Kind kind() const { return MR_FUNC; }
  enum { TYPE_TAG = MR_FUNC };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual MR_func *clone() const;

  public: virtual  void tcheck(Env &env);
  public: virtual  void print(PrintEnv &env);
  public: virtual  void print(BPEnv &bp) const;
};

class MR_access : public Member {
public:      // data
  AccessKeyword k;

public:      // funcs
  MR_access(SourceLoc _loc, SourceLoc _endloc, AccessKeyword _k) : Member(_loc, _endloc), k(_k) {
  }
  virtual ~MR_access();

  virtual Kind kind() const { return MR_ACCESS; }
  enum { TYPE_TAG = MR_ACCESS };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual MR_access *clone() const;

  public: virtual  void tcheck(Env &env);
  public: virtual  void print(PrintEnv &env);
  public: virtual  void print(BPEnv &bp) const;
};

class MR_usingDecl : public Member {
public:      // data
  ND_usingDecl *decl;

public:      // funcs
  MR_usingDecl(SourceLoc _loc, SourceLoc _endloc, ND_usingDecl *_decl) : Member(_loc, _endloc), decl(_decl) {
  }
  virtual ~MR_usingDecl();

  virtual Kind kind() const { return MR_USINGDECL; }
  enum { TYPE_TAG = MR_USINGDECL };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual MR_usingDecl *clone() const;

  public: virtual  void tcheck(Env &env);
  public: virtual  void print(PrintEnv &env);
  public: virtual  void print(BPEnv &bp) const;
};

class MR_template : public Member {
public:      // data
  TemplateDeclaration *d;

public:      // funcs
  MR_template(SourceLoc _loc, SourceLoc _endloc, TemplateDeclaration *_d) : Member(_loc, _endloc), d(_d) {
  }
  virtual ~MR_template();

  virtual Kind kind() const { return MR_TEMPLATE; }
  enum { TYPE_TAG = MR_TEMPLATE };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual MR_template *clone() const;

  public: virtual  void tcheck(Env &env);
  public: virtual  void print(PrintEnv &env);
  public: virtual  void print(BPEnv &bp) const;
};



// *** DO NOT EDIT ***
class Declarator {
  friend class XmlAstWriter_AstVisitor;
  friend class XmlAstReader;
public:      // data
  IDeclarator *decl;
  Initializer *init;

public:      // funcs
  Declarator(IDeclarator *_decl, Initializer *_init) : decl(_decl), init(_init), next( NULL), ambiguity( NULL), var( NULL), type( NULL), context( DC_UNKNOWN), ctorStatement( NULL), dtorStatement( NULL) {
  }
  ~Declarator();

  char const *kindName() const { return "Declarator"; }

  Declarator *clone() const;

  void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  void traverse(ASTVisitor &vis);

  void gdb() const;

  public:  Declarator *next ;
  public:  void setNext(Declarator *newNext);
  public:  Declarator *ambiguity ;
  public:  void addAmbiguity(Declarator *alternative);
  public:  void printAmbiguities(std::ostream &os, int indent) const;
  public:  PQName const *getDeclaratorIdC() const;
  public:  PQName *getDeclaratorId()
    { return const_cast<PQName*>(getDeclaratorIdC()); };
  public:  void setDeclaratorId(PQName *n);
  public:  SourceLoc getLoc() const;
  public:  Variable *var ;   // xml_TY xmlShouldSerialize
  public:  Type *type ;   // xml_TY
  public:  DeclaratorContext context ;   // xml
  public:  void printExtras(std::ostream &os, int indent) const;
  public:  struct Tcheck {
    // Normally, a declarator creates a Variable and inserts it
    // into the environment.  If this field is non-NULL, then the
    // declarator simply uses the supplied Variable instead.
    // Either way, the Variable* is then stored in Declarator::var.
    Variable *existingVar;

    // on the way in, this is the type computed so far; initially
    // it's just the type specifier but additional declarators will
    // layer additional type constructors on top of it and replace
    // the pointer here with a pointer to the constructed type; at
    // the end it is the fully-constructed type
    Type *type;

    // these are the declflags attached to the outer declaration
    DeclFlags dflags;

    // in a new[] declarator, when we hit the final [size], stash
    // the size's AST node pointer here; then E_new can collect it
    Expression *size_E_new;

    // if this is non-NULL, then it points at the D_func responsible
    // for creating 'type', a FunctionType; this is used to determine
    // the cv flags of the implicit 'this' parameter of member functions
    D_func *funcSyntax;

    // syntactic context
    DeclaratorContext context;

  public:
    Tcheck(Type *t, DeclFlags d, DeclaratorContext dc)
      : existingVar (NULL)
      , type        (t)
      , dflags      (d)
      , size_E_new  (NULL)
      , funcSyntax  (NULL)
      , context     (dc)
    {}
    Tcheck(Tcheck const &obj)
      : existingVar (obj.existingVar)
      , type        (obj.type)
      , dflags      (obj.dflags)
      , size_E_new  (obj.size_E_new)
      , funcSyntax  (obj.funcSyntax)
      , context     (obj.context)
    {}
    Tcheck& operator= (Tcheck const &obj) {
      existingVar = obj.existingVar;
      type        = obj.type;
      dflags      = obj.dflags;
      size_E_new  = obj.size_E_new;
      funcSyntax  = obj.funcSyntax;
      context     = obj.context;
      return *this;
    }

    bool hasFlag(DeclFlags f) const { return !!(dflags &f); }
  };
  public:  /*no_ignore*/ Declarator *tcheck(Env &env, Tcheck &dt);
  public:  void mid_tcheck(Env &env, Tcheck &dt);
  public:  void tcheck_init(Env &env);
  public:  void print(PrintEnv &env);
  public:  Statement *ctorStatement ;   // field xml_AST owner
  public:  Statement *dtorStatement ;   // field xml_AST owner
  public:  void elaborateCDtors(ElabVisitor &env, DeclFlags dflags = DF_NONE);
  public:  void print(BPEnv &bp) const;
};



// *** DO NOT EDIT ***
class IDeclarator {
  friend class XmlAstWriter_AstVisitor;
  friend class XmlAstReader;
public:      // data
  SourceLoc loc;

public:      // funcs
  IDeclarator(SourceLoc _loc) : loc(_loc) {
  }
  virtual ~IDeclarator();

  enum Kind { D_NAME, D_POINTER, D_REFERENCE, D_FUNC, D_ARRAY, D_BITFIELD, D_PTRTOMEMBER, D_GROUPING, NUM_KINDS };
  virtual Kind kind() const = 0;

  static char const * const kindNames[NUM_KINDS];
  char const *kindName() const { return kindNames[kind()]; }

  DECL_AST_DOWNCASTS(D_name, D_NAME)
  DECL_AST_DOWNCASTS(D_pointer, D_POINTER)
  DECL_AST_DOWNCASTS(D_reference, D_REFERENCE)
  DECL_AST_DOWNCASTS(D_func, D_FUNC)
  DECL_AST_DOWNCASTS(D_array, D_ARRAY)
  DECL_AST_DOWNCASTS(D_bitfield, D_BITFIELD)
  DECL_AST_DOWNCASTS(D_ptrToMember, D_PTRTOMEMBER)
  DECL_AST_DOWNCASTS(D_grouping, D_GROUPING)

  virtual IDeclarator* clone() const=0;

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  void gdb() const;

  public: virtual  PQName const *getDeclaratorIdC() const=0;
  public:  PQName *getDeclaratorId()
    { return const_cast<PQName*>(getDeclaratorIdC()); };
  public: virtual  IDeclarator const *getBaseC() const=0;
  public:  IDeclarator *getBase()
    { return const_cast<IDeclarator*>(getBaseC()); };
  public:  IDeclarator *skipGroups();
  public:  bool bottomIsDfunc() const;
  public: virtual  void tcheck(Env &env, Declarator::Tcheck &dt)=0;
  public:  bool hasInnerGrouping() const;
  public:  void print(PrintEnv &env);
  public: virtual  void print(BPEnv &bp) const=0;
  public: virtual  D_func *getD_func()=0;
};

class D_name : public IDeclarator {
public:      // data
  PQName *name;

public:      // funcs
  D_name(SourceLoc _loc, PQName *_name) : IDeclarator(_loc), name(_name) {
  }
  virtual ~D_name();

  virtual Kind kind() const { return D_NAME; }
  enum { TYPE_TAG = D_NAME };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual D_name *clone() const;

  public: virtual  PQName const *getDeclaratorIdC() const;
  public: virtual  IDeclarator const *getBaseC() const;
  public: virtual  void tcheck(Env &env, Declarator::Tcheck &dt);
  public: virtual  void print(BPEnv &bp) const;
  public: virtual  D_func *getD_func();
};

class D_pointer : public IDeclarator {
public:      // data
  CVFlags cv;
  IDeclarator *base;

public:      // funcs
  D_pointer(SourceLoc _loc, CVFlags _cv, IDeclarator *_base) : IDeclarator(_loc), cv(_cv), base(_base) {
  }
  virtual ~D_pointer();

  virtual Kind kind() const { return D_POINTER; }
  enum { TYPE_TAG = D_POINTER };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual D_pointer *clone() const;

  public: virtual  PQName const *getDeclaratorIdC() const;
  public: virtual  IDeclarator const *getBaseC() const;
  public: virtual  void tcheck(Env &env, Declarator::Tcheck &dt);
  public: virtual  void print(BPEnv &bp) const;
  public: virtual  D_func *getD_func();
};

class D_reference : public IDeclarator {
public:      // data
  IDeclarator *base;

public:      // funcs
  D_reference(SourceLoc _loc, IDeclarator *_base) : IDeclarator(_loc), base(_base) {
  }
  virtual ~D_reference();

  virtual Kind kind() const { return D_REFERENCE; }
  enum { TYPE_TAG = D_REFERENCE };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual D_reference *clone() const;

  public: virtual  PQName const *getDeclaratorIdC() const;
  public: virtual  IDeclarator const *getBaseC() const;
  public: virtual  void tcheck(Env &env, Declarator::Tcheck &dt);
  public: virtual  void print(BPEnv &bp) const;
  public: virtual  D_func *getD_func();
};

class D_func : public IDeclarator {
public:      // data
  IDeclarator *base;
  FakeList <ASTTypeId >* params;
  CVFlags cv;
  ExceptionSpec *exnSpec;
  FakeList <PQ_name >* kAndR_params;

public:      // funcs
  D_func(SourceLoc _loc, IDeclarator *_base, FakeList <ASTTypeId >* _params, CVFlags _cv, ExceptionSpec *_exnSpec, FakeList <PQ_name >* _kAndR_params = NULL) : IDeclarator(_loc), base(_base), params(_params), cv(_cv), exnSpec(_exnSpec), kAndR_params(_kAndR_params), isMember( false) {
  }
  virtual ~D_func();

  virtual Kind kind() const { return D_FUNC; }
  enum { TYPE_TAG = D_FUNC };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual D_func *clone() const;

  public:  bool isMember ;   // xml
  public: virtual  PQName const *getDeclaratorIdC() const;
  public: virtual  IDeclarator const *getBaseC() const;
  public: virtual  void tcheck(Env &env, Declarator::Tcheck &dt);
  public: virtual  void print(BPEnv &bp) const;
  public: virtual  D_func *getD_func();
};

class D_array : public IDeclarator {
public:      // data
  IDeclarator *base;
  Expression *size;

public:      // funcs
  D_array(SourceLoc _loc, IDeclarator *_base, Expression *_size) : IDeclarator(_loc), base(_base), size(_size), isNewSize( false) {
  }
  virtual ~D_array();

  virtual Kind kind() const { return D_ARRAY; }
  enum { TYPE_TAG = D_ARRAY };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual D_array *clone() const;

  public:  bool isNewSize ;   // xml
  public: virtual  PQName const *getDeclaratorIdC() const;
  public: virtual  IDeclarator const *getBaseC() const;
  public: virtual  void tcheck(Env &env, Declarator::Tcheck &dt);
  public: virtual  void print(BPEnv &bp) const;
  public: virtual  D_func *getD_func();
};

class D_bitfield : public IDeclarator {
public:      // data
  PQName *name;
  Expression *bits;

public:      // funcs
  D_bitfield(SourceLoc _loc, PQName *_name, Expression *_bits) : IDeclarator(_loc), name(_name), bits(_bits), numBits( 0) {
  }
  virtual ~D_bitfield();

  virtual Kind kind() const { return D_BITFIELD; }
  enum { TYPE_TAG = D_BITFIELD };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual D_bitfield *clone() const;

  public:  int numBits ;   // xml
  public: virtual  PQName const *getDeclaratorIdC() const;
  public: virtual  IDeclarator const *getBaseC() const;
  public: virtual  void tcheck(Env &env, Declarator::Tcheck &dt);
  public: virtual  void print(BPEnv &bp) const;
  public: virtual  D_func *getD_func();
};

class D_ptrToMember : public IDeclarator {
public:      // data
  PQName *nestedName;
  CVFlags cv;
  IDeclarator *base;

public:      // funcs
  D_ptrToMember(SourceLoc _loc, PQName *_nestedName, CVFlags _cv, IDeclarator *_base) : IDeclarator(_loc), nestedName(_nestedName), cv(_cv), base(_base) {
  }
  virtual ~D_ptrToMember();

  virtual Kind kind() const { return D_PTRTOMEMBER; }
  enum { TYPE_TAG = D_PTRTOMEMBER };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual D_ptrToMember *clone() const;

  public: virtual  PQName const *getDeclaratorIdC() const;
  public: virtual  IDeclarator const *getBaseC() const;
  public: virtual  void tcheck(Env &env, Declarator::Tcheck &dt);
  public: virtual  void print(BPEnv &bp) const;
  public: virtual  D_func *getD_func();
};

class D_grouping : public IDeclarator {
public:      // data
  IDeclarator *base;

public:      // funcs
  D_grouping(SourceLoc _loc, IDeclarator *_base) : IDeclarator(_loc), base(_base) {
  }
  virtual ~D_grouping();

  virtual Kind kind() const { return D_GROUPING; }
  enum { TYPE_TAG = D_GROUPING };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual D_grouping *clone() const;

  public: virtual  PQName const *getDeclaratorIdC() const;
  public: virtual  IDeclarator const *getBaseC() const;
  public: virtual  void tcheck(Env &env, Declarator::Tcheck &dt);
  public: virtual  void print(BPEnv &bp) const;
  public: virtual  D_func *getD_func();
};



// *** DO NOT EDIT ***
class ExceptionSpec {
  friend class XmlAstWriter_AstVisitor;
  friend class XmlAstReader;
public:      // data
  FakeList <ASTTypeId >* types;

public:      // funcs
  ExceptionSpec(FakeList <ASTTypeId >* _types) : types(_types) {
  }
  ~ExceptionSpec();

  char const *kindName() const { return "ExceptionSpec"; }

  ExceptionSpec *clone() const;

  void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  void traverse(ASTVisitor &vis);

  void gdb() const;

  public:  FunctionType::ExnSpec *tcheck(Env &env);
  public:  void print(PrintEnv &env);
  public:  void print(BPEnv &bp) const;
};



// *** DO NOT EDIT ***
class OperatorName {
  friend class XmlAstWriter_AstVisitor;
  friend class XmlAstReader;
public:      // data

public:      // funcs
  OperatorName() {
  }
  virtual ~OperatorName();

  enum Kind { ON_NEWDEL, ON_OPERATOR, ON_CONVERSION, NUM_KINDS };
  virtual Kind kind() const = 0;

  static char const * const kindNames[NUM_KINDS];
  char const *kindName() const { return kindNames[kind()]; }

  DECL_AST_DOWNCASTS(ON_newDel, ON_NEWDEL)
  DECL_AST_DOWNCASTS(ON_operator, ON_OPERATOR)
  DECL_AST_DOWNCASTS(ON_conversion, ON_CONVERSION)

  virtual OperatorName* clone() const=0;

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  void gdb() const;

  public: virtual  char const *getOperatorName() const=0;
  public:  void tcheck(Env &env);
  public: virtual  void print(BPEnv &bp) const=0;
};

class ON_newDel : public OperatorName {
public:      // data
  bool isNew;
  bool isArray;

public:      // funcs
  ON_newDel(bool _isNew, bool _isArray) : OperatorName(), isNew(_isNew), isArray(_isArray) {
  }
  virtual ~ON_newDel();

  virtual Kind kind() const { return ON_NEWDEL; }
  enum { TYPE_TAG = ON_NEWDEL };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual ON_newDel *clone() const;

  public: virtual  char const *getOperatorName() const;
  public: virtual  void print(BPEnv &bp) const;
};

class ON_operator : public OperatorName {
public:      // data
  OverloadableOp op;

public:      // funcs
  ON_operator(OverloadableOp _op) : OperatorName(), op(_op) {
  }
  virtual ~ON_operator();

  virtual Kind kind() const { return ON_OPERATOR; }
  enum { TYPE_TAG = ON_OPERATOR };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual ON_operator *clone() const;

  public: virtual  char const *getOperatorName() const;
  public: virtual  void print(BPEnv &bp) const;
};

class ON_conversion : public OperatorName {
public:      // data
  ASTTypeId *type;

public:      // funcs
  ON_conversion(ASTTypeId *_type) : OperatorName(), type(_type) {
  }
  virtual ~ON_conversion();

  virtual Kind kind() const { return ON_CONVERSION; }
  enum { TYPE_TAG = ON_CONVERSION };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual ON_conversion *clone() const;

  public: virtual  char const *getOperatorName() const;
  public: virtual  void print(BPEnv &bp) const;
};



// *** DO NOT EDIT ***
class Statement {
  friend class XmlAstWriter_AstVisitor;
  friend class XmlAstReader;
public:      // data
  SourceLoc loc;
  SourceLoc endloc;

public:      // funcs
  Statement(SourceLoc _loc, SourceLoc _endloc) : loc(_loc), endloc(_endloc), ambiguity( NULL) {
  }
  virtual ~Statement();

  enum Kind { S_SKIP, S_LABEL, S_CASE, S_DEFAULT, S_EXPR, S_COMPOUND, S_IF, S_SWITCH, S_WHILE, S_DOWHILE, S_FOR, S_BREAK, S_CONTINUE, S_RETURN, S_GOTO, S_DECL, S_TRY, S_ASM, S_NAMESPACEDECL, S_FUNCTION, S_RANGECASE, S_COMPUTEDGOTO, NUM_KINDS };
  virtual Kind kind() const = 0;

  static char const * const kindNames[NUM_KINDS];
  char const *kindName() const { return kindNames[kind()]; }

  DECL_AST_DOWNCASTS(S_skip, S_SKIP)
  DECL_AST_DOWNCASTS(S_label, S_LABEL)
  DECL_AST_DOWNCASTS(S_case, S_CASE)
  DECL_AST_DOWNCASTS(S_default, S_DEFAULT)
  DECL_AST_DOWNCASTS(S_expr, S_EXPR)
  DECL_AST_DOWNCASTS(S_compound, S_COMPOUND)
  DECL_AST_DOWNCASTS(S_if, S_IF)
  DECL_AST_DOWNCASTS(S_switch, S_SWITCH)
  DECL_AST_DOWNCASTS(S_while, S_WHILE)
  DECL_AST_DOWNCASTS(S_doWhile, S_DOWHILE)
  DECL_AST_DOWNCASTS(S_for, S_FOR)
  DECL_AST_DOWNCASTS(S_break, S_BREAK)
  DECL_AST_DOWNCASTS(S_continue, S_CONTINUE)
  DECL_AST_DOWNCASTS(S_return, S_RETURN)
  DECL_AST_DOWNCASTS(S_goto, S_GOTO)
  DECL_AST_DOWNCASTS(S_decl, S_DECL)
  DECL_AST_DOWNCASTS(S_try, S_TRY)
  DECL_AST_DOWNCASTS(S_asm, S_ASM)
  DECL_AST_DOWNCASTS(S_namespaceDecl, S_NAMESPACEDECL)
  DECL_AST_DOWNCASTS(S_function, S_FUNCTION)
  DECL_AST_DOWNCASTS(S_rangeCase, S_RANGECASE)
  DECL_AST_DOWNCASTS(S_computedGoto, S_COMPUTEDGOTO)

  virtual Statement* clone() const=0;

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  void gdb() const;

  public:  Statement * ambiguity ;
  public:  void addAmbiguity(Statement *alt);
  public:  void printAmbiguities(std::ostream &os, int indent) const;
  public:  sm::string lineColString() const;
  public:  sm::string kindLocString() const;
  public:  /*no_ignore*/ Statement *tcheck(Env &env);
  public:  void mid_tcheck(Env &env, int &);
  public: virtual  void itcheck(Env &env)=0;
  public:  void print(PrintEnv &env);
  public: virtual  void iprint(PrintEnv &env)=0;
  protected:  NextPtr next;
  public:  friend class CFGEnv;
  public:  void getSuccessors(NextPtrList &dest, bool isContinue);
  public:  sm::string successorsToString() const;
  public:  void computeCFG(CFGEnv &env);
  public: virtual  void icfg(CFGEnv &env)=0;
  public:  void print(BPEnv &bp) const;
  public: virtual  void iprint(BPEnv &bp) const=0;
  public: virtual  void cc2c(CC2CEnv &env) const=0;
};

class S_skip : public Statement {
public:      // data

public:      // funcs
  S_skip(SourceLoc _loc, SourceLoc _endloc) : Statement(_loc, _endloc) {
  }
  virtual ~S_skip();

  virtual Kind kind() const { return S_SKIP; }
  enum { TYPE_TAG = S_SKIP };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual S_skip *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void icfg(CFGEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  void cc2c(CC2CEnv &env) const;
};

class S_label : public Statement {
public:      // data
  StringRef name;
  Statement *s;

public:      // funcs
  S_label(SourceLoc _loc, SourceLoc _endloc, StringRef _name, Statement *_s) : Statement(_loc, _endloc), name(_name), s(_s) {
  }
  virtual ~S_label();

  virtual Kind kind() const { return S_LABEL; }
  enum { TYPE_TAG = S_LABEL };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual S_label *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void icfg(CFGEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  void cc2c(CC2CEnv &env) const;
};

class S_case : public Statement {
public:      // data
  Expression *expr;
  Statement *s;

public:      // funcs
  S_case(SourceLoc _loc, SourceLoc _endloc, Expression *_expr, Statement *_s) : Statement(_loc, _endloc), expr(_expr), s(_s), labelVal( 0) {
  }
  virtual ~S_case();

  virtual Kind kind() const { return S_CASE; }
  enum { TYPE_TAG = S_CASE };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual S_case *clone() const;

  public:  int labelVal ;   // xml
  public: virtual  void itcheck(Env &env);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void icfg(CFGEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  void cc2c(CC2CEnv &env) const;
};

class S_default : public Statement {
public:      // data
  Statement *s;

public:      // funcs
  S_default(SourceLoc _loc, SourceLoc _endloc, Statement *_s) : Statement(_loc, _endloc), s(_s) {
  }
  virtual ~S_default();

  virtual Kind kind() const { return S_DEFAULT; }
  enum { TYPE_TAG = S_DEFAULT };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual S_default *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void icfg(CFGEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  void cc2c(CC2CEnv &env) const;
};

class S_expr : public Statement {
public:      // data
  FullExpression *expr;

public:      // funcs
  S_expr(SourceLoc _loc, SourceLoc _endloc, FullExpression *_expr) : Statement(_loc, _endloc), expr(_expr) {
  }
  virtual ~S_expr();

  virtual Kind kind() const { return S_EXPR; }
  enum { TYPE_TAG = S_EXPR };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual S_expr *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void icfg(CFGEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  void cc2c(CC2CEnv &env) const;
};

class S_compound : public Statement {
public:      // data
  ASTList <Statement > stmts;

public:      // funcs
  S_compound(SourceLoc _loc, SourceLoc _endloc, ASTList <Statement > *_stmts) : Statement(_loc, _endloc), stmts(_stmts) {
  }
  virtual ~S_compound();

  virtual Kind kind() const { return S_COMPOUND; }
  enum { TYPE_TAG = S_COMPOUND };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual S_compound *clone() const;

  public:  void printNoBraces(BPEnv &bp) const;
  public: virtual  void itcheck(Env &env);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void icfg(CFGEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  void cc2c(CC2CEnv &env) const;
};

class S_if : public Statement {
public:      // data
  Condition *cond;
  Statement *thenBranch;
  Statement *elseBranch;

public:      // funcs
  S_if(SourceLoc _loc, SourceLoc _endloc, Condition *_cond, Statement *_thenBranch, Statement *_elseBranch) : Statement(_loc, _endloc), cond(_cond), thenBranch(_thenBranch), elseBranch(_elseBranch) {
  }
  virtual ~S_if();

  virtual Kind kind() const { return S_IF; }
  enum { TYPE_TAG = S_IF };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual S_if *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void icfg(CFGEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  void cc2c(CC2CEnv &env) const;
};

class S_switch : public Statement {
public:      // data
  Condition *cond;
  Statement *branches;

public:      // funcs
  S_switch(SourceLoc _loc, SourceLoc _endloc, Condition *_cond, Statement *_branches) : Statement(_loc, _endloc), cond(_cond), branches(_branches) {
  }
  virtual ~S_switch();

  virtual Kind kind() const { return S_SWITCH; }
  enum { TYPE_TAG = S_SWITCH };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual S_switch *clone() const;

  private:  SObjList<Statement> cases;
  public:  friend class CFGEnv;
  public:  friend class Statement;
  public: virtual  void itcheck(Env &env);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void icfg(CFGEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  void cc2c(CC2CEnv &env) const;
};

class S_while : public Statement {
public:      // data
  Condition *cond;
  Statement *body;

public:      // funcs
  S_while(SourceLoc _loc, SourceLoc _endloc, Condition *_cond, Statement *_body) : Statement(_loc, _endloc), cond(_cond), body(_body) {
  }
  virtual ~S_while();

  virtual Kind kind() const { return S_WHILE; }
  enum { TYPE_TAG = S_WHILE };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual S_while *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void icfg(CFGEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  void cc2c(CC2CEnv &env) const;
};

class S_doWhile : public Statement {
public:      // data
  Statement *body;
  FullExpression *expr;

public:      // funcs
  S_doWhile(SourceLoc _loc, SourceLoc _endloc, Statement *_body, FullExpression *_expr) : Statement(_loc, _endloc), body(_body), expr(_expr) {
  }
  virtual ~S_doWhile();

  virtual Kind kind() const { return S_DOWHILE; }
  enum { TYPE_TAG = S_DOWHILE };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual S_doWhile *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void icfg(CFGEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  void cc2c(CC2CEnv &env) const;
};

class S_for : public Statement {
public:      // data
  Statement *init;
  Condition *cond;
  FullExpression *after;
  Statement *body;

public:      // funcs
  S_for(SourceLoc _loc, SourceLoc _endloc, Statement *_init, Condition *_cond, FullExpression *_after, Statement *_body) : Statement(_loc, _endloc), init(_init), cond(_cond), after(_after), body(_body) {
  }
  virtual ~S_for();

  virtual Kind kind() const { return S_FOR; }
  enum { TYPE_TAG = S_FOR };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual S_for *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void icfg(CFGEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  void cc2c(CC2CEnv &env) const;
};

class S_break : public Statement {
public:      // data

public:      // funcs
  S_break(SourceLoc _loc, SourceLoc _endloc) : Statement(_loc, _endloc) {
  }
  virtual ~S_break();

  virtual Kind kind() const { return S_BREAK; }
  enum { TYPE_TAG = S_BREAK };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual S_break *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void icfg(CFGEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  void cc2c(CC2CEnv &env) const;
};

class S_continue : public Statement {
public:      // data

public:      // funcs
  S_continue(SourceLoc _loc, SourceLoc _endloc) : Statement(_loc, _endloc) {
  }
  virtual ~S_continue();

  virtual Kind kind() const { return S_CONTINUE; }
  enum { TYPE_TAG = S_CONTINUE };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual S_continue *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void icfg(CFGEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  void cc2c(CC2CEnv &env) const;
};

class S_return : public Statement {
public:      // data
  FullExpression *expr;

public:      // funcs
  S_return(SourceLoc _loc, SourceLoc _endloc, FullExpression *_expr) : Statement(_loc, _endloc), expr(_expr), ctorStatement( NULL) {
  }
  virtual ~S_return();

  virtual Kind kind() const { return S_RETURN; }
  enum { TYPE_TAG = S_RETURN };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual S_return *clone() const;

  public:  Statement *ctorStatement ;   // field xml_AST owner
  public:  bool elaborate(ElabVisitor &env);
  public: virtual  void itcheck(Env &env);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void icfg(CFGEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  void cc2c(CC2CEnv &env) const;
};

class S_goto : public Statement {
public:      // data
  StringRef target;

public:      // funcs
  S_goto(SourceLoc _loc, SourceLoc _endloc, StringRef _target) : Statement(_loc, _endloc), target(_target) {
  }
  virtual ~S_goto();

  virtual Kind kind() const { return S_GOTO; }
  enum { TYPE_TAG = S_GOTO };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual S_goto *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void icfg(CFGEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  void cc2c(CC2CEnv &env) const;
};

class S_decl : public Statement {
public:      // data
  Declaration *decl;

public:      // funcs
  S_decl(SourceLoc _loc, SourceLoc _endloc, Declaration *_decl) : Statement(_loc, _endloc), decl(_decl) {
  }
  virtual ~S_decl();

  virtual Kind kind() const { return S_DECL; }
  enum { TYPE_TAG = S_DECL };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual S_decl *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void icfg(CFGEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  void cc2c(CC2CEnv &env) const;
};

class S_try : public Statement {
public:      // data
  Statement *body;
  FakeList <Handler >* handlers;

public:      // funcs
  S_try(SourceLoc _loc, SourceLoc _endloc, Statement *_body, FakeList <Handler >* _handlers) : Statement(_loc, _endloc), body(_body), handlers(_handlers) {
  }
  virtual ~S_try();

  virtual Kind kind() const { return S_TRY; }
  enum { TYPE_TAG = S_TRY };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual S_try *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void icfg(CFGEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  void cc2c(CC2CEnv &env) const;
};

class S_asm : public Statement {
public:      // data
  E_stringLit *text;

public:      // funcs
  S_asm(SourceLoc _loc, SourceLoc _endloc, E_stringLit *_text) : Statement(_loc, _endloc), text(_text) {
  }
  virtual ~S_asm();

  virtual Kind kind() const { return S_ASM; }
  enum { TYPE_TAG = S_ASM };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual S_asm *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void icfg(CFGEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  void cc2c(CC2CEnv &env) const;
};

class S_namespaceDecl : public Statement {
public:      // data
  NamespaceDecl *decl;

public:      // funcs
  S_namespaceDecl(SourceLoc _loc, SourceLoc _endloc, NamespaceDecl *_decl) : Statement(_loc, _endloc), decl(_decl) {
  }
  virtual ~S_namespaceDecl();

  virtual Kind kind() const { return S_NAMESPACEDECL; }
  enum { TYPE_TAG = S_NAMESPACEDECL };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual S_namespaceDecl *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void icfg(CFGEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  void cc2c(CC2CEnv &env) const;
};

class S_function : public Statement {
public:      // data
  Function *f;

public:      // funcs
  S_function(SourceLoc _loc, SourceLoc _endloc, Function *_f) : Statement(_loc, _endloc), f(_f) {
  }
  virtual ~S_function();

  virtual Kind kind() const { return S_FUNCTION; }
  enum { TYPE_TAG = S_FUNCTION };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual S_function *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void icfg(CFGEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  void cc2c(CC2CEnv &env) const;
};

class S_rangeCase : public Statement {
public:      // data
  Expression *exprLo;
  Expression *exprHi;
  Statement *s;

public:      // funcs
  S_rangeCase(SourceLoc _loc, SourceLoc _endloc, Expression *_exprLo, Expression *_exprHi, Statement *_s) : Statement(_loc, _endloc), exprLo(_exprLo), exprHi(_exprHi), s(_s), labelValLo( 0), labelValHi( 0) {
  }
  virtual ~S_rangeCase();

  virtual Kind kind() const { return S_RANGECASE; }
  enum { TYPE_TAG = S_RANGECASE };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual S_rangeCase *clone() const;

  public:  int labelValLo ;   // xml
  public:  int labelValHi ;   // xml
  public: virtual  void itcheck(Env &env);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void icfg(CFGEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  void cc2c(CC2CEnv &env) const;
};

class S_computedGoto : public Statement {
public:      // data
  Expression *target;

public:      // funcs
  S_computedGoto(SourceLoc _loc, SourceLoc _endloc, Expression *_target) : Statement(_loc, _endloc), target(_target) {
  }
  virtual ~S_computedGoto();

  virtual Kind kind() const { return S_COMPUTEDGOTO; }
  enum { TYPE_TAG = S_COMPUTEDGOTO };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual S_computedGoto *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void icfg(CFGEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  void cc2c(CC2CEnv &env) const;
};



// *** DO NOT EDIT ***
class Condition {
  friend class XmlAstWriter_AstVisitor;
  friend class XmlAstReader;
public:      // data

public:      // funcs
  Condition() : ambiguity( NULL) {
  }
  virtual ~Condition();

  enum Kind { CN_EXPR, CN_DECL, NUM_KINDS };
  virtual Kind kind() const = 0;

  static char const * const kindNames[NUM_KINDS];
  char const *kindName() const { return kindNames[kind()]; }

  DECL_AST_DOWNCASTS(CN_expr, CN_EXPR)
  DECL_AST_DOWNCASTS(CN_decl, CN_DECL)

  virtual Condition* clone() const=0;

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  void gdb() const;

  public:  Condition *ambiguity ;
  public:  void addAmbiguity(Condition *alternative);
  public:  void printAmbiguities(std::ostream &os, int indent) const;
  public:  /*no_ignore*/ Condition *tcheck(Env &env);
  public:  void mid_tcheck(Env &env, int &) { itcheck(env); };
  public: virtual  void itcheck(Env &env)=0;
  public: virtual  void print(PrintEnv &env)=0;
  public: virtual  void print(BPEnv &bp) const=0;
};

class CN_expr : public Condition {
public:      // data
  FullExpression *expr;

public:      // funcs
  CN_expr(FullExpression *_expr) : Condition(), expr(_expr) {
  }
  virtual ~CN_expr();

  virtual Kind kind() const { return CN_EXPR; }
  enum { TYPE_TAG = CN_EXPR };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual CN_expr *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void print(PrintEnv &env);
  public: virtual  void print(BPEnv &bp) const;
};

class CN_decl : public Condition {
public:      // data
  ASTTypeId *typeId;

public:      // funcs
  CN_decl(ASTTypeId *_typeId) : Condition(), typeId(_typeId) {
  }
  virtual ~CN_decl();

  virtual Kind kind() const { return CN_DECL; }
  enum { TYPE_TAG = CN_DECL };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual CN_decl *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void print(PrintEnv &env);
  public: virtual  void print(BPEnv &bp) const;
};



// *** DO NOT EDIT ***
class Handler {
  friend class XmlAstWriter_AstVisitor;
  friend class XmlAstReader;
public:      // data
  ASTTypeId *typeId;
  Statement *body;

public:      // funcs
  Handler(ASTTypeId *_typeId, Statement *_body) : typeId(_typeId), body(_body), next( NULL), globalVar( NULL), annot( NULL), localArg(NULL), globalDtorStatement( NULL) {
  }
  ~Handler();

  char const *kindName() const { return "Handler"; }

  Handler *clone() const;

  void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  void traverse(ASTVisitor &vis);

  void gdb() const;

  public:  Handler *next ;
  public:  bool isEllipsis() const;
  public:  void tcheck(Env &env);
  public:  void print(PrintEnv &env);
  public:  Variable *globalVar ;   // xml_TY xmlShouldSerialize
  private:  FullExpressionAnnot *annot ;   // xml_AST owner
  public:  bool hasAnnot();
  public:  FullExpressionAnnot *getAnnot();
  public:  Expression *localArg;   // field xml_AST owner
  public:  Statement *globalDtorStatement ;   // field xml_AST owner
  public:  void elaborate(ElabVisitor &env);
  public:  void print(BPEnv &bp) const;
};



// *** DO NOT EDIT ***
class Expression {
  friend class XmlAstWriter_AstVisitor;
  friend class XmlAstReader;
public:      // data
  SourceLoc loc;
  SourceLoc endloc;

public:      // funcs
  Expression(SourceLoc _loc, SourceLoc _endloc) : loc(_loc), endloc(_endloc), ambiguity( NULL), type( NULL) {
  }
  virtual ~Expression();

  enum Kind { E_BOOLLIT, E_INTLIT, E_FLOATLIT, E_STRINGLIT, E_CHARLIT, E_THIS, E_VARIABLE, E_FUNCALL, E_CONSTRUCTOR, E_FIELDACC, E_SIZEOF, E_UNARY, E_EFFECT, E_BINARY, E_ADDROF, E_DEREF, E_CAST, E_COND, E_SIZEOFTYPE, E_ASSIGN, E_NEW, E_DELETE, E_THROW, E_KEYWORDCAST, E_TYPEIDEXPR, E_TYPEIDTYPE, E_GROUPING, E_ARROW, E_STATEMENT, E_COMPOUNDLIT, E___BUILTIN_CONSTANT_P, E___BUILTIN_VA_ARG, E_ALIGNOFTYPE, E_ALIGNOFEXPR, E_GNUCOND, E_ADDROFLABEL, NUM_KINDS };
  virtual Kind kind() const = 0;

  static char const * const kindNames[NUM_KINDS];
  char const *kindName() const { return kindNames[kind()]; }

  DECL_AST_DOWNCASTS(E_boolLit, E_BOOLLIT)
  DECL_AST_DOWNCASTS(E_intLit, E_INTLIT)
  DECL_AST_DOWNCASTS(E_floatLit, E_FLOATLIT)
  DECL_AST_DOWNCASTS(E_stringLit, E_STRINGLIT)
  DECL_AST_DOWNCASTS(E_charLit, E_CHARLIT)
  DECL_AST_DOWNCASTS(E_this, E_THIS)
  DECL_AST_DOWNCASTS(E_variable, E_VARIABLE)
  DECL_AST_DOWNCASTS(E_funCall, E_FUNCALL)
  DECL_AST_DOWNCASTS(E_constructor, E_CONSTRUCTOR)
  DECL_AST_DOWNCASTS(E_fieldAcc, E_FIELDACC)
  DECL_AST_DOWNCASTS(E_sizeof, E_SIZEOF)
  DECL_AST_DOWNCASTS(E_unary, E_UNARY)
  DECL_AST_DOWNCASTS(E_effect, E_EFFECT)
  DECL_AST_DOWNCASTS(E_binary, E_BINARY)
  DECL_AST_DOWNCASTS(E_addrOf, E_ADDROF)
  DECL_AST_DOWNCASTS(E_deref, E_DEREF)
  DECL_AST_DOWNCASTS(E_cast, E_CAST)
  DECL_AST_DOWNCASTS(E_cond, E_COND)
  DECL_AST_DOWNCASTS(E_sizeofType, E_SIZEOFTYPE)
  DECL_AST_DOWNCASTS(E_assign, E_ASSIGN)
  DECL_AST_DOWNCASTS(E_new, E_NEW)
  DECL_AST_DOWNCASTS(E_delete, E_DELETE)
  DECL_AST_DOWNCASTS(E_throw, E_THROW)
  DECL_AST_DOWNCASTS(E_keywordCast, E_KEYWORDCAST)
  DECL_AST_DOWNCASTS(E_typeidExpr, E_TYPEIDEXPR)
  DECL_AST_DOWNCASTS(E_typeidType, E_TYPEIDTYPE)
  DECL_AST_DOWNCASTS(E_grouping, E_GROUPING)
  DECL_AST_DOWNCASTS(E_arrow, E_ARROW)
  DECL_AST_DOWNCASTS(E_statement, E_STATEMENT)
  DECL_AST_DOWNCASTS(E_compoundLit, E_COMPOUNDLIT)
  DECL_AST_DOWNCASTS(E___builtin_constant_p, E___BUILTIN_CONSTANT_P)
  DECL_AST_DOWNCASTS(E___builtin_va_arg, E___BUILTIN_VA_ARG)
  DECL_AST_DOWNCASTS(E_alignofType, E_ALIGNOFTYPE)
  DECL_AST_DOWNCASTS(E_alignofExpr, E_ALIGNOFEXPR)
  DECL_AST_DOWNCASTS(E_gnuCond, E_GNUCOND)
  DECL_AST_DOWNCASTS(E_addrOfLabel, E_ADDROFLABEL)

  virtual Expression* clone() const=0;

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  void gdb() const;

  public:  Expression *ambiguity ;
  public:  void addAmbiguity(Expression *alternative);
  public:  void printAmbiguities(std::ostream &os, int indent) const;
  public:  bool isBinary(BinaryOp op) const;
  public:  Expression *skipGroups();
  public:  Expression const *skipGroupsC() const;
  public:  void tcheck(Env &env, Expression *&ptr);
  public:  void mid_tcheck(Env &env, Expression *&replacement);
  public: virtual  Type *itcheck_x(Env &env, Expression *&replacement)=0;
  public:  Type *type ;   // xml_TY
  public:  Type *getType() { return type; };
  public:  bool constEval(Env &env, int &result) const;
  public:  bool constEval(Env &env, int &result, bool &dependent) const;
  public:  CValue constEval(ConstEval &env) const;
  public:  CValue iconstEval(ConstEval &env) const;
  public:  virtual CValue extConstEval(ConstEval &env) const;
  public:  CValue constEvalAddr(ConstEval &env) const;
  public:  CValue constEvalCast(ConstEval &env, ASTTypeId const *ctype,
                              Expression const *expr) const;
  public:  static bool hasUnparenthesizedGT(Expression *&expr);
  public:  bool ihasUnparenthesizedGT();
  public:  virtual bool extHasUnparenthesizedGT();
  public:  SpecialExpr getSpecial(CCLang &lang) const;
  public:  void printExtras(std::ostream &os, int indent) const;
  public:  void print(PrintEnv &env);
  public: virtual  void iprint(PrintEnv &env)=0;
  public:  sm::string exprToString() const;
  public:  sm::string asString() const { return exprToString(); };
  protected:  void printSubexp(BPEnv &bp, Expression const *subexp,
                             bool isRightChild) const;
  protected:  void printSubexpL(BPEnv &bp, Expression const *subexp) const
    { printSubexp(bp, subexp, false /*isRightChild*/); };
  protected:  void printSubexpR(BPEnv &bp, Expression const *subexp) const
    { printSubexp(bp, subexp, true /*isRightChild*/); };
  public:  void printExpPA(BPEnv &bp, int parentPA,
                         bool isRightChild = false) const;
  public:  void print(BPEnv &bp) const;
  public: virtual  void iprint(BPEnv &bp) const=0;
  public:  Expression *cc2cNoSideEffects(CC2CEnv &env) const;
  public: virtual  Expression *cc2c(CC2CEnv &env) const=0;
};

class E_boolLit : public Expression {
public:      // data
  bool b;

public:      // funcs
  E_boolLit(SourceLoc _loc, SourceLoc _endloc, bool _b) : Expression(_loc, _endloc), b(_b) {
  }
  virtual ~E_boolLit();

  virtual Kind kind() const { return E_BOOLLIT; }
  enum { TYPE_TAG = E_BOOLLIT };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual E_boolLit *clone() const;

  public: virtual  Type *itcheck_x(Env &env, Expression *&replacement);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  Expression *cc2c(CC2CEnv &env) const;
};

class E_intLit : public Expression {
public:      // data
  StringRef text;

public:      // funcs
  E_intLit(SourceLoc _loc, SourceLoc _endloc, StringRef _text) : Expression(_loc, _endloc), text(_text), i( 0) {
  }
  virtual ~E_intLit();

  virtual Kind kind() const { return E_INTLIT; }
  enum { TYPE_TAG = E_INTLIT };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual E_intLit *clone() const;

  public:  unsigned long i ;   // xml
  public: virtual  Type *itcheck_x(Env &env, Expression *&replacement);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  Expression *cc2c(CC2CEnv &env) const;
};

class E_floatLit : public Expression {
public:      // data
  StringRef text;

public:      // funcs
  E_floatLit(SourceLoc _loc, SourceLoc _endloc, StringRef _text) : Expression(_loc, _endloc), text(_text), d( 0) {
  }
  virtual ~E_floatLit();

  virtual Kind kind() const { return E_FLOATLIT; }
  enum { TYPE_TAG = E_FLOATLIT };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual E_floatLit *clone() const;

  public:  double d ;   // xml
  public: virtual  Type *itcheck_x(Env &env, Expression *&replacement);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  Expression *cc2c(CC2CEnv &env) const;
};

class E_stringLit : public Expression {
public:      // data
  StringRef text;
  E_stringLit *continuation;
  StringRef fullTextNQ;

public:      // funcs
  E_stringLit(SourceLoc _loc, SourceLoc _endloc, StringRef _text, E_stringLit *_continuation = NULL, StringRef _fullTextNQ = NULL) : Expression(_loc, _endloc), text(_text), continuation(_continuation), fullTextNQ(_fullTextNQ) {
  }
  virtual ~E_stringLit();

  virtual Kind kind() const { return E_STRINGLIT; }
  enum { TYPE_TAG = E_STRINGLIT };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual E_stringLit *clone() const;

  public: virtual  Type *itcheck_x(Env &env, Expression *&replacement);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  Expression *cc2c(CC2CEnv &env) const;
};

class E_charLit : public Expression {
public:      // data
  StringRef text;

public:      // funcs
  E_charLit(SourceLoc _loc, SourceLoc _endloc, StringRef _text) : Expression(_loc, _endloc), text(_text), c( 0) {
  }
  virtual ~E_charLit();

  virtual Kind kind() const { return E_CHARLIT; }
  enum { TYPE_TAG = E_CHARLIT };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual E_charLit *clone() const;

  public:  unsigned int c ;   // xml
  public: virtual  Type *itcheck_x(Env &env, Expression *&replacement);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  Expression *cc2c(CC2CEnv &env) const;
};

class E_this : public Expression {
public:      // data

public:      // funcs
  E_this(SourceLoc _loc, SourceLoc _endloc) : Expression(_loc, _endloc), receiver( NULL) {
  }
  virtual ~E_this();

  virtual Kind kind() const { return E_THIS; }
  enum { TYPE_TAG = E_THIS };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual E_this *clone() const;

  public:  Variable *receiver ;   // xml_TY xmlShouldSerialize
  public: virtual  Type *itcheck_x(Env &env, Expression *&replacement);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  Expression *cc2c(CC2CEnv &env) const;
};

class E_variable : public Expression {
public:      // data
  PQName *name;

public:      // funcs
  E_variable(SourceLoc _loc, SourceLoc _endloc, PQName *_name) : Expression(_loc, _endloc), name(_name), var( NULL), nondependentVar( NULL) {
  }
  virtual ~E_variable();

  virtual Kind kind() const { return E_VARIABLE; }
  enum { TYPE_TAG = E_VARIABLE };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual E_variable *clone() const;

  public:  Variable *var ;   // xml_TY xmlShouldSerialize
  public:  Type *itcheck_var(Env &env, Expression *&replacement, LookupFlags flags);
  public:  Type *itcheck_var_set(Env &env, Expression *&replacement,
                                    LookupFlags flags, LookupSet &set);
  public:  Variable *nondependentVar ;   // xml_TY xmlShouldSerialize
  public: virtual  Type *itcheck_x(Env &env, Expression *&replacement);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  Expression *cc2c(CC2CEnv &env) const;
};

class E_funCall : public Expression {
public:      // data
  Expression *func;
  FakeList <ArgExpression >* args;

public:      // funcs
  E_funCall(SourceLoc _loc, SourceLoc _endloc, Expression *_func, FakeList <ArgExpression >* _args) : Expression(_loc, _endloc), func(_func), args(_args), retObj( NULL) {
  }
  virtual ~E_funCall();

  virtual Kind kind() const { return E_FUNCALL; }
  enum { TYPE_TAG = E_FUNCALL };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual E_funCall *clone() const;

  public:  void inner1_itcheck(Env &env, LookupSet &candidates);
  public:  Type *inner2_itcheck(Env &env, LookupSet &candidates);
  public:  Expression *retObj ;   // field xml_AST owner
  public: virtual  Type *itcheck_x(Env &env, Expression *&replacement);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  Expression *cc2c(CC2CEnv &env) const;
};

class E_constructor : public Expression {
public:      // data
  TypeSpecifier *spec;
  FakeList <ArgExpression >* args;

public:      // funcs
  E_constructor(SourceLoc _loc, SourceLoc _endloc, TypeSpecifier *_spec, FakeList <ArgExpression >* _args) : Expression(_loc, _endloc), spec(_spec), args(_args), ctorVar( NULL), artificial( false), retObj( NULL) {
  }
  virtual ~E_constructor();

  virtual Kind kind() const { return E_CONSTRUCTOR; }
  enum { TYPE_TAG = E_CONSTRUCTOR };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual E_constructor *clone() const;

  public:  void inner1_itcheck(Env &env);
  public:  Type *inner2_itcheck(Env &env, Expression *&replacement);
  public:  Variable *ctorVar ;   // xml_TY xmlShouldSerialize
  public:  bool artificial ;   // field xml
  public:  Expression *retObj ;   // field xml_AST owner
  public: virtual  Type *itcheck_x(Env &env, Expression *&replacement);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  Expression *cc2c(CC2CEnv &env) const;
};

class E_fieldAcc : public Expression {
public:      // data
  Expression *obj;
  PQName *fieldName;

public:      // funcs
  E_fieldAcc(SourceLoc _loc, SourceLoc _endloc, Expression *_obj, PQName *_fieldName) : Expression(_loc, _endloc), obj(_obj), fieldName(_fieldName), field( NULL) {
  }
  virtual ~E_fieldAcc();

  virtual Kind kind() const { return E_FIELDACC; }
  enum { TYPE_TAG = E_FIELDACC };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual E_fieldAcc *clone() const;

  public:  Variable *field ;   // xml_TY xmlShouldSerialize
  public:  Type *itcheck_fieldAcc(Env &env, LookupFlags flags);
  public:  Type *itcheck_fieldAcc_set(Env &env, LookupFlags flags,
                                         LookupSet &candidates);
  public:  Type *itcheck_complex_selector(Env &env, LookupFlags flags,
                                             LookupSet &candidates);
  public: virtual  Type *itcheck_x(Env &env, Expression *&replacement);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  Expression *cc2c(CC2CEnv &env) const;
};

class E_sizeof : public Expression {
public:      // data
  Expression *expr;

public:      // funcs
  E_sizeof(SourceLoc _loc, SourceLoc _endloc, Expression *_expr) : Expression(_loc, _endloc), expr(_expr), size( -1) {
  }
  virtual ~E_sizeof();

  virtual Kind kind() const { return E_SIZEOF; }
  enum { TYPE_TAG = E_SIZEOF };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual E_sizeof *clone() const;

  public:  int size ;   // xml
  public: virtual  Type *itcheck_x(Env &env, Expression *&replacement);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  Expression *cc2c(CC2CEnv &env) const;
};

class E_unary : public Expression {
public:      // data
  UnaryOp op;
  Expression *expr;

public:      // funcs
  E_unary(SourceLoc _loc, SourceLoc _endloc, UnaryOp _op, Expression *_expr) : Expression(_loc, _endloc), op(_op), expr(_expr) {
  }
  virtual ~E_unary();

  virtual Kind kind() const { return E_UNARY; }
  enum { TYPE_TAG = E_UNARY };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual E_unary *clone() const;

  public: virtual  Type *itcheck_x(Env &env, Expression *&replacement);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  Expression *cc2c(CC2CEnv &env) const;
};

class E_effect : public Expression {
public:      // data
  EffectOp op;
  Expression *expr;

public:      // funcs
  E_effect(SourceLoc _loc, SourceLoc _endloc, EffectOp _op, Expression *_expr) : Expression(_loc, _endloc), op(_op), expr(_expr) {
  }
  virtual ~E_effect();

  virtual Kind kind() const { return E_EFFECT; }
  enum { TYPE_TAG = E_EFFECT };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual E_effect *clone() const;

  public: virtual  Type *itcheck_x(Env &env, Expression *&replacement);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  Expression *cc2c(CC2CEnv &env) const;
};

class E_binary : public Expression {
public:      // data
  Expression *e1;
  BinaryOp op;
  Expression *e2;

public:      // funcs
  E_binary(SourceLoc _loc, SourceLoc _endloc, Expression *_e1, BinaryOp _op, Expression *_e2) : Expression(_loc, _endloc), e1(_e1), op(_op), e2(_e2) {
  }
  virtual ~E_binary();

  virtual Kind kind() const { return E_BINARY; }
  enum { TYPE_TAG = E_BINARY };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual E_binary *clone() const;

  public:  Type *itcheck_complex_arith(Env &env);
  public: virtual  Type *itcheck_x(Env &env, Expression *&replacement);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  Expression *cc2c(CC2CEnv &env) const;
};

class E_addrOf : public Expression {
public:      // data
  Expression *expr;

public:      // funcs
  E_addrOf(SourceLoc _loc, SourceLoc _endloc, Expression *_expr) : Expression(_loc, _endloc), expr(_expr) {
  }
  virtual ~E_addrOf();

  virtual Kind kind() const { return E_ADDROF; }
  enum { TYPE_TAG = E_ADDROF };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual E_addrOf *clone() const;

  public:  Type *itcheck_addrOf_set(Env &env, Expression *&replacement,
                                       LookupFlags flags, LookupSet &set);
  public: virtual  Type *itcheck_x(Env &env, Expression *&replacement);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  Expression *cc2c(CC2CEnv &env) const;
};

class E_deref : public Expression {
public:      // data
  Expression *ptr;

public:      // funcs
  E_deref(SourceLoc _loc, SourceLoc _endloc, Expression *_ptr) : Expression(_loc, _endloc), ptr(_ptr) {
  }
  virtual ~E_deref();

  virtual Kind kind() const { return E_DEREF; }
  enum { TYPE_TAG = E_DEREF };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual E_deref *clone() const;

  public: virtual  Type *itcheck_x(Env &env, Expression *&replacement);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  Expression *cc2c(CC2CEnv &env) const;
};

class E_cast : public Expression {
public:      // data
  ASTTypeId *ctype;
  Expression *expr;

public:      // funcs
  E_cast(SourceLoc _loc, SourceLoc _endloc, ASTTypeId *_ctype, Expression *_expr) : Expression(_loc, _endloc), ctype(_ctype), expr(_expr), tcheckedType( false) {
  }
  virtual ~E_cast();

  virtual Kind kind() const { return E_CAST; }
  enum { TYPE_TAG = E_CAST };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual E_cast *clone() const;

  public:  bool tcheckedType ;   // xml
  public: virtual  Type *itcheck_x(Env &env, Expression *&replacement);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  Expression *cc2c(CC2CEnv &env) const;
};

class E_cond : public Expression {
public:      // data
  Expression *cond;
  Expression *th;
  Expression *el;

public:      // funcs
  E_cond(SourceLoc _loc, SourceLoc _endloc, Expression *_cond, Expression *_th, Expression *_el) : Expression(_loc, _endloc), cond(_cond), th(_th), el(_el) {
  }
  virtual ~E_cond();

  virtual Kind kind() const { return E_COND; }
  enum { TYPE_TAG = E_COND };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual E_cond *clone() const;

  public: virtual  Type *itcheck_x(Env &env, Expression *&replacement);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  Expression *cc2c(CC2CEnv &env) const;
};

class E_sizeofType : public Expression {
public:      // data
  ASTTypeId *atype;

public:      // funcs
  E_sizeofType(SourceLoc _loc, SourceLoc _endloc, ASTTypeId *_atype) : Expression(_loc, _endloc), atype(_atype), size( -1), tchecked( false) {
  }
  virtual ~E_sizeofType();

  virtual Kind kind() const { return E_SIZEOFTYPE; }
  enum { TYPE_TAG = E_SIZEOFTYPE };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual E_sizeofType *clone() const;

  public:  int size ;   // xml
  public:  bool tchecked ;   // xml
  public: virtual  Type *itcheck_x(Env &env, Expression *&replacement);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  Expression *cc2c(CC2CEnv &env) const;
};

class E_assign : public Expression {
public:      // data
  Expression *target;
  BinaryOp op;
  Expression *src;

public:      // funcs
  E_assign(SourceLoc _loc, SourceLoc _endloc, Expression *_target, BinaryOp _op, Expression *_src) : Expression(_loc, _endloc), target(_target), op(_op), src(_src) {
  }
  virtual ~E_assign();

  virtual Kind kind() const { return E_ASSIGN; }
  enum { TYPE_TAG = E_ASSIGN };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual E_assign *clone() const;

  public: virtual  Type *itcheck_x(Env &env, Expression *&replacement);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  Expression *cc2c(CC2CEnv &env) const;
};

class E_new : public Expression {
public:      // data
  bool colonColon;
  FakeList <ArgExpression >* placementArgs;
  ASTTypeId *atype;
  ArgExpressionListOpt *ctorArgs;

public:      // funcs
  E_new(SourceLoc _loc, SourceLoc _endloc, bool _colonColon, FakeList <ArgExpression >* _placementArgs, ASTTypeId *_atype, ArgExpressionListOpt *_ctorArgs) : Expression(_loc, _endloc), colonColon(_colonColon), placementArgs(_placementArgs), atype(_atype), ctorArgs(_ctorArgs), arraySize( NULL), ctorVar( NULL), ctorStatement( NULL), heapVar( NULL) {
  }
  virtual ~E_new();

  virtual Kind kind() const { return E_NEW; }
  enum { TYPE_TAG = E_NEW };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual E_new *clone() const;

  public:  Expression /*nullable serf*/ *arraySize ;   // xml_AST
  public:  Variable *ctorVar ;   // xml_TY xmlShouldSerialize
  public:  Statement *ctorStatement ;   // field xml_AST owner
  public:  Variable *heapVar ;   // xml_TY xmlShouldSerialize
  public:  bool elaborate(ElabVisitor &env);
  public: virtual  Type *itcheck_x(Env &env, Expression *&replacement);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  Expression *cc2c(CC2CEnv &env) const;
};

class E_delete : public Expression {
public:      // data
  bool colonColon;
  bool array;
  Expression *expr;

public:      // funcs
  E_delete(SourceLoc _loc, SourceLoc _endloc, bool _colonColon, bool _array, Expression *_expr) : Expression(_loc, _endloc), colonColon(_colonColon), array(_array), expr(_expr), dtorStatement( NULL) {
  }
  virtual ~E_delete();

  virtual Kind kind() const { return E_DELETE; }
  enum { TYPE_TAG = E_DELETE };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual E_delete *clone() const;

  public:  Statement *dtorStatement ;   // field xml_AST owner
  public:  bool elaborate(ElabVisitor &env);
  public: virtual  Type *itcheck_x(Env &env, Expression *&replacement);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  Expression *cc2c(CC2CEnv &env) const;
};

class E_throw : public Expression {
public:      // data
  Expression *expr;

public:      // funcs
  E_throw(SourceLoc _loc, SourceLoc _endloc, Expression *_expr) : Expression(_loc, _endloc), expr(_expr), globalVar( NULL), globalCtorStatement(NULL) {
  }
  virtual ~E_throw();

  virtual Kind kind() const { return E_THROW; }
  enum { TYPE_TAG = E_THROW };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual E_throw *clone() const;

  public:  Variable *globalVar ;   // xml_TY xmlShouldSerialize
  public:  Statement *globalCtorStatement;   // field xml_AST owner
  public:  bool elaborate(ElabVisitor &env);
  public: virtual  Type *itcheck_x(Env &env, Expression *&replacement);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  Expression *cc2c(CC2CEnv &env) const;
};

class E_keywordCast : public Expression {
public:      // data
  CastKeyword key;
  ASTTypeId *ctype;
  Expression *expr;

public:      // funcs
  E_keywordCast(SourceLoc _loc, SourceLoc _endloc, CastKeyword _key, ASTTypeId *_ctype, Expression *_expr) : Expression(_loc, _endloc), key(_key), ctype(_ctype), expr(_expr) {
  }
  virtual ~E_keywordCast();

  virtual Kind kind() const { return E_KEYWORDCAST; }
  enum { TYPE_TAG = E_KEYWORDCAST };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual E_keywordCast *clone() const;

  public: virtual  Type *itcheck_x(Env &env, Expression *&replacement);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  Expression *cc2c(CC2CEnv &env) const;
};

class E_typeidExpr : public Expression {
public:      // data
  Expression *expr;

public:      // funcs
  E_typeidExpr(SourceLoc _loc, SourceLoc _endloc, Expression *_expr) : Expression(_loc, _endloc), expr(_expr) {
  }
  virtual ~E_typeidExpr();

  virtual Kind kind() const { return E_TYPEIDEXPR; }
  enum { TYPE_TAG = E_TYPEIDEXPR };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual E_typeidExpr *clone() const;

  public: virtual  Type *itcheck_x(Env &env, Expression *&replacement);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  Expression *cc2c(CC2CEnv &env) const;
};

class E_typeidType : public Expression {
public:      // data
  ASTTypeId *ttype;

public:      // funcs
  E_typeidType(SourceLoc _loc, SourceLoc _endloc, ASTTypeId *_ttype) : Expression(_loc, _endloc), ttype(_ttype) {
  }
  virtual ~E_typeidType();

  virtual Kind kind() const { return E_TYPEIDTYPE; }
  enum { TYPE_TAG = E_TYPEIDTYPE };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual E_typeidType *clone() const;

  public: virtual  Type *itcheck_x(Env &env, Expression *&replacement);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  Expression *cc2c(CC2CEnv &env) const;
};

class E_grouping : public Expression {
public:      // data
  Expression *expr;

public:      // funcs
  E_grouping(SourceLoc _loc, SourceLoc _endloc, Expression *_expr) : Expression(_loc, _endloc), expr(_expr) {
  }
  virtual ~E_grouping();

  virtual Kind kind() const { return E_GROUPING; }
  enum { TYPE_TAG = E_GROUPING };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual E_grouping *clone() const;

  public:  Type *itcheck_grouping_set(Env &env, Expression *&replacement,
                                         LookupFlags flags, LookupSet &set);
  public: virtual  Type *itcheck_x(Env &env, Expression *&replacement);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  Expression *cc2c(CC2CEnv &env) const;
};

class E_arrow : public Expression {
public:      // data
  Expression *obj;
  PQName *fieldName;

public:      // funcs
  E_arrow(SourceLoc _loc, SourceLoc _endloc, Expression *_obj, PQName *_fieldName) : Expression(_loc, _endloc), obj(_obj), fieldName(_fieldName) {
  }
  virtual ~E_arrow();

  virtual Kind kind() const { return E_ARROW; }
  enum { TYPE_TAG = E_ARROW };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual E_arrow *clone() const;

  public:  Type *itcheck_arrow_set(Env &env, Expression *&replacement,
                                      LookupFlags flags, LookupSet &set);
  public: virtual  Type *itcheck_x(Env &env, Expression *&replacement);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  Expression *cc2c(CC2CEnv &env) const;
};

class E_statement : public Expression {
public:      // data
  S_compound *s;

public:      // funcs
  E_statement(SourceLoc _loc, SourceLoc _endloc, S_compound *_s) : Expression(_loc, _endloc), s(_s), tchecked( false) {
  }
  virtual ~E_statement();

  virtual Kind kind() const { return E_STATEMENT; }
  enum { TYPE_TAG = E_STATEMENT };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual E_statement *clone() const;

  public:  bool tchecked ;
  public: virtual  Type *itcheck_x(Env &env, Expression *&replacement);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  Expression *cc2c(CC2CEnv &env) const;
};

class E_compoundLit : public Expression {
public:      // data
  ASTTypeId *stype;
  IN_compound *init;

public:      // funcs
  E_compoundLit(SourceLoc _loc, SourceLoc _endloc, ASTTypeId *_stype, IN_compound *_init) : Expression(_loc, _endloc), stype(_stype), init(_init), tcheckedType( false) {
  }
  virtual ~E_compoundLit();

  virtual Kind kind() const { return E_COMPOUNDLIT; }
  enum { TYPE_TAG = E_COMPOUNDLIT };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual E_compoundLit *clone() const;

  public:  bool tcheckedType ;
  public: virtual  Type *itcheck_x(Env &env, Expression *&replacement);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  Expression *cc2c(CC2CEnv &env) const;
};

class E___builtin_constant_p : public Expression {
public:      // data
  Expression *expr;

public:      // funcs
  E___builtin_constant_p(SourceLoc _loc, SourceLoc _endloc, Expression *_expr) : Expression(_loc, _endloc), expr(_expr) {
  }
  virtual ~E___builtin_constant_p();

  virtual Kind kind() const { return E___BUILTIN_CONSTANT_P; }
  enum { TYPE_TAG = E___BUILTIN_CONSTANT_P };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual E___builtin_constant_p *clone() const;

  public: virtual  Type *itcheck_x(Env &env, Expression *&replacement);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  Expression *cc2c(CC2CEnv &env) const;
};

class E___builtin_va_arg : public Expression {
public:      // data
  Expression *expr;
  ASTTypeId *atype;

public:      // funcs
  E___builtin_va_arg(SourceLoc _loc, SourceLoc _endloc, Expression *_expr, ASTTypeId *_atype) : Expression(_loc, _endloc), expr(_expr), atype(_atype) {
  }
  virtual ~E___builtin_va_arg();

  virtual Kind kind() const { return E___BUILTIN_VA_ARG; }
  enum { TYPE_TAG = E___BUILTIN_VA_ARG };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual E___builtin_va_arg *clone() const;

  public: virtual  Type *itcheck_x(Env &env, Expression *&replacement);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  Expression *cc2c(CC2CEnv &env) const;
};

class E_alignofType : public Expression {
public:      // data
  ASTTypeId *atype;

public:      // funcs
  E_alignofType(SourceLoc _loc, SourceLoc _endloc, ASTTypeId *_atype) : Expression(_loc, _endloc), atype(_atype), alignment( 0) {
  }
  virtual ~E_alignofType();

  virtual Kind kind() const { return E_ALIGNOFTYPE; }
  enum { TYPE_TAG = E_ALIGNOFTYPE };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual E_alignofType *clone() const;

  public:  virtual CValue extConstEval(ConstEval &env) const;
  public:  int alignment ;   // xml
  public: virtual  Type *itcheck_x(Env &env, Expression *&replacement);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  Expression *cc2c(CC2CEnv &env) const;
};

class E_alignofExpr : public Expression {
public:      // data
  Expression *expr;

public:      // funcs
  E_alignofExpr(SourceLoc _loc, SourceLoc _endloc, Expression *_expr) : Expression(_loc, _endloc), expr(_expr), alignment( 0) {
  }
  virtual ~E_alignofExpr();

  virtual Kind kind() const { return E_ALIGNOFEXPR; }
  enum { TYPE_TAG = E_ALIGNOFEXPR };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual E_alignofExpr *clone() const;

  public:  virtual CValue extConstEval(ConstEval &env) const;
  public:  int alignment ;   // xml
  public: virtual  Type *itcheck_x(Env &env, Expression *&replacement);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  Expression *cc2c(CC2CEnv &env) const;
};

class E_gnuCond : public Expression {
public:      // data
  Expression *cond;
  Expression *el;

public:      // funcs
  E_gnuCond(SourceLoc _loc, SourceLoc _endloc, Expression *_cond, Expression *_el) : Expression(_loc, _endloc), cond(_cond), el(_el) {
  }
  virtual ~E_gnuCond();

  virtual Kind kind() const { return E_GNUCOND; }
  enum { TYPE_TAG = E_GNUCOND };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual E_gnuCond *clone() const;

  public:  virtual CValue extConstEval(ConstEval &env) const;
  public:  virtual bool extHasUnparenthesizedGT();
  public: virtual  Type *itcheck_x(Env &env, Expression *&replacement);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  Expression *cc2c(CC2CEnv &env) const;
};

class E_addrOfLabel : public Expression {
public:      // data
  StringRef labelName;

public:      // funcs
  E_addrOfLabel(SourceLoc _loc, SourceLoc _endloc, StringRef _labelName) : Expression(_loc, _endloc), labelName(_labelName) {
  }
  virtual ~E_addrOfLabel();

  virtual Kind kind() const { return E_ADDROFLABEL; }
  enum { TYPE_TAG = E_ADDROFLABEL };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual E_addrOfLabel *clone() const;

  public: virtual  Type *itcheck_x(Env &env, Expression *&replacement);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
  public: virtual  Expression *cc2c(CC2CEnv &env) const;
};



// *** DO NOT EDIT ***
class FullExpression {
  friend class XmlAstWriter_AstVisitor;
  friend class XmlAstReader;
public:      // data
  Expression *expr;

public:      // funcs
  FullExpression(Expression *_expr) : expr(_expr), annot( NULL) {
  }
  ~FullExpression();

  char const *kindName() const { return "FullExpression"; }

  FullExpression *clone() const;

  void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  void traverse(ASTVisitor &vis);

  void gdb() const;

  public:  void tcheck(Env &env);
  public:  Type *getType() const
    { return expr->type; };
  public:  bool constEval(Env &env, int &result) const
    { return expr->constEval(env, result); };
  public:  CValue constEval(ConstEval &env) const
    { return expr->constEval(env); };
  public:  CValue iconstEval(ConstEval &env) const
    { return expr->iconstEval(env); };
  public:  void print(PrintEnv &env);
  private:  FullExpressionAnnot *annot ;   // xml_AST owner
  public:  bool hasAnnot();
  public:  FullExpressionAnnot *getAnnot();
  public:  void print(BPEnv &bp) const;
  public:  FullExpression *cc2c(CC2CEnv &env) const;
};



// *** DO NOT EDIT ***
class ArgExpression {
  friend class XmlAstWriter_AstVisitor;
  friend class XmlAstReader;
public:      // data
  Expression *expr;

public:      // funcs
  ArgExpression(Expression *_expr) : expr(_expr), next( NULL), ambiguity( NULL) {
  }
  ~ArgExpression();

  char const *kindName() const { return "ArgExpression"; }

  ArgExpression *clone() const;

  void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  void traverse(ASTVisitor &vis);

  void gdb() const;

  public:  ArgExpression *next ;
  public:  void setNext(ArgExpression *newNext);
  public:  ArgExpression *ambiguity ;
  public:  void addAmbiguity(ArgExpression *alternative);
  public:  void printAmbiguities(std::ostream &os, int indent) const;
  public:  Type *getType() const
    { return expr->type; };
  public:  bool constEval(Env &env, int &result) const
    { return expr->constEval(env, result); };
  public:  CValue constEval(ConstEval &env) const
    { return expr->constEval(env); };
  public:  CValue iconstEval(ConstEval &env) const
    { return expr->iconstEval(env); };
  public:  bool hasUnparenthesizedGT()
    { return Expression::hasUnparenthesizedGT(expr); };
  public:  SpecialExpr getSpecial(CCLang &lang) const
    { return expr->getSpecial(lang); };
  public:  ArgExpression *tcheck(Env &env, ArgumentInfo &);
  public:  void mid_tcheck(Env &env, ArgumentInfo &);
  public:  void print(BPEnv &bp) const;
};



// *** DO NOT EDIT ***
class ArgExpressionListOpt {
  friend class XmlAstWriter_AstVisitor;
  friend class XmlAstReader;
public:      // data
  FakeList <ArgExpression >* list;

public:      // funcs
  ArgExpressionListOpt(FakeList <ArgExpression >* _list) : list(_list) {
  }
  ~ArgExpressionListOpt();

  char const *kindName() const { return "ArgExpressionListOpt"; }

  ArgExpressionListOpt *clone() const;

  void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  void traverse(ASTVisitor &vis);

  void gdb() const;

};



// *** DO NOT EDIT ***
class Initializer {
  friend class XmlAstWriter_AstVisitor;
  friend class XmlAstReader;
public:      // data
  SourceLoc loc;

public:      // funcs
  Initializer(SourceLoc _loc) : loc(_loc), next( NULL), annot( NULL) {
  }
  virtual ~Initializer();

  enum Kind { IN_EXPR, IN_COMPOUND, IN_CTOR, IN_DESIGNATED, NUM_KINDS };
  virtual Kind kind() const = 0;

  static char const * const kindNames[NUM_KINDS];
  char const *kindName() const { return kindNames[kind()]; }

  DECL_AST_DOWNCASTS(IN_expr, IN_EXPR)
  DECL_AST_DOWNCASTS(IN_compound, IN_COMPOUND)
  DECL_AST_DOWNCASTS(IN_ctor, IN_CTOR)
  DECL_AST_DOWNCASTS(IN_designated, IN_DESIGNATED)

  virtual Initializer* clone() const=0;

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  void gdb() const;

  public:  Initializer *next ;
  public: virtual  void tcheck(Env &env, Type *type)=0;
  public: virtual  void print(PrintEnv &env)=0;
  private:  FullExpressionAnnot *annot ;   // xml_AST owner
  public:  bool hasAnnot();
  public:  FullExpressionAnnot *getAnnot();
  public: virtual  void print(BPEnv &bp) const=0;
};

class IN_expr : public Initializer {
public:      // data
  Expression *e;

public:      // funcs
  IN_expr(SourceLoc _loc, Expression *_e) : Initializer(_loc), e(_e) {
  }
  virtual ~IN_expr();

  virtual Kind kind() const { return IN_EXPR; }
  enum { TYPE_TAG = IN_EXPR };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual IN_expr *clone() const;

  public: virtual  void tcheck(Env &env, Type *type);
  public: virtual  void print(PrintEnv &env);
  public: virtual  void print(BPEnv &bp) const;
};

class IN_compound : public Initializer {
public:      // data
  ASTList <Initializer > inits;

public:      // funcs
  IN_compound(SourceLoc _loc, ASTList <Initializer > *_inits) : Initializer(_loc), inits(_inits) {
  }
  virtual ~IN_compound();

  virtual Kind kind() const { return IN_COMPOUND; }
  enum { TYPE_TAG = IN_COMPOUND };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual IN_compound *clone() const;

  public: virtual  void tcheck(Env &env, Type *type);
  public: virtual  void print(PrintEnv &env);
  public: virtual  void print(BPEnv &bp) const;
};

class IN_ctor : public Initializer {
public:      // data
  FakeList <ArgExpression >* args;

public:      // funcs
  IN_ctor(SourceLoc _loc, FakeList <ArgExpression >* _args) : Initializer(_loc), args(_args), ctorVar( NULL), was_IN_expr( false) {
  }
  virtual ~IN_ctor();

  virtual Kind kind() const { return IN_CTOR; }
  enum { TYPE_TAG = IN_CTOR };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual IN_ctor *clone() const;

  public:  Variable *ctorVar ;   // xml_TY xmlShouldSerialize
  public:  bool was_IN_expr ;   // xml field
  public: virtual  void tcheck(Env &env, Type *type);
  public: virtual  void print(PrintEnv &env);
  public: virtual  void print(BPEnv &bp) const;
};

class IN_designated : public Initializer {
public:      // data
  FakeList <Designator >* designator_list;
  Initializer *init;

public:      // funcs
  IN_designated(SourceLoc _loc, FakeList <Designator >* _designator_list, Initializer *_init) : Initializer(_loc), designator_list(_designator_list), init(_init) {
  }
  virtual ~IN_designated();

  virtual Kind kind() const { return IN_DESIGNATED; }
  enum { TYPE_TAG = IN_DESIGNATED };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual IN_designated *clone() const;

  public: virtual  void tcheck(Env &env, Type *type);
  public: virtual  void print(PrintEnv &env);
  public: virtual  void print(BPEnv &bp) const;
};



// *** DO NOT EDIT ***
class TemplateDeclaration {
  friend class XmlAstWriter_AstVisitor;
  friend class XmlAstReader;
public:      // data
  TemplateParameter *params;

public:      // funcs
  TemplateDeclaration(TemplateParameter *_params) : params(_params) {
  }
  virtual ~TemplateDeclaration();

  enum Kind { TD_FUNC, TD_DECL, TD_TMEMBER, NUM_KINDS };
  virtual Kind kind() const = 0;

  static char const * const kindNames[NUM_KINDS];
  char const *kindName() const { return kindNames[kind()]; }

  DECL_AST_DOWNCASTS(TD_func, TD_FUNC)
  DECL_AST_DOWNCASTS(TD_decl, TD_DECL)
  DECL_AST_DOWNCASTS(TD_tmember, TD_TMEMBER)

  virtual TemplateDeclaration* clone() const=0;

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  void gdb() const;

  public:  void tcheck(Env &env);
  public: virtual  void itcheck(Env &env)=0;
  public:  void print(PrintEnv &env);
  public: virtual  void iprint(PrintEnv &env)=0;
  public:  void print(BPEnv &bp) const;
  public: virtual  void iprint(BPEnv &bp) const=0;
};

class TD_func : public TemplateDeclaration {
public:      // data
  Function *f;

public:      // funcs
  TD_func(TemplateParameter *_params, Function *_f) : TemplateDeclaration(_params), f(_f) {
  }
  virtual ~TD_func();

  virtual Kind kind() const { return TD_FUNC; }
  enum { TYPE_TAG = TD_FUNC };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual TD_func *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
};

class TD_decl : public TemplateDeclaration {
public:      // data
  Declaration *d;

public:      // funcs
  TD_decl(TemplateParameter *_params, Declaration *_d) : TemplateDeclaration(_params), d(_d) {
  }
  virtual ~TD_decl();

  virtual Kind kind() const { return TD_DECL; }
  enum { TYPE_TAG = TD_DECL };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual TD_decl *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
};

class TD_tmember : public TemplateDeclaration {
public:      // data
  TemplateDeclaration *d;

public:      // funcs
  TD_tmember(TemplateParameter *_params, TemplateDeclaration *_d) : TemplateDeclaration(_params), d(_d) {
  }
  virtual ~TD_tmember();

  virtual Kind kind() const { return TD_TMEMBER; }
  enum { TYPE_TAG = TD_TMEMBER };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual TD_tmember *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void iprint(PrintEnv &env);
  public: virtual  void iprint(BPEnv &bp) const;
};



// *** DO NOT EDIT ***
class TemplateParameter {
  friend class XmlAstWriter_AstVisitor;
  friend class XmlAstReader;
public:      // data
  SourceLoc loc;
  TemplateParameter *next;

public:      // funcs
  TemplateParameter(SourceLoc _loc, TemplateParameter *_next) : loc(_loc), next(_next), ambiguity( NULL), var( NULL) {
  }
  virtual ~TemplateParameter();

  enum Kind { TP_TYPE, TP_NONTYPE, TP_TEMPLATE, NUM_KINDS };
  virtual Kind kind() const = 0;

  static char const * const kindNames[NUM_KINDS];
  char const *kindName() const { return kindNames[kind()]; }

  DECL_AST_DOWNCASTS(TP_type, TP_TYPE)
  DECL_AST_DOWNCASTS(TP_nontype, TP_NONTYPE)
  DECL_AST_DOWNCASTS(TP_template, TP_TEMPLATE)

  virtual TemplateParameter* clone() const=0;

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  void gdb() const;

  public: virtual  bool hasDefaultArg() const=0;
  public:  TemplateParameter *ambiguity ;
  public:  void addAmbiguity(TemplateParameter *alternative);
  public:  void printAmbiguities(std::ostream &os, int indent) const;
  public:  /*no_ignore*/ TemplateParameter *tcheck(Env &env);
  public:  void mid_tcheck(Env &env, int &dummy);
  public: virtual  void itcheck(Env &env, int &dummy)=0;
  public:  Variable *var ;   // xml_TY xmlShouldSerialize
  public: virtual  void print(PrintEnv &env)=0;
  public: virtual  void print(BPEnv &bp) const=0;
};

class TP_type : public TemplateParameter {
public:      // data
  StringRef name;
  ASTTypeId *defaultType;

public:      // funcs
  TP_type(SourceLoc _loc, StringRef _name, ASTTypeId *_defaultType, TemplateParameter *_next) : TemplateParameter(_loc, _next), name(_name), defaultType(_defaultType) {
  }
  virtual ~TP_type();

  virtual Kind kind() const { return TP_TYPE; }
  enum { TYPE_TAG = TP_TYPE };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual TP_type *clone() const;

  public: virtual  bool hasDefaultArg() const;
  public: virtual  void itcheck(Env &env, int &dummy);
  public: virtual  void print(PrintEnv &env);
  public: virtual  void print(BPEnv &bp) const;
};

class TP_nontype : public TemplateParameter {
public:      // data
  ASTTypeId *param;

public:      // funcs
  TP_nontype(SourceLoc _loc, ASTTypeId *_param, TemplateParameter *_next) : TemplateParameter(_loc, _next), param(_param) {
  }
  virtual ~TP_nontype();

  virtual Kind kind() const { return TP_NONTYPE; }
  enum { TYPE_TAG = TP_NONTYPE };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual TP_nontype *clone() const;

  public: virtual  bool hasDefaultArg() const;
  public: virtual  void itcheck(Env &env, int &dummy);
  public: virtual  void print(PrintEnv &env);
  public: virtual  void print(BPEnv &bp) const;
};

class TP_template : public TemplateParameter {
public:      // data
  FakeList <TemplateParameter >* parameters;
  StringRef name;
  PQName *defaultTemplate;

public:      // funcs
  TP_template(SourceLoc _loc, FakeList <TemplateParameter >* _parameters, StringRef _name, PQName *_defaultTemplate, TemplateParameter *_next) : TemplateParameter(_loc, _next), parameters(_parameters), name(_name), defaultTemplate(_defaultTemplate) {
  }
  virtual ~TP_template();

  virtual Kind kind() const { return TP_TEMPLATE; }
  enum { TYPE_TAG = TP_TEMPLATE };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual TP_template *clone() const;

  public: virtual  bool hasDefaultArg() const;
  public: virtual  void itcheck(Env &env, int &dummy);
  public: virtual  void print(PrintEnv &env);
  public: virtual  void print(BPEnv &bp) const;
};



// *** DO NOT EDIT ***

  // true if any of the parameters have default values
  bool anyHaveDefaultArgs(TemplateParameter const *list);

// *** DO NOT EDIT ***
class TemplateArgument {
  friend class XmlAstWriter_AstVisitor;
  friend class XmlAstReader;
public:      // data
  TemplateArgument *next;

public:      // funcs
  TemplateArgument(TemplateArgument *_next) : next(_next), ambiguity( NULL) {
  }
  virtual ~TemplateArgument();

  enum Kind { TA_TYPE, TA_NONTYPE, TA_TEMPLATEUSED, NUM_KINDS };
  virtual Kind kind() const = 0;

  static char const * const kindNames[NUM_KINDS];
  char const *kindName() const { return kindNames[kind()]; }

  DECL_AST_DOWNCASTS(TA_type, TA_TYPE)
  DECL_AST_DOWNCASTS(TA_nontype, TA_NONTYPE)
  DECL_AST_DOWNCASTS(TA_templateUsed, TA_TEMPLATEUSED)

  virtual TemplateArgument* clone() const=0;

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  void gdb() const;

  public:  TemplateArgument *ambiguity ;
  public:  void addAmbiguity(TemplateArgument *alternative);
  public:  void printAmbiguities(std::ostream &os, int indent) const;
  public: virtual  sm::string argString() const=0;
  public:  /*no_ignore*/ TemplateArgument *tcheck(Env &env, STemplateArgument &sarg);
  public:  void mid_tcheck(Env &env, STemplateArgument &sarg);
  public: virtual  void itcheck(Env &env, STemplateArgument &sarg)=0;
  public: virtual  void print(PrintEnv &env)=0;
  public: virtual  void print(BPEnv &bp) const=0;
};

class TA_type : public TemplateArgument {
public:      // data
  ASTTypeId *type;

public:      // funcs
  TA_type(ASTTypeId *_type, TemplateArgument *_next) : TemplateArgument(_next), type(_type) {
  }
  virtual ~TA_type();

  virtual Kind kind() const { return TA_TYPE; }
  enum { TYPE_TAG = TA_TYPE };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual TA_type *clone() const;

  public: virtual  sm::string argString() const;
  public: virtual  void itcheck(Env &env, STemplateArgument &sarg);
  public: virtual  void print(PrintEnv &env);
  public: virtual  void print(BPEnv &bp) const;
};

class TA_nontype : public TemplateArgument {
public:      // data
  Expression *expr;

public:      // funcs
  TA_nontype(Expression *_expr, TemplateArgument *_next) : TemplateArgument(_next), expr(_expr) {
  }
  virtual ~TA_nontype();

  virtual Kind kind() const { return TA_NONTYPE; }
  enum { TYPE_TAG = TA_NONTYPE };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual TA_nontype *clone() const;

  public: virtual  sm::string argString() const;
  public: virtual  void itcheck(Env &env, STemplateArgument &sarg);
  public: virtual  void print(PrintEnv &env);
  public: virtual  void print(BPEnv &bp) const;
};

class TA_templateUsed : public TemplateArgument {
public:      // data

public:      // funcs
  TA_templateUsed(TemplateArgument *_next) : TemplateArgument(_next) {
  }
  virtual ~TA_templateUsed();

  virtual Kind kind() const { return TA_TEMPLATEUSED; }
  enum { TYPE_TAG = TA_TEMPLATEUSED };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual TA_templateUsed *clone() const;

  public: virtual  sm::string argString() const;
  public: virtual  void itcheck(Env &env, STemplateArgument &sarg);
  public: virtual  void print(PrintEnv &env);
  public: virtual  void print(BPEnv &bp) const;
};



// *** DO NOT EDIT ***
class NamespaceDecl {
  friend class XmlAstWriter_AstVisitor;
  friend class XmlAstReader;
public:      // data

public:      // funcs
  NamespaceDecl() {
  }
  virtual ~NamespaceDecl();

  enum Kind { ND_ALIAS, ND_USINGDECL, ND_USINGDIR, NUM_KINDS };
  virtual Kind kind() const = 0;

  static char const * const kindNames[NUM_KINDS];
  char const *kindName() const { return kindNames[kind()]; }

  DECL_AST_DOWNCASTS(ND_alias, ND_ALIAS)
  DECL_AST_DOWNCASTS(ND_usingDecl, ND_USINGDECL)
  DECL_AST_DOWNCASTS(ND_usingDir, ND_USINGDIR)

  virtual NamespaceDecl* clone() const=0;

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  void gdb() const;

  public: virtual  void tcheck(Env &env)=0;
  public: virtual  void print(PrintEnv &env)=0;
  public: virtual  void print(BPEnv &bp) const=0;
};

class ND_alias : public NamespaceDecl {
public:      // data
  StringRef alias;
  PQName *original;

public:      // funcs
  ND_alias(StringRef _alias, PQName *_original) : NamespaceDecl(), alias(_alias), original(_original) {
  }
  virtual ~ND_alias();

  virtual Kind kind() const { return ND_ALIAS; }
  enum { TYPE_TAG = ND_ALIAS };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual ND_alias *clone() const;

  public: virtual  void tcheck(Env &env);
  public: virtual  void print(PrintEnv &env);
  public: virtual  void print(BPEnv &bp) const;
};

class ND_usingDecl : public NamespaceDecl {
public:      // data
  PQName *name;

public:      // funcs
  ND_usingDecl(PQName *_name) : NamespaceDecl(), name(_name) {
  }
  virtual ~ND_usingDecl();

  virtual Kind kind() const { return ND_USINGDECL; }
  enum { TYPE_TAG = ND_USINGDECL };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual ND_usingDecl *clone() const;

  public: virtual  void tcheck(Env &env);
  public: virtual  void print(PrintEnv &env);
  public: virtual  void print(BPEnv &bp) const;
};

class ND_usingDir : public NamespaceDecl {
public:      // data
  PQName *name;

public:      // funcs
  ND_usingDir(PQName *_name) : NamespaceDecl(), name(_name) {
  }
  virtual ~ND_usingDir();

  virtual Kind kind() const { return ND_USINGDIR; }
  enum { TYPE_TAG = ND_USINGDIR };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual ND_usingDir *clone() const;

  public: virtual  void tcheck(Env &env);
  public: virtual  void print(PrintEnv &env);
  public: virtual  void print(BPEnv &bp) const;
};








// *** DO NOT EDIT ***

  // so clients outside cc_print.cc can print these lists; this
  // does *not* print the surrounding angle brackets
  void printTemplateArgumentFakeList(PrintEnv &env, FakeList<TemplateArgument> *args);

// *** DO NOT EDIT ***
                               
  // for debugging
  char *expr_toString(Expression const *e);
  int expr_debugPrint(Expression const *e);

// *** DO NOT EDIT ***
class FullExpressionAnnot {
  friend class XmlAstWriter_AstVisitor;
  friend class XmlAstReader;
public:      // data
  ASTList <Declaration > declarations;

public:      // funcs
  FullExpressionAnnot(ASTList <Declaration > *_declarations) : declarations(_declarations) {
  }
  ~FullExpressionAnnot();

  char const *kindName() const { return "FullExpressionAnnot"; }

  FullExpressionAnnot *clone() const;

  void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  void traverse(ASTVisitor &vis);

  void gdb() const;

  public:  bool noTemporaries() const { return declarations.isEmpty(); };
};



// *** DO NOT EDIT ***
class ASTTypeof {
  friend class XmlAstWriter_AstVisitor;
  friend class XmlAstReader;
public:      // data

public:      // funcs
  ASTTypeof() {
     ambiguity=NULL;
  }
  virtual ~ASTTypeof();

  enum Kind { TS_TYPEOF_EXPR, TS_TYPEOF_TYPE, NUM_KINDS };
  virtual Kind kind() const = 0;

  static char const * const kindNames[NUM_KINDS];
  char const *kindName() const { return kindNames[kind()]; }

  DECL_AST_DOWNCASTS(TS_typeof_expr, TS_TYPEOF_EXPR)
  DECL_AST_DOWNCASTS(TS_typeof_type, TS_TYPEOF_TYPE)

  virtual ASTTypeof* clone() const=0;

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  void gdb() const;

  public: virtual  void print(BPEnv &bp) const=0;
  public:  ASTTypeof *ambiguity;
  public:  void addAmbiguity(ASTTypeof *alternative);
  public:  void printAmbiguities(std::ostream &os, int indent) const;
  public:  ASTTypeof *tcheck(Env &env, DeclFlags dflags);
  public:  void mid_tcheck(Env &env, DeclFlags &dflags);
  public: virtual  Type *itcheck(Env &env, DeclFlags dflags)=0;
  public:  Type *type;   // xml_TY
};

class TS_typeof_expr : public ASTTypeof {
public:      // data
  FullExpression *expr;

public:      // funcs
  TS_typeof_expr(FullExpression *_expr) : ASTTypeof(), expr(_expr) {
  }
  virtual ~TS_typeof_expr();

  virtual Kind kind() const { return TS_TYPEOF_EXPR; }
  enum { TYPE_TAG = TS_TYPEOF_EXPR };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual TS_typeof_expr *clone() const;

  public: virtual  void print(BPEnv &bp) const;
  public: virtual  Type *itcheck(Env &env, DeclFlags dflags);
};

class TS_typeof_type : public ASTTypeof {
public:      // data
  ASTTypeId *atype;

public:      // funcs
  TS_typeof_type(ASTTypeId *_atype) : ASTTypeof(), atype(_atype) {
  }
  virtual ~TS_typeof_type();

  virtual Kind kind() const { return TS_TYPEOF_TYPE; }
  enum { TYPE_TAG = TS_TYPEOF_TYPE };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual TS_typeof_type *clone() const;

  public: virtual  void print(BPEnv &bp) const;
  public: virtual  Type *itcheck(Env &env, DeclFlags dflags);
};



// *** DO NOT EDIT ***
class Designator {
  friend class XmlAstWriter_AstVisitor;
  friend class XmlAstReader;
public:      // data
  SourceLoc loc;

public:      // funcs
  Designator(SourceLoc _loc) : loc(_loc) {
     next=NULL;
     ambiguity=NULL;
  }
  virtual ~Designator();

  enum Kind { FIELDDESIGNATOR, SUBSCRIPTDESIGNATOR, NUM_KINDS };
  virtual Kind kind() const = 0;

  static char const * const kindNames[NUM_KINDS];
  char const *kindName() const { return kindNames[kind()]; }

  DECL_AST_DOWNCASTS(FieldDesignator, FIELDDESIGNATOR)
  DECL_AST_DOWNCASTS(SubscriptDesignator, SUBSCRIPTDESIGNATOR)

  virtual Designator* clone() const=0;

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  void gdb() const;

  public: virtual  void print(BPEnv &bp) const=0;
  public:  Designator *next;
  public:  void setNext(Designator *newNext);
  public:  Designator *ambiguity;
  public:  void addAmbiguity(Designator *alternative);
  public:  void printAmbiguities(std::ostream &os, int indent) const;
  public: virtual  void print(PrintEnv &env)=0;
};

class FieldDesignator : public Designator {
public:      // data
  StringRef id;

public:      // funcs
  FieldDesignator(SourceLoc _loc, StringRef _id) : Designator(_loc), id(_id) {
  }
  virtual ~FieldDesignator();

  virtual Kind kind() const { return FIELDDESIGNATOR; }
  enum { TYPE_TAG = FIELDDESIGNATOR };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual FieldDesignator *clone() const;

  public: virtual  void print(BPEnv &bp) const;
  public: virtual  void print(PrintEnv &env);
};

class SubscriptDesignator : public Designator {
public:      // data
  Expression *idx_expr;
  Expression *idx_expr2;

public:      // funcs
  SubscriptDesignator(SourceLoc _loc, Expression *_idx_expr, Expression *_idx_expr2) : Designator(_loc), idx_expr(_idx_expr), idx_expr2(_idx_expr2), idx_computed( INT_MIN), idx_computed2( INT_MIN) {
  }
  virtual ~SubscriptDesignator();

  virtual Kind kind() const { return SUBSCRIPTDESIGNATOR; }
  enum { TYPE_TAG = SUBSCRIPTDESIGNATOR };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual SubscriptDesignator *clone() const;

  public:  int idx_computed  ;   // xml
  public:  int idx_computed2 ;   // xml
  public: virtual  void print(BPEnv &bp) const;
  public: virtual  void print(PrintEnv &env);
};



// *** DO NOT EDIT ***
class AttributeSpecifierList {
  friend class XmlAstWriter_AstVisitor;
  friend class XmlAstReader;
public:      // data
  AttributeSpecifier *spec;
  AttributeSpecifierList *next;

public:      // funcs
  AttributeSpecifierList(AttributeSpecifier *_spec, AttributeSpecifierList *_next) : spec(_spec), next(_next) {
  }
  ~AttributeSpecifierList();

  char const *kindName() const { return "AttributeSpecifierList"; }

  AttributeSpecifierList *clone() const;

  void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  void traverse(ASTVisitor &vis);

  void gdb() const;

};



// *** DO NOT EDIT ***
class AttributeSpecifier {
  friend class XmlAstWriter_AstVisitor;
  friend class XmlAstReader;
public:      // data
  Attribute *attr;
  AttributeSpecifier *next;

public:      // funcs
  AttributeSpecifier(Attribute *_attr, AttributeSpecifier *_next) : attr(_attr), next(_next) {
  }
  ~AttributeSpecifier();

  char const *kindName() const { return "AttributeSpecifier"; }

  AttributeSpecifier *clone() const;

  void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  void traverse(ASTVisitor &vis);

  void gdb() const;

};



// *** DO NOT EDIT ***
class Attribute {
  friend class XmlAstWriter_AstVisitor;
  friend class XmlAstReader;
public:      // data
  SourceLoc loc;

public:      // funcs
  Attribute(SourceLoc _loc) : loc(_loc) {
  }
  virtual ~Attribute();

  enum Kind { AT_EMPTY, AT_WORD, AT_FUNC, NUM_KINDS };
  virtual Kind kind() const = 0;

  static char const * const kindNames[NUM_KINDS];
  char const *kindName() const { return kindNames[kind()]; }

  DECL_AST_DOWNCASTS(AT_empty, AT_EMPTY)
  DECL_AST_DOWNCASTS(AT_word, AT_WORD)
  DECL_AST_DOWNCASTS(AT_func, AT_FUNC)

  virtual Attribute* clone() const=0;

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  void gdb() const;

};

class AT_empty : public Attribute {
public:      // data

public:      // funcs
  AT_empty(SourceLoc _loc) : Attribute(_loc) {
  }
  virtual ~AT_empty();

  virtual Kind kind() const { return AT_EMPTY; }
  enum { TYPE_TAG = AT_EMPTY };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual AT_empty *clone() const;

};

class AT_word : public Attribute {
public:      // data
  StringRef w;

public:      // funcs
  AT_word(SourceLoc _loc, StringRef _w) : Attribute(_loc), w(_w) {
  }
  virtual ~AT_word();

  virtual Kind kind() const { return AT_WORD; }
  enum { TYPE_TAG = AT_WORD };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual AT_word *clone() const;

};

class AT_func : public Attribute {
public:      // data
  StringRef f;
  FakeList <ArgExpression >* args;

public:      // funcs
  AT_func(SourceLoc _loc, StringRef _f, FakeList <ArgExpression >* _args) : Attribute(_loc), f(_f), args(_args) {
  }
  virtual ~AT_func();

  virtual Kind kind() const { return AT_FUNC; }
  enum { TYPE_TAG = AT_FUNC };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
  virtual void traverse(ASTVisitor &vis);

  virtual AT_func *clone() const;

};



// *** DO NOT EDIT ***

  // __attribute__ occurring directly after a declarator
  class D_attribute : public D_grouping {
  public:
    // NOTE: 'traverse' does *not* automatically go into this field,
    // because I want most clients to be oblivious to its presence.
    // They can explicitly intercept D_grouping and check for
    // D_attribute if traversal is desired.
    AttributeSpecifierList *alist;       // owner

  public:
    D_attribute(SourceLoc loc, IDeclarator *base,
                AttributeSpecifierList *alist);
    virtual ~D_attribute();

    virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;
    virtual void traverse(ASTVisitor &vis);

    virtual D_attribute *clone() const;

    virtual void tcheck(Env &env, Declarator::Tcheck &dt);

    // Return the attribute(alias("name")) name, or NULL if none.  There
    // mustn't be more than one.
    virtual StringRef getAlias() const;

  private:
    // Return the attribute alias, and check for errors
    StringRef tcheck_getAlias(Env *penv) const;
  };

// the visitor interface class
class ASTVisitor {

public:      // custom data extensions
  // this is true when we are inside the body of a template function
  // or class (uninstantiated)
  bool inTemplate;

private:     // disallowed, not implemented
  ASTVisitor(ASTVisitor&);
  void operator= (ASTVisitor&);

public:      // funcs
  ASTVisitor() { inTemplate=false; }
  virtual ~ASTVisitor();   // silence gcc warning...

  virtual bool visitTranslationUnit(TranslationUnit *obj);
  virtual void postvisitTranslationUnit(TranslationUnit *obj);
  virtual bool visitTopForm(TopForm *obj);
  virtual void postvisitTopForm(TopForm *obj);
  virtual bool visitFunction(Function *obj);
  virtual void postvisitFunction(Function *obj);
  virtual bool visitMemberInit(MemberInit *obj);
  virtual void postvisitMemberInit(MemberInit *obj);
  virtual bool visitDeclaration(Declaration *obj);
  virtual void postvisitDeclaration(Declaration *obj);
  virtual bool visitASTTypeId(ASTTypeId *obj);
  virtual void postvisitASTTypeId(ASTTypeId *obj);
  virtual bool visitPQName(PQName *obj);
  virtual void postvisitPQName(PQName *obj);
  virtual bool visitTypeSpecifier(TypeSpecifier *obj);
  virtual void postvisitTypeSpecifier(TypeSpecifier *obj);
  virtual bool visitBaseClassSpec(BaseClassSpec *obj);
  virtual void postvisitBaseClassSpec(BaseClassSpec *obj);
  virtual bool visitEnumerator(Enumerator *obj);
  virtual void postvisitEnumerator(Enumerator *obj);
  virtual bool visitMemberList(MemberList *obj);
  virtual void postvisitMemberList(MemberList *obj);
  virtual bool visitMember(Member *obj);
  virtual void postvisitMember(Member *obj);
  virtual bool visitDeclarator(Declarator *obj);
  virtual void postvisitDeclarator(Declarator *obj);
  virtual bool visitIDeclarator(IDeclarator *obj);
  virtual void postvisitIDeclarator(IDeclarator *obj);
  virtual bool visitExceptionSpec(ExceptionSpec *obj);
  virtual void postvisitExceptionSpec(ExceptionSpec *obj);
  virtual bool visitOperatorName(OperatorName *obj);
  virtual void postvisitOperatorName(OperatorName *obj);
  virtual bool visitStatement(Statement *obj);
  virtual void postvisitStatement(Statement *obj);
  virtual bool visitCondition(Condition *obj);
  virtual void postvisitCondition(Condition *obj);
  virtual bool visitHandler(Handler *obj);
  virtual void postvisitHandler(Handler *obj);
  virtual bool visitExpression(Expression *obj);
  virtual void postvisitExpression(Expression *obj);
  virtual bool visitFullExpression(FullExpression *obj);
  virtual void postvisitFullExpression(FullExpression *obj);
  virtual bool visitArgExpression(ArgExpression *obj);
  virtual void postvisitArgExpression(ArgExpression *obj);
  virtual bool visitArgExpressionListOpt(ArgExpressionListOpt *obj);
  virtual void postvisitArgExpressionListOpt(ArgExpressionListOpt *obj);
  virtual bool visitInitializer(Initializer *obj);
  virtual void postvisitInitializer(Initializer *obj);
  virtual bool visitTemplateDeclaration(TemplateDeclaration *obj);
  virtual void postvisitTemplateDeclaration(TemplateDeclaration *obj);
  virtual bool visitTemplateParameter(TemplateParameter *obj);
  virtual void postvisitTemplateParameter(TemplateParameter *obj);
  virtual bool visitTemplateArgument(TemplateArgument *obj);
  virtual void postvisitTemplateArgument(TemplateArgument *obj);
  virtual bool visitNamespaceDecl(NamespaceDecl *obj);
  virtual void postvisitNamespaceDecl(NamespaceDecl *obj);
  virtual bool visitFullExpressionAnnot(FullExpressionAnnot *obj);
  virtual void postvisitFullExpressionAnnot(FullExpressionAnnot *obj);
  virtual bool visitASTTypeof(ASTTypeof *obj);
  virtual void postvisitASTTypeof(ASTTypeof *obj);
  virtual bool visitDesignator(Designator *obj);
  virtual void postvisitDesignator(Designator *obj);
  virtual bool visitAttributeSpecifierList(AttributeSpecifierList *obj);
  virtual void postvisitAttributeSpecifierList(AttributeSpecifierList *obj);
  virtual bool visitAttributeSpecifier(AttributeSpecifier *obj);
  virtual void postvisitAttributeSpecifier(AttributeSpecifier *obj);
  virtual bool visitAttribute(Attribute *obj);
  virtual void postvisitAttribute(Attribute *obj);

  // List 'classes'
  virtual bool visitList_TranslationUnit_topForms(ASTList<TopForm>*);
  virtual void postvisitList_TranslationUnit_topForms(ASTList<TopForm>*);
  virtual bool visitList_TF_namespaceDefn_forms(ASTList<TopForm>*);
  virtual void postvisitList_TF_namespaceDefn_forms(ASTList<TopForm>*);
  virtual bool visitList_Function_inits(FakeList<MemberInit>*);
  virtual void postvisitList_Function_inits(FakeList<MemberInit>*);
  virtual bool visitList_Function_handlers(FakeList<Handler>*);
  virtual void postvisitList_Function_handlers(FakeList<Handler>*);
  virtual bool visitList_MemberInit_args(FakeList<ArgExpression>*);
  virtual void postvisitList_MemberInit_args(FakeList<ArgExpression>*);
  virtual bool visitList_MemberList_list(ASTList<Member>*);
  virtual void postvisitList_MemberList_list(ASTList<Member>*);
  virtual bool visitList_Declaration_decllist(FakeList<Declarator>*);
  virtual void postvisitList_Declaration_decllist(FakeList<Declarator>*);
  virtual bool visitList_TS_classSpec_bases(FakeList<BaseClassSpec>*);
  virtual void postvisitList_TS_classSpec_bases(FakeList<BaseClassSpec>*);
  virtual bool visitList_TS_enumSpec_elts(FakeList<Enumerator>*);
  virtual void postvisitList_TS_enumSpec_elts(FakeList<Enumerator>*);
  virtual bool visitList_D_func_params(FakeList<ASTTypeId>*);
  virtual void postvisitList_D_func_params(FakeList<ASTTypeId>*);
  virtual bool visitList_D_func_kAndR_params(FakeList<PQ_name>*);
  virtual void postvisitList_D_func_kAndR_params(FakeList<PQ_name>*);
  virtual bool visitList_S_try_handlers(FakeList<Handler>*);
  virtual void postvisitList_S_try_handlers(FakeList<Handler>*);
  virtual bool visitList_ExceptionSpec_types(FakeList<ASTTypeId>*);
  virtual void postvisitList_ExceptionSpec_types(FakeList<ASTTypeId>*);
  virtual bool visitList_S_compound_stmts(ASTList<Statement>*);
  virtual void postvisitList_S_compound_stmts(ASTList<Statement>*);
  virtual bool visitList_E_funCall_args(FakeList<ArgExpression>*);
  virtual void postvisitList_E_funCall_args(FakeList<ArgExpression>*);
  virtual bool visitList_E_constructor_args(FakeList<ArgExpression>*);
  virtual void postvisitList_E_constructor_args(FakeList<ArgExpression>*);
  virtual bool visitList_E_new_placementArgs(FakeList<ArgExpression>*);
  virtual void postvisitList_E_new_placementArgs(FakeList<ArgExpression>*);
  virtual bool visitList_ArgExpressionListOpt_list(FakeList<ArgExpression>*);
  virtual void postvisitList_ArgExpressionListOpt_list(FakeList<ArgExpression>*);
  virtual bool visitList_IN_compound_inits(ASTList<Initializer>*);
  virtual void postvisitList_IN_compound_inits(ASTList<Initializer>*);
  virtual bool visitList_IN_ctor_args(FakeList<ArgExpression>*);
  virtual void postvisitList_IN_ctor_args(FakeList<ArgExpression>*);
  virtual bool visitList_TP_template_parameters(FakeList<TemplateParameter>*);
  virtual void postvisitList_TP_template_parameters(FakeList<TemplateParameter>*);
  virtual bool visitList_IN_designated_designator_list(FakeList<Designator>*);
  virtual void postvisitList_IN_designated_designator_list(FakeList<Designator>*);
  virtual bool visitList_FullExpressionAnnot_declarations(ASTList<Declaration>*);
  virtual void postvisitList_FullExpressionAnnot_declarations(ASTList<Declaration>*);
  virtual bool visitList_AT_func_args(FakeList<ArgExpression>*);
  virtual void postvisitList_AT_func_args(FakeList<ArgExpression>*);
  virtual bool visitListItem_TranslationUnit_topForms(TopForm*);
  virtual void postvisitListItem_TranslationUnit_topForms(TopForm*);
  virtual bool visitListItem_TF_namespaceDefn_forms(TopForm*);
  virtual void postvisitListItem_TF_namespaceDefn_forms(TopForm*);
  virtual bool visitListItem_Function_inits(MemberInit*);
  virtual void postvisitListItem_Function_inits(MemberInit*);
  virtual bool visitListItem_Function_handlers(Handler*);
  virtual void postvisitListItem_Function_handlers(Handler*);
  virtual bool visitListItem_MemberInit_args(ArgExpression*);
  virtual void postvisitListItem_MemberInit_args(ArgExpression*);
  virtual bool visitListItem_MemberList_list(Member*);
  virtual void postvisitListItem_MemberList_list(Member*);
  virtual bool visitListItem_Declaration_decllist(Declarator*);
  virtual void postvisitListItem_Declaration_decllist(Declarator*);
  virtual bool visitListItem_TS_classSpec_bases(BaseClassSpec*);
  virtual void postvisitListItem_TS_classSpec_bases(BaseClassSpec*);
  virtual bool visitListItem_TS_enumSpec_elts(Enumerator*);
  virtual void postvisitListItem_TS_enumSpec_elts(Enumerator*);
  virtual bool visitListItem_D_func_params(ASTTypeId*);
  virtual void postvisitListItem_D_func_params(ASTTypeId*);
  virtual bool visitListItem_D_func_kAndR_params(PQ_name*);
  virtual void postvisitListItem_D_func_kAndR_params(PQ_name*);
  virtual bool visitListItem_S_try_handlers(Handler*);
  virtual void postvisitListItem_S_try_handlers(Handler*);
  virtual bool visitListItem_ExceptionSpec_types(ASTTypeId*);
  virtual void postvisitListItem_ExceptionSpec_types(ASTTypeId*);
  virtual bool visitListItem_S_compound_stmts(Statement*);
  virtual void postvisitListItem_S_compound_stmts(Statement*);
  virtual bool visitListItem_E_funCall_args(ArgExpression*);
  virtual void postvisitListItem_E_funCall_args(ArgExpression*);
  virtual bool visitListItem_E_constructor_args(ArgExpression*);
  virtual void postvisitListItem_E_constructor_args(ArgExpression*);
  virtual bool visitListItem_E_new_placementArgs(ArgExpression*);
  virtual void postvisitListItem_E_new_placementArgs(ArgExpression*);
  virtual bool visitListItem_ArgExpressionListOpt_list(ArgExpression*);
  virtual void postvisitListItem_ArgExpressionListOpt_list(ArgExpression*);
  virtual bool visitListItem_IN_compound_inits(Initializer*);
  virtual void postvisitListItem_IN_compound_inits(Initializer*);
  virtual bool visitListItem_IN_ctor_args(ArgExpression*);
  virtual void postvisitListItem_IN_ctor_args(ArgExpression*);
  virtual bool visitListItem_TP_template_parameters(TemplateParameter*);
  virtual void postvisitListItem_TP_template_parameters(TemplateParameter*);
  virtual bool visitListItem_IN_designated_designator_list(Designator*);
  virtual void postvisitListItem_IN_designated_designator_list(Designator*);
  virtual bool visitListItem_FullExpressionAnnot_declarations(Declaration*);
  virtual void postvisitListItem_FullExpressionAnnot_declarations(Declaration*);
  virtual bool visitListItem_AT_func_args(ArgExpression*);
  virtual void postvisitListItem_AT_func_args(ArgExpression*);
};

// the delegator-visitor interface class
class DelegatorASTVisitor : public ASTVisitor {
protected:   // data
  ASTVisitor *client;      // visitor to delegate to
  bool ensureOneVisit;                // check for visiting at most once?
  SObjSet<void*> wasVisitedASTNodes;  // set of visited nodes
  SObjSet<void*> wasVisitedList_ASTListNodes; // set of visited ASTLists
  SObjSet<void*> wasVisitedList_FakeListNodes; // set of visited FakeLists

protected:   // funcs
  bool wasVisitedAST(void *ast);
  bool wasVisitedList_ASTList(void *ast);
  bool wasVisitedList_FakeList(void *ast);

public:      // funcs
  explicit DelegatorASTVisitor(ASTVisitor *client0 = NULL, bool ensureOneVisit0 = false)
    : client(client0)
    , ensureOneVisit(ensureOneVisit0)
  {}

  virtual bool visitTranslationUnit(TranslationUnit *obj);
  virtual void postvisitTranslationUnit(TranslationUnit *obj);
  virtual bool visitTopForm(TopForm *obj);
  virtual void postvisitTopForm(TopForm *obj);
  virtual bool visitFunction(Function *obj);
  virtual void postvisitFunction(Function *obj);
  virtual bool visitMemberInit(MemberInit *obj);
  virtual void postvisitMemberInit(MemberInit *obj);
  virtual bool visitDeclaration(Declaration *obj);
  virtual void postvisitDeclaration(Declaration *obj);
  virtual bool visitASTTypeId(ASTTypeId *obj);
  virtual void postvisitASTTypeId(ASTTypeId *obj);
  virtual bool visitPQName(PQName *obj);
  virtual void postvisitPQName(PQName *obj);
  virtual bool visitTypeSpecifier(TypeSpecifier *obj);
  virtual void postvisitTypeSpecifier(TypeSpecifier *obj);
  virtual bool visitBaseClassSpec(BaseClassSpec *obj);
  virtual void postvisitBaseClassSpec(BaseClassSpec *obj);
  virtual bool visitEnumerator(Enumerator *obj);
  virtual void postvisitEnumerator(Enumerator *obj);
  virtual bool visitMemberList(MemberList *obj);
  virtual void postvisitMemberList(MemberList *obj);
  virtual bool visitMember(Member *obj);
  virtual void postvisitMember(Member *obj);
  virtual bool visitDeclarator(Declarator *obj);
  virtual void postvisitDeclarator(Declarator *obj);
  virtual bool visitIDeclarator(IDeclarator *obj);
  virtual void postvisitIDeclarator(IDeclarator *obj);
  virtual bool visitExceptionSpec(ExceptionSpec *obj);
  virtual void postvisitExceptionSpec(ExceptionSpec *obj);
  virtual bool visitOperatorName(OperatorName *obj);
  virtual void postvisitOperatorName(OperatorName *obj);
  virtual bool visitStatement(Statement *obj);
  virtual void postvisitStatement(Statement *obj);
  virtual bool visitCondition(Condition *obj);
  virtual void postvisitCondition(Condition *obj);
  virtual bool visitHandler(Handler *obj);
  virtual void postvisitHandler(Handler *obj);
  virtual bool visitExpression(Expression *obj);
  virtual void postvisitExpression(Expression *obj);
  virtual bool visitFullExpression(FullExpression *obj);
  virtual void postvisitFullExpression(FullExpression *obj);
  virtual bool visitArgExpression(ArgExpression *obj);
  virtual void postvisitArgExpression(ArgExpression *obj);
  virtual bool visitArgExpressionListOpt(ArgExpressionListOpt *obj);
  virtual void postvisitArgExpressionListOpt(ArgExpressionListOpt *obj);
  virtual bool visitInitializer(Initializer *obj);
  virtual void postvisitInitializer(Initializer *obj);
  virtual bool visitTemplateDeclaration(TemplateDeclaration *obj);
  virtual void postvisitTemplateDeclaration(TemplateDeclaration *obj);
  virtual bool visitTemplateParameter(TemplateParameter *obj);
  virtual void postvisitTemplateParameter(TemplateParameter *obj);
  virtual bool visitTemplateArgument(TemplateArgument *obj);
  virtual void postvisitTemplateArgument(TemplateArgument *obj);
  virtual bool visitNamespaceDecl(NamespaceDecl *obj);
  virtual void postvisitNamespaceDecl(NamespaceDecl *obj);
  virtual bool visitFullExpressionAnnot(FullExpressionAnnot *obj);
  virtual void postvisitFullExpressionAnnot(FullExpressionAnnot *obj);
  virtual bool visitASTTypeof(ASTTypeof *obj);
  virtual void postvisitASTTypeof(ASTTypeof *obj);
  virtual bool visitDesignator(Designator *obj);
  virtual void postvisitDesignator(Designator *obj);
  virtual bool visitAttributeSpecifierList(AttributeSpecifierList *obj);
  virtual void postvisitAttributeSpecifierList(AttributeSpecifierList *obj);
  virtual bool visitAttributeSpecifier(AttributeSpecifier *obj);
  virtual void postvisitAttributeSpecifier(AttributeSpecifier *obj);
  virtual bool visitAttribute(Attribute *obj);
  virtual void postvisitAttribute(Attribute *obj);

  // List 'classes'
  virtual bool visitList_TranslationUnit_topForms(ASTList<TopForm>*);
  virtual void postvisitList_TranslationUnit_topForms(ASTList<TopForm>*);
  virtual bool visitList_TF_namespaceDefn_forms(ASTList<TopForm>*);
  virtual void postvisitList_TF_namespaceDefn_forms(ASTList<TopForm>*);
  virtual bool visitList_Function_inits(FakeList<MemberInit>*);
  virtual void postvisitList_Function_inits(FakeList<MemberInit>*);
  virtual bool visitList_Function_handlers(FakeList<Handler>*);
  virtual void postvisitList_Function_handlers(FakeList<Handler>*);
  virtual bool visitList_MemberInit_args(FakeList<ArgExpression>*);
  virtual void postvisitList_MemberInit_args(FakeList<ArgExpression>*);
  virtual bool visitList_MemberList_list(ASTList<Member>*);
  virtual void postvisitList_MemberList_list(ASTList<Member>*);
  virtual bool visitList_Declaration_decllist(FakeList<Declarator>*);
  virtual void postvisitList_Declaration_decllist(FakeList<Declarator>*);
  virtual bool visitList_TS_classSpec_bases(FakeList<BaseClassSpec>*);
  virtual void postvisitList_TS_classSpec_bases(FakeList<BaseClassSpec>*);
  virtual bool visitList_TS_enumSpec_elts(FakeList<Enumerator>*);
  virtual void postvisitList_TS_enumSpec_elts(FakeList<Enumerator>*);
  virtual bool visitList_D_func_params(FakeList<ASTTypeId>*);
  virtual void postvisitList_D_func_params(FakeList<ASTTypeId>*);
  virtual bool visitList_D_func_kAndR_params(FakeList<PQ_name>*);
  virtual void postvisitList_D_func_kAndR_params(FakeList<PQ_name>*);
  virtual bool visitList_S_try_handlers(FakeList<Handler>*);
  virtual void postvisitList_S_try_handlers(FakeList<Handler>*);
  virtual bool visitList_ExceptionSpec_types(FakeList<ASTTypeId>*);
  virtual void postvisitList_ExceptionSpec_types(FakeList<ASTTypeId>*);
  virtual bool visitList_S_compound_stmts(ASTList<Statement>*);
  virtual void postvisitList_S_compound_stmts(ASTList<Statement>*);
  virtual bool visitList_E_funCall_args(FakeList<ArgExpression>*);
  virtual void postvisitList_E_funCall_args(FakeList<ArgExpression>*);
  virtual bool visitList_E_constructor_args(FakeList<ArgExpression>*);
  virtual void postvisitList_E_constructor_args(FakeList<ArgExpression>*);
  virtual bool visitList_E_new_placementArgs(FakeList<ArgExpression>*);
  virtual void postvisitList_E_new_placementArgs(FakeList<ArgExpression>*);
  virtual bool visitList_ArgExpressionListOpt_list(FakeList<ArgExpression>*);
  virtual void postvisitList_ArgExpressionListOpt_list(FakeList<ArgExpression>*);
  virtual bool visitList_IN_compound_inits(ASTList<Initializer>*);
  virtual void postvisitList_IN_compound_inits(ASTList<Initializer>*);
  virtual bool visitList_IN_ctor_args(FakeList<ArgExpression>*);
  virtual void postvisitList_IN_ctor_args(FakeList<ArgExpression>*);
  virtual bool visitList_TP_template_parameters(FakeList<TemplateParameter>*);
  virtual void postvisitList_TP_template_parameters(FakeList<TemplateParameter>*);
  virtual bool visitList_IN_designated_designator_list(FakeList<Designator>*);
  virtual void postvisitList_IN_designated_designator_list(FakeList<Designator>*);
  virtual bool visitList_FullExpressionAnnot_declarations(ASTList<Declaration>*);
  virtual void postvisitList_FullExpressionAnnot_declarations(ASTList<Declaration>*);
  virtual bool visitList_AT_func_args(FakeList<ArgExpression>*);
  virtual void postvisitList_AT_func_args(FakeList<ArgExpression>*);
  virtual bool visitListItem_TranslationUnit_topForms(TopForm*);
  virtual void postvisitListItem_TranslationUnit_topForms(TopForm*);
  virtual bool visitListItem_TF_namespaceDefn_forms(TopForm*);
  virtual void postvisitListItem_TF_namespaceDefn_forms(TopForm*);
  virtual bool visitListItem_Function_inits(MemberInit*);
  virtual void postvisitListItem_Function_inits(MemberInit*);
  virtual bool visitListItem_Function_handlers(Handler*);
  virtual void postvisitListItem_Function_handlers(Handler*);
  virtual bool visitListItem_MemberInit_args(ArgExpression*);
  virtual void postvisitListItem_MemberInit_args(ArgExpression*);
  virtual bool visitListItem_MemberList_list(Member*);
  virtual void postvisitListItem_MemberList_list(Member*);
  virtual bool visitListItem_Declaration_decllist(Declarator*);
  virtual void postvisitListItem_Declaration_decllist(Declarator*);
  virtual bool visitListItem_TS_classSpec_bases(BaseClassSpec*);
  virtual void postvisitListItem_TS_classSpec_bases(BaseClassSpec*);
  virtual bool visitListItem_TS_enumSpec_elts(Enumerator*);
  virtual void postvisitListItem_TS_enumSpec_elts(Enumerator*);
  virtual bool visitListItem_D_func_params(ASTTypeId*);
  virtual void postvisitListItem_D_func_params(ASTTypeId*);
  virtual bool visitListItem_D_func_kAndR_params(PQ_name*);
  virtual void postvisitListItem_D_func_kAndR_params(PQ_name*);
  virtual bool visitListItem_S_try_handlers(Handler*);
  virtual void postvisitListItem_S_try_handlers(Handler*);
  virtual bool visitListItem_ExceptionSpec_types(ASTTypeId*);
  virtual void postvisitListItem_ExceptionSpec_types(ASTTypeId*);
  virtual bool visitListItem_S_compound_stmts(Statement*);
  virtual void postvisitListItem_S_compound_stmts(Statement*);
  virtual bool visitListItem_E_funCall_args(ArgExpression*);
  virtual void postvisitListItem_E_funCall_args(ArgExpression*);
  virtual bool visitListItem_E_constructor_args(ArgExpression*);
  virtual void postvisitListItem_E_constructor_args(ArgExpression*);
  virtual bool visitListItem_E_new_placementArgs(ArgExpression*);
  virtual void postvisitListItem_E_new_placementArgs(ArgExpression*);
  virtual bool visitListItem_ArgExpressionListOpt_list(ArgExpression*);
  virtual void postvisitListItem_ArgExpressionListOpt_list(ArgExpression*);
  virtual bool visitListItem_IN_compound_inits(Initializer*);
  virtual void postvisitListItem_IN_compound_inits(Initializer*);
  virtual bool visitListItem_IN_ctor_args(ArgExpression*);
  virtual void postvisitListItem_IN_ctor_args(ArgExpression*);
  virtual bool visitListItem_TP_template_parameters(TemplateParameter*);
  virtual void postvisitListItem_TP_template_parameters(TemplateParameter*);
  virtual bool visitListItem_IN_designated_designator_list(Designator*);
  virtual void postvisitListItem_IN_designated_designator_list(Designator*);
  virtual bool visitListItem_FullExpressionAnnot_declarations(Declaration*);
  virtual void postvisitListItem_FullExpressionAnnot_declarations(Declaration*);
  virtual bool visitListItem_AT_func_args(ArgExpression*);
  virtual void postvisitListItem_AT_func_args(ArgExpression*);
};

// the xml-visitor interface class
class XmlAstWriter_AstVisitor : public ASTVisitor {
protected:   // data
  std::ostream &out;                  // output stream to print to
  IdentityManager &idmgr; // Identity Manager to use
  int &depth;                         // current depth
  bool indent;                        // should the xml be indented
  SObjSet<void*> wasVisitedASTNodes;  // set of visited nodes
  SObjSet<void*> wasVisitedList_ASTListNodes; // set of visited ASTLists
  SObjSet<void*> wasVisitedList_FakeListNodes; // set of visited FakeLists

protected:   // funcs
  bool wasVisitedAST(void *ast);
  bool wasVisitedList_ASTList(void *ast);
  bool wasVisitedList_FakeList(void *ast);
  void printIndentation();


  /* this is elsa/cc_tcheck.ast */
  virtual bool shouldSerialize(Variable const *) { return true; }
public:      // funcs
  explicit XmlAstWriter_AstVisitor(std::ostream &out0, IdentityManager &idmgr0, int &depth0, bool indent0 = false)
    : out(out0)
    , idmgr(idmgr0)
    , depth(depth0)
    , indent(indent0)
  {}

  virtual bool visitTranslationUnit(TranslationUnit *obj);
  virtual void postvisitTranslationUnit(TranslationUnit *obj);
  virtual bool visitTopForm(TopForm *obj);
  virtual void postvisitTopForm(TopForm *obj);
  virtual bool visitFunction(Function *obj);
  virtual void postvisitFunction(Function *obj);
  virtual bool visitMemberInit(MemberInit *obj);
  virtual void postvisitMemberInit(MemberInit *obj);
  virtual bool visitDeclaration(Declaration *obj);
  virtual void postvisitDeclaration(Declaration *obj);
  virtual bool visitASTTypeId(ASTTypeId *obj);
  virtual void postvisitASTTypeId(ASTTypeId *obj);
  virtual bool visitPQName(PQName *obj);
  virtual void postvisitPQName(PQName *obj);
  virtual bool visitTypeSpecifier(TypeSpecifier *obj);
  virtual void postvisitTypeSpecifier(TypeSpecifier *obj);
  virtual bool visitBaseClassSpec(BaseClassSpec *obj);
  virtual void postvisitBaseClassSpec(BaseClassSpec *obj);
  virtual bool visitEnumerator(Enumerator *obj);
  virtual void postvisitEnumerator(Enumerator *obj);
  virtual bool visitMemberList(MemberList *obj);
  virtual void postvisitMemberList(MemberList *obj);
  virtual bool visitMember(Member *obj);
  virtual void postvisitMember(Member *obj);
  virtual bool visitDeclarator(Declarator *obj);
  virtual void postvisitDeclarator(Declarator *obj);
  virtual bool visitIDeclarator(IDeclarator *obj);
  virtual void postvisitIDeclarator(IDeclarator *obj);
  virtual bool visitExceptionSpec(ExceptionSpec *obj);
  virtual void postvisitExceptionSpec(ExceptionSpec *obj);
  virtual bool visitOperatorName(OperatorName *obj);
  virtual void postvisitOperatorName(OperatorName *obj);
  virtual bool visitStatement(Statement *obj);
  virtual void postvisitStatement(Statement *obj);
  virtual bool visitCondition(Condition *obj);
  virtual void postvisitCondition(Condition *obj);
  virtual bool visitHandler(Handler *obj);
  virtual void postvisitHandler(Handler *obj);
  virtual bool visitExpression(Expression *obj);
  virtual void postvisitExpression(Expression *obj);
  virtual bool visitFullExpression(FullExpression *obj);
  virtual void postvisitFullExpression(FullExpression *obj);
  virtual bool visitArgExpression(ArgExpression *obj);
  virtual void postvisitArgExpression(ArgExpression *obj);
  virtual bool visitArgExpressionListOpt(ArgExpressionListOpt *obj);
  virtual void postvisitArgExpressionListOpt(ArgExpressionListOpt *obj);
  virtual bool visitInitializer(Initializer *obj);
  virtual void postvisitInitializer(Initializer *obj);
  virtual bool visitTemplateDeclaration(TemplateDeclaration *obj);
  virtual void postvisitTemplateDeclaration(TemplateDeclaration *obj);
  virtual bool visitTemplateParameter(TemplateParameter *obj);
  virtual void postvisitTemplateParameter(TemplateParameter *obj);
  virtual bool visitTemplateArgument(TemplateArgument *obj);
  virtual void postvisitTemplateArgument(TemplateArgument *obj);
  virtual bool visitNamespaceDecl(NamespaceDecl *obj);
  virtual void postvisitNamespaceDecl(NamespaceDecl *obj);
  virtual bool visitFullExpressionAnnot(FullExpressionAnnot *obj);
  virtual void postvisitFullExpressionAnnot(FullExpressionAnnot *obj);
  virtual bool visitASTTypeof(ASTTypeof *obj);
  virtual void postvisitASTTypeof(ASTTypeof *obj);
  virtual bool visitDesignator(Designator *obj);
  virtual void postvisitDesignator(Designator *obj);
  virtual bool visitAttributeSpecifierList(AttributeSpecifierList *obj);
  virtual void postvisitAttributeSpecifierList(AttributeSpecifierList *obj);
  virtual bool visitAttributeSpecifier(AttributeSpecifier *obj);
  virtual void postvisitAttributeSpecifier(AttributeSpecifier *obj);
  virtual bool visitAttribute(Attribute *obj);
  virtual void postvisitAttribute(Attribute *obj);

  // List 'classes'
  virtual bool visitList_TranslationUnit_topForms(ASTList<TopForm>*);
  virtual void postvisitList_TranslationUnit_topForms(ASTList<TopForm>*);
  virtual bool visitList_TF_namespaceDefn_forms(ASTList<TopForm>*);
  virtual void postvisitList_TF_namespaceDefn_forms(ASTList<TopForm>*);
  virtual bool visitList_Function_inits(FakeList<MemberInit>*);
  virtual void postvisitList_Function_inits(FakeList<MemberInit>*);
  virtual bool visitList_Function_handlers(FakeList<Handler>*);
  virtual void postvisitList_Function_handlers(FakeList<Handler>*);
  virtual bool visitList_MemberInit_args(FakeList<ArgExpression>*);
  virtual void postvisitList_MemberInit_args(FakeList<ArgExpression>*);
  virtual bool visitList_MemberList_list(ASTList<Member>*);
  virtual void postvisitList_MemberList_list(ASTList<Member>*);
  virtual bool visitList_Declaration_decllist(FakeList<Declarator>*);
  virtual void postvisitList_Declaration_decllist(FakeList<Declarator>*);
  virtual bool visitList_TS_classSpec_bases(FakeList<BaseClassSpec>*);
  virtual void postvisitList_TS_classSpec_bases(FakeList<BaseClassSpec>*);
  virtual bool visitList_TS_enumSpec_elts(FakeList<Enumerator>*);
  virtual void postvisitList_TS_enumSpec_elts(FakeList<Enumerator>*);
  virtual bool visitList_D_func_params(FakeList<ASTTypeId>*);
  virtual void postvisitList_D_func_params(FakeList<ASTTypeId>*);
  virtual bool visitList_D_func_kAndR_params(FakeList<PQ_name>*);
  virtual void postvisitList_D_func_kAndR_params(FakeList<PQ_name>*);
  virtual bool visitList_S_try_handlers(FakeList<Handler>*);
  virtual void postvisitList_S_try_handlers(FakeList<Handler>*);
  virtual bool visitList_ExceptionSpec_types(FakeList<ASTTypeId>*);
  virtual void postvisitList_ExceptionSpec_types(FakeList<ASTTypeId>*);
  virtual bool visitList_S_compound_stmts(ASTList<Statement>*);
  virtual void postvisitList_S_compound_stmts(ASTList<Statement>*);
  virtual bool visitList_E_funCall_args(FakeList<ArgExpression>*);
  virtual void postvisitList_E_funCall_args(FakeList<ArgExpression>*);
  virtual bool visitList_E_constructor_args(FakeList<ArgExpression>*);
  virtual void postvisitList_E_constructor_args(FakeList<ArgExpression>*);
  virtual bool visitList_E_new_placementArgs(FakeList<ArgExpression>*);
  virtual void postvisitList_E_new_placementArgs(FakeList<ArgExpression>*);
  virtual bool visitList_ArgExpressionListOpt_list(FakeList<ArgExpression>*);
  virtual void postvisitList_ArgExpressionListOpt_list(FakeList<ArgExpression>*);
  virtual bool visitList_IN_compound_inits(ASTList<Initializer>*);
  virtual void postvisitList_IN_compound_inits(ASTList<Initializer>*);
  virtual bool visitList_IN_ctor_args(FakeList<ArgExpression>*);
  virtual void postvisitList_IN_ctor_args(FakeList<ArgExpression>*);
  virtual bool visitList_TP_template_parameters(FakeList<TemplateParameter>*);
  virtual void postvisitList_TP_template_parameters(FakeList<TemplateParameter>*);
  virtual bool visitList_IN_designated_designator_list(FakeList<Designator>*);
  virtual void postvisitList_IN_designated_designator_list(FakeList<Designator>*);
  virtual bool visitList_FullExpressionAnnot_declarations(ASTList<Declaration>*);
  virtual void postvisitList_FullExpressionAnnot_declarations(ASTList<Declaration>*);
  virtual bool visitList_AT_func_args(FakeList<ArgExpression>*);
  virtual void postvisitList_AT_func_args(FakeList<ArgExpression>*);
  virtual bool visitListItem_TranslationUnit_topForms(TopForm*);
  virtual void postvisitListItem_TranslationUnit_topForms(TopForm*);
  virtual bool visitListItem_TF_namespaceDefn_forms(TopForm*);
  virtual void postvisitListItem_TF_namespaceDefn_forms(TopForm*);
  virtual bool visitListItem_Function_inits(MemberInit*);
  virtual void postvisitListItem_Function_inits(MemberInit*);
  virtual bool visitListItem_Function_handlers(Handler*);
  virtual void postvisitListItem_Function_handlers(Handler*);
  virtual bool visitListItem_MemberInit_args(ArgExpression*);
  virtual void postvisitListItem_MemberInit_args(ArgExpression*);
  virtual bool visitListItem_MemberList_list(Member*);
  virtual void postvisitListItem_MemberList_list(Member*);
  virtual bool visitListItem_Declaration_decllist(Declarator*);
  virtual void postvisitListItem_Declaration_decllist(Declarator*);
  virtual bool visitListItem_TS_classSpec_bases(BaseClassSpec*);
  virtual void postvisitListItem_TS_classSpec_bases(BaseClassSpec*);
  virtual bool visitListItem_TS_enumSpec_elts(Enumerator*);
  virtual void postvisitListItem_TS_enumSpec_elts(Enumerator*);
  virtual bool visitListItem_D_func_params(ASTTypeId*);
  virtual void postvisitListItem_D_func_params(ASTTypeId*);
  virtual bool visitListItem_D_func_kAndR_params(PQ_name*);
  virtual void postvisitListItem_D_func_kAndR_params(PQ_name*);
  virtual bool visitListItem_S_try_handlers(Handler*);
  virtual void postvisitListItem_S_try_handlers(Handler*);
  virtual bool visitListItem_ExceptionSpec_types(ASTTypeId*);
  virtual void postvisitListItem_ExceptionSpec_types(ASTTypeId*);
  virtual bool visitListItem_S_compound_stmts(Statement*);
  virtual void postvisitListItem_S_compound_stmts(Statement*);
  virtual bool visitListItem_E_funCall_args(ArgExpression*);
  virtual void postvisitListItem_E_funCall_args(ArgExpression*);
  virtual bool visitListItem_E_constructor_args(ArgExpression*);
  virtual void postvisitListItem_E_constructor_args(ArgExpression*);
  virtual bool visitListItem_E_new_placementArgs(ArgExpression*);
  virtual void postvisitListItem_E_new_placementArgs(ArgExpression*);
  virtual bool visitListItem_ArgExpressionListOpt_list(ArgExpression*);
  virtual void postvisitListItem_ArgExpressionListOpt_list(ArgExpression*);
  virtual bool visitListItem_IN_compound_inits(Initializer*);
  virtual void postvisitListItem_IN_compound_inits(Initializer*);
  virtual bool visitListItem_IN_ctor_args(ArgExpression*);
  virtual void postvisitListItem_IN_ctor_args(ArgExpression*);
  virtual bool visitListItem_TP_template_parameters(TemplateParameter*);
  virtual void postvisitListItem_TP_template_parameters(TemplateParameter*);
  virtual bool visitListItem_IN_designated_designator_list(Designator*);
  virtual void postvisitListItem_IN_designated_designator_list(Designator*);
  virtual bool visitListItem_FullExpressionAnnot_declarations(Declaration*);
  virtual void postvisitListItem_FullExpressionAnnot_declarations(Declaration*);
  virtual bool visitListItem_AT_func_args(ArgExpression*);
  virtual void postvisitListItem_AT_func_args(ArgExpression*);
};

#endif // CC_AST_GEN_H
