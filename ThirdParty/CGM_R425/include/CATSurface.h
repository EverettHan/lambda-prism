#ifndef CATSurface_h
#define CATSurface_h
// COPYRIGHT DASSAULT SYSTEMES  1999
/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 
#include "CATGeometry.h"
#include "CATEvalCommand.h"
#include "CATIsoParameter.h"

class CATMathGridOfPoints;
class CATMathGridOfVectors;
class CATMathFunctionRN;
class CATMathFunctionXY;
class CATMathBox;
class CATMathDirBox;
class CATMathPoint;
class CATMathVector;
class CATMathDirection;
class CATMathCurve;
class CATMathSetOfLongs;
class CATMathTransformation1D;
class CATMathTransformation2D;
class CATKnotVector;
class CATSurParam;
class CATSurLimits;
class CATSurEvalCommand;
class CATSurEvalResult;
class CATSurEvalLocal;
class CATSurParamReference;
class CATGeoFactory;
class CATCurve;

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATSurface ;
#else
extern "C" const IID IID_CATSurface ;
#endif

#ifdef CATCGMIncludeForCompatibility
#include "CATBaseUnknown.h"
#include "CATSurParam.h"
#include "CATSurLimits.h"
#include "CATMathGridOfPoints.h"
#include "CATMathGridOfVectors.h"
#include "CATMathFunctionXY.h"
#include "CATMathSetOfLongs.h"
#include "CATCurve.h"
#endif

class CATMathAdvancedBox;

/**
 * Interface representing the base class of all bi-parameterized
 * geometric elements. 
 * <br> A surface can be 
 * represented by three CATMathFunctionXY (<tt>(FX(x,y), FY(x,y), FZ(x,y))</tt>), 
 * that can be retrieved through the
 * <tt>GetGlobalEquation</tt> method. <tt>(x,y)</tt> are the parameters of a point on
 * the surface. These parameters can also be denoted through <tt>(u,v)</tt>,
 * and they are handled 
 * with the <tt>CATSurParam</tt> class.
 * <br>Surfaces can have several patches in each direction,
 * that are located with a patch number in the first direction <tt>iPatchU</tt> and
 * a patch number in the second direction <tt>iPatchV</tt>. Hence, you can use
 * a local parameter on a given patch, or a global parameter, that takes in account the
 * whole surface. Notice that the patch numbers are not necessarily
 * positive, but their values are consecutive.
 * <br><tt>CATSurLimits</tt> is a class allowing
 * the surface to be restricted to a part of it. 
 * The limits 
 * define the area where the surface may currently be evaluated. It should not
 * be evaluated outside this area of parameters.
 * <br>Each type of surface is responsible for the mapping (called Evaluation) between the (u,v) parameters
 * and their corresponding coordinates in the 3D space . No assumption can be made about
 * this mapping by a developper who uses these objects, except that it is C2 continuous
 * (at least twice differentiable).
 * <br>Multiple evaluations can be performed in one way by defining
 * a <tt>CATSurCommand</tt> object, evaluating through the <tt>Eval</tt>
 * method and retrieving the results with a <tt>CATSurEvalResult</tt> object.
 * @see CATSurParam, CATSurLimits, CATSurEvalCommand, CATSurEvalResult, CATSurEvalLocal
 */
class ExportedByCATGMGeometricInterfaces CATSurface : public CATGeometry
{
  CATDeclareInterface;

public:
  
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/**
 * Returns the smallest box surrounding a portion of <tt>this</tt> CATSurface, with regards to
 * the provided CATSurlimits.
 * @param iLimits
 * The limits on the surface
 * @param ioBox
 * The box surrounding the surface limited by <tt>iLimits</tt>.
 */
  virtual void GetBox( const CATSurLimits & iLimits,
                             CATMathBox   & ioBox  ) const = 0;

/**
 * Returns the mathematical point associated with a CATSurParam.
 * @param iPosition
 * The point of the surface.
 * @param ioPoint
 * The corresponding mathematical point.
 */
  virtual void EvalPoint(const CATSurParam & iPosition,
                               CATMathPoint & ioPoint )const = 0 ;

/**
 * Retrieves the first derivatives on a point of <tt>this</tt> surface. 
 * @param iParam
 * The point of the surface.
 * @param ioDU
 * The first derivative with respect to to the U parameter.
 * @param ioDV
 * The first derivative with respect to to the V parameter.
 */
  virtual void EvalFirstDeriv(const CATSurParam   & iParam,
                                    CATMathVector & ioDU  ,
                                    CATMathVector & ioDV  ) const = 0;

/**
 * Retrieves the second derivatives on a point of <tt>this</tt> surface. 
 * @param iParam
 * The point of the surface.
 * @param ioDU2
 * The second derivative with respect to to the U parameter.
 * @param ioDUDV
 * The second derivative with respect to to the UV parameters.
 * @param ioDV2
 * The second derivative with respect to to the V parameter.
 */
  virtual void EvalSecondDeriv(const CATSurParam   & iParam,
                                     CATMathVector & ioDU2 ,
                                     CATMathVector & ioDUDV,
                                     CATMathVector & ioDV2 ) const = 0;

/**
 * Retrieves the third derivatives on a point  of <tt>this</tt> surface. 
 * @param iParam
 * The point of the surface.
 * @param ioDU3
 * The third derivative with respect to to the U parameter.
 * @param ioDU2DV
 * The third derivative with respect to to the UUV parameters.
 * @param ioDUDV2
 * The third derivative with respect to to the UVV parameters.
 * @param ioDV3
 * The third derivative with respect to to the V parameter.
 */
  virtual void EvalThirdDeriv(const CATSurParam   & iParam ,
                                    CATMathVector & ioDU3  ,
                                    CATMathVector & ioDU2DV,
                                    CATMathVector & ioDUDV2,
                                    CATMathVector & ioDV3  ) const = 0;

/**
 * Retrieves the normal at a point  of <tt>this</tt> surface. 
 * @param iParam
 * The point of the surface.
 * @param ioNormal
 * The outer normal oriented along <tt> ds/du ^ ds/dv</tt>.
 */
  virtual void EvalNormal(const CATSurParam      & iParam ,
                                CATMathDirection & ioNormal) const = 0;


/**
 * Retrieves multiple evaluations on a grid of points of <tt>this</tt> CATSurface.
 * <br>The method reallocates the memory if necessary.If the number of points 
 * in U or V is 1, then the evaluation
 * is done on the low part of the CATSurLimits for this(these) coordinate(s).
 * @param iBox
 * The limits of the surface to take into account.
 * @param iNbOfPointsInU
 * The number of points to distribute inside the limits on the surface 
 * first direction.
 * @param iNbOfPointsInV
 * The number of points to distribute inside the limits on the surface 
 * second direction.
 * @param iCommand
 * The command precising the requested evaluation types.
 * @param ioResult
 * The evaluation at the given points such that the <tt>(UIndex, VIndex)</tt> point
 * evaluation is located at the <tt>3*(UIndex + iNbOfPointsInU*VIndex)</tt> place.
 */
  virtual void EvalMultiple(const CATSurLimits      & iBox          ,
                                  CATLONG32           iNbOfPointsInU,
                                  CATLONG32           iNbOfPointsInV,
                            const CATSurEvalCommand & iCommand      ,
                                  CATSurEvalResult  & ioResult      ) const = 0;
  
/**
 * Retrieves multiple evalutions at a given point of <tt>this</tt> CATSurface.
 * @param iParam
 * The point of the surface.
 * @param iCommand
 * The command precising the requested evaluation types.
 * @param ioResult
 * The resulting evaluations.
 */
  virtual void EvalLocal(const CATSurParam       & iPoint  ,
                         const CATSurEvalCommand & iCommand,
                               CATSurEvalLocal   & ioResult) const = 0;

/**
 * Creates an isoparametric curve on <tt>this</tt> CATSurface.
 * <br>The curve has the same global parameterization as the surface in this
 * direction.
 * @param iIsoParameter
 * The type of iso parametric curve.
 * @param iParam
 * The point of the surface belonging to the curve to create.
 * @param iWhere
 * A pointer to the factory for creation.
 * @return
 * A pointer to the created curve.
 */
  virtual CATCurve *ExtractIsoParametricCurve(const CATIsoParameter  iIsoParameter,
                                              const CATSurParam    & iParam       ,
                                                    CATGeoFactory  * iWhere       ) const = 0;

/**
 * Tests whether <tt>this</tt> CATSurface is periodic along the first direction.
 * <br>This method does not take into account the current limitations of 
 * the surface.
 * @return
 * The result of the test.
 * <br><b>Legal values:</b>:
 * <dl> <dt><tt>0</tt> <dd>If the CATSurface is not periodic on the first direction.
 *     <dt><tt>1</tt> <dd>If the CATsurface is periodic on the first direction.  </dl>
 */
  virtual CATBoolean IsClosedU() const = 0;

/**
 * Tests whether <tt>this</tt> CATSurface is periodic along the second direction.
 * <br>This method does not take into account the current limitations of 
 * the surface.
 * @return
 * The result of the test.
 * <br><b>Legal values:</b>:
 * <dl>
 *  <dt><tt>0</tt> <dd>If the CATSurface is not periodic on the second direction.
 *  <dt><tt>1</tt> <dd>If the CATsurface is periodic on the second direction. 
 * </dl>
 */
  virtual CATBoolean IsClosedV() const = 0;
  
/**
 * Tests whether <tt>this</tt> CATSurface is invariant.
 * <br>This method does not take into account the current limits of the surface.
 * @param iTransfo
 * The tested transformation.
 * @param ioTransfo2D
 * The 2D-transformation defining the change of parameterization between <tt>this</tt> and the transformation of
 * <tt>this</tt>. If <tt>NULL</tt>, this is not output.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 * <dl>
 * <dt><tt>1</tt> <dd>If the transformation of <tt>this</tt> is geometrically the same as <tt>this</tt>.
 * <dt><tt>0</tt> <dd>Otherwise.
 * </dl>
 */
  virtual CATBoolean IsInvariant(const CATMathTransformation   & iTransfo    ,
                                       CATMathTransformation2D * ioTransfo2D = NULL) const = 0;

/**
 * Tests whether <tt>this</tt> CATSurface is confused with another surface.
 * <br>This method does not take into account the current limits of 
 * the surfaces.
 * @param iTransfo
 * The tested transformation.
 * @param iTSurface
 * The other surface.
 * @param ioTransfo2D
 * The 2D-transformation defining the change of parametrization between the transformation of 
 * <tt>this</tt> and <tt>iTSurface</tt>. If <tt>NULL</tt>, this is not output.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 * <dl>
 * <dt><tt>1</tt> <dd>If the transformation of <tt>this</tt> is geometrically the same as <tt>iTSurface</tt>.
 *     <dt><tt>0</tt> <dd>Otherwise.
 * </dl>
 */
  virtual CATBoolean IsConfused(const CATMathTransformation   & iTransfo    ,
                                const CATSurface              * iTSurface   ,
                                      CATMathTransformation2D * ioTransfo2D = NULL) const = 0;

/**
 * Returns the knot vector of <tt>this</tt> CATSurface first direction.
 * @return
 * The pointer to the knot vector. All surfaces return a 
 * knot vector but this knot vector can be NULL, for example when the surface is a canonical surface.
 * For half-canonical surfaces such as tabulated surfaces with a non-canonical profile,
 * the knot vector along U is not NULL.
 */
  virtual const CATKnotVector * GetKnotVectorU() const = 0;

/**
 * Returns the knot vector of <tt>this</tt> CATSurface second direction.
 * @return
 * The pointer to the knot vector.
 * Note that all surfaces return a knot vector, not only NURBS. 
 * The knot vector along V can be NULL.
 */
  virtual const CATKnotVector * GetKnotVectorV() const = 0;

/**
 * Creates a CATSurParam on <tt>this</tt> surface from global parameters.
 * @param iParamU
 * The parameter value in the first direction.
 * @param iParamV
 * The parameter value in the second direction.
 * @param ioResult
 * The resulting parameter.
 */
  virtual void CreateParam(const double      & iParamU,
                           const double      & iParamV,
                                 CATSurParam & ioResult) const = 0;
/**
 * Creates a CATSurParam on <tt>this</tt> surface from local parameters.
 * @param iParamU
 * The local parameter value in the first direction on <tt>iPatchU</tt>.
 * @param iPatchU
 * The patch number in the first direction.
 * @param iParamV
 * The local parameter value in the second direction on <tt>iPatchV</tt>.
 * @param iPatchV
 * The patch number in the second direction.
 * @param ioResult
 * The resulting parameter. 
 */
  virtual void CreateParam(const double      & iParamU,
                           const CATLONG32   & iPatchU,
                           const double      & iParamV,
                           const CATLONG32   & iPatchV,
                                 CATSurParam & ioResult) const = 0;
  
/**
 * Returns the current low limit of <tt>this</tt> CATSurface.
 * @param ioParam
 * The parameter defining the first limit of <tt>this</tt> CATSurface. 
 */
  virtual void GetStartLimit(CATSurParam & ioParam) const = 0 ;
  

/**
 * Returns the current high limit of <tt>this</tt> CATSurface.
 * @param ioParam
 * The parameter defining the last limit of <tt>this</tt> CATSurface.
 */
  virtual void GetEndLimit(CATSurParam & ioParam) const = 0 ;
  

/**
 * Returns the current limits of <tt>this</tt> CATSurface.
 * @param ioLimits
 * The limitations of <tt>this</tt> CATSurface.
 */
  virtual void GetLimits(CATSurLimits & ioLimits) const = 0 ;

/**
 * Returns the maximum limits of <tt>this</tt> CATSurface.
 * <br>This does not take into account the current limits .
 * @param ioLimits
 * The maximum limits of <tt>this</tt> CATSurface.
 */
  virtual void GetMaxLimits(CATSurLimits & ioLimits) const = 0 ;



/**
 * Returns the limits of an internal patch of <tt>this</tt> CATSurface.
 * @param iPatchU
 * The patch number in the first direction.
 * @param iPatchV
 * The patch number in the second direction.
 * @param ioLimits
 * The limitations of a patch.
 */
  virtual void GetInternalLimits(const CATLONG32      iPatchU, 
                                 const CATLONG32      iPatchV,
                                       CATSurLimits & ioLimits) const = 0;


/**
 * Returns the maximum limits of an internal patch of <tt>this</tt> CATSurface.
 * <br>This does not take into account the current limits .
 * @param iPatchU
 * The patch number in the first direction.
 * @param iPatchV
 * The patch number in the second direction.
 * @param ioLimits
 * The limits of a patch.
 */
  virtual void GetInternalMaxLimits(const CATLONG32      iPatchU,
                                    const CATLONG32      iPatchV,
                                          CATSurLimits & oLimits) const = 0 ;

/**
 * Modifies the current limits of <tt>this</tt> CATSurface.
 * @param iNewLimits
 * The new current limits.
 */
  virtual void SetLimits(const CATSurLimits & iNewLimits) = 0 ;
  //-------------------------------------------------------------------------
  //- Equations management methods
  //-------------------------------------------------------------------------
/**
 * Locks any modification of the equations of<tt>this</tt> CATSurface .
 */
  virtual void Lock() = 0 ;
/**
 * Unlocks the modifications of the equations of <tt>this</tt> CATSurface.
 */
  virtual void Unlock() = 0 ;

  /**
 * Retrieves the mathematical equation associated with a patch of
 * <tt>this</tt> CATSurface.
 * <br><tt>(ioFx(U,V), ioFy(U,V), ioFz(U,V))</tt> is then a point of the surface patch.
 * <br>Before retrieving the equations, you must <tt>Lock</tt> the surface.
 * You can then obtained the equations. When you have finished, you <tt>Unlock</tt> the surface.
 * The equations are then automatically deleted. 
 * @param iPatchU
 * The patch number in the first direction.
 * @param iPatchU
 * The patch number in the second direction.
 * @param oFx
 * A pointer to the parametric equation of the first coordinate. 
 * @param oFy
 * A pointer to the parametric equation of the second coordinate. 
 * @param oFz
 * A pointer to the parametric equation of the third coordinate. 
 */
  virtual void GetEquation(const CATLONG32             iPatchU,
                           const CATLONG32             iPatchV,
                           const CATMathFunctionXY * & oFx    ,
                           const CATMathFunctionXY * & oFy    ,
                           const CATMathFunctionXY * & oFz    ) const = 0;

 /**
 * Retrieves the mathematical equation associated with
 * <tt>this</tt> CATSurface.
 * <br><tt>(ioFx(U,V), ioFy(U,V), ioFz(U,V))</tt> is then a point of the surface.
 * <br>Before retrieving the equations, you must <tt>Lock</tt> the surface.
 * You can then obtained the equations. When you have finished, you <tt>Unlock</tt> the surface.
 * The equations are then automatically deleted. 
 * @param oFx
 * A pointer to the parametric equation of the first coordinate. 
 * @param oFy
 * A pointer to the parametric equation of the second coordinate. 
 * @param oFz
 * A pointer to the parametric equation of the third coordinate. 
 */
  virtual void GetGlobalEquation(const CATMathFunctionXY * & oFx,
                                 const CATMathFunctionXY * & oFy,
                                 const CATMathFunctionXY * & oFz) const = 0;

/**
 * Returns a pointer to the mathematical representation of an isoparametric
 * curve of <tt>this</tt> CATSurface.
 * @param iIsoParameter
 * The type of iso-parametric curve.
 * @param iLocation
 * A point belonging to the curve.
 * @return
 * The corresponding mathematical curve, that
 * has to be managed (deleted) by the caller.
 */
  virtual CATMathCurve* GetMathCurve(const CATIsoParameter   iIsoParameter,
                                     const CATSurParam     & iLocation ) const = 0 ;

/**
 * Tests whether an isoparametric curve of <tt>this</tt> CATSurface has a mathematical representation.
 * @param iIsoParameter
 * The type of iso-parametric curve.
 * @param iLocation
 * A point belonging to the curve.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 *<dl> <dt><tt>1</tt> <dd>If an isoparametric curve of <tt>this</tt> has a mathematical representation.
 *     <dt><tt>0</tt> <dd>Otherwise.</dl>
 */ 
  virtual CATBoolean HasMathCurve(const CATIsoParameter   iIsoParameter,
                                  const CATSurParam     & iLocation ) const = 0 ;

/**
 * Retrieves the bounding box including a patch of <tt>this</tt> CATSurface.
 * @param iPatchU
 * The patch number in the first direction.
 * @param iPatchV
 * The patch number in the second direction.
 * @param ioBox
 * The corresponding bounding box.
 */
  virtual void GetInternalBoundingBox(const CATLONG32    iPatchU,
                                      const CATLONG32    iPatchV,
                                            CATMathBox & ioBox  ) const = 0;
 
/**
 * Retrieves the maximum bounding box including a patch of <tt>this</tt> CATSurface.
 *<br>This does not take into account the current limitations of the
 * surface.
 * @param iPatchU
 * The patch number in the first direction.
 * @param iPatchV
 * The patch number in the second direction.
 * @param ioBox
 * The corresponding bounding box.
 */
  virtual void GetInternalMaxBoundingBox(const CATLONG32    iPatchU,
                                         const CATLONG32    iPatchV,
                                               CATMathBox & ioBox) const = 0;

  /**
 * The diagnosis of evaluation.
 * @param CATSurface::NoSolution 
 *No parameter corresponds to this point
 * @param CATSurface::SingleSolution
 *Only one parameter corresponds to this point.
 *@param CATSurface::MultipleSolution
 *Several parameters correspond to this point.
 *@param CATSurface::InfiniteSolution
 * Infinitely many parameters correspond to this point.
 */
        enum CATSolutionDiagnostic { NoSolution , SingleSolution , MultipleSolution , InfiniteSolution } ;

/**
 * Retrieves the CATSurParam on <tt>this</tt> CATSurface corresponding to a given CATMathPoint.
 * <br>This transformation is only available
 * on canonical objects such as planes, cylinders, cones. If the surface is not canonical, 
 * the operator throw an exception. For non-canonical surfaces, 
 * use a projection operator.
 * @param iPoint
 * The CATMathPoint whose coordinates are to be transformed as CATSurParam.
 * @param ioParam
 * The first corresponding CATSurParam on the surface. 
 * @return
 * The diagnosis of the number of parameters that can be evaluated on this point.
 * <dl><dt> CATSurface::NoSolution  <dd>No parameter corresponds to this point.
 *     <dt> CATSurface::SingleSolution  <dd>Only one parameter corresponds to this point.
 *     <dt> CATSurface::MultipleSolution<dd>Several parameters correspond to this point.
 *     <dt> CATSurface::InfiniteSolution <dd>Infinitely many parameters correspond
 * to this point.
 *</dl>
 */
  virtual CATSurface::CATSolutionDiagnostic GetParam(const CATMathPoint & iPoint,
                                                           CATSurParam  & oIndex ) const = 0 ;

/**
 * Retrieves the CATSurParam on <tt>this</tt> CATSurface corresponding to a CATMathPoint.
 * inside limitations.
 *<br>This transformation is only available
 * on canonical objects such as planes, cylinders, cones. If the surface is not canonical,
 * the operator throws an exception. For non-canonical surface, use a projection operator.
 * @param iPoint
 * The CATMathPoint whose coordinates are to be transformed as a CATSurParam.
 * @param ioParam
 * The first corresponding CATSurParam on the surface.
 * @param iInside
 * The CATSurLimits to take into account for trimming the CATSurface.
 * @return
 * The diagnosis of the number of parameters that can be evaluated on this point.
 * <dl><dt> CATSurface::NoSolution  <dd>No parameter corresponds to this point.
 *     <dt> CATSurface::SingleSolution  <dd>Only one parameter corresponds to this point.
 *     <dt> CATSurface::MultipleSolution<dd>Several parameters correspond to this point.
 *     <dt> CATSurface::InfiniteSolution <dd>Infinitely many parameters correspond
 * to this point.
 *</dl>
 */
  virtual CATSurface::CATSolutionDiagnostic GetParam(const CATMathPoint & iPoint,
                                                           CATSurParam  & ioIndex  ,
                                                     const CATSurLimits & iInside  ) const = 0 ;

 /**
 * Retrieves the parameter on an iso-parametric curve of <tt>this</tt> CATSurface corresponding to a CATMathPoint.
 * <br> Used for surfaces for which </tt>GetImplicitEquation</tt>
 * returns a non-null pointer.
 * @param iPoint
 * The CATMathPoint whose coordinates are to be transformed as a CATSurParam.
 * @param iIsoparam
 * The isoparametric curve on which the parameter is computed.
 * @param iStart
 * The low limitation to take into account for trimming the CATSurface.
 * @param iEnd
 * The high limitation to take into account for trimming the CATSurface.
 * @param ioLambdaOnIsopar
 * The corresponding parameter value on the isoparametric curve.
 * @return
 * The diagnosis of the number of parameters that can be evaluated on this point.
 * <dl><dt> CATSurface::NoSolution  <dd>No parameter corresponds to this point.
 *     <dt> CATSurface::SingleSolution  <dd>Only one parameter corresponds to this point.
 *     <dt> CATSurface::MultipleSolution<dd>Several parameters correspond to this point.
 *     <dt> CATSurface::InfiniteSolution <dd>Infinitely many parameters correspond
 * to this point.
 *</dl>
 */
  virtual CATSurface::CATSolutionDiagnostic GetParamOnIsopar( const CATMathPoint    & iPoint,
                                                              const CATIsoParameter & iIsoparam,
                                                              const CATSurParam     & iStart,
                                                              const CATSurParam     & iEnd,
                                                                    double          & ioLambdaOnIsopar) const = 0 ;

/**
 * Tests whether two parameters can be considered as different.
 *<br>This can be used for distinguishing 2 points on both sides of a surface
 * closure.
 * @param iW1
 * The first parameter to compare.
 * @param iW2
 * The second parameter to compare.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 * <dl><dt> 0 <dd> if they are not considered as different
 *     <dt> 1 <dd> if they are considered as different</dl>
 */
  virtual CATBoolean Compare( const CATSurParam & iW1,
                              const CATSurParam & iW2 ) const = 0;

/** Checks if <tt>this</tt> CATSurface is linear in a or two directions of the parameter.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 * <dl><dt> CATIsoParNoDir   <dd> if they is no linearity
 *     <dt> CATIsoParamU     <dd> if the isoparameters with U constant are lines
 *     <dt> CATIsoParamV     <dd> if the isoparameters with V constant are lines
 *     <dt> CATIsoParBothDir <dd> if the isoparameters with U constant or V constant are lines</dl>
 */
  virtual CATIsoParameter IsLinear() const = 0;

/** Checks if <tt>this</tt> CATSurface is circular in a or two directions of the parameter.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 * <dl><dt> CATIsoParNoDir   <dd> if they is no circle on the surface
 *     <dt> CATIsoParamU     <dd> if the isoparameters with U constant are circles.
 *     <dt> CATIsoParamV     <dd> if the isoparameters with V constant are circles.
 *     <dt> CATIsoPaRBothDir <dd> if the isoparameters with U constant or V constant are circles.</dl>
 */
  virtual CATIsoParameter IsCircular() const = 0;
  
/**
 * Returns a pointer to the geometric representation of <tt>this</tt> CATSurface.
 *@return
 * The pointer to the canonical surface (CATPlane, CATCylinder, CATCone, ..)
 * of a complex object ( CATDraftSurface, CATFilletSurface) if it exists,
 *  <tt>this</tt> otherwise.
 */
  virtual const CATSurface * GetGeometricRep() const = 0;


  





  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


/**
 * @nodoc
 * Returns a linear transformation which converts the internal
 * parameter U to the naturel parameter U for implicit surfaces.
 * For example, the natural parameter of a circle is the angle.
 */
  virtual void GetMappingU(CATMathTransformation1D &ioTransfo1D) const = 0;

/**
 * @nodoc
 * Returns a linear transformation which converts the real
 * parameter V to the naturel parameter V for implicit surfaces. 
 */
  virtual void GetMappingV(CATMathTransformation1D &ioTransfo1D) const = 0;

/** @nodoc */
  virtual short GetOrientation( ) const = 0 ;
/** @nodoc */
  virtual void  SetOrientation( const short iNewOrientation ) = 0;


/**
 * @nodoc
 * Returns a pointer to the reference of <tt>this</tt> CATSurface.
 * @return
 * The pointer to the surface reference.
 */
  virtual const CATSurParamReference * GetParamReference() const = 0;


/**
 * @nodoc
 * Use GetMaxLimits.
 * Retrieves the number of patches on each direction of <tt>this</tt> CATSurface.
 */
  virtual void GetNumberOfComponent( CATLONG32 & oNbOfUPatches,
                                     CATLONG32 & oNbOfVPatches) const = 0;


/**
 * @nodoc
 * Creates a new surface, offsetted with regards to <tt>this</tt> CATSurface.
 * The newly created surface is a single surface ( as opposed to the CATOffsetSurface which will refer to this
 * single surface).
 */
  virtual CATSurface * CreateOffset(      CATGeoFactory           * iWhere, 
                                    const CATLength               & iOffset,
                                    const CATSurLimits            & iLimits,
                                          CATMathTransformation2D * &oTransfo2D) const = 0;


/**
 * @nodoc
 * Returns a pointer to the implicit equation representing <tt>this</tt> CATSurface.
 *<br>The equation is not restricted to the limits of the surface.
 * @return
 * A pointer to the equation of the surface,
 * <tt>NULL</tt> whenever no implicit equation exists for that surface type.
 * The output equation must not be deleted, as part of the object..
 */
  virtual CATMathFunctionRN *GetImplicitEquation () const = 0;

/**
 * @nodoc
 * Tests whether <tt>this</tt> CATSurface has an implicit equation.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 *<dl> <dt><tt>1</tt> <dd>If <tt>this</tt> has an implicit equation.
 *     <dt><tt>0</tt> <dd>Otherwise.</dl>
 */ 
  virtual CATBoolean HasImplicitEquation() const = 0;

 
/**
* @nodoc
 * Retrieves the CATMathDirBox surrounding the normals of <tt>this</tt> CATSurface.
 *<br>All the normals of the surface ( returned by EvalNormal ) belong to the
 * CATMathDirBox defined as the set of <br>
 *{ CATMathDirection Dir such that, 
 *   Dir * DirBox.GetDirection() > cos ( DirBox.GetSize() ) },<br>
 * where DirBox = Surface->GetDirBox() }. 
 * This method takes into account the current limitations of the surface.
 */
  virtual void GetDirBox( CATMathDirBox & oDirBox ) const = 0 ;

/**
* @nodoc
 * Retrieves the CATMathDirBox surrounding the normals of <tt>this</tt> CATSurface patch.
 *<br>All the normals of the patch ( returned by EvalNormal ) belong to the
 * CATMathDirBox defined as the set of <br>
 *{ CATMathDirection Dir such that, 
 *   Dir * DirBox.GetDirection() > cos ( DirBox.GetSize() ) },<br>
 * where DirBox = Surface->GetDirBox() }.
 * This methods takes into account the current limitations of the surface.
 */
  virtual void GetInternalDirBox(const CATLONG32       iPatchU,
                                 const CATLONG32       iPatchV,
                                       CATMathDirBox & oDirBox) const = 0;
  


// Deprecated
 /** @nodoc */
  virtual void Eval(const CATSurLimits         & iBoxToEvaluate,
                          CATEvalCommand         iCommand      ,
                          CATMathGridOfPoints  * iPointm       ,
                          CATMathGridOfVectors * iVectord1     ,
                          CATMathGridOfVectors * iVectord2     ) const = 0;

 /**
 * Retrieves the normal at a point  of <tt>this</tt> surface. 
 * The CATSurface::EvalNormal signature which returns a void should be preferred 
 * over the present API.
 * @param iParam
 * The CATSurParam which defines the point of the surface.
 * @return
 * The outer normal oriented along <tt> ds/du ^ ds/dv</tt>.
 */
  virtual CATMathDirection EvalNormal(const CATSurParam & iParam) const = 0;

 /**
 * Returns the mathematical point associated with a CATSurParam. 
 * The CATSurface::EvalPoint signature which returns a void should be preferred 
 * over the present API.
 * @param iParam
 * The CATSurParam parameter.
 * return
 * The corresponding mathematical point.
 */
  virtual CATMathPoint EvalPoint(const CATSurParam & iParam) const = 0;

 /**
 * Creates a CATSurParam on <tt>this</tt> surface from global parameters.
 * The CATSurface::CreateParam signature which returns a void should be preferred
 * over the present API.
 * @param iUParam
 * The parameter value in the first direction.
 * @param iVParam
 * The parameter value in the second direction.
 * @return
 * The resulting parameter.
 */
  virtual CATSurParam CreateParam(const double & iUParam,
                                  const double & iVParam) const = 0;
/**
 * Creates a CATSurParam on <tt>this</tt> surface from local parameters.
 * The CATSurface::CreateParam signature which returns a void should be preferred
 * over the present API.
 * @param iUParam
 * The local parameter value in the first direction on <tt>iPatchU</tt>.
 * @param iUNum
 * The patch number in the first direction.
 * @param iVParam
 * The local parameter value in the second direction on <tt>iPatchV</tt>.
 * @param iVNum
 * The patch number in the second direction.
 * @return
 * The resulting parameter. 
 */
  virtual CATSurParam CreateParam(const double    & iUParam,
                                  const CATLONG32 & iUNum  ,
                                  const double    & iVParam,
                                  const CATLONG32 & iVNum  ) const = 0;
 /**
 * Returns the current limitations of <tt>this</tt> CATSurface.
 * The CATSurface::GetLimits signature which returns a void should be preferred
 * over the present API.
 * @return
 * The limitations of <tt>this</tt> CATSurface.
 */
  virtual CATSurLimits GetLimits() const = 0;
 /**
 * Returns the high limitation of <tt>this</tt> CATSurface.
 * The CATSurface::GetEndLimit signature which returns a void should be preferred
 * over the present API.
 * @return
 * The CATSurParam which defines the high limitation of <tt>this</tt> CATSurface.
 */
  virtual CATSurParam GetEndLimit() const = 0;
 /**
 * Returns the low limitation of <tt>this</tt> CATSurface.
 * The CATSurface::GetStartLimit signature which returns a void should be preferred
 * over the present API.
 * @return
 * The CATSurParam which defines the low limitation of <tt>this</tt> CATSurface.
 */
  virtual CATSurParam GetStartLimit() const = 0;

 /** @nodoc */
  virtual CATSurLimits GetInternalLimits(const CATLONG32 iIndexU,
                                         const CATLONG32 iIndexV) const = 0;

 /** @nodoc */
  virtual CATSurLimits GetMaxLimits() const = 0;
 
/** @nodoc */
  virtual CATSurLimits GetInternalMaxLimits(const CATLONG32 iIndexU,
                                            const CATLONG32 iIndexV) const = 0;

 /** @nodoc */
  virtual CATMathBox GetInternalBoundingBox(const CATLONG32 iUNum,
                                            const CATLONG32 iVNum) const = 0;

 /** @nodoc */
  virtual CATMathBox GetInternalMaxBoundingBox(const CATLONG32 iUNum,
                                               const CATLONG32 iVNum) const = 0;

 /**
  * @nodoc
  * @return 0 on success, negative number upon error
  */
  virtual int GetAdvancedBox                   (const CATSurLimits       & iLimits,
                                                      CATMathAdvancedBox & ioBox  ) const = 0;
 /**
  * @nodoc
  * @return 0 on success, negative number upon error
  */
  virtual int GetInternalMaxAdvancedBoundingBox(const CATLONG32            iUNum,
                                                const CATLONG32            iVNum,
                                                      CATMathAdvancedBox & ioBox) const = 0;

/** @nodoc */
  virtual CATMathSetOfLongs * GetNumberOfComponent() const = 0;
 /** @nodoc */
  virtual void                OpenEquation        () const = 0;
/** @nodoc */
  virtual void                CloseEquation       () const = 0;


/** @nodoc */
  virtual void PropagateQuery(      CATICGMUnknown     * iFrom  ,
                              const CATSurLimits       & iLimits,
                                    CATCGMQueryManager & iQuery ) = 0;

};
  CATDeclareHandler(CATSurface,CATGeometry);

#endif
