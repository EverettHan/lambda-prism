#ifndef CATMathDirtyCGMLevel_h
#define CATMathDirtyCGMLevel_h
//=============================================================================
//
// COPYRIGHT : DASSAULT SYSTEMES 2008
//
// Dirty access to CGM Level ** low level mathematics frameworks with impossible standard versioning **
//
//=============================================================================
// Abstract Class     : No
// Template Code      : No
// Inline Functions   : No
//=============================================================================
//
// History
//
// 19/12/08 NLD Creation. CATMathDirtyCGMLevel()
//              Ajout _AnchorDirtyCGMLevel
// 30/01/09 NLD Ajout argument optionnel NoSOS_BSFLevel
// 26/10/11 NLD Ajout CATMathDirtyCGMLevelControl(),
//                    GetCATMathDirtyCGMLevelControl(),
//                    GetCATMathDirtyCGMLevelControlNbDetection()
//              Le systeme de controle est activé par declaratif
//                CATMathDirtyCGMLevelActiveControl=1 (comptage)
//                CATMathDirtyCGMLevelActiveControl=2 (comptage + generation de call stack)
//                CATMathDirtyCGMLevelActiveControl=3 (comptage + generation de call stack + leak volontaire (code 77))
// 10/11/15 NLD Tentative de protection par precompilation contre utilisation de CATMathDirtyCGMLevel dans YN000MAT
//=============================================================================
#include  "ExportedByCATMathStream.h"

// Protection contre utilisation depuis YN000MAT (interdite en V6). NLD101115
// - V0 solution initiale       NLD: macro specifique entrainant erreur de compilation, dans YN0000MAT/LocalInterfaces
// - V1 solution sur suggestion CPT: par test du nom du module _MK_MODNAME_ defini par le shell de construction
// #define CATMathDirtyCGMLevel_ProtectionNLD101115 "ESSAI. A debrancher si un quelconque des compilateurs ne supporte pas cela"


extern "C" ExportedByCATMathStream       int    CATMathDirtyCGMLevel(int NoSOS_BSFLevel=0) ;
extern     ExportedByCATMathStream const void*  _AnchorDirtyCGMLevel ;

// Apres definition de l'export, pour generer erreur de compilation dans l'appelant
#ifdef CATMathDirtyCGMLevel_ProtectionNLD101115
   #if ( _MK_MODNAME_ == YN000MAT )
      #define CATMathDirtyCGMLevel   CATMathDirtyCGMLevelRenamedBecauseUnavailableInV6InModule_YN000MAT
   #endif
#endif


//--------------------------------------------------------------------------------------------------
// Controles de coherence et de bon deploiement de la configuration: rend-on un niveau plus petit que le niveau BSF
// alors que l'on a un opérateur de niveau 1 au niveau BSF?
//--------------------------------------------------------------------------------------------------
// marquage des méthodes non exportées en dehors de Math; usage interne
#define NOTExportedByCATMathStream

// iLevel   : niveau lu dans la configuration ou en l'absence de configuration
// iBSFLevel: niveau CGM BSF
// les controles ne sont declenchés que lorsque iLevel est different de iBSFLevel
extern "C" NOTExportedByCATMathStream void CATMathDirtyCGMLevelControl(short iLevel, short iBSFLevel);

// indique si les controles associés à CATMathDirtyCGMLevel() sont actifs
extern "C" NOTExportedByCATMathStream int GetCATMathDirtyCGMLevelControl();

// rend le nombre de detections par les controles associés à CATMathDirtyCGMLevel()
extern "C"    ExportedByCATMathStream int GetCATMathDirtyCGMLevelControlNbDetection();

#endif
