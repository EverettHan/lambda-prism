// CATSysTSListInterface_T_IS_PTR.h


/* 
 * Optional function activated when CATSYSTS_T_IS_PTR == 1
 *
 * if iIndex is in [0;length-1]
 *   Call element destructor.
 *   Remove destroyed element from the list.
 * else  
 *   Do nothing.
 */
HRESULT Delete(int iIndex);

/* 
 * Optional function activated when CATSYSTS_T_IS_PTR == 1
 *
 * Call destructor on all elements of the list.
 * Remove all elements from the list.
 */
void DeleteAll();

/* 
 * Optional function activated when CATSYSTS_T_IS_PTR == 1
 *
 * Call destructor on all elements of the list.
 * Remove all elements from the list.
 * delete the list.
 */
void DeleteAllAndThis();


