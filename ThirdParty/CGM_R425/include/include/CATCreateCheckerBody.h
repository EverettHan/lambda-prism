// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
// Creation NVT  23/02/2001
//
// Methode permettant la creation d'une instance de l'operateur de check
// de face (_SubdCheck + CheckIntersection + CheckDecomposition).
//=============================================================================

#ifndef __CATCreateBodyChecker_h__ 
#define __CATCreateBodyChecker_h__ 

#include "CheckOperators.h"
#include "ListPOfCATCell.h"
#include "CATCheckerBody.h"

class CATGeoFactory;
class CATBody;
class CATTopData;
class CATCheckerBody;


//--------------------------------------------------------------------------------
//
// Methode: CATCreateCheckerBody
//
// Auteurs: JHN        Date: 23/09/2006
//
// Description: 
//   Creation d'une intance de l'operateur de check de Body.
//   
// Arguments:
//   iFactory       Container geometrique de iBodyToCheck
//   iData          Configuration pour le versionning + journaling
//   iBodyToCheck   Body contenant une ou plusieurs faces a checker
//   iCellsToCheck  Liste des cellules potentiellement modifiees du body. Elles sont a verifier.
//   
// Retour:
//     Pointeur sur une instance d'operateur topologique
//   
//--------------------------------------------------------------------------------
// 10/05/2010  Création de la structure int/impl CATBodyChecker/CATCXBodyChecker
//--------------------------------------------------------------------------------

ExportedByCheckOperators CATCheckerBody *
CATCreateBodyChecker(CATGeoFactory * iFactory,
                     CATTopData    * iData,
                     CATBody       * iBodyToCheck,
                     CATLISTP(CATCell) * iCellsToCheck =(CATLISTP(CATCell)*)0);
 
#endif
