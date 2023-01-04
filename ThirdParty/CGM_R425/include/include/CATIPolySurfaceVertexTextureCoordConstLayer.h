// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolySurfaceVertexTextureCoordConstLayer.h
//
//===================================================================
// May 2010  Creation: NDO
//===================================================================
#ifndef CATIPolySurfaceVertexTextureCoordConstLayer_H
#define CATIPolySurfaceVertexTextureCoordConstLayer_H

#include "PolyhedralAttributes.h"
#include "CATIPolyDoublesLayer.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"

class CATIPolySurfaceVertexTextureCoordLayer;
class CATUnicodeString;


class ExportedByPolyhedralAttributes CATIPolySurfaceVertexTextureCoordConstLayer : public CATIPolyDoublesLayer
{

public:

  virtual HRESULT GetCoords(int iVertex, double &x, double &y) const = 0;

  virtual HRESULT GetCoords(int iVertex, double &x, double &y, double &z) const = 0;

  virtual HRESULT GetTangent(int iVertex, double &tx, double &ty, double& tz) const = 0;

  virtual HRESULT GetBinormal(int iVertex, double &bnx, double &bny, double &bnz) const =0;

  virtual HRESULT GetScale(double &scale) const = 0;

  virtual CATBoolean HasCoords() const = 0;
  virtual CATBoolean HasTangents() const = 0;
  virtual CATBoolean HasBinormals() const = 0;

public:

  static const CATIPolySurfaceVertexTextureCoordConstLayer* Cast (const CATIPolyLayer*);
  static CATIPolySurfaceVertexTextureCoordConstLayer* Cast (CATIPolyLayer*);

  static const CLSID& ClassID ();
  const CLSID& GetClassID () const;

  virtual const CATUnicodeString& GetIdentifier () const;
  unsigned int GetDimension () const { return 3; }

  virtual HRESULT Get (int v, double* a) const;

  /**
   * Casts as a non-const layer.
   */
  virtual CATIPolySurfaceVertexTextureCoordLayer* NonConstCast ();

private:

  static const CLSID _ClassID;

protected:

  virtual ~CATIPolySurfaceVertexTextureCoordConstLayer () {}

};

#endif // !CATIPolySurfaceVertexTextureCoordConstLayer_H
