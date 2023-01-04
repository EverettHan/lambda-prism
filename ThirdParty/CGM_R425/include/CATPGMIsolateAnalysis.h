#ifndef CATPGMIsolateAnalysis_H
#define CATPGMIsolateAnalysis_H

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATListOfCATICGMObjects.h"

//Mathematics libraries
#include "CATMathConstant.h"

class CATBody;
class CATGeometry;

class ExportedByCATGMOperatorsInterfaces CATPGMIsolateAnalysis
{
public:
  //-------------------------------------------------------------------------------------
  //- Constructor 
  //-------------------------------------------------------------------------------------
  CATPGMIsolateAnalysis();

  //-------------------------------------------------------------------------------------
  //- Destructor 
  //-------------------------------------------------------------------------------------
  virtual ~CATPGMIsolateAnalysis();

  //-------------------------------------------------------------------------------------
  //- Check whether the Body is isolated 
  //-------------------------------------------------------------------------------------
  virtual CATBoolean IsBodyIsolated() = 0;

  //-------------------------------------------------------------------------------------
  //- Check whether a geometry is isolated 
  //-------------------------------------------------------------------------------------
  virtual CATBoolean IsIsolated(CATGeometry * iGeometry) = 0;
};

/**
 * Creates an analysis tool.
 * @return [out, delete]
 *   The tool.
 */
ExportedByCATGMOperatorsInterfaces CATPGMIsolateAnalysis *CATPGMCreateIsolateAnalysis(CATBody * iBody);

#endif
