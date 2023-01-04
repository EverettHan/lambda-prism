//===================================================================
//
// Copyright Dassault Systemes Provence 2005, all rights reserved
//
// LVL & HSW :  Header of the class CATSobVisuCreator 
//
// Date : 09 March 2005 
//===================================================================

#ifndef CATSobVisuCreator_H
#define CATSobVisuCreator_H

#include "CATSobVisu.h"
#include "CATBoolean.h"
#include "CATMathConstant.h"
#include "CATSobVisuStore.h"

class CATSobMesh;
class CATSobFace;
class CATSobVisuStore;


class ExportedByCATSobVisu CATSobVisuCreator
{
public:

//*************************************************************************//
// champs communs pour toutes les méthodes de tesselation et le stockage   //
//************************************************************************ //
 
	// constructeur de CATSobVisuCreator
		CATSobVisuCreator (CATSobMesh * iMesh = 0) ;
	// destructeur de CATSobVisuCreator
		virtual ~CATSobVisuCreator  ();
	// methode qui place le basemesh
		int SetSobMesh(CATSobMesh * iMesh);
	// methode qui fournit le niveau minimun de subdivion
		int SetLevel(int iLevel);
	// methode qui fournit le niveau maximum de subdivion
		int SetLevelMax(int iLevelMax);
	// methode qui permet de considerer ou non les edges
		int AddEdges(CATBoolean iWithEdges);
	// methode qui d'ajouter ou non la connectivité
		int AddConnectivity(CATBoolean iWithLink);
	// methode qui permet de considere ou non les points limites
		int SetMaskPt(CATBoolean iWithPtLimit);

	// methode qui permet de Passer en MonoRez
		int SetMonoResMode();

	// methode qui permet de Passer en MultiRez (par defaut deja)
		int SetMultiResMode();

		// methode qui fait la tesselation multires à sag
		int SetTesselationSag();
		
		//methode qui fait la tesselation multires avec le cone normal (par defaut deja)
		int SetTesselationConeNormal();


//***********************************************************//
// services de la vue externe de création de la tesselation   //
//********************************************************* //

	// méthode virtuelle qui place la tolerance angulaire
		virtual int SetAngularTol(CATAngle iAngularTol);

		virtual int SetFactorTol(double iSag);

		virtual int SetTol(CATAngle iAngularTol);

	// méthode virtuelle qui lance une méthode de tesselation
		virtual int Run(CATSobVisuStore * ioStore = 0);
	// méthode virtuelle qui récupère les résultats de la tesselation
		virtual int GetData(CATSobFace * iFace, float *&ioVertices, int &ioVerticesArraySize,
							float *&ioNormals, int &ioNormalsArraySize,int *&ioTriangleIndices, int &ioNbTriangle,
							int *&ioTriangleStripIndices, int &ioTriangleStrip,int *& ioVertexPerTriangleStrip,
							int *&ioTriangleFanIndices,int &ioNbTriangleFan,int *& ioNbVertexPerTriangleFan);
	

//*************************************************************************//
//variables pour la création de la tesselation                             //
//************************************************************************ //
 
	CATSobMesh *				     _Mesh              ;
	double                           _AngularTol        ;
	double							 _Sag				;
	int								 _Level             ;
	int								 _LevelMax          ;
	CATBoolean					     _WithEdges         ;
	CATBoolean					     _WithPtLimit       ;
	CATBoolean					     _WithLink          ;
	CATBoolean					     _MonoRes           ;
	CATBoolean					     _ConeNormal        ;

};

//********************************************************************************//
//fonctions qui exportent les méthode de tesselation et la procédure de stockage  //
//******************************************************************************** //

	// créer une tesselation mono résolution
		ExportedByCATSobVisu CATSobVisuCreator * CATCreateVisuMonoResRep(CATSobMesh * iMesh ) ;
	// créer une tesselation multi résolution
		ExportedByCATSobVisu CATSobVisuCreator * CATCreateVisuMultiResRep(CATSobMesh * iMesh) ;
#endif
