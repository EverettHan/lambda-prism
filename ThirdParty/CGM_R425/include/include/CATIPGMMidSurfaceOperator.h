#ifndef CATIPGMMidSurfaceOperator_h_
#define CATIPGMMidSurfaceOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2013

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMPersistentOperator.h"

class CATFace;
class CATGeoFactory;
class CATMidSurfaceOperatorImpl;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMMidSurfaceOperator;

/**
* Abstract base class for the MidSurface operator
* <br> A topological operation is realized with the appropriate operator. 
* These operators follow the global frame of the topological operators and satisfy the smart mechanism: 
* the input bodies are not modified. A new resulting body is created, 
* possibly sharing data with the input bodies.
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMMidSurfaceOperator: public CATIPGMPersistentOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMMidSurfaceOperator();

  //------------------
  // SET/GET Methods
  //------------------
  /** 
   * @nodoc
   * SetRatio .
   * @param iRatio
   * The ratio .
   * @return
   * 
   */
  virtual void SetRatio(double iRatio) = 0;

  /** 
   * @nodoc
   * AddPairOfFaces .
   * @param ipFaceP
   * The Face P .
   * @param ipFaceQ
   * The Face Q .
   * @return
   * 
   */
  virtual void AddPairOfFaces(CATFace *iPFace, CATFace *iQFace) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMMidSurfaceOperator(); // -> delete can't be called
};

// --------------------------------
// CATIPGMMidSurfaceOperator
// --------------------------------
/**
 * Global function for the creation of a CATIPGMMidSurfaceOperator operator.
 * @param iFactory
 * The pointer to the factory of the resulting body.
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. The journal inside <tt>iTopData</tt> 
 * @param iInputBody
 * The pointer to the input body.
 */
ExportedByCATGMOperatorsInterfaces 
CATIPGMMidSurfaceOperator *CATPGMCreateMidSurfaceOperator(CATGeoFactory *iFactory,
                                                          CATTopData *iTopData,
                                                          CATBody *iInputBody);

#endif /* CATIPGMMidSurfaceOperator_h_ */
