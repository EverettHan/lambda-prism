#ifndef CATICGMExtrapolParallelTool_h_
#define CATICGMExtrapolParallelTool_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMVirtual.h"

class CATBody;
class CATCGMJournalList;
class CATICGMDistanceTool;
class CATGeoFactory;
class CATLaw;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMExtrapolParallelTool;

//
//--------------------------------------------------------------------------
//
/**
 * Class defining the parallel computation.
 * <br>This class must be created with the @href CATCGMCreateExtrapolParallelTool 
 * global function and is used by the @href CATICGMTopParallel operator 
 * to define its parameters.
 */
class ExportedByCATGMOperatorsInterfaces CATICGMExtrapolParallelTool: public CATICGMVirtual
{
public:
  /**
   * Constructor
   */
  CATICGMExtrapolParallelTool();

  /**
     * Retrieves the type of computation.
     * @param oDistTool [out, IUnknown#Release]
     * The pointer to the definition of the computation type. 
     */
  virtual void GetDistanceTool(CATICGMDistanceTool *&oDistTool) = 0;

  /**
     * Retrieves the factory that creates the resulting body.
     * @param oFactory
     * The pointer to the factory that creates the resulting body. 
     */
  virtual void GetFactory(CATGeoFactory *&oFactory) = 0;

  /**
     * Retrieves the skin body on which the parallel is computed.
     * @param oSupport
     * The pointer to the skin body. 
     */
  virtual void GetSupport(CATBody *&oSupport) = 0;

  /**
     * Retrieves the topological data associated with <tt>this</tt> tool.
     * @param oData
     * The pointer to the topological data.
     */
  virtual void GetData(CATTopData *&oData) = 0;

  /**
     * Returns the relimitation type.
     * @return
     * The type of relimitation.
     * <br><b>Legal values</b>:
     * <dl><dt><tt>1</tt></dt><dd>Straight relimitation
     * <dt><tt>1</tt></dt><dd>Round relimitation
     * </dl>
     */
  virtual int GetExtrapInfo() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMExtrapolParallelTool(); // -> delete can't be called
};

/**
 * Creates a parallel computation definition.
 * @param iGeoFactory
 * The pointer to the geometry factory that creates the resulting body.
 * @param iData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled.
 * @param iDist
 * The type of computation (parallel, geodesic).
 * @param iSkinBody
 * The pointer to the skin body on which the parallel is computed.
 * @param iRelimitType
 * The type of relimitation.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>1</tt></dt><dd>Straight relimitation
 * <dt><tt>0</tt></dt><dd>Round relimitation
 * </dl>
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATICGMExtrapolParallelTool *CATCGMCreateExtrapolParallelTool(
  CATGeoFactory *iGeoFactory,
  CATTopData *iData,
  CATICGMDistanceTool *iDist,
  CATBody *iSkinBody,
  int iRelimitType = 1);

#endif /* CATICGMExtrapolParallelTool_h_ */
