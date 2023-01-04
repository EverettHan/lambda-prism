// CATSysTSMapInterface_Iterator_BASIC.h


/*
 * General remarks about map iterator
 *
 * - When you get an iterator on a map.
 *   If you modify the map, this iterator is no longer valid.
 *   You should not use it anymore, unless you reinitialize it with Begin()
 *
 */



/* 
 * Constructs an uninitialized iterator
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
 * if iterator is uninitialized or map is empty
 *   Do nothing. Return E_FAIL.
 * else if position is not end
 *   Affects iVal to value at position (with operator=). Return S_OK.
 * else
 *   Do nothing. Return E_FAIL.
 */
HRESULT SetVal(const CATSYSTS_VAL_DECL_IN_CTNR& iVal) const;

/* 
 * if iterator is uninitialized or map is empty
 *   Return NULL.
 * else if position is not end
 *   Return *pointer to value* at position.
 *   Go to next position.
 * else
 *   Return NULL.
 */
CATSYSTS_VAL_DECL_IN_CTNR* GetValAsPtr() const;

/* 
 * if iterator is uninitialized or map is empty
 *   Return NULL.
 * else if position is not end
 *   Return *pointer to const* value at position.
 *   Go to next position.
 * else
 *   Return NULL.
 */
CATSYSTS_VAL_DECL_IN_CTNR* GetValAsPtrGoToNext();

