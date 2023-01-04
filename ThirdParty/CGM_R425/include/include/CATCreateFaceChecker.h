// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
// Creation NVT  23/02/2001
//
// Methode permettant la creation d'une instance de l'operateur de check
// de face (_SubdCheck + CheckIntersection + CheckDecomposition).
//=============================================================================

#ifndef __CATCreateFaceChecker_h__ 
#define __CATCreateFaceChecker_h__ 

#include "CheckOperators.h"

class CATFaceChecker;
class CATGeoFactory;
class CATBody;
class CATTopData;


//--------------------------------------------------------------------------
//
// Methode: CATCreateFaceChecker
//
// Auteurs: NVT        Date: 23/02/2001
//
// Description: 
//   Creation d'une intance de l'operateur de check de face.
//   
// Arguments:
//   iFactory       Container geometrique de iBodyToCheck
//   iData          Configuration pour le versionning + journaling
//   iBodyToCheck   Body contenant une ou plusieurs faces a checker
//   
// Retour:
//     Pointeur sur une instance d'operateur topologique
//   
//--------------------------------------------------------------------------

ExportedByCheckOperators CATFaceChecker *
CATCreateFaceChecker(CATGeoFactory * iFactory,
                     CATTopData    * iData,
                     CATBody       * iBodyToCheck);
 
#endif
