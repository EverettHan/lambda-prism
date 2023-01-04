#ifndef CATMathDirBox_h
#define CATMathDirBox_h

// COPYRIGHT : DASSAULT SYSTEMES 1997

#include "YN000MAT.h"

#include "CATMath.h"
#include "CATMathDef.h"
#include "CATMathDirection.h"
#include "CATMathInline.h"

/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif
/**
 * Class representing a 3-dimensional right circular cone box.
 *<br> It is used for surrounding the normals of a surface.
 * It is defined by
 * a direction and an angle between <tt>0</tt> and <tt>pi;</tt> expressed
 * in radians, representing the half angular sector of the box.
 */
class ExportedByYN000MAT CATMathDirBox
{
public:
//======================================================================
//  CONSTRUCTORS AND DESTRUCTOR
//======================================================================
// Default constructor : constructs an empty box
/**
 * Constructs en empty CATMathDirBox with no valuated data.
 *<br>This is mainly used for array creation. To request an empty
 * CATMathDirBox leads to an exception, except for the IsEmpty
 * method.
 */
  CATMathDirBox(); 
  
/**
 * Constructs a CATMatDirBox from a direction and an angle.
 */
  CATMathDirBox(const CATMathDirection  &iCenterPosition,
                const CATAngle iAngularSector );

/**
 * Copy Constructor.
 */
  CATMathDirBox(const CATMathDirBox &iBoxToCopy);

//======================================================================
// SET AND GET 
//======================================================================
/**
 * Returns <tt>0</tt> is the CATMathDirBox is not empty.
 */ 
  INLINE CATBoolean IsEmpty() const;

/**
 * Resets the data of a CATMathDirBox.
 */ 
  INLINE void SetToEmpty();

/**
 * Returns the center direction of the cone.
 */
  INLINE CATMathDirection GetPosition () const ;

/**
 * Retrieves the center direction of the cone.
 */
  INLINE void GetPosition ( CATMathDirection  &oCenterPosition ) const ;

/**
 * Modifies the center direction of the cone.
 */
  INLINE void SetPosition ( const CATMathDirection  &iCenterPosition ) ;

/**
 * Returns the angle of the half angular sector of the cone, expressed in radians.
 */
  INLINE CATAngle GetSize (  ) const ;

/**
 * Modifies the angular sector of the cone, expressed in radians.
 */
  INLINE void SetSize ( const CATAngle iHalfAngularSector ) ;

//=====================================================================
// COMPUTATION THAT MODIFIES THE BOX
//======================================================================
/**
 * Replaces a CATMathDirBox with the union of two other
 * CATMathDirBoxs.
 */
  void SetToUnion(const CATMathDirBox &iBox1, const CATMathDirBox &iBox2);

/**
 * Modifies a CATMathDirBox by forcing a CATMathDirection to belong to
 * this CATMathDirBox.
 */
  void AddInside(const CATMathDirection &iDirection);

/**
 * Replaces a CATMathDirBox with the intersection of two other
 * CATMathDirBoxs.
 *<br>It can lead to an empty CATMathDirBox.
 */
  // void SetToIntersection(const CATMathDirBox &iBox1, const CATMathDirBox &iBox2);

//======================================================================
// COMPUTATION WITH A BOX THAT RETURNS A RESULT
//======================================================================
/**
 * Returns <tt>1</tt> if the CATDirMathBox is intersecting an another one.
 *<br> Note that if the intersection is a line, the
 * result is true.
 */
  CATBoolean IsIntersecting(const CATMathDirBox &iBox) const;

/**
 * Returns <tt>1</tt> if the CATMathDirBox is containing a 
 * CATMathDirection.
 */
  CATBoolean IsContaining(const CATMathDirection &iDirection) const;

/**
 * Returns <tt>1</tt> if the CATMathDirbox is completely containing an other
 * CATMathDirBox.
 *<br>Note that the empty CATMathDirBox is contained by all CATMathDirBoxs
 * and does
 * not contain any CATMathDirBoxs, even an empty one.
 */
  CATBoolean IsContaining(const CATMathDirBox &iDirBox) const;


//======================================================================
// For Debug
//======================================================================
/**
 * Dumps a CATMathDirBox.
 * <br>This writes the following on the ostream:
 * <dl><dt><tt>Empty CATMathDirBox </tt> <dd> If the box is empty. 
 *     <dt><pre>
 *Direction = ( FirstCoord  , SecondCoord  , ThirdCoord ), 
 *HalfAngle = Angle radians</pre>     
 *     <dd> If the box is not empty.</dl>
 * @param iStream
 * A pointer to the output. If <tt>0L</tt>, the method dumps 
 * on the <tt>cout</tt> output.
 */
    void Dump(ostream * iStream=0L) const;
/**
 * Use now the Dump() method.
 */
  friend ExportedByYN000MAT ostream& operator << (ostream& s,
                                                  const CATMathDirBox & iBox);

//======================================================================
// INTERNAL DATAS
//======================================================================

private:

  CATMathDirection _Position ;
  CATAngle         _Size ;
  short _Empty;

};

//======================================================================
// INLINE IMPLEMENTATIONS
//======================================================================
INLINE CATBoolean CATMathDirBox::IsEmpty() const
{
  return _Empty ? 1 : 0;
}

INLINE void CATMathDirBox::SetToEmpty()
{
  _Empty=1;
}

INLINE CATMathDirection CATMathDirBox::GetPosition () const
{
  return _Position ;
}

INLINE void CATMathDirBox::GetPosition ( CATMathDirection  &oPosition ) const
{
  oPosition = _Position ;
} 

INLINE void CATMathDirBox::SetPosition ( const CATMathDirection  &iPosition ) 
{ 
  if ( _Empty )
    {
      _Size = 0. ;
      _Empty = 0 ;
    }
  _Position = iPosition ; 
}

INLINE CATAngle CATMathDirBox::GetSize (  ) const
{
  return _Size ;
}

INLINE void CATMathDirBox::SetSize ( const CATAngle iSize ) 
{  
  if ( _Empty )
    {
      _Position = CATMathK ;
      _Empty = 0 ;
    }
  _Size = CATMin ( CATMax( 0., iSize), CATPI ) ; 
}

#endif
