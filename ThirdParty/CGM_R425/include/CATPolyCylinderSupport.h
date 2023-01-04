// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyCylinderSupport.h
//
//===================================================================
// March 2009  Creation: NDO
// May 2011 Revisited: NDO
//===================================================================
#ifndef CATPolyCylinderSupport_H
#define CATPolyCylinderSupport_H

#include "PolySupports.h"
#include "CATIPolyPrimitiveSupport.h"
#include "CATPolyMathCylinderSurface.h"
#include "CATMathPoint.h"
#include "CATMathVector.h"
#include "CATAssert.h"


/**
 * Class implementing a support as a cylinder primitive.
 */
class ExportedByPolySupports CATPolyCylinderSupport : public CATIPolyPrimitiveSupport
{

public:

  /**
   * Constructs a cylinder primitive support from a math cylinder surface and the height limits along the axis.
   * @param iCylinder
   *   The input cylinder surface.
   * @param iHeightMin
   *   The minimum height along the axis of the cylinder from its origin.
   * @param iHeighMax
   *   The maximum height along the axis of the cylinder from its origin.
   */
  CATPolyCylinderSupport (const CATPolyMathCylinderSurface& iCylinder, const double iHeightMin, const double iHeightMax);

  virtual ~CATPolyCylinderSupport ();

public:

  static const CATPolyCylinderSupport* Cast (const CATIPolyLayer*);
  static CATPolyCylinderSupport* Cast (CATIPolyLayer*);

  static const CLSID& ClassID ();
  const CLSID& GetClassID () const;

public:

  inline const CATPolyMathCylinderSurface& GetCylinderSurface () const;

  inline const CATMathVector& GetAxis () const;

  inline const CATMathPoint& GetOrigin () const;

  inline double GetRadius () const;

  inline double GetMinHeight () const;

  inline double GetMaxHeight () const;

public:

  Type GetType () const;
  const CATPolyCylinderSupport* CastAsCylinderSupport () const;

protected:

  CATPolyMathCylinderSurface* _CylinderSurface;
  double _HeightMin;
  double _HeightMax;

};

inline const CATPolyMathCylinderSurface& CATPolyCylinderSupport::GetCylinderSurface () const
{
  CATAssert (_CylinderSurface);
  return *_CylinderSurface;
}

inline const CATMathVector& CATPolyCylinderSupport::GetAxis () const
{
  CATAssert (_CylinderSurface);
  return _CylinderSurface->GetAxis ();
}

inline const CATMathPoint& CATPolyCylinderSupport::GetOrigin () const
{
  CATAssert (_CylinderSurface);
  return _CylinderSurface->GetOrigin ();
}

inline double CATPolyCylinderSupport::GetRadius () const
{
  const CATPolyMathCylinderSurface& cylinderSurface = *_CylinderSurface;
  return cylinderSurface.GetRadius ();
}

inline double CATPolyCylinderSupport::GetMinHeight () const
{
  return _HeightMin;
}

inline double CATPolyCylinderSupport::GetMaxHeight () const
{
  return _HeightMax;
}

#endif // !CATPolyCylinderSupport_H
