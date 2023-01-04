//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 1999
//==============================================================================================================
// CATCGMBucketsDef:
// Macro to define a class to manage an array with a dynamic size with a buckets mechanism.
//==============================================================================================================
// 25-Jun-2007 - JLH - Grosse erreur dans l'opérateur = ou dans le constructeur par copie :
//                     _Shift et _Mask étaient mis à 0 et non à la valeur de iOther !
// 28-Aou-2003 - FDS - Transfert dans Mathematics ( CATCldBucket* -> CATCGMBucket* )
// 14-Nov-2002 - JLH - Nouvelle gestion memoire (appel aux services CATCGMem***).
// 17-Sep-2002 - JLH - Ajout de la methode "int Add (const int iNbItems, const TheItem* iItems)"
//                     Commentaires.
// ??-Nov-1999 - JLH - Creation
//==============================================================================================================

#ifdef CATCGMBucketsDefine
#undef CATCGMBucketsDefine
#endif

#include "CATCGMemory.h"

#define CATCGMBucketsDefine(TheUpperClass,TheName,TheItem) \
TheUpperClass::CATCGMBucketsOf##TheName::CATCGMBucketsOf##TheName () : \
  _NbItemsByBlock (0), \
  _FirstNbBlocks (0), \
  _NextNbBlocks (0), \
  _Shift (0), \
  _Mask (0), \
  _NbItems (0), \
  _NbBlocks (0), \
  _Blocks (NULL) \
{ \
} \
\
TheUpperClass::CATCGMBucketsOf##TheName::CATCGMBucketsOf##TheName (const CATCGMBucketsOf##TheName& iOther) \
{ \
  _NbItemsByBlock = iOther._NbItemsByBlock ; \
  _FirstNbBlocks  = iOther._FirstNbBlocks ; \
  _NextNbBlocks   = iOther._NextNbBlocks ; \
  _Shift    = iOther._Shift ; \
  _Mask     = iOther._Mask ; \
  _NbItems  = 0 ; \
  _NbBlocks = 0 ; \
  _Blocks   = NULL ; \
  if (iOther._NbItems > 0) { \
    _NbItems  = iOther._NbItems ; \
    _NbBlocks = iOther._NbBlocks ; \
    _Blocks   = (TheItem **) CATCGMemBook (_NbBlocks * sizeof (TheItem *)) ; \
    memset (_Blocks, 0, _NbBlocks * sizeof (TheItem *)) ; \
    unsigned int blk ; \
    for (blk = 0 ; blk < _NbBlocks ; blk++) { \
      if (iOther._Blocks[blk]) { \
        _Blocks[blk] = (TheItem *) CATCGMemBook (_NbItemsByBlock * sizeof (TheItem)) ; \
        memcpy (_Blocks[blk], iOther._Blocks[blk], _NbItemsByBlock * sizeof (TheItem)) ; \
      } \
    } \
  } \
} \
\
TheUpperClass::CATCGMBucketsOf##TheName::~CATCGMBucketsOf##TheName() \
{ \
  Free() ; \
} \
\
void TheUpperClass::CATCGMBucketsOf##TheName::operator= (const CATCGMBucketsOf##TheName& iOther) \
{ \
  Free() ; \
  _NbItemsByBlock = iOther._NbItemsByBlock ; \
  _FirstNbBlocks  = iOther._FirstNbBlocks ; \
  _NextNbBlocks   = iOther._NextNbBlocks ; \
  _Shift    = iOther._Shift ; \
  _Mask     = iOther._Mask ; \
  _NbItems  = 0 ; \
  _NbBlocks = 0 ; \
  _Blocks   = NULL ; \
  if (iOther._NbItems > 0) { \
    _NbItems  = iOther._NbItems ; \
    _NbBlocks = iOther._NbBlocks ; \
    _Blocks   = (TheItem **) CATCGMemBook (_NbBlocks * sizeof (TheItem *)) ; \
    memset (_Blocks, 0, _NbBlocks * sizeof (TheItem *)) ; \
    unsigned int blk ; \
    for (blk = 0 ; blk < _NbBlocks ; blk++) { \
      if (iOther._Blocks[blk]) { \
        _Blocks[blk] = (TheItem *) CATCGMemBook (_NbItemsByBlock * sizeof (TheItem)) ; \
        memcpy (_Blocks[blk], iOther._Blocks[blk], _NbItemsByBlock * sizeof (TheItem)) ; \
      } \
    } \
  } \
} \
\
int TheUpperClass::CATCGMBucketsOf##TheName::Add (const TheItem &iItem) \
{ \
  if (_Blocks == NULL && !Alloc()) return 0 ; \
  unsigned int NbItems = _NbItems + 1 ; \
  unsigned int blk = NumBlock (NbItems) ; \
  while (blk >= _NbBlocks) { \
    if (!ReAlloc()) return 0 ; \
  } \
  if (_Blocks[blk] == NULL) { \
    _Blocks[blk] = (TheItem *) CATCGMemBook (_NbItemsByBlock * sizeof (TheItem)) ; \
    memset (_Blocks[blk], 0, _NbItemsByBlock * sizeof (TheItem)) ; \
  } \
  unsigned int icl = NumCell (NbItems) ; \
  _Blocks[blk][icl] = iItem ; \
  _NbItems = NbItems ; \
  return ((int) _NbItems) ; \
} \
\
int TheUpperClass::CATCGMBucketsOf##TheName::Add (const int      iNbItems, \
                                                  const TheItem* iItems) \
{ \
  unsigned int NbAddedItems = (unsigned int) iNbItems ; \
  if (NbAddedItems < 1) return 0 ; \
  if (NbAddedItems == 1) return Add (iItems[0]) ; \
  CATCGMValidateRange (NbAddedItems, 1, (_NbItemsByBlock+1)) ; \
  if (_Blocks == NULL && !Alloc()) return 0 ; \
  unsigned int NbItems = _NbItems + 1 ; \
  unsigned int blk = NumBlock (NbItems) ; \
  while (blk >= _NbBlocks) { \
    if (!ReAlloc()) return 0 ; \
  } \
  unsigned int icl = NumCell (NbItems) ; \
  if (icl + NbAddedItems > _NbItemsByBlock) { \
    blk++ ; \
    while (blk >= _NbBlocks) { \
      if (!ReAlloc()) return 0 ; \
    } \
    icl = 0 ; \
    NbItems = (blk << _Shift) + 1 ; \
  } \
  if (_Blocks[blk] == NULL) { \
    _Blocks[blk] = (TheItem *) CATCGMemBook (_NbItemsByBlock * sizeof (TheItem)) ; \
    memset (_Blocks[blk], 0, _NbItemsByBlock * sizeof (TheItem)) ; \
  } \
  memcpy (_Blocks[blk]+icl, iItems, NbAddedItems * sizeof (TheItem)) ; \
  _NbItems = NbItems - 1 + NbAddedItems ; \
  return ((int) NbItems) ; \
} \
\
CATBoolean TheUpperClass::CATCGMBucketsOf##TheName::Set (const int      iNoItem, \
                                                         const TheItem &iItem) \
{ \
  unsigned int NoItem = (unsigned int) iNoItem ; \
  CATCGMValidateRange (NoItem, 1, (NoItem+1)) ; \
  if (_Blocks == NULL && !Alloc()) return FALSE ; \
  unsigned int blk = NumBlock (NoItem) ; \
  while (blk >= _NbBlocks) { \
    if (!ReAlloc()) return FALSE ; \
  } \
  if (_Blocks[blk] == NULL) { \
    _Blocks[blk] = (TheItem *) CATCGMemBook (_NbItemsByBlock * sizeof (TheItem)) ; \
    memset (_Blocks[blk], 0, _NbItemsByBlock * sizeof (TheItem)) ; \
  } \
  unsigned int icl = NumCell (NoItem) ; \
  _Blocks[blk][icl] = iItem ; \
  if (NoItem > _NbItems) _NbItems = NoItem ; \
  return TRUE ; \
} \
\
CATBoolean TheUpperClass::CATCGMBucketsOf##TheName::SetNbItems (const int iNewNbItems) \
{ \
  unsigned int NewNbItems = (unsigned int) iNewNbItems ; \
  if (NewNbItems == _NbItems) return TRUE ; \
  if (NewNbItems < 1) { \
    Free() ; \
  } else if (NewNbItems > _NbItems) { \
    unsigned int blk = NumBlock (NewNbItems) ; \
    if (_Blocks == NULL && !Alloc()) return FALSE ; \
    while (blk >= _NbBlocks) if (!ReAlloc()) return FALSE ; \
    _NbItems = NewNbItems ; \
  } else { \
    unsigned int blk = NumBlock (NewNbItems) ; \
    unsigned int NbBlocks = blk + 1 ; \
    if (NbBlocks < _NbBlocks) { \
      while (_NbBlocks > NbBlocks) { \
        _NbBlocks-- ; \
        if (_Blocks[_NbBlocks]) CATCGMemClear (_Blocks[_NbBlocks]) ; \
      } \
      TheItem** Blocks = (TheItem **) CATCGMemBook (_NbBlocks * sizeof (TheItem *)) ; \
      memcpy (Blocks, _Blocks, _NbBlocks * sizeof (TheItem *)) ; \
      CATCGMemClear (_Blocks) ; \
      _Blocks = Blocks ; \
    } \
    if (_Blocks[blk] != NULL) { \
      unsigned int DebToDel = NumCell (NewNbItems) + 1 ; \
      unsigned int NbItemsToDel = _NbItemsByBlock - DebToDel ; \
      memset (_Blocks[blk]+DebToDel, 0, NbItemsToDel * sizeof (TheItem)) ; \
    } \
    _NbItems = NewNbItems ; \
  } \
  return TRUE ; \
} \
\
CATBoolean TheUpperClass::CATCGMBucketsOf##TheName::Alloc() \
{ \
  Free() ; \
  _Blocks = (TheItem **) CATCGMemBook (_FirstNbBlocks * sizeof (TheItem *)) ; \
  memset (_Blocks, 0, _FirstNbBlocks * sizeof (TheItem *)) ; \
  _NbBlocks = _FirstNbBlocks ; \
  return TRUE ; \
} \
\
CATBoolean TheUpperClass::CATCGMBucketsOf##TheName::ReAlloc() \
{ \
  unsigned int NbBlocks = _NbBlocks + _NextNbBlocks ; \
  TheItem** Blocks = (TheItem **) CATCGMemBook (NbBlocks * sizeof (TheItem *)) ; \
  memcpy (Blocks, _Blocks, _NbBlocks * sizeof (TheItem *)) ; \
  memset (Blocks+_NbBlocks, 0, _NextNbBlocks * sizeof (TheItem *)) ; \
  CATCGMemClear (_Blocks) ; \
  _Blocks   = Blocks ; \
  _NbBlocks = NbBlocks ; \
  return TRUE ; \
} \
\
CATBoolean TheUpperClass::CATCGMBucketsOf##TheName::Free () \
{ \
  if (_Blocks != NULL) { \
    unsigned int blk = _NbBlocks ; \
    while (blk > 0) { \
      blk-- ; \
      if (_Blocks[blk]) CATCGMemClear (_Blocks[blk]) ; \
    } \
    CATCGMemClear (_Blocks) ; \
    _Blocks = NULL ; \
  } \
  _NbBlocks = 0 ; \
  _NbItems  = 0 ; \
  return TRUE ; \
}
