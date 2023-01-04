// COPYRIGHT DASSAULT SYSTEMES 2013, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyBVHTreeNewStreamer.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// June 2013 Creation: AV7
//===================================================================
#ifndef CATPolyBodyBVHTreeNewStreamer_h
#define CATPolyBodyBVHTreeNewStreamer_h

// PolyhedralMathematics
#include "CATMapOfPtrToInt.h"

// PolyhedralObjects
#include "CATPolyBVHTreeNewStreamer.h"

// PolyhedralObjects
class CATPolyBody;
class CATPolySubMesh;
class CATPolyStreamRecord;
class CATPolyBVHAttribute;

class ExportedByPolyBodyBVH CATPolyBodyBVHTreeNewStreamer : public CATPolyBVHTreeNewStreamer
{
public:

  CATPolyBodyBVHTreeNewStreamer(CATMathStream & oStream, DescentMode mode);
  ~CATPolyBodyBVHTreeNewStreamer();

  virtual HRESULT StreamNode(CATBVHNodeConst & iNode, CATBoolean & oContinueDescent);
  
  virtual HRESULT StreamAttribute(CATBVHAttribute * ipAttribute);

  virtual HRESULT PreProcessingForTreeTraversal();

  virtual HRESULT PostProcessingForTreeTraversal();

private:

  HRESULT StreamPolyBody(CATPolyBody * ipPolyBody);

  HRESULT StreamPolyAttribute(CATPolyBVHAttribute * ipPolyAttribute);

  HRESULT StreamSubMesh(CATPolySubMesh * ipSubMesh);

  CATPolyStreamRecord * _pPolyBodyStreamRecord;
  CATMapOfPtrToInt      _mapOfAttributesToIds;
  CATLONG32             _currentId;
  
  enum BitFields
  {
    /** Bit 0 set. */      BitSmartNodeExpStopped         = 0x00000001,
    /** Bit 1 set. */      BitSmartRepNodeExpStopped      = 0x00000002,
    /** Bit 2 set. */      BitISmartNodeExpStopped        = 0x00000004
  };

  unsigned int _currentNodeExpStatus;
};

#endif

