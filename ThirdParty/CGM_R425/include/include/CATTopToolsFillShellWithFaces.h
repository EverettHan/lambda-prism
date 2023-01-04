#ifndef CATTopToolsFillShellWithFaces_H
#define CATTopToolsFillShellWithFaces_H
//--------------------------------------------------------------------------------------------------
// CATTopToolsFillShellWithFaces : Rattachement de Faces jointives sous un Shell
//
//  Il s'agit en fait d'un "sous-operateur" qui n'effectue qu'une construction partielle 
//       --> pas de creation d'objets topologiques (uniquement des operations Shell->AddCell() )
//       --> pas de Completed/Freeze au GetResult()
//       --> pas de gestion de suivi Topologique (pas de CATCGMJournalList)
//
//  Les Faces sont prises de la Liste de Faces specifiee en entree,
//  Le plus grand domaine connnexe possible est construit avec la restriction suivante :
//     les edges a plus de deux faces incidentes ne sont pas gerees (premiere version)
//  Les Faces qui participent a ce resultat sont supprimees de la Liste d'entree
//
//---------------------------------------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES  2000
// 20 11 2000  Creation pour faire disparaire CATTopTools::MakeShellFromFaces() ne gerant pas le versionning
//---------------------------------------------------------------------------------------------------------
#include "ExportedByCATTopologicalObjects.h"
#include "CATTopOperator.h"
#include "ListPOfCATFace.h"
#include "CATTopData.h"
#include "CATTopDefine.h"

class CATBody;
class CATFace;
class CATShell;
class CATTopToolsFillShellWithFaces;

//--------------------------------------------------------------------------------------------------
// Constructeur de l'outil topologique
//--------------------------------------------------------------------------------------------------

ExportedByCATTopologicalObjects CATTopToolsFillShellWithFaces *CATCreateTopToolsFillShellWithFaces
(CATShell          * iShell, 
 ListPOfCATFace    & ioFaces, 
 CATFace           * iFirstFace,
 CATOrientation      iFirstFaceOrientation,
 const CATTopData  & iTopData);

//--------------------------------------------------------------------------------------------------
// L'outil topologique proprement dit
//--------------------------------------------------------------------------------------------------

class ExportedByCATTopologicalObjects CATTopToolsFillShellWithFaces : public CATTopOperator
{
  
public:

  // copy constructeur et affectation (lancent une exception), ne pas les appeler
  CATTopToolsFillShellWithFaces(const CATTopToolsFillShellWithFaces & iOrig);
  CATTopToolsFillShellWithFaces & operator= (const CATTopToolsFillShellWithFaces & iOrig);

protected :
  CATTopToolsFillShellWithFaces(CATGeoFactory *, const CATTopData  & iTopData);

};


#endif

