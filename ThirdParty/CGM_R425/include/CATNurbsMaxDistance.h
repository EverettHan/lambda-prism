// COPYRIGHT DASSAULT SYSTEMES 2000
//==========================================================================
//
// CATNurbsMaxDistance
//==========================================================================
//
// Usage notes:
//
//SMT1 4.6.21 Class purpose: For two Nurbs with the "same" parametrisation, where all inner knots have mult=degree, the maximum 
// distance taken over all pairs of corresponding control points is an upper bound for the maximal distance of the two Nurbs(citation needed).
// To get a more accurate upper bound, the Nurbs can be subdivided ("discretized") further.
// The idea is that this is a cheaper alternative to a 'full' MaxDistance computation. 
// In practice there is a balance to be had: If the discretization is too coarse, the upper bound is only a rough estimation which
// impacts the calling algorithm (e.g. OptimiseContinuity seeks to deform a Nurbs within some tolerance, which may require a fairly 
// precise MaxDistance). If the Nurbs is large, the act of discretization itself can infer considerable cost. Which argument wins out requires
// further study.
// _LocalDiscretization is a first step to get the best of both worlds, but maybe a dynamic refinement is needed.
//==========================================================================
// Jun.2000 PRG  Creation                                                PRG
// Nov.2000 PRG  methode ecart max entre 2 bipare
//               besoin : transfert des nurbs V4V5
//                        les 2 bipares sont supposees etre geometriquement
//                        au meme endroit.
//                        On effectue alors une discretisation des 2 espaces nodaux
//                        en N intervalles et on compare les 2 nuages de points
// 08/07/15 NLD  ActivateG1BoundaryCheck() remplace ActivateG1BoundayCheck()
// 31/07/15 NLD  Ajout DataInitialisationsFromInputData(), _TolObject, _Config, _CGMLevel
// 04/06/21 SMT1 Properly declare ComputeKnotsToInsertOneDir, add ComputeDeformedArcs & _LocalDiscretization
//========================================================================== 

#ifndef CATNurbsMaxDistance_H
#define CATNurbsMaxDistance_H

class CATFrFNurbsBipar;
class CATFrFNurbsMultiForm;
class CATMathPoint;
class CATMathVector;
class CATMathFunctionX;
class CATMathFunctionXY;
class CATKnotVector;
class CATMathSetOfPointsND;
class CATSoftwareConfiguration;
class CATTolerance;
class CATNurbsMaxMinDistance;
//-----------------------------------------------------------------------------
#include "YP00IMPL.h"
#include "CATCGMVirtual.h"
#include "CATDataType.h"
#include "CATBoolean.h"

class ExportedByYP00IMPL CATNurbsMaxDistance  : public CATCGMVirtual
{
  public :

  //-------------------  Constructeur ------------------- 
  // iMode : 0 isoparametrical computation thanks to a discretization
  //         1 isoparametrical computation thanks to knotInsertions
  CATNurbsMaxDistance(CATFrFNurbsBipar     * bipar    , 
                                                       CATLONG32              iMode    = 0);
  CATNurbsMaxDistance(CATFrFNurbsMultiForm * multiForm, 
                                                       CATLONG32              iMode    = 0);

  //-------------------  Destructeurs -------------------
  virtual    ~CATNurbsMaxDistance                     ();

  //-------------------   Run() -------------------  
    CATLONG32 Run                                     ();

  //-------------------   ActivateBoundaryCheck() -------------------
    void      ActivateG1BoundaryCheck                 ();

  //-------------------   SetIsoparametricalMaxDistanceComputation() -------------------  
    void      SetIsoparametricalMaxDistanceComputation(CATFrFNurbsMultiForm* multiFormToCompare   ,
                                                       CATLONG32             discretizationFactor = 1,
                                                       CATBoolean            iLocalDiscretization = FALSE,
                                                       CATBoolean            iReset = FALSE);

  //-------------------   SetIsoparametricalMaxDistanceComputation() -------------------  
    void      SetIsoparametricalMaxDistanceComputation(CATFrFNurbsBipar    * biparToCompare       ,
                                                       CATLONG32             discretizationFactor = 1,
                                                       CATBoolean            iLocalDiscretization = FALSE,
                                                       CATBoolean            iReset = FALSE);

    void      SetSlidingConvergenceMode               (CATLONG32             iSlidingMode         = 1);


  //-------------------   GetMaxDistance() -------------------
    double    GetMaxDistance                          ();

  //-------------------   GetG1Deviation() -------------------
    double    GetG1Deviation                          ();

 
 
/**
* @deprecated
*/
    void      SetSupport                              (CATFrFNurbsBipar     * supportBipare        );

    int       SetSupportEquations                     (CATMathFunctionXY    * iSupportX            ,
                                                       CATMathFunctionXY    * iSupportY            ,
                                                       CATMathFunctionXY    * iSupportZ            );
 

  //------------------- enable us to stop the measurement as soon as we find a value above the authorized deviation -------------------
    void      SetMaximumDeviation                     (double                 authorizedMaximumDeviation, CATBoolean iWholeComputationRequested = FALSE);

  //------------------- optimisation afin de calculer en premier les dev. aux limites d'arc ayant changer de continuite -------------------
  //------------------- si deviation superieure a la valeur seuil en ces points, inutile d'aller plus loin -------------------
    void      SetChangedKnotNumbers                   (CATLONG32              nbChangedKnots      ,
                                                       CATLONG32            * iNumChangedKnots    );

  //Do not used. 
  // Special inputs form CATOptimizeContinuities
    int       AddMeasurePoints                  (const CATMathSetOfPointsND * iUVPoints           ,
                                                 const CATMathPoint        ** iTargetPoints       ,
                                                 const CATMathVector       ** iTargetNormal       ,
                                                 const double               * iTolPoint           ,
                                                 const double               * iTolAngle           );

  //Do not used. 
  // Special inputs form CATOptimizeContinuities
  //1 means checks are OK, 0 means that at least one measure is incorrect
    int       GetStatusOnSpecificsMeasurePoints ();

    void      SetDiscreetMeasureMode            (      int                    iActivate           = 1);

    void GetBrokenTol(CATBoolean *&ioTolBrokenU, CATBoolean *&ioTolBrokenV);

  private :
    CATLONG32 DataInitialisations               ();
    CATLONG32 DataInitialisationsFromInputData  ();

    CATLONG32 ComputeIsoparametricalMaxDistance ();
    CATLONG32 ComputeKnotInsertionMaxDistance   ();
    CATLONG32 ComputeKnotsToInsert              ();

    CATLONG32 ComputeBiparPoints                (CATFrFNurbsBipar    * bipar            ,
                                                 double              * x                ,
                                                 double              * y                ,
                                                 double              * z                );
    CATLONG32 ComputeMultiFormPoints            (CATFrFNurbsMultiForm* multiForm        ,
                                                 double              * x                ,
                                                 double              * y                ,
                                                 double              * z                );


    CATLONG32 MakeInsertionsOnBipar             (CATFrFNurbsBipar    * bipar            ,
                                                 CATFrFNurbsBipar    * biparWithKnotsInsertion,
                                                 CATLONG32           & nbCPs            );

    CATLONG32 MakeInsertionsOnMultiForm         (CATFrFNurbsMultiForm* multiForm        ,
                                                 CATFrFNurbsMultiForm* multiFormWithKnotsInsertion,
                                                 CATLONG32           & nbCPs            );
    
    CATLONG32 ComputeMaxDistance                (CATLONG32             nbCPs            ,
                                                 CATMathPoint        * initialCPs       ,
                                                 CATMathPoint        * newCPs           ,
                                                 double              & maxDistance      );

    CATLONG32 MFSlidingMaxDistanceComputation   ();
    CATLONG32 BPSlidingMaxDistanceComputation   ();

    CATLONG32 ComputeErrorAtInnerDifferentKnotsOnMultiForms
                                                (CATLONG32           & deviationIsBiggerThanTolerance);

    CATLONG32 CheckDiscretizationFactor         (CATLONG32           & discretizationFactor);
    CATLONG32 CheckDiscretizationFactorOnKV     (CATKnotVector       * kv               ,
                                                 CATLONG32           & discretizationFactor);

    CATLONG32 ComputeG1CrvBoundaryDeviation     (double              & G1BoundaryDeviation);

    CATLONG32 ComputeG1SurfaceBoundaryDeviation (CATFrFNurbsBipar    * biparToCompareWithInsertedKnots,
                                                 double              & G1SurfaceBoundaryDeviation);

    // iDiag vaut 0 si tangentes de norme non nulles
    //            1 si tangentes de normes nulles ou quasi nulle auquel cas,
    //            cela ne sert à rien de calculer de deviation.
    CATLONG32 ComputeG1DeviationAtAPoint        (CATMathPoint        * initialCPs  ,
                                                 CATMathPoint        * newCPs      ,
                                                 CATLONG32             shift       ,
                                                 CATLONG32           & diag        , //  0: tangentes de norme non nulles, 1: nulles ou quasi nulles
                                                 double              & G1Deviation );

    int       ComputeSpecificMeasures();

    CATLONG32 ComputeKnotsToInsertOneDir        (CATKnotVector       *  iKV                  ,
                                                 CATKnotVector       *  iSubKV               ,
                                                 CATLONG32            & oNbInsertKnots       ,
                                                 double              *& oInsertKnots         ,
                                                 CATLONG32           *& oInsertMult          );

    CATLONG32 ComputeDeformedArcs               (CATKnotVector       *  iKV                  ,
                                                 CATKnotVector       *  iSubKV               ,
                                                 CATBoolean          *& oDeformedArcs        );

    void ElevateToSameDegree();
    //===================================================================================================
    // DATA
    //===================================================================================================

    private:

    CATSoftwareConfiguration    * _Config;
    int                           _CGMLevel;
const CATTolerance              * _TolObject;
    CATFrFNurbsBipar            * _bipar;
    CATFrFNurbsBipar            * _initialBiparWithKnotInsertions;
    CATFrFNurbsBipar            * _biparToCompare;
    CATFrFNurbsBipar            * _biparToCompareWithInsertedKnots;

    CATFrFNurbsMultiForm        * _multiForm;
    CATFrFNurbsMultiForm        * _initialMultiFormWithKnotInsertions;
    CATFrFNurbsMultiForm        * _multiFormToCompare;
    CATFrFNurbsMultiForm        * _multiFormToCompareWithInsertedKnots;

    double                        _maxDistance;

    CATBoolean                    _LocalDiscretization;
    CATLONG32                     _discretizationFactor;
    CATLONG32                     _nbDiscretisationPoints;
    CATLONG32                     _nbDiscretisationPointsAlongU;
    CATLONG32                     _nbDiscretisationPointsAlongV;

    //CATBoolean                    *_TolBrokenU, *_TolBrokenV; 

    double                      * _x1;
    double                      * _y1;
    double                      * _z1;

    CATBoolean                    _ReferencePointsComputed;
    CATLONG32                     _iMode;
    CATLONG32                     _iSlidingMode;
    CATNurbsMaxMinDistance*       _slidingAnalysis;

    CATLONG32                     _nbInsertKnotsU;
    CATLONG32                     _nbInsertKnotsV;
    double                      * _insertKnotsU;
    double                      * _insertKnotsV;
    CATLONG32                   * _insertMultsU;
    CATLONG32                   * _insertMultsV;
 
    CATLONG32                     _nbCPs;
    CATMathPoint                * _CPs;

    CATLONG32                     _iDim;
    CATLONG32                     _iDimMF;

    CATLONG32                     _optimisationActive;

    double                        _authorizedMaximumDeviation;
    CATLONG32                     _wholeComputationRequested;

    CATLONG32                     _iCPMax;

    CATFrFNurbsBipar            * _supportBipare;

    CATMathFunctionXY           * _supportX;
    CATMathFunctionXY           * _supportY;
    CATMathFunctionXY           * _supportZ;

    CATMathPoint                * _initial3DCPs;
    CATMathPoint                * _new3DCPs;

    CATMathFunctionX            * _f1x;
    CATMathFunctionX            * _f1y;
    CATMathFunctionX            * _f1z;

    CATMathFunctionX            * _f2x;
    CATMathFunctionX            * _f2y;
    CATMathFunctionX            * _f2z;


    // For optimization
    CATLONG32                    _nbChangedKnotsU;
    CATLONG32                  * _iNumChangedKnotsU;
    
    // G1 Checks
    CATLONG32                    _G1BoundaryCheckIsActive;
    double                       _G1BoundaryMaxDeviation;

    //Data specifics to AddMeasurePoints
    const CATMathSetOfPointsND * _UVPoints;
    const CATMathPoint        ** _TargetPoints;
    const CATMathVector       ** _TargetNormal;
    const double               * _TolPoint;
    const double               * _TolAngle;
    int                          _SpecificCheckOK;

    //===============================================================
    // stat and Debug
    static CATLONG32             _Ref;         // name of the intance
    CATLONG32                    _nbRuns;      // nb runs done for this instance

};
#endif







