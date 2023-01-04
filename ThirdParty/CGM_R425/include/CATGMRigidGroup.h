//===================================================================
// COPYRIGHT [!output company] 2010/10/20
//===================================================================
// Header definition of class CATGMRigidGroup
//===================================================================

// Interface on a CDMRigidGroup, dedicated for applications that may not require CDMModel framework
// These objects are twins of CDMRigidGroup, their lifecycles are identical

//===================================================================
//  2010/10/20 Creation: chu
//===================================================================
#ifndef CATGMRigidGroup_H
#define CATGMRigidGroup_H

#include "CATErrorDef.h"
#include "CATSysBoolean.h"
#include "ListPOfCATCellManifold.h" 
#include "CATListOfCATCells.h"
#include "ListPOfCATBody.h"
#include "CATListOfCATGeometries.h"
#include "ListPOfGMRigidGroup.h"
#include "CATCDMBaseInterfaces.h" // export

class CDMRigidGroup;
class CATBody;

class ExportedByCATCDMBaseInterfaces CATGMRigidGroup
{
public:

  // Lifecycle
  virtual ~CATGMRigidGroup();

  // Get objects gathered by the group
  // Note: lists of cells (or cell_manifolds) and bodies have same size, elements are paired 
  virtual HRESULT GetGroupedCellManifolds(CATLISTP(CATCellManifold) & oCellManifoldsList, CATLISTP(CATBody) & oBodiesList) = 0;
  virtual HRESULT GetGroupedCells(CATListPtrCATCell & oCellsList, CATLISTP(CATBody) & oBodiesList) = 0;
  virtual HRESULT GetGroupedGeometries(CATLISTP(CATGeometry) & oGeometryList, CATLISTP(CATBody) & oBodiesList) = 0;

  // Navigation (rigid groups may gather sub-rigid-groups in a tree structure)
  virtual HRESULT GetOwnedRigidGroups(CATListPtrCATGMRigidGroup & oRigidGroups) = 0;
  virtual HRESULT GetOwnerRigidGroup(CATGMRigidGroup *& oRigidGroup) = 0;

  // Internal Use
  virtual CDMRigidGroup & GetAssociatedCDMRigidGroup() = 0;
  
  // Get an Id stable during stream/unstream
  virtual CATULONG32 GetStableId() = 0;

protected:

  CATGMRigidGroup();

private:

  // The copy constructor and the equal operator must not be implemented
  CATGMRigidGroup (CATGMRigidGroup &);
  CATGMRigidGroup& operator=(CATGMRigidGroup&);

};

//-----------------------------------------------------------------------
#endif
