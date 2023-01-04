#ifndef CATICGMRemoveFacesInShell_h_
#define CATICGMRemoveFacesInShell_h_

// COPYRIGHT DASSAULT SYSTEMES 2010

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopOperator.h"

class CATBody;
class CATCGMJournalList;
class CATGeoFactory;
class CATTopData;
class CATLISTP(CATCell);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMRemoveFacesInShell;

/** 
* Class representing the operator that creates a shell body from a list of faces
* Moreover, the operator allows the faces to have inside loops (holes).
* <br>To use the CATICGMRemoveFacesInShell :
* <ul><li>Create the <tt>CATCGMCreateRemoveFacesInShell</tt> global function. 
* <li>If needed, tune some parameters with the <tt>SetXxx</tt> methods. In particular, closure or internal
* loops can be described at this time.
* <li> <tt>Run</tt> the operator
* <li>Retrieve the created body (frozen by default) with the <tt>GetResult</tt> method. 
* <li>Release the operator with the <tt>Release</tt> method after use.
</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATICGMRemoveFacesInShell: public CATICGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATICGMRemoveFacesInShell();

  /** 
 * Runs <tt>this</tt> operator.
 */
  virtual int Run() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMRemoveFacesInShell(); // -> delete can't be called
};

/**
 * Creates an operator to build a new shell from an initial shell and a list of faces to remove.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. If the journal inside the
 * configuration is <tt>NULL</tt>, it is not filled. 
 * @param iBody
* The pointer to the 2D body containing the shell with faces to remove
 * @param iFacesToRemove
* The pointer to the list of faces to remove in the initial shell.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATICGMRemoveFacesInShell *CATCGMCreateRemoveFacesInShell(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBody,
  CATLISTP(CATCell) *iFacesToRemove);

#endif /* CATICGMRemoveFacesInShell_h_ */
