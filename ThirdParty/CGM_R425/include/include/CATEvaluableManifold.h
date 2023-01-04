#ifndef CATEvaluableManifold_h
#define CATEvaluableManifold_h

// COPYRIGHT DASSAULT SYSTEMES  2007

#include "CATDeclarativeManifold.h"

class CATBody;
class CATSoftwareConfiguration;

#include "CATGMModelInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMModelInterfaces IID IID_CATEvaluableManifold ;
#else
extern "C" const IID IID_CATEvaluableManifold ;
#endif

class ExportedByCATGMModelInterfaces CATEvaluableManifold : public CATDeclarativeManifold
{
  CATDeclareInterface;

public:

  virtual CATBody* UpdateRep() const = 0;
  virtual CATBoolean IsConfused(CATDeclarativeManifold   * iOtherDeclarativeManifold, 
                                double                     iLengthTol,
                                double                     iAngleTol,
                                CATBoolean               & ioPertinent,
                                CATSoftwareConfiguration * iConfig) = 0;
};
  
CATDeclareHandler(CATEvaluableManifold,CATDeclarativeManifold);

#endif
