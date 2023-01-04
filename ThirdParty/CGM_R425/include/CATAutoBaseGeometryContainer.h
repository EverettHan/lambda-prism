#ifndef CATAutoBaseGeometryContainer_H
#define CATAutoBaseGeometryContainer_H
//=============================================================================
// COPYRIGHT Dassault Systemes 2004
//=============================================================================
//
// CATAutoBaseGeometryContainer.h
// Declare a container of possibly unrelated geometric objects.
// 		
//=============================================================================
//  Dec 02, 2004
//      * BPG: Creation
//=============================================================================

#include "PersistentCell.h"
#include "CATTopRibTraceObject.h"
#include "CATListOfCATGeometries.h"

class CATGeometry;
class CATAutoBaseColor;

class ExportedByPersistentCell CATAutoBaseGeometryContainer :
  public CATTopRibTraceObject
{
public:
  CATCGMNewClassArrayDeclare; // Pool allocation

public:
  CATAutoBaseGeometryContainer(CATGeoFactory &iFactory);
  virtual ~CATAutoBaseGeometryContainer();

  void Delete();

public:
  void Append(CATGeometry *iGeometry);
  void MergeInto(CATAutoBaseGeometryContainer &iTargetContainer);

public:
  void Show(const CATAutoBaseColor &iColor);
  void NoShow();

private:
  CATLISTP(CATGeometry) _Geometries;
  CATGeoFactory &_Factory;
};

#endif // !CATAutoBaseGeometryContainer_H
