#ifndef CATLISTVALCATCRVPARAM_H
#define CATLISTVALCATCRVPARAM_H
//
// WQO Oct. 12 List of CATCrvParam
// U29 Nov. 14 Ajout du QuickSort
// WMN Jun. 16 Ajout RemovePosition et InsertAt
//
#include "ExportedByCATCGMGeoMath.h"
#include "CATCrvParam.h"

#include "CATLISTV_Clean.h"

#undef  CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByCATCGMGeoMath

#define CATLISTV_Append
#define CATLISTV_RemoveAll
#define CATLISTV_QuickSort 
#define CATLISTV_RemovePosition
#define CATLISTV_InsertAt

#include "CATLISTV_Declare.h"

CATLISTV_DECLARE(CATCrvParam);

#endif

