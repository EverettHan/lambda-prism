#ifndef CATMathInError_h
#define CATMathInError_h
//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 1997
//
// DESCRIPTION : CATMathInError class declaration: classe NLS 
/**
 * Class representing the NLS input errors of the Mathematics framework.
 */
//               
//=============================================================================
#include "CATErrors.h"
#include "CATMathematics.h"
#include "CATCGMInputError.h"


// definition du fichier de message
#ifndef MathInFile
#define MathInFile "CATMathematics"
#endif


enum {
      MathInNullDeterminant,
      MathInBadTransformationType,
	  MathInColinearDirections,
	  MathInNullValue,
	  MathInSingularPoint,
	  MathInInvalidDimension,
	  MathInInvalidIndex,
	  MathInInvalidGetUse,
	  MathInInvalidFunctionCall,
	  MathInBadConditionnedSystem,
	  MathInIdenticalPoints

      
};

class  ExportedByCATMathematics CATMathInError : public CATCGMInputError
{


  public:
    CATDeclareError(CATMathInError, CATCGMInputError)

   	/** @nodoc */
   CATCGMNewClassArrayDeclare;
};
//

#endif
