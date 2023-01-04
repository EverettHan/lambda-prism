// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyBVHTreeSetObserver.h
//
//===================================================================
//
// Usage notes:
// Observer of CATPolyBodyBVHTreeSet
//
//===================================================================
//
// Oct 2011 Creation: JXO
//===================================================================

#ifndef CATPolyBodyBVHTreeSetObserver_h
#define CATPolyBodyBVHTreeSetObserver_h

#include "PolyBodyBVH.h"

// Other
#include "CATMathTransformation.h"

// PolyMathematics
#include "CATBVHTreeSetObserver.h"
#include "CATPolyBoundingVolume.h"

// Polyhedral
#include "CATPolyBodyBVHTreeSet.h"
class CATPolyBody;

/**
 *
 */
class ExportedByPolyBodyBVH CATPolyBodyBVHTreeSetObserver : public CATBVHTreeSetObserver
{
public:
  /**
   * Constructor and destructor
   */
  CATPolyBodyBVHTreeSetObserver(){}
  virtual ~CATPolyBodyBVHTreeSetObserver(){}

  /**
   * Activate any disabled observer.
   * @return
   *         Previous state
   */
  virtual CATBoolean Enable() = 0;
  /**
   * Disable observer.
   * @return
   *         Previous state
   */
  virtual CATBoolean Disable() = 0;

  virtual void SetSpatialOptimizationMode(CATBVHTreeBuilder::SpatialOptimization iSpatialOptimization) = 0;
  virtual void SetBVType(CATPolyBoundingVolume::TypeID bvType) = 0;
  virtual HRESULT AddPolyBody(int objectId, CATPolyBody * object, const CATMathTransformation * pos, CATPolyBodyBVHTreeSet::EntityType iType) = 0;
  virtual HRESULT AddSetOfPolyBodies(int objectId,
                                     CATListPV & iPolyBodies,
                                     CATListPV * iPositions,
                                     const CATMathTransformation * iOverallPositionMatrix,
                                     CATPolyBodyBVHTreeSet::EntityType iType) = 0;
  virtual HRESULT ModifyPolyBodyPosition(int objectId, const CATMathTransformation * pos) = 0;
  virtual HRESULT DeactivatePolyBody(int objectId) = 0;
  virtual HRESULT ActivatePolyBody(int objectId) = 0;
  virtual HRESULT DeactivateAllBodies() = 0;
  virtual HRESULT ActivateAllBodies() = 0;
  virtual HRESULT RemovePolyBody(int objectId) = 0;
  virtual void UseCanonics(CATBoolean iUseCanonics) = 0;

  CATPolyBodyBVHTreeSetObserver * CastToPolyObserver() { return this; }
  CATPolyVisuBVHTreeSetObserver * CastToVisuObserver() { return 0; }

};

#endif /* CATPolyBodyBVHTreeSetObserver_h */
