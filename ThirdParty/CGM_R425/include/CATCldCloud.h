//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 1999
//==============================================================================================================
// CATCldCloud
//==============================================================================================================
// Creation: JLH - ??-Oct-1999
// 24-03-2014 CGMOFF+CGMPRJ
//==============================================================================================================

#ifndef CATCldCloud_H
#define CATCldCloud_H

/**
 * @CAA2Level L0
 * @CAA2Usage U0
 */ 

#include "CATCldUniCell.h"

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATCldCloud ;
#else
extern "C" const IID IID_CATCldCloud ;
#endif

/**
 * Interface for the CloudEditor entity <tt>CATCldCloud</tt>.<br>
 * The <tt>CATCldCloud</tt> corresponds to an <i>unordered</i> set of points.<br>
 * @see CATCldGenEntity, CATCldCell, CATCldUniCell
 */
class ExportedByCATGMGeometricInterfaces CATCldCloud : public CATCldUniCell
{
  CATDeclareInterface ;

public:

} ;

CATDeclareHandler (CATCldCloud, CATCldUniCell) ;

#endif
