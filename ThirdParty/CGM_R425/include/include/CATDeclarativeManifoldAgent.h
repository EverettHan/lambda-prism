#ifndef CATDeclarativeManifoldAgent_H
#define CATDeclarativeManifoldAgent_H

#define CATDeclarativeManifoldAgentArchitecture

#include "PersistentCell.h"
#include "CATCGMStreamAttribute.h"
#include "CATCGMNewArray.h"
#include "CATCGMNewClassArray.h"                                       
#include "CATLiveBody.h"
#include "ListPOfCATEdge.h"
#include "ListPOfCATVertex.h"
#include "ListPOfCATCellManifold.h"
#include "ListPOfCATManifoldNavigator.h"
#include "CATCollec.h"
#include "CATCellManifoldsManager.h"
#include "ListVOfLong.h"
#include "CATMathInline.h"
#include "CATDeclarativeContext.h"
#include "CATRecognizerContext.h"
#include "CATDeclarativeApplication.h"
#include "CATDeclarativeOriginModeler.h"
#include "CATDMAgentContext.h"

#include "CATPatternDefine.h"
#include "CATCellManifoldsManagerOpe.h"

class CATCellFollower;
class CATBody;
class CATCell;
class CATLISTP(CATCell);
class CATSoftwareConfiguration;
class CATGeoFactory;
class CATCGMJournalList;
class CATCGMProgressBar;
class CATPersistentCellInfra;
class CATSharedManifoldAgent;
class CATCellManifoldCreator;
class CATCellManifoldMerger;
class CATDeclarativeManifoldCarrier;
class CATDeclarativeManifoldCarrierTransfoContext;
class CATDatumManifoldCarrier;
class CATAdvancedManifoldCarrier;
class CATSubdivisionRecognizer;
class CATDatumManifoldCreator;
class CATCanonicRecognizer;
class CATFilletRecognizer;
class CATCellManifoldPatternCreator;
class CATCellManifoldOffsetCreator;
class CATCellManifoldGroupCarrier;
class CATCellManifoldGroupSplitter;
class CATWallAndBendRecognizer;
// class CATCGMHashTable;
class CATRibbonManifoldCreatorBase;
class CATFilletManifoldCreatorInfraContext;
class CATChamferRecognizer;
class CATChamferManifoldCreatorInfraContext;
class CATExtrusionManifoldCreatorBase;
class CATPadPocketManifoldCreator;
class CATHoleManifoldCreator;
class CATSlotManifoldCreator;
class CATNotchManifoldCreator;
class CATDeclarativeOperatorsBridge;
class CATDraftRecognizer;
class CATDraftManifoldCreatorInfraContext;
class CATLogoRecognizer;
class CATButtonManifoldGlobalRecognizer;
class CATButtonManifoldRecognizer;
class CATDRepAdvancedStampLocalRecognition;
class CATDRepAdvancedStampGlobalRecognition;
class CATCellHashTable;
template <class CATCellManifold> class CATLSOHashTable;

// -----------------------------------------------------------------------------------------------
// Macros dedicated to implementation of child classes
// -----------------------------------------------------------------------------------------------
#define CATCGMDeclareManifoldAgent(iChild, iParent) \
CATCGMDeclareAttribute(iChild,iParent);             \
CATCGMNewClassArrayDeclare;     

#define CATCGMImplManifoldAgent(iChild, iParent)      \
CATCGMImplAttribute(iChild,iParent,CGM_DRep_Agent,1); \
CATCGMNewClassArray(iChild,3,catcgmPoolTEMP)          

#define CATCGMImplManifoldAgentForeign(iChild, iParent, iAppName)      \
CATCGMImplAttribute(iChild,iParent,CGM_DRep_Agent,iAppName,1); \
CATCGMNewClassArray(iChild,3,catcgmPoolTEMP)

// -----------------------------------------------------------------------------------------------
class ExportedByPersistentCell CATDeclarativeManifoldAgent : protected CATCGMStreamAttribute
// -----------------------------------------------------------------------------------------------
{
public:
  CATCGMDeclareAttribute(CATDeclarativeManifoldAgent, CATCGMStreamAttribute);

  CATCGMNewClassArrayDeclare;      // Pool allocation
	
	// Constructor
  CATDeclarativeManifoldAgent();
	
  // Destructor
	virtual ~CATDeclarativeManifoldAgent();

  virtual HRESULT CreateImageManifolds() = 0;
  virtual void AddCellManifoldImage(CATLISTP(CATCellManifold) &iParentCellManifolds, CATLISTP(CATCellManifold) &iChildrenManifolds, int iInfo, CATBoolean iForbidZeroInfo=TRUE);
  virtual int GetPriority() = 0;
  virtual CATBoolean IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold() = 0;
  virtual CATDeclarativeManifoldAgent* Clone() = 0;
  //virtual const char * GetAgentNameForDebug() = 0;

  virtual HRESULT InitAgentWithContexts(CATDeclarativeContext & iContext,
                                        CATDeclarativeOriginModeler iModeler=CATDeclarativeOriginModeler_CGM,
                                        CATGeoFactory         * iFactory=NULL);

  INLINE CATSoftwareConfiguration* GetConfig() const;

  // to implement in case you need versioning to condition the priority (sometimes CellManifoldManager is not yet available)
  INLINE virtual int GetPriorityWithConfig(CATSoftwareConfiguration *iConfig);

  virtual CATCanonicRecognizer * GetAsCanonicRecognizer();
  virtual CATDeclarativeManifoldCarrier * GetAsDeclarativeManifoldCarrier();
  virtual CATDatumManifoldCarrier * GetAsDatumManifoldCarrier();
  virtual CATCellManifoldCreator* GetAsCellManifoldCreator();
  virtual CATCellManifoldMerger* GetAsCellManifoldMerger();
  virtual CATDeclarativeManifoldCarrierTransfoContext * GetAsDeclarativeManifoldCarrierTransfoContext();
  virtual CATDatumManifoldCreator* GetAsDatumManifoldCreator();
  virtual CATCellManifoldGroupCarrier * GetAsCellManifoldGroupCarrier();
  virtual CATFilletRecognizer * GetAsFilletRecognizer();
  virtual CATAdvancedManifoldCarrier * GetAsAdvancedManifoldCarrier();
  virtual CATFilletManifoldCreatorInfraContext *GetAsFilletManifoldCreatorInfraContext();
  virtual CATChamferRecognizer * GetAsChamferRecognizer();
  virtual CATChamferManifoldCreatorInfraContext *GetAsChamferManifoldCreatorInfraContext();
  virtual CATCellManifoldGroupSplitter * GetAsCellManifoldGroupSplitter();
  virtual CATSubdivisionRecognizer * GetAsSubdivisionRecognizer();
  virtual CATExtrusionManifoldCreatorBase * GetAsExtrusionManifoldCreatorBase();
  virtual CATPadPocketManifoldCreator     * GetAsPadPocketManifoldCreator();
  virtual CATHoleManifoldCreator          * GetAsHoleManifoldCreator();
  virtual CATSlotManifoldCreator          * GetAsSlotManifoldCreator();
  virtual CATNotchManifoldCreator         * GetAsNotchManifoldCreator();
  virtual CATCellManifoldPatternCreator * GetAsCellManifoldPatternCreator();
  virtual CATCellManifoldOffsetCreator * GetAsCellManifoldOffsetCreator();
  virtual CATDeclarativeManifoldDuplicationCarrier * GetAsDuplicationManifoldCarrier();
  virtual CATDraftRecognizer * GetAsDraftRecognizer();
  virtual CATDraftManifoldCreatorInfraContext *GetAsDraftManifoldCreatorInfraContext(); 
  virtual CATLogoRecognizer * GetAsLogoRecognizer();
  virtual CATButtonManifoldRecognizer * GetAsButtonManifoldRecognizer();
  virtual CATButtonManifoldGlobalRecognizer * GetAsButtonManifoldGlobalRecognizer();
  virtual CATDRepAdvancedStampLocalRecognition * GetAsDRepAdvancedStampLocalRecognition();
  virtual CATDRepAdvancedStampGlobalRecognition * GetAsDRepAdvancedStampGlobalRecognition();
  virtual CATRibbonManifoldCreatorBase * GetAsRibbonManifoldCreatorBase();

  void SetCellFollower(CATCellFollower*& ioCellFollower);
  INLINE CATCellFollower* GetCellFollower() const;

  INLINE void SetCellManifoldsManager(CATCellManifoldsManager *iManager);
  INLINE CATCellManifoldsManager* GetCellManifoldsManager() const;
  INLINE CATBoolean HaveCellManifoldManager();

  INLINE void SetDeclarativeContext(CATDeclarativeContext *iContext);
  INLINE CATDeclarativeContext* GetDeclarativeContext();

  void SetProgressBar(CATCGMProgressBar* iProgressBar);
  CATCGMProgressBar* GetProgressBar() const;
  CATBoolean SetProgress(const double iValue, const double iTotalValue = 100.0, CATBoolean iThrowIfInterrupted = FALSE, const char* iStaticConstLabel = NULL);

  void SetRecognizerContext(CATRecognizerContext & iContext);
  CATRecognizerContext * GetRecognizerContext();

  void SetDeclarativeApplication(CATDeclarativeApplication iAppli);
  CATDeclarativeApplication GetDeclarativeApplication();

  INLINE void SetCellManifoldJournal(CATCGMJournalList *iCellManifoldJournal);
  INLINE CATCGMJournalList * GetCellManifoldJournal() const;

  HRESULT SetCuttingEdges(CATLISTP(CATEdge) &iCuttingEdges);
  INLINE void GetCuttingEdgesImages(CATLISTP(CATEdge) &oCuttingEdges);
  INLINE void GetCuttingVerticesImages(CATLISTP(CATVertex) &oCuttingVertices);

  virtual CATBoolean GetAdmissibleCells(CATLISTP(CATCell) &ioAdmissibleCells);

  INLINE void AddCreatedCellManifold(ListPOfCATCellManifold& iCreatedCellManifolds);
  INLINE void GetCreatedCellManifold(ListPOfCATCellManifold& ioCreatedCellManifolds) const;
  void GetCreatedCellManifold(CATLSOHashTable<CATCellManifold> & ioCreatedCellManifolds) const;

  void GetAdmissibleCellManifold(ListPOfCATCellManifold& ioAdmissibleCellManifolds);
  
  void GetAdmissibleCellManifold(CATLSOHashTable<CATCellManifold> & ioAdmissibleCMHashTable);

  //if iOrder == -2 -> Get all images from Modification and creation order with info or not
  //   iOrder == -1 -> Get all images from Modification and creation order without info
  //   iOrder >= 0  -> Get all images from Modification and creation order with info.number == iOrder
  void GetCellManifoldImage(CATCellManifold* iMother, ListPOfCATCellManifold &ioChildren, CATLONG32 iOrder=-2, CATBoolean iCreationMode=FALSE) const;
  void GetCellManifoldParent(CATCellManifold* iChild, ListPOfCATCellManifold &ioParents);
  void GetCellManifoldImage(const ListPOfCATCellManifold &iMothers, ListPOfCATCellManifold &ioChildren, CATLONG32 iOrder=-2, CATBoolean iCreationMode=FALSE) const;
  void GetCellManifoldParent(ListPOfCATCellManifold &iChildren, ListPOfCATCellManifold &ioParents);

  void GetDeclarativeManifoldImage(CATDeclarativeManifold* iParent, ListPOfCATDeclarativeManifold &ioChildren) const;
  void GetDeclarativeManifoldParent(CATDeclarativeManifold* iChild, ListPOfCATDeclarativeManifold &ioParents);
  void GetDeclarativeManifoldParent(ListPOfCATDeclarativeManifold &iChildren, ListPOfCATDeclarativeManifold &ioParents);
  CATLONG32 GetOrder(CATCellManifold *iCreatedCellManifold);

  virtual CATBoolean IsAllowedToFail();
  virtual CATBoolean AllowSamePriorityAgent();

  INLINE void SetAgentContext(CATDMAgentContext* ipContext);

  INLINE void GetImpactedCellManifold(ListPOfCATCellManifold& ioImpactedCellManifolds);

  INLINE void AppendShareDeclarativeManifold(CATDeclarativeManifold *iShareDeclarativeManifold);
  INLINE void GetShareDeclarativeManifolds(ListPOfCATDeclarativeManifold &ioShareDeclarativeManifolds);

  virtual void Stream(CATCGMStream& Str) const;  
  virtual void UnStream(CATCGMStream& Str, CATGeoFactory* iFactory, CATSoftwareConfiguration * ipConfig);  

  virtual void Dump(CATCGMOutput &os);

  // For CGMReplay only
  static CATDeclarativeManifoldAgent* CreateAgentFromStream(const int iVersion, CATCGMStream& Str);
  static void StreamAgent(const int iVersion, const CATDeclarativeManifoldAgent* iAgent, CATCGMStream& Str);

  static CATDeclarativeManifoldAgent* CreateAgentFromId(CATLONG32 iAgentId); // To be removed when all CGMReplay have been migrated to new version
  INLINE CATLiveBody* GetOriginalBodyForKeepManifolds() const;
  
  INLINE CATGeoFactory* GetFactory();
  INLINE CATBody * GetOutputBody() const;
  INLINE CATPersistentBody * GetOutputPersistentBody();

  INLINE CATLiveBody * GetOutputLiveBody() const;

  virtual CATBoolean HasLicenseToKillDeclarativeManifold();

  void SetLastError(const char * iErrorMessageID, ListPOfCATCell & ipCellLocationList);

  INLINE int GetNbOfInputBodies() const;
  INLINE CATBody * GetInputBody(int iInputBody) const;

protected:
  
  INLINE CATLiveBody * GetInputLiveBody(int iInputBody) const;  
  INLINE CATPersistentBody * GetInputPersistentBody(int iNumInputBody);
  INLINE CATPersistentCellInfra *GetInfra();//could be empty
  CATBoolean IsACuttingEdge(CATEdge * iEdge);
  INLINE const ListPOfCATCell* GetExpectedCellsForReporting();
  void GroupCellsByDomainAndConnexity(CATBody* iOutputBody, 
    const CATLISTP(CATCell) &iImageCells, CATLISTP(CATCell) &oImageCellsSortedByDomain, CATListOfLong &oImageCellsByDomain, const CATCellHashTable * ipMultiDomCellHT=NULL);

  CATDeclarativeOperatorsBridge * GetDeclarativeOperatorsBridge();
  INLINE CATDMAgentContext* GetAgentContext() const;
  void AppendImpactedCellManifold(ListPOfCATCellManifold& iImpactedCellManifolds);
  CATBoolean DimensionChange();
  virtual CATBoolean GetThroughCreateAndModifyMode();

private:
  void UnStream(CATCGMStream& Str); // Do not use or redefine this method. Use method with Factory.

private:
  int                           _DebugTag;
  CATCellFollower             * _CellFollower;
  CATCellManifoldsManager     * _Manager;
  CATDeclarativeContext       * _DeclarativeContext;
  CATDMAgentContext           * _AgentContext;
  CATCGMProgressBar           * _ProgressBar;
  CATRecognizerContext        * _RecognizerContext; // Container object which stores the data useful for Geometrical recognition
  CATDeclarativeApplication     _DeclarativeApplication;
  CATCGMJournalList           * _CellManifoldJournal;
  ListPOfCATEdge              * _CuttingEdges;
  ListPOfCATEdge              * _CuttingEdgesImages;
  ListPOfCATVertex            * _CuttingVerticesImages;
  ListPOfCATCellManifold        _CreatedCellManifolds;
  ListPOfCATCellManifold      * _ImpactedCellManifolds;
  ListPOfCATDeclarativeManifold _ShareDeclarativeManifolds;

};

INLINE CATCellFollower* CATDeclarativeManifoldAgent::GetCellFollower() const
{
  return _CellFollower;
}

INLINE void CATDeclarativeManifoldAgent::SetCellManifoldsManager(CATCellManifoldsManager *iManager)
{
  _Manager = iManager;
}

INLINE CATCellManifoldsManager* CATDeclarativeManifoldAgent::GetCellManifoldsManager() const
{
  if (!_Manager) CATThrowForNullPointerReturnValue(NULL);
  return _Manager;
}
INLINE CATBoolean CATDeclarativeManifoldAgent::HaveCellManifoldManager()
{
  return _Manager?TRUE:FALSE;
}

INLINE void  CATDeclarativeManifoldAgent::SetDeclarativeContext(CATDeclarativeContext *iContext)
{
  if (_DeclarativeContext && iContext &&  _DeclarativeContext == iContext)//REN WK29 2021. FMR-218061
    return;

  if(_DeclarativeContext)
    _DeclarativeContext->Release();

  _DeclarativeContext = iContext;

  if(_DeclarativeContext)
    _DeclarativeContext->AddRef();
}
INLINE CATDeclarativeContext*  CATDeclarativeManifoldAgent::GetDeclarativeContext()
{
  //if (!_DeclarativeContext) CATThrowForNullPointerReturnValue(NULL);
  return _DeclarativeContext;
}
INLINE void CATDeclarativeManifoldAgent::SetCellManifoldJournal(CATCGMJournalList *iCellManifoldJournal)
{
  _CellManifoldJournal = iCellManifoldJournal;
}
INLINE CATCGMJournalList * CATDeclarativeManifoldAgent::GetCellManifoldJournal() const
{
  return _CellManifoldJournal;
}
INLINE void CATDeclarativeManifoldAgent::GetCuttingEdgesImages(CATLISTP(CATEdge) &oCuttingEdges)
{
  oCuttingEdges.RemoveAll(CATCollec::KeepAllocation);
  if (_CuttingEdgesImages)
    oCuttingEdges.Append(*_CuttingEdgesImages);
}
INLINE void CATDeclarativeManifoldAgent::GetCuttingVerticesImages(CATLISTP(CATVertex) &oCuttingVertices)
{
  oCuttingVertices.RemoveAll(CATCollec::KeepAllocation);
  if (_CuttingVerticesImages)
    oCuttingVertices.Append(*_CuttingVerticesImages);
}
INLINE void CATDeclarativeManifoldAgent::AddCreatedCellManifold(ListPOfCATCellManifold& iCreatedCellManifolds)
{
  _CreatedCellManifolds.Append(iCreatedCellManifolds);
}

INLINE void CATDeclarativeManifoldAgent::GetCreatedCellManifold(ListPOfCATCellManifold & ioCreatedCellManifolds) const {
  ioCreatedCellManifolds.Append(_CreatedCellManifolds);
}

INLINE CATBody * CATDeclarativeManifoldAgent::GetOutputBody() const
{
  return GetCellManifoldsManager()->GetOutputBody();
}
INLINE CATPersistentBody * CATDeclarativeManifoldAgent::GetOutputPersistentBody()
{
  return GetCellManifoldsManager()->GetOutputPersistentBody();
}
INLINE CATLiveBody * CATDeclarativeManifoldAgent::GetOutputLiveBody() const
{
 return CATLiveBody::GetLiveBody(GetOutputBody());
}

INLINE CATLiveBody * CATDeclarativeManifoldAgent::GetInputLiveBody(int iInputBody) const
{
 return CATLiveBody::GetLiveBody(GetInputBody(iInputBody));
}

INLINE CATPersistentBody * CATDeclarativeManifoldAgent::GetInputPersistentBody(int iNumInputBody)
{
  return GetCellManifoldsManager()->GetInputPersistentBody(iNumInputBody);
}
INLINE int CATDeclarativeManifoldAgent::GetNbOfInputBodies() const
{
  return GetCellManifoldsManager()->GetNbOfInputBodies();
}
INLINE CATBody * CATDeclarativeManifoldAgent::GetInputBody(int iInputBody) const
{
  return GetCellManifoldsManager()->GetInputBody(iInputBody);
}
INLINE CATSoftwareConfiguration* CATDeclarativeManifoldAgent::GetConfig() const
{
  return GetCellManifoldsManager()->GetConfig();
}
INLINE int CATDeclarativeManifoldAgent::GetPriorityWithConfig(CATSoftwareConfiguration *iConfig)
{
  return GetPriority();
}
INLINE CATGeoFactory* CATDeclarativeManifoldAgent::GetFactory()
{
  return GetCellManifoldsManager()->GetFactory();
}

INLINE CATPersistentCellInfra *CATDeclarativeManifoldAgent::GetInfra()
{
  return GetCellManifoldsManager()->GetLiveInfra();
}

INLINE const ListPOfCATCell* CATDeclarativeManifoldAgent::GetExpectedCellsForReporting()
{
  CATCellManifoldsManager* Manager = CATDeclarativeManifoldAgent::GetCellManifoldsManager();
  if (Manager)
    return Manager->GetExpectedCellsForReporting();
  else 
    return NULL;
}
INLINE void CATDeclarativeManifoldAgent::GetImpactedCellManifold(ListPOfCATCellManifold& ioImpactedCellManifolds)
{
  ioImpactedCellManifolds.RemoveAll(CATCollec::KeepAllocation);
  if(_ImpactedCellManifolds)
    ioImpactedCellManifolds.Append(*_ImpactedCellManifolds);
}
INLINE void CATDeclarativeManifoldAgent::SetAgentContext(CATDMAgentContext * ipContext)
{
  _AgentContext = ipContext;
}
INLINE CATDMAgentContext* CATDeclarativeManifoldAgent::GetAgentContext() const 
{
  return _AgentContext;
}
INLINE CATLiveBody* CATDeclarativeManifoldAgent::GetOriginalBodyForKeepManifolds() const
{
  return _AgentContext?_AgentContext->GetOriginalBodyForKeepManifolds():NULL;
}
INLINE void CATDeclarativeManifoldAgent::AppendShareDeclarativeManifold(CATDeclarativeManifold *iShareDeclarativeManifold)
{
  if(iShareDeclarativeManifold && !_ShareDeclarativeManifolds.Locate(iShareDeclarativeManifold))
    _ShareDeclarativeManifolds.Append(iShareDeclarativeManifold);
}
INLINE void CATDeclarativeManifoldAgent::GetShareDeclarativeManifolds(ListPOfCATDeclarativeManifold &ioShareDeclarativeManifolds)
{
  ioShareDeclarativeManifolds.Append(_ShareDeclarativeManifolds);
}
#endif
