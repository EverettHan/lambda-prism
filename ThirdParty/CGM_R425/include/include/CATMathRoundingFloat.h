//_______________________________________________________________________
//  CATMathRoundingFloat     rounding of a float
//  global method
// COPYRIGHT DASSAULT SYSTEMES  1999
//_______________________________________________________________________
//  the case iChoice=0 is roughly equivalent to:
//     tmp = log10(fabs(iNumber));
//     oPower = 10.**(-sign(tmp)*floor(fabs(tmp)));
//     CATMathRoundingFloat = floor(fabs(iNumber)*oPower);
//  but cheeper and more protected !
//
//  the results do not reflect the sign of the initial value
//_______________________________________________________________________
//  X = CATMathRoundingFloat ( iNumber, oPower, iChoice )
//_______________________________________________________________________
//  input :
//   float iNumber  : number to be rounded
//   int   iChoice  : process choice:
//         = 0   => fabs(iNumber) approached by default
//                  CATMathRoundingFloat keeps only the 1st significative
//                  digit = integer part of fabs(iNumber)*oPower
//         = 1   => fabs(iNumber) approached by excess by X/oPower, with
//                  X=1., 2. or 5.
//                  ( X/oPower = 10**(-10) if iNumber is zero )
//         = 2   => fabs(iNumber) approached by excess by 1./oPower
//         = 3   => fabs(iNumber) approached by excess by X/oPower, with 
//                  X=1., 1.25, 1.6, 2., 2.5, 3.2, 4., 5.,
//                  6.25 or 8.
//                  ( X/oPower = 10**(-10) if iNumber is zero )
//_______________________________________________________________________
//  output :
//   float oPower   : integer power of 10. such as
//                    1./oPower <= fabs(iNumber) < 10./oPower
//   float CATMathRoundingFloat :
//         part without exponent of the approximation of iNumber
//_______________________________________________________________________

#include "YN000TRE.h"

ExportedByYN000TRE float CATMathRoundingFloat
                         ( float *iNumber, float *oPower, int *iChoice );
