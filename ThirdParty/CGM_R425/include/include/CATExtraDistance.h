// COPYRIGHT DASSAULT SYSTEMES 2008
//========================================================================
//
// CATExtraDistance :
//  Operator to compute a "maximal" distance devoted to Sw
//
//========================================================================
// 26/10/12 kjd Creation
//========================================================================

#ifndef CATExtraDistance_H
#define CATExtraDistance_H 

// ExportedBy
#include "Y30C3XGG.h"

// Base class
#include "CATGeoOperator.h"

// C++11
#include "CATGeoOpVirtual.h"

#include "CATLocalDistanceType.h"
#include "CATLISTV_CATMathPoint.h"
#include "CATListOfInt.h"
#include "CATListOfDouble.h"
#include "CATListOfCATSurParams.h"
#include "CATListOfCATCrvParams.h"

class CATGeoFactory ;
class CATSoftwareConfiguration;
class CATSurface;
class CATSurLimits;
class CATCurve;
class CATCrvLimits;
class CATPoint;
class CATMathPoint;
class CATSurParam;

class ExportedByY30C3XGG CATExtraDistance : public CATGeoOperator
{
public :
  //========================================================================
  //- Object Management
  //========================================================================
   CATExtraDistance(CATGeoFactory            * iFactory,
                    CATSoftwareConfiguration * iConfig);
  ~CATExtraDistance ();

  //- ExtraDistance Computation (NewVersion)
  //========================================================================
   // WARNING :It is left to the caller to delete the elements of the pointer lists
  HRESULT ComputeExtraDistance(      CATSurface           *  iSurf1      ,
                               const CATSurLimits         *  iSurfLim1   ,
                                     CATSurface           *  iSurf2      ,
                               const CATSurLimits         *  iSurfLim2   ,
                                     CATLocalDistanceType  & ioType1     ,
                                     CATLocalDistanceType  & ioType2     ,
                                     CATListOfDouble       & oMaxDistList,
                                     CATLISTP(CATSurParam) & oP1List     ,
                                     CATLISTP(CATSurParam) & oP2List     );

  HRESULT ComputeExtraDistance(     CATSurface            *  iSurf       ,
                               const CATSurLimits         *  iSurfLim    ,
                                     CATCurve             *  iCrv        ,
                               const CATCrvLimits         *  iCrvLim     ,
                                     CATLocalDistanceType  & ioType1     ,
                                     CATLocalDistanceType  & ioType2     ,
                                     CATListOfDouble       & oMaxDistList,
                                     CATLISTP(CATSurParam) & oP1List     ,
                                     CATLISTP(CATCrvParam) & oP2List     );

  HRESULT ComputeExtraDistance(      CATSurface           *  iSurf       ,
                               const CATSurLimits         *  iSurfLim    ,
                                     CATPoint             *  iPt         ,
                                     CATLocalDistanceType  & ioType      ,
                                     CATListOfDouble       & oMaxDistList,
                                     CATLISTP(CATSurParam) & oP1List     );

  HRESULT ComputeExtraDistance(      CATCurve             *  iCrv1       ,
                               const CATCrvLimits         *  iCrvLim1    ,
                                     CATCurve             *  iCrv2       ,
                               const CATCrvLimits         *  iCrvLim2    ,
                                     CATLocalDistanceType  & ioType1     ,
                                     CATLocalDistanceType  & ioType2     ,
                                     CATListOfDouble       & oMaxDistList,
                                     CATLISTP(CATCrvParam) & oP1List     ,
                                     CATLISTP(CATCrvParam) & oP2List     );

  HRESULT ComputeExtraDistance(      CATCurve             *  iCrv        ,
                               const CATCrvLimits         *  iCrvLim     ,
                                     CATPoint             *  iPt         ,
                                     CATLocalDistanceType  & ioType      ,
                                     CATListOfDouble       & oMaxDistList,
                                     CATLISTP(CATCrvParam) & oP1List     );

  //- ExtraDistance Recognition 
  //========================================================================
  HRESULT WhichExtraDistance(        double                  iMaxDist    ,
                                     CATMathPoint          & ioP1        ,
                                     CATMathPoint          & ioP2        ,
                                     CATSurface           *  iSurf1      ,
                               const CATSurLimits         *  iSurfLim1   ,
                                     CATSurface           *  iSurf2      ,
                               const CATSurLimits         *  iSurfLim2   ,
                                     CATLocalDistanceType  & oType1      ,
                                     CATLocalDistanceType  & oType2      ,
                                     CATBoolean            & oIsConst    );

  HRESULT WhichExtraDistance(        double                  iMaxDist    ,
                                     CATMathPoint          & ioP1        ,
                                     CATMathPoint          & ioP2        ,
                                     CATSurface           *  iSurf       ,
                               const CATSurLimits         *  iSurfLim    ,
                                     CATCurve             *  iCrv        ,
                               const CATCrvLimits         *  iCrvLim     ,
                                     CATLocalDistanceType  & oType1      ,
                                     CATLocalDistanceType  & oType2      ,
                                     CATBoolean            & oIsConst    );

  HRESULT WhichExtraDistance(        double                  iMaxDist    ,
                                     CATMathPoint          & ioP1        ,
                                     CATMathPoint          & ioP2        ,
                                     CATSurface           *  iSurf       ,
                               const CATSurLimits         *  iSurfLim    ,
                                     CATLocalDistanceType  & oType1      ,
                                     CATBoolean            & oIsConst    );

  HRESULT WhichExtraDistance (       double                  iMaxDist    ,
                                     CATMathPoint          & ioP1        ,
                                     CATMathPoint          & ioP2        ,
                                     CATCurve             *  iCrv1       ,
                               const CATCrvLimits         *  iCrvLim1    ,
                                     CATCurve             *  iCrv2       ,
                               const CATCrvLimits         *  iCrvLim2    ,
                                     CATLocalDistanceType  & oType1      ,
                                     CATLocalDistanceType  & oType2      ,
                                     CATBoolean            & oIsConst    );

  HRESULT WhichExtraDistance(        double                  iMaxDist    ,
                                     CATMathPoint          & ioP1        ,
                                     CATMathPoint          & ioP2        ,
                                     CATCurve             *  iCrv        ,
                               const CATCrvLimits         *  iCrvLim     ,
                                     CATLocalDistanceType  & oType1      ,
                                     CATBoolean            & oIsConst    );


private:
  // Necessary to prevent unwanted automatic creation by the compiler
  CATExtraDistance(const CATExtraDistance & RecognizerOper);
  void operator = (const CATExtraDistance & RecognizerOper);

private : 
  //
  //========================================================================
  //- Private data
  //========================================================================
  //
  CATSoftwareConfiguration              *  _Config;
  const CATTolerance                    &  _TolObject;
  double                                   _Tol;
};


#endif







