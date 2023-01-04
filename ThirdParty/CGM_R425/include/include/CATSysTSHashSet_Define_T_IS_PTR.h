// CATSysTSHashSet_Define_T_IS_PTR.h

// functions that need T to be a pointer




void SET::Delete(const T& iEl)
{
    ABSTRACT_NODE* pAN = FindNode(iEl);
    
    if (pAN == NULL)
        return;

    delete EL(pAN);

    m_ANC.RemoveNode(*pAN);
    delete (Node_T*)pAN;
}


void SET::DeleteAll()
{
    ABSTRACT_NODE* pAN = m_ANC.m_pFirst;
    for ( ; pAN != NULL ; pAN = pAN->m_pNext )
        delete EL(pAN);

    Clear();
}


void SET::DeleteAllAndThis()
{
    DeleteAll();
    delete this;
}


