// COPYRIGHT DASSAULT SYSTEMES 2013, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyDefaultSurfaceConstTools.h
//
//===================================================================
// March 2013  Creation: NDO
//===================================================================
#ifndef CATPolyDefaultSurfaceConstTools_H
#define CATPolyDefaultSurfaceConstTools_H

#include "PolyMeshTools.h"
#include "CATIPolySurfaceConstTools.h"


/**
Default implementation of the CATIPolySurfaceConstTools.
An instance of this class can only be constructed by a derived class (constructor is protected.)
*/
class ExportedByPolyMeshTools CATPolyDefaultSurfaceConstTools : public CATIPolySurfaceConstTools
{

public:

  virtual HRESULT GetMathSurface (const CATIPolySurface& iPolySurface, CATPolyMathSurface*& oSurface) const;

  /**
   * @param oMathSurfaceSupport [out, IUnknown#Release] 
   */
  virtual HRESULT GetMathSurfaceSupport (const CATIPolySurface& iPolySurface, CATPolyMathSurfaceSupport*& oMathSurfaceSupport) const;

  virtual HRESULT IsPlanar (const CATIPolySurface& iPolySurface) const;

public:

  virtual HRESULT GetBoundingSphere (const CATIPolySurface& iPolySurface, CATPolyBoundingSphere& ioBoundingSphere,
                                     const CATMathTransformation* iPosMatrix = 0) const;

  virtual HRESULT GetAABB (const CATIPolySurface& iPolySurface, CATPolyAABB& ioAABB,
                           const CATMathTransformation* iPosMatrix = 0) const;

  virtual HRESULT GetOBB (const CATIPolySurface& iPolySurface, CATPolyOBB& ioOBB,
                          const CATMathTransformation* iPosMatrix = 0) const;

  virtual HRESULT GetAABBAndOBB (const CATIPolySurface& iPolySurface, CATPolyAABB& ioAABB, CATPolyOBB& ioOBB,
                                 const CATMathTransformation* iPosMatrix = 0) const;

  virtual HRESULT OBBSplit (const CATIPolySurface& iPolySurface, const CATPolyOBB & iSurfaceOBB, int iNaxNbSplit,
                            CATIPolySurfaceIterator *& oSplitSurfaces) const;

public:

  virtual HRESULT GetPointOnMesh (const CATIPolySurface& iPolySurface, CATMathPoint & coord) const;

  virtual HRESULT GetID (const CATIPolySurface& iPolySurface, unsigned int& oID) const;

  virtual CATBoolean ShareDataWith (const CATIPolySurface& iPolySurface, const CATIPolySurface& iWithPolySurface) const;

  virtual HRESULT GetVertexRange (const CATIPolySurface& iPolySurface, int& oMinimum, int& oMaximum) const;

  virtual HRESULT GetFacetRange (const CATIPolySurface& iPolySurface, int& oMinimum, int& oMaximum) const;

  virtual unsigned int SizeOf (const CATIPolySurface& iPolySurface) const;

public:

  virtual HRESULT GetVertexPositionLayer (const CATIPolySurface& iPolySurface, CATIPolyVertexFloatPositionConstLayer*& oLayer) const;

  virtual HRESULT GetVertexNormalLayer (const CATIPolySurface& iPolySurface, CATIPolyVertexFloatNormalConstLayer*& oLayer) const;

public:

  virtual HRESULT MakeVertexCellLayer (const CATIPolySurface& iPolySurface, CATPolyFace& iPolyFace,
                                       CATIPolySurfaceVertexCellConstLayer*& oCellLayer) const;

  virtual HRESULT GetPolyFace (const CATIPolySurface& iPolySurface, const CATPolyFace*& oPolyFace) const;

public:

  virtual HRESULT GetBaseSurfaceAndCurves (const CATIPolySurface& iPolySurface, CATIPolySurface*& oBaseSurface, CATPolyCurveList* ioCurves = 0) const;

  virtual HRESULT PushSurfaceForRefinement (const CATIPolySurface& iPolySurface) const;

  virtual HRESULT ReleaseSurfaceFromRefinementEngine (const CATIPolySurface& iPolySurface) const;

public:

  virtual HRESULT CompressMesh (const CATIPolySurface& iPolySurface, void *& oCompressedForm) const;

protected:

  /**
   * Proctected constructor.
   * An instance of this class can only be constructed by a derived class.
   */
  CATPolyDefaultSurfaceConstTools () {}

};

#endif
