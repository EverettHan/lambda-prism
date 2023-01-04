// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyBVHTreeBuilder
//
//===================================================================
// 2009-01-06   JXO
//      * New
// August 2009 - Revisit Architecture -NDO
//===================================================================
#ifndef CATPolyBodyBVHTreeBuilder_H
#define CATPolyBodyBVHTreeBuilder_H

#include "PolyBodyBVH.h"

// BVH
#include "CATBVHNodeIterator.h"
#include "CATBVHTreeBuilder.h"
#include "CATPolyBoundingVolume.h"

// System
#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATListPV.h"

class CATBVHTree;
class CATBVHNode;
class CATPolyBody;
class CATIPolySurface;
class CATMathTransformation;


/**
 * This is a builder of CATBVHNode's from the geometric entities
 * of a CATPolyBody.  Specifically, it is a builder of CATBVHNode's for the CATIPolySurface's of 
 * the CATPolyFace's of the CATPolyBody and for the CATIPolyCurve's of the CATPolyEdge of the CATPolyBody. 
 * A CATBVHNode is constructed for each CATIPolySurface (CATPolyFace) and CATIPolyCurve (CATPolyEdge)
 * of the CATPolyBody.
 */
class ExportedByPolyBodyBVH CATPolyBodyBVHTreeBuilder 
{

public:

  /**
   * Builder of CATBVHTrees given Polybodies and positions.
   * @param iSpatialOptimization
   *   Enumerator defining how the spatial hierarchy of the nodes is constructed and optimized.
   *   See CATBVHTreeBuilder.
   * @param BVType Type of the bounding volumes in the tree
   *               SphereType for spheres
   *               AABBType for axis aligned bounding boxes
   *               OBBType for both AABBs and oriented bounding boxes
   * @param iMaxNbFacetsPerNode
   *   This is an input control parameter that controls the level of division of the CATIPolySurface's.
   *   The CATIPolySurface's are divided into as many sub-surfaces as needed to have a number of facets 
   *   below or equal to this parameter.  If this parameter is set to 0, then no division of the
   *   CATIPolySurface's occurs.
   */
  CATPolyBodyBVHTreeBuilder (CATBVHTreeBuilder::SpatialOptimization iSpatialOptimization,
                             CATPolyBoundingVolume::TypeID BVType = CATPolyBoundingVolume::AABBType,
                             const unsigned int iMaxNbFacetsPerNode = 0,
                             double iInflation = 0.);

  /** Destructor */
  ~CATPolyBodyBVHTreeBuilder ();

public:

  enum EntityType
  {
    eAllEntities = 0,
    eFaceEntities,
    eEdgeEntities,
    eVertexEntities,
    eFaceAndWireEdgeEntities
  };

  /**
   * Construct a CATBVHTree given a Polybody and a position.
   * @param iPolyBody
   *   Input polybody. An addref is done on Polybody. It will be released at the tree destruction.
   * @param iPosition
   *   Optional input position. Position is duplicated, you can delete it afterwards.
   * @param iEntityType
   *   Type of entities that will have bounding volumes in the tree.
   * @param oBVHTree
   *   Output computed tree. Must be released by caller.
   * @param iSagInflate
   *   If set to true, all bounding volumes will be inflated with the sag value.
   *   The sag value is handled by the CATIPolyBodyAttributes.
   * @return
   *   S_OK: everything went fine.
   *   Any other value: Something went wrong.
   */
  HRESULT Run (CATPolyBody& iPolyBody, const CATMathTransformation* iPosition, EntityType iEntityType,
               CATBVHTree*& oBVHTree, CATBoolean iSagInflate = FALSE) const;

  /**
   * Construct a CATBVHTree given Polybodies and positions.
   * @param iPolyBodies
   *   List of input polybodies. An addref is done on the Polybodies. They will be released at the tree destruction.
   * @param iPositions
   *   Optional list of optional input positions (CATMathTransformations.)
   *   Positions are duplicated, you can delete them afterwards.
   *   If not null, must be the same size as @iPolyBodies. Some positions may also be null.
   * @param iEntityType
   *   Type of entities that will have bounding volumes in the tree.
   * @param oBVHTree
   *   Output computed tree. Must be released by caller.
   * @param iSagInflate
   *   If set to true, all bounding volumes will be inflated with the sag value.
   *   The sag value is handled by the CATIPolyBodyAttributes. 
   * @return
   *   S_OK: everything went fine.
   *   Any other value: Something went wrong.
   */
  HRESULT Run (CATListPV & iPolyBodies, CATListPV * iPositions, EntityType iEntityType,
               CATBVHTree*& oBVHTree, CATBoolean iSagInflate = FALSE) const;

  /**
  * Put canonical information as second bounding volume in result if avaiable.
  */
  void UseCanonics(CATBoolean iUseCanonics = TRUE){_UseCanonics = iUseCanonics;}

  /**
   * Intermediate nodes won't retain intermediate meshes data.
   * You will get a good memory improvement when diving deep into the tree.
   * But the tree won't be flushable anymore.
   */
  void DeleteIntermediateData(CATBoolean deleteIntermediateData = TRUE){m_deleteIntermediateData = deleteIntermediateData;}


public:

  class Iterator : public CATBVHNodeIterator
  {
  public:

    Iterator (const CATPolyBodyBVHTreeBuilder& iBuilder,
      CATListPV & iPolyBodies,
      CATListPV * iPositions,
      EntityType iEntityType,
      CATBoolean iSagInflate = FALSE);
    ~Iterator();

  public:

    CATBVHNodeIterator& Begin ();
    CATBoolean End () const;
    CATBVHNodeIterator& operator++ ();

    CATBVHNode* operator* () const;


  private:
    const CATPolyBodyBVHTreeBuilder & _Builder;
    CATListPV & _PolyBodies;
    CATListPV * _pPositions;
    CATBoolean _SagInflate;
    EntityType _EntityType;

    int _CurrentBody;
    int _nbp;
#ifndef _SUNOS_SOURCE
    mutable CATBVHNode ** _NodeList;
#else
    CATBVHNode ** _NodeList;
#endif
  };

private:
  CATBVHTreeBuilder _TreeBuilder;

  unsigned int _MaxNbFacetsPerNode;
  CATPolyBoundingVolume::TypeID _type;
  CATBoolean _UseCanonics;
  double m_Inflation;

  CATBoolean m_deleteIntermediateData;
};

#endif
