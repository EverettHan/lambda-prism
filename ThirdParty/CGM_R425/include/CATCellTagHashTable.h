#ifndef CATCellTagHashTable_H
#define CATCellTagHashTable_H
// COPYRIGHT DASSAULT SYSTEMES  1997
//=============================================================================
//
// CATCellTagHashTable
//
// Hash table of CATCell using the Tag for its Key
//
//=============================================================================
// Usage Notes:
//=============================================================================
// Aug. 99                                                       R. Aymard
//=============================================================================


#include "CATCellHashTable.h"
#include "YI00IMPL.h"
#define  CATHTAB_TAG(X)  X##TagHashTable

class ExportedByYI00IMPL CATCellTagHashTable
{ 
public : 
  // basics
  CATCellTagHashTable ( int iDimension = 10 ) ;
  CATCellTagHashTable ( CATHTAB(CATCell)* ) ;
  ~CATCellTagHashTable( );
  
  //  modification functions
  int      Insert(CATCell* iAdd);
  void     Insert(const CATHTAB(CATCell)& iAdd);
  CATCell* Remove(CATCell* iRemove);
  void     RemoveAll ();


  // inline const functions
  int             Size ()                   const  { return _HT.Size() ; };     
//  CATHashCodeIter CreateIterator()          const  { return _HT.CreateIterator();};
  void *        Locate (CATCell* iLocate) const  { return _HT.Locate(iLocate);};  
  CATCell*        Next   (CATCell* iFrom)   const  { return _HT.Next(iFrom );};

  // inline const operators
  CATCell*    Get ( const int iPos )   const { return _HT.Get(iPos); };  
//  int         operator== ( const CATCellTagHashTable& iH ) const { return _HT==iH._HT; };
//  int         operator!= ( const CATCellTagHashTable& iH ) const { return _HT!=iH._HT; };     

private : 
  CATHTAB(CATCell) _HT ; 

  CATCellTagHashTable (const CATCellTagHashTable& iCopy) ;
  CATCellTagHashTable&  operator= ( const CATCellTagHashTable& iCopy );
}; 



#endif
