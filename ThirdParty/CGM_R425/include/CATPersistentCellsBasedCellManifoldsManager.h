#ifndef CATPersistentCellsBasedCellManifoldsManager_H
#define CATPersistentCellsBasedCellManifoldsManager_H

#include "CATPersistentCell.h"
#include "CATCellManifoldsManager.h"
#include "CATCGMNewArray.h"
#include "ListPOfCATPersistentBodies.h"
#include "CATCollec.h"
#include "CATMathInline.h"

class CATPersistentCellFactory;
class CATAutoBaseThreadContext;
class CATPersistentBody;
class CATPersistentCellsJournal;
class CATBoneFollowerPersistentFaceStructure;

class ExportedByPersistentCell CATPersistentCellsBasedCellManifoldsManager : public CATCellManifoldsManager
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation

  // Constructor
  CATPersistentCellsBasedCellManifoldsManager(CATPersistentCellInfra         &iPersistentCellInfra,
                                              ListPOfCATPersistentBodies     & iInputPersistentBodies, 
                                              CATPersistentBody              & iOutputPersistentBody,
                                              CATPersistentCellsJournal      * iPersistentCellsJournal,
                                              const CATListOfInt             * iNoCopyBodies=NULL);

  const CATAutoBaseThreadContext& GetThreadContext();
  // ST5 end modifs

  void SetPatternStructure(CATBoneFollowerPersistentFaceStructure* iPatternStructure);
  void SetOffsetStructure(CATBoneFollowerPersistentFaceStructure* iOffsetStructure);
  // Destructor
  virtual ~CATPersistentCellsBasedCellManifoldsManager();

protected:

  INLINE virtual CATPersistentCellsBasedCellManifoldsManager* GetAsPersistentCellsBasedCellManifoldsManager();

};


INLINE CATPersistentCellsBasedCellManifoldsManager* CATPersistentCellsBasedCellManifoldsManager::GetAsPersistentCellsBasedCellManifoldsManager()
{
  return this;
}

#endif
