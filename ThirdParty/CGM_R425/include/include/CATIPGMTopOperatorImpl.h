#ifndef CATIPGMTopOperatorImpl_h_
#define CATIPGMTopOperatorImpl_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATIPGMTopOperator.h"
#include "CATCGMItfImplMacrosDefine.h"
#include "ExportedByCATTopologicalObjects.h"

#define CATCGM_ITF_CONCRETE_CLASS           CATTopOperator
#define CATCGM_ITF_CONCRETE_METACLASS       CATTopOperator_MetaClass

#define CATCGM_ITF_CLASS                    CATIPGMTopOperator
#define CATCGM_ITF_METACLASS                CATIPGMTopOperator_MetaClass
#define CATCGM_ITF_CLASS_IID                IID_CATIPGMTopOperator

#define CATCGM_ITF_IMPL_CLASS               CATIPGMTopOperatorImpl
#define CATCGM_ITF_PARENT_ITF_METACLASS     CATIPGMOperatorImpl::CATIPGMOperator_MetaClass
#define CATCGM_ITF_EXPORTED_BY              ExportedByCATTopologicalObjects

#include "CATCGMItfImplDeclareBegin.h"
#include "CATIPGMTopOperatorImplDeclare.h"
#include "CATCGMItfImplDeclareEnd.h"

#endif
