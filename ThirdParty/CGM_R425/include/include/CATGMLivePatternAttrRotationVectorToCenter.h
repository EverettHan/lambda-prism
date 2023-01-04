#ifndef  CATGMLivePatternAttrRotationVectorToCenter_H
#define  CATGMLivePatternAttrRotationVectorToCenter_H
//===================================================================
// COPYRIGHT Dassault Systemes 2010
//===================================================================
//
//  CATGMLivePatternAttrRotationVectorToCenter.h
// 		
//===================================================================
//  July 2010  Creation: ZUS
//===================================================================

#include "CATCGMAttribute.h"
#include "CATMathVector.h"


class CATGMLivePatternAttrRotationVectorToCenter : public CATCGMAttribute
{
public:

  CATCGMDeclareAttribute(CATGMLivePatternAttrRotationVectorToCenter, CATCGMAttribute);

  CATGMLivePatternAttrRotationVectorToCenter();
  CATGMLivePatternAttrRotationVectorToCenter(CATMathVector *iTransfoVector);
  virtual ~CATGMLivePatternAttrRotationVectorToCenter();


  CATMathVector GetRotationVectorToCenter();
  void SetRotationVectorToCenter(CATMathVector *iTransfoVector);

private:

  CATMathVector _TransfoVector;

};

#endif 

