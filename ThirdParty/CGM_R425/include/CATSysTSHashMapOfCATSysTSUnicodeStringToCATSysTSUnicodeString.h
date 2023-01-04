// CATSysTSHashMapOfCATSysTSUnicodeStringToCATSysTSUnicodeString.h

#ifndef __CATSysTSHashMapOfCATSysTSUnicodeStringToCATSysTSUnicodeString
#define __CATSysTSHashMapOfCATSysTSUnicodeStringToCATSysTSUnicodeString

#include "CATSysTS.h"
#include "CATSysTSUnicodeString.h"

#undef	ExportedBy
#define	ExportedBy ExportedByCATSysTS

#include "CATSysTSCtnrDeclInit.h"

#define CATSYSTS_CTNR                  CATSysTSHashMapOfCATSysTSUnicodeStringToCATSysTSUnicodeString

#define CATSYSTS_KEY                   CATSysTSUnicodeString
#define CATSYSTS_KEY_HAS_HASH_FUNC     1
#define CATSYSTS_KEY_HAS_GET_BIN_DUMP  0
#define CATSYSTS_KEY_IS_BUILT_IN_TYPE  1

#define CATSYSTS_VAL                   CATSysTSUnicodeString
#define CATSYSTS_VAL_HAS_COMPARE_OP    1
#define CATSYSTS_VAL_IS_PTR            0
#define CATSYSTS_VAL_IS_BUILT_IN_TYPE  1

#include "CATSysTSHashMap_Declare.h"

typedef  CATSysTSHashMapOfCATSysTSUnicodeStringToCATSysTSUnicodeString CATSysTSHashMapOfStrings;

#endif /* __CATSysTSHashMapOfCATSysTSUnicodeStringToCATSysTSUnicodeString */



