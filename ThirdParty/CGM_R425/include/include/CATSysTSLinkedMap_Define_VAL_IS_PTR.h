// CATSysTSLinkedMap_Define_VAL_IS_PTR.h


void MAP::Delete(const CATSYSTS_KEY_DECL_IN_CTNR& iKey)
{
    ABSTRACT_NODE* pAN = FindNode(iKey);

    if (pAN == NULL)
        return;

    delete VAL(pAN);

    m_ANC.RemoveNode(*pAN);
    delete (Node_KV*)pAN;
}


void MAP::DeleteAll()
{
    ABSTRACT_NODE* pAN = m_ANC.m_pFirst;
    for ( ; pAN != NULL ; pAN = pAN->m_pNext )
        delete VAL(pAN);

    Clear();
}


void MAP::DeleteAllAndThis()
{
    DeleteAll();
    delete this;
}



