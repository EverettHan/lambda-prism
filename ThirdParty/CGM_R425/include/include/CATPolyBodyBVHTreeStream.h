// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyBVHTreeStream.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// Dec 2010 Creation: JXO
//===================================================================
#ifndef CATPolyBodyBVHTreeStream_h
#define CATPolyBodyBVHTreeStream_h

#include "PolyBodyBVH.h"

#include "CATPolyBVHTreeStream.h"
#include "CATMapOfPtrToInt.h"


// Poly
class CATBVHTree;
class CATPolySubMesh;
class CATBVHNodeConst;
class CATPolyBVHAttribute;
class CATPolyStreamRecord;

// Math
class CATMathStream;


class ExportedByPolyBodyBVH CATPolyBodyBVHTreeStream : public CATPolyBVHTreeStream
{
public:

  /**
   * Constructor and destructor.
   */
  CATPolyBodyBVHTreeStream(CATMathStream & oStream, DescentMode mode = Smart);
  ~CATPolyBodyBVHTreeStream();

  virtual int Stream(CATBVHTree & Tree);


protected:
  virtual int StreamAttribute(CATBVHNodeConst & iNode, CATMathStream & oStream, CATBoolean & ocontinuedescent);

private:

  DescentMode _descentmode;

  CATPolyBVHAttribute * _CurrentParentAttribute;
  CATMapOfPtrToInt      _MapOfAttributesToIds;
  int                   _currentid;
  CATPolyStreamRecord * _record;
};

#endif // CATPolyBodyBVHTreeStream_H

