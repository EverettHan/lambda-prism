
#ifndef DSYStringHelper_H
#define DSYStringHelper_H

#include "CATSysTS.h"
#include "CATSysErrorDef.h"     // HRESULT
#include "CATSysDataType.h"

#include "DSYString.h"			// CATUnicodeString, CATString

class CATSysTSUnicodeString;

/**
 * Helper functions to allow for efficient string conversions:
 *  + Move
 *  + Copy
 * ...
 */

enum DSYStringMainRepEncoding
{
    DSYStringMainRepEncoding_Unknown = 0,
    DSYStringMainRepEncoding_MBCS    = 1,       // char view
    DSYStringMainRepEncoding_UCS2    = 2        // Unicode view
};
 
namespace DSY
{
    /************************************************************************/
    /* WARNING: CATSysTSUnicodeString is deprecated and is replaced by      */
    /*          CATUnicodeString.                                           */
    /*          The use of the below functions with CATSysTSUnicodeString   */
    /*          parameters is restricted to a migration path only           */
    /************************************************************************/
	
	
	/**
	 * CUSFrom.
	 * Builds a CATUnicodeString from a wchar_t string. 
	 * @param [in] ipStr A pointer to the wchar_t string. 
	 *        If null, this function will return an empty string (cf. CATUnicodeString::IsEmpty)
	 * @param [in, optional] iLength The length of the input wchar_t string in number of characters. 
	 *        If -1 or not supplied, the string is assumed to be null-terminated.
	 * @param [out, optional] oHr pointer to an HRESULT (local) variable. 
	 *        If not null, will be set to an HRESULT code reporting the outcome of the operation.
	 * 	      IMPORTANT: be aware that supplying this parameter may impact performance negatively.
	 * @return the string, empty in case of error
	 */
    ExportedByCATSysTS CATUnicodeString CUSFrom(const wchar_t* ipStr, size_t iLength = (size_t)-1, HRESULT *oHr = nullptr);
	
	/**
	 * CUSFrom.
	 * Builds a CATUnicodeString from a char16_t string. 
	 * @param [in] ipStr A pointer to the char16_t string. 
	 *        If null, this function will return an empty string (cf. CATUnicodeString::IsEmpty)
	 * @param [in, optional] iLength The length of the input char16_t string in number of characters. 
	 *        If -1 or not supplied, the string is assumed to be null-terminated.
	 * @param [out, optional] oHr pointer to an HRESULT (local) variable. 
	 *        If not null, will be set to an HRESULT code reporting the outcome of the operation.
	 * 	      IMPORTANT: be aware that supplying this parameter may impact performance negatively.
	 * @return the string, empty in case of error
	 */
	ExportedByCATSysTS CATUnicodeString CUSFrom(const char16_t* ipStr, size_t iLength = (size_t)-1, HRESULT *oHr = nullptr);
	 
#if (__cplusplus > 201703L) // char8_t is expected to be supported with C++20 and onwards 
    /**
	 * CUSFrom.
	 * Builds a CATUnicodeString from a char8_t string. 
	 * @param [in] ipStr A pointer to the char8_t string. 
	 *        If null, this function will return an empty string (cf. CATUnicodeString::IsEmpty)
	 * @param [in, optional] iLength The length of the input char8_t string in number of characters. 
	 *        If -1 or not supplied, the string is assumed to be null-terminated.
	 * @param [out, optional] oHr pointer to an HRESULT (local) variable. 
	 *        If not null, will be set to an HRESULT code reporting the outcome of the operation.
	 * 	      IMPORTANT: be aware that supplying this parameter may impact performance negatively.
	 * @return the string, empty in case of error
	 */
    ExportedByCATSysTS CATUnicodeString CUSFrom(const char8_t * ipStr, size_t iLength = (size_t)-1, HRESULT *oHr = nullptr);
#endif
    
    /**
     * Copy.
     * Copy iXX object to oYY object (Shallow copy, COW idiom).
     */
    ExportedByCATSysTS void Copy(CATString &oCS, const CATUnicodeString &iCUS);
    ExportedByCATSysTS void Copy(CATUnicodeString &oCUS, const CATString &iCS);
    ExportedByCATSysTS void Copy(CATSysTSUnicodeString &oCUSTS, const CATUnicodeString &iCUS);
    ExportedByCATSysTS void Copy(CATUnicodeString &oCUS, const CATSysTSUnicodeString &iCUSTS);
    ExportedByCATSysTS void Copy(CATSysTSUnicodeString &oCUSTS, const CATString &iCS);
    ExportedByCATSysTS void Copy(CATString &oCS, const CATSysTSUnicodeString &iCUSTS);
    
    /**
     * Move.
     * Move iXX object to oYY object. 
     * iXX is emptied after move.
     */
    ExportedByCATSysTS void Move(CATString &oCS, CATUnicodeString &iCUS);
    ExportedByCATSysTS void Move(CATUnicodeString &oCUS, CATString &iCS);
    ExportedByCATSysTS void Move(CATSysTSUnicodeString &oCUSTS, CATUnicodeString &iCUS);
    ExportedByCATSysTS void Move(CATUnicodeString &oCUS, CATSysTSUnicodeString &iCUSTS);
    ExportedByCATSysTS void Move(CATSysTSUnicodeString &oCUSTS, CATString &iCS);
    ExportedByCATSysTS void Move(CATString &oCS, CATSysTSUnicodeString &iCUSTS);
    
    ExportedByCATSysTS void Move(CATString &oCS, CATString &iCS);
    ExportedByCATSysTS void Move(CATUnicodeString &oCUS, CATUnicodeString &iCUS);
    ExportedByCATSysTS void Move(CATSysTSUnicodeString &oCUSTS, CATSysTSUnicodeString &iCUSTS);
    
    /**
     * StrCollate.
     * Compare two strings using locale (cf . DSYSysCLocale).
     * Compares the string iStr1 to the string iStr2, both interpreted appropriately according to the LC_COLLATE category of the C locale currently selected.
     * @param iStr1 string to be compared
     * @param iStr2 string to be compared
     * @return an integral value indicating the relationship between the strings:
     *         - zero if both strings are equal.
     *         - a value greater than zero if the first character that does not match has a greater value in iStr1 than in iStr2
     *         - a value less than zero otherwise.
     */
    ExportedByCATSysTS int StrCollate(const CATUnicodeString &iStr1, const CATUnicodeString &iStr2);
    
#define DSYStringEnvDecimalSeparator  0x01
    class _NumConvertCtx;
    /**
     * NumConvertCtx.
     * WARNING: do not share contexts between threads!
     */
    class ExportedByCATSysTS NumConvertCtx
    {
    public:
        NumConvertCtx(int iFlags = 0) : m_Data(nullptr), m_Flags(0) { Reset(); SetFlags(iFlags); }
        ~NumConvertCtx();
        
        void SetFlags(int iFlags);
        bool SetDecimalSeparator(int iDecimalSep);  // Unicode character
        void Reset();
        
        int GetFlags() { return m_Flags; }
        int GetDecimalSeparator();
        
    private:
        friend class _NumConvertCtx;
        
        // Members
        _NumConvertCtx *m_Data;
        int m_Flags;
        int m_decimalPoint;
    };
    
    /**
     * ConvertToNumEx.
     * IMPORTANT: consider using the Standard library <charconv> API instead, if applicable/available
     * Parse the input string looking for a number to save in d; whitespaces are ignored.
     * Note that by default, this function is locale (C, C++) independent and the decimal separator expected is the dot.
     * Moreover, thousands separators are not supported.
     * IMPORTANT: to handle locale-dependent decimal separators, one could write the following code:
     *      DSY::NumConvertCtx ctx(DSYStringEnvDecimalSeparator);   // Use DS locale's decimal separator setting
     *      HRESULT hr = DSY::ConvertToNumEx(d, l_szFloat, &ctx);
     * or even use the method SetDecimalSeparator.
     * @param d reference to the variable that will hold the number
     * @param iStr input string
     * @param iCtx Either null or an instance of NumConvertCtx initialized with one of the following flags:
     *         + DSYStringConvertToNumFullWidthDigitSupport Enable support for full-width digits that are commonly used in languages such as Japanese (and potentially in all languages)
                                                            Note that this may not be supported on all platforms (return code is E_NOTIMPL if not supported).
     * @return S_OK on success, an HRESULT error code otherwise.
     */
#define DSYStringConvertToNumFullWidthDigitSupport  0x10
    ExportedByCATSysTS HRESULT ConvertToNumEx(double &d, const CATUnicodeString &iStr, NumConvertCtx *iCtx = nullptr);
    
    
    /**
     * Isolate.
     * Privatize the string. 
	 * NOTE: breaks sharing of data by multiple instances (if applicable)
     */
    ExportedByCATSysTS void Isolate(CATUnicodeString &ioCUS);
    ExportedByCATSysTS void Isolate(CATString &ioCUS);
    
    /**
     * Pack.
     * Ensure that the input string representation is as compact as possible.
     * @return non-zero value if packing has been performed.
     * @return zero otherwise.
     * NOTE: for e.g., if the input string contains ASCII and is allocated in UTF-16 form,
     *       its representation will be converted to a C-string (char *).
     */
    ExportedByCATSysTS int  Pack(CATUnicodeString &ioCUS);
    ExportedByCATSysTS int  Pack(CATString &ioCUS);
    
    /**
     * DSYStringMainRepEncoding.
     * Get the encoding of the working form of the input string.
     * This should only be used as a hint for optimization purposes.
     */    
    ExportedByCATSysTS DSYStringMainRepEncoding GetMainRepEncoding(const CATUnicodeString &iCUS);
    ExportedByCATSysTS DSYStringMainRepEncoding GetMainRepEncoding(const CATString &iCS);
	
	
	/************************************************************************/
    /* Implementation                                                       */
    /************************************************************************/
	
	/** @nodoc
	 * Builds a CATUnicodeString from an UTF16-encoded string. 
	 * Mostly meant to support building a CATUnicodeString from a WCHAR string (cf. CATWTypes.h), 
	 * WCHAR is defined as "wchar_t" on Windows and as "unsigned short" on other OS 
	 * But nodoc since "unsigned short" is not a character type...
	 */
	ExportedByCATSysTS CATUnicodeString CUSFrom(const unsigned short *ipsz, size_t iLength = (size_t)-1, HRESULT *oHr = nullptr);
	
#if !defined(DSYStringHelper_INTERNAL_CUSFrom_Allow)
#define DSYStringHelper_INTERNAL_CUSFrom_Deleted
	
	// Prevent the following CUSFrom signatures to be implemented
	// The "char" character type is ambiguous (which encoding? cf. DSYStringView). For UTF-8 encoded strings, see unambiguous 'char8_t' signature
	CATUnicodeString CUSFrom(const char * ipsz, size_t iLength = (size_t)-1, HRESULT *oHr = nullptr) = delete;
	
	// char32_t is not widely used because it's often a waste of memory / discourage its usage
	CATUnicodeString CUSFrom(const char32_t* ipsz, size_t iLength = (size_t)-1, HRESULT *oHr = nullptr) = delete;
	
#endif	// DSYStringHelper_INTERNAL_CUSFrom_Allow

}	// namespace DSY

#endif  // DSYStringHelper_H
