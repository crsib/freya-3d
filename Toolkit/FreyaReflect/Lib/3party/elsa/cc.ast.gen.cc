// cc.ast.gen.cc
// *** DO NOT EDIT ***
// generated automatically by astgen, from cc.ast
// active extension modules: cc_tcheck.ast cc_print.ast cfg.ast cc_elaborate.ast bpprint.ast cc2c.ast gnu.ast kandr.ast

#include "cc.ast.gen.h"      // this module
#include "xmlhelp.h"      // to/fromXml_bool/int
#include <string.h>       // strcmp
#include "exc.h"          // xformat


// ------------------ TranslationUnit -------------------
// *** DO NOT EDIT ***
TranslationUnit::~TranslationUnit()
{
  topForms.deleteAll();
}

void TranslationUnit::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, TranslationUnit);

  PRINT_LIST(TopForm, topForms);
}

void TranslationUnit::gdb() const
  { debugPrint(std::cout, 0); }

TranslationUnit *TranslationUnit::clone() const
{
  TranslationUnit *ret = new TranslationUnit(
    cloneASTList(topForms)
  );
  return ret;
}


// ------------------ TopForm -------------------
// *** DO NOT EDIT ***
TopForm::~TopForm()
{
}

char const * const TopForm::kindNames[TopForm::NUM_KINDS] = {
  "TF_decl",
  "TF_func",
  "TF_template",
  "TF_explicitInst",
  "TF_linkage",
  "TF_one_linkage",
  "TF_asm",
  "TF_namespaceDefn",
  "TF_namespaceDecl",
};

void TopForm::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_GENERIC(loc);
}

void TopForm::gdb() const
  { debugPrint(std::cout, 0); }

DEFN_AST_DOWNCASTS(TopForm, TF_decl, TF_DECL)

TF_decl::~TF_decl()
{
  delete decl;
}

void TF_decl::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, TF_decl);

  TopForm::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(decl);
}

TF_decl *TF_decl::clone() const
{
  TF_decl *ret = new TF_decl(
    loc,
    decl? decl->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(TopForm, TF_func, TF_FUNC)

TF_func::~TF_func()
{
  delete f;
}

void TF_func::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, TF_func);

  TopForm::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(f);
}

TF_func *TF_func::clone() const
{
  TF_func *ret = new TF_func(
    loc,
    f? f->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(TopForm, TF_template, TF_TEMPLATE)

TF_template::~TF_template()
{
  delete td;
}

void TF_template::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, TF_template);

  TopForm::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(td);
}

TF_template *TF_template::clone() const
{
  TF_template *ret = new TF_template(
    loc,
    td? td->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(TopForm, TF_explicitInst, TF_EXPLICITINST)

TF_explicitInst::~TF_explicitInst()
{
  delete d;
}

void TF_explicitInst::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, TF_explicitInst);

  TopForm::debugPrint(os, indent, subtreeName);

  PRINT_GENERIC(instFlags);
  PRINT_SUBTREE(d);
}

TF_explicitInst *TF_explicitInst::clone() const
{
  TF_explicitInst *ret = new TF_explicitInst(
    loc,
    instFlags,
    d? d->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(TopForm, TF_linkage, TF_LINKAGE)

TF_linkage::~TF_linkage()
{
  delete forms;
}

void TF_linkage::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, TF_linkage);

  TopForm::debugPrint(os, indent, subtreeName);

  PRINT_CSTRING(linkageType);
  PRINT_SUBTREE(forms);
}

TF_linkage *TF_linkage::clone() const
{
  TF_linkage *ret = new TF_linkage(
    loc,
    linkageType,
    forms? forms->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(TopForm, TF_one_linkage, TF_ONE_LINKAGE)

TF_one_linkage::~TF_one_linkage()
{
  delete form;
}

void TF_one_linkage::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, TF_one_linkage);

  TopForm::debugPrint(os, indent, subtreeName);

  PRINT_CSTRING(linkageType);
  PRINT_SUBTREE(form);
}

TF_one_linkage *TF_one_linkage::clone() const
{
  TF_one_linkage *ret = new TF_one_linkage(
    loc,
    linkageType,
    form? form->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(TopForm, TF_asm, TF_ASM)

TF_asm::~TF_asm()
{
  delete text;
}

void TF_asm::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, TF_asm);

  TopForm::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(text);
}

TF_asm *TF_asm::clone() const
{
  TF_asm *ret = new TF_asm(
    loc,
    text? text->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(TopForm, TF_namespaceDefn, TF_NAMESPACEDEFN)

TF_namespaceDefn::~TF_namespaceDefn()
{
  forms.deleteAll();
}

void TF_namespaceDefn::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, TF_namespaceDefn);

  TopForm::debugPrint(os, indent, subtreeName);

  PRINT_CSTRING(name);
  PRINT_LIST(TopForm, forms);
}

TF_namespaceDefn *TF_namespaceDefn::clone() const
{
  TF_namespaceDefn *ret = new TF_namespaceDefn(
    loc,
    name,
    cloneASTList(forms)
  );
  return ret;
}

DEFN_AST_DOWNCASTS(TopForm, TF_namespaceDecl, TF_NAMESPACEDECL)

TF_namespaceDecl::~TF_namespaceDecl()
{
  delete decl;
}

void TF_namespaceDecl::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, TF_namespaceDecl);

  TopForm::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(decl);
}

TF_namespaceDecl *TF_namespaceDecl::clone() const
{
  TF_namespaceDecl *ret = new TF_namespaceDecl(
    loc,
    decl? decl->clone() : NULL
  );
  return ret;
}


// ------------------ Function -------------------
// *** DO NOT EDIT ***
Function::~Function()
{
  delete retspec;
  delete nameAndParams;
  delete body;
  delete dtorStatement;
}

void Function::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, Function);

   printExtras(os, indent); ;
   ind(os,indent) << "retVar: " << refersTo(retVar) << "\n"; ;
  PRINT_GENERIC(dflags);
  PRINT_SUBTREE(retspec);
  PRINT_SUBTREE(nameAndParams);
  PRINT_FAKE_LIST(MemberInit, inits);
  PRINT_SUBTREE(body);
  PRINT_FAKE_LIST(Handler, handlers);
  PRINT_SUBTREE(dtorStatement);
  PRINT_BOOL(implicitlyDefined);
}

void Function::gdb() const
  { debugPrint(std::cout, 0); }

Function *Function::clone() const
{
   return shallowClone(); ;
}


// ------------------ MemberInit -------------------
// *** DO NOT EDIT ***
MemberInit::~MemberInit()
{
  delete name;
  delete annot;
  delete ctorStatement;
}

void MemberInit::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, MemberInit);

   printExtras(os, indent); ;
  PRINT_GENERIC(loc);
  PRINT_GENERIC(endloc);
  PRINT_SUBTREE(name);
  PRINT_FAKE_LIST(ArgExpression, args);
  PRINT_SUBTREE(ctorStatement);
}

void MemberInit::gdb() const
  { debugPrint(std::cout, 0); }

MemberInit *MemberInit::clone() const
{
  MemberInit *ret = new MemberInit(
    loc,
    endloc,
    name? name->clone() : NULL,
    cloneFakeList(args)
  );
  
    ret->member = member;
    ret->base = base;
    ret->ctorVar = ctorVar;
  ;
  return ret;
}


// ------------------ Declaration -------------------
// *** DO NOT EDIT ***
Declaration::~Declaration()
{
  delete spec;
}

void Declaration::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, Declaration);

  PRINT_GENERIC(dflags);
  PRINT_SUBTREE(spec);
  PRINT_FAKE_LIST(Declarator, decllist);
}

void Declaration::gdb() const
  { debugPrint(std::cout, 0); }

Declaration *Declaration::clone() const
{
  Declaration *ret = new Declaration(
    dflags,
    spec? spec->clone() : NULL,
    cloneFakeList(decllist)
  );
  return ret;
}


// ------------------ ASTTypeId -------------------
// *** DO NOT EDIT ***
ASTTypeId::~ASTTypeId()
{
  delete spec;
  delete decl;
}

void ASTTypeId::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, ASTTypeId);

  PRINT_SUBTREE(spec);
  PRINT_SUBTREE(decl);
}

void ASTTypeId::gdb() const
  { debugPrint(std::cout, 0); }

ASTTypeId *ASTTypeId::clone() const
{
  ASTTypeId *ret = new ASTTypeId(
    spec? spec->clone() : NULL,
    decl? decl->clone() : NULL
  );
  return ret;
}


// ------------------ PQName -------------------
// *** DO NOT EDIT ***
PQName::~PQName()
{
}

char const * const PQName::kindNames[PQName::NUM_KINDS] = {
  "PQ_qualifier",
  "PQ_name",
  "PQ_operator",
  "PQ_template",
  "PQ_variable",
};

void PQName::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_GENERIC(loc);
}

void PQName::gdb() const
  { debugPrint(std::cout, 0); }

DEFN_AST_DOWNCASTS(PQName, PQ_qualifier, PQ_QUALIFIER)

PQ_qualifier::~PQ_qualifier()
{
  delete templArgs;
  delete rest;
}

void PQ_qualifier::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
         if (ambiguity) {
           printAmbiguities(os, indent);
           return;     // skip the normal, unambiguous-node print code
         }
       ;
  PRINT_HEADER(subtreeName, PQ_qualifier);

  PQName::debugPrint(os, indent, subtreeName);

  
         ind(os, indent) << "qualifierVar: " << refersTo(qualifierVar) << "\n";
       ;
  PRINT_CSTRING(qualifier);
  PRINT_SUBTREE(templArgs);
  PRINT_SUBTREE(rest);
}

PQ_qualifier *PQ_qualifier::clone() const
{
  PQ_qualifier *ret = new PQ_qualifier(
    loc,
    qualifier,
    templArgs? templArgs->clone() : NULL,
    rest? rest->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(PQName, PQ_name, PQ_NAME)

PQ_name::~PQ_name()
{
}

void PQ_name::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, PQ_name);

  PQName::debugPrint(os, indent, subtreeName);

  PRINT_CSTRING(name);
}

PQ_name *PQ_name::clone() const
{
  PQ_name *ret = new PQ_name(
    loc,
    name
  );
  return ret;
}

DEFN_AST_DOWNCASTS(PQName, PQ_operator, PQ_OPERATOR)

PQ_operator::~PQ_operator()
{
  delete o;
}

void PQ_operator::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, PQ_operator);

  PQName::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(o);
  PRINT_CSTRING(fakeName);
}

PQ_operator *PQ_operator::clone() const
{
  PQ_operator *ret = new PQ_operator(
    loc,
    o? o->clone() : NULL,
    fakeName
  );
  return ret;
}

DEFN_AST_DOWNCASTS(PQName, PQ_template, PQ_TEMPLATE)

PQ_template::~PQ_template()
{
  delete templArgs;
}

void PQ_template::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, PQ_template);

  PQName::debugPrint(os, indent, subtreeName);

  PRINT_CSTRING(name);
  PRINT_SUBTREE(templArgs);
}

PQ_template *PQ_template::clone() const
{
  PQ_template *ret = new PQ_template(
    loc,
    name,
    templArgs? templArgs->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(PQName, PQ_variable, PQ_VARIABLE)

PQ_variable::~PQ_variable()
{
}

void PQ_variable::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, PQ_variable);

  PQName::debugPrint(os, indent, subtreeName);

  PRINT_GENERIC(var);
}

PQ_variable *PQ_variable::clone() const
{
  PQ_variable *ret = new PQ_variable(
    loc,
    var
  );
  return ret;
}


// ------------------ TypeSpecifier -------------------
// *** DO NOT EDIT ***
TypeSpecifier::~TypeSpecifier()
{
}

char const * const TypeSpecifier::kindNames[TypeSpecifier::NUM_KINDS] = {
  "TS_name",
  "TS_simple",
  "TS_elaborated",
  "TS_classSpec",
  "TS_enumSpec",
  "TS_type",
  "TS_typeof",
};

void TypeSpecifier::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
   printExtras(os, indent); ;
  PRINT_GENERIC(loc);
  PRINT_GENERIC(cv);
}

void TypeSpecifier::gdb() const
  { debugPrint(std::cout, 0); }

DEFN_AST_DOWNCASTS(TypeSpecifier, TS_name, TS_NAME)

TS_name::~TS_name()
{
  delete name;
}

void TS_name::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, TS_name);

  TypeSpecifier::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(name);
  PRINT_BOOL(typenameUsed);
}

TS_name *TS_name::clone() const
{
  TS_name *ret = new TS_name(
    loc,
    name? name->clone() : NULL,
    typenameUsed
  );
   ret->cv = cv; ;
   ret->nondependentVar = nondependentVar; ;
  return ret;
}

DEFN_AST_DOWNCASTS(TypeSpecifier, TS_simple, TS_SIMPLE)

TS_simple::~TS_simple()
{
}

void TS_simple::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, TS_simple);

  TypeSpecifier::debugPrint(os, indent, subtreeName);

  PRINT_GENERIC(id);
}

TS_simple *TS_simple::clone() const
{
  TS_simple *ret = new TS_simple(
    loc,
    id
  );
   ret->cv = cv; ;
  return ret;
}

DEFN_AST_DOWNCASTS(TypeSpecifier, TS_elaborated, TS_ELABORATED)

TS_elaborated::~TS_elaborated()
{
  delete name;
}

void TS_elaborated::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, TS_elaborated);

  TypeSpecifier::debugPrint(os, indent, subtreeName);

  PRINT_GENERIC(keyword);
  PRINT_SUBTREE(name);
}

TS_elaborated *TS_elaborated::clone() const
{
  TS_elaborated *ret = new TS_elaborated(
    loc,
    keyword,
    name? name->clone() : NULL
  );
   ret->cv = cv; ;
  return ret;
}

DEFN_AST_DOWNCASTS(TypeSpecifier, TS_classSpec, TS_CLASSSPEC)

TS_classSpec::~TS_classSpec()
{
  delete name;
  delete members;
}

void TS_classSpec::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, TS_classSpec);

  TypeSpecifier::debugPrint(os, indent, subtreeName);

   printExtras(os, indent); ;
  PRINT_GENERIC(keyword);
  PRINT_SUBTREE(name);
  PRINT_FAKE_LIST(BaseClassSpec, bases);
  PRINT_SUBTREE(members);
}

TS_classSpec *TS_classSpec::clone() const
{
  TS_classSpec *ret = new TS_classSpec(
    loc,
    keyword,
    name? name->clone() : NULL,
    cloneFakeList(bases),
    members? members->clone() : NULL
  );
   ret->cv = cv; ;
  return ret;
}

DEFN_AST_DOWNCASTS(TypeSpecifier, TS_enumSpec, TS_ENUMSPEC)

TS_enumSpec::~TS_enumSpec()
{
}

void TS_enumSpec::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, TS_enumSpec);

  TypeSpecifier::debugPrint(os, indent, subtreeName);

  PRINT_CSTRING(name);
  PRINT_FAKE_LIST(Enumerator, elts);
}

TS_enumSpec *TS_enumSpec::clone() const
{
  TS_enumSpec *ret = new TS_enumSpec(
    loc,
    name,
    cloneFakeList(elts)
  );
   ret->cv = cv; ;
  return ret;
}

DEFN_AST_DOWNCASTS(TypeSpecifier, TS_type, TS_TYPE)

TS_type::~TS_type()
{
}

void TS_type::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, TS_type);

  TypeSpecifier::debugPrint(os, indent, subtreeName);

  PRINT_GENERIC(type);
}

TS_type *TS_type::clone() const
{
  TS_type *ret = new TS_type(
    loc,
    type
  );
   ret->cv = cv; ;
  return ret;
}

DEFN_AST_DOWNCASTS(TypeSpecifier, TS_typeof, TS_TYPEOF)

TS_typeof::~TS_typeof()
{
  delete atype;
}

void TS_typeof::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, TS_typeof);

  TypeSpecifier::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(atype);
}

TS_typeof *TS_typeof::clone() const
{
  TS_typeof *ret = new TS_typeof(
    loc,
    atype? atype->clone() : NULL
  );
   ret->cv = cv; ;
  return ret;
}


// ------------------ BaseClassSpec -------------------
// *** DO NOT EDIT ***
BaseClassSpec::~BaseClassSpec()
{
  delete name;
}

void BaseClassSpec::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, BaseClassSpec);

   printExtras(os, indent); ;
  PRINT_BOOL(isVirtual);
  PRINT_GENERIC(access);
  PRINT_SUBTREE(name);
}

void BaseClassSpec::gdb() const
  { debugPrint(std::cout, 0); }

BaseClassSpec *BaseClassSpec::clone() const
{
  BaseClassSpec *ret = new BaseClassSpec(
    isVirtual,
    access,
    name? name->clone() : NULL
  );
  return ret;
}


// ------------------ Enumerator -------------------
// *** DO NOT EDIT ***
Enumerator::~Enumerator()
{
  delete expr;
}

void Enumerator::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, Enumerator);

   printExtras(os, indent); ;
  PRINT_GENERIC(loc);
  PRINT_CSTRING(name);
  PRINT_SUBTREE(expr);
}

void Enumerator::gdb() const
  { debugPrint(std::cout, 0); }

Enumerator *Enumerator::clone() const
{
  Enumerator *ret = new Enumerator(
    loc,
    name,
    expr? expr->clone() : NULL
  );
  return ret;
}


// ------------------ MemberList -------------------
// *** DO NOT EDIT ***
MemberList::~MemberList()
{
  list.deleteAll();
}

void MemberList::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, MemberList);

  PRINT_LIST(Member, list);
}

void MemberList::gdb() const
  { debugPrint(std::cout, 0); }

MemberList *MemberList::clone() const
{
  MemberList *ret = new MemberList(
    cloneASTList(list)
  );
  return ret;
}


// ------------------ Member -------------------
// *** DO NOT EDIT ***
Member::~Member()
{
}

char const * const Member::kindNames[Member::NUM_KINDS] = {
  "MR_decl",
  "MR_func",
  "MR_access",
  "MR_usingDecl",
  "MR_template",
};

void Member::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_GENERIC(loc);
  PRINT_GENERIC(endloc);
}

void Member::gdb() const
  { debugPrint(std::cout, 0); }

DEFN_AST_DOWNCASTS(Member, MR_decl, MR_DECL)

MR_decl::~MR_decl()
{
  delete d;
}

void MR_decl::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, MR_decl);

  Member::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(d);
}

MR_decl *MR_decl::clone() const
{
  MR_decl *ret = new MR_decl(
    loc,
    endloc,
    d? d->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Member, MR_func, MR_FUNC)

MR_func::~MR_func()
{
  delete f;
}

void MR_func::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, MR_func);

  Member::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(f);
}

MR_func *MR_func::clone() const
{
  MR_func *ret = new MR_func(
    loc,
    endloc,
    f? f->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Member, MR_access, MR_ACCESS)

MR_access::~MR_access()
{
}

void MR_access::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, MR_access);

  Member::debugPrint(os, indent, subtreeName);

  PRINT_GENERIC(k);
}

MR_access *MR_access::clone() const
{
  MR_access *ret = new MR_access(
    loc,
    endloc,
    k
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Member, MR_usingDecl, MR_USINGDECL)

MR_usingDecl::~MR_usingDecl()
{
  delete decl;
}

void MR_usingDecl::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, MR_usingDecl);

  Member::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(decl);
}

MR_usingDecl *MR_usingDecl::clone() const
{
  MR_usingDecl *ret = new MR_usingDecl(
    loc,
    endloc,
    decl? decl->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Member, MR_template, MR_TEMPLATE)

MR_template::~MR_template()
{
  delete d;
}

void MR_template::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, MR_template);

  Member::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(d);
}

MR_template *MR_template::clone() const
{
  MR_template *ret = new MR_template(
    loc,
    endloc,
    d? d->clone() : NULL
  );
  return ret;
}


// ------------------ Declarator -------------------
// *** DO NOT EDIT ***
Declarator::~Declarator()
{
  delete decl;
  delete init;
  delete ctorStatement;
  delete dtorStatement;
}

void Declarator::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, Declarator);

   printExtras(os, indent); ;
  PRINT_SUBTREE(decl);
  PRINT_SUBTREE(init);
  PRINT_SUBTREE(ctorStatement);
  PRINT_SUBTREE(dtorStatement);
}

void Declarator::gdb() const
  { debugPrint(std::cout, 0); }

Declarator *Declarator::clone() const
{
  Declarator *ret = new Declarator(
    decl? decl->clone() : NULL,
    init? init->clone() : NULL
  );
  ret->var = var;;
  ret->context = context;;
  return ret;
}


// ------------------ IDeclarator -------------------
// *** DO NOT EDIT ***
IDeclarator::~IDeclarator()
{
}

char const * const IDeclarator::kindNames[IDeclarator::NUM_KINDS] = {
  "D_name",
  "D_pointer",
  "D_reference",
  "D_func",
  "D_array",
  "D_bitfield",
  "D_ptrToMember",
  "D_grouping",
};

void IDeclarator::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_GENERIC(loc);
}

void IDeclarator::gdb() const
  { debugPrint(std::cout, 0); }

DEFN_AST_DOWNCASTS(IDeclarator, D_name, D_NAME)

D_name::~D_name()
{
  delete name;
}

void D_name::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, D_name);

  IDeclarator::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(name);
}

D_name *D_name::clone() const
{
  D_name *ret = new D_name(
    loc,
    name? name->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(IDeclarator, D_pointer, D_POINTER)

D_pointer::~D_pointer()
{
  delete base;
}

void D_pointer::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, D_pointer);

  IDeclarator::debugPrint(os, indent, subtreeName);

  PRINT_GENERIC(cv);
  PRINT_SUBTREE(base);
}

D_pointer *D_pointer::clone() const
{
  D_pointer *ret = new D_pointer(
    loc,
    cv,
    base? base->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(IDeclarator, D_reference, D_REFERENCE)

D_reference::~D_reference()
{
  delete base;
}

void D_reference::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, D_reference);

  IDeclarator::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(base);
}

D_reference *D_reference::clone() const
{
  D_reference *ret = new D_reference(
    loc,
    base? base->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(IDeclarator, D_func, D_FUNC)

D_func::~D_func()
{
  delete base;
  delete exnSpec;
}

void D_func::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, D_func);

  IDeclarator::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(base);
  PRINT_FAKE_LIST(ASTTypeId, params);
  PRINT_GENERIC(cv);
  PRINT_SUBTREE(exnSpec);
  PRINT_FAKE_LIST(PQ_name, kAndR_params);
}

D_func *D_func::clone() const
{
  D_func *ret = new D_func(
    loc,
    base? base->clone() : NULL,
    cloneFakeList(params),
    cv,
    exnSpec? exnSpec->clone() : NULL,
    cloneFakeList(kAndR_params)
  );
  return ret;
}

DEFN_AST_DOWNCASTS(IDeclarator, D_array, D_ARRAY)

D_array::~D_array()
{
  delete base;
  delete size;
}

void D_array::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, D_array);

  IDeclarator::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(base);
  PRINT_SUBTREE(size);
}

D_array *D_array::clone() const
{
  D_array *ret = new D_array(
    loc,
    base? base->clone() : NULL,
    size? size->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(IDeclarator, D_bitfield, D_BITFIELD)

D_bitfield::~D_bitfield()
{
  delete name;
  delete bits;
}

void D_bitfield::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, D_bitfield);

  IDeclarator::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(name);
  PRINT_SUBTREE(bits);
}

D_bitfield *D_bitfield::clone() const
{
  D_bitfield *ret = new D_bitfield(
    loc,
    name? name->clone() : NULL,
    bits? bits->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(IDeclarator, D_ptrToMember, D_PTRTOMEMBER)

D_ptrToMember::~D_ptrToMember()
{
  delete nestedName;
  delete base;
}

void D_ptrToMember::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, D_ptrToMember);

  IDeclarator::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(nestedName);
  PRINT_GENERIC(cv);
  PRINT_SUBTREE(base);
}

D_ptrToMember *D_ptrToMember::clone() const
{
  D_ptrToMember *ret = new D_ptrToMember(
    loc,
    nestedName? nestedName->clone() : NULL,
    cv,
    base? base->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(IDeclarator, D_grouping, D_GROUPING)

D_grouping::~D_grouping()
{
  delete base;
}

void D_grouping::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, D_grouping);

  IDeclarator::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(base);
}

D_grouping *D_grouping::clone() const
{
  D_grouping *ret = new D_grouping(
    loc,
    base? base->clone() : NULL
  );
  return ret;
}


// ------------------ ExceptionSpec -------------------
// *** DO NOT EDIT ***
ExceptionSpec::~ExceptionSpec()
{
}

void ExceptionSpec::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, ExceptionSpec);

  PRINT_FAKE_LIST(ASTTypeId, types);
}

void ExceptionSpec::gdb() const
  { debugPrint(std::cout, 0); }

ExceptionSpec *ExceptionSpec::clone() const
{
  ExceptionSpec *ret = new ExceptionSpec(
    cloneFakeList(types)
  );
  return ret;
}


// ------------------ OperatorName -------------------
// *** DO NOT EDIT ***
OperatorName::~OperatorName()
{
}

char const * const OperatorName::kindNames[OperatorName::NUM_KINDS] = {
  "ON_newDel",
  "ON_operator",
  "ON_conversion",
};

void OperatorName::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
}

void OperatorName::gdb() const
  { debugPrint(std::cout, 0); }

DEFN_AST_DOWNCASTS(OperatorName, ON_newDel, ON_NEWDEL)

ON_newDel::~ON_newDel()
{
}

void ON_newDel::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, ON_newDel);

  OperatorName::debugPrint(os, indent, subtreeName);

  PRINT_BOOL(isNew);
  PRINT_BOOL(isArray);
}

ON_newDel *ON_newDel::clone() const
{
  ON_newDel *ret = new ON_newDel(
    isNew,
    isArray
  );
  return ret;
}

DEFN_AST_DOWNCASTS(OperatorName, ON_operator, ON_OPERATOR)

ON_operator::~ON_operator()
{
}

void ON_operator::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, ON_operator);

  OperatorName::debugPrint(os, indent, subtreeName);

  PRINT_GENERIC(op);
}

ON_operator *ON_operator::clone() const
{
  ON_operator *ret = new ON_operator(
    op
  );
  return ret;
}

DEFN_AST_DOWNCASTS(OperatorName, ON_conversion, ON_CONVERSION)

ON_conversion::~ON_conversion()
{
  delete type;
}

void ON_conversion::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, ON_conversion);

  OperatorName::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(type);
}

ON_conversion *ON_conversion::clone() const
{
  ON_conversion *ret = new ON_conversion(
    type? type->clone() : NULL
  );
  return ret;
}


// ------------------ Statement -------------------
// *** DO NOT EDIT ***
Statement::~Statement()
{
}

char const * const Statement::kindNames[Statement::NUM_KINDS] = {
  "S_skip",
  "S_label",
  "S_case",
  "S_default",
  "S_expr",
  "S_compound",
  "S_if",
  "S_switch",
  "S_while",
  "S_doWhile",
  "S_for",
  "S_break",
  "S_continue",
  "S_return",
  "S_goto",
  "S_decl",
  "S_try",
  "S_asm",
  "S_namespaceDecl",
  "S_function",
  "S_rangeCase",
  "S_computedGoto",
};

void Statement::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    ind(os, indent) << "succ=" << successorsToString() << std::endl;
  ;
  PRINT_GENERIC(loc);
  PRINT_GENERIC(endloc);
}

void Statement::gdb() const
  { debugPrint(std::cout, 0); }

DEFN_AST_DOWNCASTS(Statement, S_skip, S_SKIP)

S_skip::~S_skip()
{
}

void S_skip::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, S_skip);

  Statement::debugPrint(os, indent, subtreeName);

}

S_skip *S_skip::clone() const
{
  S_skip *ret = new S_skip(
    loc,
    endloc
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Statement, S_label, S_LABEL)

S_label::~S_label()
{
  delete s;
}

void S_label::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, S_label);

  Statement::debugPrint(os, indent, subtreeName);

  PRINT_CSTRING(name);
  PRINT_SUBTREE(s);
}

S_label *S_label::clone() const
{
  S_label *ret = new S_label(
    loc,
    endloc,
    name,
    s? s->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Statement, S_case, S_CASE)

S_case::~S_case()
{
  delete expr;
  delete s;
}

void S_case::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, S_case);

  Statement::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(expr);
  PRINT_SUBTREE(s);
}

S_case *S_case::clone() const
{
  S_case *ret = new S_case(
    loc,
    endloc,
    expr? expr->clone() : NULL,
    s? s->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Statement, S_default, S_DEFAULT)

S_default::~S_default()
{
  delete s;
}

void S_default::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, S_default);

  Statement::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(s);
}

S_default *S_default::clone() const
{
  S_default *ret = new S_default(
    loc,
    endloc,
    s? s->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Statement, S_expr, S_EXPR)

S_expr::~S_expr()
{
  delete expr;
}

void S_expr::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, S_expr);

  Statement::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(expr);
}

S_expr *S_expr::clone() const
{
  S_expr *ret = new S_expr(
    loc,
    endloc,
    expr? expr->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Statement, S_compound, S_COMPOUND)

S_compound::~S_compound()
{
  stmts.deleteAll();
}

void S_compound::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, S_compound);

  Statement::debugPrint(os, indent, subtreeName);

  PRINT_LIST(Statement, stmts);
}

S_compound *S_compound::clone() const
{
  S_compound *ret = new S_compound(
    loc,
    endloc,
    cloneASTList(stmts)
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Statement, S_if, S_IF)

S_if::~S_if()
{
  delete cond;
  delete thenBranch;
  delete elseBranch;
}

void S_if::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, S_if);

  Statement::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(cond);
  PRINT_SUBTREE(thenBranch);
  PRINT_SUBTREE(elseBranch);
}

S_if *S_if::clone() const
{
  S_if *ret = new S_if(
    loc,
    endloc,
    cond? cond->clone() : NULL,
    thenBranch? thenBranch->clone() : NULL,
    elseBranch? elseBranch->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Statement, S_switch, S_SWITCH)

S_switch::~S_switch()
{
  delete cond;
  delete branches;
}

void S_switch::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, S_switch);

  Statement::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(cond);
  PRINT_SUBTREE(branches);
}

S_switch *S_switch::clone() const
{
  S_switch *ret = new S_switch(
    loc,
    endloc,
    cond? cond->clone() : NULL,
    branches? branches->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Statement, S_while, S_WHILE)

S_while::~S_while()
{
  delete cond;
  delete body;
}

void S_while::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, S_while);

  Statement::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(cond);
  PRINT_SUBTREE(body);
}

S_while *S_while::clone() const
{
  S_while *ret = new S_while(
    loc,
    endloc,
    cond? cond->clone() : NULL,
    body? body->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Statement, S_doWhile, S_DOWHILE)

S_doWhile::~S_doWhile()
{
  delete body;
  delete expr;
}

void S_doWhile::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, S_doWhile);

  Statement::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(body);
  PRINT_SUBTREE(expr);
}

S_doWhile *S_doWhile::clone() const
{
  S_doWhile *ret = new S_doWhile(
    loc,
    endloc,
    body? body->clone() : NULL,
    expr? expr->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Statement, S_for, S_FOR)

S_for::~S_for()
{
  delete init;
  delete cond;
  delete after;
  delete body;
}

void S_for::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, S_for);

  Statement::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(init);
  PRINT_SUBTREE(cond);
  PRINT_SUBTREE(after);
  PRINT_SUBTREE(body);
}

S_for *S_for::clone() const
{
  S_for *ret = new S_for(
    loc,
    endloc,
    init? init->clone() : NULL,
    cond? cond->clone() : NULL,
    after? after->clone() : NULL,
    body? body->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Statement, S_break, S_BREAK)

S_break::~S_break()
{
}

void S_break::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, S_break);

  Statement::debugPrint(os, indent, subtreeName);

}

S_break *S_break::clone() const
{
  S_break *ret = new S_break(
    loc,
    endloc
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Statement, S_continue, S_CONTINUE)

S_continue::~S_continue()
{
}

void S_continue::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, S_continue);

  Statement::debugPrint(os, indent, subtreeName);

}

S_continue *S_continue::clone() const
{
  S_continue *ret = new S_continue(
    loc,
    endloc
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Statement, S_return, S_RETURN)

S_return::~S_return()
{
  delete expr;
  delete ctorStatement;
}

void S_return::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, S_return);

  Statement::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(expr);
  PRINT_SUBTREE(ctorStatement);
}

S_return *S_return::clone() const
{
  S_return *ret = new S_return(
    loc,
    endloc,
    expr? expr->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Statement, S_goto, S_GOTO)

S_goto::~S_goto()
{
}

void S_goto::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, S_goto);

  Statement::debugPrint(os, indent, subtreeName);

  PRINT_CSTRING(target);
}

S_goto *S_goto::clone() const
{
  S_goto *ret = new S_goto(
    loc,
    endloc,
    target
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Statement, S_decl, S_DECL)

S_decl::~S_decl()
{
  delete decl;
}

void S_decl::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, S_decl);

  Statement::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(decl);
}

S_decl *S_decl::clone() const
{
  S_decl *ret = new S_decl(
    loc,
    endloc,
    decl? decl->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Statement, S_try, S_TRY)

S_try::~S_try()
{
  delete body;
}

void S_try::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, S_try);

  Statement::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(body);
  PRINT_FAKE_LIST(Handler, handlers);
}

S_try *S_try::clone() const
{
  S_try *ret = new S_try(
    loc,
    endloc,
    body? body->clone() : NULL,
    cloneFakeList(handlers)
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Statement, S_asm, S_ASM)

S_asm::~S_asm()
{
  delete text;
}

void S_asm::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, S_asm);

  Statement::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(text);
}

S_asm *S_asm::clone() const
{
  S_asm *ret = new S_asm(
    loc,
    endloc,
    text? text->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Statement, S_namespaceDecl, S_NAMESPACEDECL)

S_namespaceDecl::~S_namespaceDecl()
{
  delete decl;
}

void S_namespaceDecl::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, S_namespaceDecl);

  Statement::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(decl);
}

S_namespaceDecl *S_namespaceDecl::clone() const
{
  S_namespaceDecl *ret = new S_namespaceDecl(
    loc,
    endloc,
    decl? decl->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Statement, S_function, S_FUNCTION)

S_function::~S_function()
{
  delete f;
}

void S_function::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, S_function);

  Statement::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(f);
}

S_function *S_function::clone() const
{
  S_function *ret = new S_function(
    loc,
    endloc,
    f? f->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Statement, S_rangeCase, S_RANGECASE)

S_rangeCase::~S_rangeCase()
{
  delete exprLo;
  delete exprHi;
  delete s;
}

void S_rangeCase::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, S_rangeCase);

  Statement::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(exprLo);
  PRINT_SUBTREE(exprHi);
  PRINT_SUBTREE(s);
}

S_rangeCase *S_rangeCase::clone() const
{
  S_rangeCase *ret = new S_rangeCase(
    loc,
    endloc,
    exprLo? exprLo->clone() : NULL,
    exprHi? exprHi->clone() : NULL,
    s? s->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Statement, S_computedGoto, S_COMPUTEDGOTO)

S_computedGoto::~S_computedGoto()
{
  delete target;
}

void S_computedGoto::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, S_computedGoto);

  Statement::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(target);
}

S_computedGoto *S_computedGoto::clone() const
{
  S_computedGoto *ret = new S_computedGoto(
    loc,
    endloc,
    target? target->clone() : NULL
  );
  return ret;
}


// ------------------ Condition -------------------
// *** DO NOT EDIT ***
Condition::~Condition()
{
}

char const * const Condition::kindNames[Condition::NUM_KINDS] = {
  "CN_expr",
  "CN_decl",
};

void Condition::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
}

void Condition::gdb() const
  { debugPrint(std::cout, 0); }

DEFN_AST_DOWNCASTS(Condition, CN_expr, CN_EXPR)

CN_expr::~CN_expr()
{
  delete expr;
}

void CN_expr::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, CN_expr);

  Condition::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(expr);
}

CN_expr *CN_expr::clone() const
{
  CN_expr *ret = new CN_expr(
    expr? expr->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Condition, CN_decl, CN_DECL)

CN_decl::~CN_decl()
{
  delete typeId;
}

void CN_decl::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, CN_decl);

  Condition::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(typeId);
}

CN_decl *CN_decl::clone() const
{
  CN_decl *ret = new CN_decl(
    typeId? typeId->clone() : NULL
  );
  return ret;
}


// ------------------ Handler -------------------
// *** DO NOT EDIT ***
Handler::~Handler()
{
  delete typeId;
  delete body;
  delete annot;
  delete localArg;
  delete globalDtorStatement;
}

void Handler::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, Handler);

   ind(os,indent) << "globalVar: " << refersTo(globalVar) << "\n"; ;
  PRINT_SUBTREE(typeId);
  PRINT_SUBTREE(body);
  PRINT_SUBTREE(localArg);
  PRINT_SUBTREE(globalDtorStatement);
}

void Handler::gdb() const
  { debugPrint(std::cout, 0); }

Handler *Handler::clone() const
{
  Handler *ret = new Handler(
    typeId? typeId->clone() : NULL,
    body? body->clone() : NULL
  );
  return ret;
}


// ------------------ Expression -------------------
// *** DO NOT EDIT ***
Expression::~Expression()
{
}

char const * const Expression::kindNames[Expression::NUM_KINDS] = {
  "E_boolLit",
  "E_intLit",
  "E_floatLit",
  "E_stringLit",
  "E_charLit",
  "E_this",
  "E_variable",
  "E_funCall",
  "E_constructor",
  "E_fieldAcc",
  "E_sizeof",
  "E_unary",
  "E_effect",
  "E_binary",
  "E_addrOf",
  "E_deref",
  "E_cast",
  "E_cond",
  "E_sizeofType",
  "E_assign",
  "E_new",
  "E_delete",
  "E_throw",
  "E_keywordCast",
  "E_typeidExpr",
  "E_typeidType",
  "E_grouping",
  "E_arrow",
  "E_statement",
  "E_compoundLit",
  "E___builtin_constant_p",
  "E___builtin_va_arg",
  "E_alignofType",
  "E_alignofExpr",
  "E_gnuCond",
  "E_addrOfLabel",
};

void Expression::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
   printExtras(os, indent); ;
  PRINT_GENERIC(loc);
  PRINT_GENERIC(endloc);
}

void Expression::gdb() const
  { debugPrint(std::cout, 0); }

DEFN_AST_DOWNCASTS(Expression, E_boolLit, E_BOOLLIT)

E_boolLit::~E_boolLit()
{
}

void E_boolLit::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, E_boolLit);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_BOOL(b);
}

E_boolLit *E_boolLit::clone() const
{
  E_boolLit *ret = new E_boolLit(
    loc,
    endloc,
    b
  );
  
    // don't clone something that is still ambiguous (usually means
    // hasn't been tchecked)
    xassert(!ambiguity);
  ;
  
    ret->type = type;
  ;
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_intLit, E_INTLIT)

E_intLit::~E_intLit()
{
}

void E_intLit::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, E_intLit);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_CSTRING(text);
}

E_intLit *E_intLit::clone() const
{
  E_intLit *ret = new E_intLit(
    loc,
    endloc,
    text
  );
  
    // don't clone something that is still ambiguous (usually means
    // hasn't been tchecked)
    xassert(!ambiguity);
  ;
  
    ret->type = type;
  ;
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_floatLit, E_FLOATLIT)

E_floatLit::~E_floatLit()
{
}

void E_floatLit::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, E_floatLit);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_CSTRING(text);
}

E_floatLit *E_floatLit::clone() const
{
  E_floatLit *ret = new E_floatLit(
    loc,
    endloc,
    text
  );
  
    // don't clone something that is still ambiguous (usually means
    // hasn't been tchecked)
    xassert(!ambiguity);
  ;
  
    ret->type = type;
  ;
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_stringLit, E_STRINGLIT)

E_stringLit::~E_stringLit()
{
  delete continuation;
}

void E_stringLit::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, E_stringLit);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_CSTRING(text);
  PRINT_SUBTREE(continuation);
  PRINT_CSTRING(fullTextNQ);
}

E_stringLit *E_stringLit::clone() const
{
  E_stringLit *ret = new E_stringLit(
    loc,
    endloc,
    text,
    continuation? continuation->clone() : NULL,
    fullTextNQ
  );
  
    // don't clone something that is still ambiguous (usually means
    // hasn't been tchecked)
    xassert(!ambiguity);
  ;
  
    ret->type = type;
  ;
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_charLit, E_CHARLIT)

E_charLit::~E_charLit()
{
}

void E_charLit::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, E_charLit);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_CSTRING(text);
}

E_charLit *E_charLit::clone() const
{
  E_charLit *ret = new E_charLit(
    loc,
    endloc,
    text
  );
  
    // don't clone something that is still ambiguous (usually means
    // hasn't been tchecked)
    xassert(!ambiguity);
  ;
  
    ret->type = type;
  ;
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_this, E_THIS)

E_this::~E_this()
{
}

void E_this::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, E_this);

  Expression::debugPrint(os, indent, subtreeName);

}

E_this *E_this::clone() const
{
  E_this *ret = new E_this(
    loc,
    endloc
  );
  
    // don't clone something that is still ambiguous (usually means
    // hasn't been tchecked)
    xassert(!ambiguity);
  ;
  
    ret->type = type;
  ;
   ret->receiver = receiver; ;
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_variable, E_VARIABLE)

E_variable::~E_variable()
{
  delete name;
}

void E_variable::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, E_variable);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(name);
}

E_variable *E_variable::clone() const
{
  E_variable *ret = new E_variable(
    loc,
    endloc,
    name? name->clone() : NULL
  );
  
    // don't clone something that is still ambiguous (usually means
    // hasn't been tchecked)
    xassert(!ambiguity);
  ;
  
    ret->type = type;
  ;
   ret->var = var; ;
   ret->nondependentVar = nondependentVar; ;
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_funCall, E_FUNCALL)

E_funCall::~E_funCall()
{
  delete func;
  delete retObj;
}

void E_funCall::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, E_funCall);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(func);
  PRINT_FAKE_LIST(ArgExpression, args);
  PRINT_SUBTREE(retObj);
}

E_funCall *E_funCall::clone() const
{
  E_funCall *ret = new E_funCall(
    loc,
    endloc,
    func? func->clone() : NULL,
    cloneFakeList(args)
  );
  
    // don't clone something that is still ambiguous (usually means
    // hasn't been tchecked)
    xassert(!ambiguity);
  ;
  
    ret->type = type;
  ;
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_constructor, E_CONSTRUCTOR)

E_constructor::~E_constructor()
{
  delete spec;
  delete retObj;
}

void E_constructor::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, E_constructor);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(spec);
  PRINT_FAKE_LIST(ArgExpression, args);
  PRINT_BOOL(artificial);
  PRINT_SUBTREE(retObj);
}

E_constructor *E_constructor::clone() const
{
  E_constructor *ret = new E_constructor(
    loc,
    endloc,
    spec? spec->clone() : NULL,
    cloneFakeList(args)
  );
  
    // don't clone something that is still ambiguous (usually means
    // hasn't been tchecked)
    xassert(!ambiguity);
  ;
  
    ret->type = type;
  ;
   ret->ctorVar = ctorVar; ;
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_fieldAcc, E_FIELDACC)

E_fieldAcc::~E_fieldAcc()
{
  delete obj;
  delete fieldName;
}

void E_fieldAcc::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, E_fieldAcc);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(obj);
  PRINT_SUBTREE(fieldName);
}

E_fieldAcc *E_fieldAcc::clone() const
{
  E_fieldAcc *ret = new E_fieldAcc(
    loc,
    endloc,
    obj? obj->clone() : NULL,
    fieldName? fieldName->clone() : NULL
  );
  
    // don't clone something that is still ambiguous (usually means
    // hasn't been tchecked)
    xassert(!ambiguity);
  ;
  
    ret->type = type;
  ;
   ret->field = field; ;
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_sizeof, E_SIZEOF)

E_sizeof::~E_sizeof()
{
  delete expr;
}

void E_sizeof::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, E_sizeof);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(expr);
}

E_sizeof *E_sizeof::clone() const
{
  E_sizeof *ret = new E_sizeof(
    loc,
    endloc,
    expr? expr->clone() : NULL
  );
  
    // don't clone something that is still ambiguous (usually means
    // hasn't been tchecked)
    xassert(!ambiguity);
  ;
  
    ret->type = type;
  ;
   ret->size = size; ;
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_unary, E_UNARY)

E_unary::~E_unary()
{
  delete expr;
}

void E_unary::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, E_unary);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_GENERIC(op);
  PRINT_SUBTREE(expr);
}

E_unary *E_unary::clone() const
{
  E_unary *ret = new E_unary(
    loc,
    endloc,
    op,
    expr? expr->clone() : NULL
  );
  
    // don't clone something that is still ambiguous (usually means
    // hasn't been tchecked)
    xassert(!ambiguity);
  ;
  
    ret->type = type;
  ;
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_effect, E_EFFECT)

E_effect::~E_effect()
{
  delete expr;
}

void E_effect::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, E_effect);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_GENERIC(op);
  PRINT_SUBTREE(expr);
}

E_effect *E_effect::clone() const
{
  E_effect *ret = new E_effect(
    loc,
    endloc,
    op,
    expr? expr->clone() : NULL
  );
  
    // don't clone something that is still ambiguous (usually means
    // hasn't been tchecked)
    xassert(!ambiguity);
  ;
  
    ret->type = type;
  ;
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_binary, E_BINARY)

E_binary::~E_binary()
{
  delete e1;
  delete e2;
}

void E_binary::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, E_binary);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(e1);
  PRINT_GENERIC(op);
  PRINT_SUBTREE(e2);
}

E_binary *E_binary::clone() const
{
  E_binary *ret = new E_binary(
    loc,
    endloc,
    e1? e1->clone() : NULL,
    op,
    e2? e2->clone() : NULL
  );
  
    // don't clone something that is still ambiguous (usually means
    // hasn't been tchecked)
    xassert(!ambiguity);
  ;
  
    ret->type = type;
  ;
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_addrOf, E_ADDROF)

E_addrOf::~E_addrOf()
{
  delete expr;
}

void E_addrOf::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, E_addrOf);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(expr);
}

E_addrOf *E_addrOf::clone() const
{
  E_addrOf *ret = new E_addrOf(
    loc,
    endloc,
    expr? expr->clone() : NULL
  );
  
    // don't clone something that is still ambiguous (usually means
    // hasn't been tchecked)
    xassert(!ambiguity);
  ;
  
    ret->type = type;
  ;
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_deref, E_DEREF)

E_deref::~E_deref()
{
  delete ptr;
}

void E_deref::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, E_deref);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(ptr);
}

E_deref *E_deref::clone() const
{
  E_deref *ret = new E_deref(
    loc,
    endloc,
    ptr? ptr->clone() : NULL
  );
  
    // don't clone something that is still ambiguous (usually means
    // hasn't been tchecked)
    xassert(!ambiguity);
  ;
  
    ret->type = type;
  ;
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_cast, E_CAST)

E_cast::~E_cast()
{
  delete ctype;
  delete expr;
}

void E_cast::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, E_cast);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(ctype);
  PRINT_SUBTREE(expr);
}

E_cast *E_cast::clone() const
{
  E_cast *ret = new E_cast(
    loc,
    endloc,
    ctype? ctype->clone() : NULL,
    expr? expr->clone() : NULL
  );
  
    // don't clone something that is still ambiguous (usually means
    // hasn't been tchecked)
    xassert(!ambiguity);
  ;
  
    ret->type = type;
  ;
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_cond, E_COND)

E_cond::~E_cond()
{
  delete cond;
  delete th;
  delete el;
}

void E_cond::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, E_cond);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(cond);
  PRINT_SUBTREE(th);
  PRINT_SUBTREE(el);
}

E_cond *E_cond::clone() const
{
  E_cond *ret = new E_cond(
    loc,
    endloc,
    cond? cond->clone() : NULL,
    th? th->clone() : NULL,
    el? el->clone() : NULL
  );
  
    // don't clone something that is still ambiguous (usually means
    // hasn't been tchecked)
    xassert(!ambiguity);
  ;
  
    ret->type = type;
  ;
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_sizeofType, E_SIZEOFTYPE)

E_sizeofType::~E_sizeofType()
{
  delete atype;
}

void E_sizeofType::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, E_sizeofType);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(atype);
}

E_sizeofType *E_sizeofType::clone() const
{
  E_sizeofType *ret = new E_sizeofType(
    loc,
    endloc,
    atype? atype->clone() : NULL
  );
  
    // don't clone something that is still ambiguous (usually means
    // hasn't been tchecked)
    xassert(!ambiguity);
  ;
  
    ret->type = type;
  ;
   ret->size = size; ;
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_assign, E_ASSIGN)

E_assign::~E_assign()
{
  delete target;
  delete src;
}

void E_assign::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, E_assign);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(target);
  PRINT_GENERIC(op);
  PRINT_SUBTREE(src);
}

E_assign *E_assign::clone() const
{
  E_assign *ret = new E_assign(
    loc,
    endloc,
    target? target->clone() : NULL,
    op,
    src? src->clone() : NULL
  );
  
    // don't clone something that is still ambiguous (usually means
    // hasn't been tchecked)
    xassert(!ambiguity);
  ;
  
    ret->type = type;
  ;
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_new, E_NEW)

E_new::~E_new()
{
  delete atype;
  delete ctorArgs;
  delete ctorStatement;
}

void E_new::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, E_new);

  Expression::debugPrint(os, indent, subtreeName);

   ind(os,indent) << "ctorVar: " << refersTo(ctorVar) << "\n"; ;
   ind(os,indent) << "heapVar: " << refersTo(heapVar) << "\n"; ;
  PRINT_BOOL(colonColon);
  PRINT_FAKE_LIST(ArgExpression, placementArgs);
  PRINT_SUBTREE(atype);
  PRINT_SUBTREE(ctorArgs);
  PRINT_SUBTREE(ctorStatement);
}

E_new *E_new::clone() const
{
  E_new *ret = new E_new(
    loc,
    endloc,
    colonColon,
    cloneFakeList(placementArgs),
    atype? atype->clone() : NULL,
    ctorArgs? ctorArgs->clone() : NULL
  );
  
    // don't clone something that is still ambiguous (usually means
    // hasn't been tchecked)
    xassert(!ambiguity);
  ;
  
    ret->type = type;
  ;
   ret->ctorVar = ctorVar; ;
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_delete, E_DELETE)

E_delete::~E_delete()
{
  delete expr;
  delete dtorStatement;
}

void E_delete::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, E_delete);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_BOOL(colonColon);
  PRINT_BOOL(array);
  PRINT_SUBTREE(expr);
  PRINT_SUBTREE(dtorStatement);
}

E_delete *E_delete::clone() const
{
  E_delete *ret = new E_delete(
    loc,
    endloc,
    colonColon,
    array,
    expr? expr->clone() : NULL
  );
  
    // don't clone something that is still ambiguous (usually means
    // hasn't been tchecked)
    xassert(!ambiguity);
  ;
  
    ret->type = type;
  ;
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_throw, E_THROW)

E_throw::~E_throw()
{
  delete expr;
  delete globalCtorStatement;
}

void E_throw::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, E_throw);

  Expression::debugPrint(os, indent, subtreeName);

   ind(os,indent) << "globalVar: " << refersTo(globalVar) << "\n"; ;
  PRINT_SUBTREE(expr);
  PRINT_SUBTREE(globalCtorStatement);
}

E_throw *E_throw::clone() const
{
  E_throw *ret = new E_throw(
    loc,
    endloc,
    expr? expr->clone() : NULL
  );
  
    // don't clone something that is still ambiguous (usually means
    // hasn't been tchecked)
    xassert(!ambiguity);
  ;
  
    ret->type = type;
  ;
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_keywordCast, E_KEYWORDCAST)

E_keywordCast::~E_keywordCast()
{
  delete ctype;
  delete expr;
}

void E_keywordCast::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, E_keywordCast);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_GENERIC(key);
  PRINT_SUBTREE(ctype);
  PRINT_SUBTREE(expr);
}

E_keywordCast *E_keywordCast::clone() const
{
  E_keywordCast *ret = new E_keywordCast(
    loc,
    endloc,
    key,
    ctype? ctype->clone() : NULL,
    expr? expr->clone() : NULL
  );
  
    // don't clone something that is still ambiguous (usually means
    // hasn't been tchecked)
    xassert(!ambiguity);
  ;
  
    ret->type = type;
  ;
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_typeidExpr, E_TYPEIDEXPR)

E_typeidExpr::~E_typeidExpr()
{
  delete expr;
}

void E_typeidExpr::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, E_typeidExpr);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(expr);
}

E_typeidExpr *E_typeidExpr::clone() const
{
  E_typeidExpr *ret = new E_typeidExpr(
    loc,
    endloc,
    expr? expr->clone() : NULL
  );
  
    // don't clone something that is still ambiguous (usually means
    // hasn't been tchecked)
    xassert(!ambiguity);
  ;
  
    ret->type = type;
  ;
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_typeidType, E_TYPEIDTYPE)

E_typeidType::~E_typeidType()
{
  delete ttype;
}

void E_typeidType::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, E_typeidType);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(ttype);
}

E_typeidType *E_typeidType::clone() const
{
  E_typeidType *ret = new E_typeidType(
    loc,
    endloc,
    ttype? ttype->clone() : NULL
  );
  
    // don't clone something that is still ambiguous (usually means
    // hasn't been tchecked)
    xassert(!ambiguity);
  ;
  
    ret->type = type;
  ;
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_grouping, E_GROUPING)

E_grouping::~E_grouping()
{
  delete expr;
}

void E_grouping::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, E_grouping);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(expr);
}

E_grouping *E_grouping::clone() const
{
  E_grouping *ret = new E_grouping(
    loc,
    endloc,
    expr? expr->clone() : NULL
  );
  
    // don't clone something that is still ambiguous (usually means
    // hasn't been tchecked)
    xassert(!ambiguity);
  ;
  
    ret->type = type;
  ;
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_arrow, E_ARROW)

E_arrow::~E_arrow()
{
  delete obj;
  delete fieldName;
}

void E_arrow::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, E_arrow);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(obj);
  PRINT_SUBTREE(fieldName);
}

E_arrow *E_arrow::clone() const
{
  E_arrow *ret = new E_arrow(
    loc,
    endloc,
    obj? obj->clone() : NULL,
    fieldName? fieldName->clone() : NULL
  );
  
    // don't clone something that is still ambiguous (usually means
    // hasn't been tchecked)
    xassert(!ambiguity);
  ;
  
    ret->type = type;
  ;
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_statement, E_STATEMENT)

E_statement::~E_statement()
{
  delete s;
}

void E_statement::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, E_statement);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(s);
}

E_statement *E_statement::clone() const
{
  E_statement *ret = new E_statement(
    loc,
    endloc,
    s? s->clone() : NULL
  );
  
    // don't clone something that is still ambiguous (usually means
    // hasn't been tchecked)
    xassert(!ambiguity);
  ;
  
    ret->type = type;
  ;
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_compoundLit, E_COMPOUNDLIT)

E_compoundLit::~E_compoundLit()
{
  delete stype;
  delete init;
}

void E_compoundLit::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, E_compoundLit);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(stype);
  PRINT_SUBTREE(init);
}

E_compoundLit *E_compoundLit::clone() const
{
  E_compoundLit *ret = new E_compoundLit(
    loc,
    endloc,
    stype? stype->clone() : NULL,
    init? init->clone() : NULL
  );
  
    // don't clone something that is still ambiguous (usually means
    // hasn't been tchecked)
    xassert(!ambiguity);
  ;
  
    ret->type = type;
  ;
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E___builtin_constant_p, E___BUILTIN_CONSTANT_P)

E___builtin_constant_p::~E___builtin_constant_p()
{
  delete expr;
}

void E___builtin_constant_p::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, E___builtin_constant_p);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(expr);
}

E___builtin_constant_p *E___builtin_constant_p::clone() const
{
  E___builtin_constant_p *ret = new E___builtin_constant_p(
    loc,
    endloc,
    expr? expr->clone() : NULL
  );
  
    // don't clone something that is still ambiguous (usually means
    // hasn't been tchecked)
    xassert(!ambiguity);
  ;
  
    ret->type = type;
  ;
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E___builtin_va_arg, E___BUILTIN_VA_ARG)

E___builtin_va_arg::~E___builtin_va_arg()
{
  delete expr;
  delete atype;
}

void E___builtin_va_arg::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, E___builtin_va_arg);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(expr);
  PRINT_SUBTREE(atype);
}

E___builtin_va_arg *E___builtin_va_arg::clone() const
{
  E___builtin_va_arg *ret = new E___builtin_va_arg(
    loc,
    endloc,
    expr? expr->clone() : NULL,
    atype? atype->clone() : NULL
  );
  
    // don't clone something that is still ambiguous (usually means
    // hasn't been tchecked)
    xassert(!ambiguity);
  ;
  
    ret->type = type;
  ;
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_alignofType, E_ALIGNOFTYPE)

E_alignofType::~E_alignofType()
{
  delete atype;
}

void E_alignofType::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, E_alignofType);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(atype);
}

E_alignofType *E_alignofType::clone() const
{
  E_alignofType *ret = new E_alignofType(
    loc,
    endloc,
    atype? atype->clone() : NULL
  );
  
    // don't clone something that is still ambiguous (usually means
    // hasn't been tchecked)
    xassert(!ambiguity);
  ;
  
    ret->type = type;
  ;
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_alignofExpr, E_ALIGNOFEXPR)

E_alignofExpr::~E_alignofExpr()
{
  delete expr;
}

void E_alignofExpr::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, E_alignofExpr);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(expr);
}

E_alignofExpr *E_alignofExpr::clone() const
{
  E_alignofExpr *ret = new E_alignofExpr(
    loc,
    endloc,
    expr? expr->clone() : NULL
  );
  
    // don't clone something that is still ambiguous (usually means
    // hasn't been tchecked)
    xassert(!ambiguity);
  ;
  
    ret->type = type;
  ;
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_gnuCond, E_GNUCOND)

E_gnuCond::~E_gnuCond()
{
  delete cond;
  delete el;
}

void E_gnuCond::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, E_gnuCond);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(cond);
  PRINT_SUBTREE(el);
}

E_gnuCond *E_gnuCond::clone() const
{
  E_gnuCond *ret = new E_gnuCond(
    loc,
    endloc,
    cond? cond->clone() : NULL,
    el? el->clone() : NULL
  );
  
    // don't clone something that is still ambiguous (usually means
    // hasn't been tchecked)
    xassert(!ambiguity);
  ;
  
    ret->type = type;
  ;
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_addrOfLabel, E_ADDROFLABEL)

E_addrOfLabel::~E_addrOfLabel()
{
}

void E_addrOfLabel::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, E_addrOfLabel);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_CSTRING(labelName);
}

E_addrOfLabel *E_addrOfLabel::clone() const
{
  E_addrOfLabel *ret = new E_addrOfLabel(
    loc,
    endloc,
    labelName
  );
  
    // don't clone something that is still ambiguous (usually means
    // hasn't been tchecked)
    xassert(!ambiguity);
  ;
  
    ret->type = type;
  ;
  return ret;
}


// ------------------ FullExpression -------------------
// *** DO NOT EDIT ***
FullExpression::~FullExpression()
{
  delete expr;
  delete annot;
}

void FullExpression::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, FullExpression);

  PRINT_SUBTREE(expr);
}

void FullExpression::gdb() const
  { debugPrint(std::cout, 0); }

FullExpression *FullExpression::clone() const
{
  FullExpression *ret = new FullExpression(
    expr? expr->clone() : NULL
  );
  return ret;
}


// ------------------ ArgExpression -------------------
// *** DO NOT EDIT ***
ArgExpression::~ArgExpression()
{
  delete expr;
}

void ArgExpression::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, ArgExpression);

  PRINT_SUBTREE(expr);
}

void ArgExpression::gdb() const
  { debugPrint(std::cout, 0); }

ArgExpression *ArgExpression::clone() const
{
  ArgExpression *ret = new ArgExpression(
    expr? expr->clone() : NULL
  );
  return ret;
}


// ------------------ ArgExpressionListOpt -------------------
// *** DO NOT EDIT ***
ArgExpressionListOpt::~ArgExpressionListOpt()
{
}

void ArgExpressionListOpt::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, ArgExpressionListOpt);

  PRINT_FAKE_LIST(ArgExpression, list);
}

void ArgExpressionListOpt::gdb() const
  { debugPrint(std::cout, 0); }

ArgExpressionListOpt *ArgExpressionListOpt::clone() const
{
  ArgExpressionListOpt *ret = new ArgExpressionListOpt(
    cloneFakeList(list)
  );
  return ret;
}


// ------------------ Initializer -------------------
// *** DO NOT EDIT ***
Initializer::~Initializer()
{
  delete annot;
}

char const * const Initializer::kindNames[Initializer::NUM_KINDS] = {
  "IN_expr",
  "IN_compound",
  "IN_ctor",
  "IN_designated",
};

void Initializer::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_GENERIC(loc);
}

void Initializer::gdb() const
  { debugPrint(std::cout, 0); }

DEFN_AST_DOWNCASTS(Initializer, IN_expr, IN_EXPR)

IN_expr::~IN_expr()
{
  delete e;
}

void IN_expr::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, IN_expr);

  Initializer::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(e);
}

IN_expr *IN_expr::clone() const
{
  IN_expr *ret = new IN_expr(
    loc,
    e? e->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Initializer, IN_compound, IN_COMPOUND)

IN_compound::~IN_compound()
{
  inits.deleteAll();
}

void IN_compound::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, IN_compound);

  Initializer::debugPrint(os, indent, subtreeName);

  PRINT_LIST(Initializer, inits);
}

IN_compound *IN_compound::clone() const
{
  IN_compound *ret = new IN_compound(
    loc,
    cloneASTList(inits)
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Initializer, IN_ctor, IN_CTOR)

IN_ctor::~IN_ctor()
{
}

void IN_ctor::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, IN_ctor);

  Initializer::debugPrint(os, indent, subtreeName);

  PRINT_FAKE_LIST(ArgExpression, args);
  PRINT_BOOL(was_IN_expr);
}

IN_ctor *IN_ctor::clone() const
{
  IN_ctor *ret = new IN_ctor(
    loc,
    cloneFakeList(args)
  );
  
         ret->ctorVar = ctorVar;
         ret->was_IN_expr = was_IN_expr;
       ;
  return ret;
}

DEFN_AST_DOWNCASTS(Initializer, IN_designated, IN_DESIGNATED)

IN_designated::~IN_designated()
{
  delete init;
}

void IN_designated::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, IN_designated);

  Initializer::debugPrint(os, indent, subtreeName);

  PRINT_FAKE_LIST(Designator, designator_list);
  PRINT_SUBTREE(init);
}

IN_designated *IN_designated::clone() const
{
  IN_designated *ret = new IN_designated(
    loc,
    cloneFakeList(designator_list),
    init? init->clone() : NULL
  );
  return ret;
}


// ------------------ TemplateDeclaration -------------------
// *** DO NOT EDIT ***
TemplateDeclaration::~TemplateDeclaration()
{
  delete params;
}

char const * const TemplateDeclaration::kindNames[TemplateDeclaration::NUM_KINDS] = {
  "TD_func",
  "TD_decl",
  "TD_tmember",
};

void TemplateDeclaration::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_SUBTREE(params);
}

void TemplateDeclaration::gdb() const
  { debugPrint(std::cout, 0); }

DEFN_AST_DOWNCASTS(TemplateDeclaration, TD_func, TD_FUNC)

TD_func::~TD_func()
{
  delete f;
}

void TD_func::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, TD_func);

  TemplateDeclaration::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(f);
}

TD_func *TD_func::clone() const
{
  TD_func *ret = new TD_func(
    params? params->clone() : NULL,
    f? f->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(TemplateDeclaration, TD_decl, TD_DECL)

TD_decl::~TD_decl()
{
  delete d;
}

void TD_decl::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, TD_decl);

  TemplateDeclaration::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(d);
}

TD_decl *TD_decl::clone() const
{
  TD_decl *ret = new TD_decl(
    params? params->clone() : NULL,
    d? d->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(TemplateDeclaration, TD_tmember, TD_TMEMBER)

TD_tmember::~TD_tmember()
{
  delete d;
}

void TD_tmember::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, TD_tmember);

  TemplateDeclaration::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(d);
}

TD_tmember *TD_tmember::clone() const
{
  TD_tmember *ret = new TD_tmember(
    params? params->clone() : NULL,
    d? d->clone() : NULL
  );
  return ret;
}


// ------------------ TemplateParameter -------------------
// *** DO NOT EDIT ***
TemplateParameter::~TemplateParameter()
{
}

char const * const TemplateParameter::kindNames[TemplateParameter::NUM_KINDS] = {
  "TP_type",
  "TP_nontype",
  "TP_template",
};

void TemplateParameter::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_GENERIC(loc);
  // (lastArgs are printed by subclasses)
}

void TemplateParameter::gdb() const
  { debugPrint(std::cout, 0); }

DEFN_AST_DOWNCASTS(TemplateParameter, TP_type, TP_TYPE)

TP_type::~TP_type()
{
  delete defaultType;
}

void TP_type::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, TP_type);

  TemplateParameter::debugPrint(os, indent, subtreeName);

  PRINT_CSTRING(name);
  PRINT_SUBTREE(defaultType);
  PRINT_SUBTREE(next);
}

TP_type *TP_type::clone() const
{
  TP_type *ret = new TP_type(
    loc,
    name,
    defaultType? defaultType->clone() : NULL,
    next? next->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(TemplateParameter, TP_nontype, TP_NONTYPE)

TP_nontype::~TP_nontype()
{
  delete param;
}

void TP_nontype::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, TP_nontype);

  TemplateParameter::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(param);
  PRINT_SUBTREE(next);
}

TP_nontype *TP_nontype::clone() const
{
  TP_nontype *ret = new TP_nontype(
    loc,
    param? param->clone() : NULL,
    next? next->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(TemplateParameter, TP_template, TP_TEMPLATE)

TP_template::~TP_template()
{
  delete defaultTemplate;
}

void TP_template::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, TP_template);

  TemplateParameter::debugPrint(os, indent, subtreeName);

  PRINT_FAKE_LIST(TemplateParameter, parameters);
  PRINT_CSTRING(name);
  PRINT_SUBTREE(defaultTemplate);
  PRINT_SUBTREE(next);
}

TP_template *TP_template::clone() const
{
  TP_template *ret = new TP_template(
    loc,
    cloneFakeList(parameters),
    name,
    defaultTemplate? defaultTemplate->clone() : NULL,
    next? next->clone() : NULL
  );
  return ret;
}


// ------------------ TemplateArgument -------------------
// *** DO NOT EDIT ***
TemplateArgument::~TemplateArgument()
{
}

char const * const TemplateArgument::kindNames[TemplateArgument::NUM_KINDS] = {
  "TA_type",
  "TA_nontype",
  "TA_templateUsed",
};

void TemplateArgument::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  // (lastArgs are printed by subclasses)
}

void TemplateArgument::gdb() const
  { debugPrint(std::cout, 0); }

DEFN_AST_DOWNCASTS(TemplateArgument, TA_type, TA_TYPE)

TA_type::~TA_type()
{
  delete type;
}

void TA_type::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, TA_type);

  TemplateArgument::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(type);
  PRINT_SUBTREE(next);
}

TA_type *TA_type::clone() const
{
  TA_type *ret = new TA_type(
    type? type->clone() : NULL,
    next? next->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(TemplateArgument, TA_nontype, TA_NONTYPE)

TA_nontype::~TA_nontype()
{
  delete expr;
}

void TA_nontype::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, TA_nontype);

  TemplateArgument::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(expr);
  PRINT_SUBTREE(next);
}

TA_nontype *TA_nontype::clone() const
{
  TA_nontype *ret = new TA_nontype(
    expr? expr->clone() : NULL,
    next? next->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(TemplateArgument, TA_templateUsed, TA_TEMPLATEUSED)

TA_templateUsed::~TA_templateUsed()
{
}

void TA_templateUsed::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, TA_templateUsed);

  TemplateArgument::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(next);
}

TA_templateUsed *TA_templateUsed::clone() const
{
  TA_templateUsed *ret = new TA_templateUsed(
    next? next->clone() : NULL
  );
  return ret;
}


// ------------------ NamespaceDecl -------------------
// *** DO NOT EDIT ***
NamespaceDecl::~NamespaceDecl()
{
}

char const * const NamespaceDecl::kindNames[NamespaceDecl::NUM_KINDS] = {
  "ND_alias",
  "ND_usingDecl",
  "ND_usingDir",
};

void NamespaceDecl::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
}

void NamespaceDecl::gdb() const
  { debugPrint(std::cout, 0); }

DEFN_AST_DOWNCASTS(NamespaceDecl, ND_alias, ND_ALIAS)

ND_alias::~ND_alias()
{
  delete original;
}

void ND_alias::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, ND_alias);

  NamespaceDecl::debugPrint(os, indent, subtreeName);

  PRINT_CSTRING(alias);
  PRINT_SUBTREE(original);
}

ND_alias *ND_alias::clone() const
{
  ND_alias *ret = new ND_alias(
    alias,
    original? original->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(NamespaceDecl, ND_usingDecl, ND_USINGDECL)

ND_usingDecl::~ND_usingDecl()
{
  delete name;
}

void ND_usingDecl::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, ND_usingDecl);

  NamespaceDecl::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(name);
}

ND_usingDecl *ND_usingDecl::clone() const
{
  ND_usingDecl *ret = new ND_usingDecl(
    name? name->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(NamespaceDecl, ND_usingDir, ND_USINGDIR)

ND_usingDir::~ND_usingDir()
{
  delete name;
}

void ND_usingDir::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, ND_usingDir);

  NamespaceDecl::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(name);
}

ND_usingDir *ND_usingDir::clone() const
{
  ND_usingDir *ret = new ND_usingDir(
    name? name->clone() : NULL
  );
  return ret;
}


// *** DO NOT EDIT ***

  // NOTE: do not include xml_type_id.h in the header, because it needs to
  // include cc.gen.ast.h.
  #include "xml_type_id.h"   // type system serialization identity
char const *toString(DeclaratorContext x)
{
  static char const * const map[] = {
    "DC_UNKNOWN",
    "DC_FUNCTION",
    "DC_TF_DECL",
    "DC_TF_EXPLICITINST",
    "DC_MR_DECL",
    "DC_S_DECL",
    "DC_TD_DECL",
    "DC_FEA",
    "DC_D_FUNC",
    "DC_EXCEPTIONSPEC",
    "DC_ON_CONVERSION",
    "DC_CN_DECL",
    "DC_HANDLER",
    "DC_E_CAST",
    "DC_E_SIZEOFTYPE",
    "DC_E_NEW",
    "DC_E_KEYWORDCAST",
    "DC_E_TYPEIDTYPE",
    "DC_TP_TYPE",
    "DC_TP_NONTYPE",
    "DC_TA_TYPE",
    "DC_TS_TYPEOF_TYPE",
    "DC_E_COMPOUNDLIT",
    "DC_E_ALIGNOFTYPE",
    "DC_E_BUILTIN_VA_ARG",
  };
  xassert((unsigned)x < TABLESIZE(map));
  return map[x];
};

void fromXml(DeclaratorContext &out, rostring str)
{
  for (int i=0; i<25; i++) {
    DeclaratorContext e = (DeclaratorContext)i;
    if (0==strcmp(str, toString(e))) {
      out = e;
      return;
    }
  }
  xformat(stringc << "bad DeclaratorContext value: " << str);
}


// ------------------ FullExpressionAnnot -------------------
// *** DO NOT EDIT ***
FullExpressionAnnot::~FullExpressionAnnot()
{
  declarations.deleteAll();
}

void FullExpressionAnnot::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, FullExpressionAnnot);

  PRINT_LIST(Declaration, declarations);
}

void FullExpressionAnnot::gdb() const
  { debugPrint(std::cout, 0); }

FullExpressionAnnot *FullExpressionAnnot::clone() const
{
  FullExpressionAnnot *ret = new FullExpressionAnnot(
    cloneASTList(declarations)
  );
  return ret;
}


// ------------------ ASTTypeof -------------------
// *** DO NOT EDIT ***
ASTTypeof::~ASTTypeof()
{
}

char const * const ASTTypeof::kindNames[ASTTypeof::NUM_KINDS] = {
  "TS_typeof_expr",
  "TS_typeof_type",
};

void ASTTypeof::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
}

void ASTTypeof::gdb() const
  { debugPrint(std::cout, 0); }

DEFN_AST_DOWNCASTS(ASTTypeof, TS_typeof_expr, TS_TYPEOF_EXPR)

TS_typeof_expr::~TS_typeof_expr()
{
  delete expr;
}

void TS_typeof_expr::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, TS_typeof_expr);

  ASTTypeof::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(expr);
}

TS_typeof_expr *TS_typeof_expr::clone() const
{
  TS_typeof_expr *ret = new TS_typeof_expr(
    expr? expr->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(ASTTypeof, TS_typeof_type, TS_TYPEOF_TYPE)

TS_typeof_type::~TS_typeof_type()
{
  delete atype;
}

void TS_typeof_type::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, TS_typeof_type);

  ASTTypeof::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(atype);
}

TS_typeof_type *TS_typeof_type::clone() const
{
  TS_typeof_type *ret = new TS_typeof_type(
    atype? atype->clone() : NULL
  );
  return ret;
}


// ------------------ Designator -------------------
// *** DO NOT EDIT ***
Designator::~Designator()
{
}

char const * const Designator::kindNames[Designator::NUM_KINDS] = {
  "FieldDesignator",
  "SubscriptDesignator",
};

void Designator::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_GENERIC(loc);
}

void Designator::gdb() const
  { debugPrint(std::cout, 0); }

DEFN_AST_DOWNCASTS(Designator, FieldDesignator, FIELDDESIGNATOR)

FieldDesignator::~FieldDesignator()
{
}

void FieldDesignator::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, FieldDesignator);

  Designator::debugPrint(os, indent, subtreeName);

  PRINT_CSTRING(id);
}

FieldDesignator *FieldDesignator::clone() const
{
  FieldDesignator *ret = new FieldDesignator(
    loc,
    id
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Designator, SubscriptDesignator, SUBSCRIPTDESIGNATOR)

SubscriptDesignator::~SubscriptDesignator()
{
  delete idx_expr;
  delete idx_expr2;
}

void SubscriptDesignator::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    if (ambiguity) {
      printAmbiguities(os, indent);
      return;     // skip the normal, unambiguous-node print code
    }
  ;
  PRINT_HEADER(subtreeName, SubscriptDesignator);

  Designator::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(idx_expr);
  PRINT_SUBTREE(idx_expr2);
}

SubscriptDesignator *SubscriptDesignator::clone() const
{
  SubscriptDesignator *ret = new SubscriptDesignator(
    loc,
    idx_expr? idx_expr->clone() : NULL,
    idx_expr2? idx_expr2->clone() : NULL
  );
  return ret;
}


// ------------------ AttributeSpecifierList -------------------
// *** DO NOT EDIT ***
AttributeSpecifierList::~AttributeSpecifierList()
{
  delete spec;
  delete next;
}

void AttributeSpecifierList::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, AttributeSpecifierList);

  PRINT_SUBTREE(spec);
  PRINT_SUBTREE(next);
}

void AttributeSpecifierList::gdb() const
  { debugPrint(std::cout, 0); }

AttributeSpecifierList *AttributeSpecifierList::clone() const
{
  AttributeSpecifierList *ret = new AttributeSpecifierList(
    spec? spec->clone() : NULL,
    next? next->clone() : NULL
  );
  return ret;
}


// ------------------ AttributeSpecifier -------------------
// *** DO NOT EDIT ***
AttributeSpecifier::~AttributeSpecifier()
{
  delete attr;
  delete next;
}

void AttributeSpecifier::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, AttributeSpecifier);

  PRINT_SUBTREE(attr);
  PRINT_SUBTREE(next);
}

void AttributeSpecifier::gdb() const
  { debugPrint(std::cout, 0); }

AttributeSpecifier *AttributeSpecifier::clone() const
{
  AttributeSpecifier *ret = new AttributeSpecifier(
    attr? attr->clone() : NULL,
    next? next->clone() : NULL
  );
  return ret;
}


// ------------------ Attribute -------------------
// *** DO NOT EDIT ***
Attribute::~Attribute()
{
}

char const * const Attribute::kindNames[Attribute::NUM_KINDS] = {
  "AT_empty",
  "AT_word",
  "AT_func",
};

void Attribute::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_GENERIC(loc);
}

void Attribute::gdb() const
  { debugPrint(std::cout, 0); }

DEFN_AST_DOWNCASTS(Attribute, AT_empty, AT_EMPTY)

AT_empty::~AT_empty()
{
}

void AT_empty::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, AT_empty);

  Attribute::debugPrint(os, indent, subtreeName);

}

AT_empty *AT_empty::clone() const
{
  AT_empty *ret = new AT_empty(
    loc
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Attribute, AT_word, AT_WORD)

AT_word::~AT_word()
{
}

void AT_word::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, AT_word);

  Attribute::debugPrint(os, indent, subtreeName);

  PRINT_CSTRING(w);
}

AT_word *AT_word::clone() const
{
  AT_word *ret = new AT_word(
    loc,
    w
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Attribute, AT_func, AT_FUNC)

AT_func::~AT_func()
{
}

void AT_func::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, AT_func);

  Attribute::debugPrint(os, indent, subtreeName);

  PRINT_CSTRING(f);
  PRINT_FAKE_LIST(ArgExpression, args);
}

AT_func *AT_func::clone() const
{
  AT_func *ret = new AT_func(
    loc,
    f,
    cloneFakeList(args)
  );
  return ret;
}




// ---------------------- ASTVisitor ---------------------
// default no-op visitor
ASTVisitor::~ASTVisitor() {}
bool ASTVisitor::visitTranslationUnit(TranslationUnit *obj) { return true; }
void ASTVisitor::postvisitTranslationUnit(TranslationUnit *obj) {}
bool ASTVisitor::visitTopForm(TopForm *obj) { return true; }
void ASTVisitor::postvisitTopForm(TopForm *obj) {}
bool ASTVisitor::visitFunction(Function *obj) { return true; }
void ASTVisitor::postvisitFunction(Function *obj) {}
bool ASTVisitor::visitMemberInit(MemberInit *obj) { return true; }
void ASTVisitor::postvisitMemberInit(MemberInit *obj) {}
bool ASTVisitor::visitDeclaration(Declaration *obj) { return true; }
void ASTVisitor::postvisitDeclaration(Declaration *obj) {}
bool ASTVisitor::visitASTTypeId(ASTTypeId *obj) { return true; }
void ASTVisitor::postvisitASTTypeId(ASTTypeId *obj) {}
bool ASTVisitor::visitPQName(PQName *obj) { return true; }
void ASTVisitor::postvisitPQName(PQName *obj) {}
bool ASTVisitor::visitTypeSpecifier(TypeSpecifier *obj) { return true; }
void ASTVisitor::postvisitTypeSpecifier(TypeSpecifier *obj) {}
bool ASTVisitor::visitBaseClassSpec(BaseClassSpec *obj) { return true; }
void ASTVisitor::postvisitBaseClassSpec(BaseClassSpec *obj) {}
bool ASTVisitor::visitEnumerator(Enumerator *obj) { return true; }
void ASTVisitor::postvisitEnumerator(Enumerator *obj) {}
bool ASTVisitor::visitMemberList(MemberList *obj) { return true; }
void ASTVisitor::postvisitMemberList(MemberList *obj) {}
bool ASTVisitor::visitMember(Member *obj) { return true; }
void ASTVisitor::postvisitMember(Member *obj) {}
bool ASTVisitor::visitDeclarator(Declarator *obj) { return true; }
void ASTVisitor::postvisitDeclarator(Declarator *obj) {}
bool ASTVisitor::visitIDeclarator(IDeclarator *obj) { return true; }
void ASTVisitor::postvisitIDeclarator(IDeclarator *obj) {}
bool ASTVisitor::visitExceptionSpec(ExceptionSpec *obj) { return true; }
void ASTVisitor::postvisitExceptionSpec(ExceptionSpec *obj) {}
bool ASTVisitor::visitOperatorName(OperatorName *obj) { return true; }
void ASTVisitor::postvisitOperatorName(OperatorName *obj) {}
bool ASTVisitor::visitStatement(Statement *obj) { return true; }
void ASTVisitor::postvisitStatement(Statement *obj) {}
bool ASTVisitor::visitCondition(Condition *obj) { return true; }
void ASTVisitor::postvisitCondition(Condition *obj) {}
bool ASTVisitor::visitHandler(Handler *obj) { return true; }
void ASTVisitor::postvisitHandler(Handler *obj) {}
bool ASTVisitor::visitExpression(Expression *obj) { return true; }
void ASTVisitor::postvisitExpression(Expression *obj) {}
bool ASTVisitor::visitFullExpression(FullExpression *obj) { return true; }
void ASTVisitor::postvisitFullExpression(FullExpression *obj) {}
bool ASTVisitor::visitArgExpression(ArgExpression *obj) { return true; }
void ASTVisitor::postvisitArgExpression(ArgExpression *obj) {}
bool ASTVisitor::visitArgExpressionListOpt(ArgExpressionListOpt *obj) { return true; }
void ASTVisitor::postvisitArgExpressionListOpt(ArgExpressionListOpt *obj) {}
bool ASTVisitor::visitInitializer(Initializer *obj) { return true; }
void ASTVisitor::postvisitInitializer(Initializer *obj) {}
bool ASTVisitor::visitTemplateDeclaration(TemplateDeclaration *obj) { return true; }
void ASTVisitor::postvisitTemplateDeclaration(TemplateDeclaration *obj) {}
bool ASTVisitor::visitTemplateParameter(TemplateParameter *obj) { return true; }
void ASTVisitor::postvisitTemplateParameter(TemplateParameter *obj) {}
bool ASTVisitor::visitTemplateArgument(TemplateArgument *obj) { return true; }
void ASTVisitor::postvisitTemplateArgument(TemplateArgument *obj) {}
bool ASTVisitor::visitNamespaceDecl(NamespaceDecl *obj) { return true; }
void ASTVisitor::postvisitNamespaceDecl(NamespaceDecl *obj) {}
bool ASTVisitor::visitFullExpressionAnnot(FullExpressionAnnot *obj) { return true; }
void ASTVisitor::postvisitFullExpressionAnnot(FullExpressionAnnot *obj) {}
bool ASTVisitor::visitASTTypeof(ASTTypeof *obj) { return true; }
void ASTVisitor::postvisitASTTypeof(ASTTypeof *obj) {}
bool ASTVisitor::visitDesignator(Designator *obj) { return true; }
void ASTVisitor::postvisitDesignator(Designator *obj) {}
bool ASTVisitor::visitAttributeSpecifierList(AttributeSpecifierList *obj) { return true; }
void ASTVisitor::postvisitAttributeSpecifierList(AttributeSpecifierList *obj) {}
bool ASTVisitor::visitAttributeSpecifier(AttributeSpecifier *obj) { return true; }
void ASTVisitor::postvisitAttributeSpecifier(AttributeSpecifier *obj) {}
bool ASTVisitor::visitAttribute(Attribute *obj) { return true; }
void ASTVisitor::postvisitAttribute(Attribute *obj) {}

// List 'classes'
bool ASTVisitor::visitList_TranslationUnit_topForms(ASTList<TopForm>*) { return true; }
void ASTVisitor::postvisitList_TranslationUnit_topForms(ASTList<TopForm>*) {}
bool ASTVisitor::visitList_TF_namespaceDefn_forms(ASTList<TopForm>*) { return true; }
void ASTVisitor::postvisitList_TF_namespaceDefn_forms(ASTList<TopForm>*) {}
bool ASTVisitor::visitList_Function_inits(FakeList<MemberInit>*) { return true; }
void ASTVisitor::postvisitList_Function_inits(FakeList<MemberInit>*) {}
bool ASTVisitor::visitList_Function_handlers(FakeList<Handler>*) { return true; }
void ASTVisitor::postvisitList_Function_handlers(FakeList<Handler>*) {}
bool ASTVisitor::visitList_MemberInit_args(FakeList<ArgExpression>*) { return true; }
void ASTVisitor::postvisitList_MemberInit_args(FakeList<ArgExpression>*) {}
bool ASTVisitor::visitList_MemberList_list(ASTList<Member>*) { return true; }
void ASTVisitor::postvisitList_MemberList_list(ASTList<Member>*) {}
bool ASTVisitor::visitList_Declaration_decllist(FakeList<Declarator>*) { return true; }
void ASTVisitor::postvisitList_Declaration_decllist(FakeList<Declarator>*) {}
bool ASTVisitor::visitList_TS_classSpec_bases(FakeList<BaseClassSpec>*) { return true; }
void ASTVisitor::postvisitList_TS_classSpec_bases(FakeList<BaseClassSpec>*) {}
bool ASTVisitor::visitList_TS_enumSpec_elts(FakeList<Enumerator>*) { return true; }
void ASTVisitor::postvisitList_TS_enumSpec_elts(FakeList<Enumerator>*) {}
bool ASTVisitor::visitList_D_func_params(FakeList<ASTTypeId>*) { return true; }
void ASTVisitor::postvisitList_D_func_params(FakeList<ASTTypeId>*) {}
bool ASTVisitor::visitList_D_func_kAndR_params(FakeList<PQ_name>*) { return true; }
void ASTVisitor::postvisitList_D_func_kAndR_params(FakeList<PQ_name>*) {}
bool ASTVisitor::visitList_S_try_handlers(FakeList<Handler>*) { return true; }
void ASTVisitor::postvisitList_S_try_handlers(FakeList<Handler>*) {}
bool ASTVisitor::visitList_ExceptionSpec_types(FakeList<ASTTypeId>*) { return true; }
void ASTVisitor::postvisitList_ExceptionSpec_types(FakeList<ASTTypeId>*) {}
bool ASTVisitor::visitList_S_compound_stmts(ASTList<Statement>*) { return true; }
void ASTVisitor::postvisitList_S_compound_stmts(ASTList<Statement>*) {}
bool ASTVisitor::visitList_E_funCall_args(FakeList<ArgExpression>*) { return true; }
void ASTVisitor::postvisitList_E_funCall_args(FakeList<ArgExpression>*) {}
bool ASTVisitor::visitList_E_constructor_args(FakeList<ArgExpression>*) { return true; }
void ASTVisitor::postvisitList_E_constructor_args(FakeList<ArgExpression>*) {}
bool ASTVisitor::visitList_E_new_placementArgs(FakeList<ArgExpression>*) { return true; }
void ASTVisitor::postvisitList_E_new_placementArgs(FakeList<ArgExpression>*) {}
bool ASTVisitor::visitList_ArgExpressionListOpt_list(FakeList<ArgExpression>*) { return true; }
void ASTVisitor::postvisitList_ArgExpressionListOpt_list(FakeList<ArgExpression>*) {}
bool ASTVisitor::visitList_IN_compound_inits(ASTList<Initializer>*) { return true; }
void ASTVisitor::postvisitList_IN_compound_inits(ASTList<Initializer>*) {}
bool ASTVisitor::visitList_IN_ctor_args(FakeList<ArgExpression>*) { return true; }
void ASTVisitor::postvisitList_IN_ctor_args(FakeList<ArgExpression>*) {}
bool ASTVisitor::visitList_TP_template_parameters(FakeList<TemplateParameter>*) { return true; }
void ASTVisitor::postvisitList_TP_template_parameters(FakeList<TemplateParameter>*) {}
bool ASTVisitor::visitList_IN_designated_designator_list(FakeList<Designator>*) { return true; }
void ASTVisitor::postvisitList_IN_designated_designator_list(FakeList<Designator>*) {}
bool ASTVisitor::visitList_FullExpressionAnnot_declarations(ASTList<Declaration>*) { return true; }
void ASTVisitor::postvisitList_FullExpressionAnnot_declarations(ASTList<Declaration>*) {}
bool ASTVisitor::visitList_AT_func_args(FakeList<ArgExpression>*) { return true; }
void ASTVisitor::postvisitList_AT_func_args(FakeList<ArgExpression>*) {}
bool ASTVisitor::visitListItem_TranslationUnit_topForms(TopForm*) { return true; }
void ASTVisitor::postvisitListItem_TranslationUnit_topForms(TopForm*) {}
bool ASTVisitor::visitListItem_TF_namespaceDefn_forms(TopForm*) { return true; }
void ASTVisitor::postvisitListItem_TF_namespaceDefn_forms(TopForm*) {}
bool ASTVisitor::visitListItem_Function_inits(MemberInit*) { return true; }
void ASTVisitor::postvisitListItem_Function_inits(MemberInit*) {}
bool ASTVisitor::visitListItem_Function_handlers(Handler*) { return true; }
void ASTVisitor::postvisitListItem_Function_handlers(Handler*) {}
bool ASTVisitor::visitListItem_MemberInit_args(ArgExpression*) { return true; }
void ASTVisitor::postvisitListItem_MemberInit_args(ArgExpression*) {}
bool ASTVisitor::visitListItem_MemberList_list(Member*) { return true; }
void ASTVisitor::postvisitListItem_MemberList_list(Member*) {}
bool ASTVisitor::visitListItem_Declaration_decllist(Declarator*) { return true; }
void ASTVisitor::postvisitListItem_Declaration_decllist(Declarator*) {}
bool ASTVisitor::visitListItem_TS_classSpec_bases(BaseClassSpec*) { return true; }
void ASTVisitor::postvisitListItem_TS_classSpec_bases(BaseClassSpec*) {}
bool ASTVisitor::visitListItem_TS_enumSpec_elts(Enumerator*) { return true; }
void ASTVisitor::postvisitListItem_TS_enumSpec_elts(Enumerator*) {}
bool ASTVisitor::visitListItem_D_func_params(ASTTypeId*) { return true; }
void ASTVisitor::postvisitListItem_D_func_params(ASTTypeId*) {}
bool ASTVisitor::visitListItem_D_func_kAndR_params(PQ_name*) { return true; }
void ASTVisitor::postvisitListItem_D_func_kAndR_params(PQ_name*) {}
bool ASTVisitor::visitListItem_S_try_handlers(Handler*) { return true; }
void ASTVisitor::postvisitListItem_S_try_handlers(Handler*) {}
bool ASTVisitor::visitListItem_ExceptionSpec_types(ASTTypeId*) { return true; }
void ASTVisitor::postvisitListItem_ExceptionSpec_types(ASTTypeId*) {}
bool ASTVisitor::visitListItem_S_compound_stmts(Statement*) { return true; }
void ASTVisitor::postvisitListItem_S_compound_stmts(Statement*) {}
bool ASTVisitor::visitListItem_E_funCall_args(ArgExpression*) { return true; }
void ASTVisitor::postvisitListItem_E_funCall_args(ArgExpression*) {}
bool ASTVisitor::visitListItem_E_constructor_args(ArgExpression*) { return true; }
void ASTVisitor::postvisitListItem_E_constructor_args(ArgExpression*) {}
bool ASTVisitor::visitListItem_E_new_placementArgs(ArgExpression*) { return true; }
void ASTVisitor::postvisitListItem_E_new_placementArgs(ArgExpression*) {}
bool ASTVisitor::visitListItem_ArgExpressionListOpt_list(ArgExpression*) { return true; }
void ASTVisitor::postvisitListItem_ArgExpressionListOpt_list(ArgExpression*) {}
bool ASTVisitor::visitListItem_IN_compound_inits(Initializer*) { return true; }
void ASTVisitor::postvisitListItem_IN_compound_inits(Initializer*) {}
bool ASTVisitor::visitListItem_IN_ctor_args(ArgExpression*) { return true; }
void ASTVisitor::postvisitListItem_IN_ctor_args(ArgExpression*) {}
bool ASTVisitor::visitListItem_TP_template_parameters(TemplateParameter*) { return true; }
void ASTVisitor::postvisitListItem_TP_template_parameters(TemplateParameter*) {}
bool ASTVisitor::visitListItem_IN_designated_designator_list(Designator*) { return true; }
void ASTVisitor::postvisitListItem_IN_designated_designator_list(Designator*) {}
bool ASTVisitor::visitListItem_FullExpressionAnnot_declarations(Declaration*) { return true; }
void ASTVisitor::postvisitListItem_FullExpressionAnnot_declarations(Declaration*) {}
bool ASTVisitor::visitListItem_AT_func_args(ArgExpression*) { return true; }
void ASTVisitor::postvisitListItem_AT_func_args(ArgExpression*) {}


void TranslationUnit::traverse(ASTVisitor &vis)
{
  if (!vis.visitTranslationUnit(this)) { return; }

  if (vis.visitList_TranslationUnit_topForms(&topForms)) {
    FOREACH_ASTLIST_NC(TopForm, topForms, iter) {
      if (vis.visitListItem_TranslationUnit_topForms(iter.data())) {
        iter.data()->traverse(vis);
        vis.postvisitListItem_TranslationUnit_topForms(iter.data());
      }
    }
    vis.postvisitList_TranslationUnit_topForms(&topForms);
  }
  vis.postvisitTranslationUnit(this);
}

void TopForm::traverse(ASTVisitor &vis)
{
  // no 'visit' because it's handled by subclasses

   if (ambiguity) ambiguity->traverse(vis); ;
  // no 'postvisit' either
}

void TF_decl::traverse(ASTVisitor &vis)
{
  if (!vis.visitTopForm(this)) { return; }

  TopForm::traverse(vis);

  if (decl) { decl->traverse(vis); }
  vis.postvisitTopForm(this);
}

void TF_func::traverse(ASTVisitor &vis)
{
  if (!vis.visitTopForm(this)) { return; }

  TopForm::traverse(vis);

  if (f) { f->traverse(vis); }
  vis.postvisitTopForm(this);
}

void TF_template::traverse(ASTVisitor &vis)
{
  if (!vis.visitTopForm(this)) { return; }

  TopForm::traverse(vis);

  if (td) { td->traverse(vis); }
  vis.postvisitTopForm(this);
}

void TF_explicitInst::traverse(ASTVisitor &vis)
{
  if (!vis.visitTopForm(this)) { return; }

  TopForm::traverse(vis);

  if (d) { d->traverse(vis); }
  vis.postvisitTopForm(this);
}

void TF_linkage::traverse(ASTVisitor &vis)
{
  if (!vis.visitTopForm(this)) { return; }

  TopForm::traverse(vis);

  if (forms) { forms->traverse(vis); }
  vis.postvisitTopForm(this);
}

void TF_one_linkage::traverse(ASTVisitor &vis)
{
  if (!vis.visitTopForm(this)) { return; }

  TopForm::traverse(vis);

  if (form) { form->traverse(vis); }
  vis.postvisitTopForm(this);
}

void TF_asm::traverse(ASTVisitor &vis)
{
  if (!vis.visitTopForm(this)) { return; }

  TopForm::traverse(vis);

  if (text) { text->traverse(vis); }
  vis.postvisitTopForm(this);
}

void TF_namespaceDefn::traverse(ASTVisitor &vis)
{
  if (!vis.visitTopForm(this)) { return; }

  TopForm::traverse(vis);

  if (vis.visitList_TF_namespaceDefn_forms(&forms)) {
    FOREACH_ASTLIST_NC(TopForm, forms, iter) {
      if (vis.visitListItem_TF_namespaceDefn_forms(iter.data())) {
        iter.data()->traverse(vis);
        vis.postvisitListItem_TF_namespaceDefn_forms(iter.data());
      }
    }
    vis.postvisitList_TF_namespaceDefn_forms(&forms);
  }
  vis.postvisitTopForm(this);
}

void TF_namespaceDecl::traverse(ASTVisitor &vis)
{
  if (!vis.visitTopForm(this)) { return; }

  TopForm::traverse(vis);

  if (decl) { decl->traverse(vis); }
  vis.postvisitTopForm(this);
}

void Function::traverse(ASTVisitor &vis)
{
  if (!vis.visitFunction(this)) { return; }

  if (retspec) { retspec->traverse(vis); }
  if (nameAndParams) { nameAndParams->traverse(vis); }
  if (vis.visitList_Function_inits(inits)) {
    FAKELIST_FOREACH_NC(MemberInit, inits, iter) {
      if (vis.visitListItem_Function_inits(iter)) {
        iter->traverse(vis);
        vis.postvisitListItem_Function_inits(iter);
      }
    }
    vis.postvisitList_Function_inits(inits);
  }
  if (body) { body->traverse(vis); }
  if (vis.visitList_Function_handlers(handlers)) {
    FAKELIST_FOREACH_NC(Handler, handlers, iter) {
      if (vis.visitListItem_Function_handlers(iter)) {
        iter->traverse(vis);
        vis.postvisitListItem_Function_handlers(iter);
      }
    }
    vis.postvisitList_Function_handlers(handlers);
  }
  vis.postvisitFunction(this);
}

void MemberInit::traverse(ASTVisitor &vis)
{
  if (!vis.visitMemberInit(this)) { return; }

  if (name) { name->traverse(vis); }
  if (vis.visitList_MemberInit_args(args)) {
    FAKELIST_FOREACH_NC(ArgExpression, args, iter) {
      if (vis.visitListItem_MemberInit_args(iter)) {
        iter->traverse(vis);
        vis.postvisitListItem_MemberInit_args(iter);
      }
    }
    vis.postvisitList_MemberInit_args(args);
  }
  vis.postvisitMemberInit(this);
}

void Declaration::traverse(ASTVisitor &vis)
{
  if (!vis.visitDeclaration(this)) { return; }

  if (spec) { spec->traverse(vis); }
  if (vis.visitList_Declaration_decllist(decllist)) {
    FAKELIST_FOREACH_NC(Declarator, decllist, iter) {
      if (vis.visitListItem_Declaration_decllist(iter)) {
        iter->traverse(vis);
        vis.postvisitListItem_Declaration_decllist(iter);
      }
    }
    vis.postvisitList_Declaration_decllist(decllist);
  }
  vis.postvisitDeclaration(this);
}

void ASTTypeId::traverse(ASTVisitor &vis)
{
  if (!vis.visitASTTypeId(this)) { return; }

  if (spec) { spec->traverse(vis); }
  if (decl) { decl->traverse(vis); }
   if (ambiguity) ambiguity->traverse(vis); ;
  vis.postvisitASTTypeId(this);
}

void PQName::traverse(ASTVisitor &vis)
{
  // no 'visit' because it's handled by subclasses

  // no 'postvisit' either
}

void PQ_qualifier::traverse(ASTVisitor &vis)
{
  if (!vis.visitPQName(this)) { return; }

  PQName::traverse(vis);

  if (templArgs) { templArgs->traverse(vis); }
  if (rest) { rest->traverse(vis); }
   if (ambiguity) ambiguity->traverse(vis); ;
  vis.postvisitPQName(this);
}

void PQ_name::traverse(ASTVisitor &vis)
{
  if (!vis.visitPQName(this)) { return; }

  PQName::traverse(vis);

  vis.postvisitPQName(this);
}

void PQ_operator::traverse(ASTVisitor &vis)
{
  if (!vis.visitPQName(this)) { return; }

  PQName::traverse(vis);

  if (o) { o->traverse(vis); }
  vis.postvisitPQName(this);
}

void PQ_template::traverse(ASTVisitor &vis)
{
  if (!vis.visitPQName(this)) { return; }

  PQName::traverse(vis);

  if (templArgs) { templArgs->traverse(vis); }
  vis.postvisitPQName(this);
}

void PQ_variable::traverse(ASTVisitor &vis)
{
  if (!vis.visitPQName(this)) { return; }

  PQName::traverse(vis);

  vis.postvisitPQName(this);
}

void TypeSpecifier::traverse(ASTVisitor &vis)
{
  // no 'visit' because it's handled by subclasses

  // no 'postvisit' either
}

void TS_name::traverse(ASTVisitor &vis)
{
  if (!vis.visitTypeSpecifier(this)) { return; }

  TypeSpecifier::traverse(vis);

  if (name) { name->traverse(vis); }
  vis.postvisitTypeSpecifier(this);
}

void TS_simple::traverse(ASTVisitor &vis)
{
  if (!vis.visitTypeSpecifier(this)) { return; }

  TypeSpecifier::traverse(vis);

  vis.postvisitTypeSpecifier(this);
}

void TS_elaborated::traverse(ASTVisitor &vis)
{
  if (!vis.visitTypeSpecifier(this)) { return; }

  TypeSpecifier::traverse(vis);

  if (name) { name->traverse(vis); }
  vis.postvisitTypeSpecifier(this);
}

void TS_classSpec::traverse(ASTVisitor &vis)
{
  if (!vis.visitTypeSpecifier(this)) { return; }

  TypeSpecifier::traverse(vis);

  if (name) { name->traverse(vis); }
  if (vis.visitList_TS_classSpec_bases(bases)) {
    FAKELIST_FOREACH_NC(BaseClassSpec, bases, iter) {
      if (vis.visitListItem_TS_classSpec_bases(iter)) {
        iter->traverse(vis);
        vis.postvisitListItem_TS_classSpec_bases(iter);
      }
    }
    vis.postvisitList_TS_classSpec_bases(bases);
  }
  if (members) { members->traverse(vis); }
  vis.postvisitTypeSpecifier(this);
}

void TS_enumSpec::traverse(ASTVisitor &vis)
{
  if (!vis.visitTypeSpecifier(this)) { return; }

  TypeSpecifier::traverse(vis);

  if (vis.visitList_TS_enumSpec_elts(elts)) {
    FAKELIST_FOREACH_NC(Enumerator, elts, iter) {
      if (vis.visitListItem_TS_enumSpec_elts(iter)) {
        iter->traverse(vis);
        vis.postvisitListItem_TS_enumSpec_elts(iter);
      }
    }
    vis.postvisitList_TS_enumSpec_elts(elts);
  }
  vis.postvisitTypeSpecifier(this);
}

void TS_type::traverse(ASTVisitor &vis)
{
  if (!vis.visitTypeSpecifier(this)) { return; }

  TypeSpecifier::traverse(vis);

  vis.postvisitTypeSpecifier(this);
}

void TS_typeof::traverse(ASTVisitor &vis)
{
  if (!vis.visitTypeSpecifier(this)) { return; }

  TypeSpecifier::traverse(vis);

  if (atype) { atype->traverse(vis); }
  vis.postvisitTypeSpecifier(this);
}

void BaseClassSpec::traverse(ASTVisitor &vis)
{
  if (!vis.visitBaseClassSpec(this)) { return; }

  if (name) { name->traverse(vis); }
  vis.postvisitBaseClassSpec(this);
}

void Enumerator::traverse(ASTVisitor &vis)
{
  if (!vis.visitEnumerator(this)) { return; }

  if (expr) { expr->traverse(vis); }
  vis.postvisitEnumerator(this);
}

void MemberList::traverse(ASTVisitor &vis)
{
  if (!vis.visitMemberList(this)) { return; }

  if (vis.visitList_MemberList_list(&list)) {
    FOREACH_ASTLIST_NC(Member, list, iter) {
      if (vis.visitListItem_MemberList_list(iter.data())) {
        iter.data()->traverse(vis);
        vis.postvisitListItem_MemberList_list(iter.data());
      }
    }
    vis.postvisitList_MemberList_list(&list);
  }
  vis.postvisitMemberList(this);
}

void Member::traverse(ASTVisitor &vis)
{
  // no 'visit' because it's handled by subclasses

  // no 'postvisit' either
}

void MR_decl::traverse(ASTVisitor &vis)
{
  if (!vis.visitMember(this)) { return; }

  Member::traverse(vis);

  if (d) { d->traverse(vis); }
  vis.postvisitMember(this);
}

void MR_func::traverse(ASTVisitor &vis)
{
  if (!vis.visitMember(this)) { return; }

  Member::traverse(vis);

  if (f) { f->traverse(vis); }
  vis.postvisitMember(this);
}

void MR_access::traverse(ASTVisitor &vis)
{
  if (!vis.visitMember(this)) { return; }

  Member::traverse(vis);

  vis.postvisitMember(this);
}

void MR_usingDecl::traverse(ASTVisitor &vis)
{
  if (!vis.visitMember(this)) { return; }

  Member::traverse(vis);

  if (decl) { decl->traverse(vis); }
  vis.postvisitMember(this);
}

void MR_template::traverse(ASTVisitor &vis)
{
  if (!vis.visitMember(this)) { return; }

  Member::traverse(vis);

  if (d) { d->traverse(vis); }
  vis.postvisitMember(this);
}

void Declarator::traverse(ASTVisitor &vis)
{
  if (!vis.visitDeclarator(this)) { return; }

  if (decl) { decl->traverse(vis); }
  if (init) { init->traverse(vis); }
   if (ambiguity) ambiguity->traverse(vis); ;
  vis.postvisitDeclarator(this);
}

void IDeclarator::traverse(ASTVisitor &vis)
{
  // no 'visit' because it's handled by subclasses

  // no 'postvisit' either
}

void D_name::traverse(ASTVisitor &vis)
{
  if (!vis.visitIDeclarator(this)) { return; }

  IDeclarator::traverse(vis);

  if (name) { name->traverse(vis); }
  vis.postvisitIDeclarator(this);
}

void D_pointer::traverse(ASTVisitor &vis)
{
  if (!vis.visitIDeclarator(this)) { return; }

  IDeclarator::traverse(vis);

  if (base) { base->traverse(vis); }
  vis.postvisitIDeclarator(this);
}

void D_reference::traverse(ASTVisitor &vis)
{
  if (!vis.visitIDeclarator(this)) { return; }

  IDeclarator::traverse(vis);

  if (base) { base->traverse(vis); }
  vis.postvisitIDeclarator(this);
}

void D_func::traverse(ASTVisitor &vis)
{
  if (!vis.visitIDeclarator(this)) { return; }

  IDeclarator::traverse(vis);

  if (base) { base->traverse(vis); }
  if (vis.visitList_D_func_params(params)) {
    FAKELIST_FOREACH_NC(ASTTypeId, params, iter) {
      if (vis.visitListItem_D_func_params(iter)) {
        iter->traverse(vis);
        vis.postvisitListItem_D_func_params(iter);
      }
    }
    vis.postvisitList_D_func_params(params);
  }
  if (exnSpec) { exnSpec->traverse(vis); }
  if (vis.visitList_D_func_kAndR_params(kAndR_params)) {
    FAKELIST_FOREACH_NC(PQ_name, kAndR_params, iter) {
      if (vis.visitListItem_D_func_kAndR_params(iter)) {
        iter->traverse(vis);
        vis.postvisitListItem_D_func_kAndR_params(iter);
      }
    }
    vis.postvisitList_D_func_kAndR_params(kAndR_params);
  }
  vis.postvisitIDeclarator(this);
}

void D_array::traverse(ASTVisitor &vis)
{
  if (!vis.visitIDeclarator(this)) { return; }

  IDeclarator::traverse(vis);

  if (base) { base->traverse(vis); }
  if (size) { size->traverse(vis); }
  vis.postvisitIDeclarator(this);
}

void D_bitfield::traverse(ASTVisitor &vis)
{
  if (!vis.visitIDeclarator(this)) { return; }

  IDeclarator::traverse(vis);

  if (name) { name->traverse(vis); }
  if (bits) { bits->traverse(vis); }
  vis.postvisitIDeclarator(this);
}

void D_ptrToMember::traverse(ASTVisitor &vis)
{
  if (!vis.visitIDeclarator(this)) { return; }

  IDeclarator::traverse(vis);

  if (nestedName) { nestedName->traverse(vis); }
  if (base) { base->traverse(vis); }
  vis.postvisitIDeclarator(this);
}

void D_grouping::traverse(ASTVisitor &vis)
{
  if (!vis.visitIDeclarator(this)) { return; }

  IDeclarator::traverse(vis);

  if (base) { base->traverse(vis); }
  vis.postvisitIDeclarator(this);
}

void ExceptionSpec::traverse(ASTVisitor &vis)
{
  if (!vis.visitExceptionSpec(this)) { return; }

  if (vis.visitList_ExceptionSpec_types(types)) {
    FAKELIST_FOREACH_NC(ASTTypeId, types, iter) {
      if (vis.visitListItem_ExceptionSpec_types(iter)) {
        iter->traverse(vis);
        vis.postvisitListItem_ExceptionSpec_types(iter);
      }
    }
    vis.postvisitList_ExceptionSpec_types(types);
  }
  vis.postvisitExceptionSpec(this);
}

void OperatorName::traverse(ASTVisitor &vis)
{
  // no 'visit' because it's handled by subclasses

  // no 'postvisit' either
}

void ON_newDel::traverse(ASTVisitor &vis)
{
  if (!vis.visitOperatorName(this)) { return; }

  OperatorName::traverse(vis);

  vis.postvisitOperatorName(this);
}

void ON_operator::traverse(ASTVisitor &vis)
{
  if (!vis.visitOperatorName(this)) { return; }

  OperatorName::traverse(vis);

  vis.postvisitOperatorName(this);
}

void ON_conversion::traverse(ASTVisitor &vis)
{
  if (!vis.visitOperatorName(this)) { return; }

  OperatorName::traverse(vis);

  if (type) { type->traverse(vis); }
  vis.postvisitOperatorName(this);
}

void Statement::traverse(ASTVisitor &vis)
{
  // no 'visit' because it's handled by subclasses

   if (ambiguity) ambiguity->traverse(vis); ;
  // no 'postvisit' either
}

void S_skip::traverse(ASTVisitor &vis)
{
  if (!vis.visitStatement(this)) { return; }

  Statement::traverse(vis);

  vis.postvisitStatement(this);
}

void S_label::traverse(ASTVisitor &vis)
{
  if (!vis.visitStatement(this)) { return; }

  Statement::traverse(vis);

  if (s) { s->traverse(vis); }
  vis.postvisitStatement(this);
}

void S_case::traverse(ASTVisitor &vis)
{
  if (!vis.visitStatement(this)) { return; }

  Statement::traverse(vis);

  if (expr) { expr->traverse(vis); }
  if (s) { s->traverse(vis); }
  vis.postvisitStatement(this);
}

void S_default::traverse(ASTVisitor &vis)
{
  if (!vis.visitStatement(this)) { return; }

  Statement::traverse(vis);

  if (s) { s->traverse(vis); }
  vis.postvisitStatement(this);
}

void S_expr::traverse(ASTVisitor &vis)
{
  if (!vis.visitStatement(this)) { return; }

  Statement::traverse(vis);

  if (expr) { expr->traverse(vis); }
  vis.postvisitStatement(this);
}

void S_compound::traverse(ASTVisitor &vis)
{
  if (!vis.visitStatement(this)) { return; }

  Statement::traverse(vis);

  if (vis.visitList_S_compound_stmts(&stmts)) {
    FOREACH_ASTLIST_NC(Statement, stmts, iter) {
      if (vis.visitListItem_S_compound_stmts(iter.data())) {
        iter.data()->traverse(vis);
        vis.postvisitListItem_S_compound_stmts(iter.data());
      }
    }
    vis.postvisitList_S_compound_stmts(&stmts);
  }
  vis.postvisitStatement(this);
}

void S_if::traverse(ASTVisitor &vis)
{
  if (!vis.visitStatement(this)) { return; }

  Statement::traverse(vis);

  if (cond) { cond->traverse(vis); }
  if (thenBranch) { thenBranch->traverse(vis); }
  if (elseBranch) { elseBranch->traverse(vis); }
  vis.postvisitStatement(this);
}

void S_switch::traverse(ASTVisitor &vis)
{
  if (!vis.visitStatement(this)) { return; }

  Statement::traverse(vis);

  if (cond) { cond->traverse(vis); }
  if (branches) { branches->traverse(vis); }
  vis.postvisitStatement(this);
}

void S_while::traverse(ASTVisitor &vis)
{
  if (!vis.visitStatement(this)) { return; }

  Statement::traverse(vis);

  if (cond) { cond->traverse(vis); }
  if (body) { body->traverse(vis); }
  vis.postvisitStatement(this);
}

void S_doWhile::traverse(ASTVisitor &vis)
{
  if (!vis.visitStatement(this)) { return; }

  Statement::traverse(vis);

  if (body) { body->traverse(vis); }
  if (expr) { expr->traverse(vis); }
  vis.postvisitStatement(this);
}

void S_for::traverse(ASTVisitor &vis)
{
  if (!vis.visitStatement(this)) { return; }

  Statement::traverse(vis);

  if (init) { init->traverse(vis); }
  if (cond) { cond->traverse(vis); }
  if (after) { after->traverse(vis); }
  if (body) { body->traverse(vis); }
  vis.postvisitStatement(this);
}

void S_break::traverse(ASTVisitor &vis)
{
  if (!vis.visitStatement(this)) { return; }

  Statement::traverse(vis);

  vis.postvisitStatement(this);
}

void S_continue::traverse(ASTVisitor &vis)
{
  if (!vis.visitStatement(this)) { return; }

  Statement::traverse(vis);

  vis.postvisitStatement(this);
}

void S_return::traverse(ASTVisitor &vis)
{
  if (!vis.visitStatement(this)) { return; }

  Statement::traverse(vis);

  if (expr) { expr->traverse(vis); }
  vis.postvisitStatement(this);
}

void S_goto::traverse(ASTVisitor &vis)
{
  if (!vis.visitStatement(this)) { return; }

  Statement::traverse(vis);

  vis.postvisitStatement(this);
}

void S_decl::traverse(ASTVisitor &vis)
{
  if (!vis.visitStatement(this)) { return; }

  Statement::traverse(vis);

  if (decl) { decl->traverse(vis); }
  vis.postvisitStatement(this);
}

void S_try::traverse(ASTVisitor &vis)
{
  if (!vis.visitStatement(this)) { return; }

  Statement::traverse(vis);

  if (body) { body->traverse(vis); }
  if (vis.visitList_S_try_handlers(handlers)) {
    FAKELIST_FOREACH_NC(Handler, handlers, iter) {
      if (vis.visitListItem_S_try_handlers(iter)) {
        iter->traverse(vis);
        vis.postvisitListItem_S_try_handlers(iter);
      }
    }
    vis.postvisitList_S_try_handlers(handlers);
  }
  vis.postvisitStatement(this);
}

void S_asm::traverse(ASTVisitor &vis)
{
  if (!vis.visitStatement(this)) { return; }

  Statement::traverse(vis);

  if (text) { text->traverse(vis); }
  vis.postvisitStatement(this);
}

void S_namespaceDecl::traverse(ASTVisitor &vis)
{
  if (!vis.visitStatement(this)) { return; }

  Statement::traverse(vis);

  if (decl) { decl->traverse(vis); }
  vis.postvisitStatement(this);
}

void S_function::traverse(ASTVisitor &vis)
{
  if (!vis.visitStatement(this)) { return; }

  Statement::traverse(vis);

  if (f) { f->traverse(vis); }
  vis.postvisitStatement(this);
}

void S_rangeCase::traverse(ASTVisitor &vis)
{
  if (!vis.visitStatement(this)) { return; }

  Statement::traverse(vis);

  if (exprLo) { exprLo->traverse(vis); }
  if (exprHi) { exprHi->traverse(vis); }
  if (s) { s->traverse(vis); }
  vis.postvisitStatement(this);
}

void S_computedGoto::traverse(ASTVisitor &vis)
{
  if (!vis.visitStatement(this)) { return; }

  Statement::traverse(vis);

  if (target) { target->traverse(vis); }
  vis.postvisitStatement(this);
}

void Condition::traverse(ASTVisitor &vis)
{
  // no 'visit' because it's handled by subclasses

   if (ambiguity) ambiguity->traverse(vis); ;
  // no 'postvisit' either
}

void CN_expr::traverse(ASTVisitor &vis)
{
  if (!vis.visitCondition(this)) { return; }

  Condition::traverse(vis);

  if (expr) { expr->traverse(vis); }
  vis.postvisitCondition(this);
}

void CN_decl::traverse(ASTVisitor &vis)
{
  if (!vis.visitCondition(this)) { return; }

  Condition::traverse(vis);

  if (typeId) { typeId->traverse(vis); }
  vis.postvisitCondition(this);
}

void Handler::traverse(ASTVisitor &vis)
{
  if (!vis.visitHandler(this)) { return; }

  if (typeId) { typeId->traverse(vis); }
  if (body) { body->traverse(vis); }
  vis.postvisitHandler(this);
}

void Expression::traverse(ASTVisitor &vis)
{
  // no 'visit' because it's handled by subclasses

   if (ambiguity) ambiguity->traverse(vis); ;
  // no 'postvisit' either
}

void E_boolLit::traverse(ASTVisitor &vis)
{
  if (!vis.visitExpression(this)) { return; }

  Expression::traverse(vis);

  vis.postvisitExpression(this);
}

void E_intLit::traverse(ASTVisitor &vis)
{
  if (!vis.visitExpression(this)) { return; }

  Expression::traverse(vis);

  vis.postvisitExpression(this);
}

void E_floatLit::traverse(ASTVisitor &vis)
{
  if (!vis.visitExpression(this)) { return; }

  Expression::traverse(vis);

  vis.postvisitExpression(this);
}

void E_stringLit::traverse(ASTVisitor &vis)
{
  if (!vis.visitExpression(this)) { return; }

  Expression::traverse(vis);

  if (continuation) { continuation->traverse(vis); }
  vis.postvisitExpression(this);
}

void E_charLit::traverse(ASTVisitor &vis)
{
  if (!vis.visitExpression(this)) { return; }

  Expression::traverse(vis);

  vis.postvisitExpression(this);
}

void E_this::traverse(ASTVisitor &vis)
{
  if (!vis.visitExpression(this)) { return; }

  Expression::traverse(vis);

  vis.postvisitExpression(this);
}

void E_variable::traverse(ASTVisitor &vis)
{
  if (!vis.visitExpression(this)) { return; }

  Expression::traverse(vis);

  if (name) { name->traverse(vis); }
  vis.postvisitExpression(this);
}

void E_funCall::traverse(ASTVisitor &vis)
{
  if (!vis.visitExpression(this)) { return; }

  Expression::traverse(vis);

  if (func) { func->traverse(vis); }
  if (vis.visitList_E_funCall_args(args)) {
    FAKELIST_FOREACH_NC(ArgExpression, args, iter) {
      if (vis.visitListItem_E_funCall_args(iter)) {
        iter->traverse(vis);
        vis.postvisitListItem_E_funCall_args(iter);
      }
    }
    vis.postvisitList_E_funCall_args(args);
  }
  vis.postvisitExpression(this);
}

void E_constructor::traverse(ASTVisitor &vis)
{
  if (!vis.visitExpression(this)) { return; }

  Expression::traverse(vis);

  if (spec) { spec->traverse(vis); }
  if (vis.visitList_E_constructor_args(args)) {
    FAKELIST_FOREACH_NC(ArgExpression, args, iter) {
      if (vis.visitListItem_E_constructor_args(iter)) {
        iter->traverse(vis);
        vis.postvisitListItem_E_constructor_args(iter);
      }
    }
    vis.postvisitList_E_constructor_args(args);
  }
  vis.postvisitExpression(this);
}

void E_fieldAcc::traverse(ASTVisitor &vis)
{
  if (!vis.visitExpression(this)) { return; }

  Expression::traverse(vis);

  if (obj) { obj->traverse(vis); }
  if (fieldName) { fieldName->traverse(vis); }
  vis.postvisitExpression(this);
}

void E_sizeof::traverse(ASTVisitor &vis)
{
  if (!vis.visitExpression(this)) { return; }

  Expression::traverse(vis);

  if (expr) { expr->traverse(vis); }
  vis.postvisitExpression(this);
}

void E_unary::traverse(ASTVisitor &vis)
{
  if (!vis.visitExpression(this)) { return; }

  Expression::traverse(vis);

  if (expr) { expr->traverse(vis); }
  vis.postvisitExpression(this);
}

void E_effect::traverse(ASTVisitor &vis)
{
  if (!vis.visitExpression(this)) { return; }

  Expression::traverse(vis);

  if (expr) { expr->traverse(vis); }
  vis.postvisitExpression(this);
}

void E_binary::traverse(ASTVisitor &vis)
{
  if (!vis.visitExpression(this)) { return; }

  Expression::traverse(vis);

  if (e1) { e1->traverse(vis); }
  if (e2) { e2->traverse(vis); }
  vis.postvisitExpression(this);
}

void E_addrOf::traverse(ASTVisitor &vis)
{
  if (!vis.visitExpression(this)) { return; }

  Expression::traverse(vis);

  if (expr) { expr->traverse(vis); }
  vis.postvisitExpression(this);
}

void E_deref::traverse(ASTVisitor &vis)
{
  if (!vis.visitExpression(this)) { return; }

  Expression::traverse(vis);

  if (ptr) { ptr->traverse(vis); }
  vis.postvisitExpression(this);
}

void E_cast::traverse(ASTVisitor &vis)
{
  if (!vis.visitExpression(this)) { return; }

  Expression::traverse(vis);

  if (ctype) { ctype->traverse(vis); }
  if (expr) { expr->traverse(vis); }
  vis.postvisitExpression(this);
}

void E_cond::traverse(ASTVisitor &vis)
{
  if (!vis.visitExpression(this)) { return; }

  Expression::traverse(vis);

  if (cond) { cond->traverse(vis); }
  if (th) { th->traverse(vis); }
  if (el) { el->traverse(vis); }
  vis.postvisitExpression(this);
}

void E_sizeofType::traverse(ASTVisitor &vis)
{
  if (!vis.visitExpression(this)) { return; }

  Expression::traverse(vis);

  if (atype) { atype->traverse(vis); }
  vis.postvisitExpression(this);
}

void E_assign::traverse(ASTVisitor &vis)
{
  if (!vis.visitExpression(this)) { return; }

  Expression::traverse(vis);

  if (target) { target->traverse(vis); }
  if (src) { src->traverse(vis); }
  vis.postvisitExpression(this);
}

void E_new::traverse(ASTVisitor &vis)
{
  if (!vis.visitExpression(this)) { return; }

  Expression::traverse(vis);

  if (vis.visitList_E_new_placementArgs(placementArgs)) {
    FAKELIST_FOREACH_NC(ArgExpression, placementArgs, iter) {
      if (vis.visitListItem_E_new_placementArgs(iter)) {
        iter->traverse(vis);
        vis.postvisitListItem_E_new_placementArgs(iter);
      }
    }
    vis.postvisitList_E_new_placementArgs(placementArgs);
  }
  if (atype) { atype->traverse(vis); }
  if (ctorArgs) { ctorArgs->traverse(vis); }
  vis.postvisitExpression(this);
}

void E_delete::traverse(ASTVisitor &vis)
{
  if (!vis.visitExpression(this)) { return; }

  Expression::traverse(vis);

  if (expr) { expr->traverse(vis); }
  vis.postvisitExpression(this);
}

void E_throw::traverse(ASTVisitor &vis)
{
  if (!vis.visitExpression(this)) { return; }

  Expression::traverse(vis);

  if (expr) { expr->traverse(vis); }
  vis.postvisitExpression(this);
}

void E_keywordCast::traverse(ASTVisitor &vis)
{
  if (!vis.visitExpression(this)) { return; }

  Expression::traverse(vis);

  if (ctype) { ctype->traverse(vis); }
  if (expr) { expr->traverse(vis); }
  vis.postvisitExpression(this);
}

void E_typeidExpr::traverse(ASTVisitor &vis)
{
  if (!vis.visitExpression(this)) { return; }

  Expression::traverse(vis);

  if (expr) { expr->traverse(vis); }
  vis.postvisitExpression(this);
}

void E_typeidType::traverse(ASTVisitor &vis)
{
  if (!vis.visitExpression(this)) { return; }

  Expression::traverse(vis);

  if (ttype) { ttype->traverse(vis); }
  vis.postvisitExpression(this);
}

void E_grouping::traverse(ASTVisitor &vis)
{
  if (!vis.visitExpression(this)) { return; }

  Expression::traverse(vis);

  if (expr) { expr->traverse(vis); }
  vis.postvisitExpression(this);
}

void E_arrow::traverse(ASTVisitor &vis)
{
  if (!vis.visitExpression(this)) { return; }

  Expression::traverse(vis);

  if (obj) { obj->traverse(vis); }
  if (fieldName) { fieldName->traverse(vis); }
  vis.postvisitExpression(this);
}

void E_statement::traverse(ASTVisitor &vis)
{
  if (!vis.visitExpression(this)) { return; }

  Expression::traverse(vis);

  if (s) { s->traverse(vis); }
  vis.postvisitExpression(this);
}

void E_compoundLit::traverse(ASTVisitor &vis)
{
  if (!vis.visitExpression(this)) { return; }

  Expression::traverse(vis);

  if (stype) { stype->traverse(vis); }
  if (init) { init->traverse(vis); }
  vis.postvisitExpression(this);
}

void E___builtin_constant_p::traverse(ASTVisitor &vis)
{
  if (!vis.visitExpression(this)) { return; }

  Expression::traverse(vis);

  if (expr) { expr->traverse(vis); }
  vis.postvisitExpression(this);
}

void E___builtin_va_arg::traverse(ASTVisitor &vis)
{
  if (!vis.visitExpression(this)) { return; }

  Expression::traverse(vis);

  if (expr) { expr->traverse(vis); }
  if (atype) { atype->traverse(vis); }
  vis.postvisitExpression(this);
}

void E_alignofType::traverse(ASTVisitor &vis)
{
  if (!vis.visitExpression(this)) { return; }

  Expression::traverse(vis);

  if (atype) { atype->traverse(vis); }
  vis.postvisitExpression(this);
}

void E_alignofExpr::traverse(ASTVisitor &vis)
{
  if (!vis.visitExpression(this)) { return; }

  Expression::traverse(vis);

  if (expr) { expr->traverse(vis); }
  vis.postvisitExpression(this);
}

void E_gnuCond::traverse(ASTVisitor &vis)
{
  if (!vis.visitExpression(this)) { return; }

  Expression::traverse(vis);

  if (cond) { cond->traverse(vis); }
  if (el) { el->traverse(vis); }
  vis.postvisitExpression(this);
}

void E_addrOfLabel::traverse(ASTVisitor &vis)
{
  if (!vis.visitExpression(this)) { return; }

  Expression::traverse(vis);

  vis.postvisitExpression(this);
}

void FullExpression::traverse(ASTVisitor &vis)
{
  if (!vis.visitFullExpression(this)) { return; }

  if (expr) { expr->traverse(vis); }
  vis.postvisitFullExpression(this);
}

void ArgExpression::traverse(ASTVisitor &vis)
{
  if (!vis.visitArgExpression(this)) { return; }

  if (expr) { expr->traverse(vis); }
   if (ambiguity) ambiguity->traverse(vis); ;
  vis.postvisitArgExpression(this);
}

void ArgExpressionListOpt::traverse(ASTVisitor &vis)
{
  if (!vis.visitArgExpressionListOpt(this)) { return; }

  if (vis.visitList_ArgExpressionListOpt_list(list)) {
    FAKELIST_FOREACH_NC(ArgExpression, list, iter) {
      if (vis.visitListItem_ArgExpressionListOpt_list(iter)) {
        iter->traverse(vis);
        vis.postvisitListItem_ArgExpressionListOpt_list(iter);
      }
    }
    vis.postvisitList_ArgExpressionListOpt_list(list);
  }
  vis.postvisitArgExpressionListOpt(this);
}

void Initializer::traverse(ASTVisitor &vis)
{
  // no 'visit' because it's handled by subclasses

  // no 'postvisit' either
}

void IN_expr::traverse(ASTVisitor &vis)
{
  if (!vis.visitInitializer(this)) { return; }

  Initializer::traverse(vis);

  if (e) { e->traverse(vis); }
  vis.postvisitInitializer(this);
}

void IN_compound::traverse(ASTVisitor &vis)
{
  if (!vis.visitInitializer(this)) { return; }

  Initializer::traverse(vis);

  if (vis.visitList_IN_compound_inits(&inits)) {
    FOREACH_ASTLIST_NC(Initializer, inits, iter) {
      if (vis.visitListItem_IN_compound_inits(iter.data())) {
        iter.data()->traverse(vis);
        vis.postvisitListItem_IN_compound_inits(iter.data());
      }
    }
    vis.postvisitList_IN_compound_inits(&inits);
  }
  vis.postvisitInitializer(this);
}

void IN_ctor::traverse(ASTVisitor &vis)
{
  if (!vis.visitInitializer(this)) { return; }

  Initializer::traverse(vis);

  if (vis.visitList_IN_ctor_args(args)) {
    FAKELIST_FOREACH_NC(ArgExpression, args, iter) {
      if (vis.visitListItem_IN_ctor_args(iter)) {
        iter->traverse(vis);
        vis.postvisitListItem_IN_ctor_args(iter);
      }
    }
    vis.postvisitList_IN_ctor_args(args);
  }
  vis.postvisitInitializer(this);
}

void IN_designated::traverse(ASTVisitor &vis)
{
  if (!vis.visitInitializer(this)) { return; }

  Initializer::traverse(vis);

  if (vis.visitList_IN_designated_designator_list(designator_list)) {
    FAKELIST_FOREACH_NC(Designator, designator_list, iter) {
      if (vis.visitListItem_IN_designated_designator_list(iter)) {
        iter->traverse(vis);
        vis.postvisitListItem_IN_designated_designator_list(iter);
      }
    }
    vis.postvisitList_IN_designated_designator_list(designator_list);
  }
  if (init) { init->traverse(vis); }
  vis.postvisitInitializer(this);
}

void TemplateDeclaration::traverse(ASTVisitor &vis)
{
  // no 'visit' because it's handled by subclasses

  if (params) { params->traverse(vis); }
  // no 'postvisit' either
}

void TD_func::traverse(ASTVisitor &vis)
{
  
         // we are now in a template if we already were, or if this
         // declaration is not a complete specialization
         Restorer<bool> r(vis.inTemplate, vis.inTemplate || params!=NULL);
       ;
  if (!vis.visitTemplateDeclaration(this)) { return; }

  TemplateDeclaration::traverse(vis);

  if (f) { f->traverse(vis); }
  vis.postvisitTemplateDeclaration(this);
}

void TD_decl::traverse(ASTVisitor &vis)
{
  
         Restorer<bool> r(vis.inTemplate, vis.inTemplate || params!=NULL);
       ;
  if (!vis.visitTemplateDeclaration(this)) { return; }

  TemplateDeclaration::traverse(vis);

  if (d) { d->traverse(vis); }
  vis.postvisitTemplateDeclaration(this);
}

void TD_tmember::traverse(ASTVisitor &vis)
{
  
         Restorer<bool> r(vis.inTemplate, vis.inTemplate || params!=NULL);
       ;
  if (!vis.visitTemplateDeclaration(this)) { return; }

  TemplateDeclaration::traverse(vis);

  if (d) { d->traverse(vis); }
  vis.postvisitTemplateDeclaration(this);
}

void TemplateParameter::traverse(ASTVisitor &vis)
{
  // no 'visit' because it's handled by subclasses

   if (ambiguity) ambiguity->traverse(vis); ;
  if (next) { next->traverse(vis); }
  // no 'postvisit' either
}

void TP_type::traverse(ASTVisitor &vis)
{
  if (!vis.visitTemplateParameter(this)) { return; }

  TemplateParameter::traverse(vis);

  if (defaultType) { defaultType->traverse(vis); }
  vis.postvisitTemplateParameter(this);
}

void TP_nontype::traverse(ASTVisitor &vis)
{
  if (!vis.visitTemplateParameter(this)) { return; }

  TemplateParameter::traverse(vis);

  if (param) { param->traverse(vis); }
  vis.postvisitTemplateParameter(this);
}

void TP_template::traverse(ASTVisitor &vis)
{
  if (!vis.visitTemplateParameter(this)) { return; }

  TemplateParameter::traverse(vis);

  if (vis.visitList_TP_template_parameters(parameters)) {
    FAKELIST_FOREACH_NC(TemplateParameter, parameters, iter) {
      if (vis.visitListItem_TP_template_parameters(iter)) {
        iter->traverse(vis);
        vis.postvisitListItem_TP_template_parameters(iter);
      }
    }
    vis.postvisitList_TP_template_parameters(parameters);
  }
  if (defaultTemplate) { defaultTemplate->traverse(vis); }
  vis.postvisitTemplateParameter(this);
}

void TemplateArgument::traverse(ASTVisitor &vis)
{
  // no 'visit' because it's handled by subclasses

   if (ambiguity) ambiguity->traverse(vis); ;
  if (next) { next->traverse(vis); }
  // no 'postvisit' either
}

void TA_type::traverse(ASTVisitor &vis)
{
  if (!vis.visitTemplateArgument(this)) { return; }

  TemplateArgument::traverse(vis);

  if (type) { type->traverse(vis); }
  vis.postvisitTemplateArgument(this);
}

void TA_nontype::traverse(ASTVisitor &vis)
{
  if (!vis.visitTemplateArgument(this)) { return; }

  TemplateArgument::traverse(vis);

  if (expr) { expr->traverse(vis); }
  vis.postvisitTemplateArgument(this);
}

void TA_templateUsed::traverse(ASTVisitor &vis)
{
  if (!vis.visitTemplateArgument(this)) { return; }

  TemplateArgument::traverse(vis);

  vis.postvisitTemplateArgument(this);
}

void NamespaceDecl::traverse(ASTVisitor &vis)
{
  // no 'visit' because it's handled by subclasses

  // no 'postvisit' either
}

void ND_alias::traverse(ASTVisitor &vis)
{
  if (!vis.visitNamespaceDecl(this)) { return; }

  NamespaceDecl::traverse(vis);

  if (original) { original->traverse(vis); }
  vis.postvisitNamespaceDecl(this);
}

void ND_usingDecl::traverse(ASTVisitor &vis)
{
  if (!vis.visitNamespaceDecl(this)) { return; }

  NamespaceDecl::traverse(vis);

  if (name) { name->traverse(vis); }
  vis.postvisitNamespaceDecl(this);
}

void ND_usingDir::traverse(ASTVisitor &vis)
{
  if (!vis.visitNamespaceDecl(this)) { return; }

  NamespaceDecl::traverse(vis);

  if (name) { name->traverse(vis); }
  vis.postvisitNamespaceDecl(this);
}

void FullExpressionAnnot::traverse(ASTVisitor &vis)
{
  if (!vis.visitFullExpressionAnnot(this)) { return; }

  if (vis.visitList_FullExpressionAnnot_declarations(&declarations)) {
    FOREACH_ASTLIST_NC(Declaration, declarations, iter) {
      if (vis.visitListItem_FullExpressionAnnot_declarations(iter.data())) {
        iter.data()->traverse(vis);
        vis.postvisitListItem_FullExpressionAnnot_declarations(iter.data());
      }
    }
    vis.postvisitList_FullExpressionAnnot_declarations(&declarations);
  }
  vis.postvisitFullExpressionAnnot(this);
}

void ASTTypeof::traverse(ASTVisitor &vis)
{
  // no 'visit' because it's handled by subclasses

   if (ambiguity) ambiguity->traverse(vis); ;
  // no 'postvisit' either
}

void TS_typeof_expr::traverse(ASTVisitor &vis)
{
  if (!vis.visitASTTypeof(this)) { return; }

  ASTTypeof::traverse(vis);

  if (expr) { expr->traverse(vis); }
  vis.postvisitASTTypeof(this);
}

void TS_typeof_type::traverse(ASTVisitor &vis)
{
  if (!vis.visitASTTypeof(this)) { return; }

  ASTTypeof::traverse(vis);

  if (atype) { atype->traverse(vis); }
  vis.postvisitASTTypeof(this);
}

void Designator::traverse(ASTVisitor &vis)
{
  // no 'visit' because it's handled by subclasses

   if (ambiguity) ambiguity->traverse(vis); ;
  // no 'postvisit' either
}

void FieldDesignator::traverse(ASTVisitor &vis)
{
  if (!vis.visitDesignator(this)) { return; }

  Designator::traverse(vis);

  vis.postvisitDesignator(this);
}

void SubscriptDesignator::traverse(ASTVisitor &vis)
{
  if (!vis.visitDesignator(this)) { return; }

  Designator::traverse(vis);

  if (idx_expr) { idx_expr->traverse(vis); }
  if (idx_expr2) { idx_expr2->traverse(vis); }
  vis.postvisitDesignator(this);
}

void AttributeSpecifierList::traverse(ASTVisitor &vis)
{
  if (!vis.visitAttributeSpecifierList(this)) { return; }

  if (spec) { spec->traverse(vis); }
  if (next) { next->traverse(vis); }
  vis.postvisitAttributeSpecifierList(this);
}

void AttributeSpecifier::traverse(ASTVisitor &vis)
{
  if (!vis.visitAttributeSpecifier(this)) { return; }

  if (attr) { attr->traverse(vis); }
  if (next) { next->traverse(vis); }
  vis.postvisitAttributeSpecifier(this);
}

void Attribute::traverse(ASTVisitor &vis)
{
  // no 'visit' because it's handled by subclasses

  // no 'postvisit' either
}

void AT_empty::traverse(ASTVisitor &vis)
{
  if (!vis.visitAttribute(this)) { return; }

  Attribute::traverse(vis);

  vis.postvisitAttribute(this);
}

void AT_word::traverse(ASTVisitor &vis)
{
  if (!vis.visitAttribute(this)) { return; }

  Attribute::traverse(vis);

  vis.postvisitAttribute(this);
}

void AT_func::traverse(ASTVisitor &vis)
{
  if (!vis.visitAttribute(this)) { return; }

  Attribute::traverse(vis);

  if (vis.visitList_AT_func_args(args)) {
    FAKELIST_FOREACH_NC(ArgExpression, args, iter) {
      if (vis.visitListItem_AT_func_args(iter)) {
        iter->traverse(vis);
        vis.postvisitListItem_AT_func_args(iter);
      }
    }
    vis.postvisitList_AT_func_args(args);
  }
  vis.postvisitAttribute(this);
}


// ---------------------- DelegatorASTVisitor ---------------------
bool DelegatorASTVisitor::wasVisitedAST(void *ast)
{
  if (!ast) {return false;} // avoid NULL; actually happens for FakeLists
  if (wasVisitedASTNodes.contains(ast)) {
    return true;
  } else {
    wasVisitedASTNodes.add(ast);
    return false;
  }
}

bool DelegatorASTVisitor::wasVisitedList_ASTList(void *ast)
{
  if (!ast) {return false;} // avoid NULL; actually happens for FakeLists
  if (wasVisitedList_ASTListNodes.contains(ast)) {
    return true;
  } else {
    wasVisitedList_ASTListNodes.add(ast);
    return false;
  }
}

bool DelegatorASTVisitor::wasVisitedList_FakeList(void *ast)
{
  if (!ast) {return false;} // avoid NULL; actually happens for FakeLists
  if (wasVisitedList_FakeListNodes.contains(ast)) {
    return true;
  } else {
    wasVisitedList_FakeListNodes.add(ast);
    return false;
  }
}

// default no-op delegator-visitor
bool DelegatorASTVisitor::visitTranslationUnit(TranslationUnit *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitTranslationUnit(obj) : true;
}
void DelegatorASTVisitor::postvisitTranslationUnit(TranslationUnit *obj) {
  if (client) {
    client->postvisitTranslationUnit(obj);
  }
}
bool DelegatorASTVisitor::visitTopForm(TopForm *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitTopForm(obj) : true;
}
void DelegatorASTVisitor::postvisitTopForm(TopForm *obj) {
  if (client) {
    client->postvisitTopForm(obj);
  }
}
bool DelegatorASTVisitor::visitFunction(Function *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitFunction(obj) : true;
}
void DelegatorASTVisitor::postvisitFunction(Function *obj) {
  if (client) {
    client->postvisitFunction(obj);
  }
}
bool DelegatorASTVisitor::visitMemberInit(MemberInit *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitMemberInit(obj) : true;
}
void DelegatorASTVisitor::postvisitMemberInit(MemberInit *obj) {
  if (client) {
    client->postvisitMemberInit(obj);
  }
}
bool DelegatorASTVisitor::visitDeclaration(Declaration *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitDeclaration(obj) : true;
}
void DelegatorASTVisitor::postvisitDeclaration(Declaration *obj) {
  if (client) {
    client->postvisitDeclaration(obj);
  }
}
bool DelegatorASTVisitor::visitASTTypeId(ASTTypeId *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitASTTypeId(obj) : true;
}
void DelegatorASTVisitor::postvisitASTTypeId(ASTTypeId *obj) {
  if (client) {
    client->postvisitASTTypeId(obj);
  }
}
bool DelegatorASTVisitor::visitPQName(PQName *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitPQName(obj) : true;
}
void DelegatorASTVisitor::postvisitPQName(PQName *obj) {
  if (client) {
    client->postvisitPQName(obj);
  }
}
bool DelegatorASTVisitor::visitTypeSpecifier(TypeSpecifier *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitTypeSpecifier(obj) : true;
}
void DelegatorASTVisitor::postvisitTypeSpecifier(TypeSpecifier *obj) {
  if (client) {
    client->postvisitTypeSpecifier(obj);
  }
}
bool DelegatorASTVisitor::visitBaseClassSpec(BaseClassSpec *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitBaseClassSpec(obj) : true;
}
void DelegatorASTVisitor::postvisitBaseClassSpec(BaseClassSpec *obj) {
  if (client) {
    client->postvisitBaseClassSpec(obj);
  }
}
bool DelegatorASTVisitor::visitEnumerator(Enumerator *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitEnumerator(obj) : true;
}
void DelegatorASTVisitor::postvisitEnumerator(Enumerator *obj) {
  if (client) {
    client->postvisitEnumerator(obj);
  }
}
bool DelegatorASTVisitor::visitMemberList(MemberList *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitMemberList(obj) : true;
}
void DelegatorASTVisitor::postvisitMemberList(MemberList *obj) {
  if (client) {
    client->postvisitMemberList(obj);
  }
}
bool DelegatorASTVisitor::visitMember(Member *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitMember(obj) : true;
}
void DelegatorASTVisitor::postvisitMember(Member *obj) {
  if (client) {
    client->postvisitMember(obj);
  }
}
bool DelegatorASTVisitor::visitDeclarator(Declarator *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitDeclarator(obj) : true;
}
void DelegatorASTVisitor::postvisitDeclarator(Declarator *obj) {
  if (client) {
    client->postvisitDeclarator(obj);
  }
}
bool DelegatorASTVisitor::visitIDeclarator(IDeclarator *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitIDeclarator(obj) : true;
}
void DelegatorASTVisitor::postvisitIDeclarator(IDeclarator *obj) {
  if (client) {
    client->postvisitIDeclarator(obj);
  }
}
bool DelegatorASTVisitor::visitExceptionSpec(ExceptionSpec *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitExceptionSpec(obj) : true;
}
void DelegatorASTVisitor::postvisitExceptionSpec(ExceptionSpec *obj) {
  if (client) {
    client->postvisitExceptionSpec(obj);
  }
}
bool DelegatorASTVisitor::visitOperatorName(OperatorName *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitOperatorName(obj) : true;
}
void DelegatorASTVisitor::postvisitOperatorName(OperatorName *obj) {
  if (client) {
    client->postvisitOperatorName(obj);
  }
}
bool DelegatorASTVisitor::visitStatement(Statement *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitStatement(obj) : true;
}
void DelegatorASTVisitor::postvisitStatement(Statement *obj) {
  if (client) {
    client->postvisitStatement(obj);
  }
}
bool DelegatorASTVisitor::visitCondition(Condition *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitCondition(obj) : true;
}
void DelegatorASTVisitor::postvisitCondition(Condition *obj) {
  if (client) {
    client->postvisitCondition(obj);
  }
}
bool DelegatorASTVisitor::visitHandler(Handler *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitHandler(obj) : true;
}
void DelegatorASTVisitor::postvisitHandler(Handler *obj) {
  if (client) {
    client->postvisitHandler(obj);
  }
}
bool DelegatorASTVisitor::visitExpression(Expression *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitExpression(obj) : true;
}
void DelegatorASTVisitor::postvisitExpression(Expression *obj) {
  if (client) {
    client->postvisitExpression(obj);
  }
}
bool DelegatorASTVisitor::visitFullExpression(FullExpression *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitFullExpression(obj) : true;
}
void DelegatorASTVisitor::postvisitFullExpression(FullExpression *obj) {
  if (client) {
    client->postvisitFullExpression(obj);
  }
}
bool DelegatorASTVisitor::visitArgExpression(ArgExpression *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitArgExpression(obj) : true;
}
void DelegatorASTVisitor::postvisitArgExpression(ArgExpression *obj) {
  if (client) {
    client->postvisitArgExpression(obj);
  }
}
bool DelegatorASTVisitor::visitArgExpressionListOpt(ArgExpressionListOpt *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitArgExpressionListOpt(obj) : true;
}
void DelegatorASTVisitor::postvisitArgExpressionListOpt(ArgExpressionListOpt *obj) {
  if (client) {
    client->postvisitArgExpressionListOpt(obj);
  }
}
bool DelegatorASTVisitor::visitInitializer(Initializer *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitInitializer(obj) : true;
}
void DelegatorASTVisitor::postvisitInitializer(Initializer *obj) {
  if (client) {
    client->postvisitInitializer(obj);
  }
}
bool DelegatorASTVisitor::visitTemplateDeclaration(TemplateDeclaration *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitTemplateDeclaration(obj) : true;
}
void DelegatorASTVisitor::postvisitTemplateDeclaration(TemplateDeclaration *obj) {
  if (client) {
    client->postvisitTemplateDeclaration(obj);
  }
}
bool DelegatorASTVisitor::visitTemplateParameter(TemplateParameter *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitTemplateParameter(obj) : true;
}
void DelegatorASTVisitor::postvisitTemplateParameter(TemplateParameter *obj) {
  if (client) {
    client->postvisitTemplateParameter(obj);
  }
}
bool DelegatorASTVisitor::visitTemplateArgument(TemplateArgument *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitTemplateArgument(obj) : true;
}
void DelegatorASTVisitor::postvisitTemplateArgument(TemplateArgument *obj) {
  if (client) {
    client->postvisitTemplateArgument(obj);
  }
}
bool DelegatorASTVisitor::visitNamespaceDecl(NamespaceDecl *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitNamespaceDecl(obj) : true;
}
void DelegatorASTVisitor::postvisitNamespaceDecl(NamespaceDecl *obj) {
  if (client) {
    client->postvisitNamespaceDecl(obj);
  }
}
bool DelegatorASTVisitor::visitFullExpressionAnnot(FullExpressionAnnot *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitFullExpressionAnnot(obj) : true;
}
void DelegatorASTVisitor::postvisitFullExpressionAnnot(FullExpressionAnnot *obj) {
  if (client) {
    client->postvisitFullExpressionAnnot(obj);
  }
}
bool DelegatorASTVisitor::visitASTTypeof(ASTTypeof *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitASTTypeof(obj) : true;
}
void DelegatorASTVisitor::postvisitASTTypeof(ASTTypeof *obj) {
  if (client) {
    client->postvisitASTTypeof(obj);
  }
}
bool DelegatorASTVisitor::visitDesignator(Designator *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitDesignator(obj) : true;
}
void DelegatorASTVisitor::postvisitDesignator(Designator *obj) {
  if (client) {
    client->postvisitDesignator(obj);
  }
}
bool DelegatorASTVisitor::visitAttributeSpecifierList(AttributeSpecifierList *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitAttributeSpecifierList(obj) : true;
}
void DelegatorASTVisitor::postvisitAttributeSpecifierList(AttributeSpecifierList *obj) {
  if (client) {
    client->postvisitAttributeSpecifierList(obj);
  }
}
bool DelegatorASTVisitor::visitAttributeSpecifier(AttributeSpecifier *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitAttributeSpecifier(obj) : true;
}
void DelegatorASTVisitor::postvisitAttributeSpecifier(AttributeSpecifier *obj) {
  if (client) {
    client->postvisitAttributeSpecifier(obj);
  }
}
bool DelegatorASTVisitor::visitAttribute(Attribute *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitAttribute(obj) : true;
}
void DelegatorASTVisitor::postvisitAttribute(Attribute *obj) {
  if (client) {
    client->postvisitAttribute(obj);
  }
}

// List 'classes'
bool DelegatorASTVisitor::visitList_TranslationUnit_topForms(ASTList<TopForm>* obj) {
  if (ensureOneVisit) xassert(!wasVisitedList_ASTList(obj));
  return client ? client->visitList_TranslationUnit_topForms(obj) : true;
}
void DelegatorASTVisitor::postvisitList_TranslationUnit_topForms(ASTList<TopForm>* obj) {
  if (client) {
    client->postvisitList_TranslationUnit_topForms(obj);
  }
}
bool DelegatorASTVisitor::visitList_TF_namespaceDefn_forms(ASTList<TopForm>* obj) {
  if (ensureOneVisit) xassert(!wasVisitedList_ASTList(obj));
  return client ? client->visitList_TF_namespaceDefn_forms(obj) : true;
}
void DelegatorASTVisitor::postvisitList_TF_namespaceDefn_forms(ASTList<TopForm>* obj) {
  if (client) {
    client->postvisitList_TF_namespaceDefn_forms(obj);
  }
}
bool DelegatorASTVisitor::visitList_Function_inits(FakeList<MemberInit>* obj) {
  if (ensureOneVisit) xassert(!wasVisitedList_FakeList(obj));
  return client ? client->visitList_Function_inits(obj) : true;
}
void DelegatorASTVisitor::postvisitList_Function_inits(FakeList<MemberInit>* obj) {
  if (client) {
    client->postvisitList_Function_inits(obj);
  }
}
bool DelegatorASTVisitor::visitList_Function_handlers(FakeList<Handler>* obj) {
  if (ensureOneVisit) xassert(!wasVisitedList_FakeList(obj));
  return client ? client->visitList_Function_handlers(obj) : true;
}
void DelegatorASTVisitor::postvisitList_Function_handlers(FakeList<Handler>* obj) {
  if (client) {
    client->postvisitList_Function_handlers(obj);
  }
}
bool DelegatorASTVisitor::visitList_MemberInit_args(FakeList<ArgExpression>* obj) {
  if (ensureOneVisit) xassert(!wasVisitedList_FakeList(obj));
  return client ? client->visitList_MemberInit_args(obj) : true;
}
void DelegatorASTVisitor::postvisitList_MemberInit_args(FakeList<ArgExpression>* obj) {
  if (client) {
    client->postvisitList_MemberInit_args(obj);
  }
}
bool DelegatorASTVisitor::visitList_MemberList_list(ASTList<Member>* obj) {
  if (ensureOneVisit) xassert(!wasVisitedList_ASTList(obj));
  return client ? client->visitList_MemberList_list(obj) : true;
}
void DelegatorASTVisitor::postvisitList_MemberList_list(ASTList<Member>* obj) {
  if (client) {
    client->postvisitList_MemberList_list(obj);
  }
}
bool DelegatorASTVisitor::visitList_Declaration_decllist(FakeList<Declarator>* obj) {
  if (ensureOneVisit) xassert(!wasVisitedList_FakeList(obj));
  return client ? client->visitList_Declaration_decllist(obj) : true;
}
void DelegatorASTVisitor::postvisitList_Declaration_decllist(FakeList<Declarator>* obj) {
  if (client) {
    client->postvisitList_Declaration_decllist(obj);
  }
}
bool DelegatorASTVisitor::visitList_TS_classSpec_bases(FakeList<BaseClassSpec>* obj) {
  if (ensureOneVisit) xassert(!wasVisitedList_FakeList(obj));
  return client ? client->visitList_TS_classSpec_bases(obj) : true;
}
void DelegatorASTVisitor::postvisitList_TS_classSpec_bases(FakeList<BaseClassSpec>* obj) {
  if (client) {
    client->postvisitList_TS_classSpec_bases(obj);
  }
}
bool DelegatorASTVisitor::visitList_TS_enumSpec_elts(FakeList<Enumerator>* obj) {
  if (ensureOneVisit) xassert(!wasVisitedList_FakeList(obj));
  return client ? client->visitList_TS_enumSpec_elts(obj) : true;
}
void DelegatorASTVisitor::postvisitList_TS_enumSpec_elts(FakeList<Enumerator>* obj) {
  if (client) {
    client->postvisitList_TS_enumSpec_elts(obj);
  }
}
bool DelegatorASTVisitor::visitList_D_func_params(FakeList<ASTTypeId>* obj) {
  if (ensureOneVisit) xassert(!wasVisitedList_FakeList(obj));
  return client ? client->visitList_D_func_params(obj) : true;
}
void DelegatorASTVisitor::postvisitList_D_func_params(FakeList<ASTTypeId>* obj) {
  if (client) {
    client->postvisitList_D_func_params(obj);
  }
}
bool DelegatorASTVisitor::visitList_D_func_kAndR_params(FakeList<PQ_name>* obj) {
  if (ensureOneVisit) xassert(!wasVisitedList_FakeList(obj));
  return client ? client->visitList_D_func_kAndR_params(obj) : true;
}
void DelegatorASTVisitor::postvisitList_D_func_kAndR_params(FakeList<PQ_name>* obj) {
  if (client) {
    client->postvisitList_D_func_kAndR_params(obj);
  }
}
bool DelegatorASTVisitor::visitList_S_try_handlers(FakeList<Handler>* obj) {
  if (ensureOneVisit) xassert(!wasVisitedList_FakeList(obj));
  return client ? client->visitList_S_try_handlers(obj) : true;
}
void DelegatorASTVisitor::postvisitList_S_try_handlers(FakeList<Handler>* obj) {
  if (client) {
    client->postvisitList_S_try_handlers(obj);
  }
}
bool DelegatorASTVisitor::visitList_ExceptionSpec_types(FakeList<ASTTypeId>* obj) {
  if (ensureOneVisit) xassert(!wasVisitedList_FakeList(obj));
  return client ? client->visitList_ExceptionSpec_types(obj) : true;
}
void DelegatorASTVisitor::postvisitList_ExceptionSpec_types(FakeList<ASTTypeId>* obj) {
  if (client) {
    client->postvisitList_ExceptionSpec_types(obj);
  }
}
bool DelegatorASTVisitor::visitList_S_compound_stmts(ASTList<Statement>* obj) {
  if (ensureOneVisit) xassert(!wasVisitedList_ASTList(obj));
  return client ? client->visitList_S_compound_stmts(obj) : true;
}
void DelegatorASTVisitor::postvisitList_S_compound_stmts(ASTList<Statement>* obj) {
  if (client) {
    client->postvisitList_S_compound_stmts(obj);
  }
}
bool DelegatorASTVisitor::visitList_E_funCall_args(FakeList<ArgExpression>* obj) {
  if (ensureOneVisit) xassert(!wasVisitedList_FakeList(obj));
  return client ? client->visitList_E_funCall_args(obj) : true;
}
void DelegatorASTVisitor::postvisitList_E_funCall_args(FakeList<ArgExpression>* obj) {
  if (client) {
    client->postvisitList_E_funCall_args(obj);
  }
}
bool DelegatorASTVisitor::visitList_E_constructor_args(FakeList<ArgExpression>* obj) {
  if (ensureOneVisit) xassert(!wasVisitedList_FakeList(obj));
  return client ? client->visitList_E_constructor_args(obj) : true;
}
void DelegatorASTVisitor::postvisitList_E_constructor_args(FakeList<ArgExpression>* obj) {
  if (client) {
    client->postvisitList_E_constructor_args(obj);
  }
}
bool DelegatorASTVisitor::visitList_E_new_placementArgs(FakeList<ArgExpression>* obj) {
  if (ensureOneVisit) xassert(!wasVisitedList_FakeList(obj));
  return client ? client->visitList_E_new_placementArgs(obj) : true;
}
void DelegatorASTVisitor::postvisitList_E_new_placementArgs(FakeList<ArgExpression>* obj) {
  if (client) {
    client->postvisitList_E_new_placementArgs(obj);
  }
}
bool DelegatorASTVisitor::visitList_ArgExpressionListOpt_list(FakeList<ArgExpression>* obj) {
  if (ensureOneVisit) xassert(!wasVisitedList_FakeList(obj));
  return client ? client->visitList_ArgExpressionListOpt_list(obj) : true;
}
void DelegatorASTVisitor::postvisitList_ArgExpressionListOpt_list(FakeList<ArgExpression>* obj) {
  if (client) {
    client->postvisitList_ArgExpressionListOpt_list(obj);
  }
}
bool DelegatorASTVisitor::visitList_IN_compound_inits(ASTList<Initializer>* obj) {
  if (ensureOneVisit) xassert(!wasVisitedList_ASTList(obj));
  return client ? client->visitList_IN_compound_inits(obj) : true;
}
void DelegatorASTVisitor::postvisitList_IN_compound_inits(ASTList<Initializer>* obj) {
  if (client) {
    client->postvisitList_IN_compound_inits(obj);
  }
}
bool DelegatorASTVisitor::visitList_IN_ctor_args(FakeList<ArgExpression>* obj) {
  if (ensureOneVisit) xassert(!wasVisitedList_FakeList(obj));
  return client ? client->visitList_IN_ctor_args(obj) : true;
}
void DelegatorASTVisitor::postvisitList_IN_ctor_args(FakeList<ArgExpression>* obj) {
  if (client) {
    client->postvisitList_IN_ctor_args(obj);
  }
}
bool DelegatorASTVisitor::visitList_TP_template_parameters(FakeList<TemplateParameter>* obj) {
  if (ensureOneVisit) xassert(!wasVisitedList_FakeList(obj));
  return client ? client->visitList_TP_template_parameters(obj) : true;
}
void DelegatorASTVisitor::postvisitList_TP_template_parameters(FakeList<TemplateParameter>* obj) {
  if (client) {
    client->postvisitList_TP_template_parameters(obj);
  }
}
bool DelegatorASTVisitor::visitList_IN_designated_designator_list(FakeList<Designator>* obj) {
  if (ensureOneVisit) xassert(!wasVisitedList_FakeList(obj));
  return client ? client->visitList_IN_designated_designator_list(obj) : true;
}
void DelegatorASTVisitor::postvisitList_IN_designated_designator_list(FakeList<Designator>* obj) {
  if (client) {
    client->postvisitList_IN_designated_designator_list(obj);
  }
}
bool DelegatorASTVisitor::visitList_FullExpressionAnnot_declarations(ASTList<Declaration>* obj) {
  if (ensureOneVisit) xassert(!wasVisitedList_ASTList(obj));
  return client ? client->visitList_FullExpressionAnnot_declarations(obj) : true;
}
void DelegatorASTVisitor::postvisitList_FullExpressionAnnot_declarations(ASTList<Declaration>* obj) {
  if (client) {
    client->postvisitList_FullExpressionAnnot_declarations(obj);
  }
}
bool DelegatorASTVisitor::visitList_AT_func_args(FakeList<ArgExpression>* obj) {
  if (ensureOneVisit) xassert(!wasVisitedList_FakeList(obj));
  return client ? client->visitList_AT_func_args(obj) : true;
}
void DelegatorASTVisitor::postvisitList_AT_func_args(FakeList<ArgExpression>* obj) {
  if (client) {
    client->postvisitList_AT_func_args(obj);
  }
}
bool DelegatorASTVisitor::visitListItem_TranslationUnit_topForms(TopForm *obj) {
  return client ? client->visitListItem_TranslationUnit_topForms(obj) : true;
}
void DelegatorASTVisitor::postvisitListItem_TranslationUnit_topForms(TopForm *obj) {
  if (client) {
    client->postvisitListItem_TranslationUnit_topForms(obj);
  }
}
bool DelegatorASTVisitor::visitListItem_TF_namespaceDefn_forms(TopForm *obj) {
  return client ? client->visitListItem_TF_namespaceDefn_forms(obj) : true;
}
void DelegatorASTVisitor::postvisitListItem_TF_namespaceDefn_forms(TopForm *obj) {
  if (client) {
    client->postvisitListItem_TF_namespaceDefn_forms(obj);
  }
}
bool DelegatorASTVisitor::visitListItem_Function_inits(MemberInit *obj) {
  return client ? client->visitListItem_Function_inits(obj) : true;
}
void DelegatorASTVisitor::postvisitListItem_Function_inits(MemberInit *obj) {
  if (client) {
    client->postvisitListItem_Function_inits(obj);
  }
}
bool DelegatorASTVisitor::visitListItem_Function_handlers(Handler *obj) {
  return client ? client->visitListItem_Function_handlers(obj) : true;
}
void DelegatorASTVisitor::postvisitListItem_Function_handlers(Handler *obj) {
  if (client) {
    client->postvisitListItem_Function_handlers(obj);
  }
}
bool DelegatorASTVisitor::visitListItem_MemberInit_args(ArgExpression *obj) {
  return client ? client->visitListItem_MemberInit_args(obj) : true;
}
void DelegatorASTVisitor::postvisitListItem_MemberInit_args(ArgExpression *obj) {
  if (client) {
    client->postvisitListItem_MemberInit_args(obj);
  }
}
bool DelegatorASTVisitor::visitListItem_MemberList_list(Member *obj) {
  return client ? client->visitListItem_MemberList_list(obj) : true;
}
void DelegatorASTVisitor::postvisitListItem_MemberList_list(Member *obj) {
  if (client) {
    client->postvisitListItem_MemberList_list(obj);
  }
}
bool DelegatorASTVisitor::visitListItem_Declaration_decllist(Declarator *obj) {
  return client ? client->visitListItem_Declaration_decllist(obj) : true;
}
void DelegatorASTVisitor::postvisitListItem_Declaration_decllist(Declarator *obj) {
  if (client) {
    client->postvisitListItem_Declaration_decllist(obj);
  }
}
bool DelegatorASTVisitor::visitListItem_TS_classSpec_bases(BaseClassSpec *obj) {
  return client ? client->visitListItem_TS_classSpec_bases(obj) : true;
}
void DelegatorASTVisitor::postvisitListItem_TS_classSpec_bases(BaseClassSpec *obj) {
  if (client) {
    client->postvisitListItem_TS_classSpec_bases(obj);
  }
}
bool DelegatorASTVisitor::visitListItem_TS_enumSpec_elts(Enumerator *obj) {
  return client ? client->visitListItem_TS_enumSpec_elts(obj) : true;
}
void DelegatorASTVisitor::postvisitListItem_TS_enumSpec_elts(Enumerator *obj) {
  if (client) {
    client->postvisitListItem_TS_enumSpec_elts(obj);
  }
}
bool DelegatorASTVisitor::visitListItem_D_func_params(ASTTypeId *obj) {
  return client ? client->visitListItem_D_func_params(obj) : true;
}
void DelegatorASTVisitor::postvisitListItem_D_func_params(ASTTypeId *obj) {
  if (client) {
    client->postvisitListItem_D_func_params(obj);
  }
}
bool DelegatorASTVisitor::visitListItem_D_func_kAndR_params(PQ_name *obj) {
  return client ? client->visitListItem_D_func_kAndR_params(obj) : true;
}
void DelegatorASTVisitor::postvisitListItem_D_func_kAndR_params(PQ_name *obj) {
  if (client) {
    client->postvisitListItem_D_func_kAndR_params(obj);
  }
}
bool DelegatorASTVisitor::visitListItem_S_try_handlers(Handler *obj) {
  return client ? client->visitListItem_S_try_handlers(obj) : true;
}
void DelegatorASTVisitor::postvisitListItem_S_try_handlers(Handler *obj) {
  if (client) {
    client->postvisitListItem_S_try_handlers(obj);
  }
}
bool DelegatorASTVisitor::visitListItem_ExceptionSpec_types(ASTTypeId *obj) {
  return client ? client->visitListItem_ExceptionSpec_types(obj) : true;
}
void DelegatorASTVisitor::postvisitListItem_ExceptionSpec_types(ASTTypeId *obj) {
  if (client) {
    client->postvisitListItem_ExceptionSpec_types(obj);
  }
}
bool DelegatorASTVisitor::visitListItem_S_compound_stmts(Statement *obj) {
  return client ? client->visitListItem_S_compound_stmts(obj) : true;
}
void DelegatorASTVisitor::postvisitListItem_S_compound_stmts(Statement *obj) {
  if (client) {
    client->postvisitListItem_S_compound_stmts(obj);
  }
}
bool DelegatorASTVisitor::visitListItem_E_funCall_args(ArgExpression *obj) {
  return client ? client->visitListItem_E_funCall_args(obj) : true;
}
void DelegatorASTVisitor::postvisitListItem_E_funCall_args(ArgExpression *obj) {
  if (client) {
    client->postvisitListItem_E_funCall_args(obj);
  }
}
bool DelegatorASTVisitor::visitListItem_E_constructor_args(ArgExpression *obj) {
  return client ? client->visitListItem_E_constructor_args(obj) : true;
}
void DelegatorASTVisitor::postvisitListItem_E_constructor_args(ArgExpression *obj) {
  if (client) {
    client->postvisitListItem_E_constructor_args(obj);
  }
}
bool DelegatorASTVisitor::visitListItem_E_new_placementArgs(ArgExpression *obj) {
  return client ? client->visitListItem_E_new_placementArgs(obj) : true;
}
void DelegatorASTVisitor::postvisitListItem_E_new_placementArgs(ArgExpression *obj) {
  if (client) {
    client->postvisitListItem_E_new_placementArgs(obj);
  }
}
bool DelegatorASTVisitor::visitListItem_ArgExpressionListOpt_list(ArgExpression *obj) {
  return client ? client->visitListItem_ArgExpressionListOpt_list(obj) : true;
}
void DelegatorASTVisitor::postvisitListItem_ArgExpressionListOpt_list(ArgExpression *obj) {
  if (client) {
    client->postvisitListItem_ArgExpressionListOpt_list(obj);
  }
}
bool DelegatorASTVisitor::visitListItem_IN_compound_inits(Initializer *obj) {
  return client ? client->visitListItem_IN_compound_inits(obj) : true;
}
void DelegatorASTVisitor::postvisitListItem_IN_compound_inits(Initializer *obj) {
  if (client) {
    client->postvisitListItem_IN_compound_inits(obj);
  }
}
bool DelegatorASTVisitor::visitListItem_IN_ctor_args(ArgExpression *obj) {
  return client ? client->visitListItem_IN_ctor_args(obj) : true;
}
void DelegatorASTVisitor::postvisitListItem_IN_ctor_args(ArgExpression *obj) {
  if (client) {
    client->postvisitListItem_IN_ctor_args(obj);
  }
}
bool DelegatorASTVisitor::visitListItem_TP_template_parameters(TemplateParameter *obj) {
  return client ? client->visitListItem_TP_template_parameters(obj) : true;
}
void DelegatorASTVisitor::postvisitListItem_TP_template_parameters(TemplateParameter *obj) {
  if (client) {
    client->postvisitListItem_TP_template_parameters(obj);
  }
}
bool DelegatorASTVisitor::visitListItem_IN_designated_designator_list(Designator *obj) {
  return client ? client->visitListItem_IN_designated_designator_list(obj) : true;
}
void DelegatorASTVisitor::postvisitListItem_IN_designated_designator_list(Designator *obj) {
  if (client) {
    client->postvisitListItem_IN_designated_designator_list(obj);
  }
}
bool DelegatorASTVisitor::visitListItem_FullExpressionAnnot_declarations(Declaration *obj) {
  return client ? client->visitListItem_FullExpressionAnnot_declarations(obj) : true;
}
void DelegatorASTVisitor::postvisitListItem_FullExpressionAnnot_declarations(Declaration *obj) {
  if (client) {
    client->postvisitListItem_FullExpressionAnnot_declarations(obj);
  }
}
bool DelegatorASTVisitor::visitListItem_AT_func_args(ArgExpression *obj) {
  return client ? client->visitListItem_AT_func_args(obj) : true;
}
void DelegatorASTVisitor::postvisitListItem_AT_func_args(ArgExpression *obj) {
  if (client) {
    client->postvisitListItem_AT_func_args(obj);
  }
}


// ---------------------- XmlAstWriter_AstVisitor ---------------------
bool XmlAstWriter_AstVisitor::wasVisitedAST(void *ast)
{
  if (!ast) {return false;} // avoid NULL; actually happens for FakeLists
  if (wasVisitedASTNodes.contains(ast)) {
    return true;
  } else {
    wasVisitedASTNodes.add(ast);
    return false;
  }
}

bool XmlAstWriter_AstVisitor::wasVisitedList_ASTList(void *ast)
{
  if (!ast) {return false;} // avoid NULL; actually happens for FakeLists
  if (wasVisitedList_ASTListNodes.contains(ast)) {
    return true;
  } else {
    wasVisitedList_ASTListNodes.add(ast);
    return false;
  }
}

bool XmlAstWriter_AstVisitor::wasVisitedList_FakeList(void *ast)
{
  if (!ast) {return false;} // avoid NULL; actually happens for FakeLists
  if (wasVisitedList_FakeListNodes.contains(ast)) {
    return true;
  } else {
    wasVisitedList_FakeListNodes.add(ast);
    return false;
  }
}

void XmlAstWriter_AstVisitor::printIndentation()
{
  writeSpaces(out, depth);
}

// default xml-visitor
bool XmlAstWriter_AstVisitor::visitTranslationUnit(TranslationUnit *obj) {
  if (wasVisitedAST(obj)) return false;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << obj->kindName();
  ++depth;
  out << " _id=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  if (obj && obj->topForms.isNotEmpty()) {
    out << '\n';
    if (indent) printIndentation();
    out << "topForms=";
    outputXmlPointerQuoted(out, "AL", uniqueIdAST(&(obj->topForms)));
  }
  if (obj && obj->globalScope) {
    out << '\n';
    if (indent) printIndentation();
    out << "globalScope=";
    /*catch-all*/outputXmlPointerQuoted(out, "TY", idmgr.uniqueId(obj->globalScope));
  }
  --depth;
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitTranslationUnit(TranslationUnit *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}

bool XmlAstWriter_AstVisitor::visitTopForm(TopForm *obj) {
  if (wasVisitedAST(obj)) return false;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << obj->kindName();
  ++depth;
  out << " _id=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '\n';
  if (indent) printIndentation();
  out << "loc=";
  outputXmlAttrQuoted(out, toXml_SourceLoc(obj->loc));
  switch(obj->kind()) {
  default: xfailure("bad tag"); break;
  case TopForm::TF_DECL: {
    TF_decl *obj0 = obj->asTF_decl();
  if (obj0 && obj0->decl) {
    out << '\n';
    if (indent) printIndentation();
    out << "decl=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->decl));
  }
    obj0 = NULL;
    break;
    }
  case TopForm::TF_FUNC: {
    TF_func *obj0 = obj->asTF_func();
  if (obj0 && obj0->f) {
    out << '\n';
    if (indent) printIndentation();
    out << "f=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->f));
  }
    obj0 = NULL;
    break;
    }
  case TopForm::TF_TEMPLATE: {
    TF_template *obj0 = obj->asTF_template();
  if (obj0 && obj0->td) {
    out << '\n';
    if (indent) printIndentation();
    out << "td=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->td));
  }
    obj0 = NULL;
    break;
    }
  case TopForm::TF_EXPLICITINST: {
    TF_explicitInst *obj0 = obj->asTF_explicitInst();
  out << '\n';
  if (indent) printIndentation();
  out << "instFlags=";
  outputXmlAttrQuoted(out, toXml(obj0->instFlags));
  if (obj0 && obj0->d) {
    out << '\n';
    if (indent) printIndentation();
    out << "d=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->d));
  }
    obj0 = NULL;
    break;
    }
  case TopForm::TF_LINKAGE: {
    TF_linkage *obj0 = obj->asTF_linkage();
  if (obj0->linkageType) {
    out << '\n';
    if (indent) printIndentation();
    out << "linkageType=";
    outputXmlAttrQuoted(out, obj0->linkageType);
  } else {
  }
  if (obj0 && obj0->forms) {
    out << '\n';
    if (indent) printIndentation();
    out << "forms=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->forms));
  }
    obj0 = NULL;
    break;
    }
  case TopForm::TF_ONE_LINKAGE: {
    TF_one_linkage *obj0 = obj->asTF_one_linkage();
  if (obj0->linkageType) {
    out << '\n';
    if (indent) printIndentation();
    out << "linkageType=";
    outputXmlAttrQuoted(out, obj0->linkageType);
  } else {
  }
  if (obj0 && obj0->form) {
    out << '\n';
    if (indent) printIndentation();
    out << "form=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->form));
  }
    obj0 = NULL;
    break;
    }
  case TopForm::TF_ASM: {
    TF_asm *obj0 = obj->asTF_asm();
  if (obj0 && obj0->text) {
    out << '\n';
    if (indent) printIndentation();
    out << "text=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->text));
  }
    obj0 = NULL;
    break;
    }
  case TopForm::TF_NAMESPACEDEFN: {
    TF_namespaceDefn *obj0 = obj->asTF_namespaceDefn();
  if (obj0->name) {
    out << '\n';
    if (indent) printIndentation();
    out << "name=";
    outputXmlAttrQuoted(out, obj0->name);
  } else {
  }
  if (obj0 && obj0->forms.isNotEmpty()) {
    out << '\n';
    if (indent) printIndentation();
    out << "forms=";
    outputXmlPointerQuoted(out, "AL", uniqueIdAST(&(obj0->forms)));
  }
    obj0 = NULL;
    break;
    }
  case TopForm::TF_NAMESPACEDECL: {
    TF_namespaceDecl *obj0 = obj->asTF_namespaceDecl();
  if (obj0 && obj0->decl) {
    out << '\n';
    if (indent) printIndentation();
    out << "decl=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->decl));
  }
    obj0 = NULL;
    break;
    }
  }
  --depth;
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitTopForm(TopForm *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}

bool XmlAstWriter_AstVisitor::visitFunction(Function *obj) {
  if (wasVisitedAST(obj)) return false;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << obj->kindName();
  ++depth;
  out << " _id=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '\n';
  if (indent) printIndentation();
  out << "dflags=";
  outputXmlAttrQuoted(out, toXml(obj->dflags));
  if (obj && obj->retspec) {
    out << '\n';
    if (indent) printIndentation();
    out << "retspec=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj->retspec));
  }
  if (obj && obj->nameAndParams) {
    out << '\n';
    if (indent) printIndentation();
    out << "nameAndParams=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj->nameAndParams));
  }
  if (obj && obj->inits) {
    out << '\n';
    if (indent) printIndentation();
    out << "inits=";
    outputXmlPointerQuoted(out, "FL", uniqueIdAST(obj->inits));
  }
  if (obj && obj->body) {
    out << '\n';
    if (indent) printIndentation();
    out << "body=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj->body));
  }
  if (obj && obj->handlers) {
    out << '\n';
    if (indent) printIndentation();
    out << "handlers=";
    outputXmlPointerQuoted(out, "FL", uniqueIdAST(obj->handlers));
  }
  if (obj && obj->funcType) {
    out << '\n';
    if (indent) printIndentation();
    out << "funcType=";
    /*catch-all*/outputXmlPointerQuoted(out, "TY", idmgr.uniqueId(obj->funcType));
  }
  if (obj && obj->receiver && shouldSerialize(obj->receiver)) {
    out << '\n';
    if (indent) printIndentation();
    out << "receiver=";
    /*catch-all*/outputXmlPointerQuoted(out, "TY", idmgr.uniqueId(obj->receiver));
  }
  if (obj && obj->retVar && shouldSerialize(obj->retVar)) {
    out << '\n';
    if (indent) printIndentation();
    out << "retVar=";
    /*catch-all*/outputXmlPointerQuoted(out, "TY", idmgr.uniqueId(obj->retVar));
  }
  if (obj && obj->dtorStatement) {
    out << '\n';
    if (indent) printIndentation();
    out << "dtorStatement=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj->dtorStatement));
  }
  out << '\n';
  if (indent) printIndentation();
  out << "implicitlyDefined=";
  outputXmlAttrQuotedNoEscape(out, toXml_bool(obj->implicitlyDefined));
  --depth;
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitFunction(Function *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}

bool XmlAstWriter_AstVisitor::visitMemberInit(MemberInit *obj) {
  if (wasVisitedAST(obj)) return false;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << obj->kindName();
  ++depth;
  out << " _id=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '\n';
  if (indent) printIndentation();
  out << "loc=";
  outputXmlAttrQuoted(out, toXml_SourceLoc(obj->loc));
  out << '\n';
  if (indent) printIndentation();
  out << "endloc=";
  outputXmlAttrQuoted(out, toXml_SourceLoc(obj->endloc));
  if (obj && obj->name) {
    out << '\n';
    if (indent) printIndentation();
    out << "name=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj->name));
  }
  if (obj && obj->args) {
    out << '\n';
    if (indent) printIndentation();
    out << "args=";
    outputXmlPointerQuoted(out, "FL", uniqueIdAST(obj->args));
  }
  if (obj && obj->member && shouldSerialize(obj->member)) {
    out << '\n';
    if (indent) printIndentation();
    out << "member=";
    /*catch-all*/outputXmlPointerQuoted(out, "TY", idmgr.uniqueId(obj->member));
  }
  if (obj && obj->base) {
    out << '\n';
    if (indent) printIndentation();
    out << "base=";
    /*catch-all*/outputXmlPointerQuoted(out, "TY", idmgr.uniqueId(obj->base));
  }
  if (obj && obj->ctorVar && shouldSerialize(obj->ctorVar)) {
    out << '\n';
    if (indent) printIndentation();
    out << "ctorVar=";
    /*catch-all*/outputXmlPointerQuoted(out, "TY", idmgr.uniqueId(obj->ctorVar));
  }
  if (obj && obj->annot) {
    out << '\n';
    if (indent) printIndentation();
    out << "annot=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj->annot));
  }
  if (obj && obj->ctorStatement) {
    out << '\n';
    if (indent) printIndentation();
    out << "ctorStatement=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj->ctorStatement));
  }
  --depth;
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitMemberInit(MemberInit *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}

bool XmlAstWriter_AstVisitor::visitDeclaration(Declaration *obj) {
  if (wasVisitedAST(obj)) return false;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << obj->kindName();
  ++depth;
  out << " _id=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '\n';
  if (indent) printIndentation();
  out << "dflags=";
  outputXmlAttrQuoted(out, toXml(obj->dflags));
  if (obj && obj->spec) {
    out << '\n';
    if (indent) printIndentation();
    out << "spec=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj->spec));
  }
  if (obj && obj->decllist) {
    out << '\n';
    if (indent) printIndentation();
    out << "decllist=";
    outputXmlPointerQuoted(out, "FL", uniqueIdAST(obj->decllist));
  }
  --depth;
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitDeclaration(Declaration *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}

bool XmlAstWriter_AstVisitor::visitASTTypeId(ASTTypeId *obj) {
  if (wasVisitedAST(obj)) return false;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << obj->kindName();
  ++depth;
  out << " _id=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  if (obj && obj->spec) {
    out << '\n';
    if (indent) printIndentation();
    out << "spec=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj->spec));
  }
  if (obj && obj->decl) {
    out << '\n';
    if (indent) printIndentation();
    out << "decl=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj->decl));
  }
  --depth;
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitASTTypeId(ASTTypeId *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}

bool XmlAstWriter_AstVisitor::visitPQName(PQName *obj) {
  if (wasVisitedAST(obj)) return false;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << obj->kindName();
  ++depth;
  out << " _id=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '\n';
  if (indent) printIndentation();
  out << "loc=";
  outputXmlAttrQuoted(out, toXml_SourceLoc(obj->loc));
  switch(obj->kind()) {
  default: xfailure("bad tag"); break;
  case PQName::PQ_QUALIFIER: {
    PQ_qualifier *obj0 = obj->asPQ_qualifier();
  if (obj0->qualifier) {
    out << '\n';
    if (indent) printIndentation();
    out << "qualifier=";
    outputXmlAttrQuoted(out, obj0->qualifier);
  } else {
  }
  if (obj0 && obj0->templArgs) {
    out << '\n';
    if (indent) printIndentation();
    out << "templArgs=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->templArgs));
  }
  if (obj0 && obj0->rest) {
    out << '\n';
    if (indent) printIndentation();
    out << "rest=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->rest));
  }
  if (obj0 && obj0->qualifierVar && shouldSerialize(obj0->qualifierVar)) {
    out << '\n';
    if (indent) printIndentation();
    out << "qualifierVar=";
    /*catch-all*/outputXmlPointerQuoted(out, "TY", idmgr.uniqueId(obj0->qualifierVar));
  }
  if (obj0) {
    out << '\n';
    if (indent) printIndentation();
    out << "sargs=";
    outputXmlPointerQuoted(out, "OL", uniqueIdAST(&obj0->sargs));
  }
    obj0 = NULL;
    break;
    }
  case PQName::PQ_NAME: {
    PQ_name *obj0 = obj->asPQ_name();
  if (obj0->name) {
    out << '\n';
    if (indent) printIndentation();
    out << "name=";
    outputXmlAttrQuoted(out, obj0->name);
  } else {
  }
    obj0 = NULL;
    break;
    }
  case PQName::PQ_OPERATOR: {
    PQ_operator *obj0 = obj->asPQ_operator();
  if (obj0 && obj0->o) {
    out << '\n';
    if (indent) printIndentation();
    out << "o=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->o));
  }
  if (obj0->fakeName) {
    out << '\n';
    if (indent) printIndentation();
    out << "fakeName=";
    outputXmlAttrQuoted(out, obj0->fakeName);
  } else {
  }
    obj0 = NULL;
    break;
    }
  case PQName::PQ_TEMPLATE: {
    PQ_template *obj0 = obj->asPQ_template();
  if (obj0->name) {
    out << '\n';
    if (indent) printIndentation();
    out << "name=";
    outputXmlAttrQuoted(out, obj0->name);
  } else {
  }
  if (obj0 && obj0->templArgs) {
    out << '\n';
    if (indent) printIndentation();
    out << "templArgs=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->templArgs));
  }
  if (obj0) {
    out << '\n';
    if (indent) printIndentation();
    out << "sargs=";
    outputXmlPointerQuoted(out, "OL", uniqueIdAST(&obj0->sargs));
  }
    obj0 = NULL;
    break;
    }
  case PQName::PQ_VARIABLE: {
    PQ_variable *obj0 = obj->asPQ_variable();
  if (obj0 && obj0->var) {
    out << '\n';
    if (indent) printIndentation();
    out << "var=";
    /*catch-all*/outputXmlPointerQuoted(out, "TY", idmgr.uniqueId(obj0->var));
  }
    obj0 = NULL;
    break;
    }
  }
  --depth;
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitPQName(PQName *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}

bool XmlAstWriter_AstVisitor::visitTypeSpecifier(TypeSpecifier *obj) {
  if (wasVisitedAST(obj)) return false;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << obj->kindName();
  ++depth;
  out << " _id=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '\n';
  if (indent) printIndentation();
  out << "loc=";
  outputXmlAttrQuoted(out, toXml_SourceLoc(obj->loc));
  out << '\n';
  if (indent) printIndentation();
  out << "cv=";
  outputXmlAttrQuoted(out, toXml(obj->cv));
  switch(obj->kind()) {
  default: xfailure("bad tag"); break;
  case TypeSpecifier::TS_NAME: {
    TS_name *obj0 = obj->asTS_name();
  if (obj0 && obj0->name) {
    out << '\n';
    if (indent) printIndentation();
    out << "name=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->name));
  }
  out << '\n';
  if (indent) printIndentation();
  out << "typenameUsed=";
  outputXmlAttrQuotedNoEscape(out, toXml_bool(obj0->typenameUsed));
  if (obj0 && obj0->var && shouldSerialize(obj0->var)) {
    out << '\n';
    if (indent) printIndentation();
    out << "var=";
    /*catch-all*/outputXmlPointerQuoted(out, "TY", idmgr.uniqueId(obj0->var));
  }
  if (obj0 && obj0->nondependentVar && shouldSerialize(obj0->nondependentVar)) {
    out << '\n';
    if (indent) printIndentation();
    out << "nondependentVar=";
    /*catch-all*/outputXmlPointerQuoted(out, "TY", idmgr.uniqueId(obj0->nondependentVar));
  }
    obj0 = NULL;
    break;
    }
  case TypeSpecifier::TS_SIMPLE: {
    TS_simple *obj0 = obj->asTS_simple();
  out << '\n';
  if (indent) printIndentation();
  out << "id=";
  outputXmlAttrQuoted(out, toXml(obj0->id));
    obj0 = NULL;
    break;
    }
  case TypeSpecifier::TS_ELABORATED: {
    TS_elaborated *obj0 = obj->asTS_elaborated();
  out << '\n';
  if (indent) printIndentation();
  out << "keyword=";
  outputXmlAttrQuoted(out, toXml(obj0->keyword));
  if (obj0 && obj0->name) {
    out << '\n';
    if (indent) printIndentation();
    out << "name=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->name));
  }
  if (obj0 && obj0->atype) {
    out << '\n';
    if (indent) printIndentation();
    out << "atype=";
    /*catch-all*/outputXmlPointerQuoted(out, "TY", idmgr.uniqueId(obj0->atype));
  }
    obj0 = NULL;
    break;
    }
  case TypeSpecifier::TS_CLASSSPEC: {
    TS_classSpec *obj0 = obj->asTS_classSpec();
  out << '\n';
  if (indent) printIndentation();
  out << "keyword=";
  outputXmlAttrQuoted(out, toXml(obj0->keyword));
  if (obj0 && obj0->name) {
    out << '\n';
    if (indent) printIndentation();
    out << "name=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->name));
  }
  if (obj0 && obj0->bases) {
    out << '\n';
    if (indent) printIndentation();
    out << "bases=";
    outputXmlPointerQuoted(out, "FL", uniqueIdAST(obj0->bases));
  }
  if (obj0 && obj0->members) {
    out << '\n';
    if (indent) printIndentation();
    out << "members=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->members));
  }
  if (obj0 && obj0->ctype) {
    out << '\n';
    if (indent) printIndentation();
    out << "ctype=";
    /*catch-all*/outputXmlPointerQuoted(out, "TY", idmgr.uniqueId(obj0->ctype));
  }
    obj0 = NULL;
    break;
    }
  case TypeSpecifier::TS_ENUMSPEC: {
    TS_enumSpec *obj0 = obj->asTS_enumSpec();
  if (obj0->name) {
    out << '\n';
    if (indent) printIndentation();
    out << "name=";
    outputXmlAttrQuoted(out, obj0->name);
  } else {
  }
  if (obj0 && obj0->elts) {
    out << '\n';
    if (indent) printIndentation();
    out << "elts=";
    outputXmlPointerQuoted(out, "FL", uniqueIdAST(obj0->elts));
  }
  if (obj0 && obj0->etype) {
    out << '\n';
    if (indent) printIndentation();
    out << "etype=";
    /*catch-all*/outputXmlPointerQuoted(out, "TY", idmgr.uniqueId(obj0->etype));
  }
    obj0 = NULL;
    break;
    }
  case TypeSpecifier::TS_TYPE: {
    TS_type *obj0 = obj->asTS_type();
  if (obj0 && obj0->type) {
    out << '\n';
    if (indent) printIndentation();
    out << "type=";
    /*catch-all*/outputXmlPointerQuoted(out, "TY", idmgr.uniqueId(obj0->type));
  }
    obj0 = NULL;
    break;
    }
  case TypeSpecifier::TS_TYPEOF: {
    TS_typeof *obj0 = obj->asTS_typeof();
  if (obj0 && obj0->atype) {
    out << '\n';
    if (indent) printIndentation();
    out << "atype=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->atype));
  }
    obj0 = NULL;
    break;
    }
  }
  --depth;
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitTypeSpecifier(TypeSpecifier *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}

bool XmlAstWriter_AstVisitor::visitBaseClassSpec(BaseClassSpec *obj) {
  if (wasVisitedAST(obj)) return false;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << obj->kindName();
  ++depth;
  out << " _id=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '\n';
  if (indent) printIndentation();
  out << "isVirtual=";
  outputXmlAttrQuotedNoEscape(out, toXml_bool(obj->isVirtual));
  out << '\n';
  if (indent) printIndentation();
  out << "access=";
  outputXmlAttrQuoted(out, toXml(obj->access));
  if (obj && obj->name) {
    out << '\n';
    if (indent) printIndentation();
    out << "name=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj->name));
  }
  if (obj && obj->type) {
    out << '\n';
    if (indent) printIndentation();
    out << "type=";
    /*catch-all*/outputXmlPointerQuoted(out, "TY", idmgr.uniqueId(obj->type));
  }
  --depth;
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitBaseClassSpec(BaseClassSpec *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}

bool XmlAstWriter_AstVisitor::visitEnumerator(Enumerator *obj) {
  if (wasVisitedAST(obj)) return false;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << obj->kindName();
  ++depth;
  out << " _id=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '\n';
  if (indent) printIndentation();
  out << "loc=";
  outputXmlAttrQuoted(out, toXml_SourceLoc(obj->loc));
  if (obj->name) {
    out << '\n';
    if (indent) printIndentation();
    out << "name=";
    outputXmlAttrQuoted(out, obj->name);
  } else {
  }
  if (obj && obj->expr) {
    out << '\n';
    if (indent) printIndentation();
    out << "expr=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj->expr));
  }
  if (obj && obj->var && shouldSerialize(obj->var)) {
    out << '\n';
    if (indent) printIndentation();
    out << "var=";
    /*catch-all*/outputXmlPointerQuoted(out, "TY", idmgr.uniqueId(obj->var));
  }
  out << '\n';
  if (indent) printIndentation();
  out << "enumValue=";
  outputXmlAttrQuotedNoEscape(out, toXml_int(obj->enumValue));
  --depth;
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitEnumerator(Enumerator *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}

bool XmlAstWriter_AstVisitor::visitMemberList(MemberList *obj) {
  if (wasVisitedAST(obj)) return false;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << obj->kindName();
  ++depth;
  out << " _id=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  if (obj && obj->list.isNotEmpty()) {
    out << '\n';
    if (indent) printIndentation();
    out << "list=";
    outputXmlPointerQuoted(out, "AL", uniqueIdAST(&(obj->list)));
  }
  --depth;
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitMemberList(MemberList *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}

bool XmlAstWriter_AstVisitor::visitMember(Member *obj) {
  if (wasVisitedAST(obj)) return false;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << obj->kindName();
  ++depth;
  out << " _id=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '\n';
  if (indent) printIndentation();
  out << "loc=";
  outputXmlAttrQuoted(out, toXml_SourceLoc(obj->loc));
  out << '\n';
  if (indent) printIndentation();
  out << "endloc=";
  outputXmlAttrQuoted(out, toXml_SourceLoc(obj->endloc));
  switch(obj->kind()) {
  default: xfailure("bad tag"); break;
  case Member::MR_DECL: {
    MR_decl *obj0 = obj->asMR_decl();
  if (obj0 && obj0->d) {
    out << '\n';
    if (indent) printIndentation();
    out << "d=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->d));
  }
    obj0 = NULL;
    break;
    }
  case Member::MR_FUNC: {
    MR_func *obj0 = obj->asMR_func();
  if (obj0 && obj0->f) {
    out << '\n';
    if (indent) printIndentation();
    out << "f=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->f));
  }
    obj0 = NULL;
    break;
    }
  case Member::MR_ACCESS: {
    MR_access *obj0 = obj->asMR_access();
  out << '\n';
  if (indent) printIndentation();
  out << "k=";
  outputXmlAttrQuoted(out, toXml(obj0->k));
    obj0 = NULL;
    break;
    }
  case Member::MR_USINGDECL: {
    MR_usingDecl *obj0 = obj->asMR_usingDecl();
  if (obj0 && obj0->decl) {
    out << '\n';
    if (indent) printIndentation();
    out << "decl=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->decl));
  }
    obj0 = NULL;
    break;
    }
  case Member::MR_TEMPLATE: {
    MR_template *obj0 = obj->asMR_template();
  if (obj0 && obj0->d) {
    out << '\n';
    if (indent) printIndentation();
    out << "d=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->d));
  }
    obj0 = NULL;
    break;
    }
  }
  --depth;
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitMember(Member *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}

bool XmlAstWriter_AstVisitor::visitDeclarator(Declarator *obj) {
  if (wasVisitedAST(obj)) return false;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << obj->kindName();
  ++depth;
  out << " _id=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  if (obj && obj->decl) {
    out << '\n';
    if (indent) printIndentation();
    out << "decl=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj->decl));
  }
  if (obj && obj->init) {
    out << '\n';
    if (indent) printIndentation();
    out << "init=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj->init));
  }
  if (obj && obj->var && shouldSerialize(obj->var)) {
    out << '\n';
    if (indent) printIndentation();
    out << "var=";
    /*catch-all*/outputXmlPointerQuoted(out, "TY", idmgr.uniqueId(obj->var));
  }
  if (obj && obj->type) {
    out << '\n';
    if (indent) printIndentation();
    out << "type=";
    /*catch-all*/outputXmlPointerQuoted(out, "TY", idmgr.uniqueId(obj->type));
  }
  out << '\n';
  if (indent) printIndentation();
  out << "context=";
  outputXmlAttrQuoted(out, toXml(obj->context));
  if (obj && obj->ctorStatement) {
    out << '\n';
    if (indent) printIndentation();
    out << "ctorStatement=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj->ctorStatement));
  }
  if (obj && obj->dtorStatement) {
    out << '\n';
    if (indent) printIndentation();
    out << "dtorStatement=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj->dtorStatement));
  }
  --depth;
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitDeclarator(Declarator *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}

bool XmlAstWriter_AstVisitor::visitIDeclarator(IDeclarator *obj) {
  if (wasVisitedAST(obj)) return false;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << obj->kindName();
  ++depth;
  out << " _id=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '\n';
  if (indent) printIndentation();
  out << "loc=";
  outputXmlAttrQuoted(out, toXml_SourceLoc(obj->loc));
  switch(obj->kind()) {
  default: xfailure("bad tag"); break;
  case IDeclarator::D_NAME: {
    D_name *obj0 = obj->asD_name();
  if (obj0 && obj0->name) {
    out << '\n';
    if (indent) printIndentation();
    out << "name=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->name));
  }
    obj0 = NULL;
    break;
    }
  case IDeclarator::D_POINTER: {
    D_pointer *obj0 = obj->asD_pointer();
  out << '\n';
  if (indent) printIndentation();
  out << "cv=";
  outputXmlAttrQuoted(out, toXml(obj0->cv));
  if (obj0 && obj0->base) {
    out << '\n';
    if (indent) printIndentation();
    out << "base=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->base));
  }
    obj0 = NULL;
    break;
    }
  case IDeclarator::D_REFERENCE: {
    D_reference *obj0 = obj->asD_reference();
  if (obj0 && obj0->base) {
    out << '\n';
    if (indent) printIndentation();
    out << "base=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->base));
  }
    obj0 = NULL;
    break;
    }
  case IDeclarator::D_FUNC: {
    D_func *obj0 = obj->asD_func();
  if (obj0 && obj0->base) {
    out << '\n';
    if (indent) printIndentation();
    out << "base=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->base));
  }
  if (obj0 && obj0->params) {
    out << '\n';
    if (indent) printIndentation();
    out << "params=";
    outputXmlPointerQuoted(out, "FL", uniqueIdAST(obj0->params));
  }
  out << '\n';
  if (indent) printIndentation();
  out << "cv=";
  outputXmlAttrQuoted(out, toXml(obj0->cv));
  if (obj0 && obj0->exnSpec) {
    out << '\n';
    if (indent) printIndentation();
    out << "exnSpec=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->exnSpec));
  }
  if (obj0 && obj0->kAndR_params) {
    out << '\n';
    if (indent) printIndentation();
    out << "kAndR_params=";
    outputXmlPointerQuoted(out, "FL", uniqueIdAST(obj0->kAndR_params));
  }
  out << '\n';
  if (indent) printIndentation();
  out << "isMember=";
  outputXmlAttrQuotedNoEscape(out, toXml_bool(obj0->isMember));
    obj0 = NULL;
    break;
    }
  case IDeclarator::D_ARRAY: {
    D_array *obj0 = obj->asD_array();
  if (obj0 && obj0->base) {
    out << '\n';
    if (indent) printIndentation();
    out << "base=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->base));
  }
  if (obj0 && obj0->size) {
    out << '\n';
    if (indent) printIndentation();
    out << "size=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->size));
  }
  out << '\n';
  if (indent) printIndentation();
  out << "isNewSize=";
  outputXmlAttrQuotedNoEscape(out, toXml_bool(obj0->isNewSize));
    obj0 = NULL;
    break;
    }
  case IDeclarator::D_BITFIELD: {
    D_bitfield *obj0 = obj->asD_bitfield();
  if (obj0 && obj0->name) {
    out << '\n';
    if (indent) printIndentation();
    out << "name=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->name));
  }
  if (obj0 && obj0->bits) {
    out << '\n';
    if (indent) printIndentation();
    out << "bits=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->bits));
  }
  out << '\n';
  if (indent) printIndentation();
  out << "numBits=";
  outputXmlAttrQuotedNoEscape(out, toXml_int(obj0->numBits));
    obj0 = NULL;
    break;
    }
  case IDeclarator::D_PTRTOMEMBER: {
    D_ptrToMember *obj0 = obj->asD_ptrToMember();
  if (obj0 && obj0->nestedName) {
    out << '\n';
    if (indent) printIndentation();
    out << "nestedName=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->nestedName));
  }
  out << '\n';
  if (indent) printIndentation();
  out << "cv=";
  outputXmlAttrQuoted(out, toXml(obj0->cv));
  if (obj0 && obj0->base) {
    out << '\n';
    if (indent) printIndentation();
    out << "base=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->base));
  }
    obj0 = NULL;
    break;
    }
  case IDeclarator::D_GROUPING: {
    D_grouping *obj0 = obj->asD_grouping();
  if (obj0 && obj0->base) {
    out << '\n';
    if (indent) printIndentation();
    out << "base=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->base));
  }
    obj0 = NULL;
    break;
    }
  }
  --depth;
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitIDeclarator(IDeclarator *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}

bool XmlAstWriter_AstVisitor::visitExceptionSpec(ExceptionSpec *obj) {
  if (wasVisitedAST(obj)) return false;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << obj->kindName();
  ++depth;
  out << " _id=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  if (obj && obj->types) {
    out << '\n';
    if (indent) printIndentation();
    out << "types=";
    outputXmlPointerQuoted(out, "FL", uniqueIdAST(obj->types));
  }
  --depth;
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitExceptionSpec(ExceptionSpec *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}

bool XmlAstWriter_AstVisitor::visitOperatorName(OperatorName *obj) {
  if (wasVisitedAST(obj)) return false;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << obj->kindName();
  ++depth;
  out << " _id=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  switch(obj->kind()) {
  default: xfailure("bad tag"); break;
  case OperatorName::ON_NEWDEL: {
    ON_newDel *obj0 = obj->asON_newDel();
  out << '\n';
  if (indent) printIndentation();
  out << "isNew=";
  outputXmlAttrQuotedNoEscape(out, toXml_bool(obj0->isNew));
  out << '\n';
  if (indent) printIndentation();
  out << "isArray=";
  outputXmlAttrQuotedNoEscape(out, toXml_bool(obj0->isArray));
    obj0 = NULL;
    break;
    }
  case OperatorName::ON_OPERATOR: {
    ON_operator *obj0 = obj->asON_operator();
  out << '\n';
  if (indent) printIndentation();
  out << "op=";
  outputXmlAttrQuoted(out, toXml(obj0->op));
    obj0 = NULL;
    break;
    }
  case OperatorName::ON_CONVERSION: {
    ON_conversion *obj0 = obj->asON_conversion();
  if (obj0 && obj0->type) {
    out << '\n';
    if (indent) printIndentation();
    out << "type=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->type));
  }
    obj0 = NULL;
    break;
    }
  }
  --depth;
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitOperatorName(OperatorName *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}

bool XmlAstWriter_AstVisitor::visitStatement(Statement *obj) {
  if (wasVisitedAST(obj)) return false;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << obj->kindName();
  ++depth;
  out << " _id=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '\n';
  if (indent) printIndentation();
  out << "loc=";
  outputXmlAttrQuoted(out, toXml_SourceLoc(obj->loc));
  out << '\n';
  if (indent) printIndentation();
  out << "endloc=";
  outputXmlAttrQuoted(out, toXml_SourceLoc(obj->endloc));
  switch(obj->kind()) {
  default: xfailure("bad tag"); break;
  case Statement::S_SKIP: {
    S_skip *obj0 = obj->asS_skip();
    obj0 = NULL;
    break;
    }
  case Statement::S_LABEL: {
    S_label *obj0 = obj->asS_label();
  if (obj0->name) {
    out << '\n';
    if (indent) printIndentation();
    out << "name=";
    outputXmlAttrQuoted(out, obj0->name);
  } else {
  }
  if (obj0 && obj0->s) {
    out << '\n';
    if (indent) printIndentation();
    out << "s=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->s));
  }
    obj0 = NULL;
    break;
    }
  case Statement::S_CASE: {
    S_case *obj0 = obj->asS_case();
  if (obj0 && obj0->expr) {
    out << '\n';
    if (indent) printIndentation();
    out << "expr=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->expr));
  }
  if (obj0 && obj0->s) {
    out << '\n';
    if (indent) printIndentation();
    out << "s=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->s));
  }
  out << '\n';
  if (indent) printIndentation();
  out << "labelVal=";
  outputXmlAttrQuotedNoEscape(out, toXml_int(obj0->labelVal));
    obj0 = NULL;
    break;
    }
  case Statement::S_DEFAULT: {
    S_default *obj0 = obj->asS_default();
  if (obj0 && obj0->s) {
    out << '\n';
    if (indent) printIndentation();
    out << "s=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->s));
  }
    obj0 = NULL;
    break;
    }
  case Statement::S_EXPR: {
    S_expr *obj0 = obj->asS_expr();
  if (obj0 && obj0->expr) {
    out << '\n';
    if (indent) printIndentation();
    out << "expr=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->expr));
  }
    obj0 = NULL;
    break;
    }
  case Statement::S_COMPOUND: {
    S_compound *obj0 = obj->asS_compound();
  if (obj0 && obj0->stmts.isNotEmpty()) {
    out << '\n';
    if (indent) printIndentation();
    out << "stmts=";
    outputXmlPointerQuoted(out, "AL", uniqueIdAST(&(obj0->stmts)));
  }
    obj0 = NULL;
    break;
    }
  case Statement::S_IF: {
    S_if *obj0 = obj->asS_if();
  if (obj0 && obj0->cond) {
    out << '\n';
    if (indent) printIndentation();
    out << "cond=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->cond));
  }
  if (obj0 && obj0->thenBranch) {
    out << '\n';
    if (indent) printIndentation();
    out << "thenBranch=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->thenBranch));
  }
  if (obj0 && obj0->elseBranch) {
    out << '\n';
    if (indent) printIndentation();
    out << "elseBranch=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->elseBranch));
  }
    obj0 = NULL;
    break;
    }
  case Statement::S_SWITCH: {
    S_switch *obj0 = obj->asS_switch();
  if (obj0 && obj0->cond) {
    out << '\n';
    if (indent) printIndentation();
    out << "cond=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->cond));
  }
  if (obj0 && obj0->branches) {
    out << '\n';
    if (indent) printIndentation();
    out << "branches=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->branches));
  }
    obj0 = NULL;
    break;
    }
  case Statement::S_WHILE: {
    S_while *obj0 = obj->asS_while();
  if (obj0 && obj0->cond) {
    out << '\n';
    if (indent) printIndentation();
    out << "cond=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->cond));
  }
  if (obj0 && obj0->body) {
    out << '\n';
    if (indent) printIndentation();
    out << "body=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->body));
  }
    obj0 = NULL;
    break;
    }
  case Statement::S_DOWHILE: {
    S_doWhile *obj0 = obj->asS_doWhile();
  if (obj0 && obj0->body) {
    out << '\n';
    if (indent) printIndentation();
    out << "body=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->body));
  }
  if (obj0 && obj0->expr) {
    out << '\n';
    if (indent) printIndentation();
    out << "expr=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->expr));
  }
    obj0 = NULL;
    break;
    }
  case Statement::S_FOR: {
    S_for *obj0 = obj->asS_for();
  if (obj0 && obj0->init) {
    out << '\n';
    if (indent) printIndentation();
    out << "init=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->init));
  }
  if (obj0 && obj0->cond) {
    out << '\n';
    if (indent) printIndentation();
    out << "cond=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->cond));
  }
  if (obj0 && obj0->after) {
    out << '\n';
    if (indent) printIndentation();
    out << "after=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->after));
  }
  if (obj0 && obj0->body) {
    out << '\n';
    if (indent) printIndentation();
    out << "body=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->body));
  }
    obj0 = NULL;
    break;
    }
  case Statement::S_BREAK: {
    S_break *obj0 = obj->asS_break();
    obj0 = NULL;
    break;
    }
  case Statement::S_CONTINUE: {
    S_continue *obj0 = obj->asS_continue();
    obj0 = NULL;
    break;
    }
  case Statement::S_RETURN: {
    S_return *obj0 = obj->asS_return();
  if (obj0 && obj0->expr) {
    out << '\n';
    if (indent) printIndentation();
    out << "expr=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->expr));
  }
  if (obj0 && obj0->ctorStatement) {
    out << '\n';
    if (indent) printIndentation();
    out << "ctorStatement=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->ctorStatement));
  }
    obj0 = NULL;
    break;
    }
  case Statement::S_GOTO: {
    S_goto *obj0 = obj->asS_goto();
  if (obj0->target) {
    out << '\n';
    if (indent) printIndentation();
    out << "target=";
    outputXmlAttrQuoted(out, obj0->target);
  } else {
  }
    obj0 = NULL;
    break;
    }
  case Statement::S_DECL: {
    S_decl *obj0 = obj->asS_decl();
  if (obj0 && obj0->decl) {
    out << '\n';
    if (indent) printIndentation();
    out << "decl=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->decl));
  }
    obj0 = NULL;
    break;
    }
  case Statement::S_TRY: {
    S_try *obj0 = obj->asS_try();
  if (obj0 && obj0->body) {
    out << '\n';
    if (indent) printIndentation();
    out << "body=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->body));
  }
  if (obj0 && obj0->handlers) {
    out << '\n';
    if (indent) printIndentation();
    out << "handlers=";
    outputXmlPointerQuoted(out, "FL", uniqueIdAST(obj0->handlers));
  }
    obj0 = NULL;
    break;
    }
  case Statement::S_ASM: {
    S_asm *obj0 = obj->asS_asm();
  if (obj0 && obj0->text) {
    out << '\n';
    if (indent) printIndentation();
    out << "text=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->text));
  }
    obj0 = NULL;
    break;
    }
  case Statement::S_NAMESPACEDECL: {
    S_namespaceDecl *obj0 = obj->asS_namespaceDecl();
  if (obj0 && obj0->decl) {
    out << '\n';
    if (indent) printIndentation();
    out << "decl=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->decl));
  }
    obj0 = NULL;
    break;
    }
  case Statement::S_FUNCTION: {
    S_function *obj0 = obj->asS_function();
  if (obj0 && obj0->f) {
    out << '\n';
    if (indent) printIndentation();
    out << "f=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->f));
  }
    obj0 = NULL;
    break;
    }
  case Statement::S_RANGECASE: {
    S_rangeCase *obj0 = obj->asS_rangeCase();
  if (obj0 && obj0->exprLo) {
    out << '\n';
    if (indent) printIndentation();
    out << "exprLo=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->exprLo));
  }
  if (obj0 && obj0->exprHi) {
    out << '\n';
    if (indent) printIndentation();
    out << "exprHi=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->exprHi));
  }
  if (obj0 && obj0->s) {
    out << '\n';
    if (indent) printIndentation();
    out << "s=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->s));
  }
  out << '\n';
  if (indent) printIndentation();
  out << "labelValLo=";
  outputXmlAttrQuotedNoEscape(out, toXml_int(obj0->labelValLo));
  out << '\n';
  if (indent) printIndentation();
  out << "labelValHi=";
  outputXmlAttrQuotedNoEscape(out, toXml_int(obj0->labelValHi));
    obj0 = NULL;
    break;
    }
  case Statement::S_COMPUTEDGOTO: {
    S_computedGoto *obj0 = obj->asS_computedGoto();
  if (obj0 && obj0->target) {
    out << '\n';
    if (indent) printIndentation();
    out << "target=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->target));
  }
    obj0 = NULL;
    break;
    }
  }
  --depth;
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitStatement(Statement *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}

bool XmlAstWriter_AstVisitor::visitCondition(Condition *obj) {
  if (wasVisitedAST(obj)) return false;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << obj->kindName();
  ++depth;
  out << " _id=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  switch(obj->kind()) {
  default: xfailure("bad tag"); break;
  case Condition::CN_EXPR: {
    CN_expr *obj0 = obj->asCN_expr();
  if (obj0 && obj0->expr) {
    out << '\n';
    if (indent) printIndentation();
    out << "expr=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->expr));
  }
    obj0 = NULL;
    break;
    }
  case Condition::CN_DECL: {
    CN_decl *obj0 = obj->asCN_decl();
  if (obj0 && obj0->typeId) {
    out << '\n';
    if (indent) printIndentation();
    out << "typeId=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->typeId));
  }
    obj0 = NULL;
    break;
    }
  }
  --depth;
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitCondition(Condition *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}

bool XmlAstWriter_AstVisitor::visitHandler(Handler *obj) {
  if (wasVisitedAST(obj)) return false;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << obj->kindName();
  ++depth;
  out << " _id=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  if (obj && obj->typeId) {
    out << '\n';
    if (indent) printIndentation();
    out << "typeId=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj->typeId));
  }
  if (obj && obj->body) {
    out << '\n';
    if (indent) printIndentation();
    out << "body=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj->body));
  }
  if (obj && obj->globalVar && shouldSerialize(obj->globalVar)) {
    out << '\n';
    if (indent) printIndentation();
    out << "globalVar=";
    /*catch-all*/outputXmlPointerQuoted(out, "TY", idmgr.uniqueId(obj->globalVar));
  }
  if (obj && obj->annot) {
    out << '\n';
    if (indent) printIndentation();
    out << "annot=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj->annot));
  }
  if (obj && obj->localArg) {
    out << '\n';
    if (indent) printIndentation();
    out << "localArg=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj->localArg));
  }
  if (obj && obj->globalDtorStatement) {
    out << '\n';
    if (indent) printIndentation();
    out << "globalDtorStatement=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj->globalDtorStatement));
  }
  --depth;
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitHandler(Handler *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}

bool XmlAstWriter_AstVisitor::visitExpression(Expression *obj) {
  if (wasVisitedAST(obj)) return false;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << obj->kindName();
  ++depth;
  out << " _id=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '\n';
  if (indent) printIndentation();
  out << "loc=";
  outputXmlAttrQuoted(out, toXml_SourceLoc(obj->loc));
  out << '\n';
  if (indent) printIndentation();
  out << "endloc=";
  outputXmlAttrQuoted(out, toXml_SourceLoc(obj->endloc));
  if (obj && obj->type) {
    out << '\n';
    if (indent) printIndentation();
    out << "type=";
    /*catch-all*/outputXmlPointerQuoted(out, "TY", idmgr.uniqueId(obj->type));
  }
  switch(obj->kind()) {
  default: xfailure("bad tag"); break;
  case Expression::E_BOOLLIT: {
    E_boolLit *obj0 = obj->asE_boolLit();
  out << '\n';
  if (indent) printIndentation();
  out << "b=";
  outputXmlAttrQuotedNoEscape(out, toXml_bool(obj0->b));
    obj0 = NULL;
    break;
    }
  case Expression::E_INTLIT: {
    E_intLit *obj0 = obj->asE_intLit();
  if (obj0->text) {
    out << '\n';
    if (indent) printIndentation();
    out << "text=";
    outputXmlAttrQuoted(out, obj0->text);
  } else {
  }
  out << '\n';
  if (indent) printIndentation();
  out << "i=";
  outputXmlAttrQuotedNoEscape(out, toXml_unsigned_long(obj0->i));
    obj0 = NULL;
    break;
    }
  case Expression::E_FLOATLIT: {
    E_floatLit *obj0 = obj->asE_floatLit();
  if (obj0->text) {
    out << '\n';
    if (indent) printIndentation();
    out << "text=";
    outputXmlAttrQuoted(out, obj0->text);
  } else {
  }
  out << '\n';
  if (indent) printIndentation();
  out << "d=";
  outputXmlAttrQuotedNoEscape(out, toXml_double(obj0->d));
    obj0 = NULL;
    break;
    }
  case Expression::E_STRINGLIT: {
    E_stringLit *obj0 = obj->asE_stringLit();
  if (obj0->text) {
    out << '\n';
    if (indent) printIndentation();
    out << "text=";
    outputXmlAttrQuoted(out, obj0->text);
  } else {
  }
  if (obj0 && obj0->continuation) {
    out << '\n';
    if (indent) printIndentation();
    out << "continuation=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->continuation));
  }
  if (obj0->fullTextNQ) {
    out << '\n';
    if (indent) printIndentation();
    out << "fullTextNQ=";
    outputXmlAttrQuoted(out, obj0->fullTextNQ);
  } else {
  }
    obj0 = NULL;
    break;
    }
  case Expression::E_CHARLIT: {
    E_charLit *obj0 = obj->asE_charLit();
  if (obj0->text) {
    out << '\n';
    if (indent) printIndentation();
    out << "text=";
    outputXmlAttrQuoted(out, obj0->text);
  } else {
  }
  out << '\n';
  if (indent) printIndentation();
  out << "c=";
  outputXmlAttrQuotedNoEscape(out, toXml_unsigned_int(obj0->c));
    obj0 = NULL;
    break;
    }
  case Expression::E_THIS: {
    E_this *obj0 = obj->asE_this();
  if (obj0 && obj0->receiver && shouldSerialize(obj0->receiver)) {
    out << '\n';
    if (indent) printIndentation();
    out << "receiver=";
    /*catch-all*/outputXmlPointerQuoted(out, "TY", idmgr.uniqueId(obj0->receiver));
  }
    obj0 = NULL;
    break;
    }
  case Expression::E_VARIABLE: {
    E_variable *obj0 = obj->asE_variable();
  if (obj0 && obj0->name) {
    out << '\n';
    if (indent) printIndentation();
    out << "name=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->name));
  }
  if (obj0 && obj0->var && shouldSerialize(obj0->var)) {
    out << '\n';
    if (indent) printIndentation();
    out << "var=";
    /*catch-all*/outputXmlPointerQuoted(out, "TY", idmgr.uniqueId(obj0->var));
  }
  if (obj0 && obj0->nondependentVar && shouldSerialize(obj0->nondependentVar)) {
    out << '\n';
    if (indent) printIndentation();
    out << "nondependentVar=";
    /*catch-all*/outputXmlPointerQuoted(out, "TY", idmgr.uniqueId(obj0->nondependentVar));
  }
    obj0 = NULL;
    break;
    }
  case Expression::E_FUNCALL: {
    E_funCall *obj0 = obj->asE_funCall();
  if (obj0 && obj0->func) {
    out << '\n';
    if (indent) printIndentation();
    out << "func=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->func));
  }
  if (obj0 && obj0->args) {
    out << '\n';
    if (indent) printIndentation();
    out << "args=";
    outputXmlPointerQuoted(out, "FL", uniqueIdAST(obj0->args));
  }
  if (obj0 && obj0->retObj) {
    out << '\n';
    if (indent) printIndentation();
    out << "retObj=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->retObj));
  }
    obj0 = NULL;
    break;
    }
  case Expression::E_CONSTRUCTOR: {
    E_constructor *obj0 = obj->asE_constructor();
  if (obj0 && obj0->spec) {
    out << '\n';
    if (indent) printIndentation();
    out << "spec=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->spec));
  }
  if (obj0 && obj0->args) {
    out << '\n';
    if (indent) printIndentation();
    out << "args=";
    outputXmlPointerQuoted(out, "FL", uniqueIdAST(obj0->args));
  }
  if (obj0 && obj0->ctorVar && shouldSerialize(obj0->ctorVar)) {
    out << '\n';
    if (indent) printIndentation();
    out << "ctorVar=";
    /*catch-all*/outputXmlPointerQuoted(out, "TY", idmgr.uniqueId(obj0->ctorVar));
  }
  out << '\n';
  if (indent) printIndentation();
  out << "artificial=";
  outputXmlAttrQuotedNoEscape(out, toXml_bool(obj0->artificial));
  if (obj0 && obj0->retObj) {
    out << '\n';
    if (indent) printIndentation();
    out << "retObj=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->retObj));
  }
    obj0 = NULL;
    break;
    }
  case Expression::E_FIELDACC: {
    E_fieldAcc *obj0 = obj->asE_fieldAcc();
  if (obj0 && obj0->obj) {
    out << '\n';
    if (indent) printIndentation();
    out << "obj=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->obj));
  }
  if (obj0 && obj0->fieldName) {
    out << '\n';
    if (indent) printIndentation();
    out << "fieldName=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->fieldName));
  }
  if (obj0 && obj0->field && shouldSerialize(obj0->field)) {
    out << '\n';
    if (indent) printIndentation();
    out << "field=";
    /*catch-all*/outputXmlPointerQuoted(out, "TY", idmgr.uniqueId(obj0->field));
  }
    obj0 = NULL;
    break;
    }
  case Expression::E_SIZEOF: {
    E_sizeof *obj0 = obj->asE_sizeof();
  if (obj0 && obj0->expr) {
    out << '\n';
    if (indent) printIndentation();
    out << "expr=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->expr));
  }
  out << '\n';
  if (indent) printIndentation();
  out << "size=";
  outputXmlAttrQuotedNoEscape(out, toXml_int(obj0->size));
    obj0 = NULL;
    break;
    }
  case Expression::E_UNARY: {
    E_unary *obj0 = obj->asE_unary();
  out << '\n';
  if (indent) printIndentation();
  out << "op=";
  outputXmlAttrQuoted(out, toXml(obj0->op));
  if (obj0 && obj0->expr) {
    out << '\n';
    if (indent) printIndentation();
    out << "expr=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->expr));
  }
    obj0 = NULL;
    break;
    }
  case Expression::E_EFFECT: {
    E_effect *obj0 = obj->asE_effect();
  out << '\n';
  if (indent) printIndentation();
  out << "op=";
  outputXmlAttrQuoted(out, toXml(obj0->op));
  if (obj0 && obj0->expr) {
    out << '\n';
    if (indent) printIndentation();
    out << "expr=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->expr));
  }
    obj0 = NULL;
    break;
    }
  case Expression::E_BINARY: {
    E_binary *obj0 = obj->asE_binary();
  if (obj0 && obj0->e1) {
    out << '\n';
    if (indent) printIndentation();
    out << "e1=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->e1));
  }
  out << '\n';
  if (indent) printIndentation();
  out << "op=";
  outputXmlAttrQuoted(out, toXml(obj0->op));
  if (obj0 && obj0->e2) {
    out << '\n';
    if (indent) printIndentation();
    out << "e2=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->e2));
  }
    obj0 = NULL;
    break;
    }
  case Expression::E_ADDROF: {
    E_addrOf *obj0 = obj->asE_addrOf();
  if (obj0 && obj0->expr) {
    out << '\n';
    if (indent) printIndentation();
    out << "expr=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->expr));
  }
    obj0 = NULL;
    break;
    }
  case Expression::E_DEREF: {
    E_deref *obj0 = obj->asE_deref();
  if (obj0 && obj0->ptr) {
    out << '\n';
    if (indent) printIndentation();
    out << "ptr=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->ptr));
  }
    obj0 = NULL;
    break;
    }
  case Expression::E_CAST: {
    E_cast *obj0 = obj->asE_cast();
  if (obj0 && obj0->ctype) {
    out << '\n';
    if (indent) printIndentation();
    out << "ctype=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->ctype));
  }
  if (obj0 && obj0->expr) {
    out << '\n';
    if (indent) printIndentation();
    out << "expr=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->expr));
  }
  out << '\n';
  if (indent) printIndentation();
  out << "tcheckedType=";
  outputXmlAttrQuotedNoEscape(out, toXml_bool(obj0->tcheckedType));
    obj0 = NULL;
    break;
    }
  case Expression::E_COND: {
    E_cond *obj0 = obj->asE_cond();
  if (obj0 && obj0->cond) {
    out << '\n';
    if (indent) printIndentation();
    out << "cond=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->cond));
  }
  if (obj0 && obj0->th) {
    out << '\n';
    if (indent) printIndentation();
    out << "th=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->th));
  }
  if (obj0 && obj0->el) {
    out << '\n';
    if (indent) printIndentation();
    out << "el=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->el));
  }
    obj0 = NULL;
    break;
    }
  case Expression::E_SIZEOFTYPE: {
    E_sizeofType *obj0 = obj->asE_sizeofType();
  if (obj0 && obj0->atype) {
    out << '\n';
    if (indent) printIndentation();
    out << "atype=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->atype));
  }
  out << '\n';
  if (indent) printIndentation();
  out << "size=";
  outputXmlAttrQuotedNoEscape(out, toXml_int(obj0->size));
  out << '\n';
  if (indent) printIndentation();
  out << "tchecked=";
  outputXmlAttrQuotedNoEscape(out, toXml_bool(obj0->tchecked));
    obj0 = NULL;
    break;
    }
  case Expression::E_ASSIGN: {
    E_assign *obj0 = obj->asE_assign();
  if (obj0 && obj0->target) {
    out << '\n';
    if (indent) printIndentation();
    out << "target=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->target));
  }
  out << '\n';
  if (indent) printIndentation();
  out << "op=";
  outputXmlAttrQuoted(out, toXml(obj0->op));
  if (obj0 && obj0->src) {
    out << '\n';
    if (indent) printIndentation();
    out << "src=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->src));
  }
    obj0 = NULL;
    break;
    }
  case Expression::E_NEW: {
    E_new *obj0 = obj->asE_new();
  out << '\n';
  if (indent) printIndentation();
  out << "colonColon=";
  outputXmlAttrQuotedNoEscape(out, toXml_bool(obj0->colonColon));
  if (obj0 && obj0->placementArgs) {
    out << '\n';
    if (indent) printIndentation();
    out << "placementArgs=";
    outputXmlPointerQuoted(out, "FL", uniqueIdAST(obj0->placementArgs));
  }
  if (obj0 && obj0->atype) {
    out << '\n';
    if (indent) printIndentation();
    out << "atype=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->atype));
  }
  if (obj0 && obj0->ctorArgs) {
    out << '\n';
    if (indent) printIndentation();
    out << "ctorArgs=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->ctorArgs));
  }
  if (obj0 && obj0->arraySize) {
    out << '\n';
    if (indent) printIndentation();
    out << "arraySize=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->arraySize));
  }
  if (obj0 && obj0->ctorVar && shouldSerialize(obj0->ctorVar)) {
    out << '\n';
    if (indent) printIndentation();
    out << "ctorVar=";
    /*catch-all*/outputXmlPointerQuoted(out, "TY", idmgr.uniqueId(obj0->ctorVar));
  }
  if (obj0 && obj0->ctorStatement) {
    out << '\n';
    if (indent) printIndentation();
    out << "ctorStatement=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->ctorStatement));
  }
  if (obj0 && obj0->heapVar && shouldSerialize(obj0->heapVar)) {
    out << '\n';
    if (indent) printIndentation();
    out << "heapVar=";
    /*catch-all*/outputXmlPointerQuoted(out, "TY", idmgr.uniqueId(obj0->heapVar));
  }
    obj0 = NULL;
    break;
    }
  case Expression::E_DELETE: {
    E_delete *obj0 = obj->asE_delete();
  out << '\n';
  if (indent) printIndentation();
  out << "colonColon=";
  outputXmlAttrQuotedNoEscape(out, toXml_bool(obj0->colonColon));
  out << '\n';
  if (indent) printIndentation();
  out << "array=";
  outputXmlAttrQuotedNoEscape(out, toXml_bool(obj0->array));
  if (obj0 && obj0->expr) {
    out << '\n';
    if (indent) printIndentation();
    out << "expr=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->expr));
  }
  if (obj0 && obj0->dtorStatement) {
    out << '\n';
    if (indent) printIndentation();
    out << "dtorStatement=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->dtorStatement));
  }
    obj0 = NULL;
    break;
    }
  case Expression::E_THROW: {
    E_throw *obj0 = obj->asE_throw();
  if (obj0 && obj0->expr) {
    out << '\n';
    if (indent) printIndentation();
    out << "expr=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->expr));
  }
  if (obj0 && obj0->globalVar && shouldSerialize(obj0->globalVar)) {
    out << '\n';
    if (indent) printIndentation();
    out << "globalVar=";
    /*catch-all*/outputXmlPointerQuoted(out, "TY", idmgr.uniqueId(obj0->globalVar));
  }
  if (obj0 && obj0->globalCtorStatement) {
    out << '\n';
    if (indent) printIndentation();
    out << "globalCtorStatement=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->globalCtorStatement));
  }
    obj0 = NULL;
    break;
    }
  case Expression::E_KEYWORDCAST: {
    E_keywordCast *obj0 = obj->asE_keywordCast();
  out << '\n';
  if (indent) printIndentation();
  out << "key=";
  outputXmlAttrQuoted(out, toXml(obj0->key));
  if (obj0 && obj0->ctype) {
    out << '\n';
    if (indent) printIndentation();
    out << "ctype=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->ctype));
  }
  if (obj0 && obj0->expr) {
    out << '\n';
    if (indent) printIndentation();
    out << "expr=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->expr));
  }
    obj0 = NULL;
    break;
    }
  case Expression::E_TYPEIDEXPR: {
    E_typeidExpr *obj0 = obj->asE_typeidExpr();
  if (obj0 && obj0->expr) {
    out << '\n';
    if (indent) printIndentation();
    out << "expr=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->expr));
  }
    obj0 = NULL;
    break;
    }
  case Expression::E_TYPEIDTYPE: {
    E_typeidType *obj0 = obj->asE_typeidType();
  if (obj0 && obj0->ttype) {
    out << '\n';
    if (indent) printIndentation();
    out << "ttype=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->ttype));
  }
    obj0 = NULL;
    break;
    }
  case Expression::E_GROUPING: {
    E_grouping *obj0 = obj->asE_grouping();
  if (obj0 && obj0->expr) {
    out << '\n';
    if (indent) printIndentation();
    out << "expr=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->expr));
  }
    obj0 = NULL;
    break;
    }
  case Expression::E_ARROW: {
    E_arrow *obj0 = obj->asE_arrow();
  if (obj0 && obj0->obj) {
    out << '\n';
    if (indent) printIndentation();
    out << "obj=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->obj));
  }
  if (obj0 && obj0->fieldName) {
    out << '\n';
    if (indent) printIndentation();
    out << "fieldName=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->fieldName));
  }
    obj0 = NULL;
    break;
    }
  case Expression::E_STATEMENT: {
    E_statement *obj0 = obj->asE_statement();
  if (obj0 && obj0->s) {
    out << '\n';
    if (indent) printIndentation();
    out << "s=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->s));
  }
    obj0 = NULL;
    break;
    }
  case Expression::E_COMPOUNDLIT: {
    E_compoundLit *obj0 = obj->asE_compoundLit();
  if (obj0 && obj0->stype) {
    out << '\n';
    if (indent) printIndentation();
    out << "stype=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->stype));
  }
  if (obj0 && obj0->init) {
    out << '\n';
    if (indent) printIndentation();
    out << "init=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->init));
  }
    obj0 = NULL;
    break;
    }
  case Expression::E___BUILTIN_CONSTANT_P: {
    E___builtin_constant_p *obj0 = obj->asE___builtin_constant_p();
  if (obj0 && obj0->expr) {
    out << '\n';
    if (indent) printIndentation();
    out << "expr=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->expr));
  }
    obj0 = NULL;
    break;
    }
  case Expression::E___BUILTIN_VA_ARG: {
    E___builtin_va_arg *obj0 = obj->asE___builtin_va_arg();
  if (obj0 && obj0->expr) {
    out << '\n';
    if (indent) printIndentation();
    out << "expr=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->expr));
  }
  if (obj0 && obj0->atype) {
    out << '\n';
    if (indent) printIndentation();
    out << "atype=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->atype));
  }
    obj0 = NULL;
    break;
    }
  case Expression::E_ALIGNOFTYPE: {
    E_alignofType *obj0 = obj->asE_alignofType();
  if (obj0 && obj0->atype) {
    out << '\n';
    if (indent) printIndentation();
    out << "atype=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->atype));
  }
  out << '\n';
  if (indent) printIndentation();
  out << "alignment=";
  outputXmlAttrQuotedNoEscape(out, toXml_int(obj0->alignment));
    obj0 = NULL;
    break;
    }
  case Expression::E_ALIGNOFEXPR: {
    E_alignofExpr *obj0 = obj->asE_alignofExpr();
  if (obj0 && obj0->expr) {
    out << '\n';
    if (indent) printIndentation();
    out << "expr=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->expr));
  }
  out << '\n';
  if (indent) printIndentation();
  out << "alignment=";
  outputXmlAttrQuotedNoEscape(out, toXml_int(obj0->alignment));
    obj0 = NULL;
    break;
    }
  case Expression::E_GNUCOND: {
    E_gnuCond *obj0 = obj->asE_gnuCond();
  if (obj0 && obj0->cond) {
    out << '\n';
    if (indent) printIndentation();
    out << "cond=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->cond));
  }
  if (obj0 && obj0->el) {
    out << '\n';
    if (indent) printIndentation();
    out << "el=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->el));
  }
    obj0 = NULL;
    break;
    }
  case Expression::E_ADDROFLABEL: {
    E_addrOfLabel *obj0 = obj->asE_addrOfLabel();
  if (obj0->labelName) {
    out << '\n';
    if (indent) printIndentation();
    out << "labelName=";
    outputXmlAttrQuoted(out, obj0->labelName);
  } else {
  }
    obj0 = NULL;
    break;
    }
  }
  --depth;
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitExpression(Expression *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}

bool XmlAstWriter_AstVisitor::visitFullExpression(FullExpression *obj) {
  if (wasVisitedAST(obj)) return false;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << obj->kindName();
  ++depth;
  out << " _id=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  if (obj && obj->expr) {
    out << '\n';
    if (indent) printIndentation();
    out << "expr=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj->expr));
  }
  if (obj && obj->annot) {
    out << '\n';
    if (indent) printIndentation();
    out << "annot=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj->annot));
  }
  --depth;
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitFullExpression(FullExpression *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}

bool XmlAstWriter_AstVisitor::visitArgExpression(ArgExpression *obj) {
  if (wasVisitedAST(obj)) return false;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << obj->kindName();
  ++depth;
  out << " _id=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  if (obj && obj->expr) {
    out << '\n';
    if (indent) printIndentation();
    out << "expr=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj->expr));
  }
  --depth;
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitArgExpression(ArgExpression *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}

bool XmlAstWriter_AstVisitor::visitArgExpressionListOpt(ArgExpressionListOpt *obj) {
  if (wasVisitedAST(obj)) return false;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << obj->kindName();
  ++depth;
  out << " _id=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  if (obj && obj->list) {
    out << '\n';
    if (indent) printIndentation();
    out << "list=";
    outputXmlPointerQuoted(out, "FL", uniqueIdAST(obj->list));
  }
  --depth;
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitArgExpressionListOpt(ArgExpressionListOpt *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}

bool XmlAstWriter_AstVisitor::visitInitializer(Initializer *obj) {
  if (wasVisitedAST(obj)) return false;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << obj->kindName();
  ++depth;
  out << " _id=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '\n';
  if (indent) printIndentation();
  out << "loc=";
  outputXmlAttrQuoted(out, toXml_SourceLoc(obj->loc));
  if (obj && obj->annot) {
    out << '\n';
    if (indent) printIndentation();
    out << "annot=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj->annot));
  }
  switch(obj->kind()) {
  default: xfailure("bad tag"); break;
  case Initializer::IN_EXPR: {
    IN_expr *obj0 = obj->asIN_expr();
  if (obj0 && obj0->e) {
    out << '\n';
    if (indent) printIndentation();
    out << "e=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->e));
  }
    obj0 = NULL;
    break;
    }
  case Initializer::IN_COMPOUND: {
    IN_compound *obj0 = obj->asIN_compound();
  if (obj0 && obj0->inits.isNotEmpty()) {
    out << '\n';
    if (indent) printIndentation();
    out << "inits=";
    outputXmlPointerQuoted(out, "AL", uniqueIdAST(&(obj0->inits)));
  }
    obj0 = NULL;
    break;
    }
  case Initializer::IN_CTOR: {
    IN_ctor *obj0 = obj->asIN_ctor();
  if (obj0 && obj0->args) {
    out << '\n';
    if (indent) printIndentation();
    out << "args=";
    outputXmlPointerQuoted(out, "FL", uniqueIdAST(obj0->args));
  }
  if (obj0 && obj0->ctorVar && shouldSerialize(obj0->ctorVar)) {
    out << '\n';
    if (indent) printIndentation();
    out << "ctorVar=";
    /*catch-all*/outputXmlPointerQuoted(out, "TY", idmgr.uniqueId(obj0->ctorVar));
  }
  out << '\n';
  if (indent) printIndentation();
  out << "was_IN_expr=";
  outputXmlAttrQuotedNoEscape(out, toXml_bool(obj0->was_IN_expr));
    obj0 = NULL;
    break;
    }
  case Initializer::IN_DESIGNATED: {
    IN_designated *obj0 = obj->asIN_designated();
  if (obj0 && obj0->designator_list) {
    out << '\n';
    if (indent) printIndentation();
    out << "designator_list=";
    outputXmlPointerQuoted(out, "FL", uniqueIdAST(obj0->designator_list));
  }
  if (obj0 && obj0->init) {
    out << '\n';
    if (indent) printIndentation();
    out << "init=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->init));
  }
    obj0 = NULL;
    break;
    }
  }
  --depth;
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitInitializer(Initializer *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}

bool XmlAstWriter_AstVisitor::visitTemplateDeclaration(TemplateDeclaration *obj) {
  if (wasVisitedAST(obj)) return false;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << obj->kindName();
  ++depth;
  out << " _id=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  if (obj && obj->params) {
    out << '\n';
    if (indent) printIndentation();
    out << "params=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj->params));
  }
  switch(obj->kind()) {
  default: xfailure("bad tag"); break;
  case TemplateDeclaration::TD_FUNC: {
    TD_func *obj0 = obj->asTD_func();
  if (obj0 && obj0->f) {
    out << '\n';
    if (indent) printIndentation();
    out << "f=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->f));
  }
    obj0 = NULL;
    break;
    }
  case TemplateDeclaration::TD_DECL: {
    TD_decl *obj0 = obj->asTD_decl();
  if (obj0 && obj0->d) {
    out << '\n';
    if (indent) printIndentation();
    out << "d=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->d));
  }
    obj0 = NULL;
    break;
    }
  case TemplateDeclaration::TD_TMEMBER: {
    TD_tmember *obj0 = obj->asTD_tmember();
  if (obj0 && obj0->d) {
    out << '\n';
    if (indent) printIndentation();
    out << "d=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->d));
  }
    obj0 = NULL;
    break;
    }
  }
  --depth;
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitTemplateDeclaration(TemplateDeclaration *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}

bool XmlAstWriter_AstVisitor::visitTemplateParameter(TemplateParameter *obj) {
  if (wasVisitedAST(obj)) return false;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << obj->kindName();
  ++depth;
  out << " _id=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '\n';
  if (indent) printIndentation();
  out << "loc=";
  outputXmlAttrQuoted(out, toXml_SourceLoc(obj->loc));
  if (obj && obj->var && shouldSerialize(obj->var)) {
    out << '\n';
    if (indent) printIndentation();
    out << "var=";
    /*catch-all*/outputXmlPointerQuoted(out, "TY", idmgr.uniqueId(obj->var));
  }
  switch(obj->kind()) {
  default: xfailure("bad tag"); break;
  case TemplateParameter::TP_TYPE: {
    TP_type *obj0 = obj->asTP_type();
  if (obj0->name) {
    out << '\n';
    if (indent) printIndentation();
    out << "name=";
    outputXmlAttrQuoted(out, obj0->name);
  } else {
  }
  if (obj0 && obj0->defaultType) {
    out << '\n';
    if (indent) printIndentation();
    out << "defaultType=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->defaultType));
  }
    obj0 = NULL;
    break;
    }
  case TemplateParameter::TP_NONTYPE: {
    TP_nontype *obj0 = obj->asTP_nontype();
  if (obj0 && obj0->param) {
    out << '\n';
    if (indent) printIndentation();
    out << "param=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->param));
  }
    obj0 = NULL;
    break;
    }
  case TemplateParameter::TP_TEMPLATE: {
    TP_template *obj0 = obj->asTP_template();
  if (obj0 && obj0->parameters) {
    out << '\n';
    if (indent) printIndentation();
    out << "parameters=";
    outputXmlPointerQuoted(out, "FL", uniqueIdAST(obj0->parameters));
  }
  if (obj0->name) {
    out << '\n';
    if (indent) printIndentation();
    out << "name=";
    outputXmlAttrQuoted(out, obj0->name);
  } else {
  }
  if (obj0 && obj0->defaultTemplate) {
    out << '\n';
    if (indent) printIndentation();
    out << "defaultTemplate=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->defaultTemplate));
  }
    obj0 = NULL;
    break;
    }
  }
  if (obj && obj->next) {
    out << '\n';
    if (indent) printIndentation();
    out << "next=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj->next));
  }
  --depth;
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitTemplateParameter(TemplateParameter *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}

bool XmlAstWriter_AstVisitor::visitTemplateArgument(TemplateArgument *obj) {
  if (wasVisitedAST(obj)) return false;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << obj->kindName();
  ++depth;
  out << " _id=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  switch(obj->kind()) {
  default: xfailure("bad tag"); break;
  case TemplateArgument::TA_TYPE: {
    TA_type *obj0 = obj->asTA_type();
  if (obj0 && obj0->type) {
    out << '\n';
    if (indent) printIndentation();
    out << "type=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->type));
  }
    obj0 = NULL;
    break;
    }
  case TemplateArgument::TA_NONTYPE: {
    TA_nontype *obj0 = obj->asTA_nontype();
  if (obj0 && obj0->expr) {
    out << '\n';
    if (indent) printIndentation();
    out << "expr=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->expr));
  }
    obj0 = NULL;
    break;
    }
  case TemplateArgument::TA_TEMPLATEUSED: {
    TA_templateUsed *obj0 = obj->asTA_templateUsed();
    obj0 = NULL;
    break;
    }
  }
  if (obj && obj->next) {
    out << '\n';
    if (indent) printIndentation();
    out << "next=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj->next));
  }
  --depth;
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitTemplateArgument(TemplateArgument *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}

bool XmlAstWriter_AstVisitor::visitNamespaceDecl(NamespaceDecl *obj) {
  if (wasVisitedAST(obj)) return false;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << obj->kindName();
  ++depth;
  out << " _id=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  switch(obj->kind()) {
  default: xfailure("bad tag"); break;
  case NamespaceDecl::ND_ALIAS: {
    ND_alias *obj0 = obj->asND_alias();
  if (obj0->alias) {
    out << '\n';
    if (indent) printIndentation();
    out << "alias=";
    outputXmlAttrQuoted(out, obj0->alias);
  } else {
  }
  if (obj0 && obj0->original) {
    out << '\n';
    if (indent) printIndentation();
    out << "original=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->original));
  }
    obj0 = NULL;
    break;
    }
  case NamespaceDecl::ND_USINGDECL: {
    ND_usingDecl *obj0 = obj->asND_usingDecl();
  if (obj0 && obj0->name) {
    out << '\n';
    if (indent) printIndentation();
    out << "name=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->name));
  }
    obj0 = NULL;
    break;
    }
  case NamespaceDecl::ND_USINGDIR: {
    ND_usingDir *obj0 = obj->asND_usingDir();
  if (obj0 && obj0->name) {
    out << '\n';
    if (indent) printIndentation();
    out << "name=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->name));
  }
    obj0 = NULL;
    break;
    }
  }
  --depth;
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitNamespaceDecl(NamespaceDecl *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}

bool XmlAstWriter_AstVisitor::visitFullExpressionAnnot(FullExpressionAnnot *obj) {
  if (wasVisitedAST(obj)) return false;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << obj->kindName();
  ++depth;
  out << " _id=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  if (obj && obj->declarations.isNotEmpty()) {
    out << '\n';
    if (indent) printIndentation();
    out << "declarations=";
    outputXmlPointerQuoted(out, "AL", uniqueIdAST(&(obj->declarations)));
  }
  --depth;
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitFullExpressionAnnot(FullExpressionAnnot *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}

bool XmlAstWriter_AstVisitor::visitASTTypeof(ASTTypeof *obj) {
  if (wasVisitedAST(obj)) return false;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << obj->kindName();
  ++depth;
  out << " _id=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  if (obj && obj->type) {
    out << '\n';
    if (indent) printIndentation();
    out << "type=";
    /*catch-all*/outputXmlPointerQuoted(out, "TY", idmgr.uniqueId(obj->type));
  }
  switch(obj->kind()) {
  default: xfailure("bad tag"); break;
  case ASTTypeof::TS_TYPEOF_EXPR: {
    TS_typeof_expr *obj0 = obj->asTS_typeof_expr();
  if (obj0 && obj0->expr) {
    out << '\n';
    if (indent) printIndentation();
    out << "expr=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->expr));
  }
    obj0 = NULL;
    break;
    }
  case ASTTypeof::TS_TYPEOF_TYPE: {
    TS_typeof_type *obj0 = obj->asTS_typeof_type();
  if (obj0 && obj0->atype) {
    out << '\n';
    if (indent) printIndentation();
    out << "atype=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->atype));
  }
    obj0 = NULL;
    break;
    }
  }
  --depth;
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitASTTypeof(ASTTypeof *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}

bool XmlAstWriter_AstVisitor::visitDesignator(Designator *obj) {
  if (wasVisitedAST(obj)) return false;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << obj->kindName();
  ++depth;
  out << " _id=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '\n';
  if (indent) printIndentation();
  out << "loc=";
  outputXmlAttrQuoted(out, toXml_SourceLoc(obj->loc));
  switch(obj->kind()) {
  default: xfailure("bad tag"); break;
  case Designator::FIELDDESIGNATOR: {
    FieldDesignator *obj0 = obj->asFieldDesignator();
  if (obj0->id) {
    out << '\n';
    if (indent) printIndentation();
    out << "id=";
    outputXmlAttrQuoted(out, obj0->id);
  } else {
  }
    obj0 = NULL;
    break;
    }
  case Designator::SUBSCRIPTDESIGNATOR: {
    SubscriptDesignator *obj0 = obj->asSubscriptDesignator();
  if (obj0 && obj0->idx_expr) {
    out << '\n';
    if (indent) printIndentation();
    out << "idx_expr=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->idx_expr));
  }
  if (obj0 && obj0->idx_expr2) {
    out << '\n';
    if (indent) printIndentation();
    out << "idx_expr2=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->idx_expr2));
  }
  out << '\n';
  if (indent) printIndentation();
  out << "idx_computed=";
  outputXmlAttrQuotedNoEscape(out, toXml_int(obj0->idx_computed));
  out << '\n';
  if (indent) printIndentation();
  out << "idx_computed2=";
  outputXmlAttrQuotedNoEscape(out, toXml_int(obj0->idx_computed2));
    obj0 = NULL;
    break;
    }
  }
  --depth;
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitDesignator(Designator *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}

bool XmlAstWriter_AstVisitor::visitAttributeSpecifierList(AttributeSpecifierList *obj) {
  if (wasVisitedAST(obj)) return false;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << obj->kindName();
  ++depth;
  out << " _id=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  if (obj && obj->spec) {
    out << '\n';
    if (indent) printIndentation();
    out << "spec=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj->spec));
  }
  if (obj && obj->next) {
    out << '\n';
    if (indent) printIndentation();
    out << "next=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj->next));
  }
  --depth;
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitAttributeSpecifierList(AttributeSpecifierList *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}

bool XmlAstWriter_AstVisitor::visitAttributeSpecifier(AttributeSpecifier *obj) {
  if (wasVisitedAST(obj)) return false;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << obj->kindName();
  ++depth;
  out << " _id=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  if (obj && obj->attr) {
    out << '\n';
    if (indent) printIndentation();
    out << "attr=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj->attr));
  }
  if (obj && obj->next) {
    out << '\n';
    if (indent) printIndentation();
    out << "next=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj->next));
  }
  --depth;
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitAttributeSpecifier(AttributeSpecifier *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}

bool XmlAstWriter_AstVisitor::visitAttribute(Attribute *obj) {
  if (wasVisitedAST(obj)) return false;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << obj->kindName();
  ++depth;
  out << " _id=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '\n';
  if (indent) printIndentation();
  out << "loc=";
  outputXmlAttrQuoted(out, toXml_SourceLoc(obj->loc));
  switch(obj->kind()) {
  default: xfailure("bad tag"); break;
  case Attribute::AT_EMPTY: {
    AT_empty *obj0 = obj->asAT_empty();
    obj0 = NULL;
    break;
    }
  case Attribute::AT_WORD: {
    AT_word *obj0 = obj->asAT_word();
  if (obj0->w) {
    out << '\n';
    if (indent) printIndentation();
    out << "w=";
    outputXmlAttrQuoted(out, obj0->w);
  } else {
  }
    obj0 = NULL;
    break;
    }
  case Attribute::AT_FUNC: {
    AT_func *obj0 = obj->asAT_func();
  if (obj0->f) {
    out << '\n';
    if (indent) printIndentation();
    out << "f=";
    outputXmlAttrQuoted(out, obj0->f);
  } else {
  }
  if (obj0 && obj0->args) {
    out << '\n';
    if (indent) printIndentation();
    out << "args=";
    outputXmlPointerQuoted(out, "FL", uniqueIdAST(obj0->args));
  }
    obj0 = NULL;
    break;
    }
  }
  --depth;
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitAttribute(Attribute *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}


// List 'classes'
bool XmlAstWriter_AstVisitor::visitList_TranslationUnit_topForms(ASTList<TopForm>* obj) {
  if (obj->isNotEmpty()) {
    if(wasVisitedList_ASTList(obj)) return false;
    out << '\n';
    if (indent) printIndentation();
    out << "<List_TranslationUnit_topForms _id=";
    outputXmlPointerQuoted(out, "AL", uniqueIdAST(obj));
    out << '>';
    ++depth;
  };
  return true;
}

void XmlAstWriter_AstVisitor::postvisitList_TranslationUnit_topForms(ASTList<TopForm>* obj) {
  if (obj->isNotEmpty()) {
    --depth;
    out << '\n';
    if (indent) printIndentation();
    out << "</List_TranslationUnit_topForms>";
  }
}

bool XmlAstWriter_AstVisitor::visitListItem_TranslationUnit_topForms(TopForm *obj) {
  xassert(obj);
  out << '\n';
  if (indent) printIndentation();
  out << "<_List_Item" << " item=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitListItem_TranslationUnit_topForms(TopForm *obj) {
  xassert(obj);
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << "</_List_Item>";
}

bool XmlAstWriter_AstVisitor::visitList_TF_namespaceDefn_forms(ASTList<TopForm>* obj) {
  if (obj->isNotEmpty()) {
    if(wasVisitedList_ASTList(obj)) return false;
    out << '\n';
    if (indent) printIndentation();
    out << "<List_TF_namespaceDefn_forms _id=";
    outputXmlPointerQuoted(out, "AL", uniqueIdAST(obj));
    out << '>';
    ++depth;
  };
  return true;
}

void XmlAstWriter_AstVisitor::postvisitList_TF_namespaceDefn_forms(ASTList<TopForm>* obj) {
  if (obj->isNotEmpty()) {
    --depth;
    out << '\n';
    if (indent) printIndentation();
    out << "</List_TF_namespaceDefn_forms>";
  }
}

bool XmlAstWriter_AstVisitor::visitListItem_TF_namespaceDefn_forms(TopForm *obj) {
  xassert(obj);
  out << '\n';
  if (indent) printIndentation();
  out << "<_List_Item" << " item=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitListItem_TF_namespaceDefn_forms(TopForm *obj) {
  xassert(obj);
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << "</_List_Item>";
}

bool XmlAstWriter_AstVisitor::visitList_Function_inits(FakeList<MemberInit>* obj) {
  if (obj->isNotEmpty()) {
    if(wasVisitedList_FakeList(obj)) return false;
    out << '\n';
    if (indent) printIndentation();
    out << "<List_Function_inits _id=";
    outputXmlPointerQuoted(out, "FL", uniqueIdAST(obj));
    out << '>';
    ++depth;
  };
  return true;
}

void XmlAstWriter_AstVisitor::postvisitList_Function_inits(FakeList<MemberInit>* obj) {
  if (obj->isNotEmpty()) {
    --depth;
    out << '\n';
    if (indent) printIndentation();
    out << "</List_Function_inits>";
  }
}

bool XmlAstWriter_AstVisitor::visitListItem_Function_inits(MemberInit *obj) {
  xassert(obj);
  out << '\n';
  if (indent) printIndentation();
  out << "<_List_Item" << " item=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitListItem_Function_inits(MemberInit *obj) {
  xassert(obj);
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << "</_List_Item>";
}

bool XmlAstWriter_AstVisitor::visitList_Function_handlers(FakeList<Handler>* obj) {
  if (obj->isNotEmpty()) {
    if(wasVisitedList_FakeList(obj)) return false;
    out << '\n';
    if (indent) printIndentation();
    out << "<List_Function_handlers _id=";
    outputXmlPointerQuoted(out, "FL", uniqueIdAST(obj));
    out << '>';
    ++depth;
  };
  return true;
}

void XmlAstWriter_AstVisitor::postvisitList_Function_handlers(FakeList<Handler>* obj) {
  if (obj->isNotEmpty()) {
    --depth;
    out << '\n';
    if (indent) printIndentation();
    out << "</List_Function_handlers>";
  }
}

bool XmlAstWriter_AstVisitor::visitListItem_Function_handlers(Handler *obj) {
  xassert(obj);
  out << '\n';
  if (indent) printIndentation();
  out << "<_List_Item" << " item=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitListItem_Function_handlers(Handler *obj) {
  xassert(obj);
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << "</_List_Item>";
}

bool XmlAstWriter_AstVisitor::visitList_MemberInit_args(FakeList<ArgExpression>* obj) {
  if (obj->isNotEmpty()) {
    if(wasVisitedList_FakeList(obj)) return false;
    out << '\n';
    if (indent) printIndentation();
    out << "<List_MemberInit_args _id=";
    outputXmlPointerQuoted(out, "FL", uniqueIdAST(obj));
    out << '>';
    ++depth;
  };
  return true;
}

void XmlAstWriter_AstVisitor::postvisitList_MemberInit_args(FakeList<ArgExpression>* obj) {
  if (obj->isNotEmpty()) {
    --depth;
    out << '\n';
    if (indent) printIndentation();
    out << "</List_MemberInit_args>";
  }
}

bool XmlAstWriter_AstVisitor::visitListItem_MemberInit_args(ArgExpression *obj) {
  xassert(obj);
  out << '\n';
  if (indent) printIndentation();
  out << "<_List_Item" << " item=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitListItem_MemberInit_args(ArgExpression *obj) {
  xassert(obj);
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << "</_List_Item>";
}

bool XmlAstWriter_AstVisitor::visitList_MemberList_list(ASTList<Member>* obj) {
  if (obj->isNotEmpty()) {
    if(wasVisitedList_ASTList(obj)) return false;
    out << '\n';
    if (indent) printIndentation();
    out << "<List_MemberList_list _id=";
    outputXmlPointerQuoted(out, "AL", uniqueIdAST(obj));
    out << '>';
    ++depth;
  };
  return true;
}

void XmlAstWriter_AstVisitor::postvisitList_MemberList_list(ASTList<Member>* obj) {
  if (obj->isNotEmpty()) {
    --depth;
    out << '\n';
    if (indent) printIndentation();
    out << "</List_MemberList_list>";
  }
}

bool XmlAstWriter_AstVisitor::visitListItem_MemberList_list(Member *obj) {
  xassert(obj);
  out << '\n';
  if (indent) printIndentation();
  out << "<_List_Item" << " item=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitListItem_MemberList_list(Member *obj) {
  xassert(obj);
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << "</_List_Item>";
}

bool XmlAstWriter_AstVisitor::visitList_Declaration_decllist(FakeList<Declarator>* obj) {
  if (obj->isNotEmpty()) {
    if(wasVisitedList_FakeList(obj)) return false;
    out << '\n';
    if (indent) printIndentation();
    out << "<List_Declaration_decllist _id=";
    outputXmlPointerQuoted(out, "FL", uniqueIdAST(obj));
    out << '>';
    ++depth;
  };
  return true;
}

void XmlAstWriter_AstVisitor::postvisitList_Declaration_decllist(FakeList<Declarator>* obj) {
  if (obj->isNotEmpty()) {
    --depth;
    out << '\n';
    if (indent) printIndentation();
    out << "</List_Declaration_decllist>";
  }
}

bool XmlAstWriter_AstVisitor::visitListItem_Declaration_decllist(Declarator *obj) {
  xassert(obj);
  out << '\n';
  if (indent) printIndentation();
  out << "<_List_Item" << " item=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitListItem_Declaration_decllist(Declarator *obj) {
  xassert(obj);
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << "</_List_Item>";
}

bool XmlAstWriter_AstVisitor::visitList_TS_classSpec_bases(FakeList<BaseClassSpec>* obj) {
  if (obj->isNotEmpty()) {
    if(wasVisitedList_FakeList(obj)) return false;
    out << '\n';
    if (indent) printIndentation();
    out << "<List_TS_classSpec_bases _id=";
    outputXmlPointerQuoted(out, "FL", uniqueIdAST(obj));
    out << '>';
    ++depth;
  };
  return true;
}

void XmlAstWriter_AstVisitor::postvisitList_TS_classSpec_bases(FakeList<BaseClassSpec>* obj) {
  if (obj->isNotEmpty()) {
    --depth;
    out << '\n';
    if (indent) printIndentation();
    out << "</List_TS_classSpec_bases>";
  }
}

bool XmlAstWriter_AstVisitor::visitListItem_TS_classSpec_bases(BaseClassSpec *obj) {
  xassert(obj);
  out << '\n';
  if (indent) printIndentation();
  out << "<_List_Item" << " item=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitListItem_TS_classSpec_bases(BaseClassSpec *obj) {
  xassert(obj);
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << "</_List_Item>";
}

bool XmlAstWriter_AstVisitor::visitList_TS_enumSpec_elts(FakeList<Enumerator>* obj) {
  if (obj->isNotEmpty()) {
    if(wasVisitedList_FakeList(obj)) return false;
    out << '\n';
    if (indent) printIndentation();
    out << "<List_TS_enumSpec_elts _id=";
    outputXmlPointerQuoted(out, "FL", uniqueIdAST(obj));
    out << '>';
    ++depth;
  };
  return true;
}

void XmlAstWriter_AstVisitor::postvisitList_TS_enumSpec_elts(FakeList<Enumerator>* obj) {
  if (obj->isNotEmpty()) {
    --depth;
    out << '\n';
    if (indent) printIndentation();
    out << "</List_TS_enumSpec_elts>";
  }
}

bool XmlAstWriter_AstVisitor::visitListItem_TS_enumSpec_elts(Enumerator *obj) {
  xassert(obj);
  out << '\n';
  if (indent) printIndentation();
  out << "<_List_Item" << " item=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitListItem_TS_enumSpec_elts(Enumerator *obj) {
  xassert(obj);
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << "</_List_Item>";
}

bool XmlAstWriter_AstVisitor::visitList_D_func_params(FakeList<ASTTypeId>* obj) {
  if (obj->isNotEmpty()) {
    if(wasVisitedList_FakeList(obj)) return false;
    out << '\n';
    if (indent) printIndentation();
    out << "<List_D_func_params _id=";
    outputXmlPointerQuoted(out, "FL", uniqueIdAST(obj));
    out << '>';
    ++depth;
  };
  return true;
}

void XmlAstWriter_AstVisitor::postvisitList_D_func_params(FakeList<ASTTypeId>* obj) {
  if (obj->isNotEmpty()) {
    --depth;
    out << '\n';
    if (indent) printIndentation();
    out << "</List_D_func_params>";
  }
}

bool XmlAstWriter_AstVisitor::visitListItem_D_func_params(ASTTypeId *obj) {
  xassert(obj);
  out << '\n';
  if (indent) printIndentation();
  out << "<_List_Item" << " item=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitListItem_D_func_params(ASTTypeId *obj) {
  xassert(obj);
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << "</_List_Item>";
}

bool XmlAstWriter_AstVisitor::visitList_D_func_kAndR_params(FakeList<PQ_name>* obj) {
  if (obj->isNotEmpty()) {
    if(wasVisitedList_FakeList(obj)) return false;
    out << '\n';
    if (indent) printIndentation();
    out << "<List_D_func_kAndR_params _id=";
    outputXmlPointerQuoted(out, "FL", uniqueIdAST(obj));
    out << '>';
    ++depth;
  };
  return true;
}

void XmlAstWriter_AstVisitor::postvisitList_D_func_kAndR_params(FakeList<PQ_name>* obj) {
  if (obj->isNotEmpty()) {
    --depth;
    out << '\n';
    if (indent) printIndentation();
    out << "</List_D_func_kAndR_params>";
  }
}

bool XmlAstWriter_AstVisitor::visitListItem_D_func_kAndR_params(PQ_name *obj) {
  xassert(obj);
  out << '\n';
  if (indent) printIndentation();
  out << "<_List_Item" << " item=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitListItem_D_func_kAndR_params(PQ_name *obj) {
  xassert(obj);
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << "</_List_Item>";
}

bool XmlAstWriter_AstVisitor::visitList_S_try_handlers(FakeList<Handler>* obj) {
  if (obj->isNotEmpty()) {
    if(wasVisitedList_FakeList(obj)) return false;
    out << '\n';
    if (indent) printIndentation();
    out << "<List_S_try_handlers _id=";
    outputXmlPointerQuoted(out, "FL", uniqueIdAST(obj));
    out << '>';
    ++depth;
  };
  return true;
}

void XmlAstWriter_AstVisitor::postvisitList_S_try_handlers(FakeList<Handler>* obj) {
  if (obj->isNotEmpty()) {
    --depth;
    out << '\n';
    if (indent) printIndentation();
    out << "</List_S_try_handlers>";
  }
}

bool XmlAstWriter_AstVisitor::visitListItem_S_try_handlers(Handler *obj) {
  xassert(obj);
  out << '\n';
  if (indent) printIndentation();
  out << "<_List_Item" << " item=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitListItem_S_try_handlers(Handler *obj) {
  xassert(obj);
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << "</_List_Item>";
}

bool XmlAstWriter_AstVisitor::visitList_ExceptionSpec_types(FakeList<ASTTypeId>* obj) {
  if (obj->isNotEmpty()) {
    if(wasVisitedList_FakeList(obj)) return false;
    out << '\n';
    if (indent) printIndentation();
    out << "<List_ExceptionSpec_types _id=";
    outputXmlPointerQuoted(out, "FL", uniqueIdAST(obj));
    out << '>';
    ++depth;
  };
  return true;
}

void XmlAstWriter_AstVisitor::postvisitList_ExceptionSpec_types(FakeList<ASTTypeId>* obj) {
  if (obj->isNotEmpty()) {
    --depth;
    out << '\n';
    if (indent) printIndentation();
    out << "</List_ExceptionSpec_types>";
  }
}

bool XmlAstWriter_AstVisitor::visitListItem_ExceptionSpec_types(ASTTypeId *obj) {
  xassert(obj);
  out << '\n';
  if (indent) printIndentation();
  out << "<_List_Item" << " item=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitListItem_ExceptionSpec_types(ASTTypeId *obj) {
  xassert(obj);
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << "</_List_Item>";
}

bool XmlAstWriter_AstVisitor::visitList_S_compound_stmts(ASTList<Statement>* obj) {
  if (obj->isNotEmpty()) {
    if(wasVisitedList_ASTList(obj)) return false;
    out << '\n';
    if (indent) printIndentation();
    out << "<List_S_compound_stmts _id=";
    outputXmlPointerQuoted(out, "AL", uniqueIdAST(obj));
    out << '>';
    ++depth;
  };
  return true;
}

void XmlAstWriter_AstVisitor::postvisitList_S_compound_stmts(ASTList<Statement>* obj) {
  if (obj->isNotEmpty()) {
    --depth;
    out << '\n';
    if (indent) printIndentation();
    out << "</List_S_compound_stmts>";
  }
}

bool XmlAstWriter_AstVisitor::visitListItem_S_compound_stmts(Statement *obj) {
  xassert(obj);
  out << '\n';
  if (indent) printIndentation();
  out << "<_List_Item" << " item=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitListItem_S_compound_stmts(Statement *obj) {
  xassert(obj);
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << "</_List_Item>";
}

bool XmlAstWriter_AstVisitor::visitList_E_funCall_args(FakeList<ArgExpression>* obj) {
  if (obj->isNotEmpty()) {
    if(wasVisitedList_FakeList(obj)) return false;
    out << '\n';
    if (indent) printIndentation();
    out << "<List_E_funCall_args _id=";
    outputXmlPointerQuoted(out, "FL", uniqueIdAST(obj));
    out << '>';
    ++depth;
  };
  return true;
}

void XmlAstWriter_AstVisitor::postvisitList_E_funCall_args(FakeList<ArgExpression>* obj) {
  if (obj->isNotEmpty()) {
    --depth;
    out << '\n';
    if (indent) printIndentation();
    out << "</List_E_funCall_args>";
  }
}

bool XmlAstWriter_AstVisitor::visitListItem_E_funCall_args(ArgExpression *obj) {
  xassert(obj);
  out << '\n';
  if (indent) printIndentation();
  out << "<_List_Item" << " item=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitListItem_E_funCall_args(ArgExpression *obj) {
  xassert(obj);
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << "</_List_Item>";
}

bool XmlAstWriter_AstVisitor::visitList_E_constructor_args(FakeList<ArgExpression>* obj) {
  if (obj->isNotEmpty()) {
    if(wasVisitedList_FakeList(obj)) return false;
    out << '\n';
    if (indent) printIndentation();
    out << "<List_E_constructor_args _id=";
    outputXmlPointerQuoted(out, "FL", uniqueIdAST(obj));
    out << '>';
    ++depth;
  };
  return true;
}

void XmlAstWriter_AstVisitor::postvisitList_E_constructor_args(FakeList<ArgExpression>* obj) {
  if (obj->isNotEmpty()) {
    --depth;
    out << '\n';
    if (indent) printIndentation();
    out << "</List_E_constructor_args>";
  }
}

bool XmlAstWriter_AstVisitor::visitListItem_E_constructor_args(ArgExpression *obj) {
  xassert(obj);
  out << '\n';
  if (indent) printIndentation();
  out << "<_List_Item" << " item=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitListItem_E_constructor_args(ArgExpression *obj) {
  xassert(obj);
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << "</_List_Item>";
}

bool XmlAstWriter_AstVisitor::visitList_E_new_placementArgs(FakeList<ArgExpression>* obj) {
  if (obj->isNotEmpty()) {
    if(wasVisitedList_FakeList(obj)) return false;
    out << '\n';
    if (indent) printIndentation();
    out << "<List_E_new_placementArgs _id=";
    outputXmlPointerQuoted(out, "FL", uniqueIdAST(obj));
    out << '>';
    ++depth;
  };
  return true;
}

void XmlAstWriter_AstVisitor::postvisitList_E_new_placementArgs(FakeList<ArgExpression>* obj) {
  if (obj->isNotEmpty()) {
    --depth;
    out << '\n';
    if (indent) printIndentation();
    out << "</List_E_new_placementArgs>";
  }
}

bool XmlAstWriter_AstVisitor::visitListItem_E_new_placementArgs(ArgExpression *obj) {
  xassert(obj);
  out << '\n';
  if (indent) printIndentation();
  out << "<_List_Item" << " item=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitListItem_E_new_placementArgs(ArgExpression *obj) {
  xassert(obj);
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << "</_List_Item>";
}

bool XmlAstWriter_AstVisitor::visitList_ArgExpressionListOpt_list(FakeList<ArgExpression>* obj) {
  if (obj->isNotEmpty()) {
    if(wasVisitedList_FakeList(obj)) return false;
    out << '\n';
    if (indent) printIndentation();
    out << "<List_ArgExpressionListOpt_list _id=";
    outputXmlPointerQuoted(out, "FL", uniqueIdAST(obj));
    out << '>';
    ++depth;
  };
  return true;
}

void XmlAstWriter_AstVisitor::postvisitList_ArgExpressionListOpt_list(FakeList<ArgExpression>* obj) {
  if (obj->isNotEmpty()) {
    --depth;
    out << '\n';
    if (indent) printIndentation();
    out << "</List_ArgExpressionListOpt_list>";
  }
}

bool XmlAstWriter_AstVisitor::visitListItem_ArgExpressionListOpt_list(ArgExpression *obj) {
  xassert(obj);
  out << '\n';
  if (indent) printIndentation();
  out << "<_List_Item" << " item=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitListItem_ArgExpressionListOpt_list(ArgExpression *obj) {
  xassert(obj);
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << "</_List_Item>";
}

bool XmlAstWriter_AstVisitor::visitList_IN_compound_inits(ASTList<Initializer>* obj) {
  if (obj->isNotEmpty()) {
    if(wasVisitedList_ASTList(obj)) return false;
    out << '\n';
    if (indent) printIndentation();
    out << "<List_IN_compound_inits _id=";
    outputXmlPointerQuoted(out, "AL", uniqueIdAST(obj));
    out << '>';
    ++depth;
  };
  return true;
}

void XmlAstWriter_AstVisitor::postvisitList_IN_compound_inits(ASTList<Initializer>* obj) {
  if (obj->isNotEmpty()) {
    --depth;
    out << '\n';
    if (indent) printIndentation();
    out << "</List_IN_compound_inits>";
  }
}

bool XmlAstWriter_AstVisitor::visitListItem_IN_compound_inits(Initializer *obj) {
  xassert(obj);
  out << '\n';
  if (indent) printIndentation();
  out << "<_List_Item" << " item=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitListItem_IN_compound_inits(Initializer *obj) {
  xassert(obj);
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << "</_List_Item>";
}

bool XmlAstWriter_AstVisitor::visitList_IN_ctor_args(FakeList<ArgExpression>* obj) {
  if (obj->isNotEmpty()) {
    if(wasVisitedList_FakeList(obj)) return false;
    out << '\n';
    if (indent) printIndentation();
    out << "<List_IN_ctor_args _id=";
    outputXmlPointerQuoted(out, "FL", uniqueIdAST(obj));
    out << '>';
    ++depth;
  };
  return true;
}

void XmlAstWriter_AstVisitor::postvisitList_IN_ctor_args(FakeList<ArgExpression>* obj) {
  if (obj->isNotEmpty()) {
    --depth;
    out << '\n';
    if (indent) printIndentation();
    out << "</List_IN_ctor_args>";
  }
}

bool XmlAstWriter_AstVisitor::visitListItem_IN_ctor_args(ArgExpression *obj) {
  xassert(obj);
  out << '\n';
  if (indent) printIndentation();
  out << "<_List_Item" << " item=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitListItem_IN_ctor_args(ArgExpression *obj) {
  xassert(obj);
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << "</_List_Item>";
}

bool XmlAstWriter_AstVisitor::visitList_TP_template_parameters(FakeList<TemplateParameter>* obj) {
  if (obj->isNotEmpty()) {
    if(wasVisitedList_FakeList(obj)) return false;
    out << '\n';
    if (indent) printIndentation();
    out << "<List_TP_template_parameters _id=";
    outputXmlPointerQuoted(out, "FL", uniqueIdAST(obj));
    out << '>';
    ++depth;
  };
  return true;
}

void XmlAstWriter_AstVisitor::postvisitList_TP_template_parameters(FakeList<TemplateParameter>* obj) {
  if (obj->isNotEmpty()) {
    --depth;
    out << '\n';
    if (indent) printIndentation();
    out << "</List_TP_template_parameters>";
  }
}

bool XmlAstWriter_AstVisitor::visitListItem_TP_template_parameters(TemplateParameter *obj) {
  xassert(obj);
  out << '\n';
  if (indent) printIndentation();
  out << "<_List_Item" << " item=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitListItem_TP_template_parameters(TemplateParameter *obj) {
  xassert(obj);
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << "</_List_Item>";
}

bool XmlAstWriter_AstVisitor::visitList_IN_designated_designator_list(FakeList<Designator>* obj) {
  if (obj->isNotEmpty()) {
    if(wasVisitedList_FakeList(obj)) return false;
    out << '\n';
    if (indent) printIndentation();
    out << "<List_IN_designated_designator_list _id=";
    outputXmlPointerQuoted(out, "FL", uniqueIdAST(obj));
    out << '>';
    ++depth;
  };
  return true;
}

void XmlAstWriter_AstVisitor::postvisitList_IN_designated_designator_list(FakeList<Designator>* obj) {
  if (obj->isNotEmpty()) {
    --depth;
    out << '\n';
    if (indent) printIndentation();
    out << "</List_IN_designated_designator_list>";
  }
}

bool XmlAstWriter_AstVisitor::visitListItem_IN_designated_designator_list(Designator *obj) {
  xassert(obj);
  out << '\n';
  if (indent) printIndentation();
  out << "<_List_Item" << " item=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitListItem_IN_designated_designator_list(Designator *obj) {
  xassert(obj);
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << "</_List_Item>";
}

bool XmlAstWriter_AstVisitor::visitList_FullExpressionAnnot_declarations(ASTList<Declaration>* obj) {
  if (obj->isNotEmpty()) {
    if(wasVisitedList_ASTList(obj)) return false;
    out << '\n';
    if (indent) printIndentation();
    out << "<List_FullExpressionAnnot_declarations _id=";
    outputXmlPointerQuoted(out, "AL", uniqueIdAST(obj));
    out << '>';
    ++depth;
  };
  return true;
}

void XmlAstWriter_AstVisitor::postvisitList_FullExpressionAnnot_declarations(ASTList<Declaration>* obj) {
  if (obj->isNotEmpty()) {
    --depth;
    out << '\n';
    if (indent) printIndentation();
    out << "</List_FullExpressionAnnot_declarations>";
  }
}

bool XmlAstWriter_AstVisitor::visitListItem_FullExpressionAnnot_declarations(Declaration *obj) {
  xassert(obj);
  out << '\n';
  if (indent) printIndentation();
  out << "<_List_Item" << " item=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitListItem_FullExpressionAnnot_declarations(Declaration *obj) {
  xassert(obj);
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << "</_List_Item>";
}

bool XmlAstWriter_AstVisitor::visitList_AT_func_args(FakeList<ArgExpression>* obj) {
  if (obj->isNotEmpty()) {
    if(wasVisitedList_FakeList(obj)) return false;
    out << '\n';
    if (indent) printIndentation();
    out << "<List_AT_func_args _id=";
    outputXmlPointerQuoted(out, "FL", uniqueIdAST(obj));
    out << '>';
    ++depth;
  };
  return true;
}

void XmlAstWriter_AstVisitor::postvisitList_AT_func_args(FakeList<ArgExpression>* obj) {
  if (obj->isNotEmpty()) {
    --depth;
    out << '\n';
    if (indent) printIndentation();
    out << "</List_AT_func_args>";
  }
}

bool XmlAstWriter_AstVisitor::visitListItem_AT_func_args(ArgExpression *obj) {
  xassert(obj);
  out << '\n';
  if (indent) printIndentation();
  out << "<_List_Item" << " item=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '>';
  ++depth;
  return true;
}

void XmlAstWriter_AstVisitor::postvisitListItem_AT_func_args(ArgExpression *obj) {
  xassert(obj);
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << "</_List_Item>";
}



