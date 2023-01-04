#ifndef  CATGMLivePatternAttrSecondaryTransfo_H
#define  CATGMLivePatternAttrSecondaryTransfo_H
//===================================================================
// COPYRIGHT Dassault Systemes 2010
//===================================================================
//
//  CATGMLivePatternAttrSecondaryTransfo.h
// 		
//===================================================================
//  July 2010  Creation: ZUS
//===================================================================

#include "PersistentCell.h"

#include "CATCGMAttribute.h"
#include "CATPatternSecondaryTransfoStructure.h"


class  ExportedByPersistentCell CATGMLivePatternAttrSecondaryTransformation : public CATCGMAttribute
{
public:

  CATCGMDeclareAttribute(CATGMLivePatternAttrSecondaryTransformation, CATCGMAttribute);

  CATGMLivePatternAttrSecondaryTransformation();
  CATGMLivePatternAttrSecondaryTransformation(CATPatternSecondaryTransfoStructure *iSecondaryTransfo);
  virtual ~CATGMLivePatternAttrSecondaryTransformation();

  CATPatternSecondaryTransfoStructure GetTargetSecondaryTransfo();
  void SetTargetSecondaryTransfo(CATPatternSecondaryTransfoStructure *iSecondaryTransfo);


private:

  CATPatternSecondaryTransfoStructure _SecondaryTransfo;

};

#endif 

