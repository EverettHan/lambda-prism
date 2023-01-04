#ifndef CATKNOTVECTORINTERNAL_H
#define CATKNOTVECTORINTERNAL_H

// COPYRIGHT DASSAULT SYSTEMES  2018
//=============================================================================
//
// Internal DS access on CATKnotVector
//
//=============================================================================
// 28/02/18 NLD Création pour isolation des accès internes et des services
//              que l'on ne veut pas exposer dans l'interface publique CAA de CATKnotVector
//              - la gestion des checks (but: suppression des transit par commun statique)
//              - la destruction des données d'optimisation
// 13/02/20 Q48 Add methods to get/set the knot-vector cache ("by-pass" for stability)
//=============================================================================
#include "CATIACGMLevel.h"

#include "YP00IMPL.h"


#include "CATKnotVector.h"

class CATCurve;
class CATSurface;

class CATSurfaceCGM;
class CATCurveCGM;
class CATCGMDebugImpl;
class CATTolerance;
class CATError;
//=============================================================================
class ExportedByYP00IMPL CATKnotVectorInternal
{
 // 3 classes amies utilisant DelOptimizationData()
 friend class CATSurfaceCGM;
 friend class CATCurveCGM;
 friend class CATCGMDebugImpl;

 friend class CATKnotVector;    // transitoire; tout sera fait par des Set

 public:

 typedef enum    {_CheckMonotonyWithTolerance_InactiveCheck = 1,
                  _CheckMaxKnotsCount_InactiveCheck         = 2} InactiveCheck;

                                       CATKnotVectorInternal();


             void                      SetInactiveCheck        (      InactiveCheck               iInactiveCheck     );

// avoids knot vector domain control for knot vectors not depending on scale
 static      void                      SetNotScaledKnotVector  (      CATKnotVector             & iKnotVector        );

/**
 * Redefines <tt>this</tt> as a non uniform CATKnotVector.
 * @param iDegree
 * The new degree of the polynomial basis.
 * @param iIsPeriodic
 * The new periodicity.
 * <br><b>legal values</b>0.
 * @param iKnotsCount
 * The new number of knot values specified for the knot vector. The number of arcs
 * is <tt>iKnotsCount - 1</tt>.
 * @param iKnots
 * The array of the new global parameter values at the end of each arc.
 * @param iMultiplicities
 * The array of the new corresponding multiplicities.
 * @param iIndexOffset
 * The new index for the first arc. 
 */
             void                      SetNonUniformKnotVector (      CATKnotVector             & iKnotVector        ,
                                                                const CATLONG32                 & iDegree            ,
                                                                const CATLONG32                 & iIsPeriodic        ,
                                                                const CATLONG32                 & iKnotsCount        ,
                                                                const double                   *  iKnots             ,
                                                                const CATLONG32                *  iMultiplicities    ,
                                                                const CATLONG32                   iIndexOffset       = 0);

/**
 * Redefines <tt>this</tt> as a uniform CATKnotVector .
 * @param iDegree
 * The new degree of the polynomial basis.
 * @param iIsPeriodic
 * The new periodicity.
 * <br><b>legal values</b>0.
 * @param iArcsCount
 * The new number of arcs.
 * @param iKnotStart
 * The new parameter value of the first knot.
 * @param iStep
 * The new uniform step value between two knots.
 * @param iIndexOffset
 * The new index for the first arc.
 */
             void                      SetUniformKnotVector    (      CATKnotVector             & iKnotVector        ,
                                                                const CATLONG32                 & iDegree            ,
                                                                const CATLONG32                 & iIsPeriodic        ,
                                                                const CATLONG32                 & iArcsCount         ,
                                                                const double                      iKnotStart         = 0.,
                                                                const double                      iStep              = 1.,
                                                                const CATLONG32                   iIndexOffset       = 0);

/**
 * Retrieves the current cache of the arc (to be used if strictly necessary for stability)
 */
             static CATBoolean         GetCurrentArcCache(const CATKnotVector & iKnotVec,
                                                                short         & oArcCache);

             static CATBoolean         GetCurrentArcCache(const CATSurface    * iSurface,
                                                          const CATBoolean      iGetU,
                                                          short               & oArcCache);

             static CATBoolean         GetCurrentArcCache(const CATCurve      * iCurve,
                                                                short         & oArcCache);

/**
 * Sets the current cache of the arc (to be used if strictly necessary for stability)
 */
             static void               SetCurrentArcCache(      CATKnotVector & ioKnotVec,
                                                          const short           iNewArcCache);

             static void               SetCurrentArcCache(      CATCurve      * ioCurve,
                                                          const short           iNewArcCache);
             
             static void               SetCurrentArcCache(      CATSurface    * ioSurface,
                                                          const CATBoolean      iSetU,
                                                          const short           iNewArcCache);

 protected:
 // Optimization data destruction
 // reserved use for class CATSurfaceCGM, CATCurveCGM, CATCGMDebugImpl
 // ==> protected with friend class declaration
 static      void                      DelOptimizationData     (      CATKnotVector             & iKnotVector        );

        // Attention les controles sont ici dependants des donnees membres _Check* et non plus des variables statiques
             CATError*                 ControlKnotVector       (      CATKnotVector             & iKnotVector        ,
                                                                      int                         iFreeDataIfError   ,
                                                                const CATTolerance             *  iTolObject         = 0,
                                                                      int                         iSpecialCaseStandardScaleAssumed = 0
                                                               );

 private:
        int      _CheckMonotonyWithTolerance;
        int      _CheckMaxKnotsCount;
};
#endif
