/* -*-c++-*- */
#ifndef ListPOfCATTopData_h
#define ListPOfCATTopData_h

#include "PersistentCell.h"

#include "CATLISTPP_Clean.h"
#define CATLISTPP_RemoveAll
#include "CATLISTPP_MinimumPublicInterface.h"
#define CATLISTPP_RemovePosition
#include "CATLISTPP_Declare.h"


class CATTopData;

#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByPersistentCell

CATLISTPP_DECLARE_TS( CATTopData ,10)
typedef CATLISTP(CATTopData) ListPOfCATTopData;


#endif
