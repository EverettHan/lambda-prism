#ifndef  CATGMLivePatternAttrOriginPoint_H
#define  CATGMLivePatternAttrOriginPoint_H
//===================================================================
// COPYRIGHT Dassault Systemes 2010
//===================================================================
//
//  CATGMLivePatternAttr.h
// 		
//===================================================================
//  July 2010  Creation: ZUS
//===================================================================

#include "PersistentCell.h"

#include "CATCGMAttribute.h"
#include "CATMathPoint.h"


class  ExportedByPersistentCell CATGMLivePatternAttrOriginPoint : public CATCGMAttribute
{
public:

  CATCGMDeclareAttribute(CATGMLivePatternAttrOriginPoint, CATCGMAttribute);

  CATGMLivePatternAttrOriginPoint();
  CATGMLivePatternAttrOriginPoint(CATMathPoint *iOriginPoint);
  virtual ~CATGMLivePatternAttrOriginPoint();


  CATMathPoint GetOriginPoint();
  void SetOriginPoint(CATMathPoint *iOriginPoint);

private:

  CATMathPoint _OriginPoint;

};

#endif 

