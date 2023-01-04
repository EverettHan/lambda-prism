/* -*-c++-*-*/
// COPYRIGHT DASSAULT SYSTEMES 2001
//=============================================================================
//
// CATProjectionReportEdgeCrvSur.h
//=============================================================================
// Usage Notes:
//=============================================================================
// Fev. 01   Creation                                   R.HAMZA
// 29/05/08 NLD Ajout _ConfusionPtPtOperator _ConfusionPtPtCurve
//=============================================================================

#ifndef CATProjectionReportEdgeCrvSur_H
#define CATProjectionReportEdgeCrvSur_H

#include "Y30UIUTI.h"
#include "CATCGMVirtual.h"
#include "CATBoolean.h"

class CATGeoFactory;
class CATEdgeCurve;
class CATPointOnEdgeCurve;
class CATMapX;
class CATCurve;
class CATSoftwareConfiguration;
class CATConfusionPtOnCrvPtOnCrv;

class ExportedByY30UIUTI CATProjectionReportEdgeCrvSur : public CATCGMVirtual
{
public:
   //-----------------------------------------------------------------------
   //- Object management
   //-----------------------------------------------------------------------
   CATProjectionReportEdgeCrvSur (CATGeoFactory *iFactory,
      CATSoftwareConfiguration * OpenConfig,
      CATMapX* iMapX,
      CATEdgeCurve  *iEdgeCurveToProject,
      const CATPointOnEdgeCurve * iPOECStart1,
      const CATPointOnEdgeCurve * iPOECEnd1,
      CATEdgeCurve  *iEdgeCurveProjected,
      const CATPointOnEdgeCurve * iPOECStart2,
      const CATPointOnEdgeCurve * iPOECEnd2,
      const CATPCurve * iPCrv);
   
   //Do not use
   CATProjectionReportEdgeCrvSur (CATGeoFactory *iFactory,
      CATMapX* iMapX,
      CATEdgeCurve  *iEdgeCurveToProject,
      const CATPointOnEdgeCurve * iPOECStart1,
      const CATPointOnEdgeCurve * iPOECEnd1,
      CATEdgeCurve  *iEdgeCurveProjected,
      const CATPointOnEdgeCurve * iPOECStart2,
      const CATPointOnEdgeCurve * iPOECEnd2,
      const CATPCurve * iPCrv);
   
   
   ~CATProjectionReportEdgeCrvSur();
   //-----------------------------------------------------------------------
   //- Public methods
   //-----------------------------------------------------------------------
   //
   // return the Equivalent POEC with respect Projection Report
   //
   virtual void  GetEquivalentPoint    ( const CATPointOnEdgeCurve * iCurrentPOEC,
      CATEdgeCurve  *iCurrentEdgeCurve,
      CATEdgeCurve  *iEquivalentEdgeCurve,
      CATPointOnEdgeCurve *& oEquivalentPOEC,
      const CATPCurve * iPCrv = 0) ;
   //
   // return TRUE if iEquivalentPOEC is the representant of iCurrentPOEC else FALSE
   //
   CATBoolean CheckEquivalentPoint (CATPointOnEdgeCurve * iCurrentPOEC,
      CATEdgeCurve  *iCurrentEdgeCurve,
      CATEdgeCurve  *iEquivalentEdgeCurve,
      CATPointOnEdgeCurve *& iEquivalentPOEC,
      double &oDist,
      CATMathDirection  *iDirection,
      CATPCurve * iPCrv = 0) ;
   
   
protected:
   
   CATPointOnEdgeCurve * ComputePointOnEdgeCurve(const CATCrvParam & iParam, const CATCurve * iCrv, int iIndex) ;
   
   CATLONG32 AdjustParamOnPCrv(CATCrvParam & ioParam, int iPCrvIndex, const CATCurve * iCrv, CATCrvParam * oNewParam=0);
   void CheckGeometry () ; 
   
protected:
   
   CATGeoFactory * _Factory;
   CATEdgeCurve * _ECrv[2];
   CATMapX* _MapX;
   const CATPointOnEdgeCurve * _PoecS[2], * _PoecE[2];
   const CATCurve * _PCrv;
   CATSoftwareConfiguration * _Config;
   
private:
   CATBoolean _CheckGeom;
   CATConfusionPtOnCrvPtOnCrv* _ConfusionPtPtOperator;
   CATCurve* _ConfusionPtPtCurve;
};


ExportedByY30UIUTI CATPointOnEdgeCurve * ComputePointOnEdgeCurve(CATGeoFactory * iFacto,const CATCrvParam & iParam, const CATCurve * iCrv, const CATEdgeCurve * iEdgeCurve, int nbPOEC, CATPointOnEdgeCurve ** TabPOEC);


#endif
