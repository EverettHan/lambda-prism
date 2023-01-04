/*
VB7 - W10 2017
*/
#ifndef CATGMLiveInputDataButtonManager_h
#define CATGMLiveInputDataButtonManager_h


#include "PersistentCell.h"
#include "CATCGMVirtual.h"
#include "ListPOfCATCellManifold.h"
#include "CATGMLiveInputDataManager.h"
#include "CATMathLine.h"
#include "CATButtonManifold.h"

class CATCellManifoldsManager;
class CATPersistentCellInfra;
class CATButtonManifold;
class CATlsoAgentInputDataCarrier;
class CATPersistentExtTopOperator;
class CATMathTransformation;
class CATCellManifold;
class CATGeoFactory;
class CATCGMJournalList;
class CATDeclarativeManifoldAgent;
class CATLiveBody;
class CATDeclarativeManifold;
class CATMathPlane;
class CATMathPoint;

// @nocgmitf (this class doesn't need a CATIPGM interface)
class ExportedByPersistentCell CATGMLiveInputDataButtonManager : public CATGMLiveInputDataManager
{
public:

  //constructors
  CATGMLiveInputDataButtonManager();
  CATGMLiveInputDataButtonManager(CATGMLiveInputDataManager * iInputDataManager);
  CATGMLiveInputDataButtonManager(CATCellManifoldsManager * iManifoldsManager, CATButtonManifold * iButtonManifold, ListPOfCATCellManifold & iResultCMList);

  //destructors
  virtual ~CATGMLiveInputDataButtonManager();

  CATBoolean HasEditingData();

  void GetNewSphereData(CATMathPoint & oSphereCenter, double & oSphereRadius);
  void GetNewEdgeData(CATMathPoint & oEdgeCenter, double & oEdgeRadius, CATMathPlane & oEdgePlane);
  CATGMLiveShapeButtonSide GetNewButtonSide();

  virtual CATGMLiveInputDataButtonManager * GetAsInputDataButtonManager();

private:

  void GetSphereDataFromParameter(CATMathPoint & oSphereCenter, double & oSphereRadius);
  CATButtonManifold * GetInputButtonManifold();
};

#endif
