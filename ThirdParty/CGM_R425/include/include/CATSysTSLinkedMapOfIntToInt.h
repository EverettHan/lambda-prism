// CATSysTSLinkedMapOfIntToInt.h

#ifndef _CATSysTSLinkedMapOfIntToInt_h_
#define _CATSysTSLinkedMapOfIntToInt_h_


#include "CATSysTS.h"


#undef	ExportedBy
#define	ExportedBy ExportedByCATSysTS


#include "CATSysTSCtnrDeclInit.h"

#define CATSYSTS_CTNR                  CATSysTSLinkedMapOfIntToInt

#define CATSYSTS_KEY                   int
#define CATSYSTS_KEY_HAS_HASH_FUNC     0
#define CATSYSTS_KEY_HAS_GET_BIN_DUMP  0
#define CATSYSTS_KEY_IS_BUILT_IN_TYPE  1

#define CATSYSTS_VAL                   int
#define CATSYSTS_VAL_HAS_COMPARE_OP    1
#define CATSYSTS_VAL_IS_PTR            0
#define CATSYSTS_VAL_IS_BUILT_IN_TYPE  1

#include "CATSysTSLinkedMap_Declare.h"


#endif


