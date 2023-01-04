/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATCurveBaseCGM:
// Abstract class for CGM objects that are compliant with CATCurve Interface
//=============================================================================
// Usage notes:
//
// This is an implementation of the CATCurve based on CGM V5 infrastructure.
//
//=============================================================================
// July  98 RR  Creation                                              R. Rorato
// July  98 ILY Add IsInvariant method
// Oct.  98 ILY Add IsDeepConfused method
// Jun.  12 FDS Perfo : inline constructor
// 26/11/19 NLD Mise au propre complète. Smart indent. Détabulation
//=============================================================================
#ifndef CATCurveBase_H
#define CATCurveBase_H

#include "ExportedToCGMV5Interoperability.h"                          // For Windows 
#include "CATMathDef.h"
#include "CATMathInline.h"
#include "CATOwnedCGM.h"
#include "CATCrvEvalCommand.h"
#include "CATCurve.h"                          // For CATSolutionDiagnostic
#include "CATCGMLimitsManagement.h"

class CATCrvLimits ;
class CATCrvEvalResult ;
class CATMathPoint ;
class CATMathVector ;
class CATMathBox ;
class CATMathTransformation ;
class CATMathTransformation1D ;
class CATTransfoManager ;

#include "CATListOfCATCurves.h"
class CATHashTabCATICGMUnknown;
class CATCGMPeriodicityInfo;

//#define Archi_Geo_2

class ExportedToCGMV5Interoperability CATCurveBaseCGM: public CATOwnedCGM
{
  public :
     
  //--------------------------------------------------------
  // Fusion
  virtual void                   LockEquation          (      void                   *  iForDebug);
  virtual void                   UnLockEquation        (      void                   *  iForDebug);

  virtual void                   Lock                  (const void                   *  iDebugUsage = NULL) = 0 ;
  virtual void                   Unlock                (const void                   *  iDebugUsage = NULL) = 0 ;
  virtual CATCGMLimitsManagement GetLimitsManagement   ();

  //-------------------------------------------------------------------------
  // Methods of the CATCurve Interface implemented (or pure virtual) at that level
  //-------------------------------------------------------------------------
  virtual void                   GetBox                (const CATCrvLimits            & iLimits     ,
                                                              CATMathBox              & oBox        ) const ;

  virtual int                    GetAdvancedBox        (const CATCrvLimits            & iLimits     ,
                                                              CATMathAdvancedBox      & ioBox       ) const;

  virtual int                    GetAdvancedBoundingBox(      CATMathAdvancedBox      & oBox        ) const;

  virtual CATBoolean             IsAdvancedBoundingBoxTypeAvailable
                                                       (      CATMathAdvancedBoxType    iType       ) const;

  virtual CATBoolean             IsInvariant           (const CATMathTransformation   & iTransfo    ,
                                                              CATMathTransformation1D*  oTransfo1D  = NULL) const;

          CATBoolean             IsConfused            (const CATMathTransformation   & iTransfo    ,
                                                        const CATCurve               *  iTCurve     ,
                                                              CATMathTransformation1D*  oTransfo1D  = NULL) const;
protected :
  virtual CATBoolean             IsConfused_Protected  (const CATMathTransformation   & iTransfo    ,
                                                        const CATCurve               *  iTCurve     ,
                                                              CATMathTransformation1D*  oTransfo1D  = NULL) const;
public:
  virtual CATBoolean             IsDeepConfused        (      CATTransfoManager       & iTransfo    ,
                                                        const CATGeometry            *  iTGeometry  ) const;

  virtual CATBoolean             HasMathCurve          ()                                             const = 0 ;

  // EVAL
  virtual CATMathPoint           EvalPoint             (const CATCrvParam             & iParam      ) const ; 

  virtual CATMathVector          EvalFirstDeriv        (const CATCrvParam             & iParam      ) const ; 

  virtual CATMathVector          EvalSecondDeriv       (const CATCrvParam             & iParam      ) const ; 

  virtual CATMathVector          EvalThirdDeriv        (const CATCrvParam             & iParam      ) const ; 

  virtual void                   Eval                  (const CATCrvParam             & iParam      ,
                                                        const CATCrvEvalCommand       & iCommand    ,
                                                              CATMathPoint           *  oPoint      ,
                                                              CATMathVector          *  oFirstDeriv = NULL,
                                                              CATMathVector          *  oSecondDeriv= NULL,
                                                              CATMathVector          *  oThirdDeriv = NULL ) const = 0;
 
  virtual void                   Eval                  (const CATCrvLimits            & iDomainToEvaluate,
                                                        const CATLONG32                 iNbOfPoints ,
                                                        const CATCrvEvalCommand       & iCommand    ,
                                                              CATCrvEvalResult        & oResult     ) const = 0;

  virtual CATCurve::CATSolutionDiagnostic
                                 GetParam              (const CATMathPoint            & iLocation   ,
                                                              CATCrvParam             & oIndex      ) const = 0;
  virtual CATCurve::CATSolutionDiagnostic
                                 GetParam              (const CATMathPoint            & iLocation   ,
                                                              CATCrvParam             & oIndex      ,
                                                        const CATCrvLimits            & iInside     ) const = 0;
  virtual CATLONG32              GetNumberOfComponent  ()                                             const = 0;

  virtual void                   GetEquation           (const CATLONG32                 iArc        ,
                                                        const CATMathFunctionX       *& oFx         ,
                                                        const CATMathFunctionX       *& oFy         ,
                                                        const CATMathFunctionX       *& oFz         ) const= 0;
  // Limits
  virtual void                   GetMaxLimits          (      CATCrvLimits            & oMaxLimits  ) const = 0;

  virtual void                   GetLimits             (      CATCrvLimits            & oCurrentLimits) const = 0;

  virtual CATCrvLimits           GetLimits             ()                                             const = 0;

  virtual void                   GetInternalLimits     (const CATLONG32                 iArc        ,
                                                              CATCrvLimits            & oInternalLimits) const ;

  virtual CATCrvLimits           GetInternalLimits     (const CATLONG32                 iArc        ) const ;

  virtual void                   GetInternalMaxLimits  (const CATLONG32                 iArc        ,
                                                              CATCrvLimits            & oInternalMaxLimits)  const = 0;

          void                   PerformCurveCheck     (const CATCrvParam             & icrvParamToCheck) const;

  //-------------------------------------------------------------------------
  // Gestion par evenement des modifications modeles (Extrapolation / Trim)
  //-------------------------------------------------------------------------
          void                   MaxLimitsHaveChanged  (const CATCrvLimits            & iBefore     ,
                                                        const CATCrvLimits            & iAfter      );

  //------------------------------------------------------------------------------
  // Identification des vrais implementations porteuses de donnees extrapolees
  //------------------------------------------------------------------------------
  virtual CATCGMLimitsManagement QueryLimitsManagement(       CATCrvLimits           *  ioMinimaLimits = NULL);

  //-------------------------------------------------------------------------
  // Buffer management
  //-------------------------------------------------------------------------
  virtual void                   IsModified           () ;
    
  //-------------------------------------------------------------------------
  // Integration CATCGMPeriodicityManager Procedural 
  //-------------------------------------------------------------------------
  virtual CATBoolean             CATCGMPeriodicityManager_GetInfo(      CATCGMPeriodicityInfo & oInfo) const ;
  virtual void                   CATCGMPeriodicityManager_SetInfo(const CATCGMPeriodicityInfo & iInfo)   ;
 
  //-------------------------------------------------------------------------
  // Pour Analyse Topologie
  //-------------------------------------------------------------------------
  virtual void                   GetAllGeometricRep   (       CATLISTP(CATCurve)      & ioReps      ,
                                                              CATHashTabCATICGMUnknown* iPerfoLocate= NULL);

  //-------------------------------------------------------------------------
  // Pour compact stream
  //-------------------------------------------------------------------------
  virtual void                   GetStartLocalParam    (      double                  & oStartParam ,
                                                              CATLONG32               & oPartNumber )const;
  virtual void                   GetEndLocalParam      (      double                  & oEndParam   ,
                                                              CATLONG32               & oPartNumber )const;

  virtual void                   GetStartGlobalParam   (      double                  & oStartParam )const;
  virtual void                   GetEndGlobalParam     (      double                  & oEndParam   )const;


  //-------------------------------------------------------------------------
  // Object Management
  //-------------------------------------------------------------------------
  INLINE          CATCurveBaseCGM () {};
  INLINE virtual ~CATCurveBaseCGM () {}; 
  
  //-------------------------------------------------------------------------
  // GetIndexOffset
  //-------------------------------------------------------------------------
  virtual CATLONG32              GetIndexOffset() const = 0;
  
/** @nodoc */
  virtual void                   PropagateQuery        (      CATICGMUnknown         *  iFrom       ,
                                                        const CATCrvLimits            & iLimits     ,
                                                              CATCGMQueryManager      & iQuery      ) = 0 ;
};
#endif
