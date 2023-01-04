#ifndef CATConnexComponentForFastRun_h
#define CATConnexComponentForFastRun_h
/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2009
//==========================================================================

#include "ExportedByCATTopologicalObjects.h"

#include  "CATBaseUnknown.h" 
#include "CATCGMHashTable.h"
#include "CATCGMHashTableWithAssoc.h"
#include "ListPOfCATFace.h"
class CATEdge;
class CATFace;
class CATCGMOutput;



class ExportedByCATTopologicalObjects CATConnexComponentForFastRun
{

  // Composante Connexe d'edges qui delimitent une zone modifie par l'operation.
  // Dans l'approche Black Box de Fast Update, chaque composante connexe delimite un resultat recuperable. 
  // Plusieurs resultats entoures par la meme composante connexe ne pourront pas etre separes.

public :

  CATConnexComponentForFastRun(int iExpectedNumerOfEdges = 0);
  virtual ~CATConnexComponentForFastRun();

  // Insert une edge dans la composante connexe.
  int Insert(CATEdge * iEdge);

  // Renvoie la HashTable des edges de la composante.
  CATCGMHashTable * GetEdgesHT();
  CATBoolean LocateEdge(CATEdge * iEdge);

  // Ajoute une Face a la HashTable des Faces crees associees.
  void AddCreatedFace(CATFace * iFace);
  void AddCreatedFaces(CATLISTP(CATFace)&  listFaces);

  // Ajoute une Face a la HashTable des Faces supprimees associees.
  void AddDeletedFace(CATFace * iFace);

  // Renvoie la HashTable des Faces crees associees.
  CATCGMHashTable * GetCreatedFaces();

  // Renvoie la HashTable des Faces supprimees associees.
  CATCGMHashTable * GetDeletedFaces();

  // Test si this et iComponent ont des extremites d'edge en commun.
  //CATBoolean ShareEdgesExtremitiesWith(CATConnexComponentForFastRun * iComponent);

  // Renvoie une HT des extremites d'edge qui composent les extremites de la composante 
 // CATCGMHashTable * GetExtremities();

  // Renvoie HT des Vertices appartenant a la composante
  CATCGMHashTable * GetVertices();

  // Renvoie le nombre d'Edges qui composent la composante.
  int Size();

  // Renvoie l'Edge a la position iPos.
  // iPos va de 0 a Size() - 1. 
  CATEdge * GetEdge(int iPos);

  // Affiche le contenu de la composante.
  void  Dump(CATCGMOutput& os);
  
private :
  
  // La HashTable des edges de la composante connexe.
  CATCGMHashTable * _EdgesHT;

  // La HashTable des Faces crees associees a la composante.
  // Chaque Face cree touche une et une seule composante. Les Faces crees sont utiles pour identifier les composantes connexes.
  CATCGMHashTable * _AssocCreatedFacesHT;

  // La HashTable des Faces supprimees associees a la composante.
  // Chaque Face supprimees touche une et une seule composante. Les Faces crees sont utiles pour identifier les composantes connexes.
  CATCGMHashTable * _AssocDeletedFacesHT;
  
};
#endif
