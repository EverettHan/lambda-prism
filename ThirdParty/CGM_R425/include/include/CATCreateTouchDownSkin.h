// COPYRIGHT DASSAULT SYSTEMES 2001
//=============================================================================
//
// Methode permettant la creation d'une instance de l'operateur de posage
// d' un body surfacique (iSkinBody) sur certaines faces (SetCoveredFaces sur l'operateur) 
// d'un body support (iTrimmingBody).
//=============================================================================

#ifndef __CATCreateTouchDownSkin_h__ 
#define __CATCreateTouchDownSkin_h__ 

#include "ExportedByCATTopologicalObjects.h"

class CATTopTouchDownSkin;
class CATGeoFactory;
class CATTopData;
class CATBody;
class CATShell;

//--------------------------------------------------------------------------
//
// Methode: CATCreateTouchDownSkin
//
//--------------------------------------------------------------------------

ExportedByCATTopologicalObjects CATTopTouchDownSkin *
CATCreateTouchDownSkin(CATGeoFactory     * iFactory,
                       CATTopData        * iTopData,
                       CATBody           * iTrimmingBody,
                       CATShell          * iTrimminShell,
                       CATBody           * iSkinBody,
                       CATShell          * iSkinShell);

#endif
