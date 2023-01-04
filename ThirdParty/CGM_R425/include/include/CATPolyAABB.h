//=============================================================================
// COPYRIGHT Dassault Systemes 2007
//=============================================================================
//
// CATPolyAABB.h
//
//=============================================================================
// 2007-05-21   BPG: New
//=============================================================================
#ifndef CATPolyAABB_H
#define CATPolyAABB_H

#include "PolyMathBV.h"
#include "CATPolyBoundingVolume.h"
#include "CATPolyPool.h"
#include "CATPolyBoxf.h"

#include "CATMathBox.h"

class ExportedByPolyMathBV CATPolyAABB
  : public CATPolyBoundingVolume
{
  CATPolyDeclarePooledNew;

public:

  CATPolyAABB(const CATPolyBoxf &iBox) : _Box(iBox) {}
  CATPolyAABB(const CATMathBox &iBox) : _Box(iBox) {}

  CATPolyAABB () {}

  virtual ~CATPolyAABB (){}

  TypeID GetTypeID() const; 

public:
  inline const CATPolyBoxf &GetBoxf() const { return _Box; }
  inline void SetBoxf(const CATPolyBoxf & box) { _Box = box; }
  inline void SetMathBox(const CATMathBox & box) { _Box = box; }

  CATBoolean operator ==(const CATPolyAABB & box);

public:

  HRESULT Accept (CATPolyBVConstVisitor& iVisitor) const;

  virtual CATBoolean IsEmpty() const;

protected:
  CATPolyBoxf _Box;

};


#endif // !CATPolyAABB_H
