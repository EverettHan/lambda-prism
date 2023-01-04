// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBoundingVolumeCompute.h
//
//===================================================================
// 2009-08-28   JXO
//      * New
//===================================================================
#ifndef CATPolyBoundingVolumeCompute_H
#define CATPolyBoundingVolumeCompute_H

// ExportedBy
#include "PolyBodyBVH.h"

// Poly
#include "CATPolyBoundingVolume.h"

class CATMathBox;
class CATMathPoint;
class CATMathVector;
class CATBVHNode;
class CATPolyBoundingVolume;
class CATPolyOBB;
class CATPolyAABB;
class CATPolyBoundingSphere;
class CATPolyBoundingPlane;
class CATIPolySurface;
class CATIPolyMesh;
class CATIPolyCurve;
class CATPolyBody;
class CATMathTransformation;
class CATMathOBBBase;
class CATMathPoint;

class CATPolyPlaneSupport;
class CATPolySphereSupport;
class CATPolyCylinderSupport;
class CATPolyBoxSupport;

#include "CATErrorDef.h"

/**
 * Computes some BV for positioned CATIPolyMeshes
 */

class ExportedByPolyBodyBVH CATPolyBoundingVolumeCompute
{
public:

  static HRESULT ComputeBoxFromPolyMesh(CATIPolyMesh & iMesh, CATMathBox & oAABB,
                                        const CATMathTransformation * pPos = NULL);
  
  static HRESULT ComputeOBBFromPolyMesh(CATIPolyMesh & iMesh, CATPolyOBB & oOBB, const CATMathTransformation * pPos = NULL);
  static HRESULT ComputeOBBAndAABBFromPolyMesh(CATIPolyMesh & iMesh, CATPolyOBB & oOBB, CATPolyAABB & oAABB,
                                               const CATMathTransformation * pPos = NULL);
  static HRESULT ComputeSphereFromPolyMesh(CATIPolyMesh & iMesh, CATPolyBoundingSphere & oSphere,
                                           const CATMathTransformation * pPos = NULL);
  static HRESULT ComputeAABBFromPolyMesh(CATIPolyMesh & iMesh, CATPolyAABB & oAABB, const CATMathTransformation * pPos = NULL);
  
  static HRESULT ComputeBoxFromPolyCurve(CATIPolyCurve & iCurve, CATMathBox & oAABB, const CATMathTransformation * pPos = NULL);
  static HRESULT ComputeOBBFromPolyCurve(CATIPolyCurve & iCurve, CATPolyOBB & oOBB, const CATMathTransformation * pPos = NULL);
  static HRESULT ComputeSphereFromPolyCurve(CATIPolyCurve & iCurve, CATPolyBoundingSphere & oSphere, const CATMathTransformation * pPos = NULL);
  static HRESULT ComputeAABBFromPolyCurve(CATIPolyCurve & iCurve, CATPolyAABB & oAABB, const CATMathTransformation * pPos = NULL);
  
  // Takes only CATPolyVertex:
  static HRESULT ComputeOBBFromPolyVertices(CATPolyBody& iBody, CATPolyOBB & oOBB, const CATMathTransformation * pPos = NULL);
  static HRESULT ComputeSphereFromPolyVertices(CATPolyBody& iBody, CATPolyBoundingSphere & oSphere, const CATMathTransformation * pPos = NULL);
  static HRESULT ComputeAABBFromPolyVertices(CATPolyBody& iBody, CATPolyAABB & oAABB, const CATMathTransformation * pPos = NULL);
  
  /**
   * Return BV associated to canonic (if you have a plane, returns a plane, a sphere, a sphere, etc...)
   */
  static HRESULT ComputeBVFromPolyCanonicSurface(const CATIPolySurface & iSurface, CATPolyBoundingVolume *& oBV, const CATMathTransformation * pPos = NULL);

  /**
   * Change BVs of the given node to optimize them with the (possible) canonical support of the face attached to the node.
   * If not used, iCanonicalBV is deleted.
   */
  static HRESULT UpdateBVsFromCanonicalSurface(CATBVHNode & ioNode, CATPolyBoundingVolume *& iCanonicalBV);

    
};

#endif
