/**
 * @COPYRIGHT DASSAULT SYSTEMES 2001
 * @fullReview  HCN 01:12:10
*/

/* -*-C++-*- */


#ifndef CATCGMSharpnessDataTools_H
#define CATCGMSharpnessDataTools_H

// COPYRIGHT DASSAULT SYSTEMES 2001

//===========================================================================
// Divers services pour les infos de vivicite stockees sur la topologie
//
// Dec. 01      Creation                                            HCN
// Fev. 02      CATTopGetAllEdgeSharpnessContexts                   HCN
// Mar. 02      CATTopGetAllVertexSharpnessContexts                 HCN
// Mai. 02      CATTopGetSharpnessContextsForEdgesInList
//              CATTopGetSharpnessContextsForEdge
//              CATTopGetSharpnessContextsForVerticesInList
//              CATTopGetSharpnessContextsForVertex                 HCN
//===========================================================================

#include "CXMODEL.h"
#include "CATBoolean.h"
#include "iostream.h"
#include "CATGeoDef.h"
#include "ListPOfCATVertex.h"
#include "ListPOfCATEdge.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATShell.h"
#include "CATTopDefine.h"

class CATBody;
class CATEdge;

// Cette methode renvoie dans le contexte de ipBody les contextes de vivicite
// applicable a l'edge passee en entree ipEdge,
// c'est-a-dire tous les contextes ipEdge/face1/face2/shell qui peuvent etre passes a
// CATEdge::EvalGlobalSharpness(...) ou CATEdge::SetSharness(...)
//
// Une Edge peut conduire a plusieurs contextes de vivicite si elle borde plus de deux
// faces ou partagee par plusieurs shells du body.
//
// Au retour, le contexte de rang i est defini par
//
//    ipEdge
//    ioListOfFirstFaces[i]
//    ioListOfSecondFaces[i]
//    ioListOfShells[i]
//
ExportedByCXMODEL void CATTopGetSharpnessContextsForEdge(CATBody*           ipBody,
                                                         CATEdge*           ipEdge,
                                                         CATLISTP(CATFace)& ioListOfFirstFaces,
                                                         CATLISTP(CATFace)& ioListOfSecondFaces,
                                                         CATLISTP(CATShell)& ioListOfShells);

// Cette methode renvoie dans le contexte de ipBody tous les contextes possibles de vivicite d'edge,
// c'est-a-dire tous les contextes edge/face1/face2/shell qui peuvent etre passes a
// CATEdge::EvalGlobalSharpness(...) ou CATEdge::SetSharness(...)
//
// Au retour, le contexte de rang i est defini par
//
//    ioListOfEdges[i]
//    ioListOfFirstFaces[i]
//    ioListOfSecondFaces[i]
//    ioListOfShells[i]
//
ExportedByCXMODEL void CATTopGetAllEdgeSharpnessContexts(CATBody*           ipBody,
                                                         CATLISTP(CATEdge)& ioListOfEdges,
                                                         CATLISTP(CATFace)& ioListOfFirstFaces,
                                                         CATLISTP(CATFace)& ioListOfSecondFaces,
                                                         CATLISTP(CATShell)& ioListOfShells);

// Cette methode renvoie dans le contexte de ipBody les contextes de vivicite
// applicables aux edges passees en entree dans la liste iListOfInputEdges,
// c'est-a-dire tous les contextes edge/face1/face2/shell qui peuvent etre passes a
// CATEdge::EvalGlobalSharpness(...) ou CATEdge::SetSharness(...)
//
// Une Edge peut conduire a plusieurs contextes de vivicite si elle borde plus de deux
// faces ou partagee par plusieurs shells du body.
//
// Au retour, le contexte de rang i est defini par
//
//    ioListOfEdges[i]
//    ioListOfFirstFaces[i]
//    ioListOfSecondFaces[i]
//    ioListOfShells[i]
//
ExportedByCXMODEL void CATTopGetSharpnessContextsForEdgesInList(CATBody*           ipBody,
                                                                CATLISTP(CATEdge)& iListOfInputEdges,
                                                                CATLISTP(CATEdge)& ioListOfEdges,
                                                                CATLISTP(CATFace)& ioListOfFirstFaces,
                                                                CATLISTP(CATFace)& ioListOfSecondFaces,
                                                                CATLISTP(CATShell)& ioListOfShells);

// Cette methode renvoie dans le contexte de ipBody tous les contextes possibles de vivicite
// applicables a vertex passe en entree dans ipVertex,
// c'est-a-dire tous les contextes ipVertex/edge1/edge2 qui peuvent etre passes a
// CATVertex::EvalSharpness(...) ou CATVertex::SetSharness(...)
//
// Au retour, le contexte de rang i est defini par
//
//    ipVertex
//    ioListOfFirstEdges[i]
//    ioListOfSecondEdges[i]
//
ExportedByCXMODEL void CATTopGetSharpnessContextsForVertex(CATBody*             ipBody,
                                                           CATVertex*           ipVertex,
                                                           CATLISTP(CATEdge)&   ioListOfFirstEdges,
                                                           CATLISTP(CATEdge)&   ioListOfSecondEdges);

// Cette methode renvoie dans le contexte de ipBody tous les contextes possibles de vivicite de vertices,
// c'est-a-dire tous les contextes vertex/edge1/edge2 qui peuvent etre passes a
// CATVertex::EvalSharpness(...) ou CATVertex::SetSharness(...)
//
// Au retour, le contexte de rang i est defini par
//
//    ioListOfVertices[i]
//    ioListOfFirstEdges[i]
//    ioListOfSecondEdges[i]
//
ExportedByCXMODEL void CATTopGetAllVertexSharpnessContexts(CATBody*             ipBody,
                                                           CATLISTP(CATVertex)& ioListOfVertices,
                                                           CATLISTP(CATEdge)&   ioListOfFirstEdges,
                                                           CATLISTP(CATEdge)&   ioListOfSecondEdges);

// Cette methode renvoie dans le contexte de ipBody tous les contextes possibles de vivicite
// applicables aux vertices passes en entree dans la liste iListOfInputVertices,
// c'est-a-dire tous les contextes vertex/edge1/edge2 qui peuvent etre passes a
// CATVertex::EvalSharpness(...) ou CATVertex::SetSharness(...)
//
// Au retour, le contexte de rang i est defini par
//
//    ioListOfVertices[i]
//    ioListOfFirstEdges[i]
//    ioListOfSecondEdges[i]
//
ExportedByCXMODEL void CATTopGetSharpnessContextsForVerticesInList(CATBody*             ipBody,
                                                                   CATLISTP(CATVertex)& iListOfInputVertices,
                                                                   CATLISTP(CATVertex)& ioListOfVertices,
                                                                   CATLISTP(CATEdge)&   ioListOfFirstEdges,
                                                                   CATLISTP(CATEdge)&   ioListOfSecondEdges);

// Cette methode renvoie dans le contexte de ipBody :
// - le nombre total d'edges
// - la liste des edges marquees CATSmooth dans ioListOfSmoothEdges
// - la liste des edges marquees CATSharp dans ioListOfSharpEdges
ExportedByCXMODEL void CATTopGetEdgesByStoredSharpness( CATBody*           ipBody,
                                                        int&               oTotalNbEdgesInBody,
                                                        CATLISTP(CATEdge)& ioListOfSmoothEdges,
                                                        CATLISTP(CATEdge)& ioListOfSharpEdges);


// Renvoie une chaine du style "SHARP CONVEX STATIC."
ExportedByCXMODEL void DumpSharpnessData(	ostream*			ipostream,
											                    CATGeoContinuity	iContinuity,
											                    CATGeoConvexity		iConvexity,
                                          CATBoolean*			ipStatic,
                                          CATBoolean			iWithFinalDot);

ExportedByCXMODEL void DumpContinuityData(	ostream*			ipostream,
											                    CATTopGeoContinuity	iContinuity,
                                          CATBoolean*			ipStatic,
                                          CATBoolean			iWithFinalDot);

#endif
