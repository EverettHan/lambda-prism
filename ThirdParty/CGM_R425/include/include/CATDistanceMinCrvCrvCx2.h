// COPYRIGHT DASSAULT SYSTEMES 1997
//==========================================================================
//
// CATDistanceMinCrvCrvCx2 :
// An implementation for the operator of distance min curve curve
//
//==========================================================================
//
// Usage notes:
//
//==========================================================================
// 28/11/08 NLD Utilisation de CATCGMOperatorDebug pour outillage standard de debug/mesure
// 13/12/10 KJD Remplacement de l'argument _DistMin par  son carre _SquareDist
// 13/01/12 NLD Détabulation et remise en forme
// 16/01/12 NLD Ajout RunArcArc()
//              Suppression des constructeurs sans Software Configuration
// 17/01/12 NLD Ajout Init()
//              Ajout RunArcArcLocalMin()
//              Ajout _CGMLevel
// 31/01/02 NLD Ajout Reconverge(): minimisation locale autour du minimum en cours
// 12/03/20 Q48 Headers etc for math versioning
//==========================================================================

#ifndef CATDistanceMinCrvCrvCx2_H
#define CATDistanceMinCrvCrvCx2_H

// ExportedBy
#include "Y30C3XGG.h"

// Base class
#include "CATDistanceMinCrvCrv.h"
// C++11
#include "CATGeoOpVirtual.h"

// Data types
#include "CATDataType.h"

#include "CATMathBox.h"
#include "CATMathInterval.h"

#include "CATCrvParam.h"
#include "CATCrvLimits.h"

class CATGeoFactory;
class CATMathFunctionX;
class CATPointOnCurve;
class CATSoftwareConfiguration;

#include "CATCGMOperatorDebug.h"

//-----------------------------------------------------------------------------
class ExportedByY30C3XGG CATDistanceMinCrvCrvCx2 : public CATDistanceMinCrvCrv
{
protected:
  CATCurve                 * _Crv1,
                           * _Crv2;
  CATCrvLimits               _Crv1Lim,
                             _Crv2Lim;
  CATCrvParam                _Crv1Param,
                             _Crv2Param;
  double                     _SquareDist;
  double                     _ImposedSqrDistMax;
  CATGeoFactory            * _ImplicitFactory;
  CATSoftwareConfiguration * _SoftwareConfiguration;
  short                      _CGMLevel;

public:
  // destructor -----------------------------------------
  //
  ~CATDistanceMinCrvCrvCx2();
  
  // constructor ----------------------------------------
  //
  CATDistanceMinCrvCrvCx2(CATGeoFactory            * iFactory,
                          CATSoftwareConfiguration * iConfig,
                          CATCurve                 * iCrv1,
                          CATCurve                 * iCrv2,
                          CATPointOnCurve          * Pt1Crv1,
                          CATPointOnCurve          * Pt2Crv1,
                          CATPointOnCurve          * Pt1Crv2,
                          CATPointOnCurve          * Pt2Crv2);


  CATDistanceMinCrvCrvCx2(CATGeoFactory            * iFactory,
                          CATSoftwareConfiguration * iConfig,
                          CATCurve                 * iCrv1,
                          CATCurve                 * iCrv2);
  //
  // public methods -------------------------------------
  //
  CATCGMOperatorDebugDeclareRun      (CATDistanceMinCrvCrvCx2, CATDistanceMinCrvCrv);
  int               RunOperator      ();

  void              SetLimits        (const CATCrvLimits& CrvLim1, const CATCrvLimits& CrvLim2);
  CATPointOnCurve * GetPointOnCurve  (CATCurve *) const;
  void              GetCurveParam    (CATCurve *iCurve, CATCrvParam & oParam) const;
  void              GetCurve1Param   (CATCrvParam &ioParam1) const;
  void              GetCurve2Param   (CATCrvParam &ioParam2) const;
  double            GetDistance      () const;
  void              SetMaxDistance   (double iMaxDistance);
  CATBoolean        MinDistanceFound () const;

private:
  void              Init             (CATGeoFactory            * iFactory,
                                      CATSoftwareConfiguration * iConfig,
                                      CATCurve                 * iCrv1,
                                      CATCurve                 * iCrv2);

protected:
  //--------------------------------------------------------------------------------------
  // To correct the _CrvLim so that no arc of _Crv can be reduced to one of its extremities
  //--------------------------------------------------------------------------------------
  void              CorrectLimits();
  
  //-----------------------------------------------------------------------------------
  // Test if the Extremities of a _CrvA (MPoint, CrvParam) is contained in
  // the other _CrvB (Crv, Limits) or is closest than SqrDistMin.
  // oPointCrvParam is the _CrvParam related to the solution on the _CrvA
  // oCrvCrvParam is the _CrvParam related to the solution on the _CrvB
  //-----------------------------------------------------------------------------------
  void              BoundaryTreatment(CATMathPoint             & Point,
                                const CATCrvParam              & CrvParam,
                                      CATCurve                 * Crv,
                                const CATCrvLimits             & Limits,
                                      double                   & SqrDistMin,
                                      CATCrvParam              & oPointCrvParam,
                                      CATCrvParam              & oCrvCrvParam);

  //-----------------------------------------------------------------------------------
  // Recale les parametres a CATEpsg dans les limites
  //-----------------------------------------------------------------------------------
  void              RecalParam();
  
  //--------------------------------------------------------------------------------------
  // To measure the square distance between two CATMathBoxes
  //--------------------------------------------------------------------------------------
  //void SqDistBoundingBoxes(CATMathBox BoundingBox1, CATMathBox BoundingBox2, double & oSqrDist) const;
  
  
  //--------------------------------------------------------------------------------------
  // Special Case _Crv1 & _Crv2 are both Lines
  //--------------------------------------------------------------------------------------
  void              RunLineLine      (CATMathLine              * iMathLine1,
                                      CATMathLine              * iMathLine2);
  
  //-----------------------------------------------------------------------------------
  // Special Case : _Crv1 or _Crv2 is a Line
  //-----------------------------------------------------------------------------------
  void              RunLineCurve     (int                        IsCrv1Line,
                                      CATMathLine              * iMathLine);

  void              RunArcArc        (int                        iGlobalEq,
                                      CATLONG32                  NumArc1,
                                      CATLONG32                  NbPatch1,
                                const CATMathBox               & Crv1Box,
                                const CATMathInterval          & Crv1Domain,
                                const CATMathFunctionX         * Crv1LocEq[3],
                                      CATLONG32                  NumArc2,
                                      CATLONG32                  NbPatch2,
                                const CATMathBox               & Crv2Box,
                                const CATMathInterval          & Crv2Domain,
                                const CATMathFunctionX         * Crv2LocEq[3],
                                const CATTolerance             & tol,
                                      double                     SpecialPointsSquareTol,
                                      CATBoolean                 MinMayBeInterior,
                                      CATLONG32                  CriterionForRelentless,
                                      CATLONG32                & Nbsol,
                                      CATLONG32                & OkforIntersection
                                    );


  void              RunArcArcLocalMin(CATLONG32                  NumArc1,
                                const CATCrvParam              & Init1,
                                const CATMathInterval          & Crv1Domain,
                                const CATMathFunctionX        *  Crv1LocEq[3],
                                      CATLONG32                  NumArc2,
                                const CATCrvParam              & Init2,
                                const CATMathInterval          & Crv2Domain,
                                const CATMathFunctionX        *  Crv2LocEq[3],
                                const CATTolerance             & tol
                               );

  //-----------------------------------------------------------------------------------
  // Reconverge around current best point with local minimization
  //-----------------------------------------------------------------------------------
  void              Reconverge();

  //-----------------------------------------------------------------------------------
  // Verify the special case : one curve on a surface, the other on an offset of that
  // surface, with an offset value greater or equal to the max distance imposed.
  //-----------------------------------------------------------------------------------
  CATLONG32         TrivialOffsetCase();
  

  //========================================================================
  // Gestion CGMReplay
  //========================================================================
protected:
  friend class CATGeoStreamFactory;

  // private static data
  static CATString     _OperatorId;
  static CATGeoOpTimer _Timer;

public:

  const CATString * GetOperatorId();
  //-----------------------------------------------------------------------
  //- Gestion timer
  //-----------------------------------------------------------------------
  CATGeoOpTimer * GetTimer();

  //-----------------------------------------------------------------------
  //- Gestion Mode Record
  //-----------------------------------------------------------------------

  CATExtCGMReplay  * IsRecordable  (short& LevelOfRuntime, short &VersionOfStream);
  virtual void       WriteInput    (CATCGMStream& ioStream);
  virtual void       WriteOutput   (CATCGMStream& ioStream);
  virtual CATBoolean ValidateOutput(CATCGMStream& ioStream, CATCGMOutput& os, int VersionNumber=1);
  virtual void       Dump          (CATCGMOutput& os      );
  virtual void       DumpOutput    (CATCGMStream& ioStream, CATCGMOutput& os, int VersionNumber=1);
          void       DumpOutput    (CATCGMOutput& os);

  virtual CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & os);
  virtual CATCGMOperator::CATCheckDiagnostic CheckInput (CATCGMOutput & os);


};


#endif
