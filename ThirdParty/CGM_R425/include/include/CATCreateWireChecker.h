// COPYRIGHT DASSAULT SYSTEMES 2001
//=============================================================================
// Creation NVT  23/02/2001
//
// Methode permettant la creation d'une instance de l'operateur de check
// de wire (_SubdCheck + CheckIntersection)
//=============================================================================

#ifndef __CATCreateWireChecker_h__ 
#define __CATCreateWireChecker_h__ 

#include "CheckOperators.h"

class CATWireChecker;
class CATGeoFactory;
class CATBody;
class CATTopData;


//--------------------------------------------------------------------------
//
// Methode: CATCreateWireChecker
//
// Auteurs: NVT        Date: 23/02/2001
//
// Description: 
//   Creation d'une intance de l'operateur de check de face.
//   
// Arguments:
//   iFactory       Container geometrique de iBodyToCheck
//   iData          Configuration pour le versionning + journaling
//   iBodyToCheck   Body contenant un ou plusieurs wire a checker
//   
// Retour:
//     Pointeur sur une instance d'operateur topologique
//   
//--------------------------------------------------------------------------

ExportedByCheckOperators CATWireChecker*
CATCreateWireChecker(CATGeoFactory * iFactory,
                     CATTopData    * iData,
                     CATBody       * iBodyToCheck);
 
#endif
