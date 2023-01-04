// CATSysTSMapInterface_VAL_IS_PTR.h

/* 
 * Optional function activated when CATSYSTS_T_IS_PTR == 1
 *
 * if iKey is in the map
 *   Call value targeted by iKey destructor.
 *   Remove entry targeted by iKey from the map.
 * else  
 *   Do nothing.
 */
void Delete(const CATSYSTS_KEY_DECL_IN_CTNR& iKey);

/* 
 * Optional function activated when CATSYSTS_T_IS_PTR == 1
 *
 * Call destructor on all values of the map.
 * Remove all entries from the map.
 */
void DeleteAll();

/* 
 * Optional function activated when CATSYSTS_T_IS_PTR == 1
 *
 * Call destructor on all values of the map.
 * Remove all entries from the map.
 * delete the map.
 */
void DeleteAllAndThis();


