#ifndef CATMathCombinationX_h
#define CATMathCombinationX_h

// COPYRIGHT DASSAULT SYSTEMES  1999

//=============================================================================
// 30/09/11 R1Y Added the function GetCoefficients() (for comparing geometries).
// 07/11/19 JSX ajout de "ostream & operator << " pour dump des pcurveequation
//=============================================================================
#include "CATIACGMLevel.h"
#include "YN000FUN.h"
#include "CATMathFoundationX.h"

class CATMathCombinationXDel;

class ExportedByYN000FUN CATMathCombinationX : public CATMathFoundationX
{
 private :
         CATLONG32           _N;
         double            * _coef;
   const CATMathFunctionX ** _Functions;

   friend class CATMathCombinationXDel;

 public:
            CATMathCombinationX              (const CATLONG32           & N        ,
                                              const CATMathFunctionX   ** functions,
                                              const double              * coef     ,
                                              const double                constant = 0.);
            CATMathCombinationX              (const CATMathCombinationX & f);
            CATMathCombinationX & operator = (const CATMathCombinationX & c);
   virtual ~CATMathCombinationX();

    CATCGMNewClassArrayDeclare;
    
   CATBoolean         IsAKindOf           (const CATMathClassId         ClassId) const;
   CATBoolean         IsATypeOf           (const CATMathFunctionXTypeId iType  ) const;
   CATMathClassId     IsA                 () const;
   int                GetDirectComponents (const int iSizeOfComponents, const CATMathFunctionGeneral **ioComponents) const;
   CATBoolean         IsOption            (const CATMathOption iOption) const;

   CATMathFunctionX * Duplicate           () const;
   CATMathFunctionX * DeepDuplicate       () const;
   CATMathFunctionX * DeepDuplicateWithTol(const CATTolerance *ipTolObject) const ;
   
   const double * GetCoefficients() const;

   //-----------------------------------------------------------------
   // Stream 
   //-----------------------------------------------------------------
   virtual short   GetStreamDomainType  (char ioDomain[3]) const;
           void    Stream               ( CATMathStream& Str, const char iLabelReserved[] = "" ) const;
   virtual size_t  GetStaticMemoryBytes () const;
   virtual size_t  GetDynamicMemoryBytes() const;
   /** @nodoc */
   virtual CATBoolean _IsStreamable( const CATCGMStreamVersion iTargetVersion, CATBoolean & ioReversible ) const;

   // overloading << 
   friend ExportedByYN000FUN ostream & operator << ( ostream& os, CATMathCombinationX & p );
   
   //-----------------------------------------------------------------
   // Evaluators on doubles
   //-----------------------------------------------------------------   
   double Eval           (const double & t) const;
   double EvalFirstDeriv (const double & t) const;
   double EvalSecondDeriv(const double & t) const;
   double EvalThirdDeriv (const double & t) const;

   //
   // Evaluator of function and derivatives at the same time :
   //
   void Eval(const double t, const CATMathOption iOption,
             double * f, double * df = 0, double * d2f = 0) const;

   //
   // MultiEvaluator on a regular one dimensional grid on I.
   //
   void Eval(const CATMathInterval & I, const CATLONG32 NbPoints,
             const CATMathOption iOption,
             double * f, double * df = 0, double * d2f = 0) const;

   //-----------------------------------------------------------------
   // Evaluators on intervals
   //-----------------------------------------------------------------
   CATMathInterval Eval           (const CATMathInterval & x) const;
   CATMathInterval EvalFirstDeriv (const CATMathInterval & x) const;
   CATMathInterval EvalSecondDeriv(const CATMathInterval & x) const;
   CATMathInterval EvalThirdDeriv (const CATMathInterval & x) const;

   void            Eval           (const CATMathInterval & I       ,
                                   const CATMathOption     iOptions,
                                         CATMathInterval * f       ,
                                         CATMathInterval * df      = 0,
                                         CATMathInterval * d2f     = 0) const;
};
#endif
