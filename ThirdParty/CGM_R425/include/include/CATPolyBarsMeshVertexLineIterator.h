// COPYRIGHT DASSAULT SYSTEMES 2008, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBarsMeshVertexLineIterator.h
// Header definition of CATPolyBarsMeshVertexLineIterator
//
//===================================================================
//
// Usage notes:
//
//===================================================================
// 2010-01-20 NDO: Revisit
// February 2008 Creation: ndo
//===================================================================
#ifndef CATPolyBarsMeshVertexLineIterator_H
#define CATPolyBarsMeshVertexLineIterator_H

#include "PolyFactoryImpl.h"
#include "CATPolyBarsToPolyCurveFactory.h"

class CATIPolyMesh;
class CATPolyBars;
class CATPolyBarsBarSupportLayer;
class CATPolyMeshVertexLine;


/**
* Class constructing CATPolyMeshVertexLine's from a CATIPolyMesh and CATPolyBars objects
* and an optional bar support layer.
*/
class ExportedByPolyFactoryImpl CATPolyBarsMeshVertexLineIterator : public CATPolyBarsToPolyCurveFactory
{

public:

  CATPolyBarsMeshVertexLineIterator (const CATIPolyMesh& iMesh,
                                     const CATPolyBars& iBars, 
                                     const CATPolyBarsBarSupportLayer* iSupportLayer = 0);

  virtual ~CATPolyBarsMeshVertexLineIterator ();

public:

  // Set the iterator to the beginning.
  inline CATPolyBarsMeshVertexLineIterator& Begin ();

  // Return TRUE if the iterator has reached the end and FALSE otherwise.
  inline CATBoolean End () const;

  // Increment the iterator to the next valid element.
  inline CATPolyBarsMeshVertexLineIterator& operator++ ();

public:

  inline CATPolyMeshVertexLine* Get ();

private:

  const CATIPolyMesh& _Mesh;

protected:

  virtual CATIPolyCurve* NewCurve () const;
  virtual HRESULT AppendVertex (CATIPolyCurve& iPolyCurve, const int v) const;

};

inline CATPolyBarsMeshVertexLineIterator& CATPolyBarsMeshVertexLineIterator::Begin ()
{
  CATPolyBarsToPolyCurveFactory::Begin ();
  return *this;
}

inline CATBoolean CATPolyBarsMeshVertexLineIterator::End () const
{
  return CATPolyBarsToPolyCurveFactory::End ();
}

inline CATPolyBarsMeshVertexLineIterator& CATPolyBarsMeshVertexLineIterator::operator++ ()
{
  CATPolyBarsToPolyCurveFactory::operator ++ ();
  return *this;
}

inline CATPolyMeshVertexLine* CATPolyBarsMeshVertexLineIterator::Get ()
{
  return (CATPolyMeshVertexLine*) GetCurve ();
}

#endif
