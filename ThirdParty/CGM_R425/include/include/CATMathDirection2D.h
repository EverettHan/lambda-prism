#ifndef CATMATHDIRECTION2D_H
#define CATMATHDIRECTION2D_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 


#include "CATMathematics.h"
#include "CATMathInline.h"

#include "CATMathVector2D.h"
/**
 * Defines a normalized vector in 2D space.
 * Use now a CATMathVector2D and normalize it if needed.
 */ 
class ExportedByCATMathematics CATMathDirection2D : public CATMathVector2D
{
    public :
//============================================================================
//- Constructors
//============================================================================
/**
 * Constructs a (1,0) vector.
 */
    CATMathDirection2D ();

/**
 * Constructs a CATMathDirection2D from two coordinates.
 */
    CATMathDirection2D (const double iFirstCoord,
                        const double iSecondCoord);

/**
 * Copy constructor.
 */
    CATMathDirection2D (const CATMathDirection2D & iDirectionToCopy);

/**
 * Constructs a CATMathDirection2D from a CATMathVector2D.
 */
    CATMathDirection2D (const CATMathVector2D & iVectorToCopy);
//============================================================================
//- Read
//============================================================================
/**
 * Retrieves the CATMathDirection2D coordinates in two doubles.
 */
    void GetCoord( double & ioFirstCoord, double & ioSecondCoord) const;

/**
 * Retrieves the CATMathDirection2D coordinates in an array of two doubles.
 * @param ioCoord
 * The array of 2 doubles that must be previously allocated.
 */
    void GetCoord (double ioCoord[]) const;

//============================================================================
//- Set
//============================================================================
/**
 * Modifies the CATMathDirection2D coordinates from two doubles.
 */
    void SetCoord ( const double iFirstCoord, const double iSecondCoord);

/**
 * Modifies the CATMathDirection2D coordinates from an array of two doubles.
 */
    void SetCoord (const double iCoord[]);

/** 
 * Modifies the CATMathDirection2D first coordinate.
 */
    void SetX (const double iFirstCoord);

/** 
 * Modifies the CATMathDirection2D second coordinate.
 */
    void SetY (const double iSecondCoord);

//============================================================================
//  Scalar Multiplication :
// the friend function is redefined here to avoid ambiguity
//===========================================================================
/**
 * Defines the left side scalar muliplication.
 */
friend ExportedByCATMathematics CATMathVector2D operator *
  (double iScalar, const CATMathDirection2D & iVector);


/**
 * Defines the opposite of a CATMathVector2D.
 */
INLINE CATMathDirection2D operator - () const;

};
//============================================================================
/**
 * The 2D first canonical direction.
 */
extern ExportedByCATMathematics const CATMathDirection2D CATMathI2D;
/**
 * The 2D second canonical direction.
 */
extern ExportedByCATMathematics const CATMathDirection2D CATMathJ2D;


//=============================================================================
// INLINE IMPLEMENTATIONS
//=============================================================================

INLINE CATMathDirection2D CATMathDirection2D::operator - () const
{
	CATMathDirection2D OppDir(*this);
	OppDir._x*=-1.;
	OppDir._y*=-1.;
  return OppDir;
}


#endif
