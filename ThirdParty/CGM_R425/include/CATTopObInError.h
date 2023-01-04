#ifndef CATTopObInError_h
#define CATTopObInError_h
//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 1997
//
// DESCRIPTION : CATTopObInError class declaration: classe NLS 
/**
 * Class representing the NLS input errors of the NewTopologicalObjects framework.
 */
//               
//=============================================================================
#include "CATErrors.h"
#include "CATGMModelInterfaces.h"
#include "CATCGMInputError.h"

// definition du fichier de message

#ifndef TopObInFile
#define TopObInFile "CATTopologicalObjects"
#endif


enum {
      TopObInNullPointer,
      TopObInNullData,
      TopObInEmptyObject,
      TopObInInvalidType,
      TopObInIndex,
	  TopObInMixPolyExactInputs,
      TopObInBadOrientation,
      TopObInBadMatterSideValue,
      TopObInBadLocationValue,
      TopObInBadSideValue,
      TopObInInvalidDimension,
      TopObInTooSmallDimension,
      TopObInTooLargeDimension,
      TopObInIncompatibleElement,
      TopObInNonModifiableElement,
      TopObInNoGeometry,
      TopObInIncomplete,
      TopObInIncompleteSplit,
      TopObInSurSurUndetectedConfusion
};

class  ExportedByCATGMModelInterfaces CATTopObInError : public CATCGMInputError
{


  public:

    CATDeclareError(CATTopObInError, CATCGMInputError)

   	/** @nodoc */
   CATCGMNewClassArrayDeclare;
};
//

#endif
