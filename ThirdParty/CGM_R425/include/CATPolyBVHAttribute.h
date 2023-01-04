// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBVHAttribute
//
//===================================================================
// 2009-01-06   JXO
//      * New
// August 2009 - Revisit Architecture -NDO
//===================================================================
#ifndef CATPolyBVHAttribute_H
#define CATPolyBVHAttribute_H

#include "PolyBodyBVH.h"

#include "CATGeomBVHAttribute.h"
#include "CATPolyPool.h"

// System
#include "CATDataType.h"
#include "CATSysBoolean.h"
#include "CATMutex.h"

class CATPolyBody;
class CATPolyFace;
class CATPolyEdge;
class CATPolyVertex;
class CATIPolySurface;
class CATIPolyCurve;
class CATIPolyPoint;
class CATMathTransformation;
class CATIPolySurfaceVertexPositionConstLayer;
class CATCellId;
class CATPolyOverlayBVHAttribute;

/**
 * Generic interface to polyhedral model attributes of CATBVHNode's.
 * All methods should be thread-safe, provided implementations are thread-safe.
 */
class ExportedByPolyBodyBVH CATPolyBVHAttribute : public CATGeomBVHAttribute
{
  CATPolyDeclarePooledNew;
public:

  /**
   * Virtual destructor.
   */
  virtual ~CATPolyBVHAttribute () {}

public:

  /**
   * Casting method.
   */
  CATPolyBVHAttribute* CastAsPolyAttribute ();
  /**
   * Casting method.
   */
  const CATPolyBVHAttribute* CastAsPolyAttribute () const;

  /**
   * Casting method
   */
  virtual CATPolyOverlayBVHAttribute * CastAsOverlayAttribute();

  /**
   * Casting method
   */
  virtual const CATPolyOverlayBVHAttribute * CastAsOverlayAttribute() const;

public:
  /**
   * Return wether this node contains a body (could be a CATPolyBody or not, or whatever looks like a solid.)
   * Note: this is not necessarily of dimension 3. This could be a body containing only wires for example.
   */
  virtual CATBoolean HasBody() const;
  /**
   * Return wether this node contains a cell of dimension 2.
   */
  virtual CATBoolean HasFace() const;
  /**
   * Return wether this node contains a cell of dimension 1.
   */
  virtual CATBoolean HasEdge() const;
  /**
   * Return wether this node contains a cell of dimension 0.
   */
  virtual CATBoolean HasPoints() const;

  /**
   * Return wether this node contains a CATPolyBody.
   */
  virtual CATBoolean HasPolyBody() const;
  /**
   * Return wether this node contains a CATPolyFace.
   */
  virtual CATBoolean HasPolyFace() const;
  /**
   * Return wether this node contains a CATIPolySurface.
   */
  virtual CATBoolean HasPolySurface() const;
  /**
   * Return wether this node contains a CATIPolyCurve.
   */
  virtual CATBoolean HasPolyCurve() const;
  /**
   * Return wether this node contains CATPolyPoints.
   */
  virtual CATBoolean HasPolyVertices() const;

  /**
   * Returns the id associated to the cell associated to the geometry if any.
   * Call release on it after use.
   */
  virtual CATCellId * GetId() const { return CATGeomBVHAttribute::GetId(); }

  /**
   * Returns the id associated to one cell in case of multiple cells node (vertices).
   * Call release on it after use.
   */
  virtual CATCellId * GetId(int v) const {return 0;}

  /**
   * Return the (possible) CATPolyBody associated to this attribute.
   * If you need all the the possible information (i.e. Cell layers), you can have it.
   * On the other hand, if you need only surfaces and if macro topology is not mandatory,
   * pass @iNeedCellLayers as FALSE. This is much better for performances. 
   */
  virtual CATPolyBody* GetPolyBody (CATBoolean iWithFaceEdges = TRUE) const;
  /**
   * Return the (possible) CATPolyFace associated to this attribute.
   * If you need all the the possible information (i.e. Cell layers), you can have it.
   * On the other hand, if you need only surface and if macro topology is not mandatory,
   * pass @iNeedCellLayers as FALSE. This is much better for performances. 
   */
  virtual CATPolyFace* GetPolyFace (CATBoolean iWithFaceEdges = TRUE) const;
  /**
   * Return the (possible) CATPolyEdge associated to this attribute.
   */
  virtual CATPolyEdge* GetPolyEdge () const;
  /**
   * In case this attribute contains points, return the number of points.
   */
  virtual int GetNbVertices() const;
  /**
   * Return the CATPolyVertex given its index in the PolyBody.
   */
  virtual CATPolyVertex * GetPolyVertex(int v) const;

  /**
   * Return the (possible) CATIPolySurface associated to this attribute.
   * If you need all the the possible information (i.e. Cell layers), you can have it.
   * On the other hand, if you need only surface and if macro topology is not mandatory,
   * pass @iNeedCellLayers as FALSE. This is much better for performances. 
   */
  virtual CATIPolySurface* GetPolySurface (CATBoolean iWithFaceEdges = TRUE) const;
  /**
   * Return the (possible) CATIPolyCurve associated to this attribute.
   */
  virtual CATIPolyCurve* GetPolyCurve () const;
  /**
   * Return the CATIPolyPoint given its index in the PolyBody.
   */
  virtual CATIPolyPoint* GetPolyPoint (int v) const;

  /**
   * Return the (possible) transformation associated to this attribute.
   * Note : a poly-attribute containing a CATPolyBody may have a transformation. In this case, 
   * the poisition of the node (and its Bounding Volume) is aboslute, but the Polybody is
   * positioned inside the node.
   * <br />When descending further in the tree, it may happen that the attribute associated to the
   * cells has no position. In this case the position of the parent PolyBody has to be applied nevertheless.
   */
  virtual const CATMathTransformation* GetPosition () const;

  /**
   * If this attribute contains a cell inside a CATPolyBody, it returns
   * the (possible) attribute associated to the parent polybody.
   */
  virtual CATPolyBVHAttribute * GetParentPolyBodyAttribute() const;

  /**
   * If the attribute is relative to a polybody, return its Sag.
   * Otherwise return a negative value.
   * Default implementation of the function need to create the polybody to be able
   * to fetch the sag. 
   */
  virtual double GetSag() const;

  /**
   * If the attribute is relative to a polybody, return its dimension.
   * The dimension can be 0 for points, 1 for lines, 2 for surfaces or 3 for volumes.
   * If something went wrong, return a negative value.
   */
  virtual int GetBodyDimension() const;

  /**
   * @nodoc
   */
  virtual void FlushComputedData();

  /**
   * @nodoc
   * @return to be released by caller.
   */
  virtual CATIPolySurfaceVertexPositionConstLayer * GetCachedPositionLayer();

protected:

  CATPolyBVHAttribute() {}

};

#endif
