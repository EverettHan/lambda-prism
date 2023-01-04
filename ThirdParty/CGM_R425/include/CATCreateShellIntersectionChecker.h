// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
// Creation EDS  09/10/2000
//
// Methode permettant la creation d'une instance de l'operateur de check
// d'intersection shell/shell.
//=============================================================================

#ifndef __CATCreateShellIntersectionChecker_h__ 
#define __CATCreateShellIntersectionChecker_h__ 

#include "CheckOperators.h"

class CATShellIntersectionChecker;
class CATGeoFactory;
class CATBody;
class CATTopData;


//--------------------------------------------------------------------------
//
// Methode: CATCreateShellIntersectionChecker
//
// Auteurs: EDS        Date: 09/10/2000
//
// Description: 
//   Creation d'une intance de l'operateur de check d'intersection
//   shell/shell.
//   
// Arguments:
//   iFactory               Container geometrique de iBodyToCheck
//   iData                  Configuration pour le versionning + journaling
//   iBodyToCheck           Body contenant les shells a confronter
//   
// Retour:
//     Pointeur sur une instance d'operateur topologique
//   
//--------------------------------------------------------------------------

ExportedByCheckOperators CATShellIntersectionChecker *
CATCreateShellIntersectionChecker(CATGeoFactory * iFactory,
                                  CATTopData    * iData,
                                  CATBody       * iBodyToCheck);

#endif






