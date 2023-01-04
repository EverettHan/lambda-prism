// CATSysTSListOfUnicodeString.h

#ifndef _CATSysTSListOfUnicodeString_h_
#define _CATSysTSListOfUnicodeString_h_


#include "CATSysTS.h"

#include "CATSysTSUnicodeString.h"


#undef	ExportedBy
#define	ExportedBy ExportedByCATSysTS


#include "CATSysTSCtnrDeclInit.h"

#define CATSYSTS_CTNR                CATSysTSListOfUnicodeString
#define CATSYSTS_EL_T                CATSysTSUnicodeString
#define CATSYSTS_T_HAS_COMPARE_OP    1
#define CATSYSTS_T_HAS_LESS_OP       0
#define CATSYSTS_T_IS_PTR            0
#define CATSYSTS_T_IS_BUILT_IN_TYPE  0

#include "CATSysTSLinkedList_Declare.h"


#endif
