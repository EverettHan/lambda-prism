// COPYRIGHT DASSAULT SYSTEMES 2013, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolySurfaceVertexTexCoordFloat1DLayer.h
//
//===================================================================
// January 2013  Creation: NDO
// May 2019  Modification JXO: CATUnicodeString identifier
//===================================================================
#ifndef CATPolySurfaceVertexTexCoordFloat1DLayer_H
#define CATPolySurfaceVertexTexCoordFloat1DLayer_H

#include "PolyLayers.h"
#include "CATIPolyFloatsLayer.h"
#include "CATVectorOfFloats.h"

#include "CATUnicodeString.h"


/**
 * Layer of texture coordinates (1D) for a contiguous array of vertices ranging from 1 to CATIPolySurface::GetNbVertices ().
 */
class ExportedByPolyLayers CATPolySurfaceVertexTexCoordFloat1DLayer : public CATIPolyFloatsLayer
{

public:

  CATPolySurfaceVertexTexCoordFloat1DLayer (unsigned int iNbVerticesToAllocate, const CATUnicodeString& iTextureIdentifier = "DEFAULT_TC_SET");
  ~CATPolySurfaceVertexTexCoordFloat1DLayer () {}

public:

  static const CATPolySurfaceVertexTexCoordFloat1DLayer* Cast (const CATIPolyLayer* iLayer);
  static CATPolySurfaceVertexTexCoordFloat1DLayer* Cast (CATIPolyLayer* iLayer);

  static const CLSID& ClassID ();
  const CLSID& GetClassID () const { return ClassID (); }

public:

  /**
   * Resize the layer.
   */
  HRESULT Resize (unsigned int iNbVerticesToAllocate)
  {
    return _Coords.Resize (iNbVerticesToAllocate);
  }

  unsigned int Size () const
  {
    return _Coords.Size ();
  }

public:

  unsigned int GetDimension () const { return 1; }

  const CATUnicodeString& GetIdentifier () const { return m_id; }

  HRESULT Set (int v, const float* a);
  HRESULT Get (int v, float* a) const;

  HRESULT Set (int v, const double* a);
  HRESULT Get (int v, double* a) const;

public:

  HRESULT Set (int v, const float a);
  HRESULT Get (int v, float& a) const;

  HRESULT Set (int v, const double a);
  HRESULT Get (int v, double& a) const;

private:

  CATVectorOfFloats _Coords;

  CATUnicodeString m_id;
};

#endif
