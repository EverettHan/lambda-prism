// COPYRIGHT DASSAULT SYSTEMES 
//=============================================================================
//
// CATExtrapolSurfacesForOffset :
// 
//=============================================================================
//   /04/00 FBZ Creation
//   /07/05 CQI Dichotomy treatment
//   /08/05 CQI SafeSetLimits
// 12/03/20 Q48 Headers etc for math versioning
//=============================================================================

#ifndef CATExtrapolSurfacesForOffset_H
#define CATExtrapolSurfacesForOffset_H 

// ExportedBy
#include "Y30C3XGG.h"

// Base class
#include "CATGeoOperator.h"

// C++11
#include "CATGeoOpVirtual.h"

#include "CATSkillValue.h"
#include "CATSurLimits.h"
#include "CATCrvLimits.h"
#include "CATMathVector2D.h"
#include "CATHomotopyDef.h"

#include "CATString.h"
#include "CATGeoOpTimer.h"

class CATMathIntervalND;
class CATSurface;
class CATPCurve;
class CATEdgeCurve;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATSystem6x6s;
class CATMathNxNFullMatrix;

class ExportedByY30C3XGG CATExtrapolSurfacesForOffset : public CATGeoOperator
{
  public :  
  //-----------------------------------------------------------------------
  //- Object management 
  //-----------------------------------------------------------------------
  //
  // Cet operateur prend en entrees une edge curve iEdgeCurve
  // avec ses CrvLimits iEdgeCurveLimits,
  // les deux surfaces bordant l'edge curve,
  // les deux valeurs d'offset des surfaces.
  //
  // Il a pour but de calculer apres offset des deux surfaces
  // la boite d'encombrement de l'Edge Curve sur les deux surfaces
  // et d'extrapoler si necessaire l'une d'elle.
  //
  //-----------------------------------------------------------------------

  CATExtrapolSurfacesForOffset(CATGeoFactory * iFactory,
    CATSoftwareConfiguration * iConfig,
    CATEdgeCurve * iEdgeCurve, const CATCrvLimits & iEdgeCurveLimits,
    CATSurface * iSurface1, CATSurface * iSurface2,
    double iOffset1, double iOffset2); 

  ~CATExtrapolSurfacesForOffset();

  //-----------------------------------------------------------------------
  //- Public Methods
  //-----------------------------------------------------------------------
  
  int RunOperator();
 
  //-----------------------------------------------------------------------
  //
  // SetLimits
  // specifie les limites sur la surface iSurfNumber = { 0, 1 }
  // ainsi que les cotes (umin, umax, vmin, vmax) que l'on peut
  // extrapoler dans l'operateur. Par defaut, aucun cote n'a le 
  // droit d'etre extrapole.
  //
  //-----------------------------------------------------------------------
 
  void SetLimits(const CATLONG32 iSurfNumber, const CATSurLimits & iNewLimits,
    CATSideToExtrapolate  iSide =CATNoSide);
    
  //-----------------------------------------------------------------------
  //
  // Renvoie les boites d'encombrement en UV de l'EdgeCurve sur
  // les deux surfaces apres offset
  //
  //-----------------------------------------------------------------------

  void GetBoxOnSurfaces(CATSurLimits &oLimits1, CATSurLimits &oLimits2);

  //-----------------------------------------------------------------------
  //
  // Renvoie
  //
  //    *NoNeedsForExtrapolation si on n'a pas besoin d'extrapoler la surface i
  //
  //    *ExtrapolationDone si la surface i  a ete extrapolee
  //
  //    *ImpossibleExtrapolation si on a besoin de l'extrapoler mais 
  //                   c'est impossible
  //
  //    *ReachBoundary si un des points de l'EC bute sur une frontiere
  //     fermee ou sur une boite "specified limits"
  //     (Dans le cas d'une fermeture, les limites des PCurves vont 
  //      jusqu'aux isopars de fermeture)
  //    
  //-----------------------------------------------------------------------

  enum CATExtrapolDiag { NoNeedsForExtrapolation, ExtrapolationDone, ImpossibleExtrapolation, 
    ReachBoundary};

  CATExtrapolSurfacesForOffset::CATExtrapolDiag GetDiagnosticForSurface(CATLONG32 i, CATSideToExtrapolate & oSide);

  //-----------------------------------------------------------------------
  //
  // Methodes pour recuperer les points (s'il y en a) utilises
  // dans l'operateur
  //
  // oParam1 = Param sur la Surface1
  // oParam2 = Param sur la Surface2
  // CATPointDiag = PointOK si le point ne pose pas probleme
  // CATPointDiag = PointReachBoundary si le point s'arrete sur une specifiedlimits
  //      ou sur une frontiere fermee
  //
  //-----------------------------------------------------------------------
  
  enum CATPointDiag { PointOK, PointReachBoundary};
  void BeginningPoint();
  CATLONG32 NextPoint();
  CATLONG32 GetNumberOfPoints();
  CATExtrapolSurfacesForOffset::CATPointDiag GetPoint(CATSurParam &oParam1, CATSurParam &oParam2);
  CATExtrapolSurfacesForOffset::CATPointDiag GetPoint(CATCrvParam & oECParam,
    CATSurParam &oParam1, CATSurParam &oParam2);

  //-----------------------------------------------------------------------
  // AvoidExtremities
  // 
  // Dans l'operateur, on ne tient pas compte des points extremites si 
  // iOption = 1
  //-----------------------------------------------------------------------
  
  void AvoidExtremities(CATLONG32 iOption);

  //-----------------------------------------------------------------------
  //- Private data
  //-----------------------------------------------------------------------
private :
  CATSoftwareConfiguration * _Config;
  CATEdgeCurve * _EdgeCurve;
  CATCrvLimits _ECLimits;
  CATPCurve *_PCrv[2];
  CATSurface * _Surface[2];
  CATSurParam * _SurParam0, * _InitSurParam0;
  CATSurParam * _SurParam1, * _InitSurParam1;
  CATCrvParam * _InitECParam;
  CATLONG32 _NbPoints, _IndexPoints;
  CATPointDiag *_DiagPoint;
  double _Offset[2];
  CATSurLimits _Lim[2];
  CATSideToExtrapolate _SideSpecified[2];
  CATSurLimits _BoxOnSurface[2];
  CATExtrapolDiag _Diag[2];
  CATSideToExtrapolate _Side[2];
  CATMathVector2D _VectorEstimation[2];
  CATLONG32 _IsoparUMin[2], _IsoparUMax[2], _IsoparVMin[2], _IsoparVMax[2];  // = 0 si surface non fermee et aucune isopar degeneree
                                                                        // = 1 si isopar degeneree ou surface fermee suivant cette isopar
  CATLONG32 _ReachClosedBoundaryU[2], _ReachClosedBoundaryV[2],
    _ReachSpecifiedBoundary[2]; 
  double _Resolution;

  CATLONG32 _AvoidExtremities;
  //
  // IsOutsideOrNeedsAnExtrapol
  // Teste si le point courant (iCurrentPoint) est dans les limites du domaine
  // sur une surface donnee (iSurfaceIndex)
  // Renvoie si on doit extrapoler cette surface et de quel cote.
  //
  CATBoolean  IsOutsideOrNeedsAnExtrapol(CATLONG32 iSurfaceIndex,
    CATLONG32 iCurrentPoint,
    const CATMathIntervalND &iDomain,
    double    *iInput,
    double    *iIosys,
    double     oWeight[2],
    CATLONG32       oPosition[2],
    short      &oNeedsToExtrapol,
    short * iReachBoundary = NULL);

  // 
  // CreateStartingPoints
  // Methode pour creer les points de l'edge curve desquels on lance 
  // un pas de newton
  //
  void CreateStartingPoints();

  //
  // GetBoxAfterOffSet
  // Remplit les boites d'encombrement des deux PCurves sur les deux
  // surfaces apres offset
  //
  void GetBoxAfterOffset();

  //
  // TestBoundaries
  // Teste si les surfaces sont fermees ou si une de leurs isopars 
  // est degeneree
  //
  void TestBoundaries(double * Dom);

  //
  // TryDichotomy
  // iReachedPoint is latest non-inside Newton point.
  // If iReachedPoint crosses a coordinate of iDom which has been detected
  // closed by TestBoundaries the method returns 1: a dichotomy is necessary
  // to know with precision if homotopy solution reach a boundary.
  // The method returns 0 otherwise.
  //
  short TryDichotomy(const double * iReachedPoint, const double * iDom);

  //
  // SolveByDichotomy
  // Given iHomotopySystem initialiazed in Run, try to converge from ioSolution point on best
  // solution point thanks to a dichotomy technique.
  // If given, oOffsetStop will contain the 2 offset values, respectively to the 2 surfaces, on
  // which dichotomy stopped.
  //
  void SolveByDichotomy(CATSystem6x6s & iHomotopySystem, double * ioSolution, const CATMathIntervalND & iDomain,
                        CATMathNxNFullMatrix & iJacobian, double * oOffsetStop = NULL);

  //
  // SetLimitsWithValidMaxBox
  // Relimit limits of surface 'iSurfNumber' by maximum limits obtained by GetSurfaceValidMaxBox, on the sides
  // on which is it allowed to extrapolate.
  //
  void SetLimitsWithValidMaxBox(const CATLONG32 iSurfNumber);

  CATBoolean _Dicho_Debug_Traces;
  CATLONG32  _LimitSpecified[2];

  // SafeSetLimits:
  //
  // When activated, this mode allows to relimit given limits to SetLimits a posteriori, ie. during
  // RunOperator() where we have relevant points (= starting points).
  // This is safer than standard relimitation in SetLimits because if given limits are
  // MaxLimits, we take an arbitrary param. at center of this domain and GetSurfaceValidMaxBox
  // method could return a domain that does not even contain starting points !
  //
  // NB.: this mode is activated by default in constructor for level higher than
  //      ExtrapolSurfacesForOffset_TryDichotomy versionning variable.
  CATBoolean _SafeSetLimits;


//========================================================================
// Gestion CGMReplay
//========================================================================
protected:
  friend class CATGeoStreamFactory; 

  // private static data
  static CATString _OperatorId;
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

  CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
  virtual void WriteInput(CATCGMStream  & os);
  virtual void WriteOutput(CATCGMStream & os);
	virtual CATBoolean ValidateOutput(CATCGMStream& ioStream, CATCGMOutput & os,int VersionNumber=1);
  virtual void Dump( CATCGMOutput& os ) ;
  virtual void DumpOutput(CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
  virtual void DumpOutput(CATCGMOutput& os);
  virtual CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & os);
};


ExportedByY30C3XGG CATExtrapolSurfacesForOffset * CreateExtrapolationForOffset(CATGeoFactory * iFactory,
                                                                               CATSoftwareConfiguration * iConfig,
                                                                               CATEdgeCurve * iEdgeCurve, const CATCrvLimits & iEdgeCurveLimits,
                                                                               CATSurface * iSurface1, CATSurface * iSurface2,
                                                                               double iOffset1, double iOffset2,
                                                                               CATSkillValue iMode = BASIC);

ExportedByY30C3XGG void Remove( CATExtrapolSurfacesForOffset * ExtrapolOper );

#endif
























