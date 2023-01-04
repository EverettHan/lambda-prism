#ifndef  CATGMLivePatternAttrRotationAngle_H
#define  CATGMLivePatternAttrRotationAngle_H
//===================================================================
// COPYRIGHT Dassault Systemes 2010
//===================================================================
//
//  CATGMLivePatternAttrRotationAngle.h
// 		
//===================================================================
//  July 2010  Creation: ZUS
//===================================================================

#include "PersistentCell.h"

#include "CATCGMAttribute.h"


class  ExportedByPersistentCell CATGMLivePatternAttrRotationAngle : public CATCGMAttribute
{
public:

  CATCGMDeclareAttribute(CATGMLivePatternAttrRotationAngle, CATCGMAttribute);

  CATGMLivePatternAttrRotationAngle();
  CATGMLivePatternAttrRotationAngle(double iRotationAngle);
  virtual ~CATGMLivePatternAttrRotationAngle();


  double GetTargetRotationAngle();
  void SetTargetRotationAngle(double iRotationAngle);

private:

  double _RotationAngle;

};

#endif 

