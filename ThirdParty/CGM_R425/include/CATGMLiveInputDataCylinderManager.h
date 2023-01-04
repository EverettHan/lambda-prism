/*
VB7 - W11 2015
*/
#ifndef CATGMLiveInputDataFilletManager_h
#define CATGMLiveInputDataFilletManager_h


#include "PersistentCell.h"
#include "CATCGMVirtual.h"
#include "ListPOfCATCellManifold.h"
#include "ListPOfCATEdge.h"
#include "CATGMLiveInputDataManager.h"
#include "CATMathLine.h"

class CATCellManifoldsManager;
class CATPersistentCellInfra;
class CATCylinderManifold;
class CATlsoAgentInputDataCarrier;
class CATPersistentExtTopOperator;
class CATMathTransformation;
class CATCellManifold;
class CATGeoFactory;
class CATCGMJournalList;
class CATDeclarativeManifoldAgent;
class CATLiveBody;
class CATDeclarativeManifold;

// @nocgmitf (this class doesn't need a CATIPGM interface)
class ExportedByPersistentCell CATGMLiveInputDataCylinderManager : public CATGMLiveInputDataManager
{
public:

  //constructors
  CATGMLiveInputDataCylinderManager();
  CATGMLiveInputDataCylinderManager(CATGMLiveInputDataManager * iInputDataManager);
  CATGMLiveInputDataCylinderManager(CATCellManifoldsManager * iManifoldsManager, CATCylinderManifold * iCylinderManifold, ListPOfCATCellManifold & iResultCMList);
  
  CATBoolean HasEditingData();

  HRESULT GetNewRadius(CATPositiveLength & iRadius, CATPositiveLength & oNewRadius);
  void GetNewAxis(CATMathLine & iAxis, CATMathLine & oNewAxis);

  //destructors
  virtual ~CATGMLiveInputDataCylinderManager();

  virtual CATGMLiveInputDataCylinderManager * GetAsInputDataCylinderManager();

private:

};

#endif
