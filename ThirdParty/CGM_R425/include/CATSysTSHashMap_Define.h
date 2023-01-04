// CATSysTSHashMap_Define.h


#include <math.h>




//-----------------------------------------------------
// define CATSYSTS_CTNR::LinkedMapOfKeyVal
//-----------------------------------------------------
#undef  CATSYSTS_NOT_BASIC_CNTR_DECL
#define CATSYSTS_NOT_BASIC_CNTR_DECL

#undef CATSYSTS_MAP
#undef CATSYSTS_MAP_FULL

#define CATSYSTS_MAP        LinkedMapOfKeyVal
#define CATSYSTS_MAP_FULL   CATSYSTS_HASH_MAP_FULL::LinkedMapOfKeyVal

#include "CATSysTSLinkedMap_Define.h"



//-----------------------------------------------------
// define CATSYSTS_CTNR::ArrayListOfLinkedMapOfKeyVal
//-----------------------------------------------------
#undef  CATSYSTS_NOT_BASIC_CNTR_DECL
#define CATSYSTS_NOT_BASIC_CNTR_DECL

#undef CATSYSTS_LIST
#undef CATSYSTS_LIST_FULL
#undef CATSYSTS_EL_T
#undef CATSYSTS_EL_T_FULL
#undef CATSYSTS_T_HAS_COMPARE_OP
#undef CATSYSTS_T_HAS_LESS_OP
#undef CATSYSTS_T_IS_PTR
#undef CATSYSTS_T_IS_BUILT_IN_TYPE

#define CATSYSTS_LIST                ArrayListOfLinkedMapOfKeyVal
#define CATSYSTS_LIST_FULL           CATSYSTS_HASH_MAP_FULL::ArrayListOfLinkedMapOfKeyVal
#define CATSYSTS_EL_T                LinkedMapOfKeyVal
#define CATSYSTS_EL_T_FULL           CATSYSTS_HASH_MAP_FULL::LinkedMapOfKeyVal
#define CATSYSTS_T_HAS_COMPARE_OP    0
#define CATSYSTS_T_HAS_LESS_OP       0
#define CATSYSTS_T_IS_PTR            0
#define CATSYSTS_T_IS_BUILT_IN_TYPE  0

#include "CATSysTSArrayList_Define.h"




//--------------------------------------------------------------------------
// declare CATSYSTS_CTNR : the HashMap
//--------------------------------------------------------------------------


// shortcuts
#undef  MAP_S
#define MAP_S CATSYSTS_CTNR

#undef  MAP
#define MAP CATSYSTS_HASH_MAP_FULL

#undef  K_S
#define K_S CATSYSTS_KEY

#undef  K
#define K CATSYSTS_KEY_FULL

#undef  V_S
#define V_S CATSYSTS_VAL

#undef  V
#define V CATSYSTS_VAL_FULL

#undef  ENTRY
#define ENTRY(pAN) (((Node_KV*)pAN)->m_entry)

#undef  KEY
#define KEY(pAN) (((Node_KV*)pAN)->m_entry.m_key)

#undef  VAL
#define VAL(pAN) (((Node_KV*)pAN)->m_entry.m_val)


//--------------------------------------------------------------------------------
// basic functions
//--------------------------------------------------------------------------------


MAP::MAP_S(int iCapacity, float ifLoadFactor)
{
    Init(iCapacity, ifLoadFactor);
}


MAP::MAP_S(const MAP& iMap)
: m_table(iMap.m_table), m_length(iMap.m_length), m_fCapaMult(iMap.m_fCapaMult)
{}


MAP::MAP_S(const MAP& iMap, int iCapacity)
{
    Init(iCapacity, 1.f/iMap.m_fCapaMult);
    Fill(iMap);
}


MAP::MAP_S(const MAP& iMap, int iCapacity, float ifLoadFactor)
{
    Init(iCapacity, ifLoadFactor);
    Fill(iMap);
}


MAP::~MAP_S() {}


MAP& MAP::operator=(const MAP& iMap)
{
	if ( this == &iMap) 
		return *this;

    m_table     = iMap.m_table;
    m_length    = iMap.m_length;
    m_fCapaMult = iMap.m_fCapaMult;
    return *this;
}


void MAP::Init(int iCapacity, float ifLoadFactor) 
{
    m_length = 0;
    
    if (iCapacity < 1)
        iCapacity = CATSYSTS_DEFAULT_CAPACITY;

    if (ifLoadFactor < .1f || ifLoadFactor > 100.f)
        ifLoadFactor = CATSYSTS_DEFAULT_LOAD_FACTOR;

    m_fCapaMult = 1.f / ifLoadFactor;

    int tableLength = GetMinimumTableLength(iCapacity);

    m_table.SetCapacity(tableLength);

    LinkedMapOfKeyVal emptyLnkMap;
    for ( int i = 0 ; i < tableLength ; ++i )
        m_table.PutBack(emptyLnkMap);
}


void MAP::ReHash(int iCapacity, float ifLoadFactor)
{
    MAP* pNewMap = new MAP(*this, iCapacity, ifLoadFactor);
    
    operator=(*pNewMap);

    delete pNewMap;
}



int MAP::GetLength() const
{
    return m_length;
}


CATBoolean MAP::IsEmpty() const
{
    return m_length == 0;
}


void MAP::Clear(int iCapacity, float ifLoadFactor)
{
    m_table.Clear();

    Init(iCapacity, ifLoadFactor);
}



static CATUINT32 BinHashFunc(const char* ipBin, CATUINT32 iSize)
{
   CATUINT32 seed = 131; // 31 131 1313 13131 131313 etc..
   CATUINT32 hash = 0;

   for( CATUINT32 i = 0 ; i < iSize ; ++i )
      hash = (hash*seed) + ipBin[i];

   return (hash & 0x7FFFFFFF);
}


CATUINT32 MAP::Hash(const K& iKey) const
{
    #if   CATSYSTS_KEY_HAS_HASH_FUNC    == 1

        return ((CATUINT32)iKey.HashFunc()) % m_table.GetLength();


    #elif CATSYSTS_KEY_HAS_GET_BIN_DUMP == 1

        CATUINT32 size = 0;
        const char* pBin = iKey.GetBinDump(size);
        if (pBin == NULL)
            return 0;
        return BinHashFunc(pBin, size) % m_table.GetLength();


    #elif CATSYSTS_KEY_IS_BUILT_IN_TYPE == 1

        return BinHashFunc((const char*)&iKey, sizeof(K)) % m_table.GetLength();


    #else

        return 0;


    #endif
}


MAP::LinkedMapOfKeyVal& MAP::GetLinkedMap(const K& iKey)
{
    return *m_table.GetAsPtr(Hash(iKey));
}


const MAP::LinkedMapOfKeyVal& MAP::GetLinkedMap(const K& iKey) const
{
    return *m_table.GetAsPtr(Hash(iKey));
}


int MAP::GetMinimumTableLength(int iCapacity) const
{
    return (int)ceil(iCapacity * m_fCapaMult);
}


void MAP::Put(const K& iKey, const V& iVal)
{
    LinkedMapOfKeyVal& lnkMap = GetLinkedMap(iKey);
    int lnkMapLengthDiff = -lnkMap.GetLength();

    lnkMap.Put(iKey, iVal);

    lnkMapLengthDiff += lnkMap.GetLength();

    if (lnkMapLengthDiff == 1)
    {
        if (GetMinimumTableLength(m_length+1) > m_table.GetLength())
            ReHash(m_length * 2, 1.f / m_fCapaMult);

        ++m_length;
    }
}


void MAP::Put(const MAP& iMap)
{
    const_iterator itr = iMap.cBegin();
    const Entry* pEntry = NULL;
    while (pEntry = itr.GetEntryAsPtrGoToNext())
        Put(pEntry->m_key, pEntry->m_val);
}


void MAP::Fill(const MAP& iMap)
{
    const_iterator itr = iMap.cBegin();
    const Entry* pEntry = NULL;
    while (pEntry = itr.GetEntryAsPtrGoToNext())
        GetLinkedMap(pEntry->m_key).Put(pEntry->m_key, pEntry->m_val);

    m_length = iMap.m_length;
}


HRESULT MAP::Get(const K& iKey, V& oVal) const
{
    return GetLinkedMap(iKey).Get(iKey, oVal);
}


const V* MAP::GetAsPtr(const K& iKey) const
{
    return GetLinkedMap(iKey).GetAsPtr(iKey);
}


V* MAP::GetAsPtr(const K& iKey)
{
    return GetLinkedMap(iKey).GetAsPtr(iKey);
}


void MAP::Remove(const K& iKey)
{
    LinkedMapOfKeyVal& lnkMap = GetLinkedMap(iKey);
    m_length -= lnkMap.GetLength();

    lnkMap.Remove(iKey);

    m_length += lnkMap.GetLength();
}


CATBoolean MAP::Find(const K& iKey) const
{
    return GetLinkedMap(iKey).Find(iKey);
}


MAP::const_iterator MAP::cBegin() const
{
    return const_iterator( (MAP&)*this );
}


MAP::iterator MAP::Begin()
{
    return iterator( (MAP&)*this );
}







//--------------------------------------------------------------------------------
// const_iterator functions
//--------------------------------------------------------------------------------


MAP::const_iterator::const_iterator()
: m_pMap(NULL) {}


MAP::const_iterator::const_iterator(MAP& ioMap)
: m_pMap(&ioMap)
{
    m_tableItr = ioMap.m_table.Begin();

    GoToNonEmptyLinkedMap();
}


MAP::const_iterator::const_iterator(const const_iterator& iItr)
: m_pMap(iItr.m_pMap), m_tableItr(iItr.m_tableItr), m_linkedMapItr(iItr.m_linkedMapItr) {}


MAP::const_iterator::~const_iterator() {}


MAP::const_iterator& MAP::const_iterator::operator=(const const_iterator& iItr)
{
	if ( this == &iItr)
		return * this;

    m_pMap         = iItr.m_pMap;
    m_tableItr     = iItr.m_tableItr;
    m_linkedMapItr = iItr.m_linkedMapItr;
    return *this;
}


void MAP::const_iterator::GoToNonEmptyLinkedMap()
{
    // skip all LinkedMaps that are empty
    LinkedMapOfKeyVal* pLnkMap = NULL;
    for ( ; pLnkMap = m_tableItr.GetAsPtr() ; m_tableItr.Next())
    {
        if ( pLnkMap->IsEmpty() )
            continue;

        m_linkedMapItr = pLnkMap->Begin();
        return;
    } 

    return;
}


HRESULT MAP::const_iterator::Next()
{
    m_linkedMapItr.Next();

    if (m_linkedMapItr.IsEnd() == FALSE)
        return S_OK;

    if (m_tableItr.Next() == E_FAIL)
        return E_FAIL;

    GoToNonEmptyLinkedMap();

    return S_OK;
}


CATBoolean MAP::const_iterator::IsEnd() const
{
    return m_tableItr.IsEnd();
}


CATBoolean MAP::const_iterator::operator==(const const_iterator& iItr) const
{
    return (m_pMap == iItr.m_pMap) 
        && (m_tableItr == iItr.m_tableItr) 
        && (m_linkedMapItr == iItr.m_linkedMapItr);
}


CATBoolean MAP::const_iterator::operator!=(const const_iterator& iItr) const
{
    return !operator==(iItr);
}


HRESULT MAP::const_iterator::GetKey(K& oKey) const
{
	return m_linkedMapItr.GetKey(oKey);
}


HRESULT MAP::const_iterator::GetVal(V& oVal) const
{
    return m_linkedMapItr.GetVal(oVal);
}


HRESULT MAP::const_iterator::Get(K& oKey, V& oVal) const
{
    return m_linkedMapItr.Get(oKey, oVal);
}


const K* MAP::const_iterator::GetKeyAsPtr() const
{
    return m_linkedMapItr.GetKeyAsPtr();
}


const V* MAP::const_iterator::GetValAsConstPtr() const
{
    return m_linkedMapItr.GetValAsPtr();
}


const MAP::Entry* MAP::const_iterator::GetEntryAsPtr() const
{
    return m_linkedMapItr.GetEntryAsPtr();
}


const K* MAP::const_iterator::GetKeyAsPtrGoToNext()
{
    const K* pKey = m_linkedMapItr.GetKeyAsPtr();
    Next();   
	return pKey;
}


const V* MAP::const_iterator::GetValAsConstPtrGoToNext()
{
    const V* pVal = m_linkedMapItr.GetValAsPtr();
    Next();   
	return pVal;
}


const MAP::Entry* MAP::const_iterator::GetEntryAsPtrGoToNext()
{
    const Entry* pEntry = m_linkedMapItr.GetEntryAsPtr();
    Next();   
	return pEntry;
}




//--------------------------------------------------------------------------------
// iterator functions
//--------------------------------------------------------------------------------



MAP::iterator::iterator() {}


MAP::iterator::iterator(MAP& ioMap)
: const_iterator(ioMap) {}


MAP::iterator::iterator(const iterator& iItr)
: const_iterator(iItr) {}


MAP::iterator::~iterator() {}


MAP::iterator& MAP::iterator::operator=(const iterator& iItr)
{
    const_iterator::operator=(iItr);
    return *this;
}


HRESULT MAP::iterator::SetVal(const V& iVal) const
{
    return m_linkedMapItr.SetVal(iVal);
}


V* MAP::iterator::GetValAsPtr() const
{
    return m_linkedMapItr.GetValAsPtr();
}


V* MAP::iterator::GetValAsPtrGoToNext()
{
    V* pVal = m_linkedMapItr.GetValAsPtr();
    Next();
	return pVal;
}




//--------------------------------------------------------------------------------
// functions that need VAL::operator==() and VAL::operator!=() to compile
//--------------------------------------------------------------------------------

#if CATSYSTS_VAL_HAS_COMPARE_OP == 1
#include "CATSysTSHashMap_Define_VAL_HAS_COMPARE_OP.h"
#endif



//--------------------------------------------------------------------------------
// functions that need T to be a pointer
//--------------------------------------------------------------------------------

#if CATSYSTS_VAL_IS_PTR == 1
#include "CATSysTSHashMap_Define_VAL_IS_PTR.h"
#endif







