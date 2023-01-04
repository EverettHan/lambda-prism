#ifndef CATMathCircleArc2D_h
#define CATMathCircleArc2D_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 


#include "CATErrorDef.h"
#include "CATMathematics.h"

#include "CATTolerance.h"
#include "CATMathDef.h"
#include "CATMathPoint2D.h"
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

/**
 * Class representing an arc of a circle.
 *<br>It is defined by a CATMathPoint (<tt>Center</tt>), a CATMathLength
 *(<tt>Radius</tt>) and 2 angles (<tt>StartAngle</tt> and
 *<tt>EndAngle</tt>). The angles are expressed in radians and
 *<br><tt> 0 < StartAngle < CAT2PI ,
 * StartAngle < EndAngle < StartAngle + CAT2PI</tt>. 
 */
class ExportedByCATMathematics CATMathCircleArc2D
{
public:
//======================================================================
//  CONSTRUCTORS AND DESTRUCTOR
//======================================================================
/**
 * Constructs an empty CATMathCircleArc2D without valued data.
 *<br>This is mainly used for array creation. The use of an empty
 * CATMathCircleArc2D leads to an exception, except for the IsEmpty
 * method.
 */
  CATMathCircleArc2D();
 
/** 
 * @ deprecated V5R20 Set
 * Constructs a CATMathCircleArc2D from 3 CATMathPoint.
 *<br>The circle is limited by the first and  third points, without order.
 * The program defines itself the corresponding <tt>StartAngle</tt> and
 * <tt>EndAngle</tt>. 
 * The second point belongs to the CATMathCircleArc2D. <br>
 * This constructor produces an error when the iLimit and iMiddle points are  
 * coincident. When iLimit and iOtherLimit are coincident, an arc whose 
 * diameter ends are iLimit and iOtherLimit is constructed.
 */
  CATMathCircleArc2D(const CATMathPoint2D & iLimit, 
                     const CATMathPoint2D & iMiddle, 
                     const CATMathPoint2D & iOtherLimit ) ;

  //======================================================================
  // Get/set
  //======================================================================

/** 
 * Modifies  <tt>this</tt> CATMathCircleArc2D by 3 CATMathPoint.
 *<br>The circle is limited by the first and  third points, without order.
 * The program defines itself the corresponding <tt>StartAngle</tt> and
 * <tt>EndAngle</tt>. 
 * The second point belongs to the CATMathCircleArc2D. <br>
 * This constructor produces an error when the iLimit and iMiddle points are  
 * coincident. When iLimit and iOtherLimit are coincident, an arc whose 
 * diameter ends are iLimit and iOtherLimit is constructed.
 * @return <tt>E_FAIL</tt> if t the iLimit and iMiddle points are  coincident (an arc whose 
 * diameter ends are iLimit and iOtherLimit is constructed), <tt>S_OK</tt> otherwise.
 */
  HRESULT           Set          (const CATTolerance   & iTolObject  ,
                                  const CATMathPoint2D & iLimit      ,
                                  const CATMathPoint2D & iMiddle     ,
                                  const CATMathPoint2D & iOtherLimit ) ;

 /**
 * @nodoc
 * @deprecated V5R25 Set with CATTolerance object (XScale compliant)
 */
  HRESULT           Set          (const CATMathPoint2D & iLimit      ,
                                  const CATMathPoint2D & iMiddle     ,
                                  const CATMathPoint2D & iOtherLimit ) ;


/**
 * Returns <tt>0</tt> if the data of <tt>this</tt> CATMathCircleArc2D are valuated.
 */
  short             IsEmpty      ()                          const ;

/**
 * Returns the center of <tt>this</tt> CATMathCircleArc2D.
 */
  void              GetCenter    (CATMathPoint2D & ioOrigin) const ;

/**
 * Returns the radius of <tt>this</tt> CATMathCircleArc2D.
 */
  CATPositiveLength GetRadius    ()                          const ;

/**
 * Returns the first limiting angle of <tt>this</tt> CATMathCircleArc2D in radian.
 */
  CATAngle          GetStartAngle()                          const ;

/**
 * Returns the last limiting angle of <tt>this</tt> CATMathCircleArc2D in radian.
 */
  CATAngle          GetEndAngle  ()                          const ;

  //======================================================================
  // For Debug
  //======================================================================

  /**
  * @nodoc
  * @deprecated V5R20 GetCenter
  * Use the  signature which returns a CATMathPoint2D as an output argument.
  */
  CATMathPoint2D    GetCenter    ()                          const ;


/**
 * @nodoc
 * @deprecated V5R20.
 */
  friend ExportedByCATMathematics ostream& operator << (ostream& s,
                                                  const CATMathCircleArc2D & iCircleArc);

  //======================================================================
  // INTERNAL DATA
  //======================================================================

private:

  CATMathPoint2D    _Center ;
  CATPositiveLength _Radius ;
  CATAngle          _Start  ;
  CATAngle          _End    ;
  short             _Empty  ;

};

#endif
