// CATSysTSLinkedLIST_HAS_COMPARE_OP_Define.h

// functions that need T::operator==() and T::operator!=() to compile



int LIST::Find(const T& iEl, int iStartIndex) const
{
    const ABSTRACT_NODE* pAN = m_ANC.GetNode(iStartIndex);
    if (pAN == NULL)
        return -1;

    for (int i = iStartIndex ; pAN != NULL ; pAN = pAN->m_pNext, ++i )
    {
        if ( ((const Node_T*)pAN)->m_el == iEl )
            return i;
    }

    return -1;
}


CATBoolean LIST::operator==(const LIST& iList) const
{
    if (m_ANC.m_length != iList.m_ANC.m_length)
        return FALSE;

    ABSTRACT_NODE* pAN_1 = m_ANC.m_pFirst;
    ABSTRACT_NODE* pAN_2 = iList.m_ANC.m_pFirst;
    for ( ; pAN_1!=NULL && pAN_2!=NULL ; pAN_1=pAN_1->m_pNext, pAN_2=pAN_2->m_pNext )
    { 
        if ( ((Node_T*)pAN_1)->m_el != ((Node_T*)pAN_2)->m_el )
            return FALSE;
    }

    return TRUE;
}


CATBoolean LIST::operator!=(const LIST& iList) const
{
    return !operator==(iList);
}


