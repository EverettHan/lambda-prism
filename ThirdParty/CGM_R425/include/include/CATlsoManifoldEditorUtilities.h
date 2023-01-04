#ifndef CATlsoManifoldEditorUtilities_H
#define CATlsoManifoldEditorUtilities_H

// ++++ Includes ++++
#include "PersistentCell.h"
#include "CATSysBoolean.h"
#include "CATDataType.h"
#include "IUnknown.h"
#include "ListPOfCATCell.h"
#include "ListPOfCATPersistentCells.h"
#include "CATListOfCATGeometries.h"

class CATManifoldParameter;
class CATCGMStream;
class CATGeoFactory;
class CATLiveBody;


//==========================================================================================================
// CATlsoManifoldEditorUtilities
// 
// Responsable: VB7
// 
//==========================================================================================================

class ExportedByPersistentCell CATlsoManifoldEditorUtilities
{

public :

  //symmetric to CATManifoldParameter::WriteParameter
  static CATManifoldParameter * ReadParameter(CATCGMStream  & Str, CATGeoFactory* iFactory, CATLiveBody* iLiveBody);
};




#endif 

