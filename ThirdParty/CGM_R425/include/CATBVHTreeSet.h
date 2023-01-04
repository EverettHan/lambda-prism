// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATBVHTreeSet.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// Oct 2009 Creation: JXO
// April 2012 Modification: JXO, for threadsafety
//===================================================================

#ifndef CATBVHTreeSet_h
#define CATBVHTreeSet_h

#include "BVHObjects.h"

// Interferences traces
#include "CATPolyDebugClashTraces.h"

// Math
#include "CATMathTransformation.h"

// PolyMathematics
#include "CATBVHNodeIterator.h"
#include "CATPolyBoundingVolume.h"
#include "CATBVHTreeBuilder.h"
#include "CATBVHNodeConstList.h"
#include "CATMapOfIntToPtr.h"
class PositionnedBVHTree;
class CATBVHTree;
class CATBVHNode;
class CATBVHTreeSetObserver;
class CATPolyVisuBVHTreeSetObserver;

// System
class CATMutex;
#include "CATErrorDef.h"
#include "CATSysBoolean.h"



/**
 *
 */

class ExportedByBVHObjects CATBVHTreeSet : public CATBVHNodeIterator
{
public:
  /**
   * Type. Don't use.
   */
  enum Type 
  {
    Undefined = 0,
    PolyBody,
    Visu,
    VisuOptimized
  };

  /**
   * Constructor and destructor
   */
  CATBVHTreeSet(CATBVHTreeBuilder::SpatialOptimization SpatialOptim = CATBVHTreeBuilder::eBasicOptimization, CATPolyBoundingVolume::TypeID BVType = CATPolyBoundingVolume::OBBType, Type type = Undefined);
  virtual ~CATBVHTreeSet();

  /**
   * Add a BVHTree in the set at a certain position. You can release the tree.
   * @return S_OK if the object could be correctly registered, E_FAIL otherwise.
   */
  HRESULT AddTree(int objectId, CATBVHTree * object, const CATMathTransformation * pos = NULL);

  /**
   * Modify the position of an already added rep in the set.
   * @return S_OK if the object could be correctly registered, E_FAIL otherwise.
   */
  HRESULT ModifyTreePosition(int objectId, const CATMathTransformation * pos);

  HRESULT DesactivateTree(int objectId);
  HRESULT ActivateTree(int objectId);
  HRESULT DeactivateAll();
  HRESULT ActivateAll();
  HRESULT RemoveTree(int objectId);

  /**
   * Flush the memory and associated data of the tree
   */
  HRESULT FlushTree(int objectId);

  /**
   * Process of node:
   */
  static CATBoolean IsActivated(const CATBVHNodeConst & TermNode);
  static CATBVHTree * GetTree(const CATBVHNodeConst & TermNode);
  static const CATMathTransformation & GetPosition(const CATBVHNodeConst & TermNode);
  static const CATMathTransformation* GetTransformation (const CATBVHNodeConst & TermNode);
  static int GetObjectId(const CATBVHNodeConst & TermNode);

  HRESULT GetObjectNode(int iObjectId, const CATBVHNodeConst *& oObjectNode) const;

  /**
   * Returns the overall optimized tree. Tree needs to be released.
   * @return NULL if something went wrong.
   * Needs to be thread safe.
   * @return [out, IUnknown#Release]
   */
  CATBVHTree * GetTree();

  // Iterator part for the overall tree creation
public:

  virtual CATBVHNodeIterator & Begin();

  // Return TRUE if the iterator has reached the end and FALSE otherwise.
  virtual CATBoolean End () const;

  // Increment the iterator to the next valid element.
  virtual CATBVHNodeIterator & operator++();

  // Return an instance of the CATBVHNode currently referenced by the iterator 
  // (or NULL if iterator has reached the end.)
  virtual CATBVHNode * operator* () const;

  /**
   * Debug
   * @return
   *         Id of checkpoint
   */
  virtual int CheckPoint();

  /**
   * Debug. You can release observer. This method is thread safe
   */
  void RegisterObserver(CATBVHTreeSetObserver*);

  /**
   * Debug. You can release observer. This method is thread safe
   */
  void UnregisterObserver(CATBVHTreeSetObserver*);
  
  /** Debug */
  Type GetType() const {return m_Type;}

  virtual CATBVHTreeSet* Clone() const;

protected:

  //----------------------------------------------------------
  // To be called when the overall tree need to be update
  void OverAllTreeNeedsUpdate();
  void RecursivelyDestroyIntermediateNodes(CATBVHNode * pNode);

  // Rebuild the overall tree if needed
  void RebuildOverAllTree();

  // Recycle initial BV if possible
  // if not returns a new one (then pFinalBV is removed from terminal nodes pool)
  CATPolyBoundingVolume * ApplySmartTransformation(const CATPolyBoundingVolume * pInitialBV,
                                                   const CATMathTransformation * pos);
  HRESULT SetFlagOnTree(int objectId, int flag = 0);
  HRESULT SetFlagOnAll(int flag = 0);

  virtual HRESULT VirtualRemoveTree(int objectId);
  HRESULT ProtectedAddTree(int objectId, CATBVHTree * object, const CATMathTransformation * pos);
  
protected:
  //----------------------------------------------------------
  CATBVHTreeBuilder::SpatialOptimization _eSpatialMode;
  CATPolyBoundingVolume::TypeID _eBVType;

  // Map between IDs and couples BVH + position
  // So it stores both objects and their positions.
  CATMapOfIntToPtr _oObjectIdsToNodes;

  // Iterator on the trees
  CATBVHNodeConstList _NodeList; // Actually not const
  int _iCurNode;
  //----------------------------------------------------------
  static CATMathTransformation _Identity;

  // Debug
  CATBVHTreeSetObserver * m_BVHTreeSetObserver;
  Type m_Type;

  CATBVHTreeSet( const CATBVHTreeSet& iOther );

private:
  // The tree gathering all the small trees.
  CATBVHTree * _pOverAllTree;

  // For thread-safety.
  CATMutex * m_mut;
  CATBoolean m_MutexFree;

  // For debug traces
  DEBUGCLASHOBJECTTRACE(m_traces);
};

#endif /* CATPolyVisuInterfBVHTreeSet_h */
