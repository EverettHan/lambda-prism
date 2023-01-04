//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2000
//===================================================================
//
// CATExactUVBox
//
//
//===================================================================
// Usage notes : Determine the exact surlimits containing a PCurve
//
// 14Febr2008 KJD : ajout de la methode CATExact2DBox pour Skewing 3DVia
//===================================================================

#ifndef CATExactUVBox_H
#define CATExactUVBox_H
#include "YP00IMPL.h"                    

#include "CATMathDiagnostic.h"
#include "CATListOfCATPCurves.h"
#include "CATListOfCATCrvLimits.h"

class CATCrvLimits;
class CATPCurve;
class CATSurLimits;
class CATMath2x2Matrix;
class CATSurParam;


// ioParamForMaxGap = double[4] = {MaxU, MinU, MaxV, MinV}
// ioGap3D = double[4] = {MaxU, MinU, MaxV, MinV}

ExportedByYP00IMPL CATMathDiagnostic CATExactUVBox(const CATPCurve *iPCrv,
                                                   const CATCrvLimits *iCrvLim,
                                                   CATSurLimits * ioSurLim,
                                                   double * ioParamForMaxGap = 0,
												                           double * ioGap3D = 0);

// KJD 14Febr2008 : 
// Methode permettant de calculer la boite d'encombrement dans un repere quelconque d'une liste de PCurve appartenant toutes a la meme surface.
// Le repere dans lequel on calcule la boite est obtenu a partir du repere UV de la surface par la transformation 2D iTransfo. 
// La boite d'encombrement est ensuite reecrite avec les coordonees du repere UV.
ExportedByYP00IMPL CATMathDiagnostic CATExact2DBox(const CATLISTP(CATPCurve) &iListPCrv,
                                                   const CATLISTP(CATCrvLimits) &iListCrvLim,
                                                   CATMath2x2Matrix & iTransfo,
                                                   CATSurParam & oLowParam,
                                                   CATSurParam & oHighParam);

#endif
