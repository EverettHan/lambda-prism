/* -*-c++-*- */
#ifndef ListPOfCATManifoldParameter_h
#define ListPOfCATManifoldParameter_h

#include "CATGMModelInterfaces.h"

#include "CATLISTPP_Clean.h"
#define CATLISTPP_Append
#define CATLISTPP_AppendList
#define CATLISTPP_RemoveAll
#define CATLISTPP_Locate
#define CATLISTPP_RemovePosition
#define CATLISTPP_RemoveNulls
#include "CATLISTPP_Declare.h"

class CATManifoldParameter;

#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByCATGMModelInterfaces

CATLISTPP_DECLARE_TS( CATManifoldParameter ,10);
typedef CATLISTP(CATManifoldParameter) ListPOfCATManifoldParameter;


#endif

