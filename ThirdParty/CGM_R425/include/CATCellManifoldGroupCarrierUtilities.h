#ifndef CATCellManifoldGroupCarrierUtilities_H
#define CATCellManifoldGroupCarrierUtilities_H

#include "PersistentCell.h"
#include "CATCGMNewArray.h"
#include "CATCellManifoldGroup.h"

// @nocgmitf (this class doesn't need a CATIPGM interface)
class ExportedByPersistentCell CATCellManifoldGroupCarrierUtilities
{
public:

  CATCGMNewClassArrayDeclare;      // Pool allocation

  static CATBoolean ImagesAreEqualToParents(CATCellManifoldGroup * iParentCellManifoldGroup, CATCellManifoldGroup * iImageCellManifoldGroup);
  static CATBoolean ImageContextsAreEqualToParentContexts(CATCellManifoldGroup * iParentCellManifoldGroup, CATCellManifoldGroup * iImageCellManifoldGroup);

  
};

#endif 

