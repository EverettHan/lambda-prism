#ifndef CATXBooleanFalse_H
#define CATXBooleanFalse_H
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


class ExportedByPersistentCell CATXBooleanFalse : public CATXBoolean
{
public:
  
  CATCGMNewClassArrayDeclare;      // Pool allocation
  INLINE CATXBooleanFalse();

  INLINE void SetTrue() { SetValue(TRUE); }
protected:

private:
};

INLINE CATXBooleanFalse::CATXBooleanFalse():CATXBoolean(FALSE)
{
}

#endif
