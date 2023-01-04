#ifndef CATIPGMOperatorImpl_h_
#define CATIPGMOperatorImpl_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATIPGMOperator.h"
#include "CATCGMItfImplMacrosDefine.h"
#include "CATGeometricObjects.h"

#define CATCGM_ITF_CONCRETE_CLASS           CATCGMOperator
#define CATCGM_ITF_CONCRETE_METACLASS       CATCGMOperator_MetaClass

#define CATCGM_ITF_CLASS                    CATIPGMOperator
#define CATCGM_ITF_METACLASS                CATIPGMOperator_MetaClass
#define CATCGM_ITF_CLASS_IID                IID_CATIPGMOperator

#define CATCGM_ITF_IMPL_CLASS               CATIPGMOperatorImpl
#define CATCGM_ITF_PARENT_ITF_METACLASS     CATIPGMVirtualImpl::CATIPGMVirtual_MetaClass
#define CATCGM_ITF_EXPORTED_BY              ExportedByCATGeometricObjects

#include "CATCGMItfImplDeclareBegin.h"
#include "CATIPGMOperatorImplDeclare.h"
#include "CATCGMItfImplDeclareEnd.h"

#endif
