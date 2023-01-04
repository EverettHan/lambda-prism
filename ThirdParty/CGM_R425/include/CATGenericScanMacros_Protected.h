#ifndef CATGenericScanMacros_Protected_h
#define CATGenericScanMacros_Protected_h

#include "CATDataType.h"

//*******************************************************************************************
// Creation                                                                     LD2
// Remotee en protected                                               RLA
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
// CATForListPBegin(ListToScan, CurrentElement, Type *)
// {
//   CurrentElement->...
// } CATForListPEnd;
//*******************************************************************************************


#define CATForListPBegin(LIST, CURRVALUE, TYPE)                                               \
{                                                                                             \
  int __Idex##CURRVALUE, __Nmbr##CURRVALUE((LIST).Size());                                    \
  for (__Idex##CURRVALUE = 1; __Idex##CURRVALUE <= __Nmbr##CURRVALUE; __Idex##CURRVALUE++)    \
  {                                                                                           \
    TYPE CURRVALUE = (LIST)[__Idex##CURRVALUE];                                               \
    if (CURRVALUE)                                                                            \
    {

//*******************************************************************************************

#define CATForListPInverseBegin(LIST, CURRVALUE, TYPE)                                        \
{                                                                                             \
  int __Idex##CURRVALUE, __Nmbr##CURRVALUE((LIST).Size());                                    \
  for (__Idex##CURRVALUE = __Nmbr##CURRVALUE; __Idex##CURRVALUE >= 1; __Idex##CURRVALUE--)    \
  {                                                                                           \
    TYPE CURRVALUE = (LIST)[__Idex##CURRVALUE];                                               \
    if (CURRVALUE)                                                                            \
    {

//*******************************************************************************************

#define CATForListPCastBegin(LIST, CURRVALUE, TYPE)                                           \
{                                                                                             \
  int __Idex##CURRVALUE, __Nmbr##CURRVALUE((LIST).Size());                                    \
  for (__Idex##CURRVALUE = 1; __Idex##CURRVALUE <= __Nmbr##CURRVALUE; __Idex##CURRVALUE++)    \
  {                                                                                           \
    TYPE CURRVALUE = (TYPE)((LIST)[__Idex##CURRVALUE]);                                       \
    if (CURRVALUE)                                                                            \
    {

//*******************************************************************************************

#define CATForListPEnd        \
    }                         \
  }                           \
}

//*******************************************************************************************

#define CATForListVBegin(LIST, CURRVALUE, TYPE)                                               \
{                                                                                             \
  int __Idex##CURRVALUE, __Nmbr##CURRVALUE((LIST).Size());                                    \
  for (__Idex##CURRVALUE = 1; __Idex##CURRVALUE <= __Nmbr##CURRVALUE; __Idex##CURRVALUE++)    \
  {                                                                                           \
    TYPE CURRVALUE = (LIST)[__Idex##CURRVALUE];                                               //

//*******************************************************************************************
   
#define CATForListVEnd       \
  }                          \
}                            //

//*******************************************************************************************

#define DeleteElementsInList(List, ElementType) \
CATForListPCastBegin (List, Element, ElementType) \
{ \
  if (Element) delete Element; \
} CATForListPEnd; \
(List).RemoveAll();

//*******************************************************************************************

template <class LISTTYPE, class TABLETYPE>
void FromListToTable(LISTTYPE & iList, TABLETYPE & oTable)
{
  int I, N(iList.Size());
  for (I = 1; I <= N; I++)
  {
    void * Curr = iList[I];
    oTable.Insert(Curr);
  }
}

//*******************************************************************************************

template <class LISTTYPE, class TABLETYPE>
void FromArrayToTable(LISTTYPE & iList, TABLETYPE & oTable)
{
  CATLONG32 I, N(iList.GetCount());
  for (I = 0; I < N; I++)
  {
    void * Curr = iList[I];
    oTable.Insert(Curr);
  }
}
//*******************************************************************************************

#define CATForIntListBegin(LIST, CURRVALUE)                                                       \
{                                                                                                 \
  int __Idex##CURRVALUE, __Nmbr##CURRVALUE((LIST).Size());                                        \
  for (__Idex##CURRVALUE = 1; __Idex##CURRVALUE <= __Nmbr##CURRVALUE; __Idex##CURRVALUE++)        \
  {                                                                                               \
    int CURRVALUE = (LIST)[__Idex##CURRVALUE];

//*******************************************************************************************

#define CATForIntListEnd        \
  }                          \
}

//*******************************************************************************************

#define CATForIndex(CURRVALUE) __Idex##CURRVALUE

//*******************************************************************************************

#define CATForIsLast(CURRVALUE) (__Idex##CURRVALUE == __Nmbr##CURRVALUE)

//*******************************************************************************************

#endif
