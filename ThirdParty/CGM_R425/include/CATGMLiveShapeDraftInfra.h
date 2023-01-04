#ifndef CATGMLiveShapeDraftInfra_h
#define CATGMLiveShapeDraftInfra_h
//
//// Resp: DSH1
//
#include "CATGMModelInterfaces.h"

ExportedByCATGMModelInterfaces int IsFilterAddRemove();
ExportedByCATGMModelInterfaces int CheckCylinderDeDraftCase();
ExportedByCATGMModelInterfaces int IsAddRemoveDraftWithContext2();
ExportedByCATGMModelInterfaces int IsDraftGroupingStopped();
ExportedByCATGMModelInterfaces int ReplaceSurfaceInGroups();
ExportedByCATGMModelInterfaces int IsForcedSkipRemoveDraft();
ExportedByCATGMModelInterfaces int AllowAddRemoveSimplify();
ExportedByCATGMModelInterfaces int ForceReplaceDraftSurfByGeomRep();
ExportedByCATGMModelInterfaces int ComplementaryDraftShell();
ExportedByCATGMModelInterfaces int CheckValidityDraft();
ExportedByCATGMModelInterfaces int DisableAddRemoveDraftEditPCSFix();

#endif

