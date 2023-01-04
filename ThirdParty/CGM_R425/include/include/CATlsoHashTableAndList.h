// COPYRIGHT DASSAULT SYSTEMES 2014, ALL RIGHTS RESERVED.
//=============================================================================
//
// RESPONSIBLE  : LAP 
//
// DESCRIPTION  : Macro design for CATCGMHashTable and List.
//
//=============================================================================
// Creation LAP September 2014
//
//=============================================================================

// ----------------------------------------------------------------------------
// @nocgmitf
#define LSO_APPENDHTABTOCELLHTAB(oTargetHTab, iSourceHTab) { \
  int iElement = 0; \
  int nbElements = iSourceHTab.Size(); \
  for(iElement = 0; iElement < iSourceHTab.Size(); iElement++) \
  { \
    oTargetHTab.Insert((CATCell*)iSourceHTab.Get(iElement)); \
  } \
}

// ----------------------------------------------------------------------------
// @nocgmitf
#define LSO_APPENDHTABTOHTAB(oTargetHTab, iSourceHTab) { \
  int iElement = 0; \
  int nbElements = iSourceHTab.Size(); \
  for(iElement = 0; iElement < iSourceHTab.Size(); iElement++) \
  { \
    oTargetHTab.Insert(iSourceHTab.Get(iElement)); \
  } \
}

// ----------------------------------------------------------------------------
// @nocgmitf
#define LSO_REMOVEHTABTOHTAB(oTargetHTab, iSourceHTab) { \
  int iElement = 0; \
  int nbElements = iSourceHTab.Size(); \
  for(iElement = 0; iElement < iSourceHTab.Size(); iElement++) \
  { \
    oTargetHTab.CATCGMHashTable::Remove(iSourceHTab.Get(iElement)); \
  } \
}

// ----------------------------------------------------------------------------
// LAP Perfo: a rajouter mais Resize n'est pas toujours actif ?
//  TargetList.Resize(nbElements); \
// @nocgmitf
#define LSO_APPENDHTABTOLIST(oTargetList, iSourceHTab, ConversionFunction) { \
  int iElement = 0; \
  int nbElements = iSourceHTab.Size(); \
  for(iElement = 0; iElement < iSourceHTab.Size(); iElement++) \
  { \
    oTargetList.Append(ConversionFunction(iSourceHTab.Get(iElement))); \
  } \
}

// ----------------------------------------------------------------------------
// @nocgmitf
#define LSO_APPENDLISTTOHTAB(oTargetHTab, iSourceList) { \
  int iElement = 0; \
  int nbElements = iSourceList.Size(); \
  for(iElement = 1; iElement <= nbElements; iElement++) \
  { \
     oTargetHTab.Insert(iSourceList[iElement]); \
  } \
}

// ----------------------------------------------------------------------------
// To avoid collision in HTab, keep one thirds empty.
// @nocgmitf
#define LSO_CREATEHTABFROMLIST(oTargetHTab, iSourceList)    \
CATCGMHashTable oTargetHTab(iSourceList.Size() + iSourceList.Size()/2); \
{                                                           \
  int iElement = 0;                                         \
  int nbElements = iSourceList.Size();                      \
  for(iElement = 1; iElement <= nbElements; iElement++)     \
  {                                                         \
     oTargetHTab.Insert(iSourceList[iElement]);             \
  }                                                         \
}


// ----------------------------------------------------------------------------
// @nocgmitf
#define LSO_REMOVELISTTOHTAB(oTargetHTab, iSourceList) { \
  int iElement = 0; \
  int nbElements = iSourceList.Size(); \
  for(iElement = 1; iElement <= nbElements; iElement++) \
  { \
     oTargetHTab.Remove(iSourceList[iElement]); \
  } \
}
// ----------------------------------------------------------------------------
// @nocgmitf
#define LSO_REMOVEHTABTOLIST(oTargetList, iSourceHTab,ConversionFunction) { \
  int iElement = 0; \
  int nbElements = iSourceHTab.Size(); \
  for(iElement = 0; iElement < nbElements; iElement++) \
  { \
     oTargetList.RemoveValue(ConversionFunction(iSourceHTab.Get(iElement))); \
  } \
}

// ----------------------------------------------------------------------------
// @nocgmitf
#define LSO_INTERSECTIONLISTFORMHTABANDLIST(iSourceHTab, iSourceList, oCommonList) { \
  int iElement = 0; \
  int nbElements = iSourceList.Size(); \
  for(iElement = 1; iElement <= nbElements; iElement++) \
  { \
     if (iSourceHTab.Locate(iSourceList[iElement])) \
       oCommonList.Append(iSourceList[iElement]); \
  } \
}

// ----------------------------------------------------------------------------
// @nocgmitf
#define LSO_INTERSECTIONHTABFORMHTABANDHTAB(iSource1HTab, iSource2HTab, oCommonHTab) { \
  int iElement = 0; \
  int nbElements = iSource2HTab.Size(); \
  for(iElement = 0; iElement < nbElements; iElement++) \
  { \
     if (iSource1HTab.Locate(iSource2HTab.Get(iElement))) \
       oCommonHTab.Insert(iSource2HTab.Get(iElement)); \
  } \
}
