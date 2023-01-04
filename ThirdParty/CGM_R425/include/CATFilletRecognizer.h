#ifndef CATFilletRecognizer_H
#define CATFilletRecognizer_H

#include "CATFilletManifoldCreatorBase.h"


#include "ListPOfCATDRepSeed.h"
#include "CATDRepSeedsContainer.h"
#include "CATMathInline.h"
#include "CATSurfaceRecognizer.h"

class ExportedByPersistentCell CATFilletRecognizer : public CATFilletManifoldCreatorBase
{
public:
  CATCGMDeclareManifoldAgent(CATFilletRecognizer, CATFilletManifoldCreatorBase)
	
	// Constructor
  CATFilletRecognizer();
	
  // Destructor
	virtual ~CATFilletRecognizer();

  INLINE virtual CATFilletRecognizer * GetAsFilletRecognizer();

  //virtual CATBoolean GetAdmissibleCells(CATLISTP(CATCell) &ioAdmissibleCells);
  virtual HRESULT CreateImageManifolds();
  virtual void AddCellManifoldImage(CATLISTP(CATCellManifold) &iParentCellManifolds, CATLISTP(CATCellManifold) &iChildrenManifolds, int iInfo, CATBoolean iForbidZeroInfo=TRUE);
  virtual int GetPriority();
  virtual int GetPriorityWithConfig(CATSoftwareConfiguration *iConfig);
  virtual CATBoolean IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold();
  INLINE virtual CATDeclarativeManifoldAgent* Clone();
    //Ajout QF2
  virtual CATBoolean IsTriTangent(CATLISTP(CATCellManifold) &iBoneFilletRep);
  virtual CATRibbonManifoldCreatorInfraContextUtilities * GetUtilities();

protected:

  virtual CATBoneFillet* GetRadiusAndType(CATLISTP(CATCellManifold) &iBoneFilletRep, CATLISTP(CATCellManifold) iBoneFilletSupport[2], CATPersistentBody& iPBody, ListPOfListPOfCATCellManifolds& iAllBoneAndJoint, double &ioRadius, CATSurfaceRecognizer::SurfaceType &oType);
  virtual CATBoneFillet* GetRadiusAndType(CATLISTP(CATCellManifold) &iBoneFilletRep, CATLISTP(CATCellManifold) iBoneFilletSupport[2], CATLiveBody& iLiveBody, ListPOfListPOfCATCellManifolds& iAllBoneAndJoint, double &ioRadius, CATSurfaceRecognizer::SurfaceType &oType);

  // ST5 Wk32:
  virtual void RecognizeJointAndDefineType(CATLiveBody &iLiveBody,
                                           CATGMLiveRibbonSorter &iRibbonSorter,
                                           int iJointIndex,
                                           ListPOfCATCellManifold &iJointFilletRep, 
                                           ListPOfCATCellManifold &iConnectedBoneFilletList,
                                           CATListOfInt &oResultDefineType);
  virtual void OldRecognizeJointAndDefineType(CATLiveBody &iLiveBody,
                                              ListPOfCATCellManifold &iJointFilletRep,
                                              ListPOfCATCellManifold &iConnectedBoneFilletList,
                                              CATListOfInt &oResultDefineType);

  virtual HRESULT RecognizeFilletPieces(CATBody                        & iBody, 
                                        ListPOfCATFace                 & ioFacesToBeRecognized, 
                                        CATDRepSeedsContainer          & ioFilletPiecesContainer);

  virtual void RepairBoneContextsInStepFillet(CATLiveBody              * iLiveBody,
                                              CATBoneFillet            * iBoneFillet,
                                              ListPOfCATCellManifold   & iBoneFilletRep,
                                              ListPOfCATCellManifold     ioBoneFilletSupport[2]);
  
  INLINE void AuthorizeTriTangents(CATBoolean iParam);

  //QF2 //param
  CATBoolean _TriTgtRecogAuthorized;

};

INLINE CATFilletRecognizer * CATFilletRecognizer::GetAsFilletRecognizer()
{
  return this;
}
INLINE CATDeclarativeManifoldAgent* CATFilletRecognizer::Clone()
{
  return new CATFilletRecognizer();
}

INLINE void CATFilletRecognizer::AuthorizeTriTangents(CATBoolean iParam)
{
  _TriTgtRecogAuthorized = iParam;
}

#endif
