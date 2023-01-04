#ifndef CATTopObIntError_h
#define CATTopObIntError_h
//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 1997
//
// DESCRIPTION : CATTopObIntError class declaration: NLS Class 
/**
 * Class representing the NLS internal errors of the NewTopologicalObjects framework.
 */
//               
//=============================================================================
#include "CATErrors.h"
#include "CATGMModelInterfaces.h"
#include "CATCGMInternalError.h"
// definition du fichier de message

#ifndef TopObIntFile
#define TopObIntFile "CATTopologicalObjects"
#endif


enum {
      TopObIntUnvailable,
      TopObIntobjectCreationFailed,
	  TopObIntInterfaceFailed,
	  TopObIntImplFailed,
	  TopObIntMethodCallOrder,
	  TopObIntObjectType,
	  TopObIntBadTopology,
	  TopObIntImpossibleWriting,
	  TopObIntAllocation,
	  TopObIntNoSubd,
	  TopObIntSubd,
	  TopObIntBadGeometry,
	  TopObIntMath
      
};

class  ExportedByCATGMModelInterfaces CATTopObIntError : public CATCGMInternalError
{


  public:

    CATDeclareError(CATTopObIntError, CATCGMInternalError)

   	/** @nodoc */
   CATCGMNewClassArrayDeclare;
};

#endif
