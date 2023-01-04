#ifndef CATMathIntError_h
#define CATMathIntError_h
//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 1997
//
// DESCRIPTION : CATMathIntError class declaration: classe NLS 
/**
 * Class representing the NLS internal errors of the Mathematics framework.
 */
//               
//=============================================================================
#include "CATErrors.h"
#include "CATMathematics.h"
#include "CATCGMInternalError.h"

// definition du fichier de message
#ifndef MathIntFile
#define MathIntFile "CATMathematics"
#endif


class  ExportedByCATMathematics CATMathIntError : public CATCGMInternalError
{
  public:

    CATDeclareError(CATMathIntError, CATCGMInternalError)


   	/** @nodoc */
   CATCGMNewClassArrayDeclare;
};

#endif
