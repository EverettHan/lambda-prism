#ifndef CATMathPiecewiseXY_h
#define CATMathPiecewiseXY_h
// COPYRIGHT DASSAULT SYSTEMES 1997
//===================================================================
//
// CATMathPiecewiseXY
// Class of piecewise functions of two variables
//
//===================================================================
// 16/12/08 NLD Ajout _InvMeanSlopeU,
//                    _InvMeanSlopeV
//              Ajout UpdateOptimizationData()
// 22/12/08 NLD Ajout _SpyGlobalToLocalU,
//                    _SpyGlobalToLocalV
//              Ajout AllocBorders()
// 24/12/08 NLD Declarations de classe
//              CATMathPiecewiseXYGlobalToLocalSpy
//              au lieu de void*
//              Ajout GlobalToLocalU() et GlobalToLocalV()
// 27/10/10 NLD Ajout CATMathPiecewiseXYState, _State, CreateAndShareStateXYZ()
// 20/05/16 NLD Smart indent
//===================================================================
#include "CATIACGMLevel.h"

#include "YN000FUN.h"

class CATMathDefinitionMemoryXY;

#include "CATMathCommand.h"
#include "CATMathFoundationXY.h"
#include "CATCGMNewArray.h"

class CATMathPiecewiseXYDel;
class CATMathPiecewiseXYGlobalToLocalSpy ;
class CATMathPiecewiseXYState ;

class ExportedByYN000FUN CATMathPiecewiseXY : public CATMathFoundationXY
{


 // public methods
 public:

  CATCGMNewClassArrayDeclare;

  //-----------------------------------------------------------------
  // Object management
  //-----------------------------------------------------------------
                         CATMathPiecewiseXY (const CATMathPiecewiseXY        & f        );

                         CATMathPiecewiseXY (const CATLONG32                   NU       ,
                                             const double                  *   bordersU ,
                                             const CATLONG32                   NV       ,
                                             const double                  *   bordersV ,
                                             const CATMathFunctionXY      **   functions,
                                             const double                  *   iShiftU  = 0,
                                             const double                  *   iShiftV  = 0);

  virtual               ~CATMathPiecewiseXY ();

          void           Extrapol           (const CATLONG32                  NU       ,
                                             const double                  *  bordersU ,
                                             const CATLONG32                  NV       ,
                                             const double                  *  bordersV ,
                                             const CATMathFunctionXY      **  functions);

  //-----------------------------------------------------------------
  // Information methods
  //-----------------------------------------------------------------
  virtual CATMathClassId IsA                () const;
          int            GetDirectComponents(const int                        iSizeOfComponents,
                                             const CATMathFunctionGeneral **  ioComponents     ) const;

  virtual CATBoolean     IsAKindOf          (const CATMathClassId             iClassId         ) const;
  #ifdef CATIACGMV5R21
          CATBoolean     IsATypeOf          (const CATMathFunctionXYTypeId    iType            ) const;
  #endif

  virtual CATBoolean     IsOption           (const CATMathOption              iOption          ) const;

          void           GetNumberOfPieces  (      CATLONG32                & oNU              ,
                                                   CATLONG32                & oNV              ) const;

          void           GetFunction        (const CATLONG32                  iIndexU          ,
                                             const CATLONG32                  iIndexV          ,
                                             const CATMathFunctionXY       *& oF               ,
                                                   CATMathInterval          & oIU              ,
                                                   CATMathInterval          & oIV              ) const;
  // FCX 03.2004
  virtual void           GetInternalData    (      CATLONG32                & oNU              ,
                                                   CATLONG32                & oNV              ,
                                             const double                  *& oBordersU        ,
                                             const double                  *& oBordersV        ,
                                             const double                  *& oShiftU          ,
                                             const double                  *& oShiftV          ,
                                             const CATMathFunctionXY      **& oF               ) const;

  //-----------------------------------------------------------------
  // Evaluators on doubles
  //-----------------------------------------------------------------
          double         Eval               (const double                   & u                ,
                                             const double                   & v                ) const;

          double         EvalFirstDerivX    (const double                   & u                ,
                                             const double                   & v                ) const;

          double         EvalFirstDerivY    (const double                   & u                ,
                                             const double                   & v                ) const;

          double         EvalSecondDerivX2  (const double                   & u                ,
                                             const double                   & v                ) const;

          double         EvalSecondDerivXY  (const double                   & u                ,
                                             const double                   & v                ) const;

          double         EvalSecondDerivY2  (const double                   & u                ,
                                             const double                   & v                ) const;
  /**
  * Evaluates simultaneously the value, and all the first, second and third partial derivatives 
  */
          void           EvalUpToThirdDeriv (const double                     iu               ,
                                             const double                     iv               ,
                                                   double                   & oF               ,
                                                   double                   & oFx              ,
                                                   double                   & oFy              ,
                                                   double                   & oFx2             ,
                                                   double                   & oFxy             ,
                                                   double                   & oFy2             ,
                                                   double                   & oFx3             ,
                                                   double                   & oFx2y            ,
                                                   double                   & oFxy2            ,
                                                   double                   & oFy3             ) const;
  /**
  * Evaluates the value of third partial derivatives
  */
          void           EvalAllThirdDerivs (const double                     iu               ,
                                             const double                     iv               ,
                                                   double                   & oFx3             ,
                                                   double                   & oFx2y            ,
                                                   double                   & oFxy2            ,
                                                   double                   & oFy3             ) const;

          double         EvalThirdDerivX3   (const double                   & u                ,

                                             const double                   & v                ) const;

          double         EvalThirdDerivX2Y  (const double                   & u                ,
                                             const double                   & v                ) const;

          double         EvalThirdDerivXY2  (const double                   & u                ,
                                             const double                   & v                ) const;

          double         EvalThirdDerivY3   (const double                   & u                ,
                                             const double                   & v                ) const;

   //
   // Evaluator of function and derivatives at the same time :
   // iOption is a command which contains which derivatives are requested
   // (usually, iOption = OptionEval + OptionEvalFirstDeriv)
   //
          void           Eval               (const double                     u                ,
                                             const double                     v                ,
                                             const CATMathOption              iOptions         ,
                                                   double                  *  f                ,
                                                   double                  *  fx               = 0,
                                                   double                  *  fy               = 0,
                                                   double                  *  fx2              = 0,
                                                   double                  *  fxy              = 0,
                                                   double                  *  fy2              = 0) const;
  
          void           Eval               (const CATMathIntervalND        & iDomain          ,
                                             const CATLONG32               *  NbPoints         ,
                                             const CATMathOption              iOptions         ,
                                                   double                  *  f                ,
                                                   double                  *  fx               = 0,
                                                   double                  *  fy               = 0,
                                                   double                  *  fx2              = 0,
                                                   double                  *  fxy              = 0,
                                                   double                  *  fy2              = 0) const;

  //-----------------------------------------------------------------
  // Evaluators on intervals
  //-----------------------------------------------------------------
          CATMathInterval Eval              (const CATMathInterval          & Du               ,
                                             const CATMathInterval          & Dv               ,
                                             const CATTolerance             & iTolObject       = CATGetDefaultTolerance()) const;

          CATMathInterval EvalFirstDerivX   (const CATMathInterval          & Du               ,
                                             const CATMathInterval          & Dv               ) const;

          CATMathInterval EvalFirstDerivY   (const CATMathInterval          & Du               ,
                                             const CATMathInterval          & Dv               ) const;

          CATMathInterval EvalSecondDerivX2 (const CATMathInterval          & Du               ,
                                             const CATMathInterval          & Dv               ) const;

          CATMathInterval EvalSecondDerivXY (const CATMathInterval          & Du               ,
                                             const CATMathInterval          & Dv               ) const;

          CATMathInterval EvalSecondDerivY2 (const CATMathInterval          & Du               ,
                                             const CATMathInterval          & Dv               ) const;

          void            Eval              (const CATMathInterval          & Du               ,
                                             const CATMathInterval          & Dv               ,
                                             const CATMathOption              iOptions         ,
                                                   CATMathInterval         *  f                ,
                                                   CATMathInterval         *  fx               = 0,
                                                   CATMathInterval         *  fy               = 0,
                                                   CATMathInterval         *  fx2              = 0,
                                                   CATMathInterval         *  fxy              = 0,
                                                   CATMathInterval         *  fy2              = 0,
                                             const CATTolerance             & iTolObject       = CATGetDefaultTolerance()) const;

  //-----------------------------------------------------------------
  // Duplicator
  //-----------------------------------------------------------------
          CATMathFunctionXY * Duplicate     () const;
          CATMathFunctionXY * DeepDuplicate () const;

#if defined ( CATIACGMR216CAA )
          CATMathFunctionXY * DeepDuplicateWithTol(const CATTolerance       * ipTolObject      ) const ;
#endif

  //-----------------------------------------------------------------
  // Stream 
  //-----------------------------------------------------------------
#if defined ( CATIACGMV5R21 )
  virtual short          GetStreamDomainType(      char                       ioDomain      [3]) const;
#else
  virtual short          GetStreamType      ()                                                   const;
#endif
          void           Stream             (      CATMathStream            & Str              ,
                                             const char                       iLabelReserved[] = "" ) const;
  virtual size_t         GetStaticMemoryBytes()                                                  const;
  virtual size_t         GetDynamicMemoryBytes()                                                 const;
  /** @nodoc */
  virtual CATBoolean     _IsStreamable      (const CATCGMStreamVersion        iTargetVersion   ,
                                                   CATBoolean               & ioReversible     ) const;


  // restricted use: create and share state data between 3 functions on same grid
  static  void           CreateAndShareStateXYZ(   CATMathPiecewiseXY      *  iX               ,
                                                   CATMathPiecewiseXY      *  iY               ,
                                                   CATMathPiecewiseXY      *  iZ               );

  // protected data

protected:

  virtual CATMathFunctionXY * FormalCombination
                                            (const CATLONG32                  iN               ,
                                             const CATMathFunctionXY      **  iFunc            ,
                                             const double                  *  iCoef            ,
                                             const double                     iConstant        ) const;

  // Passage du parametrage global au parametrage local en U
          void                GlobalToLocalU(const double                   & x                ,
                                                   CATLONG32                & iu               ,
                                                   double                   & u                ) const ;
  // Passage du parametrage global au parametrage local en V
          void                GlobalToLocalV(const double                   & y                ,
                                                   CATLONG32                & iv               ,
                                                   double                   & v                ) const ;

private:
          CATMathPiecewiseXY & operator =   (const CATMathPiecewiseXY       & p                );

          CATLONG32               _NU,
                                  _NV;
    const CATMathFunctionXY    ** _F;
                                                 // arrays of _NU+1 points and _NV+1 points:
          double                * _BordersU,
                                * _BordersV;
                                                 // array of _NU points and _NV points, eventually 0
          double                * _ShiftU  ,
                                * _ShiftV;
          CATMathInterval       * _Image;
          CATBoolean            * _IsImage;
          CATMathInterval       * _ImageDU,
                                * _ImageDV;
          CATBoolean            * _IsImageD;
          CATMathOption           _IsHomogene;

  // Current patch data
  // ------------------
  //_CurrentUDotNV = _NV*iu
          CATLONG32               _CurrentIdxU,
                                  _CurrentIdxV,
                                  _CurrentUDotNV;
          CATLONG32               _Initialized;
  // inverse de la pente moyenne en U et V,
  // des fonctions permettant de passer des indices de carreaux aux parametres des frontieres,
  // sur intervalle complet en [0], 1er demi-intervalle en [1] et 2eme demi-intervalle en [2]
  // (donnees d'optimisation NLD161208, voir implementation)
          double                  _InvMeanSlopeU[3],
                                  _InvMeanSlopeV[3];

  // debug: fonctions espionnes de GlobalToLocal (NLD221208, voir implementation)
  CATMathPiecewiseXYGlobalToLocalSpy * _SpyGlobalToLocalU;
  CATMathPiecewiseXYGlobalToLocalSpy * _SpyGlobalToLocalV;
  CATMathPiecewiseXYState            * _State;

  friend class CATMathPiecewiseXYGlobalToLocalSpy;
  friend class CATMathPiecewiseXYDel;
  friend class CATMathLazyPiecewiseXY;

  //this method compute the index iu and iv update _CurrentIdxU , _CurrentIdxV and _CurrentUDotNV
  //_CurrentUDotNV = _NV*iu (we avoid integer mutiplication in Eval : _F[_NV*iu + iv]in order to optimize performance)
  // it is forbidden to change _CurrentIdxU , _CurrentIdxV or _CurrentUDotNV  outside of this method
          void                GlobalToLocal (const double                   & x                ,
                                             const double                   & y                ,
                                                   CATLONG32                & iu               ,
                                                   double                   & u                ,
                                                   CATLONG32                & iv               ,
                                                   double                   & v                ) const;
          void                UpdateOptimizationData();
          void                AllocBorders();

  virtual const CATMathFunctionXY * GetF(          CATLONG32                  index            ) const;
};


#endif
