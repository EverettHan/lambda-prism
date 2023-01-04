#ifndef CATGMLivePatternUtilitiesLight_H
#define CATGMLivePatternUtilitiesLight_H

#include "CATCGMNewArray.h"

#include "CATTopDefine.h"

#include "CATGMModelInterfaces.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"


class CATSoftwareConfiguration;
class CATCellManifoldGroup;
class CATCellManifold;
class CATLiveBody;
class CATMathTransformation;

class ExportedByCATGMModelInterfaces CATGMLivePatternUtilitiesLight
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation

  CATGMLivePatternUtilitiesLight(CATSoftwareConfiguration * iConfig);
  virtual ~CATGMLivePatternUtilitiesLight();


  // Renvoie le networkgroup associe a une CM
  static HRESULT GetNetworkGroup(CATLiveBody * iLiveBody, CATCellManifold *iCM, CATCellManifoldGroup *& oNetworkGroup);

private:
  CATSoftwareConfiguration * _SoftwareConfiguration;
};

#endif 

