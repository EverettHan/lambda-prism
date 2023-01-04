#ifndef CATMathComplex_h
#define CATMathComplex_h

// COPYRIGHT DASSAULT SYSTEMES  2000

/**
* @CAA2Level L1
* @CAA2Usage U1
*/
#include <iostream.h>
#include "CATMathematics.h"
#include "CATIACGMLevel.h"
#include "CATMathInline.h"

/**
* Class representing a complex number.
* <br><tt>z = iReal+j*iImag</tt> with <tt>j*j =  -1</tt>.  
*/
class ExportedByCATMathematics CATMathComplex
{
public:

	//--------------------------------------------------------------------------
	// Constructors
	//--------------------------------------------------------------------------

	/**
	* Constructs a complex number.
	* The <tt>z = 0+j*0</tt> complex number is created.
	*/
	CATMathComplex ();

	/**
	* Constructs a complex number from two doubles, the real and the imaginary parts.
	* Constructs a complex number from <tt>iReal</tt> and <tt>iImag</tt>.
	* <br> <tt>z = iReal+j*iImag</tt>. 
	*/
	INLINE CATMathComplex (const double &iReal, const double &iImag);

	/**
	* Constructs a complex number from a real and zero as imaginary part.
	* <br> <tt>z = iReal</tt>. 
	*/
	CATMathComplex (double iReal);

	/**
	* Copy constructor.
	*/
	CATMathComplex (const CATMathComplex & iComplex);

	/**
	* Constructs a complex number from an array of two coordinates.
	* <br><tt>z = iCoord[0]+j*iCoord[1]</tt>. 
	*/
	CATMathComplex (const double iCoord[2]);

	//--------------------------------------------------------------------------
	// Read Coordinates
	//--------------------------------------------------------------------------
	/**
	* Returns the real part of a complex number.
	* @return
	* The real part.
	*/
	INLINE double GetReal () const;

	/**
	* Returns the imaginary part of a complex number.
	* @return
	* The imaginary part.
	*/
	INLINE double GetImag () const;

	/**
	* Retrieves the real and imaginary parts of a complex number.
	* <br><tt>z = ioReal+j*ioImag</tt>. 
	*/
	INLINE void GetCoord (double & ioReal, double & ioImag) const;


	//--------------------------------------------------------------------------
	// Set Coordinates
	//--------------------------------------------------------------------------
	/**
	* Sets the real part of a complex number.
	*/
	INLINE void SetReal (const double &iReal);
	
	/**
	* Sets the imaginary part of a complex number.
	*/
	INLINE void SetImag (const double &iImag);

	/**
	* Sets the real and imaginary parts of a complex number.
	*/
	INLINE void SetCoord (const double &iReal, const double &iImag);

	//--------------------------------------------------------------------------
	// Overloaded Operators
	//--------------------------------------------------------------------------

	/**
	* Addition operator.
	*/   
	CATMathComplex operator + (const CATMathComplex & iComp2) const;

	/**
	* Addition assignment operator.
	* <br>The operator modifies <tt>this</tt> complex number.
	*/
	CATMathComplex & operator += (const CATMathComplex & iComp);

	/**
	* Subtraction operator.
	*/
	CATMathComplex operator - (const CATMathComplex & iComp2) const;

	/**
	* Subtraction assignment operator.
	* <br>The operator modifies <tt>this</tt> complex number.
	*/
	CATMathComplex & operator -= (const CATMathComplex & iComp);

	/**
	* Multiplication operator.
	*/   
	CATMathComplex operator * (const CATMathComplex & iComp2) const;

	/**
	* Multiplication assignment operator.
	* <br>The operator modifies <tt>this</tt> complex number.
	*/
	CATMathComplex& operator *= (const CATMathComplex & iComp);

	/**
	* Division operator.
	*/
	CATMathComplex operator / (const CATMathComplex & iComp2) const;

	/**
	* Division assignment operator.
	* <br>The operator modifies <tt>this</tt> complex number.
	*/
	CATMathComplex & operator /= (const CATMathComplex & iComp);

	/**
	* Computes the conjugate of <tt>this</tt> complex number.
	*/
	INLINE void Conjugate( );

	/**
	* Computes the inverse of <tt>this</tt> complex number.
	* <br>If the norm is null, <tt>this</tt> is modified.
	*/
	void Inverse( ); 

	/**
	* Returns the square modulus of <tt>this</tt> complex number.
	* @return
	* <tt>iReal^2 + iImag^2</tt>.
	*/
	double SquareModulus( ) const;

	/**
	* Returns the modulus of <tt>this</tt> complex number.
	* @return
	* <tt>sqrt(iReal^2 + iImag^2)</tt>. 
	*/
	double Modulus( ) const;

	/**
	* Normalizes <tt>this</tt> complex number.
	*/
	void Normalize( );

private:  
	double _x, _y;
};
//======================================================================
// INLINE IMPLEMENTATIONS
//======================================================================
INLINE CATMathComplex::CATMathComplex(const double& iReal,const double& iImag)
{_x = iReal;_y = iImag;}
INLINE double CATMathComplex::GetReal() const { return _x; }
INLINE double CATMathComplex::GetImag() const { return _y; }
INLINE void CATMathComplex::GetCoord (double & ioReal, double & ioImag) const {ioReal = _x;ioImag = _y;}
INLINE void CATMathComplex::SetReal( const double & iReal ) { _x = iReal; }
INLINE void CATMathComplex::SetImag( const double & iImag)  { _y = iImag; }
INLINE void CATMathComplex::SetCoord(const double& iReal,const double& iImag) { _x = iReal; _y = iImag; }

INLINE void CATMathComplex::Conjugate() { _x = _x; _y = -_y; }



#endif

