#ifndef CATGMLiveShapeButtonRecognizerBridge_H
#define CATGMLiveShapeButtonRecognizerBridge_H

#include "CATCGMNewArray.h"
#include "PersistentCell.h"

class CATCellManifold;
class CATGMLiveShapeButtonData;
class CATGeoFactory;
class CATBody;
class CATSoftwareConfiguration;
class CATGMLiveShapeButtonRecognizerBridge;

typedef CATGMLiveShapeButtonRecognizerBridge*  (*CATGMLiveShapeButtonRecognizerBridgeCreator) (CATGeoFactory * iFactory, CATBody * iBody, CATSoftwareConfiguration * iConfig);

class ExportedByPersistentCell CATGMLiveShapeButtonRecognizerBridge
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation

  virtual ~CATGMLiveShapeButtonRecognizerBridge() {};

  virtual void Run() = 0;

  virtual void SetInputCellManifold(CATCellManifold * iCM) = 0;

  virtual void GetResultButtonData(CATGMLiveShapeButtonData *& oButtonData) = 0;

};

ExportedByPersistentCell CATGMLiveShapeButtonRecognizerBridge * CATCreateGMLiveShapeButtonRecognizerBridge(CATGeoFactory * iFactory, CATBody * iBody, CATSoftwareConfiguration * iConfig);

#endif 

