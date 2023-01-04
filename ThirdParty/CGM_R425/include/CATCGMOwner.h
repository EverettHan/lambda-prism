#ifndef CATCGMOwner_H
#define CATCGMOwner_H
// COPYRIGHT DASSAULT SYSTEMES 1999
/** @CAA2Required */
/*---------------------------------------------------------------------*/
/* DON'T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS  */
/* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPPEAR AT ANY TIME */
/*---------------------------------------------------------------------*/
/** @nodoc */

//====================================================================================
// Base classe for ownership (containment) of exclusive objects 
//====================================================================================
#include "CATCGMExclusive.h"
#include "CATBoolean.h"


/** @nodoc */
class ExportedByCATMathematics CATCGMOwner : public CATCGMExclusive
{
protected :

  /** @nodoc */
  CATCGMOwner() ;

  /** @nodoc */
  virtual  ~CATCGMOwner() ;

#if defined ( CATIACGMR215CAA )
  /** @nodoc */
  INLINE CATBoolean HasContents() const;
 
  /** @nodoc */
   CATCGMExclusive * SearchByMeta( void * iMeta);
#endif
 

private :

#if defined ( CATIACGMR215CAA )
  /** @nodoc */
  void ClearAllContents();
#endif

  CATCGMExclusive *_FirstInside;
  int              _AliveInside;

  /** @nodoc */
  CATCGMOwner(const CATCGMOwner &iCopy);

  /** @nodoc */
  CATCGMOwner& operator=(const CATCGMOwner &iCopy);

  friend class CATCGMExclusive;

};


#if defined ( CATIACGMR215CAA )
/** @nodoc */
INLINE CATBoolean CATCGMOwner::HasContents() const 
{ return _FirstInside ? TRUE : FALSE; } 
#endif


#endif

