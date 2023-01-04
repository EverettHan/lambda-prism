#ifndef  CATGMLivePatternAttrLinearTransfo_H
#define  CATGMLivePatternAttrLinearTransfo_H
//===================================================================
// COPYRIGHT Dassault Systemes 2010
//===================================================================
//
//  CATGMLivePatternAttr.h
// 		
//===================================================================
//  July 2010  Creation: ZUS
//===================================================================
#include "CATCGMAttribute.h"
#include "CATMathVector.h"

class CATGMLivePatternAttrLinearTransfo : public CATCGMAttribute
{
public:

  CATCGMDeclareAttribute(CATGMLivePatternAttrLinearTransfo, CATCGMAttribute);

  CATGMLivePatternAttrLinearTransfo();
  CATGMLivePatternAttrLinearTransfo(CATMathVector *iTransfoVector);
  virtual ~CATGMLivePatternAttrLinearTransfo();

  CATMathVector GetTransfoVector();
  void SetTransfoVector(CATMathVector *iTransfoVector);

private:

  CATMathVector _TransfoVector;

};

#endif 

