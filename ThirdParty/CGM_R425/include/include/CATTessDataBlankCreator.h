//=============================================================================
// COPYRIGHT Dassault Systemes 2009
//=============================================================================
//
// CATTessDataBlankCreator
//
//=============================================================================
// 2009-07-29 MPX: New
//=============================================================================
#ifndef CATTessDataBlankCreator_H
#define CATTessDataBlankCreator_H

#include "CATMathInline.h"
#include "CATTessDataCreatorBase.h"

class CATTessDataBlankCreator
  : public CATTessDataCreatorBase
{
public:
  
  // Create blank tessellation data for face/edge.
  // The memory of the returned oTessData needs to be managed by caller

  HRESULT CreateTessData(
                      CATCell& iCell, 
                      const CATTessParamToken& iToken,
                      CATTessDataCache*& oTessData);

protected:
  virtual HRESULT CreateFaceTessData(
                      CATFace& iFace, 
                      const CATTessParam& iTessParam, 
                      const CATTessParamToken& iToken,
                      const CATTessFaceDataCache*& oTessData,
                      CATBoolean& oIsAddedToCache);

  virtual HRESULT CreateEdgeTessData(
                      CATEdge& iEdge, 
                      const CATTessParam& iTessParam, 
                      const CATTessParamToken& iToken,
                      const CATTessEdgeDataCache*& oTessData,
                      CATBoolean& oIsAddedToCache);

public:

  INLINE CATTessDataBlankCreator();
  virtual ~CATTessDataBlankCreator();
};

INLINE 
CATTessDataBlankCreator::CATTessDataBlankCreator()
{
}

#endif // !CATTessDataBlankCreator_H

