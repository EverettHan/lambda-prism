// COPYRIGHT DASSAULT SYSTEMES 1997
//============================================================================
//
// CATMathSystemXYs:
// General Implementation class of non linear 
// 2x2 systems with SEPARATE variables
//
//============================================================================
// ??/??/?? ??? Creation
// 15/11/13 NLD Suppression des constructeurs invalides ne pouvant fonctionner
//                (faux constructeur par defaut, CATMathSystemXYs_01 (FAIT)
//                 faux constructeur par copie,  CATMathSystemXYs_03 (EN ATTENTE))
//              Declaration en Private, pour inaccessibilite,
//                - du vrai constructeur par defaut,
//                - du vrai constructeur par copie,
//                (ceux fournis par le compilateur ne pouvant fonctionner)
//              Colonnage
// 19/11/13 NLD Ajout Init()
//              Ajout evaluateurs par intervalles avec rescale:
//              - EvalFX(), EvalGX(), EvalFY(), EvalGY()
//              - EvalFXFirstDeriv(), EvalGXFirstDeriv(), EvalFYFirstDeriv(), EvalGYFirstDeriv()
//              Ajout evaluateurs sur double      avec rescale::
//              - EvalFX(), EvalGX(), EvalFY(), EvalGY()
//              - EvalFXFirstDeriv(), EvalFYFirstDeriv(), EvalGXFirstDeriv(), EvalGYFirstDeriv()
//                (a un seul argument)
//                (a ne pas confondre avec les signatures EvalFirstDeriv*() a deux arguments
//                 qui rendent les derivees partielles de F et G)
// 27/11/13 NLD Ajout RSolveInit() et RSolveExit() pour debug
// 27/04/17 f1z Ajout NewtonStep()
//============================================================================

#ifndef CATMathSystemXYs_H
#define CATMathSystemXYs_H

#include "YN000FUN.h"

#include "CATMathSystemXY.h"

class CATMathAttrExclusion2D;
class CATMathAttrList;
class CATMathFunctionX;
class CATMathInterval;
class CATMathInterval2D;
class CATMathIntervalND;
class CATMathPoint2D;
class CATMathSetOfPointsND;
class CATSoftwareConfiguration;

// #define CATMathSystemXYs_KeepInvalidConstructor_01
#define CATMathSystemXYs_KeepInvalidConstructor_03 " en attente de suppression, voir AdvancedMathematics.tst"

class ExportedByYN000FUN CATMathSystemXYs: public CATMathSystemXY
{
 private:
   // <--- DO NOT USE --->
                                            CATMathSystemXYs(const CATMathSystemXYs            & P);
   // <--- DO NOT USE --->
                                            CATMathSystemXYs();


 public:

   //-----------------------------------------------------------------
   // Constructors
   //-----------------------------------------------------------------
#ifdef CATMathSystemXYs_KeepInvalidConstructor_01
// <--- DO NOT USE --->
// CATMathSystemXYs_01 (please do not ever change constructors numbering)
                                            CATMathSystemXYs(      CATSoftwareConfiguration   *  iConfig    ,
                                                             const CATTolerance                & iTolObject = CATGetDefaultTolerance(),
                                                             const CATMathAttrList            *  iattr      = NULL);
#endif

// CATMathSystemXYs_02 (please do not ever change constructors numbering)
                                            CATMathSystemXYs(      CATSoftwareConfiguration   *  iConfig    , 
                                                             const CATMathFunctionX           *  iFX        ,
                                                             const CATMathFunctionX           *  iGX        ,
                                                             const CATMathFunctionX           *  iFY        ,
                                                             const CATMathFunctionX           *  iGY        ,
                                                             const CATTolerance                & iTolObject = CATGetDefaultTolerance(),
                                                             const CATMathAttrList            *  iattr      = NULL);

#ifdef CATMathSystemXYs_KeepInvalidConstructor_03
// <--- DO NOT USE --->
// CATMathSystemXYs_03 (please do not ever change constructors numbering)
                                            CATMathSystemXYs(      CATSoftwareConfiguration   *  iConfig,
                                                             const CATMathSystemXYs            & P        );
#endif   
   //-----------------------------------------------------------------
   // Information methods
   //-----------------------------------------------------------------

   virtual       CATBoolean                 IsAKindOf         (const CATMathClassId              iClassId ) const;
   virtual       CATBoolean                 IsOption          (const CATMathOption               iOption  ) const;
   virtual       CATMathClassId             IsA               ()                                            const;
   
   //-----------------------------------------------------------------
   // Evaluators
   //-----------------------------------------------------------------

   virtual       CATMathPoint2D             Eval              (const CATMathPoint2D            & Pt       ) const;
   virtual       double                     EvalF             (const CATMathPoint2D            & Pt       ) const;
   virtual       double                     EvalG             (const CATMathPoint2D            & Pt       ) const;

   // Evaluation of functions   on doubles
   virtual       double                     EvalF             (const double                    & x        ,
                                                               const double                    & y        ) const;
   virtual       double                     EvalG             (const double                    & x        ,
                                                               const double                    & y        ) const;
   //                                                                                                              // par souci de simplification,
   //                                                                                                              // et pour faciliter la migration
   //                                                                                                              // depuis les evaluations directes sur _FX, _FY, _GX, _GY
   //                                                                                                              // on ne precise qu'un argument x ou y
   //                                                                                                              // a EvalFX(), EvalFY(), EvalGX(), EvalGY(). NLD201113
   //                                                                                                              // idem pour EvalFXFirstDeriv(), ...
                 double                     EvalFX            (const double                    & x        ) const;
                 double                     EvalFY            (const double                    & y        ) const;
                 double                     EvalGX            (const double                    & x        ) const;
                 double                     EvalGY            (const double                    & y        ) const;
   //                                                                                                              // (serie de methodes a signature simplifiee NLD201113)
   //                                                                                                              // ne pas confondre EvalFXFirstDeriv et EvalFXFirstDeriv
                 double                     EvalFXFirstDeriv  (const double                    & x        ) const;
                 double                     EvalFYFirstDeriv  (const double                    & y        ) const;
                 double                     EvalGXFirstDeriv  (const double                    & x        ) const;
                 double                     EvalGYFirstDeriv  (const double                    & y        ) const;


   // Evaluation of derivatives on doubles
   //                                                                                                              // (serie de methodes standard CQI)
   // ATTENTION aux notations:
   //         EvalFirstDerivFX calcule la premiere derivee par rapport a la variable x de F (F au sens de la fonction rendue par EvalF()
   //                          et non pas la derivee de la fonction _FX
   //                          (il se trouve que c'est la meme chose)
   //         EvalFirstDerivFY calcule la premiere derivee par rapport a la variable y de F (F au sens de la fonction rendue par EvalF()
   //                          et non pas la derivee de la fonction _FY
   //                          (c'est l'oppose)
   //         Idem pour EvalGXFirstDeriv et EvalFirstDerivGY
   // 
   virtual       double                     EvalFirstDerivFX  (const double                    & x        ,
                                                               const double                    & y        ) const;
   virtual       double                     EvalFirstDerivFY  (const double                    & x        ,
                                                               const double                    & y        ) const;

   virtual       double                     EvalFirstDerivGX  (const double                    & x        ,
                                                               const double                    & y        ) const;
   virtual       double                     EvalFirstDerivGY  (const double                    & x        ,
                                                               const double                    & y        ) const;
   
   virtual       double                     EvalSecondDerivFX2(const double                    & x        ,
                                                               const double                    & y        ) const;
   virtual       double                     EvalSecondDerivFXY(const double                    & x        ,
                                                               const double                    & y        ) const;
   virtual       double                     EvalSecondDerivFY2(const double                    & x        ,
                                                               const double                    & y        ) const;

   virtual       double                     EvalSecondDerivGX2(const double                    & x        ,
                                                               const double                    & y        ) const;
   virtual       double                     EvalSecondDerivGXY(const double                    & x        ,
                                                               const double                    & y        ) const;
   virtual       double                     EvalSecondDerivGY2(const double                    & x        ,
                                                               const double                    & y        ) const;   
   //
   // Evaluator of function and derivatives at the same time (see base class for details):
   //
   virtual       void                       EvalF             (const double                      u        ,
                                                               const double                      v        , 
                                                               const CATMathOption               iOptions ,
                                                                     double                   *  f        ,
                                                                     double                   *  fx       = 0,
                                                                     double                   *  fy       = 0,
                                                                     double                   *  fx2      = 0,
                                                                     double                   *  fxy      = 0,
                                                                     double                   *  fy2      = 0) const;
   virtual       void                       EvalG             (const double                      u        ,
                                                               const double                      v        , 
                                                               const CATMathOption               iOptions ,
                                                                     double                   *  f        ,
                                                                     double                   *  fx       = 0,
                                                                     double                   *  fy       = 0,
                                                                     double                   *  fx2      = 0,
                                                                     double                   *  fxy      = 0,
                                                                     double                   *  fy2      = 0) const;

   //
   // Multi-evaluation of function and derivatives on a regular 
   // grid of Nu x Nv points delimited by  iDomain (see base class for details):
   //
   virtual       void                       EvalF             (const CATMathIntervalND         & iDomain  ,
                                                               const CATLONG32                *  NbPoints ,
                                                               const CATMathOption               iOptions ,
                                                                     double                   *  f        ,
                                                                     double                   *  fx       = 0,
                                                                     double                   *  fy       = 0,
                                                                     double                   *  fx2      = 0,
                                                                     double                   *  fxy      = 0,
                                                                     double                   *  fy2      = 0) const;

   virtual       void                       EvalG             (const CATMathIntervalND         & iDomain  ,
                                                               const CATLONG32                *  NbPoints ,
                                                               const CATMathOption               iOptions ,
                                                                     double                   *  f        ,
                                                                     double                   *  fx       = 0,
                                                                     double                   *  fy       = 0,
                                                                     double                   *  fx2      = 0,
                                                                     double                   *  fxy      = 0,
                                                                     double                   *  fy2      = 0) const;


   // Evaluation methods on intervals (standard implementation not needing derivation)                                                                                 NLD191113
                 CATMathInterval            EvalFX            (const CATMathInterval           & iDX         ) const;
                 CATMathInterval            EvalGX            (const CATMathInterval           & iDX         ) const;
                 CATMathInterval            EvalFY            (const CATMathInterval           & iDY         ) const;
                 CATMathInterval            EvalGY            (const CATMathInterval           & iDY         ) const;
                 CATMathInterval            EvalFXFirstDeriv  (const CATMathInterval           & iDX         ) const;
                 CATMathInterval            EvalGXFirstDeriv  (const CATMathInterval           & iDX         ) const;
                 CATMathInterval            EvalFYFirstDeriv  (const CATMathInterval           & iDY         ) const;
                 CATMathInterval            EvalGYFirstDeriv  (const CATMathInterval           & iDY         ) const;


 // protected methods
 protected:

   //                                                                                                       // derivation de la methode de la classe mere. non derivee au 181113
   //                                                                                                       // *** XScale: l'intervalle D doit avoir ete ramene
   //                                                                                                       // ***         au standard (puissance 1 du Scale)
   //                                                                                                       // *** par ComputeScaledDomain().                          NLD191113
   virtual       CATLONG32                  ISolve            (const CATMathInterval2D         & D        ,
                                                               const CATMathAttrList          *  attributes);
   
   //                                                                                                       // methode specifique, absente dans classe mere, mais derivee au 181113
   //                                                                                                       // *** XScale: l'intervalle D doit avoir ete ramene
   //                                                                                                       // ***         au standard (puissance 1 du Scale)
   //                                                                                                       // *** par ComputeScaledDomain().                          NLD191113
   virtual       CATLONG32                  RSolve            (const CATMathInterval2D         & D        ,
                                                               const CATLONG32                 & divider  ,
                                                               const CATMathInterval           & IF       ,
                                                               const CATMathInterval           & IG       ,
                                                               const CATMathInterval           & IDF      ,
                                                               const CATMathInterval           & IDG      ,
                                                               const CATMathInterval           & IDF2     ,
                                                               const CATMathInterval           & IDG2     );


   //                                                                                                       // to be called by RSolve() derivation at RSolve() entrance
                 void                       RSolveInit        (const CATMathInterval2D         & D        ,
                                                               const CATLONG32                 & divider
                                                              );
   //                                                                                                       // to be called by RSolve() derivation at RSolve() exit
                 void                       RSolveExit        (const CATMathInterval2D         & D        ,
                                                               const CATLONG32                 & divider
                                                              );
   //                                                                                                       // methode specifique, absente dans classe mere, mais derivee au 181113
   //                                                                                                       // *** XScale: l'intervalle D doit avoir ete ramene
   //                                                                                                       // ***         au standard (puissance 1 du Scale)
   //                                                                                                       // *** par ComputeScaledDomain().                          NLD191113
   virtual       CATLONG32                Solve_IntervalNewton(const CATMathInterval2D         & D        );
   
   //                                                                                                       // methode specifique, absente dans classe mere, mais derivee au 181113
   //                                                                                                       // *** XScale: le point Pt doit avoir ete ramene
   //                                                                                                       // ***         au standard (puissance 1 du Scale)
   //                                                                                                       // *** dans  un intervalle issu de ComputeScaledDomain().  NLD191113
   virtual       CATLONG32                Solve_Newton        (const CATMathPoint2D            & Pt       );
   
   //                                                                                                       // methode specifique, absente dans classe mere, non  derivee au 181113
   //                                                                                                       // *** XScale: l'intervalle D doit avoir ete ramene (comme le point Pt)
   //                                                                                                       // ***         au standard (puissance 1 du Scale)
   //                                                                                                       // *** par ComputeScaledDomain().                          NLD191113
   virtual       CATLONG32                Solve_SafeNewton    (const CATMathPoint2D            & Pt       ,
                                                               const CATMathInterval2D         & D        );
   
   //                                                                                                       // methode specifique, absente dans classe mere, mais derivee au 181113
   //                                                                                                       // *** XScale: l'intervalle D doit avoir ete ramene
   //                                                                                                       // ***         au standard (puissance 1 du Scale)
   //                                                                                                       // *** par ComputeScaledDomain().                          NLD191113
   virtual       CATLONG32                Solve_MaxDepth      (const CATMathInterval2D         & D        );   

   //                                                                                                       // methode specifique, absente dans classe mere, non  derivee au 181113
   virtual       CATLONG32                AddRoot             (const CATMathPoint2D            & Pt       );

   //                                                                                                       // methode specifique, absente dans classe mere            NLD210617
                 void                     NewtonStep          (const short                       iCGMLevel    ,
                                                               const CATMathInterval           & iDX          ,
                                                               const CATMathInterval           & iDY          ,
                                                               const CATMathInterval           & iImageDerivFX,
                                                               const CATMathInterval           & iImageDerivFY,
                                                               const CATMathInterval           & iImageDerivGX,
                                                               const CATMathInterval           & iImageDerivGY,
                                                                     CATMathInterval           & oJacobian    ,
                                                                     CATMathInterval           & oNewtonDX    ,
                                                                     CATMathInterval           & oNewtonDY    ,
                                                                     double                    & oTolWidthX   ,
                                                                     double                    & oTolWidthY   ) const;
 // private methods
 private:
                 void                     Init();

 protected:
           const CATMathFunctionX       * _FX       ,
                                        * _GX       ,
                                        * _FY       ,
                                        * _GY       ;
           const CATMathAttrExclusion2D * _exclusion;
                 double                   _MinWidthU,
                                          _MinWidthV;

};

#endif
