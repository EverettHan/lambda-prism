//=============================================================================
// COPYRIGHT Dassault Systemes 2004
//=============================================================================
//
// CATConnectSphereReconverge.h
// Declaration of CATConnectSphereReconverge operator.
//
// Reconverge 3 points on their 3 surfaces, to make them lie on a virtual 
// sphere of a specified radius, tangent to these surfaces.
//
//=============================================================================
//   /05/04 BPG  Creation
//   /12/17 SMT1 Add variable tool types and begin refactoring  
// 12/03/20 Q48  Headers etc for math versioning
//=============================================================================

#ifndef CATConnectSphereReconverge_H
# define CATConnectSphereReconverge_H

// ExportedBy
#include "Connect.h"

// Base class
#include "CATGeoOperator.h"

// C++11
#include "CATGeoOpVirtual.h"

#include "CATBoolean.h"

#include "CATMathPlane.h"
#include "CATMathInline.h"

# include "CATSurParam.h"
# include "CATSurLimits.h"
# include "CATCrvLimits.h"

#include "CATTolerance.h"
#include "CATMathIntervalND.h"

class CATGeoFactory;
class CATSoftwareConfiguration;

class CATConstantFilletTool;
class CATVariableFilletTool;
class CATConnectTool;
class CATSurface;

class CATMathIntervalND;
class CATMathSystem;

/**
 * Operator that reconverge 3 points on their 3 surfaces, to make them lie 
 * on a virtual sphere of a specified radius, tangent to these surfaces.
 */
class ExportedByConnect CATConnectSphereReconverge:
  public CATGeoOperator
{
  //-----------------------------------------------------------------------
  // Constructor and destructor
  //-----------------------------------------------------------------------
public:
  CATConnectSphereReconverge(CATGeoFactory *iFactory,
                             CATSoftwareConfiguration *iConfig,
                          
                             CATSurface *iSupport1,
                             const CATLONG32 iOrientation1,
                             const CATSurLimits &iLimits1,
                             const CATSurParam &iParam1,

                             CATSurface *iSupport2,
                             const CATLONG32 iOrientation2,
                             const CATSurLimits &iLimits2,
                             const CATSurParam &iParam2,

                             CATSurface *iSupport3,
                             const CATLONG32 iOrientation3,
                             const CATSurLimits &iLimits3,
                             const CATSurParam &iParam3,

                             CATConstantFilletTool *iConnectTool,
                             CATBoolean iSolverMode = TRUE);

  CATConnectSphereReconverge(CATGeoFactory *iFactory,
                             CATSoftwareConfiguration *iConfig,

                             CATSurface *iSupport1,
                             const CATLONG32 iOrientation1,
                             const CATSurLimits &iLimits1,
                             const CATSurParam &iParam1,
                             CATConstantFilletTool *iConnectTool1,

                             CATSurface *iSupport2,
                             const CATLONG32 iOrientation12,
                             const CATLONG32 iOrientation23,
                             const CATSurLimits &iLimits2,
                             const CATSurParam &iParam2,

                             CATSurface *iSupport3,
                             const CATLONG32 iOrientation3,
                             const CATSurLimits &iLimits3,
                             const CATSurParam &iParam3,
                             CATConstantFilletTool *iConnectTool3,

                             CATBoolean iSolverMode = TRUE);

  CATConnectSphereReconverge(CATGeoFactory *iFactory,
                             CATSoftwareConfiguration *iConfig,

                             CATSurface *iSupport1,
                             const CATLONG32 iOrientation1,
                             const CATSurLimits &iLimits1,
                             const CATSurParam &iParam1,
                             CATVariableFilletTool *iConnectTool1,

                             CATSurface *iSupport2,
                             const CATLONG32 iOrientation12,
                             const CATLONG32 iOrientation23,
                             const CATSurLimits &iLimits2,
                             const CATSurParam &iParam2,

                             CATSurface *iSupport3,
                             const CATLONG32 iOrientation3,
                             const CATSurLimits &iLimits3,
                             const CATSurParam &iParam3,
                             CATVariableFilletTool *iConnectTool3,

                             CATBoolean iSolverMode = TRUE);


  virtual ~CATConnectSphereReconverge();

  //-----------------------------------------------------------------------
  // Solver
  //-----------------------------------------------------------------------
public:
  /** Ask to launch an exhaustive solver if Newton solver fails */
  INLINE void SetSolverMode(CATBoolean iSolverMode);

  /** Specific mode used to manage reconvergence exit domain by
   *  triggering required extrapolations.
   *  iExtrapolFlags is an optional array of size 3 that allows to forbid any
   *  extrapolation on a given input support. For instance:
   *  iExtrapolFlags[0] = 0, iExtrapolFlags[1] = 1, iExtrapolFlags[2] = 0
   *  means that only iSupport2 is not authorized to be extrapoled.
   *  Only available for CATConstantFilletTools */
  void SetExtrapolationMode(short * iExtrapolFlags=NULL);

  /**
   * Run the reconverger.
   *
   * GetDiagnostic() must be called to know if something failed.
   */
  virtual int RunOperator();

  //-----------------------------------------------------------------------
  // Accessors
  //-----------------------------------------------------------------------
public:
  /** Return the diagnostic of reconvergence. */
  INLINE CATLONG32 GetDiagnostic() const;

  /** Return the reconverged points. */
  INLINE CATLONG32 GetPoints(CATSurParam &oParam1,
                             CATSurParam &oParam2,
                             CATSurParam &oParam3) const;

  /**
   * Return the planes (i,j) on which the reconverged points i and j
   * and the approximated center lie.
   */
  INLINE CATLONG32 GetMathPlanes(CATMathPlane &oMathPlane12,
                                 CATMathPlane &oMathPlane23,
                                 CATMathPlane &oMathPlane31) const;
    
  //-----------------------------------------------------------------------
  // CGMReplay handling
  //-----------------------------------------------------------------------
public:
  const CATString *GetOperatorId();

  CATExtCGMReplay *IsRecordable(short &LevelOfRuntime, short &VersionOfStream);

protected:
  void Init();

  int RunExtrapol(CATMathIntervalND & ioDomain, CATMathSystem * iSys, double * ioInit, CATLONG32 & oDiagnostic);
  
  CATBoolean IsOutside(CATMathIntervalND & iDomain, double * iInputPt, double * iReachedPt,
                       double & oWeight, CATLONG32 & oPosition, CATLONG32 & oWhichSurface, short * oNeedsToExtrapol = NULL);
  
  CATBoolean IsDegenerated(CATSurface * iSurf, double iUmin, double iVmin, double iUmax, double iVmax, 
                           CATMathPoint & iLowLow, CATMathPoint & iLowHigh, CATMathPoint & iHighHigh, CATMathPoint & iHighLow,
                           CATLONG32 iWhichIsopar, CATLONG32 iClosureType, CATLONG32 iVorU);
  
  void ExtrapolSurface(CATMathIntervalND & ioDomain, double * iInputPt, double * iReachedPt, double iWeight, CATLONG32 iPosition,
                       CATBoolean & oExtrapolDone);

  void CreateOutput(); 

  virtual void WriteInput(CATCGMStream &os);
  virtual void WriteOutput(CATCGMStream &os);
  virtual CATBoolean ValidateOutput(CATCGMStream& ioStream, CATCGMOutput &os, int VersionNumber = 1);

  virtual void Dump(CATCGMOutput &os);
  virtual void DumpOutput(CATCGMOutput &os);
  virtual void DumpOutput(CATCGMStream &ioStream, CATCGMOutput &os, int VersionNumber = 1);
  virtual CATCheckDiagnostic CheckOutput(CATCGMOutput & os);

  // Input
protected:
  static CATString _OperatorId;
  // Configuration
  CATSoftwareConfiguration *_Config;
  CATBoolean _solverMode;

  // Extrapolation mode data and methods
  CATBoolean _ExtrapolMode;
  short _ExtrapolFlags[3];
  //CATTolerance Object
  const CATTolerance & _TolObject;

  //Input
  CATConnectTool *_tool1, *_tool3;
  CATSurface *_surface1, *_surface2, *_surface3;
  CATSurLimits _lim1, _lim2, _lim3;
  CATLONG32 _orient1, _orient12, _orient23, _orient3;
  CATSurParam _param1, _param2, _param3;
  double _radius1, _radius3;
  CATCurve * _Spine1, *_Spine3;
  const CATMathFunctionX *_VarRadius1, *_VarRadius3;

  CATBoolean _ConstConst;
  CATBoolean _VarVar;
  CATLONG32 _Dim;

  CATMathSystem *_sphereSystem;
  CATMathIntervalND _Domain;
  double _InputInit[8];
  double _SolutionPoint[8];

   // Output
  CATLONG32 _diagnostic;
  CATSurParam _resParam1, _resParam2, _resParam3;

  CATMathPlane _mathPlanes[3];

private:
  static void ShowBoundedSurface(CATGeoFactory &iFactory, CATSurface &iSurface, CATSurLimits &iLimits, unsigned int iSurfaceColor, unsigned int iBoundaryColor);
  static void ShowParam(CATGeoFactory &iFactory, CATSurParam &iParam, CATSurface &iSurface, double iNormalScale, unsigned int iColor);
  static void ShowPlane(CATGeoFactory &iFactory, CATMathPlane &iPlane,unsigned int iColor);
};


ExportedByConnect
CATConnectSphereReconverge *
CreateCATConnectSphereReconverge(CATGeoFactory *iFactory,
                                 CATSoftwareConfiguration *iConfig,

                                 CATSurface *iSupport1,
                                 const CATLONG32 iOrientation1,
                                 const CATSurLimits &iLimit1,
                                 const CATSurParam &iParam1,

                                 CATSurface *iSupport2,
                                 const CATLONG32 iOrientation2,
                                 const CATSurLimits &iLimit2,
                                 const CATSurParam &iParam2,

                                 CATSurface *iSupport3,
                                 const CATLONG32 iOrientation3,
                                 const CATSurLimits &iLimit3,
                                 const CATSurParam &iParam3,

                                 CATConstantFilletTool *iConnectTool);

ExportedByConnect
void
Remove(CATConnectSphereReconverge *iOperator);


// INLINE methods implementation

INLINE void CATConnectSphereReconverge::SetSolverMode(CATBoolean iSolverMode)
{
  _solverMode = iSolverMode;
}

INLINE CATLONG32 CATConnectSphereReconverge::GetDiagnostic() const
{
  return _diagnostic;
}

INLINE CATLONG32 CATConnectSphereReconverge::GetPoints(CATSurParam &oParam1,
                                                       CATSurParam &oParam2,
                                                       CATSurParam &oParam3) const
{
  oParam1 = _resParam1;
  oParam2 = _resParam2;
  oParam3 = _resParam3;

  return _diagnostic;
}

INLINE CATLONG32 CATConnectSphereReconverge::GetMathPlanes(CATMathPlane &oMathPlane12,
                                                           CATMathPlane &oMathPlane23,
                                                           CATMathPlane &oMathPlane31) const
{
  oMathPlane12 = _mathPlanes[0];
  oMathPlane23 = _mathPlanes[1];
  oMathPlane31 = _mathPlanes[2];
  
  return _diagnostic;
}

#endif // !CATConnectSphereReconverge_H
