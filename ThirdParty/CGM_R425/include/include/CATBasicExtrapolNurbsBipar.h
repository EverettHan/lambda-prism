// COPYRIGHT DASSAULT SYSTEMES 1997
//==========================================================================
//
// CATBasicExtrapolNurbsBipar :
// extrapolation of a nurbsbipar on a part of a u or v isoparametric.
// We get a nurbsbipar with the same knotvector along the isoparametric
// The second direction s knotvector s degree is 1 or 2, which is
// the continuity order that is required. 
// The control points are located computed so that the acr length
// is equal to iExtrapolationParameter.
// The extrapolation is made so that we get a G1 or G2 continuity along
// the isoparametric.
// 
//==========================================================================
// Feb 99  Creation                          Pierre Garcon
//==========================================================================
// An instance of the class CATBasicExtrapolNurbsBipar will be built
// thanks to :
//  - const   CATFrFNurbsBipar* iInitialNurbsBipar :
//              a pointer on the initial CATFrFNurbsBipar,
//  - a CATLONG32 iSideOfExtrapol : 
//             0 if the extrapolation has to be done on a u-Isoparametric
//             1 if the extrapolation has to be done on a v-Isoparametric
//  - double  iIsoParameter : definition value of the isopar
//  - double  iAcrossParamLimInf : inferior limit for the second parameter
//  - double  iAcrossParamLimSup : superior limit for the second parameter
//  - double  iExtrapolationParameter :
//                  for G2 : length factor for the extrapolation (parameter)
//                  for G1 : effective 3d length (delta param can be different)
// - CATLONG32    iContinuityOrder= 1 or 2 :
//           1 for C1 continuity
//           2 for C2 continuity
// - CATLONG32    iTransitionOrientation = 1 or -1
//           indicates if the extrapolation is to be done forwards or
//           backwards (coherent with the 2nd parameter).
//
//==========================================================================
// JSX 2011 Juillet : deplacement dans GeometricOperators
// JSX 2011 Aout    : Ajout de Software et Traitement des rationelles 
// JSX 2017 Mars    : Modif pour CGMReplay ( pour debug uniquement !)
// Q48 2017 Nov     : Add new methods for quadratic extrapolation (PS-Direct)
//                      - activated via SetStartingIndexOnBorder method
//==========================================================================
#ifndef CATBasicExtrapolNurbsBipar_H
#define CATBasicExtrapolNurbsBipar_H

#include "GeoNurbsTools.h"
//#include "FrFOpeSur.h"
#include "CATDataType.h"
#include "CATBoolean.h"
#include "CATCGMVirtual.h"
class CATFrFNurbsBipar;
class CATMathPoint;
class CATMathVector;
class CATKnotVector;
class CATTolerance;
class CATSoftwareConfiguration;
//--------------------------------------------------------------------------
class ExportedByGeoNurbsTools CATBasicExtrapolNurbsBipar  : public CATCGMVirtual
  {
  public:
    friend class  CATBasicExtrapolNurbsBiparOperator;
    CATBasicExtrapolNurbsBipar(CATSoftwareConfiguration *iConfig,
                               CATFrFNurbsBipar* iInitialNurbsBipar, 
                               CATLONG32    iSideOfExtrapol,
                               double  iIsoParameter,
                               double  iAcrossParamLimInf,
                               double  iAcrossParamLimSup,
                               double  iExtrapolationParameter,
                               CATLONG32    iContinuityOrder=1,
                               CATLONG32    iTransitionOrientation=1);

    virtual ~CATBasicExtrapolNurbsBipar();

    void Run();

    void SetMaxExtrapolationLength(const double iMaxLength);
    void SetStartingIndexOnBorder(const CATLONG32 iStartingIndex);
    void SetExtrapolationParameter(const double iNewExtrapolationParameter);

    CATFrFNurbsBipar* GetExtrapolatedNurbsBipar();

  protected :
    void RunOperator();
    // fonctions internes
    void ComputeTrimmedNurbsBipar();
    
    void ComputeExtrapolatedNurbsBipar();
    void ComputeExtrapolatedNurbsBipar1();
    void ComputeExtrapolatedNurbsBipar2();

    void SetKVs();
    void ComputeContinuityFactors();
    
    void ComputeControlPoints1();
    void ComputeControlPoints2();

    CATBoolean ComputeReferenceRowData(const CATLONG32       iIndex,
                                       const CATLONG32       iStepAlongCP,
                                       const CATLONG32       iOffsetCP,
                                       const CATLONG32       iStepInsideCP,
                                             CATLONG32     & oRefIndexBorder,
                                             CATLONG32     & oRefIndexInside,
                                             CATMathVector & oRefDirection,
                                             double        & oRefDirectionNorm) const;

    void G1Computation(const short iMode, const CATMathPoint & P0, const CATMathPoint & P1,CATMathPoint & newP1);

    void G2Computation(const CATMathPoint& P0, const CATMathPoint& P1, const CATMathPoint& P2,
                       const double& localLengthD2,
                       CATMathPoint& newP1, CATMathPoint& newP2);

    void ComputeLengths();
    double D1Computation(const CATMathPoint& P0, const CATMathPoint& P1);
    double D2Computation(const CATMathPoint& P0, const CATMathPoint& P1, const CATMathPoint& P2);


    void GetPreviousKVs();

    // DATA
  protected:

     // IN
    CATSoftwareConfiguration *_Config;
    CATFrFNurbsBipar* _initialNurbsBipar; 
    CATLONG32         _iSideOfExtrapol;
    double            _iIsoParameter;
    double            _iAcrossParamLimInf;
    double            _iAcrossParamLimSup;
    double            _iExtrapolationParameter;
    CATLONG32         _iContinuityOrder;
    CATLONG32         _iTransitionOrientation;

    CATBoolean        _iMaxExtrapolationParameterSet;
    double            _iMaxExtrapolationParameter;

    CATBoolean        _iStartingIndexSet;
    CATLONG32         _iStartingIndex;

    // out
    CATFrFNurbsBipar* _extrapolatedNurbsBipar;


    // Internal

    double            _iExtrapolationParameterQuadric;
    CATLONG32         _iSignExtrapol;
    CATLONG32         _iModeG2;
    double            _SommeLambdas;
    double            _LambdaSol;


    CATKnotVector*    _KVU;
    CATKnotVector*    _KVV;
    CATLONG32         _nbUCPs;
    CATLONG32         _nbVCPs;

    CATKnotVector*    _newKVU;
    CATKnotVector*    _newKVV;
    CATLONG32         _newNbUCPs;
    CATLONG32         _newNbVCPs;

    CATKnotVector*    _newKV;
    CATLONG32         _newNbCPs;
    CATKnotVector*    _acrossKV;
    CATLONG32         _nbCPsAcross;
    CATKnotVector*    _previousKV;

    double            _newLength;

    double            _C1Factor;
    double            _C2Factor1, _C2Factor2, _C2Factor3;

    double*           _lengths1;
    double            _meanLength1;
    double*           _lengths2;
    double            _meanLength2;
    CATBoolean        _Quadratic;

    CATMathPoint* _CPs;
    CATMathPoint* _newCPs;
    double        *_Weights;
    double        *_newWeights;

    CATBoolean _InvalidExtrapolation; // extrapolation impossible degenerée ou poids negatif 

    const CATTolerance *_Tol;
  };
#endif
