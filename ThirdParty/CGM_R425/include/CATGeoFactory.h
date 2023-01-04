#ifndef CATGEOFACTORY_H
#define CATGEOFACTORY_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
* @CAA2Level L1
* @CAA2Usage U3
*/ 
#include "CATIACGMLevel.h"
#include "ExportedByCATGMGeometricInterfaces.h"

extern ExportedByCATGMGeometricInterfaces const char* CATGeometricContainer ; 

#include "CATBaseUnknown.h"
#include "CATICGMContainer.h"
#include "CATMathDef.h"
#include "CATGeometryType.h"
#include "CATListOfCATPoints.h"
#include "CATListOfCATCurves.h"
#include "CATListOfCATMathSetOfPointsND.h"
#include "CATListOfCATCrvParams.h"
#include "CATListOfCATCrvLimits.h"
#include "CATListOfInt.h"
#include "CATParameterizationOption.h"
#include "CATIAV5Level.h"
#include "CATBodyMode.h"

class CATGeometry;
class CATICGMObject;
class CATPoint;
class CATCartesianPoint;
class CATCloudOfPoints;
class CATLine;
class CATCircle;
class CATEllipse;
class CATParabola;
class CATHyperbola;
class CATPointOnCurve;
class CATPointOnEdgeCurve;
class CATPlane;
class CATBezierCurve;
class CATPLine;
class CATPCurve;
class CATEdgeCurve;
class CATNurbsCurve;
class CATSplineCurve;
class CATPointOnSurface;
class CATNurbsSurface;
class CATRuledSurface;
class CATGenericRuledSurface;
class CATSpecSurface;
class CATSpecSurfaceDef;
class CATProcSurface;
class CATProcSurfaceDef;
class CATOrientable;
class CATCurve;
class CATSurface;
class CATMathPoint;
class CATMathPoint2D;
class CATMathVector;
class CATMathDirection;
class CATMathPlane;
class CATMathLine;
class CATMathLine2D;
class CATMathAxis;
class CATMathAxis2D;
class CATMathBox2D;
class CATMathFunctionX;
class CATMathNonLinearTransformation;
class CATMathTransformation;
class CATCrvParam;
class CATCrvLimits;
class CATSurParam;
class CATSurLimits;
class CATMathSetOfPoints;
class CATMathGridOfPoints;
class CATKnotVector;
class CATSphere;
class CATCylinder;
class CATCone;
class CATTorus;
class CATTabulatedCylinder;
class CATRevolutionSurface;
class CATProcOffsetSurface;
class CATOffsetSurface;
class CATCircularSweep;
class CATGenericFillet;
class CATSweepSurface;
class CATFilletSurface;
class CATDraftSurfaceCreationData;
class CATDraftSurface;
class CATDirectionalSurface;
class CATChamferSurface;
class CATLinearTransfoSurface;
class CATNonLinearTransfoSurface;
class CATNonLinearTransfoPCurve;
class CATMathNonLinearTransformation2D;
class CATPCircle;
class CATTrimmedPCurve;
class CATPEllipse;
class CATPParabola;
class CATPHyperbola;
class CATPCurveEquation ;
class CATMacroPoint;
class CATIntCurve;
class CATSimCurve;
class CATMergedCurve;
class CATContactCurve;
class CATProcCurve;
class CATProcCurveDef;
class CATMapX;
class CATPNurbs;
class CATPSpline;
class CATHelix;
class CATBody;

class CATCldGenEntity;
class CATCldBody;
class CATCldCloud;
class CATCldScan;
class CATCldGrid;
class CATCldPolygon;
class CATCldVectors;
class CATCldSetOfScans;
class CATCldSetOfGrids;
class CATCldScanOnPolygon;
class CATCldSubPolygon;
class CATCldSetOfPoints;
class CATCldSetOfPointsF;
class CATCldSetOfPointsD;

class CATClay;
class CATTessClay;
class CATCloud;
class CATTessCloud;
class CATScan;
class CATTessScan;

class CATIForeignSurface;
class CATForeignSurfaceData;
class CATIForeignCurve;
class CATForeignCurveData;
class CATIForeignPCurve;
class CATForeignPCurveData;

class CATKnotVector;
class CATMathSetOfPointsND;
class CATMathSetOfPointsNDWithVectors;
class CATUserGeometry;

class CATLaw;
class CATConstantLaw;
class CATLinearLaw;
class CATSTypeLaw;
class CATSplineLaw;
class CATCompositeLaw;
class CATSobMesh;
class CATSubdivMesh;

class CATSweepSegmentSurface;
class CATSweepSegmentSurfaceCreationData;

class CATCGMInternalTol;
class CATGeoFactoryProtected;


#if defined (CATIACGMV5R16) && !defined (CATIAV5R16)
#define CATCGMRemoveNoDocDrop1
#endif

#if defined (CATIACGMV5R16) && !defined (CATIAV5R16)
#define CATCGMRemoveNoDocDrop2
#endif

 
//CAA_Exposed
/**
* Geometric resolution order.
* @param CatC0
* Continuity.
* @param CatC1
* Tangency.
* @param CatC2
* Curvature.
*/
enum CATResolutionType { CatC0, CatC1, CatC2 } ;

/**
* @nodoc
* Determine if Tolerances are enough compatible to Allow Copy/Paste between the two Containers
*/
enum CATCGMTolerancesCompatibility 
{
   CatCGMTolerancesNotComparable               = 0,
   CatCGMTolerancesSmallerModelSizeOrInfinite  = 1,
   CatCGMTolerancesBiggerModelSizeOrInfinite   = 2,
   CatCGMTolerancesIncompatible                = 4,
   CatCGMTolerancesIdentical                   = 6
};


#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATGeoFactory ;
#else
extern "C" const IID IID_CATGeoFactory ;
#endif


 
//CAA_Exposed CATIGemFactory
/**
* Interface representing the factory of all geometric elements.
*<br><b>Role</b>: The CATGeoFactory creates the geometric elements. It manages the AddRef mechanism.
* To suppress a geometric element, you must use <tt>CATICGMContainer::Remove</tt> method, 
* that also takes in charge the AddRef mechanism.
*<br> The creation of a container implies the creation of two factories,
* an explicit one and an implicit one.
* All the methods described here
* work on both, except the <tt>Next</tt> method, that only works on
* the explicit factory. 
*<br>At the container creation, 7 implicit objects (called Datums)
* are created and represent the canonical geometric objects: the space
* origin <tt>CATGeoFactory::O</tt>, the infinite lines in the three directions,
* <tt>CATGeoFactory::OI</tt>, <tt>CATGeoFactory::OJ</tt>, <tt>CATGeoFactory::OK</tt>, and the three
* infinite planes passing through these lines 
* <tt>CATGeoFactory::OIJ</tt>, <tt>CATGeoFactory::OJK</tt>, <tt>CATGeoFactory::OKI</tt>.
*<br>The description and the use of the entities created by the factory 
* are described in each entity class.
* <br><b>Lifecyle rules</b>: a CATGeoFactory is created by using the  <tt>CATCreateCGMContainer</tt> 
* global function or
* loaded from a stream with the  <tt>CATLoadCGMContainer</tt> global function. 
* It can be saved on a given stream (<tt>CATLoadCGMContainer</tt>).When you do not need 
* it anymore, you must close it
* <tt>CATCloseCGMContainer</tt>. All these global functions can be found in the <tt>CATCGMContainerMngt.h</tt>
* file.
*/
class ExportedByCATGMGeometricInterfaces CATGeoFactory : public CATICGMContainer
{
   CATDeclareInterface;

public:
   //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
   //
   //            C A A             M E T H O D S
   //
   //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

   //CAA_Exposed
   /**
   * Returns the model size associated with <tt>this</tt> CATGeoFactory.
   *<br> The model size defines a cubic box which contains all the objects you
   * want to create within this factory. According to the model size, the
   * resolution will be more or less accurate.
   */
   virtual double GetModelSize() const = 0;

   //CAA_Exposed 
   /**
   * Returns the minimum length of a valid object.
   * @param iResolutionType
   * <dl><dt>CatC0</dt><dd> To retrieve the minimum length of a valid object.
   *<br>Any object smaller than the resolution should not be created.
   * <dt>CatC1</dt><dd> To retrieve the minimum angle value  
   * defining a sharp angle.
   * </dl>
   */
   virtual double GetResolution(const CATResolutionType iResolutionType = CatC0) const = 0;

   //CAA_Exposed  
   /**
   * Retrieves the model unit.
   * @return
   * The unit, that is to say, the dimension in meter of 1. in the model.
   */
   virtual double GetUnit() const = 0;

   /**
   * Retrieves the size of the box centered at origin which contains all the objects, including infinite objects.
   * @return
   * The geometric infinity.
   */
   virtual double GetInfinite() const = 0;


   /**
   * Returns a pointer to the implicit geometric factory.
   * @return
   * The pointer to the implicit CATGeoFactory.
   */
   virtual CATGeoFactory* GetImplicitGeoFactory() const = 0 ;


   //-----------------------------------------------------------------------------
   //- Body creation
   //-----------------------------------------------------------------------------
#if defined ( CATIACGMR214CAA )
   /**
   * Creates  an empty topological body.
   *<br> This object is mainly used by the TopologicalObjects framework.
   * @param iMode
   *   Option for initial working mode (to reconsider only in case of specific PCS smart management case study). 
   *   By default, data structure are set for best working conditions with core operations (Boolean,Tessellation).
   * @param iRole
   *   Helpers for support. 
   * @return
   *   The pointer to the created body.
   */

  virtual CATBody * CreateBody(CATBodyMode  iMode        = CatBodyMode_Working ,
                                const char  iRole[]      = "Unknown",
                                const char *iTracability = NULL ,
                                const int   iLine        = 0 ) = 0 ; 

#else
   /**
   * Creates  an empty topological body.
   *<br> This object is mainly used by the TopologicalObjects framework.
   * @return
   * The pointer to the created body.
   */

   virtual CATBody * CreateBody() = 0 ; 

#endif


   //-------------------------------------------------------------------------
   //- CartesianPoint creation
   //-------------------------------------------------------------------------
   /**
   * Creates a geometric point from its cartesian
   * coordinates.
   * @param iFirstCoord
   * The first coordinate of the point.
   * @param iSecondCoord
   * The second coordinate of the point.
   * @param iThirdCoord
   * The third coordinate of the point.
   * @return
   * The pointer to the created point.
   */
   virtual CATCartesianPoint * CreateCartesianPoint (const double iFirstCoord,
                                                     const double iSecondCoord,
                                                     const double iThirdCoord) = 0 ;

   /**
   * Creates a geometric point from a mathematical point.
   * @param iMathPointToCopy
   * The mathematical point.
   * @return
   * The pointer to the created point.
   */
   virtual CATCartesianPoint * CreateCartesianPoint (const CATMathPoint &iMathPointToCopy) = 0 ;

   //-------------------------------------------------------------------------
   //- PointOnCurve creation
   //-------------------------------------------------------------------------
   /**
   * Creates a geometric point lying on a geometric curve from its parameter
   * on the curve.
   * @param iParam
   * The parameter on <tt>iCurve</tt>
   * @param iCurve
   * The pointer to the curve on which the point is created.
   * @return
   * The pointer to the created point.
   */
   virtual CATPointOnCurve * CreatePointOnCurve (const CATCrvParam   & iParam ,
                                                       CATCurve     *  iCurve ) = 0;

   //-------------------------------------------------------------------------
   //- PointOnEdgeCurve creation
   //-------------------------------------------------------------------------
   /**
   * Creates a geometric point lying on a CATEdgeCurve from its parameter
   * on one of the aggregated curves.
   * @param iSpecCurve
   * The pointer on one of the aggregated curves of the CATEdgeCurve 
   * <tt>iSupport</tt>, may be the CATEdgeCurve itself.
   * @param iSpecparam
   * The parameter on <tt>iSpecCurve</tt> of the PointOnEdgeCurve to create. 
   * @param iSupport
   * The CATEdgeCurve pointer.
   * @return
   * The pointer to the created point.
   */
   virtual CATPointOnEdgeCurve* CreatePointOnEdgeCurve( const CATCurve     * iSpecCurve,
                                                        const CATCrvParam  & iSpecParam,
                                                        const CATEdgeCurve * iSupport   )= 0 ;

   /**
   * Creates a geometric point lying on a CATEdgeCurve from its parameters
   * on two of the aggregated curves.
   * @param iSpecCurve1
   * The pointer ton one of the aggregated curves of the CATEdgeCurve 
   * <tt>iSupport</tt>, may be the CATEdgeCurve itself.
   * @param iSpecparam1
   * The parameter on <tt>iSpecCurve1</tt> of the PointOnEdgeCurve to create.
   * @param iSpecCurve2
   * The pointer to one of the aggregated curves of the CATEdgeCurve 
   * <tt>iSupport</tt>, may be the CATEdgeCurve itself.
   * @param iSpecparam2
   * The parameter on <tt>iSpecCurve2</tt> of the PointOnEdgeCurve to create.
   * @param iSupport
   * The CATEdgeCurve pointer.
   * @return
   * The pointer to the created point.
   */
   virtual CATPointOnEdgeCurve* CreatePointOnEdgeCurve( const CATCurve * iSpecCurve1,
                                                        const CATCrvParam  & iSpecParam1,
                                                        const CATCurve     * iSpecCurve2,
                                                        const CATCrvParam  & iSpecParam2,
                                                        const CATEdgeCurve * iSupport   )= 0 ;

   /**
   * Creates a geometric point lying on a CATEdgeCurve from its parameters
   * on a given number of the aggregated curves.
   * @param iNbOfSpecs
   * The number of aggregated curves on which the parameters of the point
   * are given.
   * @param iSpecCurve
   * The array of pointers to <tt>iNbOfSpecs</tt> aggregated curves of the CATEdgeCurve 
   * <tt>iSupport</tt>. Can contain a pointer to the CATEdgeCurve itself.
   * @param iSpecparam
   * The corresponding parameters on the <tt>iSpecCurve</tt> aggregated curves
   * of the PointOnEdgeCurve to create. 
   * @param iSupport
   * The CATEdgeCurve pointer.
   * @return
   * The pointer to the created point.
   */
   virtual CATPointOnEdgeCurve* CreatePointOnEdgeCurve( const CATLONG32 iNbOfSpecs,  
                                                        const CATCurve* iSpecCurves[], 
                                                        const CATCrvParam iSpecParams[], 
                                                        const CATEdgeCurve* iSupport   )= 0 ; 



   //-------------------------------------------------------------------------
   //- PointOnSurface basic creation
   //-------------------------------------------------------------------------
   /**
   * Creates a geometric point lying on a surface.
   * @param iParam
   * The parameters on <tt>iSurface</tt> of the point to create.
   * @param iSurface
   * The pointer to the surface on which the point is created.
   * @return
   * The pointer to the created point.
   */
   virtual CATPointOnSurface * CreatePointOnSurface (const CATSurParam & iParam  ,
                                                           CATSurface  * iSurface) = 0;


   //------------------------------------------------------------------------- 
   //- MacroPoint basic creation 
   //-------------------------------------------------------------------------
   /**
   * Creates a geometric point aggregating several geometric points.
   * <br><b>Role</b>:
   * A CATMacroPoint is the geometry of a CATVertex and is used in a topological context.
   * @param iPoints
   * The list of points to define the CATMacroPoint.
   * @return
   * The pointer to the created point.
   */
   virtual CATMacroPoint * CreateMacroPoint ( CATLISTP(CATPoint) & iPoints) = 0 ;
   /**
   * Creates an empty CATMacroPoint.
   * @return
   * The pointer to the created point.
   */
   virtual CATMacroPoint * CreateMacroPoint () = 0 ;



   //-------------------------------------------------------------------------
   //- Trimmed Line creation
   //-------------------------------------------------------------------------
   /**
   * Creates a trimmed geometric line from two geometric points.
   * @param iStart
   * The pointer to the first limiting point.
   * @param iEnd
   * The pointer to the last limiting point.
   * @return
   * The pointer to the created line.
   */
   virtual CATLine * CreateLine (const CATPoint *iStart,
                                 const CATPoint *iEnd      )  = 0 ;

   /**
   * Creates a trimmed geometric line from two mathematical points.
   * @param iStart
   * The first limiting point.
   * @param iEnd
   * The last limiting point.
   * @return
   * The pointer to the created line.
   */ 
   virtual CATLine * CreateLine (const CATMathPoint &iStart,
                                 const CATMathPoint &iEnd           ) = 0; 

   //-------------------------------------------------------------------------
   //- UnTrimmed Line creation
   //-------------------------------------------------------------------------
   /**
   * Creates an untrimmed geometricl line from a mathematical point and a direction.
   * @param iPoint
   * The mathematical point
   * @param iDirection
   * The direction
   * @return
   * The pointer to the created line.
   */
   virtual CATLine * CreateLine (const CATMathPoint     &iPoint    ,
                                 const CATMathDirection &iDirection) = 0;

   /**
   * Creates an untrimmed geometric line from 2 mathematical points.
   * @param iStart
   * The first point
   * @param iEnd
   * The second point
   * @param oLimits
   * The parameters of the corresponding points on the line.
   * @return
   * The pointer to the created line.
   */
   virtual CATLine * CreateLine (const CATMathPoint &iStart,
                                 const CATMathPoint &iEnd,
                                       CATCrvLimits &ioLimits) = 0;

   /**
   * Creates an untrimmed geometric line from 2 geometric points.
   * @param iStart
   * The pointer to the first point
   * @param iEnd
   * The pointer to the second point
   * @param oLimits
   * The parameters of the corresponding points on the line.
   * @return
   * The pointer to the created line.
   */
   virtual CATLine * CreateLine (const CATPoint     *iStart,
                                 const CATPoint     *iEnd,
                                       CATCrvLimits &ioLimits) = 0;

   //-------------------------------------------------------------------------
   //- Circle creation
   //-------------------------------------------------------------------------
   /**
   * Creates a geometric circle.
   * @param iRadius
   * The radius.
   * @param iMathPlane
   * The plane defining the center and axis of the circle.
   * @return
   * The pointer to the created circle.
   */
   virtual CATCircle * CreateCircle (const double             iRadius,
                                     const CATMathPlane      &iMathPlane) = 0;

   /**
   * Creates a geometric circle arc.
   *<br> The circle center is the origin of the plane.
   *<br><b>Note</b> <tt> 0 <= iStart < CAT2PI</tt>, 
   * <tt>iStart < iEnd <= iStart + CAT2PI</tt>
   * @param iRadius
   * The radius.
   * @param iMathPlane
   * The plane defining the center and axis of the circle.
   * @param iStart
   * The first angle limitation (in Radians).
   * @param iEnd
   * The last angle limitation (in Radians).
   * @return
   * The pointer to the created circle.
   */
   virtual CATCircle * CreateCircle (const double             iRadius,
                                     const CATMathPlane      &iMathPlane,
                                     const CATAngle           iStart,
                                     const CATAngle           iEnd    ) = 0;



   //-------------------------------------------------------------------------
   //- Ellipse creation
   //-------------------------------------------------------------------------
   /**
   * Creates a geometric ellipse.
   * @param iMajorAxis
   * The half length of the major axis.
   * @param iMinorAxis
   * The half length of the minor axis.
   * @param iMathPlane
   * The origin and axis of the ellipse.
   * @return
   * The created ellipse.
   */
   virtual CATEllipse * CreateEllipse (const double            iMajorAxis,
                                       const double            iMinorAxis,
                                       const CATMathPlane      &iMathPlane ) = 0;
   /**
   * Creates a geometric ellipse arc.
   * <br>Refer plese to the encyclopedia for the description of the angle limitations.
   * @param iMajorAxis
   * The half length of the major axis.
   * @param iMinorAxis
   * The half length of the minor axis.
   * @param iMathPlane
   * The origin and axis of the ellipse.
   * @param iStart
   * The first angle limitation (in Radians).
   * @param iEnd
   * The last angle limitation (in Radians).
   * @return
   * The pointer to the created ellipse.
   */
   virtual CATEllipse * CreateEllipse (const double            iMajorAxis,
                                       const double            iMinorAxis,
                                       const CATMathPlane      &iMathPlane, 
                                       const CATAngle           iStart,
                                       const CATAngle           iEnd  ) = 0;


   //-------------------------------------------------------------------------
   //- NurbsCurve creation
   //-------------------------------------------------------------------------
   /**
   * Creates a NURBS curve.
   * <br>Please refer to the enclycopedia to have a detailed
   * description of the NURBS representation.
   * @param iKnotVector
   * The nodal vector.
   * @param iIsRational
   * <b>Legal values</b>: 1 if the NURBS is rational, 0 otherwise.
   * @param iVertices
   * The list of the vertices.
   * @param iWeigths
   * The array of the weights.
   * @param iParameterizationOption
   * The option of parameterization. By default, the parameterization of the NURBS is modified to better
   * fit internal criteria. In this case, you can recover the initial parameterization 
   * with the @href CATNurbsCurve#GetOriginalParametrisationDATA method.
   * @return 
   * The pointer to the created curve.
   */
   virtual CATNurbsCurve* CATCreateNurbsCurve(const CATKnotVector            & iKnotVector,
                                              const CATLONG32                & iIsRational,
                                              const CATMathSetOfPoints       & iVertices  ,
                                              const double                   * iWeights   ,
                                              const CATParameterizationOption  iParameterizationOption = CatAutomaticParameterization) =0  ;
   /**
   * @nodoc
   * @deprecated V5R14 CATCreateNurbsCurve
   */
   virtual CATNurbsCurve* CreateNurbsCurve   (const CATKnotVector            & iKnotVector,
                                              const CATLONG32                & iIsRational,
                                              const CATMathSetOfPoints       & iVertices  ,
                                              const double                   * iWeights   ,
                                              const CATParameterizationOption  iParameterizationOption = CatAutomaticParameterization) =0  ;

   //-----------------------------------------------------------------------------
   //- Spline curve creation
   //-----------------------------------------------------------------------------
   /**
   * Creates a cubic Spline curve.
   * @param iPoints
   * The pointer to a CATMathSetOfPointsND, with N>=3.
   * @param iFirstCoordIndex
   * The coordinate index of the ND points to be taken as the first coordinate  
   * of the constructing points of the spline.
   * @param iSecondCoordIndex
   * The coordinate index of the ND points to be taken as the second coordinate  
   * ofthe constructing points of the spline.
   * @param iThirdCoordIndex
   * The coordinate index of the ND points to be taken as the third coordinate  
   * of the constructing points of the spline.
   * @param iParameters
   * The array of parameters defining a user Parameterization. 
   * If <tt>NULL</tt>, the
   * Parameterization is automatically defined. The size of the array is the 
   * number of points of the CATMathSetOfPointsND.
   * @return
   * The pointer to the created point.
   */
   virtual CATSplineCurve * CreateSplineCurve(const CATMathSetOfPointsND * iPoints,
                                              const CATLONG32            & iFirstCoordIndex,
                                              const CATLONG32            & iSecondCoordIndex,
                                              const CATLONG32            & iThirdCoordIndex,
                                              const double               * iParameters) =0;

   /**
   * Creates a quintic 3d spline curve.
   * @param iParams
   * The pointer to a CATMathSetOfPointsND of dimension 1 containing a user parameterization.
   * @param iPoints
   * The pointer to a CATMathSetOfPointsND containing points of a 3d Spline
   * @param iTangents
   * The pointer to a CATMathSetOfPointsND containing tangents of a 3d Spline
   * @param iSecondDerivatives
   * The pointer to a CATMathSetOfPointsND containing second derivatives of a 3d Spline
   * @param iFirstCoordIndex
   * This index is such that the points, tangents and second derivatives of the
   * first coordinate of the spline are the values of index iFirstCoordIndex
   * @param iSecondCoordIndex
   * Same as iFirstCoordIndex but for the second coordinate of the spline.
   * @param iThirdCoordIndex
   * Same as iFirstCoordIndex but for the third coordinate of the spline.
   * @return
   * The pointer to the created curve.
   */
   virtual CATSplineCurve * CreateSplineCurve(const CATMathSetOfPointsND * iParams,
                                              const CATMathSetOfPointsND * iPoints,
                                              const CATMathSetOfPointsND * iTangents,
                                              const CATMathSetOfPointsND * iSecondDerivatives,
                                              const CATLONG32              iFirstCoordIndex,
                                              const CATLONG32              iSecondCoordIndex,
                                              const CATLONG32              iThirdCoordIndex)=0;

   //-----------------------------------------------------------------------------
   //- PLine creation
   //-----------------------------------------------------------------------------
   /**
   * Creates a trimmed geometric line defined in the space of a surface.
   * @param iStart
   * The first limitation of the line.
   * @param iEnd
   * The last limitation of the line.
   * @param iSurface
   * The pointer to the surface on which the line is created.
   * @return
   * The pointer to the created line.
   */
   virtual CATPLine* CreatePLine(const CATSurParam & iStart  ,
                                 const CATSurParam & iEnd    ,
                                       CATSurface *  iSupport)  = 0 ;


   //-----------------------------------------------------------------------------
   //- PCircle creation
   //-----------------------------------------------------------------------------
   /**
   * Creates an untrimmed geometric circle defined in the space of a surface.
   * @param iRadius
   * The radius of the circle.
   * @param iCenter
   * The coordinates of the center
   * @param iSupport
   * The pointer to the surface on which the circle is created.
   * @return
   * The pointer to the created circle.
   */
   virtual CATPCircle * CreatePCircle( const double        iRadius  ,
                                       const CATSurParam & iCenter  ,
                                             CATSurface  * iSupport ) =0;

   /**
   * Creates a trimmed geometric circle defined in the space of a surface.
   * @param iRadius
   * The radius of the circle.
   * @param iCenter
   * The coordinates of the center
   * @param iStart
   * The first angle limitation (in Radians).
   * @param iEnd
   * The last angle limitation (in Radians).
   * @param iSupport
   * The pointer to the surface on which the circle is created.
   * @return
   * The pointer to the created circle.
   */
   virtual CATPCircle * CreatePCircle( const double        iRadius,
                                       const CATSurParam & iCenter,
                                       const CATAngle      iStart,
                                       const CATAngle      iEnd  ,
                                             CATSurface  * iSupport ) =0;

   /** 
   * Creates a trimmed geometric circle defined in the space of a surface
   * from 3 points.
   * @param iStart
   * The first point
   * @param iMiddle
   * The second point
   * @param iStart
   * The third point
   * @param iSupport
   * The pointer to the surface on which the circle is created.
   * @return
   * The pointer to the created circle, oriented as the surface, whatever the points are ordered. 
   */
   virtual CATPCircle * CreatePCircle( const CATSurParam & iStart   ,
                                       const CATSurParam & iMiddle  ,
                                       const CATSurParam & iEnd     ,
                                             CATSurface  * iSupport ) =0;


   //-----------------------------------------------------------------------------
   //- PEllipse creation
   //-----------------------------------------------------------------------------
   /**
   * Creates a trimmed ellipse defined in the space of a surface.
   * <br>Please refer to the encyclopedia to the detailed definition of the start and end angle.
   * @param iMajorAxis
   * The length of the half major axis.
   * @param iMinorAxis
   * The length of the half minor axis.
   * @param iOffsetAngle
   * The angle between the first direction <tt>u</tt> of the surface and the
   * major axis of the ellipse.
   * @param iCenter
   * The intersection between the minor axis and the major axis.
   * @param iStart
   * The angle low limitation measured from the major axis (in Radians).
   * @param iEnd
   * The angle high limitation measured from the major axis (in Radians).
   * @param iSupport
   * The pointer to the surface on which the ellipse is created.
   * @return
   * The pointer to the created ellipse. 
   */
   virtual CATPEllipse * CreatePEllipse( const double      &iMajorAxis,
                                         const double      &iMinorAxis,
                                         const double      &iOffsetAngle,
                                         const CATSurParam &iCenter,
                                         const CATAngle     iStart,
                                         const CATAngle     iEnd  ,
                                               CATSurface   *iSupport ) =0;
   /**
   * Creates an untrimmed ellipse defined in the space of a surface.
   * @param iMajorAxis
   * The length of the half major axis.
   * @param iMinorAxis
   * The length of the half minor axis.
   * @param iOffsetAngle
   * The angle between the first direction <tt>u</tt> of the surface and the
   * major axis of the ellipse.
   * @param iCenter
   * The intersection between the minor axis and the major axis.
   * @param iSupport
   * The pointer to the surface on which the ellipse is created.
   * @return
   * The pointer to the created ellipse.
   */  
   virtual CATPEllipse * CreatePEllipse( const double      & iMajorAxis  ,
                                         const double      & iMinorAxis  ,
                                         const double      & iOffsetAngle,
                                         const CATSurParam & iCenter     ,
                                               CATSurface  * iSupport    ) =0;

   /**
   * Creates a trimmed ellipse defined in the space of a surface.
   * <br>Please refer to the encyclopedia to the detailed definition of the start and end angle.
   * @param iAxis
   * The ellipse axis system (center, major axis, minor axis), positively oriented.
   * @param iMajorAxis
   * The length of the half major axis.
   * @param iMinorAxis
   * The length of the half minor axis.
   * @param iStart
   * The angle low limitation measured from the major axis (in Radians).
   * @param iEnd
   * The angle high limitation measured from the major axis (in Radians).
   * @param iSupport
   * The pointer to the surface on which the ellipse is created.
   * @return
   * The pointer to the created ellipse.
   */
   virtual CATPEllipse * CreatePEllipse( const CATMathAxis2D & iAxis     ,
                                         const double        & iMajorAxis,
                                         const double        & iMinorAxis,
                                         const CATAngle        iStart    ,
                                         const CATAngle        iEnd      ,
                                               CATSurface    * iSupport  ) =0;
   /**
   * Creates an untrimmed ellipse defined in the space of a surface.
   * @param iAxis
   * The ellipse axis system (center, major axis, minor axis), positively oriented.
   * @param iMajorAxis
   * The length of the half major axis.
   * @param iMinorAxis
   * The length of the half minor axis.
   * @param iSupport
   * The pointer to the surface on which the ellipse is created.
   * @return
   * The pointer to the created ellipse.
   */  
   virtual CATPEllipse * CreatePEllipse(const CATMathAxis2D & iAxis     ,
                                        const double        & iMajorAxis,
                                        const double        & iMinorAxis,
                                              CATSurface    * iSupport  ) =0;
   //-----------------------------------------------------------------------------
   //- PParabola creation
   //-----------------------------------------------------------------------------

   /**
   * Creates a trimmed parabola defined in the space of a surface.
   * @param iAxis
   * The system of 2D axis of the parabola. In this system, the implicit equation is
   *       <tt>Y^2 = 2*iP*X</tt>.
   * @param iP
   * Twice the length from the vertex of the parabola to its focus.
   * @param iStart
   * The first limit of the parabola.
   * @param iEnd
   * The last limit of the parabola.
   * These parameters correspond to the current limits of the parabola with respect to
   * the parametrization 
   *   <tt>X(t) = t^2/(2*p),  Y(t) = t </tt>  , where X and Y are relative to <tt>iAxis</tt>.
   *  <br>Notice that this parameterization is not the internal paramaterization.
   * @param iSupport
   * The pointer to the surface on which the parabola is created.
   * @return
   * The pointer to the created parabola.
   */
   virtual CATPParabola * CreatePParabola(const CATMathAxis2D & iAxis    ,
                                          const double          iP       ,
                                          const double          iStart   ,
                                          const double          iEnd     ,
                                                CATSurface    * iSupport ) =0;
   /**
   * Creates an untrimmed parabola defined in the space of a surface.
   * @param iAxis
   * The system of 2D axis of the parabola. In this system, the implicit equation is
   *       <tt>Y^2 = 2*p*X</tt>
   * @param iP
   * Twice the length from the vertex of the parabola to its focus .
   * @param iSupport
   * The pointer to the surface on which the parabola is created.
   * @return
   * The pointer to the created parabola.
   */
   virtual CATPParabola * CreatePParabola(const CATMathAxis2D & iAxis    ,
                                          const double          ip       ,
                                                CATSurface    * iSupport ) =0;

   //-----------------------------------------------------------------------------
   //- PHyperbola creation
   //-----------------------------------------------------------------------------

   /**
   * Creates a trimmed hyperbola defined in the space of a surface.
   * @param iAxis
   * The system of 2D axis of the hyperbola. In this system, the hyperbola is the branch
   * along the positive X corresponding to the implicit equation
   *       <tt>X^2/(iA^2) - Y^2/(iB^2) = 1</tt>
   * @param iA
   * The length between the center and the vertex.
   * @param iB
   * The distance between focus and center <tt>c = sqrt(iA^2+iB^2)</tt>; eccentricity <tt>e = c/iA > 1</tt>.
   * @param iStart
   * The first limit.
   * @param iEnd
   * The last limit.
   * These parameters correspond to the current limits of the parabola with respect to
   * the parameterization 
   *   <tt>X(t) = a*cosh(t), Y(t) = b*sinh(t)</tt>  , where  X and Y are relative to <tt>iAxis</tt>.
   *  <br>Notice that this parameterization is not the internal parameterization.
   * @param iSupport
   * The pointer to the surface on which the parabola is created.
   * @return
   * The pointer to the created hyperbola.
   */
   virtual CATPHyperbola * CreatePHyperbola(const CATMathAxis2D & iAxis    ,
                                            const double          iA       ,
                                            const double          iB       ,
                                            const double          iStart   ,
                                            const double          iEnd     ,
                                                  CATSurface    * iSupport ) =0;

   /**
   * Creates an untrimmed hyperbola defined in the space of a surface.
   * @param iAxis
   * The system of 2D axis of the hyperbola. In this system, the hyperbola is the branch
   * along the positive X corresponding to the implicit equation
   *       <tt>X^2/(iA^2) - Y^2/(iB^2) = 1</tt>.
   * @param iA
   * The length between the center and the vertex.
   * @param iB
   * The distance between focus and center <tt>c = sqrt(iA^2+iB^2)</tt>; eccentricity <tt>e = c/iA > 1</tt>.
   * @param iSupport
   * The pointer to the surface on which the parabola is created.
   * @return
   * The pointer to the created hyperbola.
   */
   virtual CATPHyperbola * CreatePHyperbola(const CATMathAxis2D     & iAxis    ,
                                            const double              iA       ,
                                            const double              iB       ,
                                                  CATSurface        * iSupport ) =0;


   //-----------------------------------------------------------------------------
   //- PNurbs creation
   //-----------------------------------------------------------------------------
   /**
   * Creates a NURBS curve defined in the space of a surface.
   * @param iKnotVector
   * The nodal vector.
   * @param iIsRational
   * <b>Legal values</b>: 1 if the NURBS is rational, 0 otherwise.
   * @param iVertices
   * The list of the vertices. The vertices (control points) coordinates are given as surface parameters in the
   * following order: <tt>u1, v1, u2, v2,...</tt>. Please refer to the enclycopedia to have a detailed
   * description of the NURBS representation.
   * @param iWeigths
   * The array of the weights.
   * @param iSupport
   * The pointer to the surface on which the nurbs is created.
   * @param iParameterizationOption
   * The option of parameterization. By default, the parameterization of the NURBS is modified to better
   * fit internal criteria. In this case, you can recover the initial parameterization 
   * with the @href CATPNurbs#GetOriginalParametrisationDATA method.
   * @return 
   * The pointer to the created curve.
   */
   virtual CATPNurbs * CATCreatePNurbs(      CATKnotVector            & iKnotVector,
                                       const CATLONG32                & iIsRational,
                                       const double                   * iVertices  ,
                                       const double                   * iWeights   ,
                                             CATSurface               * iSupport   ,
                                       const CATParameterizationOption  iParameterizationOption = CatAutomaticParameterization ) =0;


   /**
   * @nodoc
   * @deprecated V5R16 CATCreatePNurbs
   */
   virtual CATPNurbs * CreatePNurbs(CATKnotVector                 & iKnotVector,
                                    const CATLONG32               & iIsRational, 
                                    const double                  * iVertices,
                                    const double                  * iWeights,
                                          CATSurface              * iSupport,
                                    const CATParameterizationOption iParameterizationOption = CatAutomaticParameterization ) =0;

   //-----------------------------------------------------------------------------
   //- PSpline creation
   //-----------------------------------------------------------------------------
   /**
   * Creates a cubic spline curve defined in the space of a surface.
   *<br>This is particulary usefull for creating intersection curves. 
   * @param iPoints
   * The pointer to a CATMathSetOfPointsND, with N>=2. The points are supposed
   * to belong to the surface.
   * @param iFirstCoordIndex
   * The coordinate index of the ND points to be taken as the first coordinate  
   * of the constructing points of the spline.
   * @param iSecondCoordIndex
   * The coordinate index of the ND points to be taken as the second coordinate  
   * ofthe constructing points of the spline.
   * @param iParameters
   * The array of parameters defining a user parametrization. 
   * If <tt>NULL</tt>, the
   * parametrization is automatically defined. The size of the array is the 
   * number of points of the CATMathSetOfPointsND.
   * @param iSupport
   * The surface to which the curve belongs to.
   * @return
   * The pointer to the created curve.
   */
   virtual CATPSpline * CreatePSpline(const CATMathSetOfPointsND * iPoints,
                                      const CATLONG32            & iFirstCoordIndex,
                                      const CATLONG32            & iSecondCoordIndex,
                                      const double               * iParameters,
                                            CATSurface           * iSupport ) =0;
   /**
   * Creates a quintic spline curve defined in the space of a surface.
   *<br>This enables to create precise intersection curves with a low number of arc.
   * @param iParams
   * The pointer to a CATMathSetOfPointsND of dimension 1  defining a user parameterization.
   * @param iPoints
   * The pointer to a CATMathSetOfPointsND containing points of a PSpline
   * @param iTangents
   * The pointer to a CATMathSetOfPointsND containing tangents of a PSpline
   * @param iSecondDerivatives
   * The pointer to a CATMathSetOfPointsND containing second derivatives of a PSpline
   * @param iFirstCoordIndex
   * This index is such that the points, tangents and second derivatives of the
   * first coordinate of the spline are the values of index <tt>iFirstCoordIndex</tt>.
   * @param iSecondCoordIndex
   * Same as iFirstCoordIndex but for the second coordinate of the spline.
   * @param iSupport
   * The surface to which the curve belongs to.
   * @return 
   * The pointer to the created curve.
   */
   virtual CATPSpline * CreatePSpline(const CATMathSetOfPointsND * iParams,
                                      const CATMathSetOfPointsND * iPoints,
                                      const CATMathSetOfPointsND * iTangents,
                                      const CATMathSetOfPointsND * iSecondDerivatives,
                                      const CATLONG32              iFirstCoordIndex,
                                      const CATLONG32              iSecondCoordIndex,
                                            CATSurface           * iSupport ) =0;


   //-------------------------------------------------------------------------
   //- SimCurve creation.
   //-------------------------------------------------------------------------
   /**
   * Creates the curve that aggregates identical curves.
   * @param iCurves
   * The list of curve pointers.
   * @param iLimits
   * The list of limitations of the curves.
   * @param iOrns
   * The list of relative orientation of the curves. 
   * <br><b>Legal values</b>: 
   * <dl><dt>1</dt><dd>same orientation
   * <dt>-1</dt><dd>opposite orientation
   * </dl>
   * @param iGap
   * The maximum allowed gap between the curves.
   * @return
   * The created curve.
   */
   virtual CATSimCurve * CreateSimCurve (       CATLISTP(CATCurve)     & iCurves  ,
                                                CATLISTP(CATCrvLimits) & iLimits  ,
                                                CATListOfInt           & iOrns    ,
                                          const double                   iGap     ) = 0 ; 


   //-------------------------------------------------------------------------
   //- Plane creation
   //-------------------------------------------------------------------------
   /**
   * Creates a geometric plane from a mathematical plane.
   * @param iMathPlane
   * The mathematical point.
   * @return 
   * The pointer to the created plane.
   */
   virtual CATPlane * CreatePlane (const CATMathPlane &iMathPlane) = 0;


   //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   //- Plane creation with its equation coefficient
   //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   /**
   * Creates a geometric plane at a distance to a CATMathPlane.
   * @param iMathNormal
   * The normal to the plane.
   * @param iDistance
   * The distance along the normal direction.
   * @return 
   * The created plane.
   */
   virtual CATPlane * CreatePlane (const CATMathDirection & iMathPlaneNormal,
                                   const double           & iDistance       ) = 0;

   //-------------------------------------------------------------------------
   //- NurbsSurface creation
   //-------------------------------------------------------------------------
   /**
   * Creates a geometric NURBS surface. 
   * Please refer to the enclycopedia to have a detailed
   * description of the NURBS representation.
   * @param iKnotVectorU
   * The nodal vector in the first direction.
   * @param iKnotVectorV
   * The nodal vector in the second direction.
   * @param iIsRational
   * <b>Legal values</b>: 1 if the NURBS is rational, 0 otherwise.
   * @param iVertices
   * The grid of the vertices.
   * @param iWeigths
   * The array of the weights.
   * @param iParameterizationOption
   * The option of parameterization. By default, the parameterization of the NURBS is modified to better
   * fit internal criteria. In this case, you can recover the initial parameterization 
   * with the @href CATNurbsSurface#GetOriginalParametrisationDATA method.
   * @return 
   * The pointer to the created surface.
   */
   virtual CATNurbsSurface * CATCreateNurbsSurface (const CATKnotVector             & iKnotVectorU, 
                                                    const CATKnotVector             & iKnotVectorV,
                                                    const CATLONG32                 & iIsRational, 
                                                    const CATMathGridOfPoints       & iVertices,
                                                    const double                   *  iWeights,
                                                    const CATParameterizationOption   iParameterizationOption = CatAutomaticParameterization )  = 0;
   /**
   * @nodoc
   * @deprecated V5R14 CATCreateNurbsSurface
   */
   virtual CATNurbsSurface * CreateNurbsSurface    (const CATKnotVector             & iKnotVectorU, 
                                                    const CATKnotVector             & iKnotVectorV,
                                                    const CATLONG32                 & iIsRational, 
                                                    const CATMathGridOfPoints       & iVertices,
                                                    const double                   *  iWeights,
                                                    const CATParameterizationOption   iParameterizationOption = CatAutomaticParameterization )  = 0;

   /**
   * Creates a geometric sphere.
   * @param iAxis
   * The axis of the sphere.
   * @param iRadius
   * The radius of the sphere.
   * @return
   * The pointer to the created sphere.
   */
   virtual CATSphere * CreateSphere                (const CATMathAxis &iAxis,
                                                    const double      iRadius) =0;

   /**
   * Creates a piece of a geometric cylinder.
   * @param iAxis
   * The axis of the cylinder: 
   * <ul>
   * <li>The third direction is the rotation axis. </li>
   * <li>The first direction is the angle reference. Start and end angles are counted from 
   * this direction.</li>
   * </ul>
   * @param iRadius
   * The radius of the cylinder on the plane defined by the first 
   * and second directions of iAxis.
   * @param iAxisStart
   * The start limit along the rotation axis (third direction of iAxis).
   * @param iAxisEnd
   * The end limit along the rotation axis (third direction of iAxis)
   * @param  iAngleStart
   * The start angle in radians, counted from the first direction of iAxis.
   * When standing along the third direction of iAxis, 
   * on the plane defined by the first and second directions of iAxis, positive angles
   * are counter-clockwise (right-hand rule). 
   * If angle values are too large or inconsistent, a 2*Pi surface is created.
   * @param  iAngleEnd
   * The end angle in radians, counted from the first direction of iAxis.
   * When standing along the third direction of iAxis, 
   * on the plane defined by the first and second directions of iAxis, positive angles
   * are counter-clockwise (right-hand rule).
   * If angle values are too large or inconsistent, a 2*Pi surface is created.
   * @return
   * The pointer to the created cylinder.
   */
   virtual CATCylinder * CreateCylinder            (const CATMathAxis & iAxis,
                                                    const double      & iRadius,
                                                    const double      & iAxisStart,
                                                    const double      & iAxisEnd,
                                                    const CATAngle    & iAngleStart,
                                                    const CATAngle    & iAngleEnd) =0;
   
   /**
   * Creates a frustum of a geometric cone.
   * @param iConeAxis
   * The cone axis: 
   * <ul>
   * <li>The third direction is the rotation axis. </li>
   * <li>The first direction is the angle reference. Start and end angles are counted from 
   * this direction.</li>
   * <li>The first and second directions define a plane which supports the base radius.</li>
   * </ul>
   * @param iStartRadius
   * The radius on the plane defined by the first and second directions of iConeAxis.
   * @param iConeAngle
   * The external angle of the cone in radians (angle between the cone and the plane supporting the base radius).
   * The validity range of the cone angle is: <br>
   * <tt>0 < ConeAngle < Pi/2</tt>.
   * @param iStartAngle
   * The start angle in radians, counted from the first direction of iConeAxis.
   * When standing along the third direction of iConeAxis, 
   * on the plane defined by the first and second directions of iConeAxis, positive angles
   * are counter-clockwise(right-hand rule). 
   * If angle values are too large or inconsistent, the cone is created around 2*Pi.
   * @param iEndAngle
   * The end angle in radians, counted from the first direction of iConeAxis.
   * When standing along the third direction of iConeAxis, 
   * on the plane defined by the first and second directions of iConeAxis, positive angles
   * are counter-clockwise(right-hand rule). 
   * If angle values are too large or inconsistent, the cone is created around 2*Pi.
   * @param iStartRuleLength
   * The start limit of the cone <b>slant height</b> (the length is not
   * counted along the third direction of iConeAxis but along the cone surface).
   * @param iEndRuleLength
   * The end limit of the cone <b>slant height</b> (the length is not
   * counted along the third direction of iConeAxis but along the cone surface).
   * @return 
   * The pointer to the created cone.
   */
   virtual CATCone * CreateCone(const CATMathAxis &iConeAxis,
                                const double      iStartRadius,
                                const CATAngle    iConeAngle,
                                const CATAngle    iStartAngle,
                                const CATAngle    iEndAngle,
                                const double      iStartRuleLength,
                                const double      iEndRuleLength) =0;


   /**
   * Creates a piece of a geometric torus.
   * A torus is defined by an axis and two radii. 
   * The major ring sweeps a circle in the plane which is 
   * defined by the first and second direction of iTorusAxis.
   * Its radius is iMajorRadius and it is centered at the origin of iTorusAxis.
   * The minor ring sweeps a circle of radius iMinorRadius, centered at some point 
   * on the major ring and lying in the plane containing this center point,
   * the origin of iTorusAxis, and the vector defined by the third direction of iTorusAxis.
   * A piece of the full torus is defined by limiting the angles 
   * through which the major ring sweeps and those through which every minor ring sweeps. 
   * @param iTorusAxis
   * The axis of the torus: 
   * <ul>
   * <li>The third direction is the rotation axis. </li>
   * <li>The first direction is the major angle reference. Start and end major angles are counted from 
   * this direction.</li>
   * </ul>
   * @param iMajorRadius
   * The radius of the major ring.
   * @param iMajorStartAngle
   * The start limit of the major ring in radians, counted from the first direction of iTorusAxis.
   * Positive angles are defined by the right-hand rule around the torus axis.
   * The major start angle must be less than the major end angle. 
   * <tt>iMajorEndAngle - iMajorStartAngle</tt> must not be greater than 2*Pi.
   * @param iMajorEndAngle
   * The end limit of the major ring in radians, counted from the first direction of iTorusAxis.
   * Positive angles are defined by the right-hand rule around the torus axis.
   * The major end angle must be greater than the major start angle.<br>
   * <tt>iMajorEndAngle - iMajorStartAngle</tt> must not be greater than 2*Pi.
   * @param iMinorRadius
   * The radius of the minor ring.
   * @param iMinorStartAngle
   * The first limit of the minor circle in radians. Positive angles are in the 
   * direction of the torus axis. Angles are counted from 
   * the external minor radius in the plane
   * defined by the first and second direction of the torus axis. 
   * The minor start angle must be less than the minor end angle. 
   * <tt>iMinorEndAngle - iMinorStartAngle</tt> must not be greater than 2*Pi.
   * @param iMinorEndAngle
   * The end limit of the minor circle in radians. Positive angles are in the direction
   * of the torus axis. Angles are counted from the external minor radius in the plane
   * defined by the first and second direction of the torus axis.
   * The minor end angle must be greater than the minor start angle.
   * <tt>iMinorEndAngle - iMinorStartAngle</tt> must not be greater than 2*Pi.
   * @return
   * The pointer to the created torus.
   */
   virtual CATTorus * CreateTorus(const CATMathAxis &iTorusAxis,
                                  const double      iMajorRadius,
                                  const CATAngle    iMajorStartAngle,
                                  const CATAngle    iMajorEndAngle,
                                  const double      iMinorRadius,
                                  const CATAngle    iMinorStartAngle,
                                  const CATAngle    iMinorEndAngle) = 0;

   /**
   * Creates a piece of a geometric self-intersecting torus.
   * @param iTorusAxis
   * The axis of the torus.
   * @param iMajorRadius
   * The radius of the major circle, inferior to minor radius.
   * @param iMajorStartAngle
   * The start limit of the major ring in radians, counted from the first direction of iTorusAxis.
   * Positive angles are defined by the right-hand rule around the torus axis.
   * The major start angle must be less than the major end angle. <br>
   * <tt>iMajorEndAngle - iMajorStartAngle</tt> must not be greater than 2*Pi.
   * @param iMajorEndAngle
   * The end limit of the major ring in radians, counted from the first direction of iTorusAxis.
   * Positive angles are defined by the right-hand rule around the torus axis.
   * The major start angle must be less than the major end angle. <br>
   * <tt>iMajorEndAngle - iMajorStartAngle</tt> must not be greater than 2*Pi.
   * @param iMinorRadius
   * The radius of the minor circle, superior to major radius.
   * @param iCorePart
   * The side to keep.
   * <br><b>Legal values</b>:
   * <tt>TRUE</tt> to keep the internal part of the self-intersecting torus,
   * the result is shaped like a lemon.
   * <tt>FALSE</tt> to keep the external part, the result is shaped like an apple. 
   * @return
   * The pointer to the created torus.
   */
   virtual CATTorus * CreateTorus(const CATMathAxis & iTorusAxis,
                                        double        iMajorRadius,
                                  const CATAngle      iMajorStartAngle,
                                  const CATAngle      iMajorEndAngle,
                                        double        iMinorRadius,
                                  const CATBoolean    iCoreSide) = 0;

   /**
   * Creates a trimmed tabulated cylinder.
   * @param iProfile
   * The pointer to the profile.
   * @param iDirection
   * The direction along which the profile is swept.
   * @param iStart
   * The first limit along <tt>iDirection</tt> (can be negative ).
   * @param iEnd
   * The end limit along <tt>iDirection</tt>.  It can be negative , but <tt>iStart <= iEnd </tt>.
   * @return
   * The pointer to the created tabulated cylinder.
   */

   virtual CATTabulatedCylinder * CreateTabulatedCylinder(      CATCurve         * iProfile  ,
                                                          const CATMathDirection & iDirection,
                                                          const double           & iStart    ,
                                                          const double           & iEnd      ) =0;


   /**
   * Creates a CATTabulatedCylinder.
   * <br>If the input profile is a CATPCurve, this method tries to optimize the resulting surface
   * by replacing as far as possible the PCurve by a 3D Curve.
   * @param iProfile
   * The pointer to the profile.
   * @param iProfileLimits
   * The profile limitations.
   * @param iDirection
   * The direction along which the profile is swept.
   * @param iStart
   * The first limit along <tt>iDirection</tt> (can be negative ).
   * @param iEnd
   * The end limit along <tt>iDirection</tt>.  It can be negative , but <tt>iStart <= iEnd </tt>.
   * @param OrientationChanged
   * In case of the optimization, the relative orientation between <tt>iProfile</tt> and the generated
   * 3D curve.
   * <br><b>Legal values </b>:
   * <tt>TRUE</tt> for the same orientation, <tt>TRUE</tt> for the opposite.
   * @return
   * The pointer to the created tabulated cylinder.
   */
   virtual CATTabulatedCylinder * CreateTabulatedCylinder(      CATCurve        *  iProfile,
                                                          const CATCrvLimits     & iProfileLimits,
                                                          const CATMathDirection & iDirection,
                                                          const double           & iStart,
                                                          const double           & iEnd,
                                                                CATBoolean       & ioIsOrientationChanged) =0;

   /**
   * Creates a trimmed geometric revolution surface.
   * @param iProfile
   * The pointer to the profile.
   * @param iRefAxis
   * The axis sytem. The profile is rotated around the Z axis, and must not intersect this axis, except
   * at it first or last limits.
   * @param iStart
   * The low limitation of the rotation (in Radians).
   * @param iEnd
   * The high limitation of the rotation (in Radians).
   * @return
   * The pointer to the created revolution surface.
   */
   virtual CATRevolutionSurface * CreateRevolutionSurface(      CATCurve   *  iProfile,
                                                          const CATMathAxis & iRefAxis,
                                                          const CATAngle    & iStart  ,
                                                          const CATAngle    & iEnd    ) =0;

   /**
   * Creates a CATRevolutionSurface.
   * <br>If the input profile is a CATPCurve, this method tries to optimize the resulting surface
   * by replacing as far as possible the PCurve by a 3D Curve.
   * @param iProfile
   * The pointer to the profile.
   * @param iProfileLimits
   * The profile limitations.
   * @param iRefAxis
   * The axis sytem. The profile is rotated around the Z axis, and must not intersect this axis, except
   * at it first or last limits.
   * @param iStart
   * The low limitation of the rotation (in Radians).
   * @param iEnd
   * The high limitation of the rotation (in Radians).
   * @param OrientationChanged
   * In case of the optimization, the relative orientation between <tt>iProfile</tt> and the generated
   * 3D curve.
   * <br><b>Legal values </b>:
   * <tt>TRUE</tt> for the same orientation, <tt>TRUE</tt> for the opposite.
   * @return
   * The pointer to the created revolution surface.
   */
   virtual CATRevolutionSurface * CreateRevolutionSurface(      CATCurve    *  iProfile,
                                                          const CATCrvLimits & iProfileLimits,
                                                          const CATMathAxis  & iRefAxis,
                                                          const CATAngle     & iStart,
                                                          const CATAngle     & iEnd,
                                                                CATBoolean   & ioIsOrientationChanged ) =0;

   //-----------------------------------------------------------------------------
   //- OffsetSurface basic creation implementation
   // Offset is related to normalized DiReference/DU ^ DiReference/DV.
   // Offset may be negative.
   //-----------------------------------------------------------------------------

   /**
   * Creates a geometric offseted surface.
   * @param iOffset
   * The offset value, relative to the normalized normal to the surface 
   * (cross product of the first derivative with respect to the first direction with the first
   * derivative in the second direction).
   * @param iReference
   * The pointeur to the surface to offset.
   * @param iLimits
   * The limits on <tt>iReference</tt> to take into account in the offset operation.
   * @return
   * The pointer to the created surface.
   */
   virtual CATOffsetSurface * CreateOffsetSurface(const double          iOffset   ,
                                                        CATSurface   *  iReference,
                                                  const CATSurLimits  & iLimits   )  =0 ;


   //-------------------------------------------------------------------------
   // Constant Law creation
   //-------------------------------------------------------------------------
   /** 
   * Creates a constant law.
   * <br>A law is a function <tt>L</tt> of one parameter <tt>iT</tt> on a given 1D interval
   * <tt>[iTmin,iTmax]</tt>. A constant law is such that <tt>L(iT)=iConstant</tt> on the
   * definition interval.
   * @param iTMin
   * The lower bound of the definition interval.
   * @param iTMax
   * The upper bound of the definition interval.
   * @param iConstant
   * The constant value on the interval.
   * @return
   * The pointer to the created law.
   */
   virtual CATConstantLaw * CreateConstantLaw (const double iTMin    ,
                                               const double iTMax    ,
                                               const double iConstant) = 0;
   /** 
   * Duplicates <tt>this</tt> law.
   * @param iToCopy
   * The pointer to the law to copy.
   * @return
   * The pointer to the created law. 
   */
   virtual CATConstantLaw * CreateConstantLaw (CATConstantLaw *iToCopy) = 0;

   //-------------------------------------------------------------------------
   // Linear Law creation
   //-------------------------------------------------------------------------
   /** 
   * Creates a linear law.
   * <br>A law is a function <tt>L</tt> of one parameter <tt>iT</tt> on a given 1D interval
   * <tt>[iTmin,iTmax]</tt>. A linear law is line segment between <tt>L(iTmin)=iValueAtTMin</tt>
   * and <tt>L(iTmax)=iValueAtTMax</tt>.
   * @param iTMin
   * The lower bound of the definition interval.
   * @param iValueAtTMin
   * The law value on the lower bound of the definition interval.
   * @param iTMax
   * The upper bound of the definition interval.
   * @param iValueAtTMax
   * The law value on the upper bound of the definition interval.
   * @return
   * The pointer to the created law.
   */
   virtual CATLinearLaw * CreateLinearLaw (const double iTMin       ,
                                           const double iValueAtTMin,
                                           const double iTMax       ,
                                           const double iValueAtTMax) = 0;

   /** 
   * Duplicates <tt>this</tt> law.
   * @param iToCopy
   * The pointer to the law to copy.
   * @return
   * The pointer to the created law. 
   */
   virtual CATLinearLaw * CreateLinearLaw (CATLinearLaw *iToCopy) = 0;


   //-------------------------------------------------------------------------
   // Spline Law creation
   //-------------------------------------------------------------------------
   /** 
   * Creates a spline law.
   * <br>A law is a function <tt>L</tt> of one parameter <tt>iT</tt> on a given 1D interval
   * <tt>[iTmin,iTmax]</tt>. A spline law is a spline interpolation function between points with
   * imposed tangents.
   * @param iNbrOfConstraint
   * The number of interpolation points.
   * @param iT
   * The array of the parameters of the interpolation points.
   * @param iTMax
   * The array of the spline law value at the interpolation points.
   * @return
   * The pointer to the created law.
   */
   virtual CATSplineLaw * CreateSplineLaw (const CATLONG32  iNbrOfConstraint,
                                           const double   * iT              ,
                                           const double   * iValue          ) = 0;
   /** 
   * Duplicates <tt>this</tt> law.
   * @param iToCopy
   * The pointer to the law to copy.
   * @return
   * The pointer to the created law. 
   */
   virtual CATSplineLaw * CreateSplineLaw (CATSplineLaw *iToCopy) = 0;

   //-------------------------------------------------------------------------
   // Composite Law creation
   //-------------------------------------------------------------------------
   /** 
   * Constructs a composite law.
   * @param iNbrOfFunctions
   * The number of CATMathFunctionX intended to be used in the composite law.
   * @param iBorders
   * The array of the CATMathFunctionX borders.
   * @param iFunctions
   * The array of pointers to the CATMathFunctionX intended to be used in the
   * composite law.
   */
   virtual CATCompositeLaw * CreateCompositeLaw (const CATLONG32           iNbrOfFunctions,
                                                 const double            * iBorders       ,
                                                 const CATMathFunctionX ** iFunctions     ) = 0;

   //-------------------------------------------------------------------------
   // ForeignSurface creation
   //-------------------------------------------------------------------------
   /**
   * Creates a foreign surface.
   * @param iForeignSurfaceData
   * The pointer to the data defining the foreign surface.
   * @return
   * The pointer to the created surface.
   */
   virtual CATIForeignSurface * CreateForeignSurface(CATForeignSurfaceData* iForeignSurfaceData) = 0;

   //-------------------------------------------------------------------------
   // ForeignCurve creation 
   //-------------------------------------------------------------------------
   /**
   * Creates a foreign curve.
   * @param iForeignCurveData
   * The pointer to the data defining the foreign curve.
   * @return
   * The pointer to the created curve.
   */
   virtual CATIForeignCurve   * CreateForeignCurve  (CATForeignCurveData  * iForeignCurveData  ) = 0;

   //-------------------------------------------------------------------------
   // ForeignPCurve creation 
   //-------------------------------------------------------------------------
   /**
   * Creates a foreign Pcurve.
   * @param iForeignPCurveData
   * The pointer to the data defining the foreign Pcurve.
   * @param iSurface
   * The pointer to the surface on which the curve is defined.
   * @return
   * The pointer to the created Pcurve.
   */
   virtual CATIForeignPCurve  * CreateForeignPCurve (CATForeignPCurveData * iForeignPCurveData ,
                                                     CATSurface           * iSurface) = 0;



   /**
   * The canonical (implicit) objects.
   *@param CATGeoFactory::O
   * The origin point <tt>(0,0,0)</tt>
   *@param CATGeoFactory::OI
   * The infinite line <tt>y=0,z=0</tt>
   *@param CATGeoFactory::OJ
   * The infinite line <tt>x=0,z=0</tt>
   *@param CATGeoFactory::OK</tt>
   * The infinite line <tt>x=0,y=0</tt>
   *@param CATGeoFactory::OIJ
   * The infinite plane <tt>z=0</tt>
   *@param CATGeoFactory::OJK
   * >The infinite plane <tt>x=0</tt>
   *@param CATGeoFactory::OKI
   * The infinite plane <tt>y=0</tt>
   */
   enum CATDatumId { O, OI, OJ, OK, OIJ, OJK, OKI } ;

   /**
   * Returns a constant pointer to a given datum.
   * @param iIdent
   * The type of datum.
   * @return
   * The constant pointer to the required datum.
   */
   virtual const CATGeometry* GetDatum 
      ( const CATGeoFactory::CATDatumId iIdent )const = 0;

  /** 
   * @nodoc
   * DO NOT USE : Use static CATGeoFactoryProtected::GetFactoryProtectedInterface instead
   * TO BE REMOVED
   */
   virtual CATGeoFactoryProtected* GetProtectedInterface() const = 0;








   //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
   //
   //               N O N - C A A             M E T H O D S
   //
   //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

   /**
   * @nodoc
   * Retrieves the CATCGMInternalTol associated with <tt>this</tt> CATGeoFactory.
   */
   virtual CATCGMInternalTol * GetCGMInternalTol() = 0;


   /**
   * @nodoc
   * USING THIS SERVICE MAY LEAD TO CORRUPTED DATA.
   * Defines the model size associated with <tt>this</tt> CATGeoFactory.
   */
   virtual void                SetModelSize(const double &iModelSize) = 0;

   /**
   * @nodoc
   * USING THIS SERVICE MAY LEAD TO CORRUPTED DATA.
   * Defines the model size associated with <tt>this</tt> CATGeoFactory.
   */
   virtual void SetModelSizeAndResolution(double     iModelSizeInUnit           ,
                                          CATBoolean iKeepPreviousResolution    = FALSE,
                                          double     iResolutionC0FromModelSize = 1.E-8 ) = 0;


   /**
   * @nodoc
   * Determine if Tolerances are enough compatible to Allow Copy/Paste between the two Containers
   */
   virtual CATCGMTolerancesCompatibility  CompareTolerances(CATGeoFactory *iOtherFactory, 
                                                            CATBoolean     iThrowIfComparableButNotIdentical = FALSE) = 0 ;

   /**
   * @nodoc
   * Defines the unit associated <tt>this</tt> CATGeoFactory. 
   */
   virtual void      SetUnit(const double iUnitInMeter) = 0;

   /**
   * @nodoc
   * Add an attribute key to the list of geometric kernel attribute keys. 
   * Its type defines its behaviour according to split/merge/copy/... operations.
   */
   virtual void      AddKernelAttributeKey( int iAttributeKey, int iAttributeType ) = 0;

   /**
   * @nodoc
   * Remove an attribute key from the list of geometric kernel attribute keys. 
   */
   virtual void      RemoveKernelAttributeKey( int iAttributeKey ) = 0;

   /**
   * @nodoc
   * Returns the number of geometric kernel attribute keys. 
   */
   virtual CATLONG32 GetNbKernelAttributeKeys() = 0;

   /**
   * @nodoc
   * Returns the i-th geometric kernel attribute key, with its associated type. 
   */
   virtual int       GetKernelAttributeKey   ( CATLONG32 iIndex         ,
                                               int     & oAttributeType ) = 0;

   /**
   * Tests the confusion of 2 points.
   * @param iPoint1
   * The first point to compare.
   * @param iPoint2
   * The second point to compare.
   * @return
   * <dl><dt><tt>FALSE</tt>    <dd> if the distance between the 2 points is 
   *                            smaller than the resolution.
   *     <dt><tt>TRUE</tt>    <dd> if the distance between the 2 points is 
   *                            larger than the resolution.
   * </dl>
   */
   virtual CATBoolean Compare( const CATMathPoint & iPoint1,
                               const CATMathPoint & iPoint2 ) const = 0;

#ifndef CATCGMRemoveNoDocDrop1
   /**
   * @nodoc
   * Use now a CATCloneManager to duplicate a CATCartesianPoint.
   */
   virtual CATCartesianPoint * CreateCartesianPoint (CATCartesianPoint *iPointToCopy) = 0 ;
#endif // CATCGMRemoveNoDocDrop1

#ifndef CATCGMRemoveNoDocDrop2
   /**
   * @nodoc
   * Deprecated.
   */
   virtual CATCartesianPoint * CreateCartesianPoint () = 0 ;
#endif // CATCGMRemoveNoDocDrop2

#ifndef CATCGMRemoveNoDocDrop1
   /**
   * @nodoc
   * Use now a CATCloneManager to duplicate a CATPointOnCurve.
   */
   virtual CATPointOnCurve * CreatePointOnCurve(CATPointOnCurve *iPointToCopy) = 0;
#endif // CATCGMRemoveNoDocDrop1

   /**
   * @nodoc
   * Creates a geometric point lying on a CATEdgeCurve from an existing
   * PointOnCurve based on a curve which is part of the EdgeCurve.
   */
   virtual CATPointOnEdgeCurve* CreatePointOnEdgeCurve(const CATPointOnCurve* iPointOnACurveInEdgeCurve, 
                                                       const CATEdgeCurve   * iSupport                 )= 0 ;

#ifndef CATCGMRemoveNoDocDrop1
   /**
   * @nodoc
   * Use now a CATCloneManager to duplicate a CATPointOnEdgeCurve. 
   */
   virtual CATPointOnEdgeCurve* CreatePointOnEdgeCurve( CATPointOnEdgeCurve* iPointToCopy  )= 0 ; 
#endif // CATCGMRemoveNoDocDrop1

   /**
   *@nodoc
   * Creates a geometric point lying on the <tt>OIJ</tt> datum plane,
   * from a 2D mathematical point.
   */
   virtual CATPointOnSurface * CreatePointOnSurface(const CATMathPoint2D &iMathPoint) = 0 ;

#ifndef CATCGMRemoveNoDocDrop1
   /**
   * @nodoc
   * Use now a CATCloneManager to duplicate a CATPointOnSurface.
   */
   virtual CATPointOnSurface * CreatePointOnSurface(CATPointOnSurface *iPointToCopy) = 0;
#endif // CATCGMRemoveNoDocDrop1

#ifndef CATCGMRemoveNoDocDrop1
   /**
   * @nodoc
   * Use now a CATCloneManager to duplicate a CATMacroPoint.
   */
   virtual CATMacroPoint * CreateMacroPoint ( CATMacroPoint *ToCopy ) = 0 ;
#endif // CATCGMRemoveNoDocDrop1

   //-------------------------------------------------------------------------
   // - CloudOfPoints creation
   //-------------------------------------------------------------------------
   /**
   * @nodoc
   * Creates a permanent list of sets of 3D mathematical points.
   *<br>The list of CATMathSetOfPointsNDs will be referred to and appropriated by the new
   * CATCloudOfPoints. It will be deleted as soon as the CATCloudOfPoints
   * is deleted.
   * @param iListOfPoints
   * The list of set of points.
   * @param iOperatingDistance
   * The distance defining how two points need to be close in order  
   * to be topologically related.
   * @return
   * The pointer to the created cloud of points.
   */
   virtual CATCloudOfPoints * CreateCloudOfPoints(      CATLISTP(CATMathSetOfPointsND) & iListOfPoints     ,
                                                  const double                           iOperatingDistance) = 0 ; 



   //-------------------------------------------------------------------------
   //- Line copy
   //-------------------------------------------------------------------------
#ifndef CATCGMRemoveNoDocDrop1
   /**
   * @nodoc
   * Use now a CATCloneManager to duplicate a CATLine.
   */
   virtual CATLine * CreateLine (CATLine *iLineToCopy) = 0;
#endif // CATCGMRemoveNoDocDrop1

#ifndef CATCGMRemoveNoDocDrop2
   /**
   * @nodoc
   * Deprecated.
   */
   virtual CATCircle * CreateCircle (const CATMathSetOfPoints * iSet   ,
                                           CATCrvLimits       & iLimits) = 0;
#endif // CATCGMRemoveNoDocDrop2
#ifndef CATCGMRemoveNoDocDrop2
   /**
   * @nodoc
   * Creates a geometric circle on the <tt>OIJ</tt> datum plane with a 
   * given radius.
   *<br>The circle center is the <tt>O</tt> datum point.
   */
   virtual CATCircle * CreateCircle (const double iRadius) = 0;
#endif // CATCGMRemoveNoDocDrop2

#ifndef CATCGMRemoveNoDocDrop1
   /**
   * @nodoc
   * Use now a CATCloneManager to duplicate a CATCircle.
   */
   virtual CATCircle * CreateCircle (CATCircle *iCircleToCopy) = 0;
#endif // CATCGMRemoveNoDocDrop1

#ifndef CATCGMRemoveNoDocDrop1
   /**
   * @nodoc
   * Use now a CATCloneManager to duplicate a CATEllipse.
   */ 
   virtual CATEllipse * CreateEllipse (CATEllipse *iEllipseToCopy) = 0;
#endif // CATCGMRemoveNoDocDrop1
#ifndef CATCGMRemoveNoDocDrop2
   //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   //- Ellipse creation on the default XY plane
   //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
   /**
   * @nodoc
   * Creates a geometric ellipse on the <tt>OIJ</tt> datum plane.
   *<br> The ellipse center is the origin of the plane, and
   * the axes, these of the plane.
   */
   virtual CATEllipse * CreateEllipse (const double  iMajorAxis,
                                       const double  iMinorAxis) = 0;
#endif // CATCGMRemoveNoDocDrop2
   //-------------------------------------------------------------------------
   //- Parabola creation
   //-------------------------------------------------------------------------
#ifndef CATCGMRemoveNoDocDrop2
   /**
   * @nodoc
   * Not yet implemented.
   */
   virtual CATParabola * CreateParabola (const double       & iFocalDistance,
                                         const CATMathPlane & iPlane) =0;
#endif //CATCGMRemoveNoDocDrop2

#ifndef CATCGMRemoveNoDocDrop1
   /**
   * @nodoc
   * Not yet implemented.
   */
   virtual CATParabola * CreateParabola (CATParabola *iParabolaToCopy) = 0;
#endif // CATCGMRemoveNoDocDrop1

   //-------------------------------------------------------------------------
   //- Hyperbola creation
   //-------------------------------------------------------------------------
#ifndef CATCGMRemoveNoDocDrop2
   /**
   * @nodoc
   * Not yet implemented.
   */
   virtual CATHyperbola * CreateHyperbola (const double       & iMajaxis,
                                           const double       & iMinaxis,
                                           const CATMathPlane & iPlane  ) = 0;
#endif //CATCGMRemoveNoDocDrop2

#ifndef CATCGMRemoveNoDocDrop1
   /**
   * @nodoc
   * Not yet implemented.
   */
   virtual CATHyperbola * CreateHyperbola (CATHyperbola *iHyperbolaToCopy) = 0;
#endif // CATCGMRemoveNoDocDrop1




   //-----------------------------------------------------------------------------
   //- Helix creation
   //-----------------------------------------------------------------------------
   /**
   * Creates a geometric helix.
   * @param iAxis
   * The helix axis.
   * @param iStartingPoint
   * The origin point of the helix.
   * @param iStart
   * The first limitation of the helix from iStartingPoint. 
   * This angle is considered on the helix itself, rotating about 
   * iAxis according to the iTrigonometricOrientation parameter. 
   * @param iEnd
   * The last limitation of the helix from the origin point.
   * This angle is considered on the helix itself, rotating about iAxis according 
   * to the iTrigonometricOrientation parameter. 
   * @param iPitch
   * The height between two turns.
   * @param iTrigonometricOrientation
   * The orientation of the rotation about the axis oriented 
   * by iHelixAxisOrientation: 1 to turn counterclockwise, -1 to turn clockwise.
   * @param iRadiusEvolution
   * The coefficient of linear variation for the radius. 
   * @return
   * The created helix.
   */
   virtual CATHelix * CreateHelix( const CATMathLine      & iAxis,
                                   const CATMathPoint     & iStartingPoint,
                                   const CATAngle           iStart,
                                   const CATAngle           iEnd,
                                   const double             iPitch,
                                   const CATLONG32          iTrigonometricOrientation,
                                         double             iRadiusEvolution = 0.) = 0 ; 

   //-----------------------------------------------------------------------------
   //- CloudEditor objects creation
   //-----------------------------------------------------------------------------
   /**
   * @nodoc
   */
   virtual CATCldBody         * CreateCldBody          (const CATCldSetOfPoints* iSetOfPoints = NULL) = 0 ;
   /**
   * @nodoc
   */
   virtual CATCldBody         * CreateCldBody          (const CATCldGenEntity  * iEntity) = 0 ;
   /**
   * @nodoc
   */
   virtual CATCldCloud        * CreateCldCloud         (const CATCldGenEntity  * iEntity) = 0 ; 
   /**
   * @nodoc
   */
   virtual CATCldScan         * CreateCldScan          (const CATCldGenEntity  * iEntity) = 0 ; 
   /**
   * @nodoc
   */
   virtual CATCldGrid         * CreateCldGrid          (const CATCldGenEntity  * iEntity) = 0 ; 
   /**
   * @nodoc
   */
   virtual CATCldPolygon      * CreateCldPolygon       (const CATCldGenEntity  * iEntity) = 0 ; 
   /**
   * @nodoc
   */
  virtual CATCldSubPolygon    * CreateCldSubPolygon    (const CATCldPolygon    * iPolygon) = 0;

  /**
   * @nodoc
   */
   virtual CATCldVectors      * CreateCldVectors       (const CATCldGenEntity  * iEntity) = 0 ; 
   /**
   * @nodoc
   */
   virtual CATCldSetOfScans   * CreateCldSetOfScans    (const CATCldGenEntity  * iEntity) = 0 ;
   /**
   * @nodoc
   */
   virtual CATCldSetOfGrids   * CreateCldSetOfGrids    (const CATCldGenEntity  * iEntity) = 0 ;
   /**
   * @nodoc
   */
   virtual CATCldScanOnPolygon* CreateCldScanOnPolygon (const CATCldPolygon    * iPolygon) = 0 ; 
   /**
   * @nodoc
   */
   virtual CATCldSetOfPointsF * CreateCldSetOfPointsF () = 0 ; 
   /**
   * @nodoc
   */
   virtual CATCldSetOfPointsD * CreateCldSetOfPointsD () = 0 ; 
#ifndef CATCGMRemoveNoDocDrop2
   //-----------------------------------------------------------------------------
   //-Deprecated
   //-----------------------------------------------------------------------------
#ifndef PLATEFORME_DS64
   /**
   * @nodoc
   * Use now the CATNurbs class.
   */
   virtual CATBezierCurve* CreateBezierCurve (const int          & iNbOfCtrlPts,
                                              const int          & iNbOfArcs,
                                              const int          * iDegrees,
                                              const CATMathPoint * MathCtrlPts) = 0;
#endif //PLATEFORME_DS64
   /**
   * @nodoc
   * Use now the CATNurbs class.
   */ 
   virtual CATBezierCurve * CreateBezierCurve (const CATLONG32      iNbOfPts,
                                               const CATLONG32      iNbOfArcs, 
                                               const CATLONG32    * iArcsDegree,
                                               const CATMathPoint * iCtrlPts) = 0;

   /**
   * @nodoc
   * Use now the CATNurbs class.
   */  
   virtual CATBezierCurve * CreateBezierCurve (const CATLONG32 iNbOfPts, 
                                               const CATLONG32 iArcDegree,
                                               const CATMathPoint *iCtrlPts) = 0;
   /**
   * @nodoc
   * Use now the CATNurbs class.
   */  
   virtual CATBezierCurve * CreateBezierCurve (const CATLONG32      iNbOfPts,
                                               const CATMathPoint * iCtrlPts) = 0;

   /**
   * @nodoc
   * Use now the CATNurbs class.
   */ 
   virtual CATBezierCurve * CreateBezierCurve (const CATMathSetOfPoints *  SetOfPoints,
                                               const CATLONG32           & iNbOfArcs, 
                                               const CATLONG32          *  iArcsDegree) = 0;
   /**
   * @nodoc
   * Use now the CATNurbs class.
   */   
   virtual CATBezierCurve * CreateBezierCurve (const CATMathSetOfPoints *  SetOfPoints,
                                               const CATLONG32           & iArcDegree ) = 0;
   /**
   * @nodoc
   * Use now the CATNurbs class.
   */   
   virtual CATBezierCurve * CreateBezierCurve (const CATMathSetOfPoints *SetOfPoints) = 0;
#endif // CATCGMRemoveNoDocDrop2

#ifndef CATCGMRemoveNoDocDrop1
   /**
   * @nodoc
   * Use now the CATNurbs class.
   */   
   virtual CATBezierCurve * CreateBezierCurve (CATBezierCurve *ToCopy) = 0;
#endif // CATCGMRemoveNoDocDrop1




#ifndef CATCGMRemoveNoDocDrop1
   /**
   * @nodoc
   * Use now a CATCloneManager to duplicate a CATNurbsCurve.
   */
   virtual CATNurbsCurve * CreateNurbsCurve (CATNurbsCurve *iNurbsToCopy) = 0;
#endif // CATCGMRemoveNoDocDrop1

   /**
   * @nodoc
   * Internal Use.
   */
   virtual CATSplineCurve * CreateSplineCurve(
                                              const CATMathSetOfPointsNDWithVectors * iPoints,
                                              const double                          * iParameters ) =0;

#ifndef CATCGMRemoveNoDocDrop1
   /**
   *@nodoc
   * Use now a CATCloneManager to duplicate a CATSplineCurve.
   */
   virtual CATSplineCurve * CreateSplineCurve(CATSplineCurve *iSplineToCopy) =0;
#endif // CATCGMRemoveNoDocDrop1

#ifndef CATCGMRemoveNoDocDrop2
   /**
   * @nodoc
   */
   virtual CATTrimmedPCurve * CreateTrimmedPCurve(      CATSurface   * iSupport,
                                                        CATPCurve    * iReference, 
                                                  const CATCrvLimits & iLimits) = 0 ;
#endif // CATCGMRemoveNoDocDrop2

   /**
   * @nodoc
   * Creates a trimmed geometric line defined on the <tt>OIJ</tt> datum plane.
   */
   virtual CATPLine * CreatePLine (const CATMathPoint2D & iStart, 
                                   const CATMathPoint2D & iEnd    ) = 0 ;

   /**
   *@nodoc
   * Creates an untrimmed geometric line defined on the <tt>OIJ</tt> datum 
   * plane from a 2D mathematical line.
   */
   virtual CATPLine * CreatePLine (const CATMathLine2D & iMathLineToCopy ) = 0 ;

#ifndef CATCGMRemoveNoDocDrop1
   /**
   * @nodoc
   * Use now a CATCloneManager to duplicate a CATPline.
   */
   virtual CATPLine* CreatePLine(CATPLine *iLineToCopy) = 0 ;
#endif // CATCGMRemoveNoDocDrop1

   /**
   * @nodoc
   * Deprecated.
   */
   virtual CATPLine* CreatePLine(      CATSurface *  iSupport,
                                 const CATSurParam & iStart  ,
                                 const CATSurParam & iEnd    )  = 0 ;

 
   /**
   * @nodoc
   * Creates a trimmed geometric circle defined on the <tt>OIJ</tt> datum plane.
   *<br>The center is assumed to be on the <tt>OIJ</tt> datum plane.
   */
   virtual CATPCircle * CreatePCircle (const double              iRadius,
                                       const CATMathPoint2D    & iCenter,
                                       const CATAngle            iStart ,
                                       const CATAngle            iEnd   ) = 0;
 
 
   /**
   * @nodoc
   * Creates a trimmed geometric circle lying on the <tt>OIJ</tt> datum plane.
   *<br>The points are assumed to be on the <tt>OIJ</tt> datum plane.
   */
   virtual CATPCircle * CreatePCircle (const CATMathPoint2D & iStart ,
                                       const CATMathPoint2D & iMiddle,
                                       const CATMathPoint2D & iEnd   ) = 0 ;
 

#ifndef CATCGMRemoveNoDocDrop1
   /**
   * @nodoc
   * Use now a CATCloneManager to duplicate a CATPCircle.
   */
   virtual CATPCircle * CreatePCircle(CATPCircle *iCircleToCopy) =0;
#endif // CATCGMRemoveNoDocDrop1

#ifndef CATCGMRemoveNoDocDrop1
   /**
   * @nodoc
   * Use now a CATCloneManager to duplicate a CATPEllipse.
   */
   virtual CATPEllipse * CreatePEllipse(CATPEllipse *iEllipseToCopy) =0;
#endif // CATCGMRemoveNoDocDrop1


   //-----------------------------------------------------------------------------
   //- PCurveEquation creation
   //-----------------------------------------------------------------------------
   /** @nodoc */
   virtual CATPCurveEquation* CreatePCurveEquation(const CATMathFunctionX *iFx      ,
                                                   const CATMathFunctionX *iFy      ,
                                                   const double            iStart   ,
                                                   const double            iEnd     ,
                                                   const double            iMaxStart,
                                                   const double            iMaxEnd  ,
                                                         CATSurface       *iSupport ) =0;
   /** @nodoc */
   virtual CATPCurveEquation* CreatePCurveEquation(const CATMathFunctionX *iFx  ,
                                                   const CATMathFunctionX *iFy  ,
                                                   const CATCrvLimits     &TrimLim ,
                                                   const CATCrvLimits     &FullLim ,
                                                         CATSurface       *iSupport ) = 0;

#ifndef CATCGMRemoveNoDocDrop1
   /** @nodoc */
   virtual CATPCurveEquation* CreatePCurveEquation(CATPCurveEquation *ToCopy) =0;
#endif // CATCGMRemoveNoDocDrop1

   //
#ifndef CATCGMRemoveNoDocDrop1
   /**
   * @nodoc
   * Use now a CATCloneManager to duplicate a CATPNurbs.
   */
   virtual CATPNurbs * CreatePNurbs(CATPNurbs *iNurbsToCopy) =0;
#endif // CATCGMRemoveNoDocDrop1

   /**
   * @nodoc
   * Internal Use.
   */
   virtual CATPSpline * CreatePSpline(
                                      const CATMathSetOfPointsNDWithVectors * iPoints    ,
                                      const double                          * iParameters,
                                            CATSurface                      * iSupport   ) =0;

#ifndef CATCGMRemoveNoDocDrop1
   /**
   * @nodoc
   * Use now a CATCloneManager to duplicate a CATPSpline.
   */
   virtual CATPSpline * CreatePSpline(CATPSpline *iSplineToCopy) =0;
#endif // CATCGMRemoveNoDocDrop1

   //-------------------------------------------------------------------------
   //- IntCurve creation.
   //-------------------------------------------------------------------------
   /**
   * @nodoc
   * Use the CATIbtersectionCrvCrvOperator.
   * Creates the curve that aggregates two CATPCurves resulting of an
   * intersection.
   */
   virtual CATIntCurve * CreateIntCurve (       CATPCurve * iC1    ,
                                                CATPCurve * iC2    ) = 0;

   /** @nodoc */
   virtual CATIntCurve * CreateIntCurve ( const CATLONG32   iNbMapX,
                                          const CATMapX  ** iMapX  ,
                                          const double      iMaxGap) = 0;
#ifndef CATCGMRemoveNoDocDrop1
   /**
   * @nodoc
   * Use now a CATCloneManager to duplicate a CATIntCurve.
   */
   virtual CATIntCurve * CreateIntCurve ( CATIntCurve *iIntCurveToCopy ) = 0 ; 
#endif // CATCGMRemoveNoDocDrop1

   /**  @nodoc  */
   virtual CATSimCurve * CreateSimCurve (       CATLISTP(CATCurve)     & iCurves,
                                                CATListOfInt           & iOrns  ,
                                          const double                   iGap   ) = 0 ; 
   /**  @nodoc  */
   virtual CATSimCurve * CreateSimCurve (       CATLISTP(CATCurve)     & iNewCurves,
                                          const double                   iGap   = 0.) = 0 ; 

   /**
   * @nodoc
   * Creates the curve that aggregates one curve.
   * @param iNewCurve
   * The pointer to the first curve to aggregate into the CATSimCurve.
   */
   virtual CATSimCurve * CreateSimCurve (       CATCurve               * iNewCurve ) = 0 ; 
   /** @nodoc */
   virtual CATSimCurve * CreateSimCurve ( const CATLONG32                iNbMapX   ,
                                          const CATMapX               ** iMapX     ,
                                          const double                   iMaxGap   ) = 0;
#ifndef CATCGMRemoveNoDocDrop1
   /**
   * @nodoc
   * Use now a CATCloneManager to duplicate a CATSimCurve.
   */
   virtual CATSimCurve * CreateSimCurve (       CATSimCurve            * iSimCurveToCopy ) = 0 ; 
#endif // CATCGMRemoveNoDocDrop1

   //-------------------------------------------------------------------------
   //- MergedCurve creation.
   //-------------------------------------------------------------------------
   /**
   * @nodoc
   * Creates the curve that aggregates 2 curves.
   *<br> The current limits of each curve is taken into account 
   * to determine the result.
   */
   virtual CATMergedCurve * CreateMergedCurve (  const CATCurve* iC1, 
                                                 const CATCurve* iC2 ) = 0 ; 
   /**
   * @nodoc
   * Creates the curve that aggregates 2 trimmed curves.
   *<br> The limits to take into account is defined for each curve.
   */
   virtual CATMergedCurve * CreateMergedCurve ( const CATCurve     * iC1   ,
                                                const CATCrvLimits & iLim1 ,
                                                const CATCurve     * iC2   ,
                                                const CATCrvLimits & iLim2 ) = 0 ; 
#ifndef CATCGMRemoveNoDocDrop1
   /**
   * @nodoc
   * Use now a CATCloneManager to duplicate a CATMergeCurve.
   */
   virtual CATMergedCurve * CreateMergedCurve (CATMergedCurve *iMergedCurveToCopy) = 0 ; 
#endif // CATCGMRemoveNoDocDrop1

   /**
   * @nodoc
   * Creates the curve that aggregates 2 edges curves between PointOnEdgeCurves.
   *<br> The limits will include all the specifications of the PointOnEdgeCurves.
   *<br> PoecSi and PoecEi must refer to the same EdgeCurve, for i=1 or 2.
   */
   virtual CATMergedCurve * CreateMergedCurve ( const CATPointOnEdgeCurve  * iPoecS1,
                                                const CATPointOnEdgeCurve  * iPoecE1,
                                                const CATPointOnEdgeCurve  * iPoecS2,
                                                const CATPointOnEdgeCurve  * iPoecE2 ) = 0 ; 
   /** @nodoc */
   virtual CATMergedCurve * CreateMergedCurve ( const CATPointOnEdgeCurve  * iPoecS1,
                                                const CATPointOnEdgeCurve  * iPoecE1,
                                                const CATCurve             * iC2    ,
                                                const CATCrvLimits         & iLim2  ) = 0 ;
   /**
   * @nodoc
   * Creates the mergedcurve with your own parameters mapping .
   */
   virtual CATMergedCurve * CreateMergedCurve ( const CATCurve             * iC1  ,
                                                const CATCrvLimits         & iLim1,
                                                const CATCurve             * iC2  ,
                                                const CATCrvLimits         & iLim2,
                                                const CATMathSetOfPointsND & iParamMapping,
                                                const double                 iMaxGap       )= 0; 
   /** @nodoc */
   virtual CATMergedCurve * CreateMergedCurve ( const CATPointOnEdgeCurve*   iPoecS1, 
                                                const CATPointOnEdgeCurve*   iPoecE1, 
                                                const CATPointOnEdgeCurve*   iPoecS2, 
                                                const CATPointOnEdgeCurve*   iPoecE2,
                                                const CATMathSetOfPointsND & iParamMapping,
                                                const double                 iMaxGap       )= 0; 
   /** @nodoc */
   virtual CATMergedCurve * CreateMergedCurve ( const CATLONG32              iNbMapX,
                                                const CATMapX**              iMapX,
                                                const double                 iMaxGap) = 0;

   //-------------------------------------------------------------------------
   //- ContactCurve creation.
   //-------------------------------------------------------------------------
   /** @nodoc */
   virtual CATContactCurve * CreateContactCurve (     CATEdgeCurve* iEdgeCurve,
                                                      CATSurface*   iSurface  ) = 0;

#ifndef CATCGMRemoveNoDocDrop1
   /**
   * @nodoc
   * Use now a CATCloneManager to duplicate a CATContactCurve.
   */
   virtual CATContactCurve * CreateContactCurve ( CATContactCurve *iContactCurveToCopy ) = 0 ; 
#endif // CATCGMRemoveNoDocDrop1

   //-------------------------------------------------------------------------
   //- ProcCurve creation.
   //-------------------------------------------------------------------------
   /** @nodoc */
   virtual CATProcCurve * CreateProcCurve (CATProcCurveDef* iProcCurveDef) = 0;


   /**
   * Creates a geometric plane from 3 mathematical points.
   * <br>The directions are ortho-normalized.
   */
   virtual CATPlane * CreatePlane (const CATMathPoint &iMathOrigin,
                                   const CATMathPoint &iFirstDirection,
                                   const CATMathPoint &iSeconddirection) = 0;

   /**
   * @nodoc
   * Do not use.
   */
   virtual CATPlane * CreatePlane() = 0;

#ifndef CATCGMRemoveNoDocDrop1
   /**
   * @nodoc
   * Use now a CATCloneManager to duplicate a CATPlane.
   */
   virtual CATPlane * CreatePlane (CATPlane *iPLaneToCopy) = 0;
#endif // CATCGMRemoveNoDocDrop1


#ifndef CATCGMRemoveNoDocDrop1
   /**
   * @nodoc
   * Use now a CATCloneManager to duplicate a CATNurbsSurface.
   */
   virtual CATNurbsSurface * CreateNurbsSurface (CATNurbsSurface *iNurbsToCopy) = 0;
#endif // CATCGMRemoveNoDocDrop1

   //-------------------------------------------------------------------------
   //- RuledSurface creation
   //-------------------------------------------------------------------------
   /**
   * @nodoc
   * Creates a geometric ruled surface.
   */
   virtual CATRuledSurface * CreateRuledSurface(
                                                const CATCurve              *  iProfile,
                                                const CATMathDirection       & iDirection,
                                                const CATAngle               & iAngle,
                                                const double                 & iStartLength,
                                                const double                 & iEndLength,
                                                const CATCrvLimits          *  iLimits=0,
                                                const CATLISTP(CATCrvParam) * iPassagePoints=0) = 0;

#ifndef CATCGMRemoveNoDocDrop1
   /**
   * @nodoc 
   * Use now a CATCloneManager to duplicate a CATRuledSurface.
   */
   virtual CATRuledSurface * CreateRuledSurface(CATRuledSurface * iRuledToCopy) = 0;
#endif // CATCGMRemoveNoDocDrop1

   //-------------------------------------------------------------------------
   //- GenericRuledSurface creation
   //-------------------------------------------------------------------------
   /**
   *@nodoc
   * Creates a generic geometric ruled surface.
   * @param iLimits
   * The limitations of the generating curve <tt>iProfile</tt> if necessary.
   * @param iParams
   * The list of imposed passage parameters.
   */
   virtual CATGenericRuledSurface * CreateGenericRuledSurface(
                                                              const CATMathSetOfPointsND * iParams,
                                                              const CATMathSetOfPointsND * iPoints,
                                                              const CATMathSetOfPointsND * iTangents,
                                                              const CATMathSetOfPointsND * iSecondDerivatives,
                                                              const CATLONG32              iFirstTraceIndex,
                                                              const CATLONG32              iSecondTraceIndex) = 0;
#ifndef CATCGMRemoveNoDocDrop1
   /**
   * @nodoc
   * Use now a CATCloneManager to duplicate a CATRuledSurface.
   */
   virtual CATGenericRuledSurface * CreateGenericRuledSurface
      (CATGenericRuledSurface * iGenericRuledToCopy) = 0;
#endif // CATCGMRemoveNoDocDrop1

   /**
   * Creates a piece of a geometric sphere.
   * A sphere is defined by an axis and a radius. 
   * A piece of the full sphere is defined by limiting the meridian and parallel angles. 
   * The meridian planes pass through the axis third direction, 
   * the parallel planes are orthogonal to the axis third direction.
   * @param iAxis
   * The sphere axis.
   * <ul>
   * <li>The third direction is the rotation axis. </li>
   * <li>The first direction is the angle reference. Start and end meridian angles are counted from 
   * this direction.</li>
   * </ul>
   * @param iRadius
   * The sphere radius.
   * @param iMeridianStart
   * The low angle value of the meridians. Positive angles are defined by the right-hand rule. <br>
   * <tt>iMeridianStart < iMeridianEnd</tt><br>
   * If specified angles are too large, the surface is swept around 2*Pi.
   * @param iMeridianEnd
   * The high angle value of the meridians. Positive angles are defined by the right-hand rule.
   * <tt>iMeridianStart < iMeridianEnd</tt><br>
   * If specified angles are too large, the surface is swept around 2*Pi.
   * @param iParallelStart
   * The low angle value of the parallels.<br>
   * Positive angles are in the 
   * direction of the sphere axis. Angles are counted from 
   * the radius in the plane
   * defined by the first and second direction of the sphere axis. 
   * <tt>iParallelStart >= -Pi/2 </tt>; <tt>iParallelStart < iParallelEnd </tt>
   * @param iParallelEnd
   * The high angle value of the parallels. <br>
   * Positive angles are in the 
   * direction of the sphere axis. Angles are counted from 
   * the radius in the plane
   * defined by the first and second direction of the sphere axis. 
   * <tt>iParallelEnd <= Pi/2 </tt>; <tt>iParallelStart < iParallelEnd </tt>
   * @return
   * The created sphere.
   */
   virtual CATSphere * CreateSphere(const CATMathAxis       & iAxis         ,
                                    const double              iRadius       ,
                                    const CATAngle            iMeridianStart,
                                    const CATAngle            iMeridianEnd  ,
                                    const CATAngle            iParallelStart,
                                    const CATAngle            iParallelEnd  ) = 0 ; 


#ifndef CATCGMRemoveNoDocDrop1
   /**
   * @nodoc
   * Use now a CATCloneManager to duplicate a CATSphere.
   */
   virtual CATSphere * CreateSphere(CATSphere *iSphereToCopy) =0;
#endif // CATCGMRemoveNoDocDrop1


#ifndef CATCGMRemoveNoDocDrop1
   /** 
   * @nodoc
   * Use now a CATCloneManager to duplicate a CATCylinder.
   */   
   virtual CATCylinder * CreateCylinder(CATCylinder *iCylinderToCopy) =0;
#endif // CATCGMRemoveNoDocDrop1

#ifndef CATCGMRemoveNoDocDrop1
   /**
   * @nodoc
   * Use now a CATCloneManager to duplicate a CATCone.
   */
   virtual CATCone * CreateCone(CATCone *iConeToCopy) =0;
#endif // CATCGMRemoveNoDocDrop1

#ifndef CATCGMRemoveNoDocDrop1
   /**
   * @nodoc
   * Use now a CATCloneManager to duplicate a CATTorus.
   */
   virtual CATTorus * CreateTorus(CATTorus *iTorusToCopy) =0;
#endif // CATCGMRemoveNoDocDrop1

#ifndef CATCGMRemoveNoDocDrop1
   /**
   * @nodoc
   * Use now a CATCloneManager to duplicate a CATTabulatedCylinder.
   */
   virtual CATTabulatedCylinder * CreateTabulatedCylinder
                                                         (      CATTabulatedCylinder *iTabCylToCopy) =0;
#endif // CATCGMRemoveNoDocDrop1
#ifndef CATCGMRemoveNoDocDrop2
   /** @nodoc */
   virtual CATTabulatedCylinder * CreateTabulatedCylinder(      CATCurve        *  iProfile  ,
                                                          const CATMathDirection & iDirection,
                                                          const double           & iStart    ,
                                                          const double           & iEnd      ,
                                                                CATBoolean       & ioIsOrientationChanged) =0;
#endif // CATCGMRemoveNoDocDrop2

#ifndef CATCGMRemoveNoDocDrop1
   /**
   * @nodoc
   * Use now a CATCloneManager to duplicate a CATRevolutionSurface.
   */
   virtual CATRevolutionSurface * CreateRevolutionSurface(CATRevolutionSurface *iRevolToCopy) =0;
#endif // CATCGMRemoveNoDocDrop1

#ifndef CATCGMRemoveNoDocDrop2
   /** @nodoc */
   virtual CATRevolutionSurface * CreateRevolutionSurface(      CATCurve    *  iProfile,
                                                          const CATMathAxis  & iRefAxis,
                                                          const CATAngle     & iStart  ,
                                                          const CATAngle     & iEnd    ,
                                                                CATBoolean   & oIsOrientationChanged ) =0;
#endif // CATCGMRemoveNoDocDrop2

   //-----------------------------------------------------------------------------
   //- ProcOffsetSurface basic creation implementation
   // Offset is related to normalized DiReference/DU ^ DiReference/DV.
   // Offset may be negative.
   //-----------------------------------------------------------------------------
   /**
   * @nodoc
   * Creates a procedural offseted surface.
   */
   virtual CATProcOffsetSurface * CreateProcOffsetSurface(const double         iOffset   ,
                                                                CATSurface  *  iReference,
                                                          const CATSurLimits & iLimits   )  =0 ;

#ifndef CATCGMRemoveNoDocDrop1
   /**
   * @nodoc
   * Use now a CATCloneManager to duplicate a CATProcOffsetSurface.
   */
   virtual CATProcOffsetSurface * CreateProcOffsetSurface(CATProcOffsetSurface *iOffsetToCopy) =0 ; 
#endif // CATCGMRemoveNoDocDrop1

   /**
   * @nodoc
   * Creates a geometric offseted surface.
   */
   virtual CATOffsetSurface * CreateOffsetSurface(const double       iOffset    ,
                                                        CATSurface * iReference )  =0 ;

#ifndef CATCGMRemoveNoDocDrop1
   /**
   * @nodoc
   * Use now a CATCloneManager to duplicate a CATOffsetSurface.
   */
   virtual CATOffsetSurface * CreateOffsetSurface
                                                 (      CATOffsetSurface * iOffsetToCopy) =0 ;
#endif // CATCGMRemoveNoDocDrop1


   /**
   * @nodoc
   * Do not use.
   * Creates an offset surface with the specified geometric rep. 
   * Use now a CATOffsetOperator to create an offset surface.
   */
   virtual CATOffsetSurface * CreateOffsetSurface (const double       iOffset      ,
                                                         CATSurface * iReference   ,
                                                         CATSurface * iGeometricRep) = 0 ;

   //-----------------------------------------------------------------------------
   // Do not use * Do not use * Do not use * Do not use * Do not use * Do not use * Do not use * 
   //- OffsetSurface creation with respect to canonical representation
   // of the original surface ( sample: offseting a Cylinder may create
   // another cylinder or a line if offset value is the cylinder radius.)
   //-----------------------------------------------------------------------------
#ifndef CATCGMRemoveNoDocDrop2
   /**
   * @nodoc
   * Do not use.
   * Creates a geometric offseted geometry respecting the canonical 
   * representation of the original surface.
   *</br> Offseting a CATCylinder may create another CATCylinder or a CATLine
   * if the offset value is <tt>-Cylinder.Radius</tt>.
   */
   virtual CATGeometry * CreateOffset ( const double       iOffset    ,
                                              CATSurface * iReference ) =0 ;
#endif // CATCGMRemoveNoDocDrop2
#ifndef CATCGMRemoveNoDocDrop2
   //-----------------------------------------------------------------------------
   //- CircularSweep creation 
   //-----------------------------------------------------------------------------
   /**
   * @nodoc
   * Creates a geometric circular sweep.
   * @param iPoints
   * The CATMathSetOfPointsND of dimension 9 containing:
   *<ul><li>the 3 coordinates of the centers of the arc circle.
   *    <li>the 3 coordinates of a first point of the arc circle.
   *    <li>the 3 coordinates of a second point of the arc circle.</ul>
   * @param iParameters
   * The pointer to a user parametrization. The array size is the number of 
   * points into <tt>iPoints</tt>. If <tt>NULL</tt> the method
   * proposes a parametrization.
   * @return
   * The pointer to the created CATCircularSweep. The smallest arc is choosen.
   * The orientation is given from the first point to the second one.
   */ 
   virtual CATCircularSweep * CreateCircularSweep( 
                                                  const CATMathSetOfPointsNDWithVectors * iPoints    ,
                                                  const double                          * iParameters) =0 ; 
#endif // CATCGMRemoveNoDocDrop2

#ifndef CATCGMRemoveNoDocDrop1
   /**
   * @nodoc
   * Use now a CATCloneManager to duplicate a CATCircularSweep.
   */
   virtual CATCircularSweep * CreateCircularSweep
      ( CATCircularSweep *iSweepToCopy) =0 ;  
#endif // CATCGMRemoveNoDocDrop1

   //-----------------------------------------------------------------------------
   //- GenericFillet creation 
   //-----------------------------------------------------------------------------
   /** @nodoc */
   virtual CATGenericFillet * CreateGenericFillet(const CATMathSetOfPointsND * iParams           ,
                                                  const CATMathSetOfPointsND * iPoints           ,
                                                  const CATMathSetOfPointsND * iTangents         ,
                                                  const CATMathSetOfPointsND * iSecondDerivatives,
                                                  const CATLONG32              iFirstTraceIndex  ,
                                                  const CATLONG32              iSecondTraceIndex ,
                                                  const CATLONG32              iCenterCurveIndex ,
                                                  const CATLONG32              iAngleIndex       ,
                                                  const CATMathBox2D         * iBox              = NULL) =0 ;

#ifndef CATCGMRemoveNoDocDrop1
   /** @nodoc */
   virtual CATGenericFillet * CreateGenericFillet( CATGenericFillet *ToCopy) =0 ;
#endif // CATCGMRemoveNoDocDrop1

   //-----------------------------------------------------------------------------
   //- SweepSurface creation 
   //-----------------------------------------------------------------------------
   /** @nodoc */
   virtual CATSweepSurface * CreateSweepSurface( CATNurbsSurface *iNurbsSurface) =0 ;
#ifndef CATCGMRemoveNoDocDrop1
   /** @nodoc */
   virtual CATSweepSurface * CreateSweepSurface( CATSweepSurface *ToCopy) =0 ;
#endif // CATCGMRemoveNoDocDrop1

   //-----------------------------------------------------------------------------
   //- SweepSegmentSurface creation 
   //-----------------------------------------------------------------------------
   /** @nodoc */
   virtual CATSweepSegmentSurface * CreateSweepSegmentSurface
      ( const CATSweepSegmentSurfaceCreationData* iSweepSegmentSurfaceCreationData) =0;  

   //-----------------------------------------------------------------------------
   //- FilletSurface creation 
   //-----------------------------------------------------------------------------
   /**
   * @nodoc
   * Creates a geometric fillet with constant radius.
   * @param iPoints
   * The CATMathSetOfPointsND of dimension 9 containing:
   *<ul><li>the 3 coordinates of the centers of the arc circle.
   *    <li>the 3 coordinates of a first point of the arc circle.
   *    <li>the 3 coordinates of a second point of the arc circle.</ul>
   * @param iRadius
   * The radius if its is constant. Later, the radius law.
   * @param iCentripetalOrientation
   *<dl> <dt><tt> 1 </tt> if the normal points to the circle center 
   *(centripetal orientation).
   *      <dt><tt> -1</tt> if not (centrifugal orientation)</dl>
   * @param iParameters
   * The pointer to a user parametrization. The array size is the number of 
   * points into <tt>iPoints</tt>. If <tt>NULL</tt> the method
   * proposes a parametrization.
   */
   virtual CATFilletSurface * CreateFilletSurface(
                                                  const CATMathSetOfPointsND * iParams,
                                                  const CATMathSetOfPointsND * iPoints,
                                                  const CATMathSetOfPointsND * iTangents,
                                                  const CATMathSetOfPointsND * iSecondDerivatives,
                                                  const CATLONG32              iFirstTraceIndex,
                                                  const CATLONG32              iSecondTraceIndex,
                                                  const CATLONG32              iCenterCurveIndex,
                                                  const CATLONG32              iAngleIndex,
                                                  const short                  iConfiguration,
                                                        double                 iRadius,
                                                        CATGeometry          * iSupport1,
                                                        CATGeometry          * iSupport2,
                                                        int                    iOrientation1,
                                                        int                    iOrientation2,
                                                        CATGeometry          * iContact1,
                                                        CATGeometry          * iContact2,
                                                        CATLONG32            & oCentripetalOrientation) =0 ;
   /** @nodoc */
   virtual CATFilletSurface * CreateFilletSurface(
                                                  const CATMathSetOfPointsND * iParams,
                                                  const CATMathSetOfPointsND * iPoints,
                                                  const CATMathSetOfPointsND * iTangents,
                                                  const CATMathSetOfPointsND * iSecondDerivatives,
                                                  const CATLONG32              iFirstTraceIndex,
                                                  const CATLONG32              iSecondTraceIndex,
                                                  const CATLONG32              iCenterCurveIndex,
                                                  const CATLONG32              iAngleIndex,
                                                  const short                  iConfiguration,
                                                        CATCurve             * iSpine,
                                                        CATLaw               * iRadiusLaw,
                                                        CATLaw               * iMappingLaw,
                                                        CATGeometry          * iSupport1,
                                                        CATGeometry          * iSupport2,
                                                        int                    iOrientation1,
                                                        int                    iOrientation2,
                                                        CATGeometry          * iContact1,
                                                        CATGeometry          * iContact2,
                                                        CATLONG32            & oCentripetalOrientation,
                                                  const CATLONG32              iContinuityMode =0) =0;

   /** @nodoc */
   virtual CATFilletSurface * CreateTriTangentFilletSurface(
                                                            const CATMathSetOfPointsND * iParams,
                                                            const CATMathSetOfPointsND * iPoints,
                                                            const CATMathSetOfPointsND * iTangents,
                                                            const CATMathSetOfPointsND * iSecondDerivatives,
                                                            const CATLONG32              iFirstTraceIndex,
                                                            const CATLONG32              iSecondTraceIndex,
                                                            const CATLONG32              iCenterCurveIndex,
                                                            const CATLONG32              iAngleIndex,
                                                            const short                  iConfiguration,
                                                                  CATGeometry          * iSupport1,
                                                                  CATGeometry          * iSupport2,
                                                                  CATGeometry          * iSupport3,
                                                                  int                    iOrientation1,
                                                                  int                    iOrientation2,
                                                                  int                    iOrientation3,
                                                                  CATGeometry          * iContact1,
                                                                  CATGeometry          * iContact2,
                                                                  CATGeometry          * iContact3,
                                                                  CATLONG32            & oCentripetalOrientation) =0;
   /** @nodoc */
   virtual CATFilletSurface * CreateBiTangentCircleFilletSurface(
                                                            const CATMathSetOfPointsND * iParams,
                                                            const CATMathSetOfPointsND * iPoints,
                                                            const CATMathSetOfPointsND * iTangents,
                                                            const CATMathSetOfPointsND * iSecondDerivatives,
                                                            const CATLONG32              iFirstTraceIndex,
                                                            const CATLONG32              iSecondTraceIndex,
                                                            const CATLONG32              iCenterCurveIndex,
                                                            const CATLONG32              iAngleIndex,
                                                            const short                  iConfiguration,
                                                                  CATCurve             * iCircleSpine,
                                                                  CATCurve             * iRadiusSpine,
                                                                  CATLaw               * iRadiusLaw,
                                                                  CATLaw               * iMappingLaw,
                                                                  CATGeometry          * iSupport1,
                                                                  CATGeometry          * iSupport2,
                                                                  int                    iOrientation1,
                                                                  int                    iOrientation2,
                                                                  CATGeometry          * iContact1,
                                                                  CATGeometry          * iContact2,
                                                                  CATLONG32            & oCentripetalOrientation) =0; 

   /** @nodoc */
   virtual   CATFilletSurface * CreateSweepCircleSurface(const CATMathSetOfPointsND * iParams,
                                                         const CATMathSetOfPointsND * iPoints,
                                                         const CATMathSetOfPointsND * iTangents,
                                                         const CATMathSetOfPointsND * iSecondDerivatives,
                                                         const CATLONG32              iFirstTraceIndex,
                                                         const CATLONG32              iSecondTraceIndex,
                                                         const CATLONG32              iCenterCurveIndex,
                                                         const CATLONG32              iAngleIndex,
                                                         const short                  iConfiguration,
                                                               double                 iRadius,
                                                               CATCurve             * iCircleSpine,
                                                               CATGeometry          * iSupport1,
                                                               CATGeometry          * iSupport2,
                                                               int                    iOrientation1,
                                                               int                    iOrientation2,
                                                               CATGeometry          * iContact1,
                                                               CATGeometry          * iContact2,
                                                               CATLONG32            & oCentripetalOrientation) = 0;
   /**
   * @nodoc
   * Use now a CATCloneManager to duplicate a CATFilletSurface.
   */
   virtual CATFilletSurface * CreateFilletSurface(             CATFilletSurface     * iFilletToCopy) =0 ;

   //-----------------------------------------------------------------------------
   //- DraftSurface creation.
   //-----------------------------------------------------------------------------
   /**
   * @nodoc
   * Creates a trimmed geometric draft surface.
   * @param iLimits
   * The limitations of the generating curve <tt>iProfile</tt> if necessary.
   * @param iParams
   * The list of imposed passage parameters.
   */
   virtual CATDraftSurface * CreateDraftSurface(
                                                const CATCurve              *  iProfile,
                                                const CATMathDirection       & iDirection,
                                                const CATAngle               & iAngle,
                                                const double                 & iStartLength,
                                                const double                 & iEndLength,
                                                      CATMathSetOfPointsND   & ioMapping,
                                                const CATCrvLimits          *  iLimits=0,
                                                const CATLISTP(CATCrvParam) *  iParams=0) =0;


   /**
   * @nodoc
   * DraftSurface creation.
   */
   virtual CATDraftSurface * CreateDraftSurface(CATDraftSurfaceCreationData * ioData) =0;


   /**
   * @nodoc
   * Use now a CATCloneManager to duplicate a CATDraftSurface.
   */
   virtual CATDraftSurface * CreateDraftSurface(CATDraftSurface             * iDraftToCopy) =0;


   //-----------------------------------------------------------------------------
   // DirectionalSurface
   //-----------------------------------------------------------------------------
   /** @nodoc */
   virtual CATDirectionalSurface * CreateDirectionalSurface(
                                                            CATPCurve           *  iGuideCurve,
                                                            CATCrvLimits        *  iLimits,
                                                            CATAngle               iAngleWithNormal,
                                                            double                 iLengthRuled,
                                                            CATMathSetOfPointsND & ioMapping) =0;

   //-----------------------------------------------------------------------------
   //- ChamferSurface creation 
   //-----------------------------------------------------------------------------
   /** @nodoc */

   virtual CATChamferSurface * CreateChamferSurface(const CATMathSetOfPointsND * iParams,
                                                    const CATMathSetOfPointsND * iPoints,
                                                    const CATMathSetOfPointsND * iTangents,
                                                    const CATMathSetOfPointsND * iSecondDerivatives,
                                                    const CATLONG32              iFirstTraceIndex,
                                                    const CATLONG32              iSecondTraceIndex,
                                                    const short                  iConfiguration,
                                                //        CATCurve             * iSpine,
                                                    const CATLONG32              iChamferType,
                                                    const double                 iFirstValue,
                                                    const double                 iSecondValue,
                                                          CATSurface           * iSurface1,
                                                          CATSurface           * iSurface2,
                                                          int                    iOrientation1,
                                                          int                    iOrientation2,
                                                          CATGeometry          * iContact1,
                                                          CATGeometry          * iContact2) =0;  

#ifndef CATCGMRemoveNoDocDrop1
   /**
   * @nodoc
   * Use now a CATCloneManager to duplicate a CATChamferSurface.
   */
   virtual CATChamferSurface * CreateChamferSurface
      ( CATChamferSurface *iChamferToCopy) =0;
#endif // CATCGMRemoveNoDocDrop1

   //-----------------------------------------------------------------------------
   //- LinearTransfoSurface creation 
   //-----------------------------------------------------------------------------
   /**
   * @nodoc
   * Creates a LinearTransfo surface by applying a given transformation to the
   * reference surface.
   */

   virtual CATLinearTransfoSurface * CreateLinearTransfoSurface(CATMathTransformation & iTransformation,
                                                                CATSurface            * iReference     ) = 0;

#ifndef CATCGMRemoveNoDocDrop1
   /**
   * @nodoc
   * Use now a CATCloneManager to duplicate a CATLinearTransfoSurface.
   */
   virtual CATLinearTransfoSurface * CreateLinearTransfoSurface(CATLinearTransfoSurface * iSurfaceToCopy) = 0;
#endif // CATCGMRemoveNoDocDrop1

   //-----------------------------------------------------------------------------
   //- NonLinearTransfoSurface creation 
   //-----------------------------------------------------------------------------
   /**
   * @nodoc
   * Creates a NonLinearTransfo surface by applying a given transformation to the
   * reference surface.
   */

   virtual CATNonLinearTransfoSurface * CreateNonLinearTransfoSurface
                                                                     (CATMathNonLinearTransformation & iTransformation,
                                                                      CATSurface                     * iReference ) = 0;
   /**
   * @nodoc
   * Creates a NonLinearTransfo surface by applying a given transformation to the
   * reference surface inside given limits .
   */

   virtual CATNonLinearTransfoSurface * CreateNonLinearTransfoSurface
                                                                     (CATMathNonLinearTransformation & iTransformation,
                                                                      CATSurface                     * iReference ,
                                                                      CATSurLimits                   & iSurMaxLimits) = 0;
#ifndef CATCGMRemoveNoDocDrop1
   /**
   * @nodoc
   * Use now a CATCloneManager to duplicate a CATNonLinearTransfoSurface.
   */
   virtual CATNonLinearTransfoSurface * CreateNonLinearTransfoSurface
                                                                     (CATNonLinearTransfoSurface     * iSurfaceToCopy ) = 0;
#endif // CATCGMRemoveNoDocDrop1

   //-------------------------------------------------------------------------
   //- SpecSurface creation.
   //-------------------------------------------------------------------------
   /** @nodoc */
   virtual CATSpecSurface * CreateSpecSurface (CATSpecSurfaceDef* iSpecSurfaceDef) = 0;

   //-------------------------------------------------------------------------
   //- ProcSurface creation.
   //-------------------------------------------------------------------------
   /** @nodoc */
   virtual CATProcSurface * CreateProcSurface (CATProcSurfaceDef* iProcSurfaceDef) = 0;

   //-------------------------------------------------------------------------
   //- Non Linear Transformed PCurves
   //-------------------------------------------------------------------------
   /**
   *@nodoc
   * Creates a non linear transformed PCurve on iSupport. The returned PCurve becomes 
   * owner of the pointer ioTransfo. It verify
   *   PCrv(w) = (iuShift,ivShift) + ioTransfo*iFromPCrv(w)
   */
   virtual CATNonLinearTransfoPCurve * CreateNonLinearTransfoPCurve
                                                                   (      CATPCurve                        * iFromPCrv,
                                                                    const double                             iuShift  ,
                                                                    const double                             ivShift  ,
                                                                          CATMathNonLinearTransformation2D * ioTransfo,
                                                                          CATSurface                       * iSupport ) = 0;

   //-------------------------------------------------------------------------
   // SType Law creation
   //-------------------------------------------------------------------------
   /** @nodoc */
   virtual CATSTypeLaw * CreateSTypeLaw (const double    iTMin                ,
                                         const double    iValueAtTMin         ,
                                         const CATLONG32 iNullDerivOrderAtTMin,
                                         const double    iTMax                ,
                                         const double    iValueAtTMax         ,
                                         const CATLONG32 iNullDerivOrderAtTMax) =0;
#ifndef CATCGMRemoveNoDocDrop1
   /** @nodoc */
   virtual CATSTypeLaw     * CreateSTypeLaw     (CATSTypeLaw     * iToCopy) = 0;
#endif // CATCGMRemoveNoDocDrop1

#ifndef CATCGMRemoveNoDocDrop1
   /** @nodoc */
   virtual CATCompositeLaw * CreateCompositeLaw (CATCompositeLaw * iToCopy) = 0;
#endif // CATCGMRemoveNoDocDrop1

   /** @nodoc */
   virtual CATCompositeLaw * CreateC2ExtrapolationCompositeLaw (const CATLaw  * iToExtrapolate ,
                                                                const double    iMinLimitValue ,
                                                                const double    iMaxLimitValue ,
                                                                const CATLONG32 iSide=0) = 0;

   //-------------------------------------------------------------------------
   // Cloud creation
   // iNormals may be a NULL pointer.
   // If iPointsActivity is NULL, then all points are considered to be active.
   // CharacteristicDistance is the max of the min distance for all points, so
   // it should be strictly greater than 0. Default value will force the computation.
   //-------------------------------------------------------------------------
   /** @nodoc */
   virtual CATCloud  * CreateCloud (      CATLONG32     iNbPoints              ,
                                    const float       * iPoints                ,
                                    const float       * iNormals               ,
                                    const CATULONG32  * iPointsActivity        ,
                                          double        CharacteristicDistance = 0) = 0;

   //-------------------------------------------------------------------------
   // Scan creation
   // iNormals may be a NULL pointer.
   // If iPointsActivity is NULL, then all points are considered to be active.
   // CharacteristicDistance is the max of the min distance for all points, so
   // it should be strictly greater than 0. Default value will force the computation.
   //-------------------------------------------------------------------------
   /** @nodoc */
   virtual CATScan  * CreateScan (      CATLONG32     iNbPoints              ,
                                  const float       * iPoints                ,
                                  const float       * iNormals               ,
                                  const CATULONG32  * iPointsActivity        ,
                                        CATLONG32     NumberOfScan           ,
                                        CATLONG32   * NumberOfPointsPerScan  ,
                                        double        CharacteristicDistance = 0) = 0;

   //-------------------------------------------------------------------------
   // TessCloud creation
   // If iPrimitivesActivity is ULL, then all primitives are considered to be active.
   // iPrimitives is an array of indexes on the three vertices of the triangle.
   // iNeighbours is an array of indexes on the three neighbours triangles. If there is 
   // neighbour on a side of the triangle, index=-2.
   //-------------------------------------------------------------------------
   /** @nodoc */
   virtual CATTessCloud  * CreateTessCloud (      CATCloud    * iCloud       ,
                                                  CATLONG32     iNbPrimitives,
                                            const CATLONG32   * iPrimitives  ,
                                            const CATLONG32   * iNeighbours  ,
                                            const CATULONG32  * iPrimitivesActivity) = 0;

   //-------------------------------------------------------------------------
   // TessScan creation
   // If iPrimitivesActivity is ULL, then all primitives are considered to be active.
   // iPrimitives is an array of indexes on the three vertices of the triangle.
   // iNeighbours is an array of indexes on the three neighbours triangles. If there is 
   // neighbour on a side of the triangle, index=-2.
   //-------------------------------------------------------------------------
   /** @nodoc */
   virtual CATTessScan  * CreateTessScan (      CATScan     * iScan,
                                                CATLONG32     iNbPrimitives,
                                          const CATLONG32   * iPrimitives,
                                          const CATLONG32   * iNeighbours,
                                          const CATULONG32  * iPrimitivesActivity) = 0;

   //-------------------------------------------------------------------------
   //Subdivision Mesh creation
   //-------------------------------------------------------------------------
   /** @nodoc */
   virtual CATSubdivMesh* CreateSubdivMesh() = 0;

   /** @nodoc */
   virtual CATSubdivMesh* CreateSubdivMesh(CATSobMesh* iMesh) = 0;


   //-------------------------------------------------------------------------
   // UserGeometry creation
   //-------------------------------------------------------------------------
   /** @nodoc */
   virtual CATUserGeometry * CreateUserGeometry(CATGeometry *iGeometry) = 0;



   /**
   * @nodoc
   * Use now a CATCloneManager to duplicate a CATGeometry.
   */
   virtual CATGeometry* Clone ( const CATGeometry* iObjectToDuplicate ) = 0 ;
#ifndef CATCGMRemoveNoDocDrop2
   /**
   * @nodoc
   */
   virtual CATOrientable * CreateOrientable(      CATGeometry * iGeometry  ,
                                            const CATLONG32     iOrientable) = 0;
#endif //CATCGMRemoveNoDocDrop2

#ifndef CATCGMRemoveNoDocDrop1
   /**
   * @nodoc
   */
   virtual CATOrientable * CreateOrientable (CATOrientable *ToCopy) = 0;
#endif // CATCGMRemoveNoDocDrop1

   /**
   * @nodoc.
   */
   virtual double GetIdenticalPointTolerance() const = 0;

};


 
/**
 * @nodoc
 *  Body creation helper.
 * @param iFactory
 *  factory of geometric elements.
 */

#if defined ( CATIACGMR214CAA )
#define CATGeoCreateBody(iFactory)                  iFactory ? iFactory->CreateBody(CatBodyMode_Working, ""   , __FILE__, __LINE__ ) : NULL
#define CATGeoCreateBodyDelayed(iFactory)           iFactory ? iFactory->CreateBody(CatBodyMode_Delayed, ""   , __FILE__, __LINE__ ) : NULL
#define CATGeoCreateBodyName(iFactory,iRole)        iFactory ? iFactory->CreateBody(CatBodyMode_Working, iRole, __FILE__, __LINE__ ) : NULL
#define CATGeoCreateBodyNameDelayed(iFactory,iRole) iFactory ? iFactory->CreateBody(CatBodyMode_Delayed, iRole, __FILE__, __LINE__ ) : NULL
#else
#define CATGeoCreateBody(iFactory)                  iFactory ? iFactory->CreateBody() : NULL
#define CATGeoCreateBodyDelayed(iFactory)           iFactory ? iFactory->CreateBody() : NULL
#define CATGeoCreateBodyName(iFactory,iRole)        iFactory ? iFactory->CreateBody() : NULL
#define CATGeoCreateBodyNameDelayed(iFactory,iRole) iFactory ? iFactory->CreateBody() : NULL
#endif



CATDeclareHandler(CATGeoFactory,CATICGMContainer);

#endif

