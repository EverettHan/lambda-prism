//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2002
//=============================================================================
//
// Utilities class for Connect operators
//
//=============================================================================
// 00/01/02          Creation                             F. Caillaud
// 00/11/04 : EAB :  Versionning Interne
// 13/08/13 : XMH : ConstrainLimitsToMaxLimits
// 13/02/14 : R1Y : Added ComputeSpineParamAtPointingPoint().
// 14/02/14 : R1Y : Added GetMaxNumTangents(() and ComputeConnectTangents().
// 11/03/14 : XMH : Developed the utilities into a class used by the 
//                  Connect Piece and Computer classes
// 03/04/14 : XMH : Add ComputeSplitsBetweenCurveAndSurfaceSupports
//=============================================================================

#ifndef CATConnectUtilities_h
#define CATConnectUtilities_h

#include <math.h>
#include "CATListOfDouble.h"
#include "CATDataType.h"
#include "CATTolerance.h"

class CATMathSetOfPointsNDTwoTangents;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATCrvLimits;
class CATSurLimits;
class CATCurve;
class CATSurface;
class CATConnectTool;

//---------------------------------------------------------
// CATConnectUtilities
//---------------------------------------------------------
//
// Usage : Fillet connect computer and piece base classes contain a pointer to an instance
//         of a CATConnectUtilities utilities class and so it is easy to call methods
//         or to add new methods. The aim is to put all utilities here so that they can
//         be easily found and reused, thus reducing code duplication.
//
class CATConnectUtilities
{
public:
  CATConnectUtilities( CATGeoFactory            * iFactory, 
                       CATSoftwareConfiguration * iConfig );
  ~CATConnectUtilities();

  //-------------------------------------------------------------------------------------------------
  //
  //  CleverIsLinear :
  //    Determines whether the a number of consecutive coordinates of a set of ND points is collinear
  //
  //    iSet       : set of points to consider
  //    iNumCoord  : number of consecutaive coordinates to consider
  //    iCoord     : index of the first coordinate
  //    iTolObject : tolerance object
	//    iProfile   : To customize the check for linearity for a particular connect
  //-------------------------------------------------------------------------------------------------
  CATLONG32 CleverIsLinear(const CATMathSetOfPointsNDTwoTangents * iSet,
                           const CATLONG32                         iNumCoord,
                           const CATLONG32                       * iCoord,
                           const CATTolerance                    & iTolObject,
													 const CATConnectTool                  * iProfile = NULL) const;	

  //-------------------------------------------------------------------------------------------------
  //
  //  PointIsInList :
  //    Determines whether a 3D point is in an array of points
  //
  //    iPt    : point to consider
  //    iArray : array of points of size 3 * iN
  //    iN     : number of points in the array
  //    iTol   : tolerance
  //-------------------------------------------------------------------------------------------------
  CATBoolean PointIsInList(const double            iPt,
                           const CATListOfDouble & iArray,
                           const CATLONG32         iN,
                           const double            iTol) const;

  //-------------------------------------------------------------------------------------------------
  //
  //  ConstrainToMaxLimitsOfGeometry :
  //
  //    Reduces a set of limits to be within the maximum limits of a curve
  //    Note: Required due to some Replay data obtained from a computed maxlimits and captured on one platform
  //          might differ very slightly from the maxlimits computed on another platform
  //    ioLimitsToContrain : limits to constrain
  //    iCurve             : curve
  //-------------------------------------------------------------------------------------------------
  void ConstrainToMaxLimitsOfGeometry(      CATCrvLimits & iLimitsToContrain,
                                      const CATCurve     * iCurve) const;

  //-------------------------------------------------------------------------------------------------
  //
  //  ConstrainToMaxLimitsOfGeometry :
  // Required due to some Replay data obtained from a computed maxlimits and captured on one platform
  // might differ very slightly from the maxlimits computed on another platform
  //
  //    Reduces a set of limits to be within the maximum limits of a surface
  //    ioLimitsToContrain : limits to constrain
  //    iSurface             : surface
  //-------------------------------------------------------------------------------------------------
  void ConstrainToMaxLimitsOfGeometry(      CATSurLimits & iLimitsToContrain,
                                      const CATSurface   * iSurface) const;

  //-------------------------------------------------------------------------------------------------
  // TODO-CONNECT_REARCH
  //  ComputeSpineParamAtPointingPoint :
  //
  //     iProfile                 : Connect fillet tool
  //     iSupport1                : first support
  //     iSupport2                : second support
  //     iVector                  : 4D tangent to traces
  //     iUseMinPtCrvDist         : flag whether to use the point-curve distance as a backup
  //     ioPoint                  : 4D pointing point
  //-------------------------------------------------------------------------------------------------
  void ComputeSpineParamAtPointingPointUTIL(const CATConnectTool * const iProfile,
                                              CATSurface                   *       iSupport1,
                                              CATSurface                   *       iSupport2,
                                        const double                       * const iVector,
                                        const CATBoolean                           iUseMinPtCrvDist,
                                              double                       *       ioPoint) const;

  //-------------------------------------------------------------------------------------------------
  //
  // Computes the intersections between curve and surface supports and wraps up the intersection data
  // as a list of parameter values on the curve. If the curve is confused with the surface (with maxlimits) then
  // we return the number of confused regions
  //    iCrvLimits   : curve limits
  //    iCurve       : curve
  //    iSurface     : surface
  //    oSplits      : curve parameters where the curve intersects the surface
  //    oHowConfused : returns 0 - no regions of confusion
  //                           1 - the entire curve is confused with the surface over the interval iCrvLimits
  //                           2 - the curve is confused with the surface in one or more sub-intervals of iCrvLimits
  //-------------------------------------------------------------------------------------------------
  void ComputeSplitsBetweenCurveAndSurfaceSupports(const CATCrvLimits & iCrvLimits,
                                                   CATCurve           * iCurve,
                                                   CATSurface         * iSurface,
                                                   CATListOfDouble    & oSplits, 
                                                   short              & oHowConfused ) const;


private:

  CATGeoFactory            * _Factory;
  CATSoftwareConfiguration * _Config;

  CATLONG32 GetMaxNumTangents() const;

  void ComputeConnectTangents(      CATSurface               *       iSupport1,
                                    CATSurface               *       iSupport2,
                              const double                   * const iPoint,
                              const double                           iTolerance,  // sine of the angle between the normal vectors of the two surfaces
                                    CATBoolean               &       oIsSingular,
                                    CATLONG32                &       oNumTangents,
                                    double                   * const oTangents) const;
};

#endif
