// COPYRIGHT DASSAULT SYSTEMES 2017, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyCurveVertexWLayer.h
//
//===================================================================
// April 2017  Creation NDO
//===================================================================
#ifndef CATPolyCurveVertexWLayer_H
#define CATPolyCurveVertexWLayer_H

#include "PolyLayers.h"
#include "CATIPolyCurveVertexWLayer.h"


#ifdef PLATEFORME_DS64
#include "CATMapOfIntToPtr.h"
#else
#include "CATMapOfIntToInt.h"
#include "CATListOfDouble.h"
#endif


/**
 * Class implementing the vertex W-layer for any type of curve.
 * This class maps a vertex to a double value.
 */
class ExportedByPolyLayers CATPolyCurveVertexWLayer : public CATIPolyCurveVertexWLayer
{

public:

  inline static CATPolyCurveVertexWLayer* New (unsigned int nbEstimatedVertices = 0);

public:

  HRESULT Set (int v, double w);

  HRESULT Get (int v, double& w) const;

private:

#ifdef PLATEFORME_DS64
  CATMapOfIntToPtr _Ws;
#else
  CATMapOfIntToInt _Ws;
  CATListOfDouble _Data;
#endif

private:

  // Private constructor.
  inline CATPolyCurveVertexWLayer (const unsigned int nbEstimatedVertices);

  ~CATPolyCurveVertexWLayer () {}

};

inline CATPolyCurveVertexWLayer::CATPolyCurveVertexWLayer (const unsigned int nbEstimatedVertices) :
  _Ws (nbEstimatedVertices)
{
}

inline CATPolyCurveVertexWLayer* CATPolyCurveVertexWLayer::New (unsigned int nbEstimatedVertices)
{
  return new CATPolyCurveVertexWLayer (nbEstimatedVertices);
}

#endif // !CATPolyCurveVertexWLayer_H
