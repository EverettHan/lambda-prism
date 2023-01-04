//=================================================================================================
// COPYRIGHT DASSAULT SYSTEMES 2013, ALL RIGHTS RESERVED.
//=================================================================================================
//
// CATBVHDynamicLoader.h
//
//=================================================================================================
//
// Usage notes: A dynamic loader class to call methods from other modules by loading them
//              dynamically
//=================================================================================================
// 2013-04-25   AV7: New.
// 2014-01-20   JXO: New arguments to UnstreamVisuAttribute
//=================================================================================================

#ifndef CATBVHDynamicLoader_h
#define CATBVHDynamicLoader_h

// ExportedBy
#include "PolyBodyBVH.h"

// Poly
class CATPolyBody;
class CATPolyUnstreamRecord;
#include "CATPolyBodyBVHTreeNewStreamer.h"

// SpecialAPI
#include "CATSysBoolean.h"
#include "CATErrorDef.h"

class CATMathStream;
class CATBVHAttribute;
class CATBVHNodeConst;
class CATBVHVisuAttribute;
class CATPolyStreamRecord;
class CATPolyUnstreamRecord;

class ExportedByPolyBodyBVH CATBVHDynamicLoader
{
public:

  static HRESULT StreamSmartRepNode(CATBVHNodeConst & iNode, 
                                    CATLONG32         iStreamMode,
                                    CATMathStream   & oStream);
 
  static CATBVHNodeConst * UnstreamSmartRepNode(CATMathStream   & iStream, 
                                                CATBVHAttribute * ipAttribute);

  static void StopSmartRepNodeExpand(CATBoolean iStopExpand);

  static CATBoolean IsSmartRepNodeExpandStopped();

  static HRESULT StreamVisuAttribute(CATBVHVisuAttribute * ipAttribute, CATMathStream & oStream);

  static HRESULT UnstreamVisuAttribute(CATMathStream & iStream, CATBVHVisuAttribute *& opVisuAttribute, CATPolyBodyBVHTreeNewStreamer::DescentMode iMode, CATPolyUnstreamRecord *& pPolyBodyUnstreamRecord, CATPolyBody *& pPolyBody);

  static HRESULT StreamVisuGPAttribute(CATBVHVisuAttribute  * ipAttribute, 
                                       CATPolyStreamRecord  * ipRecord,
                                       CATMathStream        & oStream);

  static CATBVHAttribute * UnstreamVisuGPAttribute(CATPolyUnstreamRecord  * ipRecord,
                                                   CATBVHVisuAttribute    * ipParentAttribute,
                                                   CATMathStream          & iStream);


};

#endif
