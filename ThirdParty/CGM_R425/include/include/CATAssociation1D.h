/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATAssociation1D: Data of the attribute used in CATTransformation 
//                   for 1D objects
// 
//=============================================================================
// Usage notes:
//
// 
// 
//
//=============================================================================
// Abstract Class     : No
// Inline Functions   : No
//=============================================================================
// Oct. 97   Creation                                 ILY (I. Levy)
//=============================================================================
#ifndef CATASSOCIATION1D_H
#define CATASSOCIATION1D_H

//Windows compatibility
#include "YP00IMPL.h"

//Inheritance library
#include "CATAssociation.h"

//Other libraries
#include "CATMathTransformation1D.h"
#include "CATCGMNewArray.h"
#include "CATMathInline.h"

class CATMathTransformation1D;
class CATMathTransformation2D;
class CATICGMObject;
class CATCrvLimits;
class CATSurLimits;

//-----------------------------------------------------------------------------
class ExportedByYP00IMPL CATAssociation1D: public CATAssociation
{
public:
  CATCGMNewClassArrayDeclare;
  //---------------------------------------------------------------------------
  //- Constructor
  //---------------------------------------------------------------------------
  CATAssociation1D(CATICGMObject*           iIn              ,
		   CATICGMObject*           iOut             ,
		   CATMathTransformation1D* iTransfo1D = NULL,
		   CATInputType             iType = InEntry  ,
		   CATULONG32             iCount = 0       ) ;
 
  //---------------------------------------------------------------------------
  //- Destructor
  //---------------------------------------------------------------------------
  ~CATAssociation1D();

  //---------------------------------------------------------------------------
  //- GetTransfoW: returns the 1D Transformation
  //---------------------------------------------------------------------------
  INLINE void GetTransfoW(CATMathTransformation1D* &oTransfo1D) const;

  //---------------------------------------------------------------------------
  //-SetTransfoW: changes TransfoW
  //---------------------------------------------------------------------------
  virtual void SetTransfoW(CATMathTransformation1D & iTransfo1D);

  //---------------------------------------------------------------------------
  //-GetBoxW: returns the BoxW
  //---------------------------------------------------------------------------
  INLINE void GetBoxW(CATCrvLimits * &oBox) const;

  //---------------------------------------------------------------------------
  //-AddToBoxW: Add iBox or iParam to _BoxW
  //---------------------------------------------------------------------------
  virtual void AddToBoxW(CATCrvLimits & iBox);
  virtual void AddToBoxW(CATCrvParam  & iParam);

  //---------------------------------------------------------------------------
  //-Reset output data
  //---------------------------------------------------------------------------
  virtual void Reset(CATResetType iType = CATTransfoManager_ResetStd);

private:
  CATMathTransformation1D * _Transfo1D;
  CATCrvLimits            * _BoxW; 
};
//-----------------------------------------------------------------------------
//                                INLINE
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
INLINE void CATAssociation1D::GetBoxW(CATCrvLimits * &oBox) const
//-----------------------------------------------------------------------------
{
  oBox = _BoxW;
}
//-----------------------------------------------------------------------------
INLINE void CATAssociation1D::GetTransfoW(CATMathTransformation1D* &oTransfo1D) const
//-----------------------------------------------------------------------------
{
  oTransfo1D = _Transfo1D ;  
}
#endif
