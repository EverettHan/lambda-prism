/* -*-C++-*- */

#ifndef CATlsoSubscription_H
#define CATlsoSubscription_H
/*  
=============================================================================

RESPONSABLE  : A Deleglise 

DESCRIPTION  : Gestion des objets abonnes aux suppressions / remplacement
               d'un objet, individuellement ou a toute la classe

=============================================================================
*/
#include "CATDataType.h"
#include "CATCGMVirtual.h"

class CATlsoAlgoElt;
class CATlsoChainMaster;
//--------------------------------------------------------------------------

class CATlsoSubscription : public CATCGMVirtual
{

public:
  
  typedef void (* UpdateAction) (void * iSubscriber, CATlsoAlgoElt * iOld,
                                 CATLONG32 iNbNewElts, CATlsoAlgoElt ** iListOfNewElts);

  // constructeur (ne fait rien)
  // On fournit soit un objet, soit une chaine (pas les deux)
  CATlsoSubscription(CATlsoAlgoElt * iElt, CATlsoChainMaster * iChain);

  // cpy-cst et operateur = non implementes
  CATlsoSubscription(CATlsoSubscription & iOrig);
  CATlsoSubscription & operator= (const CATlsoSubscription & iRight);

  //-------------------------------------------------------------------------------------------------------
  // Surcharge du new/delete
  //-------------------------------------------------------------------------------------------------------
  CATCGMNewClassArrayDeclare;

  // destructeur
  ~CATlsoSubscription();

  // Ajout d'un contrat
  void AppendContract(void * iSubscriber, UpdateAction iAction);

  // Suppression de tous les contrats d'un abonne
  // si iForceRemove=0, on temporise la suppression des contrats specifiant _IsLocked=1
  void RemoveContract(void * iSubscriber, short iForceRemove=0);

  // Information des abonnes suite a une destruction ou un remplacement
  // (destruction si iNbNewElts = 0)
  void InformSubscribers(CATlsoAlgoElt * iOld, CATLONG32 iNbNewElts,
                         CATlsoAlgoElt ** iListOfNewElts);

  // Classe locale definissant un contrat d'abonnement
  struct Contract {
    void       * _Subscriber;
    UpdateAction _Action;

    // les 2 flags ci-dessous servent a temporiser les destructions de
    // contrats pendant qu'ils sont eux-meme executes
    short        _IsLocked;
    short        _DeleteRequest;
  };

private:

  // Recherche d'un indice de contrat, rend (-1) s'il n'y en a plus
  CATLONG32 NextContractFor(void * iSubscriber, CATLONG32 iFirstIndexToSearch = 0);
  
  // Suppression d'un seul contrat (et tass de la liste)
  // si iForceRemove=0, on temporise la suppression si _IsLocked=1
  void RemoveAction(CATLONG32 iContractIndex, short iForceRemove=0);

  // --------------------------------------------------------------------

  CATlsoAlgoElt     * _OwnerElt;
  CATlsoChainMaster * _OwnerChain;

  CATLONG32               _NbContracts;
  CATLONG32               _NbAllocated;
  Contract         * _List;
};

#endif
