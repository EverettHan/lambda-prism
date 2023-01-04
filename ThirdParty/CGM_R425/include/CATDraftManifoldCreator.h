#ifndef CATDraftManifoldCreator_H
#define CATDraftManifoldCreator_H

#include "PersistentCell.h"
#include "CATDraftManifoldCreatorBase.h"
#include "CATCGMNewArray.h"
#include "ListPOfCATBody.h"
#include "CATDraftManifold.h"

class CATCellFollower;
class CATBody;
class CATSoftwareConfiguration;
class CATGeoFactory;
class CATCGMJournalList;


class ExportedByPersistentCell CATDraftManifoldCreator : public CATDraftManifoldCreatorBase 
{
public:
  CATCGMDeclareManifoldAgent(CATDraftManifoldCreator, CATDraftManifoldCreatorBase)

	// Constructor
  CATDraftManifoldCreator(CATLiveTypeDraft iDraftType, CATAngle iAngle, const CATMathDirection& iPullingDir);
  CATDraftManifoldCreator();
	
  // Destructor
  virtual ~CATDraftManifoldCreator();

  virtual CATBoolean GetAdmissibleCells(CATLISTP(CATCell) &ioAdmissibleCells);

  virtual HRESULT CreateImageManifolds();

  virtual int GetPriority();
  virtual CATBoolean IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold();
  virtual CATDeclarativeManifoldAgent* Clone();

  virtual void Stream(CATCGMStream& Str) const;  
  virtual void UnStream (CATCGMStream& Str, CATGeoFactory* iFactory, CATSoftwareConfiguration * ipConfig); 
  virtual void Dump(CATCGMOutput &os);

protected:

private :
  CATMathDirection _PullingDir;
  CATLiveTypeDraft _DraftType;
  CATAngle _Angle;

};

#endif
