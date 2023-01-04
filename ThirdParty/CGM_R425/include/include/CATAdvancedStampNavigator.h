#ifndef CATAdvancedStampNavigator_H
#define CATAdvancedStampNavigator_H

#include "CATPersistentCell.h"
#include "CATCellManifoldGroupNavigator.h"
#include "ListPOfCATCellManifold.h"
#include "ListPOfCATBoneFillet.h"
#include "CATTopDefine.h"

class CATAdvancedStampManifoldGroupAttribute;
class CATPersistentBody;
class CATDraftManifold;
class CATBoneFillet;
class CATPersistentCellInfra;
class CATGMSpecInfra;

class ExportedByPersistentCell CATAdvancedStampNavigator : public CATCellManifoldGroupNavigator
{
public:

  // Attribute Declaration
  CATCGMDeclareManifoldNavigator(CATAdvancedStampNavigator, CATCellManifoldGroupNavigator);
  
  // Constructor
  CATAdvancedStampNavigator(CATLiveBody * iLiveBody, CATCellManifoldGroup * iNetworkGroup);
  CATAdvancedStampNavigator(CATAdvancedStampNavigator * iNavigator);

  // Destructor
  virtual ~CATAdvancedStampNavigator();


  void SetEditionMode(CATBoolean iEditionMode);
  CATBoolean GetEditionMode() const;

  CATBoolean BelongsToAdvancedStamp(CATCellManifold * iCM);

  //Get
  CATOrientation      GetTopBottomOrientation(CATSoftwareConfiguration * iConfig, CATGeoFactory & iFactory);
  CATPersistentBody * CreateInputShapePBody(CATPersistentCellInfra & iInfra);
  double              GetFilletRadius(CATGeoFactory & iFactory, int iNumOperatorID=0, CATGMSpecInfra * iSpecInfra=NULL);
  CATBoolean          GetFilletRepresentation();
  void                GetDraftDirection(CATMathDirection & oDraftDirection, int iNumOperatorID=0, CATGMSpecInfra * iSpecInfra=NULL);
  CATAngle            GetDraftAngle(int iNumOperatorID=0, CATGMSpecInfra * iSpecInfra=NULL);//Degree
  double              GetHeight(CATGeoFactory & iFactory, CATSoftwareConfiguration * iConfig, int iNumOperatorID=0, CATGMSpecInfra * iSpecInfra=NULL);
  int                 GetDimensionType();
  CATBoolean          GetTrimSupportMode();
  CATBoolean          GetCurveRepresentation();

  void GetBoundingBox(CATMathBox & oBB);

  void GetAllCellManifoldList(ListPOfCATCellManifold & oAllCMList);
  void GetTopCellManifoldList(ListPOfCATCellManifold & oTopCMList);
  void GetFilletedCellManifoldList(ListPOfCATCellManifold & oFilletedCMList);
  void GetDraftedCellManifoldList(ListPOfCATCellManifold & oDraftedCMList);
  void GetClosureCellManifoldList(ListPOfCATCellManifold & oClosureCMList);

  CATDraftManifold * GetOneDraftManifold();
  CATBoneFillet    * GetOneBoneFillet();
  void               GetAllBoneFilletList(ListPOfCATBoneFillet & oAllBoneFilletList);

  // @nocgmitf
  CATAdvancedStampNavigator * GetAsAdvancedStampNavigator();

  // @nocgmitf
  virtual HRESULT GetNetworkGroup(CATCellManifoldGroup *& oNetworkGroup) const;
  
  //return TRUE if this group is modifiable with CATManifoldEditor
  // @nocgmitf
  virtual CATBoolean IsEditable() const;

protected:

private:
  CATAdvancedStampNavigator();

  CATAngle   FixDraftAngleSign(CATAngle iDraftAngle);
  CATBoolean ComputeAdvancedStampHeight(CATGeoFactory & iFactory, CATSoftwareConfiguration * iConfig, double & oHeight);
  double     ComputeSurfacicAdvancedStampHeight(CATGeoFactory & iFactory, CATSoftwareConfiguration * iConfig);
  double     ComputeVolumicAdvancedStampHeight(CATGeoFactory & iFactory, CATSoftwareConfiguration * iConfig);
  CATBoolean IsFullDomain();

private:
  CATCellManifoldGroup                   * _NetworkGroup;
  CATAdvancedStampManifoldGroupAttribute * _AdvancedStampAttr;
  CATLiveBody * _LiveBody;
  CATBoolean _EditionMode;
};

#endif
