#ifndef CATCellManifoldPatternGroupCarrierData_H
#define CATCellManifoldPatternGroupCarrierData_H

#include "CATDeclarativeManifoldAgent.h"
#include "CATCGMNewArray.h"
#include "ListPOfCATBody.h"
#include "CATCollec.h"
#include "ListVOfLong.h"
#include "CATCellHashTable.h"

class CATCellManifoldsManager;
class CATBody;
class CATCellManifold;
class CATLISTP(CATCellManifold);
class CATDeclarativeManifold;
class CATLISTP(CATDeclarativeManifold);
class CATCell;
class CATLISTP(CATCell);
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATCellManifoldGroupOperator;
class CATCGMHashTableWithAssoc;


class CATCellManifoldPatternGroupCarrierData : public CATDeclarativeManifoldAgent
{
public:
  CATCGMDeclareManifoldAgent(CATCellManifoldPatternGroupCarrierData, CATDeclarativeManifoldAgent);

	// Constructor
  CATCellManifoldPatternGroupCarrierData();
	
  // Destructor
	virtual ~CATCellManifoldPatternGroupCarrierData();

  virtual HRESULT CreateImageManifolds();
  virtual int GetPriority();
  virtual CATBoolean IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold();
  virtual CATDeclarativeManifoldAgent* Clone();
	
private :

virtual CATCGMJournalList* GetCellManifoldGroupJournal();
virtual HRESULT  CreateImage(CATCellManifoldGroup         * iRefGroup, 
                     int                            iInstance, 
                     CATCGMJournalList            * iCMJournal, 
                     CATCellManifoldGroupOperator * iGroupOperator, 
                     CATCGMHashTableWithAssoc     * ioRelation_RefGroup_CreatedGroup, 
                     CATCellManifoldGroup        *& oCreatedGroup);
virtual HRESULT ComputeCMInCollsion(CATCGMJournalList * iCMJournal);

protected : 

  CATCGMJournalList* _CellManifoldGroupJournal;
  CATCellHashTable *_BorderEdgesHT;
  ListPOfCATCellManifold _CollisionCM;
  ListPOfCATCellManifoldGroup _CollisionCMGroup;


};

#endif
