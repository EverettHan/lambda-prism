//=============================================================================
// COPYRIGHT Dassault Systemes 2009
//=============================================================================
//
// ListVOfCATTessParamToken
//
//=============================================================================
// 2009-07-29 MPX: New
//=============================================================================
#ifndef ListVOfCATTessParamToken_H
#define ListVOfCATTessParamToken_H

#include "TessCacheObjects.h"
#include "CATTessParamToken.h"

#include "CATLISTV_Clean.h"
#define CATLISTV_Append
#define CATLISTV_AppendList
#define CATLISTV_RemoveAll
#define CATLISTV_RemoveDuplicatesCount
#define CATLISTV_Locate
#include "CATLISTV_Declare.h"

#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByTessCacheObjects

CATLISTV_DECLARE(CATTessParamToken);
typedef CATListValCATTessParamToken ListVOfCATTessParamToken;


#endif // !ListVOfCATTessParamToken_H

