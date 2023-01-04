// COPYRIGHT DASSAULT SYSTEMES 2013, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyBVHTreeNewUnstreamer.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// June 2013 Creation: AV7
// Jan  2014 Modification JXO: RegisterPolyBody
//===================================================================
#ifndef CATPolyBodyBVHTreeNewUnstreamer_h
#define CATPolyBodyBVHTreeNewUnstreamer_h

// PolyhedralMathematics
#include "CATMapOfIntToPtr.h"
#include "CATMapOfPtrToInt.h"

// PolyhedralObjects 
#include "CATPolyBVUnstreamer.h"
#include "CATPolyBVHTreeNewUnstreamer.h"

class ExportedByPolyBodyBVH CATPolyBodyBVHTreeNewUnstreamer : public CATPolyBVHTreeNewUnstreamer
{
public:

  /**
   * Constructor and destructor.
   */
  CATPolyBodyBVHTreeNewUnstreamer(CATMathStream & iStream);
  ~CATPolyBodyBVHTreeNewUnstreamer();

protected:
  
  virtual CATBVHNode * UnStreamBVHNode();

  virtual CATBVHAttribute * UnstreamAttribute();

private:

  void UnstreamBoundingVolumes(CATPolyBoundingVolume *& opBV1,
                               CATPolyBoundingVolume *& opBV2) const;

  CATPolyBVHAttribute * UnstreamPolyAttribute();

  CATBVHNode * GetNode(const CATLONG32 iType, CATBVHAttribute * ipAttribute) const;

  CATPolySubMesh * UnstreamSubMesh() const;

  HRESULT UnstreamPolyBody(CATPolyBody *& opPolyBody);
  HRESULT RegisterPolyBody(CATPolyBody & iPolyBody);

  CATPolyBVUnstreamer     _bvUnstreamer;
  CATPolyUnstreamRecord * _pPolyBodyUnstreamRecord;
  //CATMapOfIntToPtr        _mapOfIdsToPolyBodies;
  CATMapOfIntToPtr        _mapOfIdsToAttributes;
  CATMapOfPtrToInt        _currentMapOfSurfacesToIndices;
  CATMapOfPtrToInt        _currentMapOfCurvesToIndices;
  CATPolyBVHAttribute   * _pCurParentPolyAttribute;
  CATBVHVisuAttribute   * _pCurParentVisuAttribute;
  CATPolyBody           * _pUnstreamedPolyBody;
};

#endif

