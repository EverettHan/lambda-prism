/* COPYRIGHT DASSAULT SYSTEMES PROVENCE 2001
 * --------------------------------------------------------
 *=========================================================
 *   PROJET:............BeamFE                             
 *   FRAMEWORK:.........SurfacicGeoOperator                  
 *   DATE:..............Dec 2001
 *   Purpose : API for BeamFE technology
 *   BeamFE is a algorithm, base on Finite Element, able to
 *          define a BSpline  one variable function 
 *          satisfying   some constraints and  minimizing 
 *          an nergy like criterion.
 *   See Also : PlateFE technology
 *   obligation to use createMethod create instance no new
 *=========================================================
 * HISTORY:
 * Sep 2012 : KTU Removes  DebugFACTORY for SetFactory()
 * Mai 2012 : NLD Ajout SetSoftwareConfiguration()
 * Dec 2001 :     definition
 **/
 


#ifndef _CATMathBeamFE_H
#define _CATMathBeamFE_H
#include "CATGMOperatorsInterfaces.h"

class CATIMathPlateCurvConstraintArray;
class CATMathNurbsMultiForm;
class CATSoftwareConfiguration;

#include"CATBoolean.h"

class CATGeoFactory;

#ifndef NULL
#define NULL 0
#endif


#include "CATPlateFEBasicFunction.h"

class ExportedByCATGMOperatorsInterfaces CATMathBeamFE : public CATPlateFEBasicFunction
{
public:

   /*
    * Virtual Constructor
    */
   virtual ~CATMathBeamFE();

/* ====================================================================== */
/* ========================= Init methods =============================== */
/* ====================================================================== */

   /*
    * Unique Method to load constraints
    * iConstArray : constraints array
    * iTolerances : array of tolerances on constraintes 
    *               its size == sizeof(iConstArray);
    * ilevel      : priotity of this group of constraints, 
    *               must use only if Progressive prosses
    *               is actived( see Set ProgressiveLoad(under) 
    *               for more informations
    * return 1 if error 0 if not
    */ 
   virtual int Load(CATIMathPlateCurvConstraintArray* iConstArray, 
                     const int ilevel = 0) = 0;

   /*
    *  Resume all the Load
    */
   virtual void ResetConstraints() = 0;

   /*
    * Load the Curve to deform
    * initCurve  : 
    * iCoefAniso : length of delta parametric size 
    * return 1 if error 0 if not
    */ 
   virtual	int LoadCurveInit(const CATMathNurbsMultiForm* initCurve,  
									  const double iCoefAniso=50) = 0;

   /*
    * Set a weight to an order of Energy
	 * Order have to be  0 <= order <= 9;
	 * to suppress an order you have to set coef = 0.
    * return 1 if error 0 if not
    */
   virtual int LoadEnergy(const int iorder, const double icoef) = 0;

   
	/*
    * Define if the approximation precessus begin with one Bezier 
	 * or with the initial Curve.
    */
	virtual void DefineInit(const CATBoolean InitLikeCurvInit = 0) = 0;


   
   /* Set the maximum number of iteration of each Phasis
	 * iNbPhase1 : Number of iteration to Find Equilibrum 
    * beetween Constraint and Energy
    * iNbPhase2 : Number of iteration to Find the best 
    *             number of vertexes on 
    *             the Delta Curve  
    * iNbPhase3 : Number of iteration to reach the wanted accuracy.
    * Warning   : Each NumberOfIteration can be Zero but
    *             one of them have to be positive
    */
	virtual void LoadNumberOfIterations(const int iNbPhase1 = 5, 
		                                 const int iNbPhase2 = 12, 
													const int iNbPhase3 = 12,
                                       const int iWithPhase4 = 0) = 0;

   /*
	*  Un mode qui vise le respect des moindre carre des la phase1
	*  C'est utile quand il, n'y a pas de phase 2 et que l'on veut tenir les tolerance coute que coute!!!
	*/
	virtual void SetQTargetMode(const CATBoolean isQTargetMode = FALSE) = 0;

   /*
    * Set the maximum number of arcs authorized in the DeltaCurve
    */
	virtual void LoadMaximumNumberOfArc(const CATLONG32 iNbMaxOfArc) = 0;

   /*
    * To force a minimal Continuity at the delta Curve
	 *	Warning : it is not used for the BindingKnots 
    * (see LoadBindingKnots() method)
	 */
	virtual void LoadMinimalContinuity(const int MinCont)=0;

   /*
    * Force some  cutting knot ( for exemple C2
    * discontinousties points)
    * iNbCut      : number of knots 
    * iCutKnot    : array of cutting knots value's
    * iContinuity : cutting continuity
    * retrun 1 for error 0 if not
    */
   virtual int  LoadBindingKnots(const int iNbCut, 
                                 const double * iCutKnot, 
                                 const int iContinuity)=0;

   /*
	 * To Set the CodeLevel 
	 * Warning this methode erase the 
    * LoadInformation (it must be call before any Load)
    * default is the best 
	 */
	virtual void SetCodeLevel(const int iCodeLevel=-1) = 0;

   /*
	 * To Set the Software Configuration.
    * SetCodeLevel remains necessary to tune code level. 
	 */

   virtual void SetSoftwareConfiguration(CATSoftwareConfiguration* iSoftwareConfiguration) = 0;

   /* ktu nb de niveau de pnt
	 * virtual	void SetMaxLeveL(const int imaxLevel) = 0;
    * virtual void SetCompactLSC(CATBoolean iOption) = 0;
    */



/* ====================================================================== */
/* =========================== Perform  ================================= */
/* ====================================================================== */
   
   /*	
    * The Complete methode to solve.
	 * The return code can be not so accurate as Run methode. 
	 *  0 : All is Ok;
	 * -1 : Warning, the result is inaccurate
	 *  1 : Error : No result are computed.
    */
	virtual int Run() =0;


/* ====================================================================== */
/* =============== To get Result and somes informations ================= */
/* ====================================================================== */

  /*
	* To read the CodeLevel 
	*/
	virtual int GetCodeLevel() const = 0;

   /* 
	 To manage Parametric Optimisation
    virtual CATPlateFEOptimUVOption* GetOptimUVOption() = 0;
   */

   /*
    * Get the initial curve
    */
	virtual const CATMathNurbsMultiForm* GetCurveInit() = 0;

   /*
    * Get the result curve
    * return 1 for error, 0 if not
    */
	virtual int GetResult(CATMathNurbsMultiForm*& oCurve) const= 0;

   /*
	 * Get the delta curve
    * return 1 for error 0 if not 
    */
	virtual int GetDeltaCurve(CATMathNurbsMultiForm*& oCurve, const CATBoolean & iInUserSpace=TRUE) const= 0;


   /*
	 * Get the Energy on the delta Surface.
    */
	virtual double GetEnergy() const= 0;

   /*
    * return the Max order of constraint loaded;
    */
	virtual int MaxConstraintOrder() = 0;	
	
	/* 
    * Dump 
    */
	virtual void Dump(const int iLevel) const = 0;

   virtual void SetFactory(CATGeoFactory* iFactory)=0;

  /**
   * ktu 17/03/03
   * SetFilterOfCuttingByRatio:
   * Permet d'activer le filtre local des decoupes
   * par les ratio des spans
   */
   virtual void SetFilterOfCuttingByRatio( CATBoolean iFilterOn) = 0;

  /**
   * ktu  24/08/04
   * Optition  pour  fixer  les extremites
   */
   virtual int FixedExtremities( CATBoolean iFixed,
                                          CATBoolean *iPos=NULL,
                                          double * iCood=NULL) = 0;

    //@NoDoc (@KTU20130821) 
   virtual int SetScale(const double iScale )=0;
 
};

ExportedByCATGMOperatorsInterfaces CATMathBeamFE * CreateBeamFE (const int idegree,
																const int iOrder);

#endif






 
