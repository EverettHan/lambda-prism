#ifndef CATPoint_h
#define CATPoint_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATBaseUnknown.h"

#include "CATGeometry.h"

#include "CATMathDef.h"
class CATMathPoint ;

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATPoint ;
#else
extern "C" const IID IID_CATPoint ;
#endif

 
// CAA_Exposed CATIGemPoint
/**
 * Base interface for all the geometric point.
 */ 
class ExportedByCATGMGeometricInterfaces CATPoint : public CATGeometry
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
 * Retrieves the three cartesian coordinates of a geometric point.
 * @param ioFirstCoord
 * The first coordinate.
 * @param ioSecondCoord
 * The second coordinate.
 * @param ioThirdCoord
 * The third coordinate.
 */
  virtual void GetCoord(double & ioFisrtCoord,
			double & ioSecondCoord,
			double & ioThirdCoord ) const =0;

    //CAA_Exposed 
/**
 * Returns the first cartesian coordinate of <tt>this</tt> geometric point.
 * @return
 * The first coordinate
 */
  virtual double GetX()const =0;

  //CAA_Exposed 
  /**
 * Returns the second cartesian coordinate of <tt>this</tt> geometric point.
 * @return
 * The second coordinate
 */
  virtual double GetY()const =0;

  //CAA_Exposed 
  /**
 * Returns the third cartesian coordinate of <tt>this</tt> geometric point.
 * @return
 * The third coordinate
 */
  virtual double GetZ()const =0;

  //CAA_Exposed 
  /**
 * Returns <tt>this</tt> geometric point as a CATMathPoint.
 * @param ioPoint
 * The corresponding mathematical point.
 */
  virtual  void GetMathPoint(CATMathPoint & ioPoint)const =0;





  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/** @nodoc */
  virtual CATMathPoint GetMathPoint()const =0;


/** @nodoc */
  virtual void PropagateQuery(CATICGMUnknown *iFrom, CATCGMQueryManager &iQuery ) = 0;

};

  CATDeclareHandler(CATPoint,CATGeometry);

#endif
