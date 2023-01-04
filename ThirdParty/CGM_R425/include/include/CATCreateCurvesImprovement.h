#ifndef CATCreateCurvesImprovement_H
#define CATCreateCurvesImprovement_H

#include "CATGMOperatorsInterfaces.h"
#include "CATPGMCreateCurvesImprovement.h"

/**
 * Ascending compatibility for client frameworks.
 */
inline CATCurvesImprovement * CATCreateCurvesImprovement (      CATSoftwareConfiguration * iSoftwareConfiguration,
                                                                CATGeoFactory            * iFactory              ,
                                                          const CATLISTP(CATCurve)       * iCurvesToImprove      ,
                                                          const CATLISTP(CATCrvLimits)   * iListOfLimits         = 0,
                                                          const CATListOfInt             * iListOfOrientations   = 0)
{
  return CATPGMCreateCurvesImprovement(iSoftwareConfiguration, iFactory, iCurvesToImprove, iListOfLimits, iListOfOrientations);
}

/**
 * Ascending compatibility for client frameworks.
 */
inline CATCurvesImprovement * CATCreateCurvesImprovement (      CATGeoFactory          * iFactory            ,
                                                          const CATLISTP(CATCurve)     * iCurvesToImprove    ,
                                                          const CATLISTP(CATCrvLimits) * iListOfLimits       = 0,
                                                          const CATListOfInt           * iListOfOrientations = 0)
{
  return CATPGMCreateCurvesImprovement(iFactory, iCurvesToImprove, iListOfLimits, iListOfOrientations);
}


#endif /* CATCreateCurvesImprovement_H */
