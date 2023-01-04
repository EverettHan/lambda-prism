#ifndef CATIPGMGeoOperatorImpl_h_
#define CATIPGMGeoOperatorImpl_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATIPGMGeoOperator.h"
#include "CATCGMItfImplMacrosDefine.h"
#include "CATGeometricOperators.h"

#define CATCGM_ITF_CONCRETE_CLASS           CATGeoOperator
#define CATCGM_ITF_CONCRETE_METACLASS       CATGeoOperator_MetaClass

#define CATCGM_ITF_CLASS                    CATIPGMGeoOperator
#define CATCGM_ITF_METACLASS                CATIPGMGeoOperator_MetaClass
#define CATCGM_ITF_CLASS_IID                IID_CATIPGMGeoOperator

#define CATCGM_ITF_IMPL_CLASS               CATIPGMGeoOperatorImpl
#define CATCGM_ITF_PARENT_ITF_METACLASS     CATIPGMOperatorImpl::CATIPGMOperator_MetaClass
#define CATCGM_ITF_EXPORTED_BY              ExportedByCATGeometricOperators

#include "CATCGMItfImplDeclareBegin.h"
#include "CATIPGMGeoOperatorImplDeclare.h"
#include "CATCGMItfImplDeclareEnd.h"

#endif
