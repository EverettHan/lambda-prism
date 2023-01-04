/*-*-c++-*-*/
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATNewExtrapolNurbsCurve :
// Class for extrapoling a NurbsCurve beyond a box.
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// 18/02/10 NLD Ajout _CGMLevel
//=============================================================================
#ifndef CATNewExtrapolNurbsCurve_H 
#define CATNewExtrapolNurbsCurve_H 

#include "Y30C3XGG.h"

#include "CATMathDef.h"
#include <fstream.h>

class CATFrFNurbsMultiForm;
class CATKnotVector;
class CATCurve;
class CATNurbsCurve;
class CATPNurbs;
class CATGeoFactory;
class CATMathSetOfPoints;
class CATMathVector;
class CATMathVector2D;
class CATCrvParam;
class CATSoftwareConfiguration;

class ExportedByY30C3XGG CATNewExtrapolNurbsCurve 
{
public:
  //-----------------------------------------------------------------------
  //- Public Methods
  //-----------------------------------------------------------------------
  CATNewExtrapolNurbsCurve (CATGeoFactory *iFactory,
			   CATNurbsCurve * ioCrv,
			   const double &iLength,
			   const CATCrvParam & iParamOnCrv,
                           CATLONG32 iSide,
                           CATSoftwareConfiguration * iConfig);

  CATNewExtrapolNurbsCurve (CATGeoFactory *iFactory,
			   CATPNurbs * ioCrv,
			   const double &iLength,
			   const CATCrvParam & iParamOnCrv,
                           CATLONG32 iSide,
                           CATSoftwareConfiguration * iConfig);

  ~CATNewExtrapolNurbsCurve();
  
  void Run ();

  
protected:
  //-----------------------------------------------------------------------
  //- Protected data
  //-----------------------------------------------------------------------
  CATGeoFactory   * _Factory;
  CATCurve * _Crv;
  double _Length;
  int _CGMLevel;

  void InitData(const CATCrvParam & iParamOnCrv,CATSoftwareConfiguration * iConfig);
 
  //-------------------------------------------------------------------------
  // Protected methods for extrapolation
  //-------------------------------------------------------------------------

  void ReExtrapolation();

  void FunctionsExtrapolation();

  void C2BezPointsOnSide(const CATLONG32 &iSide, double &oAlpha, double &oBeta, double *oCPs);

  void GetParamForC2(const CATLONG32 &iSide, double *oParamForC2, double &oParamFin);

  void C2BezPoints(const double &alpha, const double &beta, 
                   double *TargetP, double *TargetW, double *TargetD,    
                   double *oP0, double *oP1, double *oP2, 
                   double *oP3, double *oP4, double *oP5, double *oP6);

  void TargetDerivatives(const CATLONG32 &Degree, double *CPs, 
                          double *Weights, double *u, double *oFnSDerivatives);

  void TargetDirection(double *TargetP, double *TargetW, double *TargetD,
                  double &ioalphaMin, double &ioalphaMax, double &oAlpha) ;

  //remplie _TabOfNurbs avec toutes les Curves servant a l'extrapolation
  void FillArrayOfNurbs(CATKnotVector *KnotVector,
			double *ExtrCPs,double *ExtrWeights,
			CATMathSetOfPoints &LocCPs,double *LocWeights,
			const CATLONG32 FirstVertex,const CATLONG32 Rank);
 
private:
  //-----------------------------------------------------------------------
  //- Private data
  //-----------------------------------------------------------------------
  CATKnotVector * _KnotVector;
  CATLONG32            _IsRational;
  double        * _Vertices;
  double        * _Weights;
  //La Curve a-t'elle deja ete extrapole?
  CATLONG32            _IsExtrapolated; 
  //La Curve doit etre extrapole
  CATLONG32            _Extrapol;
  //Degre de la Nurbs extrapolee
  CATLONG32            _TargetDegree;
  CATFrFNurbsMultiForm ** _TabOfNurbs;

  //_ExtrapolDirection=0 : nearest side of iParamOnCrv will be used for extrapolation.
  //if _ExtrapolDirection<0, extrapolation at curve start, else if _ExtrapolDirection>0, at curve end.
  CATLONG32 _ExtrapolDirection;

  CATLONG32 _ReExtrapol ;
  CATBoolean _CaseOfDegreeOne ;
  double _OrigLow, _OrigHigh ;

  ofstream *_anrout ;
  CATULONG32  _TempsCPU ;
  double _LongBefore ;
  double _LongAfter  ;
  CATLONG32 _CaseOfCurve;
};

#endif

