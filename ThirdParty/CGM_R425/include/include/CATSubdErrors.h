/* Generated from CATSubdErrors.msg on Mon Apr 20 18:51:39 1998
 */
#ifndef _CATSUBDERRORS_INCLUDE
#define _CATSUBDERRORS_INCLUDE

#include "CATError.h"
#include "ExportedByCATTopologicalObjects.h"

class CATTopOpInError;
class CATGeoFactory;
class CATSubdImportGraphIntError;
class CATSubdPropagatePositionIntError;
class CATSubdInternalError;


// COPYRIGHT DASSAULT SYSTEMES 1999

typedef enum {

     SubdIntCopyOrEqualOpIllegal = 0x00020001u,
 SubdIntVirtualMethodCallIllegal = 0x00020002u,
          SubdIntInvalidPosition = 0x00020003u,
            SubdIntInvalidStatus = 0x00020004u,
 SubdIntInvalidLocationOnSupport = 0x00020005u,
           SubdIntInvalidBoolean = 0x00020006u,
          SubdIntInvalidLocation = 0x00020007u,
              SubdIntInvalidSign = 0x00020008u,
      SubdIntOccurenceNotInClass = 0x00020009u,
    SubdIntOccurenceWithoutClass = 0x0002000au,
  SubdIntOccurenceNotInContainer = 0x0002000bu,
               SubdIntLinkBroken = 0x0002000cu,
                    SubdIntAbort = 0x0002000du,
                SubdIntEmptyLoop = 0x0002000eu,
                  SubdIntEmptyIS = 0x0002000fu,
      SubdIntUndetectedConfusion = 0x00020010u,
                     SubdIntToDo = 0x00020011u,

     SubdInterTopoInterGeomError = 0x00020001u,
       SubdInterTopoRelimitError = 0x00020002u,
            SubdInterTopoUnknown = 0x00020003u,

          SubdCompSubdivideError = 0x00020001u,
         SubdCompDisconnectError = 0x00020002u,
          SubdCompInterTopoError = 0x00020003u,
                 SubdCompUnknown = 0x00020004u,

      SubdSubdivideSeparateError = 0x00020001u,
      SubdSubdividePositionError = 0x00020002u,
            SubdSubdivideUnknown = 0x00020003u,

         SubdSelectPositionError = 0x00020001u,
               SubdSelectUnknown = 0x00020002u,

        SubdRelimitSeparateError = 0x00020001u,
          SubdRelimitSelectError = 0x00020002u,
              SubdRelimitUnknown = 0x00020003u,
            SubdRelimitLoopError = 0x00020004u,
           SubdRelimitShellError = 0x00020005u,

SubdSeparateCreateCompositeError = 0x00020001u,
      SubdSeparateDuplicateError = 0x00020002u,
             SubdSeparateUnknown = 0x00020003u,

             SubdPositionUnknown = 0x00020001u,

            SubdInterGeomUnknown = 0x00020001u,

   SubdDisconnectDisconnectError = 0x00020001u,
      SubdDisconnectCuttingError = 0x00020002u,
       SubdDisconnectReportError = 0x00020003u,
  SubdDisconnectClassIncoherence = 0x00020004u,
   SubdDisconnectNbDisconnectors = 0x00020005u,
           SubdDisconnectUnknown = 0x00020006u,

    SubdCuttingSpacesIncoherence = 0x00020001u,
      SubdCuttingFutureConfError = 0x00020002u,
      SubdCuttingDisconnectError = 0x00020003u,
     SubdCuttingImportGraphError = 0x00020004u,
   SubdCuttingImport3DGraphError = 0x00020005u,
         SubdCuttingFlattenError = 0x00020006u,
              SubdCuttingUnknown = 0x00020007u,

       SubdReportProjectionError = 0x00020001u,
     SubdReportConfusedFaceError = 0x00020002u,
     SubdReportConfusedLoopError = 0x00020003u,
               SubdReportUnknown = 0x00020004u,

           SubdProjectXYZUnknown = 0x00020001u,

     SubdRedondancy2x1InterError = 0x00020001u,
      SubdRedondancy2x1ConfError = 0x00020002u,
        SubdRedondancy2x1Unknown = 0x00020003u,

   SubdIntersectionRed2x1Unknown = 0x00020001u,

      SubdConfusionRed2x1Unknown = 0x00020001u,

        SubdRedondancy2x2Unknown = 0x00020001u,

            SubdPropagateUnknown = 0x00020001u,

   CXLoopInterTopoInterTopoError = 0x00020001u,
        CXLoopInterTopoR2x1Error = 0x00020002u,
        CXLoopInterTopoR2x2Error = 0x00020003u,
  CXLoopInterTopoRedondancyError = 0x00020004u,
          CXLoopInterTopoUnknown = 0x00020005u,

         SubdRedondancyR2x1Error = 0x00020001u,
         SubdRedondancyR2x2Error = 0x00020002u,
           SubdRedondancyUnknown = 0x00020003u,

SubdCalculatePositionInterTopoError = 0x00020001u,
  SubdCalculatePositionNotClosed = 0x00020002u,
    SubdCalculatePositionUnknown = 0x00020003u,

SubdCalculateOrientationInterTopoError = 0x00020001u,
SubdCalculateOrientationNotClosed = 0x00020002u,
SubdCalculateOrientationPointChoiceError = 0x00020003u,
SubdCalculateOrientationSegmentChoiceError = 0x00020004u,
 SubdCalculateOrientationUnknown = 0x00020005u,

        SubdImportGraphLoopError = 0x00020001u,
 SubdImportGraphImportGraphError = 0x00020002u,
    SubdImportGraphUntreatedEdge = 0x00020003u,
          SubdImportGraphImpasse = 0x00020004u,
          SubdImportGraphUnknown = 0x00020005u,

            SubdGraphCBSCreation = 0x00020001u,
    SubdGraphCreateContoursError = 0x00020002u,
 SubdGraphBuildContoursTreeError = 0x00020003u,
  SubdGraphCreateGraphFacesError = 0x00020004u,
       SubdGraphExportFacesError = 0x00020005u,
           SubdGraphDestroyError = 0x00020006u,
            SubdGraphMissingLink = 0x00020007u,
                SubdGraphUnknown = 0x00020008u,

               SubdPathNotClosed = 0x00020001u,
             SubdPathInvertError = 0x00020002u,
    SubdPathBuildAndReorderError = 0x00020003u,
             SubdPathAddBarError = 0x00020004u,
  SubdPathAnalyseClosedPathError = 0x00020005u,
  SubdPathExtractClosedPathError = 0x00020006u,
SubdPathExtractLastInternalBarsError = 0x00020007u,
       SubdPathBuildReverseError = 0x00020008u,
             SubdPathConcatError = 0x00020009u,
  SubdPathCalculatePositionError = 0x0002000au,
          SubdPathBuildLoopError = 0x0002000bu,
         SubdPathExportLoopError = 0x0002000cu,
                   SubdPathEmpty = 0x0002000du,
                 SubdPathUnknown = 0x0002000eu,

                SubdBarNoNextBar = 0x00020001u,
                    SubdBarEmpty = 0x00020002u,
   SubdBarPropagatePositionError = 0x00020003u,
SubdBarEvaluateGeometricalStartError = 0x00020004u,
SubdBarEvaluateGeometricalEndError = 0x00020005u,
SubdBarEvaluateGeometricalMiddleError = 0x00020006u,
           SubdBarBuildFromError = 0x00020007u,

SubdConnectorPropagatePositionError = 0x00020001u,
  SubdConnectorPropagateCbsError = 0x00020002u,
      SubdConnectorSimplifyError = 0x00020003u,

    SubdCBSBuildClosedPathsError = 0x00020001u,
 SubdCBSInitializePositionsError = 0x00020002u,
  SubdCBSPropagatePositionsError = 0x00020003u,
         SubdCBSInvalidMaxNumber = 0x00020004u,
   SubdCBSBuildContoursTreeError = 0x00020005u,
      SubdCBSCreateContoursError = 0x00020006u,
               SubdCBSNoStartBar = 0x00020007u,
         SubdCBSGetStartBarError = 0x00020008u,
        SubdCBSBarNotPositionned = 0x00020009u,
  SubdCBSSelectInternalBarsError = 0x0002000au,
            SubdCBSNoInternalBar = 0x0002000bu,

         SubdContourStorageError = 0x00020001u,
        SubdContourSimplifyError = 0x00020002u,
 SubdContourInclusionIncoherence = 0x00020003u,
SubdContourCreateGraphFacesError = 0x00020004u,

    SubdGraphFaceExportFaceError = 0x00020001u,

  SubdPropagatePositionLoopError = 0x00020001u,
 SubdPropagatePositionShellError = 0x00020002u,
SubdPropagatePositionEdgeCurveError = 0x00020003u,
SubdPropagatePositionBoundingFaceError = 0x00020004u,
   SubdPropagatePositionCLEError = 0x00020005u,
SubdPropagatePositionIncompatible = 0x00020006u,
  SubdPropagatePositionNotClosed = 0x00020007u,
    SubdPropagatePositionVsWires = 0x00020008u,

        SubdFSECInvertedOperands = 0x00020001u,

     SubdVolSkinInvertedOperands = 0x00020001u,

         SubdCheckInterTopoError = 0x00020001u,
        SubdCheckLoopOrientation = 0x00020002u,
              SubdCheckNotClosed = 0x00020003u,
   SubdCheckWrongLoopOrientation = 0x00020004u,
      SubdCheckWrongLoopPosition = 0x00020005u,
       SubdCheckShellOrientation = 0x00020006u,
  SubdCheckWrongShellOrientation = 0x00020007u,
     SubdCheckWrongShellPosition = 0x00020008u,
SubdCheckFaceOrientationIncoherence = 0x00020009u,
                SubdCheckUnknown = 0x0002000au,

  CXShellInterTopoInterTopoError = 0x00020001u,
    CXShellInterTopoMissingError = 0x00020002u,
         CXShellInterTopoUnknown = 0x00020003u,

        SubdReportMissingUnknown = 0x00020001u,

         Subd3DGraphC3BSCreation = 0x00020001u,
Subd3DGraphCreate3DContoursError = 0x00020002u,
Subd3DGraphBuild3DContoursTreeError = 0x00020003u,
Subd3DGraphCreate3DGraphVolumesError = 0x00020004u,
   Subd3DGraphExportVolumesError = 0x00020005u,
         Subd3DGraphDestroyError = 0x00020006u,
Subd3DGraphExternalBoundaryNotConnected = 0x00020007u,
              Subd3DGraphUnknown = 0x00020008u,

                  Subd3DBarEmpty = 0x00020001u,
 Subd3DBarPropagatePositionError = 0x00020002u,
     Subd3DBarPropagateC3bsError = 0x00020003u,
Subd3DBarEvaluateGeometricalMiddleError = 0x00020004u,

   Subd3DConnectorBuildFromError = 0x00020001u,
Subd3DConnectorFindNextScarEdgeError = 0x00020002u,
Subd3DConnectorPropagatePositionError = 0x00020003u,
Subd3DConnectorPropagateC3bsError = 0x00020004u,
Subd3DConnectorEvaluateGeometricalMiddleError = 0x00020005u,
            Subd3DConnectorEmpty = 0x00020006u,

Subd3DGraphVolumeExportVolumeError = 0x00020001u,

       Subd3DContourStorageError = 0x00020001u,
Subd3DContourInclusionIncoherence = 0x00020002u,
Subd3DContourCreate3DGraphVolumesError = 0x00020003u,

          SubdC3BSBuildC3bsError = 0x00020001u,
 SubdC3BSPropagatePositionsError = 0x00020002u,
        SubdC3BSInvalidMaxNumber = 0x00020003u,
SubdC3BSBuild3DContoursTreeError = 0x00020004u,
   SubdC3BSCreate3DContoursError = 0x00020005u,
       SubdC3BSBarNotPositionned = 0x00020006u,
 SubdC3BSSelectInternalBarsError = 0x00020007u,
           SubdC3BSNoInternalBar = 0x00020008u,

SubdImport3DGraphIntersectionSkinError = 0x00020001u,
        SubdImport3DGraphUnknown = 0x00020002u,
SubdImport3DGraphImport3DGraphError = 0x00020003u,

             Subd3DPathNotClosed = 0x00020001u,
           Subd3DPathInvertError = 0x00020002u,
  Subd3DPathBuildAndReorderError = 0x00020003u,
         Subd3DPathAdd3DBarError = 0x00020004u,
Subd3DPathAnalyseClosed3DPathError = 0x00020005u,
Subd3DPathExtractClosed3DPathError = 0x00020006u,
Subd3DPathExtractLastInternal3DBarsError = 0x00020007u,
     Subd3DPathBuildReverseError = 0x00020008u,
           Subd3DPathConcatError = 0x00020009u,
Subd3DPathCalculatePositionError = 0x0002000au,
   Subd3DPathBuildCompositeError = 0x0002000bu,
      Subd3DPathExportShellError = 0x0002000cu,
                 Subd3DPathEmpty = 0x0002000du,
               Subd3DPathUnknown = 0x0002000eu

} TopologicalSubdIntErrors;

class ExportedByCATTopologicalObjects CATSubdErrors
{
   public:

      static CATTopOpInError * CreateVisuError(CATGeoFactory * iFactory,
                                               const char    * iNewErrorId,
                                               CATSubdImportGraphIntError * iFromSubdError);

      static CATTopOpInError * CreateVisuError(const char    * iNewErrorId,
                                               CATSubdPropagatePositionIntError * iFromSubdError);

      // partial Subd error dedicated filter for sweep. (returns NULL if error not filtered).
      // old error to be flushed by calling software                                           NLD191012
      static CATTopOpInError * CreateVisuErrorWithPartialSweepFilter(CATGeoFactory        * iFactory  ,
                                                                     CATSubdInternalError * iSubdError);
};

#endif
