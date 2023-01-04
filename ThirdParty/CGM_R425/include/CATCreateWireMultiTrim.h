// COPYRIGHT DASSAULT SYSTEMES 2002
//=============================================================================
//
// Methode permettant la creation d'une instance de l'operateur de trim
// de plusieurs bodies contenant chacun un unique wire (iBodiesToTrim).
//=============================================================================

#ifndef __CATCreateWireMultiTrim_h__ 
#define __CATCreateWireMultiTrim_h__ 

#include "ExportedByCATTopologicalObjects.h"

#include "ListPOfCATBody.h"

class CATTopWireMultiTrim;
class CATGeoFactory;
class CATTopData;
class CATBody;

//--------------------------------------------------------------------------
//
// Methode: CATCreateWireMultiTrim
//
//--------------------------------------------------------------------------

ExportedByCATTopologicalObjects CATTopWireMultiTrim *
CATCreateWireMultiTrim(CATGeoFactory     * iFactory, CATTopData* iTopData, 
                       CATBody           * iWorkingBody,
                       CATLISTP(CATBody) * iBodiesToTrim);


#endif
