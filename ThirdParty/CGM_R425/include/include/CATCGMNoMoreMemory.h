#ifndef CATCGMNoMoreMemory_H
#define CATCGMNoMoreMemory_H
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2001
//  Methodologie CGM pour gerer les ressources memoires des objets et des operateurs
//   Pour emission d'un message d'erreur associe aux erreurs d'allocations
//==========================================================================
/*
Si vos ressources memoires sont deja obtenus par les allocateurs securise de style
     Mathematics\ProtectedInterfaces\CATCGMArrays.h
     Mathematics\ProtectedInterfaces\CATCGMNewArray.h
     Mathematics\ProtectedInterfaces\CATCGMVirtual.h
Vous n'avez aucune migration a envisager
*/
/*

  Une saturation de l'espace d'adressage mémoire  provoque des échecs d'allocation et degenere généralement en coredump.
  Voici des choix tactiques préconisés a CGM pour réduire ce type de coredump.

  Cette proposition est le choix tactique actuellement en vigueur a CGM (jusqu'a preuve d'une meilleure contre-proposition).
  même si de tels scénarios V5 ne pourront pas être aujourd'hui garanti  sans coredump pour les raisons suivantes :
    - démultiplication conséquente des allocations directes OS  "a la main" sans protection
    - la certification RunTime (ODT) n'aborde nullement les configurations de saturations mémoires 
        (de plus mkCheckSource impuissant)
    - des offres génériques (Collections/Listes du Fw System) ne sont pas encore robustes 
        en contexte de saturation mémoire

  Les grandes lignes de cette proposition sont :
     0) les objets gerent les requetes en ressources memoires par le biais d'allocateurs securises CATCGMNoMoreMemory.h 
     1) ne pas perdre la caractérisation d'une erreur de type échec d'allocation 
     2) eviter de persévérer dans les traitements iteratifs sur ce type d'erreur reconnaissable
  Ceci devrait permettre de confronter trop de logiciel en contexte de saturation memoire (Cf remarques precedentes)
  et potentiellement de  permettant a l'utilisateur de reprendre la main  
  et de tenter de sauvegarder son travail en cours (après quelques Close)


 A)  Gestion des objets et opérateurs géométriques conformes a deux lignes directrices suivantes :
 
       1) une CATError interne caracterisable  CATCGMIsANoMoreMemoryError  est levée en cas d'échec d'allocation mémoire
       
        Pour les services ayant une signature a base de HRESULT, 
        on bloque bien sur la remontée d'exception en traduisant  
        le diagnostic d'échec avec la valeur ERROR_NOT_ENOUGH_MEMORY.

            a) Offre de services centralises pour les requêtes en ressources mémoire
                    Cf   CATCGMemory.h  c'est le point de depart ..
                   catcxDoubleNew/catcxDoubleFree             a la place de new double []  et delete [] (double *)  
            b) Surcharge du new/delete par POOL des objets  ( CATICGMObject, ...)
                  rappel il s'agit ici d'un enrobage  des allocations mémoire pour des soucis performance CPU
                    intégrant en plus les notions de duree de vie et de classification.
            c) Surchage du new/delete par classe derivee CATCGMVirtual   ( CATCGMOperator, ...)
                  
          Les ressources mémoires sont donc obtenus par des services du Fw Mathematics
              sur lequel on peut introduire une politique centrale de la gestion mémoire.
          On évite donc de s'appuyer sur des services operating system ( malloc, new double[] )
          Pour rappel, un échec d'allocation de malloc mène a un pointeur NULL sans levée d'exception
          mkCheckSource ne previent pas les coredump si on enchaine directement par un memcpy/memset       

    2) la cohérence des objets conservée malgré les échecs d'allocations 
          permettant leur nettoyage/desallocation sans souci dans les traitements de CATCatch.
        (on évite d'anticiper les tailles d'allocations suite a une reallocation)

 B) Usagers du modeleur géométrique évitent de persévérer sur des échecs d'allocation mémoire

      Il faut éviter d'effectuer un Flush prématuré sur l erreur spécifique de CATCGMNoMoreMemory.h
      Il suffit donc de caractériser les situations de saturations mémoires selon la méthodologie suivante
             1)   CATCatch(CATError *erreur)  
         {
            if ( CATCGMIsANoMoreMemoryError(erreur) )
                 ....
         }
      2) if ( HRESULT == ERROR_NOT_ENOUGH_MEMORY )

  L'utilisateur a de meilleure chance de reprendre la main en cas de saturation mémoire,
     pouvant tenter de libérer des ressources et sauvegarder l'état courant de son travail .

*/
//==========================================================================
#include <stdlib.h>
#include <stddef.h>

#include "CATMathematics.h"
#include "CATErrorMacros.h"
#include "CATCGMBuildDebug.h"
#include "CATCGMThrow.h"
#include "CATBoolean.h"

#include "CATCGMemory.h"

//----------------------------------------------------------------------------------------------
// CATCGMNoMoreMemoryError)     Pour generer un diagnostic d'allocation impossible
// CATCGMIsANoMoreMemoryError)  Pour tester si un diagnostic est celui d'une allocation CGM en echec
// CATCGMNoMoreMemory)          Pour ALLOCATION EN ECHEC , UNE LEVEE D'EXEPTION EST ALORS EMISE 
//----------------------------------------------------------------------------------------------
ExportedByCATMathematics CATError * CATCGMNoMoreMemoryError(size_t iNumberOfBytes); 
ExportedByCATMathematics CATBoolean CATCGMIsANoMoreMemoryError(CATError *iError); 

#define CATCGMNoMoreMemory(iNumberOfBytes) CATCGMThrow( CATCGMNoMoreMemoryError(iNumberOfBytes) )


#endif

