#ifndef __CATSysTSListOfVectorOfBYTE_H__
#define __CATSysTSListOfVectorOfBYTE_H__

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATSysTS.h"
#include "CATSysTSVectorOfBYTE.h"

#undef	ExportedBy
#define	ExportedBy ExportedByCATSysTS


#include "CATSysTSCtnrDeclInit.h"

#define CATSYSTS_CTNR                CATSysTSListOfVectorOfBYTE
#define CATSYSTS_EL_T                CATSysTSVectorOfBYTE
#define CATSYSTS_T_HAS_COMPARE_OP    1
#define CATSYSTS_T_HAS_LESS_OP       0
#define CATSYSTS_T_IS_PTR            0
#define CATSYSTS_T_IS_BUILT_IN_TYPE  0

#include "CATSysTSLinkedList_Declare.h"

#endif
