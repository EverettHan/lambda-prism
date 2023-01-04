#ifndef CATCanonicAdvancedRecognizer_H
#define CATCanonicAdvancedRecognizer_H

#include "CATCanonicRecognizer.h"
#include "CATListOfDouble.h"
#include "CATMathPlane.h"
#include "CATMathAxis.h"
#include "CATCollec.h"
#include "CATLISTP_CATMathPlane.h"
#include "CATLISTP_CATMathAxis.h"
#include "CATMathInline.h"

template <class CATCellManifold> class CATLSOHashTable;

class ExportedByPersistentCell CATCanonicAdvancedRecognizer : public CATCanonicRecognizer
{
public:

  CATCGMDeclareManifoldAgent(CATCanonicAdvancedRecognizer, CATCanonicAdvancedRecognizer)
	
	// Constructor
  CATCanonicAdvancedRecognizer();
	
  // Destructor
	virtual ~CATCanonicAdvancedRecognizer();
  
  INLINE virtual CATDeclarativeManifoldAgent* Clone();

protected:
  virtual CATDeclarativeManifold * CreateDeclaratifManifold(CATCellManifold* iManifold);
  virtual CATDeclarativeManifold * CreateDeclaratifManifold(CATCellManifold* iCellManifold, CATLSOHashTable<CATCellManifold> &ioAdmissibleCMHashTable);
  virtual CATDeclarativeManifold * CreateDeclaratifManifold(CATCellManifold* iCellManifold, CATLISTP(CATCellManifold) &ioAdmissibleCellManifolds);

};

INLINE CATDeclarativeManifoldAgent* CATCanonicAdvancedRecognizer::Clone()
{
  return new CATCanonicAdvancedRecognizer();
}

#endif

