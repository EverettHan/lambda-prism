// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolySupport.h
//
//===================================================================
// March 2009  Creation: NDO
//===================================================================
#pragma once

#include "PolyhedralAttributes.h"
#include "CATIPolyLayer.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"
//#include "CATPolyMathObject.h"

class CATIPolyPointSupport;
class CATIPolyCurveSupport;
class CATIPolySurfaceSupport;
class CATIPolyPrimitiveSupport;

class CATPolyGPSupport;  // Do not use. (Private use.)
class CATPolyVizSupport; // Do not use. (Private use.)

class CATPolyMathCurve;
class CATPolyMathSurface;


/**
 * A CATIPolySupport is an attribute to a CATIPolyPoint, CATIPolyCurve or CATIPolySurface instance.
 * Typically, it defines the geometry of the instances.
 *
 * A primitive support can also be associated to a CATPolyBody.
 * 
 * The different types of supports are:
 * <ul>
 *   <li> CATIPolyPointSupport which can be associated to CATIPolyPoint only.
 *   <li> CATIPolyCurveSupport which can be associated to CATIPolyPoint or CATIPolyCurve.
 *   <li> CATIPolySurfaceSupport which can be associated to CATIPolyPoint, CATIPolyCurve or CATIPolySurface.
 *   <li> CATIPolyPrimitiveSupport which can be associated to CATPolyBody.
 * </ul>
 */
class ExportedByPolyhedralAttributes CATIPolySupport : public CATIPolyLayer
{

protected:

  virtual ~CATIPolySupport ();

public:

  /**
   * Type of the support (same types as those defined in CATPolyMathObject.)
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

  inline static const CATIPolySupport* Cast (const CATIPolyLayer*);
  inline static CATIPolySupport* Cast (CATIPolyLayer*);

public:

/** @name Queries
    @{ */

  /**
   * Returns the type of the support.
   */
  virtual Type GetType () const = 0;

  /**
   * Gets the ID or CGM ID associated to the support if available.
   * The method returns S_FALSE if no ID is available and S_OK if an ID is available.
   */
  virtual HRESULT GetID (unsigned int& oID) const;

  /**
   * Returns <tt>TRUE</tt> if this is a point support.
   */
  inline CATBoolean IsPoint () const;

  /**
   * Returns <tt>TRUE</tt> if this is a curve support.
   */
  inline CATBoolean IsCurve () const;

  /**
   * Returns <tt>TRUE</tt> if this is a surface support.
   */
  inline CATBoolean IsSurface () const;

  /**
   * Returns <tt>TRUE</tt> if this is a primitive support.
   */
  inline CATBoolean IsPrimitive () const;

/** @} */

public:

/** @name Casting Methods
    @{ */

  /**
    * Casts as a CATIPolySupport.
    */
  virtual CATIPolySupport* CastAsPolySupport ();

  /**
   * Casts the support as a CATIPolyPointSupport.
   */
  virtual const CATIPolyPointSupport* CastAsPoint () const;

  /**
   * Casts the support as a CATIPolyCurveSupport.
   */
  virtual const CATIPolyCurveSupport* CastAsCurve () const;

  /**
   * Casts the support as a CATIPolySurfaceSupport.
   */
  virtual const CATIPolySurfaceSupport* CastAsSurface () const;

  /**
   * Casts the support as a CATIPolyPrimitiveSupport.
   */
  virtual const CATIPolyPrimitiveSupport* CastAsPrimitive () const;

  /**
   * Casts the support as a CATIPolyPointSupport.
   */
  virtual CATIPolyPointSupport* CastAsPoint ();

  /**
   * Casts the support as a CATIPolyCurveSupport.
   */
  virtual CATIPolyCurveSupport* CastAsCurve ();

  /**
   * Casts the support as a CATIPolySurfaceSupport.
   */
  virtual CATIPolySurfaceSupport* CastAsSurface ();

  /**
   * Casts the support as a CATIPolyPrimitiveSupport.
   */
  virtual CATIPolyPrimitiveSupport* CastAsPrimitive ();

/** @} */

public:

/** @name Methods for supports defined as CATPolyMathCurve or CATPolyMathSurface.
    @{ */

  /**
   * Returns a CATPolyMathCurve only and only if the support refers directly to a CATPolyMathCurve.
   * The object returned is not supposed to be released. Its life cycle is managed by this class.
   */
  virtual HRESULT GetMathCurve (const CATPolyMathCurve*& oCurve) const;

  /**
   * Returns a CATPolyMathCurve only and only if the support refers directly to a CATPolyMathCurve.
   * The object returned is not supposed to be released. Its life cycle is managed by this class.
   */
  virtual HRESULT GetMathCurve (CATPolyMathCurve*& oCurve);

  /**
   * Returns a CATPolyMathSurface only and only if the support refers directly to a CATPolyMathSurface.  
   * The object returned is not supposed to be released. Its life cycle is managed by this class.
   */
  virtual HRESULT GetMathSurface (const CATPolyMathSurface*& oSurface) const;

  /**
   * Returns a CATPolyMathSurface only and only if the support refers directly to a CATPolyMathSurface.  
   * The object returned is not supposed to be released. Its life cycle is managed by this class.
   */
  virtual HRESULT GetMathSurface (CATPolyMathSurface*& oSurface);

/** @} */

public:

  /**
   * @nodoc
   * Do no use.
   */
  virtual CATIPolySupport* Clone () const;

protected:

  CATIPolySupport () {}

public:

  // Do not use. (Private use.)
  virtual const CATPolyGPSupport* CastAsGraphicPrimitive () const {return 0;}
  virtual const CATPolyVizSupport* CastAsVizPrimitive () const {return 0;}

  // Private use.
  /**
   * Returns a CATPolyMathCurve if one can be constructed from the support.
   * The object returned must be released by the caller.
   */
  virtual HRESULT GetNewMathCurve (CATPolyMathCurve*& oCurve) const;

  // Private use.
  /**
   * Returns a CATPolyMathSurface if one can be constructed from the support.
   * The object returned must be released by the caller.
   */
  virtual HRESULT GetNewMathSurface (CATPolyMathSurface*& oSurface) const;

};

inline const CATIPolySupport* CATIPolySupport::Cast (const CATIPolyLayer* layer)
{
  return layer ? ((CATIPolyLayer*) layer)->CastAsPolySupport () : 0;
}

inline CATIPolySupport* CATIPolySupport::Cast (CATIPolyLayer* layer)
{
  return layer ? layer->CastAsPolySupport () : 0;
}

inline CATBoolean CATIPolySupport::IsPoint () const
{
  return GetType () & ePoint ? TRUE : FALSE;
}

inline CATBoolean CATIPolySupport::IsCurve () const
{
  return GetType () & eCurve ? TRUE : FALSE;
}

inline CATBoolean CATIPolySupport::IsSurface () const
{
  return GetType () & eSurface ? TRUE : FALSE;
}

inline CATBoolean CATIPolySupport::IsPrimitive () const
{
  return GetType () & ePrimitive ? TRUE : FALSE;
}

