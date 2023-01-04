//=============================================================================================
// Copyright Dassault Systemes Provence 2003, all rights reserved 
//=============================================================================================
//
// CATSobLocalCutOperator.h
//
//=============================================================================================
//
// Usage notes: Cut local d'une face
//
//=============================================================================================
// November,  2004 : RAQ : Creation
//=============================================================================================
#ifndef CATSobLocalCutOperator_H
#define CATSobLocalCutOperator_H

#include "CATSobOperators.h"

//Eléments de structure
#include "CATSobDiag.h"
#include "CATSobListOfFace.h"
#include "CATSobListOfCell.h"

//Divers
#include "CATBoolean.h"
#include "CATListOfDouble.h"


class CATSobMesh;
class CATSobFace;
class CATSobEdge;
class CATSobCell;


class ExportedByCATSobOperators CATSobLocalCutOperator
{
public:

/**
 * Constructs the operator to be applied on a face
 *
 * @param iFace
 * The face on which the operator is to be applied
 **/
  CATSobLocalCutOperator(CATSobFace* iFace);

/**
 * @nodoc
 **/
  virtual ~CATSobLocalCutOperator();

/**
 * Gets the operator's diagnotic
 *
 * @return
 * The diag is CATSobDiag_OK if no problems in the operator,
 * else see CATSobDiag.h
 **/
  CATSobDiag GetDiag();

/**
 * Locally applies parallel cuts to the face respect to an edge of the face
 *
 * @param iEdge
 * An edge of the face
 * @param iNbCuts
 * The number of cuts to make
 * @param iRatio
 * If iRatio is NULL, the edge is uniformely cut.
 * If iRatio is not NULL, iRatio must contain iNbCuts double values such that:
 *  for each i, 0 < i < iNbCuts: 0 < iRatio[i] < 1
 *  It defines where the edge is to be cut.
 *  The smaller iRatio[i] is, the more the cut will be close to the StartVertex
 *  of the edge see in the face.
 *
 * @return
 * CATSobDiag_OK if no errors, else see CATSobDiag.h
 **/
  //CATSobDiag SetParallelCutOption(CATSobEdge* iEdge, const int iNbCut, const double* iRatio = 0);
  
/**
 * Locally applies cross cuts to the face
 *
 * @param iRatioOnU
 * A ratio given with respect to the Edge #1 of the face (U-axis)
 * @param iRatioOnV
 * A ratio given with respect to the Edge #4 of the face (V-axis)
 *
 * @return
 * CATSobDiag_OK if no errors, else see CATSobDiag.h
 **/
  //CATSobDiag SetCrossCutOption(const double iRatioOnU, const double iRatioOnV);

/**
 * Runs the operator
 *
 * @return
 * CATSobDiag_OK if no problems, else see CATSobDiag.h
 **/
  CATSobDiag Run();

/**
 * Just creates local mesh structure without updating coordinates
 **/
  void SetJustCreateStructure();





  //Création du mesh super fin pour le PCCM
  CATSobDiag CreateLocalMeshForPCCM(CATSobMesh*& oLocalMeshForPCCM,
                                    int&         oNbCutsOnUAndV,
                                    double *&    TabOfCutsOnUAndV,
                                    const int    iLevel = 2);





  //Ajout de découpes en U
  CATSobDiag AddCutsOnU(const int iNbCuts, const double* iRatio = 0);

  //Ajout de découpes en V
  CATSobDiag AddCutsOnV(const int iNbCuts, const double* iRatio = 0);

  //Ajout de découpes sur une edge
  CATSobDiag AddCutsOnEdge(const CATSobEdge* iEdgeToCut, const int iNbCuts, const double* iRatio = 0);

  //Suppression de découpes en U
  CATSobDiag RemoveCutsOnU(const int iNbCuts, const double* iRatio);

  //Suppression de découpes en V
  CATSobDiag RemoveCutsOnV(const int iNbCuts, const double* iRatio);

  //Suppression de découpes sur une edge
  CATSobDiag RemoveCutsOnEdge(const CATSobEdge* iEdge, const int iNbCuts, const double* iRatio);






private:

    // Copy constructor and equal operator
  CATSobLocalCutOperator (CATSobLocalCutOperator &);
  CATSobLocalCutOperator& operator=(CATSobLocalCutOperator&);

  //Pour les Diag
  CATSobDiag SetDiag(CATSobDiag iDiag);

  //Check des entrées
  CATSobDiag CheckInput();

  //Destruction de certains points sur les edges
  CATSobDiag RemoveCutsOnFace(const int     iNbCutsOnU,
                              const double* iRatioOnU,
                              const int     iNbCutsOnV,
                              const double* iRatioOnV);
  
  //Création des points sur les edges (avant homogeneization)
  CATSobDiag AddCutsOnFace(int&     oNbCutsOnU,
                           double*& oRatioOnU,
                           int&     oNbCutsOnV,
                           double*& oRatioOnV);

  //Homogénéisation des découpes sur la face (partie grille)
  CATSobDiag HomogenizeCutsOnFace();

  //Création des ratios en U et V pour la face mère
  CATSobDiag CreateRatioForLocalMesh(double*& oRatioOnU,
                                     int&     oNbCutsOnU,
                                     double*& oRatioOnV,
                                     int&     oNbCutsOnV);
  
  //Construction du base mesh local
  CATSobDiag CreateLocalMesh(CATSobMesh*& oLocalMesh,
                             const int    iNbCutOnU,
                             double*      iRatioOnU,
                             const int    iNbCutOnV,
                             double*      iRatioOnV);

  //Utilisation des buffers statiques
  CATSobDiag SetUseStaticBufferForMesh(CATSobMesh* iMesh, const CATBoolean iOnOff = TRUE, const int iLevel = 2);

  //Création du mesh super fin pour le PCCM
  CATSobDiag ComputeFineCuts(int&     oNbCutsOnU,
                             double*& oRatioOnU,
                             int&     oNbCutsOnV,
                             double*& oRatioOnV);

  CATSobDiag CreateLocalMeshForPCCMImpl(int &         oTargetLevel,
                                        CATSobMesh*&  oLocalMeshForPCCM,
                                        const int     iNbCutsOnU,
                                        const double* iRatioOnU,
                                        const int     iNbCutsOnV,
                                        const double* iRatioOnV,
                                        const int     iLevel = 2);

  //Récupération des déplacements des vertex locaux
  CATSobDiag GetLocalVerticesDisplacements(const int     iNbCutsOnU,
                                           const double* iRatioOnU,
                                           const int     iNbCutsOnV,
                                           const double* iRatioOnV,
                                           int&          oNbDisplacements,
                                           double*&      oDisplacements);

  //Set des déplacements sur les vertex locaux
  CATSobDiag SetLocalVerticesDisplacements(CATSobMesh*   iLocalMesh,
                                           const int     iNbCutsOnU,
                                           const double* iRatioOnU,
                                           const int     iNbCutsOnV,
                                           const double* iRatioOnV,
                                           const int     iNbDisplacements,
                                           const double* iDisplacements);

  //Report des déplacements des faces voisines sur les faces filles courantes
  CATSobDiag ReportDisplacementsOfNeighbourFaces(CATSobMesh* iLocalMesh,
                                                 const int   iNbCutsOnU,
                                                 const int   iNbCutsOnV);

  //Nettoyage
  void CleanArray(double**& iArray, const int FirstSize);

  //Data:
  CATSobFace* _Face;
  CATSobMesh* _SonMesh;
  CATListOfDouble _RatioListOnU, _RatioListOnV;
  CATListOfDouble _RatioToRemoveOnU, _RatioToRemoveOnV;

  CATSobDiag _Diag;

  CATBoolean _UpdateLocalMesh;
};



/*
ExportedByCATSobOperators
CATSobDiag ConvertDetailsToLocalCut(CATSobMesh*  iMeshWithDetails,
                                    CATSobMesh*& oMeshLocalCut,
                                    int*         oMaxLevelUsed = 0,
                                    const int    iMaxLevel = -1);
*/


















//---------------------- Méthodes inline ----------------------//

inline CATSobDiag CATSobLocalCutOperator::GetDiag()
{
  return _Diag;
}


inline CATSobDiag CATSobLocalCutOperator::SetDiag(CATSobDiag iDiag)
{
  _Diag=iDiag;
  return iDiag;
}


inline void CATSobLocalCutOperator::SetJustCreateStructure()
{
  _UpdateLocalMesh=FALSE;
}


#endif



