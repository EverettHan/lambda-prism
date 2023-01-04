//*===========================================================================*
//* COPYRIGHT DASSAULT SYSTEMES 2010                                          *
//*===========================================================================*
//*                                                                           *
//*  CASLogin                                                                 *
//*                                                                           *
//*  Usage Notes:  Client Http V1.0                                           *
//*===========================================================================*
//*  Creation novembre 2010                                       adt         *
//*===========================================================================*
#ifndef DSYCASLOGIN_H
#define DSYCASLOGIN_H
#include <stdlib.h>
#include <memory.h>
#include "CATSysDataType.h"
#include "CATHttp.h"
#include "CATHttpClient.h"


/**
 * Login error class
 */
class ExportedByJS0HTTP DSYCASLoginError
{
private:
    char * _catalog;
    char * _key;
    char * _param1;
    char * _param2;
    char * _param3;
public:
    DSYCASLoginError();
    ~DSYCASLoginError();
    void setError(const char *catalog, const char *key, const char*param1 = NULL, const char*param2 = NULL, const char*param3 = NULL);
    inline const char *getCatalog() { return _catalog; }
    inline const char *getKey()     { return _key; }
    inline const char *getParam1()  { return _param1; }
    inline const char *getParam2()  { return _param2; }
    inline const char *getParam3()  { return _param3; }
};

/**
 * Login onto CAS.
 * <br><b>Role</b>:Login onto Central Authentication Server for 3DSwymer login.
 * @param iServer 
 *      CAS server name like https//iam.3ds.com
 * @param iService
 *      the referer requesting connection  like www.3dswymer.com 
 * @param iUser 
 *      the user name.
 * @param iPwd
 *      the password.
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> E_FAIL :</tt> on failure
*/
HRESULT ExportedByJS0HTTP DSYCASLogin (
        const char *iServer, 
        const char* iService, 
        const char *iServiceArgs,
		const char *iUser, 
        const char *iPwd, 
        const char *stop = NULL, 
        DSYCASLoginError * oErrorKey = NULL, 
        char      **ioCasTgc = NULL,
        int         iDebugMode = 1);

/** @nodoc */
HRESULT ExportedByJS0HTTP DSYAnalyzeHttpResponseStatusError(const HRESULT &hrHTTPRequest, CATHttpClient &iClient, DSYCASLoginError * oErrorKey, const char * serviceAlias, const char *requestType = NULL);

/** @nodoc */
HRESULT ExportedByJS0HTTP DSYSysCASLogin(const char *iServer, const char *iUser, const char* iPwd, const char *stop);

/** @nodoc */
HRESULT	ExportedByJS0HTTP DSYSysCASLoginUnicode(const CATUnicodeString &iServer, const CATUnicodeString &iUser, const CATUnicodeString &iPwd, const CATUnicodeString &stop);

/** @nodoc */
HRESULT ExportedByJS0HTTP DSYSysCASLogout(CATUnicodeString iServer);

/** @nodoc */
bool ExportedByJS0HTTP CheckIfCASValid();

/** @nodoc */
HRESULT	ExportedByJS0HTTP DSYSysValidateTransient(const CATUnicodeString &iTransient);



#define IsCASValidV2_KEEP_SERVER_RESPONSE 1

/** @nodoc */
HRESULT ExportedByJS0HTTP GetValueFromCAS(char *buf, CATUnicodeString iKey, CATUnicodeString &oKey);

/** @nodoc */
HRESULT ExportedByJS0HTTP CheckIfCASValidV2(CATUnicodeString &oUserCAS, CATUnicodeString &oUserEmail, char *&oBody, unsigned int iFlag);

/** @nodoc */
HRESULT ExportedByJS0HTTP CheckIfCASValidFromCASUrl(CATUnicodeString iCasUrl, CATUnicodeString &oUserCAS, CATUnicodeString &oUserEmail, char *&oBody, unsigned int iFlag);

/** @nodoc */
extern "C" HRESULT ExportedByJS0HTTP SavCookies(const char *iApplication, const char *iUrl);

/** @nodoc */
extern "C" HRESULT ExportedByJS0HTTP SavCookiesUnicode(CATUnicodeString iApplication, const char *iUrl);

#define SERVICE_PASSPORT "PASSPORT"
#define SERVICE_ENOVIA "3DSpace"

/** @nodoc */
bool ExportedByJS0HTTP IsRedirectedForLogin(CATHttpClient &iHttpClient);

/** @nodoc */
//Do not delete [] the returned char*
ExportedByJS0HTTP char* DSYSysGetCASUrl();


#endif
