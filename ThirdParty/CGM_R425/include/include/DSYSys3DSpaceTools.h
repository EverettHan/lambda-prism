#ifndef DSYSys3DSpaceTools_H
#define DSYSys3DSpaceTools_H
#include "JS0HTTP.h"
#include "DSYString.h"

/************************************************************************/
/* Defines                                                              */
/************************************************************************/
#define SPACECUSTO_FIRST_URI           "/resources/custoResources/CustoResources"
#define SPACECUSTO_UPDATE_URI          "/resources/custoResources/CustoResources?currentCusto="

/************************************************************************/
/* Functions prototypes                                                 */
/************************************************************************/

HRESULT ExportedByJS0HTTP DSYSysGetLoginTicketAuth(const CATUnicodeString &i3DSpaceServer, const CATUnicodeString &iUser,
	const CATUnicodeString &iSecurityToken, const CATUnicodeString &iTenant, CATUnicodeString &oTicket, CATUnicodeString &oErrorMsgCatalog, CATUnicodeString &oErrorMsgID);

HRESULT ExportedByJS0HTTP DSYSysGetLoginTicket(const CATUnicodeString &i3DPassportServer, const CATUnicodeString &i3DSpaceServer,
	const CATUnicodeString &iUser, const CATUnicodeString &iPwd, const CATUnicodeString &iSecurityToken, const CATUnicodeString &iTenant, CATUnicodeString &oTicket, CATUnicodeString &oErrorMsgCatalog, CATUnicodeString &oErrorMsgID);

HRESULT ExportedByJS0HTTP DSYSysSetSecurityContext(const char *iOnlineInstance = NULL, unsigned int iFlag = 0);

HRESULT ExportedByJS0HTTP DSYSys3DSpaceCustoUpdateCusto( const CATUnicodeString &iSpaceUrl
                                                       , const CATUnicodeString &iTenant);

#endif
