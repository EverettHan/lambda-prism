#ifndef CATListOfCATCGMDbgPoseSurs_h
#define CATListOfCATCGMDbgPoseSurs_h

#include "CATCGMLISTPP_Declare.h"
#include "ExportedByCATTopologicalObjects.h"

class CATCGMDbgPoseSur;

CATCGMLISTPP_DECLARE(CATCGMDbgPoseSur);

/** @nodoc */
typedef CATLISTP(CATCGMDbgPoseSur) ListPOfCATCGMDbgPoseSur;

ExportedByCATTopologicalObjects int SortCATCGMDbgPoseSur(CATCGMDbgPoseSur *left, CATCGMDbgPoseSur *right);

class CATGeoFactory;
#include "ListPOfCATTopology.h"

// you must delete the CATCGMDbgPoseSur* created for output list ioPoseSur
ExportedByCATTopologicalObjects void CATCGMDbgPoseSurGet(CATGeoFactory         *iFactory, 
                                                         CATLISTP(CATCGMDbgPoseSur) &ioPoseSur);

// you must delete the CATCGMDbgPoseSur* created for output list ioPoseSur
ExportedByCATTopologicalObjects void CATCGMDbgPoseSurFilter(const CATLISTP(CATCGMDbgPoseSur) &iAll,
                                                            const CATLISTP(CATTopology)      &iContext,
                                                            CATLISTP(CATCGMDbgPoseSur)       &ioPoseSur);


#endif
