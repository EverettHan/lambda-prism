#ifndef CATPGMHybClashCellCellIter_h_
#define CATPGMHybClashCellCellIter_h_

// COPYRIGHT DASSAULT SYSTEMES 2020

#include "CATGMModelInterfaces.h"
#include "CATCGMRefCounted.h"

#include "CATSysBoolean.h"
class CATCell;

class ExportedByCATGMModelInterfaces CATPGMHybClashCellCellIter: public CATCGMRefCounted
{
public:
  // Iterator services
  // -----------------
  virtual void Begin() = 0;

  virtual CATBoolean End() = 0;

  virtual void operator ++()=0;
  
  // Data access
  // -----------
  /*
   * Method to retrieve CATCells for the current couple.
   * Int value must be 1 or 2 : the position of the cell in the couple.
   */
  virtual CATCell *GetCell(int ) = 0;

};

#endif /* CATPGMHybClashCellCellIter_h_ */
