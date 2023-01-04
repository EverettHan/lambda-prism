#ifndef CATGMLocalAdvancedStampRecognizerBridge_H
#define CATGMLocalAdvancedStampRecognizerBridge_H

#include "CATCGMNewArray.h"
#include "PersistentCell.h"
#include "ListPOfCATCellManifold.h"

class CATGMLocalAdvancedStampRecognizerBridge;
class CATGeoFactory;
class CATBody;
class CATSoftwareConfiguration;
class CATCellManifold;
class CATGMAdvancedStampLiveData;

typedef CATGMLocalAdvancedStampRecognizerBridge*  (*CATGMLocalAdvancedStampRecognizerBridgeCreator) (CATGeoFactory & iFactory, CATBody & iBody, CATSoftwareConfiguration * iConfig, CATCellManifold * iCellManifold);

class ExportedByPersistentCell CATGMLocalAdvancedStampRecognizerBridge
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation

  virtual ~CATGMLocalAdvancedStampRecognizerBridge() {};

  virtual void Run() = 0;

  virtual void SetInputCellManifold(CATCellManifold * iCellManifold) = 0;

  virtual CATGMAdvancedStampLiveData * GetResultAdvancedStampLiveData() = 0;

  virtual void GetAnalyzedCellManifoldList(ListPOfCATCellManifold & oAnalyzedCellManifoldList) = 0;

};

ExportedByPersistentCell CATGMLocalAdvancedStampRecognizerBridge * CATCreateGMLocalAdvancedStampRecognizerBridge(CATGeoFactory & iFactory, CATBody & iBody, CATSoftwareConfiguration * iConfig, CATCellManifold * iCellManifold);

#endif 

