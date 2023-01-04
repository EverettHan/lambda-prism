// COPYRIGHT Dassault Systemes Delmia Corp. 2011
//=============================================================================
//
// CATDynamicKDTreeNode.h
// Header definition of CATDynamicKDTreeNode
//=============================================================================
//
// Usage notes:
//
//=============================================================================
//  2012-12-04 - XXC: Creation
//=============================================================================

#ifndef CATDynamicKDTreeNode_H
#define CATDynamicKDTreeNode_H

//#define ATOMIC_KDTREE

#include "PolyMathContainers.h"

#include "CATMathInline.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"

class CATDynamicKDTree;

class ExportedByPolyMathContainers CATDynamicKDTreePoint
{
public:
  CATDynamicKDTreePoint() {}
  virtual ~CATDynamicKDTreePoint() {}

  virtual const double & operator[](int idx) const = 0;
  virtual unsigned int Dimension() const = 0;

protected:
  void Copy(const CATDynamicKDTreePoint & iToCopy){};
};



#ifdef ATOMIC_KDTREE

#include <atomic>

class CATDynamicKDTreeNode
{
public:

    CATDynamicKDTreeNode( CATDynamicKDTreePoint* iPoint = 0 );

    virtual ~CATDynamicKDTreeNode();

    INLINE unsigned int GetSplitDimension() const { return _SplitDim; }
    INLINE const CATDynamicKDTreePoint * GetPoint() const { return _Point; }
    

    CATDynamicKDTreePoint * _Point;

    std::atomic< CATDynamicKDTreeNode* > _a;
    std::atomic< CATDynamicKDTreeNode* > _b;

    short _SplitDim;
    double _Split;
    double _MinMax[2];

    //double * _BoxAllDim[2];
};

#else

class CATDynamicKDTreeNode
{
public:
  CATDynamicKDTreeNode(const double ** iBox, CATDynamicKDTreePoint ** iPoints, unsigned int iSize, const CATDynamicKDTree & iParent);
  /** Destructor. It only deletes subnodes, but it does not delete the
   *  points inside the nodes. To delete points, use the Empty method
   *  that recursively deletes the points and subnodes.
   */
  ~CATDynamicKDTreeNode();

  HRESULT InsertPoint(CATDynamicKDTreePoint & iPoint);

  /** Returns the number of inserted points */
  unsigned int GetNbPoints() const {return _NbPoints;}
  /** Returns the inserted points
   * ioPoints must have been already allocated to nbpoints * sizoef(point*) */
  unsigned int GetPoints(CATDynamicKDTreePoint ** ioPoints);

  /** Recursively deletes points and subnodes.
   */
  void Empty();

public:

  INLINE unsigned int GetSplitDimension() const { return _SplitDim; }
  INLINE const CATDynamicKDTreePoint * GetPoint() const { return _Point; }
  INLINE const CATDynamicKDTreeNode * GetInfSubNode() const { return _InfChild; }
  INLINE const CATDynamicKDTreeNode * GetSupSubNode() const { return _SupChild; }
  INLINE const double * Limits() const { return _BoxDim; }

private:
  CATDynamicKDTreeNode(const double ** iBox, CATDynamicKDTreePoint & iPoint, const CATDynamicKDTreeNode & iParent);

private:
  const CATDynamicKDTree & _Parent;
  CATDynamicKDTreePoint * _Point;

  unsigned int _SplitDim;
  double _BoxDim[2];
  double * _BoxAllDim[2];

  CATDynamicKDTreeNode * _InfChild;
  CATDynamicKDTreeNode * _SupChild;

  unsigned int _NbPoints;
};

#endif

#endif
