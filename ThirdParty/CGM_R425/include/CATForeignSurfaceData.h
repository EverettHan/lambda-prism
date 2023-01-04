
#ifndef CATForeignSurfaceData_H
#define CATForeignSurfaceData_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U2
 */ 

#include "YP00IMPL.h"                         // For Windows 
#include "CATForeignGeometryData.h"                          

class CATSurLimits ;                          
class CATSurParam ;
class CATSurParamReference ;
class CATKnotVector;
class CATMathFunctionXY;
class CATMathVector2D;
class CATMathFunctionRN;
class CATMathCurve ;
class CATMathBox ;
            
#include "CATMathDef.h"
#include "CATSurface.h"

/**
 * Class for the definition of data for foreign surfaces.
 * A foreign surface is introduced into CGM by filling the CATIForeignSurface object data
 * with a CATForeignSurfaceData. Then, it is automatically integrated into CGM, and
 * can be used as any CATSurface by the operators and the topology.
 * <br>To create your own surface class, you have to derive this CATForeignSurfaceData
 * class, and overload at least the mandatory methods that are associated with.
 * The pure virtual methods you must overload for your own object are:
 * <ul>
 *		<li><tt>GetLimits, GetInternalMaxLimits</tt> and <tt>GetMaxLimits</tt> 
 * 		return the current and maximum limitation respectively, <tt>SetLimits</tt> 
 *		defines a current limitation.</li>
 *		<li><tt>Extrapolate</tt> must extend the MaxLimits of this surface.</li>
 *		<li><tt>GetKnotVector</tt> retrieves the nodal representation if 
 *		your surface has several patches.</li>
 *		<li><tt>IsConfused</tt> tests is the transformation of your surface 
 *		is globally coincident with another surface.</li>
 *		<li><tt>IsPeriodicU</tt>, <tt>IsPeriodicV</tt> test whether the surface is periodic along U and V.</li>
 * </ul>
 * As a surface is a bi-parameterized geometric element,
 * it may be 
 * represented by three CATMathFunctionXY (<tt>(FX(x,y), FY(x,y), FZ(x,y))</tt>), 
 * that are retrieved through the
 * <tt>GetGlobalEquation</tt> method. <tt>(x,y)</tt> are the parameters of a point on
 * the surface. These parameters can also be denoted throughout <tt>(U,V)</tt>,
 * and they are handled
 * with the <tt>CATSurParam</tt> class. 
 * <br>Surfaces can have several patches in each direction,
 * that are located with a patch number in the first direction <tt>iPatchU</tt> and
 * a patch number in the second direction <tt>iPatchV</tt>. Hence, you can use
 * a local parameter on a given patch, or a global parameter, that takes in account the
 * whole surface. Notice that the patch numbers are not necessarily
 * positive, but their values are consecutive. If your surfaces have several patches, 
 * you must use the nodal vector
 * representation, and these nodal vectors must not be periodic.
 * <br> 
 * <tt>CATSurLimits</tt> is a class allowing
 * the surface to be restricted to a part of it. 
 * These limitations 
 * define the area where the surface may currently be evaluated.
 * <br>Each type of surface is responsible for the mapping (called Evaluation) between the (U,V) parameters
 * and their corresponding coordinates in the 3D space . No assumption can be made about
 * this mapping by a developper who uses these objects, except that it is C2 continuous
 * (at least twice differentiable).
 * <br>
 * For this reason, the developper who wants
 * to create new types of surfaces has to write the evaluation methods for his new class. 
 * Now, the evaluators are based on the evaluation of the corresponding CATMathFunctionXY. 
 * If your new surface requests a new type of CATMathFunctionXY, 
 * you must write the evaluators for
 * these new CATMathFunctionsXY.
 * @see CATIForeignSurface, CATSurface
 */

class ExportedByYP00IMPL CATForeignSurfaceData : public CATForeignGeometryData
{
  public :
    /** @nodoc */
  CATCGMDeclareAttribute (CATForeignSurfaceData,CATForeignGeometryData);

  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/**
 * Returns the mathematical point associated with a CATSurParam.
 * @param iPosition
 * The point of the surface.
 * @param ioPoint
 * The corresponding mathematical point.
 */
  virtual void EvalPoint(const CATSurParam & iPosition,
			             CATMathPoint      & ioPoint ) const;
/**
 * Retrieves the first derivatives on a point of a foreign surface. 
 * @param iParam
 * The point of the surface.
 * @param ioDU
 * The first derivative w.r.t. to the U parameter.
 * @param ioDV
 * The first derivative w.r.t. to the V parameter.
 */
  virtual void EvalFirstDeriv(const CATSurParam & iPosition,
			                  CATMathVector     & ioDU,
			                  CATMathVector     & ioDV       ) const;
/**
 * Retrieves the second derivatives on a point of a foreign surface.
 * @param iParam
 * The point of the surface.
 * @param ioDU2
 * The second derivative w.r.t. to the U parameter.
 * @param ioDUDV
 * The second derivative w.r.t. to the UV parameters.
 * @param ioDV2
 * The second derivative w.r.t. to the V parameter.
 */
  virtual void EvalSecondDeriv(const CATSurParam & iPosition,
			                   CATMathVector     & ioDU2,
			                   CATMathVector     & ioDUDV,
			                   CATMathVector     & ioDV2) const;
/**
 * Retrieves the third derivatives on a point  of a foreign surface. 
 * @param iParam
 * The point of the surface.
 * @param ioDU3
 * The third derivative w.r.t. to the U parameter.
 * @param ioDU2DV
 * The third derivative w.r.t. to the UUV parameters.
 * @param ioDUDV2
 * The third derivative w.r.t. to the UVV parameters.
 * @param ioDV3
 * The third derivative w.r.t. to the V parameter.
 */
  virtual void EvalThirdDeriv(const CATSurParam & iPosition,
			                  CATMathVector     & ioDU3,
			                  CATMathVector     & ioDU2DV,
			                  CATMathVector     & ioDUDV2,
			                  CATMathVector     & ioDV3) const;
  /**
 * Retrieves multiple evaluations on a grid of points of a foreign surface.
 *<br>The method reallocates memory if necessary.If the number of points 
 * in U or V is 1, then the evaluation
 * is done on the low part of the CATSurLimits for this(these) coordinate(s).
 * @param iBox
 * The limits of the surface to take into account.
 * @param iNbOfPointsInU
 * The number of points to distribute among the limits on the surface 
 * first direction.
 * @param iNbOfPointsInV
 * The number of points to distribute among the limits on the surface 
 * second direction.
 * @param iCommand
 * The command precising the requested evaluation types.
 * @param oResult
 * The evaluation at the given points such that the <tt>(IndexU, IndexV)</tt> point
 * evaluation is located at the <tt>3*(IndexU + iNbOfPointsInU*IndexV)</tt> place.
 */
  virtual void EvalMultiple(const CATSurLimits      & iBox,
			                CATLONG32                      iCountPointsInU,
			                CATLONG32                      iCountPointsInV,
			                const CATSurEvalCommand & iCommand,
			                CATSurEvalResult        & oResult) const;
/**
 * Retrieves multiple evalutions at a given point of <tt>this</tt> CATSurface.
 * @param iParam
 * The point of the surface.
 * @param iCommand
 * The command precising the requested evaluation types.
 * @param ioResult
 * The resulting evaluations.
 */
  virtual void EvalLocal(const CATSurParam       & iParameter,
			             const CATSurEvalCommand & iCommand,
			             CATSurEvalLocal         & oResult) const;

/**
 * Returns the smallest box surrounding a portion of a foreign surface, with regards to
 * the provided CATSurlimits.
 * @param iLimits
 * The limits on the surface
 * @param ioBox
 * The box surrounding the surface limited by <tt>iLimits</tt>.
 */
  virtual void GetBox( const CATSurLimits & iLimits, CATMathBox & ioBox) const ;

/**
 * Modifies the current limitations of a foreign surface.
 * @param iNewLimits
 * The new current limitations.
 */
  virtual void SetLimits(const CATSurLimits & iNewLimits) =0 ; 
	
/**
 * Returns the current limitations of a foreign surface.
 * @param ioLimits
 * The limitations of <tt>this</tt> CATSurface.
 */
  virtual void GetLimits(CATSurLimits & ioLimits) const  =0;

/**
 * Returns the maximum limitations of a foreign surface.
 *<br>This does not take into account the current limitations .
 * @param ioLimits
 * The maximum limitations of <tt>this</tt> CATSurface.
 */
  virtual void GetMaxLimits(CATSurLimits & ioLimits) const =0 ;

/**
 * Changes the maximum limitations of this surface.
 * @param iRequiredParamExtension
 * The value of extension.
 *<ul>
 * <li>if iRequiredParamExtension.GetX()>0, Umax is expected to increase by this value.
 * <li>if iRequiredParamExtension.GetY()<0, Vmin is expected to decrease,
 * <li>if null, no change is required in the related direction.
 * </ul>
 * @param ioActualExtension
 * If NULL, no information on actual extrapolation is required.
 */
  virtual CATBoolean Extrapolate(const CATMathVector2D & iRequiredParamExtension,
                                       CATMathVector2D * ioActualExtension = NULL  )  =0 ;

/**
 * Returns the maximum limitations of an internal patch of a foreign surface.
 *<br>This does not take into account the current limitations . These maximum
 * limits can be the creation limits or the limits that are obtained by 
 * extrapolation, depending on the types of geometric objects.
  * @param iPatchU
 * The patch number in the first direction.
 * @param iPatchV
 * The patch number in the second direction.
 * @param ioLimits
 * The limitations of a patch.
 */
  virtual void GetInternalMaxLimits(const CATLONG32 iPatchU, const CATLONG32 iPatchV, CATSurLimits & ioLimits) const =0 ;

/**
 * Returns a pointer to the first nodal vector of a foreign surface.
 * <br>This is used when the surface has several patches. If it always
 * has only one patch, you must return a null pointer.
 * @return
 * The pointer to the knot vector.
 */
  virtual const CATKnotVector * GetKnotVectorU() const=0;
/**
 * Returns a pointer to the second nodal vector of a foreign surface.
 * <br>This is used when the surface has several patches. If it always
 * has only one patch, you must return a null pointer.
 * @return
 * The pointer to the knot vector.
 */
  virtual const CATKnotVector * GetKnotVectorV() const=0;
/**
 * Retrieves the mathematical equation associated with a patch of
 * a foreign surface.
 * <br>(oFx(U,V), oFy(U,V), oFz(U,V)) is then a point of the surface patch.
 * The method creates the equations, that must not be deleted as part of the object.
 * @param iPatchU
 * The patch number in the first direction.
 * @param iPatchVm
 * The patch number in the second direction.
 * @param oFx
 * A pointer to the parametric equation of the first coordinate. 
 * @param oFy
 * A pointer to the parametric equation of the second coordinate. 
 * @param oFz
 * A pointer to the parametric equation of the third coordinate. 
 */
  virtual void CreateLocalEquation(const CATLONG32 iPatchU, const CATLONG32 iPatchV,
			                       const CATMathFunctionXY * & oFx,
			                       const CATMathFunctionXY * & oFy,
			                       const CATMathFunctionXY * & oFz)  =0; 

/**
 * Checks if a foreign surface is linear in a or two directions of the parameter.
 * By default, returns <tt>CATIsoParNoDir</tt>
 * @return
  * The result of the test.
 * <br><b>Legal values</b>:
 * <dl><dt><tt> CATIsoParNoDir </tt>  <dd> if they is no linearity
 *     <dt><tt> CATIsoParamU    </tt> <dd> if the isoparameters with U constant are lines
 *     <dt><tt> CATIsoParamV    </tt> <dd> if the isoparameters with V constant are lines
 *     <dt><tt> CATIsoParBothDir </tt><dd> if the isoparameters with U constant or V constant are lines</dl>
 */
  virtual CATIsoParameter IsLinear() const;
/**
 * Checks if a foreign surface is circular in a or two directions of the parameter.
 * <br>By default, returns <tt>CATIsoParNoDir</tt>
 * @return
  * The result of the test.
 * <br><b>Legal values</b>:
 * <dl><dt> <tt>CATIsoParNoDir  </tt> <dd> if they is no circle on the surface
 *     <dt> <tt>CATIsoParamU    </tt> <dd> if the isoparameters with U constant are circles.
 *     <dt> <tt>CATIsoParamV     </tt><dd> if the isoparameters with V constant are circles.
 *     <dt><tt> CATIsoPaRBothDir </tt><dd> if the isoparameters with U constant or V constant are circles.</dl>
 */
  virtual CATIsoParameter IsCircular() const;

/**
 * Returns a pointer to the mathematical representation of an isoparametric
 * curve of a foreign surface.
 * @param iIsoParameter
 * The type of iso-parametric curve.
 * @param iLocation
 * A point belonging to the curve.
 *@return
 * The pointer to the CATMathCurve, that has to be deleted by the caller.
 * No mathematical representation by default. 
 */
  virtual CATMathCurve* GetMathCurve(const CATIsoParameter   iIsoParameter,
				                     const CATSurParam     & iLocation  ) const ;
/**
 * Tests whether an isoparametric curve of  a foreign surface has a mathematical representation.
 * <br>Optional method. No mathematical representation by default. 
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
				                  const CATSurParam     & iLocation ) const ;

/**
 * Retrieves the CATSurParam on  a foreign surface corresponding to a given CATMathPoint.
 * <br> To write for surfaces for which </tt>GetImplicitEquation</tt>
 * returns a non-null pointer.
 * @param iLocation
 * The CATMathPoint whose coordinates are to be transformed as CATSurParam.
 * @param ioParam
 * The first corresponding CATSurParam on the surface. 
 * @return
 * The diagnosis of the number of parameters that can be evaluated on this point.
 * <dl><dt> NoSolution  <dd>No parameter corresponds to this point.
 *     <dt> SingleSolution  <dd>Only one parameter corresponds to this point.
 *     <dt> MultipleSolution<dd>Several parameters correspond to this point.
 *     <dt> InfiniteSolution <dd>Infinitely many parameters correspond
 * to this point.
 *</dl>
 */
  virtual CATSurface::CATSolutionDiagnostic GetParam(const CATMathPoint & iLocation,
						                             CATSurParam  & ioParam ) const;
/**
 * Retrieves the CATSurParam on  a foreign surface corresponding to CATMathPoint.
 * <br>Only parameters inside <tt>iInside</tt> are retrieved,
 * <br> To write for  surfaces for which </tt>GetImplicitEquation</tt>
 * returns a non-null pointer.
 * @param iLocation
 * The CATMathPoint whose coordinates are to be transformed as a CATSurParam.
 * @param ioParam
 * The first corresponding CATSurParam on the surface.
 * @param iInside
 * The CATSurLimits to take into account for trimming the CATSurface.
 * @return
 * The diagnosis of the number of parameters that can be evaluated on this point.
 * <dl><dt> NoSolution  <dd>No parameter corresponds to this point.
 *     <dt> SingleSolution  <dd>Only one parameter corresponds to this point.
 *     <dt> MultipleSolution<dd>Several parameters correspond to this point.
 *     <dt> InfiniteSolution <dd>Infinitely many parameters correspond
 * to this point.
 *</dl>
 */
  virtual CATSurface::CATSolutionDiagnostic GetParam(const CATMathPoint & iLocation,
						                             CATSurParam  & ioParam   ,
						                             const CATSurLimits & iInside  ) const;
/**
 * Retrieves the parameter on an iso-parametric curve of  a foreign surface corresponding to CATMathPoint
 * <br> To write for surfaces for which <tt>GetImplicitEquation</tt>
 * returns a non-null pointer.
 * @param iPoint
 * The CATMathPoint whose coordinates are to be transformed as a CATSurParam.
 * @param iIsoparam
 * The isoparametric curve on which the parameter is computed.
 * @param iStart
 * The low limitation to take into account for trimming the surface.
 * @param iEnd
 * The high limitation to take into account for trimming the surface.
 * @param ioLambdaOnIsopar
 * The corresponding parameter value on the isoparametric curve.
 * @return
 * The diagnosis of the number of parameters that can be evaluated on this point.
 * <dl><dt> NoSolution  <dd>No parameter corresponds to this point.
 *     <dt> SingleSolution  <dd>Only one parameter corresponds to this point.
 *     <dt> MultipleSolution<dd>Several parameters correspond to this point.
 *     <dt> InfiniteSolution <dd>Infinitely many parameters correspond
 * to this point.
 *</dl>
 */
  virtual CATSurface::CATSolutionDiagnostic GetParamOnIsopar(const CATMathPoint    & iPoint,
                                                             const CATIsoParameter & iIsoparam,
                                                             const CATSurParam     & iStart,
                                                             const CATSurParam     & iEnd,
                                                             double                & ioLambdaOnIsopar) const ;


/**
 * Tests whether a foreign surface is geometrically invariant.
 *<br>This method does not take into account the current limitations of 
 * the curve.
 * @param iTransfo
 * The tested transformation.
 * @param ioTransfo2D
 * The 2D-transformation defining the change of parametrization between <tt>this</tt> and the transformation of
 * <tt>this</tt>.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 *<dl> <dt><tt>1</tt> <dd>If the transformation of <tt>this</tt> is geometrically the same as <tt>this</tt>.
 *     <dt><tt>0</tt> <dd>Otherwise.</dl>
 */
  virtual CATBoolean IsInvariant(const CATMathTransformation   & iTransfo,
				                       CATMathTransformation2D * ioTransfo2D = NULL) const ;
  
/**
 * Tests whether the transformation of  a foreign surface is coiencident with another curve.
 *<br>This method does not take into account the current limitations of 
 * the curves.
 * @param iTransfo
 * The tested transformation.
 * @param iTSurface
 * The other surface.
 * @param ioTransfo2D
 * The 2D-transformation defining the change of parametrization between the transformation of 
 * <tt>this</tt> and <tt>iTSurface</tt>.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 *<dl> <dt><tt>1</tt> <dd>If the transformation of <tt>this</tt> is geometrically the same as <tt>iTSurface</tt>.
 *     <dt><tt>0</tt> <dd>Otherwise.</dl>
 */
  virtual CATBoolean IsConfused(const CATMathTransformation   & iTransfo,
			                    const CATSurface              * iTSurface,
			                          CATMathTransformation2D * ioTransfo2D = NULL) const =0;

/**
 * Creates a new surface, offsetted with regards to a foreign surface.
 * <br>By default, creates a CATOffsetSurface. 
 * @param iWhere
 * A pointer to the factory for creation.
 * @param iOffset
 * The offset value.
 * @param iLimits
 * The limitations to take into account.
 * @param ioTransfo2D
 * The 2D-transformation defining the change of parametrization between the surface and its offset.
 * @return
 * The created surface.
 */
  virtual CATSurface * CreateOffset( CATGeoFactory * iWhere,
		                              const double & iOffset,
		                              const CATSurLimits &iLimits,
		                              CATMathTransformation2D * &ioTransfo2D) const;


/**
 * Creates a new curve along an isoparametric curve of a foreign surface.
 * <br>By default, creates a PLine. 
 * @param iIsoParameter
 * The type of iso parametric curve.
 * @param iParam
 * The point of the surface belonging to the curve to create.
 * @param iWhere
 * A pointer to the factory for creation.
 * @return
 * A pointer to the created curve.
 */
  CATCurve * ExtractIsoParametricCurve( CATIsoParameter     iIsoParameter,
				                        const CATSurParam & iParam,     
				                        CATGeoFactory*      iWhere )const;

/**
 * Tests whether a foreign surface is periodic along the first direction. This method has to be overloaded.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 *<dl><dt> 0 <dd> if it is not periodic along the U direction
 *    <dt> 1 <dd> if it is periodic along the U direction</dl>
 */
  virtual CATBoolean IsPeriodicU() const=0;

/**
 * Tests whether a foreign surface is periodic along the second direction. This method has to be overloaded.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 *<dl><dt> 0 <dd> if it is not periodic along the V direction
 *    <dt> 1 <dd> if it is periodic along the V direction</dl>
 */
  virtual CATBoolean IsPeriodicV() const=0;


  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/**
 * @nodoc
 * Returns a pointer to the implicit equation representing  a foreign surface.
 *<br> 
 * The equation is not restricted to the limits of the surface. 
 * @return
 * The pointer to the implicit equation, NULL whenever no implicit equation exists for that surface type.
 * If the surface has an implicit equation,
 * you must write the <tt>GetParam</tt> methods.
 * The method creates the equation, that must not be deleted as part of the object.
 */
  virtual CATMathFunctionRN* CreateImplicitEquation ();

/**
 * @nodoc
 * Tests whether  a foreign surface has an implicit equation.
 * No implicit equation by default. If the surface has an implicit equation,
 * you must write the <tt>GetParam</tt> methods. 
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 *<dl> <dt><tt>1</tt> <dd>If <tt>this</tt> has an implicit equation.
 *     <dt><tt>0</tt> <dd>Otherwise.</dl>
 */ 
  virtual CATBoolean HasImplicitEquation() const ;

/**
 * @nodoc
 * Returns a pointer to the CATSurParamReference of the surface.
 * @return
 * A pointer to the reference of the surface that has <tt>this</tt> CATForeignSurfaceData.
 */
  const CATSurParamReference* GetParamReference() const;

	/** 
	* Default constructor
	*/
  CATForeignSurfaceData() ;
  virtual ~CATForeignSurfaceData() ;

//=======================================================================================
// Private Data
//=======================================================================================
  /** @nodoc */
  CATSurParamReference* _ParamReference ;

};

#endif
