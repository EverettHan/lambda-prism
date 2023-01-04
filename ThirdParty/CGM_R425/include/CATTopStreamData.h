// COPYRIGHT DASSAULT SYSTEMES 2018
//=============================================================================
//
// CATTopStreamData: 
//  Replay data usefull for stream/unstream for topological operator 
//  
//  
//
//
//=============================================================================
//
// Usage notes: 
//
//
//=============================================================================
//  Jan 2018  Creation                                                   U29
//=============================================================================

#include "ListPOfCATBody.h"
#include "CATListOfCATCGMJournals.h"
#include "CATMathInline.h"
#include "ExportedByCATTopologicalObjects.h"

#ifndef CATTopStreamData_H
#define CATTopStreamData_H

class ExportedByCATTopologicalObjects CATTopStreamData
{
public:

  CATTopStreamData(short iStreamLevel, short iMaxStreamLevel);
  virtual ~CATTopStreamData();
  INLINE short GetMaxStreamLevel(){return _maxStreamLevel;}
  INLINE short GetStreamLevel()   {return _streamLevel;}

  ListPOfCATBody          _referenceBodies;
  CATListPtrCATCGMJournal _referenceJournals;

private:
  short _streamLevel;
  short _maxStreamLevel;
};
#endif
