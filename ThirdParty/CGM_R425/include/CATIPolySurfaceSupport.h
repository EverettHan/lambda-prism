// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolySurfaceSupport.h
//
//===================================================================
// March 2009  Creation: NDO
//===================================================================
#pragma once

#include "PolyhedralAttributes.h"
#include "CATIPolySupport.h"
#include "CATErrorDef.h"

class CATPolyMathSurfaceSupport;
class CATPolyCGMFaceSupport;

class CATPolyCubicBSplineSurfaceSupport;  // Get rid of me.

class CATPolyBoundingGPSupport; // Do not use. (Private use.)
class CATPolyVizFaceSupport;    // Do not use. (Private use.)


/**
 * A CATIPolySurfaceSupport is an attribute to a CATIPolyPoint, CATIPolyCurve or CATIPolySurface.
 */
class ExportedByPolyhedralAttributes CATIPolySurfaceSupport : public CATIPolySupport
{

protected:

  virtual ~CATIPolySurfaceSupport ();

public:

  inline static const CATIPolySurfaceSupport* Cast (const CATIPolySupport*);
  inline static CATIPolySurfaceSupport* Cast (CATIPolySupport*);

  inline static const CATIPolySurfaceSupport* Cast (const CATIPolyLayer*);
  inline static CATIPolySurfaceSupport* Cast (CATIPolyLayer*);

public:

  /**
   * Returns the type of the support.
   */
  virtual Type GetType () const;

public:

  /**
   * Casts the support as a CATPolyMathSurfaceSupport.
   */
  virtual const CATPolyMathSurfaceSupport* CastAsMathSurface () const;

  /**
   * Casts the support as a CATPolyMathSurfaceSupport.
   */
  virtual CATPolyMathSurfaceSupport* CastAsMathSurface ();

  /**
   * Casts the support as a CGM face.
   */
  virtual const CATPolyCGMFaceSupport* CastAsCGMFace () const;

public:

  const CATIPolySurfaceSupport* CastAsSurface () const;
  CATIPolySurfaceSupport* CastAsSurface ();

public:

  /**
   * Returns TRUE is the surface support is planar and FALSE otherwise.
   */
  virtual CATBoolean IsPlanar () const;

  /**
   * Returns the orientation of the support.
   * @return 
   *   <ul>
   *      <li> +1: Positive
   *      <li>  0: Undefined
   *      <li> -1: Negative
   *   </ul>
   */
  virtual int GetOrientation () const;

public:

  /**
   * @nodoc
   * Method does not belong here. -NDO
   */
  CATBoolean IsQuad () const;

  /**
   * @nodoc
   * Method does not belong here. -NDO
   */
  HRESULT SetQuad (CATBoolean iIsQuad);

public:

  /** @deprecated */
  virtual const CATPolyCubicBSplineSurfaceSupport* CastAsCubicBSplineSurface () const;
 
  // Do not use. (Private use.)
  virtual const CATPolyBoundingGPSupport* CastAsBoundingGP () const;
  virtual const CATPolyVizFaceSupport* CastAsVizFace () const;

protected:

  CATIPolySurfaceSupport ();

protected:

  CATBoolean _IsQuad;  // Does not belong here! -NDO

};

inline const CATIPolySurfaceSupport* CATIPolySurfaceSupport::Cast (const CATIPolySupport* support)
{
  return support ? support->CastAsSurface () : 0;
}

inline CATIPolySurfaceSupport* CATIPolySurfaceSupport::Cast (CATIPolySupport* support)
{
  return support ? support->CastAsSurface () : 0;
}

inline const CATIPolySurfaceSupport* CATIPolySurfaceSupport::Cast (const CATIPolyLayer* layer)
{
  return Cast (CATIPolySupport::Cast (layer));
}

inline CATIPolySurfaceSupport* CATIPolySurfaceSupport::Cast (CATIPolyLayer* layer)
{
  return Cast (CATIPolySupport::Cast (layer));
}
