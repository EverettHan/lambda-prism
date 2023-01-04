// COPYRIGHT DASSAULT SYSTEMES  1997
//=============================================================================
//
// CATMathNxNFullMatrix:
// Class representing a temporary full square matrix in dimemsion N
//
//=============================================================================

#ifndef CATMath3x3FullMatrix_H  
#define CATMath3x3FullMatrix_H 

/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

#include "YN000FUN.h"
#include "CATMathNxNFullMatrix.h"


class ExportedByYN000FUN CATMath3x3FullMatrix : public CATMathNxNFullMatrix 
{ 
public:
  CATMath3x3FullMatrix (); 
  ~CATMath3x3FullMatrix ();
protected:
  double _tab[9];
};

#endif  
