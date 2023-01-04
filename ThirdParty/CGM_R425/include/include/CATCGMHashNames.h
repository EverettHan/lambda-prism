/* -*-c++-*- */
/**
* @COPYRIGHT DASSAULT SYSTEMES 2009
*/
#ifndef CATCGMHashNames_H 
#define CATCGMHashNames_H 
//=============================================================================
// DESCRIPTION :  ~ CATCGMHashDico with embedded LifeCycle
//=============================================================================
#include "CATCGMHashTableWithAssoc.h"
#include "CATDataType.h"
 
/**
*  Dictionnary of Names.
*/

class   ExportedByCATMathematics  CATCGMHashNames  : protected  CATCGMHashTableWithAssoc
{
public:
  CATCGMHashNames (int iEstimatedSize = 0);
  ~CATCGMHashNames();

  CATCGMNewClassArrayDeclare;
  
  int             Insert(const char* ipName, const CATULONGPTR iValue);

  const char    * Locate(const char* ipName, CATULONGPTR & oValue) const;

 };

 
#endif
