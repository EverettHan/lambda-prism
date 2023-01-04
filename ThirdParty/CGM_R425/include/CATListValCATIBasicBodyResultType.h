#ifndef CATLISTVALCATIBASICBODYRESULTTYPE_H
#define CATLISTVALCATIBASICBODYRESULTTYPE_H
//
// WQO Oct. 12 List of CATMathPoint
//
#include "CATGMOperatorsInterfaces.h"
#include "CATIBasicBodyFactory.h"

#include "CATLISTV_Clean.h"

#undef  CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByCATGMOperatorsInterfaces

#define CATLISTV_MinimalFunct
#undef CATLISTV_eqOP  
#undef CATLISTV_neOP  
#define CATLISTV_Append
#define CATLISTV_RemoveAll

#include "CATLISTV_Declare.h"

CATLISTV_DECLARE_TN(CATIBasicBodyFactory::CATIBasicBodyResultType, CATIBasicBodyResultType);

#endif

