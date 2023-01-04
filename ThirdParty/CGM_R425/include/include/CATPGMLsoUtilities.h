#ifndef CATPGMLsoUtilities_H
#define CATPGMLsoUtilities_H
// COPYRIGHT DASSAULT SYSTEMES 2008
//Jan 2011 Creation EYL
//-----------------------------
#include "CATGMModelInterfaces.h"

class CATSoftwareConfiguration;
class CATCGMJournalList;

class ExportedByCATGMModelInterfaces CATPGMLsoUtilities
{
public:
  CATPGMLsoUtilities(CATSoftwareConfiguration * iConfig);
  virtual ~CATPGMLsoUtilities();

  //CreateJournalOfCellsFromJournalOfCellManifolds
  //traduit un journal de CellManifold en journal de Cell
  //A utiliser avec parcimonie car cela provoque une perte d'informations
  void CreateJournalOfCellsFromJournalOfCellManifolds(CATCGMJournalList &iJournalOfCellManifolds, 
    CATCGMJournalList &ioJournalOfCells);
private:
  CATSoftwareConfiguration * _SoftwareConfiguration;
};

#endif 
