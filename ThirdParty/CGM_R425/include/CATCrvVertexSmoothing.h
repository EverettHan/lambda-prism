/* -*-C++-*-*/
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATCrvVertexSmoothing :
// Interface class of the Curve's Vertex Smoothing operator.
//
//=============================================================================
//   - this operator smoothes the polygon of the control points.
//     The smoothing value, represent the importance of the
//     smoothing factor (0 gives no change).
//   - The matrix _TargetPoints is for making local smooth :
//     if _TargetPoints[i, j]=1. then the corresponding control
//     will be smoothed, else _TargetPoints[i, j]=0. and then
//     this control point will be unchanged. If a global smoothing
//     is wished, just choose NULL argument for _TargetPoints .
//     (a matrix of dimension (N , 1) is asked, instead of a vector, 
//     for interface compatibility with the surface smoothing)
//          (above: NDN comments copied from CATCrvVertexSmoothingCx2.cpp NLD031116)
//     For _TargetPoints definition, see argument iTargetPoints in creators
//     - CATCreateCrvVertexSmoothing()   (or old one CreateCrvVertexSmoothing())
//     - CATPGMCreateCrvVertexSmoothing()
//=============================================================================
// Usage notes:
// sample of use :
// to provide
//
//=============================================================================
// Jan   98 NDN Creation
// 13/03/15 NLD Smart indent
//              XScaleRules
// 03/11/16 NLD Ajout dans l'en-tete de la description generale issue de l'implementation,
//              et en particulier de la description de _TargetPoints
//              Run() devient typee int
//              Migration vers CATCGMOperator
// 16/01/17 NLD Correction des incompatibilites avec les macros CATCGMOperatorDebug*
//=============================================================================
#ifndef CATCrvVertexSmoothing_H 
#define CATCrvVertexSmoothing_H 

#define CATCrvVertexSmoothing_AsCGMOperator

//=============================================================================
#include "CATGMOperatorsInterfaces.h"
#include "CATPGMCreateCrvVertexSmoothing.h"
#include "CATCGMVirtual.h"

#ifdef CATCrvVertexSmoothing_AsCGMOperator
#include "CATCGMOperator.h" // #include "CATGeoOperator.h" NON ACCESSIBLE
#include "CATCGMOperatorDebug.h"
class CATGeoFactory;
#endif
//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATCrvVertexSmoothing
#ifdef CATCrvVertexSmoothing_AsCGMOperator
 : public CATCGMOperator
#else
 : public CATCGMVirtual
#endif
{
#ifdef CATCrvVertexSmoothing_AsCGMOperator
  CATCGMVirtualDeclareClass(CATCrvVertexSmoothing);
#endif
  public :

#ifdef CATCrvVertexSmoothing_AsCGMOperator
                            CATCrvVertexSmoothing(CATGeoFactory* iFactory);
#endif

  virtual                  ~CATCrvVertexSmoothing();

  /** @nodoc @nocgmitf */
#ifdef CATCrvVertexSmoothing_AsCGMOperator
//  CATCGMOperatorDebugDeclareRun(CATCrvVertexSmoothing,CATCGMOperator);
#else

  virtual int               Run                  ()                   = 0;
#endif

  //                        (XScaleRules) iSmooth must be independent from factory scale. NLD130315
  virtual void              SetSmoothValue       (double    iSmooth)  = 0;

  virtual double            GetMaxDeviation      ()                   = 0;

};


#endif
