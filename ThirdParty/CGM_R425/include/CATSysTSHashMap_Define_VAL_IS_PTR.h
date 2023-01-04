// CATSysTSHashMap_Define_VAL_IS_PTR.h


void MAP::Delete(const CATSYSTS_KEY_DECL_IN_CTNR& iKey)
{
    LinkedMapOfKeyVal& lnkMap = GetLinkedMap(iKey);
    m_length -= lnkMap.GetLength();

    lnkMap.Delete(iKey);

    m_length += lnkMap.GetLength();
}


void MAP::DeleteAll()
{
    ArrayListOfLinkedMapOfKeyVal::iterator itr = m_table.Begin();
    LinkedMapOfKeyVal* pLnkMap = NULL;
    while (pLnkMap = itr.GetAsPtrGoToNext())
        pLnkMap->DeleteAll();

    m_length = 0;
}


void MAP::DeleteAllAndThis()
{
    DeleteAll();
    delete this;
}


