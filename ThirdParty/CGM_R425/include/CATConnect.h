//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 1997
//==========================================================================
//
// CATConnect:
// Connect operator includes constant radius fillet, variable radius fillet,
// edge-surface fillet, curve-surface fillet and chamfer.
/**
 * Interface representing the operator of connection of two CATSurfaces.
 *<br>This includes constant radius fillet, variable radius fillet(not yet
 * implemented), curve surface fillet and chamfer (not yet implemented).
 * The nature of the generated surface is defined by a geometric profile
 * ( circular for a fillet, linear for a chamfer, ..). This surface is
 * composed of pieces called <tt>CATConnectPieces</tt>. Each
 * <tt>CATConnectPiece</tt> is a C2 continuous biparametric entity,
 * whereas the global surface is C0 continuous.
 *<ul>
 *<li>The CATConnect operator is designed to be open to external
 * implementations.
 *<li>It is created with the <tt>CreateConnect</tt> method within a
 *<tt>CATGeoFactory</tt>, but is not streamable.
 *<li>In case of <tt>BASIC</tt>
 * mode, the operation is automatically performed.
 *<li>In case of <tt>ADVANCED</tt>
 * mode, the user may precise options with the <tt>SetXxx</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method.
 *<li>The results are accessed thanks to iterators, that allow to handle
 * multiple solutions.
 *<li> The operator is removed from the memory with the <tt>Remove</tt> method.
 *</ul>
 */
//
//==========================================================================
//
// Usage notes:
// The nature of the surface is defined by the given Geometric Profile.
//
//==========================================================================
//   /05/97     Creation                                 P. Sebah
// 11/09/97     Desctructor in protected area              X. Liu
// 06/11/97     Added Target Surpport and new domaine      X. Liu
//                         (double limitation)
//   /12/97     Documentation                                       C. Keribin
// 12/03/20 Q48 Headers etc for math versioning
// 23/03/22 S9L Overlap of twisted piece with adjacent non-twisted pieces
//==========================================================================


#ifndef CATConnect_H
#define CATConnect_H

#include "Connect.h"
#include "CATSkillValue.h"
#include "CATCGMOperator.h"
#include "CATMathDef.h"
#include "CATConnectPiece.h"
#include "CATIntersectionSign.h"
#include "CATCrvLimits.h"
#include "CATSurLimits.h"
#include "CATListOfCATSurfaces.h"
#include "CATListOfCATSurParams.h"
#include "CATIACGMLevel.h"

class CATGeoFactory;
class CATSurface;
class CATPCurve;
class CATPoint;
class CATConnectTool;
class CATIPGMConnectTool;
class CATMathSetOfPointsND;
class CATEdgeCurve;
class CATCrvParam;
class CATSoftwareConfiguration;
class CATCurve;
class CATPointOnEdgeCurve;
class CATConnectComputer;
class CATTopologyCallBacks;

// C++11
#include "CATGeoOpVirtual.h"

//-----------------------------------------------------------------------------
//
// CATConnect class specification :
//
// A CATConnet is composed of several components, called CATConnectPiece.
// Each CATConnect is a continuous biparametric entity defined by the profile.
//
//-----------------------------------------------------------------------------

class ExportedByConnect CATConnect :public CATCGMOperator
{

  // protected: // pour que les copains puissent nettoyer (RR)
  CATCGMVirtualDeclareClass(CATConnect);
public:
/**
* Destructor.
  */
  virtual ~CATConnect();

  /**
  * Constructor.
  */
  //Do not use - Use the constructor woth Config
  CATConnect(CATGeoFactory * factory);
  CATConnect(CATGeoFactory            * factory,
             CATSoftwareConfiguration * iConfig);

  //Ne pas utiliser - A supprimer - Passer la config par le constructeur!!
  void SetSoftwareConfiguration(CATSoftwareConfiguration * iConfig);
  
public:

  //---------------------------------------------------------------
  //---- Methods for basic manipulations
  //---------------------------------------------------------------


  /**
  * Returns the number of pieces of the resulting surface of a CATConnect
  * operator.
  */
  virtual CATLONG32 GetNumberOfPieces() const = 0;

  /**
  * Returns the number computed init points
  * iType
  * <dl><dt><tt>0</tt><dd> All
  *     <dt><tt>1</tt><dd> Homotopic
  *     <dt><tt>2</tt><dd> Boundary
  *     <dt><tt>3</tt><dd> Inner
  * </dl>
  */

  virtual CATLONG32 GetNumberOfInits(int iType = 0) const = 0;

  /**
  * Initializes the iterator of the resulting pieces of a CATConnect operator.
  *<br>By default, the initialization is performed once the operator has been
  * calculated, and is therefore only used to read the solutions again.
  */
  virtual void Beginning() = 0;

  /**
  * Points to the next solution piece of a CATConnect operator.
  *<br>After <tt>Beginning</tt>, it moves to the first piece.
  * @return
  *<dl><dt><tt>1</tt> <dd>if there is a solution piece.
  *    <dt><tt>0</tt> <dd>no more solution piece.</dl>
  */
  virtual CATBoolean Next() = 0;

  /**
  * Returns a pointer to the current solution piece of a CATConnect operator.
  *<br>Creates the current solution piece if necessary.
  */
  virtual CATConnectPiece * GetOnePiece() = 0;

  /**
  * Returns a CATBoolean for knowing if the current solution is twisted.
  * @return
  *<dl><dt><tt>1</tt> <dd>if the current solution is twisted.
  *    <dt><tt>0</tt> <dd>if the current solution is not twisted.</dl>
  */
  virtual CATBoolean IsCurrentPieceTwisted() = 0;

  /**
  * Returns overlap status if the current piece is ovelapping with other pieces.
  * @return
  *<dl><dt><tt>0</tt> <dd>if the current piece is not overlapped.
  *    <dt><tt>1</tt> <dd>if the current piece is patially overlapped
  *    <dt><tt>2</tt> <dd>if the current piece is completely overlapped</dl>
  */
  virtual CATLONG32 GetCurrentPieceOverlap() const = 0;

  //---------------------------------------------------------------
  //---- Methods specifying advanced options
  //---------------------------------------------------------------

  // double limits treatment
  /**
  * Modifies the CATSurfaces limitations to take into account for a CATConnect
  * operator.
  *<br> It does not change the current CATSurfaces
  * limitations. The proposed limitations have to be included into the
  * current limitations.
  *<br>In case of <tt>ADVANCED</tt> mode.
  */
  // TO BE REMOVED - BEGIN
  virtual void HoldDomain(const CATSurLimits * iNewLimitsForSupport1,
                          const CATSurLimits * iNewLimitsForSupport2) = 0;
  // TO BE REMOVED - END
  virtual void SetLimitsOnSupport(const CATLONG32      iSupportId,
                                  const CATSurLimits & iLimits) = 0;
  virtual void SetLimitsOnSupport(const CATLONG32      iSupportId,
                                  const CATCrvLimits & iLimits) = 0;

  virtual void SetSupportSurOrientation(const CATLONG32 iSupportId,
                                        const CATLONG32 iOrientation) = 0;
  virtual void SetSupportCrvOrientation(const CATLONG32 iSupportId,
                                        const CATLONG32 iOrientation) = 0;

  virtual void SetSpineLimit(const CATCrvParam & iParam,
                             const CATLONG32     iSpineLimitSide) = 0;
  virtual void SetSpineOrientation(const CATLONG32 iOrientation) = 0;

  // If set to <tt>TRUE</tt> allows for the domain to be enlarged to contain init points that would be discarded otherwise.
  // It does not try to find additional init points. Ordinarily the init points will be close to the specified limits.
  // Only implemented for constant and chordal fillet connect with surface-surface support.

  virtual void SetRelaxDomainForInits(CATBoolean iRelaxDomainForInits) = 0;

  // "exact limits" are the limits of a support without any extrapolation
  // (ie limits of the face or edge ). It is only to give an information
  // concerning the position of the face (or edge). The domain on which
  // the operator is going to run is set by "SetLimitsOnSupport" methods
  virtual void SetExactLimitsOnSupport(const CATLONG32      iSupportId,
                                       const CATSurLimits & iLimits) = 0;
  virtual void SetExactLimitsOnSupport(const CATLONG32      iSupportId,
                                       const CATCrvLimits & iLimits) = 0;

  /**
  * Should exact domain be used for computation of init points for marching?
  * <br> Exact domain must be set using <tt> SetExactLimitsOnSupport </tt> for each support domain
  * @param iFlag
  * <dl><dt><tt>TRUE</tt><dd> Use exact domain for init computation
  *     <dt><tt>FLASE</tt><dd> Do not use exact domain for init computation
  * </dl>
  */
  virtual void UseExactDomainForInit(CATBoolean iFlag) = 0;

  /**
  * Extrapolates the CATConnect solution until one of the operands boundary.
  *<br>This method has a greater priority than the <tt>HoldDomain</tt> method: the solution
  * can go outside the domain defined by <tt>HoldDomain</tt>.
  *<br>In case of <tt>ADVANCED</tt> mode.
  *@param iSupportIdToReach
  * <dl><dt><tt>CATConnectFirstSupport</tt><dd>The first CATConnect operand
  *     <dt><tt>CATConnectSecondSupport</tt><dd>The second CATConnect operand
  *     <dt><tt>CATConnectThirdSupport</tt><dd>The third surface of tangency
  *(not yet implemented)</dl>
  */
  virtual void ReachBoundaryOf(const CATLONG32 iSupportIdToReach) = 0;

  /**
  * AddSmoothLimiting
  * Dedicated methods that allows the caller to give further information so as to avoid unecessary supports
  * extrapolations.
  *
  * Surface support type
  *
  * @param iReportID
  * ID of the support
  * @param iLimitingCurve
  * Parametric curve lying on iReportID support surface used as a frontier to cross
  * @param iLimits
  * Specified limits so as to control frontier size
  * @param iMatterSide
  * -1 or +1 so as to indicate matter side (relatively to iLimitingCurve and iReportID support surface orientations)
  *
  * This method should be called as many times as user wants to set a limiting curve. If connect solution crosses
  * one of these limiting curve, all extrapolations will be forbidden along the side defined by this crossing.
  *
  * Limitation: iLimitingCurve must be an isoparametric parametric line.
  */
  virtual void AddSmoothLimiting(CATLONG32      iReportID,
                                 CATPCurve    * iLimitingCurve,
                                 CATCrvLimits & iLimits,
                                 short          iMatterSide,
                                 CATPCurve    * iOpposingCurve = NULL,
                                 CATCrvLimits * iOpposingLimits = NULL) = 0;
  /*
  *
  * EdgeCurve support type
  *
  * @param iReportID
  * ID of the support
  * @param iLimitingPOEC
  * POEC lying on iReportID support EdgeCurve used as a frontier to cross
  * @param iMatterSide
  * -1 or +1 so as to indicate matter side (relatively to iReportID support EdgeCurve orientation)
  *
  * Same usage notes as above.
  */
  virtual void AddSmoothLimiting(CATLONG32             iReportID,
                                 CATPointOnEdgeCurve * iLimitingPOEC,
                                 short                 iMatterSide) = 0;

  // user init specification
  /**
  * Imposes initial and/or final points of the resulting surface of
  * a CATConnect operator.
  *<br>In case of <tt>ADVANCED</tt> mode.
  * @param iSetOfInitPoints
  * The pointer to a xxxdimension CATMathSetOfPointsND containing initial and/or final
  * points of the solution. This argument and the following one give the
  * definition of the pieces of the CATConnect.
  * @param iStartingSignatureOnFirstSurface
  * The driving direction of the intersection edge on the first surface
  * with regards to each surface
  * normals. The natural way of the intersection edge at the starting point
  * is such that the tangent at this point has the same direction as the
  * vector product of the normals of each surface.
  *<br>Consider that the surface normal represents the outside of the matter
  * delimited by a surface. A positive signature implies that the resulting
  * matter of the intersection is on the edge left.
  * <dl><dt><tt>CATIntersectionSignPositive</tt><dd>The resulting
  * matter of the intersection is on the edge left.
  *     <dt><tt>CATIntersectionSignNegative</tt><dd>The resulting
  * matter of the intersection is on the edge right.
  *     <dt><tt>CATIntersectionSignSameDirection</tt><dd>
  *     <dt><tt>CATIntersectionSignOppositeDirection</tt><dd>
  *     <dt><tt>CATIntersectionSignUnknown</tt><dd>
  *     <dt><tt>CATIntersectionSignUnset</tt><dd></dl>
  * @param iLoopSearch
  * <dl><dt><tt>1</tt><dd>search of the scalop (loop) configurations
  *     <dt><tt>0</tt><dd>otherwise </dl>
  */
  virtual void SetStartingPoints(CATMathSetOfPointsND * iInitPoints,
                                 CATIntersectionSign    iStartingSignatureOnFirstSurface,
                                 CATBoolean             iLoopSearch = 0) = 0;

  virtual void SetPointingPoint(double * iPointingPoint) = 0;

  virtual CATBoolean IsPointingPointReached() const = 0;

  /**
  * SetCommonCurve
  * Specifies a curve common to the support surfaces to be filleted, and a point on this curve
  * so as to help init searching techniques.
  *CATConnectSurSurCx2

  * @param iCommonCurve
  * The EdgeCurve common to both supports
  * @param iCommonPoint
  * An usefull parameter on the common curve to start with init searching techniques
  * @param iOrientations
  * An optionnal 2-dimensional array of orientations (-1,+1) used to define matter side on each support surface.
  * If given, please fill it with the following convention :
  *       iOrientations[0] = -1 or +1 and is related to the PCurve contained in iCommonCurve which lies on the first support surface
  *       iOrientations[1] = -1 or +1 and is related to the PCurve contained in iCommonCurve which lies on the second support surface
  *
  * Orientation is computed as following : Orientation = FaceVsSurfaceOrn * EdgeVsFaceOrn * PCurveVsEdgeOrn
  *
  * , so Orientation == PCurveVsSurfaceOrn. This orientation defines the matter side on support surface since
  * at each point on the related PCurve, this orientations allows to orient properly UV tangent (denoted T) so
  * as (Orientation * T , T_orthogonal , NormalToSurface) is a regular axis system. Matter side is defined by
  * direction pointed by T_orthogonal.
  */
  virtual void SetCommonCurve(CATEdgeCurve * iCommonCurve,
                              CATCrvParam  * iCommonPoint,
                              short        * iOrientations = 0) = 0;

  virtual void SetCommonCurves(int             iNb0,
                               int             iNb1,
                               CATEdgeCurve ** iCommonCurve0,
                               CATEdgeCurve ** iCommonCurve1,
                               CATCrvLimits  * ilim0,
                               CATCrvLimits  * ilim1) = 0;

  virtual void SetSupportIndexTable(const CATLONG32 * iTable) = 0;

  virtual void SetPreviousSupportDimensionTable(const CATLONG32 * iTable) = 0;

  virtual void GetSupportIndex(const CATLONG32   iTopoIndex,
                                     CATLONG32 & oGeoIndex) = 0;

  // FDL debut le 16/6/2000
  virtual void GetSupportIndexInverted(const CATLONG32   iGeoIndex,
                                             CATLONG32 & oTopoIndex) = 0;
  // FDL fin le 16/6/2000

  virtual CATBoolean ReportInit(const CATGeometry   * iReportGeometry,
                                const CATLONG32       iReportID,
                                double              * ioInitPoint,
                                double              & ioInitParam,
                                CATBoolean          & oSmallDeformation,
                                const CATCrvLimits  * iReportGeometryLimits = 0) = 0;

  virtual void SetInitSignature(const CATLONG32 iSignature = 0) = 0;

  /**
  * SetLoopSearch
  * Activate the init loop research in init computation phase.
  */
  virtual void SetLoopSearch(CATBoolean iEnable = TRUE) = 0;

  /**
  * Removes a CATConfusionCrvCrv operator from memory.
  */
  friend ExportedByConnect void Remove(CATConnect *iConnectOperator);

  //start : SOU
  virtual CATBoolean HasCanonicSupports() = 0; //return TRUE is all supports are Canonic

  virtual CATConnectComputer * RunStep1() = 0;//till creation of Computer
  
  virtual int RunStep2() = 0;//fetch results of Computer Run and perfrom interpolation & piece creation

  virtual void StreamSupports(CATLISTP(CATICGMObject) & oListObjects,
                              CATCGMStream            & oOtherInput) = 0;

  virtual CATBoolean RunDone() const = 0;
  //end : SOU

  virtual void SetCallBack(CATTopologyCallBacks *iCallBack) = 0; 
  virtual void SetG1TrackDeformation(CATBoolean iDeform) = 0; 

  protected:
  CATSoftwareConfiguration * _SoftwareConfiguration;
  const CATTolerance & _TolObject;
};

//-----------------------------------------------------------------------------
//
// Public construction and destruction
//
//-----------------------------------------------------------------------------
/**
* Creates an operator for connecting two CATSurfaces.
* @param iOrientation
*<dl><dt><tt>1</tt> <dd>the surface normal represents the outside of the matter.
*    <dt><tt>-1</tt><dd>the surface normal is oriented inside the matter.</dl>
* @param iProfile
* The type of profile of the resulting surface
* @param iMode
* <dl><dt><tt>BASIC</tt> <dd>the operation is performed at the operator creation
*     <dt><tt>ADVANCED</tt><dd>otherwise </dl>
*/
ExportedByConnect
CATConnect * CreateConnect(      CATGeoFactory            * iWhere,
                                 CATSoftwareConfiguration * iConfig,
                                 CATSurface               * iSurface1,
                           const CATLONG32                  iOrientation1,
                                 CATSurface               * iSurface2,
                           const CATLONG32                  iOrientation2,
                                 CATIPGMConnectTool       * iProfile,
                           const CATSkillValue              iMode = BASIC,
                                 CATBoolean                 iG1Trackdeformation = FALSE);

// Tritangent fillet
ExportedByConnect
CATConnect * CreateConnect(      CATGeoFactory            * iWhere,
                                 CATSoftwareConfiguration * iConfig,
                                 CATSurface               * iSurface1,
                           const CATLONG32                  iOrientation1,
                                 CATSurface               * iSurface2,
                           const CATLONG32                  iOrientation2,
                                 CATSurface               * iSurface3,
                           const CATLONG32                  iOrientation3,
                                 CATIPGMConnectTool       * iProfile,
                           const CATSkillValue              iMode = BASIC);

ExportedByConnect
CATConnect * CreateConnect(      CATGeoFactory            * iWhere,
                                 CATSoftwareConfiguration * iConfig,
                                 CATSurface               * iSurface1,
                           const CATLONG32                  iOrientation1,
                                 CATSurface               * iSurface2,
                           const CATLONG32                  iOrientation2,
                                 CATSurface               * iSurface3,
                           const CATLONG32                  iOrientation3,
                           const CATSkillValue              iMode = BASIC);

ExportedByConnect
CATConnect * CreateConnect(      CATGeoFactory            * iFactoryPtr,
                                 CATSoftwareConfiguration * iConfig,
                                 CATSurface               * iSurface1Ptr,
                                 CATSurface               * iSurface2Ptr,
                                 CATSurface               * iSurface3Ptr,
                                 CATIPGMConnectTool       * iProfilePtr,
                           const CATLONG32                  iOrientation1 = 1,
                           const CATLONG32                  iOrientation2 = 1,
                           const CATSkillValue              iMode = BASIC);

ExportedByConnect
CATConnect * CreateConnect(      CATGeoFactory            * iWhere,
                                 CATSoftwareConfiguration * iConfig,
                                 CATSurface               * iSupport1,
                                 CATSurface               * iSupport2,
                                 CATIPGMConnectTool       * iProfile,
                           const CATSkillValue              iMode = BASIC);

ExportedByConnect
CATConnect * CreateConnect(      CATGeoFactory            * iWhere,
                                 CATSoftwareConfiguration * iConfig,
                                 CATCurve                 * iCurvePtr,
                           const CATLONG32                  iOrientationCurve,
                                 CATSurface               * iSurfacePtr,
                           const CATLONG32                  iOrientationSurface,
                                 CATIPGMConnectTool       * iProfilePtr,
                           const CATSkillValue              iMode = BASIC);

ExportedByConnect
CATConnect * CreateConnect(      CATGeoFactory            * iWhere,
                                 CATSoftwareConfiguration * iConfig,
                                 CATPoint                 * iPointPtr,
                                 CATSurface               * iSurfacePtr,
                           const CATLONG32                  iOrientationSurface,
                                 CATIPGMConnectTool       * iProfilePtr,
                           const CATSkillValue              iMode = BASIC);

ExportedByConnect
CATConnect * CreateConnect(      CATGeoFactory            * iWhere,
                                 CATSoftwareConfiguration * iConfig,
                                 CATPoint                 * iPoint,
                                 CATSurface               * iSurface,
                           const CATLONG32                  iOrientationSurface,
                                 CATIPGMConnectTool       * iProfile,
                                 CATLISTP(CATSurface)     & iSurfList,
                                 CATLISTP(CATSurParam)    & iSurParamList,
                           const CATSkillValue              iMode = BASIC);

ExportedByConnect
CATConnect * CreateConnect(      CATGeoFactory            * iFactory,
                                 CATSoftwareConfiguration * iConfig,
                                 CATEdgeCurve             * iEdgeCurve,
                                 CATPCurve                * iPCurveStart,
                           const CATLONG32                  iOrientationStart,
                                 CATPCurve                * iPCurveEnd,
                           const CATLONG32                  iOrientationEnd,
                                 CATSurface               * iSurface,
                           const CATLONG32                  iSurfaceOrientation,
                                 CATIPGMConnectTool       * iProfile,
                           const CATSkillValue              iMode = BASIC);

ExportedByConnect
CATConnect * CreateConnect(      CATGeoFactory            * iFactory,
                                 CATSoftwareConfiguration * iConfig,
                                 CATEdgeCurve             * iEdgeCurve,
                                 CATPCurve                * iPCurveStart,
                           const CATLONG32                  iSurfaceStartOrientation,
                           const CATLONG32                  iPCurveStartSide,
                                 CATPCurve                * iPCurveEnd,
                           const CATLONG32                  iSurfaceEndOrientation,
                           const CATLONG32                  iPCurveEndSide,
                                 CATSurface               * iSurface,
                           const CATLONG32                  iSurfaceOrientation,
                                 CATIPGMConnectTool       * iProfile,
                           const CATSkillValue              iMode = BASIC);

ExportedByConnect
CATConnect * CreateConnect(      CATGeoFactory            * iFactory,
                                 CATSoftwareConfiguration * iConfig,
                                 CATEdgeCurve             * iEdgeCurve,
                                 CATPCurve                * iPCurveStart,
                           const CATLONG32                  iSurfaceStartOrientation,
                           const CATLONG32                  iPCurveStartSide,
                                 CATPCurve                * iPCurveEnd,
                           const CATLONG32                  iSurfaceEndOrientation,
                           const CATLONG32                  iPCurveEndSide,
                           const CATBoolean                 iFirstIsCovered,
                                 CATSurface               * iSurface,
                           const CATLONG32                  iSurfaceOrientation,
                                 CATIPGMConnectTool       * iProfile,
                           const CATSkillValue              iMode = BASIC);

ExportedByConnect
CATConnect * CreateConnect(      CATGeoFactory            * iWhere,
                                 CATSoftwareConfiguration * iConfig,
                                 CATSurface               * iSurface,
                                 CATCurve                 * iGuide,
                                 CATCurve                 * iSpine,
                                 CATIPGMConnectTool       * iProfile,
                           const CATSkillValue              iMode = BASIC);

ExportedByConnect
CATConnect * CreateConnect      (CATGeoFactory            * iWhere,
                                 CATSoftwareConfiguration * iConfig,
                                 CATSurface               * iSurface,
                           const CATLONG32                  iSurfaceOrientation,
                                 CATCurve                 * iGuide,
                                 CATCurve                 * iSpine,
                                 CATIPGMConnectTool       * iProfile,
                           const CATSkillValue              iMode = BASIC);

ExportedByConnect
CATConnect * CreateConnect(      CATGeoFactory      * iWhere,
                           CATSoftwareConfiguration * iConfig,
                                 CATSurface         * iSurface1,
                           const CATLONG32            iSurfaceOrientation1,
                                 CATSurface         * iSurface2,
                           const CATLONG32            iSurfaceOrientation2,
                                 CATCurve           * iSpine,
                                 CATIPGMConnectTool * iProfile,
                           const CATSkillValue        iMode = BASIC);

// creation du fillet edge/edge
ExportedByConnect
CATConnect * CreateConnect(      CATGeoFactory            * iWhere,
                                 CATSoftwareConfiguration * iConfig,
                                 CATEdgeCurve             * iEdgeCurve1,
                                 CATPCurve                * iInPCurve1,
                           const CATLONG32                  iInSurfOrientation1,
                           const CATLONG32                  iInPCurveSide1,
                                 CATPCurve                * iOutPCurve1,
                           const CATLONG32                  iOutSurfOrientation1,
                           const CATLONG32                  iOutPCurveSide1,
                                 CATEdgeCurve             * iEdgeCurve2,
                                 CATPCurve                * iInPCurve2,
                           const CATLONG32                  iInSurfOrientation2,
                           const CATLONG32                  iInPCurveSide2,
                                 CATPCurve                * iOutPCurve2,
                           const CATLONG32                  iOutSurfOrientation2,
                           const CATLONG32                  iOutPCurveSide2,
                                 CATIPGMConnectTool       * iProfile,
                           const CATSkillValue              iMode = BASIC);

ExportedByConnect
CATConnect * CreateConnect(      CATGeoFactory            * iWhere,
                                 CATSoftwareConfiguration * iConfig,
                                 CATEdgeCurve             * iEdgeCurve1,
                                 CATPCurve                * iInPCurve1,
                           const CATLONG32                  iInSurfOrientation1,
                           const CATLONG32                  iInPCurveSide1,
                                 CATPCurve                * iOutPCurve1,
                           const CATLONG32                  iOutSurfOrientation1,
                           const CATLONG32                  iOutPCurveSide1,
                           const CATBoolean                 iFirstIsCovered1,
                                 CATEdgeCurve             * iEdgeCurve2,
                                 CATPCurve                * iInPCurve2,
                           const CATLONG32                  iInSurfOrientation2,
                           const CATLONG32                  iInPCurveSide2,
                                 CATPCurve                * iOutPCurve2,
                           const CATLONG32                  iOutSurfOrientation2,
                           const CATLONG32                  iOutPCurveSide2,
                           const CATBoolean                 iFirstIsCovered2,
                                 CATIPGMConnectTool       * iProfile,
                           const CATSkillValue              iMode = BASIC);

ExportedByConnect
CATConnect * CreateConnect(      CATGeoFactory            * iWhere,
                                 CATSoftwareConfiguration * iConfig,
                                 CATEdgeCurve             * iEdgeCurve,
                                 CATPCurve                * iHoldCurve,
                           const CATLONG32                  iHCOrientation,
                                 CATSurface               * iSurface,
                           const CATLONG32	                iSurfaceOrientation,
                                 CATIPGMConnectTool       * iProfile,
                           const CATSkillValue              iMode = BASIC);

//hold curve keep edge
ExportedByConnect
CATConnect * CreateConnect(      CATGeoFactory            * iWhere,
                                 CATSoftwareConfiguration * iConfig,
                                 CATEdgeCurve             * iEdgeCurve,
                                 CATPCurve                * iHoldCurve,
                           const CATLONG32                  iHCOrientation,
                                 CATEdgeCurve             * iEdgeCurve2,
                                 CATPCurve                * iInPCurve2,
                           const short                     iInSurfOrientation2,
                           const short                     iInPCurveSide2,
                                 CATPCurve               * iOutPCurve2,
                           const short                     iOutSurfOrientation2,
                           const short                     iOutPCurveSide2,
                           const CATBoolean                iFirstIsCovered2,
                                 CATIPGMConnectTool      * iProfile,
                           const CATSkillValue             iMode = BASIC);

//draft neutral neutral fitted
ExportedByConnect
CATConnect * CreateConnect(      CATGeoFactory            * iWhere,
                                 CATSoftwareConfiguration * iConfig,
                                 CATEdgeCurve             * iEdgeCurve1,
                                 CATPCurve                * iInPCurve1,
                           const short                      iInSurfOrientation1,
                           const short                      iInPCurveSide1,
                                 CATPCurve                * iOutPCurve1,
                           const short                      iOutSurfOrientation1,
                           const short                      iOutPCurveSide1,
                           const CATBoolean                 iFirstIsCovered1,
                                 CATEdgeCurve             * iEdgeCurve2,
                                 CATPCurve                * iInPCurve2,
                           const short                      iInSurfOrientation2,
                           const short                      iInPCurveSide2,
                                 CATPCurve                * iOutPCurve2,
                           const short                      iOutSurfOrientation2,
                           const short                      iOutPCurveSide2,
                           const CATBoolean                 iFirstIsCovered2,
                                 CATSurface               * iParting,
                                 CATIPGMConnectTool       * iProfile,
                           const CATSkillValue              iMode = BASIC);

//-----------------------------------------------------------------------------

ExportedByConnect void Remove(CATConnect * iConnectPtr);

//-----------------------------------------------------------------------------

#ifdef CATIAV5R20
// Deprecated functions but kept in CXR20 because of CATConnectTool

ExportedByConnect
CATConnect * CreateConnect(      CATGeoFactory            * iWhere,
                                 CATSoftwareConfiguration * iConfig,
                                 CATSurface               * iSurface1,
                           const CATLONG32                  iOrientation1,
                                 CATSurface               * iSurface2,
                           const CATLONG32                  iOrientation2,
                           const CATConnectTool           * iProfile,
                           const CATSkillValue              iMode = BASIC);

// Tritangent fillet
ExportedByConnect
CATConnect * CreateConnect(      CATGeoFactory            * iWhere,
                                 CATSoftwareConfiguration * iConfig,
                                 CATSurface               * iSurface1,
                           const CATLONG32                  iOrientation1,
                                 CATSurface               * iSurface2,
                           const CATLONG32                  iOrientation2,
                                 CATSurface               * iSurface3,
                           const CATLONG32                  iOrientation3,
                           const CATConnectTool           * iProfile,
                           const CATSkillValue              iMode = BASIC);

ExportedByConnect
CATConnect * CreateConnect(      CATGeoFactory            * iFactoryPtr,
                                 CATSoftwareConfiguration * iConfig,
                                 CATSurface               * iSurface1Ptr,
                                 CATSurface               * iSurface2Ptr,
                                 CATSurface               * iSurface3Ptr,
                           const CATConnectTool           * iProfilePtr,
                           const CATLONG32                  iOrientation1,
                           const CATLONG32                  iOrientation2,
                           const CATSkillValue              iMode=BASIC);

ExportedByConnect
CATConnect * CreateConnect(      CATGeoFactory            * iWhere,
                                 CATSoftwareConfiguration * iConfig,
                                 CATSurface               * iSupport1,
                                 CATSurface               * iSupport2,
                           const CATConnectTool           * iProfile,
                           const CATSkillValue              iMode = BASIC);

ExportedByConnect
CATConnect * CreateConnect(      CATGeoFactory            * iWhere,
                                 CATSoftwareConfiguration * iConfig,
                                 CATCurve                 * iCurvePtr,
                           const CATLONG32                  iOrientationCurve,
                                 CATSurface               * iSurfacePtr,
                           const CATLONG32                  iOrientationSurface,
                           const CATConnectTool           * iProfilePtr,
                           const CATSkillValue              iMode = BASIC);

ExportedByConnect
CATConnect * CreateConnect(      CATGeoFactory            * iWhere,
                                 CATSoftwareConfiguration * iConfig,
                                 CATPoint                 * iPointPtr,
                                 CATSurface               * iSurfacePtr,
                           const CATLONG32                  iOrientationSurface,
                           const CATConnectTool           * iProfilePtr,
                           const CATSkillValue              iMode = BASIC);

ExportedByConnect
CATConnect * CreateConnect(      CATGeoFactory            * iWhere,
                                 CATSoftwareConfiguration * iConfig,
                                 CATPoint                 * iPoint,
                                 CATSurface               * iSurface,
                           const CATLONG32                  iOrientationSurface,
                           const CATConnectTool           * iProfile,
                                 CATLISTP(CATSurface)     & iSurfList,
                                 CATLISTP(CATSurParam)    & iSurParamList,
                           const CATSkillValue              iMode = BASIC);

ExportedByConnect
CATConnect * CreateConnect(      CATGeoFactory            * iFactory,
                                 CATSoftwareConfiguration * iConfig,
                                 CATEdgeCurve             * iEdgeCurve,
                                 CATPCurve                * iPCurveStart,
                           const CATLONG32                  iOrientationStart,
                                 CATPCurve                * iPCurveEnd,
                           const CATLONG32                  iOrientationEnd,
                                 CATSurface               * iSurface,
                           const CATLONG32                  iSurfaceOrientation,
                           const CATConnectTool           * iProfile,
                           const CATSkillValue              iMode = BASIC);

ExportedByConnect
CATConnect * CreateConnect(      CATGeoFactory            * iFactory,
                                 CATSoftwareConfiguration * iConfig,
                                 CATEdgeCurve             * iEdgeCurve,
                                 CATPCurve                * iPCurveStart,
                           const CATLONG32                  iSurfaceStartOrientation,
                           const CATLONG32                  iPCurveStartSide,
                                 CATPCurve                * iPCurveEnd,
                           const CATLONG32                  iSurfaceEndOrientation,
                           const CATLONG32                  iPCurveEndSide,
                                 CATSurface               * iSurface,
                           const CATLONG32                  iSurfaceOrientation,
                           const CATConnectTool           * iProfile,
                           const CATSkillValue              iMode = BASIC);

ExportedByConnect
CATConnect * CreateConnect(      CATGeoFactory            * iFactory,
                                 CATSoftwareConfiguration * iConfig,
                                 CATEdgeCurve             * iEdgeCurve,
                                 CATPCurve                * iPCurveStart,
                           const CATLONG32                  iSurfaceStartOrientation,
                           const CATLONG32                  iPCurveStartSide,
                                 CATPCurve                * iPCurveEnd,
                           const CATLONG32                  iSurfaceEndOrientation,
                           const CATLONG32                  iPCurveEndSide,
                           const CATBoolean                 iFirstIsCovered,
                                 CATSurface               * iSurface,
                           const CATLONG32                  iSurfaceOrientation,
                           const CATConnectTool           * iProfile,
                           const CATSkillValue              iMode = BASIC);

ExportedByConnect
CATConnect * CreateConnect(      CATGeoFactory            * iWhere,
                                 CATSoftwareConfiguration * iConfig,
                                 CATSurface               * iSurface,
                                 CATCurve                 * iGuide,
                                 CATCurve                 * iSpine,
                           const CATConnectTool           * iProfile,
                           const CATSkillValue              iMode = BASIC);

ExportedByConnect
CATConnect * CreateConnect (      CATGeoFactory            * iWhere,
                                  CATSoftwareConfiguration * iConfig,
                                  CATSurface               * iSurface,
                            const CATLONG32                  iSurfaceOrientation,
                                  CATCurve                 * iGuide,
                                  CATCurve                 * iSpine,
                            const CATConnectTool           * iProfile,
                            const CATSkillValue              iMode = BASIC);

ExportedByConnect
CATConnect * CreateConnect(      CATGeoFactory            * iWhere,
                                 CATSoftwareConfiguration * iConfig,
                                 CATSurface               * iSurface1,
                           const CATLONG32                  iSurfaceOrientation1,
                           CATSurface                     * iSurface2,
                           const CATLONG32                  iSurfaceOrientation2,
                                 CATCurve                 * iSpine,
                           const CATConnectTool           * iProfile,
                           const CATSkillValue              iMode = BASIC);

// creation du fillet edge/edge
ExportedByConnect
CATConnect * CreateConnect(      CATGeoFactory            * iWhere,
                                 CATSoftwareConfiguration * iConfig,
                                 CATEdgeCurve             * iEdgeCurve1,
                                 CATPCurve                * iInPCurve1,
                           const CATLONG32                  iInSurfOrientation1,
                           const CATLONG32                  iInPCurveSide1,
                                 CATPCurve                * iOutPCurve1,
                           const CATLONG32                  iOutSurfOrientation1,
                           const CATLONG32                  iOutPCurveSide1,
                                 CATEdgeCurve             * iEdgeCurve2,
                                 CATPCurve                * iInPCurve2,
                           const CATLONG32                  iInSurfOrientation2,
                           const CATLONG32                  iInPCurveSide2,
                                 CATPCurve                * iOutPCurve2,
                           const CATLONG32                  iOutSurfOrientation2,
                           const CATLONG32                  iOutPCurveSide2,
                           const CATConnectTool           * iProfile,
                           const CATSkillValue              iMode = BASIC);

ExportedByConnect
CATConnect * CreateConnect(      CATGeoFactory            * iWhere,
                                 CATSoftwareConfiguration * iConfig,
                                 CATEdgeCurve             * iEdgeCurve1,
                                 CATPCurve                * iInPCurve1,
                           const CATLONG32                  iInSurfOrientation1,
                           const CATLONG32                  iInPCurveSide1,
                                 CATPCurve                * iOutPCurve1,
                           const CATLONG32                  iOutSurfOrientation1,
                           const CATLONG32                  iOutPCurveSide1,
                           const CATBoolean                 iFirstIsCovered1,
                                 CATEdgeCurve             * iEdgeCurve2,
                                 CATPCurve                * iInPCurve2,
                           const CATLONG32                  iInSurfOrientation2,
                           const CATLONG32                  iInPCurveSide2,
                                 CATPCurve                * iOutPCurve2,
                           const CATLONG32                  iOutSurfOrientation2,
                           const CATLONG32                  iOutPCurveSide2,
                           const CATBoolean                 iFirstIsCovered2,
                           const CATConnectTool           * iProfile,
                           const CATSkillValue              iMode = BASIC);

ExportedByConnect
CATConnect * CreateConnect(      CATGeoFactory            * iWhere,
                                 CATSoftwareConfiguration * iConfig,
							                   CATEdgeCurve             * iEdgeCurve,
                                 CATPCurve                * iHoldCurve,
                           const CATLONG32                  iHCOrientation,
                                 CATSurface               * iSurface,
                           const CATLONG32                  iSurfaceOrientation,
                           const CATConnectTool           * iProfile,
                           const CATSkillValue              iMode = BASIC);

//hold curve keep edge
ExportedByConnect
CATConnect * CreateConnect(      CATGeoFactory            * iWhere,
                                 CATSoftwareConfiguration * iConfig,
			                              CATEdgeCurve          * iEdgeCurve,
                                  CATPCurve               * iHoldCurve,
                            const CATLONG32                 iHCOrientation,
                                  CATEdgeCurve            * iEdgeCurve2,
                                  CATPCurve               * iInPCurve2,
                            const short                     iInSurfOrientation2,
                            const short                     iInPCurveSide2,
                                  CATPCurve               * iOutPCurve2,
                            const short                     iOutSurfOrientation2,
                            const short                     iOutPCurveSide2,
                            const CATBoolean                iFirstIsCovered2,
                            const CATConnectTool          * iProfile,
                            const CATSkillValue             iMode = BASIC);

//draft neutral neutral fitted
ExportedByConnect
CATConnect* CreateConnect(      CATGeoFactory            * iWhere,
                                CATSoftwareConfiguration * iConfig,
                                CATEdgeCurve             * iEdgeCurve1,
                                CATPCurve                * iInPCurve1,
                          const short                      iInSurfOrientation1,
                          const short                      iInPCurveSide1,
                                CATPCurve                * iOutPCurve1,
                          const short                      iOutSurfOrientation1,
                          const short                      iOutPCurveSide1,
                          const CATBoolean                 iFirstIsCovered1,
                                CATEdgeCurve             * iEdgeCurve2,
                                CATPCurve                * iInPCurve2,
                          const short                      iInSurfOrientation2,
                          const short                      iInPCurveSide2,
                                CATPCurve                * iOutPCurve2,
                          const short                      iOutSurfOrientation2,
                          const short                      iOutPCurveSide2,
                          const CATBoolean                 iFirstIsCovered2,
                                CATSurface               * iParting,
                          const CATConnectTool           * iProfile,
                          const CATSkillValue              iMode = BASIC);

#endif /* CATIAV5R20 */

#endif
