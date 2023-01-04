#ifndef CATCreateEndingShell_H
#define CATCreateEndingShell_H
/** @CAA2Required */
/*---------------------------------------------------------------------*/
/* DON'T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS  */
/* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPPEAR AT ANY TIME */
/*---------------------------------------------------------------------*/
// COPYRIGHT DASSAULT SYSTEMES 1999

//===================================================================
//
// Function definition for overiding default shape of min mode skin skin Fillet 
//
//===================================================================


// TopologicalOperators
class CATSoftwareConfiguration;

//NewTopologicalObjects
class CATBody;
class CATShell;
class CATFace;

//GeometricObjects
class CATSurParam;

//Mathematics
#include "CATMathDef.h"
class CATMathPoint;
class CATMathVector;

// Nouvelles signature en R7
#define CATCreateEndingShellNewSignature   // Versioning                dec 2000
#define CATCreateEndingShellNewSignature_2 // Sheet Metal Plan Synthol  Jun 2001

//===================================================================
typedef void (*CATCreateEndingShell)(CATSoftwareConfiguration* iConfig,
                                     void*                     iAnyData,
                                     CATMathPoint            & iCutOrigin,            // Debut de decoupe de la skin d appui
                                     CATMathVector           & iCutDirection,         // Direction de depart pour la decoupe droite (standard)
                                     CATMathVector           & iSkinNormal,           // Normale a la skin d appui dirigee vers le fillet
                                     const int                 iExtremity,            // 1 pour le debut du ruban, 2 pour la fin
                                     CATBoolean                iOrientation,          // L'exterieur du fillet est vers iCutDirection^iSkinNormal
                                     CATBody*                  iBodyToTrim,           // Body de la skin d appui
                                     CATBody*                  iTrimmingBody,         // Body dans lequel creer le Shell
                                     CATShell*               & oTrimmingShell,        // Shell a creer qui remplacera le shell plan (standard)
                                     CATFace*                & oFirstTrimmingFace,    // Face de depart dans le shell, supporte iCutOrigin
                                     CATSurParam             & oOriginPositionOnFace, // Position de iCutOrigin sur oFirstTrimmingFace
                                     CATMathVector           & oNewCutDirection);     // Nouvelle direction de depart de la decoupe (=iCutDirection si standard)
//===================================================================
#endif
