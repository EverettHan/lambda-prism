//======================================================================================//
// COPYRIGHT Dassault Systemes 2020/04/17
//======================================================================================//
//                CATCivilCurveEvaluator                                                //
//======================================================================================//
// Historic:
// 17/04/20 F4E : Creation
// 05/06/20 F4E : Flag destructor as virtual for inheriatance in Imp class
// 07/01/20 Q48 : Move data to impl class (CATCivilCurveEvaluatorImp)
//======================================================================================//

#ifndef CATCivilCurveEvaluator_H
#define CATCivilCurveEvaluator_H

// GMModelInterfaces
#include "CATGMModelInterfaces.h"

// Special API
#include "CATSysErrorDef.h"

// System
#include "CATBoolean.h"


class CAT2DCurveEvaluator;
class CATCivilCurveData;

class CATCGMOutput;

class CATApproxCivilCurve;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATSurface;
class CATCivilCurveEvaluatorImp;

// use CATCreateCivilCurveEvaluator 

class ExportedByCATGMModelInterfaces CATCivilCurveEvaluator
{
  friend class CATCivilCurveEvaluatorStream_GeoAdvCurves;

protected:

  CATCivilCurveEvaluator();

public:

  virtual ~CATCivilCurveEvaluator();

  virtual /*const*/ CAT2DCurveEvaluator * GetEvaluator() const = 0;
  virtual /*const*/ CATCivilCurveData   * GetCivilData() const = 0;

  virtual void SetEvaluatorMemoryToBeManaged(const CATBoolean iIsToManage = TRUE) = 0;
};

#endif


