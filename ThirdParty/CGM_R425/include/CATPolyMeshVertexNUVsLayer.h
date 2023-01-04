// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMeshVertexNUVsLayer.h
// Header definition of CATPolyMeshVertexNUVsLayer
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// Nov 2009 Creation: ZFI
//===================================================================

#ifndef CATPolyMeshVertexNUVsLayer_H
#define CATPolyMeshVertexNUVsLayer_H

#include "PolyMeshImpl.h"

#include "CATPolyBuckets_T.h"
#include "CATErrorDef.h"     // HRESULT definition
#include "CATPolyRefCounted.h"
#include "CATListOfDouble.h"

class ExportedByPolyMeshImpl CATPolyMeshVertexNUVsLayer  : public CATPolyRefCounted
{
public:
  CATPolyMeshVertexNUVsLayer (); 
  virtual ~CATPolyMeshVertexNUVsLayer ();  


public:
  HRESULT SetCoords(const int iIdxVertex, const double iX, const double iY, 
                    const int iKeySupport = 0);

  HRESULT GetCoords(const int iIdxVertex, double& oX, double& oY, 
                    const int iKeySupport = 0) const;


private:
  class UVs
  {
  public:
    UVs ():_KeySupport(0), _X(0), _Y(0), _AllCoords(0){}
    ~UVs()  
    {
      _KeySupport=0; 
      _X=0; 
      _Y=0; 
      if (_AllCoords) 
        delete _AllCoords; 
      _AllCoords = NULL;
    }
    inline void Reset ();

  public:
    int _KeySupport;
    double _X;
    double _Y;

    CATListOfDouble* _AllCoords;
  };

  class Specialize_CATPolyBuckets_T (UVBuckets, UVs*);

  UVBuckets _UVs;
};

#endif
