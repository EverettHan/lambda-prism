#ifndef CATIntersectionMultiSurface_H
#define CATIntersectionMultiSurface_H

// COPYRIGHT DASSAULT SYSTEMES  2000
//=============================================================================
// 15/03/17 R1Y  Added an interpolation mode for the operator.
// 26/06/17 R1Y  Added access functions for projection data for help points.
// 08/02/21 LJL2 Added SetXGMFlag()
// 11/04/21 LJL2 Added SetChordalError() and SetAngularError()
//=============================================================================

#include "Y30C3XGG.h"
#include "CATGeoOperator.h"
#include "CATMathDef.h"
#include "CATString.h"
#include "CATCreateIntersection.h"
#include "CATLISTP_CATMathPoint.h"
#include "CATListOfCATEdgeCurves.h"
#include "CATCurve.h"
#include "CATListOfHelpPointProjData.h"


class CATListOfCATCurves;
class CATMultiSurface;
class CATMathPoint;
class CATEdgeCurve;

/**
* @nodoc
* Classe permettant l'intersection de deux reseaux de surfaces.
*
*
*/
class ExportedByY30C3XGG CATIntersectionMultiSurface : public CATGeoOperator
{
   CATCGMVirtualDeclareClass(CATIntersectionMultiSurface);
public:
   /**
   * @nodoc
   *     MultiSurfaces  :  Liste des surfaces. Les surfaces sont supposees rangees dans la liste de maniere a
   *                       former une matrice NU * NV. Deux paves contigus de la matrice sont supposes continus
   *                       G0 (au sens du modeleur emetteur), les limites courantes de chaque surface correspondnt a la
   *                       partie utile (a revoir).
   *
   */
   
   CATIntersectionMultiSurface(CATGeoFactory * iFactory);
   
   /**
   * @nodoc
   * Destructor.
   */
   virtual ~CATIntersectionMultiSurface();
   
   /**
   * @nodoc
   * Set the list of init/exit 3D points that defines limitations of the intersection  
   */
   virtual void SetStartingPoints(const CATLISTP(CATMathPoint) * iPointList) = 0;
   
   /**
   * @nodoc
   * Set the list of CrvParam that defines the intersection  
   */
   virtual void SetParamOnCurve(CATListOfDouble & iCrvList) = 0;
   
   /**
   * @nodoc
   * Active the Bound Mod for the intersection the intersection  
   * IndexOperand should have the value 0 or 1 to set the multisurfacesurface 
   */
   virtual void SetBoundModON(CATBoolean iboundMod,
                              CATLONG32  iIndexOperand) = 0;
    
   /**
   * @nodoc
   * Set the singularity status of the extremities, Init or Exit
   * TRUE for singular, FALSE if not
   */
   virtual void SetSingularityFlag(CATBoolean iInitFlag,
                                   CATBoolean iExitFlag) = 0;
   
   /**
   * @nodoc
   * Set the maximum distance allowed between the intersection curve
   * and the chord defined with starting points
   */
   virtual void SetChordalError(double iChordalError) = 0;

   /**
   * @nodoc
   * Set the maximum angle allowed between the tangents and the chord
   * defined with starting points
   */
   virtual void SetAngularError(double iAngularError) = 0;

   /**
   * @nodoc
   * Set the flag when the intersection operator is called with xgm (intersection
   * curve for blend computation)
   */
   virtual void SetXGMFlag(CATBoolean iXGMFlag) = 0;

   /**
   * @nodoc
   * to provide the tolerance on the init (size of the init vertex)
   */
   virtual void SetTolOnInit(const double & iTolOnInit) = 0;
   
   /**
   * @nodoc
   * to provide the tolerance on the exit (size of the exit vertex)
   */
   virtual void SetTolOnExit(const double & iTolOnExit) = 0;
   
   /**
   * @nodoc
   * DO NOT USE
   */
   virtual void SetDoNot3DExtend(CATBoolean iNoExtend = TRUE) = 0;

   /**
   * @nodoc
   * Allow a small extrapolation of the surfaces if needed
   *  - by default extrapolation of only NURBS is allowed
   *  - the first argument turns on/off extrapolation (of NURBS)
   // - the second arguement turns on/off extrapolation of Offset surfaces
   */
   virtual void SetExtrapolationMode(const CATBoolean iAllowExtrapolation = TRUE,
                                     const CATBoolean iAllowOffsetSurfaces = FALSE) = 0;

   /** @nodoc @nocgmitf */
   virtual void SetNoInterpolationBackup() = 0;

   /**
   * @nodoc
   * Creates the solution curve of <tt>this</tt> CATIntersectionMultiSurface operator.
   */
   virtual void GetResults(CATLISTP(CATEdgeCurve) * oEdgeCrvList)=0;
   virtual void GetResults(CATLISTP(CATCurve) * oCrvList)=0;
   
   /** @nodoc @nocgmitf */
   virtual CATBoolean IsResultOK(int & oLastHelpPointOK, CATBoolean & oResultFromExit) const = 0;

   /** @nodoc @nocgmitf */
   virtual CATBoolean StoppedAtBorder(short oBorderData[]) const = 0;

   /**
   * @nodoc @nocgmitf
   * Set the projection data for help points for <tt>this</tt> CATIntersectionMultiSurface operator.
   */
   virtual CATBoolean SetHelpPointProjData(CATListOfHelpPointProjData & iHelpPointProjData) = 0;

   /**
   * @nodoc @nocgmitf
   * Get the (possibly updated) projection data for help points for <tt>this</tt> CATIntersectionMultiSurface operator.
   */
   virtual CATBoolean GetHelpPointProjData(CATListOfHelpPointProjData & oHelpPointProjData) const = 0;

   /**
   * @nodoc @nocgmitf
   * Static method to create the operator
   */
   static CATIntersectionMultiSurface* CreateIntersectionMultiSurface(       CATGeoFactory            * iWhere,
                                                                             CATSoftwareConfiguration * iConfig,
                                                                             CATMultiSurface          * iSurface1,
                                                                             CATMultiSurface          * iSurface2,
                                                                       const CATBoolean                 iInterpolMode,
                                                                       const CATBoolean                 iParasolidMode = FALSE);
};

/**
 * @nodoc
 * Create MultiSurface Intersection Operator
 */
ExportedByY30C3XGG
CATIntersectionMultiSurface * CATCreateIntersectionMultiSurface(      CATGeoFactory            * iWhere,
                                                                      CATSoftwareConfiguration * iConfig,
                                                                      CATMultiSurface          * iSurface1,
                                                                      CATMultiSurface          * iSurface2,
                                                                const CATBoolean                 iInterpolMode = FALSE,
                                                                const CATBoolean                 iParasolidMode = FALSE);


/**
 * @nodoc
 * Oder Init and Exit point in _InitPointList 
 */
// StartPoint is between point of index _IndexLim[0][0] and _IndexLim[0][1]
// EndPoint   is between point of index _IndexLim[1][0] and _IndexLim[1][1]
// Startpoint is point n => _IndexLim[0][0] = -1  _IndexLim[0][1] = n
// Endpoint   is point n => _IndexLim[0][0] =  n  _IndexLim[0][1] = -1-
ExportedByY30C3XGG
int CATIntersectionMultiSurface_OrderInitExit(CATGeoFactory          * _Factory, 
                                              CATLISTP(CATMathPoint) * _InitPointList,
                                              CATBoolean             & _Closed_Points,
                                              CATBoolean             & _Closed_InitExits,                          
                                              int                      _IndexLim[2][2]);

/**
 * @nodoc
 * @nocgmitf
 * Utility function for CATIntersectionMultiSurface_OrderInitExit
 */
ExportedByY30C3XGG
int CATIntersectionMultiSurfaceSW_OrderInitExitBackup(const CATMathPoint         * iInit,
                                                      const CATMathPoint         * iExit,
                                                            CATMathSetOfPointsND * iSet3D,
                                                      const CATTolerance         & iTol,
                                                            int                    _IndexLim[2][2]);

/**
 * @nodoc
 * @nocgmitf
 * Utility function for CATIntersectionMultiSurface_OrderInitExit
 */
ExportedByY30C3XGG
CATBoolean CATIntersectionMultiSurfaceSW_CheckSegmentProjection(const CATMathPoint * iPoint, 
                                                                const double         iPt1[], 
                                                                const double         iPt2[],
                                                                const CATTolerance & iTol,
                                                                      double       & oProjDistSq);
#endif
