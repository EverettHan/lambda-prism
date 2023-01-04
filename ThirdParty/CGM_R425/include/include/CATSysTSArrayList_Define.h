// CATSysTSArrayList_Define.h


#include <new>
#include <string.h>


// shortcuts
#undef  LIST_S
#define LIST_S CATSYSTS_LIST

#undef  LIST
#define LIST CATSYSTS_LIST_FULL

#undef  T_S
#define T_S CATSYSTS_EL_T

#undef  T
#define T CATSYSTS_EL_T_FULL


// if memcpy are enough to copy T
#undef CATSYSTS_T_IS_CLASS
#if CATSYSTS_T_IS_BUILT_IN_TYPE + CATSYSTS_T_IS_PTR > 0
    #define CATSYSTS_T_IS_CLASS 0
#else
    #define CATSYSTS_T_IS_CLASS 1
#endif


// explicit destructor non class
#undef EXPLICIT_DESTRUCTOR
#if CATSYSTS_T_IS_CLASS == 1
    #define EXPLICIT_DESTRUCTOR(v) v.~T_S()
#else
    #define EXPLICIT_DESTRUCTOR(v)
#endif



//---------------------------------------------
//---------------------------------------------
// Functions from CATSysTSListInterface_BASIC.h
//---------------------------------------------
//---------------------------------------------

LIST::LIST_S()
: m_AC(sizeof(T)) {}


#ifndef CATSYSTS_FULL_TS
LIST::LIST_S(const LIST& iList)
: m_AC(sizeof(T))
{	
	m_AC.SetCapacity(iList.m_AC.m_capacity);
	if (iList.m_AC.m_length>0)
	{
		BuildRangeFromList(0, iList);
		m_AC.m_length = iList.m_AC.m_length;
	}
}

LIST::LIST_S(const LIST& iList, int iBegin, int iEnd)
: m_AC(sizeof(T))
{  
    if (iList.m_AC.CheckRange(iBegin, iEnd) == S_OK)
	{
		m_AC.SetCapacity(iEnd - iBegin);
		BuildRangeFromRange(0, iList, iBegin, iEnd);
		m_AC.m_length = iEnd - iBegin;
	}	
}

LIST& LIST::operator=(const LIST& iList)
{
	if ( this == &iList) 
		return *this;
	
    Clear();	  
	PutBack(iList);

    return *this;
}
#endif

LIST::~LIST_S()
{
    DestroyRange(0, m_AC.m_length);
}


int LIST::GetLength() const
{
#ifdef CATSYSTS_FULL_TS
	Lock();
#endif
	
    int rc = m_AC.m_length;
	
#ifdef CATSYSTS_FULL_TS
	Unlock();
#endif
	return rc;
}


CATBoolean LIST::IsEmpty() const
{
#ifdef CATSYSTS_FULL_TS
	Lock();
#endif
	
	CATBoolean rc = ((m_AC.m_length == 0) ? (TRUE) : (FALSE));
	
#ifdef CATSYSTS_FULL_TS
	Unlock();
#endif
	
	return rc;
}


void LIST::Clear()
{
#ifdef CATSYSTS_FULL_TS
	Lock();
#endif
	
    DestroyRange(0, m_AC.m_length);
    m_AC.ReInit();
	
#ifdef CATSYSTS_FULL_TS
	Unlock();
#endif
}

//-------------------------------------------------------
//-------------------------------------------------------
// Functions specific to array lists
// Even if they are defined as public they should not be
// outside the class list.
//------------------------------------------------------
//------------------------------------------------------

T* LIST::pT(int iIndex)
{
	T* rc = (T*)m_AC.m_pArray + iIndex;
	return rc;
}


const T* LIST::pT(int iIndex) const
{
	T* rc = (T*)m_AC.m_pArray + iIndex;
	return rc;	
}



void LIST::Destroy(int iIndex)
{   
#if CATSYSTS_T_IS_CLASS == 1
	// on solaris pT(iIndex)->~T_S; does not compile... so we do:
    T* p = pT(iIndex);
    p->~T_S();	
#endif
}

void LIST::DestroyRange(int iBegin, int iEnd)
{
#if CATSYSTS_T_IS_CLASS == 1
	for (int i = iBegin ; i != iEnd ; ++i)
    {
        // on solaris pT(iIndex)->~T_S; does not compile... so we do:
        T* p = pT(i);
        p->~T_S();    
	}
#endif
}

#ifndef CATSYSTS_FULL_TS
void LIST::BuildRangeFromRange(int iInsertIndex, const LIST& iList, int iRangeBegin, int iRangeEnd) 
{
    BuildRangeFromBuffer(iInsertIndex, iList.pT(iRangeBegin), iRangeEnd - iRangeBegin);
}

void LIST::BuildRangeFromList(int iInsertIndex, const LIST& iList) 
{
    BuildRangeFromBuffer(iInsertIndex, iList.pT(0), iList.m_AC.m_length);
}
#endif

void LIST::BuildRangeFromBuffer(int iInsertIndex, const T* ipEl, int iLength) 
{
#if CATSYSTS_T_IS_CLASS == 1
        for (int i = 0 ; i != iLength ; ++i)
            new(pT(iInsertIndex + i)) T(*(ipEl + i));
#else
        memcpy(pT(iInsertIndex), ipEl, iLength*m_AC.m_sizeof_T);
#endif
}

#ifdef CATSYSTS_FULL_TS
void LIST::Lock() const
{	
	((CATMutex *)&m_Mutex)->Lock();	
}
void LIST::Unlock() const
{
	((CATMutex *)&m_Mutex)->Unlock();
}
#endif



// ------------------------ Public: Insert  ------------------------

HRESULT LIST::Insert(int iIndex, const T& iEl)
{
#ifdef CATSYSTS_FULL_TS
	Lock();
#endif
	
	HRESULT rc = E_FAIL;
	
    if (SUCCEEDED(m_AC.MakeRoom(iIndex, 1)))
	{        
		new(pT(iIndex)) T(iEl);
		rc = S_OK;
	}
	
#ifdef CATSYSTS_FULL_TS
	Unlock();
#endif
	
    return rc;
}

#ifndef CATSYSTS_FULL_TS
HRESULT LIST::Insert(int iIndex, const LIST& iList) 
{
    if (m_AC.MakeRoom(iIndex, iList.m_AC.m_length) == E_FAIL)
        return E_FAIL;

    BuildRangeFromRange(iIndex, iList, 0, iList.m_AC.m_length);
    return S_OK;
}
HRESULT LIST::Insert(int iInsertIndex, const CATSYSTS_LIST& iList, int iRangeBegin, int iRangeEnd) 
{
    if (iList.m_AC.CheckRange(iRangeBegin, iRangeEnd) == E_FAIL)
        return E_FAIL;

    if (m_AC.MakeRoom(iInsertIndex, iRangeEnd - iRangeBegin) == E_FAIL)
        return E_FAIL;

    BuildRangeFromRange(iInsertIndex, iList, iRangeBegin, iRangeEnd);
    return S_OK;
}
#endif


HRESULT LIST::Insert(int iIndex, const T* piEl, int iLength)
{
    if (piEl == NULL || iLength < 1)
        return E_FAIL;

#ifdef CATSYSTS_FULL_TS
	Lock();
#endif

	HRESULT rc = E_FAIL;
	
    if (SUCCEEDED(m_AC.MakeRoom(iIndex, iLength)))
	{        
		BuildRangeFromBuffer(iIndex, piEl, iLength);
		rc = S_OK;
	}
	
#ifdef CATSYSTS_FULL_TS
	Unlock();
#endif
	
    return rc;
}


// ------------------------ Public: Remove ------------------------

HRESULT LIST::Remove(int iIndex)
{
#ifdef CATSYSTS_FULL_TS
	Lock();
#endif
	
	HRESULT rc = E_FAIL;
	
    if (SUCCEEDED(m_AC.CheckIndex(iIndex)))
	{      
		Destroy(iIndex);
		m_AC.Move(iIndex, iIndex + 1, m_AC.m_length - iIndex - 1);
		--m_AC.m_length;
		rc = S_OK;
	}
	
#ifdef CATSYSTS_FULL_TS
	Unlock();
#endif

	return rc;
}

HRESULT LIST::RemoveRange(int iBegin, int iEnd)
{
#ifdef CATSYSTS_FULL_TS
	Lock();
#endif
	
    HRESULT rc = E_FAIL;
	
    if (SUCCEEDED(m_AC.CheckRange(iBegin, iEnd)))
	{        
		DestroyRange(iBegin, iEnd);
		m_AC.Move(iBegin, iEnd, m_AC.m_length - iEnd);
		m_AC.m_length -= iEnd - iBegin;
		rc = S_OK;
	}
	
#ifdef CATSYSTS_FULL_TS
	Unlock();
#endif

	return rc;
}



// ----------------- Public: Put/Pop...Front/Back -----------------


void LIST::PutFront(const T& iEl)
{
    Insert(0, iEl);
}


void LIST::PutBack(const T& iEl)
{
#ifdef CATSYSTS_FULL_TS
	Lock();
#endif
	
    Insert(m_AC.m_length, iEl);
		
#ifdef CATSYSTS_FULL_TS
	Unlock();
#endif
}

#ifndef CATSYSTS_FULL_TS
void LIST::PutFront(const LIST& iList)
{
    Insert(0, iList);
}

void LIST::PutBack(const LIST& iList)
{	
    Insert(m_AC.m_length, iList);
}
#endif

HRESULT LIST::PopFront(T& oEl)
{
#ifdef CATSYSTS_FULL_TS
	Lock();
#endif
	HRESULT hr = E_FAIL;
    
	if (m_AC.m_length > 0)
	{        
		T& first = *((T*)m_AC.m_pArray);
		oEl = first;
		EXPLICIT_DESTRUCTOR(first);

		m_AC.Move(0, 1, m_AC.m_length - 1);
		--m_AC.m_length;
		
		hr = S_OK;	
	}				
#ifdef CATSYSTS_FULL_TS
	Unlock();
#endif

	return hr;
}


HRESULT LIST::PopBack(T& oEl)
{
#ifdef CATSYSTS_FULL_TS
	Lock();
#endif

    HRESULT hr = E_FAIL;
    
	if (m_AC.m_length > 0)
	{ 
		
		T& last = *((T*)m_AC.m_pArray + m_AC.m_length - 1);
		oEl = last;
		EXPLICIT_DESTRUCTOR(last);

		--m_AC.m_length;
		
		hr = S_OK;	
	}		
#ifdef CATSYSTS_FULL_TS
	Unlock();
#endif

	return hr;
}

// ---------------------- Public: Set and Get ----------------------

HRESULT LIST::Set(int iIndex, const T& iEl)
{
#ifdef CATSYSTS_FULL_TS
	Lock();
#endif

    HRESULT hr = E_FAIL;
    
	if (SUCCEEDED(m_AC.CheckIndex(iIndex)))
	{        
		*pT(iIndex) = iEl;
		
		hr = S_OK;	
	}
			
#ifdef CATSYSTS_FULL_TS
	Unlock();
#endif

    return hr;
}


HRESULT LIST::Get(int iIndex, T& oEl) const
{
#ifdef CATSYSTS_FULL_TS
	Lock();
#endif

    HRESULT hr = E_FAIL;
    
	if (SUCCEEDED(m_AC.CheckIndex(iIndex)))
	{  
		oEl = *pT(iIndex);
	
		hr = S_OK;	
	}	
#ifdef CATSYSTS_FULL_TS
	Unlock();
#endif

    return hr;
}
	

T* LIST::GetAsPtr(int iIndex)
{
#ifdef CATSYSTS_FULL_TS
	Lock();
#endif

	T* rc = NULL;
	
    if (SUCCEEDED(m_AC.CheckIndex(iIndex)))	
		rc = pT(iIndex);
		
#ifdef CATSYSTS_FULL_TS
	Unlock();
#endif

    return rc;
}


const T* LIST::GetAsPtr(int iIndex) const
{
#ifdef CATSYSTS_FULL_TS
	Lock();
#endif

    const T* rc = NULL;
	
    if (SUCCEEDED(m_AC.CheckIndex(iIndex)))	
		rc = pT(iIndex);
		
#ifdef CATSYSTS_FULL_TS
	Unlock();
#endif

    return rc;
}



// ------------- Public: const/non_const...Begin/Last -------------

LIST::iterator LIST::Begin()
{
    return iterator(*this, GetLength() == 0 ? -2 : 0);
}


LIST::const_iterator LIST::cBegin() const
{
    return const_iterator((LIST&)*this, GetLength() == 0 ? -2 : 0);
}


LIST::iterator LIST::Last()
{
    return iterator(*this, GetLength() == 0 ? -2 : GetLength() - 1);
}


LIST::const_iterator LIST::cLast() const
{
    return const_iterator((LIST&)*this, GetLength() == 0 ? -2 : GetLength() - 1);
}

// ---------- Public: hint for ArrayList implementation -----------

HRESULT LIST::SetCapacity(int iCapacity)
{
#ifdef CATSYSTS_FULL_TS
	Lock();
#endif
	
    HRESULT hr = m_AC.SetCapacity(iCapacity);
	
#ifdef CATSYSTS_FULL_TS
	Unlock();
#endif
	return hr;
}

//------------------------------
//------------------------------
// list const_iterator functions
//------------------------------
//------------------------------

LIST::const_iterator::const_iterator()
: m_pList(NULL), m_index(-2) {}


LIST::const_iterator::const_iterator(LIST& ioList, int iIndex)
: m_pList(&ioList), m_index(iIndex) {}

#ifndef CATSYSTS_FULL_TS
LIST::const_iterator::const_iterator(const const_iterator& iItr)
: m_pList(iItr.m_pList), m_index(iItr.m_index) {}
LIST::const_iterator& LIST::const_iterator::operator=(const const_iterator& iItr)
{
	if ( this == &iItr)
		return *this;

    m_pList = iItr.m_pList;
    m_index = iItr.m_index;
    return *this;
}
#endif

LIST::const_iterator::~const_iterator() {}


HRESULT LIST::const_iterator::Next()
{
    if (m_pList == NULL || m_index < -1 || m_index > m_pList->GetLength() - 1)
        return E_FAIL;

    ++m_index;
	return S_OK;
}


HRESULT LIST::const_iterator::Prev()
{
    if (m_pList == NULL || m_index < 0 || m_index > m_pList->GetLength())
        return E_FAIL;

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
    return (m_pList == NULL) || (m_index < 0) || (m_index > m_pList->GetLength() - 1);
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
	if (IsEnd() == TRUE)
		return E_FAIL;

	oEl = *(m_pList->pT(m_index));
	return S_OK;
}


const T* LIST::const_iterator::GetAsConstPtr() const
{
	if (IsEnd() == TRUE)
		return NULL;

	return m_pList->pT(m_index);
}


const T* LIST::const_iterator::GetAsConstPtrGoToNext()
{
	if (IsEnd() == TRUE)
		return NULL;

	return m_pList->pT(m_index++);
}


const T* LIST::const_iterator::GetAsConstPtrGoToPrev()
{
	if (IsEnd() == TRUE)
		return NULL;

	return m_pList->pT(m_index--);
}

//------------------------
//------------------------
// list iterator functions
//------------------------
//------------------------

LIST::iterator::iterator() {}


LIST::iterator::iterator(LIST& ioList, int iIndex)
: const_iterator(ioList, iIndex) {}

#ifndef CATSYSTS_FULL_TS
LIST::iterator::iterator(const iterator& iItr)
: const_iterator(iItr) {}

LIST::iterator& LIST::iterator::operator=(const iterator& iItr)
{
    const_iterator::operator=(iItr);
    return *this;
}
#endif
LIST::iterator::~iterator() {} 

HRESULT LIST::iterator::Set(const T& iEl) const
{
	if (IsEnd() == TRUE)
		return E_FAIL;

    *(m_pList->pT(m_index)) = iEl;
	return S_OK;
}


T* LIST::iterator::GetAsPtr() const
{
    return (T*)GetAsConstPtr();
}


T* LIST::iterator::GetAsPtrGoToNext()
{
    return (T*)GetAsConstPtrGoToNext();
}


T* LIST::iterator::GetAsPtrGoToPrev()
{
    return (T*)GetAsConstPtrGoToPrev();
}


HRESULT LIST::iterator::Insert(const T& iEl)
{
    if (m_pList == NULL)
        return E_FAIL;

    if (m_pList->Insert(m_index, iEl) == E_FAIL)
        return E_FAIL;

    ++m_index;
    return S_OK;
}

#ifndef CATSYSTS_FULL_TS
HRESULT LIST::iterator::Insert(const LIST& iList)
{
    if (m_pList == NULL)
        return E_FAIL;

    if (m_pList->Insert(m_index, iList) == E_FAIL)
        return E_FAIL;

    m_index += iList.GetLength();
    return S_OK;
}
#endif

HRESULT LIST::iterator::RemoveGoToNext()
{
    if (m_pList == NULL || m_pList->Remove(m_index) == E_FAIL)
        return E_FAIL;

    ++m_index;
    return S_OK;
}


HRESULT LIST::iterator::RemoveGoToPrev()
{
    if (m_pList == NULL || m_pList->Remove(m_index) == E_FAIL)
        return E_FAIL;

    --m_index;
    return S_OK;
}

#if CATSYSTS_T_HAS_CUSTOM_COMP_METH == 1
    #include "CATSysTSArrayList_Define_T_HAS_CUSTOM_COMP_METH.h"
#endif


//--------------------------------------------------------------------------------
// create n list-constructors with 1 to n elements as arguments
//--------------------------------------------------------------------------------
#ifdef CATSYSTS_LIST_WITH_N_CONSTRUCTORS
    #include "CATSysTSArrayList_Define_N_CONSTRUCTORS.h"
#endif



//--------------------------------------------------------------------------------
// functions that need T::operator<() to compile
//--------------------------------------------------------------------------------

#if CATSYSTS_T_HAS_LESS_OP == 1
    #include "CATSysTSArrayList_Define_T_HAS_LESS_OP.h"
#endif


//--------------------------------------------------------------------------------
// functions that need T::operator==() and T::operator!=() to compile
//--------------------------------------------------------------------------------

#if CATSYSTS_T_HAS_COMPARE_OP == 1
    #include "CATSysTSArrayList_Define_T_HAS_COMPARE_OP.h"
#endif


//--------------------------------------------------------------------------------
// functions that need T to be a pointer
//--------------------------------------------------------------------------------

#if CATSYSTS_T_IS_PTR == 1
    #include "CATSysTSArrayList_Define_T_IS_PTR.h"
#endif


