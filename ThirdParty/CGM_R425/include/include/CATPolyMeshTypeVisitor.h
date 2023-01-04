// COPYRIGHT DASSAULT SYSTEMES 2013, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMeshTypeVisitor.h
//
//===================================================================
// January 2013  Creation: NDO
// August  2015  Modif JXO: CATPolyProxyMesh
//===================================================================
#ifndef CATPolyMeshTypeVisitor_H
#define CATPolyMeshTypeVisitor_H

#include "PolyMeshTools.h"
#include "CATErrorDef.h"

class CATIPolySurface;


/**
* Returns the PolyhedralObjects type of the CATIPolyMesh.
*/
class ExportedByPolyMeshTools CATPolyMeshTypeVisitor
{

public:

  CATPolyMeshTypeVisitor() {}
  ~CATPolyMeshTypeVisitor() {}

  enum MeshType
  {
    /** Unknown mesh */               eUnknownMesh = -1,
    /** CATPolyMeshImpl */            ePolyMeshImpl = 0,
    /** CATPolyCompactMesh */         ePolyCompactMesh = 1,
    /** CATPolyCompactMeshConst */    ePolyCompactMeshConst = 4,
    /** CATPolySubMesh */             ePolySubMesh = 2,
    /** CATPolyProxyMesh */           ePolyProxyMesh = 3,
    /** CATPolyEditableMesh */        ePolyEditableMesh = 5,
    /** CATPolyDeltaMeshConst */      ePolyDeltaMeshConst = 6,
    /** CATPolyDeltaKeep */           ePolyDeltaMeshKeep = 7,
    /** CATPolyDeltaRemove */         ePolyDeltaMeshRemove = 8
  };

public:

  /**
  * Returns the PolyhedralObjects type of the CATIPolySurface.
  * @param oType
  *   The type of the CATIPolySurface.
  *   <ul>
  *     <li> ePolyMeshImpl
  *     <li> ePolyCompactMesh
  *     <li> ePolyCompactMeshConst
  *     <li> ePolySubMesh
  *     <li> ePolyProxyMesh
  *     <li> ePolyEditableMesh
  *     <li> ePolyDeltaMeshConst
  *   </ul>
  */
  static MeshType Type(const CATIPolySurface& iSurface);

public:

  /**
  * Returns the PolyhedralObjects type of the CATIPolySurface.
  * @param oType
  *   The type of the CATIPolySurface.
  *   <ul>
  *     <li> ePolyMeshImpl
  *     <li> ePolyCompactMesh
  *     <li> ePolyCompactMeshConst
  *     <li> ePolySubMesh
  *     <li> ePolyProxyMesh
  *     <li> ePolyEditableMesh
  *     <li> ePolyDeltaMeshConst
  *   </ul>
  */
  HRESULT GetType(const CATIPolySurface& iSurface, unsigned int& oType);

};

#endif
