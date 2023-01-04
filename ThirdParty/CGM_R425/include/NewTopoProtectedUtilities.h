#ifndef NewTopoProtectedUtilities_h
#define NewTopoProtectedUtilities_h

/**
* Static utilities that can be called from other internal frameworks.
* Do not add a method here if it will not be used outside NewTopologicalObjects.
*/

#include "BOOPER.h"
#include "CATBoolean.h"
#include "CATDataType.h"
#include "CATCGMOperator.h"
#include "CATCGMJournal.h"
#include "CATTopologicalOperator.h"

#ifndef NULL
#define NULL 0
#endif

class CATBody;
class CATCell;
class CATVertex;
class CATShell;
class CATEdge;
class CATCGMJournalList;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATListPtrCATBody;
class CATAdaptiveHashTable;
class CATFace;
class CATListPtrCATTopology;
class CATListPtrCATFace;
class CATRawCollint;
class CATPointOnEdgeCurve;
class CATMathDirection;
class CATListPtrCATCell;
class CATTopology;
class CATICGMUnknown;
class CATListPtrCATEdge;
class CATCloneManager;
class CATCGMOutput;
class CATExtTopOperator;
class CATTopOperator;
class CATListValShort;
class CATListPtrCATCrvLimits;
class CATListPtrCATPCurve;
class CATLoop;
class CATListPtrCATDomain;
class CATTopObject;
class CATSurface;
class CATSurLimits;

class ExportedByBOOPER NewTopoProtectedUtilities
{
public:

  /** @nodoc @nocgmitf */
  static void HomeMadeDump(CATBody*iBody);

  /** @nodoc @nocgmitf */
  static void HomeMadeDump(CATCell*iCell);

  /** @nodoc @nocgmitf */
  static void EliminateCuttingRedondancies(CATEdge* iEdge,
    CATShell* iShell);

  /** @nodoc @nocgmitf */
  static void EliminateCuttingRedondancies(CATVertex* iVertex);

  /** @nodoc @nocgmitf */
  static void CreateOrdersFromCuttingBody(
    CATSoftwareConfiguration * iConfig,
    CATBody * iIntersectionInput1,
    CATBody * iIntersectionInput2,
    CATBody * iCuttingBody,
    CATCGMJournalList & ioJournalList,
    CATBoolean iModificationOrderIfPossible);

  /** @nodoc @nocgmitf */
  static void SimplifyNewerMonoBody(CATGeoFactory * iFactory,
    CATSoftwareConfiguration * iConfig,
    CATListPtrCATBody & iInputBodies,
    CATBody * ioActiveBody,
    CATCGMJournalList * ioOperationJournal);

  /** @nodoc @nocgmitf */
  static void CreateBodiesForError(CATListPtrCATBody & iInputBodies,
    CATGeoFactory * iFactory,
    CATSoftwareConfiguration * iConfig,
    CATListPtrCATBody & oAssociatedInputBodies,
    CATAdaptiveHashTable & iAllLocationCellsTable,
    CATListPtrCATBody & oLocationBodies,
    CATAdaptiveHashTable * iAllContextCellsTable,
    CATListPtrCATBody * oContextBodies);

  /** @nodoc @nocgmitf */
  static CATBody * CreatePointInsideFace(CATGeoFactory * iFactory,
    CATSoftwareConfiguration * iConfig,
    CATFace * iFace,
    CATVertex ** oVertex = NULL);

  /** @nodoc @nocgmitf */
  static CATBody * CreateBodyFromTopologies(CATGeoFactory * iFactory,
    CATSoftwareConfiguration * iConfig,
    CATListPtrCATTopology & iInput);

  /** @nodoc @nocgmitf */
  static CATBody * CreateBodyFromTopology(CATGeoFactory * iFactory,
    CATSoftwareConfiguration * iConfig,
    CATTopology * iInput);

  /** @nodoc @nocgmitf */
  static void RetrieveContainerFacesFromCuttingEdge(CATEdge * iEdge,
    CATListPtrCATFace & oListOfFaces,
    CATRawCollint & oListOfOriVsShell);

  /** @nodoc @nocgmitf */
  static void RetrieveContainersFromCuttingVertex(
    CATVertex * iVertex,
    CATListPtrCATCell & oListOfCells);

  /** @nodoc @nocgmitf */
  static void GetNormalToFaceOnPOEC(CATPointOnEdgeCurve * iPOEC,
    CATEdge             * iEdge,
    CATFace             * iFace,
    CATMathDirection    & oNormalToFace,
    int                 & oComputed);

  /** @nodoc @nocgmitf */
  static CATBody * MergedCurvesSimplification(CATBody * ipBody,
    CATListPtrCATCell & iEdges,
    CATCGMJournalList * ipJournal,
    CATSoftwareConfiguration * ipConfig);

  /** @nodoc @nocgmitf
  * Does the CATBody contain FULL cells?
  */
  static int IsBodyWithoutFull(CATTopology* iTopo);

  /** @nodoc @nocgmitf */
  static void MergeFullCellsIntoLinkedDomains(CATBody* iBody, 
    CATShell* iTopo,
    CATSoftwareConfiguration * iConfig,
    CATCGMJournalList* iJournal = NULL);

  /** @nodoc @nocgmitf
  * Service temporaire pour gestion throw ...
  * Nettoyage maison... de donnees booleennes intermediaires
  */
  static void CleanTemporaryBoolean(CATBody*iBody);

  /** @nodoc @nocgmitf
  * Service temporaire pour gestion throw ...
  * Nettoyage maison... de donnees booleennes intermediaires
  */
  static void CleanTemporaryBooleanWithoutActivate(CATBody*iBody);

  /** @nodoc @nocgmitf
  * Outils De TASS des TAGS : usage interdit sauf dans le contexte CVM ou debug
  * tass is done if iMaxTag = 0, or if geofactory maxtag is >= iMaxTag
  */
  static void TassTagsForCVM(CATGeoFactory* ipFactory, CATULONG32 iMaxTag = 0);

  /** @nodoc @nocgmitf
  * Retrieve all cells containing cuttings of iCell.
  */
  static void GetAllCellSupports(CATCell* iCell, CATListPtrCATCell& oListOfCells, int iOnlyDirect = 0);

  /** @nodoc @nocgmitf
  * Get intersection edges on a shell.
  */
  static void GetIntersectionEdgesOnShell(CATShell *iShell, CATListPtrCATEdge & oIEList);

  /** @nodoc @nocgmitf
  * Duplicate iInput and all topologies contained inside it.
  */
  static CATTopology * FullTopologyDuplication(CATGeoFactory * iFactory,
    CATSoftwareConfiguration * iConfig,
    CATTopology & iInput,
    CATCloneManager ** oCloneManager = NULL);

  /** @nodoc @nocgmitf
  * Returns FALSE if 2 cells of iResultBody have an invalid intersection, and they're not generated
  * by 2 input cells having an invalid intersection in one of the input bodies.
  */
  static CATBoolean CheckSelfIntersectionsNotInInputs(
    CATSoftwareConfiguration * iConfig,
    CATBody * iResultBody,
    CATCGMJournalList * iResultJournal,
    CATListPtrCATBody & iInputBodies,
    CATCGMOutput * oDump);

  /** @nodoc @nocgmitf */
  static void GetAllTouchedObjectsInFactory(
    CATGeoFactory * iFactory,
    CATAdaptiveHashTable & oTouchedObjects);

  /** @nodoc @nocgmitf */
  static CATCGMOperator::CATCheckDiagnostic CheckResidualTouchedInFactory(
    CATGeoFactory * iFactory,
    CATCGMOutput & os);

  /** @nodoc @nocgmitf */
  static void TransferWarning(CATExtTopOperator & iFrom, CATExtTopOperator & iTo);

  /** @nodoc @nocgmitf */
  static void TransferWarning(CATTopOperator & iFrom,    CATExtTopOperator & iTo);

  /** @nodoc @nocgmitf */
  static void TransferWarning(CATExtTopOperator & iFrom, CATTopOperator & iTo);

  /** @nodoc @nocgmitf */
  static void TransferWarning(CATTopOperator & iFrom,    CATTopOperator & iTo);

  /** @nodoc @nocgmitf */
  static CATBody * DuplicateOnlyBody(
    CATBody & iBodyToDuplicate,
    CATSoftwareConfiguration & iConfig,
    CATCGMJournalList * iJournal = NULL,
    CATCGMJournal::Type iCopyOrNoCopy = CATCGMJournal::Copy,
    CATBoolean iFullJournal = FALSE);

  /** @nodoc @nocgmitf
  * Returns TRUE if (and only if) all the following conditions are true:
  * - "iBodyWith2Faces" constains exactly 1 domain, the domain is a shell, the shell contains 2 faces
  * - the 2 faces have all their edges in common (-> the shell is closed)
  * - each face have only 1 domain (the external loop)
  * - at least one of the two faces have no gap between consecutive curves of its loop (gap smaller than factory resolution)
  * - the faces are geometrically coincident at a tolerance equal to "iTolerance"
  */
  static CATBoolean FacesHaveCommonBorderAndAreCoincident(
    CATGeoFactory * iFactory,
    CATSoftwareConfiguration * iConfig,
    CATBody * iBodyWith2Faces,
    double iTolerance);

  /** @nodoc @nocgmitf
  * Creation of upward links, if not already done.
  */
  static void ActivateBody(CATBody * iBody);

  /** @nodoc @nocgmitf */
  static double ComputeGapInActiveBody(CATCell & iCell);

  /** @nodoc @nocgmitf 
  * oOriPCurveVsLoop[I] = +1  -->  use oPCurveLimits[I]->GetHigh(...) for the "end" in the sense of the loop
  * oOriPCurveVsLoop[I] = -1  -->  use oPCurveLimits[I]->GetLow(...) for the "end" in the sense of the loop
  */
  static void DismantleLoop(
    CATSoftwareConfiguration & iConfig,
    CATLoop & iLoop,
    CATListPtrCATEdge & oEdges,
    CATListPtrCATPCurve & oPCurves,
    CATListPtrCATCrvLimits & oPCurveLimits,
    CATListValShort & oOriPCurveVsLoop);

  /** @nodoc @nocgmitf
  * U29@190417: Verify that the wires inside ipWiresBody are completly splitting ipSupportBody
  * by using the lying on links.
  * @param ipWiresBody
  *   Is the result of the a projection on ipSupportBody
  * @param ipSupportBody
  *
  */
  static CATBoolean VerifyWiresAreCompletelySplitting(CATBody * ipWiresBody,
                                                      CATBody * ipSupportBody);

  /** @nodoc @nocgmitf
  * U29@110717: 
  * Verify that the shells inside ipShellsBody are completly splitting ipSupportBody
  *  @param ipFactory
  *    The factory of the geometry.
  *  @param ipConfig
  *    The software configuration.
  *  @param ipShellsBody
  *    Surfacic splitting bodies.
  *  @param ipSupportBody
  *    Volumic body to split.
  */
  static CATBoolean VerifyShellsAreCompletelySplitting(CATGeoFactory * ipFactory,
                                                       CATSoftwareConfiguration * ipConfig,
                                                       CATBody * ipShellsBody,
                                                       CATBody * ipSupportBody);

  /** @nodoc @nocgmitf
  * U29@190417: Relimit a body by volume
  */
  static CATBody * RelimitByVolume(CATGeoFactory * iFactory,
                                   CATSoftwareConfiguration * iConfig,
                                   CATBody * iSolidBody,
                                   CATBody * iBodyToRelimit,
                                   CATCGMJournalList * iJournal = NULL);
  /** @nodoc @nocgmitf
  * U29@190417: Test if a body is volumuic.
  */
  static CATBoolean IsVolumic(CATBody * ipBody);
  
  /** @nodoc @nocgmitf
  * THM@170517: Relimit a body by another body
  */
  static CATBody* RelimitBody( CATGeoFactory* iFactory, 
                               CATTopData* iTopData, 
                               CATBody* iTrimmingBody, 
                               CATBody* iRelimitedBody, 
#ifdef InputHelpError
                               CATTopOperator * RelimOpe,
#endif
                               int iSideToKeep,
                               CATBoolean iNoSimplif);

  /** @nodoc @nocgmitf */
  static CATBody* CallCreateTopDomains(CATGeoFactory * ipFactory,
                                       CATTopData& iTopData,
                                       CATListPtrCATCell&   iCells,
                                       CATListOfInt&        iOrientations,
                                       CATListPtrCATDomain& oDomains,
                                       CATCGMJournalList * iopJournalToFill = 0,
                                       CATBody * ipBodyCreator = 0);

  /** @nodoc @nocgmitf 
  * U29@050617
  */
  static CATBoolean BodyMapping(CATBody* ipComputedBody, 
                                CATBody* ipExpectedBody,
                                double iTolerance,
                                CATCGMOutput& os,
                                CATBoolean iCheckCellRankOnDomain = FALSE);

  /** @nodoc @nocgmitf */
  static void RetrieveFirstLevelCellsNoVolumes(
    CATAdaptiveHashTable & oFirstLevelCells,
    CATTopObject & iTopObject);

  /** @nodoc @nocgmitf
  * Discretizes an UV box, using Resolution*1e-6 as delta.
  * Discretization is shifted by 1.e-7 to statistically improve the stability.
  * Each value (MinU, MinV, MaxU, MaxV) is treated separately.
  * If the discretization of a value implies violating the MaxLimits, then the original value is kept.
  */
  static void DiscretizeSurLimitsRespectingMaxLimits(
    CATSurface & iSurface,
    CATSurLimits & ioSurLimits,
    CATBoolean iUseLargeUVBox);

};

#endif
