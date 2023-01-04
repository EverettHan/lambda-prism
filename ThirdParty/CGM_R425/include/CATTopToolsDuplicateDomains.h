#ifndef CATTopToolsDuplicateDomains_H
#define CATTopToolsDuplicateDomains_H
//--------------------------------------------------------------------------------------------------
// CATTopToolsDuplicateDomains : Duplication de domaines d'un type precis avec par default inversion
//
//  Il s'agit en fait d'un "sous-operateur" qui n'effectue qu'une construction partielle 
//       --> uniquement des creations de domaines du type specifiee
//       --> pas de Completed/Freeze au GetResult()
//       --> pas de gestion de suivi Topologique (pas de CATCGMJournalList)
//
//  On Duplique tous les Domaines du Body d'entree correspondant au critere de dimension
//  en recuperant tous les cellules
//
//---------------------------------------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES  2000
// 20 11 2000  Creation pour faire disparaire CATTopBodyTools::InvertWire() ne gerant pas le versionning
//---------------------------------------------------------------------------------------------------------
#include "ExportedByCATTopologicalObjects.h"
#include "CATTopOperator.h"
#include "ListPOfCATDomain.h"
#include "CATTopData.h"
#include "CATTopDefine.h"
#include "CATBoolean.h"

class CATBody;
class CATTopology;

class CATTopToolsDuplicateDomains;
class CATCGMJournalList;

//--------------------------------------------------------------------------------------------------
// Constructeur de l'outil topologique
//--------------------------------------------------------------------------------------------------

ExportedByCATTopologicalObjects CATTopToolsDuplicateDomains *CATCreateTopToolsDuplicateDomains
(
 CATBody               * inputBody,                   // Body avec domaines
 short                   iContainedCellsDimension,    // LowDimension des domains a prendre en compte
 short                   iContainingCellDimension,    // HighDimension des domaines a prendre en compte
 CATLISTP(CATDomain)   & iCreatedDomains,             // Liste tous les domaines dupliques
 const CATTopData      & iTopData,
 CATTopology           * iBodyOrCell = NULL,  // Pour le rattachement des nouveaux Domaines
 const CATBoolean        iWithInvert = TRUE
);

//--------------------------------------------------------------------------------------------------
// L'outil topologique proprement dit
//--------------------------------------------------------------------------------------------------

class ExportedByCATTopologicalObjects CATTopToolsDuplicateDomains : public CATTopOperator
{
  
  CATCGMVirtualDeclareClass(CATTopToolsDuplicateDomains);
public:

  // copy constructeur et affectation (lancent une exception), ne pas les appeler
  CATTopToolsDuplicateDomains(const CATTopToolsDuplicateDomains & iOrig);
  CATTopToolsDuplicateDomains & operator= (const CATTopToolsDuplicateDomains & iOrig);

protected :
  CATTopToolsDuplicateDomains(CATGeoFactory *, const CATTopData  & iTopData);
  CATTopToolsDuplicateDomains(CATGeoFactory *, CATCGMJournalList * iJournal);

};


#endif

