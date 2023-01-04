//====================================================================
// Copyright Dassault Systemes Provence 2003-2018, all rights reserved 
//====================================================================
//
// CATSmoFacesUtilities.h
//
//====================================================================
//
// Usage notes:
//
//====================================================================================
// January,   2022 : RBD : Nouvelle methode SetEdgeWeight() avec poids et smoothness séparés.
// December   2020 : RBD : Ajout methode CoefNormales pour l'extrusion de faces
// Sep        2018 : ANR : Ajout de  iResolution dans NormalAtVertex (je laisse par defaut 1.e-3) et OrdonneEdges
//                         Pour ExtremeScale Il faut passer par CATTolerance
// September  2008 : RBD : Ajout SetEdgeWeight
// November   2007 : MMO : Correction des erreurs BAD004 (headerruler)
// September  2007 : RNO : Ajout ComputeLimitBox
// January    2007 : RBD : OrdonneEdges, ConnectEdges, VerifNormales et VerifInputEdges.
// November   2006 : RBD : GetLenghtEdge
// July,      2004 : RAQ : PointsAndNormalsOfFace pour les faces triangulaires
// March,     2004 : RAQ : PointsOfFace Alloc du tableau de point par le user
// February,  2004 : RAQ : NormalAtFace Alloc possible du tableau de point par le user
// January,   2004 : RAQ : Changement d'architecture des subdivisions
// Octobre,   2003 : ANR : Ajout de NormalAtVertex
// September, 2003 : JCV : Creation
//====================================================================================
#ifndef CATSmoFacesUtilities_H
#define CATSmoFacesUtilities_H

//Pour l'export
#include "CATSmoOperators.h"

//Objets subdivision
#include "CATSobDiag.h"
#include "CATSmoVertexDef.h"
// #include "CATSobVertex.h" // MMO BAD004
// #include "CATSobEdge.h" // MMO BAD004
// #include "CATSobFace.h" // MMO BAD004
#include "CATSobListOfVertex.h"
#include "CATSobListOfEdge.h"
#include "CATSobListOfFace.h"

class CATSobMesh;
class CATSobVertex; // MMO BAD004
class CATSobEdge; // MMO BAD004
class CATSobFace; // MMO BAD004

class CATMathBox;
class CATMathPoint;
class CATMathVector;

/** 
 * Compute the normal at a given face
 *
 * @param iFace
 * The face
 *
 * @return
 * The normal (or The NULL vector if there is a problem (NULL Face, #edges < 3, etc.))
 */
ExportedByCATSmoOperators 
CATMathVector NormalFace (CATSobFace * iFace);

/** 
 * Compute the center of a given face
 *
 * @param iFace
 * The face
 *
 * @return
 * A CATMathPoint containing the coordinates of the center
 */
ExportedByCATSmoOperators
CATMathPoint CenterFace (CATSobFace * iFace);

/**
 * Retreives all the points of a face at a given subdivision level
 * The array of points must be allocated by the user,
 * its size is (2^Level+1) * (2^Level+1).
 *
 * @param iFace
 * The face.
 * @param ioPointsOfFace
 * A pointer to the array of points of the face, allocated by the user
 * @param iNbPoints.
 * The number of points in the face, this value is checked to verify
 * the user has given the good size for the array.
 * @param iLevel
 * The subdivision level for which the points are retreived,
 * iLevel must be >= 1
 * 
 * @return
 * 0 if no problems occured
 */
ExportedByCATSmoOperators
int PointsOfFace(CATSobFace*   iFace,
                 CATMathPoint* ioPointsOfFace,
                 const int     iNbPoints,
                 const int     iLevel);


/**
 * Retreives the normal at a given vertex with respect to a subdivision level
 * The normal is normalized
 *
 * @param iVertex
 * The vertex
 * @param oNormal
 * The normal at this vertex
 * @param iLevel
 * The subdivision level for which the normal is to be computed,
 * the vertex must be subdivided at least once.
 * 
 * @return
 * 1 if no problems occured, else 0
 */
ExportedByCATSmoOperators 
int NormalAtVertex(CATSobVertex  *iVertex,
                   CATMathVector &oNormal,
                   const int      iLevel = -1,
                   const double    iResolution = 0.001); // @NumValidated()

ExportedByCATSmoOperators 
int NormalAtVertex (CATSobVertex  * iVertex,
                    CATSobFace    * iFace,
                    CATMathVector & oNormal,
                    const int       iLevel = -1,
                    const double    iResolution = 0.001); // @NumValidated()
/*
// calcul de la normale au vertex ( qui n'est pas un vertex ) 
// interne a un une face triangulaire ....
ExportedByCATSmoOperators 
int NormalAtVertex (CATSobFace    * iTriangularFace,
                    CATMathVector & oNormal,
                    const int       iLevel); 
*/

/**
 * Retreives all the points and the corresponding normals for a face,
 * at a given subdivision level.
 * The array of points and normals must be allocated by the user:
 * - If the face is quadrangular, their size is (2^Level+1) * (2^Level+1).
 * - If the face is not quad, their size is (2^(Level-1)+1) * (2^(Level-1)+1).
 *
 * WARNING: If the face is not quad, the level must be at least 1
 *
 * The points are arranged the following way:
 *
 *          4             The edges are indexes in the face by 1, 2, 3, 4.
 *     <-----------       The points are given from left to right and from up to down
 *   |  ......... /|\
 *   |  .........  |
 * 1 |  .........  | 3
 *   |  .........  |
 *  \|/ .........  |
 *     ----------->
 *          2
 *
 * @param iFace
 * The face
 * @param ioPointsOfFace
 * A pointer to the array of points of the face, allocated by the user
 * @param ioNormals
 * A pointer to the array of normalized normals associated with the points,
 * allocated by the user
 * @param iNbPoints
 * The number of points in the face, this value is checked to verify
 * the user has given the good size for the array
 * @param iLevel
 * The subdivision level for which the normals are to be computed,
 * iLevel must be >= 1
 * @param iIndexOfDaughterFace
 * If the face is triangular, the index of the quad face contained in this
 * triangular face must be given with: 1 <= iIndexOfDaughterFace <= 3 (see CATSobFace.h)
 * If the face is quad, iIndexOfDaughterFace must be 0 (default value)
 *
 * @return
 * 0 if no problems occured, else 1
 */
ExportedByCATSmoOperators
int PointsAndNormalsOfFace(CATSobFace*    iFace,
                           CATMathPoint*  ioPointsOfFace,
                           CATMathVector* ioNormals,
                           int&           iNbPoints,
                           const int      iLevel,
                           const int      iIndexOfDaughterFace=0);


/**
 * Retreives the normal at a given vertex with respect to a subdivision level
 * The normal is normalized
 *
 * @param iVertex
 * The vertex.
 *
 * @param iLevel
 * The subdivision level ( > 0 ),
 *
 * @param onbsharpEdges
 * The number of Sharped edges surrounding this vertex.
 *
 * @param oerror
 * 0 if no problems occured, else 1
 *
 * @return
 * the type of vertex : closed, opened ...
 */
ExportedByCATSmoOperators 
CATSmoVertexType TypeOfVertex(CATSobVertex        * iVertex,  
                              const int             iLevel,
                              int                 & onbsharpEdges,
                              int                 & oerror);




/**
 * Retreives the Lenght at a given Edge
 *
 * @param iEdge
 * The edge.
 *
 * @return
 * the lenght of the edge iEdge.
 */
ExportedByCATSmoOperators
double GetLenghtEdge (CATSobEdge * iEdge);


//Compute the The Box of the Limit Surface corresping to iFace using the discretization points of iLevel 
ExportedByCATSmoOperators
CATSobDiag ComputeLimitBox(CATSobFace*   iFace,int iLevel, CATMathBox &oBox);



// Methodes locales ........ ANR :
// la methode ComputeNormalAtOpenAndSmoothVertex disparaitra plus tard ...
// et on appelera que ComputeNormalAtSharpVertex :

ExportedByCATSmoOperators
int  FunctionForComputeSector(CATSmoVertexType iTypeOfVertex,
                              int iLevel,
                              CATLISTP(CATSobEdge)& Edges, 
                              int                 & oNbreOfSector,
                              int                ** ioSector,
                              CATBoolean iWithAllTypeOfSharp=FALSE) ;

int ComputeNormalAtCloseAndSmoothVertex(CATSobVertex  *iVertex, 
                                        CATMathVector &oNormal,
                                        const int      iLevel);

int ComputeNormalAtOpenAndSmoothVertex(CATSobVertex  *iVertex, 
                                       CATMathVector &oNormal,
                                       const int      iLevel,
                                       const double    iResolution);

int ComputeNormalAtSharpVertex(CATSobVertex  *iVertex,
                               CATSobFace    * iFace,
                               CATMathVector &oNormal,
                               const int      iLevel);

// Pour le FillBasic et XtrudeNEdges
/**
 * Sort a list of connected edges
 *
 * @param iListEdges
 * The input list of n edges.
 *
 * @param oOrdonnedEdges
 * TThe list of n edges, connected AND sorted
 *
 * @param oIsClose
 * Tell if the set of n edges is closed :
 *    = 0, the set is open
 *    = 1, the set is closed (The 1st and the last vertices are the same)
 *    = 2, The 1st and the last vertex are different but very near 
 *         (the two 3D points are within 0.001)
 *
 * @return
 * CATSobDiag
 */
ExportedByCATSmoOperators
CATSobDiag OrdonneEdges (CATLISTP(CATSobEdge) &iListEdges,
                         CATLISTP(CATSobEdge) &oOrdonnedEdges,
                         int                  &oIsClose,
                         const double          iResolution = 0.001); // @NumValidated()

/**
 * Connect a list of edges (but the edges are not sorted)
 *
 * @param ioListEdges
 * The input list of n edges.
 *
 * @param oConnectedEdges
 * The list of n edges, connected
 *
 * @return
 * CATSobDiag
 */
ExportedByCATSmoOperators
CATSobDiag ConnectEdges (CATLISTP(CATSobEdge) &ioListEdges,
                         CATLISTP(CATSobEdge) &oConnectedEdges);


/**
 * DO NOT USE
 * DEPRECATED : use the method with 4 arguments instead :
 * CATSobDiag SetEdgeWeight(CATSobEdge* ipEdge,
 *                        const int iWeight,
 *                        const CATBoolean iSmoothingOn,
 *                        const int iAutoWeightVertex) 
 * 
 * Application d'un poid sur un edge et report sur les vertex
 * @param ipEdge
 * The input edge.
 *
 * @param iWeight
 * The input weight: -100 <= iWeight <= 100. 
 * If iWeight < 0, the edge ipEdge is set sharp
 * If iWeight >= 0, the edge ipEdge is set smooth
 *
 * @param iAutoWeightVertex
 * iAutoWeightVertex <> 0 manage the weight on the vertices with the weight on the edge ipEdge
 *
 * @return
 * CATSobDiag
 */
ExportedByCATSmoOperators
CATSobDiag SetEdgeWeight(CATSobEdge* ipEdge,
                         const int iWeight,
                         const int iAutoWeightVertex);

/**
 * Application d'un poid et sharp/smooth sur un edge et report sur les vertex
 *
 * @param ipEdge
 * The input edge.
 *
 * @param iWeight
 * The input weight: 0 <= iWeight <= 100.
 * 
 * @param iSmoothingOn
 * The input sharpness (or smoothness) :
 * if iSmoothingOn == TRUE : smooth
 * if iSmoothingOn == FALSE : Sharp
 *
 * @param iAutoWeightVertex
 * iAutoWeightVertex <> 0 manage the weight on the vertices with the weight on the edge ipEdge
 *
 * @return
 * CATSobDiag
 */
ExportedByCATSmoOperators
CATSobDiag SetEdgeWeight(CATSobEdge* ipEdge,
                         const int iWeight,
                         const CATBoolean iSmoothingOn,
                         const int iAutoWeightVertex);


/**
 * Report des poids des edges d'un vertex sur une liste d'edges et report eventuels sur les vertices
 *
 * @param ipVertex
 * The input vertex.
 *
 * @param ioListEdges
 * The input/output list of edges 
 *
 * @param iAutoWeightVertex
 * iAutoWeightVertex <> 0 manage the weight on the vertices with the weight on the edge ipEdge
 *
 * @return
 * CATSobDiag
 */
ExportedByCATSmoOperators
CATSobDiag InheritWeight(CATSobVertex* ipVertex,
                         CATLISTP(CATSobEdge) &ioListEdges,
                         const int iAutoWeightVertex=0);

/**
 * Report des poids d'une edge sur  sur une liste d'edges et report eventuels sur les vertices
 *
 * @param ipEdge
 * The input edge.
 *
 * @param ioListEdges
 * The input/output list of edges 
 *
 * @param iAutoWeightVertex
 * iAutoWeightVertex <> 0 manage the weight on the vertices with the weight on the edge ipEdge
 *
 * @return
 * CATSobDiag
 */
ExportedByCATSmoOperators
CATSobDiag InheritWeight(CATSobEdge* ipEdge,
                         CATLISTP(CATSobEdge) &ioListEdges,
                         const int iAutoWeightVertex=0);

/**
 * Advanced adding faces in a mesh with tracking ability
 *
 * if iMode == AdvancedAddFaces_Out , the ioTables are the ones built during the adding process
 * if existing, they are reinitialized
 * if iMode == AdvancedAddFaces_InOut , the iotables are the ones built during the adding process
 * they are not reinitialized
 * if iMode == AdvancedAddFaces_In, the iotables are used to check existing correspondences
 *
 *@param iFaces
 * the list of the faces from original mesh to add to the copy
 *@param ioMesh
 * the copy mesh
 *@param ioOrigE
 * the original part of the correspondence table for the edges
 *@param ioCopyE
 * the copy part of the correspondence table for the edges
 *@param ioOrigV
 * the original part of the correspondence table for the vertices
 *@param ioCopyV
 * the copy part of the correspondence table for the vertices
 *@param iMode
 * see function description
 *@param ioCopyFaces
 * Optionnal, to retrieve the list of copied faces, ioCopyFaces must point to a valid list of faces.
 **/
typedef enum{ AdvancedAddFaces_In, AdvancedAddFaces_Out, AdvancedAddFaces_InOut } AdvancedAddFacesMode;

ExportedByCATSmoOperators
CATSobDiag AdvancedAddFaces(CATLISTP(CATSobFace)* iFaces,
			                      CATLISTP(CATSobEdge)*& ioOrigE, CATLISTP(CATSobEdge)*& ioCopyE, 
			                      CATLISTP(CATSobVertex)*& ioOrigV, CATLISTP(CATSobVertex)*& ioCopyV, 
			                      CATSobMesh* ioMesh, const AdvancedAddFacesMode iMode, CATLISTP(CATSobFace)* ioCopyFaces = 0);



// Pour ExtrudeNFaces et ExtrudeFacesParameter
/**
* Compute a coefficient of compatibility between 2 faces for 
*
* @param iFace1
* The input face 1.
*
* @param iFace2
* The input face 2
*
* @param iInvertNormal
*
* @return
* double
*/
ExportedByCATSmoOperators
double CoefNormales(CATSobFace* iFace1, CATSobFace* iFace2, const CATBoolean iInvertNormal, const double iEpsTol90deg);

#endif

