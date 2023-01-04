// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
// Creation EDS  11/10/2000
//
// Methode permettant la creation d'une instance de l'operateur de check
// d'intersection de wires
//=============================================================================

#ifndef __CATCreateWireIntersectionChecker_h__ 
#define __CATCreateWireIntersectionChecker_h__ 

#include "CheckOperators.h"

class CATWireIntersectionChecker;
class CATGeoFactory;
class CATBody;
class CATTopData;


//--------------------------------------------------------------------------
//
// Methode: CATCreateWireIntersectionChecker
//
// Auteurs: EDS        Date: 11/10/2000
//
// Description: 
//   Creation d'une intance de l'operateur de check d'intersection
//   de wires.
//   
// Arguments:
//   iFactory               Container geometrique de iBodyToCheck
//   iData                  Configuration pour le versioning + journaling
//   iBodyToCheck           Body contenant un ou plusieurs wires a checker
//   
// Retour:
//     Pointeur sur une instance d'operateur topologique
//   
//--------------------------------------------------------------------------

ExportedByCheckOperators CATWireIntersectionChecker *
CATCreateWireIntersectionChecker(CATGeoFactory     * iFactory,
                                 CATTopData        * iData,
                                 CATBody           * iBodyToCheck);

#endif






