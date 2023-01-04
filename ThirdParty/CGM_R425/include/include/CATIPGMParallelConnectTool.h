#ifndef CATIPGMParallelConnectTool_h_
#define CATIPGMParallelConnectTool_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMConnectTool.h"
#include "CATCollec.h"
#include "CATApproxDiagnosticType.h"

class CATCrvLimits;
class CATCurve;
class CATICGMDistanceTool;
class CATGeoFactory;
class CATGeometry;
class CATLaw;
class CATMathFunctionX;
class CATMathInterval;
class CATMathPiecewiseX;
class CATMathSetOfPointsND;
class CATParallelComputer;
class CATSoftwareConfiguration;
class CATSurLimits;
class CATSurface;
class CATICGMDistanceTool;
class CATLISTP(CATGeometry);

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMParallelConnectTool;

class ExportedByCATGMModelInterfaces CATIPGMParallelConnectTool: public CATIPGMConnectTool
{
public:
  /**
   * Constructor
   */
  CATIPGMParallelConnectTool();

  //=====================
  // Get/Set Methods
  //=====================
  virtual CATLONG32 GetType() const = 0;

  virtual CATLONG32 GetSide() const = 0;

  virtual void SetSide(CATLONG32 iSide) = 0;

  // Check Twist
  // iCheck = 0 : OFF
  // iCheck = 1 : ON
  // iCheck = 2 : new management of twist in euclidian and geodesic
  virtual void SetCheckTwist(CATLONG32 iCheck) = 0;

  virtual CATLONG32 GetCheckTwist() const = 0;

  // Methods used to obtain input laws (radius and mapping)
  virtual const CATLaw *GetRadius() const = 0;

  virtual const CATLaw *GetMapping() const = 0;

  // *** INTERNAL USE ONLY ***
  // Methods dedicated to the storage of non-approximate radius law.
  // Could be usefull to have more precise law evaluations when radius
  // law shape is critical (for instance vertical tangency)
  virtual void SetNonApproxLaw(CATLaw *iNonApproxLaw) = 0;

  virtual const CATLaw *GetNonApproxLaw() const = 0;

  // *** INTERNAL USE ONLY ***
  // Methods dedicated to the storage of specific diagnosis from the
  // approx law evaluation. The existence of vertical tangents is specified
  // in this attribute.
  virtual void SetApproxDiagnostic(CATApproxDiagnostic iApproxDiagnostic) = 0;

  virtual const CATApproxDiagnostic GetApproxDiagnostic() const = 0;

  // Method used to obtain the mathematical composition function Rfunc between radius and mapping:
  //
  //
  //        CurveDomain ---> RadiusDomain
  // Rfunc: w           ---> Rfunc(w) = RadiusLaw( Mapping ( w ) ) , where CurveDomain is mapping domain
  //                                                                 ie. physical limits of the mapping law
  //
  // *** INTERNAL USE ONLY ***
  // If iApproximateLaw = FALSE and SetNonApproxLaw has been previously called, the method
  // takes the non-approximate law as reference (ie. Rfunc(w) = NonApproxRadiusLaw( Mapping ( w ) ) )
  // Be careful, if non-approximate law has not been set, this throws
  //
  virtual const CATMathFunctionX *GetRadiusFunction(CATBoolean iApproximateLaw = TRUE) = 0;

  // CheckSmallArcs
  //
  // This method tries to retrieve the component functions of the global radius law that match with current mapping limits.
  // If this searching phase succeeded, a check on small arcs is then performed on each sub-component if they are of PolynomX type:
  //
  // |ti+1 - ti| <= iRelativTol * DomainWidth ===> small arc (iRelativTol is optionnal).
  //
  // The method returns:
  //    -1: deep error (null pointer, non polynomial function, etc.): check is irrelevant.
  //     0: check is OK (no small arcs).
  //     1: check is KO (radius law contains small arcs).
  //
  // *** INTERNAL USE ONLY ***
  //
  virtual int CheckSmallArcs(double iRelativTol = 1.e-6) = 0;

  /**
   * Returns the distance tool.
   * @return  [out, IUnknown#Release]
   *   The tool.
   */
  virtual CATICGMDistanceTool *GetDistanceTool() = 0;

  virtual CATParallelComputer *GetComputer(
    CATCurve *iCurve,
    CATCrvLimits &iCurveLimit,
    CATLONG32 iOrientationEdge,
    CATBoolean iExtrapolEdge,
    CATSurface *iSupport,
    CATSurLimits &iSupportLimit,
    CATLONG32 iOrientationSupport,
    CATBoolean iExtrapolSupport,
    CATMathSetOfPointsND *iInitPoints,
    CATBoolean iLoopSearch) = 0;

  /***********************************************************/
  /* Methods to save information for geodesic function which */
  /* needs topological informations                          */
  /***********************************************************/
  virtual void SetAttributes(CATLISTP(CATGeometry) &iAttributes) = 0;

  virtual void GetAttributes(CATLISTP(CATGeometry) &oAttributes) = 0;

  virtual void SetVariableAttribute(CATGeometry *iAttribute) = 0;

  virtual void GetVariableAttribute(CATGeometry *&oAttribute) = 0;

  virtual void SetOriginCurveSupport(CATSurface *iSupp, CATLONG32 iOrient) = 0;

  virtual void GetOriginCurveSupport(CATSurface *&oSupp, CATLONG32 &oOrient) = 0;

  virtual void SetEndSurface(CATSurface *iEndSurface) = 0;

  virtual void GetEndSurface(CATSurface **ioEndSurface) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMParallelConnectTool(); // -> delete can't be called
};

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMParallelConnectTool *CATPGMCreateParallelConnectTool(
  CATSoftwareConfiguration *iConfig,
  CATICGMDistanceTool *iDistanceTool,
  CATLaw *iMappingLaw,
  CATBoolean iIsPlanarBody = FALSE);

//Do not use - Use the constructor with CATSoftwareConfiguration
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMParallelConnectTool *CATPGMCreateParallelConnectTool(
  CATLONG32 iSide,
  CATLaw *iRadiusLaw,
  CATLaw *iMappingLaw,
  CATBoolean iIsEuclidian = TRUE);

// **** for intern use only ****
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMParallelConnectTool *CATPGMCreateParallelConnectTool(
  CATSoftwareConfiguration *iConfig,
  CATLONG32 iSide,
  CATLaw *iRadiusLaw,
  CATLaw *iMappingLaw,
  CATBoolean iIsEuclidian = TRUE);

//Do not use - Use the constructor with CATSoftwareConfiguration
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMParallelConnectTool *CATPGMCreateParallelConnectTool(
  CATICGMDistanceTool *iDistanceTool,
  CATLaw *iMappingLaw);

#endif /* CATIPGMParallelConnectTool_h_ */
