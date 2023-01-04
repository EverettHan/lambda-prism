#ifndef CATIPGMMaxOffset_h_
#define CATIPGMMaxOffset_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMOperator.h"
#include "CATMaxOffsetType.h"
#include "CATSkillValue.h"

class CATGeoFactory;
class CATMathFunctionX;
class CATMathSetOfPointsND;
class CATSoftwareConfiguration;
class CATSurParam;
class CATSurface;
class CATSurLimits;
class CATPCurve;
class CATCrvLimits;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMMaxOffset;

class ExportedByCATGMModelInterfaces CATIPGMMaxOffset: public CATIPGMOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMMaxOffset();

  // Set the limits of the surface
  virtual void HoldDomain(CATSurLimits *iSurLimits) = 0;

  // Check whether an offset is allowable.
  // NOTE: the values for singularity are a closed set.  Thus the
  //   threshold values cannot be used for offsets; the size of an
  //   offset must fall between the negative and positive thresholds.
  virtual CATBoolean CheckOffset(double &i_Offset) const = 0;

  // Methods for finding nonsingular regions with isoparametric
  // boundaries.  This search is conducted only over the HoldDomain,
  // not necessarily over the SurfaceLimits or the MaxSurfaceLimits.
  virtual CATLONG32 IsoparametricPatches(const double iOffset) = 0;

  // suppressed Run method- use SetRunOption if necessary (CATMXOFF_BOTH
  // is the default run option) then the Run() method (declared in the 
  // CATCGMOperator mother class)
  // Running the operator
  // void Run(const CATMaxOffsetRunOption iRunOption);
  // use this to set the RunOption (i.e. look for positive/negative/both
  // maxoffsets)- the default RunOption is CATMXOFF_BOTH so you need this
  // method only if you want to switch to CATMXOFF_NEG or CATMXOFF_POS
  virtual void SetRunOption(const CATMaxOffsetRunOption iRunOption) = 0;

  //Local MaxOffset calculation
  virtual CATThresholdType LocalMaxOffset(
    const CATSurParam &iParam,
    double iInputOffset,
    double &oMaxOffset) = 0;

  // GET methods.
  // ..for input parameters..
  virtual CATGeoFactory *GetFactoryPtr() const = 0;

  virtual CATSurface *GetSurfacePtr() const = 0;

  virtual CATSurLimits GetUVLimits() const = 0;

  /////////////////////////////////////////////////
  // ..for flags and thresholds :
  //
  //  The following get methods indicate the CATThresholdType found by the operator.
  //  According to the offset direction required (positive or negative), it could take the following values:
  //
  //  Specific cases:
  //    CATMXOFF_NOTSET   : no computation has been performed (Run has not been called, or the associated RunOption has not been asked).
  //    CATMXOFF_SINGULAR : the input surface has already reached its offsetability threshold (ie. offset radius = 0.).
  //    CATMXOFF_INFINITE : the input surface has no offset threshold (ex. like a plane, or a sphere for its centrifugal direction).
  //
  //  Regular case:
  //    CATMXOFF_FINITE   : the input surface is offsetable until a given limit gaved by the GetPositiveThreshold / GetNegativeThreshold according to case.
  virtual CATThresholdType GetPositiveFlag() const = 0;

  virtual CATThresholdType GetNegativeFlag() const = 0;

  //  The following get methods provide the offset threshold computed by the operator, according to the offset direction required.
  virtual double GetPositiveThreshold() const = 0;

  virtual double GetNegativeThreshold() const = 0;

  /////////////////////////////////////////////////
  // get the coords of a point whose local MaxOffset equals
  // the found global MaxOffset
  // *** unstable: debug only ***
  virtual void GetPositiveUV(double &u, double &v) const = 0;

  virtual void GetNegativeUV(double &u, double &v) const = 0;

  // ..for isoparametric regions..
  virtual CATLONG32 GetNumberIsoparamRegions() const = 0;

  virtual void Beginning() = 0;

  virtual CATBoolean GetNextRegion(CATSurLimits **oRegion) = 0;

  // do not use
  virtual void DisableSubdivide() = 0;

  // do not use
  //
  // cqi 27sep04
  virtual void DisableDirectMinimizerMode() = 0;

  // these twist analysis methods are deprecated- use
  // the CATIPGMTwistAnalysis operator instead
  // Twist analysis methods
  // A point is considered twisted if |du^dv| < resolution
  // Look for internal twists on the surface
  virtual void RunTwistAnalysis() = 0;

  // RunWithGuidePCurve (* internal use only *)
  // Specific and independant Run method used to compute the offsetability of the surface along a given contour defined
  // by a PCurve lying on this surface.
  // Inputs:
  //  - iPCrv: the guide PCurve that lies on the input surface gived to the operator
  //  - iPCrvLimits: the usefull limits on the PCurve.
  //  - iRunOption: the specific max offset option.
  // Outputs:
  //  - oPosFlag, oNegFlag: the output flag that give a status on offsetability.
  //  - oPosThres, oNegThres: output limit values of offsetability (filled in accordance with iRunOption).
  //  - oConstant is an optional array of size 2. If given, it allows to know if the maximum offset radius is constant or not.
  //    oConstant[0] = 1 if constant positive maximum offset radius, 0 otherwise.
  //    oConstant[1] = 1 if constant negative maximum offset radius, 0 otherwise.
  //
  // The methods returns 1 if succeeded, 0 otherwise (results are not relevant).
  virtual CATLONG32 RunWithGuidePCurve(
    CATPCurve *iPCrv,
    CATCrvLimits &iPCrvLimits,
    CATMaxOffsetRunOption iRunOption,
    CATThresholdType &oPosFlag,
    CATThresholdType &oNegFlag,
    double &oPosThresh,
    double &oNegThresh,
    short *oConstant = NULL) = 0;

  // Get result, call only after RunTwistAnalysis()
  virtual CATBoolean IsTwisted() = 0;

  // Get the UV parameters of the first twisted point
  virtual CATBoolean GetTwistUV(double &oTwistU, double &oTwistV) = 0;

  // Also count as a twist a point with either principal curvature
  // more than given threshold in absolute value
  virtual void SetCurvatureThreshold(double iCurvatureThreshold = 1.e3) = 0;

  //Contrary to the RunOperator whose solution is the littlest value to perform an offset of the surface.
  //In this method, the highest value is computed.
  //This method was implemented for the surface recognition and can need more implementation for other uses.
  virtual HRESULT MaximizeMaxOffset(
    CATSurLimits &iSurLimits,
    double &oValue,
    CATSurParam &oSurParam,
    double iprecision) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMMaxOffset(); // -> delete can't be called
};

// use this CTOR
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMMaxOffset *CATPGMCreateMaxOffset(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATSurface *iSurface,
  const CATSurLimits &iLimits);

// deprecated CTOR
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMMaxOffset *CATPGMCreateMaxOffset(
  CATGeoFactory *iFactory,
  CATSurface *iSurface,
  CATSkillValue iMode = BASIC);

#endif /* CATIPGMMaxOffset_h_ */
