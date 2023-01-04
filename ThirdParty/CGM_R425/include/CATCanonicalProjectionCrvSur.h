// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATCanonicalProjectionCrvSur :
//
//=============================================================================
// Usage notes:
//  This operator can be used by the projection operator to find
//  canonical projections when the surface is an infinite plane
//
//=============================================================================
// Feb. 99   Creation                              X. Gourdon    
// 04/11/08 NLD  Ajout _OperatorId et GetOperatorId()
// 14/06/19 LJL2 Migration of CATLONG32(_NbCrv) from sub-class to superclass
// 12/03/20 Q48  Headers etc for math versioning 
//=============================================================================

#ifndef CATCanonicalProjectionCrvSur_H
#define CATCanonicalProjectionCrvSur_H

// ExportedBy
#include "Y30E3PMG.h"

// Base class
#include "CATGeoOperator.h"

// C++11
#include "CATGeoOpVirtual.h"

#include "CATMathDef.h"

#include "CATCrvLimits.h"
#include "CATMathPoint.h"
#include "CATMathPlane.h"


#include "CATCreateCanonicalProjectionCrvSur.h"

class CATGeoFactory;
class CATCurve;
class CATEdgeCurve;
class CATSurface;
class CATPCurve;
class CATMathPlane;
class CATSoftwareConfiguration;

//-----------------------------------------------------------------------------
class ExportedByY30E3PMG CATCanonicalProjectionCrvSur : public CATGeoOperator
{

  CATCGMVirtualDeclareClass(CATCanonicalProjectionCrvSur);
 public:

  //-----------------------------------------------------------------
  //- Object management
  //-----------------------------------------------------------------

  CATCanonicalProjectionCrvSur(CATGeoFactory * iFactory, CATSoftwareConfiguration * iConfig,
                               CATCurve * iCurve, CATSurface * iSurface);
  CATCanonicalProjectionCrvSur(CATGeoFactory * iFactory, CATSoftwareConfiguration * iConfig,
                               CATCurve * iCurve,const CATMathPlane & iMathSupport);

  ~CATCanonicalProjectionCrvSur();

  void SetLimits(const CATCrvLimits & iLimits);
  void SetSupports(CATSurface * iSurf1, CATSurface * iSurf2);
  //-----------------------------------------------------------------
  //- Iterator
  //-----------------------------------------------------------------
  CATBoolean NextCurve();
  CATPCurve * GetPCurve();
  CATCurve * GetCurve();
  CATLONG32 GetOrientation();

  //-----------------------------------------------------------------
  //- Running the operator
  //-----------------------------------------------------------------
  /** @nodoc @nocgmitf */
  virtual int RunOperator();

  // @nocgmitf Operator Id
  const  CATString  *  GetOperatorId();  
    
protected:
  CATCanonicalProjectionCrvSur(CATGeoFactory * iFactory, CATSoftwareConfiguration * iConfig, CATCurve * iCurve);

  // Given a 3DCurve or a PCurve, returns 1 if the corresponding curve is logically a conic
  // (for example : Circle, Ellipse, PCircle, PEllipse, GetMathCurve())
  CATBoolean IsLogicalConic(CATCurve * Crv, double & MinorRadius, double & MajorRadius, CATMathPlane & MathSupport,
    int OldMode=1);

  void ProjectCanonical(const double iMajorRadius,
                        const double iMinorRadius,
                        const CATMathPlane & iMathSupport);

  void ProjectCanonical(const double iMajorRadius,
                        const double iMinorRadius,
                        const CATMathPlane & iMathSupport,
                        const CATMathPoint iExtremities[2],
                        const CATMathVector iTangents[2]);

  void ComputeMathPlaneFromSurface();
  void RemoveSmallCurves();

  CATCurve * _Crv;
  CATSurface * _Surface;
  CATMathPlane _MathSupport;
  CATCrvLimits _CrvLimits;
  CATSurface * _Support[2];
  CATLONG32 _NbCrv; // LJL2_14_06_2019_IR636830 migration of CATLONG32(_NbCrv) from sub-class to superclass

  double _Tolerance;

  // Internal data
  double _MajorR, _MinorR, _OffsetAngle, _AngleStart, _AngleEnd;
  CATMathPoint _ConicOrigin;
  CATLONG32 _Type[3]; // = 0 for ellipses and circles, = 1 for lines
  CATMathPoint _LineStart[3], _LineEnd[3];


  CATLONG32 _Index, _NbSol;  
  CATSoftwareConfiguration * _Config;
  //  private  static  data  
  static  CATString  _OperatorId;  

private:
  CATCanonicalProjectionCrvSur();
  CATCanonicalProjectionCrvSur(const CATCanonicalProjectionCrvSur &);
  void operator = (const CATCanonicalProjectionCrvSur &);


};



#endif
