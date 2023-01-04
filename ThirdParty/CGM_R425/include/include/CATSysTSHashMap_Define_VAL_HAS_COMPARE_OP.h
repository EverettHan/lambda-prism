// CATSysTSHashMap_Define_VAL_HAS_COMPARE_OP.h



void MAP::RemoveValues(const V& iVal)
{
    ArrayListOfLinkedMapOfKeyVal::iterator itr = m_table.Begin();
    LinkedMapOfKeyVal* pLnkMap = NULL;
    while (pLnkMap = itr.GetAsPtrGoToNext())
    {
        m_length -= pLnkMap->GetLength();

        pLnkMap->RemoveValues(iVal);

        m_length += pLnkMap->GetLength();
    }
}


CATBoolean MAP::operator==(const MAP& iMap) const
{
    if (m_length != iMap.m_length)
        return FALSE;

    const_iterator itr = cBegin();
    const Entry* pEntry = NULL;
    while (pEntry = itr.GetEntryAsPtrGoToNext())
    {
        const V* pFoundValue = iMap.GetAsPtr(pEntry->m_key);

        if (pFoundValue == NULL)
            return FALSE;

        if (*pFoundValue != pEntry->m_val)
            return FALSE;
    }

    return TRUE;
}


CATBoolean MAP::operator!=(const MAP& iMap) const
{
    return !operator==(iMap);
}


