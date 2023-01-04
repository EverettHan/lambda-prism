#ifndef CATLine_h
#define CATLine_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATBaseUnknown.h"
#include "CATCurve.h"
#include "CATMathPoint.h"    
#include "CATMathDirection.h" 

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATLine ;
#else
extern "C" const IID IID_CATLine ;
#endif

//CAA_Exposed  CATIGemLine
/** 
 * Interface representing a geometric 3D line.
 *<br>A CATLine is created by the <tt>CreateLine</tt> method of the
 * <tt>CATGeoFactory</tt> interface and deleted with the <tt>Remove</tt> method. 
 * A line is defined with: 
 *<table>
 * <tr><td>CATMathPoint</td><td><tt> O </tt></td>
 *                   <td> The origin point </td></tr>
 * <tr><td>CATMathDirection</td><td><tt> U </tt></td>
 *                   <td> The direction</td></tr>
 * <tr><td>CATCrvParam</td><td><tt> iStart</tt></td>
 *                   <td> The low limitation</td></tr>
 * <tr><td>CATCrvParam</td><td><tt> iEnd</tt></td>
 *                   <td> The high limitation</td></tr>
 *</table>  
 */
class ExportedByCATGMGeometricInterfaces CATLine : public CATCurve
{
  CATDeclareInterface;

public:

/**
 * Retrieves the origin of <tt>this</tt> CATLine.
 * @param ioOrigin
 * The origin.
 */
  virtual void GetOrigin(CATMathPoint &ioOrigin) const =0;

/**
 * Retrieves the direction of <tt>this</tt> CATLine.
 * @param ioDirection
 * The direction.
 */
  virtual void GetDirection(CATMathDirection &ioDirection) const =0;

 
/**
 * Defines limitations on <tt>this</tt> CATLine.
 * @param iSegmentLimit1
 * The first limitation.
 * @param iSegmentLimit2
 * The end limitation.
 */
  virtual void Set( const CATMathPoint & iSegmentLimit1,
	                const CATMathPoint & iSegmentLimit2 ) =0; 

/**
 * Modifies the origin and the direction of <tt>this</tt> CATLine.
 * @param iNewOrigin
 * The new origin.
 * @param iNewDirection
 * The new direction.
 */
  virtual void Set( const CATMathPoint & iNewOrigin, 
	                const CATMathDirection & iNewDirection) =0;

//CAA_Exposed
/**
 * Modifies the origin of <tt>this</tt> CATLine.
 * @param iNewOrigin
 * The new origin.
 */
  virtual void SetOrigin(const CATMathPoint &iNewOrigin) =0;

/**
 * Modifies the direction of <tt>this</tt> CATLine.
 * @param iNewDirection
 * The new direction.
 */
  virtual void SetDirection(const CATMathDirection &iNewDirection) =0;


/**
 * Retrieves the origin of <tt>this</tt> CATLine.
 * The signature which returns the CATMathPoint in output argument should be
 * preferably used.
 * @return
 * The origin.
 */
  virtual CATMathPoint GetOrigin() const =0;

/**
 * Retrieves the direction of <tt>this</tt> CATLine.
 * The signature which returns the CATMathDirection in output argument should be
 * preferably used.
 * @return
 * The origin.
 */
  virtual CATMathDirection GetDirection() const =0;
};
  CATDeclareHandler(CATLine,CATCurve);

#endif
