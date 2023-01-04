/*-*-c++-*-*/
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATExtrapolNurbsSurface :
// Class for extrapoling a NurbsSurface beyond a box.
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// 10/04/18 JSX Archi et Heritage
//              ajout de InitRunInCtor 
//              ajout d'un constructeur pour la classe fille, qui ne fait pas de calcul
//              repere JSX_Clean_xxx pour faire vibre le code
//=============================================================================

#ifndef CATExtrapolNurbsSurface_H 
#define CATExtrapolNurbsSurface_H 

#include "Y30C3XGG.h"
#include "CATMathDef.h"
#include "CATCGMVirtual.h"
#include "CATCreateExtrapol.h"
//#define JSX_Clean_1

class CATUtilExtrapolNurbsSurface;
class CATKnotVector;
class CATNurbsSurface;
class CATGeoFactory;
class CATMathGridOfPoints;
class CATMathVector2D;
class CATMathVector;
class CATSurParam;
class CATSoftwareConfiguration;

#include "CATFrFNurbsBipar.h"

class ExportedByY30C3XGG CATExtrapolNurbsSurface : public CATCGMVirtual
{
public:
  //-----------------------------------------------------------------------
  //- Public Methods
  //-----------------------------------------------------------------------
  CATExtrapolNurbsSurface (CATGeoFactory            * iFactory, 
                           CATSoftwareConfiguration * iConfig,
                           CATNurbsSurface          * ioSur,
                           const CATMathVector2D    & iDirection,
                           const CATSurParam        & iParamOnSur);
  //Deprecated
  CATExtrapolNurbsSurface (CATGeoFactory            *iFactory, 
                           CATNurbsSurface          * ioSur,
                           const CATMathVector2D    & iDirection,
                           const CATSurParam        & iParamOnSur);
  //used only by CATNewExtrapolSurface
  CATExtrapolNurbsSurface (CATGeoFactory            * iFactory, 
                           CATSoftwareConfiguration * iConfig,
                           CATNurbsSurface          * ioSur );


  ~CATExtrapolNurbsSurface();
  
  void Run ();

  
protected:
  //-------------------------------------------------------------------------
  // Protected methods for extrapolation
  //-------------------------------------------------------------------------
  void ReExtrapolation();
  void FunctionsExtrapolation(const CATLONG32 &ExtraU, const CATLONG32 &ExtraV);

  void C2BezPointsOnSide(const CATLONG32 &iSide, double &oAlpha, double &oBeta, double *oCPs);

  void GetParamForC2(const CATLONG32 &iSide, double *oParamForC2, double &oParamFin);

  void C2BezPoints(const double &alpha, const double &beta, 
                   double *TargetP, double *TargetW, double *TargetD,    
                   double *oP0, double *oP1, double *oP2, 
                   double *oP3, double *oP4, double *oP5, double *oP6);

  void TargetDerivatives(const CATLONG32 &Degree, double *CPs, 
                          double *Weights, double *u, double *oFnSDerivatives);

  void C2BezPointsOnCorner(const CATLONG32 &iSide, 
                           const double &Alpha, const double &Beta,
                           double *ExtrCPs, const CATLONG32 &iAdr, CATLONG32 *DirDec, const CATLONG32 &DirExtra);

  void ComputePlanarVertices(double *ExtrCPs, const CATLONG32 &iAdr, CATLONG32 *DirDec);

  //remplie _TabOfNurbs avec toutes les surfaces servant a l'extrapolation
  void FillArrayOfNurbs(CATKnotVector *KnotVectorU, CATKnotVector *KnotVectorV,
                        double        *ExtrCPs      , double *ExtrWeights,
                        CATMathGridOfPoints &LocGrid, double *LocWeights,
                        const CATLONG32 FirstVertexU, const CATLONG32 FirstVertexV,
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
  void InitRunInCtor(const CATMathVector2D & iDirection,
                     const CATSurParam & iParamOnSur);

   //==========================
   // DATA
   //==========================
protected:
  //-----------------------------------------------------------------------
  //- Protected data
  //-----------------------------------------------------------------------
  CATGeoFactory            * _Factory;
  CATSoftwareConfiguration * _SoftwareConfiguration;
  CATNurbsSurface          * _Sur;
  double                     _LengthU;
  double                     _LengthV;

//private:
protected:
  //-----------------------------------------------------------------------
  //- Private data
  //-----------------------------------------------------------------------
  CATUtilExtrapolNurbsSurface ** _TabOfNurbs;
  CATFrFNurbsBipar **_TabOfNurbsBipar;

  CATKnotVector * _KnotVectorU;
  CATKnotVector * _KnotVectorV;
  CATLONG32       _IsRational;
  double        * _Vertices;
  double        * _Weights;

  //La surface a-t'elle deja ete extrapole?
  CATLONG32       _IsExtrapolatedU; 
  CATLONG32       _IsExtrapolatedV;

  //La surface doit etre extrapole
  CATLONG32       _ExtrapolU;
  CATLONG32       _ExtrapolV;
  CATLONG32       _ReExtrapol;

  //Donnees de la surface initiale
  double          _Alpha[4];
  double          _Beta[4];

  //Degre de la Nurbs extrapolee
  CATLONG32       _TargetDegreeU;
  CATLONG32       _TargetDegreeV;

  //Config de la surface en entree : enumeration de tous ses problemes,...
  CATLONG32            _Config[4];
};


//-----------------------------------------------------------------------
//- Global functions
//-----------------------------------------------------------------------
#ifdef JSX_Clean_1
#else
ExportedByY30C3XGG CATExtrapolNurbsSurface * CreateExtrapolation(CATGeoFactory *iFactory, CATNurbsSurface * ioSur, const CATMathVector2D & iDirection, const CATSurParam & iParamOnSur);
ExportedByY30C3XGG CATExtrapolNurbsSurface * CreateExtrapolation(CATGeoFactory *iFactory, CATNurbsSurface * ioSur, const CATMathVector   & iDirection, const CATSurParam & iParamOnSur);
#endif
ExportedByY30C3XGG void Remove(CATExtrapolNurbsSurface * ExtrapolOper);
#endif
