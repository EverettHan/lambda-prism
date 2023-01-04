#ifndef CATCellManifoldOffsetGroupCarrierManager_H
#define CATCellManifoldOffsetGroupCarrierManager_H


#include "CATCGMNewArray.h"
#include "PersistentCell.h"
#include "CATCellManifoldSpecificGroupCarrierManager.h"
#include "CATCellManifoldGroupCarrier.h"
#include "CATManifoldAttribute.h"

class CATCellManifoldGroupCarrier;

class ExportedByPersistentCell CATCellManifoldOffsetGroupCarrierManager : public CATCellManifoldSpecificGroupCarrierManager
{	
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation
  // Constructor
  CATCellManifoldOffsetGroupCarrierManager(CATCellManifoldGroupCarrier *iGroupCarrier,CATDMAgentContext *iAgentContext,CATBoneFollowerPersistentFaceStructure *iOffsetStructure);

  // Destructor
  virtual ~CATCellManifoldOffsetGroupCarrierManager();

  virtual HRESULT ComputeNotUpToDateCMs(CATCellManifoldGroup * iParentCellManifoldGroup, CATCellManifoldGroup * iImageCellManifoldGroup);

  void UpdateAttributes();

  void GetNewOffsetValue(const CATLISTP(CATCellManifoldGroup) &iParentGroups, const CATCellManifoldGroup & iImageCellManifoldGroup, double & oOffsetValue, CATBoolean & oNullOffset);

  virtual void GetCellManifoldSpecificNavigators(CATLiveBody * iInputLiveBody, ListPOfCATCellManifoldGroupNavigator & oGroupNavigatorList);

  virtual CATCellManifoldOffsetGroupCarrierManager * GetAsCellManifoldOffsetGroupCarrierManager();

protected :
  
};
#endif

