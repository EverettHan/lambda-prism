//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATConnectTool:
//
//=============================================================================
//
// Usage notes:
//
//=============================================================================
// ??/01/97 SRO Creation                                             (S. Royer)
// 20/10/14 Q48 Implement X-scale in CGM-replay
// Mars  16 JSX Tool with CATSoftwareconfiguration 
//              member _Config is now shared by all tools
// Apr 21   SME31 Implement GetCutterDimension()
//=============================================================================
#ifndef CATConnectTool_h
#define CATConnectTool_h

#include "Connect.h"
#include "CATConnectDefines.h"
#include "CATCGMOperator.h"

class CATGeoFactory;
class CATSurface;

class CATGeoODTScaleManager;
class CATSoftwareConfiguration;
class CATMathPolynomX;

class ExportedByConnect CATConnectTool : public CATCGMOperator
   {
   CATCGMVirtualDeclareClass(CATConnectTool);
   public:
                                     CATConnectTool       (CATSoftwareConfiguration *iConfig = NULL);
      virtual                       ~CATConnectTool       ();
 
      virtual CATLONG32              GetType              () const=0;
      enum CutterType { CrvSur, SurSur, PtSur, SurSurSur, SurCrvCrv, CrvCrv, SurSurCrv, CrvCrvSur };
      virtual void                   SetOriginCurveSupport( CATSurface * iSupp, CATLONG32 iOrient );
      virtual void                   GetOriginCurveSupport( CATSurface *& oSupp, CATLONG32 & oOrient );
      virtual CATLONG32              GetCutterDimension(CATConnectTool::CutterType iCutterType) const;
      //=================================================
      // Methodes permettant de streamer les tools pour
      // les CGMReplays de la meme maniere que les
      // CGMOperator.
      // Pour capturer/loader un nouveau tool, certaines
      // methodes doivent etre implementees.
      // Pour exemple : CATConstantFilletTool CATEuclidianParallelTool CATParallelConnectTool
      //====================================================
      /** @nodoc @nocgmitf */
      virtual CATExtCGMReplay      * IsRecordable         (short & LevelOfRuntime, short &VersionOfStream);
      /** @nodoc @nocgmitf */
      virtual void                   WriteInput           (CATCGMStream  & ioStream);

      static  void                   WriteScaleInfo       (CATCGMStream & Str);
      static  void                   ReadScaleInfo        (CATCGMStream & Str, double & oRefScale);

      static  CATBoolean             GetScaleManager      (CATGeoFactory *iFactory,  CATGeoODTScaleManager *& oScaleManager);
      static  CATBoolean             GetScaleManager      (const double   iScaleRef, CATGeoODTScaleManager *& oScaleManager);

              CATGeoODTScaleManager* GetScaleManager      () const;

              void                   SetScaleManager      (CATGeoODTScaleManager* iScaleManager);

      virtual CATLONG32              GetSectionType       () const;

   protected:
              CATBoolean             IsPolynomialConstant(CATMathPolynomX *iPolynomial) const;

      //====================================================
      // DATA
      //====================================================
   protected:

      CATSoftwareConfiguration * _Config;
      CATGeoODTScaleManager    * _ScaleManager;
   };

#endif
