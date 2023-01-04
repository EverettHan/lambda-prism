#ifndef CATIPGMTopShellOrientation_h_
#define CATIPGMTopShellOrientation_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATShell;
class CATSurLimits;
class CATSurface;
class CATTransfoManager;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopShellOrientation;

/**
 * Class defining the operator that modifies the orientation of the faces of a shell  
 * as well as the underlying surfaces so that the faces, the surfaces and the shell 
 * all have the same orientation.
 * This operator follows the general scheme of the topological operators:
 * <ul>
 *<li> Creates the operator with the <tt>CATPGMCreateTopShellOrientation</tt> global function, which defines
 * the body which contains the faces to be inverted.
 *<li> Runs with the <tt>Run</tt> method. 
 *<li> Gets the result body by the <tt>GetResult</tt> method. 
 *<li> Release the operator with the <tt>Release</tt> method after use.
 *</ul>
 */
//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATIPGMTopShellOrientation: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopShellOrientation();

  /**
   * Runs <tt>this</tt> operator. Returns 0 if the operation completes properly.
   */
  virtual int Run() = 0;

#if defined ( CATIACGMV5R22 )
  /**
   * @nodoc
   * Change Specification To Simple Skin Inversion Without Any Surface Consideration.
   * Be carefull , input conditions are restricted to Surfacic Body (not volumic or wireframe) 
   */
  virtual void ChangeSpecificationToSimpleSkinInversionWithoutAnySurfaceConsideration() = 0;
#endif

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopShellOrientation(); // -> delete can't be called
};

#endif /* CATIPGMTopShellOrientation_h_ */
