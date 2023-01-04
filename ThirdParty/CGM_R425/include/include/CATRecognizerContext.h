// COPYRIGHT DASSAULT SYSTEMES 2010
//===============================================================================================================
//
// CATRecognizerContext :
//  Informations for the surface recognizer operator given by user
//
//===============================================================================================================
// Given informations :
// For all surfaces :
// double _LinearTol : Linear tolerance used for all length tests
// double _AngularTol  : Angular tolerance used for all angle tests
// For fillets
// double _FilletRMin : Minimal bound of the radius interval of the required fillet
// double _FilletRMax : Maximal bound of the radius interval of the required fillet
// double _ApproxQuality : Required quality for the test of the spherical enveloppe (computation of the chord)
// double _CircularSweepRMin : Minimal bound of the radius interval of the required fillet
// double _CircularSweepRMax : Maximal bound of the radius interval of the required fillet
//===============================================================================================================
// Jun. 10 Creation                                                                         E.M. Duclairoir
// Apr. 18 KJD Addition of GetParms in CATRecognizerContext
// May  19 R1Y Implemented the recognition of circular sweeps.
// Oct  19 JSX Separation CATRecognizerParams et CATRecognizerContext
//===============================================================================================================

#ifndef CATRecognizerContext_H
#define CATRecognizerContext_H 

#include "CATGMModelInterfaces.h"
#include "CATCGMStream.h"
#include "CATCGMOutput.h"
#include "CATDeclarativeContext.h"
#include "CATRecognizerParams.h"


class CATSoftwareConfiguration;
class CATGeoFactory;
class CATDeclarativeContext;


//-------------------------------------------------------------------------------------
class ExportedByCATGMModelInterfaces CATRecognizerContext
{
public :
  CATRecognizerContext(CATSoftwareConfiguration * iConfig, const CATRecognizerParams& iParams);

  /** @deprecated */
  //CATRecognizerContext(CATSoftwareConfiguration * iConfig, CATGeoFactory * iFactory);

  ~CATRecognizerContext();
   void SetConfig(CATSoftwareConfiguration * iConfig);
   CATSoftwareConfiguration * GetConfig();

  static void GetInitTolerances(CATSoftwareConfiguration *iConfig, CATGeoFactory *iFactory, double &oScale, double &oLinearTol, double &oAngularTol, double &oMergeTol);

  void GetLinearTol(double & oLinearTol) const;
  void GetAngularTol(double & oAngularTol) const;

  void SetMergeTol(const double iMergeTol);
  void GetMergeTol(double & oMergeTol) const;

  static double GetLinearTol(CATSoftwareConfiguration *iConfig, CATGeoFactory *iFactory, CATRecognizerContext *iRecogCtx);
  static double GetAngularTol(CATSoftwareConfiguration *iConfig, CATGeoFactory *iFactory, CATRecognizerContext *iRecogCtx);
  static double GetMergeTol(CATSoftwareConfiguration *iConfig, CATGeoFactory *iFactory, CATRecognizerContext *iRecogCtx);

  void GetFilletRadiusMin(double & oFilletRMin) const;
  void GetFilletRadiusMax(double & oFilletRMax) const;
  void GetFilletRadii(double & oFilletRMin, double & oFilletRMax) const;
  void GetFilletApproxQuality(double & oFilletApproxQuality) const;
  void GetFilletOpeningAngleMax(double & oFilletOpeningAngleMax) const;
  void GetBiTangentOpeningAngleMax(double & oBiTangentOpeningAngleMax) const;
  void GetTriTangentOpeningAngleMin(double & oTriTangentOpeningAngleMin) const;

  void GetChamferDistMin(double & oChamferDistMin) const;
  void GetChamferDistMax(double & oChamferDistMax) const;
  void GetChamferDistances(double & oChamferDistMin, double & oChamferDistMax) const;
  void GetChamferAngMin(double & oChamferAngMin) const;
  void GetChamferAngMax(double & oChamferAngMax) const;
  void GetChamferAngles(double & oChamferAngMin, double & oChamferAngMax) const;

  void GetDraftAngMin(double & oDraftAngMin) const;
  void GetDraftAngMax(double & oDraftAngMax) const;
  void GetDraftAngles(double & oDraftAngMin, double & oDraftAngMax) const;
  void GetDraftNeutralAngMax(double & oDraftNeutralAngMax) const;

  void GetCircularSweepRadiusMin(double & oCircularSweepRMin) const;
  void GetCircularSweepRadiusMax(double & oCircularSweepRMax) const;
  void GetCircularSweepRadii(double & oCircularSweepRMin, double & oCircularSweepRMax) const;

  void SetParms(const CATRecognizerParams& iParams);
  void GetParms(CATRecognizerParams& oParams) const;

  void InitWithDeclarativeContext(CATDeclarativeContext &iContext);
  void InitWithIndustry(CATDeclarativeContextIndustry iIndustry, CATGeoFactory *iFactory = NULL);

  /* DEPRECATED, do not use */
  void InitContextForBodyInWhite();
  void InitContextForPowerTrain();
  void InitContextForConsumerGoods();
  void InitContextForMachineDesign();
  void InitContextForShipBuilding();
  void InitContextForHighTech();
  void InitContextForBuilding();
  void InitContextForCivilEngineering();
  void InitContextForDefeaturing();
  void InitContextForMicroMechanics();
  void InitContextForExtraLargeCivilEngineering();

  void SetFilletApproxQuality(const double iFilletApproxQuality);
  void InitContextSystemParasolid();
  void InitContextSystemCATIAV5();
  void InitContextSystemACIS();
  void InitContextSystemStrimStyler();
  
  // Industry
  CATDeclarativeContextIndustry GetIndustry() const {return _Industry;}

  static CATRecognizerContext* CATLoadRecognizerContext(CATCGMStream& os, CATSoftwareConfiguration *iConfig);

  void  Write (CATCGMStream& os);
  void  Load (CATCGMStream& os);
  void  Dump (CATCGMOutput& os);

  void Scale(const double iScale); // Do not use, for XScaleODTManager only

private :
  CATSoftwareConfiguration * _Config;
  //some clients will supply detailed params, while others will believe in our setting based on industry
  CATRecognizerParams _Params;
  CATDeclarativeContextIndustry _Industry;
  //dependent on authoring kernel
  double _FilletApproxQuality;

  CATRecognizerContext(CATRecognizerContext& iOperator);
  CATRecognizerContext& operator=(const CATRecognizerContext & iOperator);
};

#endif
