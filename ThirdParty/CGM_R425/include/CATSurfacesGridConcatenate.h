/*-*-c++-*-*/
// COPYRIGHT DASSAULT SYSTEMES 2002
//==========================================================================
//
// CATSurfacesGridConcatenate :
//
// This class is first designed to concatenate a grid of surfaces
// into one or more several more continuous surfaces
//==========================================================================
// 21/01/20 NLD Suppression du vieux constructeur sans configuration
//              Mise au propre. Smart indent
//==========================================================================
#ifndef CATSurfacesGridConcatenate_H
#define CATSurfacesGridConcatenate_H

   // N.B je conserve le constructeur sans configuration de CATIPGMSurfacesGridConcatenate
   //     mais je fais dans le builder sa migration vers l'unique constructeur conservé ici
   #define CATSurfacesGridConcatenate_ShuntOldConstructor "NLD210120; ATTENTION constructeur equivalent CATIPGMSurfacesGridConcatenate conserve"

#include "Interfaces.h"

class CATGeoFactory;
class CATNurbsSurface;
class CATFrFNurbsBipar;
class CATFrFNurbsMultiForm;
class CATString;
class CATGeoOpTimer;
class CATSoftwareConfiguration;

// Base class
#include "CATGeoOperator.h"

// C++11
#include "CATGeoOpVirtual.h"

#include "CATMathTransformation2D.h"

//-----------------------------------------------------------------------------
class ExportedByInterfaces CATSurfacesGridConcatenate : public CATGeoOperator
{
  CATCGMVirtualDeclareClass(CATSurfacesGridConcatenate);
  public :
    // on a une grille de nbSurfI surfaces dans la direction I
    // et de nbSurfJ surfaces dans la direction J (i en horizontal (pour les colonnes) et j en vertival (pour les lignes)).
    // on ordonnera les surfaces dans le sens I d'abord :
    // surfaces rangees suivant les u croissants d'abord.
    // surf(i,j)=initialSurfaces[j*nbSurfI+i]
    // les surfaces resultats seront parametrees en u suivant I et en v suivant J.
  CATSurfacesGridConcatenate(CATGeoFactory            * factory,
                             CATSoftwareConfiguration * iConfig,
                             CATNurbsSurface         ** initialSurfaces,
                             CATLONG32                  nbSurfI,
                             CATLONG32                  nbSurfJ,
                             CATLONG32                * iExchangeIJFlags,         // indices comme pour les surfaces
                             CATLONG32                * iInvertIFlags,            // idem
                             CATLONG32                * iInvertJFlags,            // idem
                             double                   * internalStartIParameters, // idem, le premier param ne sera pas utilise, mais peut etre initialise a -1.
                             double                   * internalEndIParameters,   // idem, le dernier param ne sera pas utilise, mais peut etre initialise a -1.
                             double                   * internalStartJParameters, // idem, le premier param ne sera pas utilise, mais peut etre initialise a -1.
                             double                   * internalEndJParameters);  // idem, le dernier param ne sera pas utilise, mais peut etre initialise a -1.
  #ifndef CATSurfacesGridConcatenate_ShuntOldConstructor
  // Do not use from V5R15 - Use the constructor with CATSoftwareConfiguration
  CATSurfacesGridConcatenate(CATGeoFactory*      factory,
                             CATNurbsSurface**   initialSurfaces,
                             CATLONG32 nbSurfI,
                             CATLONG32 nbSurfJ,
                             CATLONG32* iExchangeIJFlags, // indices comme pour les surfaces
                             CATLONG32* iInvertIFlags, // idem
                             CATLONG32* iInvertJFlags, // idem
                             double* internalStartIParameters, // idem, le premier param ne sera pas utilise, mais peut etre initialise a -1.
                             double* internalEndIParameters, // idem, le dernier param ne sera pas utilise, mais peut etre initialise a -1.
                             double* internalStartJParameters, // idem, le premier param ne sera pas utilise, mais peut etre initialise a -1.
                             double* internalEndJParameters); // idem, le dernier param ne sera pas utilise, mais peut etre initialise a -1.
  #endif
  //
  virtual ~CATSurfacesGridConcatenate();

  // to specify the objective continuity
  //the default value is 2
  void      SetObjectiveContinuity      (CATLONG32 objectiveContinuity);    // to specitfy the expected continuity order
                                                                            // 0, 1 or 2 (2 is default value)

  void      SetKindOfContinuity         (CATLONG32 kindOfContinuity   = 0); // 0 for C (default mode)
                                                                            // 1 for G 

  void      MakeNoShapeOptimization     () // to prevent us from any shape optimisation
    // can be used only for C0, G1 ou G2 modes.
    { _optimisationMode = 0; };

  CATLONG32 RunConcatenationCheck       (); // can be called before the Run, to tune the tolerances to perform
                                            // the expected deformation
                                            // computed only for if kindOfContinuity==0
  double    GetMinimumDeviationForC0Mode();        //  rend la valeur seuil de deviation en point a prendre pour 
                                                // effectuer la concatenation en une seule surface C0. toujours calculee
  double    GetAngleThresholdForG1Concatenation(); // rend la valeur seuil a prendre comme tolerance G1
                                                // pour effectuer la concatenation en une seule surface G1. toujours calculee
  double    GetMinimumDeviationForCnMode(); // rend la valeur seuil a prendre comme tolerance en point pour 
                                         // effectuer la concatenation en une seule surface C0(G1), C1 ou C2

  //
  //  2 other deviations will be taken into account and can not really be mixed with the first one :
  //  - The first one is the parametric deviation, and enable to concatenate the grid of surface into 
  //  one C0-surface. We will call it the parametric deviation
  //  - The second deviation is the deformation that is necessary to improve the level of continuity from
  //  C0 (after concatenation) to the objective continuity (C1 or C2).
  // To simplify the interface of the current class, we just let the user specify one tolerance
  // that will be used as the sum of two tolerances.
  // Hence, it has to be greater to the C0-Parametric minimal deviation. Otherwise, we can even not
  // concatenate. If the global deforation tolerance is smaller thant the C0-parametric deviation,
  // the operator will fail.
  // Secondly, the tolerance of the optimisation will be the difference of the global deformation
  // tolerance with the C0-parametric deviation.
  //
  // If the user set the globalDeformationTolerance to -1, we will force
  // the C0 concatenation as well as the optimisation into one single surface.

  void      SetGlobalDeformationTolerance(double                   globalDeformationTolerance = -1.);

  void      SetGTolerance                (double                   maximumAuthorizedGTolerance);

  void      SetNoReparametrization       ();

  // sum of the C0parametric tolerance and of the optimisation tolerance
  double    GetGlobalDeformation         ();

  void      GetResultingSurfaces         (CATNurbsSurface      **& resultingSurfaces,
                                          CATLONG32              & nbSurfU          ,
                                          CATLONG32              & nbSurfV          );

  // supply the user with index correspondance between of the input and output surfaces,
  // as well as with 2d-transformation between the initial surface and the resulting one.
  CATLONG32 GetSurfaceMapping            (CATLONG32                iNumSurfUInit    ,
                                          CATLONG32                iNumSurfVInit    ,
                                          CATLONG32              & iNumSurfUNew     ,
                                          CATLONG32              & iNumSurfVNew     ,
                                          CATMathTransformation2D& transfor2D       );

  /** @nodoc @nocgmitf */
  virtual int RunOperator();

//  pour l'instant, on garde la meme segmentation // ie pas de suppression de noeuds
//  plus simple pour le reparametrisation
//  void SetKeepSegmentation(CATLONG32 keepSegmentation)
//  { _keepSegmentation = keepSegmentation; };

//  pour l'instant l'elevation de degre a 5 est systematique
//  void AuthorisedDegreeIncreasing(CATLONG32 minimumDegree=5) //
//  { _minimumDegree = minimumDegree; }; // default value equals 5

  private :
    void      DataInitialisation                    ();

    CATLONG32 ConvertSurfacesIntoBipares            (CATNurbsSurface    **  initialSurfaces         ,
                                                     CATLONG32              nbSurf                  ,
                                                     CATLONG32           *  iExchangeUV             ,
                                                     CATLONG32           *  iInvertU                ,
                                                     CATLONG32           *  iInvertV                ,
                                                     double              *  uStartLimits            ,
                                                     double              *  uEndLimits              ,
                                                     double              *  vStartLimits            ,
                                                     double              *  vEndLimits              ,
                                                     CATFrFNurbsBipar   **& initialBipares          );

    CATLONG32 BiparesHomogenization                 (CATFrFNurbsBipar   **& bipares                 ,
                                                     CATLONG32              nbSurfU                 ,
                                                     CATLONG32              nbSurfV                 );

    CATLONG32 BiparesConcatenateAndReparametrization(CATFrFNurbsBipar   **  bipares                 ,
                                                     CATLONG32              nbSurfU                 ,
                                                     CATLONG32              nbSurfV                 ,
                                                     double                 authorisedC0Deviation   ,
                                                     CATLONG32           *& iNumKnotTransitionU     ,
                                                     CATLONG32           *& iNumKnotTransitionV     ,
                                                     double              *& newUParameters          ,
                                                     double              *& newVParameters          ,
                                                     CATLONG32            & globalNumberOfUKnots    ,
                                                     CATLONG32            & globalNumberOfVKnots    ,
                                                     CATLONG32            & C0ConcatenationAccepted ,
                                                     CATFrFNurbsBipar    *& C0Bipar                 ,
                                                     double               & C0SlidingMaxDeviation   );

    CATLONG32 DegreeIncreasing                      (CATFrFNurbsMultiForm*& C0Bipar                 ,
                                                     CATLONG32              minimumDegree           ,
                                                     CATLONG32            & deltaDegreeIncreasing   );

    CATLONG32 BipareShapeOptimization               (CATFrFNurbsBipar    *  C0Bipar                 ,
                                                     double                 deformationTolerance    ,
                                                     CATLONG32              objectiveContinuity     ,
                                                     double               & shapeDeformation        ,
                                                     CATFrFNurbsBipar    *& optimisedBipar          );
    CATLONG32 BipareCutting                         (CATGeoFactory       *  factory                 ,
                                                     CATFrFNurbsBipar    *  optimisedBipar          ,
                                                     CATLONG32              objectiveContinuity     ,
                                                     CATLONG32            & newNbSurfU              ,
                                                     CATLONG32            & newNbSurfV              ,
                                                     CATNurbsSurface    **& resultingSurfaces       ,
                                                     CATLONG32           *& iNumSurfUMapping        ,
                                                     CATLONG32           *& iNumSurfVMapping        );

    CATLONG32 ComputeMapping                        (CATLONG32              nbSurfInit              ,
                                                     CATLONG32              nbSurfNew               ,
                                                     CATLONG32              nbKnots                 ,
                                                     CATLONG32           *  iNumKnotTransition      ,
                                                     CATLONG32           *  iNumKnotBreak           ,
                                                     CATLONG32           *  surfMapping             );

    CATLONG32 ComputeC0SlidingDeviation             (CATFrFNurbsBipar   **  bipares                 ,
                                                     CATLONG32              nbSurfU                 ,
                                                     CATLONG32              nbSurfV                 ,
                                                     CATLONG32              iDir                    ,
                                                     double               & C0MaxDeviation          );

    CATLONG32 ComputeAccurateMaxDeviation           (CATFrFNurbsBipar   **  bipares                 ,
                                                     CATLONG32              nbSurfU                 ,
                                                     CATLONG32              nbSurfV                 ,
                                                     CATLONG32              iDir                    ,
                                                     double               & C0MaxDeviation          );

    CATLONG32 PreAnalysis                           (CATFrFNurbsBipar   **  iBipares                ,
                                                     CATLONG32              iNbSurfU                ,
                                                     CATLONG32              iNbSurfV                );
    
    CATLONG32 G1Analysis                            (CATFrFNurbsBipar    *  bipare                  ,
                                                     double               & G1MaxDeviation          );

    CATNurbsSurface          ** _initialSurfaces;
    CATLONG32                   _nbSurfUInit;
    CATLONG32                   _nbSurfVInit;

    CATLONG32                 * _iExchangeUVFlags;
    CATLONG32                 * _iInvertUFlags;
    CATLONG32                 * _iInvertVFlags;
    double                    * _internalStartUParameters;
    double                    * _internalEndUParameters;
    double                    * _internalStartVParameters;
    double                    * _internalEndVParameters;

    CATLONG32                   _objectiveContinuity;
    CATLONG32                   _kindOfContinuity;

    double                      _globalDeformationTolerance;
    double                      _globalDeformation;

    double                      _C0ParametricDeviation;
    double                      _G1MaxDeviation;
    double                      _globalMinimumDeviationForCConcatenation;

    double                      _maximumAuthorizedGTolerance;

    CATNurbsSurface          ** _resultingSurfaces;
    CATLONG32                   _nbSurfUOut;
    CATLONG32                   _nbSurfVOut;
    CATLONG32                   _keepSegmentation;
    CATLONG32                   _minimumDegree;

    CATLONG32                 * _iNumSurfUMapping;
    CATLONG32                 * _iNumSurfVMapping;

    CATLONG32                 * _iNumKnotTransitionU;
    CATLONG32                 * _iNumKnotTransitionV;

    double                    * _newUParameters;
    double                    * _newVParameters;

    CATLONG32                  _globalNumberOfUKnots;
    CATLONG32                  _globalNumberOfVKnots;

    CATLONG32                  _thresholdsComputed;

    CATFrFNurbsBipar         * _C0Bipare;

    CATLONG32                  _optimisationMode;
    CATLONG32                  _discretisationFactor;
    CATLONG32                  _reparametrize;
    CATLONG32                  _debug;
    CATSoftwareConfiguration * _Config;


    //========================================================================
    // Gestion CGMReplay
    //========================================================================
protected:
  friend class CATGeoStreamFactory; 
  
  // private static data
  static CATString _OperatorId;
  static CATGeoOpTimer _Timer;
  
  static const CATString * GetDefaultOperatorId() { return & _OperatorId; };
  
public:
  
  /** @nodoc @nocgmitf */
  const CATString * GetOperatorId();
  //-----------------------------------------------------------------------
  //- Gestion timer 
  //-----------------------------------------------------------------------  
  CATGeoOpTimer * GetTimer();
  
  //-----------------------------------------------------------------------
  //- Gestion Mode Record 
  //-----------------------------------------------------------------------  
  
  /** @nodoc @nocgmitf */
  CATExtCGMReplay  * IsRecordable  (short & LevelOfRuntime, short &VersionOfStream);
  /** @nodoc @nocgmitf */
  void               WriteInput    (CATCGMStream  & os);
  /** @nodoc @nocgmitf */
  void               WriteOutput   (CATCGMStream & os);
  /** @nodoc @nocgmitf */
  CATBoolean         ValidateOutput(CATCGMStream& ioStream, CATCGMOutput & os,int VersionNumber=1);
  // dump de l'opérateur
  /** @nodoc @nocgmitf */
  void               Dump          ( CATCGMOutput& os ) ;
  // dump du resultat du run
  /** @nodoc @nocgmitf */
  void               DumpOutput    (CATCGMOutput& os);
  // dump de la reference
  /** @nodoc @nocgmitf */
  void               DumpOutput    (CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
  /** @nodoc @nocgmitf */
  CATCheckDiagnostic CheckOutput   (CATCGMOutput & os);

};
#endif









