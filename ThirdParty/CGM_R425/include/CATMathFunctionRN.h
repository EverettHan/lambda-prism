#ifndef CATMathFunctionRN_H
#define CATMathFunctionRN_H
// COPYRIGHT DASSAULT SYSTEMES 1997
//===================================================================
//
// CATMathFunctionRN :
// Abstract class of functions of N variables
//
// XScaleRules:                                                                                 (NLD220216)
// 1) standard behaviour
//  1.a) parameters
//  - domains         must behave like power 1 of factory scale
//  - parameters      must behave like power 1 of factory scale
//  - steps  computed must behave like power 1 of factory scale
//  otherwise standard derivative computations must not be used,
//  or steps _h1, _h2, _h3 must be adapted by derived class constructor
//  1.b) function result
//  - function        must behave like power 2 of factory scale
//                    if Minimize() to be used
// 2) other behaviours not handled
//  - standard behaviour is mandatory: no CATMathAttrScaleOption attribute taken into account for now,
//    neither in constructor nor in Minimize() attributes list
//    otherwise Minimize() must be implemented in derived class
//    if used
//===================================================================
// 17/10/11 NLD Ajout argument iConfig à Minimize()
// 06/03/13 NLD Ajout _Config, _h1, _h2, _h3
//              Ajout _TolObject
//              Arguments iTolObject et iConfig au constructeur
//              Ajout Init(), Set() et constructeur par copie
// 07/03/13 NLD _Config est remplacee par _ConfigHandler pour securisation tous contextes
// 22/02/16 NLD XScaleRules
//              Smart indent
// 28/05/18 NLD Deflaggage: suppression option de precompilation, le code actif (classe mère et classes derivées)
//              reste celui avec _ConfigHandler
//===================================================================
#include "CATIACGMLevel.h"

#include "YN000FUN.h"

#include "CATMathDef.h"
#include "CATMathDiagnostic.h"
#include "CATMathInterval.h"
#include "CATMathFunctionGeneral.h"

class CATTolerance;
class CATMathAttrList;
class CATMathIntervalND;
class CATMathSetOfPointsND;
class CATMathFunctionX;
class CATMathFunctionXY;
class CATMathNxNFullSymMatrix;
class CATSoftwareConfiguration;
#include "CATSoftwareConfigurationHandler.h"
//--------------------------------------------------------------------------
class ExportedByYN000FUN CATMathFunctionRN : public CATMathFunctionGeneral 
{

 // -------
 // Methods
 // -------

 // public methods
 public:

  //--------------------------------------------------------------------------
  //  Object management
  //--------------------------------------------------------------------------

  //
  //-  Constructor (iNumberOfVariables is the number of unknowns of the function)
  //
                              CATMathFunctionRN             (const CATLONG32                 iNumberOfVariables,
                                                                   CATSoftwareConfiguration* iConfig           = 0,
                                                             const CATTolerance            * iTolObject        = 0
                                                            );

                              CATMathFunctionRN             (const CATMathFunctionRN       & iF                );

  //
  //- Virtual Destructor
  //
  virtual                     ~CATMathFunctionRN            ();

  //
  //- Duplicator
  //
  virtual CATMathFunctionRN * Duplicate                     () const = 0;
  virtual CATMathFunctionRN * DeepDuplicate                 () const;
#if defined ( CATIACGMR216CAA )
  virtual CATMathFunctionRN * DeepDuplicateWithTol          (const CATTolerance            * ipTolObject   ) const;
#endif

  //--------------------------------------------------------------------------
  // Information methods
  //--------------------------------------------------------------------------
  virtual CATBoolean          IsAKindOf                     (const CATMathClassId            iClassId      )    const;

  //  Get the number of variables of the function (_N) 
          CATLONG32           GetNumberOfVariables          ()                                                  const;
   
  //-----------------------------------------------------------------
  // Evaluators on doubles
  //-----------------------------------------------------------------   
  // CAUTION: see XScaleRules above for derivative evaluations
  //-----------------------------------------------------------------   
  virtual double              Eval                          (const double                  * iX            )    const = 0;

  // In the following, iVar0, iVar1 and iVar2 represent the index of the variable
  // between 0 and _N-1
  virtual double              EvalFirstDeriv                (const CATLONG32               & iVar0         ,
                                                             const double                  * iX            )    const;

  virtual double              EvalSecondDeriv               (const CATLONG32               & iVar0         ,
                                                             const CATLONG32               & iVar1         ,
                                                             const double                  * iX            )    const;

  virtual double              EvalThirdDeriv                (const CATLONG32               & iVar0         ,
                                                             const CATLONG32               & iVar1         ,
                                                             const CATLONG32               & iVar2         ,
                                                             const double                  * iX            )    const;

  //
  // Evaluator of function and derivatives at the same time :
  // (performance are increased if redefined in derived classes)
  // iOption is a command which contains which derivatives are requested
  // (usually, iOption = OptionEval + OptionEvalFirstDeriv)
  // -  If (iOption & OptionEval), compute in *f the value of the function at iX
  // -  If (iOption & OptionEvalFirstDeriv), compute in *df the value of all the first
  //    derivatives of the function at iX.
  // -  If (iOption & OptionEvalSecondDeriv), compute in *d2f the value of all the second
  //    derivatives in d2f : d2f[_N*i+j] = (d^2 f)/(dx_i x_j)
  virtual void                Eval                          (const double                  * iX            ,
                                                             const CATMathOption             iOption       ,
                                                                   double                  * f             ,
                                                                   double                  * df            = 0,
                                                                   double                  * d2f           = 0) const;

  virtual void                Eval                          (const double                  * iX            ,
                                                             const CATMathOption             iOption       ,
                                                                   double                  * f             , 
                                                                   double                  * df            ,
                                                                   CATMathNxNFullSymMatrix * Hessian       )    const;



  //-----------------------------------------------------------------
  // Evaluators on intervals
  //-----------------------------------------------------------------
  virtual CATMathInterval     Eval                          (const CATMathIntervalND       & iD            )    const;
  virtual CATMathInterval     EvalFirstDeriv                (const CATLONG32               & iVar0         ,
                                                             const CATMathIntervalND       & iD            )    const;
  virtual CATMathInterval     EvalSecondDeriv               (const CATLONG32               & iVar0         ,
                                                             const CATLONG32               & iVar1         ,
                                                             const CATMathIntervalND       & iD            ) const;
  virtual CATMathInterval     EvalThirdDeriv                (const CATLONG32               & iVar0         ,
                                                             const CATLONG32               & iVar1         ,
                                                             const CATLONG32               & iVar2         ,
                                                             const CATMathIntervalND       & iD            ) const;
   
  //-----------------------------------------------------------------
  // Composition creation
  //-----------------------------------------------------------------

  //
  // Create the FunctionX defined by : t-> Phi( F_0(t), ..., F_{_N-1}(t) ) 
  // where Phi represents the FunctionRN "this", and F_i = iTabFunctionX[i].
  // WARNING : The returned pointer must be deleted by the caller.
  //
  virtual CATMathFunctionX  * CreateCompositionX            (const CATMathFunctionX       ** iTabFunctionX ) const;

  //
  // Create the FunctionXY defined by : (u,v) -> Phi( F_0(u,v), ..., F_{_N-1}(u,v) ) 
  // where Phi represents the FunctionRN "this", and F_i = iTabFunctionXY[i].
  // WARNING : The returned pointer must be deleted by the caller.
  //
  virtual CATMathFunctionXY * CreateCompositionXY           (const CATMathFunctionXY      ** iTabFunctionXY) const;


  //-----------------------------------------------------------------
  // Minimization
  // Min F(x) where x is the given Domain.
  // The minimization takes the bounds of the Domain in account.
  //-----------------------------------------------------------------
  // CAUTION: see XScaleRules above for miminize use
  virtual CATMathDiagnostic   Minimize                      (const CATMathIntervalND        & iDomain    ,
                                                                   CATMathSetOfPointsND     & ioRoots    ,
                                                             const CATMathAttrList          * attributes = 0,
                                                                   CATSoftwareConfiguration * iConfig    = 0) const;
 
 protected:

          void                      Set                     (const CATMathFunctionRN        & iF         );

          CATSoftwareConfiguration* GetSoftwareConfiguration()                                                const;

 private:

          void                      Init                    ();

 // -------
 // Data
 // -------

 protected:

  CATLONG32                       _N; // Number of variables of the function
  double                          _h1,
                                  _h2,
                                  _h3;
  const CATTolerance            * _TolObject;

 private:

                                        // Afin de permettre une gestion implicite aisee et securisee
                                        // des AddRef/Release sur les configurations, en particulier en cas
                                        // d'appel au constructeur par copie implicite d'une classe derivee
                                        // il vaut mieux avoir un handler, dont la recopie automatique
                                        // gerera correctement le compteur de reference,
                                        // qu'un pointeur qui sera recopie sans increment du compteur
                                        // Necessaire en particulier pour activer l'envoi d'une configuration
                                        // par CATPlaneCGM::CreateImplicitEquation(), dont la securisation
                                        // du cycle de vie rend absolument necessaire l'increment de compteur
                                        // depuis notre classe CATMathFunctionRN
                                        // avant meme que toutes les classes derivees aient ete mises au propre
                                        //          NLD070313
        CATSoftwareConfigurationHandler _ConfigHandler;
};

#endif
