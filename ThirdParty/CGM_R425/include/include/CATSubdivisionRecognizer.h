#ifndef CATSubdivisionRecognizer_H
#define CATSubdivisionRecognizer_H

#include "CATRecognizerBase.h"
#include "CATListOfCATGeometries.h"
#include "CATMathInline.h"

class CATSubdivMesh;
class CATShell; 
template <class CATCellManifold> class CATLSOHashTable;

class ExportedByPersistentCell CATSubdivisionRecognizer : public CATRecognizerBase
{
public:
  CATCGMDeclareManifoldAgent(CATSubdivisionRecognizer, CATRecognizerBase);
	
	// Constructor
  CATSubdivisionRecognizer();
	
  // Destructor
	virtual ~CATSubdivisionRecognizer();

  virtual CATSubdivisionRecognizer * GetAsSubdivisionRecognizer();

  virtual int GetPriority();
  virtual CATDeclarativeManifoldAgent* Clone();

  void SetSubdivMesh(CATSubdivMesh* iSubdivMesh, CATBody * iSubdivMeshBody);

protected:
  virtual CATDeclarativeManifold * CreateDeclaratifManifold(CATCellManifold* iManifold);

  virtual CATDeclarativeManifold * CreateDeclaratifManifold(CATCellManifold* iCellManifold, CATLSOHashTable<CATCellManifold> &ioAdmissibleCMHashTable);

  virtual CATDeclarativeManifold * CreateDeclaratifManifold(CATCellManifold* iCellManifold, CATLISTP(CATCellManifold) &ioAdmissibleCellManifolds);
  
  void AppendSubdivMesh(CATSubdivMesh* iSubdivMesh, CATShell* iSubdivShell);
  //void AppendSubdivShell(CATShell* iSubdivShell);

private:
  //void SetSubdivMesh(CATSubdivMesh* iSubdivMesh);

  CATLISTP(CATGeometry) _CandidateSubdivMeshes;
  CATLISTP(CATGeometry) _CandidateShells;
  /*CATSubdivMesh* _SubdivMesh;
  CATShell* _SubdivShell;*/
};


#endif

