
#pragma once

#include <atlstr.h>     // CString
#include "DSYString.h"

namespace DSY
{
    inline CATUnicodeString CUSFrom(const CString & iATLCString)
    {
        CATUnicodeString cus;
#ifdef UNICODE
        // CString is CStringW
        cus.BuildFromWChar(static_cast<const wchar_t *>(iATLCString), iATLCString.GetLength());
#else
        // CString is CStringA
        cus = static_cast<const char *>(iATLCString);
#endif
        return cus;
    }
    
    inline CString ATLCStringFrom(const CATUnicodeString & iCUS)
    {
#ifdef UNICODE
        // CString is CStringW
        CString atlcstr((const wchar_t *)iCUS.ConvertToUCChar(), iCUS.GetLengthInChar());
#else
        // CString is CStringA
        CString atlcstr(iCUS.ConvertToChar());
#endif
        return atlcstr;
    }
}   // namespace DSY
