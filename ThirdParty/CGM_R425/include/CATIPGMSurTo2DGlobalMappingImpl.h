#ifndef CATIPGMSurTo2DGlobalMappingImpl_h_
#define CATIPGMSurTo2DGlobalMappingImpl_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATIPGMSurTo2DGlobalMapping.h"
#include "CATCGMItfImplMacrosDefine.h"
#include "CATGeometricOperators.h"

#define CATCGM_ITF_CONCRETE_CLASS           CATSurTo2DGlobalMapping
#define CATCGM_ITF_CONCRETE_METACLASS       CATSurTo2DGlobalMapping_MetaClass

#define CATCGM_ITF_CLASS                    CATIPGMSurTo2DGlobalMapping
#define CATCGM_ITF_METACLASS                CATIPGMSurTo2DGlobalMapping_MetaClass
#define CATCGM_ITF_CLASS_IID                IID_CATIPGMSurTo2DGlobalMapping

#define CATCGM_ITF_IMPL_CLASS               CATIPGMSurTo2DGlobalMappingImpl
#define CATCGM_ITF_PARENT_ITF_METACLASS     CATIPGMOperatorImpl::CATIPGMOperator_MetaClass
#define CATCGM_ITF_EXPORTED_BY              ExportedByCATGeometricOperators

#include "CATCGMItfImplDeclareBegin.h"
#include "CATIPGMSurTo2DGlobalMappingImplDeclare.h"
#include "CATCGMItfImplDeclareEnd.h"

#endif
