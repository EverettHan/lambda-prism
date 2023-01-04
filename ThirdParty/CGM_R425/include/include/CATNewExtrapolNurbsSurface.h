/*-*-c++-*-*/
// COPYRIGHT DASSAULT SYSTEMES 2002
//=============================================================================
//
// CATNewExtrapolNurbsSurface :
// Class for extrapoling a NurbsSurface beyond a box.
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// 10/04/18  JSX flag JSX_FactorizeExtrapol
//           Reorganisation/Heritage pour partage avec CATExtrapolNurbsSurface
//
#define JSX_FactorizeExtrapol
// 15/03/19  JSX remove lines deactiavted by  JSX_FactorizeExtrapol
//
#ifndef CATNewExtrapolNurbsSurface_H 
#define CATNewExtrapolNurbsSurface_H 

#include "Y30C3XGG.h"

#include "CATMathDef.h"


#include "CATExtrapolSurface.h"
#include "CATCGMVirtual.h"

class CATKnotVector;
class CATNurbsSurface;
class CATGeoFactory;
class CATMathSetOfPoints;
class CATMathVector2D;
class CATSurParam;
class CATFrFNurbsBipar;
class CATSoftwareConfiguration;

//#define DBGBigExtrapol
#ifdef DBGBigExtrapol
#include "CATListOfInt.h"
#include "CATCGMOutput.h"
#include "CATStackTrace.h" 
#endif
#ifdef DBGBigExtrapol
  static int NbExtrapol=0;
  static CATListOfInt ListOfTag;
  static CATListOfInt ListOfNbExtrapol;
#endif

//#define CATDebugODT 
#ifdef CATDebugODT
#include <fstream.h>
#endif


#include "CATExtrapolNurbsSurface.h"
class ExportedByY30C3XGG CATNewExtrapolNurbsSurface  : public CATExtrapolNurbsSurface
{
public:
  //-----------------------------------------------------------------------
  //- Public Methods
  //-----------------------------------------------------------------------
  CATNewExtrapolNurbsSurface (CATGeoFactory *iFactory,
                              CATNurbsSurface * ioSur,
                              CATExtrapolSurface::CATSurfaceSide iSurfaceSide,
                              const CATMathVector2D & iDirection,
                              const CATSurParam & iParamOnSur,
                              CATSoftwareConfiguration * iConfig);
  
  ~CATNewExtrapolNurbsSurface();

#define JSX_RemoveSetContinuity JSX150319
#ifndef SetContinuity
  void SetContinuity(CATLONG32 iContinuity);
#endif

  // iLevel = 0 : Ancienne methode d'extrapolation.
  // iLevel = 1 : Ancienne extrapolation amelioree,
  // iLevel = 2 : Appel a l'extrapolation bord par bord ( 4 fois, VMin, VMax, UMin, UMax),
  // iLevel = 3 : Appel au bord actif ( depend de la Direction )
  void SetLevelOfExtrapolation(CATLONG32 iLevelOfExtrapolation) ;

  // Extrapolation speciale pour une nurbs provenant d'une subdivision
  // Le type d'extrapolation, ainsi que lq parametrisation necessite un travail particulier
  // Ne pas appeler : Contacter ANR
  void SetSpecialSubdiv(CATBoolean iMode = FALSE) ;

  void Init() ; 
  void Run ();
  
  void QuickRun ();
  
  void GetMaxLongOfExtrap(double &oMaxLongExtr) ;
protected:
  //-------------------------------------------------------------------------
  // Protected methods for extrapolation
  //-------------------------------------------------------------------------
  void Extrapolation();
  void ReExtrapolation();
  void FunctionsExtrapolation(const CATLONG32 &ExtraU, const CATLONG32 &ExtraV);
  
  
  void Recherche_Longueur(CATFrFNurbsBipar *iMF, CATLONG32 iSide, CATKnotVector *KnotVectorU, CATKnotVector *KnotVectorV,
                          double *ExtrCPs, double &oLong_Max) ;
  void C2BezPointsOnSide_Bis(CATFrFNurbsBipar *iMF, CATLONG32 &iSide, double LongU, double LongV, 
                             CATKnotVector *KnotVectorU, CATKnotVector *KnotVectorV,
                             double *oCPs, CATLONG32 &oIsOK);
  void C2BezPointsOnSide(const CATLONG32 &iSide, double &oAlpha, double &oBeta, double *oCPs);
  void GetParamForC2(const CATLONG32 &iSide, double *oParamForC2, double &oParamFin);
  
  void C2BezPoints(const double &alpha, const double &beta, 
                   double *TargetP, double *TargetD,    
                   double *oP0, double *oP1, double *oP2, 
                   double *oP3, double *oP4, double *oP5, double *oP6);
  
  void TargetDerivatives(const CATLONG32 &Degree, double *CPs, 
                         double *u, double *oFnSDerivatives);
  
  void C2BezPointsOnCorner(const CATLONG32 &iSide, const double &Alpha, const double &Beta,
                           double *ExtrCPs,const CATLONG32 &iAdr, CATLONG32 *DirDec, const CATLONG32 &DirExtra);
  
  void ComputePlanarVertices(double *ExtrCPs, const CATLONG32 &iAdr, CATLONG32 *DirDec);

  void TargetDirection(double *TargetP, double *TargetD,
                       double &iLengthMin, double &iCurAlpha, double &oAlpha) ;
  
  //remplie _TabOfNurbs avec toutes les surfaces servant a l'extrapolation
  void FillArrayOfNurbs(CATKnotVector *KnotVectorU, CATKnotVector *KnotVectorV,
                        double *ExtrCPs,
                        CATMathSetOfPoints &LocGrid,double *LocWeights,
                        const CATLONG32 FirstVertexU,const CATLONG32 FirstVertexV,
                        const CATLONG32 Rank);
  
  //method which fill the _Config array (private data).
  //This array describe all the "problems" of the surface to extrapol :
  //singularity, twist,...
  void CheckSurface();
  
  //directly called by CheckSurface().
  CATLONG32 IsTriangular(CATLONG32 iSide) const;
  
  private:
  //directly called by CheckSurface().
  CATLONG32 IsClosedAndG1(CATLONG32 iSide, CATLONG32& iDiagnostic) const;

  //==================================================
  // DATA
  //==================================================
protected:
  //-----------------------------------------------------------------------
  //- Protected data
  //-----------------------------------------------------------------------
  CATMathVector2D _Direction;

private:
  
  //-----------------------------------------------------------------------
  //- Private data
  //-----------------------------------------------------------------------
  CATExtrapolSurface::CATSurfaceSide  _SurfaceSide ;
  CATSurParam _ParamOnSur ;
  CATLONG32 _ContinuityOfExtrapol;
  double _MaxLongExtr;
  CATLONG32 _LevelOfExtrapolation ;
  //CATFrFNurbsBipar **_TabOfNurbsBipar;
  int             _Dim; //3==Nupbs, 4==Nurbs
  CATBoolean _ModeSubdiv ;
  CATLONG32 _CASEOfExtrapol ;
  CATLONG32 _CASEOfsurface ;
};

#endif
