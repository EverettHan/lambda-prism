#ifndef CATCellManifoldBRepCopyNavigatorInterface_H
#define CATCellManifoldBRepCopyNavigatorInterface_H

#include "CATCellManifoldGroupNavigator.h"
#include "CATGMModelInterfaces.h"
#include "ListPOfListPOfCATCellManifolds.h"

class ExportedByCATGMModelInterfaces CATCellManifoldBRepCopyNavigatorInterface : public CATCellManifoldGroupNavigator
{
public:
  // Constructor
  CATCellManifoldBRepCopyNavigatorInterface(); 

  // Destructor
  virtual ~CATCellManifoldBRepCopyNavigatorInterface();

  virtual HRESULT GetCellManifoldLists(ListPOfListPOfCATCellManifolds& oCellManifoldLists) const = 0; 

  CATCellManifoldBRepCopyNavigatorInterface* GetAsBRepCopyNavigatorInterface();

  CATCGMNewClassArrayDeclare;

protected:
  void Dump(CATCGMOutput& Output);

};


#endif
