#ifndef CATIPGMRemoveFacesInShell_h_
#define CATIPGMRemoveFacesInShell_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATBody;
class CATCGMJournalList;
class CATGeoFactory;
class CATTopData;
class CATLISTP(CATCell);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMRemoveFacesInShell;

/** 
 * Class representing the operator that creates a shell body from a list of faces
 * Moreover, the operator allows the faces to have inside loops (holes).
 * <br>To use the CATIPGMRemoveFacesInShell :
 * <ul><li>Create the <tt>CATPGMCreateRemoveFacesInShell</tt> global function. 
 * <li>If needed, tune some parameters with the <tt>SetXxx</tt> methods. In particular, closure or internal
 * loops can be described at this time.
 * <li> <tt>Run</tt> the operator
 * <li>Retrieve the created body (frozen by default) with the <tt>GetResult</tt> method. 
 * <li>Release the operator with the <tt>Release</tt> method after use.</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMRemoveFacesInShell: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMRemoveFacesInShell();

  /** 
 * Runs <tt>this</tt> operator.
 */
  virtual int Run() = 0;

  /**
 * Returns the pointer to the shell of the resulting skin body.
 * @return
 * The pointer to the shell of the resulting skin body. Remember that the whole body is retrieved with
 * the <tt>GetResult</tt> method, and you must manage its deletion if you do not want to keep it.
 */
  // ??	virtual CATShell* GetShell() const=0;
  //==============================================================================
  // CGMReplay CGMReplay CGMReplay CGMReplay CGMReplay CGMReplay CGMReplay
  //==============================================================================
  virtual void SetInitialBody(CATBody *iBody) = 0;

  virtual void SetFacesToRemove(CATLISTP(CATCell) &iFacesToRemove) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMRemoveFacesInShell(); // -> delete can't be called
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
ExportedByCATGMOperatorsInterfaces CATIPGMRemoveFacesInShell *CATPGMCreateRemoveFacesInShell(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBody,
  CATLISTP(CATCell) *iFacesToRemove);

#endif /* CATIPGMRemoveFacesInShell_h_ */
