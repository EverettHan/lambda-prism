#ifndef CATMathComplexf_h
#define CATMathComplexf_h

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
 * Class representing a complex number in float.
 * <br><tt>z = iReal+j*iImag</tt> with <tt>j*j =  -1</tt>.  
 */
class ExportedByCATMathematics CATMathComplexf
{
 public:
   
//--------------------------------------------------------------------------
// Constructors
//--------------------------------------------------------------------------
   
   /**
    * Construct the <tt>z = 0+j*0</tt> complex number.
    */
   CATMathComplexf ();
   

   /**
    * Constructs a complex number from <tt>iReal</tt> and <tt>iImag</tt>.
    * <br> <tt>z = iReal+j*iImag</tt>. 
    */
   INLINE CATMathComplexf (const float& iReal,const float& iImag);

   /**
    * Constructs a complex number from <tt>iReal</tt> and <tt>Imag=0</tt>.
    * <br> <tt>z = iReal</tt>. 
    */
   CATMathComplexf (float iReal);
     
   /**
    * Copy constructor.
    */
   CATMathComplexf (const CATMathComplexf & iComplex);
   
   /**
    * Constructs a complex number from an array of two coordinates.
    * <br><tt>z = iCoord[0]+j*iCoord[1]</tt>. 
    */
   CATMathComplexf (const float iCoord[2]);
   
   //--------------------------------------------------------------------------
   // Read Coordinates
   //--------------------------------------------------------------------------
   
   
   /**
    * Returns the real part of <tt>this</tt> complex number.
    * @return
    * The real part.
    */
   INLINE float GetReal () const;
   
   /**
   * Returns the imaginary part of <tt>this</tt> complex number.
   * @return
   * The imaginary part.
   */
   INLINE float GetImag () const;

    /**
    * Retrieves the real and imaginary parts of <tt>this</tt> complex number.
    * <br><tt>z = ioReal+j*ioImag</tt>. 
    */
    INLINE void GetCoord (float & ioReal, float & ioImag) const;

   //--------------------------------------------------------------------------
   // Set Coordinates
   //--------------------------------------------------------------------------

  
   /**
   * Sets the real part of <tt>this</tt> complex number.
   */
   INLINE void SetReal (const float& iReal);
   

   /**
   * Sets the imaginary part of <tt>this</tt> complex number.
   */
   INLINE void SetImag (const float& iImag);
  
    /**
   * Sets the real and imaginary parts of <tt>this</tt> complex number.
   */
   INLINE void SetCoord (const float& iReal,const float& iImag);

   //--------------------------------------------------------------------------
   // Overloaded Operators
   //--------------------------------------------------------------------------

   /**
    * Addition operator.
    */   
   CATMathComplexf operator + (const CATMathComplexf & iComp2) const;
  
   /**
    * Addition assignment operator.
    * <br>The operator modifies <tt>this</tt> complex number.
    */
   CATMathComplexf & operator += (const CATMathComplexf & iComp);
   
   /**
    * Subtraction operator.
    */
   CATMathComplexf operator - (const CATMathComplexf & iComp2) const;

   /**
    * Subtraction assignment operator.
    * <br>The operator modifies <tt>this</tt> complex number.
    */
   CATMathComplexf & operator -= (const CATMathComplexf & iComp);
   
   /**
    * Multiplication operator.
    */   
   CATMathComplexf operator * (const CATMathComplexf & iComp2) const;
  
   /**
    * Multiplication assignment operator.
    * <br>The operator modifies <tt>this</tt> complex number.
    */
   CATMathComplexf& operator *= (const CATMathComplexf & iComp);
   
   /**
    * Division operator.
    */
   CATMathComplexf operator / (const CATMathComplexf & iComp2) const;
   
   /**
    * Division assignment operator.
    * <br>The operator modifies <tt>this</tt> complex number.
    */
   CATMathComplexf & operator /= (const CATMathComplexf & iComp);
     
   

   /**
    * Computes the conjugate of <tt>this</tt> complex number.
    */
   INLINE void Conjugate( );

   /**
    * Computes the inverse of <tt>this</tt> complex number.
    * <br>If the norm is null, <tt>this</tt> is set to null.
    */
   void Inverse( ); 

   /**
    * Returns the square modulus of <tt>this</tt> complex number.
    * @return
    * <tt>iReal^2 + iImag^2</tt>.
    */
   float SquareModulus( ) const;

   /**
    * Returns the modulus of <tt>this</tt> complex number.
    * @return
    * <tt>sqrt(iReal^2 + iImag^2)</tt>. 
    */
   float Modulus( ) const;

   /**
    * Normalizes <tt>this</tt> complex number.
    */
   void Normalize( );
   
 private:  
   float _x, _y;
};
//======================================================================
// INLINE IMPLEMENTATIONS
//======================================================================
INLINE CATMathComplexf::CATMathComplexf(const float& iReal,const float& iImag)
{_x = iReal;_y = iImag;}
INLINE float CATMathComplexf::GetReal() const { return _x; }
INLINE float CATMathComplexf::GetImag() const { return _y; }
INLINE void CATMathComplexf::GetCoord (float & ioReal, float & ioImag) const {ioReal = _x;ioImag = _y;}
INLINE void CATMathComplexf::SetReal( const float & iReal ) { _x = iReal; }
INLINE void CATMathComplexf::SetImag( const float & iImag)  { _y = iImag; }
INLINE void CATMathComplexf::SetCoord(const float& iReal,const float& iImag) { _x = iReal; _y = iImag; }

INLINE void CATMathComplexf::Conjugate() { _x = _x; _y = -_y; }

#endif
