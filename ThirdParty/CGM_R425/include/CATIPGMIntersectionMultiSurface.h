#ifndef CATIPGMIntersectionMultiSurface_h_
#define CATIPGMIntersectionMultiSurface_h_

// COPYRIGHT DASSAULT SYSTEMES 2010

#include "CATGMModelInterfaces.h"
#include "CATIPGMGeoOperator.h"
#include "CATCollec.h"
#include "CATListOfCATEdgeCurves.h"
#include "CATListOfCATCurves.h"
#include "CATCurve.h"

class CATEdgeCurve;
class CATListOfCATCurves;
class CATMathPoint;
class CATMultiSurface;
class CATLISTP(CATCurve);
class CATLISTP(CATEdgeCurve);
class CATLISTP(CATMathPoint);


extern ExportedByCATGMModelInterfaces IID IID_CATIPGMIntersectionMultiSurface;

/**
* @nodoc
* Classe permettant l'intersection de deux reseaux de surfaces.
*
*
*/
class ExportedByCATGMModelInterfaces CATIPGMIntersectionMultiSurface: public CATIPGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMIntersectionMultiSurface();

  /**
  * @nodoc
  * Set the list of init/exit 3D points that defines limitations of the intersection  
  */
  virtual void SetStartingPoints(const CATLISTP(CATMathPoint) *iPointList) = 0;

  /**
  * @nodoc
  * Set the list of CrvParam that defines the intersection  
  */
  virtual void SetParamOnCurve(CATListOfDouble &iCrvList) = 0;

  /**
  * @nodoc
  * Active the Bound Mod for the intersection the intersection  
  * IndexOperand should have the value 0 or 1 to set the multisurfacesurface 
  */
  virtual void SetBoundModON (CATBoolean iboundMod,CATLONG32 iIndexOperand)= 0;

  /**
  * @nodoc
  * Set the singularity status of the extremities, Init or Exit
  * TRUE for singular, FALSE if not
  */
  virtual void SetSingularityFlag(CATBoolean iInitFlag, CATBoolean iExitFlag) = 0;

  /**
  * @nodoc
   * to provide the tolerance on the init (size of the init vertex)
   */
  virtual void SetTolOnInit(const double &iTolOnInit) = 0;

  /**
   * @nodoc
   * to provide the tolerance on the exit (size of the exit vertex)
   */
  virtual void SetTolOnExit(const double &iTolOnExit) = 0;

  /**
   * @nodoc
   * Extend IntCurve with 3D curves if surface are too short.
   * by default the opertor is build with iNoExtend=FALSE
   */
  virtual void SetDoNot3DExtend(CATBoolean iNoExtend = TRUE) = 0;

  /**
   * @nodoc
   * Allow a small extrapolation of the surfaces if needed
   *  - by default extrapolation of only NURBS is allowed
   *  - the first argument turns on/off extrapolation (of NURBS)
   // - the second arguement turns on/off extrapolation of Offset surfaces
   */
  virtual void SetExtrapolationMode(
    const CATBoolean iAllowExtrapolation = TRUE,
    const CATBoolean iAllowOffsetSurfaces = FALSE) = 0;

  /**
   * @nodoc
  * Creates the  solution curve of <tt>this</tt> CATIPGMIntersectionMultiSurface operator.
  */
  virtual void GetResults(CATLISTP(CATEdgeCurve) *oEdgeCrvList) = 0;

  virtual void GetResults(CATLISTP(CATCurve) *oCrvList) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMIntersectionMultiSurface(); // -> delete can't be called
};

/**
 * @nodoc
 * Create MultiSurface Intersection Operator
 */
ExportedByCATGMModelInterfaces CATIPGMIntersectionMultiSurface *CATPGMCreateIntersectionMultiSurface(
  CATGeoFactory *iWhere,
  CATSoftwareConfiguration *iConfig,
  CATMultiSurface *iSurface1,
  CATMultiSurface *iSurface2,
  const CATBoolean iInterpolMode = FALSE);

/**
 * @nodoc
 * Oder Init and Exit point in _InitPointList 
 */
// StartPoint is between point of index _IndexLim[0][0] and _IndexLim[0][1]
// EndPoint   is between point of index _IndexLim[1][0] and _IndexLim[1][1]
// Startpoint is point n => _IndexLim[0][0] = -1  _IndexLim[0][1] = n
// Endpoint   is point n => _IndexLim[0][0] =  n  _IndexLim[0][1] = -1-
ExportedByCATGMModelInterfaces int CATPGMIntersectionMultiSurface_OrderInitExit(
  CATGeoFactory *_Factory,
  CATLISTP(CATMathPoint) *_InitPointList,
  CATBoolean &_Closed_Points,
  CATBoolean &_Closed_InitExits,
  int _IndexLim[2][2]);

#endif /* CATIPGMIntersectionMultiSurface_h_ */
