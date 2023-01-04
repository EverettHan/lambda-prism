// CATSysTSLinkedSet_Define.h



// shortcuts
#undef  SET_S
#define SET_S CATSYSTS_SET

#undef  SET
#define SET CATSYSTS_SET_FULL

#undef  T_S
#define T_S CATSYSTS_EL_T

#undef  T
#define T CATSYSTS_EL_T_FULL

#undef  ABSTRACT_NODE
#define ABSTRACT_NODE CATSysTSLinkedAbstractCtnr::Node

#undef  EL
#define EL(pAN) (((Node_T*)pAN)->m_el)



//--------------------------------------------------------------------------------
// basic functions
//--------------------------------------------------------------------------------


SET::SET_S() {}


SET::SET_S(const SET& iSet)
{
    CopySet(iSet);
}


SET::~SET_S()
{
    Clear();
}


SET& SET::operator=(const SET& iSet)
{
	if ( this == &iSet)
		return *this;

    Clear();
    CopySet(iSet);
    return *this;
}


int SET::GetLength() const
{
    return m_ANC.m_length;
}


CATBoolean SET::IsEmpty() const
{
    return (m_ANC.m_length == 0);
}


void SET::Clear()
{
	ABSTRACT_NODE* pAN = m_ANC.m_pFirst;
    ABSTRACT_NODE* pNextAN = NULL;
    for ( ; pAN != NULL ; pAN = pNextAN )
    {
        pNextAN = pAN->m_pNext;
        delete (Node_T*)pAN;
    }

    m_ANC.Init();
}


CATSysTSLinkedAbstractCtnr::Node* SET::FindNode(const T& iEl) const
{
	ABSTRACT_NODE* pAN = m_ANC.m_pFirst;
    for ( ; pAN != NULL ; pAN = pAN->m_pNext )
    {
        if (EL(pAN) == iEl)
            return pAN;
    }

    return NULL;
}


void SET::CopySet(const SET& iSet)
{
    const ABSTRACT_NODE* pAN = iSet.m_ANC.m_pFirst;
    for ( ; pAN != NULL ; pAN = pAN->m_pNext )
        m_ANC.InsertNodeBetween(m_ANC.m_pLast, *(new Node_T(EL(pAN))), NULL);
}


void SET::Put(const T& iEl)
{
    if ( FindNode(iEl) != NULL )
        return;

    m_ANC.InsertNodeBetween( m_ANC.m_pLast, *(new Node_T(iEl)), NULL );
}


void SET::Remove(const T& iEl)
{
    ABSTRACT_NODE* pAN = FindNode(iEl);
    
    if (pAN == NULL)
        return;

    m_ANC.RemoveNode(*pAN);
    delete (Node_T*)pAN;
}


CATBoolean SET::Find(const T& iEl) const
{
    return FindNode(iEl) != NULL;
}



SET::const_iterator SET::cBegin() const
{
    return const_iterator( (SET&)*this, m_ANC.m_pFirst);
}


CATBoolean SET::operator==(const SET& iSet) const
{

    if (m_ANC.m_length != iSet.m_ANC.m_length)
        return FALSE;

    ABSTRACT_NODE* pAN = m_ANC.m_pFirst;
    for ( ; pAN != NULL ; pAN = pAN->m_pNext )
    { 
        if ( iSet.FindNode(EL(pAN)) == NULL )
            return FALSE;
    }

    return TRUE;
}


CATBoolean SET::operator!=(const SET& iSet) const
{
    return !operator==(iSet);

}


void SET::Put(const SET& iSet)
{
    const ABSTRACT_NODE* pAN = iSet.m_ANC.m_pFirst;
    for ( ; pAN != NULL ; pAN = pAN->m_pNext )
        Put(EL(pAN));
}


void SET::Intersect(const SET& iSet)
{
    ABSTRACT_NODE* pAN = m_ANC.m_pFirst;
    ABSTRACT_NODE* pNextAN = NULL;
    for ( ; pAN != NULL ; pAN = pNextAN)
    {
        if ( iSet.Find(EL(pAN)) == FALSE )
        {
            pNextAN = m_ANC.RemoveNodeGetNext(*pAN);
            delete (Node_T*)pAN;
        }
        else
            pNextAN = pAN->m_pNext;
    } 
}


CATBoolean SET::IsIncludedIn(const SET& iSet)
{
    if (m_ANC.m_length > iSet.m_ANC.m_length)
        return FALSE;

    ABSTRACT_NODE* pAN = m_ANC.m_pFirst;
    for ( ; pAN != NULL ; pAN = pAN->m_pNext )
    {
        if ( iSet.Find(EL(pAN)) == FALSE )
            return FALSE;
    }

    return TRUE;
}


CATBoolean SET::IsIntersect(const SET& iSet)
{
    ABSTRACT_NODE* pAN = m_ANC.m_pFirst;
    for ( ; pAN != NULL ; pAN = pAN->m_pNext )
    {
        if ( iSet.Find(EL(pAN)) == TRUE )
            return TRUE;
    }

    return FALSE;
}



// ---------- Public: hint for ArraySet implementation -----------

void SET::SetCapacity(int iCapacity) {}




//--------------------------------------------------------------------------------
// const_iterator functions
//--------------------------------------------------------------------------------


SET::const_iterator::const_iterator()
: m_pSet(NULL), m_pAN(NULL) {}


SET::const_iterator::const_iterator(SET& ioSet, ABSTRACT_NODE* iopAN)
: m_pSet(&ioSet), m_pAN(iopAN) {}


SET::const_iterator::const_iterator(const const_iterator& iItr)
: m_pSet(iItr.m_pSet), m_pAN(iItr.m_pAN) {}


SET::const_iterator::~const_iterator() {}


SET::const_iterator& SET::const_iterator::operator=(const const_iterator& iItr)
{
	if ( this == &iItr)
		return * this;

    m_pSet = iItr.m_pSet;
    m_pAN  = iItr.m_pAN;
    return *this;
}


HRESULT SET::const_iterator::Next()
{
    if (m_pAN == NULL)
        return E_FAIL;

	m_pAN = m_pAN->m_pNext;
	return S_OK;
}


CATBoolean SET::const_iterator::IsEnd() const
{
    return m_pAN == NULL;
}


CATBoolean SET::const_iterator::operator==(const const_iterator& iItr) const
{ 
    return (m_pSet == iItr.m_pSet) && (m_pAN == iItr.m_pAN);
}


CATBoolean SET::const_iterator::operator!=(const const_iterator& iItr) const
{
    return !operator==(iItr);
}


HRESULT SET::const_iterator::Get(T& oEl) const
{
	if (m_pAN == NULL)
		return E_FAIL;

	oEl = EL(m_pAN);
	return S_OK;
}


const T* SET::const_iterator::GetAsPtr() const
{
	if (m_pAN == NULL)
		return NULL;

	return &EL(m_pAN);
}


const T* SET::const_iterator::GetAsPtrGoToNext()
{
	if (m_pAN == NULL)
		return NULL;

    T* pEl = &EL(m_pAN);
    m_pAN = m_pAN->m_pNext;
	return pEl;
}



//--------------------------------------------------------------------------------
// functions that need T to be a pointer
//--------------------------------------------------------------------------------

#if CATSYSTS_T_IS_PTR == 1
#include "CATSysTSLinkedSet_Define_T_IS_PTR.h"
#endif






