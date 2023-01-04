// COPYRIGHT DASSAULT SYSTEMES 2018
//=============================================================================
//
// CATDisco3DDebug: 
//  Usefull services to debug a the Disco3D operator
//  
//
//
//=============================================================================
//
// Usage notes: 
// Activate the define  CATDisco3DDebug_ON.
//
//  Examples of usuage 
//   CATSubdOccurence.cpp
//   CATDisco3DCompatibleOp
//
//
//
//=============================================================================
//  April 2018  Creation                                                 DLR6
//=============================================================================

#ifndef CATDisco3DDebug_H
#define CATDisco3DDebug_H


#undef CATDisco3DDebug_ON

// Activate this define to use CATDisco3DDebug
// #define CATDisco3DDebug_ON
//

#undef PreciseEdge_DumpFace
#define PreciseEdge_DumpFace

#undef PreciseEdge_DumpVertices
#define PreciseEdge_DumpVertices


#ifdef CATDisco3DDebug_ON

#include "CATDisco3DDefine.h"

#include "CATCGMOutput.h"
#include "CATBoolean.h"
#include "CATUnicodeString.h"

class CATGeoFactory;
class CATSoftwareConfiguration;
class CATTopData;
class CATCGMJournal;
class CATListPtrCATCGMJournal;

class CATCXTopology;
class CATTopology;
class CATCXBody;
class CATBody;
class CATCell;
class CATCXShell;

class CATSubdOccurence;
class CATSubdMultiVolume;
class CATSubdVolume;
class CATSubdEdge;
class CATSubdConfusedLoop;

class CATDisconnectEngine;
class CATSubdIntersectionSkin;
class CATDisco3DSkin;
class CATDisconnectCell;

class CATListPtrCATICGMObject;
class CATSubdArrayOccurenceP;
class CATSubdArrayMultiVolumeP;
class CATSubdArrayIntersectionVertexP;
class CATSubdArrayVolumeP;
class CATSubdArrayCXShellP;
class CATSubdArrayDisco3DSkinP;
class CATSubdArrayIntersectionSkinP;
class CATSubdArrayEdgeCurveP;
class CATSubdArrayEdgeP;

class CATTopToolsCreateDomains;
class CATTopCompatibleCGM;

#include "CATSubdPosition.h"
#include "ListPOfCATBody.h"
#include "CATListOfCATCells.h"

#include "ExportedByCATTopologicalObjects.h"

class ExportedByCATTopologicalObjects CATDisco3DDebug
{

public:

  //**********************************
  //   CreateDomainFromFaces
  //**********************************

  static CATTopToolsCreateDomains* CreateDebugDomainFromFaces(
                                        CATGeoFactory               * iFactory,
                                  const CATTopData                  * iTopData,
                                        CATLONG32                     iNbFaces,
                                        void                       ** iTabFaces,
                                        int                         * iTabOriFaces);


  //**********************************
  //   Dump Methods
  //**********************************
  
  static void DumpSubdPosition(
                        const CATSubdPosition              &iPos,
                              CATCGMOutput                 &ioOutput);
  
  static void DumpCATCell(
                        const CATCell                     * iCell,
                              CATCGMOutput                 &ioOutput);
  static void DumpCATTopo(
                        const CATTopology                 * iTopo,
                              CATCGMOutput                 &ioOutput);
  static void DumpCATCellList(
                        const ListPOfCATCell               &iListOfCells,
                              CATCGMOutput                 &ioOutput);
  
  static CATUnicodeString GetTopoString_SAFE(
                        const CATTopology                 * ipTopo);

  static CATUnicodeString GetPreciseOccurenceString_SAFE(
                              CATSubdOccurence            * ipOcc);

  static void DumpPreciseSubdEdge_SAFE(
                              CATSubdEdge                 * ipSubdEdge,
                              CATCGMOutput                 &ioOutput = cgmout);
  static void DumpArrayPreciseSubdEdge_SAFE(
                        const CATSubdArrayEdgeP           * ipArrayEdges,
                              CATCGMOutput                 &ioOutput = cgmout);
  static void DumpPreciseOccurence_SAFE(
                              CATSubdOccurence            * ipOcc,
                              CATCGMOutput                 &ioOutput = cgmout);
  static void DumpArrayOccurences_SAFE(
                        const CATSubdArrayOccurenceP      * ipArrayOccs,
                              CATCGMOutput                 &ioOutput = cgmout);
  static void DumpArrayEdgeCurves_SAFE(
                        const CATSubdArrayEdgeCurveP      * ipArrayOccs,
                              CATCGMOutput                  &ioOutput = cgmout);

  static void DumpCompositionOfCXShell(
                              CATCXShell                  * ipCXShell,
                              CATCGMOutput                 &ioOutput);
  static void DumpFaceCompositionOfCXShell(
                              CATCXShell                  * ipCXShell,
                              CATCGMOutput                 &ioOutput);
  static void DumpCompositionOfVol(
                              CATSubdVolume               * ipSubdVol,
                              CATCGMOutput                 &ioOutput);
  static void DumpCompositionOfMultivol(
                              CATSubdMultiVolume          * ipMultivol,
                              CATCGMOutput                 &ioOutput);
  static void DumpCompositionOfMultivolList(
                              CATSubdArrayOccurenceP      * iListResultMultivol,
                              CATCGMOutput                 &ioOutput);
  static void DumpCompositionOfResultsByOperand(
                              CATSubdArrayOccurenceP      * iListResultThis,
                              CATSubdArrayOccurenceP      * iListResultOp,
                              CATCGMOutput                 &ioOutput);

  static void DumpDiscoEngineDomains(
                        const CATDisconnectEngine         * ipDiscoEngine);

  static void DumpBdryISDetails(
                              CATSubdIntersectionSkin     * ipIS);
  static void DumpBdrySkinsArrayDetails(
                        const CATSubdArrayDisco3DSkinP     &iBdrySkins);

  static void DumpGenericOccurenceForDebug(
                              CATSubdOccurence            * ipOcc,
                              CATCGMOutput                 &ioOutput);
  static void DumpSpecificOccurenceForDebug(
                              CATSubdOccurence            * ipOcc,
                              CATCGMOutput                 &ioOutput);

  static void DumpJournal_Tass(
                        const CATUnicodeString             &iTexte,
                              CATCGMJournal               * ipJournal,
                              int                           iIndent,
                              CATCGMOutput                 &ioOutput);
  static void DumpJournal_Tass(
                        const CATUnicodeString             &iText,
                              CATListPtrCATCGMJournal     * ipJournals,
                              int                           iIndent,
                              CATCGMOutput                 &ioOutput);


  //**********************************
  //   NCGM Export of each topo of a multivolume (independantly) methods
  //**********************************
  
  static CATUnicodeString GetPathToExportFolder();
  static CATUnicodeString GetDefaultFileName(
                      CATUnicodeString              iDebugOpString          = CATUnicodeString(),
                      CATBoolean                    useNbDebugExportAndIncr = FALSE,
                      CATBoolean                    includeExtensionInName  = TRUE);
  static CATUnicodeString GetDefaultCompleteFileName(
                      CATUnicodeString              iPathToResultFolder,
                      CATUnicodeString              iDebugOpString          = CATUnicodeString(),
                      CATBoolean                    useNbDebugExportAndIncr = FALSE,
                      CATBoolean                    includeExtensionInName  = TRUE);

  static CATBody* CreateNewInactiveBodyFromCells(
                const ListPOfCATCell&               iCellList);

  static CATBody* CreateNewInactiveBodyFromOneCell(
                      CATCell                     * iCell);

  static void CreateAndAppendNewInactiveBodyForEachCell(
                const ListPOfCATCell&               iCellList,
                      ListPOfCATBody&               ioBodies);

  static CATBody* CreateNewInactiveBodyFromConfusedLoop(
                const CATSubdConfusedLoop         * ipLoop);

  static CATListPtrCATICGMObject* CreateOneBodyForEachTag(
                      CATGeoFactory               * ipFactory,
                const CATLONG32                     iNbObject,
                const CATULONG32                    iTags[]);

  static void AppendOneBodyForEachTag(
                      CATListPtrCATICGMObject&      ioListBodiesAsObjs,
                      CATGeoFactory               * ipFactory,
                const CATLONG32                     iNbObject,
                const CATULONG32                    iTags[]);

  static CATBody* ConvertOccToBody(
                      CATSubdOccurence            * ipOcc);

  static CATBody* ConvertOccsToOneBody(
                const CATSubdArrayOccurenceP      * ipArrayOccs);

  static CATBody* ConvertVerticesToOneBody(
                const CATSubdArrayIntersectionVertexP   * ipArrayIVs);

  static void ExportNCGM_OccurencesInSeparateBodies(
                      CATListPtrCATICGMObject     * ipOtherDebugBodies,
                      CATSubdArrayOccurenceP      * ipArrayOccsToExport);

  static void ExportNCGMTopo(
                      CATCXTopology               * ipCXTopo,
                      CATUnicodeString              topoExportFilename);
  static void ExportNCGMTopoOfMultivol(
                      CATSubdMultiVolume          * ipMultivol,
                      CATUnicodeString              prefixStringForMV);
  static void ExportNCGMTopoOfMultivolList(
                      CATSubdArrayOccurenceP      * iListResultMultivol,
                      CATUnicodeString              prefixStringForMVList);
  static void ExportNCGMTopoOfResultsByOperand(
                      CATSubdArrayOccurenceP      * iListResultThis,
                      CATSubdArrayOccurenceP      * iListResultOp);

  static void ExportNCGMExistingCellsAndSkins(
                      CATDisconnectEngine         * ipDiscoEngine,
                const CATSubdArrayDisco3DSkinP     &iSkinsArray,
                      CATGeoFactory               * ipFactory,
                      CATSoftwareConfiguration    * ipConfig);

  static void ExportNCGMObjsTags(
                      CATGeoFactory               * ipFactory,
                const CATLONG32                     iNbObject,
                const CATULONG32                    iTags[]);

  static void AppendOneBodyForEachTag_AndExport(
                      CATListPtrCATICGMObject&      ioListBodiesAsObjs,
                      CATGeoFactory               * ipFactory,
                const CATLONG32                     iNbObject,
                const CATULONG32                    iTags[]);

private:
  static CATBody* CreateDebugBodyFromDiscoCell(
                      CATDisconnectEngine         * ipDiscoEngine,
                      CATDisconnectCell           * ipDiscoCell,
                      CATGeoFactory               * ipFactory,
                      CATSoftwareConfiguration    * ipConfig);

  struct Dbg_RGBColor
  {
    int _RedValue     = 0;
    int _GreenValue   = 0;
    int _BlueValue    = 0;

    Dbg_RGBColor(int r, int g, int b)
    {
      _RedValue     = r;
      _GreenValue   = g;
      _BlueValue    = b;
    }
  };

public:

  //**********************************
  //   Strings representing paths to folders for debug files
  //**********************************

  static CATUnicodeString PathToExportFolder;


  //**********************************
  //   Sets for NCGM exports and CGMReplay recordings
  //**********************************

  static const CATBoolean ExportSkinsOfNonDisconnectableShells;
  static const CATBoolean ExportSkinsOfDisconnectedMVs;
  static const CATBoolean ExportSkinsOfMultiVolInputs;
  static const CATBoolean ExportAllDiscoSkinsOfCaller;
  static const CATBoolean ExportEngineCellsAndSkins;
  static const CATBoolean ExportSkinsToClassify;
  static const CATBoolean ExportTopologiesByTags;

  static const CATBoolean MultiCompatible_CallForEachList;
  static const CATBoolean MultiCompatible_CleanCallForEachResult;
  static const CATBoolean AddManualCompatibleCallInMultiCompatible;
  static const CATBoolean AddManualCompatibleCallInCutBodies;

  static const CATBoolean CountCallbacks;

  static CATBoolean IsEnvVarActivated(const char* iVariable);

  //**********************************
  //   NCGM Export Methods of Debug bodies
  //**********************************
  
  static CATListPtrCATICGMObject OriginShellsOfInputSkins_AsBodies;
  static CATListPtrCATICGMObject RegisteredBodiesToExport;
  static int DEBUG_nbDebugExport;

  
  static void AppendDebugBody(
                      CATBody                     * ipDebugBody,
                      CATUnicodeString              iNameDebugBodyInNCGM);
  static void ExportBodiesToNCGM(
                      CATUnicodeString strSuffixFilename = CATUnicodeString());
  static void ClearDebugBodiesLists();


  //**********************************
  //   NCGM Export of IS
  //**********************************
  
  static void ExportSkinsToNCGM(
                const CATSubdArrayDisco3DSkinP       &iSkinsArray,
                      CATGeoFactory                 * ipFactory,
                      CATSoftwareConfiguration      * ipConfig,
                      CATBoolean                      useTopToolsCreateDomains = FALSE);
  static void AddSkinBodiesAndExportToNCGM(
                      CATListPtrCATICGMObject        &ioListBodiesToExport,
                const CATSubdArrayIntersectionSkinP  &iSkinsArray,
                      CATGeoFactory                 * ipFactory,
                      CATSoftwareConfiguration      * ipConfig,
                      CATBoolean                      useTopToolsCreateDomains = FALSE);
  static void AddDiscoSkinsAndExportToNCGM(
                      CATListPtrCATICGMObject        &ioListBodiesToExport,
                const CATSubdArrayDisco3DSkinP       &iSkinsArray,
                      CATGeoFactory                 * ipFactory,
                      CATSoftwareConfiguration      * ipConfig,
                      CATBoolean                      useTopToolsCreateDomains = FALSE);
  static void AddSkinBodiesOfCXShellAndExportToNCGM(
                      CATListPtrCATICGMObject        &ioListBodiesToExport,
                      CATCXShell                    * ipCXShell,
                      CATGeoFactory                 * ipFactory,
                      CATSoftwareConfiguration      * ipConfig,
                      CATBoolean                      useTopToolsCreateDomains = FALSE);
  static void AddSkinBodiesOfCXShellsAndExportToNCGM(
                      CATListPtrCATICGMObject        &ioListBodiesToExport,
                      CATSubdArrayCXShellP          * ipArrayOfShell,
                      CATGeoFactory                 * ipFactory,
                      CATSoftwareConfiguration      * ipConfig,
                      CATBoolean                      useTopToolsCreateDomains = FALSE);

  static void ExportSkinBodiesToNCGM(
                      CATCXBody                     * ipCXBodyToDbgExport,
                      CATGeoFactory                 * ipFactory,
                      CATSoftwareConfiguration      * ipConfig,
                      CATBoolean                      useTopToolsCreateDomains = FALSE);

  static void ExportSkinBodiesToNCGM(
                      CATSubdArrayMultiVolumeP      * ipMultiVolsToDbgExport,
                      CATGeoFactory                 * ipFactory,
                      CATSoftwareConfiguration      * ipConfig,
                      CATBoolean                      useTopToolsCreateDomains = FALSE);

  static void AddMultiVolSkinBodiesAndExportToNCGM(
                      CATListPtrCATICGMObject        &ioListBodiesToExport,
                      CATSubdArrayMultiVolumeP      * ipMultiVolsToDbgExport,
                      CATGeoFactory                 * ipFactory,
                      CATSoftwareConfiguration      * ipConfig,
                      CATBoolean                      useTopToolsCreateDomains = FALSE);

  static void GetMultiVolSkinBodies(
                      CATListPtrCATICGMObject        &oListBodies_IS,
                      CATListPtrCATICGMObject        &oListBodies_ISandSE,
                      CATSubdArrayMultiVolumeP      * ipMultiVolsToDbgExport,
                      CATGeoFactory                 * ipFactory,
                      CATSoftwareConfiguration      * ipConfig,
                      CATBoolean                      useTopToolsCreateDomains = FALSE);
  
  static void AddSkinBodiesOfCXShell(
                      CATBoolean                      addBackwardBodyOfShell,
                      CATListPtrCATICGMObject        &ioListBodiesToExport_IS,
                      CATListPtrCATICGMObject        &ioListBodiesToExport_ISandSE,
                      CATCXShell                    * ipCXShell,
                      CATGeoFactory                 * ipFactory,
                      CATSoftwareConfiguration      * ipConfig,
                const CATTopData                     &iTopData,
                      CATUnicodeString                iPrefixString             = CATUnicodeString(),
                      CATBoolean                      useTopToolsCreateDomains  = FALSE,
                const Dbg_RGBColor                  * ipSkinColor               = NULL);

private:

  static CATBody* GetISBody(
                      CATDisco3DSkin                * ipDiscoSkin,
                      CATGeoFactory                 * ipFactory,
                const CATTopData                     &iTopData,
                      CATBoolean                      useTopToolsCreateDomains = FALSE,
                      CATUnicodeString                iNamePrefix = CATUnicodeString());
  static CATBody* GetSEBody(
                      CATDisco3DSkin                * ipDiscoSkin,
                      CATGeoFactory                 * ipFactory,
                const CATTopData                     &iTopData,
                      CATUnicodeString                iNamePrefix = CATUnicodeString());

  static CATBody* GetISBody(
                      CATSubdIntersectionSkin       * ipIS,
                      CATGeoFactory                 * ipFactory,
                const CATTopData                     &iTopData,
                      CATBoolean                      useTopToolsCreateDomains = FALSE,
                      CATUnicodeString                iNamePrefix = CATUnicodeString());
  static CATBody* GetSEBody(
                      CATSubdIntersectionSkin       * ipIS,
                      CATGeoFactory                 * ipFactory,
                const CATTopData                     &iTopData,
                      CATUnicodeString                iNamePrefix = CATUnicodeString());


public:

  //**********************************
  //   Manual call of compatible operator
  //**********************************

  static void CallCompatibleOperator_DiffList_InSameConfig(
                  CATTopCompatibleCGM       * pOriginalCompatible,
                  ListPOfCATBody            * ipAllBodies,
                  ListPOfCATBody            * ipBodiesToDiscard,
                  CATBoolean                  iDoRunTheCompatible   = TRUE);

  static void CallCompatibleOperator(
                  CATGeoFactory             * ipFactory,
                  CATSoftwareConfiguration  * iConfig,
                  ListPOfCATBody            * iBodiesAddr,
                  CATBoolean                  iDoRunTheCompatible   = TRUE);

  static void CallCompatibleOperator(
                  CATGeoFactory             * ipFactory,
                  CATSoftwareConfiguration  * iConfig,
                  CATBody                   * iBody1,
                  CATBody                   * iBody2,
                  CATBoolean                  iDoRunTheCompatible   = TRUE);

};

#define   DLR6_TRACE(argStream)                                                             argStream



#define   DLR6_DEBUG_DumpCATCell(argCell, argOutput)                                        CATDisco3DDebug::DumpCATCell(argCell, argOutput)
#define   DLR6_DEBUG_DumpCATTopo(argTopo, argOutput)                                        CATDisco3DDebug::DumpCATTopo(argTopo, argOutput)
#define   DLR6_DEBUG_DumpListOfCells(argListCells, argOutput)                               CATDisco3DDebug::DumpCATCellList(argListCells, argOutput)

#define   DLR6_DEBUG_printCXShellAsDiscoResult(argShell, argOutput)                         CATDisco3DDebug::DumpCompositionOfCXShell(argShell, argOutput)
#define   DLR6_DEBUG_printSubdVolAsDiscoResult(argVol, argOutput)                           CATDisco3DDebug::DumpCompositionOfVol(argVol, argOutput)
#define   DLR6_DEBUG_printMultivolAsDiscoResult(argMultiVol, argOutput)                     CATDisco3DDebug::DumpCompositionOfMultivol(argMultiVol, argOutput)
#define   DLR6_DEBUG_printMultivolListAsDiscoResult(argMultiVolList, argOutput)             CATDisco3DDebug::DumpCompositionOfMultivolList(argMultiVolList, argOutput)
#define   DLR6_DEBUG_printResultsByOperand(argListResultThis, argListResultOp, argOutput)   CATDisco3DDebug::DumpCompositionOfResultsByOperand(argListResultThis, argListResultOp, argOutput)

#define   DLR6_DEBUG_dumpDiscoEngineDomains(argEngine)                                      CATDisco3DDebug::DumpDiscoEngineDomains(argEngine)
#define   DLR6_DEBUG_dumpBdrySkinsArrayDetails(argSkins)                                    CATDisco3DDebug::DumpBdrySkinsArrayDetails(argSkins)

#define   DLR6_DEBUG_dumpGenericOccurence(argOcc, argOutput)                                CATDisco3DDebug::DumpGenericOccurenceForDebug(argOcc, argOutput)
#define   DLR6_DEBUG_dumpSpecificOccurence(argOcc, argOutput)                               CATDisco3DDebug::DumpSpecificOccurenceForDebug(argOcc, argOutput)

#define   DLR6_DEBUG_tassAndDumpJournal(argPrefix, argJournal, argIndent, argOutput)        CATDisco3DDebug::DumpJournal_Tass(argPrefix, argJournal, argIndent, argOutput)


#else // CATDisco3DDebug_ON

#define   DLR6_TRACE(argStream)

#define   DLR6_DEBUG_DumpCATCell(argCell, argOutput)
#define   DLR6_DEBUG_DumpCATTopo(argTopo, argOutput)
#define   DLR6_DEBUG_DumpListOfCells(argListCells, argOutput)

#define   DLR6_DEBUG_printCXShellAsDiscoResult(argShell, argOutput)
#define   DLR6_DEBUG_printSubdVolAsDiscoResult(argVol, argOutput)
#define   DLR6_DEBUG_printMultivolAsDiscoResult(argMultiVol, argOutput)
#define   DLR6_DEBUG_printMultivolListAsDiscoResult(argMultiVolList, argOutput)
#define   DLR6_DEBUG_printResultsByOperand(argListResultThis, argListResultOp, argOutput)

#define   DLR6_DEBUG_dumpDiscoEngineDomains(argEngine)
#define   DLR6_DEBUG_dumpBdrySkinsArrayDetails(argIS)

#define   DLR6_DEBUG_dumpGenericOccurence(argOcc, argOutput)
#define   DLR6_DEBUG_dumpSpecificOccurence(argOcc, argOutput)

#define   DLR6_DEBUG_tassAndDumpJournal(argPrefix, argJournal, argIndent, argOutput)

#endif

#endif //CATDisco3DDebug_H
