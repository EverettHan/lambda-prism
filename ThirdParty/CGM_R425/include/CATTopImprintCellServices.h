// COPYRIGHT DASSAULT SYSTEMES 2018
//=======================================================================================================================
//
// CATTopImprintCellServices: 
// Class offers services on Imprint Attributes.
//=======================================================================================================================
// Changes
//=======================================================================================================
//
//=======================================================================================================
//
// Usage notes:
//   
// 
//
//=======================================================================================================================

#ifndef CATTopImprintCellServices_H
#define	CATTopImprintCellServices_H

#include "ExportedByCATTopologicalObjects.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"
#include "CATCollec.h"
#include "CATCGMOutput.h"
#include "CATCGMJournal.h"

class CATICGMObject;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATGeometry;
class CATLISTP(CATGeometry);
class CATLISTP(CATICGMObject);
class CATCell;
class CATCGMJournal;
class CATCGMJournalList;
class CATBody;
class CATCGMJournalInfo;
class CATListPtrCATCell;
class CATCGMHashTable;
class CATSoftwareConfiguration;
class CATListPtrCATBody;
class CATExtTopOperator;
class CATAdaptiveHashTable;
class CATTopOperator;
class CATTopology;

/**
* Class offers services on Imprint Attributes.
*/
class ExportedByCATTopologicalObjects CATTopImprintCellServices
{
public:

   /** @nodoc @nocgmitf */
   /**
   * Temporary method to simul different modelisations for imprint in propagation
   * Note : in this test we will consider that the factory is flagged as imprint, but all tested bodies to not really have imprint edges
   *        the goal is to evaluate what perf loss we would have on already existing non-imprint features
   *
   * @return a number describing the current tested model
   * <dl>
   * <dt><tt>1</tt>   <dd> current one : we flag only the factory, if the factory is flagged imprint, then we consider the operation as imprint
   * <dt><tt>2</tt>   <dd> we check for edges inside every input body to know if they are imprint or not
   * <dt><tt>3</tt>   <dd> we put attributes on FACES of bodies that have imprint edges
   * <dt><tt>4</tt>   <dd> we put attributes on SHELLS of bodies that have imprint edges
   * <dt><tt>5</tt>   <dd> we put attributes on BODIES that have imprint edges
   * </dl>
   *
   */
   static int ModelNumber_ForPerfoTest();

   /** @nodoc @nocgmitf */
   /**
   * Temporary method to decide if we always want to simulate the saearch "is the input body imprint" in the method GetExpectedCellsForReporting
   * or if we only do that search when the user wants the imprint edges to be returned
   */
   static CATBoolean GetExpectedCell_Simul_SearchImprintInBody();

   /** @nodoc @nocgmitf */
   /**
     * Fake test (for perf purpose only, will always return FALSE) to know if a topology has an imprint attribute or not
     */
   static CATBoolean PerfSimul_TopologyHasImprintAttribut(CATTopology* ipTopo);

   /** @nodoc @nocgmitf */
   /**
     * Fake test (for perf purpose only) to know if a CATBody contains an imprinted edge or not
     */
   static CATBoolean PerfSimul_BodyHasImprintAttribut(CATBody* ipBody, int curModelToTest);

   /** @nodoc @nocgmitf */
   /**
     * Fake test (for perf purpose only, will always return TRUE if the tested model is between 1 and 5) to know if a CATCeoFactory has an imprint attribute or not
     */
   static CATBoolean PerfSimul_FactoryHasImprintAttribut(CATGeoFactory* ipFactory, int curModelToTest);

   /** @nodoc @nocgmitf */
   /**
     * Test to know if some input body has an imprint atribute or not, depending on the currently tested model
     */
   static CATBoolean PerfSimul_ThereIsImprintInSomeBody(const CATListPtrCATBody& iBodiesToScan, int curModelToTest);


   /** @nodoc @nocgmitf */
   /**
   * Put the Imprint Attribute on the given Cell
   * <br><b>Role</b>: Put the Imprint Attribut on the given Cell
   *
   * @param piCellToImprint [in]
   *   The Cell to be Imprinted
   * @return
   * <dl>
   * <dt><tt>S_OK</tt>     <dd>if succeeded
   * <dt><tt>E_FAIL</tt>    <dd>if failed
   * </dl>
   *
   */
   static HRESULT SetImprint(CATCell *piCellToImprint);

   /** @nodoc @nocgmitf */
   /**
   * Put the Imprint Attribute on the given Cell
   * <br><b>Role</b>: Put the Imprint Attribut on the given Cell
   *
   * @param iCellsToImprint [in]
   *   List of cells to imprint
   * @return
   * <dl>
   * <dt><tt>S_OK</tt>     <dd>if succeeded
   * <dt><tt>E_FAIL</tt>    <dd>if failed
   * </dl>
   *
   */
   static HRESULT SetImprint(CATListPtrCATCell& iCellsToImprint);

   /** @nodoc @nocgmitf */
   /**
   * Remove the Imprint Attribute on the given Cell
   * <br><b>Role</b>: Put the Imprint Attribut on the given Cell
   *
   * @param piCellToImprint [in]
   *   The Cell to be Imprinted
   * @return
   * <dl>
   * <dt><tt>S_OK</tt>     <dd>if succeeded
   * <dt><tt>E_FAIL</tt>    <dd>if failed
   * </dl>
   *
   */
   static HRESULT UnSetImprint(CATCell *piCellToImprint);

   /** @nodoc @nocgmitf */
   /**
   * Remove the Imprint Attribute on the given Cell
   * <br><b>Role</b>: Put the Imprint Attribut on the given Cell
   *
   * @param piCellToImprint [in]
   *   The Cell to be Imprinted
   * @return
   * <dl>
   * <dt><tt>S_OK</tt>     <dd>if succeeded
   * <dt><tt>E_FAIL</tt>    <dd>if failed
   * </dl>
   *
   */
   static HRESULT UnSetImprint(CATBody *pBody,
                               CATCGMJournalList* piJournal,
                               short Dim);

   /** @nodoc @nocgmitf */
   /**
   * Test if the given Cell has an Imprint Cell Attribute
   * <br><b>Role</b>: Test if the given Cell has an Imprint Cell Attribute
   *
   * @param piCellToImprint [in]
   *   the Cell under scope
   * @return
   * <dl>
   * <dt><tt>TRUE</tt>     <dd>if Cell has an Imprint Attribute
   * <dt><tt>FALSE</tt>    <dd>if not
   * </dl>
   *
   */
   static CATBoolean HasImprintAttribut(CATCell *piCell);

   /** @nodoc @nocgmitf */
   /**
   * Test if the factory has an Imprint Attribute
   * <br><b>Role</b>: Test if the factory has an Imprint Attribute
   *
   * @param ipFactory [in]
   *   The factory to test
   * @return
   * <dl>
   * <dt><tt>TRUE</tt>     <dd>if the factory has an Imprint Attribute
   * <dt><tt>FALSE</tt>    <dd>if not
   * </dl>
   *
   */
   static CATBoolean HasImprintAttribut(CATGeoFactory *ipFactory);

   /** @nodoc @nocgmitf */
   /**
   * Test if the body has an Imprint Attribute
   * <br><b>Role</b>: Test if the factory has an Imprint Attribute
   *
   * @param ipFactory [in]
   *   The factory to test
   * @return
   * <dl>
   * <dt><tt>TRUE</tt>     <dd>if the factory has an Imprint Attribute
   * <dt><tt>FALSE</tt>    <dd>if not
   * </dl>
   *
   */
   static CATBoolean HasImprintAttribut(CATBody *ipBody);

   /** @nodoc @nocgmitf */
   /**
   * Test if the list of bodies has an Imprint Attribute
   * <br><b>Role</b>: Test if the factory has an Imprint Attribute
   *
   * @param ipFactory [in]
   *   The factory to test
   * @return
   * <dl>
   * <dt><tt>TRUE</tt>     <dd>if the factory has an Imprint Attribute
   * <dt><tt>FALSE</tt>    <dd>if not
   * </dl>
   *
   */
   static CATBoolean HasImprintAttribut(const CATListPtrCATBody& iBodiesToScan);

#ifdef CATIACGMR421CAA
   /** @nodoc @nocgmitf */
   /**
   * Log in the given Journal the events related to imprint cells
   * <br><b>Role</b>: Log in the given Journal the events related to imprint cells
   *
   * @param piSoftConfig [in]
   *   Soft Config for Algo Level Management
   *
   * @param piMasterJournal [in]
   *   Standard Journal that will embed Imprint Journal in which events related to imprint cells
   * @param iType
   *   The type of the item.
   * @param iBeforeObjects
   *   The list of the objects before the operation.
   * @param iAfterObjects
   *   The list of the objects after the operation.
   * @param iOptionalInfo
   * A pointer to an optional information. If <tt>NULL</tt>, no information is
   * added.
   * @return
   * <dl>
   * <dt><tt>S_OK</tt>     <dd>if succeeded
   * <dt><tt>E_FAIL</tt>    <dd>if failed
   * </dl>
   */
   static HRESULT Report(CATCGMJournalList *piMasterJournal,
                         CATCGMJournal::Type iType,
                         const CATLISTP(CATGeometry) & iBeforeObjects,
                         const CATLISTP(CATGeometry) & iAfterObjects,
                         CATCGMJournalInfo *ioOptionalInfo = NULL);

   /** @nodoc @nocgmitf */
   /**
   * Retrieve the Imprint Journal from the standard journal
   * <br><b>Role</b>: Dump Retrieve the Imprint Journal from the standard journal
   *
   * @param piMasterJournal [in]
   *   Standard Journal that contain the Imprint Journal
   * @return
   *  The Imprint Journal
   */
   //static CATCGMJournalList *GetImprintJournal(CATCGMJournalList *piMasterJournal);

   /** @nodoc @nocgmitf */
   /**
   * Copy the "embedded Imprint Journals", from the Master Journal , in the given Journal
   * <br><b>Role</b>: retrieve a copy of the Imprint Journals from the standard journal
   *
   * @param piMasterJournal [in]
   *   Standard Journal that will be scanned to retrieve all embedded imprint journals
   * @param pioImprintJournal [in]
   *   Journal to fill, Life Cycle Management under caller resp.
   * @return
   * <dl>
   * <dt><tt>S_OK</tt>     <dd>if succeeded
   * <dt><tt>E_FAIL</tt>    <dd>if failed
   * </dl>
   */
   static HRESULT GetImprintJournal(CATSoftwareConfiguration *piSoftConfig,
                                    CATCGMJournalList *piMasterJournal,
                                    CATCGMJournalList *&pioImprintJournal);

   /**
   * Merge the tassed "standard journal", given as input, and its potential Imprint Journal in a single journal
   * <br><b>Role</b>: return a journal that corresponds to the standard journal and the
   *
   * @param piSoftConfig [in]
   *   Soft Config that drive algo level
   * @param piMasterJournal [in]
   *   Standard Journal that will be dumped
   * @param pioImprintJournal [in]
   *   Journal to fill, Life Cycle Management under caller resp.
   * @return
   * <dl>
   * <dt><tt>S_OK</tt>     <dd>if succeeded
   * <dt><tt>E_FAIL</tt>    <dd>if failed
   * </dl>
   */
   static HRESULT GetStandardAndImprintJournal(CATSoftwareConfiguration *piSoftConfig,
                                               CATCGMJournalList *piMasterJournal,
                                               CATCGMJournalList *&pioStandardAndImprintJournal);

   /** @nodoc @nocgmitf */
   /**
   * Dump the given Journal with the embedded imprint journals (ONLY FOR DEBUG PURPOSE)
   * <br><b>Role</b>: Dump the given Journal with the embedded imprint journals
   *
   * @param piMasterJournal [in]
   *   Standard Journal that will be dumped
   *
   * @param ios [in]
   *   Stream destination
   */
   static void DumpStandardAndImprintJournal(CATCGMJournalList *piMasterJournal,
                                             CATCGMOutput & ioCGMStr,
                                             int iIdent = 0);

   /** @nodoc @nocgmitf */
   /**
   * Dump the embedded imprint journals (ONLY FOR DEBUG PURPOSE)
   * <br><b>Role</b>: Dump the embedded imprint journals
   *
   * @param piMasterJournal [in]
   *   Standard Journal to retrieve internal journal
   *
   * @param ios [in]
   *   Stream destination
   */
   static void DumpImprintJournal(CATCGMJournalList *piMasterJournal,
                                  CATCGMOutput & ioCGMStr,
                                  int iIdent = 0);

   /** @nodoc @nocgmitf */
   /**
   * Dump the content of the journal standard ans internal (ONLY FOR DEBUG PURPOSE)
   * <br><b>Role</b>: Dump the content of the journal standard ans internal
   *
   * @param piMasterJournal [in]
   *   Standard Journal to retrieve internal journal
   *
   * @param pJounrnalName [in]
   *   Jounral Name
   *
   * @param ios [in]
   *   Stream destination
   */
   static void DumpAllJournal(CATCGMJournalList *piMasterJournal,
                              CATCGMOutput & ioCGMStr,
                              char *piJounrnalName = NULL,
                              int iIdent = 0);

   /** @nodoc @nocgmitf */
   /**
   * Check if a given Cell is incident to an Imprint Cell in the contexte of the Body (ONLY FOR INTERNAL USE)
   * <br><b>Role</b>:
   * Rmk : Currently for Vertex
   *       Method should be moved to another interface
   * @param piCell [in]
   *   Input Cell
   *
   * @param piBody [in]
   *   Input Body
   *
   */
   static CATBoolean IsCellIncidentToImprintCell(CATCell *piCell,
                                                 CATBody *piBody,
                                                 CATBoolean iCheckFaces = TRUE);
   /** @nodoc @nocgmitf */
   /**
   * Define the rules that a given cell must respect to be imprinted
   * @param ipCell [in]
   *   Input Cell
   * @return
   *   TRUE if the cell can be imprinted, false otherwise.
   */
   static CATBoolean CanThisCellBeImprinted(CATCell * ipCell);

   /** @nodoc @nocgmitf */
   /**
   * CRetrieve seam Vertices from the given Body (ONLY FOR INTERNAL USE)
   * <br><b>Role</b>:
   * Rmk : Body must be 1D/2D, can be multi shell/wire but each shell must contain one face
   *       Each loop must contain 2 Edges, both edges must rely on the same Crv
   *       Method should be moved to another interface
   *
   * @param piBody [in]
   *   Input Body
   *
   *  @ param GetSeamVerticesOfBody [in/out]
   *    contain seam vertices
   *
   * @return
   * <dl>
   * <dt><tt>S_OK</tt>     <dd>if succeeded
   * <dt><tt>E_FAIL</tt>    <dd>if failed
   * </dl>
   */
   static HRESULT GetSeamVerticesOfBody(CATSoftwareConfiguration *piSoftConfig,
                                        CATBody* piBody,
                                        CATCGMHashTable *&pioHashTableOfSeamVertices);

   /** @nodoc @nocgmitf */
   /**
   * simple service for post-processing imprint journal through given options (ONLY FOR INTERNAL USE)
   *
   * <br><b>Role</b>:
   * Rmk :  The imprint journal, referenced by the input std journal, is expected tassed
   * @param piCGMJournalList [in]
   *   Input standard journal
   */
   static void RattrapImprintJournals(CATCGMJournalList *piCGMJournalList,
                                      CATBoolean iDeActivateDeletedOrders);

   /** @nodoc @nocgmitf */
   /**
   * U29: DO NOT USE UNDER DEVELOPPEMENT  !
   */
   static void CorrectOutputs_ImprintJournals(CATCGMJournalList * ipStandardJournal,
                                              const CATListPtrCATBody& iInputCopyBody,
                                              const CATListPtrCATBody& iInputNoCopyBody,
                                              CATBody * ipResultBody,
                                              CATBoolean iFullJournal = TRUE,
                                              CATBoolean iAddOrphanCreations = FALSE,
                                              CATBoolean iEliminateRedondancy = FALSE,
                                              CATBoolean iForceCreationForIncreasingDimension = FALSE,
                                              CATBoolean iConvertCreationToModifyWhenPossible = FALSE,
                                              CATBoolean iAddMissingDeletions = FALSE,
                                              CATBoolean iAddMissingKeeps = FALSE);

#endif

   /** @nodoc @nocgmitf */
   /**
   * Dump the Cells that have Imprint Attributes in a context of a given body (ONLY FOR DEBUG PURPOSE)
   * <br><b>Role</b>: Dump the Imprint Attribut of a given body
   *
   * @param piBody [in]
   *   Input Body
   *
   * @param ios [in]
   *   Stream destination
   */
   static void DumpImprintCells(CATBody *piBody,
                                CATCGMOutput & ioCGMStr,
                                short iSkipLineEachNbCell=10,
                                short iIdent=0);
   //********************************************************************************************************************
   // WARNING !!! INTERNAL ONLY
   //********************************************************************************************************************

   /** @nodoc @nocgmitf */
   static CATBoolean IsImprint_ForceImprintSimplification();

   /** @nodoc @nocgmitf */
   static CATBoolean IsImprint_DecorateSeamEdges();

   /** @nodoc @nocgmitf */
   static CATBoolean IsImprint_DecorateInputs(int iCGMLevel);

   /** @nodoc @nocgmitf */
   static CATBoolean IsImprint_SharpEdges();

   /** @nodoc @nocgmitf */
   static CATBoolean IsImprint_DecorateExtrudedShape();

   /** @nodoc @nocgmitf */
   static CATBoolean IsImprint_ForceActivation();

   /** @nodoc @nocgmitf */
   static CATBoolean IsImprint_CGMReplay();

   /** @nodoc @nocgmitf */
   static CATBoolean Is_BM_UnableCheckSameImprint();

   /** @nodoc @nocgmitf */
   static CATBoolean Is_BM_UnableMapping();

   /** @nodoc @nocgmitf */
   static CATBoolean Is_JM_UnableMappingImprintJ();

   /** @nodoc @nocgmitf */
   static CATBoolean Is_JM_UnableMapping();
   
   /**  Debug Purpose (Internal usage) */
   static int Is_OldImprintSubstitution_Requested();

   /** @nodoc @nocgmitf */
   static void DecorateForDebug(CATListPtrCATCell& iCellsToImprint,
                                CATCGMJournalList * ipMasterJournal);
   /** @nodoc @nocgmitf */
   static void DecorateForDebug(CATAdaptiveHashTable* ipCellsToImprint,
                                CATCGMJournalList * ipMasterJournal);
   /** @nodoc @nocgmitf */
   static void DecorateForTests(CATListPtrCATBody & iBodiesToDecorate,
                                int iCGMLevel);

   /** @nodoc @nocgmitf */
   static void DecorateForTests(CATTopOperator * ipOperator);

   /** @nodoc @nocgmitf */
   static CATBoolean EventuallyDeactiveGenericPropag(CATExtTopOperator * ipExtTopOperator,
                                                     const CATListPtrCATBody& iBodiesToScan);

   /** @nodoc @nocgmitf */
   static void ReplaceByNewImprintAttribute(CATGeoFactory *iGoodFactory,
                                            CATLISTP(CATICGMObject) &ioObjects);
private:
   /** @nodoc @nocgmitf */
   ~CATTopImprintCellServices();
   /** @nodoc @nocgmitf */
   CATTopImprintCellServices();
   /** @nodoc @nocgmitf */
   CATTopImprintCellServices(const CATTopImprintCellServices &iCopy);
   /** @nodoc @nocgmitf */
   CATTopImprintCellServices& operator=(const CATTopImprintCellServices &iCopy);
};
#endif
