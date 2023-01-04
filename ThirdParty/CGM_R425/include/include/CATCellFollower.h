#ifndef CATCellFollower_H
#define CATCellFollower_H

#include "CATErrorDef.h"

#include "PersistentCell.h"
#include "CATCGMNewArray.h"
#include "CATCollec.h"
#include "ListPOfCATBody.h"
#include "CATBoolean.h"
#include "CATMathInline.h"

class CATSoftwareConfiguration;
class CATGeoFactory;
class CATBody;
class CATLISTP(CATBody);
class CATCell;
class CATLISTP(CATCell);
class CATEdge;
class CATLISTP(CATEdge);
class CATCellManifold;
class CATLISTP(CATCellManifold);
class CATCGMJournalCellFollower;
class CATPersistentCellCellFollower;
class CATLISTP(CATVertex);

class ExportedByPersistentCell CATCellFollower
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation
	
	// Constructor
  CATCellFollower(CATSoftwareConfiguration* iConfig, CATGeoFactory *iFactory, 
    const CATLISTP(CATBody) &iInputBodies, CATBody* iOutputBody);
	
  // Destructor
	virtual ~CATCellFollower();

public:
  INLINE virtual CATCGMJournalCellFollower* GetAsCGMJournalCellFollower();
  INLINE virtual CATPersistentCellCellFollower* GetAsPersistentCellCellFollower();
  virtual void GetImageCells(CATLISTP(CATCell) &iParentCells, CATLISTP(CATCell) &oImageCells) = 0 ;
  virtual void GetImageCellsByCreation(CATLISTP(CATCell) &iParentCells, CATLISTP(CATCell) &oImageCells) = 0;
  
  virtual void GetParentCells(CATCell *iCell, CATLISTP(CATCell) &oParentCells, CATLISTP(CATBody) &oParentBodies, 
    CATBoolean &oInfoDefined, int &oInfoNumber) = 0;
  void GetParentCellManifolds(CATCell *iCell, CATLISTP(CATCellManifold) &oParentCellManifolds, CATBoolean &oInfoDefined, int &oInfoNumber);
  virtual void GetRelatedInputCells(CATCell *iCell,CATBody *iContainer, CATLISTP(CATCell) &oRelatedCells)=0;

  virtual void GetCellsRepresentationsInOutputBody(CATLISTP(CATCell) &iCells, CATLISTP(CATCell) &oCellsRepresentationsInOuputBody) = 0;

  virtual HRESULT RetrieveEdgeImages(CATLISTP(CATEdge) &iParentEdges, CATLISTP(CATEdge) &iImageEdges);

  virtual void GetCreatedCells(CATLISTP(CATCell) &ioCreatedCells) = 0;
  virtual void GetSharedAndModifiedCells(CATLISTP(CATCell) &ioSharedAndModifiedCells) = 0;
  virtual void GetModifiedCells(CATLISTP(CATCell) &ioModifiedCells);

  virtual CATCellFollower* Clone() = 0;
  INLINE CATSoftwareConfiguration* GetSoftwareConfiguration();
  INLINE CATGeoFactory * GetGeoFactory();

  INLINE void AllowSubdivision();
  virtual HRESULT GetCuttingCellsFromSubDivJournalItem(CATLISTP(CATEdge) &ioSubdivEdges, CATLISTP(CATVertex) &ioSubdivVertices) = 0;



protected:
  INLINE void AddInputBody(CATBody *iInputBody);
  INLINE int GetNbOfInputBodies();
  INLINE CATBody * GetInputBody(int iBody);
  INLINE CATBody * GetOutputBody();

protected:
  ListPOfCATBody _InputBodies;
  CATBody * _OutputBody;
  CATSoftwareConfiguration* _Config;
  CATGeoFactory* _Factory;
  CATBoolean _SubdivisionAllowed;
};
INLINE CATCGMJournalCellFollower* CATCellFollower::GetAsCGMJournalCellFollower()
{
  return NULL;
}
INLINE CATPersistentCellCellFollower* CATCellFollower::GetAsPersistentCellCellFollower()
{
  return NULL;
}
INLINE void CATCellFollower::AddInputBody(CATBody *iInputBody)
{
  _InputBodies.Append(iInputBody);
}

INLINE int CATCellFollower::GetNbOfInputBodies()
{
  return _InputBodies.Size();
}
 
INLINE CATBody * CATCellFollower::GetInputBody(int iBody)
{
  return _InputBodies[iBody];
}

INLINE CATBody * CATCellFollower::GetOutputBody()
{
  return _OutputBody;
}
INLINE CATSoftwareConfiguration* CATCellFollower::GetSoftwareConfiguration()
{
  return _Config;
}
INLINE CATGeoFactory * CATCellFollower::GetGeoFactory()
{
  return _Factory;
}
INLINE void CATCellFollower::AllowSubdivision()
{
  _SubdivisionAllowed = TRUE;
}
#endif
