#ifndef CATIPGMRunnerOperatorImpl_h_
#define CATIPGMRunnerOperatorImpl_h_

// COPYRIGHT DASSAULT SYSTEMES 2010

#include "CATIPGMRunnerOperator.h"
#include "CATCGMItfImplMacrosDefine.h"

#define CATCGM_ITF_CONCRETE_CLASS           CATTopOperator
#define CATCGM_ITF_CONCRETE_METACLASS       CATTopOperator_MetaClass

#define CATCGM_ITF_CLASS                    CATIPGMRunnerOperator
#define CATCGM_ITF_METACLASS                CATIPGMRunnerOperator_MetaClass
#define CATCGM_ITF_CLASS_IID                IID_CATIPGMRunnerOperator

#define CATCGM_ITF_IMPL_CLASS               CATIPGMRunnerOperatorImpl
#define CATCGM_ITF_PARENT_ITF_METACLASS     CATIPGMVirtualImpl::CATIPGMVirtual_MetaClass
#define CATCGM_ITF_EXPORTED_BY

#include "CATCGMItfImplDeclareBegin.h"
#include "CATIPGMRunnerOperatorImplDeclare.h"
#include "CATCGMItfImplDeclareEnd.h"

#endif
