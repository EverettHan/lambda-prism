//=============================================================================
// COPYRIGHT Dassault Systemes 2007
//=============================================================================
//
// CATPolyBoundingVolume.h
//
//=============================================================================
// 2007-05-21   BPG: New
//=============================================================================
#ifndef CATPolyBoundingVolume_H
#define CATPolyBoundingVolume_H

#include "PolyMathBV.h"
#include "CATErrorDef.h"  // Definition of HRESULT.
#include "CATSysBoolean.h"

class CATPolyBVConstVisitor;


class ExportedByPolyMathBV CATPolyBoundingVolume
{
public:

  // Comment: Not needed (that would save some memory below!) -NDO
  enum TypeID
    { AABBType,
      SphereType,
      OBBType,
      PlaneType,
      CapsCylinderType,
      CylinderType = CapsCylinderType};

public:

  CATPolyBoundingVolume () {}
  virtual ~CATPolyBoundingVolume(){}

public:

  virtual HRESULT Accept (CATPolyBVConstVisitor& iVisitor) const = 0;
  //virtual HRESULT Accept (CATPolyBVVisitor& iVisitor) = 0;  // Not sure anyone need a non-const visitor. -NDO

  virtual CATBoolean IsEmpty() const = 0;

public:
  virtual TypeID GetTypeID() const = 0; 

};

// ----------------------------------------------------------------------------

#endif // !CATPolyBoundingVolume_H
