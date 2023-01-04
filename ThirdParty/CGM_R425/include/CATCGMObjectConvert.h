#ifndef CATCGMObjectConvert_H
#define CATCGMObjectConvert_H


#include "ExportedByCATTopologicalObjects.h"
#include "CATGeoOperator.h"

class CATGeoFactory;


class ExportedByCATTopologicalObjects CATCGMObjectConvert : public CATGeoOperator
{
	CATCGMVirtualDeclareClass(CATCGMObjectConvert);

public:

	/**
	* Destructor.
	*/
	virtual ~CATCGMObjectConvert();

	/**
	*  Set stream version to identify the incompatibles Objects
	*/
	virtual void SetTargetVersion(CATCGMStreamVersion & iTargetVersion) = 0;

	/**
    *  Add objects to convert
	*/
	virtual void AddObjectsToConvert(CATLISTP(CATICGMObject) & iObjectsToConvert) = 0;

	/**
    *  Get all objects to convert
    */
	virtual void GetObjectsToConvert(CATLISTP(CATICGMObject) & oObjectsToConvert) = 0;

	enum ObjectConvertDiagnosis
	{
		NotInitialized,
		NoNeedConvert,
		NoAvailableConvert,
		ConvertSuccessful,
		ConvertFailed
	};

	/**
    *  Get diagnosis and converted object if conversion is successful
    */
	virtual CATICGMObject*  GetResult(CATICGMObject* & iObjectToConvert, ObjectConvertDiagnosis & oDiagnosis) = 0;

protected:

	/**
  * @nodoc
  * Virtual constructor of a CATCGMObjectConvert.<br>
  * Cannot be called. Use the <tt>CATCreateXxx</tt> global function
  * to create the Xxx operator.
  */
	CATCGMObjectConvert(CATGeoFactory* iFactory);


};

ExportedByCATTopologicalObjects CATCGMObjectConvert* CATCreateCGMObjectConvert(CATGeoFactory *   iFactory,
	CATSoftwareConfiguration* iConfig);

#endif


