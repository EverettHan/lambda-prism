#ifndef __CATContextForFastRunInternal_H__
#define __CATContextForFastRunInternal_H__
//===========================================================================================================
// Internal context objects that belong to an overall context object that has more than one result. 
// We can't have internal context objects inside this class.
// 13/11/2014  G5S Creation.	
// 17/12/2014  G5S Rename CreateInternalContexts to SetNboldResults.																																						  G5S
//===========================================================================================================
#include "CATContextForFastRunExt.h"

class CATContextForFastRunInternal: public CATContextForFastRunExt
{
public:
	CATContextForFastRunInternal(CATResultIDForFastRun iResultID, CATContextForFastRunExt * iOwningContext);
	virtual ~CATContextForFastRunInternal();

  virtual CATString GetType();

	 CATCGMNewClassArrayDeclare;

	// Overload GetInternalContextForFastRun(..) so that we throw if iResultID != 1 because we should never
	// ask an internal context for its internal context.
  virtual CATContextForFastRunExt * GetInternalContextForFastRunExt(CATResultIDForFastRun iResultID);
	virtual CATContextForFastRunExt * GetInternalContextForFastRunExt(int i, CATResultIDForFastRun &oResultID);

	// Overload SetNbOldResults() so that we throw, because we should never create internal contexts inside an
	// internal context.
	virtual void SetNbOldResults(int iNbInternalContexts);

	// Get the result ID.
  INLINE virtual CATResultIDForFastRun GetResultID() {return _ResultID;};

	// Get owning context.
	INLINE virtual CATContextForFastRunExt * GetOwningContext() {return _OwningContext;}

private:
	CATResultIDForFastRun _ResultID;
	CATContextForFastRunExt * _OwningContext;
};

#endif // __CATContextForFastRunInternal_H__
