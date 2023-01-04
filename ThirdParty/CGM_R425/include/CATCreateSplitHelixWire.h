// COPYRIGHT DASSAULT SYSTEMES 2006
//=============================================================================
//
// Methode permettant la creation d'une instance de l'operateur de split
// d'un body contenant un unique wire pose sur une courbe helice (iBodyToSplit).
//=============================================================================

#ifndef __CATCreateSplitHelixWire_h__ 
#define __CATCreateSplitHelixWire_h__ 

#include "ExportedByCATTopologicalObjects.h"

class CATTopSplitHelixWire;
class CATGeoFactory;
class CATTopData;
class CATBody;

//--------------------------------------------------------------------------
//
// Methode: CATCreateSplitHelixWire
//
//--------------------------------------------------------------------------

ExportedByCATTopologicalObjects CATTopSplitHelixWire*
CATCreateSplitHelixWire(CATGeoFactory * iFactory, 
                        CATTopData    * iTopData, 
                        CATBody       * iWorkingBody,
                        CATBody       * iBodyToSplit);


#endif
