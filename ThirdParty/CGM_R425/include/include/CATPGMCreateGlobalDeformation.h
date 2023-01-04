#ifndef CATPGMCreateGlobalDeformation_h_
#define CATPGMCreateGlobalDeformation_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATDataType.h"
#include "CATSkillValue.h"

class CATGeoFactory;
class CATGlobalDeformation;
class CATMathAxis;
class CATNurbsCurve;
class CATNurbsSurface;
class CATGeometry;

//-----------------------------------------------------------------------------
//Cartesian deformation: StartAxis and TargetAxis define a linear transformation
//-----------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATGlobalDeformation *CATPGMCreateGlobalDeformation(
  CATGeoFactory *ifactory,
  CATMathAxis *iStartAxis,
  CATMathAxis *iTargetAxis,
  const CATLONG32 iNbOfGeometricElementsToMove,
  CATGeometry **iGeometricElementsToMove,
  CATSkillValue iMode = BASIC);

inline CATGlobalDeformation *CreateGlobalDeformation(
  CATGeoFactory *ifactory,
  CATMathAxis *iStartAxis,
  CATMathAxis *iTargetAxis,
  const CATLONG32 iNbOfGeometricElementsToMove,
  CATGeometry **iGeometricElementsToMove,
  CATSkillValue iMode = BASIC)
{
  return CATPGMCreateGlobalDeformation(ifactory, iStartAxis, iTargetAxis, iNbOfGeometricElementsToMove, iGeometricElementsToMove, iMode);
}

//-----------------------------------------------------------------------------
//Cartesian deformation with adjustment surface(s) . The linear transformation
//first define by  StartAxis and TargetAxis is modified by guiding constraints.  
//-----------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATGlobalDeformation *CATPGMCreateGlobalDeformation(
  CATGeoFactory *ifactory,
  CATMathAxis *iStartAxis,
  CATMathAxis *iTargetAxis,
  const CATLONG32 iNbOfGuidingSurfaces,
  CATNurbsSurface **iGuidingSurfaces,
  const CATLONG32 iNbOfGeometricElementsToMove,
  CATGeometry **iGeometricElementsToMove,
  CATSkillValue iMode = BASIC);

inline CATGlobalDeformation *CreateGlobalDeformation(
  CATGeoFactory *ifactory,
  CATMathAxis *iStartAxis,
  CATMathAxis *iTargetAxis,
  const CATLONG32 iNbOfGuidingSurfaces,
  CATNurbsSurface **iGuidingSurfaces,
  const CATLONG32 iNbOfGeometricElementsToMove,
  CATGeometry **iGeometricElementsToMove,
  CATSkillValue iMode = BASIC)
{
  return CATPGMCreateGlobalDeformation(ifactory, iStartAxis, iTargetAxis, iNbOfGuidingSurfaces, iGuidingSurfaces, iNbOfGeometricElementsToMove, iGeometricElementsToMove, iMode);
}

//-----------------------------------------------------------------------------
//Cartesian deformation with adjustment surface(s) . The linear transformation
//first define by  StartAxis and TargetAxis is modified by guiding constraints.  
//-----------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATGlobalDeformation *CATPGMCreateGlobalDeformation(
  CATGeoFactory *ifactory,
  CATMathAxis *iStartAxis,
  CATMathAxis *iTargetAxis,
  const CATLONG32 iNbOfGuidingSurfaces,
  CATNurbsSurface **iGuidingSurfaces,
  const CATLONG32 iNbOfGeometricElementsToMove,
  CATGeometry **iGeometricElementsToMove,
  const CATLONG32 iConstraintOnGuide,
  CATSkillValue iMode = BASIC);

inline CATGlobalDeformation *CreateGlobalDeformation(
  CATGeoFactory *ifactory,
  CATMathAxis *iStartAxis,
  CATMathAxis *iTargetAxis,
  const CATLONG32 iNbOfGuidingSurfaces,
  CATNurbsSurface **iGuidingSurfaces,
  const CATLONG32 iNbOfGeometricElementsToMove,
  CATGeometry **iGeometricElementsToMove,
  const CATLONG32 iConstraintOnGuide,
  CATSkillValue iMode = BASIC)
{
  return CATPGMCreateGlobalDeformation(ifactory, iStartAxis, iTargetAxis, iNbOfGuidingSurfaces, iGuidingSurfaces, iNbOfGeometricElementsToMove, iGeometricElementsToMove, iConstraintOnGuide, iMode);
}

//-----------------------------------------------------------------------------
//Deformation defined by two parametric surfaces
//-----------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATGlobalDeformation *CATPGMCreateGlobalDeformation(
  CATGeoFactory *ifactory,
  CATNurbsSurface *iStartParametrisationSurface,
  CATNurbsSurface *iTargetParametrisationSurface,
  const CATLONG32 iNbOfGeometricElementsToDeform,
  CATGeometry **iGeometricElementsToDeform,
  CATSkillValue iMode = BASIC);

inline CATGlobalDeformation *CreateGlobalDeformation(
  CATGeoFactory *ifactory,
  CATNurbsSurface *iStartParametrisationSurface,
  CATNurbsSurface *iTargetParametrisationSurface,
  const CATLONG32 iNbOfGeometricElementsToDeform,
  CATGeometry **iGeometricElementsToDeform,
  CATSkillValue iMode = BASIC)
{
  return CATPGMCreateGlobalDeformation(ifactory, iStartParametrisationSurface, iTargetParametrisationSurface, iNbOfGeometricElementsToDeform, iGeometricElementsToDeform, iMode);
}

//-----------------------------------------------------------------------------
//Deformation defined by two parametric surfaces with Guiding  surfaces 
//-----------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATGlobalDeformation *CATPGMCreateGlobalDeformation(
  CATGeoFactory *ifactory,
  CATNurbsSurface *iStartParametrisationSurface,
  CATNurbsSurface *iTargetParametrisationSurface,
  const CATLONG32 iNbOfGuidingSurfaces,
  CATNurbsSurface **iGuidingSurfaces,
  const CATLONG32 iNbOfGeometricElementsToDeform,
  CATGeometry **iGeometricElementsToDeform,
  CATSkillValue iMode = BASIC);

inline CATGlobalDeformation *CreateGlobalDeformation(
  CATGeoFactory *ifactory,
  CATNurbsSurface *iStartParametrisationSurface,
  CATNurbsSurface *iTargetParametrisationSurface,
  const CATLONG32 iNbOfGuidingSurfaces,
  CATNurbsSurface **iGuidingSurfaces,
  const CATLONG32 iNbOfGeometricElementsToDeform,
  CATGeometry **iGeometricElementsToDeform,
  CATSkillValue iMode = BASIC)
{
  return CATPGMCreateGlobalDeformation(ifactory, iStartParametrisationSurface, iTargetParametrisationSurface, iNbOfGuidingSurfaces, iGuidingSurfaces, iNbOfGeometricElementsToDeform, iGeometricElementsToDeform, iMode);
}

//-----------------------------------------------------------------------------
//Deformation defined by two parametric surfaces with Guiding  surfaces 
//-----------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATGlobalDeformation *CATPGMCreateGlobalDeformation(
  CATGeoFactory *ifactory,
  CATNurbsSurface *iStartParametrisationSurface,
  CATNurbsSurface *iTargetParametrisationSurface,
  const CATLONG32 iNbOfGuidingSurfaces,
  CATNurbsSurface **iGuidingSurfaces,
  const CATLONG32 iNbOfGeometricElementsToDeform,
  CATGeometry **iGeometricElementsToDeform,
  const CATLONG32 iConstraintOnGuide,
  CATSkillValue iMode = BASIC);

inline CATGlobalDeformation *CreateGlobalDeformation(
  CATGeoFactory *ifactory,
  CATNurbsSurface *iStartParametrisationSurface,
  CATNurbsSurface *iTargetParametrisationSurface,
  const CATLONG32 iNbOfGuidingSurfaces,
  CATNurbsSurface **iGuidingSurfaces,
  const CATLONG32 iNbOfGeometricElementsToDeform,
  CATGeometry **iGeometricElementsToDeform,
  const CATLONG32 iConstraintOnGuide,
  CATSkillValue iMode = BASIC)
{
  return CATPGMCreateGlobalDeformation(ifactory, iStartParametrisationSurface, iTargetParametrisationSurface, iNbOfGuidingSurfaces, iGuidingSurfaces, iNbOfGeometricElementsToDeform, iGeometricElementsToDeform, iConstraintOnGuide, iMode);
}

//-----------------------------------------------------------------------------
//Deformation defined by curve and  surface
//-----------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATGlobalDeformation *CATPGMCreateGlobalDeformation(
  CATGeoFactory *ifactory,
  CATNurbsCurve *iStartParametrisationSpineCurve,
  CATNurbsSurface *iStartParametrisationSurface,
  CATNurbsCurve *iTargetParametrisationSpineCurve,
  CATNurbsSurface *iTargetParametrisationSurface,
  const CATLONG32 iNbOfGeometricElementsToDeform,
  CATGeometry **iGeometricElementsToDeform,
  CATSkillValue iMode = BASIC);

inline CATGlobalDeformation *CreateGlobalDeformation(
  CATGeoFactory *ifactory,
  CATNurbsCurve *iStartParametrisationSpineCurve,
  CATNurbsSurface *iStartParametrisationSurface,
  CATNurbsCurve *iTargetParametrisationSpineCurve,
  CATNurbsSurface *iTargetParametrisationSurface,
  const CATLONG32 iNbOfGeometricElementsToDeform,
  CATGeometry **iGeometricElementsToDeform,
  CATSkillValue iMode = BASIC)
{
  return CATPGMCreateGlobalDeformation(ifactory, iStartParametrisationSpineCurve, iStartParametrisationSurface, iTargetParametrisationSpineCurve, iTargetParametrisationSurface, iNbOfGeometricElementsToDeform, iGeometricElementsToDeform, iMode);
}

//-----------------------------------------------------------------------------
//Deformation defined by curve and  surface  with Guiding  surfaces 
//-----------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATGlobalDeformation *CATPGMCreateGlobalDeformation(
  CATGeoFactory *ifactory,
  CATNurbsCurve *iStartParametrisationSpineCurve,
  CATNurbsSurface *iStartParametrisationSurface,
  CATNurbsCurve *iTargetParametrisationSpineCurve,
  CATNurbsSurface *iTargetParametrisationSurface,
  const CATLONG32 iNbOfGuidingSurfaces,
  CATNurbsSurface **iGuidingSurfaces,
  const CATLONG32 iNbOfGeometricElementsToDeform,
  CATGeometry **iGeometricElementsToDeform,
  CATSkillValue iMode = BASIC);

inline CATGlobalDeformation *CreateGlobalDeformation(
  CATGeoFactory *ifactory,
  CATNurbsCurve *iStartParametrisationSpineCurve,
  CATNurbsSurface *iStartParametrisationSurface,
  CATNurbsCurve *iTargetParametrisationSpineCurve,
  CATNurbsSurface *iTargetParametrisationSurface,
  const CATLONG32 iNbOfGuidingSurfaces,
  CATNurbsSurface **iGuidingSurfaces,
  const CATLONG32 iNbOfGeometricElementsToDeform,
  CATGeometry **iGeometricElementsToDeform,
  CATSkillValue iMode = BASIC)
{
  return CATPGMCreateGlobalDeformation(ifactory, iStartParametrisationSpineCurve, iStartParametrisationSurface, iTargetParametrisationSpineCurve, iTargetParametrisationSurface, iNbOfGuidingSurfaces, iGuidingSurfaces, iNbOfGeometricElementsToDeform, iGeometricElementsToDeform, iMode);
}

//-----------------------------------------------------------------------------
//Deformation defined by curve and  surface  with Guiding  surfaces 
//-----------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATGlobalDeformation *CATPGMCreateGlobalDeformation(
  CATGeoFactory *ifactory,
  CATNurbsCurve *iStartParametrisationSpineCurve,
  CATNurbsSurface *iStartParametrisationSurface,
  CATNurbsCurve *iTargetParametrisationSpineCurve,
  CATNurbsSurface *iTargetParametrisationSurface,
  const CATLONG32 iNbOfGuidingSurfaces,
  CATNurbsSurface **iGuidingSurfaces,
  const CATLONG32 iNbOfGeometricElementsToDeform,
  CATGeometry **iGeometricElementsToDeform,
  const CATLONG32 iConstraintOnGuide,
  CATSkillValue iMode = BASIC);

inline CATGlobalDeformation *CreateGlobalDeformation(
  CATGeoFactory *ifactory,
  CATNurbsCurve *iStartParametrisationSpineCurve,
  CATNurbsSurface *iStartParametrisationSurface,
  CATNurbsCurve *iTargetParametrisationSpineCurve,
  CATNurbsSurface *iTargetParametrisationSurface,
  const CATLONG32 iNbOfGuidingSurfaces,
  CATNurbsSurface **iGuidingSurfaces,
  const CATLONG32 iNbOfGeometricElementsToDeform,
  CATGeometry **iGeometricElementsToDeform,
  const CATLONG32 iConstraintOnGuide,
  CATSkillValue iMode = BASIC)
{
  return CATPGMCreateGlobalDeformation(ifactory, iStartParametrisationSpineCurve, iStartParametrisationSurface, iTargetParametrisationSpineCurve, iTargetParametrisationSurface, iNbOfGuidingSurfaces, iGuidingSurfaces, iNbOfGeometricElementsToDeform, iGeometricElementsToDeform, iConstraintOnGuide, iMode);
}

//-----------------------------------------------------------------------------
// Curve Wrap   
//-----------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATGlobalDeformation *CATPGMCreateGlobalDeformation(
  CATGeoFactory *iFactory,
  CATNurbsCurve *iStartParametrisationSpine,
  CATNurbsCurve *iStartProjDirectionCrv,
  const CATLONG32 iNbOfReferenceCrv,
  CATNurbsCurve **iStartReferenceCrv,
  CATNurbsCurve *iTargetParametrisationSpine,
  CATNurbsCurve *iTargetProjDirectionCrv,
  CATNurbsCurve **iTargetReferenceCrv,
  const CATLONG32 iNbOfGeometricObjectsToDeform,
  CATGeometry **iGeometricObjectsToDeform,
  CATSkillValue iMode);

inline CATGlobalDeformation *CreateGlobalDeformation(
  CATGeoFactory *iFactory,
  CATNurbsCurve *iStartParametrisationSpine,
  CATNurbsCurve *iStartProjDirectionCrv,
  const CATLONG32 iNbOfReferenceCrv,
  CATNurbsCurve **iStartReferenceCrv,
  CATNurbsCurve *iTargetParametrisationSpine,
  CATNurbsCurve *iTargetProjDirectionCrv,
  CATNurbsCurve **iTargetReferenceCrv,
  const CATLONG32 iNbOfGeometricObjectsToDeform,
  CATGeometry **iGeometricObjectsToDeform,
  CATSkillValue iMode)
{
  return CATPGMCreateGlobalDeformation(iFactory, iStartParametrisationSpine, iStartProjDirectionCrv, iNbOfReferenceCrv, iStartReferenceCrv, iTargetParametrisationSpine, iTargetProjDirectionCrv, iTargetReferenceCrv, iNbOfGeometricObjectsToDeform, iGeometricObjectsToDeform, iMode);
}

//-----------------------------------------------------------------------------
// Curve Wrap  with Guids 
//-----------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATGlobalDeformation *CATPGMCreateGlobalDeformation(
  CATGeoFactory *iFactory,
  CATNurbsCurve *iStartParametrisationSpine,
  CATNurbsCurve *iStartProjDirectionCrv,
  const CATLONG32 iNbOfReferenceCrv,
  CATNurbsCurve **iStartReferenceCrv,
  CATNurbsCurve *iTargetParametrisationSpine,
  CATNurbsCurve *iTargetProjDirectionCrv,
  CATNurbsCurve **iTargetReferenceCrv,
  const CATLONG32 iNbOfAdjustmentSurfaces,
  CATNurbsSurface **iAdjustmentSurfaces,
  const CATLONG32 iNbOfGeometricObjectsToDeform,
  CATGeometry **iGeometricObjectsToDeform,
  CATSkillValue iMode);

inline CATGlobalDeformation *CreateGlobalDeformation(
  CATGeoFactory *iFactory,
  CATNurbsCurve *iStartParametrisationSpine,
  CATNurbsCurve *iStartProjDirectionCrv,
  const CATLONG32 iNbOfReferenceCrv,
  CATNurbsCurve **iStartReferenceCrv,
  CATNurbsCurve *iTargetParametrisationSpine,
  CATNurbsCurve *iTargetProjDirectionCrv,
  CATNurbsCurve **iTargetReferenceCrv,
  const CATLONG32 iNbOfAdjustmentSurfaces,
  CATNurbsSurface **iAdjustmentSurfaces,
  const CATLONG32 iNbOfGeometricObjectsToDeform,
  CATGeometry **iGeometricObjectsToDeform,
  CATSkillValue iMode)
{
  return CATPGMCreateGlobalDeformation(iFactory, iStartParametrisationSpine, iStartProjDirectionCrv, iNbOfReferenceCrv, iStartReferenceCrv, iTargetParametrisationSpine, iTargetProjDirectionCrv, iTargetReferenceCrv, iNbOfAdjustmentSurfaces, iAdjustmentSurfaces, iNbOfGeometricObjectsToDeform, iGeometricObjectsToDeform, iMode);
}

//-----------------------------------------------------------------------------
// Curve Wrap  with Guids & constraint on first guide
//-----------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATGlobalDeformation *CATPGMCreateGlobalDeformation(
  CATGeoFactory *iFactory,
  CATNurbsCurve *iStartParametrisationSpine,
  CATNurbsCurve *iStartProjDirectionCrv,
  const CATLONG32 iNbOfReferenceCrv,
  CATNurbsCurve **iStartReferenceCrv,
  CATNurbsCurve *iTargetParametrisationSpine,
  CATNurbsCurve *iTargetProjDirectionCrv,
  CATNurbsCurve **iTargetReferenceCrv,
  const CATLONG32 iNbOfAdjustmentSurfaces,
  CATNurbsSurface **iAdjustmentSurfaces,
  const CATLONG32 iNbOfGeometricObjectsToDeform,
  CATGeometry **iGeometricObjectsToDeform,
  const CATLONG32 iConstraintOnGuide,
  CATSkillValue iMode);

inline CATGlobalDeformation *CreateGlobalDeformation(
  CATGeoFactory *iFactory,
  CATNurbsCurve *iStartParametrisationSpine,
  CATNurbsCurve *iStartProjDirectionCrv,
  const CATLONG32 iNbOfReferenceCrv,
  CATNurbsCurve **iStartReferenceCrv,
  CATNurbsCurve *iTargetParametrisationSpine,
  CATNurbsCurve *iTargetProjDirectionCrv,
  CATNurbsCurve **iTargetReferenceCrv,
  const CATLONG32 iNbOfAdjustmentSurfaces,
  CATNurbsSurface **iAdjustmentSurfaces,
  const CATLONG32 iNbOfGeometricObjectsToDeform,
  CATGeometry **iGeometricObjectsToDeform,
  const CATLONG32 iConstraintOnGuide,
  CATSkillValue iMode)
{
  return CATPGMCreateGlobalDeformation(iFactory, iStartParametrisationSpine, iStartProjDirectionCrv, iNbOfReferenceCrv, iStartReferenceCrv, iTargetParametrisationSpine, iTargetProjDirectionCrv, iTargetReferenceCrv, iNbOfAdjustmentSurfaces, iAdjustmentSurfaces, iNbOfGeometricObjectsToDeform, iGeometricObjectsToDeform, iConstraintOnGuide, iMode);
}

//****************Temporary solution to handle the fact that **CATNurbsSurface
//is not recognised as **GATGeometry: *****************************************
//-----------------------------------------------------------------------------
//Cartesian deformation: StartAxis and TargetAxis define a linear transformation
//-----------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATGlobalDeformation *CATPGMCreateGlobalDeformation(
  CATGeoFactory *ifactory,
  CATMathAxis *iStartAxis,
  CATMathAxis *iTargetAxis,
  const CATLONG32 iNbOfGeometricElementsToMove,
  CATNurbsSurface **iGeometricElementsToMove,
  CATSkillValue iMode = BASIC);

inline CATGlobalDeformation *CreateGlobalDeformation(
  CATGeoFactory *ifactory,
  CATMathAxis *iStartAxis,
  CATMathAxis *iTargetAxis,
  const CATLONG32 iNbOfGeometricElementsToMove,
  CATNurbsSurface **iGeometricElementsToMove,
  CATSkillValue iMode = BASIC)
{
  return CATPGMCreateGlobalDeformation(ifactory, iStartAxis, iTargetAxis, iNbOfGeometricElementsToMove, iGeometricElementsToMove, iMode);
}

//-----------------------------------------------------------------------------
//Cartesian deformation with adjustment surface(s) . The linear transformation
//first define by  StartAxis and TargetAxis is modified by guiding constraints.  
//-----------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATGlobalDeformation *CATPGMCreateGlobalDeformation(
  CATGeoFactory *ifactory,
  CATMathAxis *iStartAxis,
  CATMathAxis *iTargetAxis,
  const CATLONG32 iNbOfGuidingSurfaces,
  CATNurbsSurface **iGuidingSurfaces,
  const CATLONG32 iNbOfGeometricElementsToMove,
  CATNurbsSurface **iGeometricElementsToMove,
  CATSkillValue iMode = BASIC);

inline CATGlobalDeformation *CreateGlobalDeformation(
  CATGeoFactory *ifactory,
  CATMathAxis *iStartAxis,
  CATMathAxis *iTargetAxis,
  const CATLONG32 iNbOfGuidingSurfaces,
  CATNurbsSurface **iGuidingSurfaces,
  const CATLONG32 iNbOfGeometricElementsToMove,
  CATNurbsSurface **iGeometricElementsToMove,
  CATSkillValue iMode = BASIC)
{
  return CATPGMCreateGlobalDeformation(ifactory, iStartAxis, iTargetAxis, iNbOfGuidingSurfaces, iGuidingSurfaces, iNbOfGeometricElementsToMove, iGeometricElementsToMove, iMode);
}

//-----------------------------------------------------------------------------
//Cartesian deformation with adjustment surface(s) . The linear transformation
//first define by  StartAxis and TargetAxis is modified by guiding constraints.  
//-----------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATGlobalDeformation *CATPGMCreateGlobalDeformation(
  CATGeoFactory *ifactory,
  CATMathAxis *iStartAxis,
  CATMathAxis *iTargetAxis,
  const CATLONG32 iNbOfGuidingSurfaces,
  CATNurbsSurface **iGuidingSurfaces,
  const CATLONG32 iNbOfGeometricElementsToMove,
  CATNurbsSurface **iGeometricElementsToMove,
  const CATLONG32 iConstraintOnGuide,
  CATSkillValue iMode = BASIC);

inline CATGlobalDeformation *CreateGlobalDeformation(
  CATGeoFactory *ifactory,
  CATMathAxis *iStartAxis,
  CATMathAxis *iTargetAxis,
  const CATLONG32 iNbOfGuidingSurfaces,
  CATNurbsSurface **iGuidingSurfaces,
  const CATLONG32 iNbOfGeometricElementsToMove,
  CATNurbsSurface **iGeometricElementsToMove,
  const CATLONG32 iConstraintOnGuide,
  CATSkillValue iMode = BASIC)
{
  return CATPGMCreateGlobalDeformation(ifactory, iStartAxis, iTargetAxis, iNbOfGuidingSurfaces, iGuidingSurfaces, iNbOfGeometricElementsToMove, iGeometricElementsToMove, iConstraintOnGuide, iMode);
}

//-----------------------------------------------------------------------------
//Deformation defined by two parametric surfaces
//-----------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATGlobalDeformation *CATPGMCreateGlobalDeformation(
  CATGeoFactory *ifactory,
  CATNurbsSurface *iStartParametrisationSurface,
  CATNurbsSurface *iTargetParametrisationSurface,
  const CATLONG32 iNbOfGeometricElementsToDeform,
  CATNurbsSurface **iGeometricElementsToDeform,
  CATSkillValue iMode = BASIC);

inline CATGlobalDeformation *CreateGlobalDeformation(
  CATGeoFactory *ifactory,
  CATNurbsSurface *iStartParametrisationSurface,
  CATNurbsSurface *iTargetParametrisationSurface,
  const CATLONG32 iNbOfGeometricElementsToDeform,
  CATNurbsSurface **iGeometricElementsToDeform,
  CATSkillValue iMode = BASIC)
{
  return CATPGMCreateGlobalDeformation(ifactory, iStartParametrisationSurface, iTargetParametrisationSurface, iNbOfGeometricElementsToDeform, iGeometricElementsToDeform, iMode);
}

//-----------------------------------------------------------------------------
//Deformation defined by two parametric surfaces with Guiding  surfaces 
//-----------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATGlobalDeformation *CATPGMCreateGlobalDeformation(
  CATGeoFactory *ifactory,
  CATNurbsSurface *iStartParametrisationSurface,
  CATNurbsSurface *iTargetParametrisationSurface,
  const CATLONG32 iNbOfGuidingSurfaces,
  CATNurbsSurface **iGuidingSurfaces,
  const CATLONG32 iNbOfGeometricElementsToDeform,
  CATNurbsSurface **iGeometricElementsToDeform,
  CATSkillValue iMode = BASIC);

inline CATGlobalDeformation *CreateGlobalDeformation(
  CATGeoFactory *ifactory,
  CATNurbsSurface *iStartParametrisationSurface,
  CATNurbsSurface *iTargetParametrisationSurface,
  const CATLONG32 iNbOfGuidingSurfaces,
  CATNurbsSurface **iGuidingSurfaces,
  const CATLONG32 iNbOfGeometricElementsToDeform,
  CATNurbsSurface **iGeometricElementsToDeform,
  CATSkillValue iMode = BASIC)
{
  return CATPGMCreateGlobalDeformation(ifactory, iStartParametrisationSurface, iTargetParametrisationSurface, iNbOfGuidingSurfaces, iGuidingSurfaces, iNbOfGeometricElementsToDeform, iGeometricElementsToDeform, iMode);
}

//-----------------------------------------------------------------------------
//Deformation defined by two parametric surfaces with Guiding  surfaces 
//-----------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATGlobalDeformation *CATPGMCreateGlobalDeformation(
  CATGeoFactory *ifactory,
  CATNurbsSurface *iStartParametrisationSurface,
  CATNurbsSurface *iTargetParametrisationSurface,
  const CATLONG32 iNbOfGuidingSurfaces,
  CATNurbsSurface **iGuidingSurfaces,
  const CATLONG32 iNbOfGeometricElementsToDeform,
  CATNurbsSurface **iGeometricElementsToDeform,
  const CATLONG32 iConstraintOnGuide,
  CATSkillValue iMode = BASIC);

inline CATGlobalDeformation *CreateGlobalDeformation(
  CATGeoFactory *ifactory,
  CATNurbsSurface *iStartParametrisationSurface,
  CATNurbsSurface *iTargetParametrisationSurface,
  const CATLONG32 iNbOfGuidingSurfaces,
  CATNurbsSurface **iGuidingSurfaces,
  const CATLONG32 iNbOfGeometricElementsToDeform,
  CATNurbsSurface **iGeometricElementsToDeform,
  const CATLONG32 iConstraintOnGuide,
  CATSkillValue iMode = BASIC)
{
  return CATPGMCreateGlobalDeformation(ifactory, iStartParametrisationSurface, iTargetParametrisationSurface, iNbOfGuidingSurfaces, iGuidingSurfaces, iNbOfGeometricElementsToDeform, iGeometricElementsToDeform, iConstraintOnGuide, iMode);
}

//-----------------------------------------------------------------------------
//Deformation defined by curve and  surface
//-----------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATGlobalDeformation *CATPGMCreateGlobalDeformation(
  CATGeoFactory *ifactory,
  CATNurbsCurve *iStartParametrisationSpineCurve,
  CATNurbsSurface *iStartParametrisationSurface,
  CATNurbsCurve *iTargetParametrisationSpineCurve,
  CATNurbsSurface *iTargetParametrisationSurface,
  const CATLONG32 iNbOfGeometricElementsToDeform,
  CATNurbsSurface **iGeometricElementsToDeform,
  CATSkillValue iMode = BASIC);

inline CATGlobalDeformation *CreateGlobalDeformation(
  CATGeoFactory *ifactory,
  CATNurbsCurve *iStartParametrisationSpineCurve,
  CATNurbsSurface *iStartParametrisationSurface,
  CATNurbsCurve *iTargetParametrisationSpineCurve,
  CATNurbsSurface *iTargetParametrisationSurface,
  const CATLONG32 iNbOfGeometricElementsToDeform,
  CATNurbsSurface **iGeometricElementsToDeform,
  CATSkillValue iMode = BASIC)
{
  return CATPGMCreateGlobalDeformation(ifactory, iStartParametrisationSpineCurve, iStartParametrisationSurface, iTargetParametrisationSpineCurve, iTargetParametrisationSurface, iNbOfGeometricElementsToDeform, iGeometricElementsToDeform, iMode);
}

//-----------------------------------------------------------------------------
//Deformation defined by curve and  surface  with Guiding  surfaces 
//-----------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATGlobalDeformation *CATPGMCreateGlobalDeformation(
  CATGeoFactory *ifactory,
  CATNurbsCurve *iStartParametrisationSpineCurve,
  CATNurbsSurface *iStartParametrisationSurface,
  CATNurbsCurve *iTargetParametrisationSpineCurve,
  CATNurbsSurface *iTargetParametrisationSurface,
  const CATLONG32 iNbOfGuidingSurfaces,
  CATNurbsSurface **iGuidingSurfaces,
  const CATLONG32 iNbOfGeometricElementsToDeform,
  CATNurbsSurface **iGeometricElementsToDeform,
  CATSkillValue iMode = BASIC);

inline CATGlobalDeformation *CreateGlobalDeformation(
  CATGeoFactory *ifactory,
  CATNurbsCurve *iStartParametrisationSpineCurve,
  CATNurbsSurface *iStartParametrisationSurface,
  CATNurbsCurve *iTargetParametrisationSpineCurve,
  CATNurbsSurface *iTargetParametrisationSurface,
  const CATLONG32 iNbOfGuidingSurfaces,
  CATNurbsSurface **iGuidingSurfaces,
  const CATLONG32 iNbOfGeometricElementsToDeform,
  CATNurbsSurface **iGeometricElementsToDeform,
  CATSkillValue iMode = BASIC)
{
  return CATPGMCreateGlobalDeformation(ifactory, iStartParametrisationSpineCurve, iStartParametrisationSurface, iTargetParametrisationSpineCurve, iTargetParametrisationSurface, iNbOfGuidingSurfaces, iGuidingSurfaces, iNbOfGeometricElementsToDeform, iGeometricElementsToDeform, iMode);
}

//-----------------------------------------------------------------------------
//Deformation defined by curve and  surface  with Guiding  surfaces 
//-----------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATGlobalDeformation *CATPGMCreateGlobalDeformation(
  CATGeoFactory *ifactory,
  CATNurbsCurve *iStartParametrisationSpineCurve,
  CATNurbsSurface *iStartParametrisationSurface,
  CATNurbsCurve *iTargetParametrisationSpineCurve,
  CATNurbsSurface *iTargetParametrisationSurface,
  const CATLONG32 iNbOfGuidingSurfaces,
  CATNurbsSurface **iGuidingSurfaces,
  const CATLONG32 iNbOfGeometricElementsToDeform,
  CATNurbsSurface **iGeometricElementsToDeform,
  const CATLONG32 iConstraintOnGuide,
  CATSkillValue iMode = BASIC);

inline CATGlobalDeformation *CreateGlobalDeformation(
  CATGeoFactory *ifactory,
  CATNurbsCurve *iStartParametrisationSpineCurve,
  CATNurbsSurface *iStartParametrisationSurface,
  CATNurbsCurve *iTargetParametrisationSpineCurve,
  CATNurbsSurface *iTargetParametrisationSurface,
  const CATLONG32 iNbOfGuidingSurfaces,
  CATNurbsSurface **iGuidingSurfaces,
  const CATLONG32 iNbOfGeometricElementsToDeform,
  CATNurbsSurface **iGeometricElementsToDeform,
  const CATLONG32 iConstraintOnGuide,
  CATSkillValue iMode = BASIC)
{
  return CATPGMCreateGlobalDeformation(ifactory, iStartParametrisationSpineCurve, iStartParametrisationSurface, iTargetParametrisationSpineCurve, iTargetParametrisationSurface, iNbOfGuidingSurfaces, iGuidingSurfaces, iNbOfGeometricElementsToDeform, iGeometricElementsToDeform, iConstraintOnGuide, iMode);
}

//-----------------------------------------------------------------------------
// Curve Wrap   
//-----------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATGlobalDeformation *CATPGMCreateGlobalDeformation(
  CATGeoFactory *iFactory,
  CATNurbsCurve *iStartParametrisationSpine,
  CATNurbsCurve *iStartProjDirectionCrv,
  const CATLONG32 iNbOfReferenceCrv,
  CATNurbsCurve **iStartReferenceCrv,
  CATNurbsCurve *iTargetParametrisationSpine,
  CATNurbsCurve *iTargetProjDirectionCrv,
  CATNurbsCurve **iTargetReferenceCrv,
  const CATLONG32 iNbOfGeometricObjectsToDeform,
  CATNurbsSurface **iGeometricObjectsToDeform,
  CATSkillValue iMode);

inline CATGlobalDeformation *CreateGlobalDeformation(
  CATGeoFactory *iFactory,
  CATNurbsCurve *iStartParametrisationSpine,
  CATNurbsCurve *iStartProjDirectionCrv,
  const CATLONG32 iNbOfReferenceCrv,
  CATNurbsCurve **iStartReferenceCrv,
  CATNurbsCurve *iTargetParametrisationSpine,
  CATNurbsCurve *iTargetProjDirectionCrv,
  CATNurbsCurve **iTargetReferenceCrv,
  const CATLONG32 iNbOfGeometricObjectsToDeform,
  CATNurbsSurface **iGeometricObjectsToDeform,
  CATSkillValue iMode)
{
  return CATPGMCreateGlobalDeformation(iFactory, iStartParametrisationSpine, iStartProjDirectionCrv, iNbOfReferenceCrv, iStartReferenceCrv, iTargetParametrisationSpine, iTargetProjDirectionCrv, iTargetReferenceCrv, iNbOfGeometricObjectsToDeform, iGeometricObjectsToDeform, iMode);
}

//-----------------------------------------------------------------------------
// Curve Wrap  with Guids 
//-----------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATGlobalDeformation *CATPGMCreateGlobalDeformation(
  CATGeoFactory *iFactory,
  CATNurbsCurve *iStartParametrisationSpine,
  CATNurbsCurve *iStartProjDirectionCrv,
  const CATLONG32 iNbOfReferenceCrv,
  CATNurbsCurve **iStartReferenceCrv,
  CATNurbsCurve *iTargetParametrisationSpine,
  CATNurbsCurve *iTargetProjDirectionCrv,
  CATNurbsCurve **iTargetReferenceCrv,
  const CATLONG32 iNbOfAdjustmentSurfaces,
  CATNurbsSurface **iAdjustmentSurfaces,
  const CATLONG32 iNbOfGeometricObjectsToDeform,
  CATNurbsSurface **iGeometricObjectsToDeform,
  CATSkillValue iMode);

inline CATGlobalDeformation *CreateGlobalDeformation(
  CATGeoFactory *iFactory,
  CATNurbsCurve *iStartParametrisationSpine,
  CATNurbsCurve *iStartProjDirectionCrv,
  const CATLONG32 iNbOfReferenceCrv,
  CATNurbsCurve **iStartReferenceCrv,
  CATNurbsCurve *iTargetParametrisationSpine,
  CATNurbsCurve *iTargetProjDirectionCrv,
  CATNurbsCurve **iTargetReferenceCrv,
  const CATLONG32 iNbOfAdjustmentSurfaces,
  CATNurbsSurface **iAdjustmentSurfaces,
  const CATLONG32 iNbOfGeometricObjectsToDeform,
  CATNurbsSurface **iGeometricObjectsToDeform,
  CATSkillValue iMode)
{
  return CATPGMCreateGlobalDeformation(iFactory, iStartParametrisationSpine, iStartProjDirectionCrv, iNbOfReferenceCrv, iStartReferenceCrv, iTargetParametrisationSpine, iTargetProjDirectionCrv, iTargetReferenceCrv, iNbOfAdjustmentSurfaces, iAdjustmentSurfaces, iNbOfGeometricObjectsToDeform, iGeometricObjectsToDeform, iMode);
}

//-----------------------------------------------------------------------------
// Curve Wrap  with Guids & constraint on first guide
//-----------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATGlobalDeformation *CATPGMCreateGlobalDeformation(
  CATGeoFactory *iFactory,
  CATNurbsCurve *iStartParametrisationSpine,
  CATNurbsCurve *iStartProjDirectionCrv,
  const CATLONG32 iNbOfReferenceCrv,
  CATNurbsCurve **iStartReferenceCrv,
  CATNurbsCurve *iTargetParametrisationSpine,
  CATNurbsCurve *iTargetProjDirectionCrv,
  CATNurbsCurve **iTargetReferenceCrv,
  const CATLONG32 iNbOfAdjustmentSurfaces,
  CATNurbsSurface **iAdjustmentSurfaces,
  const CATLONG32 iNbOfGeometricObjectsToDeform,
  CATNurbsSurface **iGeometricObjectsToDeform,
  const CATLONG32 iConstraintOnGuide,
  CATSkillValue iMode);

inline CATGlobalDeformation *CreateGlobalDeformation(
  CATGeoFactory *iFactory,
  CATNurbsCurve *iStartParametrisationSpine,
  CATNurbsCurve *iStartProjDirectionCrv,
  const CATLONG32 iNbOfReferenceCrv,
  CATNurbsCurve **iStartReferenceCrv,
  CATNurbsCurve *iTargetParametrisationSpine,
  CATNurbsCurve *iTargetProjDirectionCrv,
  CATNurbsCurve **iTargetReferenceCrv,
  const CATLONG32 iNbOfAdjustmentSurfaces,
  CATNurbsSurface **iAdjustmentSurfaces,
  const CATLONG32 iNbOfGeometricObjectsToDeform,
  CATNurbsSurface **iGeometricObjectsToDeform,
  const CATLONG32 iConstraintOnGuide,
  CATSkillValue iMode)
{
  return CATPGMCreateGlobalDeformation(iFactory, iStartParametrisationSpine, iStartProjDirectionCrv, iNbOfReferenceCrv, iStartReferenceCrv, iTargetParametrisationSpine, iTargetProjDirectionCrv, iTargetReferenceCrv, iNbOfAdjustmentSurfaces, iAdjustmentSurfaces, iNbOfGeometricObjectsToDeform, iGeometricObjectsToDeform, iConstraintOnGuide, iMode);
}

ExportedByCATGMOperatorsInterfaces
void Remove( CATGlobalDeformation *&ioCATGlobalDeformation ) ;

#endif /* CATPGMCreateGlobalDeformation_h_ */
