// CATSysTSArrayList_Define_T_IS_PTR.h

// functions that can be used when T is a pointer



HRESULT LIST::Delete(int iIndex)
{
#ifdef CATSYSTS_FULL_TS
	Lock();
#endif
	
	HRESULT hr = E_FAIL;
	
    if (SUCCEEDED(m_AC.CheckIndex(iIndex)))
	{       

		Destroy(iIndex);
		delete *pT(iIndex);

		m_AC.Move(iIndex, iIndex + 1, m_AC.m_length - iIndex - 1);
		--m_AC.m_length;
		
		hr = S_OK;
	}
	
#ifdef CATSYSTS_FULL_TS
	Unlock();
#endif

	return hr;
}


void LIST::DeleteAll()
{
#ifdef CATSYSTS_FULL_TS
	Lock();
#endif
	
	for (int i = 0 ; i != m_AC.m_length ; ++i)
        delete *pT(i);

    Clear();

#ifdef CATSYSTS_FULL_TS
	Unlock();
#endif
}


void LIST::DeleteAllAndThis()
{
    DeleteAll();
    delete this;
}

HRESULT LIST::iterator::DeleteGoToNext()
{

#ifdef CATSYSTS_FULL_TS
	Lock();
#endif
	
	HRESULT hr = E_FAIL;
	
    if (m_pList && SUCCEEDED(m_pList->Delete(m_index)))
	{
		hr = S_OK;
		++m_index;
	}

#ifdef CATSYSTS_FULL_TS
	Unlock();
#endif	
	
    return hr;
}


HRESULT LIST::iterator::DeleteGoToPrev()
{
#ifdef CATSYSTS_FULL_TS
	Lock();
#endif
	HRESULT hr = E_FAIL;
	
    if (m_pList && SUCCEEDED(m_pList->Delete(m_index)))
	{
		hr = S_OK;
		--m_index;
	}
		
#ifdef CATSYSTS_FULL_TS
	Unlock();
#endif
    return hr;
}



