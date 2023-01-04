//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2005
//=============================================================================
//
// CATMathSurfaceGData:
//  Base class for storage of mathematical data related to a surface (point,
//  first deriv, ...).
//
//  This class is dedicated to use in CATMathLocalConnectChecker. It allows
//  to provide the mathematical inputs data that will be  used for local 
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

#ifndef CATMathSurfaceGData_H
#define CATMathSurfaceGData_H

#include "YN000ANL.h"

#include "CATCGMVirtual.h"
#include "CATMathVector.h"


class CATMathPoint;
class CATMathVector;
class CATSoftwareConfiguration;

#define MSGDATADIM  3
#define MSGDATASIZE 10 // Pt + DU + DV + DU2 + DUDV + DV2 + DU3 + DU2DV + DUDV2 + DV3

class ExportedByYN000ANL CATMathSurfaceGData : public CATCGMVirtual
{
public:

  CATMathSurfaceGData();

  CATMathSurfaceGData(int iOrder);

	~CATMathSurfaceGData();

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

  // -------------------------------------------------------------
  // SetPoint       requires G0Continuity to be set
  // SetFirstDerivs requires G1Continuity to be set
  // SetSecDerivs   requires G2Continuity to be set
  // SetThirdDerivs requires G3Continuity to be set
  // -------------------------------------------------------------

  // NB. for SetFirstDerivs: iori is an optional orientation (-1,+1) used to re-orient normal
  //     vector: Normal = iori * (iDU^iDV). +1 is taken by default.

  void SetPoint(CATMathPoint & iPt);
  void SetFirstDerivs(CATMathVector & iDU, CATMathVector & iDV, int iori = 1);
  void SetSecDerivs(CATMathVector & iDU2, CATMathVector & iDUDV, CATMathVector & iDV2);
  void SetThirdDerivs(CATMathVector & iDU3, CATMathVector & iDU2DV, CATMathVector & iDUDV2, CATMathVector & iDV3);

  // SetNormal allows to store explicitly an own normal vector with its orientation.
  // iNormal will be used as default normal instead of computing it with DU and DV vectors.
  //
  // It requires G1Continuity order
  void SetNormal(CATMathVector & iNormal);
  // ResetNormal allows to cancel explicit normal setting.
  void ResetNormal();

  // SetEdgeTangent allows to set tangent vector to the edge of the surface.
  // For instance: iTangent = BoundaryPCurve->EvalFirstDeriv.
  //
  // It requires G2Continuity order
  void SetEdgeTangent(CATMathVector & iTangent);
  // ResetEdgeTangent allows to cancel explicit edge tangent setting.
  void ResetEdgeTangent();

  // -------------------------------------------------------------
  // GET METHODS
  // -------------------------------------------------------------

  int GetDataOrder();

  void GetPoint(CATMathPoint & oPt);
  void GetFirstDerivs(CATMathVector & oDU, CATMathVector & oDV, int * oori = NULL);
  void GetSecDerivs(CATMathVector & oDU2, CATMathVector & oDUDV, CATMathVector & oDV2);
  void GetThirdDerivs(CATMathVector & oDU3, CATMathVector & oDU2DV, CATMathVector & oDUDV2, CATMathVector & oDV3);

  // Requires G1Continuity order
  // Return 1 if normal has been previously set, 0 otherwise.
  // If 0, user needs to compute its own normal thanks to GetFirstDerivs data.
  int GetNormal(CATMathVector & oNormal);

  // Requires G2Continuity order
  // Return 1 if edge tangent has been previously set, 0 otherwise.
  int GetEdgeTangent(CATMathVector & oTangent);

private:

  int       _ori;
  int       _order;
  double    _data[MSGDATADIM*MSGDATASIZE];
  double  * _normal;
  double  * _tangent;
};

#endif
