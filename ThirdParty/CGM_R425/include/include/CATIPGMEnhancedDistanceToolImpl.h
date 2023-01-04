#ifndef CATIPGMEnhancedDistanceToolImpl_h_
#define CATIPGMEnhancedDistanceToolImpl_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATIPGMEnhancedDistanceTool.h"
#include "CATCGMItfImplMacrosDefine.h"
#include "CATGeometricOperators.h"

#define CATCGM_ITF_CONCRETE_CLASS           CATEnhancedDistanceTool
#define CATCGM_ITF_CONCRETE_METACLASS       CATEnhancedDistanceTool_MetaClass

#define CATCGM_ITF_CLASS                    CATIPGMEnhancedDistanceTool
#define CATCGM_ITF_METACLASS                CATIPGMEnhancedDistanceTool_MetaClass
#define CATCGM_ITF_CLASS_IID                IID_CATIPGMEnhancedDistanceTool

#define CATCGM_ITF_IMPL_CLASS               CATIPGMEnhancedDistanceToolImpl
#define CATCGM_ITF_PARENT_ITF_METACLASS     CATIPGMDistanceToolImpl::CATIPGMDistanceTool_MetaClass
#define CATCGM_ITF_EXPORTED_BY              ExportedByCATGeometricOperators

#include "CATCGMItfImplDeclareBegin.h"
#include "CATIPGMEnhancedDistanceToolImplDeclare.h"
#include "CATCGMItfImplDeclareEnd.h"

#endif
