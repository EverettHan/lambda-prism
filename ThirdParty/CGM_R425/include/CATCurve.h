#ifndef CATCurve_h
#define CATCurve_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATGeometry.h"
#include "CATMathDef.h"
#include "CATCrvEvalCommand.h"

/* To suppress */
#include "CATEvalCommand.h"
/* To suppress */

#include "CATMathSetOfPoints.h" 
#include "CATMathSetOfVectors.h"
class CATMathFunctionX;
class CATMathPoint;
class CATMathVector;
class CATMathBox;
class CATMathCurve;
class CATKnotVector;
class CATGeometry;
class CATPCurve;
class CATPlane;
class CATCrvParamReference;
class CATCrvParam;
class CATCrvLimits;
class CATSetOfCrvParams;
class CATCrvEvalLocal;
class CATCrvEvalResult;
class CATMathTransformation1D;

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATCurve ;
#else
extern "C" const IID IID_CATCurve ;
#endif

class CATMathAdvancedBox;

/**
 * Interface representing the base class for all curves.
 * Each point of a curve is identified by a global parameter
 * <tt>CATCrvParam</tt>. A curve portion is defined by <tt>CATCrvLimits</tt>.
 * <b>Curve parameterization</b><br>
 * The geometric modeler optimal behavior requires
 * arc length parameterized
 * (or nearly arc length parameterized) curves. Standard operators generate 
 * arc length parameterized curves and complete properly when their input data
 * are arc length parameterized curves. Non-standard curves (foreign curves)
 * should be created as arc length parameterized curves.<br>
 * <b>Retrieving the CATCrvParam of a 3D point located on a curve</b> <br>
 * To retrieve the curve parameter associated with a
 * 3D point, use a geometric projection operator.
 * <b>Retrieving the point and derivatives from a CATCrvParam</b><br>
 * Multiple evaluations can be performed in one way by defining
 * a <tt>CATCrvCommand</tt> object, evaluating through the <tt>Eval</tt>
 * method and retrieving the results with a <tt>CATCrvEvalResult</tt> object.
 * Example:
 * <pre>
 * CATCrvEvalLocal EvalResult;
 * CATCrvParam Parameter ;
 * Curve->GetStartLimit(Parameter) ;
 * Curve->Eval(Parameter, CATCrvEvalCommand::EvalPoint                , EvalResult) ; // Evaluate point
 * Curve->Eval(Parameter, CATCrvEvalCommand::EvalFirstDerivative      , EvalResult) ; // Evaluate first  derivative
 * Curve->Eval(Parameter, CATCrvEvalCommand::EvalSecondDerivative     , EvalResult) ; // Evaluate second derivative
 * Curve->Eval(Parameter, CATCrvEvalCommand::EvalThirdDerivative      , EvalResult) ; // Evaluate third  derivative
 * Curve->Eval(Parameter, CATCrvEvalCommand::EvalUpToFirstDerivative  , EvalResult) ; // Evaluate all    derivatives up to first  derivative 
 * Curve->Eval(Parameter, CATCrvEvalCommand::EvalUpToSecondDerivative , EvalResult) ; // Evaluate all    derivatives up to second derivative 
 * Curve->Eval(Parameter, CATCrvEvalCommand::EvalUpToThirdDerivative  , EvalResult) ; // Evaluate all    derivatives up to third  derivative 
 * </pre>
 * <br> The first and last arc number can be retrieved with the <tt>GetMaxLimits</tt> method.
 */
class ExportedByCATGMGeometricInterfaces CATCurve : public CATGeometry
{
  CATDeclareInterface;

public:

/**
 * Evaluates <tt>this</tt> CATCurve and its derivatives associated with <tt>this</tt> CATCrvParam.
 * @param iPoint
 * The parameter of the point to evaluate.
 * @param iCommand
 * The type of evaluation.
 * @param ioResult.
 * The object containing the results.
 */
  virtual void Eval(const CATCrvParam       & iPoint,
		    const CATCrvEvalCommand & iCommand,
		    CATCrvEvalLocal         & ioResult) const =0 ;

 /**
 * Evaluates <tt>this</tt> CATCurve and its derivatives inside a domain.
 * @param iDomainToEvaluate
 * The limits inside which the domain is to be evaluated.
 * @param iNbOfPoints
 * The number of equally spaced points of <tt>iDomainToEvaluate</tt>.
 * @param iCommand
 * The type of evaluation.
 * @param ioResult.
 * The object containing the results.
 */
  virtual void Eval(const CATCrvLimits      & iDomainToEvaluate,
		    const CATLONG32                iNbOfPoints,
		    const CATCrvEvalCommand & iCommand,
		    CATCrvEvalResult        & ioResult) const =0 ;

/**
 * Evaluates <tt>this</tt> CATCurve and its derivatives associated with <tt>this</tt> CATCrvParam.
 * @param iParam
 * The parameter of the point to evaluate.
 * @param iCommand
 * The type of evaluation. The corresponding output pointer must be allocated.
 * @param iPoint
 * A pointer to the resulting 3D point.
 * @param iFirstDeriv 
 * A pointer to the resulting first derivative.
 * @param iSecondDeriv 
 * A pointer to the resulting second derivative.
 * @param iThirdDeriv 
 * A pointer to the resulting third derivative.
 */
  virtual void Eval(const CATCrvParam & iParam,
		    const CATCrvEvalCommand & iCommand,
		    CATMathPoint* iPoint,
		    CATMathVector* iFirstDeriv = NULL,
		    CATMathVector* iSecondDeriv = NULL,
		    CATMathVector* iThirdDeriv = NULL ) const =0;

/**
 * Sets a global parameter on <tt>this</tt> CATCurve.
 * @param iGlobalParam
 * The value of the global parameter.
 * @param ioParam
 * The corresponding parameter on <tt>this</tt>, valuated with <tt>iGlobalParam</tt>.
 */
  virtual void CreateParam(const double iGlobalParam, CATCrvParam & ioParam) const =0;

/**
 * Sets a global parameter on a CATCurve from a local parameter and
 * an arc number.
 * @param iLocal
 * The value of the local parameter.
 * @param iArc
 * The arc number.
 * @param ioParam
 * The corresponding parameter on <tt>this</tt>, valuated with <tt>iGlobalParam</tt>.
 */ 

  virtual void CreateParam(const double iLocal, const CATLONG32 iArc, CATCrvParam & ioParam) const =0;

/**
 * Returns the knot vector associated with <tt>this</tt> CATCurve.
 * @return
 * The knot vector.
 */
  virtual const CATKnotVector * GetKnotVector() const =0;

 /**
 * Returns the current limits of <tt>this</tt> CATCurve.
 * @param ioCurrentLimits
 * The current limits.
 */
  virtual void GetLimits(CATCrvLimits & ioCurrentLimits) const =0;

 /**
 * Returns the maximum limitations of <tt>this</tt> CATCurve.
 * <br>This does not take into account the current limitations of the
 * curve. This maximum
 * limits can be the creation limits or the limits that are obtained by 
 * extrapolation, depending on the types of geometric objects.
 * @param ioMaxLimits
 * The maximum limits.
 */
  virtual void GetMaxLimits(CATCrvLimits & ioMaxLimits) const = 0 ;

//CAA_Exposed
/**
 * Returns the limitations of an arc of <tt>this</tt> CATCurve.
 *<br>This does not take into account the current limitations of the
 * curve.
 * @param iArc
 * The arc number.
 * @param ioInternalMaxLimits
 * The corresponding limitations.
 */
  virtual void GetInternalMaxLimits(const CATLONG32 iArc, CATCrvLimits & ioInternalMaxLimits) const =0;

/**
 * Returns the limitations of an arc of <tt>this</tt> CATCurve.
  *<br>This takes into account the current limitations of the
 * curve.
 * @param iArc
 * The arc number.
 * @param ioInternalMaxLimits
 * The corresponding limitations.
 */
  virtual void GetInternalLimits(const CATLONG32 iArc, CATCrvLimits & ioInternalMaxLimits) const =0;

//CAA_Exposed
/**
 * Returns the low current limitation of <tt>this</tt> CATCurve.
 * @param ioStartParam
 * The first limitation.
 */
  virtual void GetStartLimit(CATCrvParam & ioStartParam) const =0;

  //CAA_Exposed
/**
 * Returns the high current limitation of <tt>this</tt> CATCurve.
  * @param ioEndParam
 * The end limitation.
 */
  virtual void GetEndLimit(CATCrvParam & ioEndParam) const =0;

/**
 * Modifies the limitations of <tt>this</tt> CATCurve.
 * @param iLimits
 * The new current limitations.
 */
  virtual void SetLimits(const CATCrvLimits & iLimits)=0;

 //-------------------------------------------------------------------------
 //- Equations management
 //-------------------------------------------------------------------------
  //CAA_Exposed
/**
 * Locks the equations of <tt>this</tt> CATCurve before read them.
 */
  virtual void Lock() = 0 ;

  //CAA_Exposed
  /**
 * Unlocks the equations of <tt>this</tt> CATCurve after read them.
 */
  virtual void Unlock() = 0 ;

  //CAA_Exposed
/**
 * Retrieves the mathematical equation associated with an arc of
 * <tt>this</tt > CATCurve.
 * <br>Before retrieving the equations, you must <tt>Lock</tt> the curve.
 * You can then obtained the equations. When you have finished, you <tt>Unlock</tt> the curve.
 * The equations are then automatically deleted. 
 * @param iArc
 * The arc number.
 * @param oFx
 * A pointer to the equation of the first coordinate <tt>X=oFx(w)</tt>.
 * @param oFy
 * A pointer to the equation of the second coordinate <tt>Y=oFy(w)</tt>.
 * @param oFz
 * A pointer to the equation of the third coordinate <tt>Z=oFy(w)</tt>.
 */
  virtual void GetEquation(const CATLONG32 iArc,
			   const CATMathFunctionX * & oFx,
			   const CATMathFunctionX * & oFy,
			   const CATMathFunctionX * & oFz) const=0;

  //CAA_Exposed
/**
 * Retrieves the mathematical equation associated with 
 * <tt>this</tt > CATCurve.
* <br>Before retrieving the equations, you must <tt>Lock</tt> the curve.
 * You can then obtained the equations. When you have finished, you <tt>Unlock</tt> the curve.
 * The equations are then automatically deleted. 
 * @param oFx
 * A pointer to the equation of the first coordinate <tt>X=oFx(w)</tt>.
 * @param oFy
 * A pointer to the equation of the second coordinate <tt>Y=oFy(w)</tt>.
 * @param oFz
 * A pointer to the equation of the third coordinate <tt>Z=oFy(w)</tt>.
 */
  virtual void GetGlobalEquation(const CATMathFunctionX * & oFx,
				 const CATMathFunctionX * & oFy,
				 const CATMathFunctionX * & oFz) const=0;

  //CAA_Exposed
/**
 * Tests whether <tt>this</tt> CATCurve is periodic.
 *<br>This method does not take into account the current limitations of 
 * the curve.
 * @return
 * The result of the test.
 * <br><b>Legal values:</b>:
 *<dl> <dt><tt>0</tt> <dd>If the CATCurve is not periodic.
 *     <dt><tt>1</tt> <dd>If the CATCurve is periodic.  </dl>
 */
  virtual CATBoolean IsClosed() const=0;
 	
  //CAA_Exposed
/**
 * Tests whether <tt>this</tt> CATCurve is invariant.
 *<br>This method does not take into account the current limitations of 
 * the curve.
 * @param oTransfo1D
 * The 1D-transformation defining the change of parametrization between <tt>this</tt> and the transformation of
 * <tt>this</tt>. If <tt>NULL</tt>, this argument is not set.
 * @return
 * The result of the test.
 * <br><b>Legal values:</b>:
 *<dl> <dt><tt>1</tt> <dd>If the transformation of <tt>this</tt> is geometrically the same as <tt>this</tt>.
 *     <dt><tt>0</tt> <dd>Otherwise.</dl>
 */
  virtual CATBoolean IsInvariant(const CATMathTransformation & iTransfo,
			         CATMathTransformation1D* oTransfo1D = NULL) const = 0;

  //CAA_Exposed
/**
 * Tests whether <tt>this</tt> CATCurve is confused with another curve.
 *<br>This method does not take into account the current limitations of 
 * the curves.
 * @param oTransfo1D
 * The 1D-transformation defining the change of parametrization between the transformation of 
 * <tt>this</tt> and <tt>iTCurve</tt>. If <tt>NULL</tt>, this argument is not set.
 * @return
  * The result of the test.
 * <br><b>Legal values:</b>:
 *<dl> <dt><tt>1</tt> <dd>If the transformation of <tt>this</tt> is geometrically the same as <tt>iTCurve</tt>.
 *     <dt><tt>0</tt> <dd>Otherwise.</dl>
 */
  virtual CATBoolean IsConfused(const CATMathTransformation   & iTransfo,
				const CATCurve                * iTCurve,
				      CATMathTransformation1D * oTransfo1D = NULL) const = 0;

 /**
 * Retrieves the maximum bounding box including an arc of <tt>this</tt> CATCurve.
 * <br>This does not take into account the current limitations of the curve.
 * @param iArc
 * The arc number.
 * @param ioBox.
 * The 3D box.
 */
  virtual void GetInternalMaxBoundingBox(const CATLONG32 iArc, CATMathBox & ioBox) const = 0 ;

/**
 * Retrieves the bounding box including an arc of <tt>this</tt> CATCurve.
 *<br>This takes into account the current limitations of the
 * curve.
 * @param iArc
 * The arc number.
 * @param ioBox.
 * The 3D box.
 */
  virtual void GetInternalBoundingBox(const CATLONG32 iArc, CATMathBox & ioBox) const = 0 ;

  //CAA_Exposed
/**
 * Computes the bounding box of <tt>this</tt> CATCurve trimmed by given Limits.
 *<br>This does not take into account the current limitations of the
 * curve.
 * @param iLimits
 * The domain to take into account.
 * @param ioBox.
 * The 3D box.
 */
  virtual void GetBox( const CATCrvLimits & iLimits, CATMathBox & ioBox ) const = 0 ;

  //CAA_Exposed
/**
 * Returns a pointer to the mathematical representation of <tt>this</tt> CATCurve.
 * The life cycle of the returned CATMathCurve must be managed by the calling application.
 * <pre>
 * CATMathCurve * pMathCurve = hCurve->GetMathCurve();
 * if (pMathCurve)
 *   {
 *     ...
 *     delete pMathCurve; pMathCurve=NULL;
 *	 }
 * </pre>
 * @return 
 * The mathematical curve associated with <tt>this</tt>. If the
 * mathematical representation does not exist, the method returns a
 * <tt>NULL</tt> pointer.
 */
  virtual CATMathCurve* GetMathCurve() const = 0 ;

  //CAA_Exposed
/**
 * Tests whether <tt>this</tt> CATCurve has a mathematical representation.
 * @return
 * The result of the test.
 * <br><b>Legal values:</b>:
 *<dl> <dt><tt>1</tt> <dd>If <tt>this</tt> has a mathematical representation.
 *     <dt><tt>0</tt> <dd>Otherwise.</dl>
 */ 
  virtual CATBoolean HasMathCurve() const = 0 ;
 
  //CAA_Exposed
/**
 * Returns a pointer to the geometric representation of <tt>this</tt> CATCurve.
 * @param ioRepLimits
 * The limitations of the returned curve.
 * @param ioRepOrientation
 * The relative orientation of the returned curve.
 * <br><b>Legal values:</b>:
 * <dl> <dt> <tt>1</tt> <dd> If the returned curve has the same orientation
 *      <dt> <tt>-1</tt> <dd> If the returned curve has the opposite orientation.
 *</dl>
 * @return
 * The canonical underlying geometry.
 *<br> This is usefull for CATEdgeCurves suc as CATSimCurves in order to access
 * the underlying canonical geometry (such as CATCircle, CATLine,...).
 *  Returns <tt>this</tt> otherwise.
 */
  virtual const CATCurve * GetGeometricRep(CATCrvLimits & ioRepLimits,
					   short & ioRepOrientation) const = 0 ;

  //CAA_Exposed
/**
 * The diagnosis of evaluation.
 * @param NoSolution 
 *No parameter corresponds to this point
 * @param SingleSolution
 *Only one parameter corresponds to this point.
 *@param MultipleSolution
 *Several parameters correspond to this point.
 *@param InfiniteSolution
 * Infinitely many parameters correspond
 */
  enum CATSolutionDiagnostic { NoSolution , 
			       SingleSolution , 
			       MultipleSolution ,
			       InfiniteSolution } ;
//CAA_Exposed
 /**
 * Retrieves the CATCrvParam on <tt>this</tt> CATCurve corresponding to a given CATMathPoint.
 * <br>This transformation is only available
 * on canonical objects such as planes, lines, conics.
 * @param iPoint
 * The CATMathPoint which coordinates are to be transformed as CATCrvParam.
 * @param ioParam
 * The first corresponding CATCrvParam on the curve. 
 * @return
 * The diagnosis of the number of parameters that can be evaluated on this point.
 */
  virtual CATCurve::CATSolutionDiagnostic GetParam(const CATMathPoint & iPoint,
						         CATCrvParam  & ioParam) const = 0 ;

  //CAA_Exposed
/**
 * Retrieves the CATCrvParam on <tt>this</tt> CATCurve corresponding to a CATMathPoint
 * inside limitations.
 *<br>This transformation is only available
 * on canonical objects such as lines and conics.
 * @param iPoint
 * The CATMathPoint whose coordinates are to be transformed as a CATCrvParam.
 * @param ioParam
 * The first corresponding CATCrvParam on the curve.
 * @param iInside
 * The CATCrvLimits to take into account for trimming the CATCurve.
 * @return
 * The diagnosis of the number of parameters that can be evaluated on this point.
 */
  virtual CATCurve::CATSolutionDiagnostic GetParam(const CATMathPoint & iPoint,
		          		       	         CATCrvParam  & ioParam   ,
						   const CATCrvLimits & iInside  ) const = 0 ;


 //CAA_Exposed
/**
  * Tests whether <tt>this</tt> CATCurve is containing another one.
  * @param iOther
  * The oother curve.
  * @return
  * The diagnosis of the test.
  *<dl> <dt> FALSE <dd> if the CATCurve does not contain <tt>iOther</tt>
  *     <dt> TRUE <dd> if the CATCurve contains <tt>iOther</tt> </dl>
  */
  virtual CATBoolean IsContaining ( const CATCurve* iOther ) const = 0 ;


  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/**
 * @nodoc
 * Returns a pointer to the reference of a CATCurve.
 * @return
 * The curve reference.
 */
  virtual const CATCrvParamReference * GetParamReference() const = 0;

/** 
  * @nodoc 
  * Use GetMaxLimits.
  */
  virtual CATLONG32 GetNumberOfComponent() const =0;

/** @nodoc */
  enum CATProjectionDiagnostic { ProjectionDone, 
				 ProjectionNotAvailableYet, 
                                 ProjectionSingular,
				 ProjectionOverlaps, 
				 ProjectionDimensionLost } ; 

/** @nodoc*/
  virtual CATCurve::CATProjectionDiagnostic 
  CreateProjection(CATPlane* iOn, CATPCurve* & oProjection, 
		   CATSetOfCrvParams* iIndexOnCurve=NULL,CATSetOfCrvParams* ioIndexOnPCurve=NULL) const=0;

  /**  @nodoc */
  virtual CATGeometry* GetOwner ( ) const = 0 ;

  /** 
  * Evaluates <tt>this</tt> CATCurve by computing a CATMathPoint from a CATCrvParam.
  * <p>The CATCurve::Eval signature with the CATCrvEvalCommand::EvalPoint argument
  * should be preferred over CATCurve::EvalPoint as CATCurve::EvalPoint
  * can lead to bad performances when it is used intensively. 
  * @param iParam
  * The parameter of the point to evaluate.
  * @return CATMathPoint 
  * The CATMathPoint which has iParam as its parameter.  
  */
  virtual CATMathPoint EvalPoint(const CATCrvParam & iParam) const =0; 
  /** 
  * Evaluates <tt>this</tt> CATCurve by computing a first derivative from a CATCrvParam.
  * <p>The CATCurve::Eval signature with the CATCrvEvalCommand::EvalFirstDeriv argument
  * should be preferred over CATCurve::EvalFirstDeriv as CATCurve::EvalFirstDeriv
  * can lead to bad performances when it is used intensively. 
  * @param iParam
  * The parameter of the vector to evaluate.
  * @return CATMathVector 
  * The CATMathVector which has iParam as its parameter.  
  */
  virtual CATMathVector EvalFirstDeriv(const CATCrvParam & iParam) const =0;
   /** 
  * Evaluates <tt>this</tt> CATCurve by computing a second derivative from a CATCrvParam.
  * <p>The CATCurve::Eval signature with the CATCrvEvalCommand::EvalSecondDeriv argument
  * should be preferred over CATCurve::EvalSecondDeriv as CATCurve::EvalSecondDeriv
  * can lead to bad performances when it is used intensively. 
  * @param iParam
  * The parameter of the vector to evaluate.
  * @return CATMathVector 
  * The CATMathVector which has iParam as its parameter.  
  */
  virtual CATMathVector EvalSecondDeriv(const CATCrvParam & iParam) const =0;
   /** 
  * Evaluates <tt>this</tt> CATCurve by computing a third derivative from a CATCrvParam.
  * <p>The CATCurve::Eval signature with the CATCrvEvalCommand::EvalThirdDeriv argument
  * should be preferred over CATCurve::EvalThirdDeriv as CATCurve::EvalThirdDeriv
  * can lead to bad performances when it is used intensively. 
  * @param iParam
  * The parameter of the vector to evaluate.
  * @return CATMathVector 
  * The CATMathVector which has iParam as its parameter.  
  */
  virtual CATMathVector EvalThirdDeriv(const CATCrvParam & iParam) const =0;
    /** @nodoc */
  virtual void Eval(const CATCrvLimits & box,
		    CATEvalCommand command,
		    CATMathSetOfPoints *& point,
		    CATMathSetOfVectors *& dw,
		    CATMathSetOfVectors *& dw2) const =0;
 /**
 * Sets a global parameter on a CATCurve from a local parameter and
 * an arc number. This API can lead to bad performances when it is used intensively. 
 * <p>The CATCurve::CreateParam signature which returns a void (see above) 
 * should be preferred over the present signature.
 * @param iLocal
 * The value of the local parameter.
 * @param iArc
 * The arc number.
 * @return
 * The corresponding parameter on <tt>this</tt>, valuated with <tt>iGlobalParam</tt>.
 */ 
  virtual CATCrvParam CreateParam(const double & iLocal, const CATLONG32 & iArc) const =0;
  /**
 * Sets a global parameter on <tt>this</tt> CATCurve.
 * This API can lead to bad performances when it is used intensively. 
 * <p>The CATCurve::CreateParam signature which returns a void (see above) 
 * should be preferred over the present signature.
 * @param iGlobalParam
 * The value of the global parameter.
 * @return ioParam
 * The corresponding parameter on <tt>this</tt>, valuated with <tt>iGlobalParam</tt>.
 */
  virtual CATCrvParam CreateParam(const double & iGlobalParam) const =0;
  /**
 * Returns the limitations of <tt>this</tt> CATCurve.
 * The CATCurve::GetLimits signature which returns a void should be preferred 
 * over the present API.
 * @return
 * The current limitations.
 */
  virtual CATCrvLimits GetLimits() const =0;
 /**
 * Returns the maximum limitations of <tt>this</tt> CATCurve.
 * The CATCurve::GetMaxLimits signature which returns a void should be preferred 
 * over the present API.
 * @return
 * The current limitations.
 */
  virtual CATCrvLimits GetMaxLimits() const = 0 ;
    /** @nodoc */
  virtual CATCrvLimits GetInternalMaxLimits(const CATLONG32 iArc) const =0;
    /** @nodoc */
  virtual CATCrvLimits GetInternalLimits(const CATLONG32 iArc) const =0;
  /**
 * Returns the low current limitation of <tt>this</tt> CATCurve.
 * The CATCurve::GetStartLimit signature which returns a void should be preferred 
 * over the present API.
 * @return
 * The start limitation.
 */
  virtual CATCrvParam GetStartLimit() const =0;
  /**
 * Returns the high current limitation of <tt>this</tt> CATCurve.
 * The CATCurve::GetEndLimit signature which returns a void should be preferred 
 * over the present API.
 * @return
 * The end limitation.
 */
  virtual CATCrvParam GetEndLimit() const =0;
    /** @nodoc */
  virtual CATMathBox GetInternalMaxBoundingBox(const CATLONG32 iArc) const = 0 ;
    /** @nodoc */
  virtual CATMathBox GetInternalBoundingBox(const CATLONG32 iArc) const = 0;
    /** @nodoc */
  virtual void OpenEquation () const=0;
    /** @nodoc */
  virtual void CloseEquation () const=0;
	 /**
 * @nodoc
 * converts the internal parameter W to the naturel parameter W for implicit curves. 
 * For example, the natural parameter of a circle is the angle.
 */
	virtual double GetNaturalParamFromParam(const CATCrvParam &iParam) const=0;
	/**
 * @nodoc
 * converts the natural parameter W to the internal parameter W for implicit curves. 
 */
	virtual void GetParamFromNaturalParam(double iNatural, CATCrvParam &oParam) const=0;

 /**
  * @nodoc
  * @return 0 on success, negative number upon error
  */
  virtual int GetAdvancedBox(const CATCrvLimits &iLimits, CATMathAdvancedBox &ioBox) const = 0;

/** @nodoc */
  virtual void PropagateQuery(CATICGMUnknown *iFrom, const CATCrvLimits & iLimits, CATCGMQueryManager &iQuery ) = 0;
};
CATDeclareHandler(CATCurve,CATGeometry);

#endif
