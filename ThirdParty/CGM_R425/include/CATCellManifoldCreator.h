#ifndef CATCellManifoldCreator_H
#define CATCellManifoldCreator_H

#include "CATDeclarativeManifoldAgent.h"
#include "PersistentCell.h"
#include "CATCGMNewArray.h"
#include "ListPOfCATBody.h"
#include "CATListOfInt.h"
#include "CATCollec.h"
#include "CATMathInline.h"

class CATCellManifoldsManager;
class CATCellFollower;
class CATBody;
class CATDomain;
class CATShell;
class CATCell;
class CATLISTP(CATCell);
class CATEdge;
class CATLISTP(CATEdge);
class CATCellManifold;
class CATLISTP(CATCellManifold);
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATCGMHashTable;


class ExportedByPersistentCell CATCellManifoldCreator : public CATDeclarativeManifoldAgent
{
public:
  CATCGMDeclareManifoldAgent(CATCellManifoldCreator, CATDeclarativeManifoldAgent);

  // Constructor
  CATCellManifoldCreator();

  // Destructor
  virtual ~CATCellManifoldCreator();

  virtual CATBoolean GetAdmissibleCells(CATLISTP(CATCell) &ioAdmissibleCells);
  INLINE CATCGMHashTable* GetOutBodyCellManifoldHashTable();
  virtual HRESULT CreateImageManifolds();
  virtual void AddCellManifoldImage(CATLISTP(CATCellManifold) &iParentCellManifolds, CATLISTP(CATCellManifold) &iChildrenManifolds, int iInfo, CATBoolean iForbidZeroInfo=TRUE);
  virtual int GetPriority();
  INLINE virtual CATBoolean IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold();
  INLINE virtual CATDeclarativeManifoldAgent* Clone();

  INLINE virtual CATCellManifoldCreator* GetAsCellManifoldCreator();

  void SetNoFacePropagation();
  void SetUserDefinedCuttingVertices(ListPOfCATVertex &iUserDefinedCuttingVertices);

  INLINE CATBoolean GetCellManifoldsCuttingMode() const;
  INLINE void SetCellManifoldsCuttingMode(CATBoolean iBoolValue);

protected:
  virtual void CreateCellManifolds(CATDeclarativeManifoldAgent &iDMAgent, CATDomain &iDomain, CATLISTP(CATCell) &iDomainCells, 
    int iCellsDim, CATLISTP(CATCellManifold) &ioCreatedCellManifolds);

private:
  void CreateCellManifolds(CATDeclarativeManifoldAgent &iDMAgent, CATLISTP(CATCellManifold) &ioCreatedCellManifolds);

  void CheckNoPropagationBetweenPlanAndCylinder(ListPOfCATCell & ioManifoldFaces, CATFace * iFace);

  void CreateCellManifoldsAccordingToConnexity(CATDomain &iDomain, CATLISTP(CATCell) &iCells, int iCellsDim, 
    CATBoolean iCellsWithParents, int* iInfoNumber, CATLISTP(CATEdge) &iCuttingEdges, CATLISTP(CATVertex) &iCuttingVertices,
    CATLISTP(CATCellManifold) &ioCreatedCellManifolds, CATListOfInt &ioCreationInfos, CATBoolean iPropagate=TRUE);

  void AddCuttingVerticesFromConnectedCellManiolds(CATDomain &iDomain, 
    CATLISTP(CATCell) &iCells, CATLISTP(CATVertex) &ioCuttingVertices);

  void PropagateFace(CATFace* iFace, CATShell *iShell, CATLISTP(CATCell) &iAuthorizedFaces,
    CATBoolean iFaceWithParents, CATLISTP(CATEdge) &iCuttingEdges, CATLISTP(CATCell) &oFaces);
  void PropagateEdge(CATEdge* iEdge, CATDomain &iDomain, const CATLISTP(CATCell) &iAuthorizedEdges, 
    CATBoolean iEdgeWithParents, CATLISTP(CATVertex) &iCuttingVertices, CATLISTP(CATCell) &oEdges);

  void GenerateOutBodyCellManifoldHashTable();
  enum MergeStatus { CommonFormerCMFound,MergeIsForbiden,NothingFound};
  MergeStatus AreCellsInCommonDeclarativeManifoldInFormerLiveBody(const ListPOfCATCell & Cells1,const ListPOfCATCell & Cells2);

  void AddDeleteOrderToCellManifoldJournal();

  CATBoolean ForbidPropagationForCarton(CATFace * iFace);

  CATBoolean        _FacePropagation;
  ListPOfCATVertex  _UserDefinedCuttingVertices;
  CATCGMHashTable*  _OutBodyCMHashTable;
  CATBoolean        _CellManifoldsCuttingMode;
  
  ListPOfCATDeclarativeManifold _AddedDeclarativeManifolds;
};

INLINE CATCGMHashTable* CATCellManifoldCreator::GetOutBodyCellManifoldHashTable()
{
  return _OutBodyCMHashTable;
}
INLINE CATBoolean CATCellManifoldCreator::IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold()
{
  return FALSE;
}
INLINE CATDeclarativeManifoldAgent* CATCellManifoldCreator::Clone()
{
  return new CATCellManifoldCreator();
}
INLINE CATCellManifoldCreator* CATCellManifoldCreator::GetAsCellManifoldCreator()
{
  return this;
}

INLINE void CATCellManifoldCreator::SetCellManifoldsCuttingMode(CATBoolean iBoolValue) {
  _CellManifoldsCuttingMode = iBoolValue; }

INLINE CATBoolean CATCellManifoldCreator::GetCellManifoldsCuttingMode() const {
  return _CellManifoldsCuttingMode; }

#endif
