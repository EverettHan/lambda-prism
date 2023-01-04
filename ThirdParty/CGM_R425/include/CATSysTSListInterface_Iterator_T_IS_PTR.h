// CATSysTSListInterface_Iterator_T_IS_PTR.h


/* 
 * Optional function activated when CATSYSTS_T_IS_PTR == 1
 *
 * if iterator is unitialized or list is empty
 *   Do nothing. Return E_FAIL.
 * if iIndex is in [0;length-1]
 *   Call element at position destructor.
 *   Remove destroyed element from the list.
 *   Go to next position.
 *   Return S_OK.
 * else 
 *   Do nothing. Return E_FAIL.
 */
HRESULT DeleteGoToNext();

/* 
 * Optional function activated when CATSYSTS_T_IS_PTR == 1
 *
 * if iterator is unitialized or list is empty
 *   Do nothing. Return E_FAIL.
 * if iIndex is in [0;length-1]
 *   Call element at position destructor.
 *   Remove destroyed element from the list.
 *   Go to previous position.
 *   Return S_OK.
 * else 
 *   Do nothing. Return E_FAIL.
 */
HRESULT DeleteGoToPrev();



