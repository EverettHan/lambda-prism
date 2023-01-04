// CATSysTSListInterface_BASIC.h


/* 
 * Constructs an empty list
 */
CATSYSTS_LIST();

/* 
 * if 0 <= iBegin < iEnd <= length
 *   Constructs a list from a iList slice
 * else
 *   Constructs an empty list
 */
CATSYSTS_LIST(const CATSYSTS_LIST& iList, int iBegin, int iEnd);

/* 
 * Copy constructor
 */
CATSYSTS_LIST(const CATSYSTS_LIST& iList);

/* 
 * Destructor
 */
virtual ~CATSYSTS_LIST();

/* 
 * Assignment operator
 */
CATSYSTS_LIST& operator=(const CATSYSTS_LIST& iList);


/* 
 * Return the list number of elements
 */
int GetLength() const;


/* 
 * if length == 0
 *   Return TRUE
 * else
 *   Return FALSE
 */
CATBoolean IsEmpty() const;


/* 
 * Remove all elements from the list.
 */
void Clear();


/* 
 * Insert element iEl at the beginning of the list.
 */
void PutFront(const CATSYSTS_EL_T_DECL_IN_CTNR& iEl);

/* 
 * Insert list iList at the beginning of the list.
 */
void PutFront(const CATSYSTS_LIST& iList);

/* 
 * Insert element iEl at the end of the list.
 */
void PutBack(const CATSYSTS_EL_T_DECL_IN_CTNR& iEl);

/* 
 * Insert list iList at the end of the list.
 */
void PutBack(const CATSYSTS_LIST& iList);



/* 
 * if iIndex is in [0;length]
 *   Insert element iEl *before* iIndex. Return S_OK.
 * else  
 *   Do nothing. Return E_FAIL.
 */
HRESULT Insert(int iIndex, const CATSYSTS_EL_T_DECL_IN_CTNR& iEl);

/* 
 * if iIndex is in [0;length]
 *   Insert list iList *before* iIndex. Return S_OK.
 * else
 *   Do nothing. Return E_FAIL.
 */
HRESULT Insert(int iIndex, const CATSYSTS_LIST& iList);

/* 
 * if ( 0 <= iBegin < iEnd <= length ) and ( iIndex is in [0;length] )
 *   Insert range from iRangeBegin (including) to iRangeEnd (excluding) from iList *before* iIndex.
 *   Return S_OK.
 * else
 *   Do nothing. Return E_FAIL.
 */
HRESULT Insert(int iInsertIndex, const CATSYSTS_LIST& iList, int iRangeBegin, int iRangeEnd);

/* 
 * if iIndex is in [0;length]
 *   Insert buffer piEl of length iLength *before* iIndex. Return S_OK.
 * else
 *   Do nothing. Return E_FAIL.
 */
HRESULT Insert(int iIndex, const CATSYSTS_EL_T_DECL_IN_CTNR* piEl, int iLength);


/* 
 * if iIndex is in [0;length-1]
 *   Affect (operator=) iEl to element at iIndex . Return S_OK.
 * else
 *   Do nothing. Return E_FAIL.
 */
HRESULT Set(int iIndex, const CATSYSTS_EL_T_DECL_IN_CTNR& iEl);

/* 
 * if iIndex is in [0;length-1]
 *   Affect (operator=) element at iIndex to oEl. Return S_OK.
 * else
 *   Do nothing. Return E_FAIL.
 */
HRESULT Get(int iIndex, CATSYSTS_EL_T_DECL_IN_CTNR& oEl) const;

/* 
 * if iIndex is in [0;length-1]
 *   Return pointer to element at iIndex.
 * else
 *   Return NULL.
 */
CATSYSTS_EL_T_DECL_IN_CTNR* GetAsPtr(int iIndex);

/* 
 * if iIndex is in [0;length-1]
 *   Return pointer to *const* element at iIndex.
 * else
 *   Return NULL.
 */
const CATSYSTS_EL_T_DECL_IN_CTNR* GetAsPtr(int iIndex) const;


/* 
 * if iIndex is in [0;length-1]
 *   Remove element at iIndex. Return S_OK.
 * else
 *   Do nothing. Return E_FAIL.
 */
HRESULT Remove(int iIndex); 

/* 
 * if 0 <= iBegin < iEnd <= length
 *   Remove all elements between position iBegin (including ) and iEnd (excluding). Return S_OK.
 * else
 *   Do nothing. Return E_FAIL.
 */
HRESULT RemoveRange(int iBegin, int iEnd); 


/* 
 * if the list is not empty
 *   Affect (operator=) *last* element to oEl.
 *   Remove *last* element from the list.
 *   Return S_OK.
 * else
 *   Do nothing. Return E_FAIL.
 */
HRESULT PopBack(CATSYSTS_EL_T_DECL_IN_CTNR& oEl);

/* 
 * if the list is not empty
 *   Affect (operator=) *first* element to oEl.
 *   Remove *first* element from the list.
 *   Return S_OK.
 * else
 *   Do nothing. Return E_FAIL.
 */
HRESULT PopFront(CATSYSTS_EL_T_DECL_IN_CTNR& oEl);


/* 
 * if the list is not empty
 *   Return an iterator to the *first* element.
 * else
 *   Return an uninitialized iterator.
 */
CATSYSTS_LIST::iterator Begin();

/* 
 * if the list is not empty
 *   Return a const_iterator to the *first* element.
 * else
 *   Return an uninitialized const_iterator.
 */
CATSYSTS_LIST::const_iterator cBegin() const;

/* 
 * if the list is not empty
 *   Return an iterator to the *last* element.
 * else
 *   Return an uninitialized iterator.
 */
CATSYSTS_LIST::iterator Last();

/* 
 * if the list is not empty
 *   Return a const_iterator to the *last* element.
 * else
 *   Return an uninitialized const_iterator.
 */
CATSYSTS_LIST::const_iterator cLast() const;



/* 
 * Hint for ArrayList implementation, do nothing for LinkedList implementation.
 * if iCapacity > length
 *   Set the expected maximum number of elements in the list.
 *   No allocation will occur while length stays under (or equal) to iCapacity.
 * else
 *   Do nothing.
 */
HRESULT SetCapacity(int iCapacity);



