/*
SOU - W17 2016
*/
#ifndef CATGMLiveInputDataDraftManager_h
#define CATGMLiveInputDataDraftManager_h


#include "PersistentCell.h"
#include "CATCGMVirtual.h"
#include "ListPOfCATCellManifold.h"
#include "ListPOfCATEdge.h"
#include "CATGMLiveInputDataManager.h"
#include "CATMathConstant.h"

class CATCellManifoldsManager;
class CATPersistentCellInfra;
class CATlsoAgentInputDataCarrier;
class CATPersistentExtTopOperator;
class CATMathTransformation;
class CATCellManifold;
class CATGeoFactory;
class CATCGMJournalList;
class CATDeclarativeManifoldAgent;
class CATLiveBody;
class CATDeclarativeManifold;
class CATDraftManifold;
class CATMathDirection;

// @nocgmitf (this class doesn't need a CATIPGM interface)
class ExportedByPersistentCell CATGMLiveInputDataDraftManager : public CATGMLiveInputDataManager
{
public:

  //constructors
  CATGMLiveInputDataDraftManager();
  CATGMLiveInputDataDraftManager(CATCellManifoldsManager * iManifoldsManager, CATDraftManifold * iDraftManifold, ListPOfCATCellManifold & iResultCMList);
  //CATGMLiveInputDataDraftManager(CATPersistentCellInfra      * iPersistentCellInfra, CATPersistentExtTopOperator * iOperatorId, CATPersistentBody * iCurrentPBody, CATDraftManifold * iDraftManifold, ListPOfCATEdge & iResultEdgeList);

  //destructors
  virtual ~CATGMLiveInputDataDraftManager();

  CATBoolean GetNewValues (const CATMathDirection& iDir, CATAngle iAngle, CATMathDirection& oNewDir, CATAngle& oAngle);


private:

};

#endif
