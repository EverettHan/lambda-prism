// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyBVHTreeUnstream.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// Dec 2010 Creation: JXO
//===================================================================
#ifndef CATPolyBodyBVHTreeUnstream_h
#define CATPolyBodyBVHTreeUnstream_h

#include "PolyBodyBVH.h"

#include "CATPolyBVHTreeUnStream.h"
#include "CATMapOfIntToPtr.h"
#include "CATMapOfPtrToInt.h"

// Poly
class CATBVHTree;
class CATPolySubMesh;
class CATBVHNodeConst;
class CATPolyBVHAttribute;
class CATPolyUnstreamRecord;

// Math
class CATMathStream;

class ExportedByPolyBodyBVH CATPolyBodyBVHTreeUnstream : public CATPolyBVHTreeUnStream
{
public:

  /**
   * Constructor and destructor.
   */
  CATPolyBodyBVHTreeUnstream(CATMathStream & iStream);
  ~CATPolyBodyBVHTreeUnstream();

protected:
  virtual int UnStreamAttribute(CATBVHNode & iNode, CATMathStream & iStream, int nodetype);
  virtual CATBoolean CheckVersion(int version);
  virtual void SetMode(int mode);
  enum DescentMode
  {
    Full = 0,
    AsIs,
    Smart
  };
  virtual CATBVHNode * GetNewCATBVHNode(int nodetype, int nbchildren);
  void ReadMaxNbOfChildrenPerNode(CATBVHNode & iNode, CATMathStream & iStream);

private:

  CATPolyBVHAttribute   * _CurrentParentAttribute;
  CATMapOfIntToPtr        _MapOfIdsToAttributes;
  CATMapOfIntToPtr        _MapOfIdsToPolyBodies;
  CATMapOfPtrToInt        _CurrentMapOfSurfacesToIndices;
  CATMapOfPtrToInt        _CurrentMapOfCurvesToIndices;
  CATLONG32               _currentid;
  CATPolyUnstreamRecord * _record;
  DescentMode             _descentmode;
};

#endif // CATPolyBodyBVHTreeUnstream_H

