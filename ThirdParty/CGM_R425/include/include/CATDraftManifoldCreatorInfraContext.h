#ifndef CATDraftManifoldCreatorInfraContext_H
#define CATDraftManifoldCreatorInfraContext_H


#include "CATDraftManifoldCreatorBase.h"
#include "CATCGMNewArray.h"

#include "ListPOfCATGMLiveContextualFeatureFollowers.h"
#include "CATCGMJournalList.h"
#include "ListPOfCATCell.h"
#include "ListPOfCATFace.h"

class CATRibbonManifoldCreatorInfraContextUtilities;
class CATGMLiveDraftPiece;
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
class ExportedByPersistentCell LSODraftRibbon
{
 public:
   LSODraftRibbon();
   LSODraftRibbon(double iDraftAngle, const ListPOfCATFace &iFacesToDraft);
   LSODraftRibbon( const LSODraftRibbon *iRib);
   ~LSODraftRibbon();

   double GetDraftAngle() {return _DraftAngle;}
   void GetFacesToDraft(ListPOfCATFace &oFacesToDraft) ;
private:
   double _DraftAngle;
   ListPOfCATFace   _FacesToDraft;
};
//----------------------------------------------------------------------------------------------------------
class ExportedByPersistentCell LSODraftDomain
{
 public:
   LSODraftDomain();
   LSODraftDomain(const CATMathDirection &iPullDir, int iNRib, LSODraftRibbon** iRib, const ListPOfCATFace &iNeutralFaces);
   LSODraftDomain(const LSODraftDomain* iDomain);
   ~LSODraftDomain();

   void GetPullingDirection(CATMathDirection &oPullDir);
   void GetNeutralFaces(ListPOfCATFace &oNeutralFaces);
   int GetNbRibbons() {return _nRib;}
   LSODraftRibbon* GetRib(int iIndex);
 private:
   CATMathDirection _PullingDirection;
   ListPOfCATFace   _NeutralFaces;
   LSODraftRibbon**  _pRibbons;
   int        _nRib;
};
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
class ExportedByPersistentCell CATDraftManifoldCreatorInfraContext : public CATDraftManifoldCreatorBase 
{
public:
  CATCGMDeclareManifoldAgent(CATDraftManifoldCreatorInfraContext, CATDraftManifoldCreatorBase);
	
	// Constructor
  CATDraftManifoldCreatorInfraContext();
	
  // Destructor
	virtual ~CATDraftManifoldCreatorInfraContext();

  virtual CATBoolean GetAdmissibleCells(CATLISTP(CATCell) &ioAdmissibleCells);
  void SetDraftManifoldFollowers(ListPOfCATGMLiveContextualFeatureFollowers &iDraftFollowers,CATListPV &iMatchedRibbons,ListPOfCATCell &iGlobalFacesToDraft);
  void SetCreationJournal(CATCGMJournalList* iJournal, int iNumDomains, LSODraftDomain** iDomains);

  virtual HRESULT CreateImageManifolds();
  virtual void AddCellManifoldImage(CATLISTP(CATCellManifold) &iParentCellManifolds, CATLISTP(CATCellManifold) &iChildrenManifolds, int iInfo, CATBoolean iForbidZeroInfo=TRUE);

  virtual int GetPriority();
  virtual CATBoolean IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold();
  INLINE virtual CATDeclarativeManifoldAgent* Clone();

  CATRibbonManifoldCreatorInfraContextUtilities *GetUtilities();

  INLINE virtual CATDraftManifoldCreatorInfraContext *GetAsDraftManifoldCreatorInfraContext();

protected:
  virtual HRESULT SortFacesImplementation(ListPOfCATFace &iFacesToRecognize, ListPOfCATDRepSeed &oRibbonPieces);

private: 

  CATGMLiveDraftPiece* CreateDraftPiece( ListPOfCATFace &iUnAffectedDraftFaces
                                        ,ListPOfCATFace &iDraftFaces
                                        ,ListPOfCATFace &iNeutralFaces
                                        ,const CATMathDirection& iPullDir
                                        ,const double &iAngle);

  
void GetNeutralFaces(CATBody* &ipBody, const ListPOfCATFace &iDraftFaces,ListPOfCATFace &oNeutralFaces);//DSH1 Aug 2018

void PropagateFaces(CATGeoFactory * iFactory,
                    CATTopData * iTopData,
                    CATBody * iBody,
                    CATLISTP(CATFace) * iInitialFaces,
                    CATLISTP(CATFace) &oPropagatatedFaces,
                    const CATLISTP(CATFace) &iStoppingFaces);//DSH1 Oct 2021

  CATCGMJournalList _LocalCellManifoldJournal;
  //twin list
  ListPOfCATGMLiveContextualFeatureFollowers _DraftManifoldFollowers;
  CATListPV _DraftRibbons;//CATListPV because we haven't access to CATDynDraftRibbon
  ListPOfCATCell _GlobalFacesToDraft;

  CATRibbonManifoldCreatorInfraContextUtilities *_InfraContextUtilities;
  CATCGMJournalList* _Journal;
  LSODraftDomain**  _pDomains;
  int        _nbDomain;
};

INLINE CATDeclarativeManifoldAgent* CATDraftManifoldCreatorInfraContext::Clone()
{
  return new CATDraftManifoldCreatorInfraContext();
}

INLINE CATDraftManifoldCreatorInfraContext *CATDraftManifoldCreatorInfraContext::GetAsDraftManifoldCreatorInfraContext()
{
 return this;
}

#endif
