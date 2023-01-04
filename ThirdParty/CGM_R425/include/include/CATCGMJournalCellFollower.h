#ifndef CATCGMJournalCellFollower_H
#define CATCGMJournalCellFollower_H

#include "CATCellFollower.h"
#include "PersistentCell.h"
#include "CATCGMNewArray.h"
#include "CATCollec.h"
#include "ListPOfCATBody.h"
#include "CATCGMJournalList.h"
#include "CATTopJournalSpy.h"
#include "CATMathInline.h"

class CATSoftwareConfiguration;
class CATGeoFactory;
class CATBody;
class CATLISTP(CATBody);
class CATCell;
class CATLISTP(CATCell);
class CATVertex;
class CATLISTP(CATVertex);
class CATCellHashTable;

class ExportedByPersistentCell CATCGMJournalCellFollower : public CATCellFollower
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation
	
	// Constructor
  CATCGMJournalCellFollower(CATSoftwareConfiguration* iConfig, CATGeoFactory *iFactory, 
    const CATLISTP(CATBody) &iInputBodies, CATBody* iOutputBody, 
    CATCGMJournalList *iJournal, CATTopJournalSpy &iJournalSpy);
	
  // Destructor
	~CATCGMJournalCellFollower();

  INLINE void SetReportingCells(ListPOfCATCell *iReportingCells);
  INLINE void SetOutputBodyCellHashTable (const CATCellHashTable* iOutputBodyCellHashTable);

  INLINE virtual CATCGMJournalCellFollower* GetAsCGMJournalCellFollower();
  INLINE CATBoolean IsCGMJournalEmpty();
  virtual HRESULT RetrieveEdgeImages(CATLISTP(CATEdge) &iParentEdges, CATLISTP(CATEdge) &iImageEdges);
  HRESULT GetCuttingCellsFromSubDivJournalItem(CATLISTP(CATEdge) &ioSubdivEdges, CATLISTP(CATVertex) &ioSubdivVertices);

  virtual void GetCreatedCells(CATLISTP(CATCell) &ioCreatedCells);
  virtual void GetSharedAndModifiedCells(CATLISTP(CATCell) &ioSharedAndModifiedCells);

public:
  virtual void GetImageCells(CATLISTP(CATCell) &iParentCells, CATLISTP(CATCell) &oImageCells);
  virtual void GetImageCellsByCreation(CATLISTP(CATCell) &iParentCells, CATLISTP(CATCell) &oImageCells);
  virtual void GetParentCells(CATCell *iCell, CATLISTP(CATCell) &oParentCells, CATLISTP(CATBody) &oParentBodies, 
    CATBoolean &oInfoDefined, int &oInfoNumber);
  virtual void GetRelatedInputCells(CATCell *iCell,CATBody *iContainer, CATLISTP(CATCell) &oRelatedCells);
  virtual CATCellFollower* Clone();

  virtual void GetCellsRepresentationsInOutputBody(CATLISTP(CATCell) &iCells, CATLISTP(CATCell) &oCellsRepresentationsInOuputBody); 

private:
  CATCGMJournalList* _Journal;
  CATTopJournalSpy _JournalSpy;
  ListPOfCATCell* _ReportingCells;
  const CATCellHashTable * _OutputBodyCellHTable;
};

INLINE void CATCGMJournalCellFollower::SetReportingCells(ListPOfCATCell *iReportingCells)
{
  _ReportingCells = iReportingCells;
}
INLINE void CATCGMJournalCellFollower::SetOutputBodyCellHashTable (const CATCellHashTable* iOutputBodyCellHashTable)
{
  _OutputBodyCellHTable = iOutputBodyCellHashTable;
}
INLINE CATCGMJournalCellFollower* CATCGMJournalCellFollower::GetAsCGMJournalCellFollower()
{
  return this;
}
INLINE CATBoolean CATCGMJournalCellFollower::IsCGMJournalEmpty()
{
  if (_Journal == NULL || _Journal->Next(NULL) == NULL)
    return TRUE;
  else
    return FALSE;
}
#endif
