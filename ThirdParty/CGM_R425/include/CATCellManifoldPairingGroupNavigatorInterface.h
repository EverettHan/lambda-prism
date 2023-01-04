// COPYRIGHT DASSAULT SYSTEMES 2021, ALL RIGHTS RESERVED.
//=============================================================================
//
// RESPONSIBLE  : ZUT
//
// DESCRIPTION  : CATCellManifoldPairingGroupNavigatorInterface
//
//=============================================================================
// Creation ZUT February 2021
//=============================================================================


#ifndef CATCellManifoldPairingGroupNavigatorInterface_H
#define CATCellManifoldPairingGroupNavigatorInterface_H

#include "CATGMModelInterfaces.h"
#include "CATCellManifoldGroupNavigator.h"
#include "ListPOfCATCellManifold.h" 
#include "CATBoolean.h"

class CATCellManifoldPairingGroupNavigator;
class CATCellManifoldGroup;
class CATCellManifold;

class ExportedByCATGMModelInterfaces CATCellManifoldPairingGroupNavigatorInterface : public CATCellManifoldGroupNavigator
{
public:
  CATCGMNewClassArrayDeclare; // Pool allocation

  // Constructor
  CATCellManifoldPairingGroupNavigatorInterface(); 

  // Destructor
  virtual ~CATCellManifoldPairingGroupNavigatorInterface();

  // Cast
  CATCellManifoldPairingGroupNavigatorInterface * GetAsPairingGroupNavigatorInterface();

  virtual HRESULT GetDeclarativeType(CATDeclarativeType & oType) const = 0;

  virtual HRESULT GetNetworkGroup(CATCellManifoldGroup *& oNetworkGroup) const = 0;
  
  virtual HRESULT GetAllCellManifolds(CATLISTP(CATCellManifold) & oListOfCellManifolds) const = 0;

  // Checks if CellManifold belongs to PairingGroup: 0 = No, 1 = Yes 
  virtual CATBoolean BelongsToPairingGroup(CATCellManifold * iCM) const = 0;

  void Dump(CATCGMOutput & oStr);
};

#endif /* CATCellManifoldPairingGroupNavigatorInterface */
