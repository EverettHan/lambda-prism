//=============================================================================
// COPYRIGHT Dassault Systemes 2009
//=============================================================================
//
// CATTessCacheEngineBase
//
//=============================================================================
// 2009-07-29 MPX: New
//=============================================================================
#ifndef CATTessCacheEngineBase_H
#define CATTessCacheEngineBase_H

#include "TessCacheObjects.h"
#include "CATMathInline.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"
#include "ListVOfCATTessParamToken.h"

#include "CATGeometry.h"
#include "CATBody.h"
#include "CATFace.h"
#include "CATEdge.h"


class CATTessParam;
class CATTessParamToken;
class CATTessDataCreatorBase;
class CATTessDataCache;
class CATTessFaceDataCache;
class CATTessEdgeDataCache;
class CATCGMAttrId;
class CATTessDataCacheAttribute;
class CATTessParamAttribute;
class CATCGMProgressBar;

////////////////////////////////////////////////////////////////////////////////
//
// class CATTessCacheEngineBase
//
// Purpose:
//    This class does not have any public methods. It is meant for derivation.
//    The derived class should expose the interfaces it needs to.
//    This class provides the engine infrastructure for
//      - creating
//      - querying
//      - removing
//    of Tessellation Cache.
//    But this class does not provide any functionality for actual tessellation.
//    Instead it accepts a pointer to pure virtual class CATTessDataCreatorBase,
//    which needs to be derived from and its tessellation methods needs to be
//    implemented by it.
//
// Internals:
//    The data structure classes for the tessellation cache mechanism are:
//      
////////////////////////////////////////////////////////////////////////////////

class ExportedByTessCacheObjects CATTessCacheEngineBase
{

protected:

  ///////////////////////////////////////////////////////
  // Methods for direct use by derived class interfaces
  ///////////////////////////////////////////////////////

  INLINE static HRESULT DefineTessellationParameters(
            CATBody& iBody, 
            const CATTessParam& iTessParam, 
            CATTessParamToken& ioToken);

  INLINE static HRESULT DefineTessellationParameters(
            CATFace& iFace, 
            const CATTessParam& iTessParam, 
            CATTessParamToken& ioToken);

  INLINE static HRESULT DefineTessellationParameters(
            CATEdge& iEdge, 
            const CATTessParam& iTessParam, 
            CATTessParamToken& ioToken);



  INLINE static HRESULT GetExistingTessParamTokens(
            CATBody& iBody, 
            ListVOfCATTessParamToken& oTokens);

  INLINE static HRESULT GetExistingTessParamTokens(
            CATFace& iFace, 
            ListVOfCATTessParamToken& oTokens);

  INLINE static HRESULT GetExistingTessParamTokens(
            CATEdge& iEdge, 
            ListVOfCATTessParamToken& oTokens);



  INLINE static HRESULT GetTessParamForGivenToken(
            CATBody& iBody, 
            const CATTessParamToken& iToken,
            CATTessParam& oTessParam);

  INLINE static HRESULT GetTessParamForGivenToken(
            CATFace& iFace, 
            const CATTessParamToken& iToken,
            CATTessParam& oTessParam);

  INLINE static HRESULT GetTessParamForGivenToken(
            CATEdge& iEdge, 
            const CATTessParamToken& iToken,
            CATTessParam& oTessParam);

  INLINE static HRESULT GetTessParamForGivenToken(
            const CATTessParamToken& iToken,
            CATTessParam& oTessParam);



  INLINE static HRESULT RemoveTessCacheData(
            CATBody& iBody,
            const CATTessParamToken& iToken);

  INLINE static HRESULT RemoveTessCacheData(
            CATFace& iFace,
            const CATTessParamToken& iToken);

  INLINE static HRESULT RemoveTessCacheData(
            CATEdge& iEdge,
            const CATTessParamToken& iToken);


protected:

  //////////////////////////////////////////////////
  // Methods for use internal use
  //////////////////////////////////////////////////

  static HRESULT __DefineTessellationParameters(
            CATGeometry& iGeometry, 
            const CATTessParam& iTessParam, 
            CATTessParamToken& ioToken);

  static HRESULT __GetExistingTessParamTokens(
            CATGeometry& iGeometry, 
            ListVOfCATTessParamToken& oTokens);

  static HRESULT __GetTessParamAttribForGivenToken(
            const CATTessParamToken& iToken,
            CATTessParamAttribute*& oTessParamAttr,
            CATGeometry*& oParamOwner);

  static HRESULT __GetTessParamForGivenToken(
            const CATTessParamToken& iToken,
            CATTessParam& oTessParam);

  static HRESULT __RemoveTessCacheData(
            CATGeometry& iGeometry, 
            const CATTessParamToken& iToken);

  static HRESULT __RemoveLocalTessCache(
            CATCell& iCell, 
            const CATTessParamToken& iToken);

  static HRESULT __GetCATCGMAttrId(
            CATCell& iCell, 
            const CATCGMAttrId*& oAttrId);

  static HRESULT __CreateNewCacheAttribute(
            CATCell& iCell, 
            const CATTessParamToken& iToken,
            const CATTessDataCache& iTessDataCache,
            CATTessDataCacheAttribute*& oCacheAttribute);

  static HRESULT __GetTessellationData(
            CATFace& iFace,
            const CATTessParamToken& iToken,
            CATTessDataCreatorBase& iTessDataCreator,
            const CATTessFaceDataCache*& oTessData);

  static HRESULT __GetTessellationData(
            CATEdge& iEdge,
            const CATTessParamToken& iToken,
            CATTessDataCreatorBase& iTessDataCreator,
            const CATTessEdgeDataCache*& oTessData);

  static HRESULT __GetTessellationData(
            CATCell& iCell,
            const CATTessParamToken& iToken,
            CATTessDataCreatorBase& iTessDataCreator,
            const CATTessDataCache*& oTessData);

  /**
   * @param oTessData [out, IUnknown#Release] 
   */
  static HRESULT __GetExistingTessellationData(
            CATCell& iCell,
            const CATTessParamToken& iToken,
            const CATTessDataCache*& oTessData);

  static HRESULT __CreateNewBlankTessellationData(
            CATCell& iCell,
            const CATTessParamToken& iToken,
            CATTessDataCache*& oTessData);

  static HRESULT __AddCache(
            CATCell& iCell, 
            const CATTessParamToken& iToken,
            const CATTessDataCache& iTessDataCache);

  static HRESULT __ComputeTessellationDataIfNotAlreadyComputed(
            CATCell& iCell,
            const CATTessParamToken& iToken,
            CATTessDataCreatorBase& iTessDataCreator,
            const CATTessDataCache*& oTessData);

  /*
  static HRESULT __GenerateTessCacheForEntireBody(
            CATBody& iBody, 
            const CATTessParamToken& iToken,
            CATBoolean iExcludeEdges,
            CATBoolean iExcludeFaces,
            CATTessDataCreatorBase& iTessDataCreator,
            CATCGMProgressBar* iProgressBar);
  */

  friend class CATTessCacheWorkerAttribute;
  friend class CATTessParamAttribute;
};



INLINE HRESULT 
CATTessCacheEngineBase::DefineTessellationParameters(
            CATBody& iBody, 
            const CATTessParam& iTessParam, 
            CATTessParamToken& ioToken)
{
  return __DefineTessellationParameters(
            iBody, 
            iTessParam, 
            ioToken);
}

INLINE HRESULT 
CATTessCacheEngineBase::DefineTessellationParameters(
            CATFace& iFace, 
            const CATTessParam& iTessParam, 
            CATTessParamToken& ioToken)
{
  return __DefineTessellationParameters(
            iFace, 
            iTessParam, 
            ioToken);
}

INLINE HRESULT 
CATTessCacheEngineBase::DefineTessellationParameters(
            CATEdge& iEdge, 
            const CATTessParam& iTessParam, 
            CATTessParamToken& ioToken)
{
  return __DefineTessellationParameters(
            iEdge, 
            iTessParam, 
            ioToken);
}

INLINE HRESULT 
CATTessCacheEngineBase::GetExistingTessParamTokens(
            CATBody& iBody, 
            ListVOfCATTessParamToken& oTokens)
{
  return __GetExistingTessParamTokens(
            iBody, 
            oTokens);
}

INLINE HRESULT 
CATTessCacheEngineBase::GetExistingTessParamTokens(
            CATFace& iFace, 
            ListVOfCATTessParamToken& oTokens)
{
  return __GetExistingTessParamTokens(
            iFace, 
            oTokens);
}

INLINE HRESULT 
CATTessCacheEngineBase::GetExistingTessParamTokens(
            CATEdge& iEdge, 
            ListVOfCATTessParamToken& oTokens)
{
  return __GetExistingTessParamTokens(
            iEdge, 
            oTokens);
}

INLINE HRESULT 
CATTessCacheEngineBase::GetTessParamForGivenToken(
            CATBody& iBody, 
            const CATTessParamToken& iToken,
            CATTessParam& oTessParam)
{
  return __GetTessParamForGivenToken(
            iToken,
            oTessParam);
}

INLINE HRESULT 
CATTessCacheEngineBase::GetTessParamForGivenToken(
            CATFace& iFace, 
            const CATTessParamToken& iToken,
            CATTessParam& oTessParam)
{
  return __GetTessParamForGivenToken(
            iToken,
            oTessParam);
}

INLINE HRESULT 
CATTessCacheEngineBase::GetTessParamForGivenToken(
            CATEdge& iEdge, 
            const CATTessParamToken& iToken,
            CATTessParam& oTessParam)
{
  return __GetTessParamForGivenToken(
            iToken,
            oTessParam);
}

INLINE HRESULT 
CATTessCacheEngineBase::GetTessParamForGivenToken(
            const CATTessParamToken& iToken,
            CATTessParam& oTessParam)
{
  return __GetTessParamForGivenToken(
            iToken,
            oTessParam);
}

INLINE HRESULT 
CATTessCacheEngineBase::RemoveTessCacheData(
            CATBody& iBody,
            const CATTessParamToken& iToken)
{
  return __RemoveTessCacheData(
            iBody,
            iToken);
}

INLINE HRESULT 
CATTessCacheEngineBase::RemoveTessCacheData(
            CATFace& iFace,
            const CATTessParamToken& iToken)
{
  return __RemoveTessCacheData(
            iFace,
            iToken);
}

INLINE HRESULT 
CATTessCacheEngineBase::RemoveTessCacheData(
            CATEdge& iEdge,
            const CATTessParamToken& iToken)
{
  return __RemoveTessCacheData(
            iEdge,
            iToken);
}


#endif // !CATTessCacheEngineBase_H

