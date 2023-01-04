#ifndef CATNavigatorBase_H
#define CATNavigatorBase_H

#include "CATDRepNavigatorInterface.h"
#include "CATBody.h"
#include "CATPersistentCell.h"
#include "CATCollecRoot.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATEdge.h"
#include "ListPOfCATVertex.h"
#include "ListPOfCATCellManifold.h"
#include "CATLISTV_CATMathPoint.h"
#include "ListPOfCATNavigatorPseudoVertex.h"
#include "CATMathInline.h"

class CATDRepNavigator;
class CATCell;
class CATFace;
class CATEdge;
class CATVertex;
class CATCellManifold;
class CellHashTableAssocList;
class CATCellManifoldHashTable;
class CATDeclarativeManifoldHashTable;
class CATLISTP(CATCell);

class ExportedByPersistentCell CATNavigatorBase : public CATDRepNavigatorInterface
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation

  // Constructor
  CATNavigatorBase(const CATTopData &iData, CATBody* iBody); 

  // Destructor
  virtual ~CATNavigatorBase();

  // GetAs methods
  virtual CATDRepNavigator * GetAsDRepNavigator();

  // Set methods
  void SetCell(CATCell * iCell);
  void SetCellManifold(CATCellManifold * iCellManifold, CATCellManifold * iSecondCellManifold = NULL); 

  // Compute methods
  virtual HRESULT ComputeAdjacentElements(CATBoolean iOnlySmoothAdjacency = FALSE, CATBoolean iComputeTransitionMathPoint = FALSE, CATBoolean iIgnoreCellsWithSameSurface = FALSE);
  virtual HRESULT ComputeBorderPseudoVertices(CATBoolean iOnlyPseudoVertexWithAtLeastFourSharpEdges = TRUE, CATBoolean iComputePseudoVertexMathPoint = TRUE);
  virtual HRESULT ComputeCommonBorderEdges();

  // Extend user selection
  // virtual HRESULT SpecExtendCellManifolds(const ListPOfCATCellManifold &iUserCMSelection, CATCellManifoldHashTable &oSpecExtentedCMHashTab) const;
  virtual HRESULT NeutralContextToDraftManifold(CATCellManifold *ipCellManifold, CATDeclarativeManifoldHashTable &oRelativeDraftManifoldHT) const;

  //Get methods
  virtual HRESULT GetCells(CATLISTP(CATCell) &oResultCells) const;
  void GetFaces(CATLISTP(CATFace) &oResultFaces);
  void GetEdges(CATLISTP(CATEdge) &oResultEdges);
  void GetVertices(CATLISTP(CATVertex) &oResultVertices);
  void GetCellManifolds(CATLISTP(CATCellManifold) &oResultCelManifolds);
  void GetMathPoints(CATLISTV(CATMathPoint) &oResultMathPoints);
  void StealPseudovertices(CATLISTP(CATNavigatorPseudoVertex) &oResultPseudoVertices); // PseudoVertices should be deleted by the caller of this method



  HRESULT FindNeighbours(ListPOfCATCell & iCells, ListPOfCATCell & oNeighbourCells, int iDim);
  HRESULT FindNeighbours(CATCell * iCell, ListPOfCATCell & oNeighbourCells, int iDim);

protected:
  void ClearInputs();
  void ClearOutputs();
  void AddPseudovertex(CATNavigatorPseudoVertex* &ioPseudoVertex);

  INLINE CATSoftwareConfiguration* GetConfig() const;
  INLINE CATGeoFactory* GetFactory() const ;


private:
  CATNavigatorBase(const CATNavigatorBase&);  
  CATNavigatorBase& operator=(const CATNavigatorBase&);  

protected:
  CATTopData _TopData;
  CATBody* _Body;
  CATBody * GetBody() const;

  CATCell* _InputCell; 
  CATCellManifold* _InputCellManifold, *_InputCellManifold2;

  ListPOfCATFace _ResultFaces;
  ListPOfCATEdge _ResultEdges;
  ListPOfCATVertex _ResultVertices;
  ListPOfCATCellManifold _ResultCellManifolds;
  CATLISTV(CATMathPoint) _ResultMathPoints;
  CATLISTP(CATNavigatorPseudoVertex) _ResultPseudoVertices;

  CellHashTableAssocList * _PartialActivation;

};

INLINE CATSoftwareConfiguration* CATNavigatorBase::GetConfig() const
{
  return _TopData.GetSoftwareConfiguration();
}
INLINE CATGeoFactory* CATNavigatorBase::GetFactory() const
{
  if (_Body)
    return _Body->GetFactory();
  else
  return NULL;
}

#endif
