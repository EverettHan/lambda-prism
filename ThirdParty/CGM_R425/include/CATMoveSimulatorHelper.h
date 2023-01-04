// COPYRIGHT DASSAULT SYSTEMES 2020
//=============================================================================
//
// CATMoveSimulatorHelper 
//  Fully abstract class, the goal is that the content of each method is
//  calling an operator of TopologicalOperator framework.
//  And those methods will be implemented in a daughter class
//  of CATMoveSimulatorHelper that will be created in TopologicalOperators
//
//
//=============================================================================
//  June 2020  Creation                                                 DLR6
//=============================================================================

#ifndef MoveSimulatorHelper_H
#define MoveSimulatorHelper_H


class CATGeoFactory;
class CATTopData;

class CATBody;
class CATSurface;
class CATPCurve;
class CATCrvLimits;


#include "CATMathDirection.h"
#include "CATMathDef.h"

#include "CATTopRelimitByVolumeSelectionType.h"

#include "ExportedByCATTopologicalObjects.h"

class ExportedByCATTopologicalObjects CATMoveSimulatorHelper
{
protected:
  CATMoveSimulatorHelper(CATGeoFactory    * ipFactory,
                      CATTopData       * ipTopData);

public:
  virtual CATBody*  DoCallTo_DynBoolean_Intersection(
                        CATGeoFactory       * ipFactory       ,
                        CATTopData          * ipTopData       ,
                        CATBody             * ipBody_1        ,
                        CATBody             * ipBody_2        ) const = 0;

  virtual CATBody*  DoCallTo_DynBoolean_Union(
                        CATGeoFactory       * ipFactory       ,
                        CATTopData          * ipTopData       ,
                        CATBody             * ipBody_1        ,
                        CATBody             * ipBody_2        ) const = 0;

  virtual CATBody*  DoCallTo_RelimitByVolume(
                        CATGeoFactory       * ipFactory       ,
                        CATTopData          * ipTopData       ,
                        CATBody             * ipBody_1        ,
                        CATBody             * ipBody_2        ,
                        CATTopRelimitByVolumeSelectionType iSelectionType) const = 0;

  virtual double    Compute_MinDistanceBodyBody(
                        CATGeoFactory       * ipFactory       ,
                        CATTopData          * ipTopData       ,
                        CATBody             * ipBody_1        ,
                        CATBody             * ipBody_2        ,
                  const CATMathDirection     &iExtrudeDir     ) const = 0;

  virtual CATBody*  DoCallTo_ReflectLine(
                        CATGeoFactory       * ipFactory       ,
                        CATTopData          * ipTopData       ,
                        CATBody             * iInputSkin      ,
                  const CATMathVector        &iDirection      ,
                        CATAngle              iAngle          ) const = 0;

  virtual CATBody*  DoCallTo_Prism(
                        CATGeoFactory       * ipFactory       ,
                        CATTopData          * ipTopData       ,
                        CATBody             * ipBodyToExtrude ,
                  const CATMathDirection     &iExtrudeDir     ,
                        CATLength             iBegin          ,
                        CATLength             iEnd            ) const = 0;

  virtual CATBody*  DoCallTo_HybIntersect(
                        CATGeoFactory       * ipFactory       ,
                        CATTopData          * ipTopData       ,
                        CATBody             * ipBody_1        ,
                        CATBody             * ipBody_2        ) const = 0;

  virtual CATBody*  DoCallTo_CreateTopSkin(
                        CATGeoFactory       * ipFactory       ,
                        CATTopData          * ipTopData       ,
                        CATSurface          * ipSurface       ,
                        int                   iNbPcurves      ,
                        CATPCurve           **iPcurves        ,
                        CATCrvLimits        * iLimits         ,
                        short               * iOrientations   ) const = 0;

  virtual CATBody*  DoCallTo_HybSplit(
                        CATGeoFactory       * ipFactory       ,
                        CATTopData          * ipTopData       ,
                        CATBody             * iBodyToSplit    ,
                        short                 iSideToKeep     ,
                        CATBody             * iSplittingBody  ,
                        CATBody             * iCuttingBody    ) const = 0;

  virtual CATBody*  DoCallTo_HybBoundary(
                        CATGeoFactory       * ipFactory       ,
                        CATTopData          * ipTopData       ,
                        CATBody             * iBodyToGetBdry  ) const = 0;

  virtual double    ComputeMaxDistanceBodyAlongAxis(
                        CATGeoFactory       * ipFactory       ,
                        CATTopData          * ipTopData       ,
                        CATBody             * ipBody          ,
                        const CATMathVector  &iDirection      ,
                        CATBody             **opBodyOfMaxExtremum = NULL,
                        CATBody             **opBodyOfMinExtremum = NULL) const = 0;

  virtual double    ComputeMaxDifferenceBetweenBodiesAlongAxis(
                        CATGeoFactory       * ipFactory       ,
                        CATTopData          * ipTopData       ,
                        CATBody             * ipBody_A        ,
                        CATBody             * ipBody_B        ,
                        const CATMathVector  &iDirection      ,
                        CATBody             **opBodyOfMaximumFromA = NULL,
                        CATBody             **opBodyOfMaximumFromB = NULL) const = 0;
};


#endif //MoveSimulatorHelper_H
