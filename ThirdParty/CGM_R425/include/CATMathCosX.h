//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2017
//=============================================================================
// CATMathCosX :
// Simple cos(x) function encapsulated into a CATMathFunctionX.
// Useful for prototype
//            ---------
// (with combine function for instance, to avoid created a
//  new functionX class).
//
// CAUTION: no customer stream NLD290321
//
//=============================================================================
// 23/02/17 F1Z : Creation
// 29/03/21 NLD : Ajout DeepDuplicate() et DeepDuplicateWithTol()
// 29/03/21 NLD : Gestion du stream (interne CGMReplay seulement)
//                - derivation de GetDirectComponents()
//                - derivation de _IsStreamable()
//                - derivation de GetStreamType()
//                - derivation de Steam()
//                - derivation de DeepDuplicate()
//                - ajout de CATFunctionXUnStream_CosX()
// DD/MM/YY
//=============================================================================

#ifndef CATMathCosX_H
#define CATMathCosX_H

// System
#include "CATBoolean.h"

// Mathematics
#include "CATMathDef.h"
#include "CATMathConstant.h"

// Advanced mathematics
#include "CATMathFunctionX.h"
#include "YN000FUN.h"

class CATTolerance;

//=============================================================================
class ExportedByYN000FUN CATMathCosX : public CATMathFunctionX
{
public:
   //-----------------------------------------------------------------------------
   // Class Management
   //-----------------------------------------------------------------------------
           CATMathCosX();
          ~CATMathCosX();

   //-----------------------------------------------------------------------------
   // Identity
   //-----------------------------------------------------------------------------
           CATBoolean         IsAKindOf              (const CATMathClassId             iClassId         ) const;
           CATMathClassId     IsA                    ()                                                   const;
           CATBoolean         IsOption               (const CATMathOption              iOption          ) const;
           CATMathFunctionX * Duplicate              ()                                                   const;
   virtual CATMathFunctionX * DeepDuplicate          ()                                                   const;
           CATMathFunctionX * DeepDuplicateWithTol   (const CATTolerance            *  ipTolObject      ) const;

  //-----------------------------------------------------------------
  // Stream management
  //-----------------------------------------------------------------
   virtual int                GetDirectComponents    (const int                        iSizeOfComponents,
                                                      const CATMathFunctionGeneral **  ioComponents     ) const;

   virtual CATBoolean         _IsStreamable          (const CATCGMStreamVersion        iTargetVersion   ,
                                                            CATBoolean               & ioReversible     ) const;

   virtual short              GetStreamDomainType    (      char                       ioDomain[3]      ) const;

   virtual void               Stream                 (      CATMathStream            & Str              ,
                                                      const char                       iLabelReserved[] ) const ;

   //-----------------------------------------------------------------------------
   // Evaluation
   //-----------------------------------------------------------------------------
           double             Eval                   (const double                   & iT               ) const;
           double             EvalFirstDeriv         (const double                   & iT               ) const;
           double             EvalSecondDeriv        (const double                   & iT               ) const;
           double             EvalThirdDeriv         (const double                   & iT               ) const;
};

#endif

