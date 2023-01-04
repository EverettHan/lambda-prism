/* -*-c++-*- */
#ifndef CATCGMIncrementalTagAbsolutePosition_H
#define CATCGMIncrementalTagAbsolutePosition_H
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATCGMIncrementalTagAbsolutePosition:
// Data permiting to locate the stream data of an object 
// used during incremental unstream
//
//=============================================================================
// Avr. 10 Creation                                                         VUC
//=============================================================================

#include "ExportedByCATCGMFusion.h"        
#include "CATDataType.h"
#include "CATMathInline.h"

class ExportedByCATCGMFusion CATCGMIncrementalTagAbsolutePosition
{

public :

  CATCGMIncrementalTagAbsolutePosition();
  CATCGMIncrementalTagAbsolutePosition(CATULONG32 iTag,CATULONG32 iIncrementIndex,CATULONG32 iStreamIndex);
  virtual ~CATCGMIncrementalTagAbsolutePosition();
  
  INLINE void SetTag(CATULONG32 iTag);
  INLINE void SetIncrementIndex(CATULONG32 iIncrementIndex);
  INLINE void SetStreamIndex(CATULONG32 iStreamIndex);  

  INLINE CATULONG32 GetTag();
  INLINE CATULONG32 GetIncrementIndex();
  INLINE CATULONG32 GetStreamIndex();  

private :

  CATULONG32 _IncrementIndex; //index of the increment in the list/chain (starts at 1)
  CATULONG32 _Tag; //tag of the corresponding object
  CATULONG32 _StreamIndex; //index of the object in the increment

};

INLINE void CATCGMIncrementalTagAbsolutePosition::SetTag(CATULONG32 iTag)
{ _Tag = iTag;}

INLINE void CATCGMIncrementalTagAbsolutePosition::SetIncrementIndex(CATULONG32 iIncrementIndex)
{ _IncrementIndex = iIncrementIndex;}

INLINE void CATCGMIncrementalTagAbsolutePosition::SetStreamIndex(CATULONG32 iStreamIndex)
{ _StreamIndex = iStreamIndex;}

INLINE CATULONG32 CATCGMIncrementalTagAbsolutePosition::GetTag()
{ return _Tag;}

INLINE CATULONG32 CATCGMIncrementalTagAbsolutePosition::GetIncrementIndex()
{ return _IncrementIndex;}

INLINE CATULONG32 CATCGMIncrementalTagAbsolutePosition::GetStreamIndex()
{ return _StreamIndex;}

#endif 
