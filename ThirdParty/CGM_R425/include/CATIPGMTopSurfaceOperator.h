#ifndef CATIPGMTopSurfaceOperator_h_
#define CATIPGMTopSurfaceOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopSurfaceOperator;

//COPYRIGHT DASSAULT SYSTEMES 1998
//===================================================================
//     Author : JEL
//     Date   : 17 / 06 / 1999
// Class CATIPGMTopSurfaceOperator :
// Operator offers the Topological build of a surface :
//
//-------------------------------------------------------------------
// Notes :
// -----
// The Run() method is mandatory.
// The result Body will be frozen by default.
// Report can be done on operator.
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// Usage Notes :
// -----------
//  basic class : no direct use.
//===================================================================
class ExportedByCATGMOperatorsInterfaces CATIPGMTopSurfaceOperator: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopSurfaceOperator();

  //
  // Set Methods
  //
  /**  
 * @nodoc 
 */
  virtual CATLONG32 SetClosure(CATLONG32 iclosed) = 0;

  //
  // Get Methods
  //
  /**  
 * @nodoc 
 */
  virtual CATLONG32 GetClosure(CATLONG32 &oClosed) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopSurfaceOperator(); // -> delete can't be called
};

#endif /* CATIPGMTopSurfaceOperator_h_ */
