#ifndef CATPGMTopoDebug_h_
#define CATPGMTopoDebug_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATCollec.h"
#include "CATDataType.h"
#include "CATBoolean.h"
#include "ListVOfLong.h"
#include "IUnknown.h"

class CATBody;
class CATCGMOutput;
class CATCXConnectedCells;
class CATCXTopology;
class CATCXVertexIter;
class CATCX_CHECKUP;
class CATCell;
class CATGeoFactory;
class CATTopology;
class CATLISTP(CATDomain);
class CATLISTP(CATConnectedCellsIterator);
class CATLISTP(CATFace);
class CATLISTP(CATTopology);
class CATLISTP(CATCell);

class ExportedByCATGMModelInterfaces CATPGMTopoDebug
{
public:
  static short IsAvailable();

  // keep only roots of Debug
  static CATBoolean IsTemporaryInactive();

  static CATBoolean SetTemporaryInactive(CATBoolean iInactivated);

  //---------------------------------------------------------------------------
  // Pour gestion des liens pose-Sur
  //---------------------------------------------------------------------------
  static void DumpLyingOn(
    CATGeoFactory *iFactory,
    CATCGMOutput &ios,
    int &ioNumberOfCellWithLyingOn,
    int &ioNbCellWithGOODLyingOn,
    int &ioNbCellWithBADLyingOn);

  static void DumpHiddenSubdOccurences(
    CATTopology *iTopology,
    CATCGMOutput &ios,
    int &ioNumberOfHiddenSubdOccurences);

  static void GetCellWithLyingOns(
    CATGeoFactory *iFactory,
    CATLISTP(CATCell) &ioCells);

  //---------------------------------------------------------------------------
  // Body / CellsHighestDimension avec isLocallyManifold
  //---------------------------------------------------------------------------
  static void isLocallyManifold(
    CATBody *iBody,
    const CATLONG32 iCellsMaxDim,
    const CATBoolean isHomogeneous,
    const CATBoolean isLocallyManifold,
    const CATLISTP(CATCell) &iFreeCell,
    const CATLISTP(CATCell) &iNonManifoldCell);

  //---------------------------------------------------------------------------
  // Controle validite des liens inverses de modelisation
  //---------------------------------------------------------------------------
  static void CheckActivation(CATCXTopology *iContext = NULL);

  static void CheckUpwardLinks(CATCXTopology *iTopo, CATCX_CHECKUP *iReport);

  static CATBoolean SetCoverageMode_CATCX_UPWARD(CATBoolean _iActive);

  //---------------------------------------------------------------------------
  // Gestion deportee du Debug CATCX_NCGM
  //---------------------------------------------------------------------------
  static void DebugVertexIter(CATCXVertexIter *iter);

  static void DebugIsSharingTopology(
    CATTopology *iFirst,
    CATTopology *iWith,
    CATBoolean result,
    CATLISTP(CATTopology) *ioSharingFederator);

  static void DebugHasInfiniteGeometry(CATBody *iBody, CATBoolean result);

  static void DebugFacePropagate(
    CATBody *iBody,
    CATLISTP(CATFace) *iInitialFaces,
    CATLISTP(CATFace) &result);

  static void DebugBodyCellNeighbours(
    CATBody *iBody,
    const CATLISTP(CATCell) *iCellList,
    const CATListOfLong *inputOrientations,
    const short iVersionGenericNaming,
    CATLISTP(CATCell) &result,
    CATListOfLong &oNbOfCellsByDomain);

  static void DebugBorderedFaces(
    CATBody *iBody,
    CATCell *iCell,
    CATLISTP(CATCell) &oFaces,
    CATListOfLong &oNbOfFacesByDomain,
    short iSoftwareLevel,
    HRESULT result);

  static void DebugCellNeighbours(
    CATCell *iCell,
    CATBody *inBody,
    CATLISTP(CATCell) &oCell,
    HRESULT result);

  static void DebugSelectEdgesFromFaces(
    CATBody *iBody,
    const CATLISTP(CATFace) &iFaceList,
    CATLISTP(CATCell) &result);

  static void DebugInternalVertices(
    CATBody *iBody,
    const CATLISTP(CATCell) &iFaces1,
    const CATLISTP(CATCell) &iFaces2,
    CATLISTP(CATCell) &iVertices);

  static void DebugCommonEdgesBefore(
    CATBody *iBody,
    const CATLISTP(CATCell) &iFaces1,
    const CATLISTP(CATCell) &iFaces2);

  static void DebugCommonEdges(
    CATBody *iBody,
    const CATLISTP(CATCell) &iFaces1,
    const CATLISTP(CATCell) &iFaces2,
    CATLISTP(CATCell) &ioResult,
    CATListOfLong &ioListOrientation,
    CATListOfLong &ioNbOfEdgesByDomain);

  static void DebugGroupCells(
    const CATLISTP(CATCell) &cellsInput,
    CATBody *body,
    CATLISTP(CATConnectedCellsIterator) &oCellsIterator);

  static void DebugGroupManyCells(
    const CATLISTP(CATCell) &cellsInput,
    CATBody *body,
    CATLISTP(CATConnectedCellsIterator) &oCellsIterator);

  static void DebugCommonCells(
    const CATLISTP(CATConnectedCellsIterator) &iList,
    CATLISTP(CATConnectedCellsIterator) &oList);

  static void DebugSelectBoundary(
    CATCXConnectedCells *iCtx,
    CATLISTP(CATConnectedCellsIterator) &oList);

  static void DebugCreateDomainsBefore(
    CATBody *iBody,
    const CATLISTP(CATCell) &iCells,
    const CATListOfInt &iOris);

  static void DebugCreateDomains(
    CATBody *iBody,
    const CATLISTP(CATCell) &iCells,
    const CATListOfInt &iOris,
    const CATLISTP(CATDomain) &Domains);

  //---------------------------------------------------------------------------
  // Obtention du niveau de versioning CGM lors de l'achevement de construction
  //---------------------------------------------------------------------------
  static short GetCompletedLevel(CATBody *iBody);

  //---------------------------------------------------------------------------
  // For Debug Only, obtention du contexte du dernier Body aggregeant 
  //---------------------------------------------------------------------------
  static CATBody *GetLastBodyContextForDebugOnly(CATTopology *iTopology);

};

#endif /* CATPGMTopoDebug_h_ */
