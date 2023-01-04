#ifndef CATCGMBackSaveError_h
#define CATCGMBackSaveError_h

//=============================================================================
//  CATBack save warning  
//  If any object is converted en Nurbs, then create this warning and report it 
//  to DownwardCompatiblity application 
//=============================================================================

#include "ExportedByGeometricObjects.h"
#include "CATCGMInputError.h"

class  ExportedByGeometricObjects CATCGMBackSaveError : public CATCGMInputError
{
public:
	    CATDeclareError(CATCGMBackSaveError, CATCGMInputError)

		/** @nodoc */
		CATCGMNewClassArrayDeclare;

		virtual ~CATCGMBackSaveError();

		void SetCompatibilityInformation(int iNbIncompatibleObjects, int iNbConvertedObjects);

		int _NbIncompatibleObjects;
		int _NbConvertedObjects;
};

#endif

