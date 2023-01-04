// COPYRIGHT DASSAULT SYSTEMES  2021
#ifndef CATListPtrDynBoolSharedFaceData_h
#define CATListPtrDynBoolSharedFaceData_h

/* 
 * collection CATLISTP(CATDynBooleanSharedFaceData)
 */

class CATDynBooleanSharedFaceData;

#include "CATLISTPP_Clean.h"
#define CATLISTPP_Size
#define CATLISTPP_Append
//#define CATLISTPP_InsertAt
//#define CATLISTPP_Locate
//#define CATLISTPP_RemoveValue
#define CATLISTPP_RemovePosition
#define CATLISTPP_RemoveAll
#include "CATLISTPP_Declare.h"


#include "BOOLEAN.h"

#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByBOOLEAN

CATLISTPP_DECLARE_TNS(CATDynBooleanSharedFaceData, DynBoolSharedFaceData, 4)

#endif // CATListPtrDynBoolSharedFaceData_h
