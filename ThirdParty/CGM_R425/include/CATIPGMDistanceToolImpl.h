#ifndef CATIPGMDistanceToolImpl_h_
#define CATIPGMDistanceToolImpl_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATIPGMDistanceTool.h"
#include "CATCGMItfImplMacrosDefine.h"
#include "CATGeometricOperators.h"

#define CATCGM_ITF_CONCRETE_CLASS           CATDistanceTool
#define CATCGM_ITF_CONCRETE_METACLASS       CATDistanceTool_MetaClass

#define CATCGM_ITF_CLASS                    CATIPGMDistanceTool
#define CATCGM_ITF_METACLASS                CATIPGMDistanceTool_MetaClass
#define CATCGM_ITF_CLASS_IID                IID_CATIPGMDistanceTool

#define CATCGM_ITF_IMPL_CLASS               CATIPGMDistanceToolImpl
#define CATCGM_ITF_PARENT_ITF_METACLASS     CATIPGMVirtualImpl::CATIPGMVirtual_MetaClass
#define CATCGM_ITF_EXPORTED_BY              ExportedByCATGeometricOperators

#include "CATCGMItfImplDeclareBegin.h"
#include "CATIPGMDistanceToolImplDeclare.h"
#include "CATCGMItfImplDeclareEnd.h"

#endif
