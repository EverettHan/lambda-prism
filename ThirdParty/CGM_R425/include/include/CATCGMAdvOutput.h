#ifndef CATCGMAdvOutput_h_
#define CATCGMAdvOutput_h_

// COPYRIGHT DASSAULT SYSTEMES  1999

#include "YN000FUN.h"
#include "CATCGMOutput.h"

class CATMathTrigonometricX ;
class CATMathPolynomXY ;
class CATMathPolynomX ;
class CATMathNxNFullSymMatrix ;
class CATMathNxNMatrix ;
class CATMathNxNBandSymMatrix ;
class CATMathMxNMatrix ;
class CATMathArctanCosX ;
class CATMathHyperbolicX ;
class CATMathInterval ;
class CATMathIntervalND ;
class CATMathLinearXY ;
class CATMathCombinationX;


ExportedByYN000FUN CATCGMOutput & operator << ( CATCGMOutput& , CATMathTrigonometricX & );
ExportedByYN000FUN CATCGMOutput & operator << ( CATCGMOutput& , CATMathPolynomX & );
ExportedByYN000FUN CATCGMOutput & operator << ( CATCGMOutput& , CATMathArctanCosX & );
ExportedByYN000FUN CATCGMOutput & operator << ( CATCGMOutput& , CATMathHyperbolicX & );

ExportedByYN000FUN CATCGMOutput & operator << ( CATCGMOutput& , CATMathLinearXY & );
ExportedByYN000FUN CATCGMOutput & operator << ( CATCGMOutput& , CATMathPolynomXY & );
ExportedByYN000FUN CATCGMOutput & operator << ( CATCGMOutput& , CATMathCombinationX & );

ExportedByYN000FUN CATCGMOutput & operator << ( CATCGMOutput& , const CATMathInterval & );
ExportedByYN000FUN CATCGMOutput & operator << ( CATCGMOutput& , const CATMathIntervalND & );

ExportedByYN000FUN CATCGMOutput & operator << ( CATCGMOutput& , const CATMathNxNFullSymMatrix &);
ExportedByYN000FUN CATCGMOutput & operator << ( CATCGMOutput& , const CATMathNxNMatrix &);
ExportedByYN000FUN CATCGMOutput & operator << ( CATCGMOutput& , const CATMathNxNBandSymMatrix &);
ExportedByYN000FUN CATCGMOutput & operator << ( CATCGMOutput& , const CATMathMxNMatrix &);



#endif
