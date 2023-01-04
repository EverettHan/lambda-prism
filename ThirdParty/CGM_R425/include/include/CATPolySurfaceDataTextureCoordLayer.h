// COPYRIGHT DASSAULT SYSTEMES 2013, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolySurfaceDataTextureCoordLayer.h
//
//===================================================================
// January 2013  Creation: NDO
//===================================================================
#ifndef CATPolySurfaceDataTextureCoordLayer_H
#define CATPolySurfaceDataTextureCoordLayer_H

#include "PolyLayers.h"
#include "CATIPolySurfaceVertexTextureCoordLayer.h"

class CATIPolyDoublesLayer;


class ExportedByPolyLayers CATPolySurfaceDataTextureCoordLayer : public CATIPolySurfaceVertexTextureCoordLayer
{

public:

  static CATPolySurfaceDataTextureCoordLayer* New (CATIPolyDoublesLayer& iLayer);
  virtual ~CATPolySurfaceDataTextureCoordLayer ();

  const CATUnicodeString& GetIdentifier () const;
  unsigned int GetDimension () const;

public:

  HRESULT SetCoords (int v, double x, double y);
  HRESULT GetCoords (int v, double &x, double &y) const;

  HRESULT SetCoords (int iVertex, double x, double y, double z);
  HRESULT GetCoords (int iVertex, double& x, double& y, double& z) const;

  HRESULT Empty () {return S_FALSE;}
  CATBoolean HasCoords () const {return TRUE;}

public:

  HRESULT SetTangent (int iVertex, double tx, double ty, double tz) {return S_FALSE;}
  HRESULT SetBinormal (int iVertex, double bnx, double bny, double bnz) {return S_FALSE;}
  HRESULT SetScale (double scale) {return S_FALSE;}

  HRESULT GetTangent (int iVertex, double &tx, double &ty, double& tz) const {return S_FALSE;}
  HRESULT GetBinormal (int iVertex, double &bnx, double &bny, double &bnz) const {return S_FALSE;}
  HRESULT GetScale (double &scale) const {return S_FALSE;}
  
  CATBoolean HasTangents () const {return 0;}
  CATBoolean HasBinormals () const {return 0;}

private:

  CATIPolyDoublesLayer& _Layer;

private:

  CATPolySurfaceDataTextureCoordLayer (CATIPolyDoublesLayer& iLayer);

};

#endif
