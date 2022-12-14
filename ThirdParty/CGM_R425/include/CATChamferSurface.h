/* -*-c++-*-*/
#ifndef CATChamferSurface_h
#define CATChamferSurface_h


// COPYRIGHT DASSAULT SYSTEMES 1999

/**
 * Interface representing a Chamfer surface.
 *<br> The CATChamferSurface is created by the <tt>CreateChamferSurface</tt>
 * method of the <tt>CATGeoFactory</tt> interface.
 *<br>A CATChamfer is the surface generated by ruled surfaces passing through
 *<tt>Surface1Points</tt> and <tt>Surface2Points</tt> points.
 *It keeps its canonicity, and can be a cone, a plane, or a CATGenericRuledSurface
 *for the most general case. This canonical
 * surface is retrieved thanks to the <tt>GetGeometricRep</tt> inherited method.
 *<table>
 * <tr><td>CATMathSetOfPointsND</td><td><tt> Surface1Points </tt></td>
 *                <td> The corresponding points on the first surface </td></tr>
 * <tr><td>CATMathSetOfPointsND</td><td><tt> Surface2Points </tt></td>
 *                <td> The corresponding points on the second surface </td></tr>
 *</table>
 */
//
#include "CATBaseUnknown.h"
#include "CATSurface.h"
#include "CATConnectBordersCommand.h"  // to include Options Commands of CreateBorders
#include "ExportedByCATGMGeometricInterfaces.h"
class CATGeometry;
class CATCrvParam;

// Define here all levels of "configuration's argument" used in CreateChamfer
#define CATChamferSurface_Configuration_NoConfig_0    0
#define CATChamferSurface_Configuration_CenterPlane_1 1


#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATChamferSurface ;
#else
extern "C" const IID IID_CATChamferSurface ;
#endif

class ExportedByCATGMGeometricInterfaces CATChamferSurface : public CATSurface
{
  CATDeclareInterface;

  public:

  virtual CATLONG32 GetSurfaceOrientation() const=0;

  /**
   * Creates the boundaries of a CATChamferSurface.
   *<br>The boundaries may degenerate as points.
   * @param iCommand
   * The types of required boundaries.
   *<dl><dt> CreateStartBorder
   *       <dd>The boundary passing through the <tt>Surface1Points</tt>
   *    <dt> CreateEndBorder
   *       <dd>The boundary passing through the <tt>Surface2Points</tt>
   *    <dt> CreateSplineBorder1
   *       <dd>The line arc boundary passing through the first point of <tt>Surface1Points</tt>
   * and <tt>Surface2Points</tt>.
   *     <dt> CreateSplineBorder1
   *       <dd>The line arc boundary passing through the last point of <tt>Surface1Points</tt>
   * and <tt>Surface2Points</tt>.
   *     <dt> sum of the former types <dd>for multiple creation </dl>.
   * @param oSplineBorder1
   * The boundary passing through the <tt>Surface1Points</tt> according to
   * <tt>iCommand</tt>, NULL otherwise.
   * @param oSplineBorder2
   * The boundary passing through the <tt>Surface2Points</tt> according to
   * <tt>iCommand</tt>, NULL otherwise.
   * @param oStartBorder
   * The line arc boundary passing through the first point of <tt>Surface1Points</tt>
   * and <tt>Surface2Points</tt> according to <tt>iCommand</tt>, NULL otherwise.
   * @param oEndBorder
   * The line arc boundary passing through the last point of <tt>Surface1Points</tt>
   * and <tt>Surface2Points</tt> according to
   * <tt>iCommand</tt>, NULL otherwise.
   */
  virtual void CreateBorders(CATGeoFactory *iWhere,
                             CATConnectBordersCommand iCommand,
                             CATGeometry *& oSplineBorder1,
                             CATGeometry *& oSplineBorder2,
                             CATGeometry *& oStartBorder,
                             CATGeometry *& oEndBorder,
                             const CATCrvParam * iSplineStartPosition = 0,
                             const CATCrvParam * iSplineEndPosition = 0,
                             const CATCrvParam * iStartBorderPosition = 0,
                             const CATCrvParam * iEndBorderPosition = 0,
                             const CATLONG32 iParamID = 0) const =0;

  virtual void CreateBorders( CATGeoFactory      * iWhere,
                              const CATSurParam  * iStart,
                              const CATSurParam  * iEnd,
                              CATGeometry       *& oBorder ) const = 0;
  //-------------------------------------------------------------
  // GetSurface / GetContact: For iSupportID, use names defined in
  // CATConnectDefines.h
  //-------------------------------------------------------------
  virtual void GetSurface(const CATLONG32 iSupportID,
                          CATSurface * &oSurface,
                          int &oOrientation) const =0;

  virtual void GetSupport(const CATLONG32 iSupportID,
                          CATGeometry * &oSupport,
                          int &oOrientation) const =0;

  virtual void GetContact(const CATLONG32 iSupportID,
                          CATGeometry * &oContact) const =0;

  virtual void GetChamferTypeAndValues(CATLONG32 & oChamferType, double & oFirstValue,
                                       double & oSecondValue) const = 0;

  // Useful only for Approximate Chamfer
  virtual CATBoolean GetChamferTypeAndOriginalValues(CATLONG32 & oChamferType,
                                                     double & oOriginalFirstValue,
                                                     double & oOriginalSecondValue) const = 0;
  // Useful only for Approximate Chamfer
  virtual void SetOriginalValues(const double iOriginalFirstValue, const double iOriginalSecondValue) const = 0;

  /**
   * @nodoc
   * Call this method after an extrapolation to update all objects
   * dependent on the surface (PCurves)
   */
  virtual void IsTrimmed() = 0;

};
CATDeclareHandler(CATChamferSurface,CATSurface);

#endif
