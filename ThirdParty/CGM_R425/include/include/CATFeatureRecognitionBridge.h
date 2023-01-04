//========================================================================
// 18/09/19 PKC ajout CATSoftwareConfiguration aux arguments de _HoleDepth 
//              et de _BodyExtrema
//========================================================================

#ifndef CATFeatureRecognitionBridge_h
#define CATFeatureRecognitionBridge_h

#include "ExportedByCATTopologicalObjects.h"

class CATGeoFactory;
class CATBody;
class CATMathVector;
class CATMathDirection;
class CATMathLine;
class CATMathPoint;
class CATSoftwareConfiguration;

class ExportedByCATTopologicalObjects CATFeatureRecognitionBridge
{
public:
   virtual ~CATFeatureRecognitionBridge();
   // The implementation assumes that iPtOrigin is somewhere between the two hole extrema.
   static double HoleDepth(CATGeoFactory* iFactory, CATSoftwareConfiguration * iConfig, CATBody * iBody, CATMathLine const & iAxis, CATMathPoint const & iPtOrigin, CATMathPoint & oAxisOrigin);
   static void BodyExtrema(CATGeoFactory* iFactory, CATSoftwareConfiguration * iConfig, CATBody * iBody, CATMathDirection const & iDirection, CATMathPoint const & iOrigin, double & oMinDistance, double & oMaxDistance);
protected:
   CATFeatureRecognitionBridge();
   static CATFeatureRecognitionBridge * _Bridge;
   virtual double _HoleDepth(CATGeoFactory* iFactory, CATSoftwareConfiguration * iConfig, CATBody * iBody, CATMathLine const & iAxis, CATMathPoint const & iPtOrigin, CATMathPoint & oAxisOrigin) = 0;
   virtual void _BodyExtrema(CATGeoFactory* iFactory, CATSoftwareConfiguration * iConfig, CATBody * iBody, CATMathDirection const & iDirection, CATMathPoint const & iOrigin, double & oMinDistance, double & oMaxDistance) = 0;
private:
   static void Init();
};

#endif
