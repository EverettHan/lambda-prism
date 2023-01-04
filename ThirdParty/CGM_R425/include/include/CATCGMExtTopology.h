/* -*-c++-*- */
#ifndef CATCGMExtTopology_H
#define CATCGMExtTopology_H
//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 2001
// DESCRIPTION : Default extension for CATTopology Class 
//               BUT Methods are not implemented
// CATV4TopGeometry inherits from this class
//
//=============================================================================
// Jan. 03   Les methodes suivantes sont DEPRECATED dans CATEdge.h
//           EvalSharpness                         GetLocalSharpness
//           EvalGlobalSharpness  => remplace par  GetGlobalSharpness
//           SetSharpness                          SetGlobalSharpness     HCN
// Feb. 04 GetCellNumbers(...)                                            HCN
// Jan. 05 Suppression CATIAV5R13 et CATIAV5R14                           HCN
// Aout 06 Bug (oubli de mettre defaut value arg. in GetGeometry)         CBK
//=============================================================================

/*

  La classe CATCGMExtTopology implemente toutes les methodes des interfaces suivantes :

     CATTopObject
     CATBody
     CATCell
     CATVolume
     CATFace
     CATEdge
     CATVertex
     CATDomain
     CATLump
     CATShell
     CATEdgeDomain
     CATWire
     CATLoop
     CATVertexInface
     CATVertexInVolume

  Les methodes mises en commemtaires sont les methodes avec la meme signature.

*/

#include "CATIACGMLevel.h" // automatic treatment EB_2014_04_16
#include "CATTopology.h"
#include "CATTopObject.h"
#include "CATBody.h"
#include "CATCell.h"
#include "CATVolume.h"
#include "CATFace.h"
#include "CATEdge.h"
#include "CATVertex.h"
#include "CATDomain.h"
#include "CATLump.h"
#include "CATShell.h"
#include "CATEdgeDomain.h"
#include "CATWire.h"
#include "CATLoop.h"
#include "CATVertexInFace.h"
#include "CATVertexInVolume.h"
#include "CATCGMExtensionV4.h"
#include "YI00IMPL.h"

class ExportedByYI00IMPL CATCGMExtTopology: public CATCGMExtensionV4
{
public:

  //===========================================================================
  // Adhesion a l'interface CATTopology
  //===========================================================================
  virtual void               GetAllCells(CATLISTP(CATCell)& ioResult, short iDimension);

  virtual void               GetCellNumbers(int* iopNbVertices, int* iopNbEdges, int* iopNbFaces, int* iopNbVolumes);

  virtual CATCellHashTable * GetAllCells(short iDimension);

  virtual CATBoolean         IsInside(CATBody* iBody, CATTopology* iTopologyInside=NULL,
                                      CATBoolean iGenerateUpwardLinks = FALSE);

  virtual CATBoolean         IsTouched();

  virtual void               Touch(CATBody* iBodyForImpactPropagation);

  virtual void               GetAllDomains(short iContainedCellsDimension,
                                           short iContainingCellDimension,
                                           CATLISTP(CATDomain)& ioResult);

  //===========================================================================
  // Adhesion a l'interface CATTopObject
  //===========================================================================
  virtual CATLONG32        GetNbDomains();

  virtual CATDomain * GetDomain(CATLONG32 iNum, CATLocation *oLocation);

  virtual void        AddDomainWithLocation(CATDomain * iDomain, CATLocation iLocation);

  virtual void        RemoveDomain(CATDomain * iDomainToDetach, CATBoolean iRemoveFromFactory);

  virtual int         GetBoundedTopObjects(CATBody * iBody,
                                           CATTopObject **ioUppers, CATSide *ioSides,
                                           const int iSizeOutput,
                                           CATDomain **ioDomains = NULL, CATGeometry **ioGeometries = NULL);

  virtual int         GetBoundaryTopObjects(CATTopObject **ioUppers, CATSide *ioSides,
                                            const int iSizeOutput,
                                            CATDomain **ioDomains = NULL, CATGeometry **ioGeometries = NULL);

  virtual int         IsBoundaryOfTopObject(CATTopObject *iUpper, CATSide *ioSides,
                                            const int iSizeOutput,
                                            CATDomain **ioDomains = NULL, CATGeometry **ioGeometries = NULL);

  virtual CATBoolean  HasInfiniteGeometry(); // TCX le 29/05/2001

  //===========================================================================
  // Adhesion a l'interface CATBody
  //===========================================================================
  virtual CATCell                * CreateCell(short iDimension);

  virtual CATVolume              * CreateVolume();

  virtual CATFace                * CreateFace();

  virtual CATEdge                * CreateEdge();

  virtual CATVertex              * CreateVertex();

  virtual CATDomain              * CreateDomain(short iContainedCellsDimension,
                                                short iContainingCellDimension,
                                                CATLocation iLocation);

  virtual CATLump                * CreateLump();

  virtual CATShell               * CreateShell(CATLocation iLocation);

  virtual CATWire                * CreateWire();

  virtual CATVertexInVolume      * CreateVertexInVolume();

  virtual CATLoop                * CreateLoop(CATLocation iLocation);

  virtual CATVertexInFace        * CreateVertexInFace();

  virtual void                     AddDomain(CATDomain * iDomainToAdd, CATLocation iLocation);

  virtual CATSmartBodyDuplicator * CreateSmartDuplicator(CATBody* iBodyToRecopy, CATTopData &iTopData);

  virtual CATICGMSmartBodyDuplicator*  CreateISmartDuplicator(CATBody* iBodyToRecopy, CATTopData &iTopData);

  virtual CATSmartBodyDuplicator * CreateSmartDuplicator(CATBody* iBodyToRecopy, CATCGMJournalList* iReport);

  virtual CATICGMSmartBodyDuplicator*  CreateISmartDuplicator(CATBody* iBodyToRecopy, CATCGMJournalList* iReport);

  virtual void                     GetCellsHighestDimension(CATLONG32& ioCellsMaxDim,CATBoolean& ioIsHomogeneous,
                                                            CATBoolean* ioIsLocallyManifold,
                                                            ListPOfCATCell * oNonManifoldCells = NULL);

  virtual CATLISTP(CATCell)        CATEdgePropagate(CATLISTP(CATCell) * iInitialEdges,
                                                    CATBody::CATPropagationTypePr3 iPropagationType,
                                                    CATLISTP(CATEdge) * iRollingEdges);

  virtual CATLISTP(CATFace)        CATFacePropagate(CATLISTP(CATFace) * iInitialFaces);

  virtual void                     GroupCells(const CATLISTP(CATCell) * iCellList,
                                              CATLISTP(CATConnectedCellsIterator) & ioCellsIterator);

  virtual CATLISTP(CATCell)        GroupCells(const CATLISTP(CATCell) * iCellList,
                                              CATListOfLong          & ioNbOfCellsByDomain);

  virtual CATLISTP(CATCell)        CommonEdges(const CATLISTP(CATCell) * iFaceList_1,
                                               const CATLISTP(CATCell) * iFaceList_2,
                                               CATListOfLong          & oListOrientation,
                                               CATListOfLong          & oNbOfEdgesByDomain);

  virtual CATLISTP(CATCell)        CellNeighbours(const CATLISTP(CATCell) * iCellList,
                                                  const CATListOfLong     * iListOrientation,
                                                  CATListOfLong           & oNbOfCellsByDomain,
                                                  const short iVersionGenericNaming = 0);

  virtual CATLISTP(CATCell)        SelectEdgesFromFaces(const CATLISTP(CATFace) * iFaceList);

  virtual CATLISTP(CATFace)        FacePropagateReflectLine(CATBody::CATReflectPropagationType  Propagation,
                                                            const CATMathVector        &PullingDirection,
                                                            const CATAngle            &Angle,
                                                            const CATLISTP(CATFace)   *iInitialFaces);

  virtual CATBoolean               CheckWiresIntersection(CATSurface *iSurface); 

  virtual void                     Freeze();

  virtual CATGeoFactory          * GetFactory();

  virtual CATTopLyingOnDiagnostic  IsLyingOn(CATBody* iDomain);

  virtual void CleanTouch(); // TCX le 29/05/2001

  //===========================================================================
  // Adhesion a l'interface CATCell
  //===========================================================================
  // virtual void                      AddDomain(CATDomain * iDomain, CATLocation iLocation = CATLocationUnknown);

  virtual CATLONG32                      GetNbInternalDomains();

  virtual short                     GetDimension();

  virtual void                      AddBoundingCell(CATCell * iBoundingCell, CATSide iSideOrientation, 
                                                    CATDomain * iDomain,   CATGeometry* iWithGeometry);

  virtual void                      RemoveBoundingCell(CATCell * iCellToRemove, CATBoolean iRemoveFromFactory = FALSE );

  virtual void                      SetGeometry(CATGeometry * iGeometry,
                                                CATOrientation iOrientation);

  virtual void                      SetGeometryOrientation(CATOrientation iNewOrientation);

  virtual CATGeometry             * GetGeometry(CATOrientation * ioOrientation = NULL );

  virtual CATOrientation            GetGeometryOrientation();

  virtual void                      SetGeometryOnCell(CATCell     * iBoundedCell, 
                                                      CATSide       iSide,
                                                      CATGeometry * iGeomOnSupport);

  virtual CATGeometry             * GetGeometryOnCell(CATCell        * iBoundedCell, 
                                                      CATSide          iSide, 
                                                      CATOrientation * ioOrientation);

  virtual CATBoundaryIterator     * CreateBoundaryIterator();

  virtual CATBoundedCellsIterator * CreateBoundedCellsIterator(CATBody* iInBody);

  virtual CATULONG32              GetNbBoundedCells(CATBody*   inBody, 
                                                      CATBoolean iDifferentiateMatterSide);

  virtual HRESULT                   CellNeighbours(CATBody *inBody, ListPOfCATCell  &oNeighbourCells);

  virtual void                      SetInfinite(CATBoolean iYesOrNo);

  virtual CATBoolean                GetInfinite() const;

  virtual CATBoolean                IsOnBorder(CATCell* iUpperDimCell,
                                               CATSide* ioSide);

  virtual CATSide                   GetMatterSide(CATCell* iUpperDimCell);

  virtual CATCell                 * GetNeighborCell(CATCell*    iBorderCell,
                                                    CATBody*    iInBody,
                                                    short*  ioRelativeOrientation);

  virtual HRESULT  GetNeighborCells(CATCell*           iBorderCell,       CATBody*     iInBody,
                                    CATLISTP(CATCell)& ioNeighborCells,   CATListOfLong * ioRelativeOrientations =NULL ) ;

  virtual void                      GetCommonBorderCells(CATCell*           iCell, 
                                                         short              iMaxDepthSearch,
                                                         CATLISTP(CATCell)& ioResultCells,
                                                         short              iResultCellsDimension);

  virtual void                      EstimateCenter(CATMathPoint& ioResult) const;

  virtual void                      SetLyingOn(CATCell* iSupport,CATGeometry* iWithAssociatedGeometry);

  virtual void                      UnsetLyingOn(CATCell* iSupport);

  virtual void                      GetLyingOn(CATLISTP(CATCell)& ioSupports,CATBody* iInBody);

  virtual CATGeometry             * GetLyingGeometryOn(CATCell* iSupport);

  virtual CATBoolean                IsLyingOn(CATTopology           *iContainerOfSupportingCell, 
                                              CATLISTP(CATCell)     *ioSupports = NULL, 
                                              CATLISTP(CATGeometry) *ioGeomSupports = NULL);
  
  virtual CATBoolean                IsCandidateForReporting(CATBody* inBody);  // TCX le 29/05/2001

  virtual void                      GetLyingGeometriesOn(CATCell* iSupport, CATLISTP(CATGeometry)& ioGeomSupports);

  virtual void                      GetFederatorsLyingOn(CATBody* iInBody,  CATLISTP(CATTopology)& ioFederatorsSupport);


  //===========================================================================
  // Adhesion a l'interface CATVolume
  //===========================================================================
  // no method

  //===========================================================================
  // Adhesion a l'interface CATFace
  //===========================================================================
  virtual void                 SetSurface(CATSurface * iSurface,
                                          CATOrientation iOrientation);

  virtual CATSurface         * GetSurface(CATOrientation * ioOrientation);

  virtual const CATMathBox   * Get3DBoundingBox();

  virtual const CATSurLimits * Get2DBoundingBox();

  virtual void                 EstimateCenterParam(CATSurParam& oCenterParam) const;

  virtual CATBoolean           EvalNormal(CATSurParam&   iSurParam,
                                          CATMathVector& ioNormal,
                                          CATBoolean     iNormalization);

  virtual double               CalcArea();

  virtual CATFace            * SmartDuplication(CATBody* iBody,
                                                CATShell* iOldShell,
                                                CATShell* iShell,
                                                CATCGMJournalList* iJournal);

  virtual CATFace            * SmartDuplicationReplace(CATBody* iBody, CATShell* iShell, CATCGMJournalList* iJournal);

  //===========================================================================
  // Adhesion a l'interface CATEdge
  //===========================================================================
  virtual void                 SetCurve(CATEdgeCurve * iCurve, CATOrientation iOrientation);

  virtual CATEdgeCurve       * GetCurve(CATOrientation * ioOrientation);

  virtual CATPCurve          * GetGeometryOnFace(CATFace   * iBoundedFace, CATSide iSide,
                                                 CATOrientation * ioOrientation,
                                                 CATCrvParam  * ioStartParam,
                                                 CATCrvParam  * ioEndParam);

  virtual void                 SetGeometryOnFace(CATFace    * iBoundedFace,  CATSide  iSide,
                                                 CATPCurve           * iPCurve,
                                                 CATPointOnEdgeCurve * iStartVertexGeometry,
                                                 CATPointOnEdgeCurve * iEndVertexGeometry);

  virtual void                 SetGeometryOnSupport(CATPCurve           * iPCurve , 
                                                    CATOrientation        orientation,
                                                    CATPointOnEdgeCurve * iStart,
                                                    CATPointOnEdgeCurve * iEnd);

  virtual CATSide              GetSideOnFace(CATFace *iBoundedFace);

  virtual void                 SetSideOnFace(CATFace *iBoundedFace, CATSide iSide);

  virtual void                 GetNextInLoop(CATSide iSideVsFace, CATFace * iBoundedFace,
                                             CATEdge ** oNextEdge, CATSide * oSide);

  virtual void                 GetPreviousInLoop(CATSide iSideVsFace,
                                                 CATFace * iBoundedFace,
                                                 CATEdge ** oPrevEdge,
                                                 CATSide * oSide);

  virtual void                 GetVertices(CATVertex **oStartVertex, CATVertex **oEndVertex);

  virtual void                 GetVerticesPointsOnEdgeCurve(CATPointOnEdgeCurve  ** oStartPoec,
                                                            CATPointOnEdgeCurve  ** oEndPoec);

  virtual void                 GetVerticesParamsOnEdgeCurve(CATCrvParam * oStartParam, CATCrvParam * oEndParam);

  virtual CATBoolean           EvalTangent(const CATCrvParam & iParamOnEdgeCurve, 
                                           CATMathVector     & ioTangentVector,
                                           CATBoolean  iTgtNormalization);

  virtual CATAngle             EvalSharpness(const CATCrvParam & iParamOnEdgeCurve, 
                                             CATFace           * iFace1,
                                             CATFace           * iFace2,
                                             CATTopSharpness&    ioSharpness,
                                             CATOrientation    * oOrientation,
                                             CATShell*           iShellOwningTheTwoFaces);

  virtual void                 EvalGlobalSharpness(CATFace *iFace1,
                                                   CATFace *iFace2,
                                                   CATTopSharpness  & ioSharpness,
                                                   CATOrientation   * oOrientation,
                                                   CATShell         * iShellOwningTheTwoFaces,
                                                   CATBoolean       * oDefinedSharpness);

  virtual void                 SetSharpness(CATFace *iFace1, CATFace *iFace2,
                                            const CATGeoContinuity   iSharpness,
                                            const CATGeoConvexity    iConcavity,
                                            CATShell *iShellOwningTheTwoFaces);

  virtual CATAngle             GetLocalSharpness(CATTopData        & iTopData,
                                                 const CATCrvParam & iParamOnEdgeCurve, 
                                                 CATFace           * iFace1,
                                                 CATFace           * iFace2,
                                                 CATTopSharpness&    oSharpness,
                                                 CATOrientation    * oOrientation = NULL,
                                                 CATShell*           iShellOwningTheTwoFaces = NULL,
                                                 CATAngle            iMinSharpAngle = CATTopSharpAngle); // en rad


  virtual void                 GetGlobalSharpness(CATTopData       & iTopData,
                                                  CATFace          * iFace1,
                                                  CATFace          * iFace2,
                                                  CATTopSharpness  & oSharpness,
                                                  CATOrientation   * oOrientation = NULL,
                                                  CATShell         * iShellOwningTheTwoFaces = NULL,
                                                  CATBoolean         iComputeConvexity = TRUE,
                                                  CATBoolean         iForceGeometricEvaluation = FALSE,
                                                  CATBoolean       * oStoredSharpness = NULL,
                                                  CATAngle           iMinSharpAngle = CATTopSharpAngle); // en rad

  virtual CATBoolean           SetGlobalSharpness(CATTopData             & iTopData,
                                                  CATFace                * iFace1,
                                                  CATFace                * iFace2,
                                                  const CATGeoContinuity   iSharpness,
                                                  const CATGeoConvexity    iConcavity = CATUnknownConvexity,
                                                  CATShell               * iShellOwningTheTwoFaces = NULL,
                                                  CATAngle                 iMinSharpAngle = CATTopSharpAngle, // en rad
                                                  CATBoolean               iCheckBeforeSet = TRUE,
                                                  CATBoolean               iForceGeometricEvaluation = FALSE);

  virtual double               CalcLength(); 

  virtual const CATSurLimits * Get2DBoundingBox(CATFace* iBoundedFace);

  virtual void                 SetJunctionStatus(CATTopData &iTopData, CATTopJunctionEdgeStatus iFlag = CatTopJunction);

  virtual CATTopJunctionEdgeStatus GetJunctionStatus();

  virtual  HRESULT             GetBorderedFaces(CATBody *iBody, 
                                                CATLISTP(CATCell) & oFaces,
                                                CATListOfLong     & oNbOfFacesByDomain);

  //===========================================================================
  // Adhesion a l'interface CATVertex
  //===========================================================================
  virtual void                  SetPoint(CATPoint * iPoint);

  virtual CATPoint            * GetPoint();

  virtual void                  GetGeometryOnEdgeAndFace(CATEdge * iBoundedEdge,
                                                         CATFace * iBoundedFace,
                                                         CATPCurve*&  oPCurve,
                                                         CATCrvParam& oParam);

  virtual CATPointOnEdgeCurve * GetGeometryOnEdge(CATEdge * iBoundedEdge,
                                                  const CATSide& iSide);

  virtual void                  GetParamOnEdgeCurve(CATEdge *      iBoundedEdge,
                                                    CATEdgeCurve*& oEdgeCurve,
                                                    CATCrvParam&   ioParamOnEdgeCurve,
                                                    const CATSide& iSide);

  virtual void                  SetGeometryOnEdge(CATEdge *            iBoundedEdge,
                                                  const CATSide&       iSide,
                                                  CATPointOnEdgeCurve* iPtOnCrv);

#ifdef CATIACGMV5R17
  virtual CATVertexIterator   * CreateRadialIterator(CATBody *iInBody, const CATTopData * iData = 0);
#else
  //deprecated V5R17.
  virtual CATVertexIterator   * CreateRadialIterator(CATBody *iInBody);
#endif

  virtual void                  UnlinkUselessGeometry(CATPoint   *iSpecificPoint,
                                                      CATBoolean  iRemoveFromFactory);

  virtual void                  EvalSharpness(CATEdge              *iEdge1,
                                              CATEdge              *iEdge2,
                                              CATTopGeoContinuity  &oContinuity,
                                              CATAngle             *oAngle = NULL,
                                              CATTopSign           *oOrientation = NULL,
                                              CATBoolean           *oDefinedContinuity = NULL,
                                              CATAngle             iMinSharpAngle = CATTopSharpAngle);

  virtual void                  SetSharpness(CATEdge              *iEdge1,
                                             CATEdge              *iEdge2,
                                             CATTopGeoContinuity  iContinuity,
                                             CATAngle             iMinSharpAngle = CATTopSharpAngle);

  //===========================================================================
  // Adhesion a l'interface CATDomain
  //===========================================================================
  virtual short                   GetLowDimension();

  virtual short                   GetHighDimension();

  virtual CATLocation             GetLocation(CATTopology* iBodyOrCell);

  virtual void                    SetLocation(CATLocation iLocation);

  virtual CATCell               * GetOwningCell(CATBody *iInBody) const;

  virtual void                    AddCell(CATCell * iCellToAdd, CATOrientation iOrientation);

  virtual void                    RemoveCell(CATCell * iCellToDetach, CATBoolean iRemoveFromFactory);

  virtual CATLONG32                    GetNbCellUses();

  virtual CATCell               * GetCell(CATLONG32 iNumCell, CATOrientation * oOrientation);

  virtual CATLONG32                    GetCellRank(CATCell* iCell, CATOrientation * ioOrientation);

  virtual int                     Owns(CATCell* iCellToTest,CATSide* ioSide);

  virtual CATTopLyingOnDiagnostic IsLyingOn(CATDomain* iDomain);

  virtual void                    Invert();

  //===========================================================================
  // Adhesion a l'interface CATLump
  //===========================================================================
  // no method

  //===========================================================================
  // Adhesion a l'interface CATShell
  //===========================================================================
  virtual CATBoolean IsClosed();    

  virtual CATShell * SmartDuplication(CATBody* iBody,
                                      CATLISTP(CATCell)& iCellsToDuplicate,
                                      CATCGMJournalList* iJournal,
                                      CATBody* iShellBody);

  virtual CATShell * EmptySmartDuplication(CATBody* iBody);

  //===========================================================================
  // Adhesion a l'interface CATEdgeDomain
  //===========================================================================
  virtual void InsertEdge(CATEdge* iEdge,
                          CATULONG32  iPosition,
                          CATOrientation iOrientation);

  //===========================================================================
  // Adhesion a l'interface CATWire
  //===========================================================================
  virtual int         GetVertexRank(CATVertex* iVertex);

  virtual CATVertex * GetVertex(int iRank);

  virtual void        GetExtremities(CATVertex    **oStartVertex,
                                     CATVertex    **oEndVertex,
                                     CATMathVector *oStartTangent,
                                     CATMathVector *oEndTangent);
  // virtual CATBoolean  IsClosed();    

  virtual void        ChangeClosureVertex(CATVertex* iNewClosureVertex);

  virtual CATBoolean  CheckWireSelfIntersection(CATSurface * iSurface,
                                                CATBody *iBody);

  //===========================================================================
  // Adhesion a l'interface CATLoop
  //===========================================================================
  virtual void   Done();
  // virtual double CalcArea();

  //===========================================================================
  // Adhesion a l'interface CATVertexInFace
  //===========================================================================
  // no method

  //===========================================================================
  // Adhesion a l'interface CATVertexInVolume
  //===========================================================================
  // no method
  
  //===========================================================================
  // Constructor - Destructor
  //===========================================================================
  CATCGMExtTopology();
  virtual ~CATCGMExtTopology();
};

#endif
