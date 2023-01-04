// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolyCurveSupport.h
//
//===================================================================
// March 2009  Creation: NDO
//===================================================================
#pragma once

#include "PolyhedralAttributes.h"
#include "CATIPolySupport.h"
#include "CATErrorDef.h"

class CATPolyMathCurveSupport;
class CATPolyCGMCurveSupport;
class CATPolyCGMEdgeSupport;
class CATPolyCGMMathCurveSupport;


/**
 * A CATIPolyCurveSupport is an attribute to a CATIPolyPoint or CATIPolyCurve.
 */
class ExportedByPolyhedralAttributes CATIPolyCurveSupport : public CATIPolySupport
{

public:

  virtual ~CATIPolyCurveSupport () {}

public:

  inline static const CATIPolyCurveSupport* Cast (const CATIPolySupport*);
  inline static CATIPolyCurveSupport* Cast (CATIPolySupport*);

  inline static const CATIPolyCurveSupport* Cast (const CATIPolyLayer*);
  inline static CATIPolyCurveSupport* Cast (CATIPolyLayer*);

public:

  /**
   * Returns the type of the support.
   */
  virtual Type GetType () const;

public:

  /**
   * Casts the support as a CATPolyMathCurveSupport.
   */
  virtual const CATPolyMathCurveSupport* CastAsMathCurve () const;

  /**
   * Casts the support as a CATPolyMathCurveSupport.
   */
  virtual CATPolyMathCurveSupport* CastAsMathCurve ();

  /**
   * Casts the support as a CGM curve.
   */
  virtual const CATPolyCGMCurveSupport* CastAsCGMCurve () const;

  /**
   * Casts the support as a CGM edge.
   */
  virtual const CATPolyCGMEdgeSupport* CastAsCGMEdge () const;

  /**
   * Casts the support as a CGM math curve.
   */
  virtual const CATPolyCGMMathCurveSupport* CastAsCGMMathCurve () const;

public:

  const CATIPolyCurveSupport* CastAsCurve () const;
  CATIPolyCurveSupport* CastAsCurve ();

protected:

  CATIPolyCurveSupport () {}

};

inline const CATIPolyCurveSupport* CATIPolyCurveSupport::Cast (const CATIPolySupport* support)
{
  return support ? support->CastAsCurve () : 0;
}

inline CATIPolyCurveSupport* CATIPolyCurveSupport::Cast (CATIPolySupport* support)
{
  return support ? support->CastAsCurve () : 0;
}

inline const CATIPolyCurveSupport* CATIPolyCurveSupport::Cast (const CATIPolyLayer* layer)
{
  return Cast (CATIPolySupport::Cast (layer));
}

inline CATIPolyCurveSupport* CATIPolyCurveSupport::Cast (CATIPolyLayer* layer)
{
  return Cast (CATIPolySupport::Cast (layer));
}
