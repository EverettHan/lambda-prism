//===================================================================
// Header definition of class CATMathOptimizer
// Previously CATMathOptimize
//===================================================================
//
// Usage notes:
// Class that represents the Global Optimization Solver.
// 
// 
// Global Optimization Solver     
// Objective function F(iaX, data)       
// 
// 
// Finds oX that realizes the minimum value of F(iaX, data) inside given bounds [_aXMin, _aXMax].               
// F may or not be differentiable, no gradient evaluation is required.   
// 
//    Global algorithm as Evolutionary Algorithms are available: 
//      Particle Swarm Optimization (PSO)
//       --> An initial population evolves during several generations to converge to the global optimum.
//      BAT Algorithm (BA)
//       --> An initial population evolves during several generations to converge to the global optimum.
// 
//    Local algorithms are also available
//       Nelder-Mead (NM)
//       --> A starting point is required
// 
//    A Global hybrid method is also available:
//       --> First, a global algorithm is launched, then a local algorithm is performed. 
//
//    CATOptReal default type is double. 
//    Changing default type is possible in CATMathOptTools.h
//
// Notice that in YN000FUN there is the class CATMathGAOptimizer (Genetic algorithm)
//                which is also a global method based on population.
//                In the long term, it will be  beneficial to migrate it in this fw.   
//               
//===================================================================
//  Creation  : Gabrielle SABATIER
//  Industrialization 2012-08-08 : E.-M. Duclairoir/KJD 
//   - new class : CATOptParam
//   - addition of the Get/SetOptParam methods which modify
//       or return the intrinsic parameters of the different clustering algorithms 
//   - addition of the GetImplementationMethod method which gets access to the internal optimization methods. 
//   - addition of the GetClusteringMethod method which gets access to the internal clustering methods. 
//   - ascent of the GetBestPoints method
//   Rearchi 2016-06-10 KJD 
//   - deprecation of the Init methods with function ptr and of the APIs with String replaced by APIs with enums
//   - addition of the Create method with software config and tolerance
//   - removal APIs with CATOptFuntion replaced by APIs with CATMathOptFuntion and CATMathOptSystem
// 15Dec16 KJD Deletion of the param iweight in AddExpression to be as general as possible initially
// 02/02/17 KJD Addition of the method EvalAll 
// 08/02/17 KJD Addition of the class elements _EqConstrNb, _GlobalSystem to drive Constrained Optim via Penalty method
// 22/03/17 KJD Addition of SetPenaltyCoeff to manage internally the coefficients used for constraints in the penalty method
// 02/05/17 KJD 1)Rearchi of CATMathOptimizer, split between interface(CATmathoptimizer) and the implementation (CATOptManager)
//              => deletion of the friend links, of some internal data (_GlobalSystem, _best, ...) or of the protected services (GetXXXXProtected, SnapToDomain, ...)
//              => addition of new elements _pOptimAlgo, _MethodId, _ToUpdate, _ListOfOptParamLabel, _ListOfOptParamValue
//              => Some APIs become (pure) virtual  SetData, GetBestPoints, GetBestPoint, AddExpression
//              => new API InitAlgo to provide to implementation the settings
//              2) To prepare Maximization , addition of the new class element _Minimization and of the new API SetMaximization
//              3) Modification of GetNorm API, caller have to precise the type of impacted system
//              4) outsourcing of the static methods (GetMethodName/GetParamLabel/GetDescription/GetMethodFromDescription) into CATOptTools 
// 16/05/17 KJD Taking into account of Bounding Constraints (_BoundConstraints,AddBoundConstraint) 
// 20/09/17 KJD Adddition of the Flag  AddAsBoundConstraint in SetDomain to enable to treat all the bounds of the domain as bound constraints.
//              WARNING : the problem becomes constrained in that case
// XX/11/17 KJD Adddition of the API AddLinearConstraints to manage the linear constraints thanks to matrices and right-hand sides
// 10/05/18 KJD Full migration to the new architecture (since 2017 for R420 but Migration postponed for CXR28 because of an ICEM dependancy)
//===================================================================
#pragma once
#ifndef CATMathOptimizer_H
#define CATMathOptimizer_H

#include "CATIAV5Level.h"
//#ifndef CATIAR420 
//#define CATMathOpt_OldArchi
//#endif

#include "YN000OPT.h"
#include "CATOptTypes.h"
#include "CATOptParam.h"
#include "CATTolerance.h"
#include "CATToleranceAccess.h"
#include "CATListOfInt.h"
#include "CATLISTP_CATOptParam.h"
#include "CATOptParam.h"
#ifdef CATMathOpt_OldArchi
#include "CATOptFunction.h"
#endif

class CATMathOptFunction;
class CATMathOptSystem;
class CATSoftwareConfiguration;
class CATOptManager;
class CATMathMxNMatrix;

class ExportedByYN000OPT CATMathOptimizer 
{ 
public:
  /** 
  * Constructor.
  * Initialization of the class parameters (space size, function identity, ...)
  * @param iConfig      the provided software configuaration
  * @param iTolObject   the set of geometric and mathematical tolerances used during the solving
  * @param iSpaceSize   the value of space dimension.
  */
  CATMathOptimizer (CATSoftwareConfiguration * iConfig, const CATTolerance  & iTolObject, CATULONG32 iSpaceSize, CATOptMethodId iMethodId);



  /**
  * Destructor.
  */
  ~CATMathOptimizer ();

 /** 
  * Sets the boundaries of the working space. Default values are 0 and 1 in each direction.
  * @param iaXMin  Vector of space size dimension which contains the lower bounds of the search domain.
  * @param iaXMax  Vector of space size dimension which contains the upper bounds of the search domain.
  * @param iAddAsBoundConstraint  boolean to manage or not all the bounds of the domain as bound constraints.
  * WARNING : with iAddAsBoundConstraint = TRUE, the bounds are treated as bound constraints and the problem becomes constrained.   
  */
  virtual void SetDomain (CATOptReal const * iaXMin , CATOptReal const * iaXMax, CATBoolean iAddAsBoundConstraint = FALSE);

  /** 
  * Set/Get the maximum number of evaluations.
  * @param iEvaluationMax       New value of the maximum number of evaluations.
  */
  virtual void       SetNumberOfEvaluations (CATULONG32);

  virtual CATULONG32 GetNumberOfEvaluations () const;

  /**
  * Sets the treshold and precision values.
  * @param iThreshold New value of the treshold.
  * @param iPrecision New value of the presicion.
  */
  virtual void SetStopObjective (CATOptReal iThreshold, CATOptReal iPrecision);

  /**
  * Add an expression to the system 
  * @param S                        Either sObjective/sEqualityConstraint/sInequalityConstraint
  * @param pf                       Expression
  */
  virtual void AddExpression(CATOptExprType S, CATMathOptFunction * pf);

  /**
  * Add a bound constraint to the system 
  * @param iIdxVar        index of the involved variable   
  * @param iBound         value of the bound
  * @param iUpperBound    nature of the bound (TRUE if upper bound, FALSE if lower bound)
  */
  void AddBoundConstraint(CATULONG32 iIdxVar, CATOptReal iBound, CATBoolean iUpperBound = TRUE);

  /**
  * Add a set of linear constraints to the system 
  * @param S                        Either sEqualityConstraint/sInequalityConstraint
  * @param iMatrix                  the m-by-n linear constraint matrix with m the number of expressions and n  the number of involved variables
  * @param iRHS                     the m coefficients of the right-hand sides of the constraints 
  */
  virtual void AddLinearConstraints(CATOptExprType S, CATMathMxNMatrix & iMatrix , CATOptReal * iRHS);


  /**
  * Set the norm used for the computation of the Objectif or the Contraints
  * @param S                        Either sObjective/sEqualityConstraint/sInequalityConstraint
  * @param iNorm                   The new norm to use
  */
  void SetNorm(CATOptExprType S, CATOptNorm iNorm);


  /** 
  * Sets/Gets the specific parameters of the different optimization algorithms  
  * iNameParam is the name of the parameter 
  * iParamValue its value
  * returns S_OK if the action is performed otherwise S_FALSE or E_FAIL
  */
   HRESULT SetOptParam ( const CATOptParamLabel & iNameParam, CATOptParam & iParamValue);

   //HRESULT GetOptParam ( const CATOptParamLabel & iNameParam, CATOptParam  & oParamValue);

  /** 
  * Performs the optimization algorithm.
  * @param  ioaBestPoint Best point coordinates at the end of the algorithm.\
  *  If it's a local method, it's also the start point.
  *  For global method see CATOptPopulationBasedGlobalMethods::SetStartPoints
  *  WARNING  :  The returned value is the found minimum value of the provided system relative to a  norm.
  *              According to the optimization methods, the selected norm can be imposed.
  *              It can differ from the awaited  minimum because of the norm.
  *              It is highly advised to compute again the minimum with the wanted norm.    
  */
  virtual CATOptReal Run (CATOptReal *) ;

  /** 
  * Selects the best point (that means the point with a minimum value).
  * @param oBestPoint        Output parameter which may contain the best point coordinates.
  * @return                  0 if the best point is returned , 1 if not.
  */
  int GetBestPoint (CATOptReal *) const;

  /**
  * Selects several best points (that means points with the lowest values).
  * @param oBestPoint        Output parameter which may contain the best points coordinates.
  * @param ioBestPoints      Input parameter which contains the number of best points the user wants to consider. Output parameters which contains the actual number of clusters.
  * @return                  0 if oBestPoint contains the best points coordinates, 1 if not. 
  */
  int GetBestPoints (CATOptReal*, CATULONG32 &);

  /**
  *  Returns the properties of the method decribed by its id to build a class instance using its properties :
  //To update every time there is a new method
  */
  virtual CATOptDescription GetDescription();

  /**
  * Get the value of the space dimension.
  */
 CATULONG32 GetSpaceSize() const;
 
  /**
  * Get an expression of the system 
  * @param S                       Either sObjective/sEqualityConstraint/sInequalityConstraint
  * @param iIdxFunction            index of the awaited function  (included between 0 and the number of  functions -1)
  * @return                        the associated CATMathOptFunction if exists or null otherwise
  */
   CATMathOptFunction *  GetExpression(CATOptExprType S, CATULONG32 iIdxFunction) const;
   
  /**
  * Get the global number of the expressions of the system (objective expressions + constraints )
  * @return    the global number of the expressions
  */
   int  GetExpressionNumber() const;

  /**
  * Get the number of the expressions of the system according to its nature (objective  or constraints)
  * @param S   Either sObjective/sEqualityConstraint/sInequalityConstraint
  * @return    the global number of the expressions
  */
   int GetExpressionNumber(CATOptExprType S) const;

   CATOptNorm GetNorm(CATOptExprType S) const;


private:
  CATMathOptimizer ();
  CATMathOptimizer (CATMathOptimizer const &);
  CATMathOptimizer& operator= (CATMathOptimizer const &);

 //===========================================================================================================
  //
  //  DEPRECATED Methods
  //
  //===========================================================================================================
  public :
  /** 
  * deprecated
  * Constructor.
  * Initialization of the class parameters (space size, function identity, ...)
  * @param iConfig the provided software configuaration
  * @param iSpaceSize   the value of space dimension.
  * @param iTolObject the set of geometric and mathematical tolerances used during the solving
  * @note Use AddExpression to define the identity of the function to works on and any pointer needed by it
  */
 // CATMathOptimizer (CATSoftwareConfiguration *  iConfig, CATULONG32 iSpaceSize, const CATTolerance    & iTolObject = CATGetDefaultTolerance());

#ifdef CATMathOpt_OldArchi
  /** 
  * deprecated
  * Constructor.
  * Initialization of the class parameters (space size, function identity, ...)
  * @param iSpaceSize   The value of space dimension.
  * @param ipF          The identity of the function to work on.
  * @param idata        Any pointer needed by the objective function.
  */
  CATMathOptimizer (CATOptMethodId iMethodId, CATULONG32, CATOptFunctional, void const * = 0);


  virtual void SetData(CATOptFunctional, void const * = 0);

  /**
  *  @deprecated 
  *  Enables the user to build a class instance using the name of the class.
  *  @param iNameMethod    Name of the class.
  *  @param iSpaceSize     The value of space dimension.
  *  @param ipF            The identity of the function to work on.
  *  @param idata          Any pointer needed by the objective function.
  *  @return               An instance of CATMathOptimizer.
  //To update every time there is a new method
  */
  static CATMathOptimizer * InitialisationMethod (CATString , CATULONG32, CATOptFunctional, void const *);

  /**
  *  @deprecated 
  *  Enables the user to build a class instance using its properties :
  *  @param iProperties    Properties of the method :  CATOpt_LOCAL CATOpt_GLOBAL CATOpt_HYBRID CATOpt_MULTIPLE_SOLUTIONS CATOpt_EQUATION_WHITEBOX CATOpt_GRADIENT CATOpt_HESSIAN 
  *  @param iSpaceSize     The value of space dimension.
  *  @param ipF            The identity of the function to work on.
  *  @param idata          Any pointer needed by the objective function.
  *  @return               An instance of CATMathOptimizer.
  //To update every time there is a new method
  */
  static CATMathOptimizer * InitialisationMethod (CATULONG32, CATULONG32, CATOptFunctional, void const *);

  /**
  * @deprecated AddExpression
  * Sets functions
  * @param iFunctions          The functions
  */
  virtual void SetFunctions(CATOptFunction *);
#endif
 
   /** 
  * Sets/Gets the specific parameters of the different optimization algorithms  
  * iNameParam is the name of the parameter 
  * iParamValue its value
  * returns S_OK if the action is performed otherwise S_FALSE or E_FAIL
  * Instance of  available  parameters :
  * "Global_StartPoints"                 (Set -> (CATULONG32, CATOptReal *)) for the global mathod based on populations
  * "Global_ClusterNumber"               (Get/Set -> CATULONG32) for the global mathod based on populations
  * "Global_RealClusterNumber"           (Get -> CATULONG32) for the global mathod based on populations

  */
 HRESULT SetOptParam ( const CATString & iNameParam, CATOptParam & iParamValue);

 //HRESULT GetOptParam ( const CATString & iNameParam, CATOptParam  & oParamValue);

 void SetMaximization();

private:
   void Init(CATSoftwareConfiguration *  iConfig,   CATULONG32 iSpaceSize);
   void InitAlgo();
   void SelectAlgo();

 //===========================================================================================================
 //
 //  DATA
 //
 //===========================================================================================================

protected:

   // Input
  CATSoftwareConfiguration  * _pConfig;
  const CATFullTolerance    & _TolObject;
  CATULONG32                  _spaceSize; // Space dimension.
  CATOptManager              * _pOptimAlgo;
  CATOptMethodId              _MethodId;
  CATBoolean                  _Minimization;
  CATBoolean                  _ToUpdate;

  CATOptReal *_aXMin;           // Vector of space size dimension which contains the lower bounds of the search domain.
  CATOptReal *_aXMax;           // Vector of space size dimension which contains the upper bounds of the search domain.

  CATULONG32  _evaluationMax;   // Maximum number of evaluations allowed.
  CATOptReal  _threshold ;      // Treshold value. When the best value is lower than the treshold value plus the precision value, the algorithm stops.
  CATOptReal  _precision;       // Precison value. When the best value is lower than the treshold value plus the precision value, the algorithm stops.

  CATListOfInt _ListOfOptParamLabel;
  CATLISTP(CATOptParam) _ListOfOptParamValue;

  //
  // Functions
  //
  CATMathOptSystem    * _Objective;
  CATMathOptSystem    * _EqualityConstraints;
  CATMathOptSystem    * _InequalityConstraints;
  CATMathOptSystem    * _BoundConstraints;

#ifdef CATMathOpt_OldArchi
  CATOptFunctional _pF;             // Objective function identity.
  void const      *_data;           // Pointer needed by the objective function.
  CATULONG32       _LM_nbFunctions; // Number of functions
  CATOptFunction * _LM_Functions;   // Functions
#endif 
  
};

//
 /**
  *  Create a class instance using the name of the class. 
  *  @param iConfig the provided software configuaration 
  *  @param iTolObject the set of geometric and mathematical tolerances used during the solving
  *  @param iSpaceSize     The value of space dimension.
  *  @param iNameMethod    Name of the class.
  *  @return               An instance of CATMathOptimizer.
  //To update every time there is a new method
  */
ExportedByYN000OPT CATMathOptimizer * CreateMathOptimizer(CATSoftwareConfiguration * ipConfig, 
                                                          const CATTolerance       & iTolObject, 
                                                          CATULONG32                 iSize,
                                                          CATOptMethodId             iMethodId);
ExportedByYN000OPT void Remove(CATMathOptimizer * & ioOper);

#endif
