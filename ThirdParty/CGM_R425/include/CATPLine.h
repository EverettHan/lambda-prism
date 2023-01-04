#ifndef CATPLine_h
#define CATPLine_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 
#include "CATPCurve.h"
#include "CATIsoParameter.h"                   
class CATSurParam ;
#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATPLine ;
#else
extern "C" const IID IID_CATPLine ;
#endif
	//CAA_Exposed CATIGemPLine
/**
 * Interface representing a line in the space of a surface.
 *<br> The CATPLine is created by the <tt>CreatePLine</tt>
 * method of the <tt>CATGeoFactory</tt> interface and deleted with the <tt>Remove</tt> method. 
 *<br>A CATPLine is defined with:
 *<table>
 * <tr><td>CATSurface</td><td><tt>Sur </tt></td>
 *                 <td> The underlying surface</td></tr>
 * <tr><td>CATMathPoint</td><td><tt> O </tt></td>
 *                   <td> The origin point </td></tr>
 * <tr><td>CATMathDirection</td><td><tt> U </tt></td>
 *                   <td> The direction</td></tr>
 * <tr><td>CATSurParam</td><td><tt> iStart </tt></td>
 *                   <td> The low limitation</td></tr>
 * <tr><td>CATSurParam</td><td><tt> iEnd </tt></td>
 *                   <td> The high limitation</td></tr>
 *</table>  
 */
class ExportedByCATGMGeometricInterfaces CATPLine : public CATPCurve
{
  CATDeclareInterface;

public :
		//CAA_Exposed
/**
 * Tests whether <tt>this</tt> CATPLine is isoparametric.
 * @return
 * The diagnosis of isoparametricity.
 */
  virtual CATIsoParameter IsIsoParametric () const = 0 ;

	//CAA_Exposed
/**
 * Returns the low limitation of a CATPLine.
 * @return
 * The first limitation.
 */
  virtual CATSurParam GetStart () const = 0 ;

  	//CAA_Exposed
/**
 * Returns the high limitation of a CATPLine.
 * @return
 * The end limitation.
 */
  virtual CATSurParam GetEnd () const = 0 ;

  	//CAA_Exposed
/**
 * Modifies the characteristics of a CATPLine.
 * @param iStart
 * The first limitation.
 * @param iEnd
 * The end limitation.
 * @param iSupport
 * A pointer to the underlying surface.
 */
  virtual void Set(const CATSurParam & iStart, 
		   const CATSurParam & iEnd, 
		         CATSurface  * iSupport ) = 0 ;

  	//CAA_Exposed
/**
 * Modifies the low limitation of a CATPLine.
 * @param iStart
 * The first limitation.
 *<br>It may change the direction of the CATPLine.
 */
  virtual void SetStart ( const CATSurParam & iStart ) = 0 ;

  	//CAA_Exposed
/**
 * Modifies the high limitation of a CATPLine.
  * @param iEnd
 * The end limitation.
 *<br>It may change the direction of the CATPLine.
 */
  virtual void SetEnd ( const CATSurParam & iEnd ) = 0 ;

};
  CATDeclareHandler(CATPLine,CATPCurve);

#endif
