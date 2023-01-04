//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2005
//=============================================================================
//
// CATConnectCheckerSurUtilities:
//  Base class for diverse computations (first deriv, etc.) on a surface
//
//=============================================================================
// May 2005   Creation                                              CQI
//=============================================================================

#ifndef CATConnectCheckerSurUtilities_H
#define CATConnectCheckerSurUtilities_H

#include "CATCGMVirtual.h"
#include "CATMathVector.h"
#include "CATBoolean.h"
#include "CATSurLimits.h"

#include "CATConnectCheckerDef.h"

class CATGeoFactory;
class CATSurface;
class CATPointOnEdgeCurve;
class CATSoftwareConfiguration;

class CATConnectCheckerSurUtilities : public CATCGMVirtual
{
public:
  //-----------------------------------------------------------------------
  //- Object management
  //-----------------------------------------------------------------------

  CATConnectCheckerSurUtilities(CATGeoFactory             * iFactory,
                                CATSoftwareConfiguration  * iConfig,
                                CATSurface                * iSurface,
                                const CATSurLimits        & iSurLimits);

	~CATConnectCheckerSurUtilities();

  //-----------------------------------------------------------------------
  //- Public methods
  //-----------------------------------------------------------------------

  //
  // Computes the evaluation of surface's first derivatives. Manage singularities (null derivative) with
  // respect to a 3D tolerance by default (use Set3DTol to change it) with a UV-shift from singular
  // point at a shift tol (use Set2DTol to change it) and store usefull parameter in oParam
  CATBoolean ComputeFirstDeriv(const CATSurParam & iParam, CATMathVector & ioDU, CATMathVector & ioDV, CATSurParam & oParam);

  //
  // Sets a given absolute tolerance used to filter singularities such as null derivatives
  void Set3DTol(const double i3DTol);
  
  //
  // Sets a given absolute tolerance used to shift in UV from singular points
  void Set2DTol(const double i2DTol);


protected:

  //
  // Check if || iDUorDV ||^2 < _3DTol
  CATBoolean IsNullFirstDeriv(const CATMathVector & iDUorDV);

  //
  // Compute extremities with taking account of geometric rep (revolve or not)
  void GetExtremities(const double iU, double & ioUmin, double & ioVmin, double & ioUmax, double & ioVmax);

  //
  // Manage a shift (+ or - _2DTol) from a singular point located at iUorV parameter
  void ShiftFromSingularity(double & ioUorV, const double iLow, const double iHigh);

  CATGeoFactory             * _Factory;
  CATSoftwareConfiguration  * _Config;

  /////////////////////////////
  // Input geometries
  /////////////////////////////
  
  CATSurface * _Surface;
  CATSurface * _GeometricRep;
  CATSurLimits _UVLim;
  CATBoolean   _IsARevolve;

  /////////////////////////////
  // Tolerances
  /////////////////////////////
  double       _3DTol;
  double       _2DTol;
};

#endif
