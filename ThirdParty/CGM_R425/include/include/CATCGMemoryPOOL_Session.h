#ifndef CATCGMemoryPOOL_Session_H
#define CATCGMemoryPOOL_Session_H
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2008
/** @CAA2Required */
/**
* @level Private
* @usage U1
*
*    For general solution concerning GM diagnostic inside an applicative product
*       with some major PCS criteria as memory (working set , virtual size)
* 
*    This Multiple purpose analysis can be extended,
*      this support is tightly linked with some recurrent CoreDump incident
*         misunderstood concerning  origin of memory consumption
*         badly managed when request of allocations begin to fail
* 
*    Meaningfull report avec provided with activation of following environement variable
*         CATCGAMeasure=Home=E:\tmp,PCS   (Cache option should be omitted)
*/
//--------------------------------------------------------------------------------------
// 18/02/19 NLD - Mise au propre et documentation
//              - _CallCount passe sur 2 bits au lieu de 1, pour gestion mode 2
//--------------------------------------------------------------------------------------
#include <string.h>
#include <stdio.h>
#include <stddef.h>

#include "CATDataType.h"
#include "CATBoolean.h"

#include "CATCGAMEM.h"

#include "CATCGMaxLong.h"
#include "CATCGMNewManagement.h"
#include "CATCGAMEMStats.h"
#include "CATMathematics.h"
#include "CATErrorDef.h"
#include "CATCGMemory.h"
#include "CATCGMManageMemory.h"
#include "CATCGMemoryPOOL.h"

class CATCGMNewMetaBloc;
class CATCGMArrayPool;

//--------------------------------------------------------------------------------------
// Caracteristiques globales de la Session memoire
//--------------------------------------------------------------------------------------

#define MAX_Book_64Bytes         17

#define MAX_DebugCharacters   32768

#include "CATMathematics.h"

//--------------------------------------------------------------------------------------
class ExportedByCATMathematics CATCGMemoryPOOL_Session
{
public :


                                  CATCGMemoryPOOL_Session();
                                 ~CATCGMemoryPOOL_Session();

       void                       InitializeMemoryManagement(); // service dedie a l'initialisation

static CATCGMemoryPOOL_Session    _CATCGMemoryPOOL_Session;

   CATBoolean                     _MemoryManagementIsDefined;
   CATBoolean                     _MemoryManagementInitializeEnded;

   // N.B (analyse et commentaires NLD180219)
   //     toutes les variables declarées avec : 1 (ou : 2) sont explicitement et systématiquement initialisées une à une
   //     dans CATCGMemoryPOOL_Session::InitializeMemoryManagement(), (bizarrement placé dans CATCGAMeasureGlobal_EndOfProcess.cpp)
   //     en plus du memset global mettant des 0, (et donc après celui-ci)
   //     sauf
   //     - _CATCGMemBookStats                                (pas d'initialisation)
   //     - _CGMTkJournaling_AutomaticByEnvironnementVariable (pas d'initialisation)
   //     - _With_CATCX_MEMORY                                (initialisation conditionnelle)
   // Avant ou après le passage de _CallCount sur 2 bits
   //     les 7 variables _follow_IsNeeded à _NoExitForODT              sont vues à la meme adresse
   //     les 8 variables _IsAlreadyExited à _With_CATCX_MEMORY         sont vues à la meme adresse
   //     les 4 variables _DisabledPool    à _ExitForODTOnBadNewSpecial sont vues à la meme adresse
   // Mais POURQUOI tient-on absolument à economiser quelques misérables octets sur une structure de taille 33144 au 180219,
   // (essentiellement à cause de _Debug_Characters_Size)
   // et à garantir ainsi des noeuds au cerveau ou des dysfonctionnements?
   
   unsigned int                   _follow_IsNeeded                 :  2; // Debug particulier est requis
   unsigned int                   _follow_SetValueAtInitAndExit    :  1; // Force valeur initiale a l'allocation/desallocation objet

   unsigned int                   _NameClass                       :  1; // Pour debug memoire avec le nom des classes des objets surcharges new/delete
   unsigned int                   _InstanceCounter                 :  1; // Pour debug memoire avec numero d'instance dans la classe

   unsigned int                   _UnderODT                        :  1; // detection d'un contexte d'ODT
   unsigned int                   _UnderPurify                     :  1; // detection d'un contexte Replay Purify

   unsigned int                   _NoExitForODT                    :  1; // debranchement des exit CGM possibles dans les ODTS
   unsigned int                   _IsAlreadyExited                 :  1; // detection d'une sortie deja realisee (exit en cours
   
   unsigned int                   _HasBeenMultiThreaded            :  1; // passage en multi-threading ..

   unsigned int                   _DetectUseCountStillUsedAtDelete :  1; // Debug Objet de modelisation CGM.

   unsigned int                   _VariousProvider                 :  1; // allocations non typees de CGM sont aiguillees
                                                                         // sur la surcharge du new/delete pour les petites tailles
   
   unsigned int                   _CATCX_MEMORY_Authorized         :  1; // +1:Possibilite de MultiThread


   unsigned int                   _CATCGMemBookStats               :  1; // statistiques pour CATCGMemBook/CATCGMemClear
   unsigned int                   _CGMTkJournaling_AutomaticByEnvironnementVariable    :  1; //


   unsigned int                   _With_CATCX_MEMORY               :  1; // statistiques pour CATCGMemBook/CATCGMemClear

   unsigned int                   _DisabledPool                    :  1; //   ?????
   unsigned int                   _CallCount                       :  2; // 2 bits au lieu de 1; NLD180219
   unsigned int                   _TraceMode                       :  1; //   ?????
   unsigned int                   _ExitForODTOnBadNewSpecial       :  1; //   ?????

   char                         * _CATCX_MEMORY_Filename;                // Log des statiques

   int                            _follow_SetValue_AtInit;               // Valeur de remplissage
   int                            _follow_SetValue_AtExit;               // Valeur de remplissage

   //--------------------------------------------------------------------------------------
   // Identification de Pool d'allocation
   //--------------------------------------------------------------------------------------
   CATCGMNewMetaBloc            * _FirstMetaBloc;                        // premier metabloc alloue Specialement Boot CATCGMNewMetaBloc
   CATCGMNewMetaBloc            * _MetaBloc_CATTopData;                  // Pour filtrage fuites memoire
   CATCGMNewMetaBloc           ** _MetaMetaBloc;

   CATCGMemoryPOOL              * _FirstPool;
   CATCGMemoryPOOL              * _Pool_Geometry;                        // Les Objets geometriques (document)
   CATCGMemoryPOOL              * _Pool_Topology;                        // Les Objets topologiques (document)
   CATCGMemoryPOOL              * _Pool_Permanent;                       // Les rares objets globaux
   CATCGMemoryPOOL              * _Pool_Temporary;                       // Les donnees d'operateurs
   CATCGMemoryPOOL              * _Pool_V4XP;                            // les objets V4
   CATCGMemoryPOOL              * _Pool_666;                             //
   CATCGMemoryPOOL              * _Pool_Visualization;                   // Les Objets topologiques (document)

   CATCGMMutex                  * _Mutex_Global;
 
   CATCGMemoryProvider            _DefaultMemoryProvider;

   CATCGAMEM::CATMemoryStrategy   _Pool_Default_Strategy;

   CATCGMArrayPool              * _Array_Geometry;
   CATCGMArrayPool              * _Array_Temporary;


  //---------------------------------------------------------------------------
  // Gestion d'une eventuelle table associative pour les allocations de 512 Ko
  // Mais on peut garantir que cet acces direct reussi, d'ailleurs il y a en general
  //    - INSERT  : deux cases possibles ou inserer un Allocator
  //    - QUERY   : trois cases eventuelles ou on recherchera un Allocator
  //                 a partir de l'adresse d'un Objet
  // Toutefois ce codage permets dans le cas standard
  //    un access direct O(1) plutot qu'en O(n)
  //---------------------------------------------------------------------------
   size_t                         _PageAllocator_BlobBytes;
   int                            _PageAllocator_BlobBits;
   int                            _PageAllocator_CumulatedNumber;


   int                            _PageAllocator_MappingBloc_Bits;
   CATULONG64                     _PageAllocator_MappingBloc_Size;
   CATCGMPageAllocator         ** _PageAllocator_MappingBlob;
 
   //--------------------------------------------------------------------------------------
   // Gestion allocation heterogene 
   //     Mathematics\ProtectedInterfaces\CATCGMemory.h
   //--------------------------------------------------------------------------------------
   CATCGMemoryProvider            _Book_Provider;
   CATCGMaxLong                   _Book_CurrentNbBook;
   CATCGMaxLong                   _Book_TotalNbBook;
   CATCGMaxLong                   _Book_CumulatedBytes;
   CATCGMaxLong                   _Book_CurrentNbBookOfArrayPool;
   int                            _Book_64Bytes[MAX_Book_64Bytes];
#ifdef _WINDOWS_SOURCE 
   HANDLE                         _Book_Heap;          // Gestion Heap privee
#endif
   CATSysPoolPtr                  _Book_SysPool;
    
   // Seulement pour malloc, renseignes seulement si CATCGMEMBOOK_MALLOC_STATS est defini dans CATCGMemory.cpp
   CATCGMaxLong                   _Book_RealCumulatedBytes; 
   CATCGMaxLong                   _Book_RealCumulatedFreedBytes; // Seulement pour malloc


   //-----------------------------------------------------------------------
   // Nom de l'ODT pour Authorisation.
   //-----------------------------------------------------------------------
   char                         * _CurrentODTName;

   //-----------------------------------------------------------------------
   // Pour Gestion CATCX_MEMORY=follow..
   //-----------------------------------------------------------------------
   double                       * _follow_Adress;
   int                            _follow_ClassInstance;
   char                         * _follow_ClassName;

   //-----------------------------------------------------------------------
   // Pour Debug
   //-----------------------------------------------------------------------
   char                           _Debug_Characters[MAX_DebugCharacters];
   size_t                         _Debug_UsedCharacters;
  
   CATCGMNewMetaBloc            * _CATSoftwareConfiguration;
};


 
#endif
