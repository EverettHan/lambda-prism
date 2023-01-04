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
#ifndef DSYMATRIXLOGIN_H
#define DSYMATRIXLOGIN_H
#include <stdlib.h>
#include <memory.h>
#include "CATSysDataType.h"
#include "CATHttp.h"
#include "CATHttpClient.h"


/** @nodoc */
HRESULT ExportedByJS0HTTP DSYSysMatrixLogin(const char *iServer, const char *iServiceArgs, const char *iUser, const char *iPwd);

/** @nodoc */
HRESULT	ExportedByJS0HTTP DSYSysMatrixLoginUnicode(const CATUnicodeString &iServer, const CATUnicodeString &iParam, const CATUnicodeString &iUser, const CATUnicodeString &iPwd);

/** @nodoc */
HRESULT ExportedByJS0HTTP DSYSysMatrixLogout(CATUnicodeString iServer);

#endif
