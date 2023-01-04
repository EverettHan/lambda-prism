#ifndef CATCanonicRecognizer_H
#define CATCanonicRecognizer_H

#include "CATRecognizerBase.h"
#include "CATMathInline.h"

template <class CATCellManifold> class CATLSOHashTable;

class ExportedByPersistentCell CATCanonicRecognizer : public CATRecognizerBase
{
public:
  CATCGMDeclareManifoldAgent(CATCanonicRecognizer, CATDeclarativeManifoldAgent);
	
	// Constructor
  CATCanonicRecognizer();
	
  // Destructor
	virtual ~CATCanonicRecognizer();

  virtual int GetPriority();
  INLINE virtual CATDeclarativeManifoldAgent* Clone();

  virtual CATCanonicRecognizer * GetAsCanonicRecognizer();

protected:
  /*
  virtual CATBoolean IsAllowed(CATCellManifold* iManifold);
  virtual CATBoolean AreEquivalent(CATCellManifold* iManifold1, CATCellManifold* iManifold2);
  virtual CATDeclarativeManifold* CreateDeclaratifManifold(CATLISTP(CATCellManifold) &iConnectedEquivalentCellManifold);
  */
  virtual CATDeclarativeManifold * CreateDeclaratifManifold(CATCellManifold* iCellManifold);

  // Performance ehancement
  virtual CATDeclarativeManifold * CreateDeclaratifManifold(CATCellManifold* iCellManifold, CATLSOHashTable<CATCellManifold> &ioAdmissibleCMHashTable);

  virtual CATDeclarativeManifold * CreateDeclaratifManifold(CATCellManifold* iCellManifold, CATLISTP(CATCellManifold) &ioAdmissibleCellManifolds);  

};

INLINE CATDeclarativeManifoldAgent* CATCanonicRecognizer::Clone()
{
  return new CATCanonicRecognizer();
}

#endif

