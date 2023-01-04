#ifndef CATXBooleanTrue_H
#define CATXBooleanTrue_H
//===================================================================
// COPYRIGHT Dassault Systemes 2004
//===================================================================
//
// CATAutoFilletCATAutoFilletBuildStatus.h
// 		
//===================================================================
//  Feb 2004  Creation: JHG
//===================================================================

#include "PersistentCell.h"
#include "CATTopRibObject.h"
#include "CATXBoolean.h"
#include "CATCGMNewArray.h"


class ExportedByPersistentCell CATXBooleanTrue : public CATXBoolean
{
public:
  
  CATCGMNewClassArrayDeclare;      // Pool allocation
  INLINE CATXBooleanTrue();

  INLINE void SetFalse() { 
    SetValue(FALSE); }
protected:

private:
};

INLINE CATXBooleanTrue::CATXBooleanTrue():CATXBoolean(TRUE)
{
}

#endif
