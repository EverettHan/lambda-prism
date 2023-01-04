#ifndef CATForeignPCurveData_H
#define CATForeignPCurveData_H

// COPYRIGHT DASSAULT SYSTEMES  2000

/**
 * @CAA2Level L1
 * @CAA2Usage U2
 */ 

#include "CATGeometricObjects.h"                        
#include "CATForeignGeometryData.h"  
#include "CATBoolean.h"                               

class CATSurParam;
class CATMathVector2D;
class CATMathTransformation2D;
class CATMathTransformation1D;
class CATMathTransformation;
class CATKnotVector;
class CATCrvLimits;
class CATCrvParam;
class CATCurve;
class CATCrvParamReference;
class CATMathFunctionX;
class CATCrvEvalCommand;

/**
 * Base class of the attributes defining the data of a foreign Pcurve.
 *<br>A foreign Pcurve is introduced into CGM by filling the CATIForeignPCurve object data
 * with a CATForeignPCurveData. Then, it is automatically integrated into CGM, and
 * can be used as any CATPCurve by the operators and the topology.
 * To create your own curve type, you have to derive the CATForeignPCurveData
 * class, and re-write the methods that are associated with.
 */
//class ExportedByCATGeometricObjects CATForeignPCurveData : public CATForeignCurveData
class ExportedByCATGeometricObjects CATForeignPCurveData : public CATForeignGeometryData
{
  public :
/** @nodoc */
  CATCGMDeclareAttribute (CATForeignPCurveData,CATForeignGeometryData);

/**
 * Retrieves the knot vector associated with a CATIForeignPCurve.
 * @return
 * The knot vector.
 */
   virtual const CATKnotVector * GetKnotVector() const = 0 ;

/**
 * Modifies the limitations of a CATIForeignPCurve.
 * @param iLimits
 * The new current limitations.
 */
   virtual void SetLimits(const CATCrvLimits & iLimits) = 0 ;

/**
 * Retrieves the limitations of a CATIForeignPCurve.
 * @param ioLimits
 * The current limitations.
 */
   virtual void GetLimits(CATCrvLimits & ioLimits) const = 0 ;

/**
 * Retrieves the maximum limitations of a CATIForeignPCurve.
 *<br>This does not take into account the current limitations of the
 * curve. This maximum
 * limits can be the creation limits or the limits that are obtained by 
 * extrapolation, depending on the types of geometric objects.
 * @param ioMaxLimits
 * The maximum limits.
 */
   virtual void GetMaxLimits(CATCrvLimits & ioMaxLimits) const = 0 ;

/**
 * Retrieves the limitations of an arc of a CATIForeignPCurve.
 *<br>This does not take into account the current limitations of the
 * curve.
 * @param iArc
 * The arc number.
 * @param ioInternalMaxLimits
 * The corresponding limitations.
 */
  virtual void GetInternalMaxLimits(const CATLONG32 iArc, CATCrvLimits & ioInternalMaxLimits) const = 0 ;

/**
 * Retrieves the limitations of an arc of a CATIForeignPCurve.
 *<br>This takes into account the current limitations of the
 * curve.
 * @param iArc
 * The arc number.
 * @param ioInternalLimits
 * The corresponding limitations.
 */
   virtual void GetInternalLimits(const CATLONG32 iArc, CATCrvLimits & ioInternalLimits) const = 0 ;

/**
 * Tests whether a CATIForeignPCurve is periodic.
 *<br>This method does not take into account the current limitations of 
 * the curve.
 * @return
 * The result of the test.
 * <br><b>Legal values:</b>:
 *<dl> <dt><tt>0</tt> <dd>If the CATIForeignPCurve is not periodic.
 *     <dt><tt>1</tt> <dd>If the CATIForeignPCurve is periodic.  </dl>
 */
   virtual CATBoolean IsPeriodic() const = 0 ;

/**
 * Tests whether a CATIForeignPCurve is invariant for a given CATMathTransformation.
 *<br>This method does not take into account the current limitations of 
 * the curve.
 * @param iTransfo
 * The transformation.
 * @param ioTransfo1D
 * The 1D-transformation defining the change of parameterization between 
 * the CATIForeignPCurve and the transformation of
 * <tt>this</tt>. If <tt>NULL</tt>, this argument is not set.
 * @return
 * The result of the test.
 * <br><b>Legal values:</b>:
 *<dl> <dt><tt>1</tt> <dd>If the transformation of the CATIForeignPCurve is geometrically the same as itself.
 *     <dt><tt>0</tt> <dd>Otherwise.</dl>
 */
   virtual CATBoolean IsInvariant(const CATMathTransformation & iTransfo,
 			                     CATMathTransformation1D* ioTransfo1D = NULL) const ;
/**
 * Tests whether a CATIForeignPCurve is confused with another curve for a given transformation.
 *<br>This method does not take into account the current limitations of 
 * the curves.
 * @param iTransfo
 * The transformation.
 * @param ioTransfo1D
 * The 1D-transformation defining the change of parameterization between the transformation of 
 * the CATIForeignPCurve and <tt>iTCurve</tt>. If <tt>NULL</tt>, this argument is not set.
 * @return
 * The result of the test.
 * <br><b>Legal values:</b>:
 *<dl> <dt><tt>1</tt> <dd>If the transformation of the CATIForeignPCurve is geometrically the same as <tt>iTCurve</tt>.
 *     <dt><tt>0</tt> <dd>Otherwise.</dl>
 */
   virtual CATBoolean IsConfused(const CATMathTransformation   & iTransfo,
 				                const CATCurve                * iTCurve,
 				                CATMathTransformation1D       * ioTransfo1D ) const = 0 ;


/**
 * Retrieves the mathematical equation associated with an arc of
 * a CATIForeignPCurve on the space of the surface.
 * <br>The retrieved equations are created by the method, and must not be deleted,
 * as part of the object.
 * @param iArcIndex
 * The arc number.
 * @param oFx
 * The pointer to the equation of the first coordinate <tt>U=oFx(w)</tt>.
 * @param oFy
 * The pointer to the equation of the second coordinate <tt>V=oFy(w)</tt>.
 */
 virtual void CreateLocalPEquation( const CATLONG32 iArcIndex, 
		                     const CATMathFunctionX * & oFx, 
		                     const CATMathFunctionX * & oFy) =0;

 /**
  * Transforms <tt>this</tt> CATForeignPCurve with a tranformation in the space of the surface.
  * @param iTransfo2D
  * The 2D transformation to apply.
  * @param oTransfo1D
  * The mapping of parameter if the 2D transformation is reduced to a re-parameterization of the Pcurve.
  */
 virtual void ApplyTransformation2D(const CATMathTransformation2D& iTransfo2D,
				   CATMathTransformation1D* oTransfo1D = NULL)=0;


 /**
 * Applies a geometrical transformation to <tt>this</tt> CATForeignGeometryData. 
 * @param iTransfo
 * The transformation process to be used.
 */
   virtual void           Move3D(CATTransfoManager& iTransfo) ;

/** 
 * Constructs a geometrically transformed copy of <tt>this</tt> CATForeignGeometryData. 
 * <br>Optional method. By default, copies , then transforms.
 * @param iTransfo
 * The transformation process to be used.
 */
  virtual CATGeometry*   CloneAndMove3D(CATTransfoManager& iTransfo) const ;

 /**
 * Retrieves the multi-evaluation of <tt>this</tt> CATIForeignPCurve point on the underlying CATSurface.
 * @param iParam
 * The parameter where to evaluate.
 * @param iCommand
 * The type of evaluation. The corresponding output pointer must be allocated.
 * @param ioPoint
 * The pointer to the resulting CATSurParam.
 * @param ioFirstDeriv 
 * The pointer to the resulting first derivative.
 * @param ioSecondDeriv 
 * The pointer to the resulting second derivative.
 * @param ioThirdDeriv 
 * The pointer to the resulting third derivative.
 */
 virtual void EvalUV(const CATCrvParam &iParam,
		      const CATCrvEvalCommand &iCommand,
		      CATSurParam   *ioPoint,
		      CATMathVector2D *ioFirstDeriv  = NULL,
		      CATMathVector2D *ioSecondDeriv = NULL,
		      CATMathVector2D *ioThirdDeriv  = NULL) const;


/**
 * Default constructor.
 */
  CATForeignPCurveData() ;
  virtual ~CATForeignPCurveData() ;

/**
 * @nodoc
 * Returns a pointer to the reference of a CATIForeignPCurve.
 * @return
 * The pointer to the reference of the curve that has <tt>this</tt> CATForeignPCurveData.
 */
  const CATCrvParamReference* GetParamReference() const;

  private:
        /** @nodoc */
  CATCrvParamReference* _ParamReference ;
};

#endif
