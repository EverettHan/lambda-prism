#ifndef CATMathFractionX_h
#define CATMathFractionX_h

//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
// ??/??/?? ??? Fuckin creator
// 06/06/07 NLD XScale: _TolObject devient public 
// 27/01/09 NLD Interface R20 (CATSoftwareConfiguration) pour Solve()
// 09/02/09 NLD Ajout _IsUnStreamed et SetIsUnStreamed()
// 13/04/11 NLD Deflaggage R20 pour Solve()
// 24/05/16 NLD Mise au propre. Smart indent
//              XScale
//              - derivation de ComputeOptimalImage()
//              - ajout (transitoire?) de _WorkConfig
//=============================================================================
#include "CATIACGMLevel.h"

#include "YN000FUN.h"
#include "CATMathFoundationX.h"

class CATMathFractionXDel;
class CATSoftwareConfiguration;

//=============================================================================
class ExportedByYN000FUN CATMathFractionX : public CATMathFoundationX
{
 public:
  //-----------------------------------------------------------------
  //- Object Management
  //-----------------------------------------------------------------
                                   CATMathFractionX    (const CATMathFunctionX *  P    ,
                                                        const CATMathFunctionX *  Q    ,
                                                        const CATTolerance      & iTol = CATGetDefaultTolerance());
                                   CATMathFractionX    (const CATMathFractionX  & F    );
  virtual      ~CATMathFractionX();

  CATCGMNewClassArrayDeclare;

                CATMathFunctionX * Duplicate           () const;
                CATMathFunctionX * DeepDuplicate       () const;
#if defined ( CATIACGMR216CAA )
                CATMathFunctionX * DeepDuplicateWithTol(const CATTolerance * ipTolObject) const;
#endif
          const CATMathFunctionX * GetNumerator        () const;
          const CATMathFunctionX * GetDenominator      () const;

  //-----------------------------------------------------------------
  // Stream 
  //-----------------------------------------------------------------
   #if defined ( CATIACGMV5R21 )
   virtual short      GetStreamDomainType  (char ioDomain[3]) const;
   #else
   virtual short      GetStreamType        () const;
   #endif
           void       Stream               (CATMathStream& Str, const char iLabelReserved[] = "" ) const;
   virtual size_t     GetStaticMemoryBytes () const;   
   virtual size_t     GetDynamicMemoryBytes() const;   
   /** @nodoc */
   virtual CATBoolean _IsStreamable        (const CATCGMStreamVersion iTargetVersion,
                                                  CATBoolean        & ioReversible  ) const;


  //-----------------------------------------------------------------
  //- Information Methods
  //-----------------------------------------------------------------
  CATMathClassId IsA() const;
  int            GetDirectComponents(const int                       iSizeOfComponents,
                                     const CATMathFunctionGeneral ** ioComponents     ) const;
  CATBoolean     IsAKindOf          (const CATMathClassId            ClassId)           const;
  CATBoolean     IsATypeOf          (const CATMathFunctionXTypeId    iType)             const;  
  CATBoolean     IsOption           (const CATMathOption             iOption)           const;

  //-----------------------------------------------------------------
  //- Evaluators on doubles
  //-----------------------------------------------------------------
  double          Eval           (const double           & t) const;
  double          EvalFirstDeriv (const double           & t) const;
  double          EvalSecondDeriv(const double           & t) const;
  double          EvalThirdDeriv (const double           & t) const;

  void            Eval           (const double             t,
                                  const CATMathOption      iOption,
                                        double           * f      ,
                                        double           * df     = 0,
                                        double           * d2f    = 0) const;

  void            Eval           (const CATMathInterval  & I      ,
                                  const CATLONG32          NbPoints,
                                  const CATMathOption      iOption,
                                        double           * f      ,
                                        double           * df     = 0,
                                        double           * d2f    = 0) const;

  //-----------------------------------------------------------------
  // Evaluators on intervals
  //-----------------------------------------------------------------
  CATMathInterval Eval           (const CATMathInterval  & x) const;
  CATMathInterval EvalFirstDeriv (const CATMathInterval  & x) const;
  CATMathInterval EvalSecondDeriv(const CATMathInterval  & x) const;
  CATMathInterval EvalThirdDeriv (const CATMathInterval  & x) const;

  void            Eval           (const CATMathInterval  & I       ,
                                  const CATMathOption      iOptions,
                                        CATMathInterval *  f       ,
                                        CATMathInterval *  df      = 0, 
                                        CATMathInterval *  d2f     = 0) const;

  /**
  * @nodoc
  * Computes a quite good interval containing the image of (I), thanks to a recursive process.
  */
  CATMathInterval ComputeOptimalImage         (const CATMathInterval          & I            ,
                                               const CATTolerance             & iTolObject   = CATGetDefaultTolerance(),
                                                     CATMathAttrScaleOption  *  iScaleOption = NULL,
                                                     CATSoftwareConfiguration*  iConfig      = NULL
                                              ) const;

  //-----------------------------------------------------------------
  // Solver
  //----------------------------------------------------------------- 
  CATMathDiagnostic Solve        (const CATMathInterval          & D          ,
                                        CATMathSetOfPointsND     & roots      ,
                                  const CATMathAttrList         *  attributes = 0,
                                        CATSoftwareConfiguration*  iConfig    = NULL
                                 ) const;

  //----------------------------------------------------------------- 
  // To call when fraction is read in stream
  //----------------------------------------------------------------- 
  void              SetIsUnStreamed() ;

 private:
  //-----------------------------------------------------------------
  // Private methods
  //-----------------------------------------------------------------
  
  // Interval evaluator for the denominator, returning in *f an interval not 
  // containing zero.
  void              EvalDenom     (const CATMathInterval & I       ,
                                   const CATMathOption     iOptions,
                                         CATMathInterval * f       ,
                                         CATMathInterval * df      = 0, 
                                         CATMathInterval * d2f     = 0) const;

  // Recursive EvalDenom called by EvalDenom
  // 0 is returned if zero was found in the image of the denominator, else 1
  // is returned
  CATBoolean        REvalDenom    (const CATMathInterval & I       ,
                                         CATMathInterval & f       ) const;


   //-----------------------------------------------------------------
  // Raises an exception explaining that a denominator is null
  // therefore an evaluation cannot be performed.

  void              ThrowForNullDenom () const;

  //-----------------------------------------------------------------
  // Data
  //-----------------------------------------------------------------
 public:
  const CATTolerance      & _TolObject; //NLD public pour XScale

 private:


  // ATTENTION: toute modification doit etre repercutee dans
  // GeometricObjectsCGM/CATGeometricObjectsCGM.m/src/CATCompareGeometryImp.cpp
  // voir ODT GeometricObjectsCGM.tst CompareGeometrySizeof_IfKOContactGeometryTeam
  // NLD300516
  const CATMathFunctionX  * _P,
                          * _Q;

  int                       _IsUnStreamed; // when fraction is read in stream

  CATSoftwareConfiguration* _WorkConfig;


  friend class CATMathFractionXDel;
};

#endif
