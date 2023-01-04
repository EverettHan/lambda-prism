#ifndef CATIPGMTopPlaneOperator_h_
#define CATIPGMTopPlaneOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopSurfaceOperator.h"
#include "CATMathDef.h"

class CATMathVector;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopPlaneOperator;

//COPYRIGHT DASSAULT SYSTEMES 2004
//===================================================================
//
// Author : ALV
// Date   : 20/07/2004
// Class CATIPGMTopPlaneOperator :
// Operator offers the topological build of a plane :
//  - Through one line angle with a plane
//  - offset of a plane at a given distance,
//  - offset of a plane through a point,
//  - by rotation of a plane of an angle round an axis (axis and plane being parallel) 
//  - passing through three points,
//  - passing through two lines,
//  - passing through a point and a line,
//  - passing through a planar curve,
//  - normal to a curve at a point,
//  - tangent to a surface at a point,
//  - defined by A,B,C,D such as Ax + By + Cz = D,
//  - as mean plane of points.
//
//===================================================================
/** 
  * ================== 
  * ================== 
  * ================== 
  * ================== 
  * ==================
  *
  * DO NOT USE THIS OPERATOR
  * OPERATOR IS UNDER CONSTRUCTION
  *
  * ================== 
  * ================== 
  * ================== 
  * ================== 
  * ================== 
  */
class ExportedByCATGMOperatorsInterfaces CATIPGMTopPlaneOperator: public CATIPGMTopSurfaceOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopPlaneOperator();

  virtual void SetNormale(const CATMathVector &NormalePlane) = 0;

  virtual void GetNormale(CATMathVector &NormalePlane) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopPlaneOperator(); // -> delete can't be called
};

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopPlaneOperator *CATPGMCreateTopPlaneByLineAngularOperator(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iPlane,
  CATBody *iLine,
  CATAngle iAngle);

#endif /* CATIPGMTopPlaneOperator_h_ */
