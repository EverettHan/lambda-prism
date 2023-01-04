/*-*-c++-*-*/
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATExtrapolSplineCurve :
// Class for extrapoling a SplineCurve beyond a box.
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// 27/02/18 R1Y Added functions for the linear extrapolation of splines.
//=============================================================================

#ifndef CATExtrapolSplineCurve_H 
#define CATExtrapolSplineCurve_H 

#include "Y30C3XGG.h"

#include "CATMathDef.h"
#include "CATCGMVirtual.h"
#include "CATGeoOpDebug.h"

class CATKnotVector;
class CATCurve;
class CATSplineCurve;
class CATPSpline;
class CATGeoFactory;
class CATMathVector;
class CATMathVector2D;
class CATMathSetOfPointsND;
class CATCrvParam;
class CATSoftwareConfiguration;

class ExportedByY30C3XGG CATExtrapolSplineCurve   : public CATCGMVirtual
{
public:
  //-----------------------------------------------------------------------
  //- Public Methods
  //-----------------------------------------------------------------------
  CATExtrapolSplineCurve (     CATGeoFactory            * iFactory   ,
                               CATSplineCurve           * ioCrv      ,
                         const double                   & iLength    ,
                         const CATCrvParam              & iParamOnCrv,
                               CATLONG32                  iSide      = 0 ,
                               CATSoftwareConfiguration * iConfig    = NULL);

  CATExtrapolSplineCurve (     CATGeoFactory            * iFactory   ,
                               CATPSpline               * ioCrv      ,
                         const double                   & iLength    ,
                         const CATCrvParam              & iParamOnCrv,
                               CATLONG32                  iSide      = 0 ,
                               CATSoftwareConfiguration * iConfig    = NULL);


  ~CATExtrapolSplineCurve();
  
  void Run ();
  
protected:
  //-----------------------------------------------------------------------
  //- Protected data
  //-----------------------------------------------------------------------
  CATGeoFactory   * _Factory;
  CATCurve        * _Crv;
 
private:
  //-----------------------------------------------------------------------
  //- Private data
  //-----------------------------------------------------------------------
  // Donnees pour extrapolation
  CATLONG32       _Extrapol;
  double          _Length;
  double          _GlobalParamOnCrv;
  CATLONG32       _Dimension; 
  CATLONG32       _IsExtrapolated;
  //_ExtrapolDirection=0 : nearest side of iParamOnCrv will be used for extrapolation.
  //if _ExtrapolDirection<0, extrapolation at curve start, else if _ExtrapolDirection>0, at curve end.
  CATLONG32       _ExtrapolDirection;

  CATSoftwareConfiguration * _Config;

  CATCurve * Convert ();
  void UpdateSplineWithNurbs (CATCurve *iNurbs);
  void UpdateSplineDataForLinearExtrapol(const CATLONG32              iStartIndex,
                                         const CATLONG32              iEndIndex,
                                               CATMathSetOfPointsND & ioTangents,
                                               CATMathSetOfPointsND & ioSecondDerivs) const;

  GEOPDEBUG_CMD(void Debug_CheckSplineDataForLinearExtrapol(const CATMathSetOfPointsND         & iTangents,
                                                            const CATMathSetOfPointsND         & iSecondDerivs,
                                                            const CATLONG32                      iExtrapolIndex,
                                                            const double               * const   iAdjacentTangent) const);
};


//-----------------------------------------------------------------------
//- Global functions
//-----------------------------------------------------------------------
//iSide=0 : nearest side of iParamOnCrv will be used for extrapolation.
//if iSide<0, extrapolation at curve start, else if iSide>0, at curve end.
ExportedByY30C3XGG CATExtrapolSplineCurve * CreateExtrapolation(CATGeoFactory *iFactory,
                                                                CATSplineCurve * ioCrv,
                                                                const double & iLength,
                                                                const CATCrvParam & iParamOnCrv,
                                                                CATLONG32 iSide=0,
                                                                CATSoftwareConfiguration * iConfig=0);

ExportedByY30C3XGG CATExtrapolSplineCurve * CreateExtrapolation(CATGeoFactory *iFactory, CATPSpline * ioCrv,
                                                                const double &iLength,
                                                                const CATCrvParam & iParamOnCrv,
                                                                CATLONG32 iSide=0,
                                                                CATSoftwareConfiguration * iConfig=0);

ExportedByY30C3XGG void Remove(CATExtrapolSplineCurve *& ExtrapolOper);


#endif
