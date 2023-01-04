/* -*-C++-*- */

#ifndef CATlsoChainMaster_H
#define CATlsoChainMaster_H
/*  
=============================================================================

RESPONSABLE  : L. Marini

DESCRIPTION  : Administration d'une chaine d'objets algorithmiques
               (gestion commune = identification, creation / suppression
               gestion des zones de travail)

=============================================================================
*/
#include "CATDataType.h"
#include "CATlsoSubscription.h" // pour recuperer le typdef Action
#include "CATCGMVirtual.h"
#include "CATMathInline.h"
#include "PersistentCell.h"

class CATlsoAlgoElt;
class CATCGMOutput;
class CATGeometry;

//--------------------------------------------------------------------------

class ExportedByPersistentCell CATlsoChainMaster : public CATCGMVirtual
{

public:

  enum { MAXZTR = 3 }; // nombre maximum de zones de travail pour un objet
  enum { _DummyNameLength = 60 };
  
  CATlsoAlgoElt      * _Root;
  CATlsoAlgoElt      * _Oldest;
  CATlsoAlgoElt      * _OwningElt;     // 0 sauf si chaine encapsulee ds un algo-elt
  CATLONG32            _LastId;
  short                _KeepObjects;
  short                _GlobalDelete;  // 1 si on detruit tous les objets chaines
  short                _NbZtr;
  short                _IsZtrLocked[MAXZTR];
  char               * _ZtrPostIt[MAXZTR];
  char               * _ShortClassName;
  int                  _AttribKeyForModelObject;
  CATlsoSubscription * _Subscription;  // Gestion des effacements et remplacements
  
  CATLONG32            _NbElements; // Nombre d'objets dans la chaine d'aglo element

  // Stream destine a recevoir le dump complet de la classe en fin d'algo (debug)
  // ou le dump chronologique
  CATCGMOutput * _DumpDestinationBeforeBeingDeleted;
  CATCGMOutput * _ChronoDumpDestination;
  
  // Constructeur
  // iKeepObjects = 0 si les objets de la chaine ont vocation a etre detruits immediatement apres usage,
  // iKeepObjects = 1 si les objets de la chaine ont vocation a etre conserves jusqu'a la fin de l'algo
  CATlsoChainMaster(short iNbZtr = MAXZTR, short iKeepObjects = 1, char * iShortClassName = 0);

  // Copy-const non implemente (interdit)
  CATlsoChainMaster(CATlsoChainMaster& iOrig);

  //-------------------------------------------------------------------------------------------------------
  // Surcharge du new/delete
  //-------------------------------------------------------------------------------------------------------
  CATCGMNewClassArrayDeclare;
  
  // Destructeur
  ~CATlsoChainMaster();

  // Acces a l'objet proprietaire s'il existe
  INLINE void SetOwningElt(CATlsoAlgoElt * iOwner);

  // Gestion des destructions de tous les objets chaines
  INLINE short GetGlobalDelete() const;
  INLINE void SetGlobalDelete(short iVal=1);

  // Gestion du mode de conservation des objets (permet de garder ou non les
  // objets de type operateur apres usage pour des besoins de debug ou de journal)
  void SetKeepObjectsMode(short iMode);
  short GetKeepObjectsMode() const;

  // Ajout ou suppression d'un contrat d'abonnement a la chaine d'elements
#ifdef LAP_REMOVE_FOR_COVERAGE
  void AppendContract(void * iSubscriber,
                      CATlsoSubscription::UpdateAction iAction);
  void RemoveContract(void * iSubscriber);
#endif

  // Lecture du numero de l'objet le plus jeune (_Root, ou zero)
  CATLONG32 YoungestNum() const;

  // Gestion de la cle d'attribut (optionnelle, zero si sans interet) par laquelle
  // les objets modeles correspondant pointent vers les objets de la chaine
  INLINE int GetAttribKeyForModelObject();
  INLINE void SetAttribKeyForModelObject(int iKey);

  // Recherche de l'algo-elt associe a un objet modele
  CATlsoAlgoElt * GetAlgoEltAssociatedWith( CATGeometry * iObj) const;

  // Methodes de dump. DumpChain ne dumpe que les objets + recents que (chaines
  // par _Next au dela de ..) l'objet de numero iAfterNum s'il est present, et
  // filtre les objets par ipDumpIt (avec un contexte) s'il est fourni, ou dump
  // de l'objet numero iJustThisNumber si ce numero est > 0
  void DumpChain(CATCGMOutput & iOutStream,
                 int iAfterNum = 0,
                 short iLongDump = 0,
                 char (*ipDumpIt) (CATlsoAlgoElt*,void*) = 0,
                 void * iContextForIPDumpIt = 0,
                 CATLONG32 iJustThisNumber = 0);

  friend CATCGMOutput & operator<< (CATCGMOutput& s, const CATlsoChainMaster& iAdmin);

  // Dump d'un objet par son nom precede de l'adresse du contexte (debug)
  // ex: SearchObj("0x4682f600,VRep71");
  static void SearchObj(char * iInfo);

  // Verifications de base (ne doit premunir que des erreurs fatales)
  // Le niveau de "check" en entree augmente avec le cgmout (0 = rapide)
  // lance une exception si un probleme est detecte
  // ne doit jamais verifier les objets accroches ou le contexte (sinon boucle)
  virtual void CheckValid(short iCostLevel=0);

  // Recherche d'un objet par son numero 
  // (la version INLINE est accessible au debugger)
  INLINE CATlsoAlgoElt * GetAlgoElt(CATLONG32 iNum);
  CATlsoAlgoElt * ImplementGetAlgoElt(CATLONG32 iNum);

  INLINE CATLONG32 GetNbElements() const;
  
};

// Implementations INLINE
INLINE CATlsoAlgoElt * CATlsoChainMaster::GetAlgoElt(CATLONG32 iNum) {
  return ImplementGetAlgoElt(iNum); }

INLINE short CATlsoChainMaster::GetGlobalDelete() const {
  return _GlobalDelete; }

INLINE void CATlsoChainMaster::SetGlobalDelete(short iVal) {
  _GlobalDelete = iVal; }

INLINE int CATlsoChainMaster::GetAttribKeyForModelObject() {
  return _AttribKeyForModelObject; }

INLINE void CATlsoChainMaster::SetAttribKeyForModelObject(int iKey) {
  _AttribKeyForModelObject = iKey; }

INLINE void CATlsoChainMaster::SetOwningElt(CATlsoAlgoElt * iOwner) {
  _OwningElt = iOwner; }

INLINE CATLONG32 CATlsoChainMaster::GetNbElements() const {
  return _NbElements; }

#endif















