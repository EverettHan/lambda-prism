// CATSysTSMapInterface_ConstIterator_BASIC.h


/*
 * General remarks about map const_iterator
 *
 * - When you get a const_iterator on a map.
 *   If you modify the map, this const_iterator is no longer valid.
 *   You should not use it anymore, unless you reinitialize it with cBegin()
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
 * if iterator is uninitialized or map is empty
 *   Return E_FAIL.
 * else if position is not end
 *   Go to next position. Return S_OK.
 * else
 *   Return E_FAIL.
 */
HRESULT Next();

/* 
 * if iterator is uninitialized or map is empty
 *   Return TRUE.
 * else if position is end
 *   Return TRUE.
 * else
 *   Return FALSE.
 */
CATBoolean IsEnd() const;

/* 
 * let's call "uninitialized or map is empty": "INVALID"
 *
 * if (iterator is INVALID) and (iItr is INVALID)
 *   Return TRUE.
 * else if only one of them is INVALID
 *   Return FALSE.
 * else if they both points to the same map and have the same position
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
 * if iterator is uninitialized or map is empty
 *   Do nothing. Return E_FAIL.
 * else if position is not end
 *   Affects key at position to oKey (with operator=). Return S_OK.
 * else
 *   Do nothing. Return E_FAIL.
 */
HRESULT GetKey(CATSYSTS_KEY_DECL_IN_CTNR& oKey) const;

/* 
 * if iterator is uninitialized or map is empty
 *   Do nothing. Return E_FAIL.
 * else if position is not end
 *   Affects value at position to oVal (with operator=). Return S_OK.
 * else
 *   Do nothing. Return E_FAIL.
 */
HRESULT GetVal(CATSYSTS_VAL_DECL_IN_CTNR& oVal) const;

/* 
 * if iterator is uninitialized or map is empty
 *   Do nothing. Return E_FAIL.
 * else if position is not end
 *   Affects key at position to oKey (with operator=).
 *   Affects value at position to oVal (with operator=).
 *   Return S_OK.
 * else
 *   Do nothing. Return E_FAIL.
 */
HRESULT Get(CATSYSTS_KEY_DECL_IN_CTNR& oKey, CATSYSTS_VAL_DECL_IN_CTNR& oVal) const;

/* 
 * if iterator is uninitialized or map is empty
 *   Return NULL.
 * else if position is not end
 *   Return *pointer to const* key at position.
 * else
 *   Return NULL.
 */
const CATSYSTS_KEY_DECL_IN_CTNR* GetKeyAsPtr() const;

/* 
 * if iterator is uninitialized or map is empty
 *   Return NULL.
 * else if position is not end
 *   Return *pointer to const* value at position.
 * else
 *   Return NULL.
 */
const CATSYSTS_VAL_DECL_IN_CTNR* GetValAsConstPtr() const;

/* 
 * if iterator is uninitialized or map is empty
 *   Return NULL.
 * else if position is not end
 *   Return *pointer to const* entry at position.
 * else
 *   Return NULL.
 */
const Entry* GetEntryAsPtr() const;

/* 
 * if iterator is uninitialized or map is empty
 *   Return NULL.
 * else if position is not end
 *   Return *pointer to const* key at position.
 *   Go to next position.
 * else
 *   Return NULL.
 */
const CATSYSTS_KEY_DECL_IN_CTNR* GetKeyAsPtrGoToNext();

/* 
 * if iterator is uninitialized or map is empty
 *   Return NULL.
 * else if position is not end
 *   Return *pointer to const* value at position.
 *   Go to next position.
 * else
 *   Return NULL.
 */
const CATSYSTS_VAL_DECL_IN_CTNR* GetValAsConstPtrGoToNext();

/* 
 * if iterator is uninitialized or map is empty
 *   Return NULL.
 * else if position is not end
 *   Return *pointer to const* entry at position.
 *   Go to next position.
 * else
 *   Return NULL.
 */
const Entry* GetEntryAsPtrGoToNext();



