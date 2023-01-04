/* -*-C++-*- */
#ifndef CATTopTools_H
#define CATTopTools_H

// COPYRIGHT DASSAULT SYSTEMES 1998

//-----------------------------------------------------------------------------
//
// CATTopTools
// ------------------
//  Topologic Basic Services 
//  do not instanciate this class
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// May     98 Creation From TopologicalBasic              rad
// Dec     98 Added MakeShellFromFaces                    hkl
// Jan     99 Added EvalMiddle, EvalExtremities           hkl 
// 29/04/06 NLD Ajout de FindDegenerateEdges() et FindBorderedFaces()
// 12/06/08 NLD Ajout de LockOrUnlockUnderLyingGeometry()
// 28/01/09 NLD Ajout argument optionnel iConfig a ComputeMaxGapOnBody()
// 01/02/12 UVC Average sharpness angle of an edge
// 15/10/13 HLN Ajout de CreateEdgeFromCurve
// 07/07/15 DPS Add IsACGMExactTopology & IsACGMPolyhedralTopology static methods
// 21/04/16 DPS Add CreateBodyWithTheSameTypeOf in order to instanciate the right implementation (exact or polyhedral) 
//              according to the type of a topological interface as reference
// 31/05/22 QF2 Add GenericGroupCells. Compute GroupCells for all modeler. 
//-----------------------------------------------------------------------------

#include "YI00IMPL.h"
#include "CATErrorDef.h"
#include "CATTopDef.h"
#include "CATMathDef.h"
#include "ListPOfCATCell.h"
#include "ListPOfCATEdge.h"
#include "ListPOfCATFace.h"
#include "ListVOfLong.h"
#include "ListPOfCATTopology.h"
#include "ListPOfCATBody.h"
#include <CATListOfCATGeometries.h>

#include "CATBoolean.h"
#include "CATMathConstant.h"
#include "CATTopDefine.h"
#include "CATSurLimits.h"
#include "CATTopData.h"
#include "CATTopToolsGapCheckMode.h"

class CATMathPoint;
class CATMathVector;

class CATPointOnEdgeCurve;
class CATEdgeCurve;
class CATPCurve;
class CATCurve;
class CATSurface;
class CATCrvParam;
class CATMathBox;

class CATBody;
class CATShell;
class CATCell;
class CATEdge;
class CATFace;
class CATVertex;
class CATDomain;
class CATLoop;

class CATGeoFactory;
class CATSoftwareConfiguration;
class CATTopology;
 
#include "ListPOfCATConnectedCellsIterator.h"
#include "CATListOfInt.h"
#include "CATConnectedCellsIterator.h"
#include "CATBodyMode.h"

 
//class CATBoolean;

class ExportedByYI00IMPL CATTopTools
{
public:
  
  //----------------------------------------------------------------------------------------------------------
  // Type conversion
  //----------------------------------------------------------------------------------------------------------
  static void GetFaces(const ListPOfCATCell &iListOfCells, ListPOfCATFace &oListOfFaces);
  static void GetCells(const ListPOfCATFace &iListOfFaces, ListPOfCATCell &oListOfCells);

  //----------------------------------------------------------------------------------------------------------
  // Cf CATIPGMTopToolsCreateDomains.h without topology construction 
  //----------------------------------------------------------------------------------------------------------

  static void  MinimalPartitionForOrientableSolutions(const CATLISTP(CATCell) &             inputCells, 
                                                      const CATListOfInt      &             inputOrientations,
                                                      CATBody                             * iBody,
                                                      CATLISTP(CATConnectedCellsIterator) & oList,
                                                      int                                 & anomaliesDetected );

  //----------------------------------------------------------------------------------------------------------
  // Permets de s'appuyer sur l'evaluateur geometrique de Vivicite sous-jacent a Edge->EvalGlobalSharpness
  //----------------------------------------------------------------------------------------------------------
  static void  ComputeGlobalSharpness(
    
    CATCrvParam           PoecCrv[2],                 // equivalent a la restriction topologique de l'Edge
    
    CATOrientation        EdgeCurveOrientation,    // euiavelent au support geometrique de l'Edge
    CATEdgeCurve        * EdgeCurve,               //  ..  a l'orientation EdgeCurve / Edge
    CATPCurve           * PCurve[2],               //  ..  aux deux representants de l'EdgeCurve sur les Faces incidentes
    
    CATBoolean            FirstFaceIsLeft,         // determine si la premiere Face equivalente est vue Left dans Body/Shell/..
    CATSide               MattSideFace[2],         //  equivalent au cote Matiere Edge/Face
    CATOrientation        faceOrient[2],           //  .. a l'orientation Surface / Face
    CATSurface          * Surface[2],              //  .. a la representation geometrique des Faces
    
    CATTopSharpness     & oSharpness,                      // Resultat de l'evaluation globale (continuite et convexite)

    CATAngle            * ioWantingAngleInMiddle = NULL,   // desir d'une evaluation intermediaire 
    
    CATAngle              iMaxSmoothnessAngle = CATTopSharpAngle ); // possibilite de changer la tolerance angulaire de vivicite
  
  //----------------------------------------------------------------------------
  // Creation d'un Body mono-wire-mono-edge
  // a partir d'une edge, et eventuellement du body s'il existe deja
  //----------------------------------------------------------------------------
  static CATBody * CreateBodyMonoWireMonoEdge(CATEdge * iEdge, CATGeoFactory *iGeoFactory, CATBody * iBody=NULL, const CATBoolean iDuplicate=FALSE);

  //----------------------------------------------------------------------------
  // Creation d'une Edge a partir d'une Curve et d'un Body de creation eventuel
  //----------------------------------------------------------------------------
  static CATEdge *CreateEdgeFromCurve(CATGeoFactory *iGeoFactory, CATCurve *iCurve, CATBody *iBody = NULL);

  //----------------------------------------------------------------------------------------------------------
  // Calcul des Gaps sur les edges transverses d'un Body Shell superieurs au GapMax CGM
  //----------------------------------------------------------------------------------------------------------
  enum GapCheckMode
  {
    G0GapCheckMode = CATTopToolsG0GapCheckMode,
    SharpEdgeCheckMode = CATTopToolsSharpEdgeCheckMode,
    SmoothSharpEdgeCheckMode = CATTopToolsSmoothSharpEdgeCheckMode
  };
  static CATBoolean  ComputeMaxGapOnBody (CATBody                   * iBody,
                                          CATShell                  * iShell, 
                                          ListPOfCATEdge             &oListPOfEdge,
                                          CATLISTP(CATBody)         * oListPOfEdgeBody=NULL,
                                          CATTopTools::GapCheckMode   iGapCheckMode=CATTopTools::G0GapCheckMode,
                                          CATSoftwareConfiguration*   iConfig=NULL
                                         );

  static CATBoolean  ComputeMaxGapOnBody (CATBody                   * iBody,
                                          CATShell                  * iShell, 
                                          ListPOfCATEdge             &oListPOfEdge,
                                          CATLISTP(CATBody)         * oListPOfEdgeBody,
                                          CATTopTools::GapCheckMode   iGapCheckMode,
                                          const ListPOfCATEdge       &iListPOfEdgeToCheck,
                                          CATSoftwareConfiguration*   iConfig=NULL
                                         );
  //----------------------------------------------------------------------------------------------------------
  // Detection du caractere "mort-vivant" d'une edge
  //----------------------------------------------------------------------------------------------------------
  static CATBoolean CheckSmoothSharpEdge(CATEdge *iEdge,
                                         CATFace *iAdjFace1,
                                         CATFace *iAdjFace2);

  //----------------------------------------------------------------------------------------------------------
  // Permets de s'appuyer sur l'evaluateur geometrique de Vivicite sous-jacent a Edge->EvalSharpness
  //----------------------------------------------------------------------------------------------------------
  static void ComputeLocalSharpness(
    
    const CATCrvParam         & iParamOnEdgeCurve,  // equivalent a la restriction topologique de l'Edge
    
    CATOrientation        EdgeCurveOrientation,    // euiavelent au support geometrique de l'Edge
    CATEdgeCurve        * EdgeCurve,               //  ..  a l'orientation EdgeCurve / Edge
    CATPCurve           * PCurve[2],               //  ..  aux deux representants de l'EdgeCurve sur les Faces incidentes
    
    CATBoolean            FirstFaceIsLeft,         // determine si la premiere Face equivalente est vue Left dans Body/Shell/..
    CATSide               MattSideFace[2],         //  equivalent au cote Matiere Edge/Face
    CATOrientation        faceOrient[2],           //  .. a l'orientation Surface / Face
    CATSurface          * Surface[2],              //  .. a la representation geometrique des Faces
    
    CATTopSharpness     & oSharpness,              // Resultat de l'evaluation globale (continuite et convexite)
    CATAngle            & Angle,                   // Resultat
    
    CATAngle                 iMaxSmoothnessAngle = CATTopSharpAngle ); // possibilite de changer la tolerance angulaire de vivicite
  

  /**	@nodoc */
  /** 
  * Check sharpness of a vertex(edge) regarding its incident edges(faces) 
  *
  * @param iTopData [in]
  *   TopData that contain embed the SoftConfig 
  * @param iCell [in]
  *   Cell under scope 
  * @param iIncidCell1 [in]
  *   First Incident cell to iCell
  * @param iIncidCell2 [in]
  *   Second Incident cell to iCell
  *
  * @return
  * <dl>
  * <dt><tt>TRUE</tt>     <dd> if iCell is Shap
  * <dt><tt>FALSE</tt>    <dd> otherwise
  * </dl>
  *
  */
  static CATBoolean IsCellSmooth(CATTopData& iTopData,CATCell *iCell,CATCell* iIncidCell1,CATCell* iIncidCell2);


  /**	@nodoc */
  /** Specific method for the drafting.
  * <BR> Evaluates the transversal curvature discontinuity in order to decide whether to display the edge.
  * The result is the transversal curvature discontinuity, including adjacent surfaces curvature.
  * Do not use iRefCurvature (may disappear soon).
  */
  static double GetCurvatureStep(CATSoftwareConfiguration* iConfig, CATBody* iBody, CATEdge* iEdge, const double iRefCurvature=0.);

  //----------------------------------------------------------------------------------------------------------
  // ...
  //----------------------------------------------------------------------------------------------------------

  static void GetAllEdges(CATFace *iFace, ListPOfCATEdge &oEdges);
  
  static CATShell* GetShell (CATBody *iBody, CATCell *iCell, CATSide *oSide=NULL);
  
  static int GetBnddFacesOnShell(CATEdge  * iEdge, CATShell * iShell,
                                  CATBody  * iBody, CATFace  *oFaces[], const int SizeoFaces = 2);

  static  HRESULT GetBorderedFaces(CATBody *iBody, CATCell *iCell,
                                   CATLISTP(CATCell) & oFaces,
                                   CATListOfLong     & oNbOfFacesByDomain,
                                   short iSoftwareLevel = 0);

  static CATBoolean GetInfinite(CATDomain* iDomain);

  static CATBoolean IsSharingTopology(CATTopology* iFirst, CATTopology* iWith, 
                                      CATLISTP(CATTopology) *ioSharingFederator = NULL);

  // Check if the CGM implementation of the topological interface is exact (CATCXTopology) and V5 or not
  static CATBoolean IsACGMExactTopology(CATTopology * iTopoInterface);

  // Check if the CGM implementation of the topological interface is polyhedral (CATGMPolyTopology) or not
  static CATBoolean IsACGMPolyhedralTopology(CATTopology * iTopoInterface); 

  /*
  * Create a Body with the right implementation (exact or polyhedral) according to the type of a topological instance as reference
  * This service is Safe (Throw an error instead of returning a null pointer)
  * @param iTopoItfRef
  *   Topological interface (CATBody, CATDomain or CATCell) as reference type (exact or polyhedral)
  *   Can be set as NULL. In this case, the input factory is mandatory and the default type is Exact
  * @param iGeoFactory
  *   option : by default, the CATGeoFactory will be retrieved from iTopoItfRef via the GetContainer() API in explicit mode
  * @param iMode
  *   Option for initial working mode (to reconsider only in case of specific PCS smart management case study). 
  *   By default, data structure are set for best working conditions with core operations (Boolean,Tessellation).
  */
  static CATBody * CreateBodyWithTheSameTypeOf(CATTopology * iTopoItfRef, CATGeoFactory * iGeoFactory = NULL, CATBodyMode iMode = CatBodyMode_Working);


 /**
  *  -- GenericGroupCells -- 
  * ----------------------------------------------------------------------------------------
  *  [ Polyhedral Compliant ]
  *  In Dev. Use a generic algorithm for all modeler. DO NOT USE YET.
  * ----------------------------------------------------------------------------------------
  *  Group the input cells in a set of connected components.
  *  @param ipCellsToGroup
  *    The input cells to group. They have to belong to the given ipBody.
  *  @param oNbCellByGroup
  *    output list of short containing the cells number of each connected component.
  *  @param oGroups
  *    The resulting connected component.
  *  @param iConsiderNonManifold
  *    Example: If 3 faces are connected by one edge
  *      iConsiderNonManifold = TRUE means that the 3 faces will be in 3 connected components
  *      iConsiderNonManifold = FALSE means that the 3 faces will be in one single connected component.
  *    Same thing for edges.
  *  @param ipConfig
  *    The CGM Config.
  *  @return
  *    HRESULT
  */  
  static HRESULT GenericGroupCells(CATSoftwareConfiguration * ipConfig,
                                    CATBody                  * ipBody,
                                    const ListPOfCATCell     & iCellsToGroup, 
                                    CATListOfLong            & oNbCellByGroup, 
                                    ListPOfCATCell           & oGroups, 
                                    CATBoolean         iConsiderNonManifold=FALSE, 
                                    CATBoolean         iConsiderImprint=FALSE);

  //----------------------------------------------------------------------------------------------------------
  //   Renvoie en valeur de retour le nombre de domaine trouves
  // L'appelant fournit en entree un Tableau avec sa dimension que l'on remplit sans debordement
  //  Verifier que la valeur de retour est inferieure ou egale a la dimension du Tableau
  //  Sinon reeffectuer un appel avec un Tableau de la dimension adequate
  //----------------------------------------------------------------------------------------------------------
  static int GetBoundedDomains(CATCell   *iCell,  CATBody  * iBody, 
                               CATDomain *(oDomains[]), CATOrientation *oOrientations, const int SizeOutput = 1);


  static void GetBnddEdgesOnFace(CATVertex *iVertex, CATFace *iFace, ListPOfCATEdge &oEdges);

  static void EvalNormalOnShell(CATShell     * iShell,
                                CATMathPoint & oPoint,
                                CATMathVector& oNormal,
                                CATFace      * iFace=NULL);
  
  static double EvalTransversalCurvature(CATSoftwareConfiguration * iConfig,
                                         const CATCrvParam & iCrvParam,
                                         CATEdge    *iEdge, 
                                         CATFace    *iFace,
                                         CATBoolean &oIsOk);
  /* Deprecated */
  static double EvalTransversalCurvature(const CATCrvParam & iCrvParam,
                                         CATEdge    *iEdge, 
                                         CATFace    *iFace,
                                         CATBoolean &oIsOk);

  static void EvalExtremities(CATEdge*iEdge, CATMathPoint & oStartPt, CATMathPoint & oEndPt);
  static void EvalMiddle     (CATEdge*iEdge, CATMathPoint & oMidPt);

  static CATBoolean  IsShellAVolume (CATBody *  iBody,  CATShell * iShell );  
  static void GetBorderEdges(CATLISTP(CATFace) const &iFaces, CATLISTP(CATEdge) &oEdges, CATLISTP(CATFace) &oBorderFaces);


  static void Get2DExactBoundingBox(CATFace * iFace, CATSurLimits & o2DExactBoundingBox);

  //---------------------------------------------------
  // For access to UV Box of Loop
  //
  //    Old : Outer Loop (should be same same as owning Face(s) ) 
  //    New : Inner Loop (for )
  //
  //  Input      : Loop
  //  Output     : UV Box and optionnaly 3D Box
  //  Management : specify if first time computed, result should be kept on object
  //                   pros : if same request asked, quicker result (stored and not computed)
  //                   cons : increase memory and disk size
  //
  //  result UV Box specification : 
  //
  // Return Value : 
  //            TRUE  if good result 
  //            FALSE otherwise in abnormal case 
  //---------------------------------------------------
  static CATBoolean Get2DBoundingBox(CATLoop      * iLoop, 
                                     CATSurLimits & o2DBoundingBox,
                                     CATMathBox   * ioBox3D = NULL,
                                     CATBoolean     iFirstTimeComputedMustBeKept = FALSE );


  // renvoie TRUE s'il y a des edges degenerees
  // et rend leur liste.
  // construit optionnellement des bodies pour chacune de ces edges si un pointeur de liste de bodies est specifie
  static CATBoolean FindDegenerateEdges (CATGeoFactory *iFactory,
                                         CATTopData&    iTopData,
                                         CATTopology               * iTopology,
                                         double                      iMinLength,
                                         ListPOfCATEdge             &DegeneratedEdges,
                                         CATLISTP(CATBody)         * DegeneratedEdgesBodies) ;

  static void FindBorderedFaces    (CATGeoFactory *iFactory,
                                    CATTopData&    iTopData,
                                    CATBody*        iBody,
                                    ListPOfCATEdge& iEdges,
                                    CATLISTP(CATCell)& oFaces,
                                    CATLISTP(CATBody)* oFacesBodies) ;

  // Lock/Unlock des géométries sous les entrées pour gagner du temps
  // sur le chargement des equations qui ne sera fait qu'une seule fois
  // iLock = 1 pour lock, 0 pour Unlock
  static void LockOrUnlockUnderLyingGeometry(int iLock, CATLISTP(CATGeometry)& iListInput) ;

  // 01-Feb-2012 UVC: Obtain the angle between the surfaces on a point on an edge
  static void ComputeAngleOnEdge( const CATAngle      iMinSharpAngle,
                                               CATBoolean          iFirstFaceIsLeft,
                                               CATEdgeCurve      * iEdgeCurve,
                                               CATOrientation      iEdgeCurveOrientation,
                                               const CATCrvParam & iEdgeCurveParam,
                                               CATPCurve        ** iPCurve,
                                               CATSide           * iFaceMatterSide,
                                               CATOrientation    * iFaceOrientation,
                                               CATSurface       ** iSurface,
                                               CATAngle          & oAngle );

  // 01-Feb-2012 UVC: Obtain an average angle along an edge
  static void ComputeAverageAngleOnEdge( const CATAngle      iMinSharpAngle,
                                         CATBoolean          iFirstFaceIsLeft,
                                         CATEdgeCurve      * iEdgeCurve,
                                         CATOrientation      iEdgeCurveOrientation,
                                         CATCrvParam       * iEdgeCurveParam,
                                         CATPCurve        ** iPCurve,
                                         CATSide           * iFaceMatterSide,
                                         CATOrientation    * iFaceOrientation,
                                         CATSurface       ** iSurface,
                                         CATAngle          & oAngle,
                                         const short         iNbSamples = 5);

  static CATAngle AverageAngleComputation(CATEdge         * iEdge,
                                          CATFace         * iFace[2],
                                          CATBoolean        iFirstFaceIsLeft);

  //REN Wk 13 2012 
  static void ComputeAdvancedAnglesOnEdge(const CATAngle     iMinSharpAngle,
                                         CATBoolean          iFirstFaceIsLeft,
                                         CATEdgeCurve      * iEdgeCurve,
                                         CATOrientation      iEdgeCurveOrientation,
                                         CATCrvParam       * iEdgeCurveParam,
                                         CATPCurve        ** iPCurve,
                                         CATSide           * iFaceMatterSide,
                                         CATOrientation    * iFaceOrientation,
                                         CATSurface       ** iSurface,
                                         CATListOfDouble & ioListOfMinMaxAvgAngles,
                                         CATListOfDouble & ioListOfMinMaxAvgParams,
                                         const short         iNbSamples = 5);


  static void CalcLength(CATSoftwareConfiguration* iConfig, CATEdge* iEdge, CATBoolean iExact, double& oLength);

};


#endif
