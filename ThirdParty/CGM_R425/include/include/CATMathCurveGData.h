//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2005
//=============================================================================
//
// CATMathCurveGData:
//  Base class for storage of mathematical data related to a curve (point,
//  first deriv, ...)
//
//  This class is dedicated to use in CATMathLocalConnectChecker. It allows
//  to provide the mathematical inputs  data that will be  used for local 
//  computation of geometric continuity.
//
// Usage notes (see commands in CATMathConnectCheckerTools.h) :
//
// * For a G0-computation, please SetDataOrder with G0Continuity.
// * For a G1-computation, please SetDataOrder with G1Continuity.
// * For a G2-computation, please SetDataOrder with G1Continuity and 
//   G2Continuity.
// * For a G3-computation, please SetDataOrder with G1Continuity,
//   G2Continuity and G3Continuity.
//
//=============================================================================
// October 2005   Creation                                              CQI
//=============================================================================

#ifndef CATMathCurveGData_H
#define CATMathCurveGData_H

#include "YN000ANL.h"

#include "CATCGMVirtual.h"
#include "CATMathVector.h"

class CATMathPoint;
class CATMathVector;
class CATSoftwareConfiguration;

#define MCGDATADIM  3
#define MCGDATASIZE 6 // Pt + FirstDeriv + SecondDeriv + ThirdDeriv + OrderPDeriv + OrderQDeriv

class ExportedByYN000ANL CATMathCurveGData : public CATCGMVirtual
{
public:

  CATMathCurveGData();

  CATMathCurveGData(int iOrder);

	~CATMathCurveGData();

  // To reset current container data
  void Reset();

  // -------------------------------------------------------------
  // SET METHODS
  // -------------------------------------------------------------

  // G-Continuity (see commands in CATMathConnectCheckerTools.h)
  //
  // ex. SetDataOrder(G1Continuity | G2Continuity) = G1 + G2 activated.
  //
  void SetDataOrder(int iOrder);

  // Mandatory set methods that must be called
  //
  // G0Continuity: SetPoint
  // G1Continuity: SetFirstDeriv + SetTangentOrientation ( + SetOrderPDeriv if known to be singular)
  // G2Continuity: G1Continuity methods + SetSecDeriv    ( + SetOrderQDeriv if known to be singular)
  // G3Continuity: G2Continuity methods + SetThirdDeriv

  // -------------------------------------------------------------
  // Point       = C(t)    requires G0Continuity to be set
  // FirstDeriv  = C'(t)   requires G1Continuity to be set
  // SecDeriv    = C''(t)  requires G2Continuity to be set
  // ThirdDeriv  = C'''(t) requires G3Continuity to be set
  // -------------------------------------------------------------

  // Following methods must be used to store the true evaluation and derivatives
  // of a given curve, ie. derivative with associated parameter 't'
  void SetPoint(CATMathPoint & iPt);
  void SetFirstDeriv(CATMathVector & iFirstDeriv);
  void SetSecDeriv(CATMathVector & iSecDeriv);
  void SetThirdDeriv(CATMathVector & iThirdDeriv);

  // Following method must be called (with G1Continuity order) so as to store
  // the requested tangent orientation (does not modify first deriv. stored):
  // iori = -1 ===> tangent will be oriented as  C'(t)
  // iori = +1 ===> tangent will be oriented as -C'(t) 
  void SetTangentOrientation(int iori);

  // -------------------------------------------------------------
  // Singular cases management: when C'(t) and C''(t) are not 
  // regular enough to define curve's Frenet basis, higher 
  // derivative orders are required.
  // -------------------------------------------------------------

  // To store the first non null derivative of order p > 0 denoted C(p)
  //
  // Requires G1Continuity to be set
  void SetOrderPDeriv(CATMathVector & iOrderPDeriv, int ip);

  // To store the second derivative of order q > p, non null, and non colinear to C(p).
  // We denote C(q) this vector.
  //
  // Requires G2Continuity to be set
  void SetOrderQDeriv(CATMathVector & iOrderQDeriv, int iq);

  // Allows to flag explicitly the current curve as line (a singular curve
  // could be considered as a line if all derivatives higher than p order are null).
  //
  // NB. : this method could be called whatever is the data order.
  void SetIsALine(int iEnable=1);

  // -------------------------------------------------------------
  // GET METHODS
  // -------------------------------------------------------------

  int GetDataOrder();

  void GetPoint(CATMathPoint & oPt);
  void GetFirstDeriv(CATMathVector & oFirstDeriv);
  void GetSecDeriv(CATMathVector & oSecDeriv);
  void GetThirdDeriv(CATMathVector & oThirdDeriv);

  int GetTangentOrientation();

  int GetOrderPDeriv(CATMathVector & oOrderPDeriv, int & op);
  int GetOrderQDeriv(CATMathVector & oOrderQDeriv, int & oq);

  int IsALine()
  { return _IsALine; }

private:

  int    _order;
  int    _IsALine;
  int    _derivorders[2];
  int    _ori;
  double _data[MCGDATADIM*MCGDATASIZE];
};

#endif
