// COPYRIGHT DASSAULT SYSTEMES 2013, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBVHTreeNewStreamer.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// June 2013 Creation: AV7
//===================================================================
#ifndef CATPolyBVUnstreamer_h
#define CATPolyBVUnstreamer_h

// ExportedBy
#include "PolyBodyBVH.h"

class CATMathStream;
class CATPolyBoundingVolume;

class ExportedByPolyBodyBVH CATPolyBVUnstreamer
{
public:
  
  CATPolyBVUnstreamer(CATMathStream & oStream, int iVersion = 0);
  
  ~CATPolyBVUnstreamer();

  CATPolyBoundingVolume *  Unstream() const;

  void SetVersion(int iVersion);

private:

  CATMathStream & _stream;
  int             _version;
};

#endif
