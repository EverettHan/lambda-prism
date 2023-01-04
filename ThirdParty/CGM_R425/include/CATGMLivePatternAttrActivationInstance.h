#ifndef  CATGMLivePatternAttrActivationInstance_H
#define  CATGMLivePatternAttrActivationInstance_H
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
#include "CATPatternActivationInstanceStructure.h"


class  ExportedByPersistentCell CATGMLivePatternAttrActivationInstance : public CATCGMAttribute
{
public:

  CATCGMDeclareAttribute(CATGMLivePatternAttrActivationInstance, CATCGMAttribute);

  CATGMLivePatternAttrActivationInstance();
  CATGMLivePatternAttrActivationInstance(CATPatternActivationInstanceStructure *iActivationInstance);
  virtual ~CATGMLivePatternAttrActivationInstance();

  CATPatternActivationInstanceStructure GetTargetActivationInstance();
  void SetTargetActivationInstance(CATPatternActivationInstanceStructure *iActivationInstance);


private:

  CATPatternActivationInstanceStructure _ActivationInstance;

};

#endif 

