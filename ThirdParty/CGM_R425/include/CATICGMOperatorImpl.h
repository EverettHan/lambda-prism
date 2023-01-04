#ifndef CATICGMOperatorImpl_h_
#define CATICGMOperatorImpl_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATICGMOperator.h"
#include "CATCGMItfImplMacrosDefine.h"
#include "CATGeometricObjects.h"

#define CATCGM_ITF_CONCRETE_CLASS           CATCGMOperator
#define CATCGM_ITF_CONCRETE_METACLASS       CATCGMOperator_MetaClass

#define CATCGM_ITF_CLASS                    CATICGMOperator
#define CATCGM_ITF_METACLASS                CATICGMOperator_MetaClass
#define CATCGM_ITF_CLASS_IID                IID_CATICGMOperator

#define CATCGM_ITF_IMPL_CLASS               CATICGMOperatorImpl
#define CATCGM_ITF_PARENT_ITF_METACLASS     CATICGMVirtualImpl::CATICGMVirtual_MetaClass
#define CATCGM_ITF_EXPORTED_BY              ExportedByCATGeometricObjects

#include "CATCGMItfImplDeclareBegin.h"
#include "CATICGMOperatorImplDeclare.h"
#include "CATCGMItfImplDeclareEnd.h"

#endif
