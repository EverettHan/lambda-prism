// COPYRIGHT DASSAULT SYSTEMES 1997
//===================================================================
//
// CATMathSquareDistXYsDel:
// Class like CATMathSquareDistXYs but which deletes the composite 
// functions in the destructor 
//
//===================================================================
//
// Usage notes:
//
//===================================================================
// 30/01/09 NLD Le constructeur prend une SoftwareConfiguration

#ifndef CATMathSquareDistXYsDel_H
#define CATMathSquareDistXYsDel_H

#include "CATMathSquareDistXYs.h"
#include "YN000FUN.h"

class CATMathFunctionX;
class CATSoftwareConfiguration;

class ExportedByYN000FUN CATMathSquareDistXYsDel : public CATMathSquareDistXYs
{
 public:   
  CATMathSquareDistXYsDel(CATLONG32 iN,  
			  CATMathFunctionX ** iF, 
			  CATMathFunctionX ** iG,
           CATSoftwareConfiguration* iConfig
                          );
  ~CATMathSquareDistXYsDel();
  CATCGMNewClassArrayDeclare;
};
#endif
