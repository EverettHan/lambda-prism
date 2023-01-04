//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2021
//=============================================================================
//
// CATPolyPersistencyLayer
//
// information about persistency - atomic operation
//
//=============================================================================
// 08/21 : F1Z : Creation
//=============================================================================

#pragma once

// CATMathStram
#include "CATMathStream.h"

// Polyhedral Interfaces
#include "CATIPolyLayer.h"


class CATPolyPersistencyLayer : public CATIPolyLayer
{
private:
  int _count;

public:
  CATPolyPersistencyLayer();
  ~CATPolyPersistencyLayer();

  static const CATPolyPersistencyLayer* Cast (const CATIPolyLayer* iLayer);
  static CATPolyPersistencyLayer* Cast (CATIPolyLayer* iLayer);

  const CLSID& GetClassID() const;
  static const CLSID& ClassID();

  bool IsPersistent() const;

  void Increment();
  bool Decrement();

  void Stream(CATMathStream& ioStream);
  void Unstream(CATMathStream& ioStream);
};


