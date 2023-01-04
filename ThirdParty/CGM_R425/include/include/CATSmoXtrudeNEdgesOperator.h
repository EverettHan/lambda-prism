//======================================================================
// Copyright Dassault Systemes Provence 2006, all rights reserved 
//======================================================================
//
// CATSmoXtrudeNEdgesOperator.h
//
//======================================================================
//
// Usage notes:
//
//======================================================================
// November,     2020 : RBD : Ajout methode GetImgPoint()
//                            DEPRECATED : Use CATSmoXtrudeNEdgesParameter instead
// June,         2020 : RBD : Ajout methode SetExtrapoleAlongMeshLines() for edges extrusion along mesh lines (STANDARD mode) 
//                            DEPRECATED : Use CATSmoXtrudeNEdgesParameter instead
// November,     2017 : RBD : Ajout set multi-paramètres pour la symétrie, d'après code RAQ
// February,     2017 : RBD : STANDARD mode : SetExtrapoleFixedVector
// January,      2011 : RBD : STANDARD mode : SetLength et GetLentgh
// October,      2010 : RBD : Report CXR20
// April,        2010 : RBD : ADVANCED mode pour BMW = Draft direction + Angle + Length
// December,     2006 : RBD : Creation
//======================================================================
#ifndef CATSmoXtrudeNEdgesOperator_H
#define CATSmoXtrudeNEdgesOperator_H

//Pour l'héritage
#include "CATSmoSubdivisionMeshOperator.h"

//Pour l'export
#include "CATSmoOperators.h"

//Objets subdivision
#include "CATSobDiag.h"
#include "CATSobEdge.h"
#include "CATSobListOfEdge.h"
#include "CATSobFace.h"
#include "CATSobListOfFace.h"
#include "CATMathDirection.h"
#include "CATBoolean.h"

#include "CATLib.h" //Monocodage OS

//STL
#ifdef _AIX_SOURCE
#undef throw
#endif  //_AIX_SOURCE
#include <vector>

class CATMathVector;
class CATMathPlane;
class CATSobMesh;
class CATSmoMeshTopoModifOperator;
class CATSmoXtrudeNEdgesParameter;



class ExportedByCATSmoOperators CATSmoXtrudeNEdgesOperator: public CATSmoSubdivisionMeshOperator
{
public:

  //Destructeur
  virtual ~CATSmoXtrudeNEdgesOperator();

  //Mono-parameter set : ipParam is addreferenced by the operator, it is also released with it.
  virtual void SetEdgesToXtrude(CATSmoXtrudeNEdgesParameter* ipParam) = 0;

  //Multi-parameters set : parameters are all addreferenced by the operator, they're also released with it.
  virtual void SetEdgesToXtrude(const std::vector<CATSmoXtrudeNEdgesParameter*>& iParams) = 0;

#if defined(_WINDOWS_SOURCE) || defined(_LINUX_SOURCE)
  //Multi-parameters set : parameters are not addreferenced by the operator, but the operator will release them.
  //This signature is useful if you just want to give the parameters to the operator and then you don't care about them anymore.
  virtual void SetEdgesToXtrude(std::vector<CATSmoXtrudeNEdgesParameter*>&& ioParams) = 0;
#endif  //_WINDOWS_SOURCE || _LINUX_SOURCE


  //DEPRECATED : Use CATSmoXtrudeNEdgesParameter instead
  //Set d'une liste d'aretes a extruder
  virtual void SetEdgesToXtrude(CATLISTP(CATSobEdge)* iEdgesToXtrude) = 0;

  //DEPRECATED : Use CATSmoXtrudeNEdgesParameter instead
  // Set STANDARD mode : with or without fixed direction (Default)
  virtual void SetStandardMode() = 0;

  //DEPRECATED : Use CATSmoXtrudeNEdgesParameter instead
  // Set ADVANCED mode : Drafting Direction + Angle + Length
  virtual void SetAdvancedMode() = 0;

  //DEPRECATED : Use CATSmoXtrudeNEdgesParameter instead
  //------ Poids  :
  // Set Weight and Sharpness (Poids) sur les aretes du profil selectionne (STANDARD and ADVANCED mode)
  // iWeight : Le poids varie entre 0 (defaut) et +100.
  // iSmooth : Smooth (default) or not smooth the edges (= Sharpness)
  virtual void SetInputEdgesWeight(const int iWeight = 0, const CATBoolean iSmooth = 1) = 0;

  //DEPRECATED : Use CATSmoXtrudeNEdgesParameter instead
  //------ Activation du poid automatique sur les vertex (STANDARD and ADVANCED mode) :
  virtual void SetAutoWeight(const CATBoolean iAutoWeight = 1) = 0;

  //DEPRECATED : Use CATSmoXtrudeNEdgesParameter instead
  //------ Nombre de secteurs de la subdivision (STANDARD and ADVANCED mode)
  virtual void SetNbSectors(const int iNbSectors = 1) = 0;

  //DEPRECATED : Use CATSmoXtrudeNEdgesParameter instead
  //------ Get : image d'un point sur 1 arête par extrusion  
  virtual CATSobDiag GetImgPoint(const CATSobEdge* iEdge, const double iLambda, CATMathPoint &oEdgePoint, CATMathPoint &oImgPoint, CATMathDirection &oInitialXtrudeDir) = 0;

  //
  //-=-=-=-=-=-=-=- STANDARD mode -=-=-=-=-=-=-=-
  //DEPRECATED : Use CATSmoXtrudeNEdgesParameter instead
  //------ Length  :
  // Set Length (STANDARD mode only)
  virtual CATSobDiag SetLength(const CATSobEdge* iEdge, const double iLength) = 0;

  //DEPRECATED : Use CATSmoXtrudeNEdgesParameter instead
  // Get Length (STANDARD mode only)
  virtual void GetLength(const CATSobEdge* iEdge, double &oLength) = 0;
 
  //DEPRECATED : Use CATSmoXtrudeNEdgesParameter instead
  //------ fixed direction  :
  // Set a fixed direction for extrusion
  virtual CATSobDiag SetExtrapoleFixedVector(CATMathVector* iFixedVector = NULL) = 0;
 
  //DEPRECATED : Use CATSmoXtrudeNEdgesParameter instead
  // Get a pre-computed default fixed direction for extrusion (WARNING : The result may be the null vector) 
    // return CATSobDiag_EdgeLenghtMin iff oDefaultDirection is the null vector
    // else return CATSobDiag_OK
  virtual CATSobDiag GetDefaultFixedVector(CATMathVector& oDefaultDirection) = 0;  

  //DEPRECATED : Use CATSmoExtrudeFacesParameter instead
  // Set : Extrusion directions are computed along mesh lines (STANDARD Mode) 
  // 0 : No extrusion along mesh lines
  // 1 : The extrusion direction is the mean between two extremal edges at each vertex
  // 2 : The extrusion direction is the mesh line that is closer to a direction orthogonal at each vertex 
  virtual CATSobDiag SetExtrapoleAlongMeshLines(int iIsDirectionAlongMeshLines = 1) = 0;

  //DEPRECATED : Use CATSmoXtrudeNEdgesParameter instead
  // Ajout ANR : on extrapole d'une longueur donnee
  virtual void SetExtrapoleLength(const double iLength) = 0;

  //DEPRECATED : Use CATSmoXtrudeNEdgesParameter instead
  // Ajout ANR : on extrapole d'une longueur donnee
  virtual void SetMeanPlane(CATMathPlane *iMeanPlane, CATBoolean iQuasiPlanar=FALSE) = 0;

  //DEPRECATED : Use CATSmoXtrudeNEdgesParameter instead
  // Ajout ANR : BaseMesh Input est une grille
  virtual void SetBaseMeshMxN(CATBoolean iBaseMeshMxN=FALSE) = 0;

  //DEPRECATED : Use CATSmoXtrudeNEdgesParameter instead
  // *** WARNING : Work only with Set mono-parameter case ***
  // Ajout ANR : 
  virtual void GetNewFaces(CATLISTP(CATSobFace) &oNewFaces) = 0;

  //
  //-=-=-=-=-=-=-=- ADVANCED mode -=-=-=-=-=-=-=-

  //------ Draft direction :
  //DEPRECATED : Use CATSmoXtrudeNEdgesParameter instead
  // Set Drafting Direction (ADVANCED mode only)
  virtual CATSobDiag SetDraftDirection(const CATMathDirection &iDraftDirection) = 0;

  //DEPRECATED : Use CATSmoXtrudeNEdgesParameter instead
  // Get Drafting Direction (ADVANCED mode only)
  virtual void GetDraftDirection(CATMathDirection &oDraftDirection) = 0;

  //------ Angle (en degrés) :
  //DEPRECATED : Use CATSmoXtrudeNEdgesParameter instead
  // Set Angle (ADVANCED mode only)
  virtual void SetAngle(const double iAngleDeg) = 0;

  //DEPRECATED : Use CATSmoXtrudeNEdgesParameter instead
  // Get Angle (ADVANCED mode only)
  virtual void GetAngle(double &oAngleDeg) = 0;

  //------ Length  :
  //DEPRECATED : Use CATSmoXtrudeNEdgesParameter instead
  // Set Length (ADVANCED mode only)
  virtual CATSobDiag SetLength(const double iLength) = 0;

  //DEPRECATED : Use CATSmoXtrudeNEdgesParameter instead
  // Get Length (ADVANCED mode only)
  virtual void GetLength(double &oLength) = 0;


protected:

  //Constructeur
  CATSmoXtrudeNEdgesOperator(CATSobMesh* iMesh, CATSmoMeshTopoModifOperator* iTopoModifOpe);

  //Run de l'opérateur
  virtual CATSobDiag RunOperator() = 0;

};


//Méthode de création de l'opérateur
ExportedByCATSmoOperators
CATSmoXtrudeNEdgesOperator* CATSmoCreateXtrudeNEdgesOperator(CATSobMesh* iMesh, 
                                                             CATSmoMeshTopoModifOperator* iTopoModifOpe = 0);


#endif

