// COPYRIGHT DASSAULT SYSTEMES 1997
//===================================================================
//
// CATConfusionPropagationCrvCrv
// Class for operator of propagation of confusion between two curves
//
//===================================================================
// Feb. 97    Creation                                  X. Gourdon
// Aug. 97    Better treatment of total confusion
//            Special treatment in the line-line case   X.Gourdon
// Sep. 97                                              X.Gourdon
//            Lifting : taking into account equations 
//            and the continuity of curves
//===================================================================

#ifndef CATConfusionPropagationCrvCrv_H
#define CATConfusionPropagationCrvCrv_H

#include "Y30A3HGG.h"

#include "CATCrvParam.h"
#include "CATMathDef.h"
#include "CATCGMVirtual.h"
#include "CATCreateConfusionPropagationCrvCrv.h"

class CATCurve;
class CATEdgeCurve;
class CATPointOnEdgeCurve;
class CATMathPoint;
class CATGeoFactory;
class CATMathSetOfPointsND;
class CATSoftwareConfiguration;

#undef CATGAP

class ExportedByY30A3HGG CATConfusionPropagationCrvCrv  : public CATCGMVirtual
{
 private:
  double tolerance; 

  const CATCurve * _crv1, * _crv2;

  const CATPointOnEdgeCurve * _StartPtOnECrv1, * _EndPtOnECrv1;
  const CATPointOnEdgeCurve * _StartPtOnECrv2, * _EndPtOnECrv2;   

  const CATEdgeCurve * _ECrv1, * _ECrv2;
  CATCrvParam _pStart1, _pEnd1, _pStart2, _pEnd2;  
  CATBoolean _confusion;
  CATCrvParam _EndConfusion1, _EndConfusion2;   
  CATCrvParam _ProjectionConfusion1, _ProjectionConfusion2;   

  CATGeoFactory * _Factory;

  CATMathSetOfPointsND * _ParamMapping;
  CATSoftwareConfiguration * _Config;
  
public:

  //-----------------------------------------------------------------------
  //- Object management
  //-----------------------------------------------------------------------
  CATConfusionPropagationCrvCrv(CATGeoFactory * iFactory,
                                CATSoftwareConfiguration * iConfig,
                                const CATPointOnEdgeCurve *StartPtOnECrv1, 
                                const CATPointOnEdgeCurve *EndPtOnECrv1,
                                const CATCurve * iCrv1,
                                const CATPointOnEdgeCurve *StartPtOnECrv2,
                                const CATPointOnEdgeCurve *EndPtOnECrv2,
                                const CATCurve * iCrv2,
                                const double iTol) ;

  CATConfusionPropagationCrvCrv(CATGeoFactory * iFactory,
                                CATSoftwareConfiguration * iConfig,
                                const CATCrvParam & StartParam1,
                                const CATCrvParam & EndParam1,
                                const CATCurve * iCrv1,
                                const CATCrvParam & StartParam2,
                                const CATCrvParam & EndParam2,
                                const CATCurve * iCrv2,
                                const double iTol) ;

  ~CATConfusionPropagationCrvCrv();

  //
  //- Methods
  //

   // the confusion is propagated from StartPoint1 and StartPoint2 :
   // 
   // - there is a confusion if one of the curve between StartPoint and
   //   EndPoint is included in the other curve at tol : in this
   //   case, GetConfusion() returns 1, otherwise it returns 0
   //
   // - If there is confusion, GetConfusionEndOnCurve() returns the extremity 
   //   of the confusion along each curve,
   //   GetConfusionProjectionEndOnCurve() returns their projection on the other curve
   //
   //  Remarks :
   //  * there is at least one of the points returned by GetConfusionEndOnCurve()
   //    which is an extremity
   //  * if there is no total confusion, the methods GetConfusionEndOnCurve()
   //    and GetConfusionProjectionEndOnCurve() returns EndPoint for the curve
   //    which is totally included in the other

  void Run();
  CATBoolean GetConfusion() const; // returns 1 if confusion,  0 otherwise.
  void GetConfusionEndOnCurve(const CATCurve * iCrv, CATCrvParam & oParam) const;
  CATPointOnEdgeCurve*  GetConfusionEndOnCurve(const CATEdgeCurve * iECrv) const;   
   // Attention : si un point sorti
   // est egal a un point d entree, retourner les memes pointeurs.
  CATPointOnEdgeCurve*  GetConfusionProjectionEndOnCurve (const CATEdgeCurve * iECrv) const;   
  void GetConfusionProjectionOnCurve(const CATCurve * iCrv, CATCrvParam & oParam) const;

   //
   //- Method to know if there is total confusion
   //
   CATBoolean GetTotalConfusion() const;

  // Call this method before running for a param mapping to be filled
  void FillParamMapping(CATMathSetOfPointsND & oParamMapping);
   

   //
   //- Private methods
   //
 private:

  void RunOnTwoLines();
  CATBoolean FirstStage() const;   
  
  CATBoolean EndOfConfusionTreatment(const CATBoolean Crv1IncludedInCrv2,
				     const CATBoolean Crv2IncludedInCrv1);
  
  CATBoolean ProjectionOfConfusion(const CATMathPoint & PtEndOfConfusion1,
				   const CATCurve * curve2,
				   const CATCrvLimits & limits2,
				   const CATLONG32 & keepdirection,
				   CATCrvParam & ProjectionConfusion);    
  
};

// compute in Projection the nearest point to Point on the segment [Start,End] 
// Return t such that Projection=Start+t*(End-Start);
// DG Ne pas oublier les ExportedBy 
// double DistanceMinToSegment(const CATMathPoint & Point, 
ExportedByY30A3HGG double DistanceMinToSegment(const CATMathPoint & Point,
                                               const CATMathPoint & Start,
                                               const CATMathPoint & End,
                                               CATMathPoint & Projection);
			   
//
//- Destructor
//


ExportedByY30A3HGG void
RemoveConfusionPropagation(CATConfusionPropagationCrvCrv * iConf);



#endif

