#ifndef CATMathAxis2D_H
#define CATMathAxis2D_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATMathematics.h"
#include "CATErrorDef.h" //HRESULT

#include "CATMathPoint2D.h"
#include "CATMathDirection2D.h"

/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

/**
 * Class representing a mathematical axis system in dimension 2.
 * <b>Role</b>:
 * <br>It is composed of an <tt>Origin</tt>, and of two directions 
 * (normalized vectors) <tt>FirstDirection</tt>, <tt>SecondDirection</tt>.
 * If the two directions are not directly
 * orthogonal or normalized, it will be done internally.
 */ 
class ExportedByCATMathematics CATMathAxis2D
{
 public:
//============================================================================
//- Constructors
//============================================================================
/**
 * Constructs a canonical CATMathAxis2D.
 *<br><tt>Origin=(0,0)</tt>, <tt>FirstDirection = (1,0)</tt>, 
 * <tt>SecondDirection =(0,1)</tt>.
 */ 
  CATMathAxis2D ();

/**
 * @nodoc
 * @deprecated V5R20 Set
 * Constructs CATMathAxis2D from a CATMathPoint2D and two CATMathVector2D.
 * <br>The input vectors must not be colinear, but this is not checked.
 */
  CATMathAxis2D (const CATMathPoint2D & iOrigin,
                               const CATMathVector2D & iFirstDirection,
                               const CATMathVector2D & iSecondDirection);

/**
 * Copy constructor.
 */
   CATMathAxis2D (const CATMathAxis2D & iAxisToCopy);

//============================================================================
//- Get/Set
//============================================================================

/** 
 * Retrieves the two (orthonormalized) directions of <tt>this</tt> CATMathAxis2D.
 */
  void GetDirections (CATMathVector2D & ioFirstDirection,
                                  CATMathVector2D & ioSecondDirection) const;

/**
 * Modifies the directions of <tt>this</tt> CATMathAxis2D.
 * @return
 * <tt>FALSE</tt> if the input vectors are colinear, <tt>TRUE</tt> otherwise.
 */
  CATBoolean SetDirections (const CATMathVector2D & iFirstDirection,
                                                const CATMathVector2D & iSecondDirection);

  /**
  * Modifies CATMathAxis2D from a CATMathPoint2D and two CATMathVector2D.
  * @return
 * <tt>FALSE</tt> if the input vectors are colinear, <tt>TRUE</tt> otherwise.
  */
  HRESULT Set(const CATMathPoint2D & iOrigin,
                           const CATMathVector2D & iFirstDirection,
                           const CATMathVector2D & iSecondDirection);

/** 
 * Returns the origin of <tt>this</tt> CATMathAxis2D.
 */
   void GetOrigin (CATMathPoint2D & ioOrigin) const;
   
/**
 * Modifies the origin of <tt>this</tt> CATMathAxis2D.
 */
  void SetOrigin (const CATMathPoint2D & iOrigin);

/** 
 * Returns the first (normalized) direction of <tt>this</tt> CATMathAxis2D.
 */
  void GetFirstDirection (CATMathVector2D & ioFirstDirection) const;

/** 
 * Returns the second (normalized) direction of <tt>this</tt> CATMathAxis2D.
 */
  void GetSecondDirection (CATMathVector2D & ioSecondDirection) const;

//===========================================================================
//- Deprecated
//===========================================================================

  /**
  * @nodoc
  * @deprecated V5R20.
  * Dumps <tt>this</tt> CATMathAxis2D.
  * <br>This writes the following lines on the ostream:
  *<pre>
  * Origin    = ( OriginFirstCoord    , OriginSecondCoord   )
  * FirstDir  = ( FirstDirFirstCoord  , FirstDirSecondCoord )
  * SecondDir = ( SecondDirFirstCoord , SecondDirSecondCoord )
  *</pre>
  * @param iStream  
  * A pointer to the output. If <tt>0L</tt>, the method dumps the 
  * coordinates on the <tt>cout</tt> output.
  */
  void Dump(ostream * iStream=0L) const;


  /**
  * @nodoc
  * @deprecated V5R20 GetOrigin
  * Use the  signature which returns a CATMathPoint2D as an output argument.
  */
  CATMathPoint2D GetOrigin () const;

  /**
  * @nodoc
  * @deprecated V5R20 GetFirstDirection
  * Use the  signature which returns a CATMathVector2D as an output argument.
  */
     CATMathDirection2D GetFirstDirection () const;

  /**
  * @nodoc
  * @deprecated V5R20 GetSecondDirection
  * Use the  signature which returns a CATMathVector2D as an output argument.
  */
  CATMathDirection2D GetSecondDirection () const;

//===========================================================================
//- Private data
//===========================================================================
 private :
  CATMathVector2D _FirstAxis, _SecondAxis;
  CATMathPoint2D   _Origin;
};

#endif
