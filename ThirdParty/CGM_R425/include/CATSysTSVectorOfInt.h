// CATSysTSVectorOfInt.h

#ifndef _CATSysTSVectorOfInt_h_
#define _CATSysTSVectorOfInt_h_


#include "CATSysTS.h"


#undef	ExportedBy
#define	ExportedBy ExportedByCATSysTS


#include "CATSysTSCtnrDeclInit.h"

#define CATSYSTS_CTNR                CATSysTSVectorOfInt
#define CATSYSTS_EL_T                int
#define CATSYSTS_T_HAS_COMPARE_OP    1
#define CATSYSTS_T_HAS_LESS_OP       1
#define CATSYSTS_T_IS_PTR            0
#define CATSYSTS_T_IS_BUILT_IN_TYPE  1

#include "CATSysTSArrayList_Declare.h"


#endif



