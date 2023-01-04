#ifndef CATCGMExclusive_H
#define CATCGMExclusive_H
// COPYRIGHT DASSAULT SYSTEMES 1999
/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

//====================================================================================
// Base classe for object which can be aggregated with at most one ownership (modelisation)
//====================================================================================
#include "CATIACGMLevel.h"
#include "CATCGMUnknown.h"
 
class CATCGMOwner;

/** @nodoc */
class ExportedByCATMathematics CATCGMExclusive  : public CATCGMUnknown 
{
public :
 

  /** @nodoc */
  void                SetOwner(CATCGMOwner *iOwner);
  /** @nodoc */
  INLINE CATCGMOwner *GetOwner() const;

#if defined ( CATIACGMR215CAA )
  /** @nodoc */
  virtual  void * GetMeta();
#endif


protected :

  /** @nodoc */
  CATCGMExclusive() ;
  /** @nodoc */
  virtual  ~CATCGMExclusive() ;


private :

  /** @nodoc */
  CATCGMExclusive(const CATCGMExclusive &iCopy);
  /** @nodoc */
  CATCGMExclusive& operator=(const CATCGMExclusive &iCopy);
 
  CATCGMOwner      * const _Owner;
  CATCGMExclusive  *       _NextInside;
  CATCGMExclusive  *       _PrevInside;

  friend class CATCGMOwner;
};

 
/** @nodoc */
INLINE  CATCGMOwner *CATCGMExclusive::GetOwner() const 
{ return _Owner; } 

#endif

