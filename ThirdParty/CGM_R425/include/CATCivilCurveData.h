//======================================================================================//
// COPYRIGHT Dassault Systemes 2020/04/17
//======================================================================================//
//                CATCivilCurveData                                                     //
//======================================================================================//
// Historic:
// 17/04/20 F4E : Creation
// 05/06/20 F4E : Add missing includes + indent
// 08/09/20 JSX : Remove all data of the interface
//======================================================================================//

#ifndef CATCivilCurveData_H
#define CATCivilCurveData_H

// Mathematics
#include "CATMathConstant.h"


// GMModelInterfaces
#include "CATCivilCurveDef.h"
#include "CATGMModelInterfaces.h"

// System
#include "CATBoolean.h"


class CATSoftwareConfiguration;
class CATTolerance;
class CATCGMOutput;
class CATCGMStream;
class CATGeoODTScaleManager;
class CAT2DCurveEvaluator;

class ExportedByCATGMModelInterfaces CATCivilCurveData
{
protected:

  CATCivilCurveData();

public:

  virtual ~CATCivilCurveData();

  virtual CATBoolean     IsAKindOf(const CATMathClassId iClassId) const;
  virtual CATMathClassId IsA()                                    const;

  //virtual void               Run() = 0;        // to compute class internal data when needed
  virtual CATCivilCurveType  GetCivilCurveType() const = 0;
};
#endif


