#ifndef CATIPGMConnectToolImpl_h_
#define CATIPGMConnectToolImpl_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATIPGMConnectTool.h"
#include "CATCGMItfImplMacrosDefine.h"
#include "CATGeometricOperators.h"

#define CATCGM_ITF_CONCRETE_CLASS           CATConnectTool
#define CATCGM_ITF_CONCRETE_METACLASS       CATConnectTool_MetaClass

#define CATCGM_ITF_CLASS                    CATIPGMConnectTool
#define CATCGM_ITF_METACLASS                CATIPGMConnectTool_MetaClass
#define CATCGM_ITF_CLASS_IID                IID_CATIPGMConnectTool

#define CATCGM_ITF_IMPL_CLASS               CATIPGMConnectToolImpl
#define CATCGM_ITF_PARENT_ITF_METACLASS     CATIPGMOperatorImpl::CATIPGMOperator_MetaClass
#define CATCGM_ITF_EXPORTED_BY              ExportedByCATGeometricOperators

#include "CATCGMItfImplDeclareBegin.h"
#include "CATIPGMConnectToolImplDeclare.h"
#include "CATCGMItfImplDeclareEnd.h"

#endif
