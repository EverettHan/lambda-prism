// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATIntersectionEdgeCrvSur :
// Implementation class for intersection between an EdgeCurve and a Surface
//
//=============================================================================
// Usage notes:
//
//
//=============================================================================
// Nov. 97  PSH Creation                                             P. Sebah
// Dec. 98  XGN New version                                          X. Gourdon
// 14/09/21 NLD Detabulation, Mise au propre, Smart indent
// 15/09/21 NLD Ajout Init0()
//=============================================================================

#ifndef CATIntersectionEdgeCrvSur_H
#define CATIntersectionEdgeCrvSur_H

#include "Y30C3XGG.h"

#include "CATSkillValue.h"
#include "CATCrvParam.h"
#include "CATSurParam.h"
#include "CATMathSetOfPointsND.h"
#include "CATIntersectionSign.h"
#include "CATCGMVirtual.h"
#include "CATCreateIntersectionEdgeCrvSur.h"
#include "CATTolerance.h"

class CATCrvLimits;
class CATSurLimits;
class CATMathBox;
class CATMathFunctionX;
class CATMathFunctionXY;
class CATMathIntervalND;
class CATGeoFactory;
class CATEdgeCurve;
class CATMergedCurve;
class CATCurve;
class CATPointOnEdgeCurve;
class CATSurface;
class CATCurve;

class CATIntersectionEdgeCrvSurPointResult;
class CATIntersectionEdgeCrvSurMCrvResult;

class CATPlane;

class CATSoftwareConfiguration;

class ExportedByY30C3XGG CATIntersectionEdgeCrvSur : public CATCGMVirtual
 {
 public:
  //-----------------------------------------------------------------------
  //- Object management
  //-----------------------------------------------------------------------

  CATIntersectionEdgeCrvSur (      CATGeoFactory            * iFactory  ,
                                   CATSoftwareConfiguration * iConfig   ,
                                   CATEdgeCurve             * iEdgeCurve,
                             const CATPointOnEdgeCurve      * iPOECStart,
                             const CATPointOnEdgeCurve      * iPOECEnd  ,
                             const CATCurve                ** iTabCrv   ,
                             const CATLONG32                  iNbCrv    ,
                                   CATSurface               * iSurface  );
  
  CATIntersectionEdgeCrvSur (      CATGeoFactory            * iFactory  ,
                                   CATSoftwareConfiguration * iConfig   ,
                                   CATEdgeCurve             * iEdgeCurve,
                             const CATPointOnEdgeCurve      * iPOECStart,
                             const CATPointOnEdgeCurve      * iPOECEnd  ,
                             const CATCurve                 * iCrv0     ,
                             const CATCurve                 * iCrv1     ,
                                   CATSurface               * iSurface  );

  virtual ~CATIntersectionEdgeCrvSur   ();

  //-----------------------------------------------------------------------
  //- Public Methods
  //-----------------------------------------------------------------------
  
  //
  // Setting methods
  //
  // Setting eventual init points
  // if the parameter iCrv is set, then it means that the init point lies on the curve iCrv
                void                  SetAdditionnalInit      (const CATPointOnEdgeCurve * iPOEC     ,
                                                               const CATSurParam         & iSurParam ,
                                                               const CATTolerance        & iTol      ,
                                                               const CATCurve            * iCrv      = 0);

                void                  SetDontFindOtherInit    ();

                void                  SetLimits               (const CATSurLimits        & iLimitsSur);
  // Ne plus utiliser
                void                  SetLimits               (const CATCrvLimits        & iLimitsCrv);

                void                  SetLimits               (const CATPointOnEdgeCurve * iStartPOEC,
                                                               const CATPointOnEdgeCurve * iEndPOEC  );
  
  virtual       void                  Run                     ();

                void                  BeginningPoint          ();
                CATLONG32             GetNumberOfPoints       () const;
                CATBoolean            NextPoint               ();
                CATPointOnEdgeCurve * GetPointOnEdgeCurve     ();
                void                  GetSurfaceParam         (const CATCurve    * iCrv,
                                                                     CATSurParam & oParam) const;
          const CATPointOnEdgeCurve * GetRelatedInit          () const;

  virtual       CATIntersectionSign   GetSignature            () const;


                void                  BeginningCurve          ();
                CATLONG32             GetNumberOfCurves       () const;
                CATBoolean            NextCurve               ();
                CATMergedCurve      * GetMergedCurve          (      CATPointOnEdgeCurve * & oPOECStart     ,
                                                                     CATPointOnEdgeCurve * & oPOECEnd       );
  virtual       void                  GetExtremitiesOnSurface (      CATSurParam           & oSurParamStart ,
                                                                     CATSurParam           & oSurParamEnd   ) const;

                void                  GetRelatedInit          (const CATPointOnEdgeCurve * & oStart         ,
                                                               const CATPointOnEdgeCurve * & oEnd           ) const;

                void                  GetSignature            (      CATIntersectionSign   & oSignatureStart,
                                                                     CATIntersectionSign   & oSignatureEnd  ) const;

protected:
  //-----------------------------------------------------------------------
  //- Protected Methods
  //-----------------------------------------------------------------------
                void                  Init                    ();
                void                  RunWithoutInit          (const CATTolerance          & iTol           );

 private:
  //-----------------------------------------------------------------------
  //- Private Methods
  //-----------------------------------------------------------------------

                void                  Init0                   (      CATGeoFactory             * iFactory  ,
                                                                     CATSoftwareConfiguration  * iConfig   ,
                                                                     CATEdgeCurve              * iEdgeCurve,
                                                               const CATPointOnEdgeCurve       * iPOECStart,
                                                               const CATPointOnEdgeCurve       * iPOECEnd  ,
                                                          //   const CATCurve                 ** iTabCrv   ,
                                                          //   const CATLONG32                   iNbCrv    ,
                                                                     CATSurface                * iSurface  );


                void                  RunFromInit             (      CATMathSetOfPointsND  & UVW0W1L     );

                void                  IntersectPatchWithCurve (const CATCurve              * iCrv        ,
                                                               const CATCrvParam           & iStartParam ,
                                                               const CATCrvParam           & iEndParam   ,
                                                               const CATLONG32               iu          ,
                                                               const CATLONG32               iv          ,
                                                               const CATMathFunctionXY     * iSX         ,
                                                               const CATMathFunctionXY     * iSY         ,
                                                               const CATMathFunctionXY     * iSZ         ,
                                                               const CATMathBox            & iSurBox     ,
                                                                     CATMathIntervalND     & ioDomain    ,
                                                                     CATMathSetOfPointsND  & ioGlobalSol );


                void                  AddPointSolution        (const CATCrvParam           & iC0         ,
                                                               const CATCrvParam           & iC1         ,
                                                               const CATSurParam           & iS0         ,
                                                               const CATSurParam           & iS1         );


                void                  AddMCrvSolution         (const double                 iwStart      ,
                                                               const CATCurve             * iCrvStart    ,
                                                               const CATPointOnEdgeCurve  * iPOECStart   ,
                                                               const double                 iwEnd        ,
                                                               const CATCurve             * iCrvEnd      ,
                                                               const CATPointOnEdgeCurve  * iPOECEnd     ,
                                                                     CATMathSetOfPointsND * iPtOnSur     ,
                                                               const CATBoolean             iMCrvToCreate);

                CATIntersectionSign   ComputeSignature        (const CATCrvParam          & iCrvParam    ,
                                                               const CATCurve             * iCrv         ,
                                                               const CATSurParam          & iSurParam    ) const;

                void                  TransferInit            (const CATCurve             * iCrv0        ,
                                                               const double                 iw0          ,
                                                               const CATCurve             * iCrv1        ,
                                                               const double                 iLambda      ,
                                                               const double                 iu           ,
                                                               const double                 iv           ,
                                                                     double               & ou           ,
                                                                     double               & ov           ,
                                                                     double               & oOutputw     ,
                                                               const CATCurve           * & oOutputCurve);

  //-----------------------------------------------------------------------
  //- Protected data
  //-----------------------------------------------------------------------
protected:

        CATGeoFactory                        * _Factory    ;
        CATSoftwareConfiguration             * _Config     ;
        double                                 _CreationTol;

  const CATSurface                           * _Surf       ;
        CATSurParam                            _StartSurf  ,
                                               _EndSurf    ;

        CATEdgeCurve                         * _ECrv       ;
  const CATPointOnEdgeCurve                  * _StartECrv  ,
                                             * _EndECrv    ;
  const CATCurve                             * _Crv0       ,
                                             * _Crv1       ;
        CATMathFunctionX                     * _Mapping01  ,
                                             * _Mapping10  ;
        double                                 _wStart0    ,
                                               _wEnd0      ,
                                               _wStart1    ,
                                               _wEnd1      ;
        double                                 _wStartMax0 ,
                                               _wEndMax0   ,
                                               _wStartMax1 ,
                                               _wEndMax1   ;

        CATLONG32                              _IndexPoint ,
                                               _NbPoints   ,
                                               _MaxNbPoints;
        CATIntersectionEdgeCrvSurPointResult * _SolPoint   ;

        CATLONG32                              _IndexMCrv   ,
                                               _NbMCrv      ,
                                               _MaxNbMCrv   ;
        CATIntersectionEdgeCrvSurMCrvResult  * _SolMCrv     ;

        CATMathSetOfPointsND                   _Init        ;
  const CATPointOnEdgeCurve                 ** _POECInit    ;
        CATLONG32                              _MaxNbPOECInit;
        CATLONG32                              _NbPOECInit  ;
        CATBoolean                             _DontFindOtherInit;

}; 

void FindPlaneSubDomain(const CATPlane     * iPlane,
                        const CATTolerance & iTol,
                        const CATMathBox   & iBox,
                              CATSurLimits & oLimits);

ExportedByY30C3XGG void Remove(CATIntersectionEdgeCrvSur * iOper);

#endif
