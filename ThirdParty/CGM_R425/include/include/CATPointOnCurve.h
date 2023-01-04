#ifndef CATPointOnCurve_h
#define CATPointOnCurve_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATBaseUnknown.h"
#include "CATPoint.h"
class CATCrvParam ;
class CATCurve ;

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATPointOnCurve ;
#else
extern "C" const IID IID_CATPointOnCurve ;
#endif

/**
 * Interface representing a point lying on curve.
  * <br><b>Role</b>: A CATPointOnCurve can be seen as 1 coordinate (called curve parameter) in the space of
 * the curve.
 *<br>The CATPointOnCurve is created through the <tt>CreatePointOnCurve</tt>
 * method of the <tt>CATGeoFactory</tt> interface and deleted with the <tt>Remove</tt> method.
 */
class ExportedByCATGMGeometricInterfaces CATPointOnCurve : public CATPoint
{
  CATDeclareInterface;

public:
/**
 * Returns the corresponding parameter on the curve.
 * @param oParam
 * The parameter of the curve.
 */
  virtual void GetParam(CATCrvParam & oParam) const = 0;

/**
 * Modifies the parameter of <tt>this</tt> CATPointOnCurve.
 * @param iNewParam
 * The new value of the parameter
 */
  virtual void SetParam( const CATCrvParam & iNewParam )  = 0;

/**
 * Returns the underlying CATCurve of <tt>this</tt> CATPointOnCurve.
 * @return
 * A pointer to the supporting curve.
 */
  virtual CATCurve *GetCurve() const = 0;
 
/**
 * Modifies the underlying CATCurve of <tt>this</tt> CATPointOnCurve.
 * @param iNewSupport
 * A pointer to the new supporting curve.
 */
  virtual void SetCurve( CATCurve* iNewSupport ) = 0;

/**
 * Returns the corresponding parameter on the curve. 
 * User preferably the signature which returns a CATCrvParam in output argument.
 * @return
 * The CATCrvParam
 */
  virtual CATCrvParam GetParam() const = 0;
};

CATDeclareHandler(CATPointOnCurve,CATPoint);

#endif
