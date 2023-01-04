#ifndef CATCGM_LightSession_H
#define CATCGM_LightSession_H
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
*      this support is tightly linked with some reccurent CoreDump incident
*         misunderstood concerning  origin of memory consumption
*         badly managed when request of allocations begin to fail
* 
*    Meaningfull report avec provided with activation of following environement variable
*         CATCGAMeasure=Home=E:\tmp,PCS   (Cache option should be omitted)
*/
//--------------------------------------------------------------------------------------

#include <string.h>
#include <stdio.h>
#include <stddef.h>

#include "CATDataType.h"
#include "CATBoolean.h"

#include "CATMathematics.h"

//--------------------------------------------------------------------------------------
typedef int (*CATCGAMEM_Exit)();

//--------------------------------------------------------------------------------------
#define MAX_Exit_Array           48
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
class ExportedByCATMathematics CATCGM_LightSession
{
public :

                             CATCGM_LightSession   ();
                            ~CATCGM_LightSession   ();

         void                InitializeLightSession(); // service dedie a l'initialisation LIGHT (without DLL treatment)

  static CATCGM_LightSession _CATCGM_LightSession;

         CATBoolean          _LightSessionIsDefined;                     // NLD190219 anciennement _LightSessiontIsDefined
         CATBoolean          _LightSessionInitializeEnded;

         unsigned int       _Enable_CATDevelopmentStage           :  1; // Optim CATGetEnv
         unsigned int       _Enable_CATDevelopmentStage_Computed  :  1; // Optim CATGetEnv

         unsigned int       _Dedicated_InternalDS_BSFTST          :  1; // Optim Internal DS BSFTST
         unsigned int       _Dedicated_InternalDS_Computed        :  1; //

         unsigned int       _Dedicated_IsUnderODT                 :  1; // CATCGMIsUnderODT::IsUnderODT
         unsigned int       _Dedicated_IsUnderODT_Computed        :  1; //

         unsigned int       _CATCGAMeasure_Enabled                :  1; // CATCGAMeasure

         unsigned int       _MultiThreadEnable                    :  1; // Possibilite de MultiThread; inactif par défaut; activable seulement par déclaratif
         unsigned int       _MultiThreadIsActive                  :  1; // Activation courante du MultiThread; necessite _MultiThreadEnable

         unsigned int       _UnderCATCX_MEMORY_MAIN               :  1; // detection contexte executable sous controle CGM

         unsigned int       _Exit_SortieFinale_Done               :  1; // Sortie finale déjà effectuee


         unsigned int       _Exit_CATCallOnExit_Done              :  1; // Abonnement Fw System sur traitement exit
         unsigned int       _Exit_atexit_Done                     :  1; // Abonnement Operating System sur traitement exit
         unsigned int       _Exit_FirstIsEnough                   :  1; // Premiere retour exit est suffisant pour agir
         unsigned int       _Exit_SortieFinale_Ressources         :  1; // Sortie finale deje effectuee

         unsigned short     _Exit_Defaut_ReturnCode;                    // Valeur d'Exit.


         int                _Exit_AtExit_Nb;
         int                _Exit_BeforeExit_Nb;
         CATCGAMEM_Exit     _Exit_AtExit_Array    [ MAX_Exit_Array ];
         CATCGAMEM_Exit     _Exit_BeforeExit_Array[ MAX_Exit_Array ];


};
 
//--------------------------------------------------------------------------------------
ExportedByCATMathematics CATBoolean CATCGMControlInternalDS_BSFTST();

#endif
