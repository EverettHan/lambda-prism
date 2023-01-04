// CATSysTSLinkedMap_Define_VAL_HAS_COMPARE_OP.h


void MAP::RemoveValues(const V& iVal)
{
	ABSTRACT_NODE* pAN = m_ANC.m_pFirst;
    ABSTRACT_NODE* pNextAN = NULL;
    for ( ; pAN != NULL ; pAN = pNextAN )
    {
        pNextAN = pAN->m_pNext;
        if ( VAL(pAN) == iVal )
        {
            m_ANC.RemoveNode(*pAN);
            delete (Node_KV*)pAN;
        }
    }
}


CATBoolean MAP::operator==(const MAP& iMap) const
{
    if (m_ANC.m_length != iMap.m_ANC.m_length)
        return FALSE;

    ABSTRACT_NODE* pAN = m_ANC.m_pFirst;
    for ( ; pAN != NULL ; pAN = pAN->m_pNext )
    { 
        ABSTRACT_NODE* pFoundAN = iMap.FindNode(KEY(pAN));

        if ( pFoundAN == NULL )
            return FALSE;

        if ( VAL(pFoundAN) != VAL(pAN) )
            return FALSE;
    }

    return TRUE;
}


CATBoolean MAP::operator!=(const MAP& iMap) const
{
    return !operator==(iMap);
}


