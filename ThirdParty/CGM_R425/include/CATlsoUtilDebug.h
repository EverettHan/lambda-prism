/* -*-C++-*- */

#ifndef CATlsoUtilDebug_H
#define CATlsoUtilDebug_H
/*  
=============================================================================

RESPONSABLE  : L Marini

DESCRIPTION  : Class for debug only:
               - dump of list
               - color and name for body
               
=============================================================================
*/
class CATlsoContext;
class CATCGMOutput;
class CATBody;
class CATCGMJournalList;
class CATDRepExtTopOperator;
class CATMathTransformation;
class CATHashTableWithIntAssoc;
class CATCellHashTable;
class CATFaceHashTable;
class CATTopOpInError;
class CATCGMInputError;
class CATCGMAnnotation;
class CATCGMHashTable;
class CATLine;
class CATExtCGMReplay;
class CATCGMStream;

#include "PersistentCell.h"
#include "ListPOfCATTopology.h"
#include "ListPOfCATCell.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATEdge.h"
#include "ListPOfCATVertex.h"
#include "ListPOfCATDomain.h"
#include "CATListOfCATGeometries.h" 
#include "CATBoolean.h"
#include "ListPOfCATBody.h"
#include "CATDataType.h"
#include "CATLiveBody.h"
#include "ListPOfCATLiveBody.h"
#include "CATCGMHashTable.h"
#include "ListPOfListPOfCATCell.h"
#include "ListPOfCATPersistentCells.h"
#include "ListPOfCATManifold.h"
#include "CATDeclarativeApplication.h"
#include "CATDeclarativeOriginModeler.h"
#include "CATDeclarativeContext.h"
#include "CATExtTopOperator.h"
#include "ListPOfCATManifoldModification.h"
#include "ListPOfCATDeclarativeManifold.h"
#include "CATContextualManifold.h"
#include "CATEvaluableManifold.h"
#include "CATPlaneManifold.h"
#include "CATManifoldAttribute.h"
#include "CATExtrusionManifoldAttribute.h"
#include "CATHoleManifoldAttribute.h"

//--------------------------------------------------------------------------

ExportedByPersistentCell int LSODump(const CATCGMHashTable* iHT);
ExportedByPersistentCell int LSODump(const CATCGMJournalList* iJournal);

class ExportedByPersistentCell CATlsoUtilDebug
{

public:

  //-----------------------------------------------------------------------------
  // Dump of a journal
  //-----------------------------------------------------------------------------
  static void DumpJournal(CATCGMOutput      & os,
                          CATCGMJournalList * iJournal,
                          const char        * iJournalName);


  //-----------------------------------------------------------------------------
  // Dump of an Error
  //-----------------------------------------------------------------------------
  // Dump the chain of error
  static void DumpTopOpInError( CATCGMOutput            & os,
                                CATTopOpInError         * iError,
                                const char              * iErrorName,
                                CATBoolean                iHighLightLocationCells=FALSE);

  // Dump the first error
  static void DumpCGMInputError( CATCGMOutput            & os,
                                 CATCGMInputError        * iError,
                                const char               * iErrorName);

  // Send To Explicit Factory a list of Body
  static void SendToExplicitFactory(const ListPOfCATBody & iBodyList);

  //-----------------------------------------------------------------------------
  // Dump of a hashTable with int association
  //-----------------------------------------------------------------------------
  static void DumpHT(CATCGMOutput                   & os,
                     const CATHashTableWithIntAssoc & iHT,
                     const char                     * iHTName);

  //-----------------------------------------------------------------------------
  // Dump of a list of geometry
  //-----------------------------------------------------------------------------
  static void DumpList(CATCGMOutput                & os,
                       const CATLISTP(CATGeometry) & iGeomList,
                       const char                  * iListName);

  //-----------------------------------------------------------------------------
  // Dump of a list of cells
  //-----------------------------------------------------------------------------
  static void DumpList(CATCGMOutput         & os,
                       const ListPOfCATCell & iCellList,
                       const char           * iListName);


  //-----------------------------------------------------------------------------
  // Dump of a list of persistent cells
  //-----------------------------------------------------------------------------
  static void DumpList(CATCGMOutput                    & os,
                       const ListPOfCATPersistentCells & iCellList,
                       const char                      * iListName);


  //-----------------------------------------------------------------------------
  // Dump of a HashTable of Cells
  //-----------------------------------------------------------------------------
  static void DumpList(CATCGMOutput         & os,
                       const CATCellHashTable * iCellHashTable,
                       const char           * iListName);


  //-----------------------------------------------------------------------------
  // Dump of a list of Manifolds (CATCellManifoldGroup, CATDeclarativeManifold)
  //-----------------------------------------------------------------------------
  static void DumpList(CATCGMOutput                 & os,
                       const ListPOfCATManifold     & iManifoldList,
                       const char                   * iListName);

  //-----------------------------------------------------------------------------
  // Dump of a list of CellManifolds
  //-----------------------------------------------------------------------------
  static void DumpList(CATCGMOutput                 & os,
                       const ListPOfCATCellManifold & iCellManifoldList,
                       const char                   * iListName);

  //-----------------------------------------------------------------------------
  // Dump of a list of DeclarativeManifolds
  //-----------------------------------------------------------------------------
  static void DumpList(CATCGMOutput                        & os,
                       const ListPOfCATDeclarativeManifold & iDeclarativeManifoldList,
                       const char                          * iListName);

  //-----------------------------------------------------------------------------
  // Dump of a list of Face
  //-----------------------------------------------------------------------------
  static void DumpList(CATCGMOutput         & os,
                       const ListPOfCATFace & iFaceList,
                       const char           * iListName);

  //-----------------------------------------------------------------------------
  // Dump of a list of Edge
  //-----------------------------------------------------------------------------
  static void DumpList(CATCGMOutput         & os,
                       const ListPOfCATEdge & iEdgeList,
                       const char           * iListName);

  //-----------------------------------------------------------------------------
  // Dump of a list of Vertex
  //-----------------------------------------------------------------------------
  static void DumpList(CATCGMOutput           & os,
                       const ListPOfCATVertex & iVertexList,
                       const char             * iListName);

  //-----------------------------------------------------------------------------
  // Dump of a list of Body
  //-----------------------------------------------------------------------------
  static void DumpList(CATCGMOutput         & os,
                       const ListPOfCATBody & iBodyList,
                       const char           * iListName);

  //-----------------------------------------------------------------------------
  // Dump of a list of Domain
  //-----------------------------------------------------------------------------
  static void DumpList(CATCGMOutput           & os,
                       const ListPOfCATDomain & iDomainList,
                       const char             * iListName);

  //-----------------------------------------------------------------------------
  // Dump of a list of ManifoldModification
  //-----------------------------------------------------------------------------
  static void DumpList(CATCGMOutput                         & os,
                       const ListPOfCATManifoldModification & iModifList,
                       const char                           * iListName);


  //-----------------------------------------------------------------------------
  // Dump of a list of Double
  //-----------------------------------------------------------------------------
  static void DumpList(CATCGMOutput           & os,
                       const CATListOfDouble  & iListOfDouble,
                       const char             * iListName=NULL);

  static void DumpList(CATCGMOutput             & os,
                       const ListPOfCATTopology & iListOfTopology,
                       const char               * iListName=NULL);
  //-----------------------------------------------------------------------------
  // Dump the differences between two lists of CATFace
  //-----------------------------------------------------------------------------
  static void DumpFaceListDifferences (const ListPOfCATFace& iFaceList1, const CATUnicodeString& iListName1,
                                       const ListPOfCATFace& iFaceList2, const CATUnicodeString& iListName2,
                                       CATCGMOutput& os);

  //-----------------------------------------------------------------------------
  // Dump of a HashTable of Cells
  //-----------------------------------------------------------------------------
  static void DumpHashTable(CATCGMOutput           & Os,
                            const CATCellHashTable & iCellHT,
                            const char             * iHTName=NULL);


  //-----------------------------------------------------------------------------
  // Dump Transformation
  //-----------------------------------------------------------------------------
  static void DumpTransformation(CATCGMOutput       & os,
                       const CATMathTransformation  & iTransformation,
                       const char                   * iName=NULL);

  //-----------------------------------------------------------------------------
  // Dump DRepOptions
  //-----------------------------------------------------------------------------
  static void DumpDRepOptions(CATCGMOutput & os,
                              CATLiveBody  * iLiveBody);


  //-----------------------------------------------------------------------------
  // Put red color and name on body.
  //-----------------------------------------------------------------------------
  static void PutRedColorAndNameOnBody(CATBody & iErrorBody,
                                       char    * iNameBody);

  //-----------------------------------------------------------------------------
  // Put select color on cell list
  //-----------------------------------------------------------------------------
  static void PutSelectColorOnInputCells(const ListPOfCATCell &iInputCells);

  static void PutSelectColorOnInputCells(const ListPOfListPOfCATCell &iListOfInputCells);

  static void PutColorOnCellHashTable(const CATCellHashTable & iCellHT, int red, int green, int blue);
  static void PutColorOnFaceHashTable(const CATFaceHashTable & iFaceHT, int red, int green, int blue);

  static void PutColorOnCellList(const ListPOfCATCell &iCellList, int red, int green, int blue);
  static void PutColorOnFaceList(const ListPOfCATFace &iFaceList, int red, int green, int blue);

  // param visible = 0: noshow,  1: show in black,  2: show like face color
  //
  // see DeclarativeOperators.tst\LSODoc.d\LSO_Debug\NCGM_like_3DEXPERIENCE.pptx
  static void ResetColorAs3DEXPERIENCE(CATBody * ipBody, int iVisibleVertex=0, int iVivisibleEdge=1);

  // Display black edge and black vertices and hide vertices
  static void ResetEdgeColorAs3DEXPERIENCE(CATBody * ipBody, int red=0, int green=0, int blue=0);

  static void ReleaseAllEdgeAttribute (CATBody* ipBody);

  // Switch mode for vertices
  static void HideShowVertices(CATBody * ipBody, CATBoolean iForceHide=FALSE);

  static void PutColorOnCellDim(CATBody * ipBody, int iDimensionCell, int red, int green, int blue);

  // CGMReplay
  //-----------------------------------------------------------------------------
  static CATExtCGMReplay * GetAssociatedCGMReplay(CATCGMStream &iStr);

  //-----------------------------------------------------------------------------
  // Create Line between 2 edges 
  //-----------------------------------------------------------------------------
  static CATLine * CreateLineBetween2Edges(CATGeoFactory *iFactory, CATEdge *iEdge1, CATEdge *iEdge2, const int (* iLineColorRGB)[3]=NULL );

  //-----------------------------------------------------------------------------
  // IsNameOnBodyAlreadyExist
  //-----------------------------------------------------------------------------
  static CATBoolean IsNameOnBodyAlreadyExist(char * iNameBody, CATGeoFactory & iFactory);


  //-----------------------------------------------------------------------------
  // PutAnnotationOnCell
  //-----------------------------------------------------------------------------
  static CATCGMAnnotation * PutAnnotationOnCell(const CATCell           * iCell, 
                                                const CATUnicodeString  & iText, 
                                                const int              (* iColorRGB)[3]   = NULL, 
                                                const char                OperatorFlag[4] = "DRep",
                                                const double           (* iCoord)[3]      = NULL);

  //-----------------------------------------------------------------------------
  // Put name and color (optional) on body 
  //-----------------------------------------------------------------------------
  static void PutNameAndColorOnBody(CATBody &  iErrorBody,
                                    const char *  iNameBody,
                                    short      iColor_R = -1,
                                    short      iColor_G = -1,
                                    short      iColor_B = -1,
                                    CATBoolean iPreserveOldName = TRUE,
                                    CATLONG32  iNumber = -1,
                                    CATLONG32  iSubNumber = -1);


  //-----------------------------------------------------------------------------
  // Check the CM belong to input and output Bodies
  //-----------------------------------------------------------------------------
  static void CheckJournalForDebug(CATCGMJournalList * iCMJournal,
                                   const char        * iOpName,
                                   const ListPOfCATLiveBody & iInputLiveBodyList,
                                   const ListPOfCATLiveBody & iOutputLiveBodyList);

  //-----------------------------------------------------------------------------
  // Dump the name of the operator
  //-----------------------------------------------------------------------------
  static void DumpOperatorName(CATDRepExtTopOperator       * iOpeImpl,
                               CATCGMOutput                & os,
                               const char                  * iAdditionalText=NULL);

  //-----------------------------------------------------------------------------
  // PutYellowOrangeTwoGradualColor
  //  iNumberOfCurrentObject = [1, N]
  //  iNbObjects             = N
  //-----------------------------------------------------------------------------
  static void PutYellowOrangeTwoGradualColor(CATICGMObject * iObj,
                                             int             iNumberOfCurrentObject,
                                             int             iNbObjects);

  //-----------------------------------------------------------------------------
  // PutPinkBlueTwoGradualColor
  //  iNumberOfCurrentObject = [1, N]
  //  iNbObjects             = N
  //-----------------------------------------------------------------------------
  static void PutPinkBlueTwoGradualColor(CATICGMObject * iObj,
                                         int             iNumberOfCurrentObject,
                                         int             iNbObjects);


  //-----------------------------------------------------------------------------
  // PutColorPaletteOnObjects
  //-----------------------------------------------------------------------------
  static void GetColorPalette(int iNumberOfCurrentObject, int &oR, int &oG, int &oB);
  static void PutColorPaletteOnObjects(CATICGMObject *iObj, int iNumberOfCurrentObject);

  //-----------------------------------------------------------------------------
  // Utilities to display arrow, cylinders etc.
  // NB: in case the shape is oriented (cone, arrow), iP2 is always the point/end
  //-----------------------------------------------------------------------------
  static double GetBodyMaxLength(CATBody &iBody);
  static CATMathPoint GetMiddlePoint(CATBody &iBody, CATFace &iFace, CATBoolean iOffsetWithShellNormal = FALSE);
  static CATMathPoint GetMiddlePoint(CATBody &iBody, ListPOfCATFace &iFaces, CATBoolean iOffsetWithShellNormal = FALSE);
  static CATMathPoint GetMiddlePoint(CATBody &iBody, CATCellManifold &iCM, CATBoolean iOffsetWithShellNormal = FALSE);
  static CATMathPoint GetMiddlePoint(CATBody &iBody, CATDeclarativeManifold &iDM, CATBoolean iOffsetWithShellNormal = FALSE);
  
private:
  static CATCylinder* DisplayCylinder(CATBody &iBody, CATMathPoint &iP1, CATMathPoint &iP2, double iRadius, int iR, int iG, int iB, CATLISTP(CATICGMObject) *ioToClean = NULL);
  static CATCone* DisplayCone(CATBody &iBody, CATMathPoint &iP1, CATMathPoint &iP2, int iR, int iG, int iB, CATLISTP(CATICGMObject) *ioToClean = NULL);
  static CATTorus* DisplayTorus(CATBody &iBody, CATMathPoint &iP1, CATMathPoint &iP2, CATMathVector &iV, double iRadius, double iAngleShift, int iR, int iG, int iB, CATLISTP(CATICGMObject) *ioToClean = NULL);
public:
  static void DisplayArrow(CATBody &iBody, CATMathPoint &iP1, CATMathPoint &iP2, int iR, int iG, int iB, CATLISTP(CATICGMObject) *ioToClean = NULL);
  static void DisplayCurveArrow(CATBody &iBody, CATMathPoint &iP1, CATMathPoint &iP2, CATMathVector &iV, int iR, int iG, int iB, CATLISTP(CATICGMObject) *ioToClean = NULL);

  //-----------------------------------------------------------------------------
  // CATCGMLiveOperatorSettings
  //-----------------------------------------------------------------------------
  static void SetLiveSetting_Application (CATDeclarativeApplication iApplication);
  static void SetLiveSetting_Industry (CATDeclarativeContextIndustry iIndustry);
  static void SetLiveSetting_Modeler (CATDeclarativeOriginModeler iModeler);

  static CATDeclarativeApplication     GetLiveSetting_Application ();
  static CATDeclarativeContextIndustry GetLiveSetting_Industry    ();
  static CATDeclarativeOriginModeler   GetLiveSetting_Modeler     ();

  static void HideAllBodiesExceptList(CATGeoFactory &iGeoFactory, ListPOfCATBody &iBodiesToShow);


  //-----------------------------------------------------------------------------
  // Pilot the prefix of CGMReplay
  //
  // c:lsoprj : "CGMReplay Prefix (LAP) [0(force off), 1(force on), 2(force force)] (default: 1)";
  //
  // set CATLSOProject_CGMReplayPrefix=0    To deactivate the prefix
  // set CATLSOProject_CGMReplayPrefix=1    Insert your prefix in the automatic prefix.
  // set CATLSOProject_CGMReplayPrefix=2    Force to stream only your prefix.
  //-----------------------------------------------------------------------------
  static void SetCGMReplayPrefixeName(const char *ipPrefixe, int iNumber=0);      // Main useful method.
  static void SwithableSetPrefixeName(const char *ipText);                        // In case of complexe prefix name, if you want to pilot the force mode with interactiv or variable

  // To manage the imbrication of operators
  static void SetExtTopKeyForPrefixeName  (CATExtTopOperator * ipExtTopKey);      // It’s already installed in the CATAdvancedExtTopOperator. Use it to avoid reset from sub operator.
  static void ResetExtTopKeyForPrefixeName(CATExtTopOperator * ipExtTopKey);      // It’s already installed in the CATAdvancedExtTopOperator. You have to call it in the desturctor.
  static void ResetCGMReplayPrefixeName   (CATExtTopOperator * ipExtTopKey=NULL); // To call at the end of the global operator. It’s already installed in the CATAdvancedExtTopOperator (PersistentOperator).

};


#endif
