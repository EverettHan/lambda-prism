// COPYRIGHT DASSAULT SYSTEMES 2014

/**
 * DSYSysNLSCore is an API which allows to retrieve NLS data from 
 * the SUPPLANG_V6 file.
 */

#ifndef DSYSysNLSCore_H
#define DSYSysNLSCore_H

#include <stddef.h>             // size_t
#include "CATSysTS.h"
#include "CATSysDataType.h"
#include "CATSysErrorDef.h"

#define DSYSYS_NLSFILTER_STANDARD       0x0
#define DSYSYS_NLSFILTER_CUSTOM         0x1

struct DSYSysNLSEnv             // POD
{
    char     language[32];
    char     country [32];
    char     lang    [32];                      // "<language>[_<country_region>[.<code_page>]]"
    char     codePage[16];                      // character set used for encoding multibyte strings
    wchar_t  decimalPoint[8];                   // Decimal-point separator
    size_t   mbCharMaxSize;                     // the maximum size of a multibyte character (If not available, set to 0)
};

    
/**
 * GetEnvNLSData.
 * Fills a DSYSysNLSEnv structure with NLS environment data.
 * @retval S_OK if the session is valid.
 * @retval E_FAIL in case of error.
 */
ExportedByCATSysTS HRESULT GetEnvNLSData(DSYSysNLSEnv *oData);
inline HRESULT GetEnvNLSDataA(DSYSysNLSEnv *oData) { return GetEnvNLSData(oData); }
    
#endif // DSYSysNLSCore_H
