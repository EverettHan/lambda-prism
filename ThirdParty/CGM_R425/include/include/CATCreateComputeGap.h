// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
// Creation NVT 31/01/2001
//
// Methode permettant la creation d'une instance de l'operateur de calcul
// de trous d'un body
//=============================================================================

#ifndef __CATCreateComputeGap_h__ 
#define __CATCreateComputeGap_h__ 

#include "ExportedByCATTopologicalObjects.h"

class CATTopComputeGap;
class CATGeoFactory;
class CATBody;
class CATTopData;


//--------------------------------------------------------------------------
//
// Methode: CATCreateComputeGap
//
// Auteurs: EDS        Date: 31/01/2001
//
// Description: 
//   Creation d'une intance de l'operateur de calcul de trou
//   d'un body volumique 
//   
// Arguments:
//   iFactory               Container geometrique de iBodyToRecompose
//   iData                  Configuration pour le versionning + journaling
//   iBodyToAnalyse       
//   
// Retour:
//   
//--------------------------------------------------------------------------

ExportedByCATTopologicalObjects CATTopComputeGap *
CATCreateComputeGap(CATGeoFactory * iFactory,
                         CATTopData    * iData,
                         CATBody       * iBodyToAnalyse);

#endif






