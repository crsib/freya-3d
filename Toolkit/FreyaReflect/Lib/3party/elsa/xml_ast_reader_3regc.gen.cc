      case XTOK_TranslationUnit:
        registerAttr_TranslationUnit((TranslationUnit*)target, attr, yytext0);
      break;
      case XTOK_TF_decl:
        registerAttr_TF_decl((TF_decl*)target, attr, yytext0);
      break;
      case XTOK_TF_func:
        registerAttr_TF_func((TF_func*)target, attr, yytext0);
      break;
      case XTOK_TF_template:
        registerAttr_TF_template((TF_template*)target, attr, yytext0);
      break;
      case XTOK_TF_explicitInst:
        registerAttr_TF_explicitInst((TF_explicitInst*)target, attr, yytext0);
      break;
      case XTOK_TF_linkage:
        registerAttr_TF_linkage((TF_linkage*)target, attr, yytext0);
      break;
      case XTOK_TF_one_linkage:
        registerAttr_TF_one_linkage((TF_one_linkage*)target, attr, yytext0);
      break;
      case XTOK_TF_asm:
        registerAttr_TF_asm((TF_asm*)target, attr, yytext0);
      break;
      case XTOK_TF_namespaceDefn:
        registerAttr_TF_namespaceDefn((TF_namespaceDefn*)target, attr, yytext0);
      break;
      case XTOK_TF_namespaceDecl:
        registerAttr_TF_namespaceDecl((TF_namespaceDecl*)target, attr, yytext0);
      break;
      case XTOK_Function:
        registerAttr_Function((Function*)target, attr, yytext0);
      break;
      case XTOK_MemberInit:
        registerAttr_MemberInit((MemberInit*)target, attr, yytext0);
      break;
      case XTOK_Declaration:
        registerAttr_Declaration((Declaration*)target, attr, yytext0);
      break;
      case XTOK_ASTTypeId:
        registerAttr_ASTTypeId((ASTTypeId*)target, attr, yytext0);
      break;
      case XTOK_PQ_qualifier:
        registerAttr_PQ_qualifier((PQ_qualifier*)target, attr, yytext0);
      break;
      case XTOK_PQ_name:
        registerAttr_PQ_name((PQ_name*)target, attr, yytext0);
      break;
      case XTOK_PQ_operator:
        registerAttr_PQ_operator((PQ_operator*)target, attr, yytext0);
      break;
      case XTOK_PQ_template:
        registerAttr_PQ_template((PQ_template*)target, attr, yytext0);
      break;
      case XTOK_PQ_variable:
        registerAttr_PQ_variable((PQ_variable*)target, attr, yytext0);
      break;
      case XTOK_TS_name:
        registerAttr_TS_name((TS_name*)target, attr, yytext0);
      break;
      case XTOK_TS_simple:
        registerAttr_TS_simple((TS_simple*)target, attr, yytext0);
      break;
      case XTOK_TS_elaborated:
        registerAttr_TS_elaborated((TS_elaborated*)target, attr, yytext0);
      break;
      case XTOK_TS_classSpec:
        registerAttr_TS_classSpec((TS_classSpec*)target, attr, yytext0);
      break;
      case XTOK_TS_enumSpec:
        registerAttr_TS_enumSpec((TS_enumSpec*)target, attr, yytext0);
      break;
      case XTOK_TS_type:
        registerAttr_TS_type((TS_type*)target, attr, yytext0);
      break;
      case XTOK_TS_typeof:
        registerAttr_TS_typeof((TS_typeof*)target, attr, yytext0);
      break;
      case XTOK_BaseClassSpec:
        registerAttr_BaseClassSpec((BaseClassSpec*)target, attr, yytext0);
      break;
      case XTOK_Enumerator:
        registerAttr_Enumerator((Enumerator*)target, attr, yytext0);
      break;
      case XTOK_MemberList:
        registerAttr_MemberList((MemberList*)target, attr, yytext0);
      break;
      case XTOK_MR_decl:
        registerAttr_MR_decl((MR_decl*)target, attr, yytext0);
      break;
      case XTOK_MR_func:
        registerAttr_MR_func((MR_func*)target, attr, yytext0);
      break;
      case XTOK_MR_access:
        registerAttr_MR_access((MR_access*)target, attr, yytext0);
      break;
      case XTOK_MR_usingDecl:
        registerAttr_MR_usingDecl((MR_usingDecl*)target, attr, yytext0);
      break;
      case XTOK_MR_template:
        registerAttr_MR_template((MR_template*)target, attr, yytext0);
      break;
      case XTOK_Declarator:
        registerAttr_Declarator((Declarator*)target, attr, yytext0);
      break;
      case XTOK_D_name:
        registerAttr_D_name((D_name*)target, attr, yytext0);
      break;
      case XTOK_D_pointer:
        registerAttr_D_pointer((D_pointer*)target, attr, yytext0);
      break;
      case XTOK_D_reference:
        registerAttr_D_reference((D_reference*)target, attr, yytext0);
      break;
      case XTOK_D_func:
        registerAttr_D_func((D_func*)target, attr, yytext0);
      break;
      case XTOK_D_array:
        registerAttr_D_array((D_array*)target, attr, yytext0);
      break;
      case XTOK_D_bitfield:
        registerAttr_D_bitfield((D_bitfield*)target, attr, yytext0);
      break;
      case XTOK_D_ptrToMember:
        registerAttr_D_ptrToMember((D_ptrToMember*)target, attr, yytext0);
      break;
      case XTOK_D_grouping:
        registerAttr_D_grouping((D_grouping*)target, attr, yytext0);
      break;
      case XTOK_ExceptionSpec:
        registerAttr_ExceptionSpec((ExceptionSpec*)target, attr, yytext0);
      break;
      case XTOK_ON_newDel:
        registerAttr_ON_newDel((ON_newDel*)target, attr, yytext0);
      break;
      case XTOK_ON_operator:
        registerAttr_ON_operator((ON_operator*)target, attr, yytext0);
      break;
      case XTOK_ON_conversion:
        registerAttr_ON_conversion((ON_conversion*)target, attr, yytext0);
      break;
      case XTOK_S_skip:
        registerAttr_S_skip((S_skip*)target, attr, yytext0);
      break;
      case XTOK_S_label:
        registerAttr_S_label((S_label*)target, attr, yytext0);
      break;
      case XTOK_S_case:
        registerAttr_S_case((S_case*)target, attr, yytext0);
      break;
      case XTOK_S_default:
        registerAttr_S_default((S_default*)target, attr, yytext0);
      break;
      case XTOK_S_expr:
        registerAttr_S_expr((S_expr*)target, attr, yytext0);
      break;
      case XTOK_S_compound:
        registerAttr_S_compound((S_compound*)target, attr, yytext0);
      break;
      case XTOK_S_if:
        registerAttr_S_if((S_if*)target, attr, yytext0);
      break;
      case XTOK_S_switch:
        registerAttr_S_switch((S_switch*)target, attr, yytext0);
      break;
      case XTOK_S_while:
        registerAttr_S_while((S_while*)target, attr, yytext0);
      break;
      case XTOK_S_doWhile:
        registerAttr_S_doWhile((S_doWhile*)target, attr, yytext0);
      break;
      case XTOK_S_for:
        registerAttr_S_for((S_for*)target, attr, yytext0);
      break;
      case XTOK_S_break:
        registerAttr_S_break((S_break*)target, attr, yytext0);
      break;
      case XTOK_S_continue:
        registerAttr_S_continue((S_continue*)target, attr, yytext0);
      break;
      case XTOK_S_return:
        registerAttr_S_return((S_return*)target, attr, yytext0);
      break;
      case XTOK_S_goto:
        registerAttr_S_goto((S_goto*)target, attr, yytext0);
      break;
      case XTOK_S_decl:
        registerAttr_S_decl((S_decl*)target, attr, yytext0);
      break;
      case XTOK_S_try:
        registerAttr_S_try((S_try*)target, attr, yytext0);
      break;
      case XTOK_S_asm:
        registerAttr_S_asm((S_asm*)target, attr, yytext0);
      break;
      case XTOK_S_namespaceDecl:
        registerAttr_S_namespaceDecl((S_namespaceDecl*)target, attr, yytext0);
      break;
      case XTOK_S_function:
        registerAttr_S_function((S_function*)target, attr, yytext0);
      break;
      case XTOK_S_rangeCase:
        registerAttr_S_rangeCase((S_rangeCase*)target, attr, yytext0);
      break;
      case XTOK_S_computedGoto:
        registerAttr_S_computedGoto((S_computedGoto*)target, attr, yytext0);
      break;
      case XTOK_CN_expr:
        registerAttr_CN_expr((CN_expr*)target, attr, yytext0);
      break;
      case XTOK_CN_decl:
        registerAttr_CN_decl((CN_decl*)target, attr, yytext0);
      break;
      case XTOK_Handler:
        registerAttr_Handler((Handler*)target, attr, yytext0);
      break;
      case XTOK_E_boolLit:
        registerAttr_E_boolLit((E_boolLit*)target, attr, yytext0);
      break;
      case XTOK_E_intLit:
        registerAttr_E_intLit((E_intLit*)target, attr, yytext0);
      break;
      case XTOK_E_floatLit:
        registerAttr_E_floatLit((E_floatLit*)target, attr, yytext0);
      break;
      case XTOK_E_stringLit:
        registerAttr_E_stringLit((E_stringLit*)target, attr, yytext0);
      break;
      case XTOK_E_charLit:
        registerAttr_E_charLit((E_charLit*)target, attr, yytext0);
      break;
      case XTOK_E_this:
        registerAttr_E_this((E_this*)target, attr, yytext0);
      break;
      case XTOK_E_variable:
        registerAttr_E_variable((E_variable*)target, attr, yytext0);
      break;
      case XTOK_E_funCall:
        registerAttr_E_funCall((E_funCall*)target, attr, yytext0);
      break;
      case XTOK_E_constructor:
        registerAttr_E_constructor((E_constructor*)target, attr, yytext0);
      break;
      case XTOK_E_fieldAcc:
        registerAttr_E_fieldAcc((E_fieldAcc*)target, attr, yytext0);
      break;
      case XTOK_E_sizeof:
        registerAttr_E_sizeof((E_sizeof*)target, attr, yytext0);
      break;
      case XTOK_E_unary:
        registerAttr_E_unary((E_unary*)target, attr, yytext0);
      break;
      case XTOK_E_effect:
        registerAttr_E_effect((E_effect*)target, attr, yytext0);
      break;
      case XTOK_E_binary:
        registerAttr_E_binary((E_binary*)target, attr, yytext0);
      break;
      case XTOK_E_addrOf:
        registerAttr_E_addrOf((E_addrOf*)target, attr, yytext0);
      break;
      case XTOK_E_deref:
        registerAttr_E_deref((E_deref*)target, attr, yytext0);
      break;
      case XTOK_E_cast:
        registerAttr_E_cast((E_cast*)target, attr, yytext0);
      break;
      case XTOK_E_cond:
        registerAttr_E_cond((E_cond*)target, attr, yytext0);
      break;
      case XTOK_E_sizeofType:
        registerAttr_E_sizeofType((E_sizeofType*)target, attr, yytext0);
      break;
      case XTOK_E_assign:
        registerAttr_E_assign((E_assign*)target, attr, yytext0);
      break;
      case XTOK_E_new:
        registerAttr_E_new((E_new*)target, attr, yytext0);
      break;
      case XTOK_E_delete:
        registerAttr_E_delete((E_delete*)target, attr, yytext0);
      break;
      case XTOK_E_throw:
        registerAttr_E_throw((E_throw*)target, attr, yytext0);
      break;
      case XTOK_E_keywordCast:
        registerAttr_E_keywordCast((E_keywordCast*)target, attr, yytext0);
      break;
      case XTOK_E_typeidExpr:
        registerAttr_E_typeidExpr((E_typeidExpr*)target, attr, yytext0);
      break;
      case XTOK_E_typeidType:
        registerAttr_E_typeidType((E_typeidType*)target, attr, yytext0);
      break;
      case XTOK_E_grouping:
        registerAttr_E_grouping((E_grouping*)target, attr, yytext0);
      break;
      case XTOK_E_arrow:
        registerAttr_E_arrow((E_arrow*)target, attr, yytext0);
      break;
      case XTOK_E_statement:
        registerAttr_E_statement((E_statement*)target, attr, yytext0);
      break;
      case XTOK_E_compoundLit:
        registerAttr_E_compoundLit((E_compoundLit*)target, attr, yytext0);
      break;
      case XTOK_E___builtin_constant_p:
        registerAttr_E___builtin_constant_p((E___builtin_constant_p*)target, attr, yytext0);
      break;
      case XTOK_E___builtin_va_arg:
        registerAttr_E___builtin_va_arg((E___builtin_va_arg*)target, attr, yytext0);
      break;
      case XTOK_E_alignofType:
        registerAttr_E_alignofType((E_alignofType*)target, attr, yytext0);
      break;
      case XTOK_E_alignofExpr:
        registerAttr_E_alignofExpr((E_alignofExpr*)target, attr, yytext0);
      break;
      case XTOK_E_gnuCond:
        registerAttr_E_gnuCond((E_gnuCond*)target, attr, yytext0);
      break;
      case XTOK_E_addrOfLabel:
        registerAttr_E_addrOfLabel((E_addrOfLabel*)target, attr, yytext0);
      break;
      case XTOK_FullExpression:
        registerAttr_FullExpression((FullExpression*)target, attr, yytext0);
      break;
      case XTOK_ArgExpression:
        registerAttr_ArgExpression((ArgExpression*)target, attr, yytext0);
      break;
      case XTOK_ArgExpressionListOpt:
        registerAttr_ArgExpressionListOpt((ArgExpressionListOpt*)target, attr, yytext0);
      break;
      case XTOK_IN_expr:
        registerAttr_IN_expr((IN_expr*)target, attr, yytext0);
      break;
      case XTOK_IN_compound:
        registerAttr_IN_compound((IN_compound*)target, attr, yytext0);
      break;
      case XTOK_IN_ctor:
        registerAttr_IN_ctor((IN_ctor*)target, attr, yytext0);
      break;
      case XTOK_IN_designated:
        registerAttr_IN_designated((IN_designated*)target, attr, yytext0);
      break;
      case XTOK_TD_func:
        registerAttr_TD_func((TD_func*)target, attr, yytext0);
      break;
      case XTOK_TD_decl:
        registerAttr_TD_decl((TD_decl*)target, attr, yytext0);
      break;
      case XTOK_TD_tmember:
        registerAttr_TD_tmember((TD_tmember*)target, attr, yytext0);
      break;
      case XTOK_TP_type:
        registerAttr_TP_type((TP_type*)target, attr, yytext0);
      break;
      case XTOK_TP_nontype:
        registerAttr_TP_nontype((TP_nontype*)target, attr, yytext0);
      break;
      case XTOK_TP_template:
        registerAttr_TP_template((TP_template*)target, attr, yytext0);
      break;
      case XTOK_TA_type:
        registerAttr_TA_type((TA_type*)target, attr, yytext0);
      break;
      case XTOK_TA_nontype:
        registerAttr_TA_nontype((TA_nontype*)target, attr, yytext0);
      break;
      case XTOK_TA_templateUsed:
        registerAttr_TA_templateUsed((TA_templateUsed*)target, attr, yytext0);
      break;
      case XTOK_ND_alias:
        registerAttr_ND_alias((ND_alias*)target, attr, yytext0);
      break;
      case XTOK_ND_usingDecl:
        registerAttr_ND_usingDecl((ND_usingDecl*)target, attr, yytext0);
      break;
      case XTOK_ND_usingDir:
        registerAttr_ND_usingDir((ND_usingDir*)target, attr, yytext0);
      break;
      case XTOK_FullExpressionAnnot:
        registerAttr_FullExpressionAnnot((FullExpressionAnnot*)target, attr, yytext0);
      break;
      case XTOK_TS_typeof_expr:
        registerAttr_TS_typeof_expr((TS_typeof_expr*)target, attr, yytext0);
      break;
      case XTOK_TS_typeof_type:
        registerAttr_TS_typeof_type((TS_typeof_type*)target, attr, yytext0);
      break;
      case XTOK_FieldDesignator:
        registerAttr_FieldDesignator((FieldDesignator*)target, attr, yytext0);
      break;
      case XTOK_SubscriptDesignator:
        registerAttr_SubscriptDesignator((SubscriptDesignator*)target, attr, yytext0);
      break;
      case XTOK_AttributeSpecifierList:
        registerAttr_AttributeSpecifierList((AttributeSpecifierList*)target, attr, yytext0);
      break;
      case XTOK_AttributeSpecifier:
        registerAttr_AttributeSpecifier((AttributeSpecifier*)target, attr, yytext0);
      break;
      case XTOK_AT_empty:
        registerAttr_AT_empty((AT_empty*)target, attr, yytext0);
      break;
      case XTOK_AT_word:
        registerAttr_AT_word((AT_word*)target, attr, yytext0);
      break;
      case XTOK_AT_func:
        registerAttr_AT_func((AT_func*)target, attr, yytext0);
      break;
