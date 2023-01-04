#ifndef CATIForeignPCurve_h
#define CATIForeignPCurve_h

// COPYRIGHT DASSAULT SYSTEMES 1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */

#include "CATPCurve.h"
#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATIForeignPCurve ;
#else
extern "C" const IID IID_CATIForeignPCurve ;
#endif

class CATForeignPCurveData;

/**
 * Interface representing the class of the foreign mono-parameterized
 * geometric elements in surface parametric space. 
 * <br>A foreign PCurve is introduced into CGM by filling the CATIForeignPCurve object data
 * with a CATForeignPCurveData. Then, it is automatically integrated into CGM, and
 * can be used as any CATCurve by the operators and the topology.
 * To create your own Curve class, you have to derive the CATForeignPCurveData
 * class, and re-write the methods that are associated with.
 * <br> A CATIForeignPCurve object is create through the method @href CATGeoFactory#CreateForeignPCurve .
 * @see CATForeignPCurveData
 */
class ExportedByCATGMGeometricInterfaces CATIForeignPCurve : public CATPCurve
{
  CATDeclareInterface;

public:
/**
 * Retrieves a pointer to the data of <tt>this</tt> CATIForeignPCurve.
 * @return
 * The pointer to the data of <tt>this</tt> foreign PCurve.
 */
  virtual CATForeignPCurveData * GetData() const = 0;

};
  
CATDeclareHandler(CATIForeignPCurve,CATPCurve);

#endif
