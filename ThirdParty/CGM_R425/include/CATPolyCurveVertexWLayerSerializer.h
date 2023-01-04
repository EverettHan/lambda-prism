//=============================================================================
// COPYRIGHT Dassault Systemes 2008
//=============================================================================
//
// CATPolyCurveVertexWLayerSerializer
//
//=============================================================================
// 2008-03-06   BPG: New
//=============================================================================
#ifndef CATPolyCurveVertexWLayerSerializer_H
#define CATPolyCurveVertexWLayerSerializer_H

#include "CATErrorDef.h"

//
class CATIPolyCurve;
class CATIPolyCurveVertexWLayer;
class CATIPolyCurveVertexIterator;

//
#include "PolySerializers.h"
class ExportedByPolySerializers CATPolyCurveVertexWLayerSerializer
{
  // Serialize to float buffer
public:
  HRESULT Serialize(CATIPolyCurve &iCurve,
                    float *VertexWBuffer) const;

  HRESULT Serialize(CATIPolyCurve &iCurve,
                    float *&VertexWBuffer, int &oVertexWBufferSize) const;

  // Serialize to double buffer
public:
  HRESULT Serialize(CATIPolyCurve &iCurve,
                    double *VertexWBuffer) const;

  HRESULT Serialize(CATIPolyCurve &iCurve,
                    double *&VertexWBuffer, int &oVertexWBufferSize) const;
};

#endif // !CATPolyCurveVertexWLayerSerializer_H
