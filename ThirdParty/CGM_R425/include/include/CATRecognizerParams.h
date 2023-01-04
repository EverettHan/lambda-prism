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

#ifndef CATRecognizerParams_H
#define CATRecognizerParams_H 

#include "CATGMModelInterfaces.h"
#include "CATCGMStream.h"
#include "CATCGMOutput.h"
//#include "CATDeclarativeContext.h"

class CATSoftwareConfiguration;
class CATGeoFactory;
//class CATDeclarativeContext;

//-------------------------------------------------------------------------------------
class ExportedByCATGMModelInterfaces CATRecognizerParams
{
public:
  CATRecognizerParams(CATSoftwareConfiguration *iConfig, CATGeoFactory *iFactory = NULL);

  /** @deprecated */
  CATRecognizerParams(double iFactoryScale);
  void Init( double iFactoryScale );

  CATRecognizerParams& operator=(const CATRecognizerParams& iParam);

  double _FactoryScale;
  double _LinearTol;
  double _AngularTol;
  double _MergeTol;

  //fillet
  double _FilletRMin;
  double _FilletRMax;
  double _FilletOpeningAngleMax;
  double _BiTangentOpeningAngleMax;
  double _TriTangentOpeningAngleMin;
  double _FilletApproxQuality;        // jsx vient du context a verfier

  
  // Chamfer
  double _ChamferDMin;
  double _ChamferDMax;
  double _ChamferAMin;
  double _ChamferAMax;

  // Draft
  double _DraftAMin;
  double _DraftAMax;
  double _DraftNeutralAMax;

  // Circular Sweep
  double _CircularSweepRMin;
  double _CircularSweepRMax;

  void  Write (CATCGMStream& os);
  void  Load (CATCGMStream& os);
  void  Dump (CATCGMOutput& os);
};

#endif
