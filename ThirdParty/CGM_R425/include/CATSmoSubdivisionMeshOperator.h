//===================================================================================
// Copyright Dassault Systemes Provence 2003-2007, All Rights Reserved 
//===================================================================================
//
// CATSmoSubdivisionMeshOperator.h
//
//===================================================================================
//
// Usage notes: Base class for all mesh operators
//
//===================================================================================
//  June       2008 : UIQ : Ajout de Get de Liste pour l'operateur de Minimisation
//  November,  2007 : MMO : Correction des erreurs BAD004 (headerruler)
//  January,   2006 : RAQ : Modif pour nouveaux opérateurs topo sur CATSubdivMesh
//  January,   2004 : RAQ : Changement d'architecture des subdivisions
//  September, 2003 : JCV : Creation
//===================================================================================
#ifndef CATSmoSubdivisionMeshOperator_H
#define CATSmoSubdivisionMeshOperator_H

//Pour l'export
#include "CATSmoOperators.h"

//Objets Subdivision
#include "CATSobDiag.h"
#include "CATSobListOfEdge.h"
#include "CATSobListOfFace.h"
#include "CATListOfInt.h"
#include "CATBoolean.h"

//Divers
#include "CATBoolean.h"

class CATSobMesh;
class CATSobFace;
class CATSobEdge;
class CATSobVertex;

class CATSmoMeshTopoModifOperator;
class CATSmoDebugFactory;

class ExportedByCATSmoOperators CATSmoSubdivisionMeshOperator
{
public:
	
	//Destructeur
  virtual ~CATSmoSubdivisionMeshOperator();
	
  //Set d'un level pour versionning
  void SetVersionningLevel(const short iLevel);
	
	//Run de l'opérateur
  virtual CATSobDiag Run();
	
  //Diag de l'opérateur
  CATSobDiag GetDiag() const;

  //Obtention du mesh résultat
  CATSobMesh* GetResultMesh();

  //Test si le run a déjà été fait
  CATBoolean HasAlreadyRun() const;

  //Test si l'opérateur est multi-run
  CATBoolean IsMultiRun() const;

  //Désactivation du multi-run
  void DisableMultiRun();

  // Passe une factory de debug (instance de debug sera detruite par cet objet)
  void SetDebugFactory(CATSmoDebugFactory * iFactory);

  //Méthode de Get pour l'operateur de Minimisation
  CATListOfInt& GetListOldFaceForMinimise();
  CATListOfInt& GetListNewFaceForMinimise();
  CATListOfInt& GetListFaceTamponForMinimise();

  //Set pour remplir les listes de minimisation ou non
  void SetIsMinimisation(CATBoolean iIsMinimisation);

protected:

	//Constructeurs
  CATSmoSubdivisionMeshOperator(CATSobMesh* iMesh = 0);
  CATSmoSubdivisionMeshOperator(CATSobMesh* iMesh, CATSmoMeshTopoModifOperator* iTopoModifOpe);

  //Set du mesh en cas de constructeur par défault
  void SetCurrentMesh(CATSobMesh* iCurrentMesh);

  //L'opérateur est multi-run
  void SetMultiRunOperator(const CATBoolean iIsMultiRun = FALSE);

  //Run de l'implémentation
  virtual CATSobDiag RunOperator() = 0;

  //Création d'une face, à surcharger par les opérateurs topo
  virtual CATSobDiag CreateFace(CATLISTP(CATSobEdge)& iEdgesOfFace, CATSobFace*& oNewFace);

  // Creation de plusieurs faces, l'ordre de creation respectant la connexite
  // NE PAS surcharger dans l'opérateur topo
  virtual CATSobDiag MultiFacesCreation(const int iNbFacesToCreate,
                                        CATLISTP(CATSobEdge) iEdgesOfFacesToCreate[],
                                        CATSobFace** ioCreatedFaces = 0);

  //Ajout de plusieurs faces dans un mesh (sans join !!!)
  virtual CATSobDiag AddFaces(CATLISTP(CATSobFace)& iFacesToAdd, CATLISTP(CATSobFace)* ioCopiedFaces = 0);

  //Destruction d'une face, à surcharger par les opérateurs topo
  virtual CATSobDiag RemoveFace(CATSobFace* iFaceToRemove);

  //Création d'une edge, à surcharger par les opérateurs topo
  virtual CATSobDiag CreateEdge(CATSobVertex* iStartVertex, CATSobVertex* iEndVertex, CATSobEdge*& oCreatedEdge);

  //Destruction d'une edge, à surcharger par les opérateurs topo
  virtual CATSobDiag RemoveEdge(CATSobEdge* iEdgeToRemove);

  //Création d'un vertex, à surcharger par les opérateurs topo
  virtual CATSobDiag CreateVertex(const double* iVertexCoords, CATSobVertex*& oCreatedVertex);
  virtual CATSobDiag CreateVertex(const double iX, const double iY, const double iZ, CATSobVertex*& oCreatedVertex);

  //Destruction d'un vertex, à surcharger par les opérateurs topo
  virtual CATSobDiag RemoveVertex(CATSobVertex* iVertexToRemove);

  //Mise à jour du mesh courant
  CATSobDiag UpdateCurrentMesh();
	
	//Distance entre deux points
  double SquareDistance(const double Pt1[], const double Pt2[]);

  //Gestion du diag
  CATSobDiag SetDiag(const CATSobDiag iDiag);
  CATSobDiag ReturnErrorDiag(const char* iString, int iLine, const CATSobDiag iDiag, const CATBoolean iWithSetDiag=TRUE) const;
	
	//------ Data:
  short _VersionningLevel;
  CATSobMesh* _CurrentMesh;
  CATSmoDebugFactory* _DBGFactory;
  CATSobDiag _Diag;
  CATBoolean _OperatorAlreadyRun, _IsMultiRunOperator;

  CATSmoMeshTopoModifOperator* _TopoModifOpe;

  //List de tag de Face pour l'opérateur de Minimise
  CATListOfInt _TagOldFaceForMinimise;
  CATListOfInt _TagNewFaceForMinimise;
  CATListOfInt _FaceTamponForMinimise;
  CATBoolean _IsMinimisation;

  //Fonction pour incrémenter les listes liste de la minimisation
  void AppendOldFaceForMinimise(int iTag);
  void AppendNewFaceForMinimise(int iTag);
  void AppendFaceTamponForMinimise(int iTag);

  //Fonction qui retourne vrai si le tag existe dans la liste
  //des Faces Tampons et faux sinon
  CATBoolean ExistFaceTampon(int iTag);

};


#endif


