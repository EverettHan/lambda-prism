// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolySphereSupport.h
//
//===================================================================
// March 2009  Creation: NDO
// May 2011 Revisited: NDO
//===================================================================
#ifndef CATPolySphereSupport_H
#define CATPolySphereSupport_H

#include "PolySupports.h"
#include "CATIPolyPrimitiveSupport.h"
#include "CATPolyMathSphereSurface.h"
#include "CATMathPoint.h"


/**
 * Class implementing a support as a sphere primitive.
 */
class ExportedByPolySupports CATPolySphereSupport : public CATIPolyPrimitiveSupport
{
public:

  /**
   * Constructs a sphere primitive support from a math sphere surface.
   * @param iSphere
   *   The input sphere surface.
   */
  CATPolySphereSupport (const CATPolyMathSphereSurface& iSphere);

  CATPolySphereSupport (const CATMathPoint& iCenter, const double iRadius);

  virtual ~CATPolySphereSupport ();

public:

  static const CATPolySphereSupport* Cast (const CATIPolyLayer*);
  static CATPolySphereSupport* Cast (CATIPolyLayer*);

  static const CLSID& ClassID ();
  const CLSID& GetClassID () const;

public:

  inline const CATPolyMathSphereSurface& GetSphereSurface () const;

  inline const CATMathPoint& GetCenter () const;

  inline double GetRadius () const;

public:

  Type GetType () const;
  const CATPolySphereSupport* CastAsSphereSupport () const;

protected:

  CATPolyMathSphereSurface* _SphereSurface;

};

inline const CATPolyMathSphereSurface& CATPolySphereSupport::GetSphereSurface () const
{
  const CATPolyMathSphereSurface& sphereSurface = *_SphereSurface;
  return sphereSurface;
}

inline const CATMathPoint& CATPolySphereSupport::GetCenter () const
{
  const CATPolyMathSphereSurface& sphereSurface = *_SphereSurface;
  return sphereSurface.GetCenter ();
}

inline double CATPolySphereSupport::GetRadius () const
{
  const CATPolyMathSphereSurface& sphereSurface = *_SphereSurface;
  return sphereSurface.GetRadius ();
}

#endif // !CATPolySphereSupport_H
