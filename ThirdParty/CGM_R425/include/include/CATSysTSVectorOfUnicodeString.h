// CATSysTSVectorOfUnicodeString.h

#ifndef _CATSysTSVectorOfUnicodeString_h_
#define _CATSysTSVectorOfUnicodeString_h_


#include "CATSysTS.h"
#include "CATSysTSUnicodeString.h"

#undef	ExportedBy
#define	ExportedBy ExportedByCATSysTS


#include "CATSysTSCtnrDeclInit.h"

#define CATSYSTS_CTNR                CATSysTSVectorOfUnicodeString
#define CATSYSTS_EL_T                CATSysTSUnicodeString
#define CATSYSTS_T_HAS_COMPARE_OP    1
#define CATSYSTS_T_HAS_LESS_OP       0
#define CATSYSTS_T_IS_PTR            0
#define CATSYSTS_T_IS_BUILT_IN_TYPE  0
#define CATSYSTS_T_HAS_CUSTOM_COMP_METH 1

#include "CATSysTSArrayList_Declare.h"


#endif



