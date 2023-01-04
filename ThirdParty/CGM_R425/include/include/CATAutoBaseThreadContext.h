//===================================================================
// COPYRIGHT Dassault Systemes 2003
//===================================================================
//
// 		
//===================================================================
//  Jul 2006  Creation: JHG
//==========================================================================================================


#ifndef CATAutoBaseThreadContext_H
#define CATAutoBaseThreadContext_H


#include "CATBoolean.h"
#include "CATCGMNewArray.h"
#include "PersistentCell.h"
#include "CATMathInline.h"

class CATGeoFactory;

class ExportedByPersistentCell CATAutoBaseThreadContext
{

public:
  CATCGMNewClassArrayDeclare;      // Pool allocation

  CATAutoBaseThreadContext(CATGeoFactory &iFactory,
    int iThreadId);

  virtual ~CATAutoBaseThreadContext();
  
  INLINE CATAutoBaseThreadContext &Deref() { return *this; }
  INLINE const CATAutoBaseThreadContext &ConstDeref() const { return *this; }

  CATGeoFactory &GetGeoFactory() const { return _Factory; }
  CATGeoFactory *GetFactory() const { return &_Factory; }
  CATGeoFactory &Factory() const { return _Factory; }
  int GetThreadId() const { return _ThreadId; }

private:

  /** ~ stricly forbiden call ~ **/
  CATAutoBaseThreadContext (const CATAutoBaseThreadContext & iOther);
  CATAutoBaseThreadContext & operator = (const CATAutoBaseThreadContext & iOther);

  CATGeoFactory &_Factory;
  int _ThreadId;
};

#endif
