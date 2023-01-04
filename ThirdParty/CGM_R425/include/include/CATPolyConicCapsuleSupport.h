// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyConicCapsuleSupport.h
//
//===================================================================
// 2010-09-21  XXC: Creation
// 2011-05-17  NDO: Revisited
//===================================================================
#ifndef CATPolyConicCapsuleSupport_H
#define CATPolyConicCapsuleSupport_H

#include "PolySupports.h"
#include "CATIPolyPrimitiveSupport.h"

#include "CATMathPoint.h"
#include "CATMathVector.h"


/**
 * Class implementing a support as a conic-capsule primitive.
 * A conic-capsule primitive is defined a conic-cylinder capped by two partial spheres
 * (not quite half-spheres if tangency between the spheres and conic-cylinder is preserved.)
 * The radius of the spheres are not necessarily the same.  If they are the same, then
 * the primitive is a standard capsule.
 */
class ExportedByPolySupports CATPolyConicCapsuleSupport : public CATIPolyPrimitiveSupport
{

public:

  /**
   * Constructs of a CATPolyConicCapsuleSupport.
   */
  CATPolyConicCapsuleSupport (const CATMathPoint& iFirstOrigin, const CATMathPoint& iSecondOrigin, 
                                     const double iFirstRadius, const double iSecondRadius);

  virtual ~CATPolyConicCapsuleSupport () {}

public:

  static const CATPolyConicCapsuleSupport* Cast (const CATIPolyLayer*);
  static CATPolyConicCapsuleSupport* Cast (CATIPolyLayer*);

  static const CLSID& ClassID ();
  const CLSID& GetClassID () const;

public:

  inline const CATMathPoint& GetFirstOrigin () const;
  inline const CATMathPoint& GetSecondOrigin () const;
  inline const double GetFirstRadius () const;
  inline const double GetSecondRadius () const;
  inline const double GetHeight () const;

  inline const CATMathVector& GetU () const;
  inline const CATMathVector& GetV () const;
  inline const CATMathVector& GetW () const;

public:

  Type GetType () const;
  const CATPolyConicCapsuleSupport* CastAsConicCapsuleSupport () const;

protected:

  CATMathVector _U, _V, _W;  // The main axis of the capsule.  The _W axis is the axis of the conic-cylinder.
  CATMathPoint _Center1;  // Center of the first sphere.
  CATMathPoint _Center2;  // Center of the second sphere.
  double _Radius1;  // Radius of the first sphere.
  double _Radius2;  // Radius of the second sphere.
  double _Height;  // Height of the capsule (more detailed definition?)

};

inline const CATMathPoint& CATPolyConicCapsuleSupport::GetFirstOrigin () const
{
  return _Center1;
}

inline const CATMathPoint& CATPolyConicCapsuleSupport::GetSecondOrigin () const
{
  return _Center2;
}

inline const double CATPolyConicCapsuleSupport::GetFirstRadius () const
{
  return _Radius1;
}

inline const double CATPolyConicCapsuleSupport::GetSecondRadius () const
{
  return _Radius2;
}

inline const double CATPolyConicCapsuleSupport::GetHeight () const
{
  return _Height;
}

inline const CATMathVector& CATPolyConicCapsuleSupport::GetU () const
{
  return _U;
}

inline const CATMathVector& CATPolyConicCapsuleSupport::GetV () const
{
  return _V;
}

inline const CATMathVector& CATPolyConicCapsuleSupport::GetW () const
{
  return _W;
}

#endif // !CATPolyConicCapsuleSupport_H
