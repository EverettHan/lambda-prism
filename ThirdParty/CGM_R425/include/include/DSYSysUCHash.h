#ifndef DSYSysUCHash_H
#define DSYSysUCHash_H

#include "CATSysTS.h"
#include "CATSysDataType.h"

// Legacy defines
#ifndef UHASH_EMPTY
# define UHASH_EMPTY                    1
#endif

// TODO: remove the below typedef when its defined in either CATDataType or 
// CATSysDataType header.
typedef unsigned int CATHashKey;

class DSYSysCodePage;

namespace DSYSysUCAlgorithm
{
    /************************************************************************/
    /* Hash algorithms                                                      */
    /************************************************************************/
    
    /**
     * Remarks on the interoperability with CATUnicodeString hash values.
     * Unlike the CATUnicodeString API, the following hash calculation 
     * routines DO NOT unset the MSB in the hash values.
     * This imply that one can't safely use the return value of ComputeHashKey
     * and/or HashFunc as a seed to compute a new hash value.
     * The sign bit has been masked for compatibility purposes. Consider the 
     * following code:
     *   // ...
     *   // // Sample Hash table implementation
     *   // int hash = HashV3FromXXXX(...);
     *   // int idx = hash % 100;            // Modulo preserves the sign bit
     *   // Bucket buck = myHashTable[idx];  // DANGEROUS!!!
     *   // ...
     *   // At this point, without "idx" might hold a negative value,
     *   // which would probably lead to an invalid memory access.
     */
    
    // DO NOT USE BEGIN
    // See below this section.
    /**
    * HashV3 algorithm.
    * This algorithm computes a hash value for an input string based on its 
    * UCS-2/UTF-16 representation.
    * IMPORTANT: to allow for evolutions, one must use the generic signatures
    * (cf. HashFromXXXX functions below).
    */
    ExportedByCATSysTS CATHashKey HashV3FromUCS2(const CATUC2Bytes *iStrUCS2, size_t iNChar, CATHashKey iHash = 0);
    ExportedByCATSysTS CATHashKey HashV3FromUTF8(const char *iStrUTF8, size_t iNBytes, CATHashKey iHash = 0);
#if (__cplusplus > 201703L) // char8_t is expected to be supported with C++20 and onwards 
    inline CATHashKey HashV3FromUTF8(const char8_t *iStrUTF8, size_t iNBytes, CATHashKey iHash = 0) {
        return HashV3FromUTF8(reinterpret_cast<char const*>(iStrUTF8), iNBytes, iHash);
    }
#endif
    ExportedByCATSysTS CATHashKey HashV3FromMBCS(const char *iStrMBCS, size_t iNBytes, CATHashKey iHash = 0, const DSYSysCodePage *iCP = NULL);
    /**
     * Optimistic algorithm.
     * This algorithm is based on the assumption that the vast majority of 
     * MBCS strings are in fact US ASCII (character value < 128). This is due 
     * to the fact that they are often built from C-string literals that are 
     * hard-coded or more generally from C-string that act as identificators.
     * TODO OPTIMIZATION: as a side effect, this routine could indicate to 
     * the caller whether or not the input string is ASCII-encoded.
     */
    ExportedByCATSysTS CATHashKey HashV3FromMBCSOptimistic(const char *iStrMBCS, size_t iNBytes, CATHashKey iHash = 0, const DSYSysCodePage *iCP = NULL);
    // DO NOT USE END
    
    /**
    * Unified hash algorithm. It is declined in three flavours that allow to 
    * compute a unique hash value for a given string encoded in any of the 
    * following formats:
    *  - UCS-2/UTF-16
    *  - UTF-8
    *  - MBCS (locale dependent, cf. DSYSysCodePage)
    * 
    * @param [in]  iStrXXXX is a pointer to the string to be hashed.
    * @param [in]  iNChar|iNBytes is the length|size of the input string in 
    *              characters|bytes.
    * @param [in]  iHash is the input hash value for the algorithm. Specifying 
    *              this parameter allows for efficient hash updating. (for e.g 
    *              in the case of a string that is build in a loop).
    *              [WARNING]: when iHash is supplied, caution must be taken so 
    *              iNChar does not split a multibyte character (UTF-8/UTF-16),
    *              otherwise, the final hash value will be incorrect!
    * @param [in]  iCP is reserved for internal use only.
    * @retval hash value.
    */
    inline CATHashKey HashFromUCS2(const CATUC2Bytes *iStrUCS2, size_t iNChar, CATHashKey iHash = 0)
    {
        return HashV3FromUCS2(iStrUCS2, iNChar, iHash);
    }
    
    template<typename _CTyp>
    inline CATHashKey HashFromUTF8(const _CTyp *iStrUTF8, size_t iNBytes, CATHashKey iHash = 0)
    {
        return HashV3FromUTF8(iStrUTF8, iNBytes, iHash);
    }
    
    inline CATHashKey HashFromMBCS(const char *iStrMBCS, size_t iNBytes, CATHashKey iHash = 0, const DSYSysCodePage *iCP = NULL)
    {
        return HashV3FromMBCSOptimistic(iStrMBCS, iNBytes, iHash, iCP);
    }
        
    /************************************************************************/
    /* Legacy Hash algorithms                                               */
    /************************************************************************/
    /**
    * @deprecated
    * HashV2MBCS is a legacy hash algorithm that is based on MBCS encoding.
    * Therefore, its results depend on the locale used to encode the input 
    * string. It was used in CATUnicodeString prior to the R217 version.
    */
    ExportedByCATSysTS CATHashKey HashV2MBCS(const char *iStrMBCS, size_t iNBytes);
    
    /**
    * @deprecated
    * HashV2UCS2 is a legacy hash algorithm that is based on the UCS-2 
    * encoding.
    * It was used in CATSysTSUnicodeString prior to the R217 version.
    */
    ExportedByCATSysTS CATHashKey HashV2UCS2(const CATUC2Bytes *iStrUCS2, size_t iNChar);
}

#endif  // DSYSysUCHash_H
