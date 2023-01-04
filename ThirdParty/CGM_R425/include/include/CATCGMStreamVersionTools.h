#ifndef CATCGMStreamVersionTools_h
#define CATCGMStreamVersionTools_h
// COPYRIGHT DASSAULT SYSTEMES  2007
//-----------------------------------------------------------------------------
// Context : NCGM Data Version
// Subject : Debug Converter between String and integer (CATCGMStreamVersion)
//-----------------------------------------------------------------------------
/**
* @level Private
* @usage U1
*/
#include "CATBoolean.h"
#include "CATUnicodeString.h"

#include "ExportedByCATMathStream.h"
#include "CATMathStreamVersionDef.h"
#include "CATListOfCATUnicodeString.h"


/**
 * Debug NCGM Data Version
 */
class ExportedByCATMathStream  CATCGMStreamVersionTools
{
public :

 /**
   * StringToInt  
   *    @param iVersion : string (debug) 
   *    @param oVersion : integer CATCGMStreamVersion
   * return TRUE if succeeded
   */
  static CATBoolean StringToInt(const CATUnicodeString &iVersion, CATCGMStreamVersion &oVersion) ;


 /**
   * IntToString  
   *    @param iVersion : integer CATCGMStreamVersion 
   *    @param oVersion : string (debug) 
   * return TRUE if succeeded
   */
  static CATBoolean IntToString(const CATCGMStreamVersion &iVersion, CATUnicodeString &oVersion) ;


 /**
   * CATCGMStreamVersionMinorable : detect if a data version is manageble in older version  
   *    @param iVersion : string (debug) 
   *    @param oVersion : integer CATCGMStreamVersion
   * return TRUE if succeeded
   */
  static CATBoolean CATCGMStreamVersionMinorable(const CATCGMStreamVersion &iVersion, CATCGMStreamVersion &oVersion) ;
 

  /**
  * AnalyseDirectory :  
  */
  static void  AnalyseDirectory(const CATUnicodeString       & iDirectory,
                                const char                 *   ipSuffixFilter,
                                CATListOfCATUnicodeString  * & oFileNames,
                                 const CATBoolean iWithRiskyConcatenate = FALSE,
                                 CATUnicodeString * iHeaderFileRiskyConcatenate = NULL) ;


  /**
  * ShowType :  
  */
  static const char *ShowType(const short itp);
};

#endif
