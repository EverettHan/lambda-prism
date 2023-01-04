// COPYRIGHT Dassault Systemes Delmia Corp. 2011
//=============================================================================
//
// CATDynamicKDTree.h
// Header definition of CATDynamicKDTree
//=============================================================================
//
// Usage notes:
//
//=============================================================================
//  2012-12-04 - XXC: Creation
//=============================================================================

#ifndef CATDynamicKDTree_H
#define CATDynamicKDTree_H

#include "PolyMathContainers.h"

#include "CATMathInline.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"

class CATDynamicKDTreePoint;
class CATDynamicKDTreeNode;



//#define ATOMIC_KDTREE
//#define ATOMIC_KDTREE2
#ifdef ATOMIC_KDTREE

// still in dev

#include <atomic>


class ExportedByPolyMathContainers CATDynamicKDTree
{
public:

    CATDynamicKDTree( unsigned int iDimension );

    ~CATDynamicKDTree();

    void Destroy( CATDynamicKDTreeNode* iNode );

    HRESULT Insert( CATDynamicKDTreePoint & iP );

    void SetBoxLimits(double ** iBox);

    INLINE unsigned int GetDimension() const { return _Dimension; }

    std::atomic<CATDynamicKDTreeNode*> _root;

    const unsigned int _Dimension;
    double * _Box[2];

    unsigned m_nodes;
};

#else

class ExportedByPolyMathContainers CATDynamicKDTree
{
 public:

  CATDynamicKDTree(unsigned int iDimension, unsigned int iOrder = 1, CATBoolean iUseMediumInsertion = FALSE);
  ~CATDynamicKDTree();

  HRESULT Init();

  unsigned int Size() const;

  INLINE unsigned int GetDimension() const { return _Dimension; }
  INLINE unsigned int GetOrder() const { return _Order; }

  INLINE const CATDynamicKDTreeNode * const * const GetRoots() const { return _Roots; }

  void SetBoxLimits(double ** iBox);

  HRESULT Insert(CATDynamicKDTreePoint & ipValues);

private:
  CATDynamicKDTree();

  unsigned int * _CurrentOrders;
  unsigned int * _CurrentSizes;

  unsigned int _Order;
  const unsigned int _Dimension;
  const CATBoolean _UseMediumInsertion;

  CATDynamicKDTreeNode ** _Roots;
  double * _Box[2];
};

#endif

#endif
