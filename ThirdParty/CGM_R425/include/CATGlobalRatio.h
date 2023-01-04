#ifndef CATGlobalRatio_h_
#define CATGlobalRatio_h_

/**
 * This header only exists in order to avoid compilation errors in client frameworks
 * (CATClassACoreResources, CATCompositesModel, CATCompositesServices, CATCompositesUI, CATDesignerModel,
 * CATDesignerResources, CATSmModel, CATSurfacicResources, FreeStyleAnalysisModel, FreeStyleAnalysisUI,
 * FreeStyleResources, FreeStyleShapeModel, FreeStyleShapeUI.tst, FreeStyleSketchResources, GSMModel,
 * MechanicalModeler, PartDesignUI).
 * Once these frameworks are migrated to CATPGMStaticGlobalRatio.h, the current header
 * must be deleted.
 */

#include "CATPGMStaticGlobalRatio.h"

class ExportedByCATGMModelInterfaces StaticGlobalRatio: public CATPGMStaticGlobalRatio
{
};

#endif // CATGlobalRatio_h_
