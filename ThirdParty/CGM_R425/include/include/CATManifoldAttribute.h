#ifndef CATManifoldAttribute_h
#define CATManifoldAttribute_h

// COPYRIGHT DASSAULT SYSTEMES  2007

#include "CATIACGMLevel.h"
#include "CATCGMNewArray.h"
#include "CATCGMStreamAttribute.h"
#include "ListPOfCATManifoldAttribute.h"
#include "ListPOfCATManifoldParameter.h"
#include "CATICGMObject.h"

class CATCloneManager;
class CATTransfoManager;
class CATLiveBody;
class CATDeclarativeManifoldAgent;
class CATCellManifoldsManager;
class CATCellManifoldGroup;
class CATTopData;
class CATCellManifoldGroupCGM;
class CATCellManifoldGroupNavigator;
class CATLISTP(CATCellManifoldGroup);
class CATExtrusionManifoldAttribute;
class CATPadPocketManifoldAttribute;
class CATHoleManifoldAttribute;
class CATSlotManifoldAttribute;
class CATOffsetManifoldAttribute;
class CATOffsetManifoldSpecificationAttribute;
class CATOffsetReferenceManifoldAttribute;
class CATOffsetLateralFacesManifoldAttribute;
class CATPatternManifoldAttribute;
class CATPatternManifoldSpecificationAttribute;
class CATPatternReferenceManifoldAttribute;
class CATBRepCopyManifoldAttribute;
class CATBRepCopyManifoldSpecificationAttribute;
class CATCutoutManifoldAttribute;
class CATDraftManifoldAttribute;
class CATLogoManifoldAttribute;
class CATGeoFactory;
class CATInstancesManifoldSpecificationAttribute;
class CATInstancesManifoldAttribute;
class CATInstancesReferenceManifoldAttribute;
class CATThreadSpecParams;
class CATGroupSpecParams;
class CATManifoldGroupAttribute;
class CATGMSHMLiveManifoldAttribute;
class CATGMCrtLiveManifoldCellAttribute;
class CATManifoldAttributeSample;
class CATAdvancedStampManifoldGroupAttribute;
class CATCellManifoldGroupCarrier;
class CATVolatileDraftGroupManifoldAttribute;
class CATThinWallDraftGroupManifoldAttribute;
class CATThinWallDraftSideManifoldAttribute;
class CATPairingManifoldAttribute;
class CATWallManifoldAttribute;
class CATBendManifoldAttribute;

#include "CATGMModelInterfaces.h"

class ExportedByCATGMModelInterfaces CATManifoldAttribute : public CATCGMStreamAttribute
{
public:
  CATCGMDeclareAttribute (CATManifoldAttribute,CATCGMStreamAttribute); 

  CATManifoldAttribute(); 
  virtual ~CATManifoldAttribute();
  CATCGMNewClassArrayDeclare;      // Pool allocation

  virtual CATManifoldAttribute* CreateImageManifoldAttribute(CATLiveBody &iLiveBody, CATLISTP(CATManifoldAttribute) &iParentManifoldAttributes) const =0;

  virtual CATManifoldAttribute* Clone(CATCloneManager& iCloner) const =0;
  virtual void Move3D(CATTransfoManager& iTransfo) =0;
  virtual void GetColor(int &oR, int &oG, int &oB) const =0;

  virtual CATManifoldAttribute* CloneAndMove3D(CATTransfoManager& iTransfo) const;
  virtual HRESULT GenerateParameters (CATTopData * iTopData, CATCellManifoldGroupCGM * iGroup, ListPOfCATManifoldParameter &oManifoldParameters) const;

  virtual CATBoolean AreSpecificDatasImagesEqualToParents(CATCellManifoldGroupCarrier * iCellManifoldGroupCarrier)const;

  virtual HRESULT CreateImageAttribute(const CATLISTP(CATCellManifoldGroup) & iParentGroups, 
                                        const CATCellManifoldGroup          & iImageCellManifoldGroup, 
                                        CATCellManifoldsManager             & iCellManifoldsManager,
                                        CATManifoldAttribute               *& oImageManifoldAttribute ) const;

  virtual void Dump(CATCGMOutput& iWhereToWrite) const;

  virtual CATBoolean IsEquivalentTo(const CATManifoldAttribute &iOtherManifoldAttribute, CATGeoFactory * iFactory) const;
  virtual CATBoolean HaveSameType(CATManifoldAttribute &iOtherManifoldAttribute) const;

  virtual CATCellManifoldGroupNavigator * CreateGroupNavigator(CATLiveBody * iLiveBody, const CATTopData & iTopData, CATCellManifoldGroup * iGroup) const;

  virtual void GetLinksCGM(CATLISTP(CATICGMObject) &oLinks,
                           CATCGMLinkType           iLinkType,
                           CATRCOLL(int)*           oSharedStatus,
                           CATLISTV(CATString)*     oLinksString);

  // Check integrity, coherence between the Attribute and the topology.
  virtual HRESULT CheckConsistency(const CATLiveBody * iLiveBody, const CATCellManifoldGroup &iOwningGroup, CATCGMOutput *oDbgTraces=NULL) const;

  virtual CATExtrusionManifoldAttribute *GetAsExtrusionManifoldAttribute();
  virtual CATPadPocketManifoldAttribute *GetAsPadPocketManifoldAttribute();  
  virtual CATHoleManifoldAttribute *GetAsHoleManifoldAttribute();  
  virtual CATSlotManifoldAttribute *GetAsSlotManifoldAttribute();
  virtual CATInstancesManifoldSpecificationAttribute *GetAsInstancesManifoldSpecificationAttribute();
  virtual CATInstancesManifoldAttribute *GetAsInstancesManifoldAttribute();
  virtual CATInstancesReferenceManifoldAttribute *GetAsInstancesReferenceManifoldAttribute();
  virtual CATOffsetManifoldAttribute *GetAsOffsetManifoldAttribute();  
  virtual CATOffsetManifoldSpecificationAttribute *GetAsOffsetManifoldSpecificationAttribute();
  virtual CATOffsetReferenceManifoldAttribute *GetAsOffsetReferenceManifoldAttribute();
  virtual CATOffsetLateralFacesManifoldAttribute *GetAsOffsetLateralFacesManifoldAttribute();
  virtual CATPatternManifoldAttribute *GetAsPatternManifoldAttribute();
  virtual CATPatternManifoldSpecificationAttribute *GetAsPatternManifoldSpecificationAttribute();
  virtual CATPatternReferenceManifoldAttribute *GetAsPatternReferenceManifoldAttribute();
  virtual CATBRepCopyManifoldAttribute *GetAsBRepCopyManifoldAttribute();
  virtual CATBRepCopyManifoldSpecificationAttribute *GetAsBRepCopyManifoldSpecificationAttribute();
  virtual CATCutoutManifoldAttribute* GetAsCutoutManifoldAttribute();
  virtual CATDraftManifoldAttribute* GetAsDraftManifoldAttribute();
  virtual CATLogoManifoldAttribute* GetAsLogoManifoldAttribute();
  virtual CATGroupSpecParams * GetAsGroupSpecParams() const;
  virtual CATThreadSpecParams * GetAsThreadSpecParams() const;
  virtual CATManifoldGroupAttribute * GetAsManifoldGroupAttribute();
  virtual CATGMSHMLiveManifoldAttribute *GetAsGMSHMLiveManifoldAttribute();
  virtual CATGMCrtLiveManifoldCellAttribute *GetAsGMCrtLiveManifoldCellAttribute();
  virtual CATManifoldAttributeSample *GetAsManifoldAttributeSample() const;
  virtual CATAdvancedStampManifoldGroupAttribute *GetAsAdvancedStampManifoldGroupAttribute();
  virtual CATVolatileDraftGroupManifoldAttribute *GetAsVolatileDraftGroupManifoldAttribute();
  virtual CATThinWallDraftGroupManifoldAttribute *GetAsThinWallDraftGroupManifoldAttribute();
  virtual CATThinWallDraftSideManifoldAttribute *GetAsThinWallDraftSideManifoldAttribute();
  virtual CATPairingManifoldAttribute *GetAsPairingManifoldAttribute();
  virtual CATWallManifoldAttribute *GetAsWallManifoldAttribute();
  virtual CATBendManifoldAttribute *GetAsBendManifoldAttribute();

// ----------------------------------------------------------------------------
  // Do not use
// ----------------------------------------------------------------------------
  virtual CATManifoldAttribute* CloneWithSameLinks(CATCloneManager& iCloner) const; // Compatibility method. Do not use. Should not be necessary. To be removed.

protected:
  void CloneLinks(CATCloneManager& iCloneManager, CATManifoldAttribute& iCloned) const;

  virtual CATManifoldAttribute* CreateImageAttribute(const CATLISTP(CATCellManifoldGroup) &iParentGroups, 
                                                     const CATCellManifoldGroup           &iImageCellManifoldGroup, 
                                                     CATCellManifoldsManager &iCellManifoldsManager) const;

  virtual HRESULT CheckImageValidity( const CATLISTP(CATCellManifoldGroup) &iParentGroups, const CATCellManifoldGroup & iImageCellManifoldGroup, CATCellManifoldsManager &iCellManifoldsManager) const;
};

#endif

