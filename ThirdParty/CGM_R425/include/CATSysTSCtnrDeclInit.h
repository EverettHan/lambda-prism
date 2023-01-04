// CATSysTSCtnrDeclInit.h


// if CtnrClass is nested in NestClass then define:
// CATSYSTS_CTNR      as CtnrClass
// CATSYSTS_CTNR_FULL as NestClass::CtnrClass

#undef CATSYSTS_CTNR
#undef CATSYSTS_CTNR_FULL


// if ElementClass is nested in NestClass then define:
// CATSYSTS_EL_T      as ElementClass
// CATSYSTS_EL_T_FULL as NestClass::ElementClass
#undef CATSYSTS_EL_T
#undef CATSYSTS_EL_T_FULL

#undef CATSYSTS_EL_T_DECL_IN_CTNR

#undef CATSYSTS_T_HAS_COMPARE_OP
#undef CATSYSTS_T_HAS_LESS_OP
#undef CATSYSTS_T_HAS_CUSTOM_COMP_METH
#undef CATSYSTS_T_IS_PTR
#undef CATSYSTS_T_IS_BUILT_IN_TYPE

// to create n list-constructors with 1..n elements as arguments, then define:
// CATSYSTS_LIST_WITH_N_CONSTRUCTORS to n (0<n<10)
#undef CATSYSTS_LIST_WITH_N_CONSTRUCTORS

// if KeyClass is nested in NestClass then define:
// CATSYSTS_KEY      as KeyClass
// CATSYSTS_KEY_FULL as NestClass::KeyClass

// if KeyClass is nested in NestClass and CtnrClass is nested in the *same NestClass* then define:
// CATSYSTS_CTNR               as CtnrClass
// CATSYSTS_CTNR_FULL          as NestClass::CtnrClass
// CATSYSTS_KEY                as KeyClass
// CATSYSTS_KEY_FULL           as NestClass::KeyClass
// CATSYSTS_KEY_DECL_IN_CTNR   as KeyClass

#undef CATSYSTS_KEY
#undef CATSYSTS_KEY_FULL
#undef CATSYSTS_KEY_DECL_IN_CTNR

#undef CATSYSTS_KEY_HAS_HASH_FUNC
#undef CATSYSTS_KEY_HAS_GET_BIN_DUMP
#undef CATSYSTS_KEY_IS_BUILT_IN_TYPE


// VAL nested classes declaration is the same as KEY

#undef CATSYSTS_VAL
#undef CATSYSTS_VAL_FULL
#undef CATSYSTS_VAL_DECL_IN_CTNR

#undef CATSYSTS_VAL_HAS_COMPARE_OP
#undef CATSYSTS_VAL_IS_PTR
#undef CATSYSTS_VAL_IS_BUILT_IN_TYPE

// To declare the list fully thread safe and not only by occurence. 
// Only implemented for ArrayList.
#undef CATSYSTS_FULL_TS

// basic ctnr declaration (you can ignore it)
#undef CATSYSTS_NOT_BASIC_CNTR_DECL





