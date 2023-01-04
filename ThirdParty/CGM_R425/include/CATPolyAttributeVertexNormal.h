// COPYRIGHT DASSAULT SYSTEMES 2005, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyAttributeVertexNormal.h
//
//===================================================================
// September 2005 Creation: ndo
//===================================================================
#ifndef CATPolyAttributeVertexNormal_H
#define CATPolyAttributeVertexNormal_H

#include "PolyMeshImpl.h"
#include "CATErrorDef.h" // HRESULT definition
#include "CATMathVector.h"

#include "CATPolyAttribute.h"
#include "CATPolySurfaceVertexNNormalsLayer.h"
#include "CATAssert.h"

class CATIPolySurface;


/*
** DO NOT USE!  DO NOT USE! ** 
** DEPRECATED CLASS **

SEE INSTEAD CATPolySurfaceVertexNNormalsLayer.h in PolyhedralObjects.
*/
class ExportedByPolyMeshImpl CATPolyAttributeVertexNormal : public CATPolyAttribute
{

public :

  CATPolyAttributeVertexNormal (CATPolySurfaceVertexNNormalsLayer* iNormalLayer = 0);

  ~CATPolyAttributeVertexNormal ();

public:

  inline CATPolySurfaceVertexNNormalsLayer& GetNormalLayer ();
  inline const CATPolySurfaceVertexNNormalsLayer& GetNormalLayer () const;

public:

  // DEPRECATED!
  inline HRESULT SetNormal (const int v, const CATMathVector& N, const int key = 0);
  inline HRESULT SetNormal (const int v, const float iNormalX, const float iNormalY, const float iNormalZ, const int key = 0);

  // DEPRECATED!
  inline HRESULT GetNormal (const int v, CATMathVector& N, const int key = 0) const;
  inline HRESULT GetNormal (const int v, float& oNormalX, float& oNormalY, float& oNormalZ, const int key = 0) const;

  // DEPRECATED!
  inline HRESULT UnsetNormal (const int v, const int key);

  // DEPRECATED!
  inline int GetNbNormals (const int v) const;

public:

  static const CATPolyAttributeVertexNormal* Cast (const CATIPolyLayer*);
  static CATPolyAttributeVertexNormal* Cast (CATIPolyLayer*);

  static const CLSID& ClassID ();
  const CLSID& GetClassID () const;

private:

  static const CLSID _ClassID;

  CATIPolySurface* _DummyPolySurface;
  CATPolySurfaceVertexNNormalsLayer* _NormalLayer;

};


inline CATPolySurfaceVertexNNormalsLayer& CATPolyAttributeVertexNormal::GetNormalLayer ()
{
  CATAssert (_NormalLayer);
  return *_NormalLayer;
}

inline const CATPolySurfaceVertexNNormalsLayer& CATPolyAttributeVertexNormal::GetNormalLayer () const
{
  CATAssert (_NormalLayer);
  return *_NormalLayer;
}

inline HRESULT CATPolyAttributeVertexNormal::SetNormal (const int v, const CATMathVector& N, const int key)
{
  return _NormalLayer ? _NormalLayer->Set (v, N, key) : E_FAIL;
}

inline HRESULT CATPolyAttributeVertexNormal::SetNormal (const int v, const float x, const float y, const float z, const int key)
{
  return _NormalLayer ? _NormalLayer->Set (v, CATMathVector (x, y, z), key) : E_FAIL;
}

inline HRESULT CATPolyAttributeVertexNormal::GetNormal (const int v, CATMathVector& N, const int key) const
{
  return _NormalLayer ? _NormalLayer->Get (v, N, key) : E_FAIL;
}

inline HRESULT CATPolyAttributeVertexNormal::GetNormal (const int v, float& x, float& y, float& z, const int key) const
{
  CATMathVector N;
  HRESULT hr = _NormalLayer ? _NormalLayer->Get (v, N, key) : E_FAIL;
  x = (float) N.GetX ();
  y = (float) N.GetY ();
  z = (float) N.GetZ ();
  return hr;
}

inline HRESULT CATPolyAttributeVertexNormal::UnsetNormal (const int v, const int key)
{
  return _NormalLayer ? _NormalLayer->Unset (v, key) : E_FAIL;
}

inline int CATPolyAttributeVertexNormal::GetNbNormals (const int v) const
{
  return _NormalLayer ? _NormalLayer->GetNbNormals (v) : E_FAIL;
}

#endif
