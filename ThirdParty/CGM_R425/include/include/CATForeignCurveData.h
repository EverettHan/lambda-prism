#ifndef CATForeignCurveData_H
#define CATForeignCurveData_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U2
 */ 

#include "YP00IMPL.h"
#include "CATForeignGeometryData.h"


class CATCrvParam;
class CATCrvEvalCommand;
class CATCrvEvalResult;
class CATCrvEvalLocal;
class CATCrvLimits;
class CATMathTransformation;
class CATMathTransformation1D;
class CATCurve;
class CATKnotVector;
class CATMathPoint;
class CATMathFunctionX;
class CATMathCurve;
class CATSurParamReference;

#include "CATCurve.h"
/**
 * Base class of the attributes defining the data of a foreign curve.
 *<br>A foreign curve is introduced into CGM by filling the CATIForeignCurve object data
 * with a CATForeignCurveData. Then, it is automatically integrated into CGM, and
 * can be used as any CATCurve by the operators and the topology.
 * To create your own curve type, you have to derive the CATForeignCurveData
 * class, and re-write the methods that are associated with.
 */
class ExportedByYP00IMPL CATForeignCurveData : public CATForeignGeometryData
{
  public :
/** @nodoc */
  CATCGMDeclareAttribute (CATForeignCurveData,CATForeignGeometryData);
/**
 * Evaluates a CATIForeignCurve and its derivatives.
 * @param iPoint
 * The parameter of the point to evaluate.
 * @param iCommand
 * The type of evaluation.
 * @param ioResult.
 * The object containing the results.
 */
  virtual void Eval(const CATCrvParam       & iPoint,
                    const CATCrvEvalCommand & iCommand,
                          CATCrvEvalLocal   & ioResult) const ;
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
                    const CATLONG32           iNbOfPoints      ,
                    const CATCrvEvalCommand & iCommand         ,
                          CATCrvEvalResult  & ioResult         ) const ;

/**
 * Returns the knot vector associated with a CATIForeignCurve.
 * @return
 * The knot vector.
 */
  virtual const CATKnotVector * GetKnotVector() const = 0 ;

/**
 * Modifies the limitations of a CATIForeignCurve.
 * @param iLimits
 * The new current limitations.
 */
  virtual void SetLimits   (const CATCrvLimits & iCurrentLimits) = 0 ;

/**
 * Returns the limitations of a CATIForeignCurve.
 * @param ioCurrentLimits
 * The current limitations.
 */
  virtual void GetLimits   (      CATCrvLimits & ioCurrentLimits) const = 0 ;

/**
 * Returns the maximum limitations of a CATIForeignCurve.
 *<br>This does not take into account the current limitations of the
 * curve. This maximum
 * limits can be the creation limits or the limits that are obtained by 
 * extrapolation, depending on the types of geometric objects.
 * @param ioMaxLimits
 * The maximum limits.
 */
  virtual void GetMaxLimits(      CATCrvLimits & ioMaxLimits) const = 0 ;

/**
 * Returns the limitations of an arc of a CATIForeignCurve.
 *<br>This does not take into account the current limitations of the
 * curve.
 * @param iArc
 * The arc number.
 * @param ioInternalMaxLimits
 * The corresponding limitations.
 */
  virtual void GetInternalMaxLimits(const CATLONG32 iArc, CATCrvLimits & ioInternalMaxLimits) const = 0 ;

/**
 * Returns the limitations of an arc of a CATIForeignCurve.
 *<br>This takes into account the current limitations of the
 * curve.
 * @param iArc
 * The arc number.
 * @param ioInternalMaxLimits
 * The corresponding limitations.
 */
  virtual void GetInternalLimits(const CATLONG32 iArc, CATCrvLimits & ioInternalLimits) const = 0 ;

/**
 * Tests whether a CATIForeignCurve is periodic.
 *<br>This method does not take into account the current limitations of 
 * the curve.
 * @return
 * The result of the test.
 * <br><b>Legal values:</b>:
 *<dl> <dt><tt>0</tt> <dd>If the CATIForeignCurve is not periodic.
 *     <dt><tt>1</tt> <dd>If the CATIForeignCurve is periodic.  </dl>
 */
  virtual CATBoolean IsPeriodic() const = 0 ;

/**
 * Tests whether a CATIForeignCurve is invariant.
 *<br>This method does not take into account the current limitations of 
 * the curve.
 * @param oTransfo1D
 * The 1D-transformation defining the change of parametrization between 
 * the CATIForeignCurve and the transformation of
 * <tt>this</tt>. If <tt>NULL</tt>, this argument is not set.
 * @return
 * The result of the test.
 * <br><b>Legal values:</b>:
 *<dl> <dt><tt>1</tt> <dd>If the transformation of the CATIForeignCurve is geometrically the same as itself.
 *     <dt><tt>0</tt> <dd>Otherwise.</dl>
 */
  virtual CATBoolean IsInvariant(const CATMathTransformation   & iTransfo   ,
                                       CATMathTransformation1D*  oTransfo1D = NULL) const ;
/**
 * Tests whether a CATIForeignCurve is confused with another curve.
 *<br>This method does not take into account the current limitations of 
 * the curves.
 * @param oTransfo1D
 * The 1D-transformation defining the change of parametrization between the transformation of 
 * the CATIForeignCurve and <tt>iTCurve</tt>. If <tt>NULL</tt>, this argument is not set.
 * @return
 * The result of the test.
 * <br><b>Legal values:</b>:
 *<dl> <dt><tt>1</tt> <dd>If the transformation of the CATIForeignCurve is geometrically the same as <tt>iTCurve</tt>.
 *     <dt><tt>0</tt> <dd>Otherwise.</dl>
 */
  virtual CATBoolean IsConfused(const CATMathTransformation   & iTransfo   ,
                                const CATCurve                * iTCurve    ,
                                      CATMathTransformation1D * oTransfo1D ) const = 0 ;

/**
 * Returns a pointer to the mathematical representation of <tt>this</tt> CATCurve.
 *<br> The CATMathCurve . 
 * @return 
 * The associated mathematical curve, that belongs to this CATCurve.If the
 * mathematical representation does not exist, the method returns a
 *<tt>NULL</tt> pointer.
 */
  virtual CATMathCurve* GetMathCurve() const ;
/**
 * Tests whether a CATIForeignCurve has a mathematical representation.
 * @return
 * The result of the test.
 * <br><b>Legal values:</b>:
 *<dl> <dt><tt>1</tt> <dd>If a CATIForeignCurve has a mathematical representation.
 *     <dt><tt>0</tt> <dd>Otherwise.</dl>
 */ 
  virtual CATBoolean HasMathCurve() const ;

/**
 * Retrieves the CATCrvParam on a CATIForeignCurve corresponding to a given CATMathPoint.
 * <br>This transformation is only available
 * on canonical objects such as planes, lines, conics.
 * @param iPoint
 * The CATMathPoint which coordinates are to be transformed as CATCrvParam.
 * @param ioParam
 * The first corresponding CATCrvParam on the curve. 
 * @return
 * The diagnosis of the number of parameters that can be evaluated on this point.
 */
  virtual CATCurve::CATSolutionDiagnostic GetParam(const CATMathPoint & iPoint ,
                                                         CATCrvParam  & ioParam) const ;
  
/**
 * Retrieves the CATCrvParam on a CATIForeignCurve corresponding to a CATMathPoint
 * inside limitations.
 *<br>This transformation is only available
 * on canonical objects such as lines and conics.
 * @param iPoint
 * The CATMathPoint whose coordinates are to be transformed as a CATCrvParam.
 * @param ioParam
 * The first corresponding CATCrvParam on the curve.
 * @param iInside
 * The CATCrvLimits to take into account for trimming the curve.
 * @return
 * The diagnosis of the number of parameters that can be evaluated on this point.
 */
    virtual CATCurve::CATSolutionDiagnostic GetParam(const CATMathPoint & iPoint   ,
                                                           CATCrvParam  & ioParam  ,
                                                     const CATCrvLimits & iInside  ) const ;

/**
 * Retrieves the mathematical equation associated with an arc of
 * a CATIForeignCurve.
 * <br>The retrieved equations are created by the method, and must not be deleted,
 * as part of the object.
 * @param iIndex
 * The arc number.
 * @param oFx
 * A pointer to the equation of the first coordinate <tt>X=oFx(w)</tt>.
 * @param oFy
 * A pointer to the equation of the second coordinate <tt>Y=oFy(w)</tt>.
 * @param oFz
 * A pointer to the equation of the third coordinate <tt>Z=oFy(w)</tt>.
 */
  virtual void CreateLocalEquation(const CATLONG32            iIndex,
                                   const CATMathFunctionX * & oFx   ,
                                   const CATMathFunctionX * & oFy   ,
                                   const CATMathFunctionX * & oFz   ) = 0 ;

/**
 * @nodoc
 * Returns a pointer to the reference of a CATIForeignCurve.
 * @return
 * The pointer to the reference of the curve that has <tt>this</tt> CATForeignCurveData.
 */
  const CATCrvParamReference* GetParamReference() const;

/**
 * Default constructor.
 */
           CATForeignCurveData() ;
  virtual ~CATForeignCurveData() ;

  /** @nodoc */
  CATCrvParamReference* _ParamReference ;

};

#endif
