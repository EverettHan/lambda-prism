#ifndef CATIPGMMidSurfaceAdvancedOperator_h_
#define CATIPGMMidSurfaceAdvancedOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2013

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMPersistentOperator.h"
#include "ListPOfCATFace.h"

class CATFace;
class CATGeoFactory;
class CATMidSurfaceOperatorImpl;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMMidSurfaceAdvancedOperator;

/**
* Abstract base class for the MidSurfaceAdvanced operator
* <br> A topological operation is realized with the appropriate operator. 
* These operators follow the global frame of the topological operators and satisfy the smart mechanism: 
* the input bodies are not modified. A new resulting body is created, 
* possibly sharing data with the input bodies.
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMMidSurfaceAdvancedOperator: public CATIPGMPersistentOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMMidSurfaceAdvancedOperator();

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
  virtual void AddPairOfFaces(CATFace *ipFaceP, CATFace *ipFaceQ) = 0;

  /** 
   * @nodoc
   * InitPairOfFaces .
   * @param ipFaceP
   * The Face P .
   * @param ipFaceQ
   * The Face Q .
   * @param iRatio
   * The ratio .
   * @return
   * 
   */
  virtual void InitPairOfFaces(CATFace *ipFaceP, CATFace *ipFaceQ, double iRatio) = 0;

  /** 
   * @nodoc
   * SetMainMidSurfaceForRib .
   * @param ipBodyMidSurfaceMain
   * The body of the main mid-surface .
   * @return
   * 
   */
  virtual void SetMainMidSurfaceForRib(CATBody *ipBodyMidSurfaceMain = NULL) = 0;

  /** 
   * @nodoc
   * InitListOfFaces .
   * @param iListOfFaces
   * The list of faces to mid-surface by offset .
   * @param iDistance
   * The distance to offset .
   * @param iRatio
   * The ratio .
   * @return
   * 
   */
  virtual void InitListOfFaces(
    CATLISTP(CATFace) &iListOfFaces,
    double iDistance,
    double iRatio) = 0;

  /** 
   * @nodoc
   * InitListOfFaces .
   * @param iListOfFaces
   * The list of faces to mid-surface by offset in associative distance mode.
   * @param iRatio
   * The ratio .
   * @param iAssociativeDistanceMode
   * Mode set to 1 for MIN, set to 2 for MAX, and set to 3 for AVERAGE distance .
   * @param iMaxThickness
   * The Max thickness to filter faces with distance > iMaxThickness .
   * @return
   * 
   */
  virtual void InitListOfFaces(
    CATLISTP(CATFace) &iListOfFaces,
    double iRatio,
    int iAssociativeDistanceMode,
    double iMaxThickness) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMMidSurfaceAdvancedOperator(); // -> delete can't be called
};

// --------------------------------
// CATIPGMMidSurfaceAdvancedOperator
// --------------------------------
/** 
 * Global function for the creation of a CATIPGMMidSurfaceAdvancedOperator operator.
 * @param iFactory
 * The pointer to the factory of the resulting body.
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. The journal inside <tt>iTopData</tt> 
 * @param iInputBody
 * The pointer to the input body.
 */
ExportedByCATGMOperatorsInterfaces 
CATIPGMMidSurfaceAdvancedOperator *CATPGMCreateMidSurfaceAdvancedOperator(CATGeoFactory *iFactory,
                                                                          CATTopData *iTopData,
                                                                          CATBody *iInputBody);

#endif /* CATIPGMMidSurfaceAdvancedOperator_h_ */
