// COPYRIGHT DASSAULT SYSTEMES 2020, ALL RIGHTS RESERVED.
//=============================================================================
//
// RESPONSIBLE  : ZUT
//
// DESCRIPTION  : CATCellManifoldVolatileDraftGroupNavigatorInterface
//
//=============================================================================
// Creation ZUT March 2020
//=============================================================================


#ifndef CATCellManifoldVolatileDraftGroupNavigatorInterface_H
#define CATCellManifoldVolatileDraftGroupNavigatorInterface_H

#include "CATGMModelInterfaces.h"
#include "CATCellManifoldGroupNavigator.h"
#include "ListPOfCATCellManifold.h" 
#include "CATBoolean.h"

class CATCellManifoldVolatileDraftGroupNavigator;
class CATCellManifoldGroup;
class CATCellManifold;

class ExportedByCATGMModelInterfaces CATCellManifoldVolatileDraftGroupNavigatorInterface : public CATCellManifoldGroupNavigator
{
public:
  CATCGMNewClassArrayDeclare; // Pool allocation

  // Constructor
  CATCellManifoldVolatileDraftGroupNavigatorInterface(); 

  // Destructor
  virtual ~CATCellManifoldVolatileDraftGroupNavigatorInterface();

  // Cast
  CATCellManifoldVolatileDraftGroupNavigatorInterface * GetAsVolatileDraftGroupNavigatorInterface();

  virtual HRESULT GetDeclarativeType(CATDeclarativeType & oType) const = 0;

  virtual HRESULT GetNetworkGroup(CATCellManifoldGroup *& oNetworkGroup) const = 0;
  
  virtual HRESULT GetAllCellManifolds(CATLISTP(CATCellManifold) & oListOfCellManifolds) const = 0;

  // Checks if CellManifold belongs to VolatileDraftGroup: 0 = No, 1 = Yes 
  virtual CATBoolean BelongsToVolatileDraftGroup(CATCellManifold * iCM) const = 0;

  void Dump(CATCGMOutput & oStr);
};

#endif /* CATCellManifoldVolatileDraftGroupNavigatorInterface */
