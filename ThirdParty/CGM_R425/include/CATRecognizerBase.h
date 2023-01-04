#ifndef CATRecognizerBase_H
#define CATRecognizerBase_H

#include "CATDeclarativeManifoldAgent.h"
#include "CATMathInline.h"

class CATDeclarativeManifold;
template <class CATCellManifold> class CATLSOHashTable;

class ExportedByPersistentCell CATRecognizerBase : public CATDeclarativeManifoldAgent
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation
	
	// Constructor
  CATRecognizerBase();
	
  // Destructor
	virtual ~CATRecognizerBase();

  virtual HRESULT CreateImageManifolds();
  INLINE virtual CATBoolean IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold();

protected:
  //virtual CATBoolean IsAllowed(CATCellManifold* iManifold) = 0;
  //virtual CATBoolean AreEquivalent(CATCellManifold* iManifold1, CATCellManifold* iManifold2) = 0;
  //virtual CATDeclarativeManifold* CreateDeclaratifManifold(CATLISTP(CATCellManifold) &iConnectedEquivalentCellManifold) = 0;

  virtual CATDeclarativeManifold * CreateDeclaratifManifold(CATCellManifold* iManifold) = 0;

  // Performance ehancement
  virtual CATDeclarativeManifold * CreateDeclaratifManifold(CATCellManifold* iCellManifold, CATLSOHashTable<CATCellManifold> &ioAdmissibleCMHashTable) = 0;
  
  // Dont use (bad perfo)
  virtual CATDeclarativeManifold * CreateDeclaratifManifold(CATCellManifold* iCellManifold, CATLISTP(CATCellManifold) &ioAdmissibleCellManifolds) = 0;

private:
  //void CreateDeclaratifManifoldsByConnectedSubset(CATLISTP(CATCellManifold) &iEquivalentCellManifold);
};

INLINE CATBoolean CATRecognizerBase::IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold()
{
  return TRUE;
}
#endif

