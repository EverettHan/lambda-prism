#ifndef CATCuttingsData_h
#define CATCuttingsData_h

#include "CATMathInline.h"
#include "CATBoolean.h"
#include "ExportedByCATTopologicalObjects.h"
#include "CATListOfInt.h"

class CATHashTableWithIntAssoc;
class CATBody;
class CATListPtrCATBody;
class CATCGMHashTableWithAssoc;
class CATAdaptiveHashTable;
class CATCGMJournalList;

struct ExportedByCATTopologicalObjects CATCuttingsData
{
  static CATCuttingsData* Build(const CATListPtrCATBody& iCuttingWires,
                                        const CATListOfInt& iOrientations,
                                        CATBoolean iIsBoundary,
                                        int iMultiInterIdx,
                                        CATCGMHashTableWithAssoc* ipWireInterToWID,
                                        const CATAdaptiveHashTable& iHTWiresBoundaryOfConfusion,
                                        CATBody * ipBodySplitted);


  static CATCuttingsData* Merge(CATCuttingsData* ipCuttingData1,CATCuttingsData * ipCuttingData2);

  /**
  * Creer les liens entre les cuttings data pour toutes les edges et les faces
  *  à partir des liens sur les bodies.
  *
  * @param iHTBodyToCuttingData
  *   Lien Body -> cuttingData
  * @param ipOperationReport
  *   Journal des eventuels modifications des cellules. Warning: the journal will be tassed !
  * @param oHTCellToCuttingData
  *   Lien Edge/Face -> cuttingData. 
  */
  static void TransfereLinksFromBodyToAllCells_Tass(const CATCGMHashTableWithAssoc& iHTBodyToCuttingData,
                                                    CATCGMJournalList * ipOperationReport,
                                                    CATCGMHashTableWithAssoc& oHTCellToCuttingData);


  ~CATCuttingsData();
  void Dump();

  CATHashTableWithIntAssoc* _pCuttingDomainToOri;
  CATBoolean                _isOnBorder;       //La mosaic possède une edge qui est sur le bord du shell initial
  int                       _multipleInterIdx; // La coupante traverse le shell initiale plusieurs fois

private:
  CATCuttingsData();
};

#endif
