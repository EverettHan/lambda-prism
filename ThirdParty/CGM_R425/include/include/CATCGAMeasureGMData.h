#ifndef CATCGAMeasureGMData_H
#define CATCGAMeasureGMData_H
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2008
/** @CAA2Required */
/**
* @level Private
* @usage U1
*
*    For general solution concerning GM diagnostic inside an applicative product
*       with some major PCS criteria as memory (working set , virtual size)
* 
*    This Multiple purpose analysis can be extended,
*      this support is tightly linked with some reccurent CoreDump incident
*         misunderstood concerning  origin of memory consumption
*         badly managed when request of allocations begin to fail
* 
*    Meaningfull report avec provided with activation of following environement variable
*         CATCGAMeasure=Home=E:\tmp,PCS   (Cache option should be omitted)
*/
//------------------------------------------------------------ 
// area(s) of data
//------------------------------------------------------------ 
#include "CATDataType.h"
#include "CATUnicodeString.h"
#include "CATMathInline.h"
#include "CATCGMKernel.h"

// Stack Node
class ExportedByCATCGMKernel CATCGAMeasureGMData
{
public :


  CATLONG64              _GMLeanDifferentialWorkingSet; // CATIfWePurgeNonPersistent
  CATULONG64             _GMObjectCreations;
  CATULONG64             _GMObjectDeletions;
  CATULONG64             _GMLeanObjects; // CATIfWePurgeNonPersistent
  CATULONG64             _GMLockedObjects; // CATIfWePurgeNonPersistent
  CATULONG64             _DeepGMObjectCreations;
  CATULONG64             _DeepGMObjectDeletions;

  INLINE CATCGAMeasureGMData() 
  { 
    _GMLeanDifferentialWorkingSet = 0;
	  _GMObjectCreations = 0;
	  _GMObjectDeletions = 0;
	  _GMLeanObjects = 0;
	  _GMLockedObjects = 0;
    _DeepGMObjectCreations = 0;
  	_DeepGMObjectDeletions = 0;
  }

  INLINE ~CATCGAMeasureGMData()
  { 
    _GMLeanDifferentialWorkingSet = 0;
	  _GMObjectCreations = 0;
	  _GMObjectDeletions = 0;
	  _GMLeanObjects = 0;
	  _GMLockedObjects = 0;
    _DeepGMObjectCreations = 0;
  	_DeepGMObjectDeletions = 0;
  }

  INLINE void Reset()
  { 
    _GMLeanDifferentialWorkingSet = 0;
	  _GMObjectCreations = 0;
	  _GMObjectDeletions = 0;
	  _GMLeanObjects = 0;
	  _GMLockedObjects = 0;
    _DeepGMObjectCreations = 0;
  	_DeepGMObjectDeletions = 0;
  }

  INLINE CATCGAMeasureGMData(const CATCGAMeasureGMData &iCopy);
  INLINE CATCGAMeasureGMData& operator=(const CATCGAMeasureGMData &iCopy);

  INLINE void  AddMeasure(CATCGAMeasureGMData & iMeasure );
};

 
/** --------------------------------------------------------------------------------
* Constructor by Copie
* -------------------------------------------------------------------------------- **/
INLINE CATCGAMeasureGMData::CATCGAMeasureGMData(const CATCGAMeasureGMData &iOther) 
{
  _GMLeanDifferentialWorkingSet = iOther._GMLeanDifferentialWorkingSet;
  _GMObjectCreations   = iOther._GMObjectCreations;
  _GMObjectDeletions   = iOther._GMObjectDeletions;
  _GMLeanObjects       = iOther._GMLeanObjects;
  _GMLockedObjects         = iOther._GMLockedObjects;
  _DeepGMObjectCreations   = iOther._DeepGMObjectCreations;
  _DeepGMObjectDeletions   = iOther._DeepGMObjectDeletions;
}
 
/** --------------------------------------------------------------------------------
* Constructor by Copie
* -------------------------------------------------------------------------------- **/
INLINE CATCGAMeasureGMData& CATCGAMeasureGMData::operator=(const CATCGAMeasureGMData &iOther)
{
  if (&iOther == this)  return *this;

  _GMLeanDifferentialWorkingSet = iOther._GMLeanDifferentialWorkingSet;
  _GMObjectCreations   = iOther._GMObjectCreations;
  _GMObjectDeletions   = iOther._GMObjectDeletions;
  _GMLeanObjects       = iOther._GMLeanObjects;
  _GMLockedObjects         = iOther._GMLockedObjects;
  _DeepGMObjectCreations   = iOther._DeepGMObjectCreations;
  _DeepGMObjectDeletions   = iOther._DeepGMObjectDeletions;

  return *this;
}

/**
* AddMeasure 
*/
INLINE  void  CATCGAMeasureGMData::AddMeasure(CATCGAMeasureGMData & iMeasure ) 
{
  _GMLeanDifferentialWorkingSet += iMeasure._GMLeanDifferentialWorkingSet;
  _GMObjectCreations   += iMeasure._GMObjectCreations;
  _GMObjectDeletions   += iMeasure._GMObjectDeletions;
  _GMLeanObjects       += iMeasure._GMLeanObjects;
  _GMLockedObjects         += iMeasure._GMLockedObjects;
  _DeepGMObjectCreations   += iMeasure._DeepGMObjectCreations;
  _DeepGMObjectDeletions   += iMeasure._DeepGMObjectDeletions;
}

#endif
