#ifndef CATGeoObInErrorDataCGM_h
#define CATGeoObInErrorDataCGM_h
//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 1997
//
// DESCRIPTION : CATGeoObInError class declaration: classe NLS 
/**
 * Class representing limited explicit Data Error of GeometricObjectsCGM framework.
 */
//               
//=============================================================================
#include "CATGeoObInError.h"
#include "ExportedByGeometricObjects.h"

class  ExportedByGeometricObjects CATGeoObInErrorDataCGM : public CATGeoObInError
{
  public:
   CATDeclareErrorClass(CATGeoObInErrorDataCGM, CATGeoObInError)
    	/** @nodoc */
   CATCGMNewClassArrayDeclare;

   CATGeoObInErrorDataCGM( const char *msgId,const char *catalog );
   virtual ~CATGeoObInErrorDataCGM();

    /** @nodoc */
    virtual CATGeoObInErrorDataCGM *IsDataCGM();

    void SetCompatibilityError(CATBoolean DataCompatibilityError,int NbIncomptabilbleObjects);
    CATBoolean IsCompatibilityError();
    int GetNbIncomptabilbleObjects();

    /** Scale ERROR  */
    CATBoolean  _ScaleError;
    double      _ScaleOnDisk;

    /** Foreign ERROR  */
    CATBoolean       _ForeignError;
		CATUnicodeString _ForeignAttrName;
  	CATUnicodeString _ForeignDomainName;

    /** BackSave ERROR**/
    CATBoolean  _DataCompatibilityError;
    int         _NbIncomptabilbleObjects;


};
//

#endif
