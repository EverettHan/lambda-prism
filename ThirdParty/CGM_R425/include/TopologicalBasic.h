#ifndef TopologicalBasic_H
#define TopologicalBasic_H

// COPYRIGHT DASSAULT SYSTEMES 1999

#include "CXMODEL.h"
#include "ExportedByCATTopologicalObjects.h"
#include "CATMathDef.h"
#include "CATCell.h"

#include "ListPOfCATCell.h"
#include "ListPOfCATEdge.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATDomain.h"
#include "ListPOfListPOfCATFace.h"
#include "CATListOfInt.h"
#include "CATMathInline.h"


class CATGeoFactory;
class CATPoint;
class CATPointOnCurve;
class CATPointOnEdgeCurve;
class CATPointOnSurface;

class CATBody;
class CATDomain;
class CATShell;
class CATLoop;
class CATVertex;
class CATEdge;
class CATFace;
class CATEdgeCurve;


class CATSurParam;
class CATCrvParam;
class CATSurLimits;
class CATPCurve;
class CATMathVector;
class CellHashTableAssocList;

class CATSoftwareConfiguration;

class ExportedByCATTopologicalObjects TopologicalBasic
{
public:
  
  
  //------------------------------------------------------------------------------
  // Determination si une cellule est sur le bord d'une autre cellule
  // (exemples: une Edge est sur le bord d'une Face, mais un Vertex qui est sur
  // une telle Edge l'est aussi)
  //------------------------------------------------------------------------------
  // Renvoie CATBoolean(1) si Cell fait partie du bord de BoundedCell  
  static CATBoolean IsOnBorder     
    (CATCell * iCell,                   // Cellule bord candidate
     CATCell * iBoundedCell,            // Cellule dont on cherche une cellule bord
     CATSide & oSide                    // Side si iCell est sur le bord immediat, Unknown sinon
    );
  
  static void CreateBorder (CATBody              *Body,
                            CATEdge              *Edge,
                            CATPointOnEdgeCurve  *StartPOEC,
                            CATPointOnEdgeCurve  *EndPOEC,
                            CATVertex           **StartVertex = NULL,
                            CATVertex           **EndVertex   = NULL);
  
  
  
  
  //------------------------------------------------------------------------------
  // Get cells bordered by a given border cell on a given side
  // (i.e. the bordered cells' matter with respect to the border cell 
  // is on the opposite side)
  //------------------------------------------------------------------------------
  
  static void GetBoundedCellsOnSide(CATCell          *iBorderCell, 
                                    CATSide           iSide,  
                                    CATBody          *inBody,
                                    ListPOfCATCell   &oCell); 
  
  //------------------------------------------------------------------------------
  // Create a vertex located at a given parameter value on an edge
  // Please note: The vertex is not linked in any way to the edge
  //------------------------------------------------------------------------------
  
  static CATVertex *CreateVertexOnEdge  // returns the generated vertex
    (CATBody         *iBody,       // Creation body
     CATEdge         *iEdge,       // Edge to be cut
     CATCrvParam     &iParam);     // Parameter on PCurve of edge
  
  static CATVertex* CreateVertex(CATBody * ipBodyCreator,
                                 CATPointOnEdgeCurve* ipPOEC);

  static CATEdge*  CreateEdge(CATBody * ipBodyCreator,
                              CATEdgeCurve * ipEdgeCurve,
                              CATOrientation iOriEdgeCurveVsEdge,
                              CATPointOnEdgeCurve * ipStartPOEC,
                              CATPointOnEdgeCurve * ipEndPOEC);
  //------------------------------------------------------------------------------
  // Decoupe d'une edge en deux en un point donne
  // NB: Aucun test de validite de la decoupe n'est effectue. i.e. des "petites"
  //     aretes peuvent etre generees
  //------------------------------------------------------------------------------
  
  static void  SplitEdgeAtPoint
    (CATBody         *iBody,       // Body de creation
    CATEdge         *iEdge,       // Edge a decouper
    CATCrvParam     &iParam,      // parametre identifiant le point de decoupe
    // sur la EdgeCurve de la Edge
    CATEdge        *&LeftEdge,    // Edge resultat a gauche du point de decoupe
    CATVertex      *&Vertex,      // Vertex cree au point de decoupe
    CATEdge        *&RightEdge);  // Edge resultat a droite du point de decoupe
  
  
  
  //------------------------------------------------------------------------------
  // Determination du Domain contenu dans un Body et contenant une cellule
  // WARNING: ne pas utiliser pour le chercher le shell d'une face 
  //          ==> KO si on a affaire a un body ferme !
  //          mais utiliser   CATTopTools::GetShell
  //------------------------------------------------------------------------------
  
  static CATDomain *GetDomain   // Renvoie le Domain
    (
    CATBody *iBody,     // Body en entree
    CATCell *iCell,     // Cellule en entree
    CATSide &oSide      // Cote matiere de la face par rapport au Domain en sortie
    );
  
  
  
  //------------------------------------------------------------------------------
  // Determination des cellules communes au bords de deux cellules fournies en
  // entree
  //------------------------------------------------------------------------------
  
  static void GetCommonBorderCells
    (
    CATCell         *iCell1,          // Premiere cellule en entree
    CATCell         *iCell2,          // Deuxieme cellule en entree
    CATLONG32             DepthOfSearch,   // Profondeur de recherche dans les bord:
    //   1 : on ne regarde que les bords immediats
    //       (exemple: les aretes bordant des faces)
    //   2 : on regarde aussi les bords des bords
    //       si on n'a rien trouve sur les bords immediats
    //   etc.
    ListPOfCATCell  &CommonCell       // Liste des cellules bords commune ayant la plus
    // grande dimension (i.e. toutes les cellules bordantes
    // dans la liste ont la meme dimension
    );
  
  
  //------------------------------------------------------------------------------
  // Get the border domain containing a given border cell of a given bounded cell
  //------------------------------------------------------------------------------
  
  static CATDomain *GetDomainOfBorderCell
    (CATBody *iBody,       // Body 
    CATCell *iBorderCell, // Border cell located on unknown border domain
    CATCell *iCell);      // Bounded cell
  
  
  //------------------------------------------------------------------------------
  // Get the border domain containing a given border cell of a given bounded cell
  // by using a downwards iterator
  //------------------------------------------------------------------------------
  
  static CATDomain *GetDomainOfBorderCell
    (CATCell *iBorderCell, // Border cell located on unknown border domain
    CATCell *iCell);      // Bounded cell
  
  //------------------------------------------------------------------------------
  // Get the side of an edge bounding a shell
  // (return unknown if the edge is internal)
  //------------------------------------------------------------------------------
  
  static CATSide GetSideEdgeVsShell (CATBody * iBody,
    CATDomain * iDom,
    CATEdge* iEdge);
  
  // -------------------------------------------------------------------------------
  // Determine si deux faces partageant un vertex sont continues en normale. Dans le 
  // meme temps, on determine l'orientation de face2 par rapport a face1 de maniere
  // a avoir des orientations compatibles. Ceci pour les cas ou modulo pi les deux 
  // faces sont continues en normale. 
  // Cette routine devra etre optimisee afin de determiner sans calcul geometrique
  // la vivivite et l'orientation. Suppose peut etre d'avoir un manifold de refernce
  // -------------------------------------------------------------------------------
  
  static CATTopGeoContinuity CheckNormalContinuity // Renvoie Smooth si continue en normale, Sharp sinon 
    (
    CATSoftwareConfiguration * iConfig, 
    CATFace                *iFace1,      // premiere face
    CATFace                *iFace2,      // seconde face
    CATVertex              *iVertex,     // vertex liant les deux faces 
    CATTopSign          &oOrientation // Orientation a appliquer a face2
    );
  
  // -------------------------------------------------------------------------------
  // Determine si deux edges partageant un vertex sont continues en tangence.
  // Calcule egalement l'orientation de iEdge2 par rapport a iEdge1
  //
  // Renvoie Smooth si continue en tangente, Sharp sinon
  //  
  // -------------------------------------------------------------------------------
  
  static CATTopGeoContinuity CheckTangencyContinuity(
    CATEdge                *iEdge1,      // premiere edge 
    CATEdge                *iEdge2,      // seconde edge 
    CATVertex              *iVertex,     // vertex liant les deux edges 
    CATAngle               &oAngle,      // Angle entre les tangentes 
    CATTopSign          &oOrientation // Orientation a appliquer a face2
    );
  
  // -------------------------------------------------------------------------------
  // Determine si la tangente d'une edge est situe dans le plan tangent d'une face 
  // Renvoie smooth si ok, sharp sinon 
  // iFace : face servant definir le plan tangent 
  // iEdge : edge donnee
  // 
  // -------------------------------------------------------------------------------
  
  static CATTopGeoContinuity CheckTangencyContinuity(CATSoftwareConfiguration * iConfig, 
    CATFace   *iFace,
    CATEdge   *iEdge,
    CATBody   *inBody,  
    CATVertex *iVertex);
  
  // -------------------------------------------------------------------------------
  // -------------------------------------------------------------------------------
  //   Recherches d'elements adjacents 
  // -------------------------------------------------------------------------------
  // -------------------------------------------------------------------------------
  
  // -------------------------------------------------------------------------------
  // Determine la face adjacente a une edge et a une face. Dans le meme temps
  // on determine l'orientation de la face adjacente de maniere a ce qu'elles 
  // forment un couple compatible   
  //
  //  Warning : Si l'edge borde la face passee en argument, on renvoie cette face
  //  -------
  //  oOrientation :  Sign entre iFace et le Resultat 
  // -------------------------------------------------------------------------------
  
  static CATFace * GetAdjacentFace(CATEdge        *iEdge,    
    CATFace        *iFace,    
    CATBody        *iBody,  
    CATTopSign  oOrientation  );
  
  
  // -------------------------------------------------------------------------------
  // Determine les faces adjacentes a une edge
  // ATTENTION: la liste des faces n'est pas videe en entree !
  // -------------------------------------------------------------------------------
  
  static void GetBnddFaces (CATEdge         *iEdge,    
    CATBody         *inBody,
    ListPOfCATFace  &oAdjFaces );
  

  static void GetBnddFaces (ListPOfCATEdge &iEdgeList,
                            CATBody        *inBody,
                            ListPOfCATFace &oAdjFaces );
  
  // -------------------------------------------------------------------------------
  // Determine les cellules de dimension n+1 adjacentes a une cellule de dimension n
  // ATTENTION: la liste des cellules bordantes n'est pas videe en entree !
  // -------------------------------------------------------------------------------
  static void GetBnddCells(CATCell        *iCell, 
    CATBody        *inBody,
    ListPOfCATCell &oBnddCells);
  
  
  // -------------------------------------------------------------------------------
  // Determine les faces et les edges adjacentes a un vertex
  // oEdges  : Edges partageant le sommet
  // oSide   : Indique pour chaque edge si le vertex est left, ...
  // oFaces  : Faces partageant le sommet  
  // -------------------------------------------------------------------------------
  
  static void GetAllBnddCell (CATVertex      *iVertex,
    CATBody*        inBody,
    ListPOfCATEdge &oEdges, 
    CATListOfInt   &oSide,  
    ListPOfCATFace &oFaces);
  
  // -------------------------------------------------------------------------------
  //oSmoothSkins : Memory is allocated to create each element of this list, so client needs to free it.
  // -------------------------------------------------------------------------------
  static void GetSmoothSkins(CATSoftwareConfiguration *iConfig, 
                             CATGeoFactory            &iFactory,
                             ListPOfCATFace           &iFaces, 
                             CATBody                  &iBody, 
                             ListPOfListPOfCATFace    &oSmoothSkins);

  // -------------------------------------------------------------------------------
  // -------------------------------------------------------------------------------
  //   Services d'orientation 
  // -------------------------------------------------------------------------------
  // -------------------------------------------------------------------------------
  
  // -------------------------------------------------------------------------------
  // Oriente une cellule de maniere coherente avec une cellule de reference
  //
  // Warning : Les cellules doivent etre de meme dimension - Pas de verifs
  // -------
  // -------------------------------------------------------------------------------
  
  static CATTopSign GetGoodOrientation // Renvoie le coeff correcteur
    (
    CATCell  *iRefCell,   // Cellule de reference 
    CATCell  *iCell,      // Cellule a orienter 
    CATCell  *iCommonCell // Cellule liant RefCell et Cell
    );
  
  
  // -------------------------------------------------------------------------------
  // -------------------------------------------------------------------------------
  //   Services d'acces a la geometrie 
  // -------------------------------------------------------------------------------
  // -------------------------------------------------------------------------------
  
  //------------------------------------------------------------------------------
  // Get the poec on an EdgeCurve for a given vertex and edge
  //------------------------------------------------------------------------------
  
  static CATPointOnEdgeCurve * GetGeometryOn
    (
    CATSoftwareConfiguration * iConfig, 
    CATVertex * iVertex, // Vertex dont on veut le Poec
    CATEdge   * iEdge    // Edge sur laquelle est pose iVertex
    );

  static CATPointOnEdgeCurve * GetGeometryOn
    (
    CATVertex * iVertex, // Vertex dont on veut le Poec
    CATEdge   * iEdge    // Edge sur laquelle est pose iVertex
    );
  
  // -------------------------------------------------------------------------------
  // Determine le parametre sur macro curve d'un vertex 
  // -------------------------------------------------------------------------------
  
  static void GetGeometryOn
    (
    CATVertex   *iVertex,     // Vertex dont on veut le CrvParam 
    CATEdge     *iEdge,       // Edge sur laquelle est pose Vertex
    CATCrvParam &ParmOnMCurve // Parametre sur la MacroCurve pointe par Edge du 
    );                         // representant de Vertex sur Edge
  
  
  // -------------------------------------------------------------------------------
  // Determine le parametre sur pcurve d'un vertex a partr d'une face et d'une 
  // edge  
  // (la fonction retourne un CATBoolean qui indique si le parametre
  // est une spec du POEC ou non)
  // -------------------------------------------------------------------------------
  /* Deprecated */
  static CATBoolean GetGeometryOn 
    (
    CATVertex    *iVertex,       // Vertex "pose" sur iFace 
    CATEdge      *iEdge,         // Edge sur laquelle est pose iVertex et bordant iFace
    CATFace      *iFace,         // Face sur laquelle iVertex est "projete"
    CATCrvParam  &oParmOnPCurve, // Parametre du representant de iVertex sur oPCurve 
    CATPCurve   *&oPCurve        // Representant de iEdge sur iFace 
    );

  static CATBoolean GetGeometryOn 
    (
    CATSoftwareConfiguration * iConfig,
    CATVertex    *iVertex,       // Vertex "pose" sur iFace 
    CATEdge      *iEdge,         // Edge sur laquelle est pose iVertex et bordant iFace
    CATFace      *iFace,         // Face sur laquelle iVertex est "projete"
    CATCrvParam  &oParmOnPCurve, // Parametre du representant de iVertex sur oPCurve 
    CATPCurve   *&oPCurve        // Representant de iEdge sur iFace 
    );
  
  
  
  // *************** OBSOLETE **********************
  //   A virer apres verification 
  //------------------------------------------------------------------------------
  // Determine le PointOnCurve sur l EdgeCurve a partir d'un vertex, d'une edge
  // et d'une face
  //------------------------------------------------------------------------------
  static CATPointOnEdgeCurve *GetGeometryOn 
    (
    CATVertex    *iVertex,       // Vertex "pose" sur iFace 
    CATEdge      *iEdge,         // Edge sur laquelle est pose iVertex et bordant iFace
    CATFace      *iFace,         // Face sur laquelle iVertex est "projete"
    CATPCurve   *&oPCurve        // PCurve sous iEdge dans iFace
    );

  static CATPointOnEdgeCurve *GetGeometryOn 
    (
    CATSoftwareConfiguration * iConfig,
    CATVertex    *iVertex,       // Vertex "pose" sur iFace 
    CATEdge      *iEdge,         // Edge sur laquelle est pose iVertex et bordant iFace
    CATFace      *iFace,         // Face sur laquelle iVertex est "projete"
    CATPCurve   *&oPCurve        // PCurve sous iEdge dans iFace
    );
  // *************** OBSOLETE **********************
  
  //------------------------------------------------------------------------------
  // Determine la PCurve sous une edge a partir d'une face
  //------------------------------------------------------------------------------
  /* Deprecated */
  static CATPCurve *GetGeometryOn
    (
    CATEdge*        iEdge,         // Edge posee sur la meme surface que iFace
    CATFace*        iFace,         // Face permettant d'identifier la PCurve
    CATOrientation& oPCurveOrient  // Representant de iEdge sur la surface de iFace 
    );

  static CATPCurve *GetGeometryOn
    (
    CATSoftwareConfiguration * iConfig,
    CATEdge*        iEdge,         // Edge posee sur la meme surface que iFace
    CATFace*        iFace,         // Face permettant d'identifier la PCurve
    CATOrientation& oPCurveOrient  // Representant de iEdge sur la surface de iFace 
    );
  
  //------------------------------------------------------------------------------
  // Private management of Loop Full Location. Forbidden use in CATIA.
  //------------------------------------------------------------------------------
  static void Done(CATLoop* iLoop);

  //------------------------------------------------------------------------------
  // Fast (session bufferized) Edge Sharpness
  //------------------------------------------------------------------------------
  static void GetGlobalSharpness(CATSoftwareConfiguration *iConfig,
                                 CATEdge                  *iEdge,
                                 CATFace                  *iFace1,
                                 CATFace                  *iFace2,
                                 CATTopSharpness          &oSharpness,
                                 CATOrientation           *oOrientation = NULL,
                                 CATShell                 *iShellOwningTheTwoFaces = NULL);

  /** @nodoc @nocgmitf */
  static void DuplicateSharpnessDataForEdgeAndVertices(CATEdge * iEdge, CATEdge * iDuplicatedEdge);

  //------------------------------------------------------------------------------
  // Check if a Face has a rectangular shape (also meaning no inner loops) with respect to it's support surface
  //------------------------------------------------------------------------------
   static CATBoolean IsRectangularShape(CATSoftwareConfiguration* iConfig, CATFace* iFace, CATSurLimits& oLimits);

  //------------------------------------------------------------------------------
  // Evaluator on Body & PolyBody
  //------------------------------------------------------------------------------
  /** @nodoc @nocgmitf */
  static HRESULT Eval(const double         iRatioOnEdge  ,
                            CATEdge      & iEdge         ,
                            CATFace      & iFace         ,
                            CATMathPoint * ioPoint       ,
                            CATMathVector* ioEdgeTangent = NULL,
                            CATMathVector* ioFaceNormal  = NULL,
                            CATBoolean   * ioApproximatedTangent = NULL,
                            CATBoolean   * ioApproximatedNormal = NULL);
  //------------------------------------------------------------------------------

};


//-----------------------------------------------------------------------------------------------------------
// Migration ancienne offre de fonction globale sur methode statique de Classe
// surlesquelles on peut effectuer un suivi (Coverage, Lignes de Code, CodeReview, ...)
//-----------------------------------------------------------------------------------------------------------

INLINE CATBoolean IsOnBorder(CATCell * iCell, CATCell * iBoundedCell, CATSide & oSide)
{
  return TopologicalBasic::IsOnBorder(iCell,iBoundedCell,oSide); 
}

INLINE void CreateBorder(CATBody *Body, CATEdge *Edge, CATPointOnEdgeCurve  *StartPOEC, CATPointOnEdgeCurve  *EndPOEC,
                         CATVertex           **StartVertex = NULL, CATVertex **EndVertex   = NULL)
{
  TopologicalBasic::CreateBorder(Body,Edge,StartPOEC,EndPOEC,StartVertex,EndVertex); 
}

INLINE void GetBoundedCellsOnSide(CATCell *iBorderCell, CATSide iSide, CATBody *inBody, ListPOfCATCell   &oCell)
{
  TopologicalBasic::GetBoundedCellsOnSide(iBorderCell,iSide,inBody,oCell); 
}

INLINE CATVertex *CreateVertexOnEdge(CATBody *iBody, CATEdge *iEdge, CATCrvParam &iParam)
{
  return TopologicalBasic::CreateVertexOnEdge(iBody,iEdge,iParam); 
}

INLINE void  SplitEdgeAtPoint(CATBody *iBody, CATEdge *iEdge, CATCrvParam &iParam, 
                              CATEdge* &LeftEdge, CATVertex* &Vertex,  CATEdge* &RightEdge)
{
  TopologicalBasic::SplitEdgeAtPoint(iBody,iEdge,iParam,LeftEdge,Vertex,RightEdge); 
}

INLINE CATDomain *GetDomain(CATBody *iBody, CATCell *iCell, CATSide &oSide)
{
  return TopologicalBasic::GetDomain(iBody,iCell,oSide); 
}

INLINE void GetCommonBorderCells(CATCell *iCell1,  CATCell *iCell2, CATLONG32  DepthOfSearch, ListPOfCATCell  &CommonCell)
{
   TopologicalBasic::GetCommonBorderCells(iCell1,iCell2,DepthOfSearch,CommonCell); 
}

INLINE CATDomain *GetDomainOfBorderCell(CATBody *iBody, CATCell *iBorderCell, CATCell *iCell)
{
  return TopologicalBasic::GetDomainOfBorderCell(iBody,iBorderCell,iCell); 
}

INLINE CATDomain *GetDomainOfBorderCell(CATCell *iBorderCell,CATCell *iCell) 
{
  return TopologicalBasic::GetDomainOfBorderCell(iBorderCell,iCell); 
}

INLINE CATSide GetSideEdgeVsShell(CATBody * iBody, CATDomain * iDom, CATEdge* iEdge)
{
  return TopologicalBasic::GetSideEdgeVsShell(iBody,iDom,iEdge); 
}

INLINE CATTopGeoContinuity CheckNormalContinuity(CATSoftwareConfiguration * iConfig,
                                                 CATFace *iFace1, CATFace *iFace2, CATVertex *iVertex, CATTopSign &oOrientation)
{
  return TopologicalBasic::CheckNormalContinuity(iConfig, iFace1,iFace2,iVertex,oOrientation); 
}

INLINE CATTopGeoContinuity CheckTangencyContinuity(CATEdge *iEdge1, CATEdge *iEdge2, CATVertex *iVertex, CATAngle &oAngle, CATTopSign& oOrientation)
{
  return TopologicalBasic::CheckTangencyContinuity(iEdge1,iEdge2,iVertex,oAngle,oOrientation); 
}

INLINE CATTopGeoContinuity CheckTangencyContinuity(CATSoftwareConfiguration * iConfig,
                                                   CATFace *iFace, CATEdge   *iEdge, CATBody   *inBody, CATVertex *iVertex)
{
  return TopologicalBasic::CheckTangencyContinuity(iConfig, iFace,iEdge,inBody,iVertex); 
}

INLINE CATFace * GetAdjacentFace(CATEdge *iEdge, CATFace*iFace, CATBody *iBody, CATTopSign  oOrientation  )
{
  return TopologicalBasic::GetAdjacentFace(iEdge,iFace,iBody,oOrientation); 
}

INLINE void GetBnddFaces(CATEdge *iEdge,CATBody* inBody, ListPOfCATFace  &oAdjFaces )
{
  TopologicalBasic::GetBnddFaces(iEdge,inBody,oAdjFaces); 
}

INLINE void GetBnddCells(CATCell*iCell, CATBody* inBody, ListPOfCATCell &oBnddCells)
{
  TopologicalBasic::GetBnddCells(iCell,inBody,oBnddCells); 
}

INLINE void GetAllBnddCell(CATVertex      *iVertex,CATBody*        inBody,
                           ListPOfCATEdge &oEdges, CATListOfInt   &oSide, ListPOfCATFace &oFaces)
{
  TopologicalBasic::GetAllBnddCell(iVertex,inBody,oEdges,oSide,oFaces); 
}

INLINE CATTopSign GetGoodOrientation(CATCell  *iRefCell, CATCell  *iCell, CATCell  *iCommonCell)
{
  return TopologicalBasic::GetGoodOrientation(iRefCell,iCell,iCommonCell); 
}

INLINE CATPointOnEdgeCurve * GetGeometryOn( CATVertex * iVertex, CATEdge   * iEdge)
{
  return TopologicalBasic::GetGeometryOn(iVertex,iEdge); 
}

INLINE void GetGeometryOn(CATVertex   *iVertex,CATEdge     *iEdge, CATCrvParam &ParmOnMCurve )
{
  TopologicalBasic::GetGeometryOn(iVertex,iEdge,ParmOnMCurve); 
}

/* Deprecated */
INLINE CATBoolean           GetGeometryOn(CATVertex    *iVertex, CATEdge *iEdge, CATFace      *iFace,
                                          CATCrvParam  &oParmOnPCurve, CATPCurve   *&oPCurve)
{
  return TopologicalBasic::GetGeometryOn(iVertex, iEdge, iFace, oParmOnPCurve, oPCurve); 
}

/* Deprecated */
INLINE CATPointOnEdgeCurve *GetGeometryOn(CATVertex    *iVertex, CATEdge *iEdge, CATFace *iFace, CATPCurve *&oPCurve)
{
  return TopologicalBasic::GetGeometryOn(iVertex,iEdge,iFace,oPCurve); 
}

/* Deprecated */
INLINE CATPCurve *GetGeometryOn(CATEdge* iEdge, CATFace* iFace, CATOrientation& oPCurveOrient)
{
  return TopologicalBasic::GetGeometryOn(iEdge,iFace,oPCurveOrient); 
}

INLINE CATBoolean GetGeometryOn(CATSoftwareConfiguration * iConfig,
                                CATVertex *iVertex, CATEdge      *iEdge, CATFace      *iFace, CATCrvParam  &oParmOnPCurve, CATPCurve   *&oPCurve)
{
  return TopologicalBasic::GetGeometryOn(iConfig, iVertex,iEdge,iFace,oParmOnPCurve,oPCurve); 
}

INLINE CATPointOnEdgeCurve *GetGeometryOn(CATSoftwareConfiguration * iConfig,
                                          CATVertex    *iVertex, CATEdge *iEdge, CATFace *iFace, CATPCurve *&oPCurve)
{
  return TopologicalBasic::GetGeometryOn(iConfig, iVertex,iEdge,iFace,oPCurve); 
}

INLINE CATPCurve *GetGeometryOn(CATSoftwareConfiguration * iConfig,
                                CATEdge* iEdge, CATFace* iFace, CATOrientation& oPCurveOrient)
{
  return TopologicalBasic::GetGeometryOn(iConfig,iEdge,iFace,oPCurveOrient); 
}

ExportedByCATTopologicalObjects int      GetMaxLowDim(CATBody* iBody);

#endif
