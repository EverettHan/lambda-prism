/* -*-c++-*- */
#ifndef ListPOfCATDeclarativeManifoldAgent_h
#define ListPOfCATDeclarativeManifoldAgent_h

#include "PersistentCell.h"

#include "CATLISTPP_Clean.h"
#define CATLISTPP_RemoveValue
#define CATLISTPP_Locate
#define CATLISTPP_Append
#define CATLISTPP_AppendList
#define CATLISTPP_RemoveAll
#define CATLISTPP_RemovePosition
#define CATLISTPP_RemoveNulls
#define CATLISTPP_InsertAt
#include "CATLISTPP_Declare.h"

class CATDeclarativeManifoldAgent;

#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByPersistentCell

CATLISTPP_DECLARE_TS( CATDeclarativeManifoldAgent ,3)
typedef CATLISTP(CATDeclarativeManifoldAgent) ListPOfCATDeclarativeManifoldAgent;


#endif

