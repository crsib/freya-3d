    case XTOK_TranslationUnit:
      return new TranslationUnit((ASTList <TopForm >*)0);
      break;
    case XTOK_TF_decl:
      return new TF_decl((SourceLoc)0, (Declaration*)0);
      break;
    case XTOK_TF_func:
      return new TF_func((SourceLoc)0, (Function*)0);
      break;
    case XTOK_TF_template:
      return new TF_template((SourceLoc)0, (TemplateDeclaration*)0);
      break;
    case XTOK_TF_explicitInst:
      return new TF_explicitInst((SourceLoc)0, (DeclFlags)0, (Declaration*)0);
      break;
    case XTOK_TF_linkage:
      return new TF_linkage((SourceLoc)0, (StringRef)0, (TranslationUnit*)0);
      break;
    case XTOK_TF_one_linkage:
      return new TF_one_linkage((SourceLoc)0, (StringRef)0, (TopForm*)0);
      break;
    case XTOK_TF_asm:
      return new TF_asm((SourceLoc)0, (E_stringLit*)0);
      break;
    case XTOK_TF_namespaceDefn:
      return new TF_namespaceDefn((SourceLoc)0, (StringRef)0, (ASTList <TopForm >*)0);
      break;
    case XTOK_TF_namespaceDecl:
      return new TF_namespaceDecl((SourceLoc)0, (NamespaceDecl*)0);
      break;
    case XTOK_Function:
      return new Function((DeclFlags)0, (TypeSpecifier*)0, (Declarator*)0, (FakeList <MemberInit >*)0, (S_compound*)0, (FakeList <Handler >*)0);
      break;
    case XTOK_MemberInit:
      return new MemberInit((SourceLoc)0, (SourceLoc)0, (PQName*)0, (FakeList <ArgExpression >*)0);
      break;
    case XTOK_Declaration:
      return new Declaration((DeclFlags)0, (TypeSpecifier*)0, (FakeList <Declarator >*)0);
      break;
    case XTOK_ASTTypeId:
      return new ASTTypeId((TypeSpecifier*)0, (Declarator*)0);
      break;
    case XTOK_PQ_qualifier:
      return new PQ_qualifier((SourceLoc)0, (StringRef)0, (TemplateArgument*)0, (PQName*)0);
      break;
    case XTOK_PQ_name:
      return new PQ_name((SourceLoc)0, (StringRef)0);
      break;
    case XTOK_PQ_operator:
      return new PQ_operator((SourceLoc)0, (OperatorName*)0, (StringRef)0);
      break;
    case XTOK_PQ_template:
      return new PQ_template((SourceLoc)0, (StringRef)0, (TemplateArgument*)0);
      break;
    case XTOK_PQ_variable:
      return new PQ_variable((SourceLoc)0, (Variable *)0);
      break;
    case XTOK_TS_name:
      return new TS_name((SourceLoc)0, (PQName*)0, (bool)0);
      break;
    case XTOK_TS_simple:
      return new TS_simple((SourceLoc)0, (SimpleTypeId)0);
      break;
    case XTOK_TS_elaborated:
      return new TS_elaborated((SourceLoc)0, (TypeIntr)0, (PQName*)0);
      break;
    case XTOK_TS_classSpec:
      return new TS_classSpec((SourceLoc)0, (TypeIntr)0, (PQName*)0, (FakeList <BaseClassSpec >*)0, (MemberList*)0);
      break;
    case XTOK_TS_enumSpec:
      return new TS_enumSpec((SourceLoc)0, (StringRef)0, (FakeList <Enumerator >*)0);
      break;
    case XTOK_TS_type:
      return new TS_type((SourceLoc)0, (Type *)0);
      break;
    case XTOK_TS_typeof:
      return new TS_typeof((SourceLoc)0, (ASTTypeof*)0);
      break;
    case XTOK_BaseClassSpec:
      return new BaseClassSpec((bool)0, (AccessKeyword)0, (PQName*)0);
      break;
    case XTOK_Enumerator:
      return new Enumerator((SourceLoc)0, (StringRef)0, (Expression*)0);
      break;
    case XTOK_MemberList:
      return new MemberList((ASTList <Member >*)0);
      break;
    case XTOK_MR_decl:
      return new MR_decl((SourceLoc)0, (SourceLoc)0, (Declaration*)0);
      break;
    case XTOK_MR_func:
      return new MR_func((SourceLoc)0, (SourceLoc)0, (Function*)0);
      break;
    case XTOK_MR_access:
      return new MR_access((SourceLoc)0, (SourceLoc)0, (AccessKeyword)0);
      break;
    case XTOK_MR_usingDecl:
      return new MR_usingDecl((SourceLoc)0, (SourceLoc)0, (ND_usingDecl*)0);
      break;
    case XTOK_MR_template:
      return new MR_template((SourceLoc)0, (SourceLoc)0, (TemplateDeclaration*)0);
      break;
    case XTOK_Declarator:
      return new Declarator((IDeclarator*)0, (Initializer*)0);
      break;
    case XTOK_D_name:
      return new D_name((SourceLoc)0, (PQName*)0);
      break;
    case XTOK_D_pointer:
      return new D_pointer((SourceLoc)0, (CVFlags)0, (IDeclarator*)0);
      break;
    case XTOK_D_reference:
      return new D_reference((SourceLoc)0, (IDeclarator*)0);
      break;
    case XTOK_D_func:
      return new D_func((SourceLoc)0, (IDeclarator*)0, (FakeList <ASTTypeId >*)0, (CVFlags)0, (ExceptionSpec*)0, NULL);
      break;
    case XTOK_D_array:
      return new D_array((SourceLoc)0, (IDeclarator*)0, (Expression*)0);
      break;
    case XTOK_D_bitfield:
      return new D_bitfield((SourceLoc)0, (PQName*)0, (Expression*)0);
      break;
    case XTOK_D_ptrToMember:
      return new D_ptrToMember((SourceLoc)0, (PQName*)0, (CVFlags)0, (IDeclarator*)0);
      break;
    case XTOK_D_grouping:
      return new D_grouping((SourceLoc)0, (IDeclarator*)0);
      break;
    case XTOK_ExceptionSpec:
      return new ExceptionSpec((FakeList <ASTTypeId >*)0);
      break;
    case XTOK_ON_newDel:
      return new ON_newDel((bool)0, (bool)0);
      break;
    case XTOK_ON_operator:
      return new ON_operator((OverloadableOp)0);
      break;
    case XTOK_ON_conversion:
      return new ON_conversion((ASTTypeId*)0);
      break;
    case XTOK_S_skip:
      return new S_skip((SourceLoc)0, (SourceLoc)0);
      break;
    case XTOK_S_label:
      return new S_label((SourceLoc)0, (SourceLoc)0, (StringRef)0, (Statement*)0);
      break;
    case XTOK_S_case:
      return new S_case((SourceLoc)0, (SourceLoc)0, (Expression*)0, (Statement*)0);
      break;
    case XTOK_S_default:
      return new S_default((SourceLoc)0, (SourceLoc)0, (Statement*)0);
      break;
    case XTOK_S_expr:
      return new S_expr((SourceLoc)0, (SourceLoc)0, (FullExpression*)0);
      break;
    case XTOK_S_compound:
      return new S_compound((SourceLoc)0, (SourceLoc)0, (ASTList <Statement >*)0);
      break;
    case XTOK_S_if:
      return new S_if((SourceLoc)0, (SourceLoc)0, (Condition*)0, (Statement*)0, (Statement*)0);
      break;
    case XTOK_S_switch:
      return new S_switch((SourceLoc)0, (SourceLoc)0, (Condition*)0, (Statement*)0);
      break;
    case XTOK_S_while:
      return new S_while((SourceLoc)0, (SourceLoc)0, (Condition*)0, (Statement*)0);
      break;
    case XTOK_S_doWhile:
      return new S_doWhile((SourceLoc)0, (SourceLoc)0, (Statement*)0, (FullExpression*)0);
      break;
    case XTOK_S_for:
      return new S_for((SourceLoc)0, (SourceLoc)0, (Statement*)0, (Condition*)0, (FullExpression*)0, (Statement*)0);
      break;
    case XTOK_S_break:
      return new S_break((SourceLoc)0, (SourceLoc)0);
      break;
    case XTOK_S_continue:
      return new S_continue((SourceLoc)0, (SourceLoc)0);
      break;
    case XTOK_S_return:
      return new S_return((SourceLoc)0, (SourceLoc)0, (FullExpression*)0);
      break;
    case XTOK_S_goto:
      return new S_goto((SourceLoc)0, (SourceLoc)0, (StringRef)0);
      break;
    case XTOK_S_decl:
      return new S_decl((SourceLoc)0, (SourceLoc)0, (Declaration*)0);
      break;
    case XTOK_S_try:
      return new S_try((SourceLoc)0, (SourceLoc)0, (Statement*)0, (FakeList <Handler >*)0);
      break;
    case XTOK_S_asm:
      return new S_asm((SourceLoc)0, (SourceLoc)0, (E_stringLit*)0);
      break;
    case XTOK_S_namespaceDecl:
      return new S_namespaceDecl((SourceLoc)0, (SourceLoc)0, (NamespaceDecl*)0);
      break;
    case XTOK_S_function:
      return new S_function((SourceLoc)0, (SourceLoc)0, (Function*)0);
      break;
    case XTOK_S_rangeCase:
      return new S_rangeCase((SourceLoc)0, (SourceLoc)0, (Expression*)0, (Expression*)0, (Statement*)0);
      break;
    case XTOK_S_computedGoto:
      return new S_computedGoto((SourceLoc)0, (SourceLoc)0, (Expression*)0);
      break;
    case XTOK_CN_expr:
      return new CN_expr((FullExpression*)0);
      break;
    case XTOK_CN_decl:
      return new CN_decl((ASTTypeId*)0);
      break;
    case XTOK_Handler:
      return new Handler((ASTTypeId*)0, (Statement*)0);
      break;
    case XTOK_E_boolLit:
      return new E_boolLit((SourceLoc)0, (SourceLoc)0, (bool)0);
      break;
    case XTOK_E_intLit:
      return new E_intLit((SourceLoc)0, (SourceLoc)0, (StringRef)0);
      break;
    case XTOK_E_floatLit:
      return new E_floatLit((SourceLoc)0, (SourceLoc)0, (StringRef)0);
      break;
    case XTOK_E_stringLit:
      return new E_stringLit((SourceLoc)0, (SourceLoc)0, (StringRef)0, NULL, NULL);
      break;
    case XTOK_E_charLit:
      return new E_charLit((SourceLoc)0, (SourceLoc)0, (StringRef)0);
      break;
    case XTOK_E_this:
      return new E_this((SourceLoc)0, (SourceLoc)0);
      break;
    case XTOK_E_variable:
      return new E_variable((SourceLoc)0, (SourceLoc)0, (PQName*)0);
      break;
    case XTOK_E_funCall:
      return new E_funCall((SourceLoc)0, (SourceLoc)0, (Expression*)0, (FakeList <ArgExpression >*)0);
      break;
    case XTOK_E_constructor:
      return new E_constructor((SourceLoc)0, (SourceLoc)0, (TypeSpecifier*)0, (FakeList <ArgExpression >*)0);
      break;
    case XTOK_E_fieldAcc:
      return new E_fieldAcc((SourceLoc)0, (SourceLoc)0, (Expression*)0, (PQName*)0);
      break;
    case XTOK_E_sizeof:
      return new E_sizeof((SourceLoc)0, (SourceLoc)0, (Expression*)0);
      break;
    case XTOK_E_unary:
      return new E_unary((SourceLoc)0, (SourceLoc)0, (UnaryOp)0, (Expression*)0);
      break;
    case XTOK_E_effect:
      return new E_effect((SourceLoc)0, (SourceLoc)0, (EffectOp)0, (Expression*)0);
      break;
    case XTOK_E_binary:
      return new E_binary((SourceLoc)0, (SourceLoc)0, (Expression*)0, (BinaryOp)0, (Expression*)0);
      break;
    case XTOK_E_addrOf:
      return new E_addrOf((SourceLoc)0, (SourceLoc)0, (Expression*)0);
      break;
    case XTOK_E_deref:
      return new E_deref((SourceLoc)0, (SourceLoc)0, (Expression*)0);
      break;
    case XTOK_E_cast:
      return new E_cast((SourceLoc)0, (SourceLoc)0, (ASTTypeId*)0, (Expression*)0);
      break;
    case XTOK_E_cond:
      return new E_cond((SourceLoc)0, (SourceLoc)0, (Expression*)0, (Expression*)0, (Expression*)0);
      break;
    case XTOK_E_sizeofType:
      return new E_sizeofType((SourceLoc)0, (SourceLoc)0, (ASTTypeId*)0);
      break;
    case XTOK_E_assign:
      return new E_assign((SourceLoc)0, (SourceLoc)0, (Expression*)0, (BinaryOp)0, (Expression*)0);
      break;
    case XTOK_E_new:
      return new E_new((SourceLoc)0, (SourceLoc)0, (bool)0, (FakeList <ArgExpression >*)0, (ASTTypeId*)0, (ArgExpressionListOpt*)0);
      break;
    case XTOK_E_delete:
      return new E_delete((SourceLoc)0, (SourceLoc)0, (bool)0, (bool)0, (Expression*)0);
      break;
    case XTOK_E_throw:
      return new E_throw((SourceLoc)0, (SourceLoc)0, (Expression*)0);
      break;
    case XTOK_E_keywordCast:
      return new E_keywordCast((SourceLoc)0, (SourceLoc)0, (CastKeyword)0, (ASTTypeId*)0, (Expression*)0);
      break;
    case XTOK_E_typeidExpr:
      return new E_typeidExpr((SourceLoc)0, (SourceLoc)0, (Expression*)0);
      break;
    case XTOK_E_typeidType:
      return new E_typeidType((SourceLoc)0, (SourceLoc)0, (ASTTypeId*)0);
      break;
    case XTOK_E_grouping:
      return new E_grouping((SourceLoc)0, (SourceLoc)0, (Expression*)0);
      break;
    case XTOK_E_arrow:
      return new E_arrow((SourceLoc)0, (SourceLoc)0, (Expression*)0, (PQName*)0);
      break;
    case XTOK_E_statement:
      return new E_statement((SourceLoc)0, (SourceLoc)0, (S_compound*)0);
      break;
    case XTOK_E_compoundLit:
      return new E_compoundLit((SourceLoc)0, (SourceLoc)0, (ASTTypeId*)0, (IN_compound*)0);
      break;
    case XTOK_E___builtin_constant_p:
      return new E___builtin_constant_p((SourceLoc)0, (SourceLoc)0, (Expression*)0);
      break;
    case XTOK_E___builtin_va_arg:
      return new E___builtin_va_arg((SourceLoc)0, (SourceLoc)0, (Expression*)0, (ASTTypeId*)0);
      break;
    case XTOK_E_alignofType:
      return new E_alignofType((SourceLoc)0, (SourceLoc)0, (ASTTypeId*)0);
      break;
    case XTOK_E_alignofExpr:
      return new E_alignofExpr((SourceLoc)0, (SourceLoc)0, (Expression*)0);
      break;
    case XTOK_E_gnuCond:
      return new E_gnuCond((SourceLoc)0, (SourceLoc)0, (Expression*)0, (Expression*)0);
      break;
    case XTOK_E_addrOfLabel:
      return new E_addrOfLabel((SourceLoc)0, (SourceLoc)0, (StringRef)0);
      break;
    case XTOK_FullExpression:
      return new FullExpression((Expression*)0);
      break;
    case XTOK_ArgExpression:
      return new ArgExpression((Expression*)0);
      break;
    case XTOK_ArgExpressionListOpt:
      return new ArgExpressionListOpt((FakeList <ArgExpression >*)0);
      break;
    case XTOK_IN_expr:
      return new IN_expr((SourceLoc)0, (Expression*)0);
      break;
    case XTOK_IN_compound:
      return new IN_compound((SourceLoc)0, (ASTList <Initializer >*)0);
      break;
    case XTOK_IN_ctor:
      return new IN_ctor((SourceLoc)0, (FakeList <ArgExpression >*)0);
      break;
    case XTOK_IN_designated:
      return new IN_designated((SourceLoc)0, (FakeList <Designator >*)0, (Initializer*)0);
      break;
    case XTOK_TD_func:
      return new TD_func((TemplateParameter*)0, (Function*)0);
      break;
    case XTOK_TD_decl:
      return new TD_decl((TemplateParameter*)0, (Declaration*)0);
      break;
    case XTOK_TD_tmember:
      return new TD_tmember((TemplateParameter*)0, (TemplateDeclaration*)0);
      break;
    case XTOK_TP_type:
      return new TP_type((SourceLoc)0, (StringRef)0, (ASTTypeId*)0, (TemplateParameter*)0);
      break;
    case XTOK_TP_nontype:
      return new TP_nontype((SourceLoc)0, (ASTTypeId*)0, (TemplateParameter*)0);
      break;
    case XTOK_TP_template:
      return new TP_template((SourceLoc)0, (FakeList <TemplateParameter >*)0, (StringRef)0, (PQName*)0, (TemplateParameter*)0);
      break;
    case XTOK_TA_type:
      return new TA_type((ASTTypeId*)0, (TemplateArgument*)0);
      break;
    case XTOK_TA_nontype:
      return new TA_nontype((Expression*)0, (TemplateArgument*)0);
      break;
    case XTOK_TA_templateUsed:
      return new TA_templateUsed((TemplateArgument*)0);
      break;
    case XTOK_ND_alias:
      return new ND_alias((StringRef)0, (PQName*)0);
      break;
    case XTOK_ND_usingDecl:
      return new ND_usingDecl((PQName*)0);
      break;
    case XTOK_ND_usingDir:
      return new ND_usingDir((PQName*)0);
      break;
    case XTOK_FullExpressionAnnot:
      return new FullExpressionAnnot((ASTList <Declaration >*)0);
      break;
    case XTOK_TS_typeof_expr:
      return new TS_typeof_expr((FullExpression*)0);
      break;
    case XTOK_TS_typeof_type:
      return new TS_typeof_type((ASTTypeId*)0);
      break;
    case XTOK_FieldDesignator:
      return new FieldDesignator((SourceLoc)0, (StringRef)0);
      break;
    case XTOK_SubscriptDesignator:
      return new SubscriptDesignator((SourceLoc)0, (Expression*)0, (Expression*)0);
      break;
    case XTOK_AttributeSpecifierList:
      return new AttributeSpecifierList((AttributeSpecifier*)0, (AttributeSpecifierList*)0);
      break;
    case XTOK_AttributeSpecifier:
      return new AttributeSpecifier((Attribute*)0, (AttributeSpecifier*)0);
      break;
    case XTOK_AT_empty:
      return new AT_empty((SourceLoc)0);
      break;
    case XTOK_AT_word:
      return new AT_word((SourceLoc)0, (StringRef)0);
      break;
    case XTOK_AT_func:
      return new AT_func((SourceLoc)0, (StringRef)0, (FakeList <ArgExpression >*)0);
      break;
    case XTOK_List_TF_namespaceDefn_forms:
      return new ASTList<TopForm>();
      break;
    case XTOK_List_TranslationUnit_topForms:
      return new ASTList<TopForm>();
      break;
    case XTOK_List_Function_inits:
      return new FakeList<MemberInit> *;
      break;
    case XTOK_List_Function_handlers:
      return new FakeList<Handler> *;
      break;
    case XTOK_List_MemberInit_args:
      return new FakeList<ArgExpression> *;
      break;
    case XTOK_List_MemberList_list:
      return new ASTList<Member>();
      break;
    case XTOK_List_Declaration_decllist:
      return new FakeList<Declarator> *;
      break;
    case XTOK_List_TS_classSpec_bases:
      return new FakeList<BaseClassSpec> *;
      break;
    case XTOK_List_TS_enumSpec_elts:
      return new FakeList<Enumerator> *;
      break;
    case XTOK_List_D_func_params:
      return new FakeList<ASTTypeId> *;
      break;
    case XTOK_List_D_func_kAndR_params:
      return new FakeList<PQ_name> *;
      break;
    case XTOK_List_S_try_handlers:
      return new FakeList<Handler> *;
      break;
    case XTOK_List_ExceptionSpec_types:
      return new FakeList<ASTTypeId> *;
      break;
    case XTOK_List_S_compound_stmts:
      return new ASTList<Statement>();
      break;
    case XTOK_List_E_funCall_args:
      return new FakeList<ArgExpression> *;
      break;
    case XTOK_List_E_constructor_args:
      return new FakeList<ArgExpression> *;
      break;
    case XTOK_List_E_new_placementArgs:
      return new FakeList<ArgExpression> *;
      break;
    case XTOK_List_ArgExpressionListOpt_list:
      return new FakeList<ArgExpression> *;
      break;
    case XTOK_List_IN_compound_inits:
      return new ASTList<Initializer>();
      break;
    case XTOK_List_IN_ctor_args:
      return new FakeList<ArgExpression> *;
      break;
    case XTOK_List_TP_template_parameters:
      return new FakeList<TemplateParameter> *;
      break;
    case XTOK_List_IN_designated_designator_list:
      return new FakeList<Designator> *;
      break;
    case XTOK_List_FullExpressionAnnot_declarations:
      return new ASTList<Declaration>();
      break;
    case XTOK_List_AT_func_args:
      return new FakeList<ArgExpression> *;
      break;
