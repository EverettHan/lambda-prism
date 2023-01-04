#ifndef CATPlane_h
#define CATPlane_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATBaseUnknown.h"
#include "CATSurface.h"
class CATMathPlane ;
class CATMathPoint ;
class CATSurParam ;
class CATMathDirection ;
#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATPlane ;
#else
extern "C" const IID IID_CATPlane ;
#endif

/**
 * Interface representing a geometrical plane.
 *<br> The CATPlane is created by the <tt>CreatePlane</tt>
 * method of the <tt>CATGeoFactory</tt> interface
 * and deleted with the <tt>Remove</tt> method.
 *<br>A CATPlane is defined with:
 *<table>
 * <tr><td>CATMathPoint</td><td><tt> Origin </tt></td>
 *                <td> The plane origin </td></tr>
 * <tr><td>CATMathDirection</td><td><tt> FirstDirection </tt></td>
 *                <td> The first normalized direction           </td></tr>
 * <tr><td>CATMathDirection</td><td><tt> SecondDirection </tt></td>
 *                 <td> The second normalized direction, othogonal to the
 *first one</td></tr>
 * <tr><td>CATSurLimits</td><td><tt> Limits </tt></td>
 *                 <td> The limitations if needed</td></tr>
 *</table>
 */
class ExportedByCATGMGeometricInterfaces CATPlane : public CATSurface
{
  CATDeclareInterface;

public:
/**
 * Retrieves the mathematical plane representing <tt>this</tt> CATPlane.
 * @param ioMathPlane
 * The corresponding mathematical definition.
 */
  virtual void GetAxis(CATMathPlane &ioMathPlane) const = 0 ;

/**
 * Retrieves the origin and the two orthonormalized directions of <tt>this</tt> CATPlane.
 * @param ioOrigin
 * The origin.
 * @param ioFirstDirection
 * The first normalized direction.
 * @param ioSecondDirection
 * The second orhto-normalized direction.
 */
  virtual void GetAxis(CATMathPoint       &ioOrigin,
			 CATMathDirection &ioFirstDirection ,
			 CATMathDirection &ioSecondDirection ) const = 0 ;

/**
 * Retrieves the origin and the normal of <tt>this</tt> CATPlane.
 * @param ioOrigin
 * The origin.
 * @param ioNormal
 * The normal.
 */
  virtual void GetNormal(CATMathPoint  &ioOrigin ,
			 CATMathVector &ioNormal) const = 0 ;

/**
 * Modifies the characteristics of <tt>this</tt> CATPlane.
 * @param iPlaneToCopy
 * The new mathematical definition.
 */
  virtual void SetAxis(const CATMathPlane &iPlaneToCopy) = 0 ;



/**
 * Retrieves the mathematical plane representing <tt>this</tt> CATPlane.
 * Use preferably the signature which returns the CATMathPlane in output argument.
 * @return
 * The corresponding mathematical definition.
 */
  virtual CATMathPlane GetAxis()const = 0 ;


};
  CATDeclareHandler(CATPlane,CATSurface);

#endif
