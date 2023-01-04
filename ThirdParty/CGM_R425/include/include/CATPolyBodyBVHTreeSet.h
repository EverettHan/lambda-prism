// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyBVHTreeSet.h
//
//===================================================================
//
// Usage notes:
// This class gather and arrange input Polybodies in an efficient
// way to be used by the interference operators.
// Moreover, this class act as cache for these operators and can be
// slightly modified between calls to the operator.
//
//===================================================================
//
// Nov 2009 Creation: JXO
//===================================================================

#ifndef CATPolyBodyBVHTreeSet_h
#define CATPolyBodyBVHTreeSet_h

#include "PolyBodyBVH.h"

// Other
#include "CATMathTransformation.h"
#include "CATMapOfIntToPtr.h"

// PolyMathematics
#include "CATBVHTreeSet.h"
#include "CATBVHNodeIterator.h"
#include "CATBVHAttribute.h"
#include "CATBVHTreeBuilder.h"
#include "CATPolyBoundingVolume.h"
class CATBVHTree;
class CATBVHNode;
class CATPolyBodyBVHTreeSetObserver;
class CATPolyBodyBVHTreeSetMetaObserver;

// Polyhedral
#include "CATMapOfPtrToPtr.h"
class CATPolyBody;

// System
#include "CATListPV.h"

/**
 * This class gather and arrange input Polybodies in an efficient
 * way to be used by the interference operators.
 * Moreover, this class act as cache for these operators and can be
 * slightly modified between calls to the operator.
 */
class ExportedByPolyBodyBVH CATPolyBodyBVHTreeSet : public CATBVHTreeSet
{
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
   * Constructor and destructor
   */
  CATPolyBodyBVHTreeSet(Type type = PolyBody);

  CATPolyBodyBVHTreeSet( const CATPolyBodyBVHTreeSet& iOther );

  virtual ~CATPolyBodyBVHTreeSet();

  /**
   * Set the spatial optimization mode to be used when the Bounding Volumes Hierachies are created.
   * Default is Basic Optimization.
   */
  virtual void SetSpatialOptimizationMode(CATBVHTreeBuilder::SpatialOptimization iSpatialOptimization);

  /**
   * Set the Bounding Volumes type to be used in BVHs.
   * Default is OBB type.
   */
  virtual void SetBVType(CATPolyBoundingVolume::TypeID bvType);

  /**
   * Add a PolyBody in the set at a certain position.
   * Position is duplicated and can be deleted after the call to AddPolyBody.
   * @param object
   *        Given Polybody can be released after this call.
   * @return S_OK if the object could be correctly registered, E_FAIL otherwise.
   */
  HRESULT AddPolyBody(int objectId, CATPolyBody * object, const CATMathTransformation * pos = NULL, EntityType iType = eFaceEntities);

  /**
   * Add a set of PolyBodies in the CATBVHTreeSet under the same id. That means that one BVH Tree is constructed
   * for this whole set, and added to the CATBVHTreeSet. objectId then references the whole set.
   * iPolyBodies and (optional) iPositions (if not null) should be the same size. Note that some positions (CATMathTransformation)
   * may however be null.
   * Positions are duplicated and can be deleted after the call to AddSetOfPolyBodies.
   * Given Polybodies can be released after this call.
   * iOverallPositionMatrix is applied to the whole set of polybodies and can later be changed with ModifyPolyBodyPosition or 
   * ModifyTreePosition (see CATBVHTreeSet).
   * @return S_OK if the objects could be correctly registered, E_FAIL otherwise.
   */
  HRESULT AddSetOfPolyBodies(int objectId,
                             CATListPV & iPolyBodies,
                             CATListPV * iPositions = 0,
                             const CATMathTransformation * iOverallPositionMatrix = 0,
                             EntityType iType = eFaceEntities);

  /**
   * Modify the position of an already added PolyBody in the set.
   * @return S_OK if the object could be correctly registered, E_FAIL otherwise.
   */
  HRESULT ModifyPolyBodyPosition(int objectId, const CATMathTransformation * pos);

  /**
   * Deactivate a PolyBody already added by AddPolyBody.
   * The object won't be processed by operators.
   * @param objectId
   *     id of the object to desactivate.
   */
  HRESULT DeactivatePolyBody(int objectId);
  /**
   * Activate a PolyBody that had previously been deactivated.
   * Note that newly added PolyBodies are activated by default.
   * @param objectId
   *     id of the object to activate.
   */
  HRESULT ActivatePolyBody(int objectId);

  /**
   * Remove given PolyBody. Polybody is released.
   */
  HRESULT RemovePolyBody(int objectId);

  /**
   * Put canonical information as second bounding volume in result if available.
   */
  void UseCanonics(CATBoolean iUseCanonics = TRUE){_UseCanonics = iUseCanonics;}

  /** Sets the max number of triangles we want per node. If more triangles 
   * are found, nodes are split. Default is 100. Works well for clash. You may
   * set it to -1 to deactivate it (sectioning...)
   */
  void SetNbMaxTrianglesPerNode(int nbmax);
  int  GetNbMaxTrianglesPerNode(){return m_NbMaxTrianglesPerNode;}

  /**
   * Debug. You can release observer.
   */
  void RegisterPolyObserver(CATPolyBodyBVHTreeSetObserver*);
  /**
   * Debug. You can release observer.
   */
  void UnregisterPolyObserver(CATPolyBodyBVHTreeSetObserver*);

  virtual CATPolyBodyBVHTreeSet* Clone() const;


protected:
  virtual HRESULT VirtualRemoveTree(int objectId);

protected:

  //----------------------------------------------------------
  CATBVHTreeBuilder::SpatialOptimization _ePolySpatialMode;
  CATPolyBoundingVolume::TypeID _ePolyBVType;

  CATMapOfPtrToPtr _MapOfPolyBodyToTrees;
  CATMapOfPtrToPtr _MapOfTreesToPolyBody;
  CATBoolean _UseCanonics;

  int m_NbMaxTrianglesPerNode;

  // Debug
  CATPolyBodyBVHTreeSetMetaObserver * m_PolyBodyBVHTreeSetObserver;

};

#endif /* CATPolyVisuInterfBVHTreeSet_h */
