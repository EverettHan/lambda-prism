#ifndef CATMATHDIRECTMINIMIZERXY_h
#define CATMATHDIRECTMINIMIZERXY_h
//=============================================================================
//
// CATMathDirectMinimizerXY
//
//=============================================================================
//
//=============================================================================
// Class used to minimize functions of two variables as an alternative to CATMathMinimizeXY
//
// This class includes an implementation of the Direct Method Minimization :
//
//        - The Direct Method Minimization is an algorithm for global minimization of C0 objective
//          functions with bounds constraints (Direct Method does not require derivatives)
//
//        - For further details :
//          cf. article "Lipschitzian Optimization Without Lipschitz Constant" D. R. Jones
//=============================================================================
//
// 29/05/07 NLD XScale: Ajout du bloc de tolerances en argument du constructeur
// 11/01/08 NLD Ajout _OKScaleReviewed et SetOKScaleReviewed() pour exclusion du controle des attributs deja certifies
// 29/01/09 NLD Ajout _Config, ajout SoftwareConfiguration en argument du constructeur
// 28/04/10 NLD Nomenclature des #define partages:
//              CATMathDirectMinimizerXY_Direct_Default_Sampling remplace DIRECT_DEFAULT_SAMPLING
//              CATMathDirectMinimizerXY_Direct_Alloc_Cos_Array  remplace DIRECT_ALLOC_COS_ARRAY
// 20/07/11 NLD Ajout _CGMLevel, AddMinimum() et LocalMinimizationOnAllInits()
// xx/09/16 JSX Elagage pour comprehnesion
//              Passage en private ou protected d'un maximum de focntions ( a reouvrir ensuite si necessaire)
//              Caslcul de DCT en fonction externe a la classe
//              Rassemblement et tri de données
// 25/04/17 PKC Suppression des méthodes FindDangerousRectangles et CheckIfDangerous inutilisées et mal codées
//=============================================================================

#include "CATBoolean.h"

#include "CATMathSetOfPointsND.h"
#include "CATMathSetOfLongs.h"
#include "CATMathFunctionXY.h"
#include "CATMathDiagnostic.h"
#include "CATMathIntervalND.h"
#include "CATMathInterval2D.h"
#include "CATMathAttrList.h"
#include "CATMathAttrIntegerValue.h"

#include "YN000FUN.h"
#include "CATCGMVirtual.h"
#include "CATMathInline.h"

class CATSoftwareConfiguration;

// Fixe le sampling par defaut de la methode DIRECT
// -> choisir imperativement une valeur IMPAIRE
#define CATMathDirectMinimizerXY_Direct_Default_Sampling 9
// Taille du tableau de valeurs precalculees :
// CATMathDirectMinimizerXY_Direct_Alloc_Cos_Array = 0.5*CATMathDirectMinimizerXY_Direct_Default_Sampling*(CATMathDirectMinimizerXY_Direct_Default_Sampling - 1)
#define CATMathDirectMinimizerXY_Direct_Alloc_Cos_Array 36




class ExportedByYN000FUN CATMathDirectMinimizerXY : public CATCGMVirtual
   {

   public:

      CATMathDirectMinimizerXY( const CATMathFunctionXY  * iF,
                                const CATTolerance       & iTolObject,
                                CATSoftwareConfiguration * iConfig      );

      virtual ~CATMathDirectMinimizerXY();

      // Minimization on a domain
      // Attributes available: ==> see CATMathMinimizeXYParams.h

      CATMathDiagnostic Minimize( const CATMathInterval2D    & iDomain,
                                  CATMathSetOfPointsND       & roots,
                                  const CATMathAttrList      * iattributes=0 );

      // Xscale 
      void SetOKScaleReviewed() ;


   private :

      // Getting methods
      void GetDomainDimensions( double & lx , double & ux , double & ly , double & uy );

      // Setting and disabling methods
      void SetReferenceDomainDimensions( const CATMathInterval2D & Domain );
      void SetDomainDimensions( const CATMathInterval2D & Domain );
      void SetSampling( const CATLONG32 SampleX , const CATLONG32 SampleY );
      void SetSubdivision( const CATLONG32 NbSudivideX , const CATLONG32 NbSudivideY );
      void SetSamplingReference( const CATLONG32 NX , const CATLONG32 NY );
      void SetLimitValue( const double LimitValue );
      void SetTolForCst( const double TolForCst );
      void SetMaxIter( const CATLONG32 MaxIter );
      void SetSampleMax( const CATLONG32 SampleMAX );
      void SetSubdivideDomain();
      void DisableSubdivideDomain();

  // ------------------------------------------------------------------------------------------
  //
  // PRESAMPLING et INITIALISATION DU DIRECT GRAPH
  //
  // PreSampling regulier effectuant le calcul des valeurs de f sur une grille M*N
  // -> teste si la fonction est constante au sens de la tolerance _TolForCst
  //
  CATMathDiagnostic PreSampling( double * f , const CATLONG32 M , const CATLONG32 N );
  //
  // Initialise le graphe utile de DIRECT et les valeurs min/max a l'aide des valeurs de f calculees
  // par PreSampling
  //
  // Mode standard et Improved (ie. sans/avec _ImprovedStorage)
  //
  void InitializeDirectGraph        ( const double * f , const CATLONG32 M , const CATLONG32 N );
  void InitializeDirectGraphImproved( const double * f , const CATLONG32 M , const CATLONG32 N );

  // Reset du DIRECT GRAPH
  // Affecte des valeurs par defaut aux valeurs min/max et
  // a _IndexStart (en mode ImprovedStorage)
  //
  void ResetGraph();

  // Taille du DIRECT GRAPH
  // 
  INLINE CATLONG32 DirectGraphLength() const { return _DirectGraph.GetNumberOfPoints(); };

  // -------------------------------------------------------------------------------------------
  //
  // DIRECT ALGORITHM
  //
  // - GRAPHE FILTRE :
  //
  // Methode de filtre permettant d'obtenir les rectangles classes par tailles di croissantes
  // et realisant la plus petite valeur fi correspondante pour chaque taille existante dans le graphe
  // Ces points sont stockes avec leur 'index' et 'flag' associes :
  //
  // Soient i , j = 0 , ... , Length(_DirectGraph) - 1
  // Pour i_fixe : fj_min = min_{ dj = di } ( f( cj ) )  
  //
  // FiltGraph = ( dj , fj_min , index , flag )
  //
  // Mode standard & ImprovedStorage
  //
  void FilterGraph        ( CATMathSetOfPointsND & FiltGraph );
  void FilterGraphImproved( CATMathSetOfPointsND & FiltGraph );

  // - STEP 2 :
  // Methode effectuant la recherche dans _DirectGraph des rectangles potentiellement optimaux
  // au sens d'une valeur courante (_fmin ou _LimitValue) et de la tolerance absolue _Epsilon
  // Retourne la liste d'index correspondante dans 'SetOfPOpt'
  //
  void GetPotentiallyOptimal( CATMathSetOfLongs & SetOfPOpt );
   //
  // - STEP 4 & 5 & 6 :
  // Subdivision du rectangle potentiellement optimal d'indice index et MAJ de _DirectGraph :
  void DividingRectangles          ( CATLONG32 index );
  void DividingRectanglesNormalized( CATLONG32 index );
  void DividingRectangles_all      ( CATLONG32 index );  // fusion en cours des 2 precedantes

  //
  // SONDAGE DES ZONES OUBLIEES ET POTENTIELLEMENT DANGEREUSES
  //
  /*
  void FindDangerousRectangles( CATMathSetOfPointsND & SetOfDangerousRectangles );
  void CheckIfDangerous( double ci , double ci_p_1 , double fi , double fi_p_1
                       , double lambda , CATBoolean & DangerousOrNot );
  */


  // Determination des parametres de discretisations effectifs
  // et de l'approche a adopter : avec ou sans _SubdivideDomain
  //
  void SetDiscretizationMethodAndParameters( const double DCTIndicator );


  // NB . : dimensionnee dans le cadre du CATMaxOffset, methode GeneralCalc
  
  // -------------------------------------------------------------------------------------------
  //
  // MINIMISEUR 1D : Minimisation le long d'un isoparametre
  //
  // XOrY = FALSE : isopar en x
  // XOrY = TRUE : isopar en y
  //
  // attributes = permet de choisir la methode (BrentMethod par defaut)
  //
  CATMathDiagnostic Minimizer1D( const double            IsoParXOrY , 
                                 const CATBoolean        XOrY       ,
                                 const CATMathAttrList * attributes =0 );
  // -------------------------------------------------------------------------------------------
  // 
  // MINIMISEUR 2D
  
  // - Minimisation globale avec contraintes de bornes de type Direct Method
  //   Permet la recherche de point(s) d'init.
  //
  //   Le minimiseur opere sur le graphe utile
  //
  CATMathDiagnostic DirectMethodMinimization();
  
  //
  // - Minimisation locale 
  //   Permet la convergence sur le(s) point(s) d'init. stockes dans _SetOfInit

  // - Minimiseur 2D local avec contraintes de bornes combinant 2 approches :
  //         - Algorithme de Newton
  //         - et algorithme de Plus Profonde Descente (Steepest Descent, ou encore Simple Gradient Method)
  //
  // NB. : CODE DUPLIQUE et AMELIORE provenant de 'CATMathMinimizeXY'
  //
  CATMathDiagnostic LocalMinimization( const double xmin,  const double xmax 
                                     , const double ymin,  const double ymax 
                                     , double & ioX , double & ioY );

  //
  // Minimisation locale du meilleur point (global) ou de tous les points(AllInits) trouvé par Minimize
  //
  CATMathDiagnostic LocalMinimizationOnGlobalOptimum( CATMathSetOfPointsND & roots );
  CATMathDiagnostic LocalMinimizationOnAllInits     ( CATMathSetOfPointsND & roots );

  // -------------------------------------------------------------------------------------------
  //
  // GESTION DES POINTS D'INIT.
  //
  // Ajout d'un point. d'init. a _SetOfInit
  //
  CATBoolean AddInit( const double x , const double y , const double f );

  // -------------------------------------------------------------------------------------------
  //
  // GESTION DES RACINES.
  //
  // Ajout d'une racine a roots
  //
  void AddMinimum(double x, double y, CATMathSetOfPointsND & roots);

  // -------------------------------------------------------------------------------------------
  //
  // DEBUG
  //
  // Test sur la validite de la partition du domaine realisee par DIRECT
  //
  CATMathDiagnostic CheckArea( double & DeltaArea );



  private :

      // Initialisation de _SetOfInit et de roots
      //
      void Initialize( CATMathSetOfPointsND & SetOfInit );



  // -------------------------------------------------------------------------------------------
  //
  // DIRECT GRAPH
  //
  // Ajout d'un domaine au graphe de la methode DIRECT -> methode a utiliser a l'INTERIEUR du domaine ou sur un COIN
  void AddData     ( double c_x  , double c_y  , double dim_x , double dim_y , double f , double flag );
  // Ajout de 2 domaines rectangles -> methode a utiliser sur le BORD du domaine
  void AddRectangle( double ci_x , double ci_y , double delta , double dim ,
                     double fi_p_1 , double fi_m_1 , CATLONG32 XorY , double flag ); 

  // -------------------------------------------------------------------------------------------
  // Touls for Domains
  double NormOFDomain(double dx, double dy);

  HRESULT UpdateCurrentDom(const CATLONG32 index, const double *points  );


//
//===============================================================
//================================= DATA ========================
//===============================================================
//
 protected:
    // input
    const CATMathFunctionXY * _F;
    CATMathSetOfPointsND _SetOfInit;
    const CATTolerance & _TolObject;

 private:
    //
    // PARAMETRES GENERAUX DU MINIMISEUR
    //
    // Domaine de la fonction 
    double _lxRef , _uxRef , _lyRef , _uyRef;  // Domaine de reference 
    double _lx    , _ux    , _ly    , _uy;     // sous Domaine courant, utilisé par la DirectMethod

    // Tolerances 
    double _TolForCst;   // Pour fonctions constantes
    double _Epsilon;     // Absolue : determine l'amelioration potentielle esperee
    CATLONG32 _MaxIter;  // nombre d'etape de divission maximal, lors de la division d'un domaine "potentiellement optimal"

    CATLONG32 _NX , _NY;            // Parametres de sampling de l'appelant
    CATLONG32 _SampleX , _SampleY ; // Parametres de sampling optimises (aprers analyse par fft)

    // Autorise l'appel de la DirectMethod sur les domaines du domaine global en nombre _NbSubdivideX*_NbSubdivideY
    // cf. SetDiscretizationMethodAndParameters
    CATBoolean _SubdivideDomain;              // Activation du mode "SubdivideDomain"
    CATLONG32  _NbSubdivideX , _NbSubdivideY; // Nombre de division dans ce mode 

    // Mode "LimitValue"
    CATBoolean _UseLimitValue;  // Activation 
    double     _LimitValue;     // Valeur
    //

    //
    // PARAMETRES SPECIFIQUES A L'ALGORITHME DIRECT
    //
    // GRAPHE UTILE : tableau de dimension 7 representant le graphe de DIRECT
    //   { xi, yi  ,, di , F(xi,yi) , Flags }
    //        xi , yi       : Centres de la partition : ci = ( )
    //        dim_x, dim_y  : Dimensions de la partition en x et y
    //        di            : Mesure  de la partition : norme L2 ou LInfinie
    //        fi = _F(xi,yi): Evaluations de la fonction objectif _F : 
    //        Flags         : Flag = 0 : point qcque. ( interieur au domaine ) - Flag = -2 : point au bord - Flag = -4 : coin

    CATMathSetOfPointsND _DirectGraph;  // GRAPHE UTILE dim=7
    // GRAPHE FILTRE : tableau de dimension 4 permettant la determination de l'enveloppe convexe inferieure droite
    CATMathSetOfPointsND _FiltGraph;

    double _xmin , _ymin , _fmin , _fmax;// Valeurs min/max retournees et utilisees par DirectMethod

    // Choix de la Norme pour les taille de domaine di
    CATBoolean _L2orLInfty;  // 0 : norme quadratique,  1 : infinie

    // Parametre permettant de borner la taille du graphe initial de DIRECT :
    // Taille maximale initiale = _SampleMAX^2 +- Residu ... 
    // Residu issu des conversions au plus proche entier
    // Si le sampling depasse _SampleMAX^2, on a recours au mode "SubdivideDomain"
    CATLONG32 _SampleMAX;   
    
    // Mode "ImprovedStorage"
    // Type de stockage et de traitement du graphe ameliorant les performances
    // -> non utilisable si la DirectMethod est 
    //    utilisee avec un graphe initial vide
    // cf. InitializeDirectGraph
    CATBoolean _ImprovedStorage; // Mode "ImprovedStorage" : 
    
    CATLONG32  _IndexStart , _IndexEnd; //Indices bornant la zone du graphe initial correspondant
                                       // aux N = DIRECT_MAXITER points realisant les meilleures valeurs de f

    CATBoolean _NormalizedMode; // TRUE => on adimensionne le domaine D a [0,1] x [0,1]

    // general 
    CATBoolean                 _OKScaleReviewed ;
    CATSoftwareConfiguration * _Config;
    int                        _CGMLevel;

};
  //
  // -------------------------------------------------------------------------------------------
  // Utilitaires externes a la classe
  // -------------------------------------------------------------------------------------------
  //
  // OPTIMISATION DU SAMPLING
  //
  // Indicateur de complexite de la fonctionnelle a traiter
  // Utilise une DCT 2D - 2eme forme
  // Entrees : grille d'evaluations de f de taille M*N
  //
  double DiscreteCosineTransformIndicator( const double * f , const CATLONG32 M , const CATLONG32 N );

  // DCT 2eme forme  Approche "slow" 1D et 2D
  //
  void SlowCosineTransform2_1D( const double * f , const CATLONG32 M ,                     double * F );
  void SlowCosineTransform2_2D( const double * f , const CATLONG32 M , const CATLONG32 N , double * F );
  // Approche Triviale pour Debug
  void TrivialCosineTransform2_2D_debug( const double * f , const CATLONG32 M , const CATLONG32 N , double * F );
  //
#endif

