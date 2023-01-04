// CATSysTSSetInterface_T_IS_PTR.h


/* 
 * Optional function activated when CATSYSTS_T_IS_PTR == 1
 *
 * if iEl is in the set
 *   Call element destructor.
 *   Remove destroyed element from the set.
 * else  
 *   Do nothing.
 */
void Delete(const CATSYSTS_EL_T_DECL_IN_CTNR& iEl);

/* 
 * Optional function activated when CATSYSTS_T_IS_PTR == 1
 *
 * Call destructor on all elements of the set.
 * Remove all elements of the set.
 */
void DeleteAll();

/* 
 * Optional function activated when CATSYSTS_T_IS_PTR == 1
 *
 * Call destructor on all elements of the set.
 * Remove all elements of the set.
 * delete the set.
 */
void DeleteAllAndThis();


