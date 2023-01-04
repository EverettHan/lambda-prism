#ifndef CATJointFillet_h
#define CATJointFillet_h

// COPYRIGHT DASSAULT SYSTEMES  2007

#include "CATContextualManifold.h"
#include "ListPOfCATBoneFillet.h"
#include "ListPOfListPOfCATCellManifolds.h"
#include "CATSoftwareConfiguration.h"
#include "ListPOfCATFace.h"
#include "CATJointManifold.h"

class CATLiveBody;
class CATBoneFillet;
class CATExtTopOperator;
class CATGMSpecInfra;

#include "YI00IMPL.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByYI00IMPL IID IID_CATJointFillet ;
#else
extern "C" const IID IID_CATJointFillet ;
#endif

//class ExportedByYI00IMPL CATJointFillet : public CATContextualManifold
class ExportedByYI00IMPL CATJointFillet : public CATJointManifold
{
  CATDeclareInterface;

public:
  
  /*virtual void Set(const ListPOfCATCellManifold &iRepresentation,
                   const ListPOfCATCellManifold &iConnectedCellManifold,
                   const CATListOfInt           &iType) = 0;*/

  virtual HRESULT JointFilletShapeAnalysis(CATLiveBody &iLiveBody, CATBoneFillet &iSrcBone, int &oShape, 
                                           ListPOfCATBoneFillet &oOtherBonesWithSameConvexity, 
                                           ListPOfCATBoneFillet &oOtherBonesWithDifferentConvexity,
                                           ListPOfCATBoneFillet &oOtherBonesWithSameType, 
                                           ListPOfCATBoneFillet &OtherBonesWithDifferentRType,
                                           ListPOfCATBoneFillet &oOtherBonesWithSameRadius, 
                                           ListPOfCATBoneFillet &OtherBonesWithDifferentRadius,
                                           ListPOfCATBoneFillet &oOtherBonesWithSameSpecs, 
                                           ListPOfCATBoneFillet &OtherBonesWithDifferentSpecs,
                                           int                   iNumOperatorId,
                                           CATGMSpecInfra       *iSpecInfra) const = 0;

  virtual HRESULT PropagateFrom(CATLiveBody          &iLiveBody, 
                                CATBoneFillet        &iSrcBoneFeature, 
                                ListPOfCATBoneFillet &oBoneToPropagateFromCurrentJoin,
                                ListPOfCATBoneFillet &oBoneNOTToPropagateFromCurrentJoin,
                                CATBoolean           &oStopOnJoint,
                                int                   iNumOperatorId,
                                CATGMSpecInfra       *iSpecInfra,
                                CATSoftwareConfiguration *iConfig,
                                CATBoolean            iMinPropagation = FALSE) const = 0;

  virtual HRESULT PropagateMerge(CATLiveBody          &iLiveBody, 
                                CATBoneFillet        &iSrcBoneFeature,
                                CATBoolean           &iSameRadiusOnly,
                                CATJointFillet  & iSrcJoint, 
                                ListPOfCATBoneFillet &oBoneToPropagateFromCurrentJoin,
                                ListPOfCATBoneFillet &oBoneNOTToPropagateFromCurrentJoin,
                                CATBoolean           &oStopOnJoint,
                                int                   iNumOperatorId,
                                CATGMSpecInfra       *iSpecInfra,
                                CATSoftwareConfiguration *iConfig,
                                ListPOfCATFace        UserRestrictionFaces, 
                                CATBoolean &LiveEditorRedoRadiusLess,
                                int           scenario=0) const = 0;

  virtual HRESULT PropagateDefeature(CATLiveBody          &iLiveBody,
                                        CATBoneFillet        &iSrcBoneFeature,
                                        CATBoolean           &iSameRadiusOnly,
                                        CATJointFillet  & iSrcJoint,
                                        ListPOfCATBoneFillet &oBoneToPropagateFromCurrentJoin,
                                        CATBoolean &LiveEditorRedoRadiusLess,
                                        int                   iNumOperatorId,
                                        CATGMSpecInfra       *iSpecInfra,
                                        ListPOfCATFace  UserRestrictionFaces,
                                        CATSoftwareConfiguration *iConfig) const = 0;
  virtual HRESULT AddBoneFilletIfTypeGreaterOrEqual(CATLiveBody &iLiveBody,
                                                    CATBoneFillet& iSrcBoneFeature, 
                                                    CATJointFillet& iSrcJointFeature, 
                                                    int NumberOfContexts, 
                                                    CATGMSpecInfra * iSpecInfra, 
                                                    int iNumOperatorId, 
                                                    ListPOfCATBoneFillet& OtherBones, 
                                                    ListPOfCATBoneFillet& oBoneToPropagateFromCurrentJoin, 
                                                    CATSoftwareConfiguration *iConfig,
                                                    CATBoolean& LiveEditorRedoRadiusLess) const = 0; 

  virtual HRESULT PropagateToSameRadius(CATLiveBody          &iLiveBody,
                                        CATBoneFillet        &iSrcBoneFeature,
                                        CATBoolean           &iSameRadiusOnly,
                                        ListPOfCATBoneFillet &oBoneToPropagateFromCurrentJoin,
                                        int                   iNumOperatorId,
                                        CATGMSpecInfra       *iSpecInfra,
                                        CATSoftwareConfiguration *iConfig) const = 0;

  virtual HRESULT HasVariableContext() const = 0;

  // only returns connected ribbons by type, not supports
  virtual HRESULT GroupContextsByType(ListPOfListPOfCATCellManifolds &oGroupsOfCtxsByType, CATListOfInt *oType = NULL) const = 0;

  virtual void GetConnectedRibbons(ListPOfCATCellManifold &oConnectedRibbons, CATListOfInt *oConnectedRibbonsType = NULL) const = 0;
  virtual void GetJointSupports(ListPOfCATCellManifold &oJointSupports) const = 0;

};
  
//CATDeclareHandler(CATJointFillet,CATContextualManifold);
CATDeclareHandler(CATJointFillet,CATJointManifold);

#endif
