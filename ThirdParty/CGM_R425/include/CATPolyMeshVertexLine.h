//=============================================================================
// COPYRIGHT Dassault Systemes 2006
//=============================================================================
//
// CATPolyMeshVertexLine.h
//
//=============================================================================
// 2006-11-15   BPG: New
//=============================================================================
#ifndef CATPolyMeshVertexLine_H
#define CATPolyMeshVertexLine_H

#include "PolyMeshImpl.h"
#include "CATPolySurfaceVertexLine.h"
#include "CATIPolyMesh.h"
#include "CATPolyDeprecated.h"

class CATIPolyMesh;


// This class redundant with CATPolySurfaceVertexLine.
// TO DO: Get rid of it.
class ExportedByPolyMeshImpl CATPolyMeshVertexLine : public CATPolySurfaceVertexLine
{

public:

  POLY_DEPRECATED ("Replace by CATPolySurfaceVertexLine.",
  static CATPolyMeshVertexLine* New (CATIPolyMesh& iMesh, CATBoolean iWithWLayer, CATBoolean iWithTangentLayer)
    {return new CATPolyMeshVertexLine (iMesh, iWithWLayer, iWithTangentLayer);})

  inline CATPolyMeshVertexLine (CATIPolyMesh& iMesh, CATBoolean iWithWLayer = FALSE, CATBoolean iWithTangentLayer = FALSE);

  virtual ~CATPolyMeshVertexLine () {}

public:

  POLY_DEPRECATED ("Replace by CATPolySurfaceVertexLine and use vertex position layer.",
  virtual HRESULT GetVertexPosition (const int v, CATMathPoint &oPoint) const);

  POLY_DEPRECATED ("Replace by CATPolySurfaceVertexLine and use vertex position layer.",
  virtual HRESULT SetVertexPosition (const int v, const CATMathPoint &P));

public:

  inline CATIPolyMesh& GetMesh ();
  inline const CATIPolyMesh& GetMesh () const;
  inline HRESULT AppendMeshVertex (int i, int &v);
  inline HRESULT InsertMeshVertex (int i, int j, int &v);
  inline int GetMeshVertex (int v) const;
  inline int GetStartMeshVertex () const;
  inline int GetEndMeshVertex () const;

private:

  // No copy constructor and assignment operator allowed.
  CATPolyMeshVertexLine (const CATPolyMeshVertexLine &iRHS);
  CATPolyMeshVertexLine& operator = (const CATPolyMeshVertexLine &iRHS);

};

inline CATPolyMeshVertexLine::CATPolyMeshVertexLine (CATIPolyMesh& iMesh, CATBoolean iWithWLayer, CATBoolean iWithTangentLayer) :
  CATPolySurfaceVertexLine (iMesh, iWithWLayer, iWithTangentLayer)
{
}

inline CATIPolyMesh& CATPolyMeshVertexLine::GetMesh ()
{
  return *GetSurface ().CastToTriMesh ();
}

inline const CATIPolyMesh& CATPolyMeshVertexLine::GetMesh () const
{
  return *GetSurface ().CastToTriMesh ();
}

inline HRESULT CATPolyMeshVertexLine::AppendMeshVertex (int i, int &v)
{
  return CATPolySurfaceVertexLine::AppendSurfaceVertex (i, v);
}

inline int CATPolyMeshVertexLine::GetMeshVertex (int v) const
{
  return GetSurfaceVertex (v);
}

inline int CATPolyMeshVertexLine::GetStartMeshVertex () const
{
  return GetStartSurfaceVertex ();
}

inline int CATPolyMeshVertexLine::GetEndMeshVertex () const
{
  return GetEndSurfaceVertex ();
}

inline HRESULT CATPolyMeshVertexLine::InsertMeshVertex (int i, int j, int &v)
{
  return CATPolySurfaceVertexLine::InsertSurfaceVertex (i, j, v);
}

#endif // !CATPolyMeshVertexLine_H
