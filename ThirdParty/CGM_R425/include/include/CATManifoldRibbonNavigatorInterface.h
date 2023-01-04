#ifndef CATManifoldRibbonNavigatorInterface_H
#define CATManifoldRibbonNavigatorInterface_H

#include "CATGMModelInterfaces.h"
#include "CATManifoldNavigator.h"
#include "ListPOfCATCellManifold.h"
#include "CATMathDef.h"
#include "CATErrorDef.h"
#include "CATFilletDefine.h"
#include "CATChamferDefine.h"
#include "CATTopDefine.h"

class CATHVertex;
class CATMathPoint;
class CATLiveBody;
class CATManifoldParameter;
class CATMathDirection;
class CATBody;

// ---- Begin of Temporary code --------------
// To activate the new Natural Shape code for Halo,
// remove the // of the next line.
// #define HALO_NEW_PARAM_NS 1
// ---- End of Temporary code ----------------


class ExportedByCATGMModelInterfaces CATManifoldRibbonNavigatorInterface : public CATManifoldNavigator
{
public:

  typedef enum 
  {
    Undef = 0,
    BoneFillet = 1, 
    JointFillet = 2, 
    BoneChamfer = 3,
    DraftManifold = 4 //DSH1 July 2016 Navigator UI for DraftManifold
  }
  CATRibbonType;

  virtual HRESULT GetAllCellManifolds(CATLISTP(CATCellManifold)& oCellManifolds) const=0;

  virtual HRESULT GetRibbonType(CATRibbonType& oType) const=0;

  virtual HRESULT GetFilletRadius(CATPositiveLength& oRadius) const=0;

  virtual HRESULT GetFilletMinMaxRadius(CATPositiveLength& oMinRadius, CATPositiveLength& oMaxRadius) const=0;

  virtual HRESULT GetFilletConvexity(CATTopConvexity& oConvexity) const = 0;

  virtual HRESULT GetSupports(ListPOfCATCellManifold oLeftAndRightSupport[2]) const=0;

  virtual HRESULT GetContexts(ListPOfCATCellManifold& oContexts) const=0;

  virtual HRESULT GetFilletRadiusType(CATFilletRadiusType &oRadiusType) const = 0;

  virtual HRESULT GetFilletSectionType(CATFilletSectionType &oSectionType) const = 0;

  virtual HRESULT GetDraftAngle(CATAngle &oDraftAngle) const = 0;

  virtual HRESULT GetDraftPullingDirection(CATMathDirection &oDraftPullingDirection) const = 0;

  virtual HRESULT IsBoneFilletConstant(CATBoolean & oConstant) const = 0;

  virtual HRESULT IsBoneFilletVariable(CATBoolean & oVariable) const = 0;

  virtual HRESULT GetChamferParameters(double &oLeftValue, double &oRightValue, CATChamferType &oType ) const = 0;

  virtual HRESULT EstimateHalo(CATGeoFactory& iFactory, CATSoftwareConfiguration& iConfig, const CATMathPoint& iLocation, CATCurve*& oHalo, CATPositiveLength& oRadius, double& oRatio, CATPositiveLength& oDistance, CATBody *oHaloBody=NULL) const = 0; // oRadius is Radius or ChordLength depending on riboon type, output values are rounded

  virtual HRESULT EstimateHalo(CATGeoFactory& iFactory, CATSoftwareConfiguration& iConfig, const CATMathPoint& iLocation, CATCurve*& oHalo, double& oRatio, CATPositiveLength& oDistance, CATBody *oHaloBody=NULL) const = 0; // Deprecated, use previous method

  virtual HRESULT EstimateHalo(CATGeoFactory& iFactory, CATSoftwareConfiguration& iConfig, const CATManifoldParameter& iParameter, CATCurve*& oHalo, CATBody *oHaloBody=NULL) const = 0;

  virtual HRESULT EstimateHalo(CATGeoFactory& iFactory, CATSoftwareConfiguration& iConfig, const CATHVertex& iLocation, CATCurve*& oHalo, CATBody *oHaloBody=NULL) const = 0;

  virtual HRESULT EstimateRHalo(CATGeoFactory &iFactory, CATSoftwareConfiguration &iConfig, double *iRatio, CATPositiveLength &oDistance, CATCurve *&oHalo, CATPositiveLength &oRadius, CATMathPoint *oLocation=NULL, CATBody *oHaloBody=NULL) const = 0;

  virtual HRESULT EstimateDHalo(CATGeoFactory &iFactory, CATSoftwareConfiguration &iConfig, CATPositiveLength *iDistance, double &oRatio, CATCurve *&oHalo, CATPositiveLength &oRadius, CATMathPoint *oLocation=NULL, CATBody *oHaloBody=NULL) const = 0;

  virtual CATLiveBody *GetLiveBody() const = 0;

  //-------------------------------------------------------------------------------------------------------
  CATManifoldRibbonNavigatorInterface(); 
  CATCGMNewClassArrayDeclare;      // Pool allocation
  virtual ~CATManifoldRibbonNavigatorInterface();
  virtual void Dump(CATCGMOutput& Output);
  //-------------------------------------------------------------------------------------------------------
  //virtual HRESULT GetBoneExtremityParameters(CATMathPoint & oStartPosition, CATMathPoint & oEndPosition, CATPositiveLength & oStartRadius, CATPositiveLength & oEndRadius, CATAngle & oStartAngle, CATAngle & oEndAngle) const = 0;

private:
  CATManifoldRibbonNavigatorInterface* GetAsRibbonNavigatorInterface();  

};


#endif
