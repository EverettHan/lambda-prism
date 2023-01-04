#ifndef CATMacroPoint_h
#define CATMacroPoint_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATPoint.h"
class CATGeometry ;
#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATMacroPoint ;
#else
extern "C" const IID IID_CATMacroPoint ;
#endif

  //CAA_Exposed CATIGemMacroPoint
/**
 * Interface representing a set geometric points to be considered as one point.
 *<br>The CATMacroPoint is created through the <tt>CreateMacroPoint</tt>
 * method of the <tt>CATGeoFactory</tt> interface and deleted with the <tt>Remove</tt> method.
 */
class ExportedByCATGMGeometricInterfaces CATMacroPoint : public CATPoint
{
  CATDeclareInterface;

  public :

  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

  //CAA_Exposed
/**
 * Scans the points included into <tt>this</tt> CATMacroPoint.
 * @param iCurrentSubElement
 * A pointer to a point of <tt>this</tt> CATMacroPoint.
 *<br> Use the NULL pointer to have the first point.
 * @return
 * A pointer to the next point. <tt>NULL</tt> when <tt>iCurrentSubElement</tt>
 * is the last point.
 */
  virtual CATPoint* Next ( CATPoint *iCurrentSubElement ) = 0 ;

    //CAA_Exposed
/**
 * Scans the points of <tt>this</tt> CATMacroPoint lying on a given geometric support.
 * @param iCurrentSubElement
 * A pointer to a point of <tt>this</tt> CATMacroPoint.
 *<br> Use the NULL pointer to have the first point.
 * @param iSupport
 * A pointer to the geometry to which the points must be related.
 * @return
 * A pointer to the next point. <tt>NULL</tt> when <tt>iCurrentSubElement</tt>
 * is the last point.
 */
  virtual CATPoint* Next ( CATPoint *iCurrentSubElement,CATGeometry* iSupport ) = 0 ;

    //CAA_Exposed
/**
 * Adds a new CATPoint into <tt>this</tt> CATMacroPoint.
 * @param iNewSubElement
 * A pointer to the new point to add. If this point already is inside <tt>this</tt> CATMacroPoint,
 * it is nor included again.
 * @return
 * <tt>iNewSubElement</tt>.
 */
  virtual CATPoint* Append ( const CATPoint* iNewSubElement ) = 0 ;

    //CAA_Exposed
/**
 * Removes a CATPoint from <tt> CATMacroPoint</tt>.
 * A pointer to the point to remove.
 */
  virtual void Remove ( CATPoint* iSubElement ) = 0 ;


  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/**
  * @nodoc
  * Tests whether a point is included into <tt>this</tt> CATMacroPoint.
  * @param iSubElement
  * A pointer to a point.
  * @return
  * The result of the test.
  * <br><b>Legal values</b>:
  * <tt>1</tt> if <tt>iSubElement</tt> is included into <tt>this</tt> CATMacroPoint, <tt>0</tt> otherwise.
  */
  virtual CATBoolean IsContaining(const CATPoint* iSubElement) const = 0;

};

CATDeclareHandler(CATMacroPoint,CATPoint);

#endif
