/* -*-C++-*- */

#ifndef CATCellManifoldBRepCopyNavigator_H
#define CATCellManifoldBRepCopyNavigator_H
// ----------------------------------------------------------------------------------------------//
// COPYRIGHT DASSAULT SYSTEMES 2013
// ----------------------------------------------------------------------------------------------//


#include "CATCellManifoldBRepCopyNavigatorInterface.h"
#include "CATPersistentCell.h"

class CATLiveBody;
class CATCellManifoldGroup;

class CATCellManifoldBRepCopyNavigator : public CATCellManifoldBRepCopyNavigatorInterface
{
public:

  // Constructor
  CATCellManifoldBRepCopyNavigator(); 
  CATCellManifoldBRepCopyNavigator(CATLiveBody* iLiveBody, CATCellManifoldGroup* iNetworkGroup); 

  //CATCGMNewClassArrayDeclare;      // Pool allocation
  CATCGMDeclareManifoldNavigator(CATCellManifoldBRepCopyNavigator, CATCellManifoldBRepCopyNavigatorInterface);

  // Destructor
  virtual ~CATCellManifoldBRepCopyNavigator();

  //Interface methods
  HRESULT GetCellManifoldLists(ListPOfListPOfCATCellManifolds& oCellManifoldLists) const; 

private:
  HRESULT GetNetworkGroup(CATCellManifoldGroup *& oNetworkGroup) const;

  CATLiveBody          * _LiveBody;
  CATCellManifoldGroup * _NetworkGroup;

};

// ---------------------------------------
// CATCreateCellManifoldBRepCopyNavigator
// ---------------------------------------
ExportedByPersistentCell CATCellManifoldBRepCopyNavigatorInterface* CATCreateCellManifoldBRepCopyNavigator(CATLiveBody* iLiveBody, CATCellManifoldGroup* iNetworkGroup); 

#endif
