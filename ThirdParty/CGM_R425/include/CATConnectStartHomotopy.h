//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 
//==========================================================================
//
// CATConnectStartHomotopy:
// Connect operator includes constant radius fillet, variable radius fillet,
// edge-surface fillet, curve-surface fillet and chamfer.
//
//==========================================================================
//
// Usage notes:
// The nature of the surface is defined by the given Geometric Profile.
//
//==========================================================================
// Sep. 98  FBD Documentation                                      F. Bezard
// 23/06/22 NLD Mise au propre
//               - detabulation
//               - smart indent
//             Numérotation des constructeurs
//             Suppression argument iMode dans tous les constructeurs
//========================================================================== 


#ifndef CATConnectStartHomotopy_H
#define CATConnectStartHomotopy_H

#include "Connect.h"
#include "CATSkillValue.h"
#include "CATMathDef.h"
#include "CATCrvLimits.h"
#include "CATSurLimits.h"
#include "CATCrvParam.h"
#include "CATSurParam.h"
#include "CATMathDirection.h"
#include "CATMathPoint.h"
#include "CATMathImplicitSystem.h"
#include "CATCGMVirtual.h"

const CATLONG32 MaxDim = 8;

class CATBody;
class CATCurve;
class CATGeoFactory;
class CATSurface;
class CATPCurve;
class CATConnectTool;
class CATPointOnSurface;
class CATSoftwareConfiguration;
class CATIPGMConnectTool;

//-----------------------------------------------------------------------------
// 
// CATConnectStartHomotopy class specification :
// 
//-----------------------------------------------------------------------------

class ExportedByConnect CATConnectStartHomotopy : public CATCGMVirtual
{

public:

  //---------------------------------------------------------------
  //---- Methods for basic manipulations
  //---------------------------------------------------------------

  //--------------------------------------------------------------- CATConnectStartHomotopy_Constructor1
  CATConnectStartHomotopy(      CATGeoFactory            *  iFactoryPtr  ,
                                CATSoftwareConfiguration *  iConfig      ,
                                CATPCurve                *  iPcrv1       ,
                          const CATCrvParam               & iParamOnPcrv1,
                          const CATLONG32                   iOrientation1,
                                CATPCurve                *  iPcrv2       ,
                          const CATCrvParam               & iParamOnPcrv2,
                          const CATLONG32                   iOrientation2,
                          const CATConnectTool           *  iConnectTool ,
//                        const CATSkillValue               iMode        ,
                                double                   *  vec          = 0,
                                CATLONG32                   iVecMode     = 0);

  //--------------------------------------------------------------- CATConnectStartHomotopy_Constructor2
  CATConnectStartHomotopy(      CATGeoFactory            *  iFactoryPtr  ,
                                CATSoftwareConfiguration *  iConfig      ,
                                CATPCurve                *  iPcrv1       ,
                          const CATCrvParam               & iParamOnPcrv1,
                          const CATLONG32                   iOrientation1,
                                CATPCurve                *  iPcrv2       ,
                          const CATCrvParam               & iParamOnPcrv2,
                          const CATLONG32                   iOrientation2,
                                CATIPGMConnectTool       *  iIConnectTool,
//                        const CATSkillValue               iMode        ,
                                double                   *  vec          = 0,
                                CATLONG32                   iVecMode     = 0);

  /**
  * Constructor avec des limites des surfaces 
  **/
  //--------------------------------------------------------------- CATConnectStartHomotopy_Constructor3
  CATConnectStartHomotopy(      CATGeoFactory            *  iFactoryPtr  ,
                                CATSoftwareConfiguration *  iConfig      ,
                                CATPCurve                *  iPcrv1       ,
                          const CATCrvParam               & iParamOnPcrv1,
                          const CATLONG32                   iOrientation1,
                                CATSurLimits              & iLimit1      ,
                                CATPCurve                *  iPcrv2       ,
                          const CATCrvParam               & iParamOnPcrv2,
                          const CATLONG32                   iOrientation2,
                                CATSurLimits              & iLimit2      ,
                          const CATConnectTool           *  iConnectTool ,
//                        const CATSkillValue               iMode        ,
                                double                   *  vec          = 0,
                                CATLONG32                   iVecMode     = 0);

  /**
  * Constructor avec des limites des surfaces 
  **/
  //--------------------------------------------------------------- CATConnectStartHomotopy_Constructor4
  CATConnectStartHomotopy(      CATGeoFactory            *  iFactoryPtr  ,
                                CATSoftwareConfiguration *  iConfig      ,
                                CATPCurve                *  iPcrv1       ,
                          const CATCrvParam               & iParamOnPcrv1,
                          const CATLONG32                   iOrientation1,
                                CATSurLimits              & iLimit1      ,
                                CATPCurve                *  iPcrv2       ,
                          const CATCrvParam               & iParamOnPcrv2,
                          const CATLONG32                   iOrientation2,
                                CATSurLimits              & iLimit2      ,
                                CATIPGMConnectTool       *  iIConnectTool,
//                        const CATSkillValue               iMode        ,
                                double                   *  vec          = 0,
                                CATLONG32                   iVecMode     = 0);
  /**
  * Destructor.
  */
  ~CATConnectStartHomotopy();

  /**
  * Runs a CATConnectStartHomotopy operator in <tt>ADVANCED</tt> mode.
  */
  void Run();

  /**
  *  Method GetCurve : Available when Diagnostic=1 or 2
  *  returns the curve solution 
  *  is a line (chamfer) or a circle (fillet).
  */
  
  CATCurve* GetCurve() const;


  
  /**
  *  Method GetSurfaceParam : Available when Diagnostic=1 
  *   returns parameters (u,v) of 
  *   point of the profile on surface surf1 if CATSurface==surf1
  *   point of the profile on surface surf2 if CATSurface==surf2
  */

  void GetParamCircleSurface(CATMathPoint &ioCentre,
                             CATMathPoint &ioPoint1,
                             CATMathPoint &ioPoint2,
                             double &oRadius) const;  
  
  CATSurParam GetSurfaceParam(const CATSurface *) const;
  
  
  /**
  *  Method GetCrvParam : Available when Diagnostic=1 and with variable tool
  *   returns parameters (w) of point on the Spine. 
  */
  
  CATCrvParam GetCrvParam(const CATCurve *) const;
  
  /**
  *  Method GetStartPoint 
  * returns the Init in R4 or R5 
  */
  
  void GetStartPoint(double * oStartPoint) const;

  /**
  *  Method GetPointOnSurface : Available when Diagnostic=1
  *  returns point of the profile on surface surf1 if CATSurface==surf1
  *  returns point of the profile on surface surf2 if CATSurface==surf2
  */
  
  CATPointOnSurface* GetPointOnSurface(const CATSurface *) const ;
  
  /**
  * Method Diagnostic
  * returns 0 if there is no solution
  * returns 1 if there is one exact solution
  * returns 2 if there is a solution on the tangents planes
  */
  
  CATLONG32 GetDiagnostic();

  /**
  * Method SetSpineLimits 
  * only in case of variable fillet
  */
  void SetSpineLimits(const CATCrvParam* iSpineLow, const CATCrvParam* iSpineHigh);

  /**
  * Method SetSpineLimits 
  * only in case of variable circle fillet
  */
  void SetSpineLimits(const CATCrvParam* iCircleSpineLow, const CATCrvParam* iCircleSpineHigh, 
                      const CATCrvParam* iRadiusSpineLow, const CATCrvParam* iRadiusSpineHigh);

  /**
  * Method SetHoldCurve 
  * only in case of HoldCurveChamfer
  */
  CATBoolean SetHoldCurve(CATPCurve * iHoldCurve,  const CATCrvLimits &iCurveLimits);
  
  /**
  * Method SetVecMode
  * only available for constant fillet yet
  * iVecMode = 0 : Vec norm = resolution
  * iVecMode = 1 : Vec norm = f(alpha) alpha angle between N1 and N2 on the common point
  */
  void SetVecMode(CATLONG32 iVecMode);

  // do not use
  //--------------------------------------------------------------- CATConnectStartHomotopy_Constructor5
  CATConnectStartHomotopy(      CATGeoFactory            *  iFactoryPtr  ,
                                CATPCurve                *  iPcrv1       ,
                          const CATCrvParam               & iParamOnPcrv1,
                          const CATLONG32                   iOrientation1,
                                CATSurLimits              & iLimit1      ,
                                CATPCurve                *  iPcrv2       ,
                          const CATCrvParam               & iParamOnPcrv2,
                          const CATLONG32                   iOrientation2,
                                CATSurLimits              & iLimit2      ,
                          const CATConnectTool           *  iConnectTool ,
 //                       const CATSkillValue               iMode        ,
                                double                   *  vec          = 0,
                                CATLONG32                   iVecMode     = 0);

  // do not use
  //--------------------------------------------------------------- CATConnectStartHomotopy_Constructor6
  CATConnectStartHomotopy(      CATGeoFactory            *  iFactoryPtr  ,
                                CATPCurve                *  iPcrv1       ,
                          const CATCrvParam               & iParamOnPcrv1,
                          const CATLONG32                   iOrientation1,
                                CATPCurve                *  iPcrv2       ,
                          const CATCrvParam               & iParamOnPcrv2,
                          const CATLONG32                   iOrientation2,
                          const CATConnectTool           *  iConnectTool ,
//                        const CATSkillValue               iMode        ,
                                double                   *  vec          = 0,
                                CATLONG32                   iVecMode     = 0);
  // do not use
  //--------------------------------------------------------------- CATConnectStartHomotopy_Constructor7
  CATConnectStartHomotopy(      CATGeoFactory            *  iFactoryPtr  ,
                                CATPCurve                *  iPcrv1       ,
                          const CATCrvParam               & iParamOnPcrv1,
                          const CATLONG32                   iOrientation1,
                                CATPCurve                *  iPcrv2       ,
                          const CATCrvParam               & iParamOnPcrv2,
                          const CATLONG32                   iOrientation2,
                                CATIPGMConnectTool       *  iIConnectTool,
//                        const CATSkillValue               iMode        ,
                                double                   *  vec          = 0,
                                CATLONG32                   iVecMode     = 0);
private:
  // pkc 4/11/2005
  // factorisation du code
  void InitializeDataMembers(      CATGeoFactory            *  iFactoryPtr  ,
                                   CATSoftwareConfiguration *  iConfig      ,
                                   CATPCurve                *  iPcrv1       ,
                             const CATCrvParam               & iParamOnPcrv1,
                             const CATLONG32                   iOrientation1,
                                   CATSurLimits              & iLimit1      ,
                                   CATPCurve                *  iPcrv2       ,
                             const CATCrvParam               & iParamOnPcrv2,
                             const CATLONG32                   iOrientation2,
                                   CATSurLimits              & iLimit2      ,
                             const CATConnectTool           *  iTool        ,
                                   CATIPGMConnectTool       *  iITool       ,
                                   double                   *  iVec         ,
                                   CATLONG32                   iVecMode     );

  // cqi 21nov05 - Linearized problem solving (requires an input vector; see constructor)
  //
  // This method takes the init point computed on common curve (u=_Init[0],v=_Init[1],r=_Init[2],s=_Init[3])
  // and solve the linearized associated problem (ie. Plane/Plane bitangency).
  // The method returns 0 if it failed or irrelevant configuration level, and returns 1 if it succeeded.
  // If so, _Init is adjusted with linearized problem solution.
  //
  // NB.: this method manages specific constant fillet vector mode (see SetVecMode(0))
  int SolveLinearizedInit();

  // cqi 16nov05 - Many solutions could exist and standard solving method may converge on the bad one.
  //
  // This method checks that current solution 'ioXsol' is on the right side (thanks to Common Curve orthogonal direction - iVec).
  // If not, it tries an alternative solving method (Safe Newton like).
  // The method :
  //  * returns -1 if no relevant solution has been found.
  //  * returns  0 if nothing is done (irrelevant required data, bad versionning level).
  //  * returns  1 if it succeeded, then solution is stored in 'ioXsol'.
  int CheckSolution(CATMathImplicitSystem * iImplicitSystem, CATMathIntervalND & iDomain, double * iN, double iD,
                    CATLONG32 iDim, double * iXinit, double * ioXsol);

  // The method :
  //  * returns -1 if UV is on the wrong side.
  //  * returns  0 if nothing is done (irrelevant required data, bad versionning level).
  //  * returns  1 if UV is on the right side.
  int ValidateUVSide(int iNumSupport, double iUref, double iVref, double iU, double iV);

private:
        CATPCurve                * _PCrv1,
                                 * _PCrv2;
        CATLONG32                  _iOrientation1,
                                   _iOrientation2;
        CATCrvParam                _iParamOnCrv1,
                                   _iParamOnCrv2,
                                   _ParamOnSpine;
        CATSurParam                _iParamOnSur1,
                                   _iParamOnSur2;
        CATSurLimits               _limit1,
                                   _limit2;
        CATPCurve                * _HoldCurve;
        CATCrvLimits               _HCLimits;

        CATMathDirection           _N1,
                                   _N2;
        CATMathPoint               _start,
                                   _end,
                                   _C;
        CATSurface               * _Surf1,
                                 * _Surf2;
        CATGeoFactory            * _Factory;
  const CATConnectTool           * _Tool;
        CATIPGMConnectTool       * _ITool;
        double                     _radius;
        double                     _Init[MaxDim];
        CATLONG32                  _Diagnostic;
        double                   * _Vec;
  const CATCrvParam              * _SpineLow;
  const CATCrvParam              * _SpineHigh;
  const CATCrvParam              * _CircleSpineLow;
  const CATCrvParam              * _CircleSpineHigh;
  const CATCrvParam              * _RadiusSpineLow;
  const CATCrvParam              * _RadiusSpineHigh;
        CATLONG32                  _VecMode;

        CATSoftwareConfiguration * _SoftwareConfiguration;
  const CATTolerance             & _TolObject;

};

//-----------------------------------------------------------------------------
// 
// Public construction and destruction 
//
//-----------------------------------------------------------------------------

/**
* Creates an operator .
*/

ExportedByConnect  
CATConnectStartHomotopy * CreateConnectStart (      CATGeoFactory            *  iFactoryPtr   ,
                                                    CATSoftwareConfiguration *  iConfig       ,
                                                    CATPCurve                *  iPcrv1        ,
                                              const CATCrvParam               & iParamOnPcrv1 ,
                                              const CATLONG32                   iOrientation1 ,
                                                    CATSurLimits              & iLimit1       ,
                                                    CATPCurve                *  iPcrv2        ,
                                              const CATCrvParam               & iParamOnPcrv2 ,
                                              const CATLONG32                   iOrientation2 ,
                                                    CATSurLimits              & iLimit2       ,
                                              const CATConnectTool           *  iProfilePtr   ,
                                              const CATSkillValue               iMode         ,
                                                    double                   *  vec           = 0);
/**
*  Remove
*/

ExportedByConnect  void Remove (CATConnectStartHomotopy *iConnectPtr);



#endif
