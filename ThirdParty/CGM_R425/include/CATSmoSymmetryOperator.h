//======================================================================
// Copyright Dassault Systemes Provence 2006, all rights reserved 
//======================================================================
//
// CATSmoSymmetryOperator.h
//
//======================================================================
//
// Usage notes:
//
//======================================================================
//  March,      2020 : RBD : Creation methode GetResultSide() pour eviter mauvaise utilisation de GetSideInfo()
//  September,  2014 : RBD : Ajout des options par SetImproveTrtTriQuadFaces()
//  January,    2009 : RBD : Gestion de l'option AutoWeight en E/S sur les edges de couture
//  October,    2006 : RBD : Creation
//======================================================================
#ifndef CATSmoSymmetryOperator_H
#define CATSmoSymmetryOperator_H

//Pour l'héritage
#include "CATSmoSubdivisionMeshOperator.h"

//Pour l'export
#include "CATSmoOperators.h"

//Divers
#include "CATMathPlane.h"
#include "CATBoolean.h"


//Objets subdivision
#include "CATSobDiag.h"
#include "CATSmoSymmetryType.h"

class CATGeometry;
class CATSobMesh;
class CATSmoMeshTopoModifOperator;


class ExportedByCATSmoOperators CATSmoSymmetryOperator: public CATSmoSubdivisionMeshOperator
{
public:

  //Destructeur
  virtual ~CATSmoSymmetryOperator();

  // Set du plan de symmetrie
  // Set de CATSmoSymSide :
  // CATSmoInvertSide     - Invert side  plane normale
  // CATSmoDirectSide     - Same side 
  // Set de CATSmoSymMode :
  // CATSmoSymmetry       - Mode Symetrie
  // CATSmoCutByPlane     - Mode coupe / plan
  virtual void SetSymmetryParam(const CATMathPlane &iPlane, 
                                const CATSmoSymSide iSide = CATSmoDirectSide, 
                                const CATSmoSymMode iMode = CATSmoSymmetry) = 0;
 
  //Set du plan V5 pour le journal topologique
  virtual void SetPlaneFace(CATGeometry* iPlaneFace) = 0;

  // Set du traitement des faces triangles et triquads (mode CATSmoSymmetry)
  // Set du traitement des faces triangles et triquads (mode CATSmoSymmetry)
  // Variable de traitement des faces 
  //  - triangulaire avec un côté sur le plan de symetrie
  //  - triangulaire-quad : quad avec 2 côtés sur le plan de symetrie
  // CATSmoEraseTriQuads (= 0)      : Ancien algorithme (suppression des triangles et quad-triangles) DEFAUT
  // CATSmoReplaceByQuads (= 1)     : Triangle et quad-triangle supprimés (donnent un quad avec la symétrie)
  // CATSmoReplaceByTriangles (= 2) : Triangle et Quad-triangle (transformé en triangle) donnent un triangle par symétrie
  // CATSmoReplaceByFusion (= 3)    : Triangle et quad triangle absorbé par ses 2 faces voisines (fusion)
  virtual void SetImproveTrtTriQuadFaces(const CATSmoTrtTriQuadFaces iTypeTrt = CATSmoEraseTriQuads) = 0;


  // Get CATSmoSymSideInfo :
  // CATSmoInfoInvertOnly - invert side Only
  // CATSmoInfoInvert     - invert side prefered
  // CATSmoInfoUndefined  - undefined (Error)
  // CATSmoInfoDirect     - same side prefered 
  // CATSmoInfoOnly       - same side Only
  virtual CATSobDiag GetSideInfo (CATSmoSymSideInfo &oSideInfo) = 0;

  // Get CATSmoSymSide : This method returns the COMPUTED side, after the Run() method.
  // CATSmoInvertSide     - Invert side : opposite normal plane
  // CATSmoDirectSide     - Same side   : same normal plane
  virtual CATSobDiag GetResultSide(CATSmoSymSide &oSide) = 0;

  //Obtention du type de symmétrie réalisée
  virtual CATSmoSymMode GetSymmetryMode() const = 0;

  // Set Sharpness sur les edges dans le plan (Mode CATSmoSymmetry)
  // iMiddleWeight (0 -> 100) : Weight to be applied on the edges in the plane (the "middle edges")
  // iMiddleSmooth : Smooth or not smooth the "middle edges" (= Sharpness)
  // iAutoWeight : Automatic compute the weight on the vertex of the "middle edges"
  // return CATSobDiag_InputInvalidValue if iMiddleWeight < 0 or iMiddleWeight > 100
  virtual CATSobDiag SetMiddleEdgesSharpness(int iMiddleWeight = 0, CATBoolean iMiddleSmooth = 1, CATBoolean iAutoWeight = 0) = 0;

  // UNSet Sharpness sur les edges dans le plan
  virtual void UnSetMiddleEdgesSharpness() = 0;

  //Récupération du plan de symétrie
  virtual const CATMathPlane& GetSymmetryPlane() const = 0;


protected:

  //Constructeur
  CATSmoSymmetryOperator(CATSobMesh* iMesh, CATSmoMeshTopoModifOperator* iTopoModifOpe);

  //Run de l'opérateur
  virtual CATSobDiag RunOperator() = 0;

};


//Méthode de création de l'opérateur
ExportedByCATSmoOperators
CATSmoSymmetryOperator* CATSmoCreateSymmetryOperator(CATSobMesh* iMesh, 
                                                     CATSmoMeshTopoModifOperator* iTopoModifOpe = 0);


#endif

