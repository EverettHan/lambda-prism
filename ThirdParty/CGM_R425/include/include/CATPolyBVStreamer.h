// COPYRIGHT DASSAULT SYSTEMES 2013, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBVStreamer.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// June 2013 Creation: AV7
//===================================================================
#ifndef CATPolyBVStreamer_h
#define CATPolyBVStreamer_h

// ExportedBy
#include "PolyBodyBVH.h"

// PolyhedralMathematics
#include "CATPolyBVConstVisitor.h"

class CATMathStream;
class CATPolyBoundingVolume;

class ExportedByPolyBodyBVH CATPolyBVStreamer: public CATPolyBVConstVisitor
{
public:
  
  CATPolyBVStreamer(CATMathStream & oStream, int iVersion = 0);
  
  ~CATPolyBVStreamer();

  HRESULT Stream(const CATPolyBoundingVolume & iBV);

private:

  virtual HRESULT VisitConcrete(const CATPolyBoundingSphere& iBV);
  
  virtual HRESULT VisitConcrete(const CATPolyBoundingPlane& iBV);
  
  virtual HRESULT VisitConcrete(const CATPolyAABB& iBV);

  virtual HRESULT VisitConcrete(const CATPolyOBB& iBV);

  virtual HRESULT VisitConcrete(const CATPolyBoundingCylinder& iBV);



  CATMathStream & _stream;
  int             _version;
};

#endif
