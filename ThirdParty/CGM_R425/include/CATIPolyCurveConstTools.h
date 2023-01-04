// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolyCurveConstTools.h
//
//===================================================================
//
// October 2009  Creation: NDO
//===================================================================
#ifndef CATIPolyCurveConstTools_H
#define CATIPolyCurveConstTools_H

#include "PolyhedralModel.h"
#include "CATErrorDef.h" 
#include "CATBoolean.h"

class CATIPolyCurve;
class CATIPolySupport; 
class CATPolyMathCurve;
class CATPolyBoundingSphere;
class CATPolyAABB;
class CATPolyOBB;
class CATMathTransformation;
class CATIPolyVertexFloatPositionConstLayer;


/**
 * The use of polyhedral tools (this class) is reserved exclusively to polyhedral frameworks.
 * Do not use anywhere else.
 * Use instead the global functions and services that are defined in CATPolyServices.h.
 * 
 * @see CATPolyServices.h
 */
class ExportedByPolyhedralModel CATIPolyCurveConstTools
{

public:

  virtual ~CATIPolyCurveConstTools () {}

public:

  //
  // GEOMETRY
  //

  /*
   * Return a CATPolyMathCurve that is associated to the support (either directly or indirectly).
   * The object returned MUST be deleted by the caller.
   */
  virtual HRESULT GetMathCurve (const CATIPolyCurve& iPolyCurve, CATPolyMathCurve*& oCurve) const = 0;

  /**
   * Return a bounding sphere of the CATIPolyCurve instance.
   * @param ioBoundingSphere
   *   The bounding sphere that will be set by a successful call.
   * @param iPosMatrix
   *   An optional transformation defining the position of the surface.
   * @return
   *   S_OK for a successful call
   *   S_FALSE if the bounding sphere has not been set.
   *   E_FAIL if an error occurs during the computation.
   */
  virtual HRESULT GetBoundingSphere (const CATIPolyCurve& iPolyCurve, CATPolyBoundingSphere& ioBoundingSphere,
                                     const CATMathTransformation* iPosMatrix = 0) const = 0;

  /**
   * Return an AABB of the CATIPolyCurve instance.
   * @param ioAABB
   *   The AABB that will be set by a successful call.
   * @param iPosMatrix
   *   An optional transformation defining the position of the surface.
   * @return
   *   S_OK for a successful call
   *   S_FALSE if the AABB has not been set.
   *   E_FAIL if an error occurs during the computation.
   */
  virtual HRESULT GetAABB (const CATIPolyCurve& iPolyCurve, CATPolyAABB& ioAABB,
                           const CATMathTransformation* iPosMatrix = 0) const = 0;

  /**
   * Return an OBB of the CATIPolyCurve instance.
   * @param ioBB
   *   The OBB that will be set by a successful call.
   * @param iPosMatrix
   *   An optional transformation defining the position of the surface.
   * @return
   *   S_OK for a successful call
   *   S_FALSE if the OBB has not been set.
   *   E_FAIL if an error occurs during the computation.
   */
  virtual HRESULT GetOBB (const CATIPolyCurve& iPolyCurve, CATPolyOBB& ioOBB,
                          const CATMathTransformation* iPosMatrix = 0) const = 0;

  /**
   * Return an AABB and an OBB of the CATIPolyCurve instance.
   * @param ioAABB
   *   The AABB that will be set by a successful call.
   * @param ioBB
   *   The OBB that will be set by a successful call.
   * @param iPosMatrix
   *   An optional transformation defining the position of the surface.
   * @return
   *   S_OK for a successful call
   *   S_FALSE if the AABB and OBB have not been set.
   *   E_FAIL if an error occurs during the computation.
   */
  virtual HRESULT GetAABBAndOBB (const CATIPolyCurve& iPolyCurve, CATPolyAABB& ioAABB, CATPolyOBB& ioOBB,
                                 const CATMathTransformation* iPosMatrix = 0) const = 0;

public:

  //
  // MISCELLANEOUS
  //

  /**
   * Returns the ID or CGM ID associated to the curve if available.
   */
  virtual HRESULT GetID (const CATIPolyCurve& iPolyCurve, unsigned int& oID) const = 0;

  /**
   * Return the size in bytes of the CATIPolyCurve and its layers.
   * The size of the dependent objects is not included.
   */
  virtual unsigned int SizeOf (const CATIPolyCurve& iPolyCurve) const = 0;

  /**
   * Returns <tt>TRUE</tt> if the CATIPolyCurve shares its data with another CATIPolyCurve.
   */
  virtual CATBoolean ShareDataWith (const CATIPolyCurve& iPolyCurve, const CATIPolyCurve& iWithPolyCurve) const = 0;

public:

  //
  // VERTEX LAYER TOOLS
  //

  /**
   * Returns the curve-vertex position layer if available in float precision.
   * The returned layer must be released.
   */
  virtual HRESULT GetVertexPositionLayer (const CATIPolyCurve& iPolyCurve, CATIPolyVertexFloatPositionConstLayer*& oLayer) const = 0;

public:

  //
  // TOOLS FOR CURVES THAT ARE DYNAMICALLY REFINABLE
  // 

  /**
   * Returns the base curve.
   * This method is for a refinement engine that can compute efficiently the refined data from the base curve.
   * @param oBaseCurve
   *   The returned base curve (also called Curve 0).  The returned instance must be released.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> If a base curve is returned.
   *   <li> <tt>S_FALSE</tt> If there is no base curve associated to this CATIPolyCurve.
   *   <li> <tt>E_FAIL</tt> If an error occurs.
   *  </ul>
   */
  virtual HRESULT GetBaseCurve (const CATIPolyCurve& iPolyCurve, CATIPolyCurve*& oBaseCurve) const = 0;

protected:

  CATIPolyCurveConstTools () {}

};

#endif // !CATIPolyCurveConstTools_H
