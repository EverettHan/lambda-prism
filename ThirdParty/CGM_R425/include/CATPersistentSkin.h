#ifndef CATPersistentSkin_H
#define CATPersistentSkin_H
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
#include "CATPersistentBody.h"
#include "CATBoolean.h"
#include "CATCGMNewArray.h"
#include "CATMathInline.h"

class CATShell;

class ExportedByPersistentCell CATPersistentSkin : public CATPersistentBody
{
  friend class CATPersistentCellFactory;
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation
  DEFINE_ADVOP_CLASS_NAME("CATPersistentSkin")

  CATShell *GetShell(const CATAutoBaseThreadContext &iThreadContext);

  virtual void Clear();

  INLINE virtual CATPersistentSkin *GetAsPersistentSkin();

protected:
// Specifie le CATBody correspondant a ce CATPersistentSkin. Attention, cette methode fait un throw si
// il contient autre chose qu'un unique CATShell
  virtual void SetCATBody(const CATAutoBaseThreadContext &iThreadContext, CATBody *iBody, CATBoolean iFrozenBody);

  CATPersistentSkin(CATPersistentCellFactory &iPersistentCellFactory);
  virtual ~CATPersistentSkin();


private:
};

INLINE CATPersistentSkin *CATPersistentSkin::GetAsPersistentSkin()
{
  return this;
}

#endif
