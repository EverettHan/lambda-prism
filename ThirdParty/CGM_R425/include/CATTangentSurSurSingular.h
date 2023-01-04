// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATTangentSurSurSingular :
// Class to compute tangents of solutions at a given point at the intersection
// of two surfaces when a singularity exists.
//
//=============================================================================
// Usage notes:
//
// The surfaces iSurf1 and iSurf2 should have a singularity at (iParam1, iParam2)
// (the tangent planes are considered as confused by the operator).
//
// 0, 1 or 2 tangents can be returned
//
//=============================================================================
// Sep. 98  Creation                                                 X. Gourdon
// Feb. 14  Replaced Run2() and added treatment for singular points.        R1Y
// Apr. 14  Added functionality for removing duplicate tangents.            R1Y
//=============================================================================

#ifndef CATTangentSurSurSingular_H
#define CATTangentSurSurSingular_H

#include "Y30C3XGG.h"

#include "CATMathDef.h"
#include "CATCGMVirtual.h"
#include "CATCreateTangentSurSurSingular.h"

class CATSurParam;
class CATSurface;
class CATMathFunctionXY;
class CATGeoFactory;
class CATSoftwareConfiguration;

// Debug
#include "CATGeoOpDebug.h"

class ExportedByY30C3XGG CATTangentSurSurSingular : public CATCGMVirtual
{

public:

  CATTangentSurSurSingular(      CATGeoFactory            * iFactory,
                                 CATSoftwareConfiguration * iConfig,
                                 CATSurface               * iSurf1,
                           const CATSurParam              & iParam1,
                                 CATSurface               * iSurf2,
                           const CATSurParam              & iParam2);

  ~CATTangentSurSurSingular();

  void SetAngularTolForIsSingular(const double iAngularTolForIsSingular);
  double GetAngularTolForIsSingular() const;
  CATBoolean PointIsSingular() const;

  CATLONG32 GetNumberOfTangents() const;
  CATBoolean NextTangent();
  void GetTangent(double oTangent[4]) const;

  void SetRemoveDuplicateTangents(const CATBoolean iRemoveDuplicateTangents = TRUE);
  CATBoolean GetRemoveDuplicateTangents() const;

  void Run();

  //-----------------------------------------------------------------------------
  // Private data
  //-----------------------------------------------------------------------------
private:

  CATGeoFactory * _Factory;
  CATSurface    * _Surf1, * _Surf2;
  double          _u, _v, _r, _s; // local coordinates in R4
  CATLONG32       _iu, _iv, _ir, _is; // indexes of patches

  const CATMathFunctionXY * _F[3], * _G[3];

  double                   * _Tangent;
  CATLONG32                  _Index, _NumberOfTangents;
  CATSoftwareConfiguration * _Config;

  double     _AngularTolForIsSingular;
  CATBoolean _PointIsSingular;
  CATBoolean _RemoveDuplicateTangents;

  //-----------------------------------------------------------------------------
  // Private methods
  //-----------------------------------------------------------------------------
  CATLONG32 RunOriginal();  // original method
  CATLONG32 SolveQuadraticForm(const double a,  // used in the original method
                               const double b,
                               const double c,
                               double oSolutions[4]);
  CATLONG32 Run2();  // replacement method
};

#endif
