/*-*-c++-*-*/
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATExtrapolNurbsCurve :
// Class for extrapoling a NurbsCurve beyond a box.
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// ??/??/?? NDN Creation
// 17/04/12 NLD L'ancien _Config est renommé _CurveConfig
//              Le nouveau _Config contient la SoftwareConfiguration
// 19/10/15 R1Y IR-402150: Changed the return type of some functions.
//=============================================================================

#ifndef CATExtrapolNurbsCurve_H 
#define CATExtrapolNurbsCurve_H 

#include "Y30C3XGG.h"
#include "CATMathDef.h"
#include "CATCGMVirtual.h"

class CATFrFNurbsMultiForm;
class CATKnotVector;
class CATCurve;
class CATNurbsCurve;
class CATPNurbs;
class CATGeoFactory;
class CATMathSetOfPoints;
class CATCrvParam;
class CATSoftwareConfiguration;

class ExportedByY30C3XGG CATExtrapolNurbsCurve : public CATCGMVirtual
{
public:
  //-----------------------------------------------------------------------
  //- Public Methods
  //-----------------------------------------------------------------------
  CATExtrapolNurbsCurve (      CATGeoFactory            * iFactory,
                               CATNurbsCurve            * ioCrv,
                         const double                   & iLength,
                         const CATCrvParam              & iParamOnCrv,
                               CATLONG32                  iSide        = 0,
                               CATSoftwareConfiguration * iConfig      = NULL);

  CATExtrapolNurbsCurve (      CATGeoFactory            * iFactory,
                               CATPNurbs                * ioCrv,
                         const double                   & iLength,
                         const CATCrvParam              & iParamOnCrv,
                               CATLONG32                  iSide        = 0 ,
                               CATSoftwareConfiguration * iConfig      = NULL);

  ~CATExtrapolNurbsCurve();

  void Run();

protected:
  //-----------------------------------------------------------------------
  //- Protected data
  //-----------------------------------------------------------------------
  CATGeoFactory   * _Factory;
  CATCurve        * _Crv;
  double            _Length;

  void InitData(const CATCrvParam              & iParamOnCrv,
                      CATSoftwareConfiguration * iConfig);

  //-------------------------------------------------------------------------
  // Protected methods for extrapolation
  //-------------------------------------------------------------------------
  CATBoolean FunctionsExtrapolation();

  CATBoolean C2BezPointsOnSide(const CATLONG32 & iSide,
                                     double    & oAlpha,
                                     double    & oBeta,
                                     double    * oCPs);

  void GetParamForC2(const CATLONG32 & iSide,
                           double    * oParamForC2,
                           double    & oParamFin);

  void C2BezPoints(const double & alpha,
                   const double & beta, 
                         double * TargetP,
                         double * TargetD,    
                         double * oP0,
                         double * oP1,
                         double * oP2, 
                         double * oP3,
                         double * oP4,
                         double * oP5,
                         double * oP6);

  CATBoolean TargetDerivatives(const CATLONG32 & Degree,
                                     double    * CPs, 
                                     double    * u,
                                     double    * oFnSDerivatives);

  //remplie _TabOfNurbs avec toutes les Curves servant a l'extrapolation
  void FillArrayOfNurbs(      CATKnotVector      * KnotVector,
                              double             * ExtrCPs,
                              CATMathSetOfPoints & LocCPs,
                              double             * LocWeights,
                        const CATLONG32            FirstVertex,
                        const CATLONG32            Rank);

  void CheckCurve();

  CATLONG32 IsClosedAndG1(CATLONG32& iDiagnostic) const;

private:
  //-----------------------------------------------------------------------
  //- Private data
  //-----------------------------------------------------------------------
  CATKnotVector        *  _KnotVector;
  CATLONG32               _IsRational;
  double               *  _Vertices;
  int                     _Dim; //3==Nupbs, 4==Nurbs
  //La Curve a-t'elle deja ete extrapole?
  CATLONG32               _IsExtrapolated; 
  //La Curve doit etre extrapole
  CATLONG32               _Extrapol;
  //Degre de la Nurbs extrapolee
  CATLONG32               _TargetDegree;
  CATFrFNurbsMultiForm ** _TabOfNurbs;

  //_ExtrapolDirection=0 : nearest side of iParamOnCrv will be used for extrapolation.
  //if _ExtrapolDirection<0, extrapolation at curve start, else if _ExtrapolDirection>0, at curve end.
  CATLONG32 _ExtrapolDirection;

  //Config de la courbe en entree : enumeration de tous ses problemes,...
  CATLONG32                  _CurveConfig[2];
  CATSoftwareConfiguration * _Config;
};

//-----------------------------------------------------------------------
//- Global functions - Do not use anymore. Use instead constructor and then call the Run method.
//-----------------------------------------------------------------------
ExportedByY30C3XGG CATExtrapolNurbsCurve * CreateExtrapolation(      CATGeoFactory *iFactory,
                                                                     CATNurbsCurve * ioCrv,
                                                               const double        & iLength,
                                                               const CATCrvParam   & iParamOnCrv);

ExportedByY30C3XGG CATExtrapolNurbsCurve * CreateExtrapolation(      CATGeoFactory * iFactory,
                                                                     CATPNurbs     * ioCrv,
                                                               const double        & iLength,
                                                               const CATCrvParam   & iParamOnCrv);

ExportedByY30C3XGG void Remove(CATExtrapolNurbsCurve *& ExtrapolOper);
#endif
