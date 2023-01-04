// COPYRIGHT DASSAULT SYSTEMES 2014
//=============================================================================
//
// CATCoincidentEdges: 
//  Pair of coincident edges used in CATTopBoundaryHomogenize.
//
//
//=============================================================================
//
// Usage notes: 
//
//
//=============================================================================
//  Janury 2017  Creation                                                   U29
//=============================================================================

#ifndef CATCoincidentEdges_H
#define CATCoincidentEdges_H

class CATListPtrCATBody;
class CATBody;

#include "CATCEF_OperatorDef.h"
#include "CATMathInline.h"

class CATCoincidentEdges 
{
  friend class CATExtTopCoincidentEdgesFinder;

public:
  //-------------------------------------------------------
  //              Creation and destruction methods
  //-------------------------------------------------------
  /**
  * Constructor
  */
  CATCoincidentEdges();

  /**
  * Destructor
  */
  ~CATCoincidentEdges();

  INLINE CATBody * GetCoincidenceBody() const;
  INLINE void GetAncestorBodies(CATListPtrCATBody& oAncestorBodies) const;
  INLINE CATCoincidenceType GetCoincidenceType() const;

private:

  CATBody * _pCoincidenceBody;

  CATListPtrCATBody _ancestorBodies;

  CATCoincidenceType _coincidenceType;

};

#endif
