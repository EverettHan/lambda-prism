#ifndef CATTopToolsRemoveCellFromBody_H
#define CATTopToolsRemoveCellFromBody_H
//--------------------------------------------------------------------------------------------------
// CATTopToolsRemoveCellFromBody : Suppression "elegante" d'une cellule d'un Body
//
//  Il s'agit en fait d'un "sous-operateur" qui n'effectue qu'une suppression partielle 
//       --> pas de Completed/Freeze au GetResult()
//       --> pas de gestion de suivi Topologique (pas de CATCGMJournalList)
//
//  Dans la premiere version, seules les cellules de Type Face ou Edge sont admises
//  Le Body doit etre modifiable
//
//   Edge : les deux Vertex sont merges s'ils sont differents
//
//   Face : Seules deux Edges bordantes sont gerees dans la premiere version,
//          et ces deux Edges sont mergees si elles sont differentes
//
//---------------------------------------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES  2000
// 20 11 2000  Creation pour faire disparaire CATTopBodyTools::RemoveEdge() et CATTopBodyTools::RemoveFace()
//             ne gerant pas le versionning
//---------------------------------------------------------------------------------------------------------
#include "ExportedByCATTopologicalObjects.h"
#include "CATTopOperator.h"
#include "CATTopData.h"
#include "CATTopDefine.h"
#include "CATBoolean.h"

class CATBody;
class CATCell;

class CATTopToolsRemoveCellFromBody;

//--------------------------------------------------------------------------------------------------
// Constructeur de l'outil topologique
//--------------------------------------------------------------------------------------------------

ExportedByCATTopologicalObjects CATTopToolsRemoveCellFromBody *CATCreateTopToolsRemoveCellFromBody
(CATBody * iBody, CATCell * iCell, const CATTopData & iTopData);

//--------------------------------------------------------------------------------------------------
// L'outil topologique proprement dit
//--------------------------------------------------------------------------------------------------

class ExportedByCATTopologicalObjects CATTopToolsRemoveCellFromBody : public CATTopOperator
{
  
public:

  // copy constructeur et affectation (lancent une exception), ne pas les appeler
  CATTopToolsRemoveCellFromBody(const CATTopToolsRemoveCellFromBody & iOrig);
  CATTopToolsRemoveCellFromBody & operator= (const CATTopToolsRemoveCellFromBody & iOrig);

protected :
  CATTopToolsRemoveCellFromBody(CATGeoFactory *, const CATTopData  & iTopData);

};


#endif

