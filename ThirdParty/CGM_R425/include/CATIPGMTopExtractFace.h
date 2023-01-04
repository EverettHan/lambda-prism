#ifndef CATIPGMTopExtractFace_h_
#define CATIPGMTopExtractFace_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATBody;
class CATCloneManager;
class CATCrvLimits;
class CATFace;
class CATIPGMHybOperator;
class CATLoop;
class CATPCurve;
class CATIPGMSkinOperator;
class CATIPGMTopologicalOperator;
class CATLISTP(CATCell);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopExtractFace;

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
class ExportedByCATGMOperatorsInterfaces CATIPGMTopExtractFace: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopExtractFace();

  //-------------------------------------------------------------------------
  // Operator management
  //-------------------------------------------------------------------------
  /**
    * Runs the operator.
    * @return
    * <br><b>Legal values</b>: <tt>0</tt> if ok, <tt>1</tt> if failed
    */
  virtual int Run() = 0;

  /**
	 * @nodoc
	 * Causes multiple result faces to be assembled by the operator.
	 */
  virtual void DoFaceAssembly() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopExtractFace(); // -> delete can't be called
};

// Supression le 11/02/05 Coverage ALV (remplacé par des #define)
// short                    show_trace; // while debugging, set this value to 1 and ...
// you will see .. heaven
/**
 * Creates an operator that extracts a face from a body.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iTopData
 * The pointer to the data defining the configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled.
 * @param iFace
 * The face to be extracted.
 * @param iMode
 * Sets the state of the resulting body.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopExtractFace *CATPGMCreateTopExtractFace(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATFace *iFace,
  CATBodyFreezeMode iMode = CATBodyFreezeOff);

/**
 * Creates an operator that extracts one or more faces from a body.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iTopData
 * The pointer to the data defining the configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled.
 * @param iFaces
 * The list of faces to be extracted.
 * @param iMode
 * Sets the state of the resulting body.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopExtractFace *CATPGMCreateTopExtractFace(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATLISTP(CATCell) *iFaces,
  CATBodyFreezeMode iMode = CATBodyFreezeOff);

#endif /* CATIPGMTopExtractFace_h_ */
