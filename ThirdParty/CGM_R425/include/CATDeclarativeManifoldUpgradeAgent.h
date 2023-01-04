//February 2017 VB7
#ifndef CATDeclarativeManifoldUpgradeAgent_H
#define CATDeclarativeManifoldUpgradeAgent_H

#include "CATDeclarativeManifoldAgent.h"

class ExportedByPersistentCell CATDeclarativeManifoldUpgradeAgent : public CATDeclarativeManifoldAgent
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation
	
	// Constructor
  CATDeclarativeManifoldUpgradeAgent();
	
  // Destructor
	virtual ~CATDeclarativeManifoldUpgradeAgent();

  virtual HRESULT CreateImageManifolds()=0;
  virtual int GetPriority() = 0;
  virtual CATBoolean IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold() = 0;
  virtual CATDeclarativeManifoldAgent* Clone() = 0;

  //return TRUE
  virtual CATBoolean HasLicenseToKillDeclarativeManifold();

protected:

  void KillDeclarativeManifold(CATDeclarativeManifold * iDM);

};

#endif

