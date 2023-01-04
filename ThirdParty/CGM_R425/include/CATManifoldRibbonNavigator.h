#ifndef CATManifoldRibbonNavigator_H
#define CATManifoldRibbonNavigator_H

#include "CATPersistentCell.h"

#include "CATTopDefine.h"
#include "CATCollecRoot.h"
#include "CATMathOBBCloud.h"   
#include "CATCellManifoldGroupNavigator.h"
#include "CATListOfShort.h"
#include "ListPOfCATCellManifold.h"
#include "ListPOfCATCellManifoldGroup.h"
#include "CATLISTP_CATMathTransformation.h"
#include "CATCollec.h"
#include "CATDRepNavigator.h"
#include "ListPOfCATCellManifoldPatternAdvancedNavigator.h"
#include "CATManifoldRibbonNavigatorInterface.h"
#include "CATPatternType.h"
#include "CATVariationalPatternParameters.h"
#include "CATPatternActivationStatus.h"
#include "ListPOfCATDeclarativeManifold.h"
#include "CATFilletDefine.h"
#include "CATChamferDefine.h"
#include "CATTopDefine.h"

class CATLiveBody;
class CATCellManifold;
class CATLISTP(CATCellManifold);
class CATCellManifoldGroup;
class CATPatternManifoldSpecificationAttribute;
class CATMathTransformation;
class CATMathLine;
class CATLISTPV;
class CATCellHashTable;
class CATCGMHashTableWithAssoc;
class CATManifoldAttribute;
class CATManifoldParameter;
class CATGeometry;
class CATCellManifoldPatternAdvancedNavigator;
class CATCellManifoldHashTableWithAttributeAssoc;
class CATCell;
class CATLISTP(CATCell);
class CATMathPoint;
class CATBody;

class ExportedByPersistentCell CATManifoldRibbonNavigator : public CATManifoldRibbonNavigatorInterface
{
public:

  // Constructor
  CATManifoldRibbonNavigator();
  CATManifoldRibbonNavigator(CATLiveBody* iLiveBody, CATDeclarativeManifold* iDM); 
  CATManifoldRibbonNavigator(CATDRepNavigator * iDrepNavigator, CATDeclarativeManifold* iDM); 
  CATManifoldRibbonNavigator(CATManifoldRibbonNavigator * iRibbonNavigator);

  //-------------------------------------------------------------------------------------------------------
  // Surcharge du new/delete
  //-------------------------------------------------------------------------------------------------------
  CATCGMDeclareManifoldNavigator(CATManifoldRibbonNavigator, CATManifoldRibbonNavigatorInterface);

  // Destructor
  virtual ~CATManifoldRibbonNavigator();

  // @nocgmitf
  CATManifoldRibbonNavigator * GetAsRibbonNavigator();

  //-------------------------------------------------------------------------------------------------------
  // Options
  //-------------------------------------------------------------------------------------------------------
  void SetEditionMode(CATBoolean iEditionMode = TRUE);

  //-----------------------------------------------------
  virtual HRESULT GetRibbonType(CATRibbonType& oType) const;
  virtual HRESULT GetFilletRadius(CATPositiveLength& oRadius) const;
  virtual HRESULT GetFilletRadius(CATPositiveLength& oRadius, CATFilletType& oFilletType) const;
  virtual HRESULT GetFilletMinMaxRadius(CATPositiveLength& oMinRadius, CATPositiveLength& oMaxRadius) const;
  virtual HRESULT GetFilletConvexity(CATTopConvexity& oConvexity) const;
  virtual HRESULT GetSupports(ListPOfCATCellManifold oLeftAndRightSupport[2]) const;
  virtual HRESULT GetContexts(ListPOfCATCellManifold& oContexts) const;
  virtual HRESULT GetFilletRadiusType(CATFilletRadiusType &oRadiusType) const;
  virtual HRESULT GetFilletSectionType(CATFilletSectionType &oSectionType) const;
  virtual HRESULT IsBoneFilletConstant(CATBoolean & oConstant) const;
  virtual HRESULT IsBoneFilletVariable(CATBoolean & oVariable) const;
  virtual HRESULT GetDraftAngle(CATAngle &oDraftAngle) const;
  virtual HRESULT GetDraftPullingDirection(CATMathDirection &oDraftPullingDirection) const;
  // Returns E_FAIL when called on a constant-radius fillet or for other error conditions.
  //virtual HRESULT GetBoneExtremityParameters(CATMathPoint & oStartPosition, CATMathPoint & oEndPosition, CATPositiveLength & oStartRadius, CATPositiveLength & oEndRadius, CATAngle & oStartAngle, CATAngle & oEndAngle) const;

  virtual HRESULT GetDeclarativeType(CATDeclarativeType &oType) const;
  
  // @nocgmitf
  virtual void Dump(CATCGMOutput& Output);

 // // @nocgmitf
 // //-------------------------------------------------------------------------------------
 // HRESULT CheckModel(int & oError);

  //-------------------------------------------------
  //     Methodes traitants des Cell Manifolds  
  //-------------------------------------------------

  // Renvoie toutes les CellManifolds / Cell du pattern
  // (used by appli)
  //----------------------------------------------------
  // @nocgmitf
  virtual HRESULT GetAllCellManifolds(CATLISTP(CATCellManifold)& oCellManifolds) const;
  // @nocgmitf
  virtual HRESULT GetCells(ListPOfCATCell& oCells) const;

  // ---- CGM Internal use only ----
  // @nocgmitf
  INLINE CATDeclarativeManifold * GetDeclarativeManifoldRibbon() const;
  
  // @nocgmitf
  INLINE CATLiveBody * GetLiveBody() const;

  // @nocgmitf
  virtual HRESULT GetChamferParameters(double &oLeftValue, double &oRightValue, CATChamferType &oType) const;

  // @nocgmitf
  HRESULT EstimateRHalo(CATGeoFactory &iFactory, CATSoftwareConfiguration &iConfig, double *iRatio, CATPositiveLength &oDistance, CATCurve *&oHalo, CATPositiveLength &oRadius, CATMathPoint *oLocation=NULL, CATBody *oHaloBody=NULL) const ;
  // @nocgmitf                                                           
  HRESULT EstimateDHalo(CATGeoFactory &iFactory, CATSoftwareConfiguration &iConfig, CATPositiveLength *iDistance, double &oRatio, CATCurve *&oHalo, CATPositiveLength &oRadius, CATMathPoint *oLocation=NULL, CATBody *oHaloBody=NULL) const ;
  // @nocgmitf                                                           
  HRESULT EstimateHalo(CATGeoFactory &iFactory, CATSoftwareConfiguration &iConfig, const CATMathPoint &iLocation, CATCurve *&oHalo, CATPositiveLength &oRadius, double &oRatio, CATPositiveLength &oDistance, CATBody *oHaloBody=NULL) const ;
  // @nocgmitf                                                           
  HRESULT EstimateHalo(CATGeoFactory &iFactory, CATSoftwareConfiguration &iConfig, const CATMathPoint &iLocation, CATCurve *&oHalo, double &oRatio, CATPositiveLength &oDistance, CATBody *oHaloBody=NULL) const ;
  // @nocgmitf                                                           
  HRESULT EstimateHalo(CATGeoFactory &iFactory, CATSoftwareConfiguration &iConfig, const CATManifoldParameter &iParameter, CATCurve *&oHalo, CATBody *oHaloBody=NULL) const;
  // @nocgmitf                                                           
  HRESULT EstimateHalo(CATGeoFactory &iFactory, CATSoftwareConfiguration &iConfig, const CATHVertex &iLocation, CATCurve *&oHalo, CATBody *oHaloBody=NULL) const;
  // @nocgmitf 
  HRESULT ReconvergeHaloOnRadius(CATGeoFactory &iFactory, CATSoftwareConfiguration &iConfig, double &iRadiusValue, const CATMathPoint &iLocation, CATCurve *&oHalo) const;

  //-------------------------------------------------
  //   Stream / Unstream 
  //-------------------------------------------------

  // @nocgmitf
  //-------------------------------------------------------------------------------------------------
  void Stream(CATCGMStream& ioStr,CATGeoFactory * iFactory) const;
  void UnStream(CATCGMStream& ioStr,CATGeoFactory * iFactory);

protected:

  void Init(CATLiveBody* iLiveBody, CATDeclarativeManifold* iDM);
  void EndInit();


protected:
  CATLiveBody*            _LiveBody;
  CATDeclarativeManifold* _DeclarativeManifold;
  CATBoolean              _EditionMode;

};

// INLINE Methods
// --------------------------
// @nocgmitf
INLINE CATDeclarativeManifold * CATManifoldRibbonNavigator::GetDeclarativeManifoldRibbon() const {
  return _DeclarativeManifold; }

// @nocgmitf
INLINE CATLiveBody * CATManifoldRibbonNavigator::GetLiveBody() const {
  return _LiveBody; }

// --------------------------------------
// CATCreateCellManifoldRibbonNavigator
// --------------------------------------
// @nocgmitf
ExportedByPersistentCell CATManifoldRibbonNavigator * CATCreateManifoldRibbonNavigator(/*const CATTopData     & iData,*/
                                                                                       CATLiveBody          * iLiveBody,
                                                                                       CATDeclarativeManifold * iDM); 


#endif
