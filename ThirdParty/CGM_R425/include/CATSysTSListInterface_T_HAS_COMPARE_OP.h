// CATSysTSListInterface_T_HAS_COMPARE_OP.h


/* 
 * Optional function activated when CATSYSTS_T_EL_HAS_COMPARE_OP == 1
 *
 * if iStartIndex is in [0;length-1]
 *   Return index of the first element equal to iEl, beginning from iStartIndex.
 *   if no equal element is found then return -1.
 * else  
 *   Return -1.
 */
int Find(const CATSYSTS_EL_T_DECL_IN_CTNR& iEl, int iStartIndex = 0) const;

/* 
 * Optional function activated when CATSYSTS_T_EL_HAS_COMPARE_OP == 1
 *
 * Compare two lists elements
 */
CATBoolean operator==(const CATSYSTS_LIST&) const;

/* 
 * Optional function activated when CATSYSTS_T_EL_HAS_COMPARE_OP == 1
 *
 * Inverse of operator==()
 */
CATBoolean operator!=(const CATSYSTS_LIST&) const;



