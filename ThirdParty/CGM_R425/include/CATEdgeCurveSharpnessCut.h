#ifndef CATEdgeCurveSharpnessCut_H
#define CATEdgeCurveSharpnessCut_H

// COPYRIGHT DASSAULT SYSTEMES  2001

//=============================================================================
//
// Calcul des decoupes aux changements de vivicite d'une EdgeCurve
//
//=============================================================================
// 28/01/09 NLD Ajout de Run() pour instrumentation
// 02/12/14 NLD Suppression du constructeur sans configuration
// 12/03/20 Q48 Headers etc for math versioning
//=============================================================================

// ExportedBy
#include "Y30UIUTI.h"

// Base class
#include "CATGeoOperator.h"

// C++11
#include "CATGeoOpVirtual.h"

#include "CATCrvParam.h"
#include "CATMathDef.h"
#include "CATGeoDef.h"
#include "CATCGMVirtual.h"
#include "CATCreateEdgeCurveSharpnessCut.h"

#include "CATString.h"
#include "CATGeoOpTimer.h"
#include "CATCGMOperatorDebug.h"

#include <fstream.h>

class CATGeoFactory;
class CATPointOnEdgeCurve;
class CATPCurve;
class CATEdgeCurve;
class CATSurface;
class CATMathInterval;
class CATEquationSharpChange;
class CATSoftwareConfiguration;

class ExportedByY30UIUTI CATEdgeCurveSharpnessCut  : public CATGeoOperator
{
public:
  CATEdgeCurveSharpnessCut(      CATGeoFactory            * iFactory,
                                 CATSoftwareConfiguration * iConfig ,
                                 CATEdgeCurve             * ECrv    ,
                                 CATPointOnEdgeCurve      * Start   ,
                                 CATPointOnEdgeCurve      * End     ,
                           const short                      SideOnFace1,
                                 CATPCurve                * PCrv1      ,
                                 CATSurface               * Surf1      ,
                           const short                      OrnFaceVsSurf1,
                                 CATPCurve                * PCrv2         ,
                                 CATSurface               * Surf2         ,
                           const short                      OrnFaceVsSurf2);

/*
  CATEdgeCurveSharpnessCut(CATGeoFactory * iFactory,
                           CATEdgeCurve * ECrv,
                           CATPointOnEdgeCurve * Start, CATPointOnEdgeCurve * End,
                           const short SideOnFace1,
                           CATPCurve * PCrv1, CATSurface * Surf1, 
                           const short OrnFaceVsSurf1,
                           CATPCurve * PCrv2,CATSurface * Surf2,
                           const short OrnFaceVsSurf2);
*/

  ~CATEdgeCurveSharpnessCut();
  

  // running the operator
  int               Run();
  
  void              SetAngularTol(double AngularTol);
  
  void              BeginningZone();
  
  CATGeoContinuity  GetSharpness();

  // Min/Max angle computation.
  //
  // Specific method used to compute the minimum and maximum G1 angular defaults of the two surfaces.
  //
  // Option: if iDisableSharpnessCuts = TRUE, the operator ONLY computes the minimum and maximum angles without
  //         performing the sharpness cut analysis.
  //         NB.: If this option is chosen, DO NOT call other get method than GetMinMaxAngle.
  void              SetMinMaxAngleComputation(CATBoolean iDisableSharpnessCuts = FALSE);
  //
  // Please note that returned angles (oMin and oMax) are in radians and in [0,PI].
  void              GetMinMaxAngle(double &oMin, double &oMax, CATCrvParam *ioParamMin=NULL, CATCrvParam *ioParamMax=NULL);
  
  CATBoolean        NextZone();
  
  void              GetExtremities(CATPointOnEdgeCurve* &oStart, CATPointOnEdgeCurve* &oEnd);

  const CATString * GetOperatorId();
  //-----------------------------------------------------------------------
  //- Gestion timer 
  //-----------------------------------------------------------------------  
  CATGeoOpTimer   * GetTimer();

  //-----------------------------------------------------------------------
  //- Gestion Mode Record 
  //-----------------------------------------------------------------------  

  CATExtCGMReplay * IsRecordable  (short        & LevelOfRuntime, short &VersionOfStream);
  void              WriteInput    (CATCGMStream & os);
  void              WriteOutput   (CATCGMStream & os);
  CATBoolean        ValidateOutput(CATCGMStream & ioStream, CATCGMOutput & os,int VersionNumber=1);
  void              Dump          (CATCGMOutput & os) ;
  void              DumpOutput    (CATCGMOutput & os);
  void              DumpOutput    (CATCGMStream & ioStream, CATCGMOutput & os, int VersionNumber=1);

  //-----------------------------------------------------------------------
  //- Protected Methods
  //-----------------------------------------------------------------------  
protected:
  // running the operator
  int               RunOperator();
  
  //-----------------------------------------------------------------------
  //- Private Methods
  //-----------------------------------------------------------------------  
private:
  // MinMax computation dedicated methods.
  void              Optimize       (CATMathInterval & iDomain, CATEquationSharpChange * iToOptimize, CATBoolean iAngleEval = TRUE);
  void              UpdateMinMax   (double iParam, double iAngle);
  
private:
  // Input Data
  CATSoftwareConfiguration * _Config;
  CATPCurve                * _PCrv[2];
  double                     _Tolerance,
                             _AngularTol,
                             _SinAngularTol;
  CATEdgeCurve             * _ECrv;
  CATSurface               * _Surf[2];
  CATPointOnEdgeCurve      * _Poec[2];
  short                      _SideOnFace,
                             _MinMaxComputation;
  short                      _OrnFaceVsSur[2];
  
  
  // Data for output
  CATLONG32                  _NbZone,
                             _IndexZone;
  CATGeoContinuity         * _Sharpness;
  double                     _Min      ,
                             _Max      ,
                             _WMin     ,
                             _WMax     ;
  CATPointOnEdgeCurve     ** _PoecStart;
  CATPointOnEdgeCurve     ** _PoecEnd;

  friend class CATGeoStreamFactory; // pour gestion du mode Record Automatique

  // private static data
  static CATString           _OperatorId;
  static CATGeoOpTimer       _Timer;

};

#endif
