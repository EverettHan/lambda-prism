/* -*-C++-*-*/
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATSurVertexSmoothing :
// Interface class of the Surface's Vertex Smoothing operator.
//
//   - this operator smooth the polygon of the control points.
//     The smoothing value, represent the importance of the
//     smoothing factor (0 gives no change).
//   - borderU or borderV can be equal to 0 for a smoothing with 
//     free edge in the chosen direction (U or V), or equal to 1
//     for C0 continuity (the border does not move).
//   - The matrix _TargetPoints is for making local smooth :
//     if _TargetPoints[i, j]=1. then the corresponding control
//     will be smoothed, else _TargetPoints[i, j]=0. and then
//     this control point will be unchanged. If a global smoothing
//     is wished, just choose NULL argument for _TargetPoints .
//          (above: NDN comments copied from CATCrvVertexSmoothingCx2.cpp NLD041116)
//     For _TargetPoints definition, see argument iTargetPoints in creators
//     - CATCreateSurVertexSmoothing()   (or old one CreateSurVertexSmoothing())
//     - CATPGMCreateSurVertexSmoothing()
//
//   - Appearently, in an iterative process, user/dialog/operator,
//     the smoothing factor may be modified and the operator rerun,
//     but is result at nth iteration does not depend on (n-1) previous run
//     NLD071116
//
//=============================================================================
// Usage notes:
// sample of use :
// to provide
//
//=============================================================================
// Jan   98 NDN Creation
// 13/03/15 NLD Smart indent
//              XScaleRules
//              Retroingenierie documentative
// 04/11/16 NLD Ajout dans l'en-tete de la description generale issue de l'implementation,
//              et en particulier de la description de _TargetPoints
//              Run() devient typee int
//              Migration sur CATCGMOperator
//              Ajout d'un constructeur
//              Documentation du Run multiple
// 16/01/17 NLD Correction des incompatibilites avec les macros CATCGMOperatorDebug*
//=============================================================================
#ifndef CATSurVertexSmoothing_H 
#define CATSurVertexSmoothing_H 

#define CATSurVertexSmoothing_AsCGMOperator

#include "CATGMOperatorsInterfaces.h"
#include "CATPGMCreateSurVertexSmoothing.h"

#ifdef CATSurVertexSmoothing_AsCGMOperator
#include "CATCGMVirtual.h"
#include "CATCGMOperator.h" // #include "CATGeoOperator.h" NON ACCESSIBLE
#include "CATCGMOperatorDebug.h"
class CATGeoFactory;
#endif
//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATSurVertexSmoothing
#ifdef CATSurVertexSmoothing_AsCGMOperator
 : public CATCGMOperator
#endif
{
#ifdef CATSurVertexSmoothing_AsCGMOperator
  CATCGMVirtualDeclareClass(CATSurVertexSmoothing);
#endif
  public :
#ifdef CATSurVertexSmoothing_AsCGMOperator
                            CATSurVertexSmoothing(CATGeoFactory* iFactory);
#endif
  
  virtual                  ~CATSurVertexSmoothing();

  /** @nodoc @nocgmitf */
#ifdef CATSurVertexSmoothing_AsCGMOperator
//  CATCGMOperatorDebugDeclareRun(CATSurVertexSmoothing,CATCGMOperator);
#else

  virtual int               Run                  ()                   = 0;
#endif

  //                        (XScaleRules) iSmooth must be independent from factory scale. NLD130315
  virtual void              SetSmoothValue       (double    iSmooth  ) = 0;

  //                        Sets imposed continuities on borders
  //                        - all imposed values must be equal to 0 or 1
  virtual void              SetContinuityOnBorder(CATLONG32 iBorderU1,
                                                  CATLONG32 iBorderU2,
                                                  CATLONG32 iBorderV1,
                                                  CATLONG32 iBorderV2) = 0;

  virtual double            GetMaxDeviation      ()                    = 0;

};

#endif
