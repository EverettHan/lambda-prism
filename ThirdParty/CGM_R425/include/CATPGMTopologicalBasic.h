#ifndef CATPGMTopologicalBasic_h_
#define CATPGMTopologicalBasic_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATBoolean.h"
#include "CATCollec.h"
#include "CATDataType.h"
#include "CATTopDefine.h"
#include "CATTopDef.h"
#include "CATMathConstant.h"
#include "ListPOfListPOfCATFace.h"

#ifndef NULL
#define NULL 0
#endif

class CATBody;
class CATCrvParam;
class CATDomain;
class CATEdge;
class CATFace;
class CATGeoFactory;
class CATLISTP_CATCell_;
class CATMathVector;
class CATPCurve;
class CATPoint;
class CATPointOnCurve;
class CATPointOnEdgeCurve;
class CATPointOnSurface;
class CATShell;
class CATSoftwareConfiguration;
class CATSurParam;
class CATVertex;
class CATCell;
class CATLoop;
class CATSurLimits;
class CATEdgeCurve;
class CATLISTP(CATEdge);
class CATLISTP(CATFace);
class CATLISTP(CATCell);

class ExportedByCATGMModelInterfaces CATPGMTopologicalBasic
{
public:
  //------------------------------------------------------------------------------
  // Determination si une cellule est sur le bord d'une autre cellule
  // (exemples: une Edge est sur le bord d'une Face, mais un Vertex qui est sur
  // une telle Edge l'est aussi)
  //------------------------------------------------------------------------------
  // Renvoie CATBoolean(1) si Cell fait partie du bord de BoundedCell  
  static CATBoolean IsOnBorder(
    CATCell *iCell,
    CATCell *iBoundedCell,
    CATSide &oSide);

  static void CreateBorder(
    CATBody *Body,
    CATEdge *Edge,
    CATPointOnEdgeCurve *StartPOEC,
    CATPointOnEdgeCurve *EndPOEC,
    CATVertex **StartVertex = NULL,
    CATVertex **EndVertex = NULL);

  //------------------------------------------------------------------------------
  // Get cells bordered by a given border cell on a given side
  // (i.e. the bordered cells' matter with respect to the border cell 
  // is on the opposite side)
  //------------------------------------------------------------------------------
  static void GetBoundedCellsOnSide(
    CATCell *iBorderCell,
    CATSide iSide,
    CATBody *inBody,
    CATLISTP(CATCell) &oCell);

  //------------------------------------------------------------------------------
  // Create a vertex located at a given parameter value on an edge
  // Please note: The vertex is not linked in any way to the edge
  //------------------------------------------------------------------------------
  static CATVertex *CreateVertexOnEdge(
    CATBody *iBody,
    CATEdge *iEdge,
    CATCrvParam &iParam);

  static CATVertex *CreateVertex(
    CATBody *ipBodyCreator,
    CATPointOnEdgeCurve *ipPOEC);

  static CATEdge *CreateEdge(
    CATBody *ipBodyCreator,
    CATEdgeCurve *ipEdgeCurve,
    CATOrientation iOriEdgeCurveVsEdge,
    CATPointOnEdgeCurve *ipStartPOEC,
    CATPointOnEdgeCurve *ipEndPOEC);

  //------------------------------------------------------------------------------
  // Decoupe d'une edge en deux en un point donne
  // NB: Aucun test de validite de la decoupe n'est effectue. i.e. des "petites"
  //     aretes peuvent etre generees
  //------------------------------------------------------------------------------
  static void SplitEdgeAtPoint(
    CATBody *iBody,
    CATEdge *iEdge,
    CATCrvParam &iParam,
    CATEdge *&LeftEdge,
    CATVertex *&Vertex,
    CATEdge *&RightEdge);

  //------------------------------------------------------------------------------
  // Determination du Domain contenu dans un Body et contenant une cellule
  // WARNING: ne pas utiliser pour le chercher le shell d'une face 
  //          ==> KO si on a affaire a un body ferme !
  //          mais utiliser   CATPGMTopTools::GetShell
  //------------------------------------------------------------------------------
  static CATDomain *GetDomain(CATBody *iBody, CATCell *iCell, CATSide &oSide);

  //------------------------------------------------------------------------------
  // Determination des cellules communes au bords de deux cellules fournies en
  // entree
  //------------------------------------------------------------------------------
  static void GetCommonBorderCells(
    CATCell *iCell1,
    CATCell *iCell2,
    CATLONG32 DepthOfSearch,
    CATLISTP(CATCell) &CommonCell);

  //------------------------------------------------------------------------------
  // Get the border domain containing a given border cell of a given bounded cell
  //------------------------------------------------------------------------------
  static CATDomain *GetDomainOfBorderCell(
    CATBody *iBody,
    CATCell *iBorderCell,
    CATCell *iCell);

  //------------------------------------------------------------------------------
  // Get the border domain containing a given border cell of a given bounded cell
  // by using a downwards iterator
  //------------------------------------------------------------------------------
  static CATDomain *GetDomainOfBorderCell(CATCell *iBorderCell, CATCell *iCell);

  //------------------------------------------------------------------------------
  // Get the side of an edge bounding a shell
  // (return unknown if the edge is internal)
  //------------------------------------------------------------------------------
  static CATSide GetSideEdgeVsShell(CATBody *iBody, CATDomain *iDom, CATEdge *iEdge);

  // -------------------------------------------------------------------------------
  // Determine si deux faces partageant un vertex sont continues en normale. Dans le 
  // meme temps, on determine l'orientation de face2 par rapport a face1 de maniere
  // a avoir des orientations compatibles. Ceci pour les cas ou modulo pi les deux 
  // faces sont continues en normale. 
  // Cette routine devra etre optimisee afin de determiner sans calcul geometrique
  // la vivivite et l'orientation. Suppose peut etre d'avoir un manifold de refernce
  // -------------------------------------------------------------------------------
  static CATTopGeoContinuity CheckNormalContinuity(
    CATSoftwareConfiguration *iConfig,
    CATFace *iFace1,
    CATFace *iFace2,
    CATVertex *iVertex,
    CATTopSign &oOrientation);

  // -------------------------------------------------------------------------------
  // Determine si deux edges partageant un vertex sont continues en tangence.
  // Calcule egalement l'orientation de iEdge2 par rapport a iEdge1
  //
  // Renvoie Smooth si continue en tangente, Sharp sinon
  //  
  // -------------------------------------------------------------------------------
  static CATTopGeoContinuity CheckTangencyContinuity(
    CATEdge *iEdge1,
    CATEdge *iEdge2,
    CATVertex *iVertex,
    CATAngle &oAngle,
    CATTopSign &oOrientation);

  // -------------------------------------------------------------------------------
  // Determine si la tangente d'une edge est situe dans le plan tangent d'une face 
  // Renvoie smooth si ok, sharp sinon 
  // iFace : face servant definir le plan tangent 
  // iEdge : edge donnee
  // 
  // -------------------------------------------------------------------------------
  static CATTopGeoContinuity CheckTangencyContinuity(
    CATSoftwareConfiguration *iConfig,
    CATFace *iFace,
    CATEdge *iEdge,
    CATBody *inBody,
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
  static CATFace *GetAdjacentFace(
    CATEdge *iEdge,
    CATFace *iFace,
    CATBody *iBody,
    CATTopSign oOrientation);

  // -------------------------------------------------------------------------------
  // Determine les faces adjacentes a une edge
  // ATTENTION: la liste des faces n'est pas videe en entree !
  // -------------------------------------------------------------------------------
  static void GetBnddFaces(
    CATEdge *iEdge,
    CATBody *inBody,
    CATLISTP(CATFace) &oAdjFaces);

  static void GetBnddFaces(
    CATLISTP(CATEdge) &iEdgeList,
    CATBody *inBody,
    CATLISTP(CATFace) &oAdjFaces);

  // -------------------------------------------------------------------------------
  // Determine les cellules de dimension n+1 adjacentes a une cellule de dimension n
  // ATTENTION: la liste des cellules bordantes n'est pas videe en entree !
  // -------------------------------------------------------------------------------
  static void GetBnddCells(
    CATCell *iCell,
    CATBody *inBody,
    CATLISTP(CATCell) &oBnddCells);

  // -------------------------------------------------------------------------------
  // Determine les faces et les edges adjacentes a un vertex
  // oEdges  : Edges partageant le sommet
  // oSide   : Indique pour chaque edge si le vertex est left, ...
  // oFaces  : Faces partageant le sommet  
  // -------------------------------------------------------------------------------
  static void GetAllBnddCell(
    CATVertex *iVertex,
    CATBody *inBody,
    CATLISTP(CATEdge) &oEdges,
    CATListOfInt &oSide,
    CATLISTP(CATFace) &oFaces);

  // -------------------------------------------------------------------------------
  //oSmoothSkins : Memory is allocated to create each element of this list, so client needs to free it.
  // -------------------------------------------------------------------------------
  static void GetSmoothSkins(
    CATSoftwareConfiguration *iConfig,
    CATGeoFactory &iFactory,
    CATLISTP(CATFace) &iFaces,
    CATBody &iBody,
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
  static CATTopSign GetGoodOrientation(
    CATCell *iRefCell,
    CATCell *iCell,
    CATCell *iCommonCell);

  // -------------------------------------------------------------------------------
  // -------------------------------------------------------------------------------
  //   Services d'acces a la geometrie 
  // -------------------------------------------------------------------------------
  // -------------------------------------------------------------------------------
  //------------------------------------------------------------------------------
  // Get the poec on an EdgeCurve for a given vertex and edge
  //------------------------------------------------------------------------------
  static CATPointOnEdgeCurve *GetGeometryOn(
    CATSoftwareConfiguration *iConfig,
    CATVertex *iVertex,
    CATEdge *iEdge);

  static CATPointOnEdgeCurve *GetGeometryOn(CATVertex *iVertex, CATEdge *iEdge);

  // -------------------------------------------------------------------------------
  // Determine le parametre sur macro curve d'un vertex 
  // -------------------------------------------------------------------------------
  static void GetGeometryOn(
    CATVertex *iVertex,
    CATEdge *iEdge,
    CATCrvParam &ParmOnMCurve);

  // -------------------------------------------------------------------------------
  // Determine le parametre sur pcurve d'un vertex a partr d'une face et d'une 
  // edge  
  // (la fonction retourne un CATBoolean qui indique si le parametre
  // est une spec du POEC ou non)
  // -------------------------------------------------------------------------------
  /* Deprecated */
  static CATBoolean GetGeometryOn(
    CATVertex *iVertex,
    CATEdge *iEdge,
    CATFace *iFace,
    CATCrvParam &oParmOnPCurve,
    CATPCurve *&oPCurve);

  static CATBoolean GetGeometryOn(
    CATSoftwareConfiguration *iConfig,
    CATVertex *iVertex,
    CATEdge *iEdge,
    CATFace *iFace,
    CATCrvParam &oParmOnPCurve,
    CATPCurve *&oPCurve);

  // *************** OBSOLETE **********************
  //   A virer apres verification 
  //------------------------------------------------------------------------------
  // Determine le PointOnCurve sur l EdgeCurve a partir d'un vertex, d'une edge
  // et d'une face
  //------------------------------------------------------------------------------
  static CATPointOnEdgeCurve *GetGeometryOn(
    CATVertex *iVertex,
    CATEdge *iEdge,
    CATFace *iFace,
    CATPCurve *&oPCurve);

  static CATPointOnEdgeCurve *GetGeometryOn(
    CATSoftwareConfiguration *iConfig,
    CATVertex *iVertex,
    CATEdge *iEdge,
    CATFace *iFace,
    CATPCurve *&oPCurve);

  // *************** OBSOLETE **********************
  //------------------------------------------------------------------------------
  // Determine la PCurve sous une edge a partir d'une face
  //------------------------------------------------------------------------------
  /* Deprecated */
  static CATPCurve *GetGeometryOn(
    CATEdge *iEdge,
    CATFace *iFace,
    CATOrientation &oPCurveOrient);

  static CATPCurve *GetGeometryOn(
    CATSoftwareConfiguration *iConfig,
    CATEdge *iEdge,
    CATFace *iFace,
    CATOrientation &oPCurveOrient);

  //------------------------------------------------------------------------------
  // Private management of Loop Full Location. Forbidden use in CATIA.
  //------------------------------------------------------------------------------
  static void Done(CATLoop *iLoop);

  //------------------------------------------------------------------------------
  // Fast (session bufferized) Edge Sharpness
  //------------------------------------------------------------------------------
  static void GetGlobalSharpness(
    CATSoftwareConfiguration *iConfig,
    CATEdge *iEdge,
    CATFace *iFace1,
    CATFace *iFace2,
    CATTopSharpness &oSharpness,
    CATOrientation *oOrientation = NULL,
    CATShell *iShellOwningTheTwoFaces = NULL);

  //------------------------------------------------------------------------------
  // Check if a Face has a rectangular shape (also meaning no inner loops) with respect to it's support surface
  //------------------------------------------------------------------------------
  static CATBoolean IsRectangularShape(
    CATSoftwareConfiguration *iConfig,
    CATFace *iFace,
    CATSurLimits &oLimits);

};

ExportedByCATGMModelInterfaces int CATPGMGetMaxLowDim(CATBody *iBody);

#endif /* CATPGMTopologicalBasic_h_ */
