// COPYRIGHT DASSAULT SYSTEMES 2001
//==========================================================================
// CATLocalizer2DFrom3D
//==========================================================================
// Usage notes:
//==========================================================================
// 03/10/17 NLD Detabulation et mise au propre
//              la methode WhatSupportOfCurve V2 devient comme les autres virtuelle pure
//              Ajout GetFaces() et GetPCurves()
//   /06/05 HLN mkchecksource (MINC)
//   /03/01 PRG
//               interface of topological utilities developped for the needs of
//               the cleancrv operator.
//               The implementation of this object will be in BasicTopologicalOperators,
//               where it will be instanciated. This object will be transmitted to the
//               freeform operator as an interface. Hence it will be used thanks
//               to a call-back system. This special used has been especially required.
//========================================================================== 
#ifndef CATLocalizer2DFrom3D_H
#define CATLocalizer2DFrom3D_H

#include "CATCGMVirtual.h"
#include "CATDataType.h"
#include "CATSurParam.h"
#include "CATMathPoint.h"
#include "CATGMOperatorsInterfaces.h"

#include "ListPOfCATCell.h"
#include "CATListOfCATCurves.h"
#include "CATListOfCATPCurves.h"


class CATPCurve;
class CATCrvLimits;
//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATLocalizer2DFrom3D : public CATCGMVirtual
{
  public :
  //-------------------  Destructor ---------------------------
  virtual ~CATLocalizer2DFrom3D();

  //-------------------  Other Methods ------------------------ 
  // Deprecated do not use anymore
  virtual CATLONG32 WhatSupportOfCurve          (const CATPCurve   * iPCurve       ,
                                                       CATLONG32   & ioSupportIndex) = 0;



  virtual CATLONG32 ProjPoint3DOnSupportBoundary(const CATMathPoint& i3DPoint      ,
                                                       CATLONG32     iSupport1Index,
                                                       CATLONG32     iSupport2Index,
                                                       CATSurParam & ioSurParam1   ,
                                                       CATSurParam & ioSurParam2   ) = 0;

  virtual CATLONG32 ProjPoint3DOnSupport        (const CATMathPoint& i3DPoint      ,
                                                       CATLONG32     iSupportIndex ,
                                                       CATSurParam & ioSurParam    ) = 0;

  virtual CATLONG32 WhatSupportOfCurve          (const CATPCurve   * iPCurve       ,
                                                       CATLONG32   & ioSupportIndex,
                                                 const CATCrvLimits* iLimits       ) = 0;
  //-------------------  Other Methods for data retrieving ---- 
  // (giving results only for specific derivations)
  virtual void      GetFaces                    (      CATLISTP(CATCell) & oPCellFaceList);

  virtual void      GetPCurves                  (      CATLISTP(CATCurve)& oPCurves);

};
#endif








