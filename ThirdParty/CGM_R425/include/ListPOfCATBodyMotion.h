#ifndef ListPOfCATBodyMotion_H
#define ListPOfCATBodyMotion_H

// COPYRIGHT DASSAULT SYSTEMES 2014

#include "CATGMModelInterfaces.h"

class CATBodyMotion;

#include "CATLISTP_Clean.h"
#define CATLISTP_Append
#define CATLISTP_RemoveAll
#include "CATLISTP_Declare.h"

#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByCATGMModelInterfaces

CATLISTP_DECLARE( CATBodyMotion );

#endif 

