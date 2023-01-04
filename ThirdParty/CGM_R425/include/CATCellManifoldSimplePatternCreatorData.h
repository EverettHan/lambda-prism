#ifndef CATCellManifoldSimplePatternCreatorData_H
#define CATCellManifoldSimplePatternCreatorData_H

//----------------------------------------------------------
// JJ3 30-09-2011 Creation
// Classe permettant de faire un new dans NewTopo
//----------------------------------------------------------


#include "CATCellManifoldPatternCreator.h"
#include "PersistentCell.h"
#include "CATCGMNewArray.h"
#include "CATMathTransformation.h"
#include "ListPOfCATPersistentBodies.h"

class CATCellManifoldGroupOperator;
class CATPersistentCellCellFollower;

class ExportedByPersistentCell CATCellManifoldSimplePatternCreatorData : public CATCellManifoldPatternCreator
{
  public:

  CATCGMDeclareManifoldAgent(CATCellManifoldSimplePatternCreatorData, CATDeclarativeManifoldAgent);

 	// Constructor
  CATCellManifoldSimplePatternCreatorData();
  CATCellManifoldSimplePatternCreatorData(short iNbInstances, CATMathTransformation &iUnitaryTransfo, CATPersistentCellInfra * iPersistentCellInfra);
	
  // Destructor
	virtual ~CATCellManifoldSimplePatternCreatorData();

//  void SetReferenceLiveBody(CATLiveBody *iRefLiveBody);
  void SetReferencePersistentBodyList(ListPOfCATPersistentBodies & iRefPersistentBodyList);

  virtual void SetNoPatternCreationFaceList(const ListPOfCATFace & iNoPatternCreationFaceList);

  virtual HRESULT CreateImageManifolds();
  virtual CATCellManifoldPatternCreator * GetAsCellManifoldPatternCreator();
  virtual int GetPriority();
  virtual CATBoolean IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold();
  virtual CATDeclarativeManifoldAgent* Clone();

protected:

  short _NbInstances;
  CATMathTransformation _UnitaryTransfo;
  //CATLiveBody* _RefLiveBody; // A RETIRER !!!!!!!
  ListPOfCATPersistentBodies _RefPersistentBodyList;
  ListPOfCATFace _NoPatternCreationFaceList;
  CATPersistentCellInfra * _PersistentCellInfra;

  int _DebugTag;

};

#endif
