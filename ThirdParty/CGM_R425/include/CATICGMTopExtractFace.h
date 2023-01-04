#ifndef CATICGMTopExtractFace_h_
#define CATICGMTopExtractFace_h_

// COPYRIGHT DASSAULT SYSTEMES 2011

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopOperator.h"

class CATBody;
class CATCloneManager;
class CATCrvLimits;
class CATFace;
class CATICGMHybOperator;
class CATLoop;
class CATPCurve;
class CATICGMSkinOperator;
class CATICGMTopologicalOperator;
class CATLISTP(CATCell);
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMTopExtractFace;

/**
 * Class representing the operator that rebuilds a body from a set of faces on an input body.
 * The new faces keep only data necessary to them. Adjacency information has disappeared.
 * If <tt>DoFaceAssembly</tt> is called before running the operator and there are two or more
 * input faces, the operator assembles the output faces. 
 * <br>To use it:
 *<ul>
 * <li>Create it with the <tt>CATCGMCreateTopExtractFace</tt> global function.
 * <li>Tune it with appropriate options, using the <tt>SetXxx</tt> methods. 
 * <li>Run it
 * <li>Get the result using the GetResult method. If you do not want 
 * to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
 * geometric factory, after the operator deletion.
 * <li>Release the operator with the <tt>Release</tt> method after use.
 *</ul> 
 */
class ExportedByCATGMOperatorsInterfaces CATICGMTopExtractFace: public CATICGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATICGMTopExtractFace();

  //-------------------------------------------------------------------------
  // Operator management
  //-------------------------------------------------------------------------
  /**
    * Runs the operator.
    * @return
    * <br><b>Legal values</b>: <tt>0</tt> if ok, <tt>1</tt> if failed
    */
  virtual int Run() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMTopExtractFace(); // -> delete can't be called
};

/**
 * Creates an operator that extracts a face from a body.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iTopData
 * The pointer to the data defining the configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled.
 * @param iFace
 * The face to be extracted.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATICGMTopExtractFace *CATCGMCreateTopExtractFace(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATFace *iFace);

#endif /* CATICGMTopExtractFace_h_ */
