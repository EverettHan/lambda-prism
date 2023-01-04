#ifndef CATPGMCreateTopParallelSimplif_h_
#define CATPGMCreateTopParallelSimplif_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @level Protected
 * @usage U1
 */

#include "CATGMOperatorsInterfaces.h"

class CATBody;
class CATICGMExtrapolParallelTool;
class CATIPGMTopParallel;

/**
* Creates a CATIPGMTopParallel operator that computes a wire parallel 
* (according to a given law) to another one on a shell.
* <b>Orientation</b>: The resulting wire is oriented as the input one.<br>
* <b>Journal</b>: If the distance is null, a new body is created and 
* the edges are written as kept. If not, the new body contains the new edges, written
* as created.
* @param iOption
* The definition of the parameters for the operation.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopParallel *CATPGMCreateTopParallelMostContinuous(
  CATICGMExtrapolParallelTool *iOption,
  CATBody *iCurve);

#endif /* CATPGMCreateTopParallelSimplif_h_ */
