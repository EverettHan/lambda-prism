#ifndef CATCGMVersionningDeclareCountDebug_H
#define CATCGMVersionningDeclareCountDebug_H
//-------------------------------------------------------------------------------------
// Infrastructure d'association d'une valeur a chaque occurence d'une variable de versionning
//-------------------------------------------------------------------------------------
// But:
// - permet d'identifier rapidement l'occurence d'utilisation d'une variable de versionning
//   causant un changement de comportement
// Utilisation:
// 1) dans le fichier général de declaration de variables de versionning qui convient, 
//    redéfinir la variable de la manière suivante, de manière a obtenir une valeur de la variable
//    par source l'utilisant
//    #include "CATCGMVersionningDeclareCountDebug.h"
//    #ifdef CGM_Versionning_XXXX
//    #undef CGM_Versionning_XXXX
//    #endif
//    // une occurence par source
//    static int _MyCGM_Versionning_UseCount=CATCGMVersionningDeclareCountDebug();
//    #define CGM_Versionning_XXXX\   (CATCGMVersionLevel_XXXX+CATCGMVersionningDeclareCountDebugBreak(_MyCGM_Versionning_UseCount)-1)
//    #endif
// 2) Reconstruire les modules des sources utilisant la variable
// 3) fixer le niveau de versionning de la variable si necessaire
//    par exemple set CGM_Versionning=XXXX=4500
//    sinon considerons ici que l'odt au nous interesse est rejoué au niveau BSF valant 4500
//    et que la variable est de ce meme niveau
//    Les differentes occurences de la variable, dans les differents sources l'utilisant, vont etre
//    alors 4500, 4501, 4502, ...
// 4) Rejouer l'odt à differents niveaux via
//    set CATCX_MEMORY=level=
//    et identifier par dichotomie ou iterations d'incrementation le niveau à partir duquel il y a
//    changement de comportement
//    par exemple, supposons qu'il y a changement de comportement au niveau 4512
//    c'est à dire à la 13eme occurence
// 5) Rejouer l'odt au debugger et mettre dans CATCGMVersionningDeclareCountDebugBreak() un point
//    d'arret conditionnel avec la condition (iCount==13)
//    Le source appelant est le source impactant
//    (N.B source au sens .cpp, et non pas necessairement l'instruction trouvee dans la pile d'appel,
//    dans le cas ou il y aurait plusieurs occurences d'utilisation au sein du meme source)
//-------------------------------------------------------------------------------------
// 02/11/11 NLD Creation avec CATCGMVersionningDeclareCountDebug() et CATCGMVersionningDeclareCountDebugBreak()
//-------------------------------------------------------------------------------------
#include "CATMathStream.h"

extern "C" ExportedByCATMathStream int CATCGMVersionningDeclareCountDebug();
extern "C" ExportedByCATMathStream int CATCGMVersionningDeclareCountDebugBreak(int iCount);

#endif
