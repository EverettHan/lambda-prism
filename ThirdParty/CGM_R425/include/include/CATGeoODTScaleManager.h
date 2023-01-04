// COPYRIGHT DASSAULT SYSTEMES 2014
//=============================================================================
//
// CATGeoODTScaleManager:
//  - Utility class for managing Xscale in CGMReplays
//=============================================================================
//=============================================================================
// Usage notes:
//=============================================================================
// 29/05/14 Q48 Creation
// 18/06/14 Q48 Add / make available more utility methods
// 20/08/14 Q48 Migrate CATGeoOperator to CATCGMOperator for utility methods
// 20/10/14 Q48 New utility methods for connect-tools (no geometry)
// 09/04/15 NLD Add ExportedBy for FreeFormOperators framework
// 21/04/17 PKC compilation warning
// 02/11/18 NLD Smart indent
// 20/11/19 Q48 Add const and migration GeoUtilities
// 02/04/20 Q48 Add Vector2D read / scale methods
// 09/02/21 Q48 Move some xScale replay functionality from CATConnectTool
// 09/02/21 Q48 Add some cache of environment / reference scale data
//=============================================================================

#ifndef CATGeoODTScaleManager_H
#define CATGeoODTScaleManager_H

#include "Y3DYNOPE.h"

// Basic types
#include "CATDataType.h"
#include "CATBoolean.h"

#ifndef NULL
#define NULL 0
#endif

// System
#include "CATError.h"

// GM Modeler
class CATPGMODTScaleManager;

// Mathematics
class CATSoftwareConfiguration;
class CATCGMOutput;
class CATMathPoint;
class CATMathPoint2D;
class CATMathVector;
class CATMathTransformation1D;
class CATMathTransformation2D;
class CATMathTransformation;
class CATMathBox;
class CATMathSetOfPointsND;

// Geometric Objects
class CATCGMOperator;
class CATTransfoManager;
class CATRootSharedDataCGM;
class CATCGMStream;
class CATGeoFactory;
class CATICGMObject;
class CATGeometry;
class CATCurve;
class CATSurface;
class CATCrvParam;
class CATCrvLimits;
class CATSurParam;
class CATSurLimits;

// Geometric Operators
class CATGeoOperator;
#include "CATGeometryPack.h"

class ExportedByY3DYNOPE CATGeoODTScaleManager
{
public:
                                            CATGeoODTScaleManager(     CATGeoFactory* iFactory);
                                           ~CATGeoODTScaleManager();

  // Memory option
  // -------------

               void                         SetOwnerFactory      (const CATBoolean iTakeOwnership = TRUE);
               void                         SetOwnerFactoryScaled(const CATBoolean iTakeOwnership = TRUE);

  // Creation methods
  // ----------------

  static       CATBoolean                   GetScaleManager(const double                   iScaleRef,
                                                            const CATUnicodeString       & iClassStr,
                                                                  CATGeoODTScaleManager *& oScaleManager);
  // Utility methods
  // ---------------
  
  static       void                         DeleteScaleManager(const CATCGMOperator*);

  static       void                         SetScaleManager   (const CATCGMOperator*, CATGeoODTScaleManager*);
  static       CATGeoODTScaleManager      * GetScaleManager   (const CATCGMOperator*);

  static       CATGeometryPack::XScaleLevel GetScaleLevel_ValidateOutput(const CATGeoODTScaleManager*);

  //CATBoolean IsOpenReplay(CATCGMStream&) const;
  static       CATBoolean                   IsClosedConfig    (CATSoftwareConfiguration *);
               CATBoolean                   IsClosedConfig    (CATSoftwareConfiguration *, CATCGMOutput &) const;
  
  static       double                       ReadScaleFromEnv  (CATCGMScaleCategory      *  oScaleEnvCategory = NULL);

  static       void                         ApplyScaleAndCheck(CATGeoODTScaleManager    *& ioScaleManager, const CATUnicodeString iUserString);

  // Handle scaling of replays with no factory by default (moved from CATConnectTool)
  static       void                         WriteScaleInfo    (CATCGMStream & ioStream);
  
  static       void                         ReadScaleInfo     (CATCGMStream & ioStream,
                                                               double       & oRefScale);


  // Run
  // ---
    
               CATBoolean                   ApplyScale();
               CATBoolean                   ApplyScale(CATError *& oError);

               CATBoolean                   ApplyScale        (const double                  iScaleRef);

  // Outputs
  // -------
  
               CATBoolean                   ScalingRequired   () const;
               CATBoolean                   ScaleAppliedOK    () const;

               double                       GetOrigScale      () const;
               double                       GetCurrScale      () const;
               CATCGMScaleCategory          GetCurrScaleCategory() const;

               CATGeoFactory              * GetOriginalFactory() const;
               CATGeoFactory              * GetScaledFactory  () const;

  static       CATICGMObject              * GetScaledObject   (const CATGeoODTScaleManager * iScaleManager,
                                                                     CATICGMObject         * iObject);

  static       CATLaw                     * GetScaledLaw      (const CATGeoODTScaleManager * iScaleManager,
                                                                     CATLaw                * iLaw,
                                                               const CATLONG32               iScaleX = -1,
                                                               const CATLONG32               iScaleF = -1,
                                                               const char                  * iLabel = NULL);

               CATICGMObject              * GetScaledObject   (      CATICGMObject         * iObject) const;

               CATGeometry                * GetScaledGeometry  (const CATGeometry           * iGeom) const;
               CATGeometry                * GetOriginalGeometry(const CATGeometry           * iGeom) const;

        const double                        GetScaleRatio     () const;
        const CATMathTransformation1D     * GetMathTransform1D() const;
        const CATMathTransformation2D     * GetMathTransform2D() const;
        const CATMathTransformation       * GetMathTransform3D() const;

              CATTransfoManager           * GetTransfoManager() const;
  
  // Utility methods
  // ---------------

              CATBoolean                    ScaleDouble     (      double   & ioValue) const;
              CATBoolean                    ScaleDoubleArray(      double     ioArray[], const CATLONG32) const;
              CATBoolean                    ScaleSqDouble   (      double   & ioValue) const;
              CATBoolean                    ScaleDouble     (      double   & ioValue,
                                                             const double   & iScalePower) const;

              CATBoolean                    ScalePoint      (   CATMathPoint    & ioPoint ) const;
              CATBoolean                    ScalePoint2D    (   CATMathPoint2D  & ioPoint ) const;
              CATBoolean                    ScaleVector     (   CATMathVector   & ioVector) const;
              CATBoolean                    ScaleVector2D   (   CATMathVector2D & ioVector) const;
              CATBoolean                    ScaleBox        (   CATMathBox      & ioBox   ) const;

              CATBoolean                    ScaleSetOfPointsND(CATMathSetOfPointsND * ioSet) const;

  static      CATBoolean                    ReadCrvParam (const CATGeoODTScaleManager * iScaleManager,
                                                                CATCGMStream          & ioStream, 
                                                          const CATCurve              * iScaledCurve,
                                                                CATCrvParam           & oParam,
                                                                CATCurve              * iOrigCurve = NULL);

  static      CATBoolean                    ReadCrvLimits(const CATGeoODTScaleManager * iScaleManager,
                                                                CATCGMStream          & ioStream, 
                                                          const CATCurve              * iScaledCurve, 
                                                                CATCrvLimits          & oLimits,
                                                                CATCurve              * iOrigCurve = NULL);

  static      CATBoolean                    ReadSurParam (const CATGeoODTScaleManager * iScaleManager,
                                                                CATCGMStream          & ioStream,
                                                          const CATSurface            * iScaledSurf,
                                                                CATSurParam           & oParam,
                                                                CATSurface            * iOrigSurf = NULL);

  static      CATBoolean                    ReadSurLimits(const CATGeoODTScaleManager * iScaleManager,
                                                                CATCGMStream          & ioStream, 
                                                          const CATSurface            * iScaledSurf, 
                                                                CATSurLimits          & oLimits,
                                                                CATSurface            * iOrigSurf = NULL,
                                                          const char                  * iLabelReserved = NULL);

  static      CATBoolean                    ReadDouble   (const CATGeoODTScaleManager * iScaleManager,
                                                                CATCGMStream          & ioStream     ,
                                                          const double                & iScalePower  ,
                                                                double                & oDouble      ,
                                                          const char                  * iLabelReserved = NULL);

  static      CATBoolean                    ReadBox      (const CATGeoODTScaleManager * iScaleManager,
                                                                CATCGMStream          & ioStream     ,
                                                                CATMathBox            & oBoxScaled   ,
                                                          const char                  * iLabelReserved = NULL);

  static      CATBoolean                    ReadPoint    (const CATGeoODTScaleManager * iScaleManager,
                                                                CATCGMStream          & ioStream     ,
                                                                CATMathPoint          & oPointScaled ,
                                                          const char                  * iLabelReserved = NULL);

  static      CATBoolean                    ReadPoint2D  (const CATGeoODTScaleManager * iScaleManager,
                                                                CATCGMStream          & ioStream     ,
                                                                CATMathPoint2D        & oPointScaled ,
                                                          const char                  * iLabelReserved = NULL);

  static      CATBoolean                    ReadVector2D (const CATGeoODTScaleManager * iScaleManager,
                                                                CATCGMStream          & ioStream     ,
                                                                CATMathVector2D       & oVecScaled ,
                                                          const char                  * iLabelReserved = NULL);

              CATBoolean                    ComputeScaledCrvParam
                                                         (const CATCrvParam           & iParam,
                                                          const CATCurve              * iCurve,
                                                                CATCrvParam           & oParam) const;

              CATBoolean                    ComputeScaledCrvLimits
                                                         (const CATCrvLimits          & iLimits,
                                                          const CATCurve              * iCurve, 
                                                                CATCrvLimits          & oLimits) const;

              CATBoolean                    ComputeScaledSurParam
                                                         (const CATSurParam           & iParam,
                                                          const CATSurface            * iSurf ,
                                                                CATSurParam           & oParam) const;

              CATBoolean                    ComputeScaledSurLimits
                                                         (const CATSurLimits          & iLimits,
                                                          const CATSurface            * iSurf,
                                                                CATSurLimits          & oLimits) const;

protected:

              CATBoolean                    ReadCrvParam(       CATCGMStream          & ioStream, 
                                                                CATCurve              * iCurve, 
                                                                CATCrvParam           & oParam,
                                                                CATCurve              * iOrigCurve = NULL) const;
  
              CATBoolean                    ReadCrvLimits(      CATCGMStream          & ioStream, 
                                                                CATCurve              * iScaledCurve,
                                                                CATCrvLimits          & oLimits,
                                                                CATCurve              * iOrigCurve = NULL) const;
  
              CATBoolean                    ReadSurParam(       CATCGMStream          & ioStream,
                                                                CATSurface            * iScaledSurf, 
                                                                CATSurParam           & oParam,
                                                                CATSurface            * iOrigSurf = NULL) const;
  

              CATBoolean                    ReadSurLimits(      CATCGMStream          & ioStream,
                                                                CATSurface            * iScaledSurf, 
                                                                CATSurLimits          & oLimits,
                                                                CATSurface            * iOrigSurf = NULL,
                                                          const char                  * iLabelReserved = NULL) const;
  
private:

               void                          ResetScaledData    ();

               void                          ConstructTransforms();

               CATRootSharedDataCGM        * GetDataFromFactory (CATGeoFactory*) const;

  CATGeoFactory           * _Factory;
  CATGeoFactory           * _FactoryScaled;

  CATBoolean                _OwnFactory;
  CATBoolean                _OwnFactoryScaled;

  CATPGMODTScaleManager   * _ScaleManager;

  /*typedef*/ // PKC 21/04/2017 useless typedef in C++, compilation warning 
  enum ScaleRC { NotApplied, AppliedError, AppliedKO, AppliedOK };
  ScaleRC                   _ScaleApplied;

  double                    _ScaleValueRef;
  double                    _ScaleValueEnv;
  CATCGMScaleCategory       _ScaleCategoryEnv;

  CATBoolean                _ScalingRequired;
  double                    _ScaleRatio; // _ScaleEnv / _ScaleRef

  CATMathTransformation1D * _Transform1D;
  CATMathTransformation2D * _Transform2D;
  CATMathTransformation   * _Transform3D;
};
#endif // CATGeoODTScaleManager_H
