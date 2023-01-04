#ifndef  CATGMLivePatternAttrComplete_H
#define  CATGMLivePatternAttrComplete_H
//===================================================================
// COPYRIGHT Dassault Systemes 2010
//===================================================================
//
//  CATGMLivePatternAttrComplete.h
// 		
//===================================================================
//  July 2010  Creation: ZUS
//===================================================================

#include "PersistentCell.h"

#include "CATCGMAttribute.h"


class  ExportedByPersistentCell CATGMLivePatternAttrComplete : public CATCGMAttribute
{
public:

  CATCGMDeclareAttribute(CATGMLivePatternAttrComplete, CATCGMAttribute);

  CATGMLivePatternAttrComplete();
  CATGMLivePatternAttrComplete(CATBoolean iPatternComplete);
  virtual ~CATGMLivePatternAttrComplete();

  CATBoolean GetTargetPatternComplete();
  void SetTargetPatternComplete(CATBoolean iPatternComplete);


private:

  CATBoolean _PatternComplete;

};

#endif // CATGMLivePatternAttrComplete 

