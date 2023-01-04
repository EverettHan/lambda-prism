// CATSysTSSetInterface_ConstIterator_BASIC.h


/*
 * General remarks about set const_iterator
 *
 * - When you get a const_iterator from a set.
 *   If you modify the set, this const_iterator is no longer valid.
 *   You should not use it anymore, unless you reinitialize it with cBegin()
 *
 * - There is no iterator on set, only const_iterator
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
 * if iterator is uninitialized or set is empty
 *   Return E_FAIL.
 * else if position is not end
 *   Go to next position. Return S_OK.
 * else
 *   Return E_FAIL.
 */
HRESULT Next();

/* 
 * if iterator is uninitialized or set is empty
 *   Return TRUE.
 * else if position is end
 *   Return TRUE.
 * else
 *   Return FALSE.
 */
CATBoolean IsEnd() const;

/* 
 * let's call "uninitialized or set is empty": "INVALID"
 *
 * if (iterator is INVALID) and (iItr is INVALID)
 *   Return TRUE.
 * else if only one of them is INVALID
 *   Return FALSE.
 * else if they both points to the same set and have the same position
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
 * if iterator is uninitialized or set is empty
 *   Do nothing. Return E_FAIL.
 * else if position is not end
 *   Affects element at position to oEl (with operator=). Return S_OK.
 * else
 *   Do nothing. Return E_FAIL.
 */
HRESULT Get(CATSYSTS_EL_T_DECL_IN_CTNR& oEl) const;

/* 
 * if iterator is uninitialized or set is empty
 *   Return NULL.
 * else if position is not end
 *   Return pointer to const element at position.
 * else
 *   Return NULL.
 */
const CATSYSTS_EL_T_DECL_IN_CTNR* GetAsPtr() const;

/* 
 * if iterator is uninitialized or set is empty
 *   Return NULL.
 * else if position is not end
 *   Return pointer to const element at position.
 *   Go to next position.
 * else
 *   Return NULL.
 */
const CATSYSTS_EL_T_DECL_IN_CTNR* GetAsPtrGoToNext();


