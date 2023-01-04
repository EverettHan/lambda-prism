#ifndef CATPersistentCellCellFollower_H
#define CATPersistentCellCellFollower_H

#include "CATCellFollower.h"
#include "PersistentCell.h"
#include "CATCGMNewArray.h"
#include "CATCollec.h"
#include "CATCGMJournal.h"

#include "CATPersistentCellFactory.h"
#include "CATAutoBaseThreadContext.h"
#include "ListPOfCATPersistentBodies.h"
#include "CATMathInline.h"
// #include "CATCGMHashTable.h"

class CATSoftwareConfiguration;
class CATGeoFactory;
class CATBody;
class CATLISTP(CATBody);
class CATCell;
class CATLISTP(CATCell);
class CATPersistentCellsJournal;
template <class CATPersistentCell> class CATLSOHashTable;
class CATPersistentBody;


class ExportedByPersistentCell CATPersistentCellCellFollower : public CATCellFollower
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation
	
  // Constructor
  CATPersistentCellCellFollower(CATPersistentCellFactory &iPersistentCellFactory, const CATAutoBaseThreadContext &iThreadContext,
    ListPOfCATPersistentBodies &iInputPersistentBodies, CATPersistentBody &iOutputPersistentBody,
    CATPersistentCellsJournal* iPersistentCellJournal,
    CATBoolean iFollowOnlyModifications);

  // Destructor
	~CATPersistentCellCellFollower();

public:
  INLINE virtual CATPersistentCellCellFollower* GetAsPersistentCellCellFollower();
  virtual void GetImageCells(CATLISTP(CATCell) &iParentCells, CATLISTP(CATCell) &oImageCells);
  virtual void GetImageCellsByCreation(CATLISTP(CATCell) &iParentCells, CATLISTP(CATCell) &oImageCells);
  virtual void GetParentCells(CATCell *iCell, CATLISTP(CATCell) &oParentCells, CATLISTP(CATBody) &oParentBodies, 
    CATBoolean &oInfoDefined, int &oInfoNumber);
  void GetCellsInInputBodies(CATCell *iCell,   CATLISTP(CATCell) &oParentCells,   CATLISTP(CATBody) &oParentBodies);
    virtual void GetRelatedInputCells(CATCell *iCell,CATBody *iContainer, CATLISTP(CATCell) &oRelatedCells);
  void GetParentCellsThroughLeafPersistentCells(CATCell *iCell, CATLISTP(CATCell) &oParentCells);

  virtual void GetCellsRepresentationsInOutputBody(CATLISTP(CATCell) &iCells, CATLISTP(CATCell) &oCellsRepresentationsInOuputBody);

  virtual void GetReportType(CATLISTP(CATCell) &iImageCells, CATCGMJournal::Type& ioReportType, int& ioInfo);

  void SetCreatedCells(CATLISTP(CATPersistentCell) &iCreatedCells);
  virtual void GetCreatedCells(CATLISTP(CATCell) &ioCreatedCells);
  virtual void GetSharedAndModifiedCells(CATLISTP(CATCell) &ioSharedAndModifiedCells);
  virtual void GetModifiedCells(CATLISTP(CATCell) &ioModifiedCells);

  virtual CATCellFollower* Clone();

  void GetCellsRepresentationsInOutputBodyWithTypes(CATLISTP(CATCell) &iCells, CATLISTP(CATCell) &oCellsRepresentationsInOuputBody, CATListOfInt &oTypes);

  HRESULT GetCuttingCellsFromSubDivJournalItem(CATLISTP(CATEdge) &ioSubdivEdges,
                                               CATLISTP(CATVertex) &ioSubdivVertices);
  INLINE void GetInputAndOutPutPersistentBodies(ListPOfCATPersistentBodies &oInputPersistentBodies,CATPersistentBody *&oOutputBody) const;
protected:
  void GetParentCellsFromPersistentCells(ListPOfCATPersistentCells &iPersistentCells, 
    CATLISTP(CATCell) &oParentCells, CATLISTP(CATBody) &oParentBodies, int iType=-1);
  INLINE CATPersistentCellFactory &GetPersistentCellFactoryRef() const;
  INLINE CATPersistentBody &GetOutputPersistentBody() const;

  void GetRepresentationInContainer(ListPOfCATPersistentCells &iPersistentCells, CATPersistentBody *iContainer, ListPOfCATCell &oCells, CATListOfInt *oTypes = NULL);

  void GetRepresentationInContainer(const CATLSOHashTable<CATPersistentCell>  & iPersistentCellHTab,
                                    CATPersistentBody                         * iContainer, 
                                    ListPOfCATCell                            & oCells,
                                    CATListOfInt                              * oTypes=NULL);

  // deprecated 
  /*void GetRepresentationInContainer(CATCGMHashTable   & iPersistentCellHTab,
                                    CATPersistentBody * iContainer, 
                                    ListPOfCATCell    & oCells,
                                    CATListOfInt      * oTypes=NULL);*/

  virtual void SearchModifiedCells();

protected:
  CATPersistentCellFactory &_PersistentCellFactory;
  const CATAutoBaseThreadContext &_ThreadContext;
  ListPOfCATPersistentBodies _InputPersistentBodies;
  CATPersistentBody& _OutputPersistentBody;
  ListPOfCATCell _ModifiedCells;
  CATBoolean _ModifiedCellsComputed;
  
  CATBoolean _FollowOnlyModifications;
  CATPersistentCellsJournal* _PersistentCellJournal;
  CATLISTP(CATPersistentCell) * _CreatedCells;
  CATCGMJournalList   * _InputOutputJournal; //EYL ForPerfos
};

INLINE CATPersistentCellCellFollower* CATPersistentCellCellFollower::GetAsPersistentCellCellFollower()
{
  return this;
}
INLINE CATPersistentCellFactory &CATPersistentCellCellFollower::GetPersistentCellFactoryRef() const
{
  return _PersistentCellFactory;
}

INLINE CATPersistentBody &CATPersistentCellCellFollower::GetOutputPersistentBody() const
{
  return _OutputPersistentBody;
}

INLINE void CATPersistentCellCellFollower::GetInputAndOutPutPersistentBodies(ListPOfCATPersistentBodies &oInputPersistentBodies,CATPersistentBody *&oOutputBody) const
{
  oInputPersistentBodies = _InputPersistentBodies;
  oOutputBody = &_OutputPersistentBody;
}

#endif
