// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
// Feb 00 Creation                       XGN
//=============================================================================
// Usage notes:
//  This operator is exclusively dedicated to the usage of CombiView operators
//
//  From 2 Geometries representing a 3D geometry on two different views, the goal is to
//  generate a third view of this 3D geometry on a third support.
//  
//  Note : some singular cases can lead to several curves solutions or to a point
//         (even from 2 pcurves)
//
//=============================================================================
#ifndef CATCombiViewPCrv_H
#define CATCombiViewPCrv_H

#include "Y30UIUTI.h"

#include "CATCGMOperator.h"

#include "CATCrvLimits.h"
#include "CATMathDef.h"
#include "CATMathPlane.h"
#include "CATSkillValue.h"

#include "CATString.h"

#include "CATCreateCombiViewPCrv.h"

class CATGeoFactory;
class CATGeometry;
class CATCurve;
class CATPCurve;
class CATSurface;
class CATPlane;
class CATPoint;
class CATPointOnSurface;
class CATSoftwareConfiguration;


class ExportedByY30UIUTI CATCombiViewPCrv : public CATCGMOperator
{
  CATCGMVirtualDeclareClass(CATCombiViewPCrv);
 public:
  //-----------------------------------------------------------------------
  //- Object management
  //-----------------------------------------------------------------------
  
  CATCombiViewPCrv (CATGeoFactory *iFactory,
                    CATSoftwareConfiguration * iConfig,
                    CATGeometry * iGeometry1,
                    CATGeometry * iGeometry2,
                    CATPlane * iSupport1,
                    CATPlane * iSupport2,
                    CATPlane * iResultSupport);

  ~CATCombiViewPCrv ();
  //-----------------------------------------------------------------------
  //- Set methods
  //-----------------------------------------------------------------------

  // When an input geometry is a pcurve, SetLimits permits to associate a given
  // limits on this PCurve (default is the currentlimits on the pcurve)
  void SetLimits(CATPCurve * iPCrv, const CATCrvLimits & iLimits);

  //-----------------------------------------------------------------------
  //- Get methods
  //-----------------------------------------------------------------------

	CATLONG32 GetNumberOfCurves();
  void BeginningCurve();
  CATBoolean NextCurve();
  // The result PCurve lies on iResultSupport and is as canonic as possible
  CATPCurve * GetPCurve(CATCrvLimits & oLimits);
  //CATPCurve * GetPCurve();

	CATLONG32 GetNumberOfPoints();
	void BeginningPoint();
	CATBoolean NextPoint();
  CATPointOnSurface * GetPoint();

  //-----------------------------------------------------------------------
  //- Running the operator
  //-----------------------------------------------------------------------
  /** @nodoc @nocgmitf */
  int RunOperator();

protected:
  // protected methods
  void RunPCrvPCrv(CATCurve * Crv1, CATMathVector & Dir1,
                   CATCurve * Crv2, CATMathVector & Dir2);
  void RunPointPCrv(CATPoint * Pt, CATMathVector & Dir1,
                    CATCurve * Crv, CATCrvLimits & Limits, CATMathVector & Dir2);
  void RunPointPoint(CATPoint * Pt1, CATMathVector & Dir1,
                     CATPoint * Pt2, CATMathVector & Dir2);
                     
protected:
  // Protected data

  // Data for input
  CATGeometry * _Geometry[2];
  CATPlane * _Plane[2];
  CATCrvLimits _Limits[2];
  CATMathPlane _MathSupport[2];
  
  CATPlane * _Surface;

  // Data for output
  CATLONG32 _NbCurves, _NbPoints;
  CATLONG32 _IndexCurve, _IndexPoint;

  CATPCurve * _PResult[12]; // At most 12 curves can be generated
  CATPointOnSurface * _PointResult[12];

  // Internal data
  CATGeometry * _Extrusions[2];
  CATCurve * _InterExtrusions[12];
	CATLONG32 _NbCurveInterExtrusions;
  CATMathPoint * _PtInterExtrusions[12];
	CATLONG32 _NbPointsInterExtrusions;

  CATSoftwareConfiguration * _Config;
  
//========================================================================
// Gestion CGMReplay
//========================================================================
protected:
  friend class CATGeoStreamFactory; 

  // private static data
  static CATString _OperatorId;

public:
  
  /** @nodoc @nocgmitf */
	const CATString * GetOperatorId();
  //-----------------------------------------------------------------------
  //- Gestion Mode Record 
  //-----------------------------------------------------------------------  

  /** @nodoc @nocgmitf */
  CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
  /** @nodoc @nocgmitf */
  virtual void WriteInput(CATCGMStream  & ioStream);
  /** @nodoc @nocgmitf */
  virtual void WriteOutput(CATCGMStream & ioStream);
  /** @nodoc @nocgmitf */
	virtual CATBoolean ValidateOutput(CATCGMStream& ioStream, CATCGMOutput& os, int VersionOfStream=1);
  CATCGMOperator::CATCheckDiagnostic  CheckOutput(CATCGMOutput & os);
  /** @nodoc @nocgmitf */
  virtual void Dump( CATCGMOutput& os ) ;
  /** @nodoc @nocgmitf */
  virtual void DumpOutput(CATCGMStream& ioStream, CATCGMOutput& os, int VersionOfStream=1);
};

ExportedByY30UIUTI
CATCombiViewPCrv * CreateCombiViewPCrv(CATGeoFactory * iFactory,
                                       CATGeometry * iGeometry1,
                                       CATGeometry * iGeometry2,
                                       CATPlane * iSupport1,
                                       CATPlane * iSupport2,
                                       CATPlane * iResultSupport,
                                       CATSkillValue iMode = BASIC);

ExportedByY30UIUTI void Remove(CATCombiViewPCrv * Oper);

#endif
