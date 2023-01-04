
#ifndef CATPlateFEBasicFunction_H
#define CATPlateFEBasicFunction_H

#include "CATGMOperatorsInterfaces.h"
#include "CATDataType.h"
#include "CATBoolean.h"
#include "CATFEMatrixType.h"
#define  CATFE_AGAIN

class CATMathPlateFEMatrix;
class CATPlateFECutting;
class CATPlateFELocalRelax;
class CATSingleVarBB;
class CATMathNurbsBipar;
class CATKnotVector;
class CATFEImposedCutting;
class CATAllPinpointConstraints;
class CATAllLinearXYZConstraints;
class CATAllLinearScalarConstraints;
class CATChangementVariables;
class CATFESparseLSCMatrix;

      
class ExportedByCATGMOperatorsInterfaces CATPlateFEBasicFunction 
{
//public:
   friend class CATMathPlateFEBasic;
protected:
  virtual ~CATPlateFEBasicFunction();

   /*
    * 
    */
   virtual int GetNbInitKnot(const int iDir, 
                              CATLONG32 & oNb)=0;

   virtual int ComputeDelta()=0;  // all ComputeSurface()=0;

   virtual int InitWeights(const double val,
                           const CATBoolean iIsAbsolute)=0; 

   virtual int InitCV()=0;

   virtual int FillCrit(      CATPlateFECutting * CutU        ,
                              CATPlateFECutting * CutV        ,
                              double            & oValEQ      ,
                        const CATBoolean          InUserSpace = TRUE,
                              double            * oRatioMax   = 0)=0; 


   /*
    * ktu 17/09/02
    * idem que fillCrit mais tient compte des poids
    */
   virtual int FillCritWithWeigth(double& oValEQ,
                                  const CATBoolean InUserSpace = TRUE) = 0; 



   virtual int  LoadDelta(const double         * iSol,
                          const CATSingleVarBB * iUBB,
                          const CATSingleVarBB * iVBB)=0;

   virtual int CreateDelta(const int   iDegreeU,
                           const int   iDegreeV,
                           const int   iEnergyOrder,
                                 int & oMultU,
                                 int & oMultV)=0; 

   virtual int MaxConstraintOrder()=0;



   /*
    * Compute Init Weight form mean tol, and the input variables
    * oTolMoy : the initial Weight
    * oTolMin :
    * oNbConstraint,
    * oConstPart : que constants part of Criterium J with w == 1.0
    * oPPCsWeightRatio : ratio of PPCs
    * oPPCsWeightRatio : ratio of LSCs
    * return :
    *         0  Successful completion
    *         1  Failure 
    */
   virtual int ComputeMeanTolerance(double & oTolMoy, 
                                    double & oTolMin,
                                    int    & oNbConstraint,
                                    double & oConstPart,
                                    double & oPPCsWeightRatio,
                                    double & oLSCsWeightRatio,
                                    double & oLXYZsWeightRatio,
                                    int    & oNbQ0Ko)=0;


   /*
    * calcul les ordres de derivation max en tenant compte des changemt de variables
    * iMaxDu : l'ordre en U
    * iMaxDv :    "     " V , si on en 1D => iMaxDv = -1 ,
    * return :
    *         0  Successful completion
    *         1  Failure 
    */
   virtual int GetMaxDuDv(int & oMaxDu, int & oMaxDV)=0;

   /*
    * get init
    */
   virtual void GetInit(CATKnotVector *& oKV_U,
                        CATKnotVector *& oKV_V,
                        double & oUmin, double & oUmax,
                        double & oVmin, double & oVmax)=0;

   /*
    * Return les vecteurs nodaux de la delta( Delta is Delta or returnedDelata
    * iConvert : Convert or no Delat, 0=> no convert, 1 = convert delta, 2= convert returnedDelata
    * oIs2D : TRUE ds le cas de surf et FALSE ds le cas 1D
    * oKVDeltaU : Ptr on delta knotVector U
    * oKVDeltaV : Ptr on delta knotVector V, NULL if !oIs2D
    * iMaxEnergyOrder : Energy Max Order 
    * /!\ Ptr must not be deleted 
    */
   virtual void GetDeltaKnotVectors(      CATBoolean     & oIs2D          ,
                                          CATKnotVector *& oKVDeltaU      ,
                                          CATKnotVector *& oKVDeltaV      ,
                                    const int              iMaxEnergyOrder,
                                    const short            iConvert       )=0;


   /*
    * Give Which Matrix type to instance and give Band of Matrix
    * oTypeOfMatrix : Matrix Type
    * oBandOfMatrix : Bonad ofMatrix
    * return :
    *         0  Successful completion
    *         1  Failure 
    */
   virtual int WhichMatrix(FEMatrixType   & oTypeOfMatrix,
                           CATLONG32      & oBandOfMatrix,
                           CATBoolean     & oMustSolve3D,
                           CATLONG32      & oBandOfMatrix3,
                           CATSingleVarBB * iUBB,
                           CATSingleVarBB * iVBB)=0;



   /*
    * Init _Solution par Delta
    * ioSol  : tab to fill 
    * return :
    *         0  Successful completion
    *         1  Failure 
    */
   virtual int InitSol(double * ioSol)=0;

   /*
    * Load or no Save delta as delta;
    * iKeep : if true keep , false delete
    */
   virtual void KeepSaveDelta(const CATBoolean iKeep)=0;


   /*
    * To the save Delta
    */
   virtual void SaveDelta()=0;

   /*
    * To the save Delta before oracle
    */
   virtual void SaveDeltaBeforeOracle()=0;


   /*
    * To the save Delta before Phase4
    */
   virtual void SaveDeltaBeforePhase4()=0;


   /*
    * UpdateWeight
    * oRatioMax : 
    * oStatusPPCA
    * oStatusLSCA
    * oStatusLXYZ
    * oUnsatisfiedOrder
    * iolocalRelax
    * return :
    *         0  Successful completion
    *         1  Failure 
    */
   virtual int UpdateWeight(double               & oRatioMax        ,
                            int                  & oStatusPPCA      ,
                            int                  & oStatusLSCA      ,
                            int                  & oStatusLXYZ      ,
                            int                  & oUnsatisfiedOrder,
                            CATPlateFELocalRelax * iolocalRelax) = 0;


   /*
    * Compute InactiveRatio : cas de Progressive Load
    * iRatioMax
    * return :
    *         0  Successful completion
    *         1  Failure 
    */
   virtual int ComputeInactivedRatio(double & oRatioMax)=0;

   /*
    * Init Insert Tools
    * iInU                 : to info if is ins U or no 
    * oKV                  : knotVetor of delta to insert
    * oImposedCut          : imposed cut
    * ExternalCuts         : Les noeuds de decoupes recomemcer (ex discC2)=0;
    * oNbExternalCuts      : leur nbre
    * oExternalCont        : leur continuite
    * oExternalVertexCuts  : les pts eventuels de decoupes aux vertex
    * oNbVertexNb          : leur nbre
    * oVertexCont          : leur continuite
    * ATTENTION : AUCUN DES PTR RETOURNES N'EST A DETRUIRE.
    * return :
    *         0  Successful completion
    *         1  Failure 
    * /
   virtual int InsertTools(const int             iDir,
                  CATKnotVector        * &   oKV, 
                  CATFEImposedCutting  * &   oImposedCut,
                  double               * &   oExternalCuts,
                  int                    &   oNbExternalCuts,
                  int                    &   oExternalCont,
                  double               * &   oExternalVertexCuts,
                  int                    &   oNbVertexNb,
                  int                    &   oVertexCont)=0;*/



   /*
    * Insert Knot
    * iTabOfKnotsToInsert :
    * iTabMuOfKnotsToInsert : tab of multiplicities of knots
    * iTabSize : nb of knots to insert
    * iInU     : insert in U or not
    * return :
    *         0  Successful completion
    *         1  Failure 
    */
   virtual int InsertionKnot(      double            *  iTabOfKnotsToInsert,
                                   CATLONG32         *  iTabMuOfKnotsToInsert,
                             const int                  iTabSize,
                             const int                  iDir)=0;


   /*
    * Compute the constante Part
    * oQ0 : the constant Part
    *         0  Successful completion
    *         1  Failure 
    */
   virtual int ComputeTheConstantPart(double & oQ0)=0;


   /*
    * Sauvegarde L'aectuel delta en U ou en V par _returnedDelta
    * return :
    *         0  Successful completion
    *         1  Failure 
    */
   virtual int SetDeltaU()=0;


   virtual int SetDeltaV()=0;

   /*
    * Intialialise _ReturnedDelta
    * iChoix : 1 => par _Delta ds l'espace user
    *          2 => par _SaveDeltaU
    *          3 => par _SaveDeltaV
    *          4 => par _SaveDeltaV et  U
    * return :
    *         0  Successful completion
    *         1  Failure 
    */
   virtual int SetReturnedDelta(const int iChoix)=0;


      /*
       * 
       * return :
       *         0  Successful completion
       *         1  Failure 
       */
   virtual int GetDeltaNbSpans(int & oNbSpans)=0;


   /*
    * 
    */
   virtual const double * GetReturnedDeltaKnot(const int iDir, 
                                       CATLONG32 & oNb)=0;

   /*
    * 
    */
   virtual CATKnotVector * GetReturnedDeltaKnotVector(const int iDir)=0;


   /*
   * FillPartialSum : l' objet utilise est le ReturnedDelat
   * iDir: la direction
   * iCut : 
   * ioTabEQ:
   * return :
   *         0  Successful completion
   *         1  Failure 
   */
   virtual int FillPartialSum(const int                  iDir      ,
                                    CATPlateFECutting *  iCut      ,
                                    double            *& ioTabEQ   ,
                                    double            *& ioTabRatio,
                                    double             & oEQ       ,
                                    double             & oRatioMax )=0;

                                        
   virtual void SetReturnedDeltaKnotVector(const int             iDir  ,
                                                 CATKnotVector & iNewKV)=0;

   /*
    * Compute InactiveRatio : cas de Progressive Load
    * ordermax : UnsatisfiedOrder
    * ioLocalRelax :
    * return :
    *         0  Successful completion
    *         1  Failure 
    */
   virtual int UpdateCurrentLevel(const int                    ordermax,
                                        CATPlateFELocalRelax * ioLocalRelax)=0;


   /*
    * fill cstraints matrix
    */
   virtual int FillMatrix(      CATMathPlateFEMatrix * ioFirstMember,
                                double               * ioSecMember  ,
                                CATSingleVarBB       * iUBB         ,
                                CATSingleVarBB       * iVBB         ,
                          const int                    iForcedBuild )=0;

   /**
    * cette methode remplit si possible 3 matrices
    * differentes. 1e pour les PPC, 1e LSC, et 1e LXYZ
    * Ainsi de les seconds membres correspondants
    * Ceci est necessaire pour la phase1 uniquement.
    * chaque matrice et SecM sont alloues par la methode,
    * Si necessaire i.e si la contrainte correspondante
    * existe.
    * L'appelant est responsable des desallocations
    * iFirstMember permet de creer les matrices
    * return :
    *         0  Successful completion
    *         1  Failure 
    */
   virtual int FillMatrix(const CATMathPlateFEMatrix *  iFirstMember,
                                CATMathPlateFEMatrix *& oFirstMemberPPCs, double *& ioSecMemberPPCs,
                                CATMathPlateFEMatrix *& oFirstMemberLSCs, double *& ioSecMemberLSCs,
                                CATMathPlateFEMatrix *& oFirstMemberLXYZ, double *& ioSecMemberLXYZ,
                          const CATSingleVarBB       * iUBB, const CATSingleVarBB * iVBB) = 0;

   /*
    * set or no local fill
    * retourne sa decision sur la capacite a activer le local
    */
   virtual CATBoolean SetLocalFill(const CATBoolean iIsLocal)=0;


   /*
    * Compute nb decoup max 
    */
   virtual int ComputeNbDecMax(const int CutInU, 
                               const int CutInV, 
                                     CATLONG32 & NbMaxU, 
                                     CATLONG32 & NbMaxV,
                               const CATLONG32 iMaxByInsert) const = 0;
   /*
    *
    */
   virtual int SetTheW(const double iTheW)=0;
   virtual CATBoolean SetNextLevel() = 0;

   /*
   */
   virtual void DisplayW() const =0; 

   virtual void DumpHeader() const =0;
   
   virtual void DumpSpecific(const int) const = 0;
   virtual void DumpBox() const = 0;
   virtual void DumpResult(const int) const = 0;
   virtual void DumpBeforeOracle() const = 0;
/*
   virtual CATAllPinpointConstraints  *    GetPPCs()   =0;
   virtual CATAllLinearXYZConstraints  *   GetLXYZCs() =0;
   virtual CATAllLinearScalarConstraints * GetLSCs()   =0;*/
   
   /*virtual int Fill(CATFESparseLSCMatrix * ioPPCsMQ,
                    CATFESparseLSCMatrix * ioLSCsMQ,
                    double * ioPPCsSecM,
                    double * ioLSCsSecM,
                    CATSingleVarBB * iUBB,
                    CATSingleVarBB * iVBB) = 0;*/

   virtual CATChangementVariables        * GetCV()   =0;

   virtual int RunOptimUV(const int ietap, double& EQ, double& EE, double& TheW, double& TheRatio)=0;
   virtual int SolveNL(double & oEE, double & oEQ)=0;
   virtual int InitMember(const short iConvert =0)=0;
   virtual int SetReduceW(const double iRatio) = 0;

   virtual       void      GetCoeffOfNormalization(double & ioCoef)= 0;

   virtual const double *  GetStatRatio( const CATBoolean iWithDump )const = 0;
   //virtual const double * GetProbaNonTenuesParSpanU( int & oNbSpans ) =0;
   //virtual const double * GetProbaNonTenuesParSpanV( int & oNbSpans ) =0;
   virtual       double    GetObjetivePercentRatio( )const =0;
};
#endif //CATPlateFEBasicFunction_H

