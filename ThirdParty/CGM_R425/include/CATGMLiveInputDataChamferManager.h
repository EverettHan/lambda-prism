/*
VB7 - W11 2015
*/
#ifndef CATGMLiveInputDataChamferManager_h
#define CATGMLiveInputDataChamferManager_h


#include "PersistentCell.h"
#include "CATCGMVirtual.h"
#include "ListPOfCATCellManifold.h"
#include "ListPOfCATEdge.h"
#include "CATGMLiveInputDataManager.h"

class CATCellManifoldsManager;
class CATPersistentCellInfra;
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
class CATBoneChamfer;

// @nocgmitf (this class doesn't need a CATIPGM interface)
class ExportedByPersistentCell CATGMLiveInputDataChamferManager : public CATGMLiveInputDataManager
{
public:

  //constructors
  CATGMLiveInputDataChamferManager();
  CATGMLiveInputDataChamferManager(CATCellManifoldsManager * iManifoldsManager, CATBoneChamfer * iBoneChamfer, ListPOfCATCellManifold & iResultCMList);

  //destructors
  virtual ~CATGMLiveInputDataChamferManager();

  void GetNewLeftAndRightValues (double iLeftValue, double iRightValue, double & oNewLeftValue, double & oNewRightValue );


private:

};

#endif
