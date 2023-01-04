//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 2006
//==============================================================================================================
// File: CATICldCloud.h
//==============================================================================================================
// Creation: JLH - 30-Jun-2006
//==============================================================================================================

#ifndef CATICldCloud_h
#define CATICldCloud_h

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATICldCell.h"

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATICldCloud ;
#else
extern "C" const IID IID_CATICldCloud ;
#endif

/**
 * Interface for the entity <tt>CATICldCloud</tt>.<br>
 * The <tt>CATICldCloud</tt> corresponds to an <i>unordered</i> set of points.<br>
 * @see CATICldGenEntity, CATICldCell
 */
class ExportedByCATGMGeometricInterfaces CATICldCloud : public CATICldCell
{
  CATDeclareInterface ;

public:

} ;

CATDeclareHandler (CATICldCloud, CATICldCell) ;

#endif
