#ifndef CATMath3x3Matrix_H
#define CATMath3x3Matrix_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
* @CAA2Level L1
* @CAA2Usage U1
*/ 

#include "CATMathematics.h"

#include "CATMathVector.h"
#include "CATMathDirection.h"
#include "CATIACGMLevel.h"

#ifdef CATIAR418
#include "CATErrorDef.h"
#else
#include "CATMathInputError.h"
#endif

class CATMathTransformation;
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;// to suppress
#endif

/**
* Class representing a matrix in dimension 3.
*<br><tt><table width = 40>
*    <tr><td> Matrix= </td><td> A11 </td><td> A12 </td><td> A13 </td>
*        </tr>
*    <tr><td>         </td><td> A21 </td><td> A22 </td><td> A23 </td>
*        </tr>
*    <tr><td>         </td><td> A31 </td><td> A32 </td><td> A33 </td>
*        </tr>
*        </table></tt>
*/ 
class ExportedByCATMathematics CATMath3x3Matrix
{
	friend class CATMathTransformation;

public:
	//=============================================================================
	// Constructors
	//============================================================================
	/**
	* Constructs the Identity CATMath3x3Matrix.
	* @return
	*    <tt><table width = 40>
	*    <tr><td> Matrix= </td><td> 1 </td><td> 0 </td><td> 0 </td>
	*        </tr>
	*    <tr><td>         </td><td> 0 </td><td> 1 </td><td> 0 </td>
	*        </tr>
	*    <tr><td>         </td><td> 0 </td><td> 0 </td><td> 1 </td>
	*        </tr>
	*        </table></tt>
	*/
	CATMath3x3Matrix (); 

	/**
	* Constructs the iA*Identity CATMath3x3Matrix.
	* @return
	*    <tt><table width = 40>
	*    <tr><td> Matrix= </td><td> iA </td><td> 0 </td><td> 0 </td>
	*        </tr>
	*    <tr><td>         </td><td> 0  </td><td>iA </td><td> 0 </td>
	*        </tr>
	*    <tr><td>         </td><td> 0  </td><td> 0 </td><td> iA </td>
	*        </tr>
	*        </table></tt> 
	*/
	CATMath3x3Matrix (const double  iA); 

	/**
	* Constructs a diagonal CATMath3x3Matrix.
	* @return
	*    <tt><table width = 40>
	*    <tr><td> Matrix= </td><td> iA11 </td><td> 0 </td><td> 0 </td>
	*        </tr>
	*    <tr><td>         </td><td> 0  </td><td>iA22 </td><td> 0 </td>
	*        </tr>
	*    <tr><td>         </td><td> 0  </td><td> 0 </td><td> iA33 </td>
	*        </tr>
	*        </table></tt> 
	*/    
	CATMath3x3Matrix (const double iA11, const double iA22 , const double iA33);

	/**
	* Constructs a CATMath3x3Matrix from its coefficients.
	* @return
	*    <tt><table width = 40>
	*    <tr><td> Matrix= </td><td> iA11  </td><td>iA12 </td><td> iA13 </td>
	*        </tr>
	*    <tr><td>         </td><td> iA21  </td><td>iA22 </td><td> iA23 </td>
	*        </tr>
	*    <tr><td>         </td><td> iA31  </td><td>iA32 </td><td> iA33 </td>
	*        </tr>
	*        </table></tt> 
	*/
	CATMath3x3Matrix (const double iA11, const double iA12, const double iA13,
		                const double iA21, const double iA22, const double iA23,
		                const double iA31, const double iA32, const double iA33);

	/** 
	* Constructs a CATMath3x3Matrix from 3 columns.
	*/
	CATMath3x3Matrix (const CATMathVector & iFirstColumn,
		                const CATMathVector & iSecondColumn,
		                const CATMathVector & iThirdColumn);

	/** 
	* Constructs a CATMath3x3Matrix resulting from the product of a CATMathVector by  
	* the transpose of another CATMathVector.
	*/
	CATMath3x3Matrix (const CATMathVector & iFirstVector,
		                const CATMathVector & iVectorToTranspose);

	/**
	* Constructs the CATMath3x3Matrix of a rotation around a direction.
	* <br><tt>iAngle</tt> is expressed in radians. 
	*/
	CATMath3x3Matrix (const CATMathVector & iAxis, const CATAngle &iAngle);

	/**
	* Constructs the CATMath3x3Matrix of a reflection.
	*/
	CATMath3x3Matrix (const CATMathVector &iReflectPlaneNormal);

	/**
	*  Copy constructor.
	*/
	CATMath3x3Matrix (const CATMath3x3Matrix &iMatrixToCopy);

	//===========================================================================
	//- Get/Set
	//===========================================================================

	/**
	* Retrieves the coefficients of <tt>this</tt> CATMath3x3Matrix.
	* <br>
	*    <tt><table width = 40>
	*    <tr><td> Matrix= </td><td> ioA11  </td><td>ioA12 </td><td> ioA13 </td>
	*        </tr>
	*    <tr><td>         </td><td> ioA21  </td><td>ioA22 </td><td> ioA23 </td>
	*        </tr>
	*    <tr><td>         </td><td> ioA31  </td><td>ioA32 </td><td> ioA33 </td>
	*        </tr>
	*        </table></tt> 
	*/
	void GetCoef (double & ioA11, double & ioA12, double & ioA13,
		            double & ioA21,  double & ioA22,   double & ioA23,
		            double & ioA31,  double & ioA32,  double & ioA33) const ;

	/**
	* Sets the coefficients of <tt>this</tt> CATMath3x3Matrix.
	* <br>
	*    <tt><table width = 40>
	*    <tr><td> Matrix= </td><td> iA11  </td><td>iA12 </td><td> iA13 </td>
	*        </tr>
	*    <tr><td>         </td><td> iA21  </td><td>iA22 </td><td> iA23 </td>
	*        </tr>
	*    <tr><td>         </td><td> iA31  </td><td>iA32 </td><td> iA33 </td>
	*        </tr>
	*        </table></tt> 
	*/
	void SetCoef (const double iA11, const double iA12, const double iA13,
		            const double iA21, const double iA22, const double iA23,
		            const double iA31, const double iA32, const double iA33);

	/**
	* Retrieves the first column of <tt>this</tt> CATMath3x3Matrix.
	*/
	void GetFirstColumn(CATMathVector & ioFirstColumn) const;

	/** 
	* Modifies the first column of <tt>this</tt> CATMath3x3Matrix.  
	*/
	void SetFirstColumn (const CATMathVector &iFirstColumn) ;

	/**
	* Retrieves the second column of <tt>this</tt> CATMath3x3Matrix.
	*/
	void GetSecondColumn(CATMathVector & ioSecondColumn) const;

	/** 
	* Modifies the second column of <tt>this</tt> CATMath3x3Matrix.
	*/
	void SetSecondColumn (const CATMathVector &iSecondColumn) ;

	/**
	* Retrieves the third column of <tt>this</tt> CATMath3x3Matrix.
	*/
	void GetThirdColumn (CATMathVector & ioThirdColumn) const ;

	/** 
	* Modifies the third column of <tt>this</tt> CATMath3x3Matrix.
	*/
	void SetThirdColumn (const CATMathVector &iThirdColumn) ;

	/** 
	* Modifies the columns of <tt>this</tt> CATMath3x3Matrix .
	*/
	void SetMatrix (const CATMathVector & iFirstColumn,
		              const CATMathVector & iSecondColumn,
		              const CATMathVector & iThirdColumn) ;

	/**
	* Returns the diagnostic of <tt>this</tt> CATMath3x3Matrix isometry.
	* @return
	* <dl>
	* <dt><tt>FALSE</tt>        <dd>if it is not an isometry.
	* <dt><tt>TRUE</tt>        <dd>if it is a direct isometry.
	* </dl>
	*/
	CATBoolean IsIsometry() const;

	/**
	* Returns the diagnostic of <tt>this</tt> CATMath3x3Matrix scaling.
	* @return
	* <dl>
	* <dt><tt>FALSE</tt>        <dd>if it is not a scaling.
	* <dt><tt>TRUE</tt>        <dd>if it is a scaling.
	* </dl>
	*/
	CATBoolean IsScaling() const ;

	//===========================================================================
	//- Methods
	//===========================================================================

	/**
	* Returns the determinant of <tt>this</tt> CATMath3x3Matrix.
	*/
	double Determinant () const ;

	/** 
	* Returns the trace of <tt>this</tt> CATMath3x3Matrix.
	*/
	double Trace() const;

	/** 
	* Transposes <tt>this</tt> CATMath3x3Matrix.
	*/
	void Transpose(CATMath3x3Matrix & ioTransposed) const;

	/** 
	* Inverses <tt>this</tt> CATMath3x3Matrix.
	*@return 
	* <tt>TRUE</tt> if <tt>this</tt> CATMath3x3Matrix is invertible, <tt>FALSE</tt> otherwise. 
	* In this last case, <tt>oInverse</tt> is not modified.
	*/
	CATBoolean Inverse(CATMath3x3Matrix & ioInverse) const;

	/** 
	* Returns the infinite norm of <tt>this</tt> CATMath3x3Matrix.
	*<br> The infinite norm is the supremum of the absolute value of the 
	* coefficients.
	*/
	double InfiniteNorm() const;

	/**
	* Retrieves the eigenvalues and eigenvectors of <tt>this</tt> CATMath3x3Matrix.
	* @param oNbEigenValues
	* Number of eigenvalues. Multiple eigenvalues are counted as their multiplicity.
	* @param oEigenValues
	* The array of the eigenvalues. You must allocate it to 3 doubles, but the retrieved information
	* is only significant for index from 0 to <tt>oNbEigenValues-1</tt>.
	* @param oHasAssociatedVector
	* The array to test if there is an eigenvector associated with an eigenvalue. This is not
	* the case when the dimension of the associated eigenspace is less than the 
	* multiplicity of the eigenvalue. The array dimension must be 3 (and you must allocate it), 
	* but the retrieved information
	* is only significant for index from 0 to <tt>oNbEigenValues-1</tt>.
	* @param oEigenVectors
	* The array of the eigenvectors. The array dimension must be 3 (and you must allocate it),
	* but the retrieved information
	* is only significant for <tt>index</tt> from 0 to <tt>oNbEigenValues-1</tt> AND
	* <tt>oHasAssociatedVector[index]==TRUE</tt>.
	*<br> The eigenvectors are normed. 
	* @param oIsDiagonal
	* <tt>TRUE</tt> if <tt>this</tt> has 3 eigenvalues and 3 eigenvectors.
	*/
	void EigenVectors(int & ioNbEigenValues,
								    double ioEigenValues[3], CATBoolean ioHasAssociatedVector[3],
								    CATMathVector ioEigenVectors[3], CATBoolean & ioIsDiagonal) const;

	/**
	* @nodoc
	* Transform a given matrix into an isometry. Return a diagnosis :
	* - 1 : the input matrix is nearly an isometry, thus a symetric Newton algorithm has been used ;
	* - 2 : an orthonormalization (Schmidt) could have been performed correctly ;
	* - 3 : an orthonormalization has been performed, but the result may be far from the input matrix
	*       because this matrix is degenerated.
	* - 0 : failure (should not happen).
	*/
	CATLONG32 MakeIsometry (CATMath3x3Matrix & oIsometry);


	//===========================================================================
	//- Overloaded Operators
	//===========================================================================

	/**
	* Defines the addition of two CATMath3x3Matrix.
	* @return
	* The CATMath3x3Matrix whose coefficients are the sum of the coefficients
	* of two CATMath3x3Matrix.
	*/
	friend ExportedByCATMathematics CATMath3x3Matrix operator +
		(const CATMath3x3Matrix & iMatrix1, const CATMath3x3Matrix &iMatrix2);

	/**
	* Defines the subtraction of two CATMath3x3Matrix.
	* @return
	* The CATMath3x3Matrix whose coefficients are the difference of the
	*  coefficients of two CATMath3x3Matrix.
	*/
	friend ExportedByCATMathematics CATMath3x3Matrix operator -
		(const CATMath3x3Matrix &iMatrix1,
		 const CATMath3x3Matrix &iMatrixToSubstract);

	/**
	* Defines the left side scalar multiplication.
	* @return
	* The CATMath3x3Matrix whose coeffients are the multiplication of the
	* coefficients of a CATMath3x3Matrix by a scalar.
	*/
	friend ExportedByCATMathematics CATMath3x3Matrix operator *
		(const double iScalar, const CATMath3x3Matrix &iMatrix);

	/**
	* Defines the right side scalar multiplication.
	* @return
	* The CATMath3x3Matrix whose coeffients are the multiplication of the
	* coefficients of a CATMath3x3Matrix by a scalar.
	*/
	friend ExportedByCATMathematics CATMath3x3Matrix operator *
		(const CATMath3x3Matrix &iMatrix, const double iScalar);

	/**
	* Defines the scalar division.
	* @return
	* The CATMath3x3Matrix whose coeffients are the division of the
	* coefficients of a CATMath3x3Matrix by a scalar.
	*/
	friend ExportedByCATMathematics CATMath3x3Matrix operator /
		(const CATMath3x3Matrix &iMatrix, const double iScalar);

	/**
	* Defines the product of two CATMath3x3Matrix.
	*/
	friend ExportedByCATMathematics CATMath3x3Matrix operator *
		(const CATMath3x3Matrix &iMatrix1, const CATMath3x3Matrix &iMatrix2);

	/**
	* Defines the product of a CATMath3x3Matrix by a CATMathVector.
	*/
	friend ExportedByCATMathematics CATMathVector operator *
		(const CATMath3x3Matrix &iMatrix, const CATMathVector &iVector);

	/**
	* Retrieves the first column of <tt>this</tt> CATMath3x3Matrix. The signature which returns 
	* the first column in an output argument should be preferably used.
	*/
	CATMathVector GetFirstColumn () const ;

	/**
	* Retrieves the second column of <tt>this</tt> CATMath3x3Matrix. The signature which returns 
	* the second column in an output argument should be preferably used.
	*/
	CATMathVector GetSecondColumn () const ;

	/**
	* Retrieves the third column of <tt>this</tt> CATMath3x3Matrix. The signature which returns 
	* the third column in an output argument should be preferably used.
	*/
	CATMathVector GetThirdColumn () const ;

	//===========================================================================
	//- Nodoc methods
	//===========================================================================

	/**
	* @nodoc
	* @deprecated V5R20 Transpose
	* Use the  signature which returns a CATMath3x3Matrix as an output argument.
	*/
	CATMath3x3Matrix Transpose () const;

	/**
	* @nodoc
	* @deprecated V5R20 Inverse
	* <br>Throws an error if the matrix is not invertible.
	* Use the  signature which returns a CATMath3x3Matrix as an output argument.
	*/
	CATMath3x3Matrix Inverse () const;

	/**
	* @nodoc
	* @deprecated V5R20 EigenVectors
	*/
	void EigenVectors(CATLONG32 & oNbEigenValues,
		                double oEigenValues[],
								    CATMathVector oEigenVectors[]) const;

	/**
	* Dumps <tt>this</tt> CATMath3x3Matrix.
	* <br>This writes the matrix coefficients on the ostream:
	* <tt><table width = 40>
	*  <tr><td>|</td><td> iA11  </td><td>iA12 </td><td> iA13 </td><td>|</td></tr>
	*  <tr><td>|</td><td> iA21  </td><td>iA22 </td><td> iA23 </td><td>|</td></tr>
	*  <tr><td>|</td><td> iA31  </td><td>iA32 </td><td> iA33 </td><td>|</td></tr>
	* </table></tt>
	* @param iStream  
	* A pointer to the output. If <tt>0L</tt>, the method dumps 
	* on the <tt>cout</tt> output.
	*/
	void Dump(ostream * iStream=0L) const;

	/**
	* @nodoc
	* @deprecated V5R20. 
	* Use now a CATMath3x3Matrix constructor.
	*/
	friend ExportedByCATMathematics CATMath3x3Matrix operator %
		(const CATMathVector &iVector1, const CATMathVector &iVectorToTranpose);

	/**
	* @nodoc
	*/
	friend ExportedByCATMathematics CATMathPoint operator * 
		(const CATMathTransformation & t, const CATMathPoint & p);

	/**
	* @nodoc
	*/
	friend ExportedByCATMathematics CATMathVector operator * 
		(const CATMathTransformation & t, const CATMathVector & v);

	//===========================================================================
	// Private data.
	//===========================================================================
private:
	double _a11, _a12, _a13,
		     _a21, _a22, _a23,
		     _a31, _a32, _a33;
	int    _type;
};

#endif

