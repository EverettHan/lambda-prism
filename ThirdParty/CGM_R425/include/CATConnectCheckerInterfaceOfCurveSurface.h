//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2005
//=============================================================================
//
// CATConnectCheckerInterfaceOfCurveSurface:
//  Base class for checking geometric continuity between a curve and a surface
//
//=============================================================================
// March 05 CQI Creation                                                    CQI
// 19/09/18 MWE SetCurvatureTolerances
// 10/06/22 NLD Ajout GetCurvatureDeviation()
//              qui doit remplacer GetCurvatureAndConvexity()
//=============================================================================

#ifndef CATConnectCheckerInterfaceOfCurveSurface_H
#define CATConnectCheckerInterfaceOfCurveSurface_H

#include "Y30A3HGG.h"
#include "CATCGMOperator.h"
#include "CATCreateConnectChecker.h"
#include "CATMathVector.h"
#include "CATBoolean.h"
#include "CATCrvParam.h"
#include "CATCrvLimits.h"
#include "CATSurLimits.h"

#include "CATConnectCheckerDef.h"
#include "CATConnectCheckerCrvUtilities.h"
#include "CATMathCurveGData.h"
#include "CATMathSurfaceGData.h"
#include "CATMathLocalConnectChecker.h"

class CATGeoFactory;
class CATEdgeCurve;
class CATPointOnEdgeCurve;
class CATSoftwareConfiguration;
class CATEdgeCurve;
class CATPointOnEdgeCurve;
class CATSurface;
#include "CATMathVector.h"
#include "CATCrvParam.h"
#include "CATCrvLimits.h"



class ExportedByY30A3HGG CATConnectCheckerInterfaceOfCurveSurface : public CATCGMOperator
{
  CATCGMVirtualDeclareClass(CATConnectCheckerInterfaceOfCurveSurface);
 public:
  //-----------------------------------------------------------------------
  //- Object management
  //-----------------------------------------------------------------------
  //
  // Connect Checker of Curve Surface
  //
  CATConnectCheckerInterfaceOfCurveSurface (      CATGeoFactory            * iFactory  ,
                                                  CATSoftwareConfiguration * iConfig   ,
                                                  CATEdgeCurve             * iEdgeCurve,
                                            const CATPointOnEdgeCurve      * iPOECStart,
                                            const CATPointOnEdgeCurve      * iPOECEnd  ,
                                            const CATPointOnEdgeCurve      * iPOECOnCrv,
                                                  CATSurface               * iSurface  ,
                                            const CATSurLimits             & iLimitSurf);
                                                      
     ~CATConnectCheckerInterfaceOfCurveSurface();

  //-----------------------------------------------------------------------
  //- Public methods
  //-----------------------------------------------------------------------

  /** @nodoc @nocgmitf */
  int RunOperator();

  // Post-Run diagnostic on whole computations (TRUE if OK, FALSE otherwise).
  // If FALSE, Get methods could return a throw if they are called 
  CATBoolean IsRunOK();

  ////////////////////////////////////////////////////////////
  // Set methods
  ////////////////////////////////////////////////////////////
  
  // Select the computation type (necessary)
  //
  // Example : Gaps + Curvatures : ... -> SetTypeOfEvalutation(CATConnectCheckerGap | CATConnectCheckerCurvature)
  //
  // CATConnectCheckerGap              1
  // CATConnectCheckerAngle            2
  // CATConnectCheckerCurvature        4
  void SetTypeOfEvaluation (CATCommandOption iCommande); 

  // Only for New Specs : define the interval of valid curvatures for your scope
  // By default : iMinCurvature corresponds to the largest radius that can be created in CATIA.
  // At scale 1 the maximum radius for a circle is 1E+7, so iMinCurvature is 1E-7.
  // CAUTION: these are values varying like power -1 of factory scale
  void SetCurvatureTolerances(double iMinCurvature, double iMaxCurvature);

  ////////////////////////////////////////////////////////////
  // Get methods
  ////////////////////////////////////////////////////////////

  // Returns the result of the G0 measure 
  // The result is a distance (positive quantity).
  //
  // Default tolerance = G0 TOL = 0.001 mm
  // A distance inferior to G0 TOL ensures G0 continuity.
  double GetDistance();

  // Returns the result of the G1 measure in radians
  // The result is an angle between 0. and 0.5*PI radians.
  //
  // Default tolerance = G1 TOL = 0.5 degree
  // An angle inferior to G1 TOL ensures G1 continuity.
  double GetAngle();

  // Returns the result of the G2 measure in percent
  // (NO; ERROR, ratio in [0, 1]; CAUTION, see below)
  // and a boolean
  // which indicates if we have the same convexity on curve and surface.
  // The result is an adimensional rate between 0. and 100 %.
  // The boolean is TRUE if same convexity has been found, FALSE otherwise.
  //
  // Default tolerance = G2 TOL = 5 percent
  // An rate inferior to G2 TOL and same convexity ensure G2 continuity.

  // CAUTION: to be fixed ???
  // as of historical version, (from the beginning)
  // and despite of documentation above,
  // ioCurvatureRate is a ratio in [0., 1.]
  // and NOT a percent in [0., 100.]
  //   NLD270522
  // PLEASE USE GetCurvatureDeviation()
  void GetCurvatureAndConvexity(double     & ioCurvatureRate,
                                CATBoolean & ioSameConvexity);

  // Returns the result of the G2 measure in percent and a boolean
  // which indicates if we have the same convexity on curve and surface.
  // The result is an adimensional rate between 0. and 100 %.
  // The boolean is TRUE if same convexity has been found, FALSE otherwise.
  //
  // Default tolerance = G2 TOL = 5 percent
  // An rate inferior to G2 TOL and same convexity ensure G2 continuity.

  // REPLACES GetCurvatureAndConvexity()
  //   NLD100622
  void GetCurvatureDeviation   (double     & ioCurvaturePercentRate,
                                CATBoolean & ioSameConvexity);

  // ** NOT AVAILABLE ***
  // Returns TRUE if an overlap exists between curve and surface, FALSE otherwise
  //CATBoolean GetOverlap();
  // ** NOT AVAILABLE ***
   
 protected:

  //-----------------------------------------------------------------------
  //- Protected methods
  //-----------------------------------------------------------------------

   CATBoolean Initialize  ();
   CATBoolean PreProcess  ();
   CATBoolean PreProcessG0();
   CATBoolean PreProcessG1();
   CATBoolean PreProcessG2();

   CATBoolean ComputeG0   ();
   CATBoolean ComputeG1   ();
   CATBoolean ComputeG2   ();
   // ** ONLY FOR OVERLAP ***
   //CATBoolean ComputeOverlap();

   CATBoolean IsAMinimum  (CATMathPoint & iP, double * UV);

   // ** ONLY FOR OVERLAP ***
   //void ProjectUVOnBorders(double *  iUV, double * ioUVproj, CATBoolean & ioDegenerate);

   void       Clean();

   ////////////////////////////////////////////////////////////
   // Debug
   ////////////////////////////////////////////////////////////
   void       MyDebug();

   CATGeoFactory                 * _Factory;
   CATSoftwareConfiguration      * _SoftwareConfiguration;

   ////////////////////////////////////////////////////////////
   // Input geometries
   ////////////////////////////////////////////////////////////
   CATEdgeCurve                  * _ECrv;
   const CATPointOnEdgeCurve     * _POECStart,
                                 * _POECEnd;
   const CATPointOnEdgeCurve     * _POECOnCrv;
   CATSurface                    * _Surf;
   CATSurLimits                    _SurLimits;
   CATCrvParam                     _cp;
   CATCrvLimits                  * _cl;
   ////////////////////////////////////////////////////////////

   CATCommandOption                _Command;

   ////////////////////////////////////////////////////////////
   // Connect checker analysis data
   ////////////////////////////////////////////////////////////
   // G0
   double                          _Gap;
   // G1
   double                          _Angle;
   // G2
   double                          _Curvature;       // N.B curvature deviation ratio (and surely not a percentage) NLD100622
   CATBoolean                      _OppositeNormals;
   // Overlap // ** NOT AVAILABLE ***
   //CATBoolean                    _Overlap;
   ////////////////////////////////////////////////////////////

   // Local operator used for G-computations
   CATMathLocalConnectChecker    * _LocalConnectChecker;

   ////////////////////////////////////////////////////////////
   // Geometric data linked to curves
   ////////////////////////////////////////////////////////////
   CATMathCurveGData               _CrvData;
   CATMathSurfaceGData             _SurData;

   // G0
   CATSurParam                     _sp;
   CATBoolean                      _OKG0;
   // G1
   CATBoolean                      _OKG1;
   // G2
   CATBoolean                      _IsALine;
   CATBoolean                      _OKG2;
   CATBoolean                      _IsAnOrthogonalProj;
   ////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////
   // Operator to compute safe tangent, normal, curvature, etc.
   ////////////////////////////////////////////////////////////
   CATConnectCheckerCrvUtilities * _CrvUtil;
   ////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////
   // ConnectChecker tolerances
   ////////////////////////////////////////////////////////////
   double                          _CRBmin;
   double                          _CRBmax;
   ////////////////////////////////////////////////////////////

   CATBoolean                      _RunOK;

//========================================================================
// CGMReplay
//========================================================================
protected:
  friend class CATGeoStreamFactory; 

  // private static data
  static CATString                 _OperatorId;

public:
  /** @nodoc @nocgmitf */
    const CATString        * GetOperatorId ();

  /** @nodoc @nocgmitf */
          CATExtCGMReplay  * IsRecordable  (short & LevelOfRuntime, short &VersionOfStream);
  /** @nodoc @nocgmitf */
  virtual void               WriteInput    ( CATCGMStream  & os);
  /** @nodoc @nocgmitf */
  virtual void               WriteOutput   (CATCGMStream & os);
  /** @nodoc @nocgmitf */
  virtual CATBoolean         ValidateOutput(CATCGMStream& ioStream, CATCGMOutput & os,int VersionNumber=1);
  /** @nodoc @nocgmitf */
  virtual void               Dump          (CATCGMOutput& os ) ;
  /** @nodoc @nocgmitf */
  virtual void               DumpOutput    (CATCGMOutput & os);
  /** @nodoc @nocgmitf */
  virtual void               DumpOutput    (CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
  /** @nodoc @nocgmitf */
  virtual CATCheckDiagnostic CheckOutput   (CATCGMOutput & os);
};

#endif


