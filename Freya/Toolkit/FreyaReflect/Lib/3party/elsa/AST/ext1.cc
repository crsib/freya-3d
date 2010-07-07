// ext1.cc
// *** DO NOT EDIT ***
// generated automatically by astgen, from example.ast
// active extension modules: ext1.ast

#include "ext1.h"      // this module
#include "xmlhelp.h"      // to/fromXml_bool/int
#include <string.h>       // strcmp
#include "exc.h"          // xformat


// ------------------ Node -------------------
// *** DO NOT EDIT ***
Node::~Node()
{
}

void Node::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, Node);

  PRINT_GENERIC(x);
  PRINT_GENERIC(y);
  PRINT_GENERIC(z);
  PRINT_GENERIC(w);
}

void Node::gdb() const
  { debugPrint(std::cout, 0); }

Node *Node::clone() const
{
  Node *ret = new Node(
    x,
    y,
    z
  );
  return ret;
}


// ------------------ NodeList -------------------
// *** DO NOT EDIT ***
NodeList::~NodeList()
{
}

char const * const NodeList::kindNames[NodeList::NUM_KINDS] = {
  "ASubclass",
  "AnotherSubclass",
};

void NodeList::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_FAKE_LIST(Node, list);
}

void NodeList::gdb() const
  { debugPrint(std::cout, 0); }

DEFN_AST_DOWNCASTS(NodeList, ASubclass, ASUBCLASS)

ASubclass::~ASubclass()
{
}

void ASubclass::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, ASubclass);

  NodeList::debugPrint(os, indent, subtreeName);

  PRINT_GENERIC(x);
}

ASubclass *ASubclass::clone() const
{
  ASubclass *ret = new ASubclass(
    cloneFakeList(list),
    x
  );
  return ret;
}

DEFN_AST_DOWNCASTS(NodeList, AnotherSubclass, ANOTHERSUBCLASS)

AnotherSubclass::~AnotherSubclass()
{
}

void AnotherSubclass::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, AnotherSubclass);

  NodeList::debugPrint(os, indent, subtreeName);

  PRINT_GENERIC(x);
}

AnotherSubclass *AnotherSubclass::clone() const
{
  AnotherSubclass *ret = new AnotherSubclass(
    cloneFakeList(list),
    x
  );
  return ret;
}


// ------------------ AnotherList -------------------
// *** DO NOT EDIT ***
AnotherList::~AnotherList()
{
  list2.deleteAll();
}

void AnotherList::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, AnotherList);

  PRINT_LIST(Node, list2);
  PRINT_GENERIC(str);
}

void AnotherList::gdb() const
  { debugPrint(std::cout, 0); }

AnotherList *AnotherList::clone() const
{
  AnotherList *ret = new AnotherList(
    cloneASTList(list2),
    str.clone()
  );
  return ret;
}


// ------------------ Super -------------------
// *** DO NOT EDIT ***
Super::~Super()
{
  delete p;
}

char const * const Super::kindNames[Super::NUM_KINDS] = {
  "Sub1",
  "Sub2",
  "SubWithDefault",
  "Sub3",
  "Sub4",
};

void Super::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_GENERIC(x);
}

void Super::gdb() const
  { debugPrint(std::cout, 0); }

DEFN_AST_DOWNCASTS(Super, Sub1, SUB1)

Sub1::~Sub1()
{
}

void Sub1::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, Sub1);

  Super::debugPrint(os, indent, subtreeName);

  PRINT_GENERIC(y);
}

Sub1 *Sub1::clone() const
{
  Sub1 *ret = new Sub1(
    x,
    y
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Super, Sub2, SUB2)

Sub2::~Sub2()
{
}

void Sub2::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, Sub2);

  Super::debugPrint(os, indent, subtreeName);

  PRINT_GENERIC(z);
}

Sub2 *Sub2::clone() const
{
  Sub2 *ret = new Sub2(
    x,
    z
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Super, SubWithDefault, SUBWITHDEFAULT)

SubWithDefault::~SubWithDefault()
{
}

void SubWithDefault::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, SubWithDefault);

  Super::debugPrint(os, indent, subtreeName);

  PRINT_GENERIC(q);
}

SubWithDefault *SubWithDefault::clone() const
{
  SubWithDefault *ret = new SubWithDefault(
    x,
    q
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Super, Sub3, SUB3)

Sub3::~Sub3()
{
  delete s1;
  delete s2;
}

void Sub3::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, Sub3);

  Super::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(s1);
  PRINT_SUBTREE(s2);
  PRINT_GENERIC(q);
}

Sub3 *Sub3::clone() const
{
  Sub3 *ret = new Sub3(
    x,
    s1? s1->clone() : NULL,
    s2? s2->clone() : NULL,
    q
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Super, Sub4, SUB4)

Sub4::~Sub4()
{
}

void Sub4::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, Sub4);

  Super::debugPrint(os, indent, subtreeName);

}

Sub4 *Sub4::clone() const
{
  Sub4 *ret = new Sub4(
    x
  );
  return ret;
}


char const *toString(AnEnum x)
{
  static char const * const map[] = {
    "AE_ONE",
    "AE_TWO",
    "AE_THREE",
    "AE_FOUR",
  };
  xassert((unsigned)x < TABLESIZE(map));
  return map[x];
};

void fromXml(AnEnum &out, rostring str)
{
  for (int i=0; i<4; i++) {
    AnEnum e = (AnEnum)i;
    if (0==strcmp(str, toString(e))) {
      out = e;
      return;
    }
  }
  xformat(stringc << "bad AnEnum value: " << str);
}


char const *toString(AnotherEnum x)
{
  static char const * const map[] = {
    "anotherone",
    "anothertwo",
    "anotherthree",
  };
  xassert((unsigned)x < TABLESIZE(map));
  return map[x];
};

void fromXml(AnotherEnum &out, rostring str)
{
  for (int i=0; i<3; i++) {
    AnotherEnum e = (AnotherEnum)i;
    if (0==strcmp(str, toString(e))) {
      out = e;
      return;
    }
  }
  xformat(stringc << "bad AnotherEnum value: " << str);
}


// ------------------ UsesEnum -------------------
// *** DO NOT EDIT ***
UsesEnum::~UsesEnum()
{
}

char const * const UsesEnum::kindNames[UsesEnum::NUM_KINDS] = {
  "UE_a",
  "UE_b",
};

void UsesEnum::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
}

void UsesEnum::gdb() const
  { debugPrint(std::cout, 0); }

DEFN_AST_DOWNCASTS(UsesEnum, UE_a, UE_A)

UE_a::~UE_a()
{
}

void UE_a::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, UE_a);

  UsesEnum::debugPrint(os, indent, subtreeName);

  PRINT_GENERIC(x);
}

UE_a *UE_a::clone() const
{
  UE_a *ret = new UE_a(
    x
  );
  return ret;
}

DEFN_AST_DOWNCASTS(UsesEnum, UE_b, UE_B)

UE_b::~UE_b()
{
}

void UE_b::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, UE_b);

  UsesEnum::debugPrint(os, indent, subtreeName);

  PRINT_GENERIC(y);
}

UE_b *UE_b::clone() const
{
  UE_b *ret = new UE_b(
    y
  );
  return ret;
}


// ------------------ InheritsSomething -------------------
// *** DO NOT EDIT ***
InheritsSomething::~InheritsSomething()
{
}

char const * const InheritsSomething::kindNames[InheritsSomething::NUM_KINDS] = {
  "IS_a",
  "IS_b",
  "IS_c",
  "IS_d",
};

void InheritsSomething::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
}

void InheritsSomething::gdb() const
  { debugPrint(std::cout, 0); }

DEFN_AST_DOWNCASTS(InheritsSomething, IS_a, IS_A)

IS_a::~IS_a()
{
}

void IS_a::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, IS_a);

  InheritsSomething::debugPrint(os, indent, subtreeName);

  PRINT_GENERIC(z);
}

IS_a *IS_a::clone() const
{
  IS_a *ret = new IS_a(
    z
  );
  return ret;
}

DEFN_AST_DOWNCASTS(InheritsSomething, IS_b, IS_B)

IS_b::~IS_b()
{
}

void IS_b::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, IS_b);

  InheritsSomething::debugPrint(os, indent, subtreeName);

  PRINT_GENERIC(q);
}

IS_b *IS_b::clone() const
{
  IS_b *ret = new IS_b(
    q
  );
  return ret;
}

DEFN_AST_DOWNCASTS(InheritsSomething, IS_c, IS_C)

IS_c::~IS_c()
{
}

void IS_c::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, IS_c);

  InheritsSomething::debugPrint(os, indent, subtreeName);

  PRINT_GENERIC(ret);
}

IS_c *IS_c::clone() const
{
  IS_c *ret = new IS_c(
    this->ret
  );
  return ret;
}

DEFN_AST_DOWNCASTS(InheritsSomething, IS_d, IS_D)

IS_d::~IS_d()
{
  delete ret;
}

void IS_d::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, IS_d);

  InheritsSomething::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(ret);
}

IS_d *IS_d::clone() const
{
  IS_d *ret = new IS_d(
    this->ret? this->ret->clone() : NULL
  );
  return ret;
}


// ------------------ HasLastArgs -------------------
// *** DO NOT EDIT ***
HasLastArgs::~HasLastArgs()
{
}

char const * const HasLastArgs::kindNames[HasLastArgs::NUM_KINDS] = {
  "Hla1",
  "Hla2",
};

void HasLastArgs::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_GENERIC(x);
  // (lastArgs are printed by subclasses)
}

void HasLastArgs::gdb() const
  { debugPrint(std::cout, 0); }

DEFN_AST_DOWNCASTS(HasLastArgs, Hla1, HLA1)

Hla1::~Hla1()
{
}

void Hla1::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, Hla1);

  HasLastArgs::debugPrint(os, indent, subtreeName);

  PRINT_GENERIC(y);
  PRINT_GENERIC(w);
}

Hla1 *Hla1::clone() const
{
  Hla1 *ret = new Hla1(
    x,
    y,
    w
  );
  return ret;
}

DEFN_AST_DOWNCASTS(HasLastArgs, Hla2, HLA2)

Hla2::~Hla2()
{
}

void Hla2::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, Hla2);

  HasLastArgs::debugPrint(os, indent, subtreeName);

  PRINT_GENERIC(y);
  PRINT_GENERIC(z);
  PRINT_GENERIC(w);
}

Hla2 *Hla2::clone() const
{
  Hla2 *ret = new Hla2(
    x,
    y,
    z,
    w
  );
  return ret;
}


// ------------------ SomethingElse -------------------
// *** DO NOT EDIT ***
SomethingElse::~SomethingElse()
{
}

void SomethingElse::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, SomethingElse);

  PRINT_GENERIC(x);
  PRINT_GENERIC(y);
}

void SomethingElse::gdb() const
  { debugPrint(std::cout, 0); }

SomethingElse *SomethingElse::clone() const
{
   return new SomethingElse(x,y); /*my own clone() code*/ ;
}


// ------------------ ANewClass -------------------
// *** DO NOT EDIT ***
ANewClass::~ANewClass()
{
}

void ANewClass::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, ANewClass);

  PRINT_GENERIC(foo);
}

void ANewClass::gdb() const
  { debugPrint(std::cout, 0); }

ANewClass *ANewClass::clone() const
{
  ANewClass *ret = new ANewClass(
    foo
  );
  return ret;
}




// ---------------------- ExampleVisitor ---------------------
// default no-op visitor
ExampleVisitor::~ExampleVisitor() {}
bool ExampleVisitor::visitNode(Node *obj) { return true; }
void ExampleVisitor::postvisitNode(Node *obj) {}
bool ExampleVisitor::visitNodeList(NodeList *obj) { return true; }
void ExampleVisitor::postvisitNodeList(NodeList *obj) {}
bool ExampleVisitor::visitAnotherList(AnotherList *obj) { return true; }
void ExampleVisitor::postvisitAnotherList(AnotherList *obj) {}
bool ExampleVisitor::visitSuper(Super *obj) { return true; }
void ExampleVisitor::postvisitSuper(Super *obj) {}
bool ExampleVisitor::visitUsesEnum(UsesEnum *obj) { return true; }
void ExampleVisitor::postvisitUsesEnum(UsesEnum *obj) {}
bool ExampleVisitor::visitInheritsSomething(InheritsSomething *obj) { return true; }
void ExampleVisitor::postvisitInheritsSomething(InheritsSomething *obj) {}
bool ExampleVisitor::visitHasLastArgs(HasLastArgs *obj) { return true; }
void ExampleVisitor::postvisitHasLastArgs(HasLastArgs *obj) {}
bool ExampleVisitor::visitSomethingElse(SomethingElse *obj) { return true; }
void ExampleVisitor::postvisitSomethingElse(SomethingElse *obj) {}
bool ExampleVisitor::visitANewClass(ANewClass *obj) { return true; }
void ExampleVisitor::postvisitANewClass(ANewClass *obj) {}

// List 'classes'
bool ExampleVisitor::visitList_NodeList_list(FakeList<Node>*) { return true; }
void ExampleVisitor::postvisitList_NodeList_list(FakeList<Node>*) {}
bool ExampleVisitor::visitList_AnotherList_list2(ASTList<Node>*) { return true; }
void ExampleVisitor::postvisitList_AnotherList_list2(ASTList<Node>*) {}
bool ExampleVisitor::visitListItem_NodeList_list(Node*) { return true; }
void ExampleVisitor::postvisitListItem_NodeList_list(Node*) {}
bool ExampleVisitor::visitListItem_AnotherList_list2(Node*) { return true; }
void ExampleVisitor::postvisitListItem_AnotherList_list2(Node*) {}


void Node::traverse(ExampleVisitor &vis)
{
  if (!vis.visitNode(this)) { return; }

   next->traverse(vis); ;
  vis.postvisitNode(this);
}

void NodeList::traverse(ExampleVisitor &vis)
{
  // no 'visit' because it's handled by subclasses

  if (vis.visitList_NodeList_list(list)) {
    FAKELIST_FOREACH_NC(Node, list, iter) {
      if (vis.visitListItem_NodeList_list(iter)) {
        iter->traverse(vis);
        vis.postvisitListItem_NodeList_list(iter);
      }
    }
    vis.postvisitList_NodeList_list(list);
  }
  // no 'postvisit' either
}

void ASubclass::traverse(ExampleVisitor &vis)
{
  if (!vis.visitNodeList(this)) { return; }

  NodeList::traverse(vis);

  vis.postvisitNodeList(this);
}

void AnotherSubclass::traverse(ExampleVisitor &vis)
{
  if (!vis.visitNodeList(this)) { return; }

  NodeList::traverse(vis);

  vis.postvisitNodeList(this);
}

void AnotherList::traverse(ExampleVisitor &vis)
{
  if (!vis.visitAnotherList(this)) { return; }

  if (vis.visitList_AnotherList_list2(&list2)) {
    FOREACH_ASTLIST_NC(Node, list2, iter) {
      if (vis.visitListItem_AnotherList_list2(iter.data())) {
        iter.data()->traverse(vis);
        vis.postvisitListItem_AnotherList_list2(iter.data());
      }
    }
    vis.postvisitList_AnotherList_list2(&list2);
  }
  vis.postvisitAnotherList(this);
}

void Super::traverse(ExampleVisitor &vis)
{
  // no 'visit' because it's handled by subclasses

  // no 'postvisit' either
}

void Sub1::traverse(ExampleVisitor &vis)
{
  if (!vis.visitSuper(this)) { return; }

  Super::traverse(vis);

  vis.postvisitSuper(this);
}

void Sub2::traverse(ExampleVisitor &vis)
{
  if (!vis.visitSuper(this)) { return; }

  Super::traverse(vis);

  vis.postvisitSuper(this);
}

void SubWithDefault::traverse(ExampleVisitor &vis)
{
  if (!vis.visitSuper(this)) { return; }

  Super::traverse(vis);

  vis.postvisitSuper(this);
}

void Sub3::traverse(ExampleVisitor &vis)
{
  if (!vis.visitSuper(this)) { return; }

  Super::traverse(vis);

  if (s1) { s1->traverse(vis); }
  if (s2) { s2->traverse(vis); }
  vis.postvisitSuper(this);
}

void Sub4::traverse(ExampleVisitor &vis)
{
  if (!vis.visitSuper(this)) { return; }

  Super::traverse(vis);

  vis.postvisitSuper(this);
}

void UsesEnum::traverse(ExampleVisitor &vis)
{
  // no 'visit' because it's handled by subclasses

  // no 'postvisit' either
}

void UE_a::traverse(ExampleVisitor &vis)
{
  if (!vis.visitUsesEnum(this)) { return; }

  UsesEnum::traverse(vis);

  vis.postvisitUsesEnum(this);
}

void UE_b::traverse(ExampleVisitor &vis)
{
  if (!vis.visitUsesEnum(this)) { return; }

  UsesEnum::traverse(vis);

  vis.postvisitUsesEnum(this);
}

void InheritsSomething::traverse(ExampleVisitor &vis)
{
  // no 'visit' because it's handled by subclasses

  // no 'postvisit' either
}

void IS_a::traverse(ExampleVisitor &vis)
{
  if (!vis.visitInheritsSomething(this)) { return; }

  InheritsSomething::traverse(vis);

  vis.postvisitInheritsSomething(this);
}

void IS_b::traverse(ExampleVisitor &vis)
{
  if (!vis.visitInheritsSomething(this)) { return; }

  InheritsSomething::traverse(vis);

  vis.postvisitInheritsSomething(this);
}

void IS_c::traverse(ExampleVisitor &vis)
{
  if (!vis.visitInheritsSomething(this)) { return; }

  InheritsSomething::traverse(vis);

  vis.postvisitInheritsSomething(this);
}

void IS_d::traverse(ExampleVisitor &vis)
{
  if (!vis.visitInheritsSomething(this)) { return; }

  InheritsSomething::traverse(vis);

  if (ret) { ret->traverse(vis); }
  vis.postvisitInheritsSomething(this);
}

void HasLastArgs::traverse(ExampleVisitor &vis)
{
  // no 'visit' because it's handled by subclasses

  // no 'postvisit' either
}

void Hla1::traverse(ExampleVisitor &vis)
{
  if (!vis.visitHasLastArgs(this)) { return; }

  HasLastArgs::traverse(vis);

  vis.postvisitHasLastArgs(this);
}

void Hla2::traverse(ExampleVisitor &vis)
{
  if (!vis.visitHasLastArgs(this)) { return; }

  HasLastArgs::traverse(vis);

  vis.postvisitHasLastArgs(this);
}

void SomethingElse::traverse(ExampleVisitor &vis)
{
  if (!vis.visitSomethingElse(this)) { return; }

  vis.postvisitSomethingElse(this);
}

void ANewClass::traverse(ExampleVisitor &vis)
{
  if (!vis.visitANewClass(this)) { return; }

  vis.postvisitANewClass(this);
}


// ---------------------- ExampleDVisitor ---------------------
bool ExampleDVisitor::wasVisitedAST(void *ast)
{
  if (!ast) {return false;} // avoid NULL; actually happens for FakeLists
  if (wasVisitedASTNodes.contains(ast)) {
    return true;
  } else {
    wasVisitedASTNodes.add(ast);
    return false;
  }
}

bool ExampleDVisitor::wasVisitedList_ASTList(void *ast)
{
  if (!ast) {return false;} // avoid NULL; actually happens for FakeLists
  if (wasVisitedList_ASTListNodes.contains(ast)) {
    return true;
  } else {
    wasVisitedList_ASTListNodes.add(ast);
    return false;
  }
}

bool ExampleDVisitor::wasVisitedList_FakeList(void *ast)
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
bool ExampleDVisitor::visitNode(Node *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitNode(obj) : true;
}
void ExampleDVisitor::postvisitNode(Node *obj) {
  if (client) {
    client->postvisitNode(obj);
  }
}
bool ExampleDVisitor::visitNodeList(NodeList *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitNodeList(obj) : true;
}
void ExampleDVisitor::postvisitNodeList(NodeList *obj) {
  if (client) {
    client->postvisitNodeList(obj);
  }
}
bool ExampleDVisitor::visitAnotherList(AnotherList *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitAnotherList(obj) : true;
}
void ExampleDVisitor::postvisitAnotherList(AnotherList *obj) {
  if (client) {
    client->postvisitAnotherList(obj);
  }
}
bool ExampleDVisitor::visitSuper(Super *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitSuper(obj) : true;
}
void ExampleDVisitor::postvisitSuper(Super *obj) {
  if (client) {
    client->postvisitSuper(obj);
  }
}
bool ExampleDVisitor::visitUsesEnum(UsesEnum *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitUsesEnum(obj) : true;
}
void ExampleDVisitor::postvisitUsesEnum(UsesEnum *obj) {
  if (client) {
    client->postvisitUsesEnum(obj);
  }
}
bool ExampleDVisitor::visitInheritsSomething(InheritsSomething *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitInheritsSomething(obj) : true;
}
void ExampleDVisitor::postvisitInheritsSomething(InheritsSomething *obj) {
  if (client) {
    client->postvisitInheritsSomething(obj);
  }
}
bool ExampleDVisitor::visitHasLastArgs(HasLastArgs *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitHasLastArgs(obj) : true;
}
void ExampleDVisitor::postvisitHasLastArgs(HasLastArgs *obj) {
  if (client) {
    client->postvisitHasLastArgs(obj);
  }
}
bool ExampleDVisitor::visitSomethingElse(SomethingElse *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitSomethingElse(obj) : true;
}
void ExampleDVisitor::postvisitSomethingElse(SomethingElse *obj) {
  if (client) {
    client->postvisitSomethingElse(obj);
  }
}
bool ExampleDVisitor::visitANewClass(ANewClass *obj) {
  if (ensureOneVisit) xassert(!wasVisitedAST(obj));
  return client ? client->visitANewClass(obj) : true;
}
void ExampleDVisitor::postvisitANewClass(ANewClass *obj) {
  if (client) {
    client->postvisitANewClass(obj);
  }
}

// List 'classes'
bool ExampleDVisitor::visitList_NodeList_list(FakeList<Node>* obj) {
  if (ensureOneVisit) xassert(!wasVisitedList_FakeList(obj));
  return client ? client->visitList_NodeList_list(obj) : true;
}
void ExampleDVisitor::postvisitList_NodeList_list(FakeList<Node>* obj) {
  if (client) {
    client->postvisitList_NodeList_list(obj);
  }
}
bool ExampleDVisitor::visitList_AnotherList_list2(ASTList<Node>* obj) {
  if (ensureOneVisit) xassert(!wasVisitedList_ASTList(obj));
  return client ? client->visitList_AnotherList_list2(obj) : true;
}
void ExampleDVisitor::postvisitList_AnotherList_list2(ASTList<Node>* obj) {
  if (client) {
    client->postvisitList_AnotherList_list2(obj);
  }
}
bool ExampleDVisitor::visitListItem_NodeList_list(Node *obj) {
  return client ? client->visitListItem_NodeList_list(obj) : true;
}
void ExampleDVisitor::postvisitListItem_NodeList_list(Node *obj) {
  if (client) {
    client->postvisitListItem_NodeList_list(obj);
  }
}
bool ExampleDVisitor::visitListItem_AnotherList_list2(Node *obj) {
  return client ? client->visitListItem_AnotherList_list2(obj) : true;
}
void ExampleDVisitor::postvisitListItem_AnotherList_list2(Node *obj) {
  if (client) {
    client->postvisitListItem_AnotherList_list2(obj);
  }
}


// ---------------------- ToXmlASTVisitor ---------------------
bool ToXmlASTVisitor::wasVisitedAST(void *ast)
{
  if (!ast) {return false;} // avoid NULL; actually happens for FakeLists
  if (wasVisitedASTNodes.contains(ast)) {
    return true;
  } else {
    wasVisitedASTNodes.add(ast);
    return false;
  }
}

bool ToXmlASTVisitor::wasVisitedList_ASTList(void *ast)
{
  if (!ast) {return false;} // avoid NULL; actually happens for FakeLists
  if (wasVisitedList_ASTListNodes.contains(ast)) {
    return true;
  } else {
    wasVisitedList_ASTListNodes.add(ast);
    return false;
  }
}

bool ToXmlASTVisitor::wasVisitedList_FakeList(void *ast)
{
  if (!ast) {return false;} // avoid NULL; actually happens for FakeLists
  if (wasVisitedList_FakeListNodes.contains(ast)) {
    return true;
  } else {
    wasVisitedList_FakeListNodes.add(ast);
    return false;
  }
}

void ToXmlASTVisitor::printIndentation()
{
  writeSpaces(out, depth);
}

// default xml-visitor
bool ToXmlASTVisitor::visitNode(Node *obj) {
  if (wasVisitedAST(obj)) return false;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << obj->kindName();
  ++depth;
  out << " _id=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '\n';
  if (indent) printIndentation();
  out << "x=";
  outputXmlAttrQuotedNoEscape(out, toXml_int(obj->x));
  out << '\n';
  if (indent) printIndentation();
  out << "y=";
  outputXmlAttrQuotedNoEscape(out, toXml_int(obj->y));
  out << '\n';
  if (indent) printIndentation();
  out << "z=";
  outputXmlAttrQuotedNoEscape(out, toXml_int(obj->z));
  --depth;
  out << '>';
  ++depth;
  return true;
}

void ToXmlASTVisitor::postvisitNode(Node *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}

bool ToXmlASTVisitor::visitNodeList(NodeList *obj) {
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
  switch(obj->kind()) {
  default: xfailure("bad tag"); break;
  case NodeList::ASUBCLASS: {
    ASubclass *obj0 = obj->asASubclass();
  out << '\n';
  if (indent) printIndentation();
  out << "x=";
  outputXmlAttrQuotedNoEscape(out, toXml_int(obj0->x));
    obj0 = NULL;
    break;
    }
  case NodeList::ANOTHERSUBCLASS: {
    AnotherSubclass *obj0 = obj->asAnotherSubclass();
  out << '\n';
  if (indent) printIndentation();
  out << "x=";
  outputXmlAttrQuotedNoEscape(out, toXml_int(obj0->x));
    obj0 = NULL;
    break;
    }
  }
  --depth;
  out << '>';
  ++depth;
  return true;
}

void ToXmlASTVisitor::postvisitNodeList(NodeList *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}

bool ToXmlASTVisitor::visitAnotherList(AnotherList *obj) {
  if (wasVisitedAST(obj)) return false;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << obj->kindName();
  ++depth;
  out << " _id=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  if (obj && obj->list2.isNotEmpty()) {
    out << '\n';
    if (indent) printIndentation();
    out << "list2=";
    outputXmlPointerQuoted(out, "AL", uniqueIdAST(&(obj->list2)));
  }
  out << '\n';
  if (indent) printIndentation();
  out << "str=";
  outputXmlAttrQuoted(out, toXml(obj->str));
  --depth;
  out << '>';
  ++depth;
  return true;
}

void ToXmlASTVisitor::postvisitAnotherList(AnotherList *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}

bool ToXmlASTVisitor::visitSuper(Super *obj) {
  if (wasVisitedAST(obj)) return false;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << obj->kindName();
  ++depth;
  out << " _id=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '\n';
  if (indent) printIndentation();
  out << "x=";
  outputXmlAttrQuotedNoEscape(out, toXml_int(obj->x));
  switch(obj->kind()) {
  default: xfailure("bad tag"); break;
  case Super::SUB1: {
    Sub1 *obj0 = obj->asSub1();
  out << '\n';
  if (indent) printIndentation();
  out << "y=";
  outputXmlAttrQuotedNoEscape(out, toXml_int(obj0->y));
    obj0 = NULL;
    break;
    }
  case Super::SUB2: {
    Sub2 *obj0 = obj->asSub2();
  out << '\n';
  if (indent) printIndentation();
  out << "z=";
  outputXmlAttrQuotedNoEscape(out, toXml_int(obj0->z));
    obj0 = NULL;
    break;
    }
  case Super::SUBWITHDEFAULT: {
    SubWithDefault *obj0 = obj->asSubWithDefault();
  out << '\n';
  if (indent) printIndentation();
  out << "q=";
  outputXmlAttrQuotedNoEscape(out, toXml_int(obj0->q));
    obj0 = NULL;
    break;
    }
  case Super::SUB3: {
    Sub3 *obj0 = obj->asSub3();
  if (obj0 && obj0->s1) {
    out << '\n';
    if (indent) printIndentation();
    out << "s1=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->s1));
  }
  if (obj0 && obj0->s2) {
    out << '\n';
    if (indent) printIndentation();
    out << "s2=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->s2));
  }
  out << '\n';
  if (indent) printIndentation();
  out << "q=";
  outputXmlAttrQuotedNoEscape(out, toXml_int(obj0->q));
    obj0 = NULL;
    break;
    }
  case Super::SUB4: {
    Sub4 *obj0 = obj->asSub4();
    obj0 = NULL;
    break;
    }
  }
  --depth;
  out << '>';
  ++depth;
  return true;
}

void ToXmlASTVisitor::postvisitSuper(Super *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}

bool ToXmlASTVisitor::visitUsesEnum(UsesEnum *obj) {
  if (wasVisitedAST(obj)) return false;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << obj->kindName();
  ++depth;
  out << " _id=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  switch(obj->kind()) {
  default: xfailure("bad tag"); break;
  case UsesEnum::UE_A: {
    UE_a *obj0 = obj->asUE_a();
  out << '\n';
  if (indent) printIndentation();
  out << "x=";
  outputXmlAttrQuoted(out, toXml(obj0->x));
    obj0 = NULL;
    break;
    }
  case UsesEnum::UE_B: {
    UE_b *obj0 = obj->asUE_b();
  out << '\n';
  if (indent) printIndentation();
  out << "y=";
  outputXmlAttrQuotedNoEscape(out, toXml_int(obj0->y));
    obj0 = NULL;
    break;
    }
  }
  --depth;
  out << '>';
  ++depth;
  return true;
}

void ToXmlASTVisitor::postvisitUsesEnum(UsesEnum *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}

bool ToXmlASTVisitor::visitInheritsSomething(InheritsSomething *obj) {
  if (wasVisitedAST(obj)) return false;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << obj->kindName();
  ++depth;
  out << " _id=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  switch(obj->kind()) {
  default: xfailure("bad tag"); break;
  case InheritsSomething::IS_A: {
    IS_a *obj0 = obj->asIS_a();
  out << '\n';
  if (indent) printIndentation();
  out << "z=";
  outputXmlAttrQuotedNoEscape(out, toXml_int(obj0->z));
    obj0 = NULL;
    break;
    }
  case InheritsSomething::IS_B: {
    IS_b *obj0 = obj->asIS_b();
  out << '\n';
  if (indent) printIndentation();
  out << "q=";
  outputXmlAttrQuotedNoEscape(out, toXml_int(obj0->q));
    obj0 = NULL;
    break;
    }
  case InheritsSomething::IS_C: {
    IS_c *obj0 = obj->asIS_c();
  out << '\n';
  if (indent) printIndentation();
  out << "ret=";
  outputXmlAttrQuotedNoEscape(out, toXml_int(obj0->ret));
    obj0 = NULL;
    break;
    }
  case InheritsSomething::IS_D: {
    IS_d *obj0 = obj->asIS_d();
  if (obj0 && obj0->ret) {
    out << '\n';
    if (indent) printIndentation();
    out << "ret=";
    outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj0->ret));
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

void ToXmlASTVisitor::postvisitInheritsSomething(InheritsSomething *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}

bool ToXmlASTVisitor::visitHasLastArgs(HasLastArgs *obj) {
  if (wasVisitedAST(obj)) return false;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << obj->kindName();
  ++depth;
  out << " _id=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '\n';
  if (indent) printIndentation();
  out << "x=";
  outputXmlAttrQuotedNoEscape(out, toXml_int(obj->x));
  switch(obj->kind()) {
  default: xfailure("bad tag"); break;
  case HasLastArgs::HLA1: {
    Hla1 *obj0 = obj->asHla1();
  out << '\n';
  if (indent) printIndentation();
  out << "y=";
  outputXmlAttrQuotedNoEscape(out, toXml_int(obj0->y));
    obj0 = NULL;
    break;
    }
  case HasLastArgs::HLA2: {
    Hla2 *obj0 = obj->asHla2();
  out << '\n';
  if (indent) printIndentation();
  out << "y=";
  outputXmlAttrQuotedNoEscape(out, toXml_int(obj0->y));
  out << '\n';
  if (indent) printIndentation();
  out << "z=";
  outputXmlAttrQuotedNoEscape(out, toXml_int(obj0->z));
    obj0 = NULL;
    break;
    }
  }
  out << '\n';
  if (indent) printIndentation();
  out << "w=";
  outputXmlAttrQuotedNoEscape(out, toXml_int(obj->w));
  --depth;
  out << '>';
  ++depth;
  return true;
}

void ToXmlASTVisitor::postvisitHasLastArgs(HasLastArgs *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}

bool ToXmlASTVisitor::visitSomethingElse(SomethingElse *obj) {
  if (wasVisitedAST(obj)) return false;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << obj->kindName();
  ++depth;
  out << " _id=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '\n';
  if (indent) printIndentation();
  out << "x=";
  outputXmlAttrQuotedNoEscape(out, toXml_int(obj->x));
  out << '\n';
  if (indent) printIndentation();
  out << "y=";
  outputXmlAttrQuotedNoEscape(out, toXml_int(obj->y));
  --depth;
  out << '>';
  ++depth;
  return true;
}

void ToXmlASTVisitor::postvisitSomethingElse(SomethingElse *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}

bool ToXmlASTVisitor::visitANewClass(ANewClass *obj) {
  if (wasVisitedAST(obj)) return false;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << obj->kindName();
  ++depth;
  out << " _id=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '\n';
  if (indent) printIndentation();
  out << "foo=";
  outputXmlAttrQuotedNoEscape(out, toXml_int(obj->foo));
  --depth;
  out << '>';
  ++depth;
  return true;
}

void ToXmlASTVisitor::postvisitANewClass(ANewClass *obj) {
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << '<' << '/' << obj->kindName() << '>';
}


// List 'classes'
bool ToXmlASTVisitor::visitList_NodeList_list(FakeList<Node>* obj) {
  if (obj->isNotEmpty()) {
    if(wasVisitedList_FakeList(obj)) return false;
    out << '\n';
    if (indent) printIndentation();
    out << "<List_NodeList_list _id=";
    outputXmlPointerQuoted(out, "FL", uniqueIdAST(obj));
    out << '>';
    ++depth;
  };
  return true;
}

void ToXmlASTVisitor::postvisitList_NodeList_list(FakeList<Node>* obj) {
  if (obj->isNotEmpty()) {
    --depth;
    out << '\n';
    if (indent) printIndentation();
    out << "</List_NodeList_list>";
  }
}

bool ToXmlASTVisitor::visitListItem_NodeList_list(Node *obj) {
  xassert(obj);
  out << '\n';
  if (indent) printIndentation();
  out << "<_List_Item" << " item=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '>';
  ++depth;
  return true;
}

void ToXmlASTVisitor::postvisitListItem_NodeList_list(Node *obj) {
  xassert(obj);
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << "</_List_Item>";
}

bool ToXmlASTVisitor::visitList_AnotherList_list2(ASTList<Node>* obj) {
  if (obj->isNotEmpty()) {
    if(wasVisitedList_ASTList(obj)) return false;
    out << '\n';
    if (indent) printIndentation();
    out << "<List_AnotherList_list2 _id=";
    outputXmlPointerQuoted(out, "AL", uniqueIdAST(obj));
    out << '>';
    ++depth;
  };
  return true;
}

void ToXmlASTVisitor::postvisitList_AnotherList_list2(ASTList<Node>* obj) {
  if (obj->isNotEmpty()) {
    --depth;
    out << '\n';
    if (indent) printIndentation();
    out << "</List_AnotherList_list2>";
  }
}

bool ToXmlASTVisitor::visitListItem_AnotherList_list2(Node *obj) {
  xassert(obj);
  out << '\n';
  if (indent) printIndentation();
  out << "<_List_Item" << " item=";
  outputXmlPointerQuoted(out, "AST", uniqueIdAST(obj));
  out << '>';
  ++depth;
  return true;
}

void ToXmlASTVisitor::postvisitListItem_AnotherList_list2(Node *obj) {
  xassert(obj);
  --depth;
  out << '\n';
  if (indent) printIndentation();
  out << "</_List_Item>";
}



// ---------------------- ExampleMVisitor ---------------------
ExampleMVisitor::~ExampleMVisitor() {}

bool ExampleMVisitor::visitNode(Node *&obj) { return true; }

void ExampleMVisitor::mtraverse(Node *&obj)
{
  if (!visitNode(obj)) { return; }

   mtraverse(obj->next); ;
}


bool ExampleMVisitor::visitNodeList(NodeList *&obj) { return true; }

void ExampleMVisitor::mtraverse(NodeList *&obj)
{
  if (!visitNodeList(obj)) { return; }

  // fakelist mtraversal: obj->list
  {
    Node **iter = (Node**)&(obj->list);
    while (*iter) {
      mtraverse(*iter);
      iter = &( (*iter)->next );
    }
  }
  switch (obj->kind()) {
    case NodeList::ASUBCLASS: {
      ASubclass *sub = (ASubclass*)obj;
      (void)sub;
      break;
    }
    case NodeList::ANOTHERSUBCLASS: {
      AnotherSubclass *sub = (AnotherSubclass*)obj;
      (void)sub;
      break;
    }
    default:;
  }
}


bool ExampleMVisitor::visitAnotherList(AnotherList *&obj) { return true; }

void ExampleMVisitor::mtraverse(AnotherList *&obj)
{
  if (!visitAnotherList(obj)) { return; }

  FOREACH_ASTLIST_NC(Node, obj->list2, iter) {
    mtraverse(iter.dataRef());
  }
}


bool ExampleMVisitor::visitSuper(Super *&obj) { return true; }

void ExampleMVisitor::mtraverse(Super *&obj)
{
  if (!visitSuper(obj)) { return; }

  switch (obj->kind()) {
    case Super::SUB1: {
      Sub1 *sub = (Sub1*)obj;
      (void)sub;
      break;
    }
    case Super::SUB2: {
      Sub2 *sub = (Sub2*)obj;
      (void)sub;
      break;
    }
    case Super::SUBWITHDEFAULT: {
      SubWithDefault *sub = (SubWithDefault*)obj;
      (void)sub;
      break;
    }
    case Super::SUB3: {
      Sub3 *sub = (Sub3*)obj;
      (void)sub;
      if (sub->s1) {
        mtraverse(sub->s1);
      }
      if (sub->s2) {
        Super* tmp = sub->s2;
        mtraverse(tmp);
        if (tmp != sub->s2) {
          sub->s2 = tmp->asSub2();
        }
      }
      break;
    }
    case Super::SUB4: {
      Sub4 *sub = (Sub4*)obj;
      (void)sub;
      break;
    }
    default:;
  }
}


bool ExampleMVisitor::visitUsesEnum(UsesEnum *&obj) { return true; }

void ExampleMVisitor::mtraverse(UsesEnum *&obj)
{
  if (!visitUsesEnum(obj)) { return; }

  switch (obj->kind()) {
    case UsesEnum::UE_A: {
      UE_a *sub = (UE_a*)obj;
      (void)sub;
      break;
    }
    case UsesEnum::UE_B: {
      UE_b *sub = (UE_b*)obj;
      (void)sub;
      break;
    }
    default:;
  }
}


bool ExampleMVisitor::visitInheritsSomething(InheritsSomething *&obj) { return true; }

void ExampleMVisitor::mtraverse(InheritsSomething *&obj)
{
  if (!visitInheritsSomething(obj)) { return; }

  switch (obj->kind()) {
    case InheritsSomething::IS_A: {
      IS_a *sub = (IS_a*)obj;
      (void)sub;
      break;
    }
    case InheritsSomething::IS_B: {
      IS_b *sub = (IS_b*)obj;
      (void)sub;
      break;
    }
    case InheritsSomething::IS_C: {
      IS_c *sub = (IS_c*)obj;
      (void)sub;
      break;
    }
    case InheritsSomething::IS_D: {
      IS_d *sub = (IS_d*)obj;
      (void)sub;
      if (sub->ret) {
        mtraverse(sub->ret);
      }
      break;
    }
    default:;
  }
}


bool ExampleMVisitor::visitHasLastArgs(HasLastArgs *&obj) { return true; }

void ExampleMVisitor::mtraverse(HasLastArgs *&obj)
{
  if (!visitHasLastArgs(obj)) { return; }

  switch (obj->kind()) {
    case HasLastArgs::HLA1: {
      Hla1 *sub = (Hla1*)obj;
      (void)sub;
      break;
    }
    case HasLastArgs::HLA2: {
      Hla2 *sub = (Hla2*)obj;
      (void)sub;
      break;
    }
    default:;
  }
}


bool ExampleMVisitor::visitSomethingElse(SomethingElse *&obj) { return true; }

void ExampleMVisitor::mtraverse(SomethingElse *&obj)
{
  if (!visitSomethingElse(obj)) { return; }

}


bool ExampleMVisitor::visitANewClass(ANewClass *&obj) { return true; }

void ExampleMVisitor::mtraverse(ANewClass *&obj)
{
  if (!visitANewClass(obj)) { return; }

}



