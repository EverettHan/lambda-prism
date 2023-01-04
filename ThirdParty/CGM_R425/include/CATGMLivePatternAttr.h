#ifndef  CATGMLivePatternAttr_H
#define  CATGMLivePatternAttr_H
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


class  ExportedByPersistentCell CATGMLivePatternAttr : public CATCGMAttribute
{
public:

  CATCGMDeclareAttribute(CATGMLivePatternAttr, CATCGMAttribute);

  CATGMLivePatternAttr();
  CATGMLivePatternAttr(short iNumberOfInstances);
  virtual ~CATGMLivePatternAttr();

  short GetTargetNumberOfInstances();
  void SetTargetNumberOfInstances(short iNumberOfInstances);


private:

  short _NumberOfInstances;

};

#endif 

