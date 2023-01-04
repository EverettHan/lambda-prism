// COPYRIGHT DASSAULT SYSTEMES 1997
//===================================================================
//
// CATMathCombinationXDel:
// Class like CATMathCombinationX but which deletes the composite 
// functions in the destructor 
//
//===================================================================
// 04/02/20 NLD Ajout CreateCombinationXDel()
//             (que l'on pourrait mettre dans CATMathFunctionX.h)
//===================================================================
#ifndef CATMathCombinationXDel_h
#define CATMathCombinationXDel_h

#include "CATMathCombinationX.h"
#include "YN000FUN.h"

class CATMathFunctionX;

class ExportedByYN000FUN CATMathCombinationXDel : public CATMathCombinationX
{
 public:
    CATMathCombinationXDel(      CATLONG32           N        ,
                                 CATMathFunctionX ** functions,
                           const double            * coef     ,
                           const double              constant = 0.);

   ~CATMathCombinationXDel();
    CATCGMNewClassArrayDeclare;
};

//----------------------------------------------------------------------------------------------------------------------------
  /**
   * Returns a function representing the linear combination of other CATMathFunctions.
   * <tt>iConstant + Sum_{i=0}^{iN-1} iCoef[i] * iFunc[i]</tt>.
   * <br>WARNING : the returned pointer must be deleted by the caller
   * (then children functions will be deleted)
   * <br> May also generate a canonic function (ex: CATMathPolynomX for the combination of CATMathPolynomX functions)
   * <br>CAUTION : if canonic function generated, all input functions are immediatly deleted
   */

//----------------------------------------------------------------------------------------------------------------------------

ExportedByYN000FUN
CATMathFunctionX * CreateCombinationXDel      (const CATLONG32                  iN                , 
                                               const CATMathFunctionX        ** iFunc             ,
                                               const double                   * iCoef             ,
                                               const double                     iConstant         = 0);


#endif
