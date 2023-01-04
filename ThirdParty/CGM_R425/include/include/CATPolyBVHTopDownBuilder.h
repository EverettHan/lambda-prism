// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBVHTopDownBuilder
//
//===================================================================
// 2009-08-31   JXO
//      * New
//===================================================================
#ifndef CATPolyBVHTopDownBuilder_H
#define CATPolyBVHTopDownBuilder_H

#include "PolyBodyBVH.h"

class CATBVHNode;
class CATPolyBVHAttribute;
class CATIPolyMesh;
class CATMathTransformation;

// System
#include "CATErrorDef.h"
#include "CATBoolean.h"

/**
* This operator spans a node by dividing it in two in a recursive way.
* Inputs are:
*    - a node that'd better have poly attributes
*    - a number of triangles threshold
* As soon as input node has more triangles than the threshold,
* it's divided right in two.
*
*/
class ExportedByPolyBodyBVH CATPolyBVHTopDownBuilder
{

public:

  /*
  * Constructor and destructor
  */
  CATPolyBVHTopDownBuilder(const unsigned int iMaxNbFacetsPerNode, CATBoolean iMutexFree = FALSE, CATBoolean deleteIntermediateData = FALSE);

  ~CATPolyBVHTopDownBuilder();

public:

  /**
  * It's currently implemented only for faces
  */
  enum EntityType
  {
    eAllEntities = 0,
    eFaceEntities,
    eEdgeEntities
  };


  HRESULT Run(CATBVHNode& ioNode, const CATMathTransformation * pPos,
    EntityType iEntityType, double inflate = 0.);

  HRESULT Run(int level, CATBVHNode& ioNode, const CATMathTransformation * pPos,
    EntityType iEntityType, double inflate = 0.);


  void ForceSetRootMesh(CATIPolyMesh * RootMesh);


private:
  // Recursive one:
  HRESULT Run(CATIPolyMesh& iMesh, CATBVHNode& ioNode, const CATMathTransformation * pPos, EntityType iEntityType, int level);
  void InflateNode(CATBVHNode& ioNode);

private:
  int _MaxNbFacetsPerNode;
  double _inflate;
  CATPolyBVHAttribute* _RootPolyAttr;
  CATIPolyMesh * _RootMesh;
  CATBoolean m_MutexFree;
  CATBoolean m_deleteIntermediateData;
};

#endif
