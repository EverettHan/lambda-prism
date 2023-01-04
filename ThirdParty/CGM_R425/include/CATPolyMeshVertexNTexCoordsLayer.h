// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMeshVertexNTexCoordsLayer.h
// Header definition of CATPolyMeshVertexNTexCoordsLayer
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// Feb 2009 Creation: ZFI
//===================================================================
#ifndef CATPolyMeshVertexNTexCoordsLayer_H
#define CATPolyMeshVertexNTexCoordsLayer_H

#include "PolyMeshImpl.h"

#include "CATPolyBuckets_T.h"
#include "CATErrorDef.h"     // HRESULT definition
#include "CATPolyRefCounted.h"
#include "CATListOfDouble.h"

class ExportedByPolyMeshImpl CATPolyMeshVertexNTexCoordsLayer  : public CATPolyRefCounted
{
public:
  CATPolyMeshVertexNTexCoordsLayer (); 
  virtual ~CATPolyMeshVertexNTexCoordsLayer ();  


public:
  HRESULT SetCoords(const int iIdxVertex, const double iX, const double iY, 
                    const int iKeySupport = 0);

  HRESULT GetCoords(const int iIdxVertex, double& oX, double& oY, 
                    const int iKeySupport = 0) const;


private:
  class TexCoords
  {
  public:
    TexCoords ():_KeySupport(0), _X(0), _Y(0), _AllCoords(0){}
    ~TexCoords()  
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

  class Specialize_CATPolyBuckets_T (TexCoordBuckets, TexCoords*);

  TexCoordBuckets _TexCoords;
};

#endif
