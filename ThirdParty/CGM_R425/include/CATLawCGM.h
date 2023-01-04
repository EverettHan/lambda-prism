/**
* @quickReview BQJ 06:05:29
*/

/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATLawCGM:
// Abstract class for CGM objects that are compliant with CATLaw Interface
//=============================================================================
// Usage notes:
//
// This is an implementation of the CATLaw based on CATCGMContainer infrastructure.
//
// No check is done on Parameter being inside Parametric definition of the Law.
//=============================================================================
// Oct.  97 tpg Creation                                       T.A. Phung (tpg)
// Mar.  04 HCN Stream/UnStreamCompact(...),
//              Stream/UnStreamCompactLossAllowed(...)
// Apr.  04 HCN GetStreamSortingKey(...),
//              GetMaxSimilarityLevel()
// 17/01/08 NLD XScale. Ajout SetScaleOption() _ScaleOption, _UseScaleOption, _CheckValue et _GottaCheckScale
// 22/01/08 NLD Ajout GetPowerScale(), GetScaledTolerances() et GetStandardScaledTolerances()
// 23/01/08 NLD Plus d'utilisation de CATMathAttrScaleOption dans SetScaleOption()
//              car il est defini en protected par Mathematics
// 25/01/08 NLD Ajout ScaleCheck()
//              Ajout _NumLaw
// 30/01/08 NLD Ajout GetScalePowerXScalePowerF()
// 06/02/08 NLD Ajout DuplicateCommonData()
// 29/02/08 NLD Ajout _GottaCheckParameters
// 29/02/08 NLD Ajout #define UseDuplicateCommonDataInClone en complement de #define UseDuplicateCommonData
// Jul.  09 VUC Suppression du StreamCompact
// 05/10/11 R1Y Added access functions (for comparing geometries).
// 05/12/16 NLD Smart indent
//=============================================================================
#ifndef CATLawCGM_H
#define CATLawCGM_H

// deviennent inutiles: deflaggage/suppression de toutes les utilisations (code actif) le 051216
#define UseDuplicateCommonData        "en test NLD060208"
#define UseDuplicateCommonDataInClone "en test NLD280208"

#include "CATIACGMLevel.h"

#include "CATCGMObject.h"                       // For inheritance 
#include "CATEvalCommand.h"      
#include "CATMathFunctionX.h"
#include "CATMathAttrScaleOption.h"
#include "CATMathPolynomX.h"
#include "CATCGMEquationError.h"
#include "CATMathLimits.h"
#include "CATTolerance.h"

class CATMathSetOfPointsND;
class CATGeoFactory;
class CATLaw;
class CATCloneManager;
class CATICGMObject;
class CATError;

//-----------------------------------------------------------------------------
class CATLawCGM: public CATCGMObject
{
  public :
 
  //--------------------------------------------------------
  // Fusion
  //--------------------------------------------------------
  virtual void              LockEquation                  (        void               *  iForDebug            );
  virtual void              UnLockEquation                (        void               *  iForDebug            );

  //-------------------------------------------------------------------------
  // Object Management
  //-------------------------------------------------------------------------
                            CATLawCGM                     ();
  virtual                  ~CATLawCGM                     ();
  virtual void              Dump                          (        CATCGMOutput        & io                   );    //  Dump 


  virtual void              PropagateQuery                (        CATICGMUnknown     *  iFrom                ,
                                                                   CATCGMQueryManager  & iQuery               ) ;

  // RAD : Macro CGM-Model pour les classes non instanciables 
  CATCGMDeclareVirtualClass;
  Data_GeometricObjectsCGM_Stream;

  //-------------------------------------------------------------------------
  // Methods of the CATLaw Interface implemented at that level
  //-------------------------------------------------------------------------

  //- Read the Definition Interval.
  virtual void              GetDefinitionInterval          (       double              & ioTMin               ,
                                                                   double              & ioTMax               )    const;

  //- Get all the parameters, for which the law evaluation gives iLawValue
  //- with tolerance on law value;
  virtual CATMathDiagnostic GetParametersForALawValue       (      double                iLawValue            ,
                                                                   CATMathSetOfPointsND &ioParameters         ,
                                                             const double                iTolOnLawValue       )          ;

  virtual CATMathDiagnostic GetParametersForALawValue       (      double                iLawValue            ,
                                                                   CATMathSetOfPointsND &ioParameters         )          ;// deprecated

  //- Read the Extremums.
  virtual void              GetExtremums                    (      double              & ioMin                ,
                                                                   double              & ioMax                )     const;

  //- Scale the Definition Interval.
  virtual void              ScaleDefinitionInterval         (const double                iNewTMin             ,
                                                             const double                iNewTMax             );

  //- Read constraint parameters count.
  virtual CATLONG32         GetNumberOfConstraintParameters ()                                                      const;

  //- Read one constraint parameter.
  // iIndex goes from 0 to the constraint parameters count - 1.
  virtual double            GetOneConstraintParameter       (const CATLONG32             iIndex               )     const;

  //- Read all constraint parameters.
  // Returns constraints count and pointer on parameters, this pointer must be
  // DELETED afterwards (NULL if constraints count = 0).
  virtual double          * GetConstraintParameters         (      CATLONG32           & oNumberOfConstraints )     const;

  //- Search for the arc (iArcRank) corresponding a given parameter T.
  // A arc is the Sub-Law between two constraints.
  // iArcRank = 1 indicates the arc following the index 0 constraint
  // parameter.
  // if T = one constraint parameter, the following arc is given.
  virtual CATLONG32          LocateArc                      (const double                iT                   )          ;

  //- Search for the contraint (iIndex) nearby a given parameter T.
  virtual CATLONG32         LocateConstraint                (const double                iT                   )    const ;

  //- Locate a parameter.
  // Returns the arc law (iArcRank) and the border
  virtual CATLONG32         LocateParameter                 (const double                iT                   ,
                                                                   double              & oTInf                ,
                                                                   double              & oTSup                )    const ;

  //- Evaluators.
          double            Eval                            (const double                iT                   )    const;
          double            EvalFirstDeriv                  (const double                iT                   )    const;
          double            EvalSecondDeriv                 (const double                iT                   )    const;
          double            EvalThirdDeriv                  (const double                iT                   )    const;
  
  // Evaluator of Value and derivatives at the same time.
          void              Eval                            (const double             *  iT                   ,
                                                             const CATLONG32             iNbrOfParam          ,
                                                             const CATEvalCommand        iCmd                 ,
                                                                   double             *  oValue               ,
                                                                   double             *  oSlope               = 0,
                                                                   double             *  oSecondDeriv         = 0,
                                                                   double             *  oThirdDeriv          = 0) const ;
  
  //- Evaluators on one arc:
  // A arc is the Sub-Law between two constraints, the parameter T is not 
  // necessary between these two constraints. 
          double            Eval                            (const CATLONG32             iArcRank             ,
                                                             const double                iT                   )    const ;

          double            EvalFirstDeriv                  (const CATLONG32             iArcRank             ,
                                                             const double                iT                   )    const ;

          double            EvalSecondDeriv                 (const CATLONG32             iArcRank             ,
                                                             const double                iT                   )    const ;

          double            EvalThirdDeriv                  (const CATLONG32             iArcRank             ,
                                                             const double                iT                   )    const ;
  
  // Evaluator on one arc of Value and derivatives at the same time.
          void              Eval                            (const CATLONG32             iArcRank             ,
                                                             const double             *  iT                   ,
                                                             const CATLONG32             iNbrOfParam          ,
                                                             const CATEvalCommand        iCmd                 ,
                                                                   double             *  oValue               ,
                                                                   double             *  oSlope               = 0,
                                                                   double             *  oSecondDeriv         = 0,
                                                                   double             *  oThirdDeriv          = 0) const ;

  
  //- Equations management
  virtual void              OpenEquation                    (const void               *  iDebugUsage          = NULL) ;

  virtual void              CloseEquation                   (const void               *  iDebugUsage          = NULL) ;

  virtual CATLONG32         GetNumberOfComponent            ()                                                     const = 0;

  virtual void              GetEquation                     (const CATLONG32             iArcRank             ,
                                                             const CATMathFunctionX   *& oF                   )    const = 0;

  virtual void              GetGlobalEquation               (const CATMathFunctionX   *& oF                   )    const;

  //- Read whether the Law is periodic.
  virtual CATBoolean        IsPeriodic                      ()                                                     const;
  //- Set the Law periodic
  //  iPeriodic = 0 : the law is not periodic  
  //  iPeriodic = 1 : the law is periodic  
  virtual void              SetPeriodic                     (const CATLONG32             iPeriodic            = 1);
  
  //- Read global continuity.
  //  0 --> C0
  //  1 --> C1
  //  n --> Cn
  virtual CATLONG32          GetGlobalContinuity            ()                                                     const ;
  virtual CATLONG32          GetGlobalContinuity            (      double                iTolPt               )    const ;

  //- Read one constraint continuity.
  virtual CATLONG32          GetConstraintContinuity        (const CATLONG32             iIndex               )    const ;
  virtual CATLONG32          GetConstraintContinuity        (const CATLONG32             iIndex               ,
                                                                   double                iTolPt               )    const ;

  //- Duplicate the Law
  virtual CATLaw          *  Duplicate                      (      CATGeoFactory      *  iFactory             )    const = 0;
 
  //- Apply a scaling to the Law
  virtual void               ApplyScaling                   (      double                iRatio               )          ;

  //- Read the scaling value
  virtual double             GetScalingValue                ()                                                     const ;

  //---------------------------------------------------------------------------
  // Clone
  //---------------------------------------------------------------------------
  virtual CATICGMObject    * Clone                          (      CATCloneManager     & iCloneManager        )    const = 0;
  //-------------------------------------------------------------------------
  // Gestion des caches
  //-------------------------------------------------------------------------
  virtual void               IsModified                     () ;

  //-------------------------------------------------------------------------
  // Gestion du scale
  //-------------------------------------------------------------------------
  //void SetScaleOption(CATMathAttrScaleOption& iScaleOption) ;
  //void SetScaleOption(CATLONG32 iPowerScaleF, CATLONG32 iPowerScaleX, CATLONG32 iReviewed=0) ;
          void               SetScalePowerXScalePowerF      (      CATLONG32             iPowerScaleX        ,
                                                                   CATLONG32             iPowerScaleF        ,
                                                                   CATLONG32             iReviewed           = 0) ;
  // returns 0 if not previously set
          CATLONG32          GetScalePowerXScalePowerF      (      CATLONG32           & oPowerScaleX        ,
                                                                   CATLONG32           & oPowerScaleF        ,
                                                                   CATLONG32           & oReviewed           )   ;

          int                GetUseScaleOption              ()                                                     const;
          void               GetScaleOption                 (   CATMathAttrScaleOption & oScaleOption        )     const;

  //-------------------------------------------------------------------------
  // Get scale powers applying to variable and law, and powered scales
  //-------------------------------------------------------------------------
          void               GetPowerScale                  (      int                 & oUseScale           ,
                                                                   int                 & oPowerX             ,
                                                                   int                 & oPowerF             ,
                                                                   double              & oPoweredScaleX      ,
                                                                   double              & oPoweredScaleF      )     const ;
  //-----------------------------------------------------------------------------
  // Get scaled tolerance for parameter and function
  //-----------------------------------------------------------------------------
          void               GetScaledTolerances            (      double                iRelativeToleranceForX,
                                                                   double                iRelativeToleranceForF,
                                                                   double              & oScaledToleranceForX,
                                                                   double              & oScaledToleranceForF)     const ;

  //-----------------------------------------------------------------------------
  // Get scaled standard tolerance for parameter and function (issued from CATEpsg)
  //-----------------------------------------------------------------------------
          void               GetStandardScaledTolerances    (      double              & oScaledToleranceForX,
                                                                   double              & oScaledToleranceForF)     const ;

  //-----------------------------------------------------------------------------
  // Verification des attributs de scale
  //-----------------------------------------------------------------------------
          void               ScaleCheck                     ()                                                     const ;

  //-------------------------------------------------------------------------
  protected :
  //-------------------------------------------------------------------------


  //-----------------------------------------------------------------------------
  // Duplication des donnees communes a tous types de lois
  //-----------------------------------------------------------------------------
          void               DuplicateCommonData            (const CATLawCGM          *  iLawToCopy          ) ;

  //-----------------------------------------------------------------------
  // Detection d'equation ouvertes empechant la redefinition d'un objet
  //-----------------------------------------------------------------------
  virtual CATBoolean         IsLocked                       (      int                *  oLockCount          = 0) ;

  //-------------------------------------------------------------------------
  // Donnees de la classe
  //-------------------------------------------------------------------------
  //NLD230108 je mets cette donnee en 1er pour tester et sortir en erreur
  //si on arrive dans l'objet loi avec une loi non CGM et ne pas risquer
  //de lire trop loin dans les donnees
  int                    _CheckValue ;
  int                    _GottaCheckScale ;
  int                    _GottaCheckParameters ;
  int                    _NumLaw ;

  double               * _ConstraintParameters;
  CATLONG32              _NbrOfConstraintParameters;

  CATLONG32              _IsPeriodic;

  double                 _Scaling;
  int                    _UseScaleOption;
  CATMathAttrScaleOption _ScaleOption;

  //-------------------------------------------------------------------------
  // Donnees Buffer pour la zone d optimisation des equations
  //-------------------------------------------------------------------------
  int                    _LockCount;
  int                    _EquationsSize;
  CATMathFunctionX    ** _Equations;

  //et des Boxs. Si Min>Max -> les boxs n'ont pas ete calcule.
  double                 _MinBox,
                         _MaxBox;
  
  
  //-------------------------------------------------------------------------
  // Check 
  //-------------------------------------------------------------------------
  virtual CATError         * CheckParameters                (const short                 iEvent              = 1) const;
  //-------------------------------------------------------------------------
  // Methods necessary for implementation in CATLawCGM.cpp
  //-------------------------------------------------------------------------
  // Methode virtuelle pure donnant la taille necessaire pour _Equations.
  virtual void               SetEquationsSize               ()                                                          = 0;
  virtual double             GetBorder                      (const CATLONG32             iBorderIndex        )    const = 0;

  //-------------------------------------------------------------------------
  // Update des donnees
  //-------------------------------------------------------------------------
  virtual void               CalculateBuffer                ()                                                          = 0 ;
  //-------------------------------------------------------------------------
  // Nettoyage du Buffer
  //-------------------------------------------------------------------------
  virtual void               ResetBuffer                    () ;

  //-------------------------------------------------------------------------
  // Test index de la contrainte
  //-------------------------------------------------------------------------
  virtual void               CheckIndex                     (const CATLONG32             iIndex              )    const ;
  virtual void               CheckArcIndex                  (const CATLONG32             iIndex              )    const ;

  //-------------------------------------------------------------------------
  // Utilitaires
  //-------------------------------------------------------------------------
          CATMathPolynomX  * CalculatePolynom               (const double             *  iTDef               ,
                                                             const double             *  iVertices           ,
                                                             const CATLONG32             iDegree             ,
                                                             const CATLONG32             iOption             = 0) const ;

          CATMathPolynomX  * CalculateExtrapolTransition    (const double                iT                  ,
                                                             const double             *  iDer                , // tableau des derivees. ordre 0, ordre 1, ordre 2
                                                             const double             *  iExtremums          ,
                                                             const CATLONG32             iOrientation        ,
                                                                   double              & oWidth              ) ;

          CATLONG32          CalculateExtrapolInterval      (const double             *  iDer                , // tableau des derivees. ordre 0, ordre 1, ordre 2
                                                             const double             *  iCoeff              ,
                                                             const double             *  iExtremums          ,
                                                             const CATLONG32             iOrientation        ,
                                                                   double             *  oD1                 ,
                                                                   double             *  oD2                 );

           double            UpdateParam                    (      double                t                   ,
                                                                   double                TMin                ,
                                                                   double                period              )     const ;

  private :

  //-------------------------------------------------------------------------
  // Code obligatoirement fourni par les classes filles
  //-------------------------------------------------------------------------
  virtual void               EvalLaw                        (const CATEvalCommand        iCmd                ,
                                                             const int                   iNbParam            ,
                                                             const double             *  iParam              ,
                                                                   double             *  oResult             )     const = 0 ;
  virtual void               EvalSubLaw                     (const CATLONG32             iArcRank            ,
                                                             const CATEvalCommand        iCmd                ,
                                                             const int                   iNbParam            ,
                                                             const double             *  iParam              ,
                                                             double                   *  oResult             )     const = 0 ;
};
#endif


