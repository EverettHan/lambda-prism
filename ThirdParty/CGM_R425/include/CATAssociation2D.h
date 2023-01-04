/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATAssociation2D: Data of the attribute used in CATTransformation 
//                   for 2D objects
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
#ifndef CATASSOCIATION2D_H
#define CATASSOCIATION2D_H

//Windows compatibility
#include "YP00IMPL.h"

//Inheritance library
#include "CATAssociation.h"

//Other libraries
#include "CATMathTransformation2D.h"
#include "CATCGMNewArray.h"
#include "CATMathInline.h"

class CATMathTransformation2D;
class CATMathTransformation1D;
class CATICGMObject;
class CATCrvLimits;
class CATSurLimits;

//-----------------------------------------------------------------------------
class ExportedByYP00IMPL CATAssociation2D: public CATAssociation
{
public:
  CATCGMNewClassArrayDeclare;
  //---------------------------------------------------------------------------
  //- Constructor
  //---------------------------------------------------------------------------
  CATAssociation2D(CATICGMObject*           iIn              ,
		   CATICGMObject*           iOut             ,
		   CATMathTransformation2D* iTransfo2D = NULL,  
		   CATInputType             iType = InEntry  ,
		   CATULONG32             iCount = 0       ) ;

  //---------------------------------------------------------------------------
  //- Destructor
  //---------------------------------------------------------------------------
  ~CATAssociation2D();

  //---------------------------------------------------------------------------
  //- GetTransfoUV: returns the 2D Transformation
  //---------------------------------------------------------------------------
  INLINE void GetTransfoUV(CATMathTransformation2D* &oTransfo2D) const;

  //---------------------------------------------------------------------------
  //-SetTransfoUV: changes TransfoUV
  //---------------------------------------------------------------------------
  virtual void SetTransfoUV(CATMathTransformation2D & iTransfo2D);

  //---------------------------------------------------------------------------
  //-GetBoxUV: returns the BoxUV
  //---------------------------------------------------------------------------
  INLINE void GetBoxUV(CATSurLimits * &oBox) const;

  //---------------------------------------------------------------------------
  //-AddToBoxUV: Add iBox or iParam to _BoxUV
  //---------------------------------------------------------------------------
  virtual void AddToBoxUV(CATSurLimits & iBox);
  virtual void AddToBoxUV(CATSurParam  & iParam);

  //---------------------------------------------------------------------------
  //-Reset output data
  //---------------------------------------------------------------------------
  virtual void Reset(CATResetType iType = CATTransfoManager_ResetStd);

private:
  CATMathTransformation2D * _Transfo2D; 
  CATSurLimits            * _BoxUV;
};
//-----------------------------------------------------------------------------
//                               INLINE
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
INLINE void CATAssociation2D::GetTransfoUV(CATMathTransformation2D* &oTransfo2D) const
//-----------------------------------------------------------------------------
{
  oTransfo2D = _Transfo2D ;
}
//-----------------------------------------------------------------------------
INLINE void CATAssociation2D::GetBoxUV(CATSurLimits * &oBox) const
//-----------------------------------------------------------------------------
{
  oBox = _BoxUV;
}
#endif
