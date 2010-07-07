bool XmlAstReader::kind2kindCat(int kind, KindCategory *kindCat) {
  switch(kind) {
  default: return false; // don't know this kind
  case XTOK_TranslationUnit: *kindCat = KC_Node; break;
  case XTOK_TopForm: *kindCat = KC_Node; break;
  case XTOK_TF_decl: *kindCat = KC_Node; break;
  case XTOK_TF_func: *kindCat = KC_Node; break;
  case XTOK_TF_template: *kindCat = KC_Node; break;
  case XTOK_TF_explicitInst: *kindCat = KC_Node; break;
  case XTOK_TF_linkage: *kindCat = KC_Node; break;
  case XTOK_TF_one_linkage: *kindCat = KC_Node; break;
  case XTOK_TF_asm: *kindCat = KC_Node; break;
  case XTOK_TF_namespaceDefn: *kindCat = KC_Node; break;
  case XTOK_TF_namespaceDecl: *kindCat = KC_Node; break;
  case XTOK_Function: *kindCat = KC_Node; break;
  case XTOK_MemberInit: *kindCat = KC_Node; break;
  case XTOK_Declaration: *kindCat = KC_Node; break;
  case XTOK_ASTTypeId: *kindCat = KC_Node; break;
  case XTOK_PQName: *kindCat = KC_Node; break;
  case XTOK_PQ_qualifier: *kindCat = KC_Node; break;
  case XTOK_PQ_name: *kindCat = KC_Node; break;
  case XTOK_PQ_operator: *kindCat = KC_Node; break;
  case XTOK_PQ_template: *kindCat = KC_Node; break;
  case XTOK_PQ_variable: *kindCat = KC_Node; break;
  case XTOK_TypeSpecifier: *kindCat = KC_Node; break;
  case XTOK_TS_name: *kindCat = KC_Node; break;
  case XTOK_TS_simple: *kindCat = KC_Node; break;
  case XTOK_TS_elaborated: *kindCat = KC_Node; break;
  case XTOK_TS_classSpec: *kindCat = KC_Node; break;
  case XTOK_TS_enumSpec: *kindCat = KC_Node; break;
  case XTOK_TS_type: *kindCat = KC_Node; break;
  case XTOK_TS_typeof: *kindCat = KC_Node; break;
  case XTOK_BaseClassSpec: *kindCat = KC_Node; break;
  case XTOK_Enumerator: *kindCat = KC_Node; break;
  case XTOK_MemberList: *kindCat = KC_Node; break;
  case XTOK_Member: *kindCat = KC_Node; break;
  case XTOK_MR_decl: *kindCat = KC_Node; break;
  case XTOK_MR_func: *kindCat = KC_Node; break;
  case XTOK_MR_access: *kindCat = KC_Node; break;
  case XTOK_MR_usingDecl: *kindCat = KC_Node; break;
  case XTOK_MR_template: *kindCat = KC_Node; break;
  case XTOK_Declarator: *kindCat = KC_Node; break;
  case XTOK_IDeclarator: *kindCat = KC_Node; break;
  case XTOK_D_name: *kindCat = KC_Node; break;
  case XTOK_D_pointer: *kindCat = KC_Node; break;
  case XTOK_D_reference: *kindCat = KC_Node; break;
  case XTOK_D_func: *kindCat = KC_Node; break;
  case XTOK_D_array: *kindCat = KC_Node; break;
  case XTOK_D_bitfield: *kindCat = KC_Node; break;
  case XTOK_D_ptrToMember: *kindCat = KC_Node; break;
  case XTOK_D_grouping: *kindCat = KC_Node; break;
  case XTOK_ExceptionSpec: *kindCat = KC_Node; break;
  case XTOK_OperatorName: *kindCat = KC_Node; break;
  case XTOK_ON_newDel: *kindCat = KC_Node; break;
  case XTOK_ON_operator: *kindCat = KC_Node; break;
  case XTOK_ON_conversion: *kindCat = KC_Node; break;
  case XTOK_Statement: *kindCat = KC_Node; break;
  case XTOK_S_skip: *kindCat = KC_Node; break;
  case XTOK_S_label: *kindCat = KC_Node; break;
  case XTOK_S_case: *kindCat = KC_Node; break;
  case XTOK_S_default: *kindCat = KC_Node; break;
  case XTOK_S_expr: *kindCat = KC_Node; break;
  case XTOK_S_compound: *kindCat = KC_Node; break;
  case XTOK_S_if: *kindCat = KC_Node; break;
  case XTOK_S_switch: *kindCat = KC_Node; break;
  case XTOK_S_while: *kindCat = KC_Node; break;
  case XTOK_S_doWhile: *kindCat = KC_Node; break;
  case XTOK_S_for: *kindCat = KC_Node; break;
  case XTOK_S_break: *kindCat = KC_Node; break;
  case XTOK_S_continue: *kindCat = KC_Node; break;
  case XTOK_S_return: *kindCat = KC_Node; break;
  case XTOK_S_goto: *kindCat = KC_Node; break;
  case XTOK_S_decl: *kindCat = KC_Node; break;
  case XTOK_S_try: *kindCat = KC_Node; break;
  case XTOK_S_asm: *kindCat = KC_Node; break;
  case XTOK_S_namespaceDecl: *kindCat = KC_Node; break;
  case XTOK_S_function: *kindCat = KC_Node; break;
  case XTOK_S_rangeCase: *kindCat = KC_Node; break;
  case XTOK_S_computedGoto: *kindCat = KC_Node; break;
  case XTOK_Condition: *kindCat = KC_Node; break;
  case XTOK_CN_expr: *kindCat = KC_Node; break;
  case XTOK_CN_decl: *kindCat = KC_Node; break;
  case XTOK_Handler: *kindCat = KC_Node; break;
  case XTOK_Expression: *kindCat = KC_Node; break;
  case XTOK_E_boolLit: *kindCat = KC_Node; break;
  case XTOK_E_intLit: *kindCat = KC_Node; break;
  case XTOK_E_floatLit: *kindCat = KC_Node; break;
  case XTOK_E_stringLit: *kindCat = KC_Node; break;
  case XTOK_E_charLit: *kindCat = KC_Node; break;
  case XTOK_E_this: *kindCat = KC_Node; break;
  case XTOK_E_variable: *kindCat = KC_Node; break;
  case XTOK_E_funCall: *kindCat = KC_Node; break;
  case XTOK_E_constructor: *kindCat = KC_Node; break;
  case XTOK_E_fieldAcc: *kindCat = KC_Node; break;
  case XTOK_E_sizeof: *kindCat = KC_Node; break;
  case XTOK_E_unary: *kindCat = KC_Node; break;
  case XTOK_E_effect: *kindCat = KC_Node; break;
  case XTOK_E_binary: *kindCat = KC_Node; break;
  case XTOK_E_addrOf: *kindCat = KC_Node; break;
  case XTOK_E_deref: *kindCat = KC_Node; break;
  case XTOK_E_cast: *kindCat = KC_Node; break;
  case XTOK_E_cond: *kindCat = KC_Node; break;
  case XTOK_E_sizeofType: *kindCat = KC_Node; break;
  case XTOK_E_assign: *kindCat = KC_Node; break;
  case XTOK_E_new: *kindCat = KC_Node; break;
  case XTOK_E_delete: *kindCat = KC_Node; break;
  case XTOK_E_throw: *kindCat = KC_Node; break;
  case XTOK_E_keywordCast: *kindCat = KC_Node; break;
  case XTOK_E_typeidExpr: *kindCat = KC_Node; break;
  case XTOK_E_typeidType: *kindCat = KC_Node; break;
  case XTOK_E_grouping: *kindCat = KC_Node; break;
  case XTOK_E_arrow: *kindCat = KC_Node; break;
  case XTOK_E_statement: *kindCat = KC_Node; break;
  case XTOK_E_compoundLit: *kindCat = KC_Node; break;
  case XTOK_E___builtin_constant_p: *kindCat = KC_Node; break;
  case XTOK_E___builtin_va_arg: *kindCat = KC_Node; break;
  case XTOK_E_alignofType: *kindCat = KC_Node; break;
  case XTOK_E_alignofExpr: *kindCat = KC_Node; break;
  case XTOK_E_gnuCond: *kindCat = KC_Node; break;
  case XTOK_E_addrOfLabel: *kindCat = KC_Node; break;
  case XTOK_FullExpression: *kindCat = KC_Node; break;
  case XTOK_ArgExpression: *kindCat = KC_Node; break;
  case XTOK_ArgExpressionListOpt: *kindCat = KC_Node; break;
  case XTOK_Initializer: *kindCat = KC_Node; break;
  case XTOK_IN_expr: *kindCat = KC_Node; break;
  case XTOK_IN_compound: *kindCat = KC_Node; break;
  case XTOK_IN_ctor: *kindCat = KC_Node; break;
  case XTOK_IN_designated: *kindCat = KC_Node; break;
  case XTOK_TemplateDeclaration: *kindCat = KC_Node; break;
  case XTOK_TD_func: *kindCat = KC_Node; break;
  case XTOK_TD_decl: *kindCat = KC_Node; break;
  case XTOK_TD_tmember: *kindCat = KC_Node; break;
  case XTOK_TemplateParameter: *kindCat = KC_Node; break;
  case XTOK_TP_type: *kindCat = KC_Node; break;
  case XTOK_TP_nontype: *kindCat = KC_Node; break;
  case XTOK_TP_template: *kindCat = KC_Node; break;
  case XTOK_TemplateArgument: *kindCat = KC_Node; break;
  case XTOK_TA_type: *kindCat = KC_Node; break;
  case XTOK_TA_nontype: *kindCat = KC_Node; break;
  case XTOK_TA_templateUsed: *kindCat = KC_Node; break;
  case XTOK_NamespaceDecl: *kindCat = KC_Node; break;
  case XTOK_ND_alias: *kindCat = KC_Node; break;
  case XTOK_ND_usingDecl: *kindCat = KC_Node; break;
  case XTOK_ND_usingDir: *kindCat = KC_Node; break;
  case XTOK_FullExpressionAnnot: *kindCat = KC_Node; break;
  case XTOK_ASTTypeof: *kindCat = KC_Node; break;
  case XTOK_TS_typeof_expr: *kindCat = KC_Node; break;
  case XTOK_TS_typeof_type: *kindCat = KC_Node; break;
  case XTOK_Designator: *kindCat = KC_Node; break;
  case XTOK_FieldDesignator: *kindCat = KC_Node; break;
  case XTOK_SubscriptDesignator: *kindCat = KC_Node; break;
  case XTOK_AttributeSpecifierList: *kindCat = KC_Node; break;
  case XTOK_AttributeSpecifier: *kindCat = KC_Node; break;
  case XTOK_Attribute: *kindCat = KC_Node; break;
  case XTOK_AT_empty: *kindCat = KC_Node; break;
  case XTOK_AT_word: *kindCat = KC_Node; break;
  case XTOK_AT_func: *kindCat = KC_Node; break;
  case XTOK_List_TF_namespaceDefn_forms: *kindCat = KC_ASTList; break;
  case XTOK_List_TranslationUnit_topForms: *kindCat = KC_ASTList; break;
  case XTOK_List_Function_inits: *kindCat = KC_FakeList; break;
  case XTOK_List_Function_handlers: *kindCat = KC_FakeList; break;
  case XTOK_List_MemberInit_args: *kindCat = KC_FakeList; break;
  case XTOK_List_MemberList_list: *kindCat = KC_ASTList; break;
  case XTOK_List_Declaration_decllist: *kindCat = KC_FakeList; break;
  case XTOK_List_TS_classSpec_bases: *kindCat = KC_FakeList; break;
  case XTOK_List_TS_enumSpec_elts: *kindCat = KC_FakeList; break;
  case XTOK_List_D_func_params: *kindCat = KC_FakeList; break;
  case XTOK_List_D_func_kAndR_params: *kindCat = KC_FakeList; break;
  case XTOK_List_S_try_handlers: *kindCat = KC_FakeList; break;
  case XTOK_List_ExceptionSpec_types: *kindCat = KC_FakeList; break;
  case XTOK_List_S_compound_stmts: *kindCat = KC_ASTList; break;
  case XTOK_List_E_funCall_args: *kindCat = KC_FakeList; break;
  case XTOK_List_E_constructor_args: *kindCat = KC_FakeList; break;
  case XTOK_List_E_new_placementArgs: *kindCat = KC_FakeList; break;
  case XTOK_List_ArgExpressionListOpt_list: *kindCat = KC_FakeList; break;
  case XTOK_List_IN_compound_inits: *kindCat = KC_ASTList; break;
  case XTOK_List_IN_ctor_args: *kindCat = KC_FakeList; break;
  case XTOK_List_TP_template_parameters: *kindCat = KC_FakeList; break;
  case XTOK_List_IN_designated_designator_list: *kindCat = KC_FakeList; break;
  case XTOK_List_FullExpressionAnnot_declarations: *kindCat = KC_ASTList; break;
  case XTOK_List_AT_func_args: *kindCat = KC_FakeList; break;
  }
  return true;
}

void XmlAstReader::registerAttr_TranslationUnit(TranslationUnit *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a TranslationUnit");
    break;
  case XTOK_topForms:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->topForms), strValue, XTOK_List_TranslationUnit_topForms, true));
    break;
  case XTOK_globalScope:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->globalScope), strValue,XTOK_Scope, false));
    break;
  }
}

void XmlAstReader::registerAttr_TF_decl(TF_decl *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a TF_decl");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_decl:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->decl), strValue,XTOK_Declaration, false));
    break;
  }
}

void XmlAstReader::registerAttr_TF_func(TF_func *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a TF_func");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_f:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->f), strValue,XTOK_Function, false));
    break;
  }
}

void XmlAstReader::registerAttr_TF_template(TF_template *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a TF_template");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_td:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->td), strValue,XTOK_TemplateDeclaration, false));
    break;
  }
}

void XmlAstReader::registerAttr_TF_explicitInst(TF_explicitInst *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a TF_explicitInst");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_instFlags:
    fromXml(obj->instFlags, strValue);
    break;
  case XTOK_d:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->d), strValue,XTOK_Declaration, false));
    break;
  }
}

void XmlAstReader::registerAttr_TF_linkage(TF_linkage *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a TF_linkage");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_linkageType:
    obj->linkageType = manager->strTable(strValue);
    break;
  case XTOK_forms:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->forms), strValue,XTOK_TranslationUnit, false));
    break;
  }
}

void XmlAstReader::registerAttr_TF_one_linkage(TF_one_linkage *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a TF_one_linkage");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_linkageType:
    obj->linkageType = manager->strTable(strValue);
    break;
  case XTOK_form:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->form), strValue,XTOK_TopForm, false));
    break;
  }
}

void XmlAstReader::registerAttr_TF_asm(TF_asm *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a TF_asm");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_text:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->text), strValue,XTOK_E_stringLit, false));
    break;
  }
}

void XmlAstReader::registerAttr_TF_namespaceDefn(TF_namespaceDefn *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a TF_namespaceDefn");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_name:
    obj->name = manager->strTable(strValue);
    break;
  case XTOK_forms:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->forms), strValue, XTOK_List_TF_namespaceDefn_forms, true));
    break;
  }
}

void XmlAstReader::registerAttr_TF_namespaceDecl(TF_namespaceDecl *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a TF_namespaceDecl");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_decl:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->decl), strValue,XTOK_NamespaceDecl, false));
    break;
  }
}

void XmlAstReader::registerAttr_Function(Function *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a Function");
    break;
  case XTOK_dflags:
    fromXml(obj->dflags, strValue);
    break;
  case XTOK_retspec:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->retspec), strValue,XTOK_TypeSpecifier, false));
    break;
  case XTOK_nameAndParams:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->nameAndParams), strValue,XTOK_Declarator, false));
    break;
  case XTOK_inits:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->inits), strValue, XTOK_List_Function_inits, true));
    break;
  case XTOK_body:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->body), strValue,XTOK_S_compound, false));
    break;
  case XTOK_handlers:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->handlers), strValue, XTOK_List_Function_handlers, true));
    break;
  case XTOK_funcType:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->funcType), strValue,XTOK_FunctionType, false));
    break;
  case XTOK_receiver:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->receiver), strValue,XTOK_Variable, false));
    break;
  case XTOK_retVar:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->retVar), strValue,XTOK_Variable, false));
    break;
  case XTOK_dtorStatement:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->dtorStatement), strValue,XTOK_Statement, false));
    break;
  case XTOK_implicitlyDefined:
    fromXml_bool(obj->implicitlyDefined, strValue);
    break;
  }
}

void XmlAstReader::registerAttr_MemberInit(MemberInit *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a MemberInit");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_name:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->name), strValue,XTOK_PQName, false));
    break;
  case XTOK_args:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->args), strValue, XTOK_List_MemberInit_args, true));
    break;
  case XTOK_member:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->member), strValue,XTOK_Variable, false));
    break;
  case XTOK_base:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->base), strValue,XTOK_CompoundType, false));
    break;
  case XTOK_ctorVar:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->ctorVar), strValue,XTOK_Variable, false));
    break;
  case XTOK_annot:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->annot), strValue,XTOK_FullExpressionAnnot, false));
    break;
  case XTOK_ctorStatement:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->ctorStatement), strValue,XTOK_Statement, false));
    break;
  }
}

void XmlAstReader::registerAttr_Declaration(Declaration *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a Declaration");
    break;
  case XTOK_dflags:
    fromXml(obj->dflags, strValue);
    break;
  case XTOK_spec:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->spec), strValue,XTOK_TypeSpecifier, false));
    break;
  case XTOK_decllist:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->decllist), strValue, XTOK_List_Declaration_decllist, true));
    break;
  }
}

void XmlAstReader::registerAttr_ASTTypeId(ASTTypeId *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a ASTTypeId");
    break;
  case XTOK_spec:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->spec), strValue,XTOK_TypeSpecifier, false));
    break;
  case XTOK_decl:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->decl), strValue,XTOK_Declarator, false));
    break;
  }
}

void XmlAstReader::registerAttr_PQ_qualifier(PQ_qualifier *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a PQ_qualifier");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_qualifier:
    obj->qualifier = manager->strTable(strValue);
    break;
  case XTOK_templArgs:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->templArgs), strValue,XTOK_TemplateArgument, false));
    break;
  case XTOK_rest:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->rest), strValue,XTOK_PQName, false));
    break;
  case XTOK_qualifierVar:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->qualifierVar), strValue,XTOK_Variable, false));
    break;
  case XTOK_sargs:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->sargs), strValue,XTOK_List_PQ_qualifier_sargs, true));
    break;
  }
}

void XmlAstReader::registerAttr_PQ_name(PQ_name *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a PQ_name");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_name:
    obj->name = manager->strTable(strValue);
    break;
  }
}

void XmlAstReader::registerAttr_PQ_operator(PQ_operator *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a PQ_operator");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_o:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->o), strValue,XTOK_OperatorName, false));
    break;
  case XTOK_fakeName:
    obj->fakeName = manager->strTable(strValue);
    break;
  }
}

void XmlAstReader::registerAttr_PQ_template(PQ_template *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a PQ_template");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_name:
    obj->name = manager->strTable(strValue);
    break;
  case XTOK_templArgs:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->templArgs), strValue,XTOK_TemplateArgument, false));
    break;
  case XTOK_sargs:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->sargs), strValue,XTOK_List_PQ_template_sargs, true));
    break;
  }
}

void XmlAstReader::registerAttr_PQ_variable(PQ_variable *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a PQ_variable");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_var:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->var), strValue,XTOK_Variable, false));
    break;
  }
}

void XmlAstReader::registerAttr_TS_name(TS_name *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a TS_name");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_cv:
    fromXml(obj->cv, strValue);
    break;
  case XTOK_name:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->name), strValue,XTOK_PQName, false));
    break;
  case XTOK_typenameUsed:
    fromXml_bool(obj->typenameUsed, strValue);
    break;
  case XTOK_var:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->var), strValue,XTOK_Variable, false));
    break;
  case XTOK_nondependentVar:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->nondependentVar), strValue,XTOK_Variable, false));
    break;
  }
}

void XmlAstReader::registerAttr_TS_simple(TS_simple *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a TS_simple");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_cv:
    fromXml(obj->cv, strValue);
    break;
  case XTOK_id:
    fromXml(obj->id, strValue);
    break;
  }
}

void XmlAstReader::registerAttr_TS_elaborated(TS_elaborated *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a TS_elaborated");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_cv:
    fromXml(obj->cv, strValue);
    break;
  case XTOK_keyword:
    fromXml(obj->keyword, strValue);
    break;
  case XTOK_name:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->name), strValue,XTOK_PQName, false));
    break;
  case XTOK_atype:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->atype), strValue,XTOK_NamedAtomicType, false));
    break;
  }
}

void XmlAstReader::registerAttr_TS_classSpec(TS_classSpec *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a TS_classSpec");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_cv:
    fromXml(obj->cv, strValue);
    break;
  case XTOK_keyword:
    fromXml(obj->keyword, strValue);
    break;
  case XTOK_name:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->name), strValue,XTOK_PQName, false));
    break;
  case XTOK_bases:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->bases), strValue, XTOK_List_TS_classSpec_bases, true));
    break;
  case XTOK_members:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->members), strValue,XTOK_MemberList, false));
    break;
  case XTOK_ctype:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->ctype), strValue,XTOK_CompoundType, false));
    break;
  }
}

void XmlAstReader::registerAttr_TS_enumSpec(TS_enumSpec *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a TS_enumSpec");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_cv:
    fromXml(obj->cv, strValue);
    break;
  case XTOK_name:
    obj->name = manager->strTable(strValue);
    break;
  case XTOK_elts:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->elts), strValue, XTOK_List_TS_enumSpec_elts, true));
    break;
  case XTOK_etype:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->etype), strValue,XTOK_EnumType, false));
    break;
  }
}

void XmlAstReader::registerAttr_TS_type(TS_type *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a TS_type");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_cv:
    fromXml(obj->cv, strValue);
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_Type, false));
    break;
  }
}

void XmlAstReader::registerAttr_TS_typeof(TS_typeof *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a TS_typeof");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_cv:
    fromXml(obj->cv, strValue);
    break;
  case XTOK_atype:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->atype), strValue,XTOK_ASTTypeof, false));
    break;
  }
}

void XmlAstReader::registerAttr_BaseClassSpec(BaseClassSpec *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a BaseClassSpec");
    break;
  case XTOK_isVirtual:
    fromXml_bool(obj->isVirtual, strValue);
    break;
  case XTOK_access:
    fromXml(obj->access, strValue);
    break;
  case XTOK_name:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->name), strValue,XTOK_PQName, false));
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_CompoundType, false));
    break;
  }
}

void XmlAstReader::registerAttr_Enumerator(Enumerator *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a Enumerator");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_name:
    obj->name = manager->strTable(strValue);
    break;
  case XTOK_expr:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->expr), strValue,XTOK_Expression, false));
    break;
  case XTOK_var:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->var), strValue,XTOK_Variable, false));
    break;
  case XTOK_enumValue:
    fromXml_int(obj->enumValue, strValue);
    break;
  }
}

void XmlAstReader::registerAttr_MemberList(MemberList *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a MemberList");
    break;
  case XTOK_list:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->list), strValue, XTOK_List_MemberList_list, true));
    break;
  }
}

void XmlAstReader::registerAttr_MR_decl(MR_decl *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a MR_decl");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_d:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->d), strValue,XTOK_Declaration, false));
    break;
  }
}

void XmlAstReader::registerAttr_MR_func(MR_func *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a MR_func");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_f:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->f), strValue,XTOK_Function, false));
    break;
  }
}

void XmlAstReader::registerAttr_MR_access(MR_access *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a MR_access");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_k:
    fromXml(obj->k, strValue);
    break;
  }
}

void XmlAstReader::registerAttr_MR_usingDecl(MR_usingDecl *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a MR_usingDecl");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_decl:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->decl), strValue,XTOK_ND_usingDecl, false));
    break;
  }
}

void XmlAstReader::registerAttr_MR_template(MR_template *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a MR_template");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_d:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->d), strValue,XTOK_TemplateDeclaration, false));
    break;
  }
}

void XmlAstReader::registerAttr_Declarator(Declarator *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a Declarator");
    break;
  case XTOK_decl:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->decl), strValue,XTOK_IDeclarator, false));
    break;
  case XTOK_init:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->init), strValue,XTOK_Initializer, false));
    break;
  case XTOK_var:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->var), strValue,XTOK_Variable, false));
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_Type, false));
    break;
  case XTOK_context:
    fromXml(obj->context, strValue);
    break;
  case XTOK_ctorStatement:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->ctorStatement), strValue,XTOK_Statement, false));
    break;
  case XTOK_dtorStatement:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->dtorStatement), strValue,XTOK_Statement, false));
    break;
  }
}

void XmlAstReader::registerAttr_D_name(D_name *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a D_name");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_name:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->name), strValue,XTOK_PQName, false));
    break;
  }
}

void XmlAstReader::registerAttr_D_pointer(D_pointer *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a D_pointer");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_cv:
    fromXml(obj->cv, strValue);
    break;
  case XTOK_base:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->base), strValue,XTOK_IDeclarator, false));
    break;
  }
}

void XmlAstReader::registerAttr_D_reference(D_reference *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a D_reference");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_base:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->base), strValue,XTOK_IDeclarator, false));
    break;
  }
}

void XmlAstReader::registerAttr_D_func(D_func *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a D_func");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_base:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->base), strValue,XTOK_IDeclarator, false));
    break;
  case XTOK_params:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->params), strValue, XTOK_List_D_func_params, true));
    break;
  case XTOK_cv:
    fromXml(obj->cv, strValue);
    break;
  case XTOK_exnSpec:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->exnSpec), strValue,XTOK_ExceptionSpec, false));
    break;
  case XTOK_kAndR_params:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->kAndR_params), strValue, XTOK_List_D_func_kAndR_params, true));
    break;
  case XTOK_isMember:
    fromXml_bool(obj->isMember, strValue);
    break;
  }
}

void XmlAstReader::registerAttr_D_array(D_array *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a D_array");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_base:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->base), strValue,XTOK_IDeclarator, false));
    break;
  case XTOK_size:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->size), strValue,XTOK_Expression, false));
    break;
  case XTOK_isNewSize:
    fromXml_bool(obj->isNewSize, strValue);
    break;
  }
}

void XmlAstReader::registerAttr_D_bitfield(D_bitfield *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a D_bitfield");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_name:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->name), strValue,XTOK_PQName, false));
    break;
  case XTOK_bits:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->bits), strValue,XTOK_Expression, false));
    break;
  case XTOK_numBits:
    fromXml_int(obj->numBits, strValue);
    break;
  }
}

void XmlAstReader::registerAttr_D_ptrToMember(D_ptrToMember *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a D_ptrToMember");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_nestedName:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->nestedName), strValue,XTOK_PQName, false));
    break;
  case XTOK_cv:
    fromXml(obj->cv, strValue);
    break;
  case XTOK_base:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->base), strValue,XTOK_IDeclarator, false));
    break;
  }
}

void XmlAstReader::registerAttr_D_grouping(D_grouping *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a D_grouping");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_base:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->base), strValue,XTOK_IDeclarator, false));
    break;
  }
}

void XmlAstReader::registerAttr_ExceptionSpec(ExceptionSpec *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a ExceptionSpec");
    break;
  case XTOK_types:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->types), strValue, XTOK_List_ExceptionSpec_types, true));
    break;
  }
}

void XmlAstReader::registerAttr_ON_newDel(ON_newDel *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a ON_newDel");
    break;
  case XTOK_isNew:
    fromXml_bool(obj->isNew, strValue);
    break;
  case XTOK_isArray:
    fromXml_bool(obj->isArray, strValue);
    break;
  }
}

void XmlAstReader::registerAttr_ON_operator(ON_operator *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a ON_operator");
    break;
  case XTOK_op:
    fromXml(obj->op, strValue);
    break;
  }
}

void XmlAstReader::registerAttr_ON_conversion(ON_conversion *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a ON_conversion");
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_ASTTypeId, false));
    break;
  }
}

void XmlAstReader::registerAttr_S_skip(S_skip *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a S_skip");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  }
}

void XmlAstReader::registerAttr_S_label(S_label *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a S_label");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_name:
    obj->name = manager->strTable(strValue);
    break;
  case XTOK_s:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->s), strValue,XTOK_Statement, false));
    break;
  }
}

void XmlAstReader::registerAttr_S_case(S_case *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a S_case");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_expr:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->expr), strValue,XTOK_Expression, false));
    break;
  case XTOK_s:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->s), strValue,XTOK_Statement, false));
    break;
  case XTOK_labelVal:
    fromXml_int(obj->labelVal, strValue);
    break;
  }
}

void XmlAstReader::registerAttr_S_default(S_default *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a S_default");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_s:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->s), strValue,XTOK_Statement, false));
    break;
  }
}

void XmlAstReader::registerAttr_S_expr(S_expr *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a S_expr");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_expr:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->expr), strValue,XTOK_FullExpression, false));
    break;
  }
}

void XmlAstReader::registerAttr_S_compound(S_compound *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a S_compound");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_stmts:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->stmts), strValue, XTOK_List_S_compound_stmts, true));
    break;
  }
}

void XmlAstReader::registerAttr_S_if(S_if *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a S_if");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_cond:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->cond), strValue,XTOK_Condition, false));
    break;
  case XTOK_thenBranch:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->thenBranch), strValue,XTOK_Statement, false));
    break;
  case XTOK_elseBranch:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->elseBranch), strValue,XTOK_Statement, false));
    break;
  }
}

void XmlAstReader::registerAttr_S_switch(S_switch *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a S_switch");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_cond:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->cond), strValue,XTOK_Condition, false));
    break;
  case XTOK_branches:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->branches), strValue,XTOK_Statement, false));
    break;
  }
}

void XmlAstReader::registerAttr_S_while(S_while *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a S_while");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_cond:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->cond), strValue,XTOK_Condition, false));
    break;
  case XTOK_body:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->body), strValue,XTOK_Statement, false));
    break;
  }
}

void XmlAstReader::registerAttr_S_doWhile(S_doWhile *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a S_doWhile");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_body:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->body), strValue,XTOK_Statement, false));
    break;
  case XTOK_expr:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->expr), strValue,XTOK_FullExpression, false));
    break;
  }
}

void XmlAstReader::registerAttr_S_for(S_for *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a S_for");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_init:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->init), strValue,XTOK_Statement, false));
    break;
  case XTOK_cond:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->cond), strValue,XTOK_Condition, false));
    break;
  case XTOK_after:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->after), strValue,XTOK_FullExpression, false));
    break;
  case XTOK_body:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->body), strValue,XTOK_Statement, false));
    break;
  }
}

void XmlAstReader::registerAttr_S_break(S_break *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a S_break");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  }
}

void XmlAstReader::registerAttr_S_continue(S_continue *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a S_continue");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  }
}

void XmlAstReader::registerAttr_S_return(S_return *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a S_return");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_expr:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->expr), strValue,XTOK_FullExpression, false));
    break;
  case XTOK_ctorStatement:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->ctorStatement), strValue,XTOK_Statement, false));
    break;
  }
}

void XmlAstReader::registerAttr_S_goto(S_goto *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a S_goto");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_target:
    obj->target = manager->strTable(strValue);
    break;
  }
}

void XmlAstReader::registerAttr_S_decl(S_decl *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a S_decl");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_decl:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->decl), strValue,XTOK_Declaration, false));
    break;
  }
}

void XmlAstReader::registerAttr_S_try(S_try *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a S_try");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_body:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->body), strValue,XTOK_Statement, false));
    break;
  case XTOK_handlers:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->handlers), strValue, XTOK_List_S_try_handlers, true));
    break;
  }
}

void XmlAstReader::registerAttr_S_asm(S_asm *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a S_asm");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_text:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->text), strValue,XTOK_E_stringLit, false));
    break;
  }
}

void XmlAstReader::registerAttr_S_namespaceDecl(S_namespaceDecl *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a S_namespaceDecl");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_decl:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->decl), strValue,XTOK_NamespaceDecl, false));
    break;
  }
}

void XmlAstReader::registerAttr_S_function(S_function *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a S_function");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_f:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->f), strValue,XTOK_Function, false));
    break;
  }
}

void XmlAstReader::registerAttr_S_rangeCase(S_rangeCase *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a S_rangeCase");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_exprLo:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->exprLo), strValue,XTOK_Expression, false));
    break;
  case XTOK_exprHi:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->exprHi), strValue,XTOK_Expression, false));
    break;
  case XTOK_s:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->s), strValue,XTOK_Statement, false));
    break;
  case XTOK_labelValLo:
    fromXml_int(obj->labelValLo, strValue);
    break;
  case XTOK_labelValHi:
    fromXml_int(obj->labelValHi, strValue);
    break;
  }
}

void XmlAstReader::registerAttr_S_computedGoto(S_computedGoto *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a S_computedGoto");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_target:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->target), strValue,XTOK_Expression, false));
    break;
  }
}

void XmlAstReader::registerAttr_CN_expr(CN_expr *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a CN_expr");
    break;
  case XTOK_expr:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->expr), strValue,XTOK_FullExpression, false));
    break;
  }
}

void XmlAstReader::registerAttr_CN_decl(CN_decl *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a CN_decl");
    break;
  case XTOK_typeId:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->typeId), strValue,XTOK_ASTTypeId, false));
    break;
  }
}

void XmlAstReader::registerAttr_Handler(Handler *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a Handler");
    break;
  case XTOK_typeId:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->typeId), strValue,XTOK_ASTTypeId, false));
    break;
  case XTOK_body:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->body), strValue,XTOK_Statement, false));
    break;
  case XTOK_globalVar:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->globalVar), strValue,XTOK_Variable, false));
    break;
  case XTOK_annot:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->annot), strValue,XTOK_FullExpressionAnnot, false));
    break;
  case XTOK_localArg:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->localArg), strValue,XTOK_Expression, false));
    break;
  case XTOK_globalDtorStatement:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->globalDtorStatement), strValue,XTOK_Statement, false));
    break;
  }
}

void XmlAstReader::registerAttr_E_boolLit(E_boolLit *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a E_boolLit");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_Type, false));
    break;
  case XTOK_b:
    fromXml_bool(obj->b, strValue);
    break;
  }
}

void XmlAstReader::registerAttr_E_intLit(E_intLit *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a E_intLit");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_Type, false));
    break;
  case XTOK_text:
    obj->text = manager->strTable(strValue);
    break;
  case XTOK_i:
    fromXml_unsigned_long(obj->i, strValue);
    break;
  }
}

void XmlAstReader::registerAttr_E_floatLit(E_floatLit *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a E_floatLit");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_Type, false));
    break;
  case XTOK_text:
    obj->text = manager->strTable(strValue);
    break;
  case XTOK_d:
    fromXml_double(obj->d, strValue);
    break;
  }
}

void XmlAstReader::registerAttr_E_stringLit(E_stringLit *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a E_stringLit");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_Type, false));
    break;
  case XTOK_text:
    obj->text = manager->strTable(strValue);
    break;
  case XTOK_continuation:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->continuation), strValue,XTOK_E_stringLit, false));
    break;
  case XTOK_fullTextNQ:
    obj->fullTextNQ = manager->strTable(strValue);
    break;
  }
}

void XmlAstReader::registerAttr_E_charLit(E_charLit *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a E_charLit");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_Type, false));
    break;
  case XTOK_text:
    obj->text = manager->strTable(strValue);
    break;
  case XTOK_c:
    fromXml_unsigned_int(obj->c, strValue);
    break;
  }
}

void XmlAstReader::registerAttr_E_this(E_this *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a E_this");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_Type, false));
    break;
  case XTOK_receiver:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->receiver), strValue,XTOK_Variable, false));
    break;
  }
}

void XmlAstReader::registerAttr_E_variable(E_variable *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a E_variable");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_Type, false));
    break;
  case XTOK_name:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->name), strValue,XTOK_PQName, false));
    break;
  case XTOK_var:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->var), strValue,XTOK_Variable, false));
    break;
  case XTOK_nondependentVar:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->nondependentVar), strValue,XTOK_Variable, false));
    break;
  }
}

void XmlAstReader::registerAttr_E_funCall(E_funCall *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a E_funCall");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_Type, false));
    break;
  case XTOK_func:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->func), strValue,XTOK_Expression, false));
    break;
  case XTOK_args:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->args), strValue, XTOK_List_E_funCall_args, true));
    break;
  case XTOK_retObj:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->retObj), strValue,XTOK_Expression, false));
    break;
  }
}

void XmlAstReader::registerAttr_E_constructor(E_constructor *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a E_constructor");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_Type, false));
    break;
  case XTOK_spec:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->spec), strValue,XTOK_TypeSpecifier, false));
    break;
  case XTOK_args:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->args), strValue, XTOK_List_E_constructor_args, true));
    break;
  case XTOK_ctorVar:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->ctorVar), strValue,XTOK_Variable, false));
    break;
  case XTOK_artificial:
    fromXml_bool(obj->artificial, strValue);
    break;
  case XTOK_retObj:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->retObj), strValue,XTOK_Expression, false));
    break;
  }
}

void XmlAstReader::registerAttr_E_fieldAcc(E_fieldAcc *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a E_fieldAcc");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_Type, false));
    break;
  case XTOK_obj:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->obj), strValue,XTOK_Expression, false));
    break;
  case XTOK_fieldName:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->fieldName), strValue,XTOK_PQName, false));
    break;
  case XTOK_field:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->field), strValue,XTOK_Variable, false));
    break;
  }
}

void XmlAstReader::registerAttr_E_sizeof(E_sizeof *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a E_sizeof");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_Type, false));
    break;
  case XTOK_expr:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->expr), strValue,XTOK_Expression, false));
    break;
  case XTOK_size:
    fromXml_int(obj->size, strValue);
    break;
  }
}

void XmlAstReader::registerAttr_E_unary(E_unary *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a E_unary");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_Type, false));
    break;
  case XTOK_op:
    fromXml(obj->op, strValue);
    break;
  case XTOK_expr:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->expr), strValue,XTOK_Expression, false));
    break;
  }
}

void XmlAstReader::registerAttr_E_effect(E_effect *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a E_effect");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_Type, false));
    break;
  case XTOK_op:
    fromXml(obj->op, strValue);
    break;
  case XTOK_expr:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->expr), strValue,XTOK_Expression, false));
    break;
  }
}

void XmlAstReader::registerAttr_E_binary(E_binary *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a E_binary");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_Type, false));
    break;
  case XTOK_e1:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->e1), strValue,XTOK_Expression, false));
    break;
  case XTOK_op:
    fromXml(obj->op, strValue);
    break;
  case XTOK_e2:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->e2), strValue,XTOK_Expression, false));
    break;
  }
}

void XmlAstReader::registerAttr_E_addrOf(E_addrOf *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a E_addrOf");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_Type, false));
    break;
  case XTOK_expr:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->expr), strValue,XTOK_Expression, false));
    break;
  }
}

void XmlAstReader::registerAttr_E_deref(E_deref *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a E_deref");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_Type, false));
    break;
  case XTOK_ptr:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->ptr), strValue,XTOK_Expression, false));
    break;
  }
}

void XmlAstReader::registerAttr_E_cast(E_cast *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a E_cast");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_Type, false));
    break;
  case XTOK_ctype:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->ctype), strValue,XTOK_ASTTypeId, false));
    break;
  case XTOK_expr:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->expr), strValue,XTOK_Expression, false));
    break;
  case XTOK_tcheckedType:
    fromXml_bool(obj->tcheckedType, strValue);
    break;
  }
}

void XmlAstReader::registerAttr_E_cond(E_cond *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a E_cond");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_Type, false));
    break;
  case XTOK_cond:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->cond), strValue,XTOK_Expression, false));
    break;
  case XTOK_th:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->th), strValue,XTOK_Expression, false));
    break;
  case XTOK_el:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->el), strValue,XTOK_Expression, false));
    break;
  }
}

void XmlAstReader::registerAttr_E_sizeofType(E_sizeofType *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a E_sizeofType");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_Type, false));
    break;
  case XTOK_atype:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->atype), strValue,XTOK_ASTTypeId, false));
    break;
  case XTOK_size:
    fromXml_int(obj->size, strValue);
    break;
  case XTOK_tchecked:
    fromXml_bool(obj->tchecked, strValue);
    break;
  }
}

void XmlAstReader::registerAttr_E_assign(E_assign *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a E_assign");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_Type, false));
    break;
  case XTOK_target:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->target), strValue,XTOK_Expression, false));
    break;
  case XTOK_op:
    fromXml(obj->op, strValue);
    break;
  case XTOK_src:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->src), strValue,XTOK_Expression, false));
    break;
  }
}

void XmlAstReader::registerAttr_E_new(E_new *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a E_new");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_Type, false));
    break;
  case XTOK_colonColon:
    fromXml_bool(obj->colonColon, strValue);
    break;
  case XTOK_placementArgs:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->placementArgs), strValue, XTOK_List_E_new_placementArgs, true));
    break;
  case XTOK_atype:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->atype), strValue,XTOK_ASTTypeId, false));
    break;
  case XTOK_ctorArgs:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->ctorArgs), strValue,XTOK_ArgExpressionListOpt, false));
    break;
  case XTOK_arraySize:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->arraySize), strValue,XTOK_Expression, false));
    break;
  case XTOK_ctorVar:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->ctorVar), strValue,XTOK_Variable, false));
    break;
  case XTOK_ctorStatement:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->ctorStatement), strValue,XTOK_Statement, false));
    break;
  case XTOK_heapVar:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->heapVar), strValue,XTOK_Variable, false));
    break;
  }
}

void XmlAstReader::registerAttr_E_delete(E_delete *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a E_delete");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_Type, false));
    break;
  case XTOK_colonColon:
    fromXml_bool(obj->colonColon, strValue);
    break;
  case XTOK_array:
    fromXml_bool(obj->array, strValue);
    break;
  case XTOK_expr:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->expr), strValue,XTOK_Expression, false));
    break;
  case XTOK_dtorStatement:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->dtorStatement), strValue,XTOK_Statement, false));
    break;
  }
}

void XmlAstReader::registerAttr_E_throw(E_throw *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a E_throw");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_Type, false));
    break;
  case XTOK_expr:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->expr), strValue,XTOK_Expression, false));
    break;
  case XTOK_globalVar:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->globalVar), strValue,XTOK_Variable, false));
    break;
  case XTOK_globalCtorStatement:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->globalCtorStatement), strValue,XTOK_Statement, false));
    break;
  }
}

void XmlAstReader::registerAttr_E_keywordCast(E_keywordCast *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a E_keywordCast");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_Type, false));
    break;
  case XTOK_key:
    fromXml(obj->key, strValue);
    break;
  case XTOK_ctype:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->ctype), strValue,XTOK_ASTTypeId, false));
    break;
  case XTOK_expr:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->expr), strValue,XTOK_Expression, false));
    break;
  }
}

void XmlAstReader::registerAttr_E_typeidExpr(E_typeidExpr *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a E_typeidExpr");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_Type, false));
    break;
  case XTOK_expr:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->expr), strValue,XTOK_Expression, false));
    break;
  }
}

void XmlAstReader::registerAttr_E_typeidType(E_typeidType *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a E_typeidType");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_Type, false));
    break;
  case XTOK_ttype:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->ttype), strValue,XTOK_ASTTypeId, false));
    break;
  }
}

void XmlAstReader::registerAttr_E_grouping(E_grouping *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a E_grouping");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_Type, false));
    break;
  case XTOK_expr:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->expr), strValue,XTOK_Expression, false));
    break;
  }
}

void XmlAstReader::registerAttr_E_arrow(E_arrow *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a E_arrow");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_Type, false));
    break;
  case XTOK_obj:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->obj), strValue,XTOK_Expression, false));
    break;
  case XTOK_fieldName:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->fieldName), strValue,XTOK_PQName, false));
    break;
  }
}

void XmlAstReader::registerAttr_E_statement(E_statement *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a E_statement");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_Type, false));
    break;
  case XTOK_s:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->s), strValue,XTOK_S_compound, false));
    break;
  }
}

void XmlAstReader::registerAttr_E_compoundLit(E_compoundLit *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a E_compoundLit");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_Type, false));
    break;
  case XTOK_stype:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->stype), strValue,XTOK_ASTTypeId, false));
    break;
  case XTOK_init:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->init), strValue,XTOK_IN_compound, false));
    break;
  }
}

void XmlAstReader::registerAttr_E___builtin_constant_p(E___builtin_constant_p *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a E___builtin_constant_p");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_Type, false));
    break;
  case XTOK_expr:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->expr), strValue,XTOK_Expression, false));
    break;
  }
}

void XmlAstReader::registerAttr_E___builtin_va_arg(E___builtin_va_arg *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a E___builtin_va_arg");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_Type, false));
    break;
  case XTOK_expr:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->expr), strValue,XTOK_Expression, false));
    break;
  case XTOK_atype:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->atype), strValue,XTOK_ASTTypeId, false));
    break;
  }
}

void XmlAstReader::registerAttr_E_alignofType(E_alignofType *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a E_alignofType");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_Type, false));
    break;
  case XTOK_atype:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->atype), strValue,XTOK_ASTTypeId, false));
    break;
  case XTOK_alignment:
    fromXml_int(obj->alignment, strValue);
    break;
  }
}

void XmlAstReader::registerAttr_E_alignofExpr(E_alignofExpr *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a E_alignofExpr");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_Type, false));
    break;
  case XTOK_expr:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->expr), strValue,XTOK_Expression, false));
    break;
  case XTOK_alignment:
    fromXml_int(obj->alignment, strValue);
    break;
  }
}

void XmlAstReader::registerAttr_E_gnuCond(E_gnuCond *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a E_gnuCond");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_Type, false));
    break;
  case XTOK_cond:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->cond), strValue,XTOK_Expression, false));
    break;
  case XTOK_el:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->el), strValue,XTOK_Expression, false));
    break;
  }
}

void XmlAstReader::registerAttr_E_addrOfLabel(E_addrOfLabel *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a E_addrOfLabel");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_endloc:
    fromXml_SourceLoc(obj->endloc, strValue);
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_Type, false));
    break;
  case XTOK_labelName:
    obj->labelName = manager->strTable(strValue);
    break;
  }
}

void XmlAstReader::registerAttr_FullExpression(FullExpression *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a FullExpression");
    break;
  case XTOK_expr:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->expr), strValue,XTOK_Expression, false));
    break;
  case XTOK_annot:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->annot), strValue,XTOK_FullExpressionAnnot, false));
    break;
  }
}

void XmlAstReader::registerAttr_ArgExpression(ArgExpression *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a ArgExpression");
    break;
  case XTOK_expr:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->expr), strValue,XTOK_Expression, false));
    break;
  }
}

void XmlAstReader::registerAttr_ArgExpressionListOpt(ArgExpressionListOpt *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a ArgExpressionListOpt");
    break;
  case XTOK_list:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->list), strValue, XTOK_List_ArgExpressionListOpt_list, true));
    break;
  }
}

void XmlAstReader::registerAttr_IN_expr(IN_expr *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a IN_expr");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_annot:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->annot), strValue,XTOK_FullExpressionAnnot, false));
    break;
  case XTOK_e:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->e), strValue,XTOK_Expression, false));
    break;
  }
}

void XmlAstReader::registerAttr_IN_compound(IN_compound *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a IN_compound");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_annot:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->annot), strValue,XTOK_FullExpressionAnnot, false));
    break;
  case XTOK_inits:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->inits), strValue, XTOK_List_IN_compound_inits, true));
    break;
  }
}

void XmlAstReader::registerAttr_IN_ctor(IN_ctor *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a IN_ctor");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_annot:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->annot), strValue,XTOK_FullExpressionAnnot, false));
    break;
  case XTOK_args:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->args), strValue, XTOK_List_IN_ctor_args, true));
    break;
  case XTOK_ctorVar:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->ctorVar), strValue,XTOK_Variable, false));
    break;
  case XTOK_was_IN_expr:
    fromXml_bool(obj->was_IN_expr, strValue);
    break;
  }
}

void XmlAstReader::registerAttr_IN_designated(IN_designated *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a IN_designated");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_annot:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->annot), strValue,XTOK_FullExpressionAnnot, false));
    break;
  case XTOK_designator_list:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->designator_list), strValue, XTOK_List_IN_designated_designator_list, true));
    break;
  case XTOK_init:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->init), strValue,XTOK_Initializer, false));
    break;
  }
}

void XmlAstReader::registerAttr_TD_func(TD_func *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a TD_func");
    break;
  case XTOK_params:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->params), strValue,XTOK_TemplateParameter, false));
    break;
  case XTOK_f:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->f), strValue,XTOK_Function, false));
    break;
  }
}

void XmlAstReader::registerAttr_TD_decl(TD_decl *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a TD_decl");
    break;
  case XTOK_params:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->params), strValue,XTOK_TemplateParameter, false));
    break;
  case XTOK_d:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->d), strValue,XTOK_Declaration, false));
    break;
  }
}

void XmlAstReader::registerAttr_TD_tmember(TD_tmember *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a TD_tmember");
    break;
  case XTOK_params:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->params), strValue,XTOK_TemplateParameter, false));
    break;
  case XTOK_d:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->d), strValue,XTOK_TemplateDeclaration, false));
    break;
  }
}

void XmlAstReader::registerAttr_TP_type(TP_type *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a TP_type");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_var:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->var), strValue,XTOK_Variable, false));
    break;
  case XTOK_next:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->next), strValue,XTOK_TemplateParameter, false));
    break;
  case XTOK_name:
    obj->name = manager->strTable(strValue);
    break;
  case XTOK_defaultType:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->defaultType), strValue,XTOK_ASTTypeId, false));
    break;
  }
}

void XmlAstReader::registerAttr_TP_nontype(TP_nontype *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a TP_nontype");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_var:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->var), strValue,XTOK_Variable, false));
    break;
  case XTOK_next:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->next), strValue,XTOK_TemplateParameter, false));
    break;
  case XTOK_param:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->param), strValue,XTOK_ASTTypeId, false));
    break;
  }
}

void XmlAstReader::registerAttr_TP_template(TP_template *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a TP_template");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_var:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->var), strValue,XTOK_Variable, false));
    break;
  case XTOK_next:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->next), strValue,XTOK_TemplateParameter, false));
    break;
  case XTOK_parameters:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->parameters), strValue, XTOK_List_TP_template_parameters, true));
    break;
  case XTOK_name:
    obj->name = manager->strTable(strValue);
    break;
  case XTOK_defaultTemplate:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->defaultTemplate), strValue,XTOK_PQName, false));
    break;
  }
}

void XmlAstReader::registerAttr_TA_type(TA_type *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a TA_type");
    break;
  case XTOK_next:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->next), strValue,XTOK_TemplateArgument, false));
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_ASTTypeId, false));
    break;
  }
}

void XmlAstReader::registerAttr_TA_nontype(TA_nontype *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a TA_nontype");
    break;
  case XTOK_next:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->next), strValue,XTOK_TemplateArgument, false));
    break;
  case XTOK_expr:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->expr), strValue,XTOK_Expression, false));
    break;
  }
}

void XmlAstReader::registerAttr_TA_templateUsed(TA_templateUsed *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a TA_templateUsed");
    break;
  case XTOK_next:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->next), strValue,XTOK_TemplateArgument, false));
    break;
  }
}

void XmlAstReader::registerAttr_ND_alias(ND_alias *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a ND_alias");
    break;
  case XTOK_alias:
    obj->alias = manager->strTable(strValue);
    break;
  case XTOK_original:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->original), strValue,XTOK_PQName, false));
    break;
  }
}

void XmlAstReader::registerAttr_ND_usingDecl(ND_usingDecl *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a ND_usingDecl");
    break;
  case XTOK_name:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->name), strValue,XTOK_PQName, false));
    break;
  }
}

void XmlAstReader::registerAttr_ND_usingDir(ND_usingDir *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a ND_usingDir");
    break;
  case XTOK_name:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->name), strValue,XTOK_PQName, false));
    break;
  }
}

void XmlAstReader::registerAttr_FullExpressionAnnot(FullExpressionAnnot *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a FullExpressionAnnot");
    break;
  case XTOK_declarations:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->declarations), strValue, XTOK_List_FullExpressionAnnot_declarations, true));
    break;
  }
}

void XmlAstReader::registerAttr_TS_typeof_expr(TS_typeof_expr *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a TS_typeof_expr");
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_Type, false));
    break;
  case XTOK_expr:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->expr), strValue,XTOK_FullExpression, false));
    break;
  }
}

void XmlAstReader::registerAttr_TS_typeof_type(TS_typeof_type *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a TS_typeof_type");
    break;
  case XTOK_type:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->type), strValue,XTOK_Type, false));
    break;
  case XTOK_atype:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->atype), strValue,XTOK_ASTTypeId, false));
    break;
  }
}

void XmlAstReader::registerAttr_FieldDesignator(FieldDesignator *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a FieldDesignator");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_id:
    obj->id = manager->strTable(strValue);
    break;
  }
}

void XmlAstReader::registerAttr_SubscriptDesignator(SubscriptDesignator *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a SubscriptDesignator");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_idx_expr:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->idx_expr), strValue,XTOK_Expression, false));
    break;
  case XTOK_idx_expr2:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->idx_expr2), strValue,XTOK_Expression, false));
    break;
  case XTOK_idx_computed:
    fromXml_int(obj->idx_computed, strValue);
    break;
  case XTOK_idx_computed2:
    fromXml_int(obj->idx_computed2, strValue);
    break;
  }
}

void XmlAstReader::registerAttr_AttributeSpecifierList(AttributeSpecifierList *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a AttributeSpecifierList");
    break;
  case XTOK_spec:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->spec), strValue,XTOK_AttributeSpecifier, false));
    break;
  case XTOK_next:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->next), strValue,XTOK_AttributeSpecifierList, false));
    break;
  }
}

void XmlAstReader::registerAttr_AttributeSpecifier(AttributeSpecifier *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a AttributeSpecifier");
    break;
  case XTOK_attr:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->attr), strValue,XTOK_Attribute, false));
    break;
  case XTOK_next:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->next), strValue,XTOK_AttributeSpecifier, false));
    break;
  }
}

void XmlAstReader::registerAttr_AT_empty(AT_empty *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a AT_empty");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  }
}

void XmlAstReader::registerAttr_AT_word(AT_word *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a AT_word");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_w:
    obj->w = manager->strTable(strValue);
    break;
  }
}

void XmlAstReader::registerAttr_AT_func(AT_func *obj, int attr, char const *strValue) {
  switch(attr) {
  default:
    xmlUserFatalError("illegal attribute for a AT_func");
    break;
  case XTOK_loc:
    fromXml_SourceLoc(obj->loc, strValue);
    break;
  case XTOK_f:
    obj->f = manager->strTable(strValue);
    break;
  case XTOK_args:
    manager->addUnsatLink(new UnsatLink((void*) &(obj->args), strValue, XTOK_List_AT_func_args, true));
    break;
  }
}

bool XmlAstReader::recordKind(int kind, bool& answer) {
  switch(kind) {
  default: return false; break;
  case XTOK_TranslationUnit: answer = false; return true; break;
  case XTOK_TF_decl: answer = false; return true; break;
  case XTOK_TF_func: answer = false; return true; break;
  case XTOK_TF_template: answer = false; return true; break;
  case XTOK_TF_explicitInst: answer = false; return true; break;
  case XTOK_TF_linkage: answer = false; return true; break;
  case XTOK_TF_one_linkage: answer = false; return true; break;
  case XTOK_TF_asm: answer = false; return true; break;
  case XTOK_TF_namespaceDefn: answer = false; return true; break;
  case XTOK_TF_namespaceDecl: answer = false; return true; break;
  case XTOK_Function: answer = false; return true; break;
  case XTOK_MemberInit: answer = false; return true; break;
  case XTOK_Declaration: answer = false; return true; break;
  case XTOK_ASTTypeId: answer = false; return true; break;
  case XTOK_PQ_qualifier: answer = false; return true; break;
  case XTOK_PQ_name: answer = false; return true; break;
  case XTOK_PQ_operator: answer = false; return true; break;
  case XTOK_PQ_template: answer = false; return true; break;
  case XTOK_PQ_variable: answer = false; return true; break;
  case XTOK_TS_name: answer = false; return true; break;
  case XTOK_TS_simple: answer = false; return true; break;
  case XTOK_TS_elaborated: answer = false; return true; break;
  case XTOK_TS_classSpec: answer = false; return true; break;
  case XTOK_TS_enumSpec: answer = false; return true; break;
  case XTOK_TS_type: answer = false; return true; break;
  case XTOK_TS_typeof: answer = false; return true; break;
  case XTOK_BaseClassSpec: answer = false; return true; break;
  case XTOK_Enumerator: answer = false; return true; break;
  case XTOK_MemberList: answer = false; return true; break;
  case XTOK_MR_decl: answer = false; return true; break;
  case XTOK_MR_func: answer = false; return true; break;
  case XTOK_MR_access: answer = false; return true; break;
  case XTOK_MR_usingDecl: answer = false; return true; break;
  case XTOK_MR_template: answer = false; return true; break;
  case XTOK_Declarator: answer = false; return true; break;
  case XTOK_D_name: answer = false; return true; break;
  case XTOK_D_pointer: answer = false; return true; break;
  case XTOK_D_reference: answer = false; return true; break;
  case XTOK_D_func: answer = false; return true; break;
  case XTOK_D_array: answer = false; return true; break;
  case XTOK_D_bitfield: answer = false; return true; break;
  case XTOK_D_ptrToMember: answer = false; return true; break;
  case XTOK_D_grouping: answer = false; return true; break;
  case XTOK_ExceptionSpec: answer = false; return true; break;
  case XTOK_ON_newDel: answer = false; return true; break;
  case XTOK_ON_operator: answer = false; return true; break;
  case XTOK_ON_conversion: answer = false; return true; break;
  case XTOK_S_skip: answer = false; return true; break;
  case XTOK_S_label: answer = false; return true; break;
  case XTOK_S_case: answer = false; return true; break;
  case XTOK_S_default: answer = false; return true; break;
  case XTOK_S_expr: answer = false; return true; break;
  case XTOK_S_compound: answer = false; return true; break;
  case XTOK_S_if: answer = false; return true; break;
  case XTOK_S_switch: answer = false; return true; break;
  case XTOK_S_while: answer = false; return true; break;
  case XTOK_S_doWhile: answer = false; return true; break;
  case XTOK_S_for: answer = false; return true; break;
  case XTOK_S_break: answer = false; return true; break;
  case XTOK_S_continue: answer = false; return true; break;
  case XTOK_S_return: answer = false; return true; break;
  case XTOK_S_goto: answer = false; return true; break;
  case XTOK_S_decl: answer = false; return true; break;
  case XTOK_S_try: answer = false; return true; break;
  case XTOK_S_asm: answer = false; return true; break;
  case XTOK_S_namespaceDecl: answer = false; return true; break;
  case XTOK_S_function: answer = false; return true; break;
  case XTOK_S_rangeCase: answer = false; return true; break;
  case XTOK_S_computedGoto: answer = false; return true; break;
  case XTOK_CN_expr: answer = false; return true; break;
  case XTOK_CN_decl: answer = false; return true; break;
  case XTOK_Handler: answer = false; return true; break;
  case XTOK_E_boolLit: answer = false; return true; break;
  case XTOK_E_intLit: answer = false; return true; break;
  case XTOK_E_floatLit: answer = false; return true; break;
  case XTOK_E_stringLit: answer = false; return true; break;
  case XTOK_E_charLit: answer = false; return true; break;
  case XTOK_E_this: answer = false; return true; break;
  case XTOK_E_variable: answer = false; return true; break;
  case XTOK_E_funCall: answer = false; return true; break;
  case XTOK_E_constructor: answer = false; return true; break;
  case XTOK_E_fieldAcc: answer = false; return true; break;
  case XTOK_E_sizeof: answer = false; return true; break;
  case XTOK_E_unary: answer = false; return true; break;
  case XTOK_E_effect: answer = false; return true; break;
  case XTOK_E_binary: answer = false; return true; break;
  case XTOK_E_addrOf: answer = false; return true; break;
  case XTOK_E_deref: answer = false; return true; break;
  case XTOK_E_cast: answer = false; return true; break;
  case XTOK_E_cond: answer = false; return true; break;
  case XTOK_E_sizeofType: answer = false; return true; break;
  case XTOK_E_assign: answer = false; return true; break;
  case XTOK_E_new: answer = false; return true; break;
  case XTOK_E_delete: answer = false; return true; break;
  case XTOK_E_throw: answer = false; return true; break;
  case XTOK_E_keywordCast: answer = false; return true; break;
  case XTOK_E_typeidExpr: answer = false; return true; break;
  case XTOK_E_typeidType: answer = false; return true; break;
  case XTOK_E_grouping: answer = false; return true; break;
  case XTOK_E_arrow: answer = false; return true; break;
  case XTOK_E_statement: answer = false; return true; break;
  case XTOK_E_compoundLit: answer = false; return true; break;
  case XTOK_E___builtin_constant_p: answer = false; return true; break;
  case XTOK_E___builtin_va_arg: answer = false; return true; break;
  case XTOK_E_alignofType: answer = false; return true; break;
  case XTOK_E_alignofExpr: answer = false; return true; break;
  case XTOK_E_gnuCond: answer = false; return true; break;
  case XTOK_E_addrOfLabel: answer = false; return true; break;
  case XTOK_FullExpression: answer = false; return true; break;
  case XTOK_ArgExpression: answer = false; return true; break;
  case XTOK_ArgExpressionListOpt: answer = false; return true; break;
  case XTOK_IN_expr: answer = false; return true; break;
  case XTOK_IN_compound: answer = false; return true; break;
  case XTOK_IN_ctor: answer = false; return true; break;
  case XTOK_IN_designated: answer = false; return true; break;
  case XTOK_TD_func: answer = false; return true; break;
  case XTOK_TD_decl: answer = false; return true; break;
  case XTOK_TD_tmember: answer = false; return true; break;
  case XTOK_TP_type: answer = false; return true; break;
  case XTOK_TP_nontype: answer = false; return true; break;
  case XTOK_TP_template: answer = false; return true; break;
  case XTOK_TA_type: answer = false; return true; break;
  case XTOK_TA_nontype: answer = false; return true; break;
  case XTOK_TA_templateUsed: answer = false; return true; break;
  case XTOK_ND_alias: answer = false; return true; break;
  case XTOK_ND_usingDecl: answer = false; return true; break;
  case XTOK_ND_usingDir: answer = false; return true; break;
  case XTOK_FullExpressionAnnot: answer = false; return true; break;
  case XTOK_TS_typeof_expr: answer = false; return true; break;
  case XTOK_TS_typeof_type: answer = false; return true; break;
  case XTOK_FieldDesignator: answer = false; return true; break;
  case XTOK_SubscriptDesignator: answer = false; return true; break;
  case XTOK_AttributeSpecifierList: answer = false; return true; break;
  case XTOK_AttributeSpecifier: answer = false; return true; break;
  case XTOK_AT_empty: answer = false; return true; break;
  case XTOK_AT_word: answer = false; return true; break;
  case XTOK_AT_func: answer = false; return true; break;
  case XTOK_List_TF_namespaceDefn_forms: answer = false; return true; break;
  case XTOK_List_TranslationUnit_topForms: answer = false; return true; break;
  case XTOK_List_Function_inits: answer = false; return true; break;
  case XTOK_List_Function_handlers: answer = false; return true; break;
  case XTOK_List_MemberInit_args: answer = false; return true; break;
  case XTOK_List_MemberList_list: answer = false; return true; break;
  case XTOK_List_Declaration_decllist: answer = false; return true; break;
  case XTOK_List_TS_classSpec_bases: answer = false; return true; break;
  case XTOK_List_TS_enumSpec_elts: answer = false; return true; break;
  case XTOK_List_D_func_params: answer = false; return true; break;
  case XTOK_List_D_func_kAndR_params: answer = false; return true; break;
  case XTOK_List_S_try_handlers: answer = false; return true; break;
  case XTOK_List_ExceptionSpec_types: answer = false; return true; break;
  case XTOK_List_S_compound_stmts: answer = false; return true; break;
  case XTOK_List_E_funCall_args: answer = false; return true; break;
  case XTOK_List_E_constructor_args: answer = false; return true; break;
  case XTOK_List_E_new_placementArgs: answer = false; return true; break;
  case XTOK_List_ArgExpressionListOpt_list: answer = false; return true; break;
  case XTOK_List_IN_compound_inits: answer = false; return true; break;
  case XTOK_List_IN_ctor_args: answer = false; return true; break;
  case XTOK_List_TP_template_parameters: answer = false; return true; break;
  case XTOK_List_IN_designated_designator_list: answer = false; return true; break;
  case XTOK_List_FullExpressionAnnot_declarations: answer = false; return true; break;
  case XTOK_List_AT_func_args: answer = false; return true; break;
  }
}

bool XmlAstReader::upcastToWantedType(void *obj, int kind, void **target, int targetKind) {
  switch(kind) {
  default: return false; break;
  case XTOK_TranslationUnit:
  case XTOK_TF_decl:
  case XTOK_TF_func:
  case XTOK_TF_template:
  case XTOK_TF_explicitInst:
  case XTOK_TF_linkage:
  case XTOK_TF_one_linkage:
  case XTOK_TF_asm:
  case XTOK_TF_namespaceDefn:
  case XTOK_TF_namespaceDecl:
  case XTOK_Function:
  case XTOK_MemberInit:
  case XTOK_Declaration:
  case XTOK_ASTTypeId:
  case XTOK_PQ_qualifier:
  case XTOK_PQ_name:
  case XTOK_PQ_operator:
  case XTOK_PQ_template:
  case XTOK_PQ_variable:
  case XTOK_TS_name:
  case XTOK_TS_simple:
  case XTOK_TS_elaborated:
  case XTOK_TS_classSpec:
  case XTOK_TS_enumSpec:
  case XTOK_TS_type:
  case XTOK_TS_typeof:
  case XTOK_BaseClassSpec:
  case XTOK_Enumerator:
  case XTOK_MemberList:
  case XTOK_MR_decl:
  case XTOK_MR_func:
  case XTOK_MR_access:
  case XTOK_MR_usingDecl:
  case XTOK_MR_template:
  case XTOK_Declarator:
  case XTOK_D_name:
  case XTOK_D_pointer:
  case XTOK_D_reference:
  case XTOK_D_func:
  case XTOK_D_array:
  case XTOK_D_bitfield:
  case XTOK_D_ptrToMember:
  case XTOK_D_grouping:
  case XTOK_ExceptionSpec:
  case XTOK_ON_newDel:
  case XTOK_ON_operator:
  case XTOK_ON_conversion:
  case XTOK_S_skip:
  case XTOK_S_label:
  case XTOK_S_case:
  case XTOK_S_default:
  case XTOK_S_expr:
  case XTOK_S_compound:
  case XTOK_S_if:
  case XTOK_S_switch:
  case XTOK_S_while:
  case XTOK_S_doWhile:
  case XTOK_S_for:
  case XTOK_S_break:
  case XTOK_S_continue:
  case XTOK_S_return:
  case XTOK_S_goto:
  case XTOK_S_decl:
  case XTOK_S_try:
  case XTOK_S_asm:
  case XTOK_S_namespaceDecl:
  case XTOK_S_function:
  case XTOK_S_rangeCase:
  case XTOK_S_computedGoto:
  case XTOK_CN_expr:
  case XTOK_CN_decl:
  case XTOK_Handler:
  case XTOK_E_boolLit:
  case XTOK_E_intLit:
  case XTOK_E_floatLit:
  case XTOK_E_stringLit:
  case XTOK_E_charLit:
  case XTOK_E_this:
  case XTOK_E_variable:
  case XTOK_E_funCall:
  case XTOK_E_constructor:
  case XTOK_E_fieldAcc:
  case XTOK_E_sizeof:
  case XTOK_E_unary:
  case XTOK_E_effect:
  case XTOK_E_binary:
  case XTOK_E_addrOf:
  case XTOK_E_deref:
  case XTOK_E_cast:
  case XTOK_E_cond:
  case XTOK_E_sizeofType:
  case XTOK_E_assign:
  case XTOK_E_new:
  case XTOK_E_delete:
  case XTOK_E_throw:
  case XTOK_E_keywordCast:
  case XTOK_E_typeidExpr:
  case XTOK_E_typeidType:
  case XTOK_E_grouping:
  case XTOK_E_arrow:
  case XTOK_E_statement:
  case XTOK_E_compoundLit:
  case XTOK_E___builtin_constant_p:
  case XTOK_E___builtin_va_arg:
  case XTOK_E_alignofType:
  case XTOK_E_alignofExpr:
  case XTOK_E_gnuCond:
  case XTOK_E_addrOfLabel:
  case XTOK_FullExpression:
  case XTOK_ArgExpression:
  case XTOK_ArgExpressionListOpt:
  case XTOK_IN_expr:
  case XTOK_IN_compound:
  case XTOK_IN_ctor:
  case XTOK_IN_designated:
  case XTOK_TD_func:
  case XTOK_TD_decl:
  case XTOK_TD_tmember:
  case XTOK_TP_type:
  case XTOK_TP_nontype:
  case XTOK_TP_template:
  case XTOK_TA_type:
  case XTOK_TA_nontype:
  case XTOK_TA_templateUsed:
  case XTOK_ND_alias:
  case XTOK_ND_usingDecl:
  case XTOK_ND_usingDir:
  case XTOK_FullExpressionAnnot:
  case XTOK_TS_typeof_expr:
  case XTOK_TS_typeof_type:
  case XTOK_FieldDesignator:
  case XTOK_SubscriptDesignator:
  case XTOK_AttributeSpecifierList:
  case XTOK_AttributeSpecifier:
  case XTOK_AT_empty:
  case XTOK_AT_word:
  case XTOK_AT_func:
  case XTOK_List_TF_namespaceDefn_forms:
  case XTOK_List_TranslationUnit_topForms:
  case XTOK_List_Function_inits:
  case XTOK_List_Function_handlers:
  case XTOK_List_MemberInit_args:
  case XTOK_List_MemberList_list:
  case XTOK_List_Declaration_decllist:
  case XTOK_List_TS_classSpec_bases:
  case XTOK_List_TS_enumSpec_elts:
  case XTOK_List_D_func_params:
  case XTOK_List_D_func_kAndR_params:
  case XTOK_List_S_try_handlers:
  case XTOK_List_ExceptionSpec_types:
  case XTOK_List_S_compound_stmts:
  case XTOK_List_E_funCall_args:
  case XTOK_List_E_constructor_args:
  case XTOK_List_E_new_placementArgs:
  case XTOK_List_ArgExpressionListOpt_list:
  case XTOK_List_IN_compound_inits:
  case XTOK_List_IN_ctor_args:
  case XTOK_List_TP_template_parameters:
  case XTOK_List_IN_designated_designator_list:
  case XTOK_List_FullExpressionAnnot_declarations:
  case XTOK_List_AT_func_args:
    xfailure("should never be called"); return true; break;
  }
}

bool XmlAstReader::callOpAssignToEmbeddedObj(void *obj, int kind, void *target) {
  switch(kind) {
  default: return false; break;
  case XTOK_TranslationUnit:
  case XTOK_TF_decl:
  case XTOK_TF_func:
  case XTOK_TF_template:
  case XTOK_TF_explicitInst:
  case XTOK_TF_linkage:
  case XTOK_TF_one_linkage:
  case XTOK_TF_asm:
  case XTOK_TF_namespaceDefn:
  case XTOK_TF_namespaceDecl:
  case XTOK_Function:
  case XTOK_MemberInit:
  case XTOK_Declaration:
  case XTOK_ASTTypeId:
  case XTOK_PQ_qualifier:
  case XTOK_PQ_name:
  case XTOK_PQ_operator:
  case XTOK_PQ_template:
  case XTOK_PQ_variable:
  case XTOK_TS_name:
  case XTOK_TS_simple:
  case XTOK_TS_elaborated:
  case XTOK_TS_classSpec:
  case XTOK_TS_enumSpec:
  case XTOK_TS_type:
  case XTOK_TS_typeof:
  case XTOK_BaseClassSpec:
  case XTOK_Enumerator:
  case XTOK_MemberList:
  case XTOK_MR_decl:
  case XTOK_MR_func:
  case XTOK_MR_access:
  case XTOK_MR_usingDecl:
  case XTOK_MR_template:
  case XTOK_Declarator:
  case XTOK_D_name:
  case XTOK_D_pointer:
  case XTOK_D_reference:
  case XTOK_D_func:
  case XTOK_D_array:
  case XTOK_D_bitfield:
  case XTOK_D_ptrToMember:
  case XTOK_D_grouping:
  case XTOK_ExceptionSpec:
  case XTOK_ON_newDel:
  case XTOK_ON_operator:
  case XTOK_ON_conversion:
  case XTOK_S_skip:
  case XTOK_S_label:
  case XTOK_S_case:
  case XTOK_S_default:
  case XTOK_S_expr:
  case XTOK_S_compound:
  case XTOK_S_if:
  case XTOK_S_switch:
  case XTOK_S_while:
  case XTOK_S_doWhile:
  case XTOK_S_for:
  case XTOK_S_break:
  case XTOK_S_continue:
  case XTOK_S_return:
  case XTOK_S_goto:
  case XTOK_S_decl:
  case XTOK_S_try:
  case XTOK_S_asm:
  case XTOK_S_namespaceDecl:
  case XTOK_S_function:
  case XTOK_S_rangeCase:
  case XTOK_S_computedGoto:
  case XTOK_CN_expr:
  case XTOK_CN_decl:
  case XTOK_Handler:
  case XTOK_E_boolLit:
  case XTOK_E_intLit:
  case XTOK_E_floatLit:
  case XTOK_E_stringLit:
  case XTOK_E_charLit:
  case XTOK_E_this:
  case XTOK_E_variable:
  case XTOK_E_funCall:
  case XTOK_E_constructor:
  case XTOK_E_fieldAcc:
  case XTOK_E_sizeof:
  case XTOK_E_unary:
  case XTOK_E_effect:
  case XTOK_E_binary:
  case XTOK_E_addrOf:
  case XTOK_E_deref:
  case XTOK_E_cast:
  case XTOK_E_cond:
  case XTOK_E_sizeofType:
  case XTOK_E_assign:
  case XTOK_E_new:
  case XTOK_E_delete:
  case XTOK_E_throw:
  case XTOK_E_keywordCast:
  case XTOK_E_typeidExpr:
  case XTOK_E_typeidType:
  case XTOK_E_grouping:
  case XTOK_E_arrow:
  case XTOK_E_statement:
  case XTOK_E_compoundLit:
  case XTOK_E___builtin_constant_p:
  case XTOK_E___builtin_va_arg:
  case XTOK_E_alignofType:
  case XTOK_E_alignofExpr:
  case XTOK_E_gnuCond:
  case XTOK_E_addrOfLabel:
  case XTOK_FullExpression:
  case XTOK_ArgExpression:
  case XTOK_ArgExpressionListOpt:
  case XTOK_IN_expr:
  case XTOK_IN_compound:
  case XTOK_IN_ctor:
  case XTOK_IN_designated:
  case XTOK_TD_func:
  case XTOK_TD_decl:
  case XTOK_TD_tmember:
  case XTOK_TP_type:
  case XTOK_TP_nontype:
  case XTOK_TP_template:
  case XTOK_TA_type:
  case XTOK_TA_nontype:
  case XTOK_TA_templateUsed:
  case XTOK_ND_alias:
  case XTOK_ND_usingDecl:
  case XTOK_ND_usingDir:
  case XTOK_FullExpressionAnnot:
  case XTOK_TS_typeof_expr:
  case XTOK_TS_typeof_type:
  case XTOK_FieldDesignator:
  case XTOK_SubscriptDesignator:
  case XTOK_AttributeSpecifierList:
  case XTOK_AttributeSpecifier:
  case XTOK_AT_empty:
  case XTOK_AT_word:
  case XTOK_AT_func:
  case XTOK_List_TF_namespaceDefn_forms:
  case XTOK_List_TranslationUnit_topForms:
  case XTOK_List_Function_inits:
  case XTOK_List_Function_handlers:
  case XTOK_List_MemberInit_args:
  case XTOK_List_MemberList_list:
  case XTOK_List_Declaration_decllist:
  case XTOK_List_TS_classSpec_bases:
  case XTOK_List_TS_enumSpec_elts:
  case XTOK_List_D_func_params:
  case XTOK_List_D_func_kAndR_params:
  case XTOK_List_S_try_handlers:
  case XTOK_List_ExceptionSpec_types:
  case XTOK_List_S_compound_stmts:
  case XTOK_List_E_funCall_args:
  case XTOK_List_E_constructor_args:
  case XTOK_List_E_new_placementArgs:
  case XTOK_List_ArgExpressionListOpt_list:
  case XTOK_List_IN_compound_inits:
  case XTOK_List_IN_ctor_args:
  case XTOK_List_TP_template_parameters:
  case XTOK_List_IN_designated_designator_list:
  case XTOK_List_FullExpressionAnnot_declarations:
  case XTOK_List_AT_func_args:
    xfailure("should never be called"); return true; break;
  }
}
bool XmlAstReader::prependToFakeList(void *&list, void *obj, int listKind) {
  switch(listKind) {
  default: return false; // we did not find a matching tag
  case XTOK_List_Function_inits: {
    prependToFakeList0<MemberInit>(list, obj);
    break;
  }
  case XTOK_List_Function_handlers: {
    prependToFakeList0<Handler>(list, obj);
    break;
  }
  case XTOK_List_MemberInit_args: {
    prependToFakeList0<ArgExpression>(list, obj);
    break;
  }
  case XTOK_List_Declaration_decllist: {
    prependToFakeList0<Declarator>(list, obj);
    break;
  }
  case XTOK_List_TS_classSpec_bases: {
    prependToFakeList0<BaseClassSpec>(list, obj);
    break;
  }
  case XTOK_List_TS_enumSpec_elts: {
    prependToFakeList0<Enumerator>(list, obj);
    break;
  }
  case XTOK_List_D_func_params: {
    prependToFakeList0<ASTTypeId>(list, obj);
    break;
  }
  case XTOK_List_D_func_kAndR_params: {
    prependToFakeList0<PQ_name>(list, obj);
    break;
  }
  case XTOK_List_S_try_handlers: {
    prependToFakeList0<Handler>(list, obj);
    break;
  }
  case XTOK_List_ExceptionSpec_types: {
    prependToFakeList0<ASTTypeId>(list, obj);
    break;
  }
  case XTOK_List_E_funCall_args: {
    prependToFakeList0<ArgExpression>(list, obj);
    break;
  }
  case XTOK_List_E_constructor_args: {
    prependToFakeList0<ArgExpression>(list, obj);
    break;
  }
  case XTOK_List_E_new_placementArgs: {
    prependToFakeList0<ArgExpression>(list, obj);
    break;
  }
  case XTOK_List_ArgExpressionListOpt_list: {
    prependToFakeList0<ArgExpression>(list, obj);
    break;
  }
  case XTOK_List_IN_ctor_args: {
    prependToFakeList0<ArgExpression>(list, obj);
    break;
  }
  case XTOK_List_TP_template_parameters: {
    prependToFakeList0<TemplateParameter>(list, obj);
    break;
  }
  case XTOK_List_IN_designated_designator_list: {
    prependToFakeList0<Designator>(list, obj);
    break;
  }
  case XTOK_List_AT_func_args: {
    prependToFakeList0<ArgExpression>(list, obj);
    break;
  }
  }
  return true;
}
bool XmlAstReader::reverseFakeList(void *&list, int listKind) {
  switch(listKind) {
  default: return false; // we did not find a matching tag
  case XTOK_List_Function_inits: {
    reverseFakeList0<MemberInit>(list);
    break;
  }
  case XTOK_List_Function_handlers: {
    reverseFakeList0<Handler>(list);
    break;
  }
  case XTOK_List_MemberInit_args: {
    reverseFakeList0<ArgExpression>(list);
    break;
  }
  case XTOK_List_Declaration_decllist: {
    reverseFakeList0<Declarator>(list);
    break;
  }
  case XTOK_List_TS_classSpec_bases: {
    reverseFakeList0<BaseClassSpec>(list);
    break;
  }
  case XTOK_List_TS_enumSpec_elts: {
    reverseFakeList0<Enumerator>(list);
    break;
  }
  case XTOK_List_D_func_params: {
    reverseFakeList0<ASTTypeId>(list);
    break;
  }
  case XTOK_List_D_func_kAndR_params: {
    reverseFakeList0<PQ_name>(list);
    break;
  }
  case XTOK_List_S_try_handlers: {
    reverseFakeList0<Handler>(list);
    break;
  }
  case XTOK_List_ExceptionSpec_types: {
    reverseFakeList0<ASTTypeId>(list);
    break;
  }
  case XTOK_List_E_funCall_args: {
    reverseFakeList0<ArgExpression>(list);
    break;
  }
  case XTOK_List_E_constructor_args: {
    reverseFakeList0<ArgExpression>(list);
    break;
  }
  case XTOK_List_E_new_placementArgs: {
    reverseFakeList0<ArgExpression>(list);
    break;
  }
  case XTOK_List_ArgExpressionListOpt_list: {
    reverseFakeList0<ArgExpression>(list);
    break;
  }
  case XTOK_List_IN_ctor_args: {
    reverseFakeList0<ArgExpression>(list);
    break;
  }
  case XTOK_List_TP_template_parameters: {
    reverseFakeList0<TemplateParameter>(list);
    break;
  }
  case XTOK_List_IN_designated_designator_list: {
    reverseFakeList0<Designator>(list);
    break;
  }
  case XTOK_List_AT_func_args: {
    reverseFakeList0<ArgExpression>(list);
    break;
  }
  }
  return true;
}
