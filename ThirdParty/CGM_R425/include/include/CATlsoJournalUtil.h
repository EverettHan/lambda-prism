#ifndef CATlsoJournalUtil_H
#define CATlsoJournalUtil_H

// ++++ Includes ++++
#include "PersistentCell.h"
#include "CATListOfCATCells.h"
#include "ListPOfCATFace.h"
#include "CATBoolean.h"
#include "CATListOfCATGeometries.h"
#include "CATDataType.h"
#include "IUnknown.h" // For HRESULT
#include "CATCGMJournal.h"
#include "CATCellManifold.h"
#include "ListPOfCATCellManifold.h"
#include "CATCGMJournalList.h"
#include "ListPOfCATBody.h"
#include "ListPOfCATPersistentBodies.h"
#include "ListPOfCATLiveBody.h"
#include "CATBody.h"

// ++++ Predeclarations ++++
class CATlsoPersistentContext;
class CATSoftwareConfiguration;
class CATGeoFactory;
class CATFace;
class CATVertex;
class CATLiveBody;
class CATPersistentCellInfra;

//=============================================================================
// CATlsoJournalUtil
// 
// responsable: LAP
// 
// Classe utilitaire pour l'operateur ModifyFace. Elle ne contient que des methodes
// statiques.
//=============================================================================

class ExportedByPersistentCell CATlsoJournalUtil
{
public:
  //---------------------------------------------------------------------------
  // METHODES STATIC
  //---------------------------------------------------------------------------
  // @nocgmitf 
  static void ChangeJournalType1ToType2(const CATCGMJournalList * iJournal,
                                        CATCGMJournal::Type iType1,
                                        CATCGMJournal::Type iType2,
                                        CATCGMJournalList *& ioModifiedJournal,
                                        CATBoolean iDeleteOrderForCreation=TRUE);

  // @nocgmitf 
  static void AddInfoToCreationItem(CATCGMJournalList *& ioJournal, int iInfo);

  // @nocgmitf 
  static int ComputeNbJournalItem(CATCGMJournalList * iJournal);
  // @nocgmitf 
  static int ComputeNbJournalItemWithType(CATCGMJournalList   * iJournal,
                                          CATCGMJournal::Type   iType,
                                          int                   iDimensionOnResultFilter=-1); // No filter
  // @nocgmitf 
  static int ComputeCreationOrderFromSameDimension(CATCGMJournalList * iJournal,
                                                   int                 iResultBodyDim);
  // @nocgmitf 
  static void ComputeCreationOrderVsModifyOrder(CATCGMJournalList * iCMJournal,
                                                int                 iResultBodyDim,
                                                int               & oNbCreationOrders,
                                                int               & oNbModifyOrders,
                                                int               & oNbDeleteOrders);
  // @nocgmitf 
  static void ComputeAbsorptionOrder(CATCGMJournalList * iJournal,
                                     int               & oNbAbsorptionOrders);
  // @nocgmitf 
  static CATBoolean OnlyCreationOrder(CATCGMJournalList * iCMJournal, int iResultBodyDim);
  // @nocgmitf 
  static CATBoolean OnlyFromNothing(CATCGMJournalList * iJournal, CATLISTP(CATCellManifold) & oBeforeCellManifoldList); //if FALSE, get before geometries // IF TRUE oBeforeGeometries.Size()==0
  // @nocgmitf 
  static void ComputeCreationOrderOfDimension(CATCGMJournalList * iJournal,
                                              int                 iDimensionFilter,
                                              int               & oNbCreationOrders,
                                              int               & oNbCreationOrdersWithInfo,
                                              int &oNbDifferentInfo);
  // @nocgmitf 
  static void OriginalCellListFromNoKeep(CATlsoPersistentContext & iContext,
                                         CATCGMJournalList       * iJournal,
                                         ListPOfCATCell          & oOriginalCellList,
                                         CATBoolean                iTopologicalCheck=FALSE,
                                         ListPOfCATCell          * oOriginalCandidateCellList=NULL);
  // @nocgmitf 
   static void OriginalCellListFromDeletion(CATCGMJournalList       * iJournal,
                                            ListPOfCATCell          & oOriginalDeletedCellList);
   // @nocgmitf 
  static void OriginalCellListFromModification(CATCGMJournalList       * iJournal,
                                               ListPOfCATCell          & oOriginalCellList);
  // @nocgmitf 
  static void OriginalCellListFromModificationOrderOnly(CATCGMJournalList       * iJournal,
                                                        ListPOfCATCell          & oOriginalCellList);
  // @nocgmitf 
  static void ResultCellListFromCreation(CATCGMJournalList       * iJournal,
                                         ListPOfCATCell          & oResultCellList,
                                         int                       iDimensionFilter = -1);

  //iMinInfo if not NULL will be used
  //iOldFaces if not empty will be used
  // @nocgmitf 
  static void ResultFacesFromModification(CATCGMJournalList *iJournal, short* iMinInfo, ListPOfCATFace *iOldFaces,  ListPOfCATFace &oResultFaces);

  //iMinInfo if not NULL will be used
  //iOldFaces if not empty will be used
  // @nocgmitf
  static void ResultFacesFromCreation(CATCGMJournalList *iJournal, short* iMinInfo, ListPOfCATFace *iOldFaces,  ListPOfCATFace &oResultFaces); //DSH1 Sep 2018

  static void ResultFacesFromAbsorption(CATCGMJournalList *iJournal, short* iMinInfo, ListPOfCATFace *iOldFaces, ListPOfCATFace &oResultFaces); //DSH1 Aug 2020
  // @param iDimensionFilter
  //      LegalValue 0 : Vertices Only
  //      LegalValue 1 : Edges Only
  //      LegalValue 2 : Faces Only
  //      LegalValue 3 : Volume Only
  //   No filter otherwise
  // @nocgmitf 
  static void ResultCellListFromCreationOrModification(CATCGMJournalList       * iJournal,
                                                       ListPOfCATCell          & oResultCellList,
                                                       int                       iDimensionFilter =-1);
  // @nocgmitf 
  static CATBoolean AreGeometricalyEqual(CATFace                  & iFace1,
                                         CATFace                  & iFace2,
                                         CATGeoFactory            & iFactory,
                                         CATSoftwareConfiguration * iConfig);

  // @nocgmitf 
  static CATBoolean AreTwinVertices(CATVertex * iVertex1, CATVertex * iVertex2, double iTol);

  // @nocgmitf 
  static void RemoveCreationOrder(CATCGMJournalList * ioJournal);

  // @nocgmitf 
  static void RemoveDeletionOrder(CATCGMJournalList * ioJournal);

  // @nocgmitf 
  static void RemoveCreationAndDeletionOrder(CATCGMJournalList * ioJournal, ListPOfCATCell &oDeletionCellList, CATLiveBody *iLiveBody=NULL, short iFilletFocusMode=0);

  // @nocgmitf 
  static void FindAllFirstGeometry(CATCGMJournalList * iJournal, CATLISTP(CATGeometry) & oFirstGeometryList);

  // @nocgmitf 
  static void FindFirstGeometryFromModification(CATCGMJournalList * iJournal, CATLISTP(CATGeometry) & oFirstGeometryList);

  // @nocgmitf 
  static void FindAllLastGeometry(CATCGMJournalList * iJournal, CATLISTP(CATGeometry) & oLastGeometryList);

  // @nocgmitf 
  static void FindLastManifold(CATCGMJournalList * iCMJournal, CATLISTP(CATCellManifold) & oLastCellManifoldList, CATCGMJournalRequest iRequestFilter=ThroughAllCreateAndModify);

  // @nocgmitf 
  static void FindAllFirstGeometry(CATCGMJournalList * iJournal,
                                   ListPOfCATCell    & iLastGeometryList,
                                   ListPOfCATCell    & oFirstGeometryList);

  // @nocgmitf 
  static void FindAllLastGeometryFromFirst(CATCGMJournalList * iJournal,
                                           const ListPOfCATFace & iFirstGeometryList,
                                           ListPOfCATFace   & oLastGeometryList,
                                           int              * iInfoOnly=NULL);

  // @nocgmitf 
  static void FindAllLastGeometryFromFirst(CATCGMJournalList * iJournal,
                                           const ListPOfCATCell & iFirstGeometryList,
                                           ListPOfCATCell   & oLastGeometryList,
                                           int              * iInfoOnly=NULL);

  static void FindAllFirstGeometryFromLast(CATCGMJournalList * iJournal,
                                           const ListPOfCATCell &iLastGeometryList,
                                           ListPOfCATCell &oFirstGeometryList,
                                           int *iInfoOnly = NULL);
    //static void FindAllLastGeometryFromFirstWithInfoOnly(CATCGMJournalList * iJournal,
    //                                       const ListPOfCATFace & iFirstGeometryList,
    //                                       ListPOfCATFace   & oLastGeometryList,
    //                                       int              * iInfoOnly=NULL); //DSH1 Sep 2018
  
  // @nocgmitf 
  static void FindAllLastGeometryFromFirst_Old(CATCGMJournalList * iJournal,
                                           ListPOfCATFace    & iFirstGeometryList,
                                           ListPOfCATFace    & oLastGeometryList);
  
  // @nocgmitf 
  static CATBoolean IsACellManifoldJournal(CATCGMJournalList * iJournal);
  
  // @nocgmitf 
  static void FindFacesWithSeveralAncestors (CATCGMJournalList * iJournal, ListPOfCATFace & oResultOutputFaces);
  
  // @nocgmitf 
  static void KeepOnlyOrderWithRibbons (CATCGMJournalList *iCMJournal, ListPOfCATCell &iDeletionCellList, CATLiveBody *iLiveBody, CATCGMJournalList *&ioResultSubJournal);

  // oResultCellJournal must be allocated or nothing will be done
  // @nocgmitf 
  static HRESULT ConvertToProceduralJournal (CATCGMJournalList *iCellJournal, 
                                              CATLISTP(CATGeometry) &iInputCellList,
                                              CATCGMJournalList *&oResultCellJournal,
                                              CATSoftwareConfiguration * iConfig);

  
  // @nocgmitf 
  static HRESULT ConvertToProceduralJournal_Old (CATCGMJournalList *iCellJournal, CATCGMJournalList *&oResultCellJournal);

  //-----------------------------------------------------------------------------
  // Create a journal to simulate a application code
  //-----------------------------------------------------------------------------
  
  // @nocgmitf 
  static void CreateAndAddModificationJournalFromTag(CATULONG32                 iBeforeTag,
                                                    CATULONG32                  iAfterTag,
                                                    CATCGMJournalList        *& ioJournal,
                                                    CATGeoFactory            *  iFactory,
                                                    CATSoftwareConfiguration *  iConfig);

  
  // @nocgmitf 
  static void FindLasts(CATCGMJournalList * iJournal, CATLISTP(CATGeometry) & iGeoms, CATLISTP(CATGeometry) & oGeoms, CATCGMJournal::Type iType);
  
  // @nocgmitf 
  static void FindLasts(CATCGMJournalList * iJournal, CATLISTP(CATGeometry) & iGeoms, CATLISTP(CATGeometry) & oGeoms, CATCGMJournalRequest iRequest);
  
  // @nocgmitf 
  static void FindAllDeletedGeometries(CATCGMJournalList * iJournal, CATLISTP(CATGeometry) & oDeletedGeometryList);

  //if iOrder <= -2 -> OK
  //   iOrder == -1 -> OK if no info
  //   iOrder >= 0  -> OK if info.number == iOrder
  // @nocgmitf 
  static CATBoolean RightOrder(CATCGMJournalList * iJournal, CATGeometry * iMother, CATGeometry * iImage, int iOrder);
  
  // @nocgmitf 
  static CATCGMJournal::Type GetTypeFromAfterObject(CATGeometry * iGeometry, CATCGMJournalList * iJournal);
  
  // @nocgmitf 
  static CATCGMJournalList *RemoveModificationInfosFromJournal(CATCGMJournalList &iJournalToModify,
                                                               CATSoftwareConfiguration *iConfig);

	static void CompleteMinimalValidJournal(ListPOfCATBody             &iInputCopyBodies,
																				  ListPOfCATBody					   &iInputNoCopyBodies,
																				  CATBody                    *iResultBody,
                                          CATCGMJournalList          &ioCellJournal);
  
  // @nocgmitf 
	static void CompleteMinimalValidJournal(const ListPOfCATPersistentBodies &iInputCopyBodies,
																					ListPOfCATPersistentBodies &iInputNoCopyBodies,
																					CATPersistentCellInfra     &iInfra,
																					CATBody                    *iResultBody,
																					CATCGMJournalList          &ioCellJournal);

  //Remove or change orders concerning CM of bodies not in the lists. Works only for Copy mode for now
  //iPreviousLiveInputBodies and iPreviousLiveOutputBodies are the old inputs and output of the journal,iLiveInputBodiesToKeep and iLiveOutputBodiesToKeep are all the new ones
  // @nocgmitf 
  static void FilterCopyJournalForSpecificLiveBodies(ListPOfCATLiveBody         &iPreviousLiveInputBodies,
                                                     ListPOfCATLiveBody         &iPreviousLiveOutputBodies,
                                                     CATCGMJournalList          &ioCellManifoldJournal,
                                                     ListPOfCATLiveBody         &iLiveInputBodiesToKeep,
                                                     ListPOfCATLiveBody         &iLiveOutputBodiesToKeep,                                                     
                                                     CATCGMJournalList          &oFilteredCellManifoldJournal);

private :

  // INTERNAL METHODS
  // --------------------
  // @nocgmitf 
  static CATBoolean ContainSameGeometry (CATLISTP(CATGeometry) &iBeforeList, CATLISTP(CATGeometry) &iAfterlist);
  // @nocgmitf 
  static void CompleteMinimalValidJournalMain(CATCellHashTable              &iInputCopyBodiesReportingCells,
                                              CATCellHashTable              &InputNoCopyBodiesReportingCells,
                                              ListPOfCATCell                &iOutputReportingCells,
																					    CATCGMJournalList             &ioCellJournal);

};

#endif /* CATlsoJournalUtil_H */
