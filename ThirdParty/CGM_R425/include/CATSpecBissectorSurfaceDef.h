// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// Class designed to handle the  definition of a bissector surface 
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Aug.  00 FBZ Creation                                                    FBZ
// Oct.  01 SDP Merge with directional surfaces
// Sep.  11 R1Y Added access functions (for comparing geometries).
// 25/07/12 PKC Untabify
// 05/09/12 PKC Software Config in Extrapol
// 20/07/18 NLD Suppression du constructeur sans configuration
//=============================================================================

// Whenever _PCrv2 is NULL, the bisector surface behaves like a directional

#ifndef CATSpecBissectorSurfaceDef_H
#define CATSpecBissectorSurfaceDef_H

#include "YP00IMPL.h"

#include "CATSpecSurfaceDef.h"
#include "CATCrvLimits.h"
#include "CATListOfDouble.h"

class CATSurface;
class CATPCurve;
class CATEdgeCurve;
class CATMathFunctionX;
class CATCrvLimits;
class CATMathSetOfPointsND;
class CATSoftwareConfiguration;

//-----------------------------------------------------------------------------
//
class ExportedByYP00IMPL CATSpecBissectorSurfaceDef : public CATSpecSurfaceDef
{
public:
  
  //-------------------------------------------------------------------------
  // Constructors
  //-------------------------------------------------------------------------
  CATSpecBissectorSurfaceDef();
  CATSpecBissectorSurfaceDef(      CATSoftwareConfiguration *  iConfig      ,
                                   CATEdgeCurve             *  iEdgeCurve   ,
                                   CATPCurve                *  iPCurve1     ,
                                   CATPCurve                *  iPCurve2     ,
                             const CATCrvLimits              & iLimOnPCurve1,
                                   double                      iAngle       , // en fait c'est un ratio entre iPCurve1 et iPCurve2; NLD200718
                                   double                      iLength      );


// #define CATSpecBissectorSurfaceDef_KeepOldConstructor

#ifdef CATSpecBissectorSurfaceDef_KeepOldConstructor
  CATSpecBissectorSurfaceDef(      CATEdgeCurve             *  iEdgeCurve   ,
                                   CATPCurve                *  iPCurve1     ,
                                   CATPCurve                *  iPCurve2     ,
                             const CATCrvLimits              & iLimOnPCurve1,
                                   double                      iAngle       , // en fait c'est un ratio entre iPCurve1 et iPCurve2; NLD200718
                                   double                      iLength      );
#endif
  //-------------------------------------------------------------------------
  // virtual Destructor
  //-------------------------------------------------------------------------
  ~CATSpecBissectorSurfaceDef();
  
  //-------------------------------------------------------------------------
  // Gets the type of proccurve
  //-------------------------------------------------------------------------
  CATSpecSurfaceDef::Type GetType() const;
  
  //-------------------------------------------------------------------------
  // Pour le stream
  //-------------------------------------------------------------------------
  void Stream( CATCGMStream& Str );
  void UnStream( CATCGMStream& Str );
  CATBoolean IsStreamable( const CATCGMStreamVersion iTargetVersion, CATBoolean & ioReversible ) const;
  void Dump(CATCGMOutput & os);
  
  //-------------------------------------------------------------------------
  // Duplicate this 
  //-------------------------------------------------------------------------
  CATSpecSurfaceDef * Duplicate() const;
  
  void ApplyTransformation(const CATMathTransformation & iTransfo);
  
  void CreateSurface();
  
  void SetBissectorData(CATEdgeCurve *EC, CATPCurve *PC1, CATPCurve *PC2);

  void GetBissectorData(CATEdgeCurve * &oEC, CATPCurve * &oPC1, CATPCurve * &oPC2, CATCrvLimits & oLimOnPC1) const;

  void GetMapping(CATMathSetOfPointsND * & oMap) const;
  
  void Extrapolation(const CATCrvLimits & NewMaxLimOnPC1, CATSoftwareConfiguration * iConfig);

  void Unextrapolation(const CATCrvLimits & NewMaxLimOnPC1);

  void OperateOnCrvLimitsAndLengthParameter(const CATCrvParamReference* ParamRef,CATPositiveLength Ratio);

  /**
  *
  */
  void SetConstraintsAtExtremities(const CATMathPoint & iPoint, const CATMathVector & iVector, short iStartOrEnd);
  void SetFirstOrderConstraints   (short i, const CATMathPoint & Point, const CATMathVector & Normal,
                                   const CATMathVector & PointDeriv, const CATMathVector & NormalDeriv);
  void GetConstraints             (short * IsConstrained, CATMathPoint * Point, CATMathVector * Normal,
                                   CATMathVector * PointDeriv, CATMathVector * NormalDeriv) const;
  void ForceThroughPoint          (const CATMathPoint & Apex);

  void AppendMandatorySamplingPoints(CATListOfDouble &iPointsToForceEvalOn);

 /**
  *
  */
  void DeformToMatchConstraints(CATMathSetOfPointsND & ioParameters, CATMathSetOfPointsND & ioPoints, 
                                CATMathSetOfPointsND & ioTangents, CATMathSetOfPointsND & ioSecondDerivatives);

  // used to force the old type of sampling (level 0)
  // default is level 1 = adaptive sampling, improves the quality of the explicit interpol
  void ForceLevel(short Level);

  void SetLimitsOnPCrv1(const CATCrvLimits & iLimOnPCrv1);

  int IsDirectional();

  double GetAngle() const;
  double GetLength() const;
  double GetLambda() const;

  void GetForceThroughPoint(CATBoolean & oForceThroughPoint,
                            CATMathPoint & oApex) const;

  short GetLevel() const;

  
private:

  void       Init                       ();
  void       ComputePointForDeformation (const CATMathPoint & iPoint, const CATMathVector & iVector,
                                         const double * iOriginalPoint, double * oPointForDeformation);
  void       ImposeConstraintDebug(CATMathSetOfPointsND & ioPoints, CATMathSetOfPointsND & ioTangents);
  CATBoolean IsConnectedWithPreviousPart(CATLONG32 iOrientation, CATMathSetOfPointsND & iPoints);
  CATBoolean AreSetsConnected           (CATMathSetOfPointsND & iFirstPoints, CATMathSetOfPointsND & iLastPoints, double iTolerance);
  void       DeformToMatchConstraintsG0 (CATMathSetOfPointsND & ioParameters, CATMathSetOfPointsND & ioPoints, 
                                         CATMathSetOfPointsND & ioTangents, CATMathSetOfPointsND & ioSecondDerivatives);
  void       DeformToMatchConstraintsG1 (CATMathSetOfPointsND & ioParameters, CATMathSetOfPointsND & ioPoints, 
                                         CATMathSetOfPointsND & ioTangents, CATMathSetOfPointsND & ioSecondDerivatives);

  void       CreateSurface_ForceThroughPoint();
  void       ComputeLambda              ();

  //==============================================================================================================
  // DATA
  //==============================================================================================================

private:
  CATEdgeCurve             * _EC;
  CATPCurve                * _PCrv1, *_PCrv2;
  CATCrvLimits               _LimitsOnPCrv1;
  double                     _Angle, _Length,_Lambda;
  CATMathSetOfPointsND     * _Mapping;
  CATMathPoint               _ConstrainedPointAtExtremities[2];
  CATMathVector              _ConstrainedVectorAtExtremities[2];
  CATMathVector              _ConstrainedPointDeriv[2];
  CATMathVector              _ConstrainedNormalDeriv[2];
  short                      _IsExtremityConstrained[2];
  CATBoolean                 _ForceThroughPoint;
  CATMathPoint               _Apex;
  CATListOfDouble            _MandatorySamplingPoints;

  short                      _Level;
  CATSoftwareConfiguration * _Config;


};

#endif
