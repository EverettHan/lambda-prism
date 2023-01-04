// CATSysTSArrayList_Define_T_HAS_COMPARE_OP.h

// functions that need T::operator==() and T::operator!=() to compile



int LIST::Find(const T& iEl, int iStartIndex) const
{	
#ifdef CATSYSTS_FULL_TS
	Lock();
#endif
	int rc = -1;
	
    if (SUCCEEDED(m_AC.CheckIndex(iStartIndex)))
	{		
		for (int i = iStartIndex ; i != m_AC.m_length ; ++i)
		{
			if (*pT(i) == iEl)
			{	
				rc = i;
				break;
			}
		}
	}
	
#ifdef CATSYSTS_FULL_TS
	Unlock();
#endif
	
    return rc;
}

#ifndef CATSYSTS_FULL_TS
CATBoolean LIST::operator==(const LIST& iList) const
{ 
    if (m_AC.m_length != iList.m_AC.m_length)
        return FALSE;

    for ( int i = 0 ; i != m_AC.m_length ; ++i )
    {
        if (*pT(i) != *iList.pT(i))
            return FALSE;
    }

    return TRUE;
}
CATBoolean LIST::operator!=(const LIST& iList) const
{
    return !operator==(iList);
}
#endif







