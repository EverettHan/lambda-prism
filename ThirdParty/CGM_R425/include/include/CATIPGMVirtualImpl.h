/**
 * @fullReview CPT 06:07:19
 */
#ifndef CATIPGMVirtualImpl_h_
#define CATIPGMVirtualImpl_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATIPGMVirtual.h"
#include "CATCGMItfImplMacrosDefine.h"
#include "CATMathematics.h"

#define CATCGM_ITF_CONCRETE_CLASS           CATCGMVirtual
#define CATCGM_ITF_CONCRETE_METACLASS       CATCGMVirtual_MetaClass

#define CATCGM_ITF_CLASS                    CATIPGMVirtual
#define CATCGM_ITF_METACLASS                CATIPGMVirtual_MetaClass
#define CATCGM_ITF_CLASS_IID                IID_CATIPGMVirtual

#define CATCGM_ITF_IMPL_CLASS               CATIPGMVirtualImpl
#undef CATCGM_ITF_PARENT_ITF_METACLASS
#define CATCGM_ITF_EXPORTED_BY              ExportedByCATMathematics

#include "CATCGMItfImplDeclareBegin.h"
#include "CATIPGMVirtualImplDeclare.h"
#include "CATCGMItfImplDeclareEnd.h"

#endif
