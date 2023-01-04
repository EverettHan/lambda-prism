//=============================================================================
// COPYRIGHT Dassault Systemes 2009
//=============================================================================
//
// CATTessDataCreatorBase
//
//=============================================================================
// 2009-07-29 MPX: New
//=============================================================================
#ifndef CATTessDataCreatorBase_H
#define CATTessDataCreatorBase_H

#include "TessCacheObjects.h"
#include "CATMathInline.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"


class CATCell;
class CATFace;
class CATEdge;
class CATTessParam;
class CATTessDataCache;
class CATTessParamToken;
class CATTessFaceDataCache;
class CATTessEdgeDataCache;

class ExportedByTessCacheObjects CATTessDataCreatorBase
{

public:

  // Create tessellation data for face/edge, for the given iTessParam
  // The memory of the returned oTessData needs to be managed by caller
  // oIsAddedToCache is set to true if it has added the data to cache
  
  virtual HRESULT CreateFaceTessData(
                        CATFace& iFace, 
                        const CATTessParam& iTessParam, 
                        const CATTessParamToken& iToken, 
                        const CATTessFaceDataCache*& oTessData,
                        CATBoolean& oIsAddedToCache) = 0;

  virtual HRESULT CreateEdgeTessData(
                        CATEdge& iEdge, 
                        const CATTessParam& iTessParam, 
                        const CATTessParamToken& iToken, 
                        const CATTessEdgeDataCache*& oTessData,
                        CATBoolean& oIsAddedToCache) = 0;

  // iCell can be a CATFace or CATEdge
  virtual HRESULT CreateTessData(
                        CATCell& iCell, 
                        const CATTessParam& iTessParam, 
                        const CATTessParamToken& iToken, 
                        const CATTessDataCache*& oTessData,
                        CATBoolean& oIsAddedToCache);

public:

  INLINE CATTessDataCreatorBase();
  virtual ~CATTessDataCreatorBase();

};

INLINE 
CATTessDataCreatorBase::CATTessDataCreatorBase()
{
}

#endif // !CATTessDataCreatorBase_H

