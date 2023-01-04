// COPYRIGHT DASSAULT SYSTEMES  1997
#ifndef CATMathVectorialFunctionX_H
#define CATMathVectorialFunctionX_H
//=============================================================================
//
// CATMathVectorialFunctionX:
// Abstract class used to define a set of functions from a domain included in
// R-->RN with F differentiable (C1) and N>=1.
//
//=============================================================================
//
// Usage notes:
// The result of the sample method is a set of points in RN and a set of points
// in R. 
// To use this class you will need to derivate
// this abstract class and define some evaluators on your concrete system
// of functions. You will have to code Eval method and it is also 
// strongly recommended to code EvalFirstDeriv.
// If you want to put some users constraints, you will need to derivative
// the abstract class CATMathConstraint and to code its evaluators.
//
// XScaleRules:                                                                                 (NLD021213)
//  - there is no ScaleOption (of typeCATMathAttrScaleOption) describing the vectorial function :
//    scale behaviour is imposed
//  - domains         must behave like power 1 of factory scale
//  - parameters      must behave like power 1 of factory scale
//  - points computed must behave like power 1 of factory scale
//  - steps  computed must behave like power 1 of factory scale
//
//=============================================================================
// 26/05/08 NLD Ajout _GlobalEps
// 27/05/08 NLD Ajout _OKScaleReviewed, _ScaleAlreadyChecked, SetOKScaleReviewed(), CATMathVectorialFunctionXParallelDebugCond()
//              _DummyMinStepPoint remplace _MinStepPoint
//              Ajout SampleInit()
// 29/05/08 NLD Ajout _CGMLevel
//              // differe, impact trop lourd: Le constructeur sans configuration devient prive
//              La configuration devient privee, on y accede par
//              GetSoftwareConfiguration()/SetSoftwareConfiguration()
// 20/07/10 NLD Deflaggage local sans impact
// 02/12/13 NLD Ajout XScaleRules
//              Smart indent
// 04/05/16 NLD Documentation des attributs de Sample() et SamppleStepByStep()
// 13/04/17 NLD GetSoftwareConfiguration() devient const pour appel depuis evaluateurs
//              Ajout Init()
//              Regroupement des methodes entre elles / regroupement des donnees entre elles
//=============================================================================
class CATMathInterval;
class CATMathSetOfPointsND;
class CATMathAttrList;
class CATMathAttribute;
class CATMathIntervalND;
class CATMathEvalRecord;

#include "CATMathConstraint.h"
#include "YN000FUN.h"
#include "CATMathDef.h"
#include "CATMathInterval.h"
#include "CATMathDiagnostic.h"
#include "CATMathAttrDecomposition.h"
#include "CATCGMNewArray.h"
#include "CATMathListOfEvalRecord.h"
#include "CATCGMVirtual.h"
#include "CATTolerance.h"

ExportedByYN000FUN extern const CATMathAttrId AttrDomainPoint;
ExportedByYN000FUN extern const CATMathAttrId AttrStopParam;
// Diagnostic
#include "CATMathStopDiagnostic.h"

class CATSoftwareConfiguration;

//-----------------------------------------------------------------------------
class ExportedByYN000FUN CATMathVectorialFunctionX  : public CATCGMVirtual
{ 
  public:  
//----------------------------------------------------------  
//  Constructor (iN is the number of functions of the system)
//----------------------------------------------------------    
                              CATMathVectorialFunctionX (      CATSoftwareConfiguration *  iConfig,
                                                         const CATLONG32                   iN     ,
                                                         const CATTolerance              & iTol   = CATGetDefaultTolerance());

    //Do not use from V5R15 - Use the constructor with CATSoftwareConfiguration
    //private:
                              CATMathVectorialFunctionX (const CATLONG32  iN);

  public:
//----------------------------------------------------------  
//  Default Constructor 
//----------------------------------------------------------    
                              CATMathVectorialFunctionX ();
//------------ 
//  Destructor  
//------------  
    virtual                  ~CATMathVectorialFunctionX ();
//-----------------------------------------------------------------
// Information methods
//-----------------------------------------------------------------
    virtual CATBoolean        IsOption                  (const CATMathOption               iOption) const;

//  Get the number of functions of the system (N) 
            CATLONG32         GetNumberOfFunctions      () const; 

//  Compute the sampling method :
//   Given a iDomain of parameters in R (ex: [Domain[0], Domain[1]]),
//   the Sample method finds a set of sorted points Xi on the curve
//   and a set of sorted parameters, all contained by the iDomain.
//   The mode of repartition of the points and the density are given by the
//   iAttributes argument.
//   The CATMathDiagnostic is CATMathOK if the Sample found a set of points.
//   Otherwise a failure diagnostic is given.
//   The GetDiagnostic method give you the reason of the end of the sampling.
//
//   Handled attributes: (documentation by NLD040516)
//   -  CATMathAttrRepartition
//   -  CATMathConstraint
//   - (CATMathAttrPointerValue) AttrDomainPoints       
//   - (CATMathAttrPointerValue) AttrStopParam 
//   -  CATMathAttrDecomposition
    virtual CATMathDiagnostic Sample                    (const CATMathInterval           & iDomain     ,
                                                               CATMathSetOfPointsND      & oSetOfPoints,
                                                               CATMathSetOfPointsND      & oSetOfParam ,
                                                         const CATMathAttrList          *  iAttributes = 0);
//  Compute the sampling method :
//   Given a iDomain of parameters in R (ex: [Domain[0], Domain[1]]),and a set of points,
//   the Sample method step by step finds the next points Xi on the curve
//   and the next parameters, all contained by the iDomain.
//   The mode of repartition of the points and the density are given by the
//   iAttributes argument.
//   The CATMathDiagnostic is CATMathOK if the Sample found a set of points.  
//   Otherwise a failure diagnostic is given.
//   The GetDiagnostic method give you the reason of the end of the sampling.   
//
//   Handled attributes: (documentation by NLD040516)
//   see Sample above
    virtual CATMathDiagnostic SampleStepByStep          (const CATMathInterval           & iDomain     ,
                                                               CATMathSetOfPointsND      & oSetOfPoints,
                                                               CATMathSetOfPointsND      & oSetOfParam ,
                                                         const CATMathAttrList          *  iAttributes = 0);

//  Get the ending diagnostic of samplimg algorithm:
//   . CATMathStopBySingularPoint : The last point is a singular one 
//   . CATMathStopByUserConstraint: The last point is the last of th iDomain     
//   . CATMathStopInsideDomain    : The last point is singular and is strictly inside 
//                                  the Domain (cusp, ...)
    virtual CATMathStopDiagnostic GetDiagnostic         () const;

// Evaluators: iX is a point in R.
//  . oFX = F(iX) is the image of iX by F. oFX      is in RN and is already allocated. 
//  . oDFX  is the first  derivative of F at iX and is in RN and is already allocated. 
//  . oD2FX is the second derivative of F at iX and is in RN and is already allocated. 
//  . oTX   is the normed tangent at iX         and is in RN and is already allocated.
    virtual void               Eval                     (const double                      iX   ,
                                                               double                   *  oFX  ) const = 0;

    virtual void               EvalFirstDeriv           (const double                      iX   ,
                                                               double                   *  oDFX ) const;

    virtual void               EvalSecondDeriv          (const double                      iX   ,
                                                               double                   *  oD2FX) const; 

    virtual void               Eval                     (const double                      iX   ,
                                                               double                   *  oFX  ,
                                                               double                   *  oDFX ) const;

    virtual void               EvalDeriv                (const double                      iX   ,
                                                               double                   *  oDFX ,
                                                               double                   *  oD2FX) const;

    virtual void               Eval                     (const double                      iX   ,
                                                               double                   *  oFX  ,
                                                               double                   *  oDFX ,
                                                               double                   *  oD2FX) const;

    virtual void               EvalTangent              (const double                      iX   ,
                                                               double                   *  oTX  );

            // Step calculation : find step at point iXcur.
    virtual double             EvalStep                 (const double                      iX   ,
                                                               double                      d    ,
                                                               double                      f    );

         // Step calculation : find step at point iXcur.
            void               SetDim                   (const CATLONG32                   iN   ); 

// Storage Feature
            int                GetNumberOfPoints        () const;
    // Return the quantity of stored points

            void             SelectWellDistributedPoints(const double                      iParam0,
                                                         const double                      iParam1,
                                                         const CATLONG32                   NbSample,
                                                               double                   *  oLambda) const;
    // Recherche NbSample points bien repartis dans l'intervalle (ouvert) de parametres donnes.
    // Choisit dans la mesure du possible des points deja calcules.
    // Renvoie le resultat sous la forme d'un tableau de poids entre 0 et 1 (strict).

   // Recherche dans un segment [iW0,iW1] des parametres de discontinuites de type iTDIST ( C2 ou C1 )
   // En sortie Type et Parametre de dist
   // Dans un premier temps seules les discontinuites C1 sont detectées 
            CATMathDiagnostic FindC1Discontinuity       (      double                      iW0  ,
                                                               double                      iW1  ,
                                                               CATLONG32                   iTDist,
                                                               CATLONG32                 & oTDist,
                                                               double                    & oWDist,
                                                               CATBoolean                & oFound);

   //Versionning par set en attendant les migrations client pour correct Ri Ext - EAB
            void               SetNoInstability         ();
  
            void               SetOKScaleReviewed       ();

            CATSoftwareConfiguration* GetSoftwareConfiguration()                                    const;
            void                      SetSoftwareConfiguration
                                                        (      CATSoftwareConfiguration *  iSoftwareConfiguration) ;


  ////////////////
  // Protected  //
  ////////////////
  protected:

//
// Eval estimated square curvature at a point
//
            double             EvalSquareCurvature      (const double                      iX   ,
                                                               double                      n    );

 
//
// Eval norme of estimated derivative at a point
//
            double             NormedFirstDeriv         (const double                      iX   ); 
//  
// Find marching orientation at every  point  
//  
            double             ScalarProduct            (const double                   *  iCurrentTangent,
                                                               double                   *  iStartTangent  );
//  
// Compute the distance between two successives points, and return 0 if the  
// distance is bigger than  max previously fixed. 
//
            CATLONG32          IsPointNotTooFar         (const double                   *  iCurrentPoint  ,
                                                               double                   *  iNextPoint     );
//  
// Recording of a new good point & a new param in the sets of points  
//
            CATLONG32          RecordPoint              (const double                      iX             ,
                                                               CATMathSetOfPointsND      & oSetOfPoints   ,
                                                               CATMathSetOfPointsND      & oSetOfParam    );
//  
// Recording of a new good point & a new param in the sets of points  
//
            CATLONG32          IsGoodPoint              (      double                    & iX             ,
                                                         const CATMathIntervalND         & DomainX        );
//  
// Equal the parameter with the specific one given by user  
//
            void               AdjustParam              (      double                    & iX             ,
                                                               CATLONG32                   i              ,
                                                         const double                   *& iStopParam     ,
                                                         const double                   *  p              );
//  
// Increase the parameter  
//
            void               GoNext                   (      double                    & iX             ,
                                                               double                    & iStep1         ,
                                                               double                    & iStep2         ,
                                                               double                      t0             ,
                                                               double                      tf             );
//  
// Global test to estimate the best parameter for the sample method.
//
            CATLONG32          GlobalPrediction         (      double                      t0             ,
                                                               double                      tf             );
//
// Singularity verification : find is point iXcur is singular.
//
    virtual CATLONG32          IsFirstDerivNull         (const double                      iX             );
//
// Return Step at Current point where curvature and sag are given and step
// must be between MinStep and MaxStep
//
    virtual double             EvalStepWithSquareCurvature
                                                        (const double                      iSquareCurvature,
                                                         const double                      iSag            ,
                                                         const double                      iMinStep        ,
                                                         const double                      iMaxStep        ,
                                                         const double                      iNorme          ); 
//
//  Convergence to X where G(X) = 0 , G(X) a constraint 
//   An initial guess ioX is given for X.
//   The CATMathDiagnostic is CATMathOK if the Solve found a point. 
//   Otherwise a failure diagnostic is given:
//    . CATMathMaxIteration  
//    . CATMathOutOfDomain 
//
    virtual CATMathDiagnostic  SolveOnConstraint        (      CATMathConstraint        *  G               ,
                                                               double                    & ioX             );
//
//  Convergence to X where F(X) = 0,
//   An initial guess ioX is given for X.
//   The CATMathDiagnostic is CATMathOK if the Solve found a point. 
//   Otherwise a failure diagnostic is given:
//    . CATMathMaxIteration  
//    . CATMathOutOfDomain 
//
    virtual CATMathDiagnostic  SolveOnDomainBorder      (const double                      id              ,
                                                         const CATLONG32                   iu              ,
                                                               double                    & ioX             ); 
//
//  Convergence to X where F'(X) = 0 ,  
//   An initial guess iX is given for X.
//   The CATMathDiagnostic is CATMathOK if the Solve found a point. 
//   Otherwise a failure diagnostic is given:
//    . CATMathMaxIteration  
//    . CATMathOutOfDomain 
//
    virtual CATMathDiagnostic SolveOnSingularity        (      double                    & ioX             );


// Recording Some Evaluations
//   These methods can be included in the evaluators for the derivate classes.
//   They let you store some evaluations in order to avoid repeating them in the future.
//   Storage is made in increasing order for the parameter.
//    !!!! Warning : Indexes start at 1 !!!! (rule for CATLISTP types)
//   Some of the following members are "const" since they are supposed to be called in
//   evaluators...
 
           void               SetStorageFeature         (      CATBoolean                  value           );
  // Toggles ON/OFF the storage feature. Default is OFF.
  // If ON, storage will be made by default evaluators.
  // These evaluators always check if the value is precomputed.

           CATLONG32          GetStatusInStock          (      double                      iparam          ) const;
  // Check if the function has already been computed for this value of parameter.
  // Return -1 if not, the order of the storage otherwise.
  
           CATLONG32          GetStatusInStock          (      double                      iparam          ,
                                                               int                      *  oind            ) const;
  // Idem, where you get in oind the position of the point in the stock.
  // If the point is not present, you may insert it at position oind.

           void               UpdateStock               (      double                      iparam          ,
                                                               double                   *  point           ,
                                                               double                   *  fder            = 0,
                                                               double                   *  sder            = 0) const;
  // Adds a point or updates it to the stock.

           void               UpdateStock               (      int                         ipos            ,
                                                               double                      iparam          ,
                                                               double                   *  point           ,
                                                               double                   *  fder            = 0,
                                                               double                   *  sder            = 0) const;
  // Adds a point or updates it to the stock. Faster because you give the position.
  // You must give the RIGHT position where the point is or must be added in the stock,
  // with respect to the increasing order.

   virtual CATBoolean         EqualForStorage           (      double                      iparam1         ,
                                                               double                      iparam2         ) const;
   // TRUE if parameters are equal with tolerence CATEpsilon (1.e-15)
   // You can surcharge this method to define your tolerence.

           void               ResetStock                ();
  // Reset the stock.
  // Does not change Storage Feature status (on/off).

           void               CreateOrReplaceInStock    (      CATBoolean                  CreateNew       ,
                                                               int                         pos             ,
                                                               double                      iparam          ,
                                                               double                   *  point           ,
                                                               double                   *  fder            = 0,
                                                               double                   *  sder            = 0) const;
  // Obvious.
  // Note that the parameter can not be updated if CreateNew is FALSE, and is ignored in that case.

           void               GetStockItem              (      int                         ipos            ,
                                                               double                    & oparam          ,
                                                               CATLONG32                 & oorder          ,
                                                               double                   *  odata           ) const;
           void               GetDataFromStock          (      int                         ipos            ,
                                                               double                    & oparam          ,
                                                               double                   *  point           = 0,
                                                               double                   *  fder            = 0,
                                                               double                   *  sder            = 0) const;
           void               GetDataFromStock          (      int                         ipos            ,
                                                               double                    & oparam          ,
                                                               CATLONG32                 & oorder          ,
                                                               double                   *  point           = 0,
                                                               double                   *  fder            = 0,
                                                               double                   *  sder            = 0) const;
           void               GetPointFromStock         (      int                         ipos            ,
                                                               double                   *  point           = 0,
                                                               double                   *  fder            = 0,
                                                               double                   *  sder            = 0) const;
  // Get information at position ipos from stock.
  // If stored order is less than required, you may get NULL pointers as result.

           double             NearestCalculatedParam    (const double                      iparam0         ,
                                                         const double                      iparam          ,
                                                         const double                      iparam1         ,
                                                               CATLONG32                *  ind             = 0) const;

  ////////////////
  // Private    //
  ////////////////

 private:
            void               Init                     (      CATSoftwareConfiguration *  iConfig,
                                                         const CATLONG32                   iN     );

//
// Allocate the memory for the protected datas
//
           void                Allocation               ();
//
// Desallocate the memory for the protected datas
//
           void                Desallocation            ();

           void CATMathVectorialFunctionXParallelDebugCond
                                                        (const CATMathInterval           & iD              ) ;

           void               SampleInit                (const CATMathInterval           & Domain          ,
                                                               CATMathSetOfPointsND      & SetOfPoints     ,
                                                               CATMathSetOfPointsND      & SetOfParam      ,
                                                         const CATMathAttrList          *  Options         ,
                                                         const CATMathAttribute         *& oLimite         ,
                                                               CATMathIntervalND        *& oDomainX        ,
                                                         const CATMathAttribute         *& oStopPoints     ,
                                                         const CATMathAttribute         *& oContraintes    ,
                                                               CATLONG32                 & oNbParam        ,
                                                         const double                   *& oP0
                                                        ) ;

//----------------------------------------------------------  
// DATA
//----------------------------------------------------------  

 private:
    CATSoftwareConfiguration     *  _Config;


 protected:
  const CATTolerance              & _TolObject;
        CATMathStopDiagnostic       _Diagnostic;
        double                   *  _CurrentPoint;
        double                   *  _NextPoint;
        double                   *  _CurrentTangent;
        double                   *  _NextTangent;
        double                   *  _DF;
        double                   *  _D2F;
        double                   *  _Deriv;
        double                   *  _Deriv2;
        double                   *  _FX;
        double                   *  _DFXLocalplus,
                                 *  _DFXLocalmoins;
  const double                   *  _StopParam;
        double                      _Sag,
                                    _MinStep,
                                    _MaxStep,
                                    _SagPoint,
                                    _DummyMinStepPoint, //NLD270508 renommee car pas initialisee correctement
                                    _CosMin,
                                    _SquareMaxStepPoint;
        double                      _GlobalEps ;
        CATMathInterval             _Domain;
        CATLONG32                   _N,
                                    _Orientation,
                                    _LookMax,
                                    _PointOK,
                                    _TangentsOK; 

  // Versionning par set en attendant les migrations client pour correct Ri Ext - EAB
        CATBoolean                  _NoInstability;


  // Seaches nearest already calculated parameter in specified interval.
  // The search starts from index ind if specified, else 1.
  // If no param is found, return iparam and *ind does not change.
  // If one param is found, you get its index in *ind.
  
        CATBoolean                  _StorageFeature;

  ////////////////
  // Private    //
  ////////////////
private:

        CATLONG32                   _OnlyDecomposition,
                                    _StoreTangent     ,
                                    _StoreVector      ;
        CATMathAttrDecomposition *  _Decomposition    ;
  
        CATLISTP(CATMathEvalRecord) _Stock;
        CATMathVectorialFunctionX*  _me;

        int                         _OKScaleReviewed;
        int                         _ScaleAlreadyChecked;
        int                         _CGMLevel;

//
//
};  
#endif  
