/* -*-c++-*- */
#ifndef ListPOfCATCGMChain_h
#define ListPOfCATCGMChain_h

#include "CATCGMChain.h"

#include "CATCGMLISTPP_Declare.h"

CATCGMLISTPP_DECLARE(CATCGMChain);

typedef CATLISTP(CATCGMChain) ListPOfCATCGMChain;


ExportedByCATTopologicalObjects void GetAllActiveCATCGMChain (ListPOfCATCGMChain * chains);
ExportedByCATTopologicalObjects void ResetAllActiveCATCGMChain();
ExportedByCATTopologicalObjects void RemoveActiveCATCGMChain(CATCGMChain * ichain);

#endif
