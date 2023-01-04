#ifndef CATIPGMEdgeToCanonic_h_
#define CATIPGMEdgeToCanonic_h_

// COPYRIGHT DASSAULT SYSTEMES 2021

#include "CATGMModelInterfaces.h"
#include "CATIPGMOperator.h"
#include "CATGeometryType.h"
#include "CATSkillValue.h"
#include "CATMathConstant.h"
#include "CATBoolean.h"
#include "CATSysBoolean.h"

class CATCurve;
class CATCrvLimits;
class CATEdge;
class CATGeoFactory;
class CATMathCircle;
class CATMathLine;
class CATMathPlane;
class CATMathPoint;
class CATSoftwareConfiguration;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMEdgeToCanonic;

class ExportedByCATGMModelInterfaces CATIPGMEdgeToCanonic: public CATIPGMOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMEdgeToCanonic();

  //-----------------------------------------------------------------------
  //- Public Settings
  //-----------------------------------------------------------------------
  // Setting methods
  // Specify type of canonical geometry requested
  // possible types are : CATLineType, CATCircleType, CATConicType, CATEllipseType ...
  virtual void SetRequestedType(const CATGeometricType iRequestedType) = 0;

  virtual void SetTolerance(double iTolerance) = 0;

  // Multi-Run mode : can Reset the input edge before Run()
  virtual void SetEdge(CATEdge *iEdge) = 0;

  //-----------------------------------------------------------------------
  //- Public Get Methods
  //-----------------------------------------------------------------------
  // Returns canonical equivalent curve
  // returns 0 if no canonical equivalent curve has been found
  // The caller becomes responsible of the Life Cycle Managment of the returned CATCurve :
  // please call CATGeoFactory->Remove() in order to release the CATCurve after use.
  virtual CATCurve *GetResult() = 0;

  // Returns canonical equivalent curve with the Curve limits matching with the input CATEdge
  // returns 0 if no canonical equivalent curve has been found
  // The caller becomes responsible of the Life Cycle Management of the returned CATCurve :
  // please call CATGeoFactory->Remove() in order to release the CATCurve after use.
  virtual CATCurve *GetResult(CATCrvLimits &oLimits) = 0;

  // Retrieve specific canonicity after Run
  // It's not necessary to get the CATCurve before calling these methods
  // returns FALSE if these methods are called before Run, or if the operator has been created with invalid data

  virtual CATBoolean IsLinear() = 0;

  virtual CATBoolean IsLinear(CATMathLine &oLine) = 0;

  virtual CATBoolean IsLinear(CATMathPoint &oStartLinePoint, CATMathPoint &oEndLinePoint) = 0;

  virtual CATBoolean IsCircular() = 0;

  virtual CATBoolean IsCircular(CATMathCircle &oCircle) = 0;

  virtual CATBoolean IsCircular(
    CATMathPlane &oCircleSupport,
    double &oRadius,
    CATAngle &oStartAngle,
    CATAngle &oEndAngle) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMEdgeToCanonic(); // -> delete can't be called
};

/**
 * Creates the CATIPGMEdgeToCanonic operator from an edge
 * @param iFactory
 * The factory where new geometric objects will be created.
 * @param iSoftwareConfiguration
 * The pointer to the software configuration
 * @param iEdgeToCanonic
 * The edge to retrieve the canonicity knowledge
 * @param iMode
 * The mode of use.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>BASIC</tt> <dd>The operation is performed at the operator creation without any option.
 *     <dt><tt>ADVANCED</tt>  :
 * mode, options can be precised with the <tt>SetXxx</tt> methods,
 * <dd>Use the <tt>Run</tt> method to computes the operation.</dl>
 * @return [out, IUnknown#Release]
 *The pointer to the created operator.
 */
ExportedByCATGMModelInterfaces CATIPGMEdgeToCanonic *CATPGMCreateEdgeToCanonic(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATEdge *iEdgeToCanonic,
  CATSkillValue iMode = ADVANCED);

#endif /* CATIPGMEdgeToCanonic_h_ */
