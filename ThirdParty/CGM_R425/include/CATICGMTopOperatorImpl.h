#ifndef CATICGMTopOperatorImpl_h_
#define CATICGMTopOperatorImpl_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATICGMTopOperator.h"
#include "CATCGMItfImplMacrosDefine.h"
#include "ExportedByCATTopologicalObjects.h"

#define CATCGM_ITF_CONCRETE_CLASS           CATTopOperator
#define CATCGM_ITF_CONCRETE_METACLASS       CATTopOperator_MetaClass

#define CATCGM_ITF_CLASS                    CATICGMTopOperator
#define CATCGM_ITF_METACLASS                CATICGMTopOperator_MetaClass
#define CATCGM_ITF_CLASS_IID                IID_CATICGMTopOperator

#define CATCGM_ITF_IMPL_CLASS               CATICGMTopOperatorImpl
#define CATCGM_ITF_PARENT_ITF_METACLASS     CATICGMOperatorImpl::CATICGMOperator_MetaClass
#define CATCGM_ITF_EXPORTED_BY              ExportedByCATTopologicalObjects

#include "CATCGMItfImplDeclareBegin.h"
#include "CATICGMTopOperatorImplDeclare.h"
#include "CATCGMItfImplDeclareEnd.h"

#endif
