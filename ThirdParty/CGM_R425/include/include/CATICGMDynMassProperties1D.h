#ifndef CATICGMDynMassProperties1D_h_
#define CATICGMDynMassProperties1D_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMModelInterfaces.h"
#include "CATIACGMLevel.h"
#ifdef CATIACGMV5R21
#include "CATICGMOperator.h"
#else
#include "CATICGMVirtual.h"
#endif
#include "CATMathDef.h"

class CATSoftwareConfiguration;
class CATCurve;
class CATCrvParam;

extern ExportedByCATGMModelInterfaces IID IID_CATICGMDynMassProperties1D;

/**
 * Class defining the geometric operator to perform a global analysis on a CATCurve.
 * <br>This class is transient and cannot be streamed. It performs conversion from curve parameter
 * to length and the converse.
 * The class is created with the <tt>CATCGMDynCreateMassProperties1D</tt> global method and is
 * is released with the <tt>Release</tt> method.
 */
#ifdef CATIACGMV5R21
class ExportedByCATGMModelInterfaces CATICGMDynMassProperties1D: public CATICGMOperator
#else
class ExportedByCATGMModelInterfaces CATICGMDynMassProperties1D: public CATICGMVirtual
#endif
{
public:
  /**
   * Constructor
   */
  CATICGMDynMassProperties1D();

  /**
   * Returns the CATCrvParam corresponding to the point at a given length
   * of another point.
   * @param iParam
   * The point on the curve.
   * @param iLength
   * The length on the curve measured from the point <tt>iParam</tt>.
   * @return
   * The corresponding point.
   */
  virtual CATCrvParam GetParamFromLength(
    const CATCrvParam &iParam,
    const CATLength &iLength) const = 0;

  /**
   * Returns the length between two points of a CATCurve.
   * @param iParam1
   * The first point.
   * @param iParam2
   * The second point.
   * @return
   * The length between the two points.
   */
  virtual CATLength GetLengthFromParams(
    const CATCrvParam &iParam1,
    const CATCrvParam &iParam2) const = 0;

  /**
   * Returns the total length of a CATCurve.
   * @return
   * The total length of the curve
   */
  virtual CATPositiveLength GetLength() const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMDynMassProperties1D(); // -> delete can't be called
};

/**
 * Creates a global analyzer on a CATCurve.
 * @param iCurveToAnalyze
 * The pointer to the curve to analyze.
 * @param iSoftwareConfig
 * The pointer to the CATSoftwareConfiguration.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMModelInterfaces CATICGMDynMassProperties1D *CATCGMDynCreateMassProperties1D(
  CATCurve *iCurveToAnalyze,
  CATSoftwareConfiguration *iSoftwareConfig);

#endif /* CATICGMDynMassProperties1D_h_ */
