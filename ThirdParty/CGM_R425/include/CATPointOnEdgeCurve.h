#ifndef CATPointOnEdgeCurve_h
#define CATPointOnEdgeCurve_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 
#include "CATPointOnCurve.h"
#include "CATListOfCATPCurves.h"
#include "CATListOfCATCrvParams.h"

class CATEdgeCurve ;
class CATCurve ;
class CATCrvParam ;
class CATCX_CHECKUP;
class CATPointOnEdgeCurve;

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATPointOnEdgeCurve ;
#else
extern "C" const IID IID_CATPointOnEdgeCurve ;
#endif

  //CAA_Exposed CATIGemPOEC
/**
 * Interface defining a point lying on a CATEdgeCurve.
 * <br><b>Role</b>: A CATPointOnEdgeCurve knows how to map its parameter into the parameter on
 * each curve of the edge curve, even if these parameters have not been already specified.
 * <br>A CATPointOnEdgeCurve is defined with an underlying CATEdgeCurve and
 * a list of parameters on the CATCurves of the CATEdgeCurve. 
 * The parameters can be not specified for some curves. They remain implicit
 * and are evaluated through the <tt>GetEquivalentPoint</tt> method of the
 *<tt>CATEdgeCurve</tt> interface.
 *<br>A CATPointOnEdgeCurve is created through the <tt>CreatePointOnEdgeCurve</tt>
 * method of the <tt>CATGeoFactory</tt> interface and deleted with the <tt>Remove</tt> method.
 */
class ExportedByCATGMGeometricInterfaces CATPointOnEdgeCurve : public CATPointOnCurve
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
 * Replaces all the characteristics of <tt>this</tt> CATPointOnEdgeCurve.
 * @param iNbOfSpecs
 * The number of parameters to specify.
 * @param iSpecCurves[]
 * The array of the pointers to curves of <tt>iSupport</tt>.
 * @param iSpecParams[]
 * The array of the corresponding parameters.
 * @param iSupport
 * The underlying CATEdgeCurve.
 */
  virtual void Set ( const CATLONG32 iNbOfSpecs, 
		     const CATCurve* iSpecCurves[],
		     const CATCrvParam iSpecParams[],
		     const CATEdgeCurve* iSupport ) = 0 ;

	/** @nodoc */
  virtual void CheckPointOnEdgeCurve(double iTol=0., CATCX_CHECKUP* report=0) const=0;

	    //CAA_Exposed
/**
 * Adds a parameter specification on a CATCurve of a CATEdgeCurve.
 *<br>This method replaces the parameter if it was already defined on this CATCurve.
 * @param iCurveInsideEdgeCurve
 * A pointer to a curve of the CATEdgeCurve.
 * @param iNewParam
 * The new parameter on <tt>iCurveInsideEdgeCurve</tt>.
 */
  virtual void SetParamOn (const CATCurve* iCurveInsideEdgeCurve, 
			   const CATCrvParam & iNewParam            ) = 0 ;

    //CAA_Exposed
/**
 * Returns the number of specified parameters in <tt>this</tt> CATPointOnEdgeCurve.
 * @return
 * The number of parameters.
 */
  virtual CATLONG32 GetSpecsCount () const = 0 ;

    //CAA_Exposed
/**
 * Retrieves the specified parameter and its associated CATCurve of <tt>this</tt> CATPointOnEdgeCurve.
 * @param iSpecIndex
 * The index (beginning at 0) of a specified parameter on <tt>this</tt> CATPointOnEdgeCurve.
 * @param ioSpecCurves
 * A pointer to the corresponding curve.
 * @param ioSpecParam
 * The corresponding parameter.
 */
  virtual void GetSpec ( CATLONG32   iSpecIndex,
			 const CATCurve* & ioSpecCurves,
			 CATCrvParam     & ioSpecParams   ) const = 0 ;

    //CAA_Exposed
/**
 * Retrieves the parameter of <tt>this</tt> CATPointOnEdgeCurve related to a given curve inside the CATEdgeCurve.
 *<br> If the parameter was not specified on this CATCurve, the method
 * computes the equivalent parameter.
 * @param iCurveInsideEdgeCurve
 * A pointer to a curve of the CATEdgeCurve.
 * @param ioParamOnCurve
 * The corresponding parameter.
 * @return
 * The computation type of the parameter
 * <br><b>Legal values</b>:
 * 1 if the parameter was already specified, 0 otherwise (use of @href CATCurve#GetEquivalentParam ).
 */
  virtual CATBoolean GetParamOn( const CATCurve* iCurveInsideEdgeCurve, CATCrvParam & ioParamOnCurve ) const = 0 ;





  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/** @nodoc */
  virtual CATCrvParam GetParamOn( const CATCurve* iCurveInsideEdgeCurve ) const = 0 ;

};

CATDeclareHandler(CATPointOnEdgeCurve,CATPointOnCurve);


#endif
