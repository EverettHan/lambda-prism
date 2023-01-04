// COPYRIGHT DASSAULT SYSTEMES 2013, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolySurfaceVertexTexCoordFloat2DLayer.h
//
//===================================================================
// January 2013  Creation: NDO
// May 2019  Modification JXO: CATUnicodeString identifier
//===================================================================
#ifndef CATPolySurfaceVertexTexCoordFloat2DLayer_H
#define CATPolySurfaceVertexTexCoordFloat2DLayer_H

#include "PolyLayers.h"
#include "CATIPolyFloatsLayer.h"
#include "CATVectorOfFloats.h"

#include "CATUnicodeString.h"


/**
 * Layer of texture coordinates (2D) for a contiguous array of vertices ranging from 1 to CATIPolySurface::GetNbVertices ().
 */
class ExportedByPolyLayers CATPolySurfaceVertexTexCoordFloat2DLayer : public CATIPolyFloatsLayer
{

public:

  CATPolySurfaceVertexTexCoordFloat2DLayer (unsigned int iNbVerticesToAllocate, const CATUnicodeString & iTextureIdentifier = "DEFAULT_TC_SET");
  ~CATPolySurfaceVertexTexCoordFloat2DLayer () {}

public:

  static const CATPolySurfaceVertexTexCoordFloat2DLayer* Cast (const CATIPolyLayer* iLayer);
  static CATPolySurfaceVertexTexCoordFloat2DLayer* Cast (CATIPolyLayer* iLayer);

  static const CLSID& ClassID ();
  const CLSID& GetClassID () const;

public:

  /**
   * Resize the layer.
   */
  HRESULT Resize (unsigned int iNbVerticesToAllocate)
  {
    return _Coords.Resize (2 * iNbVerticesToAllocate);
  }

  unsigned int Size () const
  {
    return _Coords.Size () / 2;
  }

public:

  unsigned int GetDimension () const { return 2; }

  const CATUnicodeString& GetIdentifier () const { return m_id; }

  HRESULT Set (int v, const float* a);
  HRESULT Get (int v, float* a) const;

  HRESULT Set (int v, const double* a);
  HRESULT Get (int v, double* a) const;

public:

  HRESULT Set (int v, const float a, const float b);
  HRESULT Get (int v, float& a, float& b) const;

  HRESULT Set (int v, const double a, const double b);
  HRESULT Get (int v, double& a, double& b) const;

private:

  CATVectorOfFloats _Coords;

  CATUnicodeString m_id;
};

#endif
