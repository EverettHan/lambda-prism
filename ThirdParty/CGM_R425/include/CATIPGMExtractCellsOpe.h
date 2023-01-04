#ifndef CATIPGMExtractCellsOpe_h_
#define CATIPGMExtractCellsOpe_h_

// COPYRIGHT DASSAULT SYSTEMES 2017

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMPersistentOperator.h"

class CATBody;
class CATGeoFactory;
class CATTopData;
class CATLISTP(CATCell);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMExtractCellsOpe;

/** 
 * Class representing the operator that creates a body from a list of cells.
 * Moreover, the operator allows input hybrid or/and non-manifold body. 
 * Be aware that the result body could also be non-manifold depending of the given input cells.
 * <br>To use the CATIPGMExtractCellsOpe :
 * <ul><li>Create the <tt>CATPGMCreateExtractCellsOpe</tt> global function. 
 * <li>If needed, tune some parameters with the <tt>SetXxx</tt> methods. In particular, closure or internal
 * loops can be described at this time.
 * <li> <tt>Run</tt> the operator
 * <li>Retrieve the created body (frozen by default) with the <tt>GetResult</tt> method. 
 * <li>Release the operator with the <tt>Release</tt> method after use.</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMExtractCellsOpe: public CATIPGMPersistentOperator
{
public:

  // =========================================================
  // Set Methods ( before Run )
  // =========================================================
  /**
  * Set a list of CATDomain for priority orientation.
  * @param iDomainList
  * The domain list to append.
  */
  virtual void SetDomainsOrientationPriority(const CATLISTP(CATDomain) &iDomainList) = 0;

  /**
  * Enable 'reverse' selection of all other cells on the body that are not in the given input cells.
  * @param iValue
  *<dl>
  *<dt><tt>FALSE</tt></dt><dd> This mode is used by default at the creation of the operator.
  *<dt><tt>TRUE</tt></dt><dd>  Create a body with all cells that are NOT in <tt>iInputCellList</tt>.
  *</dl>
  */
  virtual void SetComplementaryMode(CATBoolean iValue = TRUE) = 0;




  //==========================================================
  // Get Methods  ( Output after Run )
  // =========================================================
  /** 
  * Only if <tt>iInputCellList</tt> are CATFace or CATEdge type.
  * Retrieve all cells whose orientation have been inverted regarding their respective new domain.
  * @param oInvertedCellList
  * The list of pointer on resulting cells.
  * Restriction : This method will return E_FAIL if input cells are Volume type of Vertex type. 
  *               This method also return E_FAIL if any input cell belong to more than one domain (shell or Loop).
  **/
  virtual HRESULT GetInvertedCells(CATLISTP(CATCell) &oInvertedCellList) const = 0;


protected:

  /**
   * Constructor
   */
  CATIPGMExtractCellsOpe();

  /**
   * Destructor
   */
  virtual ~CATIPGMExtractCellsOpe(); // -> delete can't be called
};

/**
 * Creates an operator to build a new body from an initial body and a list of cells to extract.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. If the journal inside the
 * configuration is <tt>NULL</tt>, it is not filled. 
 * @param iBody
 * The pointer to the body containing the cells to extract.
 * @param iInputCellList
 * The pointer to the list of cells to extract in the input body. 
 * All given cells must have the same dimension. Vertices, Edges, Faces and Volumes are accepted. 
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMExtractCellsOpe *CATPGMCreateExtractCellsOpe(
  CATGeoFactory *ipFactory,
  CATTopData *ipTopData,
  CATBody *ipInputBody,
  const CATLISTP(CATCell) &iInputCellList);

#endif /* CATIPGMExtractCellsOpe_h_ */


