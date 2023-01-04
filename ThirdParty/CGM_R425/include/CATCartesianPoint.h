#ifndef CATCartesianPoint_h
#define CATCartesianPoint_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATBaseUnknown.h"

#include <stdio.h>

#include "CATPoint.h"

#include "CATMathDef.h"

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATCartesianPoint ;
#else
extern "C" const IID IID_CATCartesianPoint ;
#endif

  //CAA_Exposed CATIGemCartesianPoint
/**
 * Interface representing a geometric cartesian point.
 *<br>The CATCartesianPoint is created through the <tt>CreateCartesianPoint</tt>
 * method of the <tt>CATGeoFactory</tt> interface, and deleted with the <tt>Remove</tt> method.
 */
class ExportedByCATGMGeometricInterfaces CATCartesianPoint : public CATPoint
{
  CATDeclareInterface;

public:
    //CAA_Exposed 
/**
 * Modifies the three cartesian coordinates of <tt>this</tt> CATCartesianPoint.
  * @param iFirstCoord
 * The first coordinate.
 * @param iSecondCoord
 * The second coordinate.
 * @param iThirdCoord
 * The third coordinate.
 */
  virtual void SetCoord(double iFirstCoord,
			double iSecondCoord,
			double iThirdCoord)=0;

  //CAA_Exposed 
 /**
 * Modifies the first cartesian coordinate of <tt>this</tt> CATCartesianPoint.
 * @param iFirstCoord
 * The new value of the first coordinate.
 */
  virtual void SetX(double iFirstCoord)=0;

    //CAA_Exposed 
/**
 * Modifies the second cartesian coordinate of <tt>this</tt> CATCartesianPoint.
 * @param iSecondCoord
 * The new value of the second coordinate.
 */
  virtual void SetY(double iSecondCoord)=0;

    //CAA_Exposed 
/**
 * Modifies the third cartesian coordinate of <tt>this</tt> CATCartesianPoint.
 * @param iThirdCoord
 * The vnew value of the third coordinate.
 */
  virtual void SetZ(double iThirdCoord)=0;

};

  CATDeclareHandler(CATCartesianPoint,CATPoint);

#endif
