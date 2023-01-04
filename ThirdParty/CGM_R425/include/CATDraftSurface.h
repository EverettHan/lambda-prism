#ifndef CATDraftSurface_h
#define CATDraftSurface_h

// COPYRIGHT DASSAULT SYSTEMES 1997

class CATPCurve;
class CATGeoFactory;
class CATDraftSurfaceCreationData;
#include "CATBaseUnknown.h"
#include "CATSurface.h"
#include "ExportedByCATGMGeometricInterfaces.h"

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATDraftSurface;
#else
extern "C" const IID IID_CATDraftSurface;
#endif

/**
 * Interface representing a draft surface.
 *<br> The CATDraftSurface is created by the <tt>CreateDraftSurface</tt>
 * method of the <tt>CATGeoFactory</tt> interface. 
 *<br>A CATDraftSurface is the surface generated by a cone sliding on a profile.
 * It keeps its canonicity, and can be a plane,
 * a cone, or a CATRuledSurface for the most general case. This canonical
 * surface is retrieved thanks to the <tt>GetGeometricRep</tt> 
 * inherited method. A CATDraftSurface is defined with:
 *<table>
 * <tr><td>CATCurve</td><td><tt> Profile </tt></td>
 *                <td> The profile on which the cone slides (first direction) </td></tr>
 * <tr><td>CATMathDirection</td><td><tt> Direction </tt></td>
 *                <td> The cone direction </td></tr>
 * <tr><td>CATAngle</td><td><tt> Angle </tt></td>
 *                <td> The angle between the direction and the draft surface
 *                      normal.</td></tr>
 * <tr><td>double</td><td><tt> StartLength </tt></td>
 *                 <td>The low limitation in the second direction</td></tr>
 * <tr><td>double</td><td><tt> EndLength </tt></td>
 *                 <td>The high limitation in the second direction</td></tr>
 *</table>
 *Note that <tt>StartLength < EndLength </tt> and may be negative.
 */
class ExportedByCATGMGeometricInterfaces CATDraftSurface : public CATSurface
{
  CATDeclareInterface;

 public:

/**
 * Creates the CATPCurve corresponding to the generating profile.
 * @param iGeoFactory
 * The pointer to the geometry factory that creates the curve.
 * @return
 * The pointer to the created curve.
 */
  virtual CATPCurve * CreateNeutralPCurve(CATGeoFactory * iGeoFactory) const=0;

  // For Extrapolation.
  virtual void Extrapolation(CATDraftSurfaceCreationData *iData) =0;

	// Get the data used to generate the CATDraftSurface.
	virtual CATDraftSurfaceCreationData * GetCreationData() const =0;

  // Get the bounding rule lines of the draft surface.
/**
 * Creates the CATPCurve corresponding to the rule line passing through the
 * low limitation of the generating curve.
 *<br>Note that it can be different to a surface border in case of a planar
 * generated surface.
 * @param iGeoFactory
 * The pointer to the geometry factory that creates the curve.
 * @return
 * The pointer to the created curve.
 */
  virtual CATPCurve * CreateStartRuleLine(CATGeoFactory * iGeoFactory) const=0;

/**
 * Creates the CATPCurve corresponding to the rule line passing through the
 * high limitation of the generating curve.
 *<br>Note that it can be different to a surface border in case of a planar
 * generated surface.
 * @param iGeoFactory
 * The pointer to the geometry factory that creates the curve.
 * @return
 * The pointer to the created curve.
 */
  virtual CATPCurve * CreateEndRuleLine(CATGeoFactory * iGeoFactory) const=0;

/**
 * Creates the CATPCurve corresponding to the rule line passing through a point of
 * the draft surface.
 *<br>Note that it can be not parallel to the surface border in case of a 
 * planar generated surface.
 * @param iGeoFactory
 * The pointer to the geometry factory that creates the curve.
 * @param iSurParam
 * The point of the draft surface.
 * @return
 * The pointer to the created curve.
 */
  virtual CATPCurve * CreateInnerRuleLine(CATGeoFactory * iGeoFactory, const CATSurParam &iSurParam) const=0;


  // Get and set the draft lengths.
/**
 * Modifies the limitation lengths on the rule direction of a CATDraftSurface.
 */
  virtual void SetLengthsOnRule(const double iStartLength, const double iEndLength) =0;

/**
 * Retrieves the limitation lengths on the rule direction of a CATDraftSurface.
 */
  virtual void GetLengthsOnRule(double & oStartLength, double & oEndLength) const=0;

/**
 * Modifies the limitations on the profile of a CATDraftSurface.
 */
  virtual void SetLimitsOnProfile(const double iStartLimit, const double iEndLimit) =0;

  /**
 * Retrieves the limitations on the profile of a CATDraftSurface.
 */
  virtual void GetLimitsOnProfile(double & oStartLimit, double & oEndLimit) const=0;

  virtual void GetParameterOrientations(short & RelativeUOrient, short & RelativeVOrient) const=0;
};
  CATDeclareHandler(CATDraftSurface, CATSurface);

#endif
