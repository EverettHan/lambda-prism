#ifndef CATGMLivePatternRefUtilities_H
#define CATGMLivePatternRefUtilities_H

#include "CATCGMNewArray.h"
#include "CATTopDefine.h"
#include "CATPersistentCell.h"
#include "ListPOfCATCellManifold.h"

class CATCellManifoldPatternNavigator;
class CATCellManifold;
class CATPersistentBody;
class CATPersistentCellInfra;
class CATHVertex;


class ExportedByPersistentCell CATGMLivePatternRefUtilities
{
public:

  static void GetTargetCellManifoldList(CATCellManifoldPatternNavigator * iPatternNav, CATCellManifold * iCM, CATCGMJournalList * iNewReferenceJournal, ListPOfCATCellManifold & oTargetCMListOnRef);
  static void GetTargetCellManifoldList(CATCellManifoldPatternNavigator * iPatternNav, ListPOfCATCellManifold & iCMList, CATCGMJournalList * iNewReferenceJournal, ListPOfCATCellManifold & oTargetCMListOnRef);
  static CATBoolean AreImagesHVertices(CATHVertex * iOnInputHVertex, CATHVertex * iOnRefHVertex, CATCellManifoldPatternNavigator * iPatternNav, CATCGMJournalList * iNewReferenceJournal);
};

#endif 

