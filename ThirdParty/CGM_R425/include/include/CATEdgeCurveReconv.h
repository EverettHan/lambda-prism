#ifndef CATEdgeCurveReconv_h
#define CATEdgeCurveReconv_h

// COPYRIGHT DASSAULT SYSTEMES 2002
//=============================================================================
//
// CATEdgeCurveReconv:
// A partir des PCurves PC1 et PC2, membres de l'EdgeCurve EC, cree une
// nouvelle EdgeCurve geometriquement equivalente entre StartPOEC et EndPOEC,
// ayant un representant sur chacun des fonds de PC1 et PC2 et ne presentant 
// pas les eventuels defauts d'overlap/gap affligeant l'EdgeCurve input.
// L'appelant specifie une boite UV sur chaque surface support (zone de validite
// de la surface). Il est possible de specifier des contraintes point/tangente 3d 
// aux extremites.
// 
// Dans un premier temps, seuls les overlaps sont traites. Les PCurves de
// l'EdgeCurve resultat sont contenues dans les boites UV donnees en input
// (pas d'extrapolation).
//
//=============================================================================
// June 2002  Creation                                        S. Dauby
//=============================================================================

#include "Y30C3XGG.h"

#include "CATCGMOperator.h"
#include "CATSurLimits.h"
#include "CATString.h"

class CATGeoFactory;
class CATSoftwareConfiguration;
class CATEdgeCurve;
class CATPCurve;
class CATPointOnEdgeCurve;
class CATMathPoint;
class CATMathVector;
class CATSurSurInterpol;
class CATSurface;
class CATMathImplicitSystem;
class CATInclusionPtSur;

class ExportedByY30C3XGG CATEdgeCurveReconv : public CATCGMOperator
{
public:
  CATEdgeCurveReconv(CATGeoFactory * Factory, CATSoftwareConfiguration * Config,
                     CATEdgeCurve * EC, CATPCurve * PC1, CATPCurve * PC2,
                     const CATSurLimits & Box1, const CATSurLimits & Box2,
                     CATPointOnEdgeCurve * StartPOEC, CATPointOnEdgeCurve * EndPOEC);
  virtual ~CATEdgeCurveReconv();

  // passer le pointeur NULL pour laisser une contrainte vide
  void SetConstraints(const CATMathPoint * StartPoint,
                      const CATMathPoint * EndPoint,
                      const CATMathVector * StartTangent,
                      const CATMathVector * EndTangent);

  int RunOperator();

  void GetResult(CATEdgeCurve * & NewEC, CATPCurve * & NewPC1, CATPCurve * & NewPC2,
                 CATPointOnEdgeCurve * & NewStartPOEC, CATPointOnEdgeCurve * & NewEndPOEC,
                 short & OriNewECvsEC);

private:

  CATLONG32 Initialize();
  void CleanUp();

  CATLONG32 FindExtremities();
  CATLONG32 TryPLine();
  CATLONG32 CreateArcLimits();
  CATLONG32 CreateArcs();
  CATLONG32 CreateEdgeCurve();

  void ComputeMean3DPoint(CATPointOnEdgeCurve * POEC, CATMathPoint & M);
  void ComputeMean3DTangent(CATPointOnEdgeCurve * POEC, CATMathVector & Tg);
  CATLONG32 CheckEdgeCurve(CATEdgeCurve * EC, 
                      CATPointOnEdgeCurve * StartPOEC,
                      CATPointOnEdgeCurve * EndPOEC);


  CATCheckDiagnostic CheckOutput1(CATCGMOutput & os);
  CATCheckDiagnostic CheckOutput2(CATCGMOutput & os);
  CATCheckDiagnostic CheckOutput3(CATCGMOutput & os);
  CATCheckDiagnostic CheckOutput4(CATCGMOutput & os);



  // input
  CATSoftwareConfiguration * _Config;
  CATEdgeCurve * _EC;
  CATPCurve * _PCrv[2];
  CATSurLimits _SurLim[2];
  CATPointOnEdgeCurve * _StartPOEC;
  CATPointOnEdgeCurve * _EndPOEC;
  CATMathPoint * _StartPoint;
  CATMathPoint * _EndPoint;
  CATMathVector * _StartTangent;
  CATMathVector * _EndTangent;

  // output
  CATEdgeCurve * _NewEC;
  CATPCurve * _NewPC[2];
  CATPointOnEdgeCurve * _NewStartPOEC;
  CATPointOnEdgeCurve * _NewEndPOEC;

  // work data
  CATSurface * _Surf[2];
  CATMathImplicitSystem * _ImplicitSystem;
  CATSurSurInterpol * _Interpol;
  double _dom[8];
  short _oriPCvsEC[2];
  double _Res;
  CATInclusionPtSur * _Incl[2];
  double _gapEC;

  double _start[4];
  double _start_tg[4];
  double _end[4];
  double _end_tg[4];


//========================================================================
// CGMReplay
//========================================================================
protected:
  friend class CATGeoStreamFactory; 

  // private static data
  static CATString _OperatorId;
public:
	const CATString * GetOperatorId();

  CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
  virtual void WriteInput(CATCGMStream  & os);
  virtual void WriteOutput(CATCGMStream & os);
	virtual CATBoolean ValidateOutput(CATCGMStream& ioStream, CATCGMOutput & os,int VersionNumber=1);
  virtual void Dump( CATCGMOutput& os ) ;
  virtual void DumpOutput(CATCGMOutput & os);
  virtual void DumpOutput(CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
  virtual CATCheckDiagnostic CheckOutput(CATCGMOutput & os);
};

#endif
