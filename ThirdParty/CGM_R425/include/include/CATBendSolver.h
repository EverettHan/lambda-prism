//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2006
//=============================================================================
//
// CATBendSolver :
//   Class used to connect two 3D passing points O1 and O2 associated with
//   two 3D cinematically oriented tangents V1 and V2, using circle arcs
//   of given radius and one line segment.
//
// Main application : Electrical Harness Design.
//
//=============================================================================
// Usage notes:
//
//=============================================================================
//   /03/06 CQI Creation
// 12/03/20 Q48 Headers etc for math versioning
//=============================================================================

#ifndef CATBendSolver_H
#define CATBendSolver_H 

// ExportedBy
#include "Y30UIUTI.h"

// Base class
#include "CATGeoOperator.h"

// C++11
#include "CATGeoOpVirtual.h"

#include "CATBendDefines.h"
#include "CATBendResult.h"
#include "CATMathSetOfPointsND.h"
#include "CATMathInline.h"

class CATGeoFactory;
class CATSoftwareConfiguration;
class CATBendSystemXY;
class CATBendSystem;
class CATBendFunctionX;
class CATMathPoint2D;

class ExportedByY30UIUTI CATBendSolver : public CATGeoOperator
{
public :
  
  //-----------------------------------------------------------------------
  //- Object Management
  //-----------------------------------------------------------------------
  
  CATBendSolver(CATGeoFactory * iFactory, CATSoftwareConfiguration * iConfig,
                const double iO1[], const double iV1[], const double iO2[], const double iV2[],
                const double iRadius);
  
  ~CATBendSolver();
  
  //-----------------------------------------------------------------------
  //- Set methods
  //-----------------------------------------------------------------------
  
  void SetData(const double iO1[], const double iV1[], const double iO2[], const double iV2[], const double iRadius);
  void SetStartData(const double iO1[], const double iV1[]);
  void SetEndData(const double iO2[], const double iV2[]);
  void SetRadius(const double iRadius);

  //-----------------------------------------------------------------------
  //- Run operator
  //-----------------------------------------------------------------------

  int RunOperator();
  
  //-----------------------------------------------------------------------
  //- Get methods
  //-----------------------------------------------------------------------
  
  INLINE CATBendDiagnostic GetDiagnostic() const { return _Diag; }
  
  INLINE CATLONG32 GetResultSize() const { return _Size; }
  
  CATBendResult * GetBendResult(CATLONG32 iIndex);
  
private :

  void Reset();
  void CleanResults();
  void AllocResults(CATLONG32 iSize);

  void PreProcess();
  void ComputeCharacteristicData();
  void ComputeMaxDomain();
  void DetectExplicitCase();

  ////////////////////
  // * RunExplicit.
  ////////////////////
  void RunExplicit();
  // Explicit internal sub-methods.
  void RunInfiniteNull();        // Case 1, 2 and 3
  void RunInfiniteInfinite();    // Case 4 (4-A and 4-B) and 7
  void RunNullNull();            // Case 5
  void RunComplementaryAngles(); // Case 6
  ////////////////////

  ////////////////////
  // * RunGeneric.
  ////////////////////
  void RunGeneric();
  void ComputeInit(int iXorY, double & ioParam, int iDepth=0); // 0 for X init, 1 for Y init
  // Main method for solution computation from init previously computed. Returns 1 if succeded, 0 otherwise.
  int ComputeOptimalSolution(CATLONG32 iMaxIter, CATLONG32 iMaxAdjust, CATLONG32 iMaxTries, double iReductionFactor);
  int ModifyInit(CATMathPoint2D iPconnect[2], CATMathPoint2D iOppositePole[2], double & ioXscaled, double & ioYscaled);
  void ProjectInCircleBasis(double iParam, CATMathPoint2D & oP);
  void ProjectInMixedBasis(double iParam, double iDist, CATMathPoint2D & oP);
  void FromMixedToCircleBasis(double iCos, double iSin, CATMathPoint2D & ioP);
  void Intersect(CATMathPoint2D & iF, CATMathPoint2D & iP, double & oParam);
  int TreatCusp(double & ioX, double & ioY);
  // Newton reconvergence method that work on (_Xsol,_Ysol). Returns 1 if succeded, 0 otherwise.
  int Reconverge(double & ioX, double & ioY);
  // This method construct, check, prepare and store the bend result from scaled values (iXsol,iYsol) previously computed.
  // The method returns 1 if it succeded (geometrical solution is ok and result is stored), 0 or -1 (deep failure) if
  // it failed (no result has been stored).
  int CheckAndStoreResult(const double iXscaled, const double iYscaled, CATMathPoint2D oPconnect[2], CATMathPoint2D oOppositePole[2]);
  ////////////////////
  
  ////////////////////
  // * RunAngular.
  ////////////////////
  void RunAngular(int iTryFilter = 1);
  // This method checks if lines (O1,V1) and (O2,V2) are coplanar (ie. intersecting or parallel).
  // It returns 1 if so, 0 otherwise (not coplanar or confused).
  int IsCoplanar();
  // Solve methods.
  // These methods should be called to solve the bend problem in angular parametrization. They have for effect to build
  // the required function (1D) or system (ND), and manage all the solve steps (domain, options, effective solving).
  // The method returns 1 if it found at least one solution, 0 if it failed. If succeeded, output sets are stored with
  // solutions found.
  int Solve1D(CATMathSetOfPointsND & oRoots1D); // dimension 1: parameter  = Theta (bend direction angle).
  int SolveND(CATMathSetOfPointsND & oRootsND, int EasySolver, int iTryFilter=1); // dimension 3: parameters = Phi, Psi (normal planes angles) and Theta (bend direction angle).
  // Filter method used to eliminate parasite angular solutions.
  // X must be a pointer to the solution values of dimension 1 (Solve1D) or 3 (SolveND).
  // The method returns 1 if the input solution is correct, 0 otherwise (parasite solution, invalid input).
  // NB.: the method must be used after Solve1D and/or SolveND calls since it needs to have functionX/system allocated.
  int FilterAngularSol(const double * X, CATLONG32 Dim);
  int ComputeAngularData(const double * X, CATLONG32 Dim,
                         CATMathPlane & oPln1, CATMathPlane & oPln2,
                         CATMathPoint & oPC1, CATMathPoint & oPC2,
                         CATMathVector * oBendDir = NULL);
  int StoreAngularResult(const double * X, CATLONG32 Dim);

  // Standard storage method usefull for (Circle,Line,Circle) storage and length check on each.
  // The method returns 1 if OK, -1 if deep problem.
  int StoreStandard(CATMathPlane & iCirclePln1, CATMathPoint & iStartLine, CATMathPoint & iEndLine, CATMathPlane & iCirclePln2, double iAngles[]);

  // DEBUG
  void CheckBendFunction(CATCGMOutput & os);
  void CheckBendSystem(CATCGMOutput & os);
  // DEBUG
  
  // Input data.
  double _O1[3], _V1input[3], _O2[3], _V2input[3];
  double _inputRadius;
  
  // Internal data.
  //    Geometrical information.
  double _V1[3], _V2[3];
  double _Radius, _R, _S, _T, _U;
  //    Explicit flag diagnosis.
  CATLONG32 _ExplicitCase;
  //    Solver parameters, tolerance and limits.
  CATBendSystemXY  * _BendSystem;
  CATBendSystem    * _AngularSystem;
  CATBendFunctionX * _AngularFuncX;
  double _Xsol, _Ysol;
  double _Epsilon;
  //double _Xmin, _Xmax, _Ymin, _Ymax;
  
  // Internal tolerances.
  //    Numerical tolerances.
  double _EpsAngle; //, _EpsDist;
  //    Geometrical tolerances.
  double _AngleTol, _DistTol;

  CATBendDiagnostic _Diag;    // Bend solver global diagnosis
  CATLONG32         _Size;    // Result size (maximum size = 3)
  CATBendResult  ** _Results; // Result tab
  CATBoolean     *  _Remove;  // Remove flags (TRUE: remove authorized, else FALSE)
  
  CATSoftwareConfiguration * _Config;
  
  //========================================================================
  // CGMReplay
  //========================================================================
protected:
  friend class CATGeoStreamFactory; 
  
  // private static data
  static CATString _OperatorId;
  
public:
  const CATString * GetOperatorId();
  
  CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
  virtual void WriteInput(CATCGMStream  & os);
  virtual void WriteOutput(CATCGMStream & os);
  virtual CATBoolean ValidateOutput(CATCGMStream& ioStream, CATCGMOutput & os,int VersionNumber=1);
  virtual void Dump( CATCGMOutput& os ) ;
  virtual void DumpOutput(CATCGMOutput & os);
  virtual void DumpOutput(CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
  virtual CATCheckDiagnostic CheckOutput(CATCGMOutput & os);
};

#endif







