#ifndef CATICGMDistanceToolImpl_h_
#define CATICGMDistanceToolImpl_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATICGMDistanceTool.h"
#include "CATCGMItfImplMacrosDefine.h"
#include "CATGeometricOperators.h"

#define CATCGM_ITF_CONCRETE_CLASS           CATDistanceTool
#define CATCGM_ITF_CONCRETE_METACLASS       CATDistanceTool_MetaClass

#define CATCGM_ITF_CLASS                    CATICGMDistanceTool
#define CATCGM_ITF_METACLASS                CATICGMDistanceTool_MetaClass
#define CATCGM_ITF_CLASS_IID                IID_CATICGMDistanceTool

#define CATCGM_ITF_IMPL_CLASS               CATICGMDistanceToolImpl
#define CATCGM_ITF_PARENT_ITF_METACLASS     CATICGMVirtualImpl::CATICGMVirtual_MetaClass
#define CATCGM_ITF_EXPORTED_BY              ExportedByCATGeometricOperators

#include "CATCGMItfImplDeclareBegin.h"
#include "CATICGMDistanceToolImplDeclare.h"
#include "CATCGMItfImplDeclareEnd.h"

#endif
