#ifndef CATTopOpIntError_h
#define CATTopOpIntError_h
//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 1997
//
// DESCRIPTION : CATTopOpIntError class declaration
//               
//=============================================================================
#include "CATErrors.h"
#include "CATGMModelInterfaces.h"
#include "CATCGMInternalError.h"

#include "CATIAV5Level.h" // to suppress

#ifndef TopOpIntFile
#define TopOpIntFile "CATTopologicalOperators"
#endif

#ifndef CATSurfacicTopoOperatorsFile
#define CATSurfacicTopoOperatorsFile "CATSurfacicTopoOperators"
#endif

enum {
      TopOpIntDisconnect,
	  TopOpIntDisconnectOpenLoop,
      TopOpIntDisconnectTooManyEdges,
	  TopOpIntDisconnectLeftRecursion,
	  TopOpIntDisconnectRightRecursion,
	  TopOpIntDisconnectRecursion,
	  TopOpIntDisconnectFirstBodyError,
	  TopOpIntDisconnectSecondBodyError,
	  TopOpIntDisconnectFirstCellMissing,
	  TopOpIntDisconnectNextCellMissing,
	  TopOpIntDisconnectEdgeCurveMissing,
	  TopOpIntDisconnectVertexGeometryMissing,
	  TopOpIntDisconnectDataStructureMissing,
      TopOpIntShell,
	  TopOpIntNotImplemented,
	  TopOpIntBadTopology,
	  TopOpIntBadGeometry,
	  TopOpIntMath,
	  TopOpIntAllTopo,
	  TopOpIntAllGeo,
	  TopOpIntShellSurfaceExtrapolation,
	  TopOpIntShellCurveExtrapolation,
	  TopOpIntShellCurrentVersion,
	  TopOpIntRibbonInternalError,
	  TopOpIntTwistedRibbon,
	  TopOpIntInterruptedRibbon,
	  TopOpIntRibbonRelimitation,
	  TopOpIntRibbonLocalReorder,
	  TopOpIntRibbonInitialization,
	  TopOpIntRibbonBadNumberOfFaces,
	  TopOpIntRibbonBadNumberOfEdges,
	  TopOpIntRibbonBadNumberOfRadii,
	  TopOpIntRibbonNoExtrapolation,
	  TopOpIntRibbonNoGeometry,
	  TopOpIntRibbonTooManySolution,
	  TopOpIntDraftInternalError,
	  TopOpIntTwistedDraft,
	  TopOpIntInterruptedDraft,
	  TopOpIntDraftRelimitation,
	  TopOpIntDraftInitialization,
	  TopOpIntSweepInternalError,
    TopOpIntShellSelfIntersectingGraphForDisco2D,
		TopOpIntExtrudeEmptyWire,
		TopOpIntCloseInternalError,
		TopOpIntAllocation,
		TopOpIntLoftSectionHomogenization,
		TopOpIntLoftGuideHomogenization,
		TopOpIntCornerRelimitation,
		TopOpIntCornerTooManySolutions,
    TopOpIntStylingFilletTriangularBreak,
		TopOpIntShellSideFace,
		TopOpIntInvalidInput,
		TopOpIntInvalidType,
		TopOpIntEmptyResult,
		TopOpIntRibbonOrder
};


class  ExportedByCATGMModelInterfaces CATTopOpIntError : public CATCGMInternalError
{
  public:

    CATDeclareError(CATTopOpIntError, CATCGMInternalError)

   	/** @nodoc */
   CATCGMNewClassArrayDeclare;
};




//

#endif
