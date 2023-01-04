// CATSysTSListInterface_ConstIterator_BASIC.h


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
 * Constructs an uninitialized const_iterator
 */
const_iterator();

/* 
 * Copy constructor
 */
const_iterator(const const_iterator& iItr);

/* 
 * Destructor
 */
virtual ~const_iterator();

/* 
 * Assignment operator
 */
const_iterator& operator=(const const_iterator& iItr);



/* 
 * if iterator is uninitialized or list is empty
 *   Return E_FAIL.
 * else if position is in [-1;length-1]
 *   Go to next position. Return S_OK.
 * else
 *   Return E_FAIL.
 */
HRESULT Next();

/* 
 * if iterator is uninitialized or list is empty
 *   Return E_FAIL.
 * else if position is in [0;length]
 *   Go to previous position. Return S_OK.
 * else
 *   Return E_FAIL.
 */
HRESULT Prev();

/* 
 * if iterator is uninitialized or list is empty
 *   Return FALSE.
 * else if position is in 0
 *   Return TRUE.
 * else
 *   Return FALSE.
 */
CATBoolean IsBegin() const;

/* 
 * if iterator is uninitialized or list is empty
 *   Return FALSE.
 * else if position is in length-1
 *   Return TRUE.
 * else
 *   Return FALSE.
 */
CATBoolean IsLast() const;

/* 
 * if iterator is uninitialized or list is empty
 *   Return TRUE.
 * else if position is in -1 or length
 *   Return TRUE.
 * else
 *   Return FALSE.
 */
CATBoolean IsEnd() const;

/* 
 * if iterator is uninitialized or list is empty
 *   Return -2.
 * else
 *   Return position.
 */
int GetIndex() const;

/* 
 * let's call "uninitialized or list is empty": "INVALID"
 *
 * if (iterator is INVALID) and (iItr is INVALID)
 *   Return TRUE.
 * else if only one of them is INVALID
 *   Return FALSE.
 * else if they both points to the same list and have the same index
 *   Return TRUE.
 * else
 *   Return FALSE.
 */
CATBoolean operator==(const const_iterator& iItr) const;

/* 
 * Inverse of operator==()
 */
CATBoolean operator!=(const const_iterator& iItr) const;


/* 
 * if iterator is uninitialized or list is empty
 *   Do nothing. Return E_FAIL.
 * else if position is in [0;length-1]
 *   Affects element at position to oEl (with operator=). Return S_OK.
 * else
 *   Do nothing. Return E_FAIL.
 */
HRESULT Get(CATSYSTS_EL_T_DECL_IN_CTNR& oEl) const;

/* 
 * if iterator is uninitialized or list is empty
 *   Return NULL.
 * else if position is in [0;length-1]
 *   Return pointer to const element at position.
 * else
 *   Return NULL.
 */
const CATSYSTS_EL_T_DECL_IN_CTNR* GetAsConstPtr() const;

/* 
 * if iterator is uninitialized or list is empty
 *   Return NULL.
 * else if position is in [0;length-1]
 *   Return pointer to const element at position.
 *   Go to next position.
 * else
 *   Return NULL.
 */
const CATSYSTS_EL_T_DECL_IN_CTNR* GetAsConstPtrGoToNext();

/* 
 * if iterator is uninitialized or list is empty
 *   Return NULL.
 * else if position is in [0;length-1]
 *   Return pointer to const element at position.
 *   Go to previous position
 * else
 *   Return NULL.
 */
const CATSYSTS_EL_T_DECL_IN_CTNR* GetAsConstPtrGoToPrev();




