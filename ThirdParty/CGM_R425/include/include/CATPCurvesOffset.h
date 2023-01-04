/*-*-C++-*-*/
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
//
// Given a couple of CATPCurves, this operator creates a surface
// bissectrice 
// Only for CGM internal USE !!
//
// sdp 15apr02: precisions sur les specs de l'operateur
// Les inputs iStartLength et iEndLength indiquent la zone utile de la surface
// bissectrice selon la direction orthogonale aux PCurves supports. L'orientation 
// de normale de reference est celle de la premiere PCurve. Par exemple,
// iStartLength=0. et iEndLength=2. signifie que, etant donne un point sur la 
// PCurve 1 et son homologue sur la PCurve 2, la zone utile correspondante sur
// la surface bissectrice est comprise entre le point considere et ce point +
// 2.*la normale moyenne normee _orientee comme la normale sur la premiere PCurve_.
//
// iStartLength et iEndLength ont incidemment pour effet de determiner les
// CurrentLimits des objets crees par l'operateur mais dans la mesure ou on
// souhaite s'affranchir des CurrentLimits, il convient de ne pas le considerer
// comme une spec de l'operateur. Une nouvelle methode CreateRuleLine a ete 
// creee, renvoyant deux CrvParam sur l'objet cree, correspondant a iStartLength
// et iEndLength. La methode CreateRuleLine sans CrvParam en valeur de retour
// est obsolete.
// 
//
//=============================================================================
//   /07/00 FBZ Creation
// 12/03/20 Q48 Headers etc for math versioning
//=============================================================================
#ifndef CATPCurvesOffset_H 
#define CATPCurvesOffset_H

// ExportedBy
#include "Y30C3XGG.h"

// Base class
#include "CATGeoOperator.h"

// C++11
#include "CATGeoOpVirtual.h"

#include "CATSkillValue.h"
#include "CATMathDef.h"
#include "CATMathInline.h"
#include "CATListOfCATSurfaces.h"
#include "CATCrvLimits.h"
#include "CATMathPoint.h"
#include "CATMathVector.h"
#include "CATString.h"
#include "CATGeoOpTimer.h"
#include "CATSurLimits.h"
#include "CATListOfDouble.h"

class CATEdgeCurve;
class CATPCurve;
class CATPLine;
class CATSurface;
class CATGeoFactory;
class CATCrvParam;
class CATSurParam;
class CATMathSetOfPointsND;
class CATSoftwareConfiguration;
class CATPointOnEdgeCurve;

//-----------------------------------------------------------------------------
class ExportedByY30C3XGG CATPCurvesOffset : public CATGeoOperator
{
public :
	
	//-----------------------------------------------------------------------------------------------
	// Constructor
	//-----------------------------------------------------------------------------------------------
	CATPCurvesOffset(CATGeoFactory            * iFactory,
                         CATSoftwareConfiguration * iConfig,
                         CATEdgeCurve             * iEdgeCurve,
                         CATPCurve                * iPCrv1,
                         CATPCurve                * iPCrv2,
                         CATCrvLimits             * iLimitsOnPCrv1,
                         CATCrvLimits             * iLimitsOnPCrv2,
                         double                     iStartLength,
                         double                     iEndLength);
  
	//-----------------------------------------------------------------------------------------------
	// Destructor
	//-----------------------------------------------------------------------------------------------
	~CATPCurvesOffset() ;
	
	//-----------------------------------------------------------------------------------------------
	// Run
	//-----------------------------------------------------------------------------------------------
	int                     RunOperator() ;
	
    //-----------------------------------------------------------------------------------------------
	// SetPreviousSurface
	// ------------------
	// you can call many times this method for a list of CATSurface.
	//-----------------------------------------------------------------------------------------------
	void                     SetPreviousSurface(CATSurface * iPreviousOne);
	
	//-----------------------------------------------------------------------------------------------
	// CreateRuleLine
	// --------------
	// creates a PLine on the surface from iParamOnInitialCrv 
  // also returns the Start and End CrvParams on the created PLine corresponding
  // to the iStartLength and iEndLength inputs of the operator
	//-----------------------------------------------------------------------------------------------
  CATPLine * CreateRuleLine(const CATCrvParam & iParamOnInitialCrv,
                            const CATPCurve * iPCurve,
                            CATCrvParam & oStartParam,
                            CATCrvParam & oEndParam);

  //
  // deprecated
  //
  CATPLine *              CreateRuleLine(const CATCrvParam &iParamOnInitialCrv,
		const CATPCurve * iPCurve) ;
	
	//-----------------------------------------------------------------------------------------------
	// GetSurface
	// ----------
	// returns the surface created by the operator	 (directional or bisectric surface)
	//-----------------------------------------------------------------------------------------------
	CATSurface *             GetSurface() ;
	
	//-----------------------------------------------------------------------------------------------
	// GetSurParamFromCrvParam
	// -----------------------
	// get the corresponding SurParam on the surface
	// from a CrvParam on one of the PCurve.
	//-----------------------------------------------------------------------------------------------
	void                     GetSurParamFromCrvParam(const CATCrvParam &iParam, const CATPCurve * iPCurve,
		CATSurParam &oParam) ;
	
	//-----------------------------------------------------------------------------------------------
	// GetUVBox
	// --------
	// get the uv box of the projection of the pcurve on the result surface.
	//-----------------------------------------------------------------------------------------------
    void                     GetUVBox(CATPCurve * iPCurve, const CATCrvLimits & iLim, CATSurLimits &oLimits) ;
	
	//-----------------------------------------------------------------------------------------------
	// GetOrientation
	// --------------
	// returns the sign of the determinant ( Derivative of the PCurve,
	//									 Normal to the surface,
	//									 Normal to the directional surface) 
	//                   at the StartParam of the PCurve.
	//-----------------------------------------------------------------------------------------------
	short                     GetOrientation(const CATPCurve * iPCrv);
	
	//-----------------------------------------------------------------------------------------------
	// IsLengthValid !!Method not yet implemented!!
	// -------------
	// tests if there is no twist on the GenericRuledSurface with these values 
	// of start and end length.
	// 
	// iStartLength < iEndLength
	//-----------------------------------------------------------------------------------------------
	CATBoolean               IsLengthValid(double iStartLength, double iEndLength) ;
	
	
  //-----------------------------------------------------------------------------------------------
  // SetChoiceOfSurface
  //
  // iPCurveToChoose = 0 On passe dans le code de choix par defaut
  //                   1 On cree une surface directionnelle sur la 1ere PCurve
  //                   2    ""                           ""        2eme   ""
  //                   3 On cree une surface bissectrice
  //
  //-----------------------------------------------------------------------------------------------
  void                     SetChoiceOfSurface(CATLONG32 iPCurveToChoose);
  CATLONG32 GetChoiceOfSurface();


  //-----------------------------------------------------------------------------------------------
  // Evaluation du Point 3D, du vecteur normal pour l'appel ulterieur a SetConstraintsAtExtremities
  // On peut en option demander les vecteurs derives pour assurer la contrainte G1.
  //-----------------------------------------------------------------------------------------------
  static void EvalConstraintsData(const CATPCurve * iPCurve, const CATCrvParam &iParam,
                                  CATMathPoint & ioPoint, CATMathVector & ioNormalVector,
                                  CATMathVector * ioDeriv=0, CATMathVector * ioNormalDeriv=0);

  //-----------------------------------------------------------------------------------------------
  // Test de relachement des contraintes G0 - Mode "Alpha user G0"
  //
  // Prise en compte d'un angle max. assurant le respect de la jointivite G0 le long de la
  // surface bissectrice, suivant la normale a la PCurve
  //
  //-----------------------------------------------------------------------------------------------
  void SetAlphaUserG0(const double iAlphaUserG0);

  //-----------------------------------------------------------------------------------------------
  // Test de relachement des contraintes G1 - Mode "Alpha user G1"
  //
  // Prise en compte d'un angle max. assurant le respect apres offset de la jointivite G0 de la surface
  // construite avec les surfaces bissectrices situees de part et d'autre, malgre le relachement des
  // contraintes G1.
  //
  // N.B. : Le relachement des contraintes G1 est souhaitable (contraintes trop "fortes" en general)
  //        mais ne peut avoir lieu que dans des situations particulieres pour lesquelles le respect 
  //        des contraintes G0 suffisent.
  //-----------------------------------------------------------------------------------------------
  void SetAlphaUserG1(const double iAlphaUserG1);


  //-----------------------------------------------------------------------------------------------
  // Calcul du poids associe aux contraintes de deformation. On privilegie la contrainte associee
  // a l'edge la plus courte. La somme des poids est 1.
  //-----------------------------------------------------------------------------------------------
  static void ComputeConstraintWeights(CATEdgeCurve * iEC[2],
                                       CATPointOnEdgeCurve * iStartPOEC[2],
                                       CATPointOnEdgeCurve * iEndPOEC[2],
                                       double oWeight[2]);


 /**
  *Set target point and vector at an extremity.
  *iStartOrEnd: 0 for start, 1 for end (orientation defined by the first PCurve)
  * sdp 17oct02- added two optional vectors for 1st order deformation
  */
  void SetConstraintsAtExtremities(const CATMathPoint & iPoint, const CATMathVector & iNormalVector, short iStartOrEnd,
                                   const CATMathVector * iDeriv=0, const CATMathVector * iNormalDeriv=0);


  //-----------------------------------------------------------------------------------------------
  // Pour demander que la surface creee soit non pas un peigne de normales, mais le cone engendre
  // par l'edge curve et le sommet iApex.
  //-----------------------------------------------------------------------------------------------
  void ForceThroughPoint(const CATMathPoint & iApex);

  // ajout d'une liste de points (PcrvParam globaux sur PCrv0) sur lesquels l'evaluation est obligatoire
  void AppendPointsToForceEvalOn(CATListOfDouble &iPointsToForceEvalOn);

  //-----------------------------------------------------------------------------------------------
  // Pour imposer une surface (cree hors de l'operateur), qui n'est pas necessairement le peigne des
  // normales. La seule contrainte est que les PCurves inputs soient posees sur la surface (limitee
  // par les  SurLimits passees en input) a la resolution pres. Dans ce mode, la spec de CreateRuleLine
  // devient: intersection du plan normal a l'edge curve avec la surface imposee; Start et End restent
  // relatifs a l'orientation de normale de la premiere PCurve.
  // *** AUJOURD'HUI SEULS SONT ACCEPTES LES PLANS *** En effet, la spec de CreateRuleLine doit etre
  // revue pour les cas non-plans.
  //-----------------------------------------------------------------------------------------------
  void ForceSurface(CATSurface * iSurf, const CATSurLimits & iSurLimits);

  //------------------------------------------------------------------------------------------------
  // Option utilisee par le code de creation des surfaces directionnelles du Thick
  // Elle indique au PCurvesOffset d'essayer de faire des surfaces directionnelles (et donc d'oublier
  // les contraintes) s'il le peut
  // Valeur par defaut : FALSE.
  //------------------------------------------------------------------------------------------------
  INLINE void SetTryToMakeCanonicalIfPossible(short iCanonical) {_TryToMakeCanonicalIfPossible = iCanonical;}
 

// private methods
private:
  CATLONG32 ReportCrvSurBis(const CATCrvParam &iParam, const CATPCurve * iPCurve,
    CATSurParam &oParam) const;
  CATLONG32 ReportCrvSurDir(const CATCrvParam &iParam, const CATPCurve * iPCurve,
    CATSurParam &oParam) const;
  CATLONG32 ReportCrvSurCone(const CATCrvParam &iParam, const CATPCurve * iPCurve,
    CATSurParam &oParam) const;
  CATLONG32 ReportCrvSurTabCyl(const CATCrvParam & iParam, const CATPCurve * iPCurve,
    CATSurParam & oParam) const;
  void ReportCrvSur_ForceThroughPoint(const CATCrvParam & iParam, const CATPCurve * iPCurve,
    CATSurParam & oParam) const;
	
	// Choix du type de surface a creer suivant les PCurves donnees en entree
	void ChooseTypeOfSurface();	
	void ChooseCanonicSurface(CATLONG32 iIndex);
	void CreateSurface();
	void CreatePlane();
	void CreateCylinder();
	void CreateCone();
  void CheckForceThroughPoint();

  // post-pro pour trouver une surface canonique
  void CreateCanonicalSurface();

  //-----------------------------------------------------------------------------------------------
  // SimplifyEdgeCurve
  //
  // Simplification des Edge Curves fats pour resoudre les problemes d'extrapolation des surfaces 
  // bissectrices
  //
  // Ex. probleme d'HomotopyCrvSur : extrapolation de la surf. biss. impossible car _EdgeCurve
  // contient une PLine posee sur un fillet en pointe
  //
  // Rq. :    1- Methode de simplification versionnee (PCurvesOffset_SimplifiedEdgeCurve)
  //             appelee en debut de Run()
  //
  //          2- _NewSurface (surface bissectrice) pointe sur _EdgeCurveLight et non plus sur
  //             _EdgeCurve
  //          
  //          3- Le parametrage de la surface bissectrice est lie a celui de _Pcrv[0],
  //             SimplifyEdgeCurve() ne modifie donc pas le parametrage des surf. biss.
  //             ---> GetSurParamFromCrvParam est iso-comportement
  // 
  //-----------------------------------------------------------------------------------------------
  CATBoolean SimplifyEdgeCurve();
  CATEdgeCurve * _EdgeCurveLight; // ECrv simplifiee
  CATLONG32 _IsEdgeCurveLightGiven;
  
  double ComputeTrueGap();
	
	enum  TypeOfSurf 
    { DirectionalSurface,
      BisectorSurface,
      Plane,
      Cone,
      Cylinder,
      TabCyl,
      ForcedSurface };
	TypeOfSurf                _Type;
	
	CATGeoFactory *           _Factory;
  CATSoftwareConfiguration *_Config;
	CATEdgeCurve *            _EdgeCurve;
	CATPCurve     *           _Pcrv[2];
	const CATSurface *        _Surf[2];
	CATSurface    *           _NewSurface;
	CATLISTP(CATSurface)      _PreviousSurface;
	double                    _Angle;
	double                    _StartLength;
	double                    _EndLength;
  CATCrvLimits              _Limits[2];
  CATMathSetOfPointsND *    _Mapping[2];
  CATLONG32                 _IndexPcrv;
  CATLONG32                 _IsChoosed,_IsEdgeCurveGiven;
  CATMathPoint              _ConstrainedPointAtExtremities[2];
  CATMathVector             _ConstrainedVectorAtExtremities[2];
  CATMathVector             _ConstrainedPointDeriv[2];
  CATMathVector             _ConstrainedNormalDeriv[2];
  short                     _IsExtremityConstrained[2]; // 0 = no constraint
                                    // 1 = 0th-order constraint
                                    // 2 = 1st-order constraint
  short                     _IsExtremityConstrainedInput[2]; // Copie non modifiee de l'entree
  // car le _IsExtremityConstrained est modifie a certains points dans l'algo..

  CATBoolean                _ForceThroughPoint;
  CATMathPoint              _Apex;

  CATSurface              * _ForcedSurf;
  CATSurLimits              _ForcedSurfLimits;

  short                     _TryToMakeCanonicalIfPossible;

  CATListOfDouble           _PointsToForceEvalOn;

  double _truegap;

  // cqi 14dec04 - Alpha user G1 & G0
  // G0
  double _AlphaUserG0;
  short _IsAlphaG0Set;
  // G1
  double _AlphaUserG1;
  short _IsAlphaG1Set;
  
  
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
  void DumpOutput(CATCGMOutput & os);
  virtual void DumpOutput(CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
  virtual CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & os);
};
 
//-----------------------------------------------------------------------------
ExportedByY30C3XGG
CATPCurvesOffset * CreatePCurvesOffset(CATGeoFactory * iFactory,
                                       CATSoftwareConfiguration * iConfig,
									   CATEdgeCurve  * iEdgeCurve,
									   CATPCurve     * iPCrv1,
									   CATPCurve     * iPCrv2,
									   CATCrvLimits  * iLimitsOnPCrv1,
									   CATCrvLimits  * iLimitsOnPCrv2,
									   CATLength       iStartLength,
									   CATLength       iEndLength);


ExportedByY30C3XGG
void Remove(CATPCurvesOffset *&iOperator);

#endif
