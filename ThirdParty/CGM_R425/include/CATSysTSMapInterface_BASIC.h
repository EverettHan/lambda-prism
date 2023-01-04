// CATSysTSMapInterface_BASIC.h


/*
 * General remarks about capacity and load factor
 *
 * - They are hints for HashMap implementation of Map interface.
 *
 * - Load factor is the maximum average number of entries by hash code.
 *   It is the maximum fill factor of the hash table.
 *
 * - Capacity is the expected maximum number of elements in the map.
 *
 * - After capacity is set, 
 *   no rehash will occur while length stays under (or equal) to capacity
 *
 */


#define CATSYSTS_DEFAULT_CAPACITY 12
#define CATSYSTS_DEFAULT_LOAD_FACTOR .75f


/* 
 * Constructs a map
 */
CATSYSTS_MAP(int iCapacity = CATSYSTS_DEFAULT_CAPACITY, float ifLoadFactor = CATSYSTS_DEFAULT_LOAD_FACTOR);

/* 
 * Copy constructor
 * For HashMap implementation: does not trigger rehash.
 */
CATSYSTS_MAP(const CATSYSTS_MAP& iMap);

/* 
 * Copy constructor
 * For HashMap implementation: set capacity, trigger rehash.
 */
CATSYSTS_MAP(const CATSYSTS_MAP& iMap, int iCapacity);

/* 
 * Copy constructor
 * For HashMap implementation: set capacity, set loadFactor, trigger rehash.
 */
CATSYSTS_MAP(const CATSYSTS_MAP& iMap, int iCapacity, float ifLoadFactor);

/* 
 * Destructor
 */
virtual ~CATSYSTS_MAP();

/* 
 * Assignment operator
 * For HashMap implementation: does not trigger rehash.
 */
CATSYSTS_MAP& operator=(const CATSYSTS_MAP& iMap);


/* 
 * Return the map number of entries.
 */
int GetLength() const;

/* 
 * if length == 0
 *   Return TRUE.
 * else
 *   Return FALSE.
 */
CATBoolean IsEmpty() const;

/* 
 * Remove all entries from the map.
 */
void Clear(int iCapacity = CATSYSTS_DEFAULT_CAPACITY, float ifLoadFactor = CATSYSTS_DEFAULT_LOAD_FACTOR);

/* 
 * if iKey is in the map
 *   Affects (operator=) iVal to the value targeted by iKey.
 * else
 *   Add entry (iKey,iVal) to the map.
 */
void Put(const CATSYSTS_KEY_DECL_IN_CTNR& iKey, const CATSYSTS_VAL_DECL_IN_CTNR& iVal);

/* 
 * Put all entries of iMap in the map.
 */
void Put(const CATSYSTS_MAP& iMap);

/* 
 * if iKey is in the map
 *   Affects (operator=) the value targeted by iKey to oVal. Return S_OK.
 * else
 *   Do nothing. Return E_FAIL.
 */
HRESULT Get(const CATSYSTS_KEY_DECL_IN_CTNR& iKey, CATSYSTS_VAL_DECL_IN_CTNR& oVal) const;

/* 
 * if iKey is in the map
 *   Return a pointer to the value targeted by iKey.
 * else
 *   Return NULL.
 */
CATSYSTS_VAL_DECL_IN_CTNR* GetAsPtr(const CATSYSTS_KEY_DECL_IN_CTNR& iKey);

/* 
 * if iKey is in the map
 *   Return a pointer to const the value targeted by iKey.
 * else
 *   Return NULL.
 */
const CATSYSTS_VAL_DECL_IN_CTNR* GetAsPtr(const CATSYSTS_KEY_DECL_IN_CTNR& iKey) const;

/* 
 * if iKey is in the map
 *   Remove the entry targeted by iKey.
 * else
 *   Do nothing.
 */
void Remove(const CATSYSTS_KEY_DECL_IN_CTNR& iKey);

/* 
 * if iKey is in the map
 *   Return TRUE.
 * else
 *   Return FALSE.
 */
CATBoolean Find(const CATSYSTS_KEY_DECL_IN_CTNR& iKey) const;


/* 
 * if the map is not empty
 *   Return an iterator.
 * else
 *   Return an uninitialized iterator.
 */
CATSYSTS_MAP::iterator Begin();

/* 
 * if the map is not empty
 *   Return a const_iterator.
 * else
 *   Return an uninitialized const_iterator.
 */
CATSYSTS_MAP::const_iterator cBegin() const;

/* 
 * For HashMap implementation
 * Rehash the hash table given capacity and load factor
 */
void ReHash(int iCapacity, float ifLoadFactor);

