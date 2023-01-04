//===================================================================
// COPYRIGHT Dassault Systemes 2003
//===================================================================
//
// 		
//===================================================================
//  Jul 2006  Creation: JHG
//==========================================================================================================


#ifndef CATAutoBaseLastCall_H
#define CATAutoBaseLastCall_H

//#define AUTOFILLET_LOCAL_UPDATE

#ifdef AUTOFILLET_LOCAL_UPDATE

#include "CATBoolean.h"
#include "CATCGMNewArray.h"
#include "PersistentCell.h"
#include "CATMathInline.h"

class CATGeoFactory;
class CATSoftwareConfiguration;
class CATBody;
class CATCGMJournalList;

class ExportedByPersistentCell CATAutoBaseLastCall
{

public:
  CATCGMNewClassArrayDeclare;      // Pool allocation

  CATAutoBaseLastCall(CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig);

  virtual ~CATAutoBaseLastCall();
  
  void SetLastCallData(CATBody *iInput,
    CATBody *iResult, CATCGMJournalList *iJournal);

  CATBoolean HasSameFactory(CATGeoFactory *iFactory) { return iFactory == _Factory; };

  INLINE CATBody *ReadInputBody() { return _Input; };
  INLINE CATBody *ReadResultBody() { return _Result; };
  INLINE CATCGMJournalList *ReadOperationJournal() { return _Journal; };

private:
  CATBody *_Input;
  CATBody *_Result;
  CATCGMJournalList *_Journal;

  CATGeoFactory *_Factory;
  CATSoftwareConfiguration *_Config;
};
#endif

#endif
