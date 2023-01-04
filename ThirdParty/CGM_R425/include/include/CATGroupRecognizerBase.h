//Nov 2011 EYL
#ifndef CATGroupRecognizerBase_H
#define CATGroupRecognizerBase_H

#include "CATDeclarativeManifoldAgent.h"
#include "CATMathInline.h"

class CATDeclarativeManifold;

class ExportedByPersistentCell CATGroupRecognizerBase : public CATDeclarativeManifoldAgent
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation
	
	// Constructor
  CATGroupRecognizerBase();
	
  // Destructor
	virtual ~CATGroupRecognizerBase();

  virtual HRESULT CreateImageManifolds();
  INLINE virtual CATBoolean IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold();
  virtual HRESULT CreateManifoldGroup()=0;

protected:
  //virtual CATBoolean IsAllowed(CATCellManifold* iManifold) = 0;
  //virtual CATBoolean AreEquivalent(CATCellManifold* iManifold1, CATCellManifold* iManifold2) = 0;
  //virtual CATDeclarativeManifold* CreateDeclaratifManifold(CATLISTP(CATCellManifold) &iConnectedEquivalentCellManifold) = 0;

 // virtual CATDeclarativeManifold* CreateDeclaratifManifold(CATCellManifold* iManifold) = 0;

private:
  //void CreateDeclaratifManifoldsByConnectedSubset(CATLISTP(CATCellManifold) &iEquivalentCellManifold);
};

INLINE CATBoolean CATGroupRecognizerBase::IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold()
{
  return TRUE;
}
#endif

