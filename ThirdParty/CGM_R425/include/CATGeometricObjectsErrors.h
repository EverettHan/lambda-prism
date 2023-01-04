
#ifndef _CATGeometricObjectsErrors_h
#define _CATGeometricObjectsErrors_h

// COPYRIGHT DASSAULT SYSTEMES 1999

/** @CAA2Required */

/* Generated from CATGeometricObjectsErrors.msg on Fri Jul 10 09:31:33 1998
 */
typedef enum {

             GBInEInvalidPointer = 0x00020001u,
               GBInEInvalidInput = 0x00020002u,
             GBInEInvalidSupport = 0x00020003u,
GBInEInvalidInputValueSmallerThanI = 0x00020004u,
GBInEInvalidInputValueLargerThanI = 0x00020005u,
 GBInEInvalidInputValueBeetweenI = 0x00020006u,
GBInEInvalidInputValueSmallerThanR = 0x00020007u,
GBInEInvalidInputValueLargerThanR = 0x00020008u,
 GBInEInvalidInputValueBeetweenR = 0x00020009u,
GBInEInvalidInputValueSmallerThanC = 0x0002000au,
GBInEInvalidInputValueLargerThanC = 0x0002000bu,
           GBInEInvalidInputType = 0x0002000cu,
GBInEInvalidInputObjectNotInInfiniteBox = 0x0002000du,
GBInEInvalidInputObjectTypeNotSupported = 0x0002000eu,
  GBInEInvalidInputObjectIsEmpty = 0x0002000fu,
GBInEInvalidInputCoordinatesDifferentFromPreviousOnes = 0x00020010u,
GBInEInvalidInputPointIsNotOnSurface = 0x00020011u,
GBInEInvalidInputMacroElementWithSeveralComponents = 0x00020012u,
GBInEInvalidInputMergeIsNotPossible = 0x00020013u,
             GBInEInvalidSurface = 0x00020014u,
   GBInEObjectCannotBeReferredTo = 0x00020015u,
GBInEModificationWhileEquationOpened = 0x00020016u,
    GBInEInvalidInputOrientation = 0x00020017u,
GBInEInvalidInputObjectCannotBelongToSeveralObjects = 0x00020018u,
GBInEInvalidInputCurveDoesNotBelongToEdgeCurve = 0x00020019u,
GBInEInvalidInputCurveSeveralTimesInEdgeCurve = 0x0002001au,
GBInECloudOfPointsVectorIsNotDefined = 0x0002001bu,
    GBInESelfIntersectingSurface = 0x0002001cu,
          GBInEPointNotOnSurface = 0x0002001du,
                   GBInEBadOrder = 0x0002001eu,
     GBInEIntervalPeriodConflict = 0x0002001fu,
        GBInENonIncreasingValues = 0x00020020u,
GBInEInvalidInputPeriodicMultiplicities = 0x00020021u,
GBInEInvalidInputNonPeriodicMultiplicities = 0x00020022u,

         GBIntEUnavailableMethod = 0x00020001u,
      GBIntEObjectCreationFailed = 0x00020002u,
    GBIntEInterfaceBindingFailed = 0x00020003u,
    GBIntEInvalidOrderMethodCall = 0x00020004u,
     GBIntEInvalidParameterValue = 0x00020005u,
         GBIntEInvalidObjectType = 0x00020006u,
           GBIntEObjectShouldBeA = 0x00020007u,
         GBIntEInvalidMethodCall = 0x00020008u,
      GBIntENotValuableParameter = 0x00020009u,
       GBIntEGetLimitsOnEmptyBox = 0x0002000au,
GBIntEPointSurfaceProjectionFailed = 0x0002000bu,
GBIntEPointCurveProjectionFailed = 0x0002000cu,
         GBIntEUnavailableResult = 0x0002000du,
               GBIntEUnsetObject = 0x0002000eu,
GBIntEInvalidStreamUnstreamOrder = 0x0002000fu,
GBIntEInvalidStreamUnstreamOfLinks = 0x00020010u,
GBIntEInvalidStreamLinksCountExceeded = 0x00020011u,
        GBIntECorruptedContainer = 0x00020012u,
         GBIntEUnknownObjectType = 0x00020013u,
            GBIntEUnknownVersion = 0x00020014u,

    GBIntEFactoryOpenDualLoading = 0x00020015u

} GeometricObjectsErrors;

#endif
