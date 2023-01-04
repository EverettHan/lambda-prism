#ifndef CATCGMUnknown_H
#define CATCGMUnknown_H
// COPYRIGHT DASSAULT SYSTEMES 1999
/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

//==============================================================================================================================================
// Base classe for simpliest shareable object
//    (without explicit deletion but with counter management as restrictive IUnknown without associated extended behaviors)
//==============================================================================================================================================

#include "IUnknown.h"
#include "CATMathematics.h"
#include "CATMathInline.h"
#include "CATDataType.h"
#include "CATThrowForNullPointer.h"

class CATCGMOwner;

/** @nodoc */
class ExportedByCATMathematics CATCGMUnknown 
{
public :

  /** @nodoc */
  INLINE CATLONG32  GetCounter() const;

  /** @nodoc */
  virtual CATLONG32   __stdcall  AddRef (void*  iReferencing);
  /** @nodoc */
  virtual CATLONG32   __stdcall  Release(void*  iReferencing);
 
protected :

  /** @nodoc */
  CATCGMUnknown() ;
  /** @nodoc */
  virtual  ~CATCGMUnknown() ;

    /** @nodoc */
  CATCGMUnknown(const CATCGMUnknown &iCopy);
  /** @nodoc */
  CATCGMUnknown& operator=(const CATCGMUnknown &iCopy);

private :

  CATLONG32     _Counter;
};

  /** @nodoc */
INLINE   CATLONG32   CATCGMUnknown::GetCounter() const
{ return _Counter; } 
 

#endif

