#ifndef CATMathGAOptimizer_H
#define CATMathGAOptimizer_H
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 1997 
//==========================================================================
//
// CATMathGAOptimizer:
// Class for genetic algorithm optimizer 
//
//==========================================================================
// 27.04.18 KJD 1) Migration of CATMathGAOptimizer_MaxNumParameters from 10 to 100
//              2) Architecture modifications : 
//                 - outsourcing of CATMathGAPopulation in a local interface
//                 - migration from public to private of the APIs ShiftPopulation,
//                    Statistics, Initialize, InitReport, Print, GenerateXXX
//                 - deletion of the API GetOptimum
//                 - migration of the _Optimum attribute from  CATMathGAIndividual
//                    to a pointer on it
//              3) Extension to the combinatorial GA 
//                 CURRENTLY, THE COMBINATORIAL MAXIMIZATION HAS NOT BEEN YET IMPLEMENTED 
//                 In CATMathGAOptimizer via new argt in ctor and _CombinOptim
//                 - modification of bound attributes : _Low/_UpBound -> _rLow/_iLow/_rUp/_iUpBound 
//                 - addition of new APIs with CATLONG32 : GenerateXXXMin,
//                    SetParamValLimits, EvalFitness , GetOptimumParams  
//                 In CATMathGAIndividual 
//                 - addition of _iCode and of the CopyCode API
// 10.05.18 KJD Code Factorization of the methods Minmize/Maximize/GenerateMin/GenerateMax
//              thanks to the new APIs  Optimize, GenerateMinMax, GenerateContMinMax. 
//              => GenerateMin/GenerateMax are not anymore useful (deletion)
//              + new unit service IsRefFitnessReached
// 15.05.18 KJD 1) Independence of the class CATMathGAIndividual from CATMathGAOptimizer_MaxNumParameters :
//                 Previously, static allocation of the class data  with  size = CATMathGAOptimizer_MaxNumParameters
//                 From now, dynamic allocation with size the number of params of the individual
//                 => new API and new attribute in CATMathGAIndividual : _N, dtor, UpdateSize,
//                 + new definitions of_r(/l)Code : double(/CATLONG32) X[CATMathGAOptimizer_MaxNumParameters] -> double(/CATLONG32) *X  
//                 Later, CATMathGAIndividual will be moved to the header of CATMathGAPopulation and its API UpdateSize will be pure-virtual
//              2) depreciation of SetParamValLimits(double*,double*) with no size because internally copy of the pointer and not of the data of the array 
//                 If the table are deleted before optimization, the internal data will be invalid.
//==========================================================================

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "YN000FUN.h"
#include "CATDataType.h"
#include "CATSysBoolean.h"

class CATMathGAPopulation;
class CATMathGAIndividual;


class ExportedByYN000FUN CATMathGAOptimizer 
{

public:
/******************************************************************************************/
/*** Optimizer  Constructor :                                                             */
/******************************************************************************************/
  CATMathGAOptimizer(CATBoolean iCombinatorialOptim);
/******************************************************************************************/
/*** Optimizer Destructor :                                                               */
/******************************************************************************************/
  ~CATMathGAOptimizer();
/******************************************************************************************/
/*** Function to define by the current problem :                                          */
/***     -In_Arg_1 : Number of parameter                                                  */
/***     -In_Arg_2 : Current point values                                                 */
/*** WARNING : According to the selected optimisation (continuous or combinatorial),      */
/***           implement the right EvalFitness  !!                                          */
/******************************************************************************************/
  virtual double EvalFitness           (CATLONG32,double*) = 0;  
  virtual double EvalFitness           (CATLONG32,CATLONG32*) {return 0.;};  
/******************************************************************************************/
/*** Sets the maximum number of iterations :                                              */
/***     -In_Arg_1 : MaxNumber value                                                      */
/******************************************************************************************/
  void    SetMaxNumber           (CATLONG32);
/******************************************************************************************/
/*** Sets Crossover value :                                                               */
/***     -In_Arg_1 : CrossOver Value                                                      */
/******************************************************************************************/
  void    SetCrossValue          (double);
/******************************************************************************************/
/*** Sets Mutation value :                                                                */
/***     -In_Arg_1 : Mutation Value                                                       */
/******************************************************************************************/
  void    SetMutatValue          (double);
/******************************************************************************************/
/*** Sets the Number of Parameter of the problem :                                        */
/***     -In_Arg_1 : Number of parameters                                                 */
/******************************************************************************************/
  void    SetNumParams           (CATLONG32);
/******************************************************************************************/
/*** Sets the Size of the Population :                                                    */
/***     -In_Arg_1 : Size of Population                                                   */
/******************************************************************************************/
  void    SetPopulationSize      (CATLONG32);
/******************************************************************************************/
/*** DEPRECATED SetParamValLimits                                                                          */
/*** Sets the Limits of parameters                                                        */
/***     -In_Arg_1 : Table of Low values                                                  */
/***     -In_Arg_2 : Table of Upper values                                                */
/*** WARNING : internally copy of the pointer and not of the data of the array            */
/***       If the table are deleted before optimization, the internal data will be invalid*/
/******************************************************************************************/
 // void    SetParamValLimits      (double*,double*); 
/******************************************************************************************/
/*** Sets the Limits of parameters                                                        */
/***     -In_Arg_1 : Size of the tables of Low/Upper values                               */
/***     -In_Arg_2 : Table of Low values                                                  */
/***     -In_Arg_3 : Table of Upper values                                                */
/******************************************************************************************/
  void    SetParamValLimits      (CATLONG32,double*,double*); 
  void    SetParamValLimits      (CATLONG32,CATLONG32*,CATLONG32*);
/******************************************************************************************/
/*** Sets the process to use :                                                            */
/***     -In_Arg_1 : Number of process                                                    */
/******************************************************************************************/
  void    SetProcess             (CATLONG32);
/******************************************************************************************/
/*** Sets the Seed to use, default value is -3 :                                          */
/******************************************************************************************/
  void    SetSeed                (CATLONG32);
/******************************************************************************************/
/*** Sets Value to use to stop iteration when best solution fitness is over               */
/*** the required one :                                                                   */
/***     -In_Arg_1 : Maximum Number of iterations when best solution never changes        */
/***                 Default value is 10                                                  */
/******************************************************************************************/
  void    SetIdemFitnessCount    (CATLONG32);
/******************************************************************************************/
/*** Sets Nmber of iterations before traecs refresh (used the trace the process)          */
/******************************************************************************************/
  void    SetRefresh             (CATLONG32);
/******************************************************************************************/
/*** Sets Value of precision to reach                                                     */
/***     -In_Arg_1 : Precision Value                                                      */
/******************************************************************************************/
  void    SetFitnessReference    (double);
/******************************************************************************************/
/*** Reads Best solution Parameters                                                       */
/****     -Out_Arg_1 : Table of parameters                                                */
/******************************************************************************************/
  void    GetOptimumParams       (double*); 
  void    GetOptimumParams    (CATLONG32*);
/******************************************************************************************/
/*** Reads Best solution Fitness                                                          */
/******************************************************************************************/
  double  GetOptimumFitness      ();

/******************************************************************************************/
/*** Global Minimization process                                                          */
/******************************************************************************************/
  void    Minimize               ();
/******************************************************************************************/
/*** Global Maximization process                                                          */
/******************************************************************************************/
  void    Maximize               ();



/******************************************************************************************/
/*** Optimizer Private Methods                                                              */
/******************************************************************************************/
private:
  /******************************************************************************************/
/*** Shifts OldPopulation with NewPopulation                                              */
/******************************************************************************************/
  void    ShiftPopulation        ();
/******************************************************************************************/
/*** Generates statitics like population maximum and minimum fitnesses                    */
/***     -In_Arg_1 : Pointer of Population                                                */
/******************************************************************************************/
  void    Statistics             (CATMathGAPopulation*);
/******************************************************************************************/
/*** Initializes the optimization process                                                 */
/******************************************************************************************/
  void    Initialize             ();
/******************************************************************************************/
/*** Generates process reports for initial values                                         */
/******************************************************************************************/
  void    InitReport             ();
/******************************************************************************************/
/*** Generates Generation reports                                                         */
/***     -In_Arg_1 : Generation number                                                    */
/******************************************************************************************/
  void    Report                 (CATLONG32);
/******************************************************************************************/
/*** Prints Individual datum                                                              */
/***     -In_Arg_1 : Individual to print                                                  */
/***     -In_Arg_2 : Individual name                                                      */
/******************************************************************************************/
  void    Print                  (CATMathGAIndividual&,char*); 
/******************************************************************************************/
/*** Global Minimization/Maximization process                                             */
/***     -In_Arg_1 : Boolean indicating if it is a minimization or a maximization         */
/******************************************************************************************/
  void    Optimize          (CATBoolean);
/******************************************************************************************/
/*** Optimization process for one generation                                              */
/***     -In_Arg_1 : Boolean indicating if it is a minimization or a maximization         */
/******************************************************************************************/
   void    GenerateMinMax    (CATBoolean);
/******************************************************************************************/
/***Minimization/Maximization process for one generation in case of continuous optimization*/
/***     -In_Arg_1 : Boolean indicating if it is a minimization or a maximization         */
/******************************************************************************************/
  void GenerateContMinMax(CATBoolean);
/******************************************************************************************/
/*** Minimization process for one generation  in case of combinatorial optimization       */
/******************************************************************************************/
  void    GenerateCombMin            ();
/******************************************************************************************/
/*** Checks if the FitnessReference is reached                                            */
/***     -In_Arg_1 : Boolean indicating if it is a minimization or a maximization         */
/******************************************************************************************/
  CATBoolean IsRefFitnessReached(CATBoolean);

/******************************************************************************************/
/*** Optimizer Private Data                                                               */
/******************************************************************************************/
private:
  CATLONG32                 _MaxNumberOfGenerations ;
  CATLONG32                 _PopulationSize;
  CATLONG32                 _NumParams;
  double                    _Pcross ;
  double                    _Pmutat ;
  double*                   _rLowBound ;
  double*                   _rUpBound ;
  CATLONG32*                _lLowBound ;
  CATLONG32*                _lUpBound ;
  double                    _FitnessReference ;
  CATLONG32                 _Process;
  CATLONG32                 _Refresh;
  CATLONG32                 _Seed   ;
  CATLONG32                 _IdemFitnessCount;
  CATMathGAIndividual*       _Optimum;
  CATMathGAPopulation*      _OldPopulation ;
  CATMathGAPopulation*      _NewPopulation ;
  CATBoolean                _CombinOptim;
  CATBoolean                _OldSetParamsValLimits;
}; 
#endif
