// CATSysTSArrayList_Define_T_HAS_CUSTOM_COMP_METH.h

// implementation of CATSysTSListInterface_T_HAS_CUSTOM_COMP_METH.h

#ifndef CATSYSTS_FULL_TS
void LIST::Sort(int (*compare)(const T *, const T *))
{
  if (NULL== m_AC.m_pArray)
    return;
  qsort(m_AC.m_pArray, m_AC.m_length, m_AC.m_sizeof_T, (int (*)(const void *, const void *)) compare);
}
#endif
