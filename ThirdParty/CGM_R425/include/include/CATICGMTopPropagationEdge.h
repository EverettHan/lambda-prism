#ifndef CATICGMTopPropagationEdge_h_
#define CATICGMTopPropagationEdge_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMModelInterfaces.h"
#include "CATICGMTopOperator.h"
#include "CATCollec.h"

//class CATCell;
//class CATEdge;
//class CATLISTP_CATCell_;
//class CATLISTP_CATEdge_;
//class CATUnicodeString;
class CATLISTP(CATCell);

extern ExportedByCATGMModelInterfaces IID IID_CATICGMTopPropagationEdge;

class ExportedByCATGMModelInterfaces CATICGMTopPropagationEdge: public CATICGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATICGMTopPropagationEdge();

  /**
* Runs the operator
*/
  virtual int Run() = 0;

  /**
* Returns the list of cells tangent to the initial edges.
*/
  virtual void GetResultListEdges(CATLISTP(CATCell) &ioListEdges) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMTopPropagationEdge(); // -> delete can't be called
};

#endif /* CATICGMTopPropagationEdge_h_ */
