// CATSysTSListInterface_Iterator_BASIC.h


/* 
 * const_iterator and iterator positions
 * 
 * list of string that contains "a", "b", "c"
 *   elements:         NULL      <->   "a"   <->     "b"      <->   "c"   <->     NULL
 *   iterator:    Begin().Prev() <-> Begin() <-> Begin.Next() <-> Last()  <-> Last().Next()
 *   position:          -1       <->    0    <->      1       <->    2    <->      3 (= length)
 *
 */



/* 
 * Constructs an iterator is uninitialized iterator
 */
iterator();

/* 
 * Copy constructor
 */
iterator(const iterator& iItr);

/* 
 * Destructor
 */
virtual ~iterator();

/* 
 * Assignment operator
 */
iterator& operator=(const iterator& iItr);


/* 
 * if iterator is uninitialized or list is empty
 *   Do nothing. Return E_FAIL.
 * else if position is in [0;length-1]
 *   Affect (operator=) iEl to element at position. Return S_OK.
 * else
 *   Do nothing. Return E_FAIL.
 */
HRESULT Set(const CATSYSTS_EL_T_DECL_IN_CTNR& iEl) const;

/* 
 * if iterator is uninitialized or list is empty
 *   Return NULL.
 * else if position is in [0;length-1]
 *   Return pointer to element at position.
 * else
 *   Return NULL.
 */
CATSYSTS_EL_T_DECL_IN_CTNR* GetAsPtr() const;

/* 
 * if iterator is uninitialized or list is empty
 *   Return NULL.
 * else if position is in [0;length-1]
 *   Return pointer to element at position.
 *   Go to next position.
 * else
 *   Return NULL.
 */
CATSYSTS_EL_T_DECL_IN_CTNR* GetAsPtrGoToNext();

/* 
 * if iterator is uninitialized or list is empty
 *   Return NULL.
 * else if position is in [0;length-1]
 *   Return pointer to const element at position.
 *   Go to previous position
 * else
 *   Return NULL.
 */
CATSYSTS_EL_T_DECL_IN_CTNR* GetAsPtrGoToPrev();

/* 
 * if iterator is uninitialized or list is empty
 *   Do nothing. Return E_FAIL.
 * else if position is in [0;length]
 *   Insert element iEl before position. Return S_OK.
 *   Position after the call has increased by one.
 *   Iterator points to the same element as before the call.
 * else  
 *   Do nothing. Return E_FAIL.
 */
HRESULT Insert(const CATSYSTS_EL_T_DECL_IN_CTNR& iEl);

/* 
 * if iterator is uninitialized or list is empty
 *   Do nothing. Return E_FAIL.
 * else if position is in [0;length]
 *   Insert list iList before position. Return S_OK.
 *   Position after the call has increased by iList length.
 *   Iterator points to the same element as before the call.
 * else  
 *   Do nothing. Return E_FAIL.
 */
HRESULT Insert(const CATSYSTS_LIST& iList);

/* 
 * if iterator is uninitialized or list is empty
 *   Do nothing. Return E_FAIL.
 * else if position is in [0;length-1]
 *   Remove element at position.
 *   Go to next position.
 *   Return S_OK.
 * else  
 *   Do nothing. Return E_FAIL.
 */
HRESULT RemoveGoToNext();

/* 
 * if iterator is uninitialized or list is empty
 *   Do nothing. Return E_FAIL.
 * else if position is in [0;length-1]
 *   Remove element at position.
 *   Go to previous position.
 *   Return S_OK.
 * else  
 *   Do nothing. Return E_FAIL.
 */
HRESULT RemoveGoToPrev();


