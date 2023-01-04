#ifndef ListPOfCATListOfShort_H
#define ListPOfCATListOfShort_H

#include "CATGMModelInterfaces.h"
#include "CATLISTPP_Clean.h"
#define CATLISTPP_RemoveAll
#define CATLISTPP_AppendList
#define CATLISTPP_RemovePosition
#include "CATLISTPP_MinimumPublicInterface.h"
#include "CATLISTPP_Declare.h"

#include "CATListOfShort.h"

#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByCATGMModelInterfaces

CATLISTPP_DECLARE_TS(CATListOfShort, 3)
typedef CATLISTP(CATListOfShort) ListPOfCATListOfShort;

#endif
