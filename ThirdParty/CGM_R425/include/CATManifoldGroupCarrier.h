#ifndef CATManifoldGroupCarrier_H
#define CATManifoldGroupCarrier_H

#include "CATDeclarativeManifoldAgent.h"
#include "PersistentCell.h"
#include "CATCGMNewArray.h"
#include "ListPOfCATBody.h"
#include "CATCollec.h"
#include "ListVOfLong.h"

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


class ExportedByPersistentCell CATManifoldGroupCarrier : public CATDeclarativeManifoldAgent
{
public:
  CATCGMDeclareManifoldAgent(CATManifoldGroupCarrier, CATDeclarativeManifoldAgent);

	// Constructor
  CATManifoldGroupCarrier();
	
  // Destructor
	virtual ~CATManifoldGroupCarrier();

  virtual HRESULT CreateImageManifolds();
  virtual int GetPriority();
  virtual CATBoolean IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold();
  virtual CATDeclarativeManifoldAgent* Clone();

private:
  //void PropagateDeclarativeManifoldsToCarry(CATLISTP(CATManifoldGroup) &ioManifoldGroupsToCarry, 
  //  CATLISTP(CATDeclarativeManifold) &ioImageDeclarativeManifolds);
  void CreateImageManifoldGroupsFromDeclarativeManifoldImage(CATLISTP(CATManifoldGroup) &iParentManifoldGroups,
    CATLISTP(CATDeclarativeManifold) &iImageDeclarativeManifolds, CATListOfShort* iTypes);


};

#endif
