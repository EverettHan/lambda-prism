#ifndef CATMathTransformation_H
#define CATMathTransformation_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATMathematics.h"

#include "CATMath3x3Matrix.h"
#include "CATMathPoint.h"
#include "CATMathLine.h"
#include "CATMathPlane.h"
#include "CATMathVector.h"
#include "CATMathAxis.h"
#include "CATIAV5Level.h"


#include "CATMathDirection.h"
#include "CATMathLimits.h"
#include "CATErrorDef.h" //HRESULT

/**
* @nodoc
*/
extern  ExportedByCATMathematics CATMathPoint  operator * (
  const CATMathTransformation & iTransfo,
  const CATMathPoint & iPointToTransfo);
/**
* @nodoc
*/
extern  ExportedByCATMathematics CATMathVector operator * (
  const CATMathTransformation & iTransfo,
  const CATMathVector & iVectorToTransfo);
/**
* @nodoc
* @deprecated V5R20 ApplyTo
*/
extern  ExportedByCATMathematics CATMathLine   operator * (
  const CATMathTransformation & iTransfo,
  const CATMathLine & iLineToTransfo);
/**
* @nodoc
* @deprecated V5R20 ApplyTo
*/
extern  ExportedByCATMathematics CATMathPlane  operator * (
  const CATMathTransformation & iTransfo,
  const CATMathPlane & iPlaneToTransfo);
/**
* @nodoc
* @deprecated V5R20 ApplyTo
*/
extern  ExportedByCATMathematics CATMathAxis   operator * (
  const CATMathTransformation & iTransfo,
  const CATMathAxis & iAxisToTransfo);

/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;// to suppress
#endif

/**
* Class representing a transformation in dimension 3.
* <br>It is composed of a matrix <tt>Matrix</tt>, 
* and of a translation <tt>Vector</tt>.
*<br><tt><table width = 40>
*    <tr><td> Matrix= </td><td> a11 </td><td> a12 </td><td> a13 </td>
*        <td> Vector= </td><td> u1 </td></tr>
*    <tr><td></td>         <td> a21 </td><td> a22 </td><td> a23 </td>
*        <td>         </td><td> u2 </td></tr>
*    <tr><td></td>         <td> a31 </td><td> a32 </td><td> a33 </td>
*        <td>         </td><td> u3 </td></tr>
*        </table></tt>
* <br>Apply transformations by using the <tt>*</tt> operator.
* <br>Available transformations are scaling, translation, reflection, 
* rotation.
*/ 
class ExportedByCATMathematics CATMathTransformation
{
  
  
public:
  //============================================================================
  //- Constructors
  //============================================================================
  /**
  * Constructs an Identity transformation.
  * <br> <tt>Matrix= Identity</tt>, <tt>Vector = (0,0,0) </tt>
  */ 
  CATMathTransformation();
  
  /**
  * Constructs a CATMathTransformation from a CATMath3x3Matrix and a CATMathVector.
  */
  CATMathTransformation(const CATMath3x3Matrix & iMatrix,
                        const CATMathVector &iTranslation);
  
  /**
  * Constructs a scaling.
  */
  CATMathTransformation(const CATMathPoint & iCenter ,
                        const double iScale);
  
  /**
  * Constructs a translation.
  */
  CATMathTransformation(const CATMathVector & iTranslation);
  
  /**
  * Constructs a reflection from a CATMathPoint and a CATMathVector.
  */
  CATMathTransformation(const CATMathPoint &iReflectPlaneOrigin,
                        const CATMathVector &iReflectPlaneNormal);
  
  /**
  * Constructs a reflection on a plane.
  */
  CATMathTransformation(const CATMathPlane & iReflectPlane);
  
  /**
  * Constructs an affinity with respect to a plane.
  */
  CATMathTransformation(const CATMathPlane & iPlane, const double iScale);
  
  /**
  * Constructs a rotation (radians).
  * @param iAngle
  * The angle in radians.
  * @param iAxis
  * The rotation axis.
  */
  CATMathTransformation(const CATAngle &iAngle, const CATMathLine & iAxis);
  
  /**
  * Constructs an affinity with respect to a given ratio for each direction of a CATMathAxis.
  * @param iAxis
  * The three direction of the affinity.
  * @param iRatio
  * Array of 3 doubles, giving the ratio in each direction.
  */
  CATMathTransformation(const CATMathAxis & iAxis, const double iRatio[]);
  

  /**
  * @nodoc
  * @deprecated V5R15 Set
  * Constructs a transformation of axis systems.
  *<br>
  * This transformation transforms, in the global axis system
  * <tt>CATMathOIJK</tt>, the coordinates of a point <tt>M</tt>
  * into the coordinates of the point <tt>TM</tt> such that:
  * <tt>M</tt> and <tt>TM</tt> have the same coordinate values
  * in the axis <tt>iFromAxis</tt> and <tt>iToAxis</tt>. 
  *<br>
  * Now, for defining the transformation from <tt>iFromAxis</tt> to <tt>iToAxis</tt>, you have to combine
  * two transformations, in the following way:
  *   <tt> CATMathTransformation(iToAxis, CATMathOIJK) * CATMathTransformation(CATMathOIJK, iFromAxis)</tt>
  */
  CATMathTransformation(const CATMathAxis & iFromAxis, const CATMathAxis & iToAxis);
  
  /**
  * @nodoc
  * @deprecated V5R15 Set
  * Creates an interpolation of an isometry.
  *<br>This can be used for simulating intermediate steps of a displacement.
  *<br>Throws an error if the two transformations are not compatible.
  * @param iFactor
  * The ratio of the intermediate step: <tt>0 < iFactor < 1</tt>.     
  */
  CATMathTransformation(const double iFactor, 
                        const CATMathTransformation & iFromTansfo,
                        const CATMathTransformation & iToTransfo);


  /**
  * Copy constructor.
  */
  CATMathTransformation(const CATMathTransformation & iTransfoToCopy);
  
  /**
  * @nodoc
  * @deprecated V5R20 SetCoefficients
  *Throws an error if iNbCoeff value is not 12 or 16.
  *<br>Constructs a transformation from an array[] of doubles.
  * <br>If <tt>iNbCoeff=12</tt>, the array is:
  *<br><tt><table width = 40>
  *    <tr><td> iCoeff</td><td> a11 </td><td> a12 </td><td> a13 </td>
  *        <td> u1 </td></tr>
  *    <tr><td></td>         <td> a21 </td><td> a22 </td><td> a23 </td>
  *        <td> u2 </td></tr>
  *    <tr><td></td>         <td> a31 </td><td> a32 </td><td> a33 </td>
  *        <td> u3 </td></tr>
  *        </table></tt>
  * and the coefficients must be given COLUMN by COLUMN.
  * <br>If <tt>iNbCoeff=16</tt>, DO NOT USE- the array is:
  *<br><tt><table width = 40>
  *    <tr><td> iCoeff</td><td> a11 </td><td> a12 </td><td> a13 </td>
  *        <td>  u1  </td></tr>
  *    <tr><td></td>         <td> a21 </td><td> a22 </td><td> a23 </td>
  *        <td>  u2      </td></tr>
  *    <tr><td></td>         <td> a31 </td><td> a32 </td><td> a33 </td>
  *        <td>  u3      </td></tr>
  *    <tr><td></td>         <td>  0  </td><td>  0  </td><td> 0   </td>
  *        <td>  1     </td></tr>
  *        </table></tt>
  * and the coefficients must be given COLUMN by COLUMN.
  */
  CATMathTransformation(const double iCoeff[], const CATLONG32 iNbCoeff = 12);
  
  //===========================================================================
  //  Get/Set
  //===========================================================================
  /**
  * Set an interpolation of an isometry.
  *<br>This can be used for simulating intermediate steps of a displacement.
  * @param iFactor
  * The ratio of the intermediate step: <tt>0 < iFactor < 1</tt>.     
  * @return 
  * <tt>E_FAIL</tt> if the two transformations are not compatible, <tt>S_OK</tt> otherwise. 
  */
  HRESULT Set(const double iFactor,
              const CATMathTransformation & iFromTansfo,
              const CATMathTransformation & iToTransfo);	

  /**
  * Set an transformation of axis systems.
  *<br>
  * This transformation transforms, in the global axis system
  * <tt>CATMathOIJK</tt>, the coordinates of a point <tt>M</tt>
  * into the coordinates of the point <tt>TM</tt> such that:
  * <tt>M</tt> and <tt>TM</tt> have the same coordinate values
  * in the axis <tt>iFromAxis</tt> and <tt>iToAxis</tt>. 
  *<br>
  * Now, for defining the transformation from <tt>iFromAxis</tt> to <tt>iToAxis</tt>, you have to combine
  * two transformations, in the following way:
  *   <tt> CATMathTransformation(iToAxis, CATMathOIJK) * CATMathTransformation(CATMathOIJK, iFromAxis)</tt>
  * @return 
  * <tt>E_FAIL</tt> if an error occurs, <tt>S_OK</tt> otherwise. 
  */
  HRESULT Set(const CATMathAxis & iFromAxis,const CATMathAxis & iToAxis);
  
  /**
  * Set a transformation of axis systems in the global axis system CATMathOIJK.
  * It transforms the axis <tt>iFromAxis</tt> into the global axis system CATMathOIJK. 
  * This transformation can be also used in the frame of a change of basis.
  * In that case, the name is ambiguous because  
  *<br>
  * this transformation transforms the coordinates  <tt>P_OIJK</tt>
  * in the global axis system <tt>CATMathOIJK</tt> of a point into its coordinates 
  * <tt>P_FromAxis</tt> in the axis <tt>iFromAxis</tt>. 
  *
  *  <tt> P_FromAxis = (*this) *  P_OIJK </tt>
  *<br>
  * contrary to what it was written previously.
  * @return 
  * <tt>E_FAIL</tt> if an error occurs, <tt>S_OK</tt> otherwise. 
  * This API is equivalent to CATMathTransformation(iFromAxis, CATMathOIJK)
  */
  HRESULT SetFromAxisToOIJK(const CATMathAxis & iFromAxis);

  /**
  * Set a transformation of axis systems in the global axis system CATMathOIJK.
  * It transforms the global axis system CATMathOIJK into the axis <tt>iToAxis</tt>. 
  * This transformation can be also used in the frame of a change of basis.
  * In that case, the name is ambiguous because  
  *<br>
  * this transformation transforms the coordinates <tt>P_ToAxis</tt>
  * in the axis <tt>iToAxis</tt>  of a point into its coordinates 
  *  <tt>P_OIJK</tt> in the global axis system <tt>CATMathOIJK</tt>.
  *
  *  <tt> P_OIJK = (*this) *  P_ToAxis </tt>
  *<br>
  * contrary to what it was written previously.
  * @return 
  * <tt>E_FAIL</tt> if an error occurs, <tt>S_OK</tt> otherwise. 
  * This API is equivalent to CATMathTransformation(CATMathOIJK, iToAxis)
  */
  HRESULT SetFromOIJKToAxis(const CATMathAxis & iToAxis);

  /**
  * Retrieves the CATMath3x3Matrix associated with <tt>this</tt> CATMathTransformation.
  */
  void GetMatrix(CATMath3x3Matrix & ioMatrix) const;
  
  /**
  * Sets the matrix of <tt>this</tt> CATMathTransformation.
  */
  void SetMatrix(const CATMath3x3Matrix & iMatrix) ;

  /**
  * Retrieves the CATMathVector associated with <tt>this</tt> CATMathTransformation.
  */
  void GetVector(CATMathVector & ioVector) const;
  
  /**
  * Sets the vector of <tt>this</tt> CATMathTransformation.
  */
  void SetVector(const CATMathVector & iVector) ;
  
  /**
  * @nodoc
  * @deprecated V5R15 GetCoefficients
  *Throws an error if iNbCoeff value is not 12 or 16.
  *<br>Retrieves the coefficients of <tt>this</tt> CATMathTransformation in an array[] of doubles.
  * <br>If <tt>iNbCoeff=12</tt>, the array is:
  *<br><tt><table width = 40>
  *    <tr><td> oCoeff</td><td> a11 </td><td> a12 </td><td> a13 </td>
  *        <td> u1 </td></tr>
  *    <tr><td></td>         <td> a21 </td><td> a22 </td><td> a23 </td>
  *        <td> u2 </td></tr>
  *    <tr><td></td>         <td> a31 </td><td> a32 </td><td> a33 </td>
  *        <td> u3 </td></tr>
  *        </table></tt>
  * and the coefficients are given COLUMN by COLUMN.
  * <br>If <tt>iNbCoeff=16</tt>, DO NOT USE - and the array is:
  *<br><tt><table width = 40>
  *    <tr><td> oCoeff</td><td> a11 </td><td> a12 </td><td> a13 </td>
  *        <td>  u1  </td></tr>
  *    <tr><td></td>         <td> a21 </td><td> a22 </td><td> a23 </td>
  *        <td>  u2      </td></tr>
  *    <tr><td></td>         <td> a31 </td><td> a32 </td><td> a33 </td>
  *        <td>  u3      </td></tr>
  *    <tr><td></td>         <td>  0  </td><td>  0  </td><td> 0   </td>
  *        <td>  1     </td></tr>
  *        </table></tt>
  * and the coefficients are given COLUMN by COLUMN.
  */
  void GetCoef(double iCoeff[], const CATLONG32 iNbCoeff = 12) const;	

  /**
  *Retrieves the coefficients of <tt>this</tt> CATMathTransformation in an array[] of doubles.
  *<br>If <tt>iNbCoeff=12</tt>, the array is:
  *<br><tt><table width = 40>
  *    <tr><td> oCoeff</td><td> a11 </td><td> a12 </td><td> a13 </td>
  *        <td> u1 </td></tr>
  *    <tr><td></td>         <td> a21 </td><td> a22 </td><td> a23 </td>
  *        <td> u2 </td></tr>
  *    <tr><td></td>         <td> a31 </td><td> a32 </td><td> a33 </td>
  *        <td> u3 </td></tr>
  *        </table></tt>
  * and the coefficients are given COLUMN by COLUMN.
  *<br>If <tt>iNbCoeff=16</tt>, DO NOT USE - and the array is:
  *<br><tt><table width = 40>
  *    <tr><td> oCoeff</td><td> a11 </td><td> a12 </td><td> a13 </td>
  *        <td>  u1  </td></tr>
  *    <tr><td></td>         <td> a21 </td><td> a22 </td><td> a23 </td>
  *        <td>  u2      </td></tr>
  *    <tr><td></td>         <td> a31 </td><td> a32 </td><td> a33 </td>
  *        <td>  u3      </td></tr>
  *    <tr><td></td>         <td>  0  </td><td>  0  </td><td> 0   </td>
  *        <td>  1     </td></tr>
  *        </table></tt>
  * and the coefficients are given COLUMN by COLUMN.
  * @return 
  * <tt>E_FAIL</tt> if iNbCoeff value is not 12 or 16, <tt>S_OK</tt> otherwise. 
  */
  HRESULT GetCoefficients(double iCoeff[], const CATLONG32 iNbCoeff = 12) const;	
  
  /**
  * @nodoc
  * @deprecated V5R15 SetCoefficients
  *Throws an error if iNbCoeff value is not 12 or 16.
  *<br>Modifies the coefficients of <tt>this</tt> CATMathTransformation from an array[] of doubles.
  * <br>If <tt>iNbCoeff=12</tt>, the array is:
  *<br><tt><table width = 40>
  *    <tr><td> iCoeff</td><td> a11 </td><td> a12 </td><td> a13 </td>
  *        <td> u1 </td></tr>
  *    <tr><td></td>         <td> a21 </td><td> a22 </td><td> a23 </td>
  *        <td> u2 </td></tr>
  *    <tr><td></td>         <td> a31 </td><td> a32 </td><td> a33 </td>
  *        <td> u3 </td></tr>
  *        </table></tt>
  * and the coefficients must be given COLUMN by COLUMN.
  * <br>If <tt>iNbCoeff=16</tt>, DO NOT USE - the array is:
  *<br><tt><table width = 40>
  *    <tr><td> iCoeff</td><td> a11 </td><td> a12 </td><td> a13 </td>
  *        <td>  u1  </td></tr>
  *    <tr><td></td>         <td> a21 </td><td> a22 </td><td> a23 </td>
  *        <td>  u2      </td></tr>
  *    <tr><td></td>         <td> a31 </td><td> a32 </td><td> a33 </td>
  *        <td>  u3      </td></tr>
  *    <tr><td></td>         <td>  0  </td><td>  0  </td><td> 0   </td>
  *        <td>  1     </td></tr>
  *        </table></tt>
  * and the coefficients must be given COLUMN by COLUMN.
  */
  void SetCoef(const double iCoeff[], const CATLONG32 iNbCoeff = 12);


  /**
  *Modifies the coefficients of <tt>this</tt> CATMathTransformation from an array[] of doubles.
  *<br>If <tt>iNbCoeff=12</tt>, the array is:
  *<br><tt><table width = 40>
  *    <tr><td> iCoeff</td><td> a11 </td><td> a12 </td><td> a13 </td>
  *        <td> u1 </td></tr>
  *    <tr><td></td>         <td> a21 </td><td> a22 </td><td> a23 </td>
  *        <td> u2 </td></tr>
  *    <tr><td></td>         <td> a31 </td><td> a32 </td><td> a33 </td>
  *        <td> u3 </td></tr>
  *        </table></tt>
  * and the coefficients must be given COLUMN by COLUMN.
  *<br>If <tt>iNbCoeff=16</tt>, DO NOT USE - the array is:
  *<br><tt><table width = 40>
  *    <tr><td> iCoeff</td><td> a11 </td><td> a12 </td><td> a13 </td>
  *        <td>  u1  </td></tr>
  *    <tr><td></td>         <td> a21 </td><td> a22 </td><td> a23 </td>
  *        <td>  u2      </td></tr>
  *    <tr><td></td>         <td> a31 </td><td> a32 </td><td> a33 </td>
  *        <td>  u3      </td></tr>
  *    <tr><td></td>         <td>  0  </td><td>  0  </td><td> 0   </td>
  *        <td>  1     </td></tr>
  *        </table></tt>
  * and the coefficients must be given COLUMN by COLUMN.
  * @return 
  * <tt>E_FAIL</tt> if iNbCoeff value is not 12 or 16, <tt>S_OK</tt> otherwise. 
  */
  HRESULT SetCoefficients(const double iCoeff[], const CATLONG32 iNbCoeff = 12);
  
  /**
  * Tests if the matrix of <tt>this</tt> CATMathTransformation is an isometry (keeps the distances).
  * return
  * <dl>
  * <dt><tt>FALSE</tt>        <dd>if it is not an isometry.
  * <dt><tt>TRUE</tt>        <dd>if it is a direct isometry.
  * </dl>
  */
  CATBoolean IsIsometry() const;
  
  /**
  * Tests if the matrix of <tt>this</tt> CATMathTransformation is the identity (invariant).
  * @return
  * <dl>
  * <dt><tt>FALSE</tt>        <dd>if it is not the identity.
  * <dt><tt>TRUE</tt>        <dd>if it is the identity.
  * </dl>
  */
  CATBoolean IsIdentity() const;
  
  /**
  * Tests if the matrix of <tt>this</tt> CATMathTransformation is a similitude and retrieves the scale.
  * @return
  * <dl>
  * <dt><tt>FALSE</tt>        <dd>if it is not a similitude.
  * <dt><tt>TRUE</tt>        <dd>if it is a similitude.
  * </dl>
  */
  CATBoolean IsSimilitude(double & ioScale) const;
  
  /**
  * Tests if <tt>this</tt> CATMathTransformation is a scaling and retrieves the Origin and 
  * the Scale.
  * @return
  * <dl>
  * <dt><tt>FALSE</tt>        <dd>if it is not a scaling.
  * <dt><tt>TRUE</tt>        <dd>if it is a scaling.
  * </dl>
  */
  CATBoolean IsScaling(CATMathPoint & ioOrigin, double & ioScale) const;
  
  /**
  * Tests if <tt>this</tt> CATMathTransformation is a reflection and retrieves the reflect plane.
  * @return
  * <dl>
  * <dt><tt>FALSE</tt>        <dd>if it is not a reflection.
  * <dt><tt>TRUE</tt>        <dd>if it is a reflection.
  * </dl>
  */
  CATBoolean IsReflection(CATMathPlane & ioReflectPlane) const;
    
  /**
  * Tests if the matrix of <tt>this</tt> CATMathTransformation is a rotation and retrieves the axis and the
  * angle in radian.
  * @return
  * <dl>
  * <dt><tt>FALSE</tt>        <dd>if it is not a rotation.
  * <dt><tt>TRUE</tt>        <dd>if it is a rotation.
  * </dl>
  */
  CATBoolean IsRotation( CATAngle & ioAngle, CATMathLine & ioAxis, const double iTol = 0.) const;
  
  //===========================================================================
  //  Inverse
  //===========================================================================
  /**
  * @nodoc
  * @deprecated V5R15 ComputeInverse
  * Retrieves the inverse of <tt>this</tt> CATMathTransformation.
  * @return 
  * <tt>TRUE</tt> if <tt>this</tt> CATMathTransformation is invertible, <tt>FALSE</tt> otherwise. 
  * In this last case, <tt>oInverse</tt> is not modified.
  */
  CATBoolean  Inverse(CATMathTransformation & ioInverse) const;

  /**
  * Retrieves the inverse of <tt>this</tt> CATMathTransformation.
  * @return 
  * <tt>S_OK</tt> if <tt>this</tt> CATMathTransformation is invertible, <tt>E_FAIL</tt> otherwise. 
  * In this last case, <tt>oInverse</tt> is not modified.
  */
  HRESULT ComputeInverse(CATMathTransformation & ioInverse) const;
  
  //===========================================================================
  // Apply transformations
  //===========================================================================
  /**
  * @nodoc
  * @deprecated V5R21 ApplyToLine
  * Computes the CATMathLine transformation.
  * @param iLineToTransfo
  *  The CATMathLine of origin 
  * @param oLine
  *  The transformed CATMathLine
  * Note that it could change the length if the transformation is not an isometry.
  * @return 
  * <tt>E_FAIL</tt> if an error occurs, <tt>S_OK</tt> otherwise. 
  */
  HRESULT  ApplyTo(const CATMathLine & iLineToTransfo, CATMathLine & oLine);
  
  /**
  * Computes the CATMathLine transformation.
  * @param iLineToTransfo
  *  The CATMathLine of origin 
  * @param oLine
  *  The transformed CATMathLine
  * Note that it could change the length if the transformation is not an isometry.
  * @return 
  * <tt>E_FAIL</tt> if an error occurs, <tt>S_OK</tt> otherwise. 
  */
  HRESULT  ApplyToLine(const CATMathLine & iLineToTransfo, CATMathLine & oLine) const;

  /**
  * @nodoc
  * @deprecated V5R21 ApplyToPlane
  * Computes the CATMathPlane transformation.
  * @param iPlaneToTransfo
  *  The CATMathPlane of origin 
  * @param oPlane
  * The transformed planed
  *  Note that the second direction of the transformated plane is re-orthonormalized. 
  * @return 
  * <tt>E_FAIL</tt> if an error occurs, <tt>S_OK</tt> otherwise. 
  */
  HRESULT   ApplyTo (const CATMathPlane & iPlaneToTransfo, CATMathPlane & oPlane);

  /**
  * Computes the CATMathPlane transformation.
  * @param iPlaneToTransfo
  *  The CATMathPlane of origin 
  * @param oPlane
  * The transformed planed
  *  Note that the second direction of the transformated plane is re-orthonormalized. 
  * @return 
  * <tt>E_FAIL</tt> if an error occurs, <tt>S_OK</tt> otherwise. 
  */
  HRESULT   ApplyToPlane (const CATMathPlane & iPlaneToTransfo, CATMathPlane & oPlane) const;
  
  /**
  * @nodoc
  * @deprecated V5R21 ApplyToAxis
  * Computes the CATMathAxis transformation.
  * @param iAxisToTransfo
  *  The CATMathAxis of origin 
  * @param oAxis
  * The transformed CATMathAxis
  *  Note that the second and third directions of the transformated axis are re-orthonormalized. 
  * @return 
  * <tt>E_FAIL</tt> if an error occurs, <tt>S_OK</tt> otherwise. 
  */
  HRESULT ApplyTo (const CATMathAxis & iAxisToTransfo,  CATMathAxis & oAxis);

  /**
  * Computes the CATMathAxis transformation.
  * @param iAxisToTransfo
  *  The CATMathAxis of origin 
  * @param oAxis
  * The transformed CATMathAxis
  *  Note that the second and third directions of the transformated axis are re-orthonormalized. 
  * @return 
  * <tt>E_FAIL</tt> if an error occurs, <tt>S_OK</tt> otherwise. 
  */
  HRESULT ApplyToAxis (const CATMathAxis & iAxisToTransfo,  CATMathAxis & oAxis) const ;
  //===========================================================================
  //  Overloaded operators
  //===========================================================================
  /**
  * Defines the composition of two CATMathTransformations.
  * @return
  * The CATMathTransformation defined by:
  * <tt> Matrix = iTransfo1.Matrix * iTransfo2.Matrix</tt>
  *<br><tt> Vector = iTransfo1.Matrix * iTransfo2.Vector +iTransfo1.Vector</tt> 
  */
  friend ExportedByCATMathematics CATMathTransformation operator * (
    const CATMathTransformation & iTransfo1,
    const CATMathTransformation & iTransfo2);

  /**
  * Defines the CATMathPoint transformation.
  * @return
  *  The CATMathPoint defined by: 
  * <tt> iTransfo.Matrix*iPointToTransfo + iTransfo.Vector</tt>
  */
  friend  ExportedByCATMathematics CATMathPoint  operator * (
    const CATMathTransformation & iTransfo,
    const CATMathPoint & iPointToTransfo);

  /**
  * Defines the CATMathVector transformation.
  * @return
  *  The CATMathVector defined by <tt> iTransfo.Matrix*iVectorToTransfo </tt>
  */
  friend  ExportedByCATMathematics CATMathVector operator * (
    const CATMathTransformation & iTransfo,
    const CATMathVector & iVectorToTransfo);

  /**
  * @nodoc
  * @deprecated V5R20 ApplyTo
  * Defines the CATMathLine transformation.
  * @return
  *  The CATMathLine of origin 
  * <tt> iTransfo*iLineToTransfo.Origin </tt>
  * and of direction <tt> iTransfo*iLineToTransfo.Direction</tt>. Note that
  * it could change the length if the transformation is not an isometry.
  */
  friend ExportedByCATMathematics CATMathLine   operator * (
    const CATMathTransformation & iTransfo,
    const CATMathLine & iLineToTransfo);

  /**
  * @nodoc
  * @deprecated V5R20 ApplyTo
  * Defines the CATMathPlane transformation.
  * @return
  *  The CATMathPlane of origin 
  * <tt> iTransfo*iPlaneToTransfo.Origin </tt>
  * and of directions <tt> iTransfo*iPlaneToTransfo.FirstDirection</tt> and 
  * <tt> iTransfo*iPlaneToTransfo.SecondDirection</tt>.
  *  Note that the second direction of the transformated plane is
  *  re-orthonormalized. 
  */
  friend  ExportedByCATMathematics CATMathPlane  operator * (
    const CATMathTransformation & iTransfo,
    const CATMathPlane & iPlaneToTransfo);

  /**
  * @nodoc
  * @deprecated V5R20 ApplyTo
  * Defines the CATMathAxis transformation.
  * @return
  *  The CATMathAxis of origin 
  * <tt> iTransfo*iAxisToTransfo.Origin </tt>
  * and of directions <tt> iTransfo*iAxisToTransfo.FirstDirection</tt>, 
  * <tt> iTransfo*iAxisToTransfo.SecondDirection</tt> and
  * <tt> iTransfo*iAxisToTransfo.ThirdDirection</tt>.
  *  Note that the second and third directions of the transformated axis are
  *  re-orthonormalized. 
  */
  friend  ExportedByCATMathematics CATMathAxis   operator * (
    const CATMathTransformation & iTransfo,
    const CATMathAxis & iAxisToTransfo);

  /**
  * @nodoc
  * Computes the Euler angles associated to the rotation of the CATMathTransformation
  * in radian and under the following convention :
  * Extrinsic ZXY Euler Rotation
  * oAngle1 rotate about Z (xyz) => (x'y',z)
  * oAngle2 rotate about X (x'y',z) => (x',y",z')
  * oAngle3 rotate about Y (x',y",z') => (x",y",z")
  */
  HRESULT GetEulerAngles(double & oAngle1, double & oAngle2, double & oAngle3) const;

  /**
  * @nodoc
  * Compute the matrix associated to the Euler angles given as input
  * in radian and under the following convention :
  * Extrinsic ZXY Euler Rotation
  * iAngle1 rotate about Z (xyz) => (x'y',z)
  * iAngle2 rotate about X (x'y',z) => (x',y",z') 
  * iAngle3 rotate about Y (x',y",z') => (x",y",z")
  */
  HRESULT ComputeMatrixFromEulerAngles(double iAngle1, double iAngle2, double iAngle3);

  /**
  * @nodoc
  * @deprecated V5R20
  * Constructs a rotation (degree).
  */
  CATMathTransformation(const CATMathLine & iAxis, const CATAngle &iAngle);

  /**
  * @nodoc
  * @deprecated V5R20
  * Tests if the transformation is a rotation and retrieves the axis and the
  * angle in degree.
  * @return
  * <dl>
  * <dt><tt>0</tt>        <dd>if it is not a rotation.
  * <dt><tt>1</tt>        <dd>if it is a rotation.
  * </dl>
  */
  CATBoolean IsRotation(CATMathLine & oAxis, CATAngle & oAngle) const;

  /**
  * @nodoc
  * @deprecated V5R20
  */
  CATMath3x3Matrix GetMatrix() const;

  /**
  * @nodoc
  * @deprecated V5R20
  */
  CATMathVector GetVector() const;

  /**
  * @nodoc
  * @deprecated V5R15 ComputeInverse
  * <br>Throws an error if the matrix is not invertible.
  */
  CATMathTransformation Inverse() const;

  /**
  * @nodoc
  */
  CATMath3x3Matrix& GetDataMatrix() const;

  /**
  * @nodoc
  */
  CATMathVector& GetDataVector() const;

  /**
  * Dumps <tt>this</tt> CATMathTransformation.
  * <br>This writes the following lines on the ostream:
  *    <tt><table width = 40>
  *<tr><td> Matrix= </td><td>|</td><td> iA11 </td><td> iA12 </td>
  *                  <td> iA13 </td><td>|</td></tr>
  *<tr><td>         </td><td>|</td><td> iA21 </td><td> iA22 </td>
  *                  <td> iA23 </td><td>|</td></tr>
  *<tr><td>         </td><td>|</td><td> iA31 </td><td> iA32 </td>
  *                  <td> iA33 </td><td>|</td></tr>
  *<tr><td>Translation= </td><td>(</td><td> FirstCoord,</td><td>SecondCoord,</td>
  *                      <td> ThirdCoord</td><td>)</td></tr>
  *        </table></tt> 
  * @param iStream  
  * A pointer to the output. If <tt>0L</tt>, the method dumps 
  * on the <tt>cout</tt> output.
  */
  void Dump(ostream * iStream=0L) const;

  /**
  * @nodoc
  */
  CATBoolean IsSimilitude() const;
  
   private:
     CATMath3x3Matrix _matrix;
     CATMathVector _vector;
};

#endif
