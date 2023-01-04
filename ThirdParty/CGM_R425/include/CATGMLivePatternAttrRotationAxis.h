#ifndef  CATGMLivePatternAttrRotationAxis_H
#define  CATGMLivePatternAttrRotationAxis_H
//===================================================================
// COPYRIGHT Dassault Systemes 2010
//===================================================================
//
//  CATGMLivePatternAttrRotationAxis.h
// 		
//===================================================================
//  July 2010  Creation: ZUS
//===================================================================

#include "PersistentCell.h"

#include "CATCGMAttribute.h"
#include "CATMathLine.h"


class  ExportedByPersistentCell CATGMLivePatternAttrRotationAxis : public CATCGMAttribute
{
public:

  CATCGMDeclareAttribute(CATGMLivePatternAttrRotationAxis, CATCGMAttribute);

  CATGMLivePatternAttrRotationAxis();
  CATGMLivePatternAttrRotationAxis(CATMathLine *iRotationAxis);
  virtual ~CATGMLivePatternAttrRotationAxis();


  CATMathLine GetTargetRotationAxis();
  void SetTargetRotationAxis(CATMathLine *iRotationAxis);

private:

  CATMathLine _RotationAxis;

};

#endif // CATGMLivePatternAttrRotationAxis_H 

