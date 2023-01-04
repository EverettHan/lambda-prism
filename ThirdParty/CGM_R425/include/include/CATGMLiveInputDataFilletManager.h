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
class ExportedByPersistentCell CATGMLiveInputDataFilletManager : public CATGMLiveInputDataManager
{
public:

  //constructors
  CATGMLiveInputDataFilletManager();
  CATGMLiveInputDataFilletManager(CATGMLiveInputDataManager * iInputDataManager);
  CATGMLiveInputDataFilletManager(CATCellManifoldsManager * iManifoldsManager, CATBoneFillet * iBoneFillet, ListPOfCATCellManifold & iResultCMList);
  CATGMLiveInputDataFilletManager(CATPersistentCellInfra  * iPersistentCellInfra, CATlsoAgentInputDataCarrier * iAgentInputDataCarrier, CATPersistentBody * iCurrentPBody, CATBoneFillet * iBoneFillet, ListPOfCATEdge & iResultEdgeList);
  
  //destructors
  virtual ~CATGMLiveInputDataFilletManager();

  double GetNewRadius(double iOldRadius);

  static CATMathTransformation * GetTransfo(CATHVertex* iSource, CATHVertex* iTarget, CATCellManifoldsManager * iManifoldsManager);

  virtual CATGMLiveInputDataFilletManager * GetAsInputDataFilletManager();

private:
  CATMathTransformation * GetTransfo(CATHVertex* iSource);

};

#endif
