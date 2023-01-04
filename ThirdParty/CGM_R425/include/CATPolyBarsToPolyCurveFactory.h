// COPYRIGHT DASSAULT SYSTEMES 2008, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBarsToPolyCurveFactory.h
//
//===================================================================
// 2010-01-20 NDO: Revisit
// February 2008 Creation: ndo
//===================================================================
#ifndef CATPolyBarsToPolyCurveFactory_H
#define CATPolyBarsToPolyCurveFactory_H

#include "PolyFactoryImpl.h"
#include "CATErrorDef.h"     // HRESULT definition (for compil under UNIX)
#include "CATPolyBitSet.h"
#include "CATPolyBarsBarIterator.h"
#include "CATBoolean.h"

class CATPolyBars;
class CATIPolyCurveVertexPositionConstLayer;
class CATPolyBarsBarSupportLayer;
class CATIPolyCurve;


/**
* Class constructing CATIPolyCurve's from a CATPolyBars object and an optional bar support layer.
*/
class ExportedByPolyFactoryImpl CATPolyBarsToPolyCurveFactory 
{

public:

  CATPolyBarsToPolyCurveFactory (const CATPolyBars& iBars, 
                                 const CATIPolyCurveVertexPositionConstLayer* iVertexPositionLayer,
                                 const CATPolyBarsBarSupportLayer* iBarSupportLayer = 0, CATBoolean iTwoSided = FALSE);

  virtual ~CATPolyBarsToPolyCurveFactory ();

public:

  // Set the iterator to the beginning.
  CATPolyBarsToPolyCurveFactory& Begin ();

  // Return TRUE if the iterator has reached the end and FALSE otherwise.
  inline CATBoolean End () const;

  // Increment the iterator to the next valid element.
  CATPolyBarsToPolyCurveFactory& operator++ ();

public:

  /*
   * Construct a CATIPolyCurve given the current bar pointed by the iterator.
   * The object returned must be released.
   */
  inline CATIPolyCurve* GetCurve ();

  /*
   * Return the start bar of a curve at the current position of the iterator.
   */
  inline int GetStartBar () const;

private:

  const CATPolyBars& _Bars;
  const CATIPolyCurveVertexPositionConstLayer* _VertexPositionLayer;
  const CATPolyBarsBarSupportLayer* _BarSupportLayer;

  CATPolyBarsBarIterator _BarIterator;
  CATPolyBitSet _BarVisited;

  int _Bar;  // Index of first edge-bar of a new CATIPolyCurve.
  CATBoolean _TwoSided; // Set to TRUE if bars orientation does not matter, FALSE otherwise (default is FALSE)
  CATBoolean _FirstEdgeInverted; // TRUE if the Rewind function ends on a bar with wrong orientation considering the two sided iteration.
private:

  // Calculate the valence of the vertex.
  int GetValence (const int vertex) const;

  void Rewind (const int bar);

  CATIPolyCurve* ConstructCurve ();

  // Return the ID of the curve support.
  // This support ID is obtained from the bar support layer if defined.
  // If the support is not defined, then the method returns 0.
  int GetCurveSupportID (const int bar) const;

protected:

  virtual CATIPolyCurve* NewCurve () const;
  virtual HRESULT AppendVertex (CATIPolyCurve& iPolyCurve, const int v) const;

};

inline CATBoolean CATPolyBarsToPolyCurveFactory::End () const
{
  return _Bar == 0 ? TRUE : FALSE;
}

inline CATIPolyCurve* CATPolyBarsToPolyCurveFactory::GetCurve ()
{
  return ConstructCurve ();
}

inline int CATPolyBarsToPolyCurveFactory::GetStartBar () const
{
  return _Bar;
}

#endif
