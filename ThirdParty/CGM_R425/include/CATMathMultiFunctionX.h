#ifndef CATMathMultiFunctionX_H
#define CATMathMultiFunctionX_H

// COPYRIGHT DASSAULT SYSTEMES 1999

#include "CATMathVectorialFunctionX.h"
#include "CATMathSetOfPointsND.h"
#include "CATMathDef.h"
#include "CATMathFunctionX.h"

#include "CATTolerance.h"

class CATSoftwareConfiguration;


class ExportedByYN000FUN CATMathMultiFunctionX : public CATMathVectorialFunctionX
{

 private:
  const CATMathFunctionX **_function;

  public:  
//----------------------------------------------------------  
//  Constructor (iN is the number of functions of the system)
//----------------------------------------------------------    
    CATMathMultiFunctionX (const CATLONG32  iN, const CATMathFunctionX **Eq);   
    CATMathMultiFunctionX (CATSoftwareConfiguration   *iSoftwareConfiguration,const CATLONG32  iN, const CATMathFunctionX **Eq,const CATTolerance &iTol=CATGetDefaultTolerance());   
//------------ 
//  Destructor  
//------------  
    virtual ~CATMathMultiFunctionX ();
    CATCGMNewClassArrayDeclare;
// 
// Evaluators: iX is a point in R.
//  . oFX = F(iX) is the image of iX by F. oFX is in RN and is already allocated. 
//  . oDFX is the derivative of F at iX and is in RN and is already allocated. 
//  . oD2FX is the second derivative of F at iX and is in RN and is already allocated. 
//
   void Eval            (const double  iX, double *oFX) const;
   void EvalFirstDeriv  (const double  iX, double *oDFX) const; 
   void EvalSecondDeriv (const double  iX, double *oD2FX) const; 
   void Eval            (const double  iX, double *oFX, double *oDFX) const;

};  
#endif 
