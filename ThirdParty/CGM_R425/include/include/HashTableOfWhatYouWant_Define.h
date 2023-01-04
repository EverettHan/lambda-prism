
unsigned int WHAT_I_WANT_AS_HASH_FUNCTION_NAME(void * ipElem)
{
  unsigned int Val = 0;

  WHAT_I_WANT_AS_STRUCT_NAME * pElem = (WHAT_I_WANT_AS_STRUCT_NAME *) ipElem;
  if (pElem != NULL)
  {
    CATListPV List;
    pElem->GetDeterminingPointers(List);
    int iList, nbList(List.Size());
    for (iList = 1; iList <= nbList; iList++)
      Val += CATCGMHashTableBase::HashKeyFunction(List[iList]);
    List.RemoveAll();
  }

  return Val;
}

int WHAT_I_WANT_AS_COMPARE_FUNCTION_NAME(void* ipElem1, void* ipElem2)
{
  WHAT_I_WANT_AS_STRUCT_NAME * pElem1 = (WHAT_I_WANT_AS_STRUCT_NAME *) ipElem1;
  WHAT_I_WANT_AS_STRUCT_NAME * pElem2 = (WHAT_I_WANT_AS_STRUCT_NAME *) ipElem2;

  return ( ( (pElem1 != NULL)
          && (pElem2 != NULL)
          && ((*pElem1) == (*pElem2)) ) ? 0 : 1 );
}

WHAT_I_WANT_AS_HASH_TABLE_NAME::~WHAT_I_WANT_AS_HASH_TABLE_NAME()
{
  int I, N(_RealHT.Size());
  for (I = 0; I < N; I++)
  {
    WHAT_I_WANT_AS_STRUCT_NAME * pElem = (WHAT_I_WANT_AS_STRUCT_NAME *)_RealHT.Get(I);
    delete pElem;
  }
  _RealHT.RemoveAll();
}

WHAT_I_WANT_AS_STRUCT_NAME * WHAT_I_WANT_AS_HASH_TABLE_NAME::Insert(WHAT_I_WANT_TO_LOCATE)
{
  int Val = 0;

  WHAT_I_WANT_AS_STRUCT_NAME * pElem = new WHAT_I_WANT_AS_STRUCT_NAME(WHAT_I_WANT_TO_LOCATE_SHORT);
  if (pElem != NULL)
  {
    Val = _RealHT.Insert(pElem);
    if (Val == 1)
    {
    }
    else
    {
      delete pElem;
      pElem = NULL;
    }
  }

  return pElem;
}

WHAT_I_WANT_AS_STRUCT_NAME * WHAT_I_WANT_AS_HASH_TABLE_NAME::LocateOrInsert(WHAT_I_WANT_TO_LOCATE)
{
  WHAT_I_WANT_AS_STRUCT_NAME * Result = this->Locate(WHAT_I_WANT_TO_LOCATE_SHORT);

  if (!Result)
  {
    Result = this->Insert(WHAT_I_WANT_TO_LOCATE_SHORT);
  }

  return Result;
}

int WHAT_I_WANT_AS_HASH_TABLE_NAME::Remove(WHAT_I_WANT_TO_LOCATE)
{
  int Val = 0;

  WHAT_I_WANT_AS_STRUCT_NAME Elem(WHAT_I_WANT_TO_LOCATE_SHORT);

  WHAT_I_WANT_AS_STRUCT_NAME ** ppElem = (WHAT_I_WANT_AS_STRUCT_NAME **) _RealHT.Locate(&Elem);

  if (ppElem != NULL)
  {
    WHAT_I_WANT_AS_STRUCT_NAME * pElem = *ppElem;

    if (pElem != NULL)
    {
      Val = _RealHT.Remove(pElem);
      delete pElem;
      pElem = NULL;
    }
  }

  return Val;
}

WHAT_I_WANT_AS_STRUCT_NAME * WHAT_I_WANT_AS_HASH_TABLE_NAME::Get(int iPos) const
{
  return (WHAT_I_WANT_AS_STRUCT_NAME *) _RealHT.Get(iPos);
}

void WHAT_I_WANT_AS_HASH_TABLE_NAME::RemoveAll()
{
  int iTable, nbTable(_RealHT.Size());
  for (iTable = 0; iTable < nbTable; iTable++)
  {
    WHAT_I_WANT_AS_STRUCT_NAME * pElem = (WHAT_I_WANT_AS_STRUCT_NAME *) _RealHT.Get(iTable);
    if (pElem != NULL)
    {
      delete pElem;
      pElem = NULL;
    }
  }

  _RealHT.RemoveAll();

  return;
}

