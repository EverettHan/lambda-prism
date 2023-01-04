#ifndef CATIPGMTopParallel_h_
#define CATIPGMTopParallel_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATTopDefine.h"

class CATBody;
class CATIPGMDistanceTool;
class CATIPGMExtrapolParallelTool;
class CATWire;
class CATICGMExtrapolParallelTool;
class CATICGMDistanceTool;
/**
 * @level Protected
 * @usage U1
 */
extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopParallel;

/**
* Class representing the operator that computes a wire parallel to another one on a skin body.
* <br>The CATIPGMTopParallel operator follows the global frame of the topological operators
* and satisfies the smart mechanism: the
* input bodies are not modified. A new resulting body is created, 
* possibly sharing data with the input bodies.
*<ul>
* <li>A CATIPGMTopParallel operator is created with the <tt>CATPGMCreateTopParallel</tt> global function.
* It must be directly released with the <tt>Release</tt> method after use. It is not streamable. 
*<li>The computation is done by the <tt>Run</tt> method. 
*<li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory, after the operator deletion.
*</ul>
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMTopParallel: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopParallel();

  /** @nodoc */
  virtual void GetSide(CATOrientation &oOri) = 0;

  /** @nodoc */
  virtual void SetSide(CATOrientation iOri) = 0;

  /** @nodoc */
  virtual void SetPLineSimplif(CATLONG32 simplif) = 0;

  // 0 = No PLine simplification
  /** @nodoc */
  virtual void GetPLineSimplif(CATLONG32 &simplif) = 0;

  // 0 = No PLine simplification

  #ifdef CATIACGMR424CAA
  /**
  * Set the extrapolation mode 
  * for the extrapolation of the parallel result wire on the support shell
  * @param iExtrapolationMode
  * <br><b>Legal values</b>:
  * <dl><dt><tt>0</tt><dd> No Extrapolation. 
  *     <dt><tt>1</tt><dd> Extrapolation in tangency continuity. 
  *     <dt><tt>2</tt><dd> Extrapolation in curvature continuity. </dl>
  */
  virtual void SetExtrapolationMode(short iExtrapolationMode = 0) = 0;

  /** 
  * Get the extrapolation mode
  * for the extrapolation of the parallel result wire on the support shell
  * @param oExtrapolationMode
  * <br><b>Legal values</b>:
  * <dl><dt><tt>0</tt><dd> No Extrapolation.
  *     <dt><tt>1</tt><dd> Extrapolation in tangency continuity. 
  *     <dt><tt>2</tt><dd> Extrapolation in curvature continuity. </dl>
  */
  virtual void GetExtrapolationMode(short &oExtrapolationMode) = 0;
  #endif

  /**
   * Returns the pointer to the resulting body.
   * @return
   * The pointer to the resulting body. If you do not want to keep it, 
   * use the @href CATICGMContainer#Remove method to remove it from the 
   * geometric factory, after the operator deletion.
   */
  virtual CATBody *GetResult() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopParallel(); // -> delete can't be called
};

/**
* Creates a CATIPGMTopParallel operator that computes a wire parallel 
* (according to a given law) to another one on a shell.
* <b>Orientation</b>: The resulting wire is oriented as the input one.<br>
* <b>Journal</b>: If the distance is null, a new body is created and 
* the edges are written as kept. If not, the new body contains the new edges, written
* as created.
* @param iOption
* The definition of the parameters for the operation.
* @param iCurve
* The input wire.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopParallel *CATPGMCreateTopParallel(
  CATICGMExtrapolParallelTool *iOption,
  CATBody *iCurve);

/**
* @nodoc
* Creates a CATIPGMTopParallel operator that computes a wire parallel 
* (according to a given law) to another one on a shell.
* <br>
* <b>Orientation</b>: The resulting wire is oriented as the input one.<br>
* <b>Journal</b>: If the distance is null, a new body is created and 
* the edges are written as kept. If not, the new body contains the new edges, written
* as created.
* @param iFactory
* The pointer to the factory of the resulting body.
* @param iData
* The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
* is <tt>NULL</tt>, it is not filled.
* @param iCurve
* The pointer to the body defining the wire. 
* @param iSupport
* The pointer to the body defining the support of the input (and output) wire.
* @param iDistance
* The type of parallel computation.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopParallel *CATPGMCreateTopParallel(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iCurve,
  CATBody *iSupport,
  CATICGMDistanceTool *iDistance);

#endif /* CATIPGMTopParallel_h_ */
