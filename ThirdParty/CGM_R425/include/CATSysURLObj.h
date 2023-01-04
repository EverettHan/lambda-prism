
#ifndef CATSysURLObj_H
#define CATSysURLObj_H

#include "JS0HTTP.h"
#include "CATSysErrorDef.h"
#include "DSYString.h"
#include "CATHttpTools.h"

#include <algorithm>    // std::swap

class ExportedByJS0HTTP CATSysURLObj
{
public:
    // Inline constructors
    CATSysURLObj(const CATUnicodeString &iszUrl) 
        : m_szUrl(iszUrl), hrInit(S_FALSE) { Init(); }
    CATSysURLObj(const char *iszUrl) 
        : m_szUrl(iszUrl), hrInit(S_FALSE) { Init(); }
    CATSysURLObj(const wchar_t *iszUrl) 
        : hrInit(S_FALSE) { m_szUrl.BuildFromWChar(iszUrl); Init(); }
    
    CATSysURLObj(const CATSysURLObj & iOther);
    CATSysURLObj(CATSysURLObj && iRValue);          // Move constructor
    CATSysURLObj& operator=(CATSysURLObj iOther);
    CATUnicodeString    GetScheme();
    CATUnicodeString    GetHost();
    CATUnicodeString    GetPort();
    CATUnicodeString    GetURI();

    bool IsValid() const;
    HRESULT Init(); // deprecated, use IsValid() which is const
    
    CATUnicodeString ToString() const { return m_szUrl; } // Normalized, lower case URL string, that can be used for comparison (alternatively to operator ==)
    ~CATSysURLObj();
    
    bool operator ==(const CATSysURLObj & iComparand) const;
    inline bool operator !=(const CATSysURLObj & iComparand) const { return !(*this == iComparand); }
    
    // Members
    CATSysURL m_UrlStruct;
    
private:

    // Members
    CATUnicodeString m_szUrl;
    CATUnicodeString m_Port;
    HRESULT hrInit;
};


inline CATSysURLObj::CATSysURLObj(CATSysURLObj && iRValue) : m_szUrl(iRValue.m_szUrl)
{
    this->hrInit = iRValue.hrInit;
    this->m_UrlStruct = iRValue.m_UrlStruct;
    memset(&iRValue.m_UrlStruct, 0, sizeof (CATSysURL));
}

inline CATSysURLObj& CATSysURLObj::CATSysURLObj::operator=(CATSysURLObj iOther)
{
    std::swap(this->m_UrlStruct, iOther.m_UrlStruct);
    std::swap(this->m_szUrl, iOther.m_szUrl);
    std::swap(this->hrInit,  iOther.hrInit);
    return *this;
}

inline bool CATSysURLObj::IsValid() const
{
    return SUCCEEDED(hrInit);
}

#endif  // CATSysURLObj_H
