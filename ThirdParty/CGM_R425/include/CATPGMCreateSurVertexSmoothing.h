#ifndef CATPGMCreateSurVertexSmoothing_h_
#define CATPGMCreateSurVertexSmoothing_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATDataType.h"
#include "CATSkillValue.h"

class CATNurbsSurface;
class CATSurVertexSmoothing;
class CATMathMxNFullMatrix;
class CATSoftwareConfiguration;

// NLD report ajout CGMPRJ du 130315. Necessaire ici pourquoi?
#ifndef NULL
#define NULL  0
#endif
//
//                        (XScaleRules) iSmooth must be independent from factory scale. NLD130315
//                        see CATSurVertexSmoothing class definition for iTargetPoints  NLD031116
ExportedByCATGMOperatorsInterfaces
CATSurVertexSmoothing *CATPGMCreateSurVertexSmoothing(
                                                      CATSoftwareConfiguration* iSoftwareConfiguration,
                                                      CATNurbsSurface         * iNurbsSurface         ,
                                                      double                    iSmooth               ,
                                                      CATLONG32                 iBorderU1             ,
                                                      CATLONG32                 iBorderU2             ,
                                                      CATLONG32                 iBorderV1             ,
                                                      CATLONG32                 iBorderV2             ,
                                                      CATMathMxNFullMatrix    * iTargetPoints         ,
                                                      CATSkillValue             iMode                 = BASIC);

/**
 * Ascending compatibility for client frameworks. This inline function must be deleted once clients call
 * CATPGMCreateSurVertexSmoothing.
 */
inline CATSurVertexSmoothing *CreateSurVertexSmoothing(
                                                      CATNurbsSurface         * iNurbsSurface         ,
                                                      double                    iSmooth               ,
                                                      CATLONG32                 iBorderU1             ,
                                                      CATLONG32                 iBorderU2             ,
                                                      CATLONG32                 iBorderV1             ,
                                                      CATLONG32                 iBorderV2             ,
                                                      CATMathMxNFullMatrix    * iTargetPoints         ,
                                                      CATSkillValue             iMode                 = BASIC)
{
  return CATPGMCreateSurVertexSmoothing((CATSoftwareConfiguration*) NULL,
                                        iNurbsSurface, iSmooth,
                                        iBorderU1,
                                        iBorderU2,
                                        iBorderV1,
                                        iBorderV2,
                                        iTargetPoints,
                                        iMode);
}

//
ExportedByCATGMOperatorsInterfaces
void Remove( CATSurVertexSmoothing *&ioVertexSmoothing );

#endif /* CATPGMCreateSurVertexSmoothing_h_ */
