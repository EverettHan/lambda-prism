#ifndef  CATGMLivePatternAttrReference_H
#define  CATGMLivePatternAttrReference_H
//===================================================================
// COPYRIGHT Dassault Systemes 2010
//===================================================================
//
//  CATGMLivePatternAttrReference.h
// 		
//===================================================================
//  July 2010  Creation: ZUS
//===================================================================

#include "PersistentCell.h"

#include "CATCGMAttribute.h"
#include "CATLiveBody.h"


class  ExportedByPersistentCell CATGMLivePatternAttrReference : public CATCGMAttribute
{
public:

  CATCGMDeclareAttribute(CATGMLivePatternAttrReference, CATCGMAttribute);

  CATGMLivePatternAttrReference();
  CATGMLivePatternAttrReference(CATLiveBody *iReference);
  virtual ~CATGMLivePatternAttrReference();


  CATLiveBody *GetTargetReference();
  void SetTargetReference(CATLiveBody *iReference);

private:

  CATLiveBody *_Reference;

};

#endif 

