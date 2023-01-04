#ifndef CATICGMTopShellOrientation_h_
#define CATICGMTopShellOrientation_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopOperator.h"

class CATShell;
class CATSurLimits;
class CATSurface;
class CATTransfoManager;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMTopShellOrientation;

/**
 * Class defining the operator that modifies the orientation of the faces of a shell  
 * as well as the underlying surfaces so that the faces, the surfaces and the shell 
 * all have the same orientation.
 * This operator follows the general scheme of the topological operators:
 * <ul>
 *<li> Creates the operator with the <tt>CATCGMCreateTopShellOrientation</tt> global function, which defines
 * the body which contains the faces to be inverted.
 *<li> Runs with the <tt>Run</tt> method. 
 *<li> Gets the result body by the <tt>GetResult</tt> method. 
 *<li> Release the operator with the <tt>Release</tt> method after use.
 *</ul>
 */
//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATICGMTopShellOrientation: public CATICGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATICGMTopShellOrientation();

  /**
   * Runs <tt>this</tt> operator. Returns 0 if the operation completes properly.
   */
  virtual int Run() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMTopShellOrientation(); // -> delete can't be called
};

#endif /* CATICGMTopShellOrientation_h_ */
