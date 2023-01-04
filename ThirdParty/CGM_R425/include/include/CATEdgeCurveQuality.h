/* -*-c++-*-*/
// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// CATEdgeCurveQuality.h
//=============================================================================
// Usage Notes:
//=============================================================================
// Jun.  99 XGN Creation                                             X. Gourdon
// 28/09/20 NLD Ajout Init()
//              Ajout InitCrv()
//              Mise au propre
// 05/02/21 NLD Ajout Clear()
//              Ajout argument oError à InitCrv()
//=============================================================================

#ifndef CATEdgeCurveQuality_H
#define CATEdgeCurveQuality_H

#include "Y30UIUTI.h"

#include "CATMathInterval.h"
#include "CATListOfCATCurves.h"
#include "CATPGMEdgeCurveQuality.h"

class CATCurve;
class CATEdgeCurve;
class CATGeoFactory;
class CATPCurve;
class CATPointOnEdgeCurve;
class CATSoftwareConfiguration;
class CATSurface;
class CATError;

class ExportedByY30UIUTI CATEdgeCurveQuality : public CATPGMEdgeCurveQuality
{
 public:
  //-----------------------------------------------------------------------
  //- Object management
  //-----------------------------------------------------------------------

                  CATEdgeCurveQuality         (      CATGeoFactory            * iFactory      ,
                                                     CATSoftwareConfiguration * iConfig       ,
                                                     CATEdgeCurve             * iEdgeCurve    ,
                                               const CATPointOnEdgeCurve      * iPOECStart    ,
                                               const CATPointOnEdgeCurve      * iPOECEnd      ,
                                               const CATCurve                 * iCrv1         ,
                                               const CATCurve                 * iCrv2         );

                  CATEdgeCurveQuality         (      CATGeoFactory            * iFactory      ,
                                                     CATSoftwareConfiguration * iConfig       ,
                                                     CATEdgeCurve             * iEdgeCurve    ,
                                               const CATPointOnEdgeCurve      * iPOECStart    = 0,
                                               const CATPointOnEdgeCurve      * iPOECEnd      = 0,
                                               const CATLONG32                  iNbCrv        = 0,
                                                     CATCurve                ** iTabCrv       = 0);
   //do not use
                  CATEdgeCurveQuality         (      CATGeoFactory            * iFactory      ,
                                                     CATEdgeCurve             * iEdgeCurve    ,
                                               const CATPointOnEdgeCurve      * iPOECStart    ,
                                               const CATPointOnEdgeCurve      * iPOECEnd      ,
                                               const CATCurve                 * iCrv1         ,
                                               const CATCurve                 * iCrv2         );

   //do not use
                  CATEdgeCurveQuality         (      CATGeoFactory            * iFactory      ,
                                                     CATEdgeCurve             * iEdgeCurve    ,
                                               const CATPointOnEdgeCurve      * iPOECStart    = 0,
                                               const CATPointOnEdgeCurve      * iPOECEnd      = 0,
                                               const CATLONG32                  iNbCrv        = 0,
                                                     CATCurve                ** iTabCrv       = 0);

                 ~CATEdgeCurveQuality();

  //-----------------------------------------------------------------------
  //- Public methods
  //-----------------------------------------------------------------------

  // return the maxgap (with respect to the input poecs)
  double          ComputeMaxGap                     (CATCrvParam               * oWorstParam1 = 0,
                                                     CATCrvParam               * oWorstParam2 = 0,
                                                     double                      iTolerance   = 0.);

  // return the Global maxgap (with respect to the input poecs and listes of Pcurves)
  double          ComputeGlobalMaxGap                (CATCrvParam              * oWorstParam1 = 0,
                                                      CATCrvParam              * oWorstParam2 = 0,
                                                      double                     iTolerance   = 0.);
  // return the min and max angle (in radian)
  // Note : The operator should be initialized with the first constructor and
  //        the two Curves (iCrv1 and iCrv2) must be some PCurves.
  // Note : Since no information is known on the orientation of the face/surface
  // and side on face, the angle returned are between -pi/2 and pi/2 and the sign
  // depends only on the orientation of the surfaces
  CATMathInterval ComputeMinMaxAngle                  ();

  // return the min and max angle (in radian), taking into account the relative
  // orientation between the face and surface given by
  // OriFaceVsSurface1 and OriFaceVsSurface2 (=+1 or -1).
  // The angles returned are between -pi and pi.
  // The sign of the angles is decided from the side of the edgecurve 
  // on the first face (=1 by default, that is the first face is at the left 
  // of the EdgeCurve by default). Thus, if the SideEdgeCrvOnFace1 is not 
  // given (default behaviour), the sign of the angles is not determined.
  // Note : The operator should be initialized with the first constructor and
  //        the two Curves (iCrv1 and iCrv2) must be some PCurves.
  CATMathInterval ComputeOrientedMinMaxAngle          (int                       OriFaceVsSurface1  ,
                                                       int                       OriFaceVsSurface2  ,
                                                       int                       SideEdgeCrvOnFace1 = 1);

  // return the max curvature difference
  double          ComputeMaxCurvature                 ();
  // choice the Number of discretization point to compute the max Gap
  void            SetNumberOfPoints                   (CATLONG32                 iNumberOfPoints    );

  // choice the Number of discretization point per arc in case of Nurbs Curve, to compute the max Gap 
  // Default value 5
  void            SetNumberOfPointsPerArcForNurbsCurve(CATLONG32                 iNumberOfPoints    );

  void            SetReconvergeMaxGap                 ();

  // KY1 : 
  /*
  * @nodoc @nocgmitf
  */
  void            GetListOfCurvesOfGlobalMaxGap       (CATLISTP(CATCurve)       & ioListOfCrvMaxGap  );

  /**
  * @nodoc
  */
  void            SetSymmetrizedMapping               ();

 protected:
   void           InitializeDataForAngles             (CATCrvParam                Start[2],
                                                       CATCrvParam                End  [2]);

   CATBoolean     ComputeAngle                  (const CATCrvParam              & Param0            ,
                                                 const CATCrvParam              & Param1            ,
                                                       int                        OriFaceVsSurface1 ,
                                                       int                        OriFaceVsSurface2 ,
                                                       int                        SideEdgeCrvOnFace1,
                                                       double                   & oAngle            );

   CATBoolean      ComputeSinAngle              (const CATCrvParam              & Param0            ,
                                                 const CATCrvParam              & Param1            ,
                                                       double                   & oSinAngle         );

 private:
   void            Init                         (      CATGeoFactory            * iFactory          ,
                                                       CATSoftwareConfiguration * iConfig           ,
                                                       CATEdgeCurve             * iEdgeCurve        ,
                                                 const CATPointOnEdgeCurve      * iPOECStart        ,
                                                 const CATPointOnEdgeCurve      * iPOECEnd          );

   void            InitCrv                      (const CATLONG32                  iNbCrv            ,
                                                       CATCurve                ** iTabCrv           ,
                                                       CATError                *& oError            );

   void            Clear                        ();


 protected:
         CATGeoFactory            * _Factory;
         CATEdgeCurve             * _ECrv;

         CATLONG32                  _NbSample;
         CATLONG32                  _NbSamplePerArcForNurbsCrv;

         CATLONG32                  _NbCrv;
         CATCurve                ** _CrvTab;

   const CATPointOnEdgeCurve      * _POECStart,
                                  * _POECEnd;

   const CATCurve                 * _Crv[2];
   const CATPCurve                * _PCrv[2];

         CATSurface               * _Support[2];
         CATBoolean                 _ReconvergeMaxGap;
         CATSoftwareConfiguration * _Config;
         CATLISTP(CATCurve)         _ListOfCrvOfMaxGap;
         CATBoolean                 _SymmetrizedMapping;
};

#endif
