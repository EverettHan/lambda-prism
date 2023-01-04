#ifndef CATGMLivePersistentCellInformer_H
#define CATGMLivePersistentCellInformer_H

#include "PersistentCell.h"
#include "CATCGMNewArray.h"
#include "CATMathInline.h"

class CATPersistentBody;
class CATPersistentFace;
class CATAutoBaseThreadContext;
class CATFace;
class CATGMLiveInfra;

class ExportedByPersistentCell CATGMLivePersistentCellInformer 
{
public:
  friend class CATPersistentCellInfra;
  friend class CATGMLiveInfra;
  CATCGMNewClassArrayDeclare;      // Pool allocation
	
	// Constructor
  CATGMLivePersistentCellInformer();
	
  // Destructor
	~CATGMLivePersistentCellInformer();

protected:
  INLINE void SetPersistentBody(CATPersistentBody* iPersistentBody);
  CATPersistentFace* GetPersistentFace(CATFace *iFace, const CATAutoBaseThreadContext &iThreadContext);

private:
 CATPersistentBody* _PersistentBody;
};

INLINE void CATGMLivePersistentCellInformer::SetPersistentBody(CATPersistentBody* iPersistentBody)
{
  _PersistentBody = iPersistentBody;
}

#endif
