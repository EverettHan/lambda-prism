// CATSysTSSetInterface_BASIC.h


/* 
 * Constructs a set
 */
CATSYSTS_SET();

/* 
 * Copy constructor
 */
CATSYSTS_SET(const CATSYSTS_SET& iSet);

/* 
 * Destructor
 */
virtual ~CATSYSTS_SET();

/* 
 * Assignment operator
 */
CATSYSTS_SET& operator=(const CATSYSTS_SET& iSet);



/* 
 * Return the set number of elements
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
 * Remove all elements from the set.
 */
void Clear();


/* 
 * if iEl is in the set
 *   Do nothing.
 * else
 *   Insert iEl in the set.
 */
void Put(const CATSYSTS_EL_T_DECL_IN_CTNR& iEl);


/* 
 * if iEl is in the set
 *   Remove it.
 * else
 *   Do nothing.
 */
void Remove(const CATSYSTS_EL_T_DECL_IN_CTNR& iEl);

/* 
 * if iEl is in the set
 *   Return TRUE.
 * else
 *   Return FASLE.
 */
CATBoolean Find(const CATSYSTS_EL_T_DECL_IN_CTNR& iEl) const;


/* 
 * if the set is not empty
 *   Return a const_iterator.
 * else
 *   Return an uninitialized const_iterator.
 */
CATSYSTS_SET::const_iterator cBegin() const;


/*
 * Compare two sets elements.
 */
CATBoolean operator==(const CATSYSTS_SET& iSet) const;

/*
 * Compare two sets elements.
 */
CATBoolean operator!=(const CATSYSTS_SET& iSet) const;


/*
 * Insert iSet into the set.
 */
void Put(const CATSYSTS_SET& iSet);


/*
 * Intersect the set with iSet.
 * Remove all elements of the set that are not in iSet.
 */
void Intersect(const CATSYSTS_SET& iSet);

/*
 * if all elements of the set are in iSet
 *   Return TRUE.
 * else
 *   Return FALSE.
 */
CATBoolean IsIncludedIn(const CATSYSTS_SET& iSet);

/*
 * if the set and iSet have at least one element in common
 *   Return TRUE.
 * else
 *   Return FALSE.
 */
CATBoolean IsIntersect(const CATSYSTS_SET& iSet);


/* 
 * Hint for ArraySet implementation, do nothing for LinkedSet implementation.
 * if iCapacity > length
 *   Set the expected maximum number of elements in the set.
 *   No allocation will occur while length stays under (or equal) to iCapacity.
 * else
 *   Do nothing.
 */
void SetCapacity(int iCapacity);



