// CATSysTSLinkedList_Define.h



// shortcuts
#undef  LIST_S
#define LIST_S CATSYSTS_LIST

#undef  LIST
#define LIST CATSYSTS_LIST_FULL

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


LIST::LIST_S() {}


LIST::LIST_S(const LIST& iList)
{
    PutBack(iList);
}


LIST::LIST_S(const LIST& iList, int iBegin, int iEnd)
{  
    Insert(0, iList, iBegin, iEnd);
}


LIST::~LIST_S()
{
    Clear();
}


LIST& LIST::operator=(const LIST& iList)
{
	if ( this == &iList)
		return *this;

    Clear();
    PutBack(iList);
    return *this;
}


int LIST::GetLength() const
{
    return m_ANC.m_length;
}


CATBoolean LIST::IsEmpty() const
{
    return m_ANC.m_length == 0;
}


void LIST::Clear()
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



// ------------------------ Public: Remove  -----------------------


HRESULT LIST::Remove(int iIndex)
{
    ABSTRACT_NODE* pAN = m_ANC.PopNode(iIndex);
    if (pAN == NULL)
        return E_FAIL;

    delete (Node_T*)pAN;
    return S_OK;
}


HRESULT LIST::RemoveRange(int iBegin, int iEnd)
{
    ABSTRACT_NODE* pAN = NULL;
    ABSTRACT_NODE* pEndAN = NULL;
    if ( m_ANC.GetNodeRange(iBegin, iEnd, pAN, pEndAN) == E_FAIL )
        return E_FAIL;

    ABSTRACT_NODE* pNextAN = NULL;
    for ( ; pAN != pEndAN && pAN != NULL ; pAN = pNextAN )
    {
        pNextAN = m_ANC.RemoveNodeGetNext(*pAN);
        delete (Node_T*)pAN;
    }

    return S_OK;
}


// ----------------- Public: Put/Pop...Front/Back -----------------


void LIST::PutFront(const T& iEl)
{
    m_ANC.InsertNodeBetween(NULL, *(new Node_T(iEl)), m_ANC.m_pFirst);
}


void LIST::PutBack(const T& iEl)
{
    m_ANC.InsertNodeBetween(m_ANC.m_pLast, *(new Node_T(iEl)), NULL);
}


void LIST::PutFront(const LIST& iList)
{
    ABSTRACT_NODE* pAN = iList.m_ANC.m_pLast;
    for ( ; pAN != NULL ; pAN = pAN->m_pPrev )
        PutFront( EL(pAN) );
}


void LIST::PutBack(const LIST& iList)
{
    ABSTRACT_NODE* pAN = iList.m_ANC.m_pFirst;
    for ( ; pAN != NULL ; pAN = pAN->m_pNext )
        PutBack( EL(pAN) );
}


HRESULT LIST::PopFront(T& oEl)
{
    ABSTRACT_NODE* pFirstAN = m_ANC.PopFirstNode();
    if (pFirstAN == NULL)
        return E_FAIL;

    oEl = EL(pFirstAN);
    delete (Node_T*)pFirstAN;
    return S_OK;
}


HRESULT LIST::PopBack(T& oEl)
{
    ABSTRACT_NODE* pLastAN = m_ANC.PopLastNode();
    if (pLastAN == NULL)
        return E_FAIL;

    oEl = EL(pLastAN);
    delete (Node_T*)pLastAN;
    return S_OK;
}



// -------- Private: Insert Element/List Before/After Node --------- 


void LIST::InsertElementBeforeNode(ABSTRACT_NODE& ioAN, const T& iEl)
{
    m_ANC.InsertNodeBetween(ioAN.m_pPrev, *(new Node_T(iEl)), &ioAN);
}


void LIST::InsertListBeforeNode(ABSTRACT_NODE& ioAN, const LIST& iList)
{
    ABSTRACT_NODE* pAN = iList.m_ANC.m_pFirst;
    for ( ; pAN != NULL ; pAN = pAN->m_pNext )
        m_ANC.InsertNodeBetween( ioAN.m_pPrev, *(new Node_T(EL(pAN))), &ioAN );
}


void LIST::PutBackNodeRange(ABSTRACT_NODE* ipBeginAN, ABSTRACT_NODE* ipEndAN)
{
    ABSTRACT_NODE* pAN = ipBeginAN;
    for ( ; pAN != ipEndAN && pAN != NULL ; pAN = pAN->m_pNext )
        PutBack( EL(pAN) );
}


void LIST::InsertNodeRangeBeforeNode(ABSTRACT_NODE& ioInsertAN, ABSTRACT_NODE* ipBeginAN, ABSTRACT_NODE* ipEndAN)
{
    ABSTRACT_NODE* pAN = ipBeginAN;
    for ( ; pAN != ipEndAN && pAN != NULL ; pAN = pAN->m_pNext )
        InsertElementBeforeNode( ioInsertAN, EL(pAN) );
}



// ------------------------ Public: Insert  ------------------------


HRESULT LIST::Insert(int iIndex, const T& iEl)
{
    ABSTRACT_NODE* pAN = m_ANC.GetNode(iIndex);
    
    if (iIndex == m_ANC.m_length)
    {
        PutBack(iEl);
        return S_OK;
    }

    if (pAN == NULL)
        return E_FAIL;

    InsertElementBeforeNode(*pAN, iEl);
    return S_OK;
}


HRESULT LIST::Insert(int iIndex, const LIST& iList)
{
    ABSTRACT_NODE* pAN = m_ANC.GetNode(iIndex);
    
    if (iIndex == m_ANC.m_length)
    {
        PutBack(iList);
        return S_OK;
    }

    if (pAN == NULL)
        return E_FAIL;

    InsertListBeforeNode(*pAN, iList);
    return S_OK;
}


HRESULT LIST::Insert(int iInsertIndex, const CATSYSTS_LIST& iList, int iRangeBegin, int iRangeEnd) 
{
    ABSTRACT_NODE* pBeginAN = NULL;
    ABSTRACT_NODE* pEndAN = NULL;
    if ( iList.m_ANC.GetNodeRange(iRangeBegin, iRangeEnd, pBeginAN, pEndAN) == E_FAIL )
        return E_FAIL;
    
    if (iInsertIndex == m_ANC.m_length)
    {
        PutBackNodeRange(pBeginAN, pEndAN);
        return S_OK;
    }

    ABSTRACT_NODE* pInsertAN = m_ANC.GetNode(iInsertIndex);
    if (pInsertAN == NULL)
        return E_FAIL;

    InsertNodeRangeBeforeNode(*pInsertAN, pBeginAN, pEndAN);
    return S_OK;
}



HRESULT LIST::Insert(int iIndex, const T* piEl, int iLength)
{
    if (piEl == NULL || iLength < 1)
        return E_FAIL;
    
    if (iIndex == m_ANC.m_length)
    {
        for ( int i = 0 ; i != iLength ; ++i )
            PutBack(piEl[i]);
        return S_OK;
    }

    ABSTRACT_NODE* pAN = m_ANC.GetNode(iIndex);
    if (pAN == NULL)
        return E_FAIL;

    for ( int i = 0 ; i != iLength ; ++i )
        m_ANC.InsertNodeBetween( pAN->m_pPrev, *(new Node_T(piEl[i])), pAN );

    return S_OK;
}



// ---------------------- Public: Set and Get ----------------------


HRESULT LIST::Set(int iIndex, const T& iEl)
{
    ABSTRACT_NODE* pAN = m_ANC.GetNode(iIndex);
    if (pAN == NULL)
        return E_FAIL;

    EL(pAN) = iEl;
    return S_OK;
}

HRESULT LIST::Get(int iIndex, T& oEl) const
{
    const ABSTRACT_NODE* pAN = m_ANC.GetNode(iIndex);
    if (pAN == NULL)
        return E_FAIL;

    oEl = EL(pAN);
    return S_OK;
}


T* LIST::GetAsPtr(int iIndex)
{
    ABSTRACT_NODE* pAN = m_ANC.GetNode(iIndex);
    if (pAN == NULL)
        return NULL;

    return &EL(pAN);
}


const T* LIST::GetAsPtr(int iIndex) const
{
    const ABSTRACT_NODE* pAN = m_ANC.GetNode(iIndex);
    if (pAN == NULL)
        return NULL;

    return &EL(pAN);
}



// ------------- Public: const/non_const...Begin/Last -------------


LIST::iterator LIST::Begin()
{  
    if (m_ANC.m_length == 0)
        return iterator( *this, NULL, -2 );

    return iterator( *this, m_ANC.m_pFirst, 0 );
}


LIST::const_iterator LIST::cBegin() const
{
    if (m_ANC.m_length == 0)
        return const_iterator( (LIST&)*this, NULL, -2 );

    return const_iterator( (LIST&)*this, m_ANC.m_pFirst, 0 );
}


LIST::iterator LIST::Last()
{
    if (m_ANC.m_length == 0)
        return iterator( *this, NULL, -2 );

    return iterator( *this, m_ANC.m_pLast, m_ANC.m_length - 1 );
}


LIST::const_iterator LIST::cLast() const
{
    if (m_ANC.m_length == 0)
        return const_iterator( (LIST&)*this, NULL, -2 );

    return const_iterator( (LIST&)*this, m_ANC.m_pLast, m_ANC.m_length - 1 );
}


// ---------- Public: hint for ArrayList implementation -----------

HRESULT LIST::SetCapacity(int iCapacity) {return E_FAIL;}




//--------------------------------------------------------------------------------
// const_iterator functions
//--------------------------------------------------------------------------------


LIST::const_iterator::const_iterator()
: m_pList(NULL), m_pAN(NULL), m_index(-2) {}


LIST::const_iterator::const_iterator(LIST& ioList, ABSTRACT_NODE* iopAN, int iIndex)
: m_pList(&ioList), m_pAN(iopAN), m_index(iIndex) {}


LIST::const_iterator::const_iterator(const const_iterator& iItr)
: m_pList(iItr.m_pList), m_pAN(iItr.m_pAN), m_index(iItr.m_index) {}


LIST::const_iterator::~const_iterator() {}


LIST::const_iterator& LIST::const_iterator::operator=(const const_iterator& iItr)
{
	if (this == &iItr)
		return *this;

    m_pList = iItr.m_pList;
    m_pAN   = iItr.m_pAN;
    m_index = iItr.m_index;
    return *this;
}


HRESULT LIST::const_iterator::Next()
{
    if (m_pAN == NULL)
    {
        if ( (m_index == -1) && (m_pList != NULL) )
        {
            m_pAN = m_pList->m_ANC.m_pFirst;
            return S_OK;
        }

        return E_FAIL;
    }

	m_pAN = m_pAN->m_pNext;
    ++m_index;
	return S_OK;
}


HRESULT LIST::const_iterator::Prev()
{
    if (m_pAN == NULL)
    {
        // if empty list then Begin() returns itr whose index == 0 => Prev() must FAIL
        if ( (m_pList != NULL) && (m_index == m_pList->GetLength()) )
        {
            m_pAN = m_pList->m_ANC.m_pLast;
            return S_OK;
        }

        return E_FAIL;
    }

	m_pAN = m_pAN->m_pPrev;
    --m_index;
	return S_OK;
}


CATBoolean LIST::const_iterator::IsBegin() const
{
    return (m_index == 0);
}


CATBoolean LIST::const_iterator::IsLast() const
{
    return (m_pList != NULL) && (m_index == m_pList->GetLength() - 1);
}


CATBoolean LIST::const_iterator::IsEnd() const
{
    return m_pAN == NULL;
}


int LIST::const_iterator::GetIndex() const
{
    return m_index;
}


CATBoolean LIST::const_iterator::operator==(const const_iterator& iItr) const
{ 
    return (m_pList == iItr.m_pList) && (m_index == iItr.m_index);
}


CATBoolean LIST::const_iterator::operator!=(const const_iterator& iItr) const
{
    return !operator==(iItr);
}


HRESULT LIST::const_iterator::Get(T& oEl) const
{
	if (m_pAN == NULL)
		return E_FAIL;

	oEl = EL(m_pAN);
	return S_OK;
}


const T* LIST::const_iterator::GetAsConstPtr() const
{
	if (m_pAN == NULL)
		return NULL;

	return &EL(m_pAN);
}


const T* LIST::const_iterator::GetAsConstPtrGoToNext()
{
	if (m_pAN == NULL)
		return NULL;

    T* pEl = &EL(m_pAN);
    m_pAN = m_pAN->m_pNext;
    ++m_index;
	return pEl;
}


const T* LIST::const_iterator::GetAsConstPtrGoToPrev()
{
	if (m_pAN == NULL)
		return NULL;

    T* pEl = &EL(m_pAN);
    m_pAN = m_pAN->m_pPrev;
    --m_index;
	return pEl;
}



//--------------------------------------------------------------------------------
// iterator functions
//--------------------------------------------------------------------------------


LIST::iterator::iterator() {}


LIST::iterator::iterator(LIST& ioList, ABSTRACT_NODE* iopAN, int iIndex)
: const_iterator(ioList, iopAN, iIndex) {}


LIST::iterator::iterator(const iterator& iItr)
: const_iterator(iItr) {}


LIST::iterator::~iterator() {}


LIST::iterator& LIST::iterator::operator=(const iterator& iItr)
{
    const_iterator::operator=(iItr);
    return *this;
}


HRESULT LIST::iterator::Set(const T& iEl) const
{
	if (m_pAN == NULL)
		return E_FAIL;

	EL(m_pAN) = iEl;
	return S_OK;
}


T* LIST::iterator::GetAsPtr() const
{
	if (m_pAN == NULL)
		return NULL;

	return &EL(m_pAN);
}


T* LIST::iterator::GetAsPtrGoToNext()
{
	if (m_pAN == NULL)
		return NULL;

    T* pEl = &EL(m_pAN);
    m_pAN = m_pAN->m_pNext;
    ++m_index;
	return pEl;
}


T* LIST::iterator::GetAsPtrGoToPrev()
{
	if (m_pAN == NULL)
		return NULL;

    T* pEl = &EL(m_pAN);
    m_pAN = m_pAN->m_pPrev;
    --m_index;
	return pEl;
}


HRESULT LIST::iterator::RemoveGoToNext()
{
	ABSTRACT_NODE* pAN = m_pAN;
    if ( pAN == NULL || m_pList == NULL)
        return E_FAIL;

    m_pAN = m_pList->m_ANC.RemoveNodeGetNext(*pAN);
    delete (Node_T*)pAN;

    ++m_index;

    return S_OK;
}


HRESULT LIST::iterator::RemoveGoToPrev()
{
	ABSTRACT_NODE* pAN = m_pAN;
    if ( pAN == NULL || m_pList == NULL)
        return E_FAIL;

    m_pAN = m_pList->m_ANC.RemoveNodeGetPrev(*pAN);
    delete (Node_T*)pAN;

    --m_index;

    return S_OK;
}


HRESULT LIST::iterator::Insert(const T& iEl)
{
    if (m_pList == NULL)
        return E_FAIL;

    if (m_index == m_pList->GetLength())
    { 
        m_pList->PutBack(iEl);
        m_index = m_pList->GetLength();
        return S_OK;
    }

    if (m_pAN == NULL)
        return E_FAIL;

    m_pList->InsertElementBeforeNode(*m_pAN, iEl);

    ++m_index;
    return S_OK;
}


HRESULT LIST::iterator::Insert(const LIST& iList)
{
    if (m_pList == NULL)
        return E_FAIL;
    
    if (m_index == m_pList->GetLength())
    { 
        m_pList->PutBack(iList);
        m_index = m_pList->GetLength();
        return S_OK;
    }

    if (m_pAN == NULL)
        return E_FAIL;

    m_pList->InsertListBeforeNode(*m_pAN, iList);

    m_index += iList.GetLength();
    return S_OK;
}


//--------------------------------------------------------------------------------
// functions that need T::operator<() to compile
//--------------------------------------------------------------------------------

#if CATSYSTS_T_HAS_LESS_OP == 1
    #include "CATSysTSLinkedList_Define_T_HAS_LESS_OP.h"
#endif


//--------------------------------------------------------------------------------
// functions that need T::operator==() and T::operator!=() to compile
//--------------------------------------------------------------------------------

#if CATSYSTS_T_HAS_COMPARE_OP == 1
    #include "CATSysTSLinkedList_Define_T_HAS_COMPARE_OP.h"
#endif


//--------------------------------------------------------------------------------
// functions that need T to be a pointer
//--------------------------------------------------------------------------------

#if CATSYSTS_T_IS_PTR == 1
    #include "CATSysTSLinkedList_Define_T_IS_PTR.h"
#endif






