//===================================================================
// COPYRIGHT Dassault Systemes 2015/01/08
//===================================================================
// CATUtilMassProperties3D.cpp
// Header definition of class CATUtilMassProperties3D
//===================================================================
//
// Usage notes: Utilies for MassProperties3D.
//
//===================================================================
// Historic
//  08-Jan-2015 : F1Z - Creation.
//  21-Apr-2017 : PKC   compilation warning
//  30-06-2021  : NLD - Mise au propre
//                      - detabulation
//                      - smart indent
//                    - Ajout GetGlobalContext()
//===================================================================

#ifndef CATUtilMassProperties3D_H
#define CATUtilMassProperties3D_H

// System
#include "CATBoolean.h"

// Mathematics

#include "CATTolerance.h"
#include "CATString.h"
#include "CATMathPoint.h"
#include "CATMathVector.h"
#include "CATMath3x3Matrix.h"

// Geometric operator
#include "Y30UIUTI.h"

// GMModelInterface
#include "CATTopDefine.h"

// Not an attribut
class CATCGMOutput;
class CATCGMStream;

//-----------------------------------------------------------------------
/*typedef*/ // PKC 21/04/2017 useless typedef in C++, compilation warning 
enum IntegrationFocus{NO_FOCUS, BOTH_FOCUS, AREA_FOCUS, VOLUME_FOCUS};

// Class intended to handle the global mass propreties context information
// and provide few methods to interact with them.
class ExportedByY30UIUTI CATMassPropertiesGlobalContext
{
public:
                     CATMassPropertiesGlobalContext ();
                     CATMassPropertiesGlobalContext (const double           & iVolume      ,
                                                     const double           & iVolumeError ,
                                                     const double           & iArea        ,
                                                     const double           & iAreaError   ,
                                                     const double           & iTol         ,
                                                           IntegrationFocus   iFocusContext);
                     CATMassPropertiesGlobalContext (const CATMassPropertiesGlobalContext &);
   virtual          ~CATMassPropertiesGlobalContext ();

   // -------------------
   // Set methods
   // -------------------
          void       SetGlobalContext               (const double           & iVolume      ,
                                                     const double           & iVolumeError ,
                                                     const double           & iArea        ,
                                                     const double           & iAreaError   ,
                                                     const double           & iTol         ,
                                                           IntegrationFocus   iFocusContext);

   // -------------------
   // Get methods
   // -------------------
          void       GetGlobalContext               (      double           & oVolume      ,
                                                           double           & oVolumeError ,
                                                           double           & oArea        ,
                                                           double           & oAreaError   ,
                                                           double           & oTol         ,
                                                           IntegrationFocus & oFocusContext);

          void       GetTargetRelTolerance          (      double           & oTargetRelTol);

          void       GetFocus                       (      IntegrationFocus & oFocus);

   // -------------------
   // Computation methods
   // -------------------
          CATBoolean IsGlobalContextRespected       (const double           & iVolError       ,
                                                     const double           & iAreaError      ,
                                                           double           * iTargetRelTol   = NULL ) const;

          void       ComputeNewTargetAbsError       (      double             iVol            ,
                                                           double             iVolError       ,
                                                           double             iArea           ,
                                                           double             iAreaError      ,
                                                           double           & oErrorVolume    ,
                                                           double           & oErrorArea      );

          CATBoolean IsFirstBetter                  (      double             iVolError1      ,
                                                           double             iAreaError1     ,
                                                           double             iVolError2      ,
                                                           double             iAreaError2     );

   // -------------------
   // Display methods
   // -------------------
          void       Write                          (      CATCGMStream     & ioStream        );
   static CATMassPropertiesGlobalContext
                     Read                           (      CATCGMStream     & iStream         );
          void       Dump                           (      CATCGMOutput     & os              ,
                                                     const CATTolerance     & iTol            = CATGetDefaultTolerance(),
                                                           CATString          iShift          = CATString());


private:

   // ----------------
   // Attributs
   // ----------------
   // MassProperties global context
   double           _GlobalVolume;
   double           _GlobalVolumeError;
   double           _GlobalArea;
   double           _GlobalAreaError;

   // Target relative tolerance
   double           _TargetTol;

   // Integration context
   IntegrationFocus _FocusContext;
};

// -------------------------------------------------
// Class intended to handle the mass propreties information (3D or 2D, not 1D yet)
// and provide few methods to interact with them.
class ExportedByY30UIUTI CATMassProperties3DInfo
{
public:
   // -------------------------------
   // Constructor(s) & Desctructor(s)
   // -------------------------------
            CATMassProperties3DInfo();
            CATMassProperties3DInfo(const CATMassProperties3DInfo &iToCopy);
   virtual ~CATMassProperties3DInfo();

   // -------------------------------
   // Set methods
   // -------------------------------
   void       SetMassPropertiesInfo(double        & iVolume       ,
                                    double        & iArea         ,
                                    CATMathPoint  & iCOG          ,
                                    double          iInertia[6]   ,
                                    double        & iVolumeError  ,
                                    double        & iAreaError    ,
                                    CATMathVector & iCOGError     ,
                                    CATBoolean      iIsRecentered = FALSE,
                                    CATBoolean      iIsNormalized = FALSE);
   void       SetVolumeComputationInfo(CATBoolean   iIsVolumeComputed);

   // -------------------------------
   // Get methods
   // -------------------------------
   CATBoolean IsMassPropertiesInfoStored();
   void       GetMassPropertiesInfo(double        & oVolume               ,
                                    double        & oArea                 ,
                                    CATMathPoint  & oCOG                  ,
                                    double          oInertia[6]           ,
                                    double        & oVolumeError          ,
                                    double        & oAreaError            ,
                                    CATMathVector & oCOGError             ) const;

   void       GetMassPropertiesInfo(double        * oVolume               ,
                                    double        * oWetArea              ,
                                    CATMathPoint  * oCenterOfGravity      ,
                                    double        * oInertia              ,
                                    double        * oVolumeError          = NULL,
                                    double        * oAreaError            = NULL,
                                    CATMathVector * oCenterOfGravityError = NULL) const;
   void       GetInertialMatrix(CATMath3x3Matrix &oInertiaMatrix);

   // -------------------------------
   // Update & Apply method
   // -------------------------------
   void       Reset                     ();
   void       ResetArea                 ();
   void       ResetVolume               ();

   void       UpdateMassPropertiesError (      CATMassProperties3DInfo & iMassPropertiesInfo);
   void       SwapCoordinates           (const int                       iSwapIndice[6]    );
   void       UpdateToOrigin            (      CATMathPoint            & iOrigin           );
   void       Normalize                 (      double                    iRelTol           ,
                                         const double                  * iMaxError         = NULL);
   void       UpdateToOriginAndNormalize(      CATMathPoint            & iOrigin           ,
                                               double                    iRelTol           ,
                                                                         // Computation optimization to reduce intermediate huge values
                                         const double                  * iMaxError         = NULL);

   void       ApplySurfaceOrientation   (      CATOrientation          & iSurfaceOrientation);
   void       ApplyFaceOrientation      (      CATOrientation          & iFaceOrientation   );

   // -------------------------------
   // Check method
   // -------------------------------
   CATBoolean IsGlobalContextRespected(const CATMassPropertiesGlobalContext & iGlobalContext      ,
                                             double                         * iTargetRelTol=NULL  );
   CATBoolean IsSimilar               (      CATMassProperties3DInfo        & iMassPropertiesInfo ,
                                             double                           iRelTol             = 0.9);

   // -------------------------------
   // Operation method
   // -------------------------------
   void                     operator += (const CATMassProperties3DInfo & iMassProp);
   void                     operator -= (const CATMassProperties3DInfo & iMassProp);
   CATMassProperties3DInfo& operator  = (const CATMassProperties3DInfo & iToCopy);

   // -------------------
   // Display methods
   // -------------------
          void                    Write(CATCGMStream &ioStream);
   static CATMassProperties3DInfo Read(CATCGMStream &iStream);
          void                    Dump(CATCGMOutput &os, const CATTolerance &iTol=CATGetDefaultTolerance(), CATString iShift=CATString());

private:
   // -------------------
   // Internal methods
   // -------------------
   CATMassProperties3DInfo GetReverse() const;

   // -------------------------------
   // Attributs
   // -------------------------------
   // Mass Properties info
   CATBoolean      _MassPropertiesInfoSet;
   CATBoolean      _IsVolumeComputed;
   CATBoolean      _Recentered;
   CATBoolean      _Normalized;

   double          _Volume;
   double          _Area;
   CATMathPoint    _CenterOfGravity;
   double          _IData[6];
   double          _VolumeError;
   double          _AreaError;
   CATMathVector   _CenterOfGravityError;
};

// -------------------------------------------------
// Class intended to handle the mass propreties computation information
class ExportedByY30UIUTI CATMassProperties3DGeoComputationInfo
{
public:

   // -------------------------------
   // Constructor(s) & Desctructor(s)
   // -------------------------------
   CATMassProperties3DGeoComputationInfo();
   CATMassProperties3DGeoComputationInfo(CATMassProperties3DGeoComputationInfo &iToCopy);
   virtual ~CATMassProperties3DGeoComputationInfo();

   // -------------------------------
   // Set methods
   // -------------------------------
   void SetComputationInformation(CATBoolean iIsIsoU, double iIsoValue);

   // -------------------------------
   // Get methods
   // -------------------------------
          CATBoolean                            IsComputationInformationStored();
          void                                  GetComputationInformation     (      CATBoolean   & oIsIsoU  ,
                                                                                     double       & oIsoValue);

   // -------------------
   // Display methods
   // -------------------
          void                                  Write                         (      CATCGMStream & ioStream);
   static CATMassProperties3DGeoComputationInfo Read                          (      CATCGMStream & iStream );
          void                                  Dump                          (      CATCGMOutput & os      ,
                                                                               const CATTolerance & iTol    = CATGetDefaultTolerance(),
                                                                                     CATString      iShift  = CATString());

private:

   // -------------------------------
   // Attributs
   // -------------------------------
   // Computation information
   CATBoolean     _ComputationInfoSet;
   CATBoolean     _IsIsoU;
   double         _IsoValue;
};

//-----------------------------------------------------------------------

#endif
