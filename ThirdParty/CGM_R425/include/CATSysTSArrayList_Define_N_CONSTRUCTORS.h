// CATSysTSArrayList_Define_N_CONSTRUCTORS.h

// create n list-constructors with 1 to n elements as arguments



#if CATSYSTS_LIST_WITH_N_CONSTRUCTORS>0 && CATSYSTS_LIST_WITH_N_CONSTRUCTORS<10
/* 
 * Constructs a list with 1 element
 */
LIST::LIST_S(const T& iEl1)
: m_AC(sizeof(T))
{
  PutBack(iEl1);
}

#else
#error bad value for CATSYSTS_LIST_WITH_N_CONSTRUCTORS
#endif


#if CATSYSTS_LIST_WITH_N_CONSTRUCTORS>1
/* 
 * Constructs a list with 2 elements
 */
LIST::LIST_S(const T& iEl1,
             const T& iEl2)
: m_AC(sizeof(T))
{
  PutBack(iEl1);
  PutBack(iEl2);
}

#endif


#if CATSYSTS_LIST_WITH_N_CONSTRUCTORS>2
/* 
 * Constructs a list with 3 elements
 */
LIST::LIST_S(const T& iEl1,
             const T& iEl2,
             const T& iEl3)
: m_AC(sizeof(T))
{
  PutBack(iEl1);
  PutBack(iEl2);
  PutBack(iEl3);
}

#endif


#if CATSYSTS_LIST_WITH_N_CONSTRUCTORS>3
/* 
 * Constructs a list with 4 elements
 */
LIST::LIST_S(const T& iEl1,
             const T& iEl2,
             const T& iEl3,
             const T& iEl4)
: m_AC(sizeof(T))
{
  PutBack(iEl1);
  PutBack(iEl2);
  PutBack(iEl3);
  PutBack(iEl4);
}

#endif

#if CATSYSTS_LIST_WITH_N_CONSTRUCTORS>4
/* 
 * Constructs a list with 5 elements
 */
LIST::LIST_S(const T& iEl1,
             const T& iEl2,
             const T& iEl3,
             const T& iEl4,
             const T& iEl5)
: m_AC(sizeof(T))
{
  PutBack(iEl1);
  PutBack(iEl2);
  PutBack(iEl3);
  PutBack(iEl4);
  PutBack(iEl5);
}

#endif


#if CATSYSTS_LIST_WITH_N_CONSTRUCTORS>5
/* 
 * Constructs a list with 6 elements
 */
LIST::LIST_S(const T& iEl1,
             const T& iEl2,
             const T& iEl3,
             const T& iEl4,
             const T& iEl5,
             const T& iEl6)
: m_AC(sizeof(T))
{
  PutBack(iEl1);
  PutBack(iEl2);
  PutBack(iEl3);
  PutBack(iEl4);
  PutBack(iEl5);
  PutBack(iEl6);
}

#endif


#if CATSYSTS_LIST_WITH_N_CONSTRUCTORS>6
/* 
 * Constructs a list with 7 elements
 */
LIST::LIST_S(const T& iEl1,
             const T& iEl2,
             const T& iEl3,
             const T& iEl4,
             const T& iEl5,
             const T& iEl6,
             const T& iEl7)
: m_AC(sizeof(T))
{
  PutBack(iEl1);
  PutBack(iEl2);
  PutBack(iEl3);
  PutBack(iEl4);
  PutBack(iEl5);
  PutBack(iEl6);
  PutBack(iEl7);
}

#endif


#if CATSYSTS_LIST_WITH_N_CONSTRUCTORS>7
/* 
 * Constructs a list with 8 elements
 */
LIST::LIST_S(const T& iEl1,
             const T& iEl2,
             const T& iEl3,
             const T& iEl4,
             const T& iEl5,
             const T& iEl6,
             const T& iEl7,
             const T& iEl8)
: m_AC(sizeof(T))
{
  PutBack(iEl1);
  PutBack(iEl2);
  PutBack(iEl3);
  PutBack(iEl4);
  PutBack(iEl5);
  PutBack(iEl6);
  PutBack(iEl7);
  PutBack(iEl8);
}

#endif


#if CATSYSTS_LIST_WITH_N_CONSTRUCTORS>8
/* 
 * Constructs a list with 9 elements
 */
LIST::LIST_S(const T& iEl1,
             const T& iEl2,
             const T& iEl3,
             const T& iEl4,
             const T& iEl5,
             const T& iEl6,
             const T& iEl7,
             const T& iEl8,
             const T& iEl9)
: m_AC(sizeof(T))
{
  PutBack(iEl1);
  PutBack(iEl2);
  PutBack(iEl3);
  PutBack(iEl4);
  PutBack(iEl5);
  PutBack(iEl6);
  PutBack(iEl7);
  PutBack(iEl8);
  PutBack(iEl9);
}

#endif








