#ifndef CATOwnedByPersistentCellFactory_H
#define CATOwnedByPersistentCellFactory_H
//=============================================================================
// COPYRIGHT Dassault Systemes 2003, 2004
//=============================================================================
//
// CATOwnedByPersistentCellFactory.h
// 		
//=============================================================================
//  Oct 2003  Creation: JHG
//=============================================================================

#include "PersistentCell.h"
#include "CATTopRibTraceObject.h"
#include "CATThrowForNullPointer.h"
#include "CATCGMNewArray.h"
#include "CATDerefMacros.h"
#include "CATMathInline.h"


class CATPersistentCellFactory;

class ExportedByPersistentCell CATOwnedByPersistentCellFactory: public CATTopRibTraceObject
{
public:
  CATCGMNewClassArrayDeclare; // Pool allocation

public:
  CATOwnedByPersistentCellFactory(CATPersistentCellFactory &iFactory);
  virtual ~CATOwnedByPersistentCellFactory();

  INLINE CATPersistentCellFactory *GetPersistentCellFactory() const;
  INLINE CATPersistentCellFactory &GetPersistentCellFactoryRef() const;

  DEFINE_ADVOP_CLASS(CATOwnedByPersistentCellFactory)

private:
  CATPersistentCellFactory &_Factory;
};

INLINE
CATPersistentCellFactory *CATOwnedByPersistentCellFactory::GetPersistentCellFactory() const
{
  return &_Factory;
}

INLINE
CATPersistentCellFactory &CATOwnedByPersistentCellFactory::GetPersistentCellFactoryRef() const
{
  return _Factory;
}

#endif // !CATOwnedByPersistentCellFactory_H
