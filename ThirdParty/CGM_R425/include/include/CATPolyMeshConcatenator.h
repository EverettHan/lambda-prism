//=============================================================================
// COPYRIGHT Dassault Systemes 2008
//=============================================================================
//
// CATPolyMeshConcatenator.cpp
//
//=============================================================================
// 2008-05-20   BPG: New.
//=============================================================================
#ifndef CATPolyMeshConcatenator_H
#define CATPolyMeshConcatenator_H

#include "CATErrorDef.h"
#include "CATBoolean.h"

//
class CATMapOfIntToInt;
class CATIPolyMesh;

//
#include "PolyMeshImpl.h"

class ExportedByPolyMeshImpl CATPolyMeshConcatenator
{
public:
  CATPolyMeshConcatenator();

public:
  HRESULT Concatenate(CATIPolyMesh &ioDstMesh,
                      /* const */ CATIPolyMesh &iSrcMesh,
                      CATMapOfIntToInt **oSrcVertexToDstVertexMap,
                      CATMapOfIntToInt **oSrcTriangleToDstTriangleMap) const;

public:
  // TRUE by default
  // inline HRESULT DoTriangleCenteredTopologyImport(CATBoolean iFlag = TRUE);

public:
  // TRUE by default
  inline HRESULT DoCopyVertexPositionLayer(CATBoolean iFlag = TRUE);

  // TRUE by default
  inline HRESULT DoCopyVertexNormalLayer(CATBoolean iFlag = TRUE);

  // TRUE by default
  inline HRESULT DoCopyVertexUVLayer(CATBoolean iFlag = TRUE);

  //TRUE by default
  inline HRESULT DoCopyVerteTextureCoordsLayer(CATBoolean iFlag = TRUE);

protected:
  HRESULT ConcatenateTriangles(CATIPolyMesh &ioDstMesh, const CATIPolyMesh &iSrcMesh,
                               CATMapOfIntToInt &ioSrcVertexDstVertexMap,
                               CATMapOfIntToInt **oSrcTriangleDstTriangleMap) const;

protected:
  // CATBoolean _TriangleCenteredTopologyImport;

  CATBoolean _CopyVertexPositionLayer;
  CATBoolean _CopyVertexNormalLayer;
  CATBoolean _CopyVertexUVLayer;
  CATBoolean _CopyVertexTextureCoordLayer;
};

// ----------------------------------------------------------------------------

// inline HRESULT
// CATPolyMeshConcatenator::DoTriangleCenteredTopologyImport(CATBoolean iFlag)
// {
//   _TriangleCenteredTopologyImport = iFlag;
//   return S_OK;
// }

inline HRESULT 
CATPolyMeshConcatenator::DoCopyVerteTextureCoordsLayer(CATBoolean iFlag)
{
  _CopyVertexTextureCoordLayer = iFlag;
  return S_OK;
}
#endif // !CATPolyMeshConcatenator_H
