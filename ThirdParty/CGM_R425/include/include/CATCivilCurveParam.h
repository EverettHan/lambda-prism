//======================================================================================//
// COPYRIGHT Dassault Systemes 09/2022
//======================================================================================//
//                CATCivilCurveParam                                                    //
//======================================================================================//
// Historic:
// 15/09/22 Q48 : Creation
//======================================================================================//

#ifndef CATCivilCurveParam_H
#define CATCivilCurveParam_H

// ExportedBy
#include "CATGMModelInterfaces.h"

// C++11
//#include "CATGeoOpVirtual.h"
#include "CATMathVirtual.h"

// System
#include "CATBoolean.h"

// Civil
#include "CATCivilCurveDef.h"

class ExportedByCATGMModelInterfaces CATCivilCurveParam
{
public:

   CATCivilCurveParam();

   CATCivilCurveParam(const CATCivilCurveParam & iToCopy);

   CATCivilCurveParam(const CATCivilCurveDef::ParamType iType);

   CATCivilCurveParam(const CATCivilCurveDef::ParamType iType,
                      const double                      iValue);

public:

   virtual ~CATCivilCurveParam();

public:

   virtual void SetValue(const double iValue) CATMathFinal;

   virtual CATBoolean                  IsValueSet() const CATMathFinal;
   virtual double                      GetValue() const CATMathFinal;
   virtual CATCivilCurveDef::ParamType GetType () const CATMathFinal;

protected:
   
   const CATCivilCurveDef::ParamType _Type;

   double     _Value;
   CATBoolean _ValueSet;
};
#endif // CATCivilCurveParam_H
