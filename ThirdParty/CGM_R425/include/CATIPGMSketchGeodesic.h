#ifndef CATIPGMSketchGeodesic_h_
#define CATIPGMSketchGeodesic_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMSketchOperators.h"
#include "CATMathDef.h"

class CATCGMJournalList;
class CATFace;
class CATGeometry;
class CATMathVector;
class CATSurParam;
class CATWire;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMSketchGeodesic;

/**
  * Class defining the topological operator that creates a geodesic
  * curve from a point and a direction.
  *<ul>
  * <li>A CATIPGMSketchGeodesic operator is created with the <tt>CATPGMCreateGeodesicPointDir</tt> global method;
  * it must be directly released with the <tt>Release</tt> method after use. It is is not streamable. 
  * You ask for the computation by using the <tt>Run</tt> method. 
  * <li>The resulting body is retrieved with the <tt>GetResult</tt> method.
  *</ul>
  */
class ExportedByCATGMOperatorsInterfaces CATIPGMSketchGeodesic: public CATIPGMSketchOperators
{
public:
  /**
   * Constructor
   */
  CATIPGMSketchGeodesic();

  /**
  * Runs the operator.
  */
  virtual int Run() = 0;

  /**
  * Replaces the support specified in the <tt>CATPGMCreateGeodesicPointDir</tt> global function.
  * @param iSupport
  * The new support.
  */
  virtual void ChangeSupport(CATGeometry *iSupport) = 0;

  /**
  * Replaces the point specified in the <tt>CATPGMCreateGeodesicPointDir</tt> global function.
  * @param iPoint
  * The new point.
  */
  virtual void ChangePoint(CATGeometry *iPoint) = 0;

  /**
  * Replaces the point and support specified in the <tt>CATPGMCreateGeodesicPointDir</tt> global function.
  * @param iSupportPoint
  * The new support.
  * @param iParam
  * The new point.
  */
  virtual void ChangePoint(CATGeometry *iSupportPoint, CATSurParam *iParam) = 0;

  /**
  * Replaces the tangent specified in the <tt>CATPGMCreateGeodesicPointDir</tt> global function.
  * @param iTangent
  * The new tangent value.
  */
  virtual void ChangeTangent(CATMathVector *iTangent) = 0;

  /**
  * Replaces the length specified in the <tt>CATPGMCreateGeodesicPointDir</tt> global function.
  * @param iLength
  * The new length value.
  */
  virtual void ChangeLength(CATPositiveLength iLength) = 0;

  /**
  * @nodoc
  */
  virtual void RemoveWire() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMSketchGeodesic(); // -> delete can't be called
};

#endif /* CATIPGMSketchGeodesic_h_ */
