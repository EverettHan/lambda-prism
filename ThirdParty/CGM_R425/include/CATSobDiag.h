//============================================================================
// Copyright Dassault Systemes Provence 2003-2018, all rights reserved 
//============================================================================
//
// CATSobDiag.h
//
//============================================================================
//
// Usage notes:
//
//============================================================================
// 28.06.2018 : MMO : Ajout CATSobDiag_InputPolyhedralBodyNotAuthorized 
//                    pour les CATBody Polyedrique non autorise en entree de certains opérateurs (POLYCRASH)
// 28.02.2013 : RAQ : Ajout CATSobDiag_MergedCurveComputationError
// December,  2009 : RAQ : Ajout IsOK(const CATSobDiag iDiag)
// April,     2008 : RAQ : Ajout CATSobDiag_InternalNullSubdivCellSurface
// January  , 2008 : MPS : Ajout CATSobDiag_NotModifiableDimension
// September, 2007 : RNO : Ajout CATSobDiag_UnableToEval
// July    ,  2007 : PMG : Ajout CATSobDiag_InsuficientNumberOfActiveCells
// March   ,  2007 : PMG : Ajout CATSobDiag_OperatorNotInitialized 
// February,  2007 : MPS : Ajout CATSobDiag_EdgesPartiallyConfused 
// February,  2007 : RAQ : Ajout ToString
// October,   2004 : RAQ : Optimisation mémoire + nouveaux diag
// January,   2004 : RAQ : Changement d'architecture des subdivisions
// January,   2004 : RAQ : Ajout CATSobDiag_SurfacePointerNotNull
// Marsh,     2003 : JCV : Creation CATSobDiag.h
//============================================================================
#ifndef CATSobDiag_H
#define CATSobDiag_H

//Pour l'export
#include "CATSobObjects.h"

//Divers
#include "CATBoolean.h"



typedef enum 
{ 
/////////////////////////////////////////////////////////////////////////////////////
  CATSobDiag_OK = 0                             // OK
/////////////////////////////////////////////////////////////////////////////////////
//                                ERREURS
/////////////////////////////////////////////////////////////////////////////////////
//                                       Erreurs sur les entrées
/////////////////////////////////////////////////////////////////////////////////////
, CATSobDiag_InputNullPointer                   // Un pointeur donne en entrée est nul.
, CATSobDiag_InputNullMesh                      // Le pointeur de mesh donne en entrée est nul.
, CATSobDiag_InputNullFace                      // Le pointeur de face donne en entrée est nul.
, CATSobDiag_InputNullEdge                      // Le pointeur d'edge donne en entrée est nul.
, CATSobDiag_InputNullVertex                    // Le pointeur de vertex donne en entrée est nul.
, CATSobDiag_InputNullCell                      // Le pointeur de cellule donné en entrée est nul.
, CATSobDiag_InputNullVertexOnEdge              // Pointeur de vertex sur edge nul.
, CATSobDiag_InputNullList                      // Le pointeur de liste donne en entrée est nul.
, CATSobDiag_InputNullLayer                     // Pointeur de layer null en entrée d'un l'opérateur.
, CATSobDiag_InputNullListener                  // Pointeur de listener null en entrée d'un l'opérateur.
, CATSobDiag_InputInvalidIndex                  // L'index donne en entrée est invalide (hors bornes).
, CATSobDiag_InputInvalidValue                  // La valeur donnée en entrée est invalide.
, CATSobDiag_InputInvalidCell                   // La cellule donnée en entrée est invalide.
, CATSobDiag_InputInvalidLevel                  // Le niveau de subdivision donné en entrée est invalide
, CATSobDiag_InputNullListElement               // Un element contenu dans la liste donnée en entrée est nul.
, CATSobDiag_InputInvalidSize                   // Une liste donnée en entrée est de taille invalide.
, CATSobDiag_InputMeshIncompatibility           // Une donnée n'est pas compatible avec le mesh courant.
, CATSobDiag_InputCellsIncompatibility          // Certaines données sont incompatibles (ex : edge hors face traitée).
, CATSobDiag_InputPolyhedralBodyNotAuthorized   // Une entrée en un CATBody Polyedrique, type d'entrée non valide
, CATSobDiag_InsuficientNumberOfActiveCells     // Nombre de cellules active insuffisante
, CATSobDiag_NotModifiableDimension             // La modification de la dimension demandée est impossible
, CATSobDiag_IncompatibleOptions                // Options incompatibles
/////////////////////////////////////////////////////////////////////////////////////
//                                       Erreurs liées à la validite de la structure
/////////////////////////////////////////////////////////////////////////////////////
, CATSobDiag_FaceNull                           // Pointeur de face nul dans le mesh -> faire un Update.
, CATSobDiag_EdgeNull                           // Pointeur d'edge nul dans le mesh -> faire un Update.
, CATSobDiag_VertexNull                         // Pointeur de vertex nul dans le mesh -> faire un Update.
, CATSobDiag_OpenVertex                         // Un vertex est ouvert, ie sur un bord
, CATSobDiag_ClosedVertex                       // Un vertex est interne, ie pas sur un bord
, CATSobDiag_MeshInvalidConnexity               // Mesh non connexe.
, CATSobDiag_EdgeLenghtMin                      // Longueur minimum d'edge non respectée.
, CATSobDiag_MeshNotQuad                        // Mesh constitue de faces non quadrangulaires.
, CATSobDiag_MeshNotTriQuad                     // Mesh constitue de faces non quadrangulaires ou triangulaires.
, CATSobDiag_MeshIncompatibility                // Une cellule n'est pas compatible avec le mesh courant.
, CATSobDiag_CellsIncompatibility               // Certaines cellules sont incompatibles (ex : edge hors face traitée).
, CATSobDiag_EdgeSameVertex                     // Une edge ne peut pas avoir le meme vertex au debut et a la fin.
, CATSobDiag_EdgeSameSupport                    // Une edge ne peut etre jointure de deux fois la meme face.
, CATSobDiag_EdgeMoreSupport                    // Une edge ne peut pas avoir plus de deux supports.
, CATSobDiag_FaceNotConnectedEdge               // Les edges de la face ne sont pas connectées.
, CATSobDiag_FaceBoundaryNotClose               // La premiere et la derniere edges de la face ne sont pas connectées.
, CATSobDiag_FaceNotQuad                        // La face n'est pas quad
, CATSobDiag_FaceInvalidEdgeSize                // Une face doit etre constituée d'au moins 3 edges.
, CATSobDiag_InvalidValenceTwoVertex            // Un vertex interne à un maillage ne peut pas être de valence 2
, CATSobDiag_BigValenceError                    // Le mesh posséde des vertex de valence trop importante
, CATSobDiag_MeshFrozen                         // Le mesh est gelé, il ne peut être modifié
, CATSobDiag_EdgesPartiallyConfused             // Dans le mesh , il existe des edges partiellement confondues
, CATSobDiag_CellTagNotUnique                   // Des valeurs de tag sont dupliquées
, CATSobDiag_CellAlreadyModified                // Cellule ne pouvant être modifiée qu'une unique fois et déjà modifiée
/////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////
, CATSobDiag_ErrorFaceAlreadyCut                // La face est déjà coupée, impossible de la redécouper
, CATSobDiag_LocalVertexNotModifiable           // Un vertex du base mesh local ne peut pas être déplacé
/////////////////////////////////////////////////////////////////////////////////////
//                                       Erreurs internes
/////////////////////////////////////////////////////////////////////////////////////
, CATSobDiag_InternalError                      // Erreur interne dans l'operateur.
, CATSobDiag_InternalNullPointer                // Pointeur nul rencontré dans l'operateur.
, CATSobDiag_InternalNullMesh                   // Pointeur de mesh nul rencontré dans l'operateur.
, CATSobDiag_InternalNullFace                   // Pointeur de face nul rencontré dans l'operateur.
, CATSobDiag_InternalNullEdge                   // Pointeur d'edge nul rencontré dans l'operateur.
, CATSobDiag_InternalNullVertex                 // Pointeur de vertex nul rencontré dans l'operateur.
, CATSobDiag_InternalNullCell                   // Pointeur de cellule nul rencontré dans l'opérateur.
, CATSobDiag_InternalNullVertexOnEdge           // Pointeur de vertex sur edge nul rencontré dans l'operateur.
, CATSobDiag_InternalNullSurface                // Pointeur de surface null rencontré dans l'opérateur.
, CATSobDiag_InternalNullSubdivCellSurface      // Pointeur de CATSubdivCellSurface null rencontré dans l'opérateur.
, CATSobDiag_InternalNullLayer                  // Pointeur de layer null rencontré dans l'opérateur.
, CATSobDiag_InternalNullListener               // Pointeur de listener null rencontré dans l'opérateur.
, CATSobDiag_InternalNullList                   // Pointeur de liste nul rencontré dans l'operateur.
, CATSobDiag_InternalInvalidSize                // Liste de taille invalide rencontrée dans l'operateur.
, CATSobDiag_InternalInvalidValue               // Valeur incorrecte rencontrée dans l'opérateur
, CATSobDiag_InternalInvalidLevel               // Le niveau de subdivision est invalide
, CATSobDiag_InternalInvalidIndex               // L'index donné est invalide (hors bornes).
/////////////////////////////////////////////////////////////////////////////////////
//                                       Pointeurs de surface non détruit
/////////////////////////////////////////////////////////////////////////////////////
, CATSobDiag_SurfacePointerNotNull              // Pointeur sur la surface d'une face non nul
/////////////////////////////////////////////////////////////////////////////////////
//                                       Erreurs relatives aux détails
/////////////////////////////////////////////////////////////////////////////////////
, CATSobDiag_NullDetail                         // Detail nul
/////////////////////////////////////////////////////////////////////////////////////
//                                       Diag pour l'opérateur de compression
/////////////////////////////////////////////////////////////////////////////////////
, CATSobDiag_Done                               // Le traîtement est effectué
, CATSobDiag_Continue                           // Le traîtement doit se poursuivre
, CATSobDiag_BadCompressorLevel                 // Erreur de version dans l'opérateur de compression
/////////////////////////////////////////////////////////////////////////////////////
//                                       Diag pour les opérateurs de topologie
/////////////////////////////////////////////////////////////////////////////////////
, CATSobDiag_InputNullOperator                  // Un pointeur donné en entrée sur un opérateur est nul
, CATSobDiag_InternalNullOperator               // Un pointeur sur un opérateur est nul en interne
, CATSobDiag_InputNullSubdivMesh                // Le CATSubdivMesh donné en entrée est nul
, CATSobDiag_InternalNullSubdivMesh             // Un CATSubdivMesh est nul dans l'opérateur
, CATSobDiag_OperatorAlreadyRun                 // L'opérateur a déjà été joué, un seul run autorisé
, CATSobDiag_OperatorNotRun                     // Aucun Run n'a été fait sur l'opérateur
, CATSobDiag_OperatorNotInitialized             // Aucun Init n'a été fait sur l'opérateur
, CATSobDiag_MergedCurveComputationError        // Unable to create a merged curve during topological update
/////////////////////////////////////////////////////////////////////////////////////
//                                       Diag pour les Eval
/////////////////////////////////////////////////////////////////////////////////////
, CATSobDiag_UnableToEval                       //Cas non gere par l'eval 
, CATSobDiag_UnableToComputeCurvature 
/////////////////////////////////////////////////////////////////////////////////////
//                                       Solveur hybride
/////////////////////////////////////////////////////////////////////////////////////
, CATSobDiag_HybSolver_AreaModificationIntersection   //Zones de modification en intersection
/////////////////////////////////////////////////////////////////////////////////////
//                                       Match de Subdivision
/////////////////////////////////////////////////////////////////////////////////////
, CATSobDiag_Match_InvalidBoundary                    //Bord non régulier pour le match : présence de poids, vertex non régulier...
, CATSobDiag_Match_InvalidRequestedContinuity         //L'opérateur ne peut pas matcher avec la continuité demandée : le wire cible ne permet pas de tenir les continuités géométriques demandées (pas de support alors que G1 ou G2 demandé par exemple),
                                                      //limitation n'autorisant que du G0 mais G1 ou G2 demandé...
, CATSobDiag_Match_IncompatibleDiscontinuities        //Le nombre de discontinuités G1 sur la cible n'est pas le même que celui du bord à matcher
, CATSobDiag_Match_IncompatibleTargetWire             //Courbe cible et bord de subdiv incompatibles : fermé/ouvert par exemple
, CATSobDiag_Match_UndefinedSupport                   //Support non définit ou ambigu
, CATSobDiag_Match_AreaModificationIntersection       //Intersection de zones de modification à l'interieur de l'opérateur de match (conflit de paramètres)
/////////////////////////////////////////////////////////////////////////////////////
//                                       Divers
/////////////////////////////////////////////////////////////////////////////////////
, CATSobDiag_ErrorNotImplemented                // Méthode non implémentée
, CATSobDiag_ErrorDeprecated                    // Méthode deprecated
/////////////////////////////////////////////////////////////////////////////////////

} CATSobDiag;


/**
 * Checks diag.
 *
 * @param iDiag
 *
 * @return
 * TRUE if iDiag is CATSobDiag_OK, FALSE otherwise.
 **/
inline ExportedByCATSobObjects
CATBoolean IsOK(const CATSobDiag iDiag) { return (iDiag==CATSobDiag_OK); }


/**
 * Gets the string corresponding to a diag
 *
 * @param iDiag
 * The Diag
 *
 * @return
 * The string corresponding to the given diag
 **/
ExportedByCATSobObjects
const char* ToString(const CATSobDiag iDiag);

#endif


