//=================================================================================
// Copyright Dassault Systemes Provence 2008, All Rights Reserved 
//=================================================================================
//
// Data of CGM implementation for the CATSubdivCellSurface object
//
//=============================================================================
// Usage notes:
//
// Strictement réservé aux implémentations CGM.
//=============================================================================
//=============================================================================
// HISTORIQUE :
//
// 24/01/2008 : RNO : Creation !! 
//============================================================================= 
#ifndef CATSapSurParam_H
#define CATSapSurParam_H

#include "CATDataType.h"
#include "CATSapApprox.h"

#include "CATMathInline.h"
//-----------------------------------------------------------------------------
class ExportedByCATSapApprox CATSapSurParam
{
public:
  //INLINE CATSapSurParam(double U, double V):_U(U),_V(V){};
  INLINE CATSapSurParam();
  INLINE CATSapSurParam(const CATLONG32 iPatchNumberU, const double iLocalParamU,
              const CATLONG32 iPatchNumberV, const double iLocalParamV);
  INLINE void SetLocal (const CATLONG32 iPatchNumberU, const double iLocalParamU,
              const CATLONG32 iPatchNumberV, const double iLocalParamV);
  INLINE ~CATSapSurParam(){};
  INLINE CATLONG32 GetPatchNumberU () const;
  INLINE CATLONG32 GetPatchNumberV () const;
  INLINE double GetLocalParamU () const;
  INLINE double GetLocalParamV () const;

  INLINE void SetLocalUVParam(const double iNewU, const double iNewV);

private :
  CATLONG32 _PatchU,
            _PatchV;
  double _LocalU,
         _LocalV;
//  double _U,_V;
};
//=============================================================================
// INLINE IMPLEMENTATIONS
//=============================================================================
CATSapSurParam::CATSapSurParam()
:
_PatchU(1),
_LocalU(0),
_PatchV(1),
_LocalV(0)
//_IsLocal(1)
{
}

CATSapSurParam::CATSapSurParam(const CATLONG32 iPatchNumberU, const double iLocalParamU,
              const CATLONG32 iPatchNumberV, const double iLocalParamV)
              :
_PatchU(iPatchNumberU),
_LocalU(iLocalParamU),
_PatchV(iPatchNumberV),
_LocalV(iLocalParamV)
//_IsLocal(1)
{
}
void CATSapSurParam::SetLocal (const CATLONG32 iPatchNumberU, const double iLocalParamU,
              const CATLONG32 iPatchNumberV, const double iLocalParamV)
{
//  _IsLocal=1;
  _PatchU=iPatchNumberU;
  _LocalU=iLocalParamU;
  _PatchV=iPatchNumberV;
  _LocalV=iLocalParamV;
}
INLINE CATLONG32 CATSapSurParam::GetPatchNumberU () const
{
  return _PatchU;
}

INLINE CATLONG32 CATSapSurParam::GetPatchNumberV () const
{
  return _PatchV;
}

INLINE double CATSapSurParam::GetLocalParamU () const
{
  return _LocalU;
}

INLINE double CATSapSurParam::GetLocalParamV () const
{
  return _LocalV;
}

INLINE void CATSapSurParam::SetLocalUVParam(const double iNewU, const double iNewV)
{
  _LocalU=iNewU;
  _LocalV=iNewV;
}

#endif
