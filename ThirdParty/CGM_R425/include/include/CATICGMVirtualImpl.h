#ifndef CATICGMVirtualImpl_h_
#define CATICGMVirtualImpl_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATICGMVirtual.h"
#include "CATCGMItfImplMacrosDefine.h"
#include "CATMathematics.h"

#define CATCGM_ITF_CONCRETE_CLASS           CATCGMVirtual
#define CATCGM_ITF_CONCRETE_METACLASS       CATCGMVirtual_MetaClass

#define CATCGM_ITF_CLASS                    CATICGMVirtual
#define CATCGM_ITF_METACLASS                CATICGMVirtual_MetaClass
#define CATCGM_ITF_CLASS_IID                IID_CATICGMVirtual

#define CATCGM_ITF_IMPL_CLASS               CATICGMVirtualImpl
#undef CATCGM_ITF_PARENT_ITF_METACLASS
#define CATCGM_ITF_EXPORTED_BY              ExportedByCATMathematics

#include "CATCGMItfImplDeclareBegin.h"
#include "CATICGMVirtualImplDeclare.h"
#include "CATCGMItfImplDeclareEnd.h"

#endif
