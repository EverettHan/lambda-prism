// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
// Creation NVT 31/01/2001
//
// Methode permettant la creation d'une instance de l'operateur de 
// reparation et nettoyage de body MonoShell MonoFace
//=============================================================================

#ifndef __CATCreateFaceHealerOperator_h__ 
#define __CATCreateFaceHealerOperator_h__ 

#include "ExportedByCATTopologicalObjects.h"

class CATTopFaceHealerOperator;
class CATGeoFactory;
class CATBody;
class CATTopData;


//--------------------------------------------------------------------------
//
// Methode: CATCreateHealerOperator
//
// Auteurs: NVT        Date: 31/01/2001
//
// Description: 
//    Creation d'une instance de l'operateur de 
//    reparation et nettoyage de body MonoShell MonoFace
// Arguments:
//   iFactory               Container geometrique de iBodyToRecompose
//   iData                  Configuration pour le versionning + journaling
//   iBodyToClean       
//   
// Retour:
//   
//--------------------------------------------------------------------------

ExportedByCATTopologicalObjects CATTopFaceHealerOperator *
CATCreateFaceHealerOperator(CATGeoFactory * iFactory,
                            CATTopData    * iData,
                            CATBody       * iBodyToClean);

#endif

