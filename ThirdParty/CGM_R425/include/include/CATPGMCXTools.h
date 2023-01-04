#ifndef CATPGMCXTools_h_
#define CATPGMCXTools_h_

// COPYRIGHT DASSAULT SYSTEMES 2010

#include "CATGMModelInterfaces.h"
#include "CATCollec.h"
#include "CATBoolean.h"
#include "CATIACGMLevel.h"
#include "CATBodyFreezeMode.h"

class CATBody;
class CATCurve;
class CATDomain;
class CATEdgeCurve;
class CATFace;
class CATMacroPoint;
class CATMathLine;
class CATMathPoint;
class CATPoint;
class CATShell;
class CATSurParam;
class CATTopData;
class CATLISTP(CATEdge);
class CATLISTP(CATWire);
class CATLISTP(CATPoint);
class CATLISTP(CATCurve);
class CATLISTP(CATCell);
class CATLISTP(CATDomain);
class CATGeometry;
class CATCGMObject;
class CATLISTP(CATCellManifold);
class CATCGMHashTable;
class CATCellHashTable;
class CATCGMOperator;

//----------------------------------------------------------------------------
// FOR INTERNAL USE ONLY
//----------------------------------------------------------------------------
class ExportedByCATGMModelInterfaces CATPGMCXTools
{
public:
  //----------------------------------------------------------------------------
  // Obtention des Cellules qui sont naturellement attendues dans le suivi :
  //  Toutes les Faces, Toutes les aretes bords libres, Toutes les vertes isoles
  //----------------------------------------------------------------------------
  static void GetExpectedCellsForReporting(
    CATBody *inBody,
    CATLISTP(CATCell) &ioReportingCells,
    const short iListManage_0Define_1Append = 0,
    const short iSel_BordOnly0_Full1_FullNoNonBordVx2 = 0);

  static void GetExpectedCellsForReporting_Helper(
    CATBody *inBody,
    CATLISTP(CATCell) &ioReportingCells,
    const short iListManage_0Define_1Append = 0,
    const short iSel_BordOnly0_Full1_FullNoNonBordVx2 = 0);

 static void GetExpectedCellsForReporting(
    CATBody *inBody,
    CATCellHashTable *&ioReportingCells,
    const short iListManage_0Define_1Append = 0,
    const short iSel_BordOnly0_Full1_FullNoNonBordVx2 = 0);

#ifdef CATIAR208
  //----------------------------------------------------------------------------
  // Obtention des Cellules qui sont naturellement attendues dans le suivi :
  //  Toutes les Faces, Toutes les aretes bords libres, Toutes les vertes isoles
  //----------------------------------------------------------------------------
  static void GetExpectedCellsForReportingLS(
     CATBody *inBody,
     CATLISTP(CATCellManifold) &ioReportingCells,
     const short iListManage_0Define_1Append = 0);
#endif

  //----------------------------------------------------------------------------
  // Obtention des Domaines qui sont naturellement attendues dans le suivi :
  //  Toutes les domaines de dimension plus élevées et fédérés par le body 
  //----------------------------------------------------------------------------
  static void GetExpectedDomainsForReporting(
    CATBody *inBody,
    CATLISTP(CATDomain) &ioReportingDomains,
    const short iListManage_0Define_1Append = 0);

  //-----------------------------------------------------------------------------------------------
  //
  //  Service a disponibilite restreinte dans un premier temps
  //
  //      Build CXR11 minum
  //      set CATCGM_WYSIWYG=1
  //      set CATDevelopmentStage=TRUE
  //
  //   GeometricObjects\ProtectedInterfaces\CATCGM_WYSIWYG.h
  //
  // Obtention des composantes geometriques directement referencees par la topologie
  //-----------------------------------------------------------------------------------------------
  //  L'analyse est relative a l'instant present
  //  L'analyse est etablie en prenant en compte tous les objets vivants dans la CATGeoFactory
  //  L'analyse ne prenant en compte initialement que le usages directs 
  //    ( i.e Edge   : PCurve de representation dans une Loop 
  //      ou  Vertex : Poecs de representation d'une Edge incidente)
  //   mais on peut etendre cette analyse avec les usages du Pose-Sur
  //----------------------------------------------------------------------------------------------------------
  //  On priviligiera cette methode au parcours exhaustif des composantes independantes de leur utilisation 
  //        (CATMacroPoint *) -> Next
  //        GeometricObjects\ProtectedInterfaces\CATEdgeCurveIterator.h
  //  Ne prendre en compte que les usages topologiques permettant
  //   d'ecremer les composantes qui devraient tot ou tard etre nettoye par une approche CLEANER.
  //----------------------------------------------------------------------------------------------------------
  static void GetComponentsUsedByTopology(
    CATEdgeCurve *iEdgeCurve,
    CATBoolean iWithWeakLinks,
    CATLISTP(CATCurve) &ioReps);

  static CATBoolean IsUsedByTopology(CATCurve *iCurve, CATBoolean iWithWeakLinks);

  static void GetComponentsUsedByTopology(
    CATMacroPoint *iMacroPoint,
    CATBoolean iWithWeakLinks,
    CATLISTP(CATPoint) &ioReps);

  static CATBoolean IsUsedByTopology(CATPoint *iCurve, CATBoolean iWithWeakLinks);

  //---------------------------------------------------------------------------------
  // Obtention d'un point "milieu" acceptable pour un shell.
  // - Le point resultat est un resultat de "EstimateCenterParamOnFace" sur une face
  // choisie comme etant la plus "proche" du centre du bloc d'encombrement du shell 
  // - Remarque : ce service est destiné à la visu , sa stabilité est non garantie
  //---------------------------------------------------------------------------------
  static void EstimateCenterParamOnShell(
    CATShell *iShell,
    CATFace *&ioFace,
    CATSurParam &ioSurParam);

  //------------------------------------------------------------------------------
  // Obtention du point "milieu" acceptable pour une face ,
  // le parametre resultant etant a l'interieur de la face :
  // - on obtient le meme resultat que "EstimateCenterParam" si et seulement si
  //   le resultat de "EstimateCenterParam" est a l'interieur de la face.
  // - Remarque : ce service est destiné à la visu , sa stabilité est non garantie
  //------------------------------------------------------------------------------
  static void EstimateCenterParamOnFace(CATFace *iFace, CATSurParam &ioSurParam);

  //------------------------------------------------------------------------------
  // GetWireOrderAndReferenceEdge : wire and edge stabilization
  // - iWiresList  : list of wire to analyze 
  // - oWiresOrder : return the order of each wire based on topological / geometric criterion 
  //                 ( size is number of wire , each value is unique between 1 and NbWires )
  //   + topological criteria : number of edges
  //   + geometric criteria : wire length.
  //   + other criterion : X / Y / Z position
  // - oReferenceEdges : return the reference edge for each wire ( size is number of wire )
  //   + if the domain is not closed , return the first edge
  //   + geometric criteria : edge length
  //   + other criterion : X / Y / Z position 
  //------------------------------------------------------------------------------
  static void GetWireOrderAndReferenceEdge(
    CATTopData &iTopData,
    CATLISTP(CATWire) &iWiresList,
    CATListOfInt &oWiresOrder,
    CATLISTP(CATEdge) &oReferenceEdges);

  //------------------------------------------------------------------------------
  // IsFaceAPlanarRevolCrown : Face Planar Revol crown recognization
  // "A face planar revol crown" is the result of a revol of a line
  // perpendicular to a revol axis :
  // - This face is lying on a plane and made of one or two loops.
  // - This face is made of 2 , 3 or 4 edges.
  // - The boundary edges of this face are made of : 
  //   + PCircle which have the same center position on the plane.
  //   + PLine 
  // This service return FALSE if it is not the case
  // It return TRUE if it is the case. Then "oRevolLine" line indicates the
  // position and direction of the revol axis line.
  //------------------------------------------------------------------------------
  static CATBoolean IsFaceAPlanarRevolCrown(
    CATTopData *iTopData,
    CATFace *iFace,
    CATMathLine &oRevolLine);

  //------------------------------------------------------------------------------
  // GetGeometryDimension
  // return the dimension of the input geometry if this geometry is a CATCell
  // or a CATCellManifold, return -1 otherwise
  //------------------------------------------------------------------------------
  static short GetGeometryDimension(CATGeometry *iGeometry);

  //------------------------------------------------------------------------------
  // GetDimBody
  // return the dimension of the Body 3 if the body contains at elast one Lump
  //------------------------------------------------------------------------------
  static int GetDimBody(CATBody *piBody);

  //------------------------------------------------------------------------------
  // IsAVolumiqBody
  // return the true if the body contains only Lump domains false otherwise
  //------------------------------------------------------------------------------
  static CATBoolean IsAVolumiqBody(CATBody *piBody);

  //------------------------------------------------------------------------------
  // AddBorderedCellsInHashTable
  //------------------------------------------------------------------------------
  /**
  * Scan the Hash Table of Cells <tt>ioHashTableOfCells</tt> and add this 
  * hash table the border cells.of each cell. If a given cell is a face, it adds its 
  * edges and vertices and if it's an edge, it adds its vertices.
  * @param ioHashTableOfCells 
  *   Hash Table of Cells to be scanned 
  */
  static void AddBorderedCellsInHashTable(CATCGMHashTable *ioHashTableOfCells);

  //----------------------------------------------------------------------------
  // Internal & Private : DO NOT USE (@KY1)
  //----------------------------------------------------------------------------
  /**
  * @nodoc
  */
  static void TransferTopData(CATCGMOperator *piCGMOperator, CATTopData *piTopData);

  //----------------------------------------------------------------------------
  // Internal & Private : DO NOT USE (@KY1)
  //----------------------------------------------------------------------------
  /**
  * @nodoc
  */
  static void TransferFreezeMode(
    CATCGMOperator *piCGMOperator,
    CATBodyFreezeMode iMode);

};

#endif /* CATPGMCXTools_h_ */
