#ifndef CATCacheTransaction_h
#define CATCacheTransaction_h
/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2020
// Transaction to enable caching of calls into CATPGMTopGN_GroupCells and CATPGMTopGN_CellNeighbours methods 
// Proposed to improve pcs for IR 759133 
//==========================================================================
/*
    CATBody   *iBody;
    CATCacheTransactionBegin(marqueur,iBody) 
    {
       // ... 
    }
    CATCacheTransactionEnd(marqueur);
*/

//==========================================================================
// 
//  PERFO : 
//
//==========================================================================
//  FONCTIONNALITES  :
//
//==========================================================================
//  RESTRICTIONS: Imperative constraints on the use of this Transaction:
//
//  1) We only use the specified Body during the whole transaction,
//     all other call concerning topology of an other Body will not 
//     benefit of the optimization
//
//  2) No Transaction stacking
//
//
//==========================================================================
//
//
//==========================================================================
#include "CATGMModelInterfaces.h"
#include "CATCGMTransaction.h"
#include "CATMathInline.h"
#include "ListPOfCATConnectedCellsIterator.h"
#include "CATHashDico.h"
#include "ListVOfLong.h"

//#define USE_STL

#ifdef USE_STL
#include <map>
#include <string>
#endif

class CATLISTP(CATCell);
class CATCell;
class CATUnicodeString;
class CATBody;


//------------------------------------------------------------------
// Transaction 
//------------------------------------------------------------------
class ExportedByCATGMModelInterfaces  CATCacheTransaction : public CATCGMTransaction
{
public :
  //------------------------------------------------------------------
  // LifeCycle
  //------------------------------------------------------------------
  static CATCacheTransaction *Create(CATBody *iBody);
  virtual void Clean();

  CATCGMNewClassArrayDeclare;

  INLINE CATBody  *GetBody() const;
  
  // cache for CellNeighbours
  void LocateInCellNeighboursCache(CATBody * iBody, const CATLISTP(CATCell) * iCellList, CATLISTP(CATCell)& oCellList);
  CATBoolean InsertInCellNeighboursCache(CATBody * iBody, const CATLISTP(CATCell) * iCellList,const CATLISTP(CATCell) iResultCells);

  // cache for GroupCells
  CATBoolean InsertInGroupCellCache(CATBody * iBody, const CATLISTP(CATCell) * iCellList, CATLISTP(CATCell)& iResultCells, CATListOfLong& iNbCellByGroup);
  void LocateInGroupCellCache(CATBody * iBody, const CATLISTP(CATCell) * iCellList, CATLISTP(CATCell)& oResultCells, CATListOfLong& oNbCellByGroup);


protected:
  // Constructor
  CATCacheTransaction(CATBody *iBody);
 
  // Data
  CATBody    *_Body; // context Body
 
#ifdef USE_STL
  std::map<std::string, CATLISTP(CATCell) *> _NeighboursCache;
  std::map<std::string, std::pair<CATLISTP(CATCell) *,CATListOfLong* > > _GroupCellCache;
#else
  CATHashDico _NeighboursCache; // map for CellNeighbours cache
  CATHashDico _GroupCellCache; // map for CellNeighbours cache
#endif
};


//------------------------------------------------------------------
// Get Context Body
//------------------------------------------------------------------
INLINE CATBody  *CATCacheTransaction::GetBody() const
{
  return _Body ;
}

//------------------------------------------------------------------
// Def Macro
//------------------------------------------------------------------
#define CATCacheTransactionBegin(marqueur,iBody)  \
  CATCacheTransaction *volatile marqueur = CATCacheTransaction::Create(iBody); \
CATTry  \
{  

#define CATCacheTransactionEnd(marqueur)  \
  if ( marqueur ) { marqueur->Clean(); delete marqueur; marqueur=NULL; } \
} \
CATCatch(CATError, error) \
{  \
  if ( marqueur ) { marqueur->Clean(); delete marqueur; marqueur=NULL; } \
  CATRethrow; \
}  \
CATEndTry 


#endif

