#ifndef CATMath2X2Matrix_H
#define CATMath2X2Matrix_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
* @CAA2Level L1
* @CAA2Usage U1
*/ 

#include "CATMathematics.h"
#include "CATTolerance.h"
#include "CATMathTransfoType.h"
#include "CATMathVector2D.h"

class CATMathDirection2D;
class CATMathTransformation2D;
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

/**
* Class representing a matrix in dimension 2.
*<br><tt><table width = 40>
*    <tr><td> Matrix= </td><td> A11 </td><td> A12 </td>
*        </tr>
*    <tr><td>         </td><td> A21 </td><td> A22 </td>
*        </tr>
*        </table></tt>
*/
class ExportedByCATMathematics CATMath2x2Matrix
{
	friend class CATMathTransformation2D;

public:

	//===========================================================================
	//- Constructors
	//===========================================================================

	/**
	* Constructs the Identity CATMath2x2Matrix.
	* @return
	*    <tt><table width = 40>
	*    <tr><td> Matrix= </td><td> 1 </td><td> 0 </td>
	*        </tr>
	*    <tr><td>         </td><td> 0 </td><td> 1 </td>
	*        </tr>
	*        </table></tt>
	*/
	CATMath2x2Matrix ();

	/**
	* Constructs a  CATMath2x2Matrix from a scalar.
	* @return
	*   If iType==CATMathScaling
	*    <tt><table width = 40>
	*    <tr><td> Matrix= </td><td> iA </td><td> 0 </td>
	*        </tr>
	*    <tr><td>         </td><td> 0  </td><td>iA </td>
	*        </tr>
	*        </table></tt> 
	*   If iType==CATMathRotation, <tt>iA</tt> is expressed in radians.
	*    <tt><table width = 20%>
	*    <tr><td> Matrix= </td><td> cos(iA) </td><td> -sin(iA) </td>
	*        </tr>
	*    <tr><td>         </td><td> sin(iA)  </td><td>cos(iA) </td>
	*        </tr>
	*        </table></tt> 
	*/
	CATMath2x2Matrix (const double  iA,
					                 const CATMathTransfoType iType = CATMathScaling);

	/**
	* Constructs a diagonal CATMath2x2Matrix.
	* @return
	*    <tt><table width = 40>
	*    <tr><td> Matrix= </td><td> iA11 </td><td> 0 </td>
	*        </tr>
	*    <tr><td>         </td><td> 0  </td><td>iA22 </td>
	*        </tr>
	*        </table></tt> 
	*/
	CATMath2x2Matrix (const double iA11, const double iA22);

	/**
	* Constructs a CATMath2x2Matrix from its coefficients.
	* @return
	*<br><tt><table width = 40>
	*    <tr><td> Matrix= </td><td> iA11 </td><td> iA12 </td>
	*        </tr>
	*    <tr><td>         </td><td> iA21 </td><td> iA22 </td>
	*        </tr>
	*        </table></tt>
	*/
	CATMath2x2Matrix (const double iA11, const double iA12,
		                             const double iA21, const double iA22);

	/**
	* Constructs a CATMath2x2Matrix from two colums.
	* @param iTranspose
	* <dl><dt>0</dt><dd>to construct a matrix with first column <tt>iV1</tt> and second
	* column <tt>iV2</tt>
	*  <dt>1</dt><dd>to construct a matrix resulting from the product of <tt>iV1</tt> by  
	* the transpose of <tt>iV2</tt>.
	*/
	CATMath2x2Matrix (const CATMathVector2D &iV1,
									 const CATMathVector2D &iV2,short iTranspose=0);

	/**
	* Constructs a reflection around a direction.
	*/
	CATMath2x2Matrix (const CATMathVector2D &iReflectDirection);

	/**
	*  Copy constructor.
	*/
	CATMath2x2Matrix (const CATMath2x2Matrix &iMatrixToCopy);

	//===========================================================================
	//- Get/Set
	//===========================================================================

	/**
	* Retrieves the first column of <tt>this</tt> CATMath2x2Matrix.
	*/  
	void GetFirstColumn (CATMathVector2D & ioFirstColumn) const ;

	/**
	* Modifies the first column of <tt>this</tt> CATMath2x2Matrix.
	*/
	void SetFirstColumn (const CATMathVector2D &iFirstColumn) ;

	/**
	* Retrieves the second column of <tt>this</tt> CATMath2x2Matrix.
	*/
	void GetSecondColumn (CATMathVector2D & ioSecondColumn) const ;

	/**
	* Modifies the second column of <tt>this</tt> CATMath2x2Matrix.
	*/
	void SetSecondColumn (const CATMathVector2D &iSecondColumn) ;

	/**
	* Retrieves the coefficients of <tt>this</tt> CATMath2x2Matrix.
	* <br>
	*    <tt><table width = 40>
	*    <tr><td> Matrix= </td><td> ioA11  </td><td>ioA12 </td>
	*        </tr>
	*    <tr><td>         </td><td> ioA21  </td><td>ioA22 </td>
	*        </tr>
	*        </table></tt> 
	*/
	void GetCoef (double & ioA11, double & ioA12, 
		                    double & ioA21,  double & ioA22);

	/**
	* Sets the coefficients of <tt>this</tt> CATMath2x2Matrix.
	* <br>
	*    <tt><table width = 40>
	*    <tr><td> Matrix= </td><td> iA11  </td><td>iA12 </td>
	*        </tr>
	*    <tr><td>         </td><td> iA21  </td><td>iA22 </td>
	*        </tr>
	*        </table></tt> 
	*/
	void SetCoef (const double ioA11, const double ioA12, 
		                   const double ioA21, const double ioA22);

	/**
	* Modifies the columns of <tt>this</tt> CATMath2x2Matrix.
	*/
	void SetMatrix (const CATMathVector2D & iFirstColumn,
		                     const CATMathVector2D & iSecondColumn) ;

	/**
	* Tests whether <tt>this</tt> CATMath2x2Matrix is an isometry.
	* @return
	* <dl>
	* <dt><tt>FALSE</tt>        <dd>if it is not an isometry.
	* <dt><tt>TRUE</tt>        <dd>if it is a direct isometry.
	* </dl>
	*/

	CATBoolean IsIsometry() const;

	/**
	* Tests whether <tt>this</tt> CATMath2x2Matrix is a scaling.
	* @return
	* <dl>
	* <dt><tt>FALSE</tt>        <dd>if it is not a scaling.
	* <dt><tt>TRUE</tt>        <dd>if it is a direct scaling.
	* </dl>
	*/
	CATBoolean IsScaling() const ;

	/**
	* Tests whether <tt>this</tt> CATMath2x2Matrix is direct.
	* @return
	* <dl>
	* <dt><tt>TRUE</tt>        <dd>if it is direct.
	* <dt><tt>FALSE</tt>        <dd>if it is indirect.
	* </dl>
	*/
	CATBoolean IsDirect() const ;

	//
	//===========================================================================
	//- Methods
	//===========================================================================

	/**
	* Returns the determinant of <tt>this</tt> CATMath2x2Matrix.
	*/
	double Determinant () const ;

	/** 
	* Returns the trace of <tt>this</tt> CATMath2x2Matrix.
	*/
	double Trace() const;

	/** 
	* Transposes <tt>this</tt> CATMath2x2Matrix.
	*/
	void Transpose(CATMath2x2Matrix & ioTransposed) const;

	/** 
	* Inverses <tt>this</tt> CATMath2x2Matrix.
	* @return 
	* <tt>TRUE</tt> if <tt>this</tt> CATMath3x3Matrix is invertible, <tt>FALSE</tt> otherwise. 
	* In this last case, <tt>ioInverse</tt> is not modified.
	*/
	CATBoolean Inverse(CATMath2x2Matrix & ioInverse) const;

	/** 
	* @nodoc
	* Returns the infinite norm of <tt>this</tt> CATMath2x2Matrix.
	*<br> The infinite norm is the supremum of the absolute value of the 
	* coefficients.
	*/
	double InfiniteNorm() const;
	
	/**
	* @nodoc
	* Retrieves the eigenvalues and eigenvectors of <tt>this</tt> CATMath2x2Matrix.
	* @param oNbEigenValues
	* Number of eigenvalues. Multiple eigenvalues are counted as their multiplicity.
	* @param oEigenValues
	* The array of the eigenvalues. You must allocate it to 2 doubles, but the retrieved information
	* is only significant for index from 0 to <tt>oNbEigenValues-1</tt>.
	* @param oHasAssociatedVector
	* The array to test if there is an eigenvector associated with an eigenvalue. This is not
	* the case when the dimension of the associated eigenspace is less than the 
	* multiplicity of the eigenvalue. The array dimension must be 2 (and you must allocate it), 
	* but the retrieved information
	* is only significant for index from 0 to <tt>oNbEigenValues-1</tt>.
	* @param oEigenVectors
	* The array of the eigenvectors. The array dimension must be 2 (and you must allocate it),
	* but the retrieved information
	* is only significant for <tt>index</tt> from 0 to <tt>oNbEigenValues-1</tt> AND
	* <tt>oHasAssociatedVector[index]==TRUE</tt>.
	*<br> The eigenvectors are normed. 
	* @param oIsDiagonal
	* <tt>TRUE</tt> if <tt>this</tt> has 2 eigenvalues and 2 eigenvectors.
	* @param iTol
	* Internal tolerance used to test if eigenvalues are distinct or if the eigenvectors are valid.
	* If it is negative, the tolerance is set to iTolObject.EpsgForRelativeTest() 
	*/
	void EigenVectors(int & oNbEigenValues,
					  double oEigenValues[2], 
					  CATBoolean oHasAssociatedVector[2],
					  CATMathVector2D oEigenVectors[2], 
					  CATBoolean & oIsDiagonal,
					  const CATTolerance& iTolObject,					  
					  double iTol= -1.) const;
	//===========================================================================
	//- Overloaded Operators
	//===========================================================================

	/**
	* Defines the addition of two CATMath2x2Matrix.
	* @return
	* The CATMath2x2Matrix whose coefficients are the sum of the coefficients
	* of two CATMath2x2Matrix.
	*/
	friend ExportedByCATMathematics CATMath2x2Matrix operator +
		(const CATMath2x2Matrix &iMatrix1, const CATMath2x2Matrix &iMatrix2);

	/**
	* Defines the subtraction of two CATMath2x2Matrix.
	* @return
	* The CATMath2x2Matrix whose coefficients are the difference of the
	* coefficients of two CATMath2x2Matrix.
	*/
	friend ExportedByCATMathematics CATMath2x2Matrix operator -
		(const CATMath2x2Matrix &iMatrix1,
		const CATMath2x2Matrix &iMatrixToSubstract);

	//  Scalar Multiplication
	/**
	* Defines the left side scalar multiplication.
	* @return
	* The CATMath2x2Matrix whose coeffients are the multiplication of the
	* coefficients of a CATMath2x2Matrix by a scalar.
	*/
	friend ExportedByCATMathematics CATMath2x2Matrix operator *
		(const double iScalar, const CATMath2x2Matrix &iMatrix);

	/**
	* Defines the right side scalar multiplication.
	* @return
	* The CATMath2x2Matrix whose coeffients are the multiplication of the
	* coefficients of a CATMath2x2Matrix by a scalar.
	*/
	friend ExportedByCATMathematics CATMath2x2Matrix operator *
		(const CATMath2x2Matrix &iMatrix, const double iScalar);

	/**
	* Defines the scalar division.
	* @return
	* The CATMath2x2Matrix whose coeffients are the division of the
	* coefficients of a CATMath2x2Matrix by a scalar.
	*/
	friend ExportedByCATMathematics CATMath2x2Matrix operator /
		(const CATMath2x2Matrix &iMatrix, const double iScalar);

	/**
	* Defines the product of two CATMath2x2Matrix.
	*/
	friend ExportedByCATMathematics CATMath2x2Matrix operator *
		(const CATMath2x2Matrix &iMatrix1, const CATMath2x2Matrix &iMatrix2);

	/**
	* Defines the product of a CATMath2x2Matrix by a CATMathVector2D.
	*/ 
	friend ExportedByCATMathematics CATMathVector2D operator *
		(const CATMath2x2Matrix &iMatrix, const CATMathVector2D &iVector);


	/**
	* Defines the product of a CATMathTransformation2D by a CATMathPoint2D.
	*/ 
    friend ExportedByCATMathematics CATMathPoint2D operator * ( const CATMathTransformation2D & t, const CATMathPoint2D & p);

	/**
	* Retrieves the first column of <tt>this</tt> CATMath2x2Matrix. The signature which returns 
	* a CATMathVector2D output argument should be preferably used.
	*/  
	CATMathVector2D GetFirstColumn () const ;

	/**
	* Retrieves the second column of <tt>this</tt> CATMath2x2Matrix. The signature which returns 
	* a CATMathVector2D output argument should be preferably used.
	*/  
	CATMathVector2D GetSecondColumn () const ;



	/**
	* @nodoc
	* @deprecated V5R20
	*/
	void SetType(const CATMathTransfoType iType,
		                   double iTol);

	/**
	* @nodoc
	* @deprecated V5R20 Transpose
	* Use the  signature which returns a CATMath2x2Matrix as an output argument.
	*/
	CATMath2x2Matrix Transpose () const;

	/**
	* @nodoc
	* @deprecated V5R20 Inverse
	* Use the  signature which returns a CATMath2x2Matrix as an output argument.
	*/
	CATMath2x2Matrix Inverse () const;

	/**
	* @nodoc
	* @deprecated V5R20
	*/
	friend ExportedByCATMathematics CATMath2x2Matrix operator %
		(const CATMathVector2D &iVector1,
		const CATMathVector2D &VectorToTranspose);


	/**
	* @nodoc
	* @deprecated V5R20
	* Dumps <tt>this</tt> CATMath2x2Matrix.
	* <br>This writes the matrix coefficients on the ostream:
	*<tt><table width = 40>
	*    <tr><td>|</td><td> iA11 </td><td> iA12 </td><td>|</td></tr>
	*    <tr><td>|</td><td> iA21 </td><td> iA22 </td><td>|</td></tr>
	* </table></tt>
	* @param iStream  
	* A pointer to the output. If <tt>0L</tt>, the method dumps
	* on the <tt>cout</tt> output.
	*/
	void Dump(ostream * iStream=0L) const;



	//===========================================================================
	// Private data
	//===========================================================================
private:
	double _a11, _a12, _a21, _a22;
	int   _type;
};

#endif
