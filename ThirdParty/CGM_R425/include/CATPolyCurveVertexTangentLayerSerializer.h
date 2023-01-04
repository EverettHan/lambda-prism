//=============================================================================
// COPYRIGHT Dassault Systemes 2008
//=============================================================================
//
// CATPolyCurveVertexTangentLayerSerializer
//
//=============================================================================
// 2008-02-29   BPG: New
//=============================================================================
#ifndef CATPolyCurveVertexTangentLayerSerializer_H
#define CATPolyCurveVertexTangentLayerSerializer_H

#include "CATErrorDef.h"

//
class CATIPolyCurve;
class CATIPolyCurveVertexTangentLayer;

//
#include "PolySerializers.h"
class ExportedByPolySerializers CATPolyCurveVertexTangentLayerSerializer
{
  // Serialize to float buffer
public:
  HRESULT Serialize(CATIPolyCurve &iCurve,
                    float *VertexTangentBuffer) const;

  HRESULT Serialize(CATIPolyCurve &iCurve,
                    float *&VertexTangentBuffer, int &oVertexTangentBufferSize) const;

  // Serialize to double buffer
public:
  HRESULT Serialize(CATIPolyCurve &iCurve,
                    double *VertexTangentBuffer) const;

  HRESULT Serialize(CATIPolyCurve &iCurve,
                    double *&VertexTangentBuffer, int &oVertexTangentBufferSize) const;
};

#endif // !CATPolyCurveVertexTangentLayerSerializer_H
