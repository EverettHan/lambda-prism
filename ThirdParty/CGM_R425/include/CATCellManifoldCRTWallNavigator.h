#ifndef CATCellManifoldCRTWallNavigator_H
#define CATCellManifoldCRTWallNavigator_H

#include "CATGMModelInterfaces.h"
#include "CATCellManifoldCRTNavigator.h"
#include "ListPOfCATCellManifold.h"
#include "CATErrorDef.h"
#include "CATListOfShort.h"
#include "ListPOfCATCellManifoldGroup.h"

class ExportedByCATGMModelInterfaces CATCellManifoldCRTWallNavigator : public CATCellManifoldCRTNavigator
{
public:

  // Constructor
  CATCellManifoldCRTWallNavigator(); 

  // Destructor
  virtual ~CATCellManifoldCRTWallNavigator();

  virtual CATCellManifoldCRTWallNavigator* GetAsCRTWallNavigator();

  virtual HRESULT GetWallGroup(CATCellManifoldGroup*& oWallGroup)=0;

  virtual HRESULT GetOrientedBendGroupList(CATLiveBody *iContextLiveBody, CATSoftwareConfiguration* ipConfig, ListPOfCATCellManifoldGroup &oBendGroupList, CATListOfShort &oLoopChangeIndexes);

  virtual HRESULT IsPlanar(CATSoftwareConfiguration* ipConfig, CATBoolean &oIsPlanar);

protected:
  void Dump(CATCGMOutput& Output);

};


#endif
