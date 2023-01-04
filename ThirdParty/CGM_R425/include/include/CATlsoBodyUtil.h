#ifndef CATlsoBodyUtil_H
#define CATlsoBodyUtil_H

// ++++ Includes ++++
#include "PersistentCell.h"
#include "ListPOfCATBody.h"
#include "CATListOfCATCells.h"
#include "ListPOfListPOfCATCell.h"
#include "ListPOfCATDeclarativeManifold.h"
#include "ListPOfCATCellManifoldGroup.h"
#include "ListPOfCATCellManifold.h"
#include "ListPOfCATLiveBody.h"
#include "CATBoolean.h"
#include "CATListOfShort.h"
#include "CATMathTransformation.h"
#include "CATCollec.h"
#include "CATLISTP_CATMathTransformation.h"
#include "ListPOfCATDomain.h"
#include "ListPOfCATPersistentBodies.h"
#include "CATListOfDouble.h"
#include "CATListOfInt.h"
#include "ListPOfCATManifold.h"
#include "CATBodyFreezeMode.h"
#include "ListPOfCATCell.h"
#include "CATLiveBody.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATEdge.h"
#include "ListPOfListPOfCATBody.h"

// ++++ Predeclarations ++++
class CATGeoFactory;
class CATCGMStream;
class CATCGMOutput;
class CATCGMJournalList;
class CATCell;
class CATICGMObject;
class CATDeclarativeManifold;
class CATManifold;
class CATCellManifoldGroup;
class CATCellManifold;
class CATLiveBody;
class CATCellManifoldPatternNavigator;
class CATlsoPersistentContext;
class CATPersistentBody;
class CATCellHashTable;
class CATSoftwareConfiguration;
class CATICGMContainer;
class CATAdvancedStampNavigator;
class CATFaceHashTable;
class CATEdgeHashTable;
class CATVertexHashTable;
class CATPersistentCellInfra;
class CATShell;


//=============================================================================
// CATlsoBodyUtil
// 
// responsable: LAP
// 
// Classe utilitaire pour l'object Body. Elle ne contient que des methodes
// statiques pour le steram de body.
//=============================================================================

class ExportedByPersistentCell CATlsoBodyUtil
{
public:
  //---------------------------------------------------------------------------
  // METHODES STATIC
  //---------------------------------------------------------------------------

  // For debug only
  static void DumpTopoAndDRep(CATBody * iBody, CATSoftwareConfiguration * iConfig, CATCGMOutput& os);


  static int GetNbDomains(CATPersistentBody * iPersistentBody, CATlsoPersistentContext & iContext);

  static void GetAllDomains(CATBody * iBody, ListPOfCATDomain & oBodyDomainList);
  static void GetAllDomains(CATPersistentBody * iPersistentBody,  CATlsoPersistentContext & iContext, ListPOfCATDomain & oBodyDomainList);
  static void GetAllDomainPersistentBodies(CATPersistentBody * iPersistentBody,  CATlsoPersistentContext & iContext, ListPOfCATPersistentBodies & oPersistentBodyDomainList);

  static void GetAllCells(CATBody *iBody, CATCellHashTable &oCellsHT, short iDim=-1); // no allocated HT
  static void GetAllCells(const ListPOfCATBody &iBodyList, ListPOfCATCell &ioCells, short iDim=-1);

  static int  GetNbFaces(CATBody * iBody);
  static void GetAllFaces(CATBody * iBody, ListPOfCATFace & oFaceList);
  static void GetAllFaces(CATBody *iBody, CATFaceHashTable &oAllFaceHT);
  static void GetAllEdges(CATBody *iBody, CATEdgeHashTable &oAllEdgeHT);
  static void GetAllEdges(CATBody *iBody, ListPOfCATEdge &oEdgeList);
	static void GetAllVertices(CATBody *iBody, CATVertexHashTable &oAllVertexHT);

  static void GetAllFaces(const ListPOfCATBody &iBodyList, ListPOfCATFace &oAllFaceList);
  static void GetAllFaces(const ListPOfCATBody &iBodyList, CATFaceHashTable &oAllFaceHT);

  static void GetAllEdges(const ListPOfCATBody &iBodyList, CATEdgeHashTable &oAllEdgeHT);

  static void GetDomainsFromDimension(CATBody * iBody, int iDimension, ListPOfCATDomain &oResultDomainList);
  static void GetDomainsByDimensions (CATBody * iBody, ListPOfCATDomain oResultDomainList[4]);
  static void GetDomainsByDimensions (const ListPOfCATBody & iBodyList, ListPOfCATDomain oResultDomainList[4]); 

  static CATBoolean AreSameLists(ListPOfCATDomain & iList1, ListPOfCATDomain & iList2);
  static CATBoolean AreSameLists(const ListPOfCATBody & iBodyList1, const ListPOfCATBody & iBodyList2); // To do

  static CATBoolean AreConnected(CATBody *iBody, const ListPOfCATBody &iBodiesList);

  static void GetNbDomainsByDimension(CATBody      * iBody,
                                      CATListOfInt & oNbDomainsByDimensionList,
                                      CATBoolean     iIncrementTheList=FALSE);
  static void GetNbDomainsByDimension(const ListPOfCATBody & iBodyList,
                                      CATListOfInt         & oNbDomainsByDimensionList);

  static void GetBodyDimensions(CATPersistentBody       * iPersistentBody,
                                CATlsoPersistentContext & iContext,
                                int                     & oLowDimension,
                                int                     & oHighDimension);

  static void GetBodyDimensions(CATBody * iBody,
                                int     & oLowDimension,
                                int     & oHighDimension);

  static short GetBodyLowDimension(CATBody * iBody);                                

  static void  GetBodyDimensions(const ListPOfCATBody & iBodyList,
                                int                  & oLowDimension,
                                int                  & oHighDimension);                      

  static CATBoolean IsClosed (CATBody * iBody);
  static CATBoolean IsClosed (CATPersistentBody * iPersistentBody, CATlsoPersistentContext & iContext);
  static CATBoolean IsVolumic(const ListPOfCATDomain & iDomainList);
  static CATBoolean IsVolumic(CATBody * iBody);
  static CATBoolean IsVolumic(CATPersistentBody * iPersistentBody, CATlsoPersistentContext & iContext);
  static CATBoolean IsSurfacic(CATBody * iBody);
  static CATBoolean IsLineic(CATBody * iBody);
  static CATBoolean IsMixedDimension(CATBody * iBody);
  static CATBoolean IsMixedDimension(ListPOfCATBody & iBodyList);
  static CATBoolean IsMixedDimension(CATPersistentBody * iPersistentBody, CATlsoPersistentContext & iContext);
  static CATBoolean IsNonManifoldVolumic(CATBody * iBody);
  static CATBoolean IsMixedDimensionWithLineic (CATBody * iBody);
  static CATBoolean IsEmpty (CATBody * iBody);
  static CATBody * CreateDuplicatedBody(CATBody * iBody, CATGeoFactory * iFactory=NULL);
  static CATBody * CreateBodyExtractFromDimension(CATBody * iBody, int iDimension,CATCGMJournalList &oJournal);
  static CATBody * CreateBodyExtractFromOtherDimensions(CATPersistentBody * iPBody, int iDimension,CATlsoPersistentContext & iContext,CATCGMJournalList &oJournal);
  static int       ExplodeBodyPerDomain(CATBody *iMultiDomainBody, ListPOfCATBody &oMonoDomainBodies);
  static int       ExplodePersistentBodyPerDomain(CATPersistentBody *iMultiDomainPBody,CATPersistentCellInfra & iPersistentInfra, ListPOfCATPersistentBodies &oMonoDomainPersistentBodies);

  static CATPersistentBody * CreatePersistentBodyExtractFromDimension(CATPersistentBody * iPersistentBody, int iDimension, CATlsoPersistentContext & iContext);
  static CATPersistentBody * CreatePersistentBodyExtractFromOtherDimensions(CATPersistentBody * iPersistentBody, int iDimension, CATlsoPersistentContext & iContext);

  // Do not used : it's a prototype for extract without loosing the activate on InputBody
  static CATBody * CreateBodyByExtract(CATBody              * iInputBody,
                                       const ListPOfCATCell & iCellToExtractList,
                                       CATBodyFreezeMode      iFreezeMode=CATBodyFreezeOn);

  // static CATBody* CreateVertexBody(CATGeoFactory* iFactory, CATMathPoint& iPoint);

  static int GetMonoVolumePBodyList(CATPersistentBody & iInputPBody, CATPersistentCellInfra & iPersistentInfra, ListPOfCATPersistentBodies & oMonoVolumePBodyList);
  static int GetMonoVolumeBodyList (CATBody & iInputBody, CATGeoFactory * ipFactory, ListPOfCATBody & oMonoVolumeBodyList);
  static int GetMultiVolumePBody (CATPersistentBody& iPBody, ListPOfCATCell& iCellList, CATPersistentCellInfra& iPersistentInfra, CATPersistentBody*& opMultiVolumePBody);
  static int GetMonoVolumePBody (CATPersistentBody& iPBody, CATCell& iCell, CATPersistentCellInfra& iPersistentInfra, CATPersistentBody*& opMonoVolumePBody);

  static void GetInterfacesFromNonManifoldBody(CATBody * iBody, ListPOfCATCell & oInterfaces);

  static CATShell * GetUniqueShell(CATBody * iBody);

  //-------------------------------------------------------------------------------------------------------
  // Duplicate Body //
  //-------------------------------------------------------------------------------------------------------
  static CATBoolean SameFactoryScale(CATGeoFactory *iFactory1, CATGeoFactory *iFactory2);
  static CATBoolean SameFactoryScale(CATBody * iIncomingBody, CATGeoFactory *iFactoryContainer);

  // Call CATBodyDatumiser
  static CATPersistentBody * CallBodyDatumiser(CATGeoFactory *iFactory, 
                                    CATSoftwareConfiguration *iConfig, 
                                    CATPersistentBody        *iPersistentBody,                                     
                                    CATlsoPersistentContext  &iContext,
                                    CATMathTransformation    *iMathTransfo=NULL,
                                    CATCGMJournalList        *oJournal=NULL,
                                    CATBoolean                iCreateManifold=FALSE);

  // Call CATBodyDatumiser
  static CATBody * CallBodyDatumiser(CATGeoFactory *iFactory, 
                                    CATSoftwareConfiguration *iConfig, 
                                    CATBody *iBodyToDuplicate, 
                                    CATMathTransformation *iMathTransfo=NULL,
                                    CATCGMJournalList *oJournal=NULL);

  static CATBody * BasicFastExtract(CATBody & iBody, CATGeoFactory & iFactory, CATFaceHashTable & iFaceHT, CATBoolean iComplementary=FALSE);

  //-------------------------------------------------------------------------------------------------------
  // ListPOfCATBody
  //-------------------------------------------------------------------------------------------------------
  // Stream(List)
  static void StreamBodyList(const ListPOfCATBody & iBodyList, CATMathStream& ioStr);
  static void StreamBody(const CATBody * iBody, CATMathStream& ioStr);
  static void StreamListOfBodyList(const ListPOfListPOfCATBody & iListOfBodyList, CATCGMStream& ioStr);

  // UnStream(List)
  static void UnStreamBodyList(ListPOfCATBody & oBodyList, CATMathStream& ioStr, CATICGMContainer * iFactory);
  static CATBody * UnStreamBody(CATMathStream& ioStr, CATICGMContainer * iFactory);
  static void UnStreamListOfBodyList(ListPOfListPOfCATBody & oListOfBodyList, CATCGMStream& ioStr, CATICGMContainer * iFactory);
  //-------------------------------------------------------------------------------------------------------
  // ListPOfCATDomain
  //-------------------------------------------------------------------------------------------------------
  // Stream(List)
  static void StreamDomainList(const ListPOfCATDomain & iDomainList, CATCGMStream& ioStr);
  static void StreamDomain(const CATDomain * iDomain, CATCGMStream& ioStr);

  // UnStream(List)
  static void UnStreamDomainList(ListPOfCATDomain & oDomainList, CATCGMStream& ioStr, CATICGMContainer * iFactory);
  static CATDomain * UnStreamDomain(CATCGMStream& ioStr, CATICGMContainer * iFactory);

  //-------------------------------------------------------------------------------------------------------
  // ListPOfCATCell
  //-------------------------------------------------------------------------------------------------------
  // Stream(List)
  static void StreamCellListOfList(const ListPOfListPOfCATCell & iCellListOfList, CATCGMStream& ioStr);
  static void StreamCellList(const ListPOfCATCell & iCellList, CATCGMStream& ioStr);
  static void StreamCellHashTable(const CATCellHashTable * iCellHashTable, CATCGMStream& ioStr);
  static void StreamCell(const CATCell * iCell, CATCGMStream& ioStr);
  static void PutColorOnCellList(const ListPOfCATCell & iCellList, int red, int green, int blue);
  static void StreamCATICGMObject(const CATICGMObject * iObject, CATCGMStream& ioStr);

  // UnStream(List)
  static void UnStreamCellListOfList(ListPOfListPOfCATCell & oCellListOfList, CATCGMStream& ioStr, CATICGMContainer * iFactory);
  static void UnStreamCellList(ListPOfCATCell & oCellList, CATCGMStream& ioStr, CATICGMContainer * iFactory);
  static CATCellHashTable * UnStreamCellHashTable(CATCGMStream& ioStr, CATICGMContainer * iFactory);
  static CATCell * UnStreamCell(CATCGMStream& ioStr, CATICGMContainer * iFactory);
  static CATICGMObject * UnStreamCATICGMObject(CATCGMStream& ioStr, CATICGMContainer * iFactory);

  //-------------------------------------------------------------------------------------------------------
  // CATCellManifold
  //-------------------------------------------------------------------------------------------------------
  // Stream(List)
  static void StreamCellManifoldList(const ListPOfCATCellManifold & iCMList, CATCGMStream& ioStr);
  static void StreamCellManifold(const CATCellManifold * iCM, CATCGMStream& ioStr);

  // UnStream(List)
  static void UnStreamCellManifoldList(ListPOfCATCellManifold & oCMList, CATCGMStream& ioStr, CATICGMContainer * iFactory);
  static CATCellManifold * UnStreamCellManifold(CATCGMStream& ioStr, CATICGMContainer * iFactory);
  //-------------------------------------------------------------------------------------------------------
  // CATDeclarativeManifold
  //-------------------------------------------------------------------------------------------------------
  // Stream(List)
  static void StreamDeclarativeManifoldList(const ListPOfCATDeclarativeManifold & iDMList, CATCGMStream& ioStr);
  static void StreamDeclarativeManifold(const CATDeclarativeManifold * iDM, CATCGMStream& ioStr);
  static void PutColorOnDeclarativeManifold(const CATDeclarativeManifold *iDM, int red, int green, int blue);
  static void PutColorOnDeclManifoldList(const ListPOfCATDeclarativeManifold & iDMList, int red, int green, int blue);

  // UnStream(List)
  static void UnStreamDeclarativeManifoldList(ListPOfCATDeclarativeManifold & oDMList, CATCGMStream& ioStr, CATICGMContainer * iFactory);
  static CATDeclarativeManifold * UnStreamDeclarativeManifold(CATCGMStream& ioStr, CATICGMContainer * iFactory);

  
  //-------------------------------------------------------------------------------------------------------
  // CATManifold
  //-------------------------------------------------------------------------------------------------------
  // Stream(List)
  static void StreamManifoldList(const ListPOfCATManifold & iDMList, CATCGMStream& ioStr);
  static void StreamManifold(const CATManifold * iDM, CATCGMStream& ioStr);

  // UnStream(List)
  static void UnStreamManifoldList(ListPOfCATManifold & oDMList, CATCGMStream& ioStr, CATICGMContainer * iFactory);
  static CATManifold * UnStreamManifold(CATCGMStream& ioStr, CATICGMContainer * iFactory);

  
  //-------------------------------------------------------------------------------------------------------
  // CATCellManifoldGroup
  //-------------------------------------------------------------------------------------------------------
  // Stream(List)
  static void StreamCellManifoldGroupList(const ListPOfCATCellManifoldGroup & iGroupList, CATCGMStream& ioStr);
  static void StreamCellManifoldGroup(const CATCellManifoldGroup * iGroup, CATCGMStream& ioStr);

  // UnStream(List)
  static void UnStreamCellManifoldGroupList(ListPOfCATCellManifoldGroup & oGroupList, CATCGMStream& ioStr, CATICGMContainer * iFactory);
  static CATCellManifoldGroup * UnStreamCellManifoldGroup(CATCGMStream& ioStr, CATICGMContainer * iFactory);


  //-------------------------------------------------------------------------------------------------------
  // CATCGMJournalList
  //-------------------------------------------------------------------------------------------------------
  static void StreamJournal(CATCGMJournalList * iJournal, CATCGMStream& ioStr, CATGeoFactory * iFactory);

  static CATCGMJournalList * UnStreamJournal(CATCGMStream& ioStr, CATGeoFactory * iFactory, CATSoftwareConfiguration * iConfig);

  static void StreamListOfShort(const CATListOfShort & iShortList, CATCGMStream& ioStr);
  static void UnStreamListOfShort(CATListOfShort & oShortList, CATCGMStream& ioStr);

  static void StreamListOfInt(const CATListOfInt & iIntList, CATCGMStream& ioStr);
  static void UnStreamListOfInt(CATListOfInt & oIntList, CATCGMStream& ioStr);

  static void StreamListOfDouble(const CATListOfDouble & iDoubleList, CATCGMStream& ioStr);
  static void UnStreamListOfDouble(CATListOfDouble & oDoubleList, CATCGMStream& ioStr);

  static void StreamCATMathTransformation(const CATMathTransformation * iTransfo, CATCGMStream& ioStr);
  static CATMathTransformation * UnStreamCATMathTransformation(CATCGMStream& ioStr);

  static void StreamListOfCATMathTransformation(const CATLISTP(CATMathTransformation) & iTransfoList, CATCGMStream& ioStr);
  static void UnStreamListOfCATMathTransformation(CATLISTP(CATMathTransformation) & oTransfoList, CATCGMStream& ioStr);

  static void StreamListOfCATLiveBody(const CATLISTP(CATLiveBody) & iLiveBodyList, CATCGMStream& ioStr);
  static void UnStreamListOfCATLiveBody(CATLISTP(CATLiveBody) & oLiveBodyList, CATCGMStream& ioStr, CATICGMContainer * iFactory);

  static void StreamLiveBody(const CATLiveBody * iLiveBody, CATCGMStream& ioStr);
  static CATLiveBody * UnStreamLiveBody(CATCGMStream& ioStr, CATICGMContainer * iFactory);

  static void StreamCATCellManifoldPatternNavigator(const CATCellManifoldPatternNavigator * iPatternNavigator, CATCGMStream& ioStr,  CATICGMContainer * iFactory);
  static CATCellManifoldPatternNavigator * UnStreamCATCellManifoldPatternNavigator(CATCGMStream& ioStr, CATICGMContainer * iFactory);

  static void StreamCATAdvancedStampNavigator(const CATAdvancedStampNavigator * iAdvancedStampNavigator, CATCGMStream& ioStr,  CATICGMContainer * iFactory);
  static CATAdvancedStampNavigator * UnStreamCATAdvancedStampNavigator(CATCGMStream& ioStr, CATICGMContainer * iFactory);

};

#endif /* CATlsoBodyUtil_H */
