// CATSysTSListInterface_T_HAS_CUSTOM_COMP_METH.h

/* 
 * Optional function activated when CATSYSTS_T_HAS_CUSTOM_COMP_METH == 1
 *
 * Sort elements in place using a custom provided compare method
 */
void Sort(int (*compare)(const CATSYSTS_EL_T_DECL_IN_CTNR *, const CATSYSTS_EL_T_DECL_IN_CTNR *));


