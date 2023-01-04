#ifndef CATCGMNewClassArray_H
#define CATCGMNewClassArray_H

   // A conserver pour quelques appels hors CGM; NLD020721
   #define CATCGMNewClassArray_catcgmdel_KeepOld "pilotage conservation temporaire ancienne signature catcgmdel"

// COPYRIGHT DASSAULT SYSTEMES 1996
//=============================================================================
//
//              macro   CATCGMNewClassArray(CLASS,NBNEWBLOC,CATCGAMEMPOOL) 
//           ou macro   CATCGMNewClassArrayDefine(CLASS,NBNEWBLOC)
//
// --> Definition de l'implementation d'une surcharge new/delete sur les petits objects CGM
//
//    ou encore pour des questions de performances
//
//         dans le header de Classe
//               inlineCATCGMNewClassArrayDeclare(CLASS,NBNEWBLOC,CATCGAMEMPOOL);
//         dans le source de la Classe
//               inlineCATCGMNewClassArrayDefine(CLASS);
//
//=============================================================================
// Usage notes:  Memory optimization by grouped allocations
//=============================================================================
// 01/01/08 NLD Ajout catcgmlastnew_debugonly pour debug
//              et de _CGMemLastNew##CLASS
// 19/05/20 NLD Adaptation/livraison du portage (R424 / TECHNO / VS2019) (modifications IK8)
//              - mise en compatibilité avec les différents niveaux V5 et V6
//              - affectation ou non au sein du new() de _CGMemLastNew##CLASS selon CATXH_CXX_UNWINDING_ON_CATTHROW
//                afin d'eviter la double destruction ultérieure via celui-ci dans quelques softs,
//                dans les cas où elle est déjà assurée automatiquement (unwinding)
//              - macro _CGMNewStatement avec implémentation selon CATXH_CXX_UNWINDING_ON_CATTHROW
//                remplaçant éventuellement
//                _CGMemLastNew##CLASS = catcgmnew(_CGMem##CLASS, Size, NBNEWBLOC, #CLASS, CATCGAMEMPOOL)
//                par catcgmnew non suivi d'affectation
// 24/06/21 NLD Ajout catcgmdel() avec nom de classe pour instrumentation
//              (ancienne signature à détruire à terme)
//              Migration des macros sur la nouvelle signature
// 25/06/21 NLD Deflaggage de niveau
//=============================================================================
#include <stddef.h>
#include <stdlib.h>

#include "CATIACGMLevel.h"
#include "CATIAV5Level.h"

#include "CATMathematics.h"
#include "CATMathInline.h"

#include "CATErrorMacrosEx.h" // CATXH_CXX_UNWINDING_ON_CATTHROW

//=============================================================================
// Partie pour forcer/tester les differentes implementations          NLD190520
// (tout ici doit rester inactif)
// #define CATXH_CXX_UNWINDING_ON_CATTHROW 1
//=============================================================================


//=============================================================================
// Debut du code
//=============================================================================
#if defined CATXH_CXX_UNWINDING_ON_CATTHROW
 #if (0 != CATXH_CXX_UNWINDING_ON_CATTHROW)
  #define CATCGMNewClassArraySaveLastNew(CLASS,Result) // empty
 #endif
#endif
#ifndef CATCGMNewClassArraySaveLastNew
  #define CATCGMNewClassArraySaveLastNew(CLASS,Result) \
    _CGMemLastNew##CLASS = Result;
#endif

// ATTENTION avec la nouvelle version IK8:
// les softs référençant _CGMemLastNew##CLASS sont au 190520
// CATKnotVector:
//   pour une vraie destruction avec _CGMemLastNewCATKnotVector
// CATTopData:
// - il y a des finesses: dans CATTopData, la variable _CGMemLastNewCATTopData
//   est utilisée non pour destruction mais pour une instrumentation
// CATSoftwareConfiguration:
// - _CGMemLastNewCATSoftwareConfiguration en commentaires
// CAThkPoint
// - utilisation des divers _CGMemLastNew##CLASS des sous-classes
//   pour catcgmdel() seulement sans appel de destructeur
// A etudier NLD190520

// Version IK8
// ++IK8 20:04:29
#if defined CATXH_CXX_UNWINDING_ON_CATTHROW
   #if (0 != CATXH_CXX_UNWINDING_ON_CATTHROW)
// When C++ unwinding is enabled, memory allocated for partially created objects that threw an exception 
// is automatically reclaimed.
// => Disable the global variable bypass designed for cleanup to avoid double delete
#define _CGMNewStatement(CLASS,NBNEWBLOC,CATCGAMEMPOOL)   \
    catcgmnew(_CGMem##CLASS, Size, NBNEWBLOC, #CLASS, CATCGAMEMPOOL)
   #endif
#endif

#ifndef _CGMNewStatement
// Poor man's solution without C++ Native Exception support... Use a global variable for cleanup
#define _CGMNewStatement(CLASS,NBNEWBLOC,CATCGAMEMPOOL)    \
    (_CGMemLastNew##CLASS = catcgmnew(_CGMem##CLASS, Size, NBNEWBLOC, #CLASS, CATCGAMEMPOOL))
#endif  // CATXH_CXX_UNWINDING_ON_CATTHROW
// ++IK8 20:04:29

class CATCGMNewMetaBloc;
class CATCGAMEM;

//=============================================================================

//-----------------------------------------------------------------------------
// Adresse du dernier new (pour debug) 
//-----------------------------------------------------------------------------
extern ExportedByCATMathematics void * catcgmlastnew_debugonly ;

//-----------------------------------------------------------------------------
ExportedByCATMathematics void * catcgmnew(CATCGMNewMetaBloc *& ioLocalMngt     ,
                                          size_t               iSize           ,
                                          const int            iNBOBJ          ,
                                          const char        *  iClassname      ,
                                          const char           iIdentityPOOL[5],
                                          CATCGAMEM         *  iPerfo          = NULL);

//-----------------------------------------------------------------------------
// (OLD, to remove)
#ifdef CATCGMNewClassArray_catcgmdel_KeepOld
ExportedByCATMathematics void   catcgmdel(CATCGMNewMetaBloc *& ioLocalMngt     ,
                                          void              *  iResult         );
#endif

//-----------------------------------------------------------------------------
// (NEW, to keep)
ExportedByCATMathematics void   catcgmdel(CATCGMNewMetaBloc *& ioLocalMngt     ,
                                          const char        *  iClassname      ,
                                          void              *  iResult         );

//-----------------------------------------------------------------------------
extern ExportedByCATMathematics const char catcgmPoolGEOM[5];
extern ExportedByCATMathematics const char catcgmPoolVISU[5];
extern ExportedByCATMathematics const char catcgmPoolPERM[5];
extern ExportedByCATMathematics const char catcgmPoolTEMP[5];
extern ExportedByCATMathematics const char catcgmPoolV4  [5];
extern ExportedByCATMathematics const char catcgmPoolTOPO[5];
extern ExportedByCATMathematics const char catcgmPool666 [5];

//----------------------------------------------------------------------------------
// Specific customisation relimited to V6 Windows  R14 RunTime
//     for a relimited impact (detection) for some scenarios algorithms depending on memory allocation
//----------------------------------------------------------------------------------
//  #if defined ( PLATEFORME_DS64 ) && defined ( _WINDOWS_SOURCE  ) && defined ( CATIAR214 )
//  #if defined ( _WINDOWS_SOURCE  ) &&  ( defined ( CATIAR214 ) || defined ( CATIAV5R23 )   )
#if defined ( _WINDOWS_SOURCE  )
#define CATCGMLowMemoryManagement_NotConstrainedByAlgorithms
#else
#undef  CATCGMLowMemoryManagement_NotConstrainedByAlgorithms
#endif


#define inlineCATCGMNewClassArrayDeclare(CLASS)                                                    \
static CATCGMNewMetaBloc * _CGMem##CLASS;                                                          \
                                                                                                   \
static void              * _CGMemLastNew##CLASS;                                                   \
                                                                                                   \
INLINE void              * operator new   (size_t);                                                \
                                                                                                   \
INLINE void                operator delete(void *)                                                 //

#define inlineCATCGMNewClassArrayDeclareAfter(CLASS,NBNEWBLOC,CATCGAMEMPOOL)                       \
                                                                                                   \
INLINE void * CLASS::operator new   (size_t Size)                                                  \
{                                                                                                  \
   return _CGMNewStatement(CLASS,NBNEWBLOC,CATCGAMEMPOOL);                                         \
}                                                                                                  \
                                                                                                   \
INLINE void   CLASS::operator delete(void* result)                                                 \
{                                                                                                  \
   catcgmdel(_CGMem##CLASS, #CLASS, result);                                                       \
}                                                                                                 //

#define inlineCATCGMNewClassArrayDefine(CLASS)                                                     \
CATCGMNewMetaBloc *CLASS::_CGMem##CLASS = NULL                                                     //


#define CATCGMNewClassArray(CLASS,NBNEWBLOC,CATCGAMEMPOOL)                                         \
                                                                                                   \
static CATCGMNewMetaBloc * _CGMem##CLASS        = NULL;                                            \
                                                                                                   \
static void              * _CGMemLastNew##CLASS = NULL;                                            \
                                                                                                   \
void * CLASS::operator new   (size_t Size)                                                         \
{                                                                                                  \
   return _CGMNewStatement(CLASS, NBNEWBLOC, CATCGAMEMPOOL);                                       \
}                                                                                                  \
                                                                                                   \
void   CLASS::operator delete(void* result)                                                        \
{                                                                                                  \
   catcgmdel(_CGMem##CLASS,  #CLASS, result);                                                      \
}                                                                                                  //

#define CATCGMNewClassArrayDefine(CLASS,NBNEWBLOC)                                                 \
CATCGMNewClassArray(CLASS, NBNEWBLOC, catcgmPool666)                                               //

#define CATCGMNewClassArrayTOPODefine(CLASS,NBNEWBLOC)                                             \
CATCGMNewClassArray(CLASS, NBNEWBLOC, catcgmPoolTOPO)                                              //



#endif 



