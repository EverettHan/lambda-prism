// COPYRIGHT DASSAULT SYSTEMES 2011
//=============================================================================
// Creation JHN  23/05/2011
//
// VoB : result of check
// on one vertex)
//=============================================================================

#ifndef __CATCGMVoBResult_h__
#define __CATCGMVoBResult_h__
#include "CATCGMVoBCheckOptions.h"
#include "CATCell.h"
#include "ListPOfCATCell.h"
#include "CATGMModelInterfaces.h"

class CATCGMStream;
class CATGeoFactory;

struct ExportedByCATGMModelInterfaces CATCGMVoBResult
{
  CATCGMVoBCheckOptions _VoBOption;
  ListPOfCATCell _VoBCheckFailureCells;

  CATCGMVoBResult();
  // copy constructor 
  CATCGMVoBResult(const CATCGMVoBResult & iOther);

private:
  // equal operator
  CATCGMVoBResult& operator=(const CATCGMVoBResult &);
  
};
/** 
 * @collection CATCGMVoBResult
 * Collection class for pointers to (topological) cells.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */

#include "CATLISTPP_Clean.h"
#include "CATLISTPP_PublicInterface.h"
#include "CATLISTPP_Declare.h"

#include "CATGMModelInterfaces.h"
#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByCATGMModelInterfaces
/** @nodoc */
CATLISTPP_DECLARE_TS(CATCGMVoBResult, 10)
/** @nodoc */
typedef CATLISTP(CATCGMVoBResult) ListPOfVoBResult;


#endif
