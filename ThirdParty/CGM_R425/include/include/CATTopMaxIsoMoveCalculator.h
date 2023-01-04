// COPYRIGHT DASSAULT SYSTEMES 2020
//=============================================================================
//
// CATTopMaxIsoMoveCalculator: 
//  Functions made for the Internship ELY2, for BatchOperation.
//
//
//=============================================================================
//  March 2020  Creation                                                 DLR6
//=============================================================================

#ifndef CATTopMaxIsoMoveCalculator_H
#define CATTopMaxIsoMoveCalculator_H


#undef ONLY_DLR6_TRACES
// Activate this macro to silence the unwanted automatic traces
// of the ReflectLine operator
//#define ONLY_DLR6_TRACES


#undef MaxIsotopoMove_ActivateDebug_ON
// Activate this macro to declare debug methods
// and to dump detailed traces in the output
//#define MaxIsotopoMove_ActivateDebug_ON

#undef MaxIsotopoMove_ActivateDebug_NCGM_ON
// Activate this macro to keep (with name and color) intermediary bodies
// alive in the factory
//#define MaxIsotopoMove_ActivateDebug_NCGM_ON
//





class CATGeoFactory;
class CATTopData;
class CATCGMJournalList;

class CATFace;
class CATBody;
class CATCXLoop;
class CATSubdArrayCXVertexP;
class CATMoveSimulatorHelper;
class CATExtTopMaxIsoMoveCalculator;

#include "CATTopOperator.h"

#include "ListPOfCATBody.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATCell.h"
#include "ListPOfCATVertex.h"
#include "ListPOfCATEdge.h"

#include "CATMathDirection.h"
#include "CATMathDef.h"

#include "CATMathInline.h"


#include "ExportedByCATTopologicalObjects.h"

class ExportedByCATTopologicalObjects CATTopMaxIsoMoveCalculator : public CATTopOperator
{
public:
  CATCGMNewClassArrayDeclare;

private:
  CATMoveSimulatorHelper  * _pMoveHelper;

  ListPOfCATFace          * _pListOfMobileFaces;
  CATBody                 * _pInputBody;
  CATMathDirection          _displacementAxis;

  ListPOfCATFace          * _pInwardMobileFaces;
  ListPOfCATFace          * _pOutwardMobileFaces;
  ListPOfCATFace          * _pOtherMobileFaces;

  CATCGMJournalList       * _pRunJournal;
  CATTopData              * _pRunTopData;

  double                    _computedMaxDeplPos;
  double                    _computedMaxDeplNeg;

public:

  CATTopMaxIsoMoveCalculator(
    CATMoveSimulatorHelper  * ipMoveHelper, CATExtTopMaxIsoMoveCalculator   * ipThisExt,
    CATGeoFactory           * ipFactory, CATTopData                      * iTopData,
    const ListPOfCATFace     &iListOfMobileFaces, CATBody                          * ipInputBody,
    const CATMathDirection   &iDisplacementAxis);

  ~CATTopMaxIsoMoveCalculator();

  void GetMaxComputedDisplacements(
    double    * opMaxDeplPos, double    * opMaxDeplNeg);

  INLINE        CATMathDirection  GetDisplacementAxis() const;
  INLINE  const ListPOfCATFace*   GetMobileFaces()      const;
  INLINE        CATBody*          GetInputBody()        const;


  //////////////////////
  //
  // Methods for CGMReplay
  //
  //

  void                  RequireDefinitionOfInputAndOutputObjects();

  // Stream inputs of operator. Exact counterpart of CATLoadxxx function
  void                  WriteInput(CATCGMStream & Str);

  void                  Dump(CATCGMOutput& ioOutput);
  void                  DumpOutput(CATCGMOutput& ioOutput);

  //
  // Methods for CGMReplay
  //
  //////////////////////

private:
  short GetThisCGMLevel();

protected:
  int RunOperator();
  
  static ListPOfCATBody* CreateOneBodyForEachFace(
    CATGeoFactory* ipFactory, CATTopData* iTopData, const ListPOfCATFace &iListOfFaces);

  static ListPOfCATBody* CreateOneBodyForEachEdge(
    CATGeoFactory* ipFactory, CATTopData* iTopData, const ListPOfCATEdge &iListOfEdges);

  static ListPOfCATBody* CreateOneBodyForEachCell(
    CATGeoFactory* ipFactory, CATTopData* iTopData, const ListPOfCATCell &iListOfCells);

  static CATBody* CreateOneBodyForAllFaces(
    CATGeoFactory* ipFactory, CATTopData* ipTopData, const ListPOfCATFace &iListOfFaces);

  static CATBody* CreateOneBodyForAllCells(
    CATGeoFactory* ipFactory, CATTopData* ipTopData, const ListPOfCATCell &iListOfCells);

  CATBody* UnionizeBodies(
    ListPOfCATBody* ipListOfBodiesToAvoid);

  CATBody* GetCompleteIntersectionBody(
    CATBody          * ipBody_A, CATBody         * ipBody_B);

  ListPOfCATBody* IntersectBodiesList_OneToOne(
    const ListPOfCATBody     &iListBodies_A, const ListPOfCATBody     &iListBodies_B);

  void CategorizeOneFaceOutwardInward(
    CATFace         * ipFace,  const CATMathDirection& iExtrudeDirection);

  void CategorizeFace_throughNormal(
    CATFace         * ipFace,  const CATMathDirection& iExtrudeDirection);

  void CategorizeFace_throughReflectLine(
    CATFace         * ipFace,  const CATMathDirection& iExtrudeDirection);

  void SplitFace_ByReflectLine(
    CATFace         * ipFace, const CATMathDirection& iExtrudeDirection,
    CATBody        ** opBody_PositiveSide, CATBody     ** opBody_NegativeSide);

  void CategorizeFacesListOutwardInward(
    ListPOfCATFace  * ipListFaceMobile, const CATMathDirection& iExtrudeDirection);

  //static CATBody* CreateBodySurfWithoutFaceAndNeighbours(
  //  CATGeoFactory             * ipFactory,
  //  CATTopData                * ipTopData,
  //  CATBody                   * iBodyOriginal,
  //  CATFace                   * ipMobileFace);
  //
  //static ListPOfCATBody* CreateListBodiesSurfWithoutFaceAndNeighbours(
  //  CATGeoFactory             * ipFactory,
  //  CATTopData                * iTopData,
  //  CATBody                   * iBodyOriginal,
  //  const ListPOfCATFace&       iListOfMobileFaces);

  double GetMinDistBetweenBodiesList_2By2(
    const ListPOfCATBody   &iListBodies_A, const ListPOfCATBody   &iListBodies_B,
    int             * opIndexOfFaceForMinDist = NULL);


  //////////////////////
  //
  // Methods to compute max possible distance of move towards inside shell
  //

public:
  void SolveMaxPossibleDistanceTowardsInsideShell(
    const ListPOfCATFace    &iListMobileFaces, const ListPOfCATBody  &iListMobileFacesAsBodies,
    const CATMathDirection  &iDirTowardsInsideShell,
    double            &ioMaxPosibleDistance, CATFace       ** opLimitingFace = NULL);

private:
  void UpdateMaxPossibleDistanceTowardsInsideShell(
    CATFace         *  ipMobileFace, CATBody     * ipMobileFaceAsBody,
    const CATMathDirection  &iDirTowardsInsideShell,
    double            &ioMaxPossibleDistance, CATFace    ** opLimitingFace);


  CATBody* GetBodyOtherEdges(
    CATFace           * ipMobileFace, CATBody     * ipMobileFaceAsBody);

  void GetOrderedEdgeFaceList_ForAllLoops(
    CATFace           * ipMobileFace,
    ListPOfCATEdge   ** opOrderedEdges, ListPOfCATFace ** opOrderedNeighbourFaces);

  void GetOrderedEdgeFaceList_ForOneLoop(
    CATFace           * ipMobileFace,
    CATCXLoop         * ipLoopOfInputFace,
    ListPOfCATEdge   ** opOrderedEdges, ListPOfCATFace ** opOrderedNeighbourFaces);

  void GetOrderedVertexFaceList(
    CATFace           * ipMobileFace,
    CATCXLoop         * ipLoopOfInputFace,
    ListPOfCATCell   ** opOrderedOppVertices, ListPOfCATFace   ** opOrderedNeighbourFaces);


  double GetNeighbourDistance(
    CATFace           * ipMobileFace,
    const CATMathDirection& iDirTowardsOutsideShell);

  double GetNeighbourDistance_ForLoopOfMoreThan3Edges(
    CATFace           * ipMobileFace,
    CATCXLoop         * ipCurCXLoop, const CATMathDirection& iDirTowardsOutsideShell);

  double GetNeighbourDistance_ForLoopOf3Edges(
    CATFace           * ipMobileFace,
    CATCXLoop         * ipCurCXLoop, const CATMathDirection& iDirTowardsOutsideShell);



  double GetBodyExtremumMaxDistance(
    CATBody* ipMobileFaceAsBody, const CATMathDirection &iDirTowardsInsideShell);


  //
  // Methods to compute max possible distance of move towards inside shell
  //
  //////////////////////


  //////////////////////
  //
  // Methods to compute max possible distance of move towards outside shell
  //

public:
  void SolveMaxPossibleDistanceTowardsOutsideShell(
    const ListPOfCATFace    &iListMobileFaces, const ListPOfCATBody  &iListMobileFacesAsBodies,
    const CATMathDirection  &iDirTowardsOutsideShell,
    double            &ioMaxPosibleDistance, CATFace       ** opLimitingFace = NULL);

private:
  void UpdateMaxPossibleDistanceTowardsOutsideShell(
    CATFace          * ipMobileFace, CATBody     * ipMobileFaceAsBody,
    const CATMathDirection  &iDirTowardsOutsideShell,
    double            &ioMaxPosibleDistance, CATFace    ** opLimitingFace);


  //
  // Methods to compute max possible distance of move towards outside shell
  //
  //////////////////////


  /**
    * Creates and gets a surfacic body that contains all faces of the input body
    * except a specific face to exclude and its neighbour faces
    *
    * @param  ipInputBody  the input body to partially copy" (except some faces)
    *
    * @param  ipFace  the face to exclude from the input body
    **/
  CATBody* GetBodyDupl(
    CATFace     * ipFace);

  void GetOrderedListBodiesOpp(
    CATFace           * ipMobileFace,
    CATCXLoop         * ipLoopOfInputFace,
    ListPOfCATEdge   ** opListOrderedEdges, ListPOfCATBody ** opListOrderedOppositeBodies);


  CATBody* GetExtrudedBody(
    CATBody         * ipBodyToExtrude,  const CATMathDirection   &iExtrusionDirection);


  ListPOfCATBody* GetListExtrudedBody(
    const ListPOfCATBody     &iListBodiesToExtrude, const CATMathDirection   &iExtrusionDirection);


  double GetMaxPossibleDistance_ForHybIntersect(
    CATBody          * ipOtherBody,
    CATBody          * ipBodyToIntersect_A, CATBody     * ipBodyToIntersect_B);

  double GetMaxPossibleDistance_ForDynSolidBoolean(
    CATBody          * ipOtherBody,
    CATBody          * ipBodyToIntersect_A, CATBody     * ipBodyToIntersect_B);



  ListPOfCATCell* GetListOtherEdges(
    CATFace           * ipMobileFace, CATBody     * ipMobileFaceAsBody);


  //////////////////////
  //
  // New Auxiliairy methods (by DLR6, 04th June 2020)
  //
  //

  static CATSubdArrayCXVertexP* GetAllNonFullVerticesBoundingAFace(
    CATFace           * ipFace);

  //
  // New Auxiliairy methods (by DLR6, 04th June 2020)
  //
  //////////////////////

#ifdef MaxIsotopoMove_ActivateDebug_NCGM_ON
  //////////////////////
  //
  // Debug method
  //
  //

  static void NamingColorBody(
    CATBody* ipBody,
    int iRed, int iGreen, int iBlue,
    CATUnicodeString &iName, int iNum = -1);

  static void DumpCATCell(
    const CATCell * iCell,
    CATCGMOutput   &ioOutput);

  static CATUnicodeString GetCellString(const CATCell* ipCell);

  static CATUnicodeString createUnicodeStringDirection(const CATMathDirection& pD, int pNumber);

  //
  // Debug method
  //
  //////////////////////
#endif // MaxIsotopoMove_ActivateDebug_NCGM_ON

};

INLINE  CATMathDirection CATTopMaxIsoMoveCalculator::GetDisplacementAxis()   const
{
  return _displacementAxis;
}

INLINE  const ListPOfCATFace* CATTopMaxIsoMoveCalculator::GetMobileFaces()   const
{
  return _pListOfMobileFaces;
}

INLINE  CATBody* CATTopMaxIsoMoveCalculator::GetInputBody()   const
{
  return _pInputBody;
}


#ifdef MaxIsotopoMove_ActivateDebug_ON

  #define   MaxMove_DebugTrace(argStream)                     argStream

  #ifdef MaxIsotopoMove_ActivateDebug_NCGM_ON
    #define   MaxMove_WhenDebugNCGM_Do(argStream)             argStream
  #else // MaxIsotopoMove_ActivateDebug_NCGM_ON
    #define   MaxMove_WhenDebugNCGM_Do(argStream)
  #endif // MaxIsotopoMove_ActivateDebug_NCGM_ON

#else // MaxIsotopoMove_ActivateDebug_ON

  #define   MaxMove_DebugTrace(argStream)
  #define   MaxMove_WhenDebugNCGM_Do(argStream)

#endif // MaxIsotopoMove_ActivateDebug_ON


#endif //CATTopMaxIsoMoveCalculator_H
