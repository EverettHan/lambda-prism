//*===========================================================================*
//* COPYRIGHT DASSAULT SYSTEMES 2005                                          *
//*===========================================================================*
//*                                                                           *
//*  CATSysTSURI                                                              *
//*                                                                           *
//*  Usage Notes:                                                             *
//*===========================================================================*
//*  Creation mars 2005                                      adt              *
//*===========================================================================*
#ifndef _CATSYSTSURI
#define _CATSYSTSURI

#include "JS0TSLIB.h"

#include "DSYString.h"
#include "CATSmartMutex.h"

class CATSysTSUnicodeString;
class CATSysTSURIConnection;
class  CATSysIntURI;

struct CATSysURIComponents
{
  CATUnicodeString _Schema;
  CATUnicodeString _Authority;
  CATUnicodeString _Path;
  CATUnicodeString _Query;
  CATUnicodeString _Fragment;
  CATUnicodeString _Host;
  int	           _Port;
};

/**
 * class defining a pointer to a V5 resource, which could be something as simple
 * as a file or a directory, or it can be a reference to a more complicated
 * object, such as aquery to a database or to a search engine.
 */
class ExportedByJS0TSLIB CATSysTSURI
{
public:
  CATSysTSURI ();
  CATSysTSURI (const char *iStr);
  CATSysTSURI (const CATUC2Bytes *iStr);
  CATSysTSURI (const CATSysTSURI&);
  CATSysTSURI (const CATUnicodeString &iStr);
  // @deprecated R418
  CATSysTSURI (const CATSysTSUnicodeString &iStr);

  virtual ~CATSysTSURI ();

/**
 * Returns a CATSysTSURIConnection. 
 * <b>Role</b>:Returns a @href CATSysTSURIConnection object which reresents the 
 * communications link between the application and the current  URI.
 * @return
 *   S_OK on Success.
*/
  HRESULT OpenConnection (CATSysTSURIConnection &oConnection);
  

/**
 * Converts the CATSysTSURI to a unicode string.
 * <b>Role</b>: Converts the current CATSysURI to a CATUC2Bytes character 
 * encoded  string.
 * @return
 *   The resulting CATUC2Bytes string
 */
  const CATUC2Bytes *ConvertToUCChar ();

/**
 * Converts the CATSysURI to a multibytes string.
 * <b>Role</b>: Converts the current CATSysURI to a multibytes character 
 * encoded  string.
 * @return
 *   The resulting multibytes string
 */
  const char *ConvertToChar ();
  

/**
 * Converts the CATSysTSURI to a unicode string.
 * <b>Role</b>: Converts the current CATSysURI to a @href CATUnicodeString
 * @param oStr
 *   The resulting CATUnicodeString
 * @return
 *   S_OK on Success.
 */
  HRESULT ConvertToString (CATUnicodeString &oStr);
  // @deprecated R418
  HRESULT ConvertToString (CATSysTSUnicodeString &oStr);
  
private:
  CATSysIntURI  *_URI;
  CATSmartMutex	_URILock;
};



#endif
