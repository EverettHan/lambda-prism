/*
VB7 - W08 2017
*/
#ifndef CATGMLiveInputDataSphereManager_h
#define CATGMLiveInputDataSphereManager_h


#include "PersistentCell.h"
#include "CATCGMVirtual.h"
#include "ListPOfCATCellManifold.h"
#include "ListPOfCATEdge.h"
#include "CATGMLiveInputDataManager.h"
#include "CATMathLine.h"

class CATCellManifoldsManager;
class CATPersistentCellInfra;
class CATSphereManifold;
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
class ExportedByPersistentCell CATGMLiveInputDataSphereManager : public CATGMLiveInputDataManager
{
public:

  //constructors
  CATGMLiveInputDataSphereManager();
  CATGMLiveInputDataSphereManager(CATGMLiveInputDataManager * iInputDataManager);
  CATGMLiveInputDataSphereManager(CATCellManifoldsManager * iManifoldsManager, CATSphereManifold * iSphereManifold, ListPOfCATCellManifold & iResultCMList);
  
  CATBoolean HasEditingData();

  void GetNewRadius(CATPositiveLength & iRadius, CATPositiveLength & oNewRadius);
  void GetNewCenter(CATMathPoint & iCenter, CATMathPoint & oCenter);

  //destructors
  virtual ~CATGMLiveInputDataSphereManager();

  virtual CATGMLiveInputDataSphereManager * GetAsInputDataSphereManager();

private:

};

#endif
