#ifndef __CATExplicitCheckOperatorTopOpBridge__
#define __CATExplicitCheckOperatorTopOpBridge__



#include "ExportedByCATTopologicalObjects.h"
#include "CATCollec.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"


class CATGeoFactory;
class CATCurve; 
class CATFace;
class CATLump;
class CATBody;
class CATSoftwareConfiguration;
class CATLISTP(CATBody);
class CATCrvParams;
//class CATListOfInt;
//class CATListOfDouble;
class CATLISTP(CATCrvLimits);
class CATLISTP(CATCurve);


class ExportedByCATTopologicalObjects CATExplicitCheckOperatorTopOpBridge
{
public:
   // -------------
   // Ctor & Dtor
   // -------------
   CATExplicitCheckOperatorTopOpBridge();
   virtual ~CATExplicitCheckOperatorTopOpBridge();

   // -------------
   // Methodes
   // -------------

   //

   //

   // -------------
   // Services
   // -------------

   /* */
   static HRESULT ComputeCurveGContinuity(CATGeoFactory *piFactory,CATSoftwareConfiguration *piSoftConfig,CATLISTP(CATCurve) &iListOfCurves,CATListOfInt &iListOfOri,
										  CATLISTP(CATCrvLimits) &iListOfCrvLimits,double iMaxGap,double iMaxAngleDeg,double iMinAngleDeg,
										  double iMaxG2Threshold,double iMinG2Threshold,double iInfiniteCurvatureRatio, CATBoolean iIsClosed, 
										  CATListOfDouble &ioListOfG0Error, CATListOfDouble &ioListOfG1Error,CATListOfDouble &ioListOfG2Delta);

   /* */
   static HRESULT ComputeFaceArea(CATSoftwareConfiguration *piSoftConfig,CATFace *piFace,double &ioArea);

   /* */
   static HRESULT ComputeLumpVolume(CATSoftwareConfiguration	*piSoftConfig,CATLump *piLump,double &ioVolume);

   /* */
   static HRESULT ComputeBodyLength(CATSoftwareConfiguration	*piSoftConfig,CATBody *piBody,double &ioLength);

   /* */
   static HRESULT AssembleListOfWireBodies(CATGeoFactory *piFactory,CATSoftwareConfiguration *piSoftConfig,CATLISTP(CATBody) &iListOfBodiesDim1,CATBody *&pBodyDim1);

protected:
   // -------------
   // Data
   // -------------
   static CATExplicitCheckOperatorTopOpBridge *_pExplicitCheckOperatorTopOpBridge;

   // -------------
   // Internal Use
   // -------------
   virtual HRESULT _ComputeCurveGContinuity(CATGeoFactory *piFactory,CATSoftwareConfiguration *piSoftConfig,CATLISTP(CATCurve) &iListOfCurves,CATListOfInt &iListOfOri,
																		  CATLISTP(CATCrvLimits) &iListOfCrvLimits,double iMaxGap,double iMaxAngleDeg,double iMinAngleDeg,
																		  double iMaxCurvatureRatio,double iMinCurvatureRatio,double iInfiniteCurvatureRatio, CATBoolean iIsClosed, 
																		  CATListOfDouble &ioListOfG0Error, CATListOfDouble &ioListOfG1Error,CATListOfDouble &ioListOfG2Error) = 0;

   virtual HRESULT _ComputeFaceArea(CATSoftwareConfiguration *piSoftConfig,CATFace *piFace,double &ioArea) = 0;

   virtual HRESULT _ComputeLumpVolume(CATSoftwareConfiguration	*piSoftConfig,CATLump *piLump,double &ioVolume) = 0;

   virtual HRESULT _ComputeBodyLength(CATSoftwareConfiguration	*piSoftConfig,CATBody *piBody,double &ioLength) = 0;

   virtual HRESULT _AssembleListOfWireBodies(CATGeoFactory *piFactory,CATSoftwareConfiguration *piSoftConfig,CATLISTP(CATBody) &iListOfBodiesDim1,CATBody *&pBodyDim1) = 0;

private:

   // -------------
   // Internal Use
   // -------------
   static void Init();

   // ---------------
   // Forbidden Ctors
   // ---------------
   CATExplicitCheckOperatorTopOpBridge(const CATExplicitCheckOperatorTopOpBridge& iExplicitCheckOperatorTopOpBridge);
   CATExplicitCheckOperatorTopOpBridge& operator = (const CATExplicitCheckOperatorTopOpBridge& iExplicitCheckOperatorTopOpBridge);
};

#endif

