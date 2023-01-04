// COPYRIGHT DASSAULT SYSTEMES 2021, ALL RIGHTS RESERVED.
//=============================================================================
//
// RESPONSIBLE  : ZUT
//
// DESCRIPTION  : CATCellManifoldPairingGroupLayer
//
//=============================================================================
// Creation ZUT February 2021
//=============================================================================

#ifndef CATCellManifoldPairingGroupLayer_H
#define CATCellManifoldPairingGroupLayer_H

#include "CATCGMNewArray.h"
#include "CATCellManifoldGroupLayer.h"
#include "CATGMModelInterfaces.h"

class ExportedByCATGMModelInterfaces CATCellManifoldPairingGroupLayer : public CATCellManifoldGroupLayer
{
public:
  CATCGMDeclareAttribute (CATCellManifoldPairingGroupLayer, CATCellManifoldGroupLayer);

  CATCellManifoldPairingGroupLayer(); 
  virtual ~CATCellManifoldPairingGroupLayer();

  virtual CATBoolean IsHierarchichal();
  virtual CATBoolean IsContextual();
  virtual HRESULT IsCellManifoldGroupMergeAllowed(CATBoolean iWithCellManifoldBelongingToAnOtherGroup);

  virtual void Stream(CATCGMStream & ioStream) const;
  virtual void UnStream(CATCGMStream& ioStream);
  
  virtual void Dump(CATCGMOutput & oStr) const; 

  HRESULT CreateGroupNavigators(CATLiveBody * iLiveBody, CATTopData & iTopData, CATLISTP(CATCellManifoldGroupNavigator) & oListOfNavigator);

private:
};

#endif /* CATCellManifoldPairingGroupLayer_H */
