//*===========================================================================*
//* COPYRIGHT DASSAULT SYSTEMES 1996                                          *
//*===========================================================================*
//*                                                                           *
//*  CATHttpCookie                                                            *
//*                                                                           *
//*  Usage Notes:  Client Http V1.0                                           *
//*===========================================================================*
//*  Creation novembre 2016                                        sip        *
//*===========================================================================*
#ifndef DSYSYSDLGTOOLS_H
#define DSYSYSDLGTOOLS_H

#include "DSYString.h"
#include "WebLogonPanel.h"


HRESULT ExportedByDSYSysDlg GetCollabPassword(CATUnicodeString	&RTCPwd);
HRESULT ExportedByDSYSysDlg FindHtmlForAlias(const CATUnicodeString& iAppInstance, char **oUrl);


#endif //DSYSYSDLGTOOLS_H
