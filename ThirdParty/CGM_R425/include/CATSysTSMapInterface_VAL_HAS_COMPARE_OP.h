// CATSysTSMapInterface_VAL_HAS_COMPARE_OP.h


/* 
 * Optional function activated when CATSYSTS_VAL_HAS_COMPARE_OP == 1
 *
 * Remove all entries that value is equal to iVal
 */
void RemoveValues(const CATSYSTS_VAL_DECL_IN_CTNR& iVal);

/* 
 * Optional function activated when CATSYSTS_T_EL_HAS_COMPARE_OP == 1
 *
 * Compare two maps
 */
CATBoolean operator==(const CATSYSTS_MAP& iMap) const;

/* 
 * Optional function activated when CATSYSTS_T_EL_HAS_COMPARE_OP == 1
 *
 * Compare two maps
 */
CATBoolean operator!=(const CATSYSTS_MAP& iMap) const;

