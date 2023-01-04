// CATSysTSLinkedList_Define_T_IS_PTR.h

// functions that need T to be a pointer




HRESULT LIST::Delete(int iIndex)
{
    ABSTRACT_NODE* pAN = m_ANC.GetNode(iIndex);
    if (pAN == NULL)
        return E_FAIL;

    delete EL(pAN);

    m_ANC.RemoveNode(*pAN);
    delete (Node_T*)pAN;

    return S_OK;
}


void LIST::DeleteAll()
{
    ABSTRACT_NODE* pAN = m_ANC.m_pFirst;
    for ( ; pAN != NULL ; pAN = pAN->m_pNext )
        delete EL(pAN);

    Clear();
}


void LIST::DeleteAllAndThis()
{
    DeleteAll();
    delete this;
}


HRESULT LIST::iterator::DeleteGoToNext()
{
    ABSTRACT_NODE* pAN = m_pAN;
    if (pAN == NULL || m_pList == NULL)
        return E_FAIL;

    delete EL(pAN);

    m_pAN = m_pList->m_ANC.RemoveNodeGetNext(*pAN);
    delete (Node_T*)pAN;

    ++m_index;

    return S_OK;
}


HRESULT LIST::iterator::DeleteGoToPrev()
{
    ABSTRACT_NODE* pAN = m_pAN;
    if (pAN == NULL || m_pList == NULL)
        return E_FAIL;

    delete EL(pAN);

    m_pAN = m_pList->m_ANC.RemoveNodeGetPrev(*pAN);
    delete (Node_T*)pAN;

    --m_index;

    return S_OK;
}





