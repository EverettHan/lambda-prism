/*
VB7 - W27 2016
*/
#ifndef CATGMLiveInputDataCMGManager_h
#define CATGMLiveInputDataCMGManager_h


#include "PersistentCell.h"
#include "CATCGMVirtual.h"
#include "ListPOfCATCellManifold.h"
#include "ListPOfCATEdge.h"
#include "CATGMLiveInputDataManager.h"

class CATCellManifoldsManager;
class CATPersistentCellInfra;
class CATBoneFillet;
class CATlsoAgentInputDataCarrier;
class CATPersistentExtTopOperator;
class CATMathTransformation;
class CATCellManifold;
class CATGeoFactory;
class CATCGMJournalList;
class CATDeclarativeManifoldAgent;
class CATHVertex;
class CATLiveBody;
class CATDeclarativeManifold;

// @nocgmitf (this class doesn't need a CATIPGM interface)
class ExportedByPersistentCell CATGMLiveInputDataCMGManager : public CATGMLiveInputDataManager
{
public:

  //constructors
  CATGMLiveInputDataCMGManager();
  CATGMLiveInputDataCMGManager(CATGMLiveInputDataCMGManager * iInputDataCMGManager);
  CATGMLiveInputDataCMGManager(CATCellManifoldsManager * iManifoldsManager, CATCellManifoldGroup * iCellManifoldGroup, ListPOfCATCellManifold & iResultCMList);

  //destructors
  virtual ~CATGMLiveInputDataCMGManager();

  virtual CATGMLiveInputDataCMGManager * GetAsInputDataCMGManager();

private:

};

#endif
