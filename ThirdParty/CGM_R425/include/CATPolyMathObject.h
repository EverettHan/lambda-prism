// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMathObject.h
//
//===================================================================
// May 2007  Creation: ndo
//===================================================================
#ifndef CATPolyMathObject_H
#define CATPolyMathObject_H

#include "PolyMathCurves.h"
#include "CATRefCounted.h"

class CATPolyMathCurve;
class CATPolyMathSurface;
class CATPolyMathQuadSurface;
class CATPolyMathTriangleSurface;


/**
 * Base class from which all math curve and surface classes derive.
 */
class ExportedByPolyMathCurves CATPolyMathObject : public CATRefCounted
{

public:

  /**
   * Type of the math objects (same types as those defined in CATIPolySupport.)
   */
  enum Type
  {
    /** Unknown type. */                                                   eUnknown                = 0x0,

    /** CATPolyMathObject::ePoint */                                       ePoint                  = 0x00000010,
    /** CATPolyMathObject::eMathPoint */                                   eMathPoint              = 0x00000011,
    /** CATPolyMathObject::eCGMPoint */                                    eCGMPoint               = 0x00000031,
    /** CATPolyMathObject::eCGMVertex */                                   eCGMVertex              = 0x00000032,

    /** CATPolyMathObject::eCurve */                                       eCurve                  = 0x00001000,
    /** CATPolyMathObject::eMathCurve */                                   eMathCurve              = 0x00001100,
    /** CATPolyMathObject::eLine */                                        eLine                   = 0x00001200,
    /** CATPolyMathObject::ePolyLine */                                    ePolyLine               = 0x00001300,
    /** CATPolyMathObject::eCircle */                                      eCircle                 = 0x00001400,
    /** CATPolyMathObject::eCubicBezierCurve */                            eCubicBezierCurve       = 0x00001500,
    /** CATPolyMathObject::eCubicBSplineCurve */                           eCubicBSplineCurve      = 0x00001600,
    /** CATPolyMathObject::eCubicBSplineIsopar */                          eCubicBSplineIsopar     = 0x00001700,
    /** CATPolyMathObject::eInQuad */                                      eInQuad                 = 0x00001800,
    /** CATPolyMathObject::eTriangleSide */                                eTriangleSide           = 0x00001900,
    /** CATPolyMathObject::eCGMCurve */                                    eCGMCurve               = 0x00003100,
    /** CATPolyMathObject::eCGMEdge */                                     eCGMEdge                = 0x00003200,

    /** CATPolyMathObject::eSurface */                                     eSurface                = 0x00100000,
    /** CATPolyMathObject::eMathSurface */                                 eMathSurface            = 0x00110000,
    /** CATPolyMathObject::ePlane */                                       ePlane                  = 0x00120000,
    /** CATPolyMathObject::eCylinder */                                    eCylinder               = 0x00130000,
    /** CATPolyMathObject::eSphere */                                      eSphere                 = 0x00140000,
    /** CATPolyMathObject::eTorus */                                       eTorus                  = 0x00150000,
    /** CATPolyMathObject::eCone */                                        eCone                   = 0x00160000,
    /** CATPolyMathObject::eCubicBSplineSurface */                         eCubicBSplineSurface    = 0x00170000,
    /** CATPolyMathObject::eTriangleSurface */                             eTriangleSurface        = 0x00180000,
    /** CATPolyMathObject::ePNTTriangleSurface */                          ePNTTriangleSurface     = 0x00190000,
    /** CATPolyMathObject::eSolidOfRevolution */                           eSolidOfRevolution      = 0x001A0000,
    /** CATPolyMathObject::eCGMSurface */                                  eCGMSurface             = 0x00310000,
    /** CATPolyMathObject::eCGMFace */                                     eCGMFace                = 0x00320000,

    /** CATPolyMathObject::ePrimitive */                                   ePrimitive              = 0x10000000,
    /** CATPolyMathObject::ePrimitiveBox */                                ePrimitiveBox           = 0x11000000,
    /** CATPolyMathObject::ePrimitiveSphere */                             ePrimitiveSphere        = 0x12000000,
    /** CATPolyMathObject::ePrimitiveCylinder */                           ePrimitiveCylinder      = 0x14000000,
    /** CATPolyMathObject::ePrimitiveConicCapsule */                       ePrimitiveConicCapsule  = 0x18000000,
  };

public:

  /**
   * Returns the type of the math object.
   */
  virtual Type GetType () const = 0;

public:

  virtual const CATPolyMathCurve* CastAsCurve () const;
  virtual const CATPolyMathSurface* CastAsSurface () const;
  virtual const CATPolyMathQuadSurface* CastAsQuadSurface () const;
  virtual const CATPolyMathTriangleSurface* CastAsTriangleSurface () const;

  virtual CATPolyMathCurve* CastAsCurve ();
  virtual CATPolyMathSurface* CastAsSurface ();
  virtual CATPolyMathQuadSurface* CastAsQuadSurface ();
  virtual CATPolyMathTriangleSurface* CastAsTriangleSurface ();

protected:

  CATPolyMathObject () {}
  virtual ~CATPolyMathObject () {}

};

#endif
