//===================================================================
// COPYRIGHT Dassault Systemes 2014
//===================================================================
// CATCDMType.h
//===================================================================
//
//===================================================================
#ifndef CATCDMType_H
#define CATCDMType_H

#include "CATCDMBaseInterfaces.h"
#include "CATBaseUnknown.h"

class CATUnicodeString;

class ExportedByCATCDMBaseInterfaces CATCDMType
{
public:

  enum NumericalType{
    ntNone=0
    ,ntBoolean
    ,ntInteger
    ,ntDouble
  };

  enum SemanticType {
    stNone=0,
    stEnum,
    stLength,
    stAngle
  };

  static CATCDMType _Boolean;
  static CATCDMType _Integer;
  static CATCDMType _Double;
  static CATCDMType _IntegerEnum;
  static CATCDMType _DoubleEnum;
  static CATCDMType _DoubleLength;
  static CATCDMType _DoubleAngle;

  inline NumericalType GetNumericalType();
  inline SemanticType  GetSemanticType();

  // Convert ParamType into Knowledge magnitude string
  // when input type has no magnitude (ex basic type : Integer, Real,  ) it returns an empty string
  // in other case it returns the corresponding KWE string
  // ptLength => LENGTH
  // ptAngle  => ANGLE
  // ...
  static HRESULT ConvertParamTypeToKnowledgeMagnitude(CATCDMType* iType, CATUnicodeString& ioString);

private :
  NumericalType _MyNumericalType;
  SemanticType  _MySemanticType;

  CATCDMType(NumericalType iNt,SemanticType iSt);
  CATCDMType(CATCDMType&);
  CATCDMType& operator=(CATCDMType&);
};

CATCDMType::NumericalType CATCDMType::GetNumericalType()
{
  return _MyNumericalType;
}
CATCDMType::SemanticType  CATCDMType::GetSemanticType()
{
  return _MySemanticType;
}


#endif
