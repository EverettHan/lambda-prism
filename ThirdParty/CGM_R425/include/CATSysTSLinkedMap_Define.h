// CATSysTSLinkedMap_Define.h



// shortcuts
#undef  MAP_S
#define MAP_S CATSYSTS_MAP

#undef  MAP
#define MAP CATSYSTS_MAP_FULL

#undef  K_S
#define K_S CATSYSTS_KEY

#undef  K
#define K CATSYSTS_KEY_FULL

#undef  V_S
#define V_S CATSYSTS_VAL

#undef  V
#define V CATSYSTS_VAL_FULL

#undef  ABSTRACT_NODE
#define ABSTRACT_NODE CATSysTSLinkedAbstractCtnr::Node

#undef  ENTRY
#define ENTRY(pAN) (((Node_KV*)pAN)->m_entry)

#undef  KEY
#define KEY(pAN) (((Node_KV*)pAN)->m_entry.m_key)

#undef  VAL
#define VAL(pAN) (((Node_KV*)pAN)->m_entry.m_val)



//--------------------------------------------------------------------------------
// basic functions
//--------------------------------------------------------------------------------


MAP::MAP_S(int iCapacity, float ifLoadFactor) {}


MAP::MAP_S(const MAP& iMap)
{
    CopyMap(iMap);
}


MAP::MAP_S(const MAP& iMap, int iCapacity)
{
    CopyMap(iMap);
}


MAP::MAP_S(const MAP& iMap, int iCapacity, float ifLoadFactor)
{
    CopyMap(iMap);
}


MAP::~MAP_S()
{
    Clear();
}


MAP& MAP::operator=(const MAP& iMap)
{
	if ( this == &iMap)
		return *this;

    Clear();
    CopyMap(iMap);
    return *this;
}


int MAP::GetLength() const
{
    return m_ANC.m_length;
}


CATBoolean MAP::IsEmpty() const
{
    return (m_ANC.m_length == 0);
}


void MAP::Clear(int iCapacity, float ifLoadFactor)
{
	ABSTRACT_NODE* pAN = m_ANC.m_pFirst;
    ABSTRACT_NODE* pNextAN = NULL;
    for ( ; pAN != NULL ; pAN = pNextAN )
    {
        pNextAN = pAN->m_pNext;
        delete (Node_KV*)pAN;
    }

    m_ANC.Init();
}


void MAP::CopyMap(const MAP& iMap)
{
    ABSTRACT_NODE* pAN = iMap.m_ANC.m_pFirst;
    for ( ; pAN != NULL ; pAN = pAN->m_pNext )
        m_ANC.InsertNodeBetween(m_ANC.m_pLast, *(new Node_KV( *(Node_KV*)pAN )), NULL);
}


ABSTRACT_NODE* MAP::FindNode(const K& iKey) const
{
    ABSTRACT_NODE* pAN = m_ANC.m_pFirst;
    for ( ; pAN != NULL ; pAN = pAN->m_pNext )
    {
        if ( KEY(pAN) == iKey )
            return pAN;
    }
    return NULL;
}


void MAP::Put(const K& iKey, const V& iVal)
{
    ABSTRACT_NODE* pAN = FindNode(iKey);

    if (pAN != NULL)
        VAL(pAN) = iVal;
    else
        m_ANC.InsertNodeBetween(m_ANC.m_pLast, *(new Node_KV(iKey, iVal)), NULL);
}


void MAP::Put(const MAP& iMap)
{
    const_iterator itr = iMap.cBegin();
    const Entry* pEntry = NULL;
    while (pEntry = itr.GetEntryAsPtrGoToNext())
        Put(pEntry->m_key, pEntry->m_val);
}


HRESULT MAP::Get(const K& iKey, V& oVal) const
{
    ABSTRACT_NODE* pAN = FindNode(iKey);
    if (pAN == NULL)
        return E_FAIL;

    oVal = VAL(pAN);
    return S_OK;
}


const V* MAP::GetAsPtr(const K& iKey) const
{
    ABSTRACT_NODE* pAN = FindNode(iKey);
    if (pAN == NULL)
        return NULL;

    return &VAL(pAN);
}


V* MAP::GetAsPtr(const K& iKey)
{
    ABSTRACT_NODE* pAN = FindNode(iKey);
    if (pAN == NULL)
        return NULL;

    return &VAL(pAN);
}


void MAP::Remove(const K& iKey)
{
    ABSTRACT_NODE* pAN = FindNode(iKey);
    if (pAN == NULL)
        return;

    m_ANC.RemoveNode(*pAN);
    delete (Node_KV*)pAN;
}


CATBoolean MAP::Find(const K& iKey) const
{
    return FindNode(iKey) == NULL ? FALSE : TRUE;
}


MAP::const_iterator MAP::cBegin() const
{
    return const_iterator( (MAP&)*this, m_ANC.m_pFirst);
}


MAP::iterator MAP::Begin()
{
    return iterator(*this, m_ANC.m_pFirst);
}


void MAP::ReHash(int iCapacity, float ifLoadFactor) {}




//--------------------------------------------------------------------------------
// const_iterator functions
//--------------------------------------------------------------------------------


MAP::const_iterator::const_iterator()
: m_pMap(NULL), m_pAN(NULL) {}


MAP::const_iterator::const_iterator(MAP& ioMap, ABSTRACT_NODE* iopAN)
: m_pMap(&ioMap), m_pAN(iopAN) {}


MAP::const_iterator::const_iterator(const const_iterator& iItr)
: m_pMap(iItr.m_pMap), m_pAN(iItr.m_pAN) {}


MAP::const_iterator::~const_iterator() {}


MAP::const_iterator& MAP::const_iterator::operator=(const const_iterator& iItr)
{
	if ( this == &iItr)
		return *this;

    m_pMap = iItr.m_pMap;
    m_pAN  = iItr.m_pAN;
    return *this;
}


HRESULT MAP::const_iterator::Next()
{
    if (m_pAN == NULL)
        return E_FAIL;

	m_pAN = m_pAN->m_pNext;
	return S_OK;
}


CATBoolean MAP::const_iterator::IsEnd() const
{
    return m_pAN == NULL;
}


CATBoolean MAP::const_iterator::operator==(const const_iterator& iItr) const
{
    return (m_pMap == iItr.m_pMap) && (m_pAN == iItr.m_pAN);
}


CATBoolean MAP::const_iterator::operator!=(const const_iterator& iItr) const
{
    return !operator==(iItr);
}


HRESULT MAP::const_iterator::GetKey(K& oKey) const
{
	if (m_pAN == NULL)
		return E_FAIL;

	oKey = KEY(m_pAN);
	return S_OK;
}


HRESULT MAP::const_iterator::GetVal(V& oVal) const
{
	if (m_pAN == NULL)
		return E_FAIL;

	oVal = VAL(m_pAN);
	return S_OK;
}


HRESULT MAP::const_iterator::Get(K& oKey, V& oVal) const
{
	if (m_pAN == NULL)
		return E_FAIL;

	oKey = KEY(m_pAN);
	oVal = VAL(m_pAN);
	return S_OK;
}


const K* MAP::const_iterator::GetKeyAsPtr() const
{
	if (m_pAN == NULL)
		return NULL;

	return &KEY(m_pAN);
}


const V* MAP::const_iterator::GetValAsConstPtr() const
{
	if (m_pAN == NULL)
		return NULL;

	return &VAL(m_pAN);
}


const MAP::Entry* MAP::const_iterator::GetEntryAsPtr() const
{
	if (m_pAN == NULL)
		return NULL;

	return &ENTRY(m_pAN);
}


const K* MAP::const_iterator::GetKeyAsPtrGoToNext()
{
	if (m_pAN == NULL)
		return NULL;

    K* pKey = &KEY(m_pAN);
    m_pAN = m_pAN->m_pNext;
	return pKey;
}


const V* MAP::const_iterator::GetValAsConstPtrGoToNext()
{
	if (m_pAN == NULL)
		return NULL;

    V* pVal = &VAL(m_pAN);
    m_pAN = m_pAN->m_pNext;
	return pVal;
}


const MAP::Entry* MAP::const_iterator::GetEntryAsPtrGoToNext()
{
	if (m_pAN == NULL)
		return NULL;

    Entry* pEntry = &ENTRY(m_pAN);
    m_pAN = m_pAN->m_pNext;
	return pEntry;
}




//--------------------------------------------------------------------------------
// iterator functions
//--------------------------------------------------------------------------------



MAP::iterator::iterator() {}


MAP::iterator::iterator(MAP& ioMap, ABSTRACT_NODE* iopAN)
: const_iterator(ioMap, iopAN) {}


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
	if (m_pAN == NULL)
		return E_FAIL;

	VAL(m_pAN) = iVal;
	return S_OK;
}


V* MAP::iterator::GetValAsPtr() const
{
	if (m_pAN == NULL)
		return NULL;

	return &VAL(m_pAN);
}


V* MAP::iterator::GetValAsPtrGoToNext()
{
	if (m_pAN == NULL)
		return NULL;

    V* pVal = &VAL(m_pAN);
    m_pAN = m_pAN->m_pNext;
	return pVal;
}




//--------------------------------------------------------------------------------
// functions that need VAL::operator==() and VAL::operator!=() to compile
//--------------------------------------------------------------------------------

#if CATSYSTS_VAL_HAS_COMPARE_OP == 1
#include "CATSysTSLinkedMap_Define_VAL_HAS_COMPARE_OP.h"
#endif



//--------------------------------------------------------------------------------
// functions that need T to be a pointer
//--------------------------------------------------------------------------------

#if CATSYSTS_VAL_IS_PTR == 1
#include "CATSysTSLinkedMap_Define_VAL_IS_PTR.h"
#endif






