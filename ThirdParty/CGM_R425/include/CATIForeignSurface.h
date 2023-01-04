#ifndef CATIForeignSurface_h
#define CATIForeignSurface_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATSurface.h"
#include "CATBooleanDef.h"
#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATIForeignSurface ;
#else
extern "C" const IID IID_CATIForeignSurface ;
#endif
class CATForeignSurfaceData;
class CATMathVector2D;

/**
 * Interface representing the  foreign bi-parameterized
 * geometric elements. 
 * <br>A foreign surface is introduced into CGM by filling the CATIForeignSurface object data
 * with a CATForeignSurfaceData. Then, it is automatically integrated into CGM, and
 * can be used as any CATSurface by the operators and the topology.
 * To create your own surface type, you have to derive the CATForeignSurfaceData
 * class, and re-write the methods that are associated with.
 * <br> A CATIForeignSurface object is create through the method 
 *<tt>CATGeoFactory::CreateForeignSurface</tt> and deleted with the <tt>Remove</tt> method.
 * @see CATForeignSurfaceData
 */
class ExportedByCATGMGeometricInterfaces CATIForeignSurface : public CATSurface
{
  CATDeclareInterface;

public:
/**
 * Retrieves a pointer to the data of <tt>this</tt> CATIForeignSurface.
 * @return
 * A pointer to the data. As part of the CATIForeignSurface, it must not be deleted. 
 */
  virtual CATForeignSurfaceData * GetData() const = 0;

/**
 * Changes the maximum limitations of <tt>this</tt> CATIForeignSurface.
 * @param iRequiredParamExtension
 * The value of the extension.
 * <ul>
 * <li>if <tt>iRequiredParamExtension.GetX() > 0</tt>, Umax is expected to increase by this value,
 * <li>if <tt>iRequiredParamExtension.GetY() < 0 </tt>, Vmin is expected to decrease,
 * <li>if null, no change is required in the related direction.
 * </ul>
 * @param ioActualExtension
 * If <tt>ioActualExtension</tt> is NULL, no information on actual extrapolation is required.
 */
  virtual CATBoolean Extrapolate(const CATMathVector2D & iRequiredParamExtension,
                                       CATMathVector2D * ioActualExtension = NULL  ) = 0 ;


};
  
CATDeclareHandler(CATIForeignSurface,CATSurface);

#endif
