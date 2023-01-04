#ifndef CATConnexComponentManager_h
#define CATConnexComponentManager_h
/*-*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2009
//==========================================================================

#include "ExportedByCATTopologicalObjects.h"

#include "CATCGMHashTable.h"
#include "CATCGMHashTableWithAssoc.h"
#include "CATCollec.h"
#include "CATBoolean.h"

class CATListPtrCATFace;
class CATCGMJournalList;
class CATConnexComponentForFastRun;
class CATEdge;
class CATFace;
class CATCellHashTable;
class CATTopology;
class CATDrawerCollector;
class CATCGMOutput;
class CATFaceHashTable;


class ExportedByCATTopologicalObjects CATConnexComponentManager
{

  // CATConnexComponentManager represente un ensemble de CATConnexComponentForFastRun, 
  // et les operations usuelles associees. 

public :
 
  CATConnexComponentManager();
  virtual ~CATConnexComponentManager();

  // Calcule des composantes connexes du graphe dont les sommets sont les elements de iSommets et les arretes sont donnees par iConnexions.
  // Les elements de iConnexions sont des Vertex. Pour chaque element, l'element associe est une CATCGMHashTable des Edges du graphe qui touche le Vertex courant.
  int ComputeConnexComponentsWithConnexions(CATDrawerCollector * iGraph, CATLISTP(CATFace)& iCreatedFaces, CATLISTP(CATFace)& iDeletedFaces);
  int ComputeConnexComponentsWithConnexions(CATDrawerCollector * iGraph, CATFaceHashTable * iCreatedFaces, CATFaceHashTable * iDeletedFaces);

  // Creer les liens entre les composantes connexes de Old Input et celles de Old Result.
  //int Compute_Relation_C_Cprime(CATConnexComponentManager * ORComponents, CATLISTP(CATFace) &createdFaces, CATCGMJournalList * oldJournal,  CATLISTP(CATFace) &modifiedFacesFromJournal);

  // Ajoute pComponent a l'ensemble.
  void AddComponent(CATConnexComponentForFastRun * pComponent);

  // Ajoute une composante et les composantes liees
  //void AddComponentAndLinkedComponents(CATConnexComponentForFastRun * pComponent);

  // Renvoie la composante connexe qui contient iEdge.
  CATConnexComponentForFastRun * GetCorrespondingComponent(CATEdge * iEdge);

  // Renvoie la composante connexe qui touche les faces de iFacesList.
  //CATConnexComponentForFastRun * GetCorrespondingComponent(CATLISTP(CATFace) &iFacesList);

   // Renvoie la composante connexe qui a pour face cree associee iCreatedFace.
  CATConnexComponentForFastRun * GetAssociatedComponent(CATFace * iCreatedFace);

  // Identifie a quelles composantes connexes correspondent les faces creees.
  //int Compute_Relation_CreatedFace_Cprime(CATLISTP(CATFace) &createdFaces, CATCGMJournalList * oldJournal);

  // Renvoie le nombre de composantes connexes.
  int Size();

  // Renvoie la composante numero i.
  CATConnexComponentForFastRun * GetComponent(int i);

  // TRUE si iComp est contenu dans l'ensemble.
  // FALSE sinon.
  CATBoolean Locate(CATConnexComponentForFastRun * iComp);

  // TRUE si iFace touche une composante connexe de l'ensemble.
  // FALSE sinon.
  //CATBoolean Touche(CATFace * iFace);

  void RemoveAll();

  //void SetVirtualEdgesHastTables(CATCGMHashTableWithAssoc * iVirtualEdgesHT1, CATCGMHashTableWithAssoc * iVirtualEdgesHT2);
  void RemoveDegeneratedComponents();//void RemoveSingletons();
  //CATCellHashTable * GetVirtualEdges(CATTopology * iTopo);
  CATCGMHashTable * GetTouchedComponents(CATFace * iFace);

  void  Dump(CATCGMOutput& os);

  void GatherIsolatedComponents(CATCGMJournalList * iOldJournal);

  
private :

  // Place les elements de iComp2 dans ioComp1)
  void Merge(CATConnexComponentForFastRun * ioComp1, CATConnexComponentForFastRun * iComp2);

  // La HashTable des CATConnexComponentForFastRun. 
  CATCGMHashTable * _ComponentsHT;

  // CATCGMHashTableWithAssoc dont les elements sont des CATEdge et les elements associes des CATConnexComponentForFastRun.
  // Permet de trouver rapidemet la composante connexe qui contient une edge connue.
 // CATCGMHashTableWithAssoc * _RelationEdgeConnexComponent;

  // Pour gerer la memoire : on detruit les composantes qui ont ete calculees avec this.
  CATBoolean _ComponentsToDelete;

  void Init();
  void Destroy();
  CATCGMHashTableWithAssoc * _Edges_VirtualEdgesHT1;
  CATCGMHashTableWithAssoc * _Edges_VirtualEdgesHT2;
  CATCGMHashTableWithAssoc * _VirtualEdges_EdgesHT1;
  CATCGMHashTableWithAssoc * _VirtualEdges_EdgesHT2;

  //CATEdge * GetVirtualEdge(CATEdge * iEdge);
  //CATEdge * GetRealEdge(CATEdge * iEdge);


};
#endif
