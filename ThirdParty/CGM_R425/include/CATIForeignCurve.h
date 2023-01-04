#ifndef CATIForeignCurve_h
#define CATIForeignCurve_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATCurve.h"
#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATIForeignCurve ;
#else
extern "C" const IID IID_CATIForeignCurve ;
#endif
class CATForeignCurveData;

/**
 * Interface representing the foreign mono-parameterized
 * geometric elements in 3D space. 
 * <br>A foreign curve is introduced into CGM by filling the CATIForeignCurve object data
 * with a CATForeignCurveData. Then, it is automatically integrated into CGM, and
 * can be used as any CATCurve by the operators and the topology.
 * To create your own curve type, you have to derive the CATForeignCurveData
 * class, and re-write the methods that are associated with.
 * <br> A CATIForeignCurve object is create through the method 
 *<tt>CATGeoFactory::CreateForeignCurve</tt> and deleted with the <tt>Remove</tt> method.
 * @see CATForeignCurveData
 */
class ExportedByCATGMGeometricInterfaces CATIForeignCurve : public CATCurve
{
  CATDeclareInterface;

public:
/**
 * Retrieves a pointer to the data of <tt>this</tt> CATIForeignCurve.
 * @return
 * A pointer to the data. As part of the CATIForeignCurve, it must not be deleted.
 */
  virtual CATForeignCurveData * GetData() const = 0;

};
  
CATDeclareHandler(CATIForeignCurve,CATCurve);

#endif
