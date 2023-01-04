
#ifndef CATMathTransformation2D_H
#define CATMathTransformation2D_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATMathematics.h"

#include "CATMath2x2Matrix.h"
#include "CATMathVector2D.h"
#include "CATMathCircleArc2D.h"
#include "CATMathDef.h"
#include "CATIAV5Level.h"
#include "CATErrorDef.h" //HRESULT

class CATMathAxis2D;
class CATMathLine2D;
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

//#ifdef CATIAV5R11
class CATMathPoint2D;
	/**
 * @nodoc
 */
extern  ExportedByCATMathematics CATMathPoint2D  operator * (
				const CATMathTransformation2D &iTransfo,
				const CATMathPoint2D &iPointToTransfo);
//#endif
/**
 * Class representing a transformation in dimension 2.
 * <br>It is composed of a matrix <tt>Matrix</tt>, 
 * and of a translation <tt>Vector</tt>.
 *<br><tt><table width = 40>
 *    <tr><td> Matrix= </td><td> a11 </td><td> a12 </td>
 *        <td> Vector= </td><td> u1 </td></tr>
 *    <tr><td></td>         <td> a21 </td><td> a22 </td>
 *        <td>         </td><td> u2 </td></tr>
 *        </table></tt>
 * <br>Apply transformations by using the <tt>*</tt> operator.
 * <br>Available transformations are scaling, translation, reflection, 
 * rotation.
 */ 
class ExportedByCATMathematics CATMathTransformation2D
{

 public:

//===========================================================================
//- Constructors
//===========================================================================
/**
 * Constructs an Identity transformation.
 * <br> <tt>Matrix= Identity</tt>, <tt>Vector = (0,0) </tt>
 */
  CATMathTransformation2D();

/**
 * Constructs from a CATMath2x2Matrix and a CATMathVector2D.
 */
  CATMathTransformation2D(const CATMath2x2Matrix & iMatrix,
                                                const CATMathVector2D & iVector);

  /**
 * Constructs a CATMathTansformation2D from a scalar and a CATMathPoint2D.
 * @return
 *   If iType== CATMathScaling
 *     <table>
 *    <tr><td> Matrix= </td><td> iA </td><td> 0 </td>
 *        </tr>
 *    <tr><td>         </td><td> 0  </td><td>iA </td>
 *        </tr>
 *        </table></tt> 
 *   If iType== CATMathRotation, <tt>iA</tt> is in radians.
 *     <table>
 *    <tr><td> Matrix= </td><td> cos(iA) </td><td> -sin(iA) </td>
 *        </tr>
 *    <tr><td>         </td><td> sin(iA)  </td><td> cos(iA) </td>
 *        </tr>
 *        </table></tt> 
 */
  CATMathTransformation2D( const double iA,const CATMathPoint2D & iCenter,
                                                  const CATMathTransfoType iType = CATMathScaling);

/**
 * Constructs a translation.
 */
  CATMathTransformation2D(const CATMathVector2D & iTranslation);

/**
 * Constructs a reflection.
 */
  CATMathTransformation2D(const CATMathLine2D & iReflectLine);


/**
 * Constructs a tranformation of axes systems.
 */
  CATMathTransformation2D(const CATMathAxis2D & iFromAxis, 
                                                 const CATMathAxis2D & iToAxis);

/**
 *  Copy constructor.
 */
  CATMathTransformation2D(const CATMathTransformation2D & iTransfoToCopy);


 /**
 * @deprecated V5R20 Set
  * Constructs theCATMathTransformation2D that transforms 3 2D points
  * into 3 new 2D points.
  * <br> The points must be different.
  * @param iFrom[]
  * The array of the six coordinates <tt>(Point1.x, Point1.y, Point2.x, Point2.y,
  *  Point3.x, Point3.y)</tt> of the initial points.
  * @param iTo[]
  * The array of the six coordinates: <tt>(Result1.x, Result1.y, Result2.x, Result2.y,
  *  Result3.x, Result3.y)</tt>of the resulting points.
  */
  CATMathTransformation2D(const double iFrom[], const double iTo[]);

//===========================================================================
//- Get/Set 
//===========================================================================
/**
  * Modifies the CATMathTransformation2D that transforms 3 2D points
  * into 3 new 2D points.
  * <br> The points must be different.
  * @param iFrom[]
  * The array of the six coordinates <tt>(Point1.x, Point1.y, Point2.x, Point2.y,
  *  Point3.x, Point3.y)</tt> of the initial points.
  * @param iTo[]
  * The array of the six coordinates: <tt>(Result1.x, Result1.y, Result2.x, Result2.y,
  *  Result3.x, Result3.y)</tt>of the resulting points.
  *@return E_FAIL if an error occurs, S_OK otherwise. 
  */
  HRESULT Set(const double iFrom[], const double iTo[]);

  /**
 * Retrieves the coefficients of <tt>this</tt> CATMathTransformation2D in an array[] of doubles.
 * <br>The size of the array is 6. If the matrix is:
 *<br><tt><table width = 40>
 *    <tr><td> iCoeff</td><td> a11 </td><td> a12 </td>
 *        <td> u1 </td></tr>
 *    <tr><td></td>         <td> a21 </td><td> a22 </td>
 *        <td> u2 </td></tr>
 *        </table></tt>
 * the coefficients must be given COLUMN by COLUMN.
 */
  void GetCoef(double iCoef[]) const;

/**
 * Retrieves the coefficients of <tt>this</tt> CATMathTransformation2D in an array[] of doubles.
 * <br>The size of the array is 6. If the matrix is:
 *<br><tt><table width = 40>
 *    <tr><td> iCoeff</td><td> a11 </td><td> a12 </td>
 *        <td> u1 </td></tr>
 *    <tr><td></td>         <td> a21 </td><td> a22 </td>
 *        <td> u2 </td></tr>
 *        </table></tt>
 * the coefficients must be given COLUMN by COLUMN.
 */
  void SetCoef(const double iCoeff[]);

 /**
 * Returns the CATMath2x2Matrix associated with <tt>this</tt> CATMathTransformation2D.
 */
  void GetMatrix(CATMath2x2Matrix & ioMatrix) const;

 /**
  * Sets the matrix of <tt>this</tt> CATMathTransformation2D.
  */
  void SetMatrix(const CATMath2x2Matrix & iMatrix) ;
 /**
  * Sets the vector of <tt>this</tt> CATMathTransformation2D.
  */
  void SetVector(const CATMathVector2D & iVector) ;
 
/**
 * Returns the CATMathVector2D associated with <tt>this</tt> CATMathTransformation2D.
 */
  void GetVector(CATMathVector2D & ioVector) const;


/**
 * Tests whether <tt>this</tt> transformation is an isometry (keeps the distances).
 * @return
 * <dl>
 * <dt><tt>FALSE</tt>        <dd>if it is not an isometry.
 * <dt><tt>TRUE</tt>        <dd>if it is a direct isometry.
 * </dl>
 */
  CATBoolean IsIsometry() const;
/**
 * Tests whether <tt>this</tt> transformation is a similitude (keeps the angles).
 * @return
 * <dl>
 * <dt><tt>FALSE</tt>        <dd>if it is not an similitude.
 * <dt><tt>TRUE</tt>        <dd>if it is a similitude.
 * </dl>
 */
  CATBoolean IsSimilitude() const;
  /**
 * Retrieves the scale of <tt>this</tt> CATMathTransformation2D.
 * @return
 * <dl>
 * <dt><tt>FALSE</tt>        <dd>if it is not an similitude.
 * <dt><tt>TRUE</tt>        <dd>if it is a similitude.
 * </dl>
 */
  CATBoolean IsSimilitude(double & oScale) const;

/**
 * Tests whether <tt>this</tt> transformation is a scaling and retrieves the Origin and 
 * the Scale.
 * @return
 * <dl>
 * <dt><tt>FALSE</tt>        <dd>if it is not a scaling.
 * <dt><tt>TRUE</tt>        <dd>if it is a scaling.
 * </dl>
 */
  CATBoolean IsScaling(CATMathPoint2D & oOrigin, double & oScale) const;

  /**
 * Tests whether <tt>this</tt> transformation is a rotation and retrieves the center and the
 * angle in radians.
 * @return
 * <dl>
 * <dt><tt>FALSE</tt>        <dd>if it is not a rotation.
 * <dt><tt>TRUE</tt>        <dd>if it is a rotation.
 * </dl>
 */
  CATBoolean IsRotation( CATAngle &ioAngle,CATMathPoint2D &ioCenter) const;

/**
 * Tests whether <tt>this</tt> transformation is direct.
 * @return
 * <dl>
 * <dt><tt>FALSE</tt>        <dd>if it is indirect.
 * <dt><tt>TRUE</tt>        <dd>if it is direct.
 * </dl>
 */
  CATBoolean IsDirect() const;

/**
 * Retrieves the inverse of <tt>this</tt> CATMathTransformation2D.
 * @return 
 * <tt>TRUE</tt> if <tt>this</tt> CATMathTransformation2D is invertible, <tt>FALSE</tt> otherwise. 
 * In this last case, <tt>ioInverse</tt> is not modified.
 */
  CATBoolean Inverse(CATMathTransformation2D & ioInverse) const;

   /**
   * @deprecated V5R21 ApplyToLine 
  * Computes the CATMathLine2D transformation.
  * @param iLineToTransfo
  *  The CATMathLine2D of origin 
  * @param oLine
  * The transformed CATMathLine2D
  *  Note that it could change the length if the transformation is not an isometry.
  * @return 
  * <tt>E_FAIL</tt> if an error occurs, <tt>S_OK</tt> otherwise. 
  */
HRESULT ApplyTo(const CATMathLine2D & iLineToTransfo, CATMathLine2D & oLine);

 /**
  * Computes the CATMathLine2D transformation.
  * @param iLineToTransfo
  *  The CATMathLine2D of origin 
  * @param oLine
  * The transformed CATMathLine2D
  *  Note that it could change the length if the transformation is not an isometry.
  * @return 
  * <tt>E_FAIL</tt> if an error occurs, <tt>S_OK</tt> otherwise. 
  */
HRESULT ApplyToLine(const CATMathLine2D & l,  CATMathLine2D & oLine) const;

/**
* @deprecated V5R21 ApplyToAxis
  * Computes the CATMathAxis transformation.
  * @param iAxisToTransfo
  *  The CATMathAxis2D of origin 
  * @param oAxis
  * The transformed CATMathAxis2D
  *  Note that the directions of the transformated axis are re-orthonormalized. 
  * @return 
  * <tt>E_FAIL</tt> if an error occurs, <tt>S_OK</tt> otherwise. 
  */
HRESULT ApplyTo(const CATMathAxis2D & iAxisToTransfo, CATMathAxis2D & oAxis);

/**
  * Computes the CATMathAxis transformation.
  * @param iAxisToTransfo
  *  The CATMathAxis2D of origin 
  * @param oAxis
  * The transformed CATMathAxis2D
  *  Note that the directions of the transformated axis are re-orthonormalized. 
  * @return 
  * <tt>E_FAIL</tt> if an error occurs, <tt>S_OK</tt> otherwise. 
  */
HRESULT ApplyToAxis(const CATMathAxis2D & p, CATMathAxis2D & oAxis) const ;
 
//===========================================================================
//- Overloaded operators
//===========================================================================
/**
 * Defines the composition of two CATMathTransformation2D.
 * @return
 * The CATMathTransformation2D defined by:
 * <tt> Matrix = iTransfo1.Matrix * iTransfo2.Matrix</tt>
 *<br><tt> Vector = iTransfo1.Matrix * iTransfo2.Vector +iTransfo1.Vector</tt> 
 */
  friend ExportedByCATMathematics CATMathTransformation2D operator * (
				const CATMathTransformation2D &iTransfo1,
				const CATMathTransformation2D &iTransfo2);

/**
 * Defines the CATMathPoint2D transformation.
 * @return
 *  The CATMathPoint2D defined by: 
 * <tt> iTransfo.Matrix*iPointToTransfo + iTransfo.Vector</tt>
 */
  friend  ExportedByCATMathematics CATMathPoint2D  operator * (
                const CATMathTransformation2D &iTransfo,
                const CATMathPoint2D &iPointToTransfo);

/**
 * Defines the CATMathVector2D transformation.
 * @return
 *  The CATMathVector2D defined by <tt> iTransfo.Matrix*iVectorToTransfo </tt>
 */
  friend  ExportedByCATMathematics CATMathVector2D operator * (
                 const CATMathTransformation2D &iTransfo,
                 const CATMathVector2D &iVectorToTransfo);

/**
 * @deprecated V5R20 ApplyTo
 * Defines the CATMathLine2D transformation.
 * @return
 *  The CATMathLine2D of origin 
 * <tt> iTransfo*iLineToTransfo.Origin </tt>
 * and of vector <tt> iTransfo*iLineToTransfo.Direction</tt>. Note that
 * it could change the length if the transformation is not an isometry.
  * <br>Throws an error if the resulting line cannot be computed.
 */
  friend ExportedByCATMathematics CATMathLine2D   operator * (
               const CATMathTransformation2D &,
               const CATMathLine2D &);

/**
 * @deprecated V5R20 ApplyTo
 * Defines the CATMathAxis2D transformation.
 * @return
 *  The CATMathAxis2D of origin 
 * <tt> iTransfo*AxisToTransfo.Origin </tt>
 * and of directions <tt> iTransfo*iAxisToTransfo.FirstDirection</tt>and 
 * <tt> iTransfo*iAxisToTransfo.SecondDirection</tt>.
 *  Note that the directions of the transformated axis are
 *  re-orthonormalized. 
 */
  friend  ExportedByCATMathematics CATMathAxis2D   operator * (
                const CATMathTransformation2D &,
                const CATMathAxis2D &);


  /**
 * @nodoc
 * @deprecated V5R20 
 */
  void SetType(const CATMathTransfoType iType, double iTol);

/**
 * @nodoc
 * @deprecated V5R20 Inverse
 * Use the  signature which returns a CATMathTransformation2D as an output argument.
 */
    CATMathTransformation2D Inverse() const;

 /**
 * @nodoc
 * @deprecated V5R20 GetMatrix
 * Use the  signature which returns a CATMath2x2Matrix as an output argument.
 */
    CATMath2x2Matrix GetMatrix() const;
/**
 * @nodoc
 * @deprecated V5R20 GetVector
* Use the  signature which returns a CATMathVector2D as an output argument.
 */
    CATMathVector2D GetVector() const;

/**
 * @nodoc
 * @deprecated V5R20.
 * Dumps a CATMathTransformation2D.
 * <br>This writes the following lines on the ostream:
 *    <tt><table width = 40>
 *<tr><td> Matrix= </td><td>|</td><td> iA11 </td><td> iA12 </td><td>|</td></tr>
 *<tr><td>         </td><td>|</td><td> iA21 </td><td> iA22 </td><td>|</td></tr>
 *<tr><td>Translation= </td><td>(</td><td> FirstCoord,</td><td>SecondCoord</td>
 *                      <td>)</td></td></tr>
 *        </table></tt> 
 * @param iStream  
 * A pointer to the output. If <tt>0L</tt>, the method dumps 
 * on the <tt>cout</tt> output.
 */
    void Dump(ostream * iStream=0L) const;
	

/**
 * @nodoc
 * @deprecated V5R20 CATMathTransformation2D
 * Use now the signature 
 *<tt>CATMathTransformation2D(const double, const CATMathPoint2D &, 
 * const CATLONG32 type = 1)</tt> in radian for a rotation.
 * Constructs the CATMathTansformation from a scalar and a CATMathPoint2D.
 * @return
 *   If iType= 1
 *     <table>
 *    <tr><td> Matrix= </td><td> iA </td><td> 0 </td>
 *        </tr>
 *    <tr><td>         </td><td> 0  </td><td>iA </td>
 *        </tr>
 *        </table></tt> 
 *   If iType= 2
 *     <table>
 *    <tr><td> Matrix= </td><td> cos(iA) </td><td> -sin(iA) </td>
 *        </tr>
 *    <tr><td>         </td><td> sin(iA)  </td><td> cos(iA) </td>
 *        </tr>
 *        </table></tt> 
 */
  CATMathTransformation2D(const CATMathPoint2D & iCenter,
                                                 const double iA,
                                                 const CATMathTransfoType iType = CATMathScaling);

/**
 * @nodoc 
 * @deprecated V5R20 IsRotation
 * Use now the signature 
 *<tt>CATBoolean IsRotation(const CATAngle &, const CATMathPoint2D &)</tt> in radian.
 *<br>
 * Tests if the transformation is a rotation and retrieves the center and the
 * angle in degree.
 * @return
 * <dl>
 * <dt><tt>0</tt>        <dd>if it is not a rotation.
 * <dt><tt>1</tt>        <dd>if it is a rotation.
 * </dl>
 */
  CATBoolean IsRotation(CATMathPoint2D &oCenter, CATAngle &oAngle) const;

//===========================================================================
// Private Data
//===========================================================================
 private:
  CATMath2x2Matrix _matrix;
  CATMathVector2D  _vector;

};

#endif
