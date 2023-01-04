#ifndef CATIPGMTopSkinBorderSorting_h_
#define CATIPGMTopSkinBorderSorting_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATLISTP(CATEdge);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopSkinBorderSorting;

// COPYRIGHT DASSAULT SYSTEMES  2004
//
/**
 * Class defining the operator that computes the list of edges bording a smooth skin.
 *<br>
 * The CATIPGMTopSkinBorderSorting follows the global frame of the topological operators and satisfies the smart mechanism: 
 * the input bodies are not modified. A new resulting body is created, 
 * possibly sharing data with the input bodies.
 *<ul>
 * <li>A CATTopSmoothSkinBorderComputer is created with the <tt>CATCreateSmoothSkinBorderComputer</tt> global method:
 * It must be directly released with the <tt>Release</tt> method after use. It is not streamable. 
 *<li>The result is accessed with the <tt>GetResultListEdges</tt> method. 
 *</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMTopSkinBorderSorting: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopSkinBorderSorting();

  /**
* @nodoc
*/
  // CATCGMNewClassArrayDeclare;
  /**
* Runs the operator
*/
  virtual int Run() = 0;

  /**
* Returns the list of cells .
*/
  virtual void GetResultListEdges(CATLISTP(CATEdge) &oListEdges) = 0;

  /**
* 
*/
  virtual CATBoolean IsBoundaryOrderStable() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopSkinBorderSorting(); // -> delete can't be called
};

#endif /* CATIPGMTopSkinBorderSorting_h_ */
