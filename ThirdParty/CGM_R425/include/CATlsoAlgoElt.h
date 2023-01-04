/* -*-C++-*- */

#ifndef CATlsoAlgoElt_H
#define CATlsoAlgoElt_H

#include "CATlsoChainMaster.h"
#include "CATThrowForNullPointer.h"
#include "CATTopOpInError.h"
#include "CATCGMVirtual.h"
#include "CATDataType.h"
#include "PersistentCell.h"
#include "CATMathInline.h"

//#define LAP_REMOVE_FOR_COVERAGE ?? Pour rebrancher les subcriptions

class CATlsoContext;
#ifdef LAP_REMOVE_FOR_COVERAGE
class CATlsoSubscription;
#endif
class CATCGMOutput;
class CATCGMStream;
class CATPersistentOperator;
class CATGeoFactory;
class CATlsoStreamableAlgoElt;
class CATlsoFuzzyExtrapolComplexShellToExtrapolate;

class ExportedByPersistentCell CATlsoAlgoElt : public CATCGMVirtual
{
  
public:

  // Copy-constructeur et operateur = (affectation) dans la meme chaine
  // Attention, ces methodes n'etant pas heritees, elles devront etre
  // explicitement appelees dans les classes derivees (via les listes
  // d'initialisation pour les constructeurs, de base ou de copie)
  CATlsoAlgoElt(CATlsoAlgoElt& iOrig);
  CATlsoAlgoElt& operator= (const CATlsoAlgoElt& iRight);

  //-------------------------------------------------------------------------------------------------------
  // Surcharge du new/delete
  //-------------------------------------------------------------------------------------------------------
  CATCGMNewClassArrayDeclare;

  // Destructeur: ote l'element de la chaine mais ne decremente pas le compteur
  // afin de ne pas risquer de re-attribuer un vieux numero a un futur objet
  virtual ~CATlsoAlgoElt();

  // Test d'identite logique
  INLINE short operator == (const CATlsoAlgoElt &iReference) const;

  // Acces a la racine, ou a l'objet operateur, ou a l'administrateur
  CATlsoContext * GetContext() const;
  INLINE CATlsoAlgoElt * GetRoot() const;
  INLINE CATlsoChainMaster * GetAdmin() const;
       
  // Acces au numero d'identification au sein de la chaine, et au numero absolu
  INLINE CATLONG32 GetNum() const;
  INLINE CATLONG32 GetUTag() const;

  // Dump du prefixe (# suivi de la sequence des numeros d'objets proprietaires)
  INLINE char* Prefix() const;

  // Compteur d'objets de la classe
  static CATLONG32 GetCount(CATlsoChainMaster * iAdmin);
  
  // Recherche de l'element suivant dans une classe donnee
  static CATlsoAlgoElt * NextElt(const CATlsoChainMaster * iAdmin,
                                const CATlsoAlgoElt * iCur);

  // Recherche de l'element precedent dans une classe donnee
  static CATlsoAlgoElt * PrevElt(const CATlsoChainMaster * iAdmin,
                                const CATlsoAlgoElt * iCur);

  static void RemoveEltFromChain(CATlsoAlgoElt *& ioAlgoElt, CATBoolean iDeleteElt=TRUE);

#ifdef LAP_REMOVE_FOR_COVERAGE
  // Ajout ou suppression d'un contrat d'abonnement individuel
  void AppendContract(void * iSubscriber,
                      CATlsoSubscription::UpdateAction iAction);
  void RemoveContract(void * iSubscriber);

  // Information des abonnes pour un remplacement d'objet 
  // (la suppression est directement geree par le destructeur)
  void TellSubscribersIAmReplaced(CATLONG32 iNbNewElts,
                                  CATlsoAlgoElt ** iListOfNewElts);
#endif

  // Suppression de tous les elements d'une chaine donnee
  // (l'objet administrateur n'est pas detruit, mais "resette")
  static void DeleteAllObjects(CATlsoChainMaster * iAdmin);

  // Initialisation et lecture des zones de travail (iZtrNum commence en 1)
  INLINE void SetZtr(short iZtrNum, CATINTPTR iVal); // 64 Bit CATLONG32 --> CATINTPTR 07/08/03 ALV
  INLINE CATINTPTR GetZtr(short iZtrNum) const;
  // Pour la methode qui suit, iZtrNum=0 signifie "toutes les ztravs"
  static void SetZtrForAllObjects(CATlsoChainMaster * iAdmin, 
                                  short iZtrNum=0, CATINTPTR iVal=0);

  // Reservation d'une zone de travail (methodes statiques)
  static short GetFreeZtrNum(CATlsoChainMaster * iAdmin);
  static void LockZtr(CATlsoChainMaster * iAdmin, short iZtrNum,
                      char * iDebugPostIt=NULL);

  // Liberation d'une zone de travail (methode statique):
  // iZtrNum=0 libere toutes les zones. Si le post-it est precise, on le 
  // compare a celui qui a ete depose a la reservation de la zone
  static void UnlockZtr(CATlsoChainMaster * iAdmin, short iZtrNum=0,
                        char * iDebugPostItControl=NULL); 

  // Remplacement d'une valeur donnee d'une ztrav par une autre pour tous
  // les objets de la classe
  static void ReplaceZtr(CATlsoChainMaster * iAdmin, short iZtrNum, 
  //+++ PR64
  //                     CATLONG32 iOldVal, CATLONG32 iNewVal);
                         CATLONGPTR iOldVal, CATLONGPTR iNewVal);
  //+++ PR64

  // Acces a un objet par son numero (numero > = 1)
  // la version INLINE rend un objet de la meme chaine (non statique)
  static CATlsoAlgoElt * GetAlgoElt(CATlsoChainMaster * iAdmin, CATLONG32 iNum);
  INLINE CATlsoAlgoElt * GetAlgoElt(CATLONG32 iNum);

  // Dump
  char * Logo() const; // rend nom abrege de la classe (facilite debug)
  friend ExportedByPersistentCell CATCGMOutput& operator<< (CATCGMOutput& s, const CATlsoAlgoElt& iObj);
  virtual void DumpObj(CATCGMOutput& s, short iLongDump=0,
                       short iZtrNoDump=0) const = 0;

  // Le dump de toute la classe prend en argument optionnel un pointeur sur
  // fonction (ipDumpIt) qui prend un CATlsoAlgoElt* et un void* et rend un
  // char=0 s'il ne faut pas dumper cet objet-la, et =1 sinon; le void* sert
  // a passer en entree des infos de contexte a la fonction de filtrage, qui
  // doivent alors etre comuniquees en dernier argument de DumpClass
  static void DumpClass(CATlsoChainMaster * iAdmin, short iLongDump=0,
                        char (*ipDumpIt) (CATlsoAlgoElt*,void*) = NULL,
                        void * iContextForIPDumpIt = NULL);

  // Idem que DumpClass avec la possibilite de choisir un stream
  static void DumpClassOnStream(CATCGMOutput & iOutStream, 
                        CATlsoChainMaster * iAdmin, short iLongDump=0,
                        char (*ipDumpIt) (CATlsoAlgoElt*,void*) = NULL,
                        void * iContextForIPDumpIt = NULL);

  // Dump chronologique de toutes les classes
  static void ChronoDumpClassesOnStream(CATCGMOutput & iOutStream, CATlsoContext * iContext, short iLongDump=0);

  // Verifications de base (ne doit premunir que des erreurs fatales)
  // Le niveau de "check" en entree augmente avec le cgmout (0 = rapide)
  // lance une exception si un probleme est detecte
  virtual void CheckValid(short iCostLevel=0);
  static void CheckAllObjects(CATlsoChainMaster * iAdmin, short iCostLevel=0);

  // Rend l'objet lui-meme s'il appartient a la chaine donnee
  const CATlsoAlgoElt * SafeCastToChain(const CATlsoChainMaster * iTargetChain) const;

  INLINE virtual CATlsoStreamableAlgoElt * GetAslsoStreamableAlgoElt() ;

protected:

  // Constructeur recevant l'objet operateur et la structure (agregee par cet
  // objet operateur) qui federe toutes les donnees administratives pour gerer
  // une chaine d'objets algorithmiques dans le contexte Shell / Thickness:
  // racine de la chaine, compteur d'objets, reservations des zones de travail.

  // Le constructeur est protege afin de rendre la classe virtuelle pure.
  CATlsoAlgoElt(CATlsoContext * iContext, CATlsoChainMaster * iAdmin);

  // Donnees membres:
  CATLONG32                _Num;
  CATLONG32                _UTag;
  CATlsoAlgoElt     *  _Next;
  CATlsoAlgoElt     *  _Prev;
  CATlsoContext     *  _Context;
  CATlsoChainMaster *  _Admin;
#ifdef LAP_REMOVE_FOR_COVERAGE
  CATlsoSubscription * _IndividualSubs;
#endif
  CATLONGPTR          _Ztr[CATlsoChainMaster::MAXZTR]; //64 Bits 20/08/03 ALV
};


// Classe destinee aux iostream
class ExportedByPersistentCell CATlsoObjName 
{
public:
  INLINE CATlsoObjName(CATLONG32 iLength, const CATlsoAlgoElt * iObj, short iDumpOwners, short iLengthIsTotal=1);
  static short GetNbDigitsForPositiveNumber(CATLONG32 iNum);
  friend ExportedByPersistentCell CATCGMOutput& operator<< (CATCGMOutput& s, const CATlsoObjName & iObj);
  
private:
  CATLONG32             _DumpLength;
  short                 _TotalLength;
  short                 _DumpOwners;
  const CATlsoAlgoElt * _ObjToDump;
};


INLINE CATlsoObjName::CATlsoObjName(CATLONG32 iLength, const CATlsoAlgoElt * iObj, short iDumpOwners, short iLengthIsTotal) :
_DumpLength(iLength), _TotalLength(iLengthIsTotal), _DumpOwners(iDumpOwners), _ObjToDump(iObj) {
}

// Implementations INLINE pour CATlsoAlgoElt

INLINE CATlsoStreamableAlgoElt * CATlsoAlgoElt::GetAslsoStreamableAlgoElt() {
  return NULL; }

INLINE short CATlsoAlgoElt::operator == (const CATlsoAlgoElt &iReference) const {
  if (_Num==iReference._Num) return 1; else return 0; }

INLINE CATlsoAlgoElt * CATlsoAlgoElt::GetRoot() const { 
  return (_Admin) ? _Admin -> _Root : NULL; }

INLINE CATlsoChainMaster * CATlsoAlgoElt::GetAdmin() const {
  return _Admin; }

INLINE CATLONG32 CATlsoAlgoElt::GetUTag() const {
  return _UTag; }

INLINE CATLONG32 CATlsoAlgoElt::GetNum() const {
    if (_Num<=0)
      CATThrowForNullPointerReturnValue(0);
    return _Num; }

INLINE void CATlsoAlgoElt::SetZtr(short iZtrNum, CATINTPTR iVal) {
  if (iZtrNum<1 || iZtrNum>CATlsoChainMaster::MAXZTR)
    CATThrowForNullPointer();
  _Ztr[iZtrNum-1] = iVal; }

INLINE CATINTPTR CATlsoAlgoElt::GetZtr(short iZtrNum) const {
  if (iZtrNum<1 || iZtrNum>CATlsoChainMaster::MAXZTR)
    CATThrowForNullPointerReturnValue(0);
  return  _Ztr[iZtrNum-1];
}

// ---------------------------------------- //
//  DEFINE  DEFINE  DEFINE  DEFINE  DEFINE  //
//  MACRO   MACRO   MACRO   MACRO   MACRO   //
// ---------------------------------------- //

#define OBJNUM(obj) (( obj ) ? ( obj -> GetNum()) : 0 )

// OBJNAM et OBJNAME ne doivent etre utilises que dans une ecriture, pour y inserer
// le nom de l'objet (obj est un CATlsoAlgoElt*, mais peut etre "NULL"), sur x caracteres
// pour OBJNAM et sur x+lon caracteres pour OBJNAME, les x premiers servant au nom
// (_ShortClassName) de la classe si l'objet est non nul
#define OBJNAME(lon,obj) CATlsoObjName( lon , obj ,1,0)
#define OBJNAM(lon,obj) CATlsoObjName( lon , obj ,1,1)

// Implementation commune aux methodes statiques "SafeCast" en un type directement
// associe a un administrateur de chaine, ou un de ses sur-types (ex: GEdge). Cette
// macro ne doit pas etre utilisee un sous-type de type chaine (tel que bipoint par
// exemple, il faut passer dans ce cas par une fonction virtuelle donc non statique)
#define ImplementSafeCastUpChain( motherName , motherShortName , sonName , sonAdminName ) \
  motherName * sonName::SafeCastTo##motherShortName(const CATlsoAlgoElt * iElt) \
{                                            \
  motherName * ret = 0;                      \
  if (iElt)                                  \
    ret = ( motherName *)                    \
    (iElt -> SafeCastToChain(iElt -> GetContext() -> Get##sonAdminName##Admin())); \
  return ret; \
}

//----------------------------------------------------------------------------
// Generateur du code d'acces a l'objet algo associe a un objet modele
#define ImplementGetObjAssociatedWith( clname, mdlname, getadm ) \
  clname * clname::GetObjAssociatedWith(CATlsoContext * iContext, mdlname * iModelObj) {\
  CATlsoChainMaster * adm = iContext -> getadm();\
  CATlsoAlgoElt * ret = adm -> GetAlgoEltAssociatedWith(iModelObj);\
  return ( clname *)(ret);\
}
//----------------------------------------------------------------------------

#endif
  
