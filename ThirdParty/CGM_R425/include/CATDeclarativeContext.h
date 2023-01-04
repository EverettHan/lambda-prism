// COPYRIGHT DASSAULT SYSTEMES 2011
//===============================================================================================================
//
// CATDeclarativeContext :
// Global context managing DRep behaviour.
// It contains specific thresholds and data to be able to filter out irrelevant behaviors, 
// such as minimal and maximal bound of the radius interval of fillets.
//
//===============================================================================================================
// Mar. 11 Creation                                                                         S. Berard
//===============================================================================================================

#ifndef CATDeclarativeContext_H
#define CATDeclarativeContext_H 

#include "CATGMModelInterfaces.h"
#include "CATCGMStream.h"
#include "CATCGMOutput.h"
#include "CATErrorDef.h"
#include "ListPOfCATBody.h"

class CATGeoFactory;

enum CATDeclarativeContextIndustry {
  // Deprecated
  CATDeclarativeContextWatch = -2,                         // Deprecated: do not use, call CATDeclarativeContextHighTech
  // --------------------------------------------------------------------------------
  // Value for User without Industry
  // --------------------------------------------------------------------------------
  CATDeclarativeContextDefault = -1,                      // Default values for CATIA Live Shape User
  // --------------------------------------------------------------------------------
  // Default System Value (not set by user)
  // --------------------------------------------------------------------------------
  CATDeclarativeContextUnknown = 0,                       // Default values for CDM initialisation, it's the same values as CATDeclarativeContextDefault
  // --------------------------------------------------------------------------------
  // Values for User with Industry
  // --------------------------------------------------------------------------------
  CATDeclarativeContextPowerTrain = 1,
  CATDeclarativeContextBiW = 2,
  CATDeclarativeContextConsumerGoods = 3,                 // !!! Values not validated yet !!!
  CATDeclarativeContextShipBuilding = 4,                  // !!! Values not validated yet !!!
  CATDeclarativeContextHighTech = 5,
  CATDeclarativeContextBuilding = 6,                      // Civil Engineering Normal Scale
  CATDeclarativeContextCivilEngineering = 7,              // Civil Engineering Large Scale
  CATDeclarativeContextMachineDesign = 8,
  CATDeclarativeContextDefeaturing = 9,                   // Defeaturing only
  CATDeclarativeContextMicroMechanics = 10,               // New in R418 / R2016x // Compatible SmallScale et NormalScale
  CATDeclarativeContextCGMInternalUse = 11,
  CATDeclarativeContextExtraLargeCivilEngineering = 12,   // Civil Engineering Extra Large Scale
  CATDeclarativeContextDefeaturingCasted = 13             // Defeaturing only
};

enum CATDeclarativeContextCompatibility {
  CATDeclarativeContextCompatibility_Unknown=-1,
  CATDeclarativeContextCompatibility_No=0,
  CATDeclarativeContextCompatibility_Yes=1,
  CATDeclarativeContextCompatibility_NeedDRep=2
};

class ExportedByCATGMModelInterfaces CATDeclarativeContext : public CATCGMVirtual
{
public :
  /**
   * @return [out, IUnknown#Release]
   */
  static CATDeclarativeContext* CATCreateDeclarativeContext(CATDeclarativeContextIndustry &iIndustry, CATSoftwareConfiguration &iConfig, CATGeoFactory *iFactory);

  /**
   * @return [out, IUnknown#Release]
   */
  static CATDeclarativeContext* CATDuplicateDeclarativeContext(CATDeclarativeContext & iDeclarativeContext);

  /**
   * Unstream method
   */
  static CATDeclarativeContext* CATLoadDeclarativeContext(CATCGMStream &ioStr, CATSoftwareConfiguration *iConfig);

  static void GetContextIndustryValues(CATDeclarativeContextIndustry iIndustry,
                                       CATSoftwareConfiguration *iConfig,
                                       CATGeoFactory *iFactory,
                                       // fillet
                                       double &oFilletMinRadius,
                                       double &oFilletMaxRadius,
                                       double &oFilletMaxOpeningAngle,
                                       double &oBitangentFilletMaxAngle,
                                       double &oTritangentFilletMinAngle,
                                       //chamfer
                                       double &oChamferMinDist,
                                       double &oChamferMaxDist,
                                       double &oChamferMinAngle,
                                       double &oChamferMaxAngle,
                                       // draft
                                       double &oDraftMinAngle,
                                       double &oDraftMaxAngle,
                                       double &oDraftNeutralMaxAngle);

  static CATBoolean IsScaleCompatible(CATDeclarativeContextIndustry iIndustry,
                                      CATSoftwareConfiguration *iConfig,
                                      CATGeoFactory *iFactory);

  // debug
  static const char *GetContextIndustryName(CATDeclarativeContextIndustry iIndustry);
  static void ForceLatestContextIndustryValuesIfActive(CATDeclarativeContextIndustry iIndustry,
                                                       CATSoftwareConfiguration *iConfig,
                                                       CATGeoFactory *iFactory,
                                                       // fillet
                                                       double &ioFilletMinRadius,
                                                       double &ioFilletMaxRadius,
                                                       double &ioFilletMaxOpeningAngle,
                                                       double &ioBitangentFilletMaxAngle,
                                                       double &ioTritangentFilletMinAngle,
                                                       //chamfer
                                                       double &ioChamferMinDist,
                                                       double &ioChamferMaxDist,
                                                       double &ioChamferMinAngle,
                                                       double &ioChamferMaxAngle,
                                                       // draft
                                                       double &ioDraftMinAngle,
                                                       double &ioDraftMaxAngle,
                                                       double &ioDraftNeutralMaxAngle);

  /**
   * AddRef
   */
  void AddRef();
   
  /**
   * Dont use delete operarand,
   * but Release()
   */
  void Release();

  void Init(CATDeclarativeContextIndustry &iIndustry, CATSoftwareConfiguration* iConfig, CATGeoFactory *iFactory = NULL);

  // Compare based on specification only (Industry)
  CATBoolean IsEqual(const CATDeclarativeContext& iOtherDeclarativeContext) const;

  // Compare based on Industry and Values
  CATBoolean operator==(const CATDeclarativeContext& iOtherDeclarativeContext) const;

  // Industry
  void GetIndustry(CATDeclarativeContextIndustry & oIndustry) const;

  // Is the context set by the User ?
  CATBoolean IsSetByUser() const;

  // ===================================
  // Set Methods
  // ===================================
  // Fillet
  HRESULT SetFilletRadiusMin(double iFilletRMin);
  HRESULT SetFilletRadiusMax(double iFilletRMax);
  HRESULT SetFilletOpeningAngleMax(double iFilletOpAMax);
  HRESULT SetBiTangentFilletMaxAngle(double iBitangentFilletMaxAngle);
  HRESULT SetTriTangentFilletMinAngle(double iTriTgtFilletAMin);

  // Chamfer
  HRESULT SetChamferDistMin(double iChamferDMin);
  HRESULT SetChamferDistMax(double iChamferDMax);
  HRESULT SetChamferAngleMin(double iChamferAMin);
  HRESULT SetChamferAngleMax(double iChamferAMax);

  // Draft
  HRESULT SetDraftAngleMin(double iDraftAMin);
  HRESULT SetDraftAngleMax(double iDraftAMax);
  HRESULT SetDraftNeutralAngleMax(double iDraftNeutralAMax);

  // ===================================
  // Get Methods
  // ===================================
  // Fillet
  void GetFilletRadiusMin(double &oFilletRMin) const;
  void GetFilletRadiusMax(double &oFilletRMax) const;
  void GetFilletOpeningAngleMax(double &oFilletOpAMax) const;
  void GetBiTangentFilletMaxAngle(double &oBitangentFilletMaxAngle) const;
  void GetTriTangentFilletMinAngle(double &oTriTgtFilletAMin) const;

  // Chamfer
  void GetChamferDistMin(double &oChamferDMin) const;
  void GetChamferDistMax(double &oChamferDMax) const;
  void GetChamferAngleMin(double &oChamferAMin) const;
  void GetChamferAngleMax(double &oChamferAMax) const;

  // Draft
  void GetDraftAngleMin(double &oDraftAMin) const;
  void GetDraftAngleMax(double &oDraftAMax) const;
  void GetDraftNeutralAngleMax(double &oDraftNeutralAMax) const;

  // ===================================
  // Stream
  // ===================================
  void    Write (CATCGMStream& os);  
  HRESULT Write (CATUnicodeString & oStringJSON) const;
  HRESULT BuildFromJSON(const CATUnicodeString & iStringJSON);

  void    Dump (CATCGMOutput& os);

  // Do not use - For Odt Scaling only
  void Scale(const double iRatio);

  // Utilitary to check whether the context is likely to be modified or not
  /*static*/ const HRESULT CheckCompatibilityWithBodies(ListPOfCATBody &iBodies);

  CATBoolean IsScaleCompatible(CATSoftwareConfiguration *iConfig, CATGeoFactory *iFactory);

  // ===================================
  // DEPRECATED, DO NOT USE
  // ===================================
  void  Load (CATCGMStream& os); // deprecated, use CATLoadDeclarativeContext
  static CATDeclarativeContext* CATCreateDeclarativeContext(CATDeclarativeContextIndustry &iIndustry); // Deprecated, use create with Config
  static CATDeclarativeContext* CATCreateDeclarativeContext(CATDeclarativeContextIndustry &iIndustry, CATSoftwareConfiguration &iConfig); // Deprecated, use create with Config and Factory
  // Check if the factory scaling is compatible with this Context
  HRESULT IsCompatibleWith(const CATGeoFactory *iTargetFactory) const;

protected :
  CATDeclarativeContext(CATDeclarativeContextIndustry &iIndustry); // Deprecated, use create with Config
  CATDeclarativeContext(CATDeclarativeContextIndustry &iIndustry, CATSoftwareConfiguration &iConfig, CATGeoFactory *iFactory = NULL);
  CATDeclarativeContext(CATDeclarativeContext & iDeclarativeContext);
  CATDeclarativeContext(CATCGMStream& os);

   /**
   * @return [out, IUnknown#Release]
   */
  virtual ~CATDeclarativeContext();


private :
  short _RefCount;
  CATDeclarativeContextIndustry _Industry;

  // Fillet
  double _FilletRMin;
  double _FilletRMax;
  double _FilletOpAMax;
  double _BiTgtAMax;
  double _TriTgtAMin;

  // Chamfer
  double _ChamferDMin;
  double _ChamferDMax;
  double _ChamferAMin;
  double _ChamferAMax;

  // Draft
  double _DraftAMin;
  double _DraftAMax;
  double _DraftNeutralAMax;

  CATDeclarativeContext& operator=(const CATDeclarativeContext & iOperator);
};

// CompatibilityCheck
static HRESULT IsContextCompatible(CATDeclarativeContext &iContext, ListPOfCATBody &iBodies);

#endif
