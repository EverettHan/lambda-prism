#ifndef CATPGMCreateCrvVertexSmoothing_h_
#define CATPGMCreateCrvVertexSmoothing_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATSkillValue.h"

class CATCrvVertexSmoothing;
class CATNurbsCurve;
class CATPNurbs;
class CATMathMxNFullMatrix;
class CATSoftwareConfiguration;

//
//                        (XScaleRules) iSmooth must be independent from factory scale. NLD130315
//                        see CATCrvVertexSmoothing class definition for iTargetPoints  NLD031116
ExportedByCATGMOperatorsInterfaces
CATCrvVertexSmoothing *CATPGMCreateCrvVertexSmoothing(
                                                      CATSoftwareConfiguration* iSoftwareConfiguration,
                                                      CATNurbsCurve           * iNurbsCurve           ,
                                                      double                    iSmooth               ,
                                                      CATMathMxNFullMatrix    * iTargetPoints         );

// DEPRECATED (see above with software configuration)
ExportedByCATGMOperatorsInterfaces
CATCrvVertexSmoothing *CATPGMCreateCrvVertexSmoothing(
                                                      CATNurbsCurve           * iNurbsCurve           ,
                                                      double                    iSmooth               ,
                                                      CATMathMxNFullMatrix    * iTargetPoints         ,
                                                      CATSkillValue             iMode                 = BASIC);

//
// Ascending compatibility for client frameworks. This inline function must be deleted once clients call
// CATPGMCreateCrvVertexSmoothing (or CATCreateCrvVertexSmoothing)
//
inline CATCrvVertexSmoothing* CreateCrvVertexSmoothing(
                                                       CATNurbsCurve          * iNurbsCurve           ,
                                                       double                   iSmooth               ,
                                                       CATMathMxNFullMatrix   * iTargetPoints         ,
                                                       CATSkillValue            iMode                 = BASIC)
{
  return CATPGMCreateCrvVertexSmoothing(iNurbsCurve, iSmooth, iTargetPoints, iMode);
}

//
//                        (XScaleRules) iSmooth must be independent from factory scale. NLD130315
//                        see CATCrvVertexSmoothing class definition for iTargetPoints  NLD031116
ExportedByCATGMOperatorsInterfaces
CATCrvVertexSmoothing* CATPGMCreateCrvVertexSmoothing (
                                                       CATSoftwareConfiguration* iSoftwareConfiguration,
                                                       CATPNurbs               * iPNurbs               ,
                                                       double                    iSmooth               ,
                                                       CATMathMxNFullMatrix    * iTargetPoints         );
// DEPRECATED (see above with software configuration)
ExportedByCATGMOperatorsInterfaces
CATCrvVertexSmoothing* CATPGMCreateCrvVertexSmoothing(
                                                      CATPNurbs                * iPNurbs               ,
                                                      double                     iSmooth               ,
                                                      CATMathMxNFullMatrix     * iTargetPoints         ,
                                                      CATSkillValue              iMode                 = BASIC);

//
// Ascending compatibility for client frameworks. This inline function must be deleted once clients call
// CATPGMCreateCrvVertexSmoothing (or CATCreateCrvVertexSmoothing)
//
inline CATCrvVertexSmoothing *CreateCrvVertexSmoothing(
                                                      CATPNurbs                * iPNurbs               ,
                                                      double                     iSmooth               ,
                                                      CATMathMxNFullMatrix     * iTargetPoints         ,
                                                      CATSkillValue              iMode                 = BASIC)
{
  return CATPGMCreateCrvVertexSmoothing(iPNurbs, iSmooth, iTargetPoints, iMode);
}

// Operator removal
ExportedByCATGMOperatorsInterfaces
void Remove( CATCrvVertexSmoothing *&iVertexSmoothing );

#endif /* CATPGMCreateCrvVertexSmoothing_h_ */
