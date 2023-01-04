//=========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2009
//=========================================================================
//
// CATGeodesicAutoParallelComputer:
//   Implementation of Geodesic Auto Parallel Operator.
//
//=========================================================================
// Usage notes:
// 10/02/2021 : SME31 : Fix for IR818780 - Protection against stack overflow 
//
//=========================================================================
#ifndef CATGeodesicAutoParallelComputer_h
#define CATGeodesicAutoParallelComputer_h

#include "CATParallelComputer.h"
#include "CATBoolean.h"
#include "CATListOfDouble.h"
#include "CATListOfCATMathSetOfPointsND.h"
#include "CATListOfCATSurfaces.h"
#include "ListPOfCATFace.h"


class CATMathVectorialFunctionX;
class CATMathQuickDiscretizeFunctionX;
class CATMathPoint;
class CATSoftwareConfiguration;
class CATMathSetOfPointsND;


//-------------------------------------------------------------------------
class ExportedByConnect CATGeodesicAutoParallelComputer 

{
public:
	//-----------------------------------------------------------------------
	// Object Management.
	//-----------------------------------------------------------------------
	CATGeodesicAutoParallelComputer(CATSoftwareConfiguration *iConfig,
														 CATGeoFactory * iFactory,
                             CATSurface * iSurface,
														 CATCurve * iCurve,
                             CATCrvLimits & iLimits,
														 CATLONG32 iOrientationEdge,
														 CATLONG32 iOrientationSurface,
														 CATParallelConnectTool * iTool,
                             CATMathQuickDiscretizeFunctionX * pExpliFunc,
                             CATListOfDouble & iListOfInitParams,
                             double iStepValue,
                             CATLISTP(CATFace) & iListOfSupportFaces);
	
	~CATGeodesicAutoParallelComputer();

  void SetListOfOffsets(CATListOfDouble &iListOfOffsets);

  void Run();

  void GetResult(CATLISTP(CATMathSetOfPointsND) & ioSol, CATLISTP(CATMathSetOfPointsND) & ioGeometryData);

  //Dynamic sampling
  //Inserts a point between iStart & iEnd recursively till some criteria is satisfied.
  void InsertPoint(double iStart, double iEnd, double step,
                   const CATMathPoint & iStartPtOnOutput, const CATMathPoint & iEndPtOnOutput);

  //Dynamic sampling
  //Treats first half of InsertPoint method
  void InsertPointLeft(double iLstart, double iLend, double iLstep, 
                       const CATMathPoint & iStartPtOnOutput, CATMathPoint & ioEndPtOnOutput);

  //Dynamic sampling
  //Treats Second half of InsertPoint method
  void InsertPointRight(double iRstart, double iRend, double iRstep, 
                        const CATMathPoint & iStartPtOnOutput, const CATMathPoint & iEndPtOnOutput);


  //Computes 3d distance on InputCurve between 2 given params
  double FindDistOnInputCurve(double iStart, double iEnd);

  //Computes 3d distance on outputCurve between 2 given params.
  //Also, computes the solutions points for iEnd param.
  double FindDistOnOutputCurve(double iStart, double iEnd, 
                               const CATMathPoint & iPrevPtOnOutput, CATMathPoint & ioCurPtOnOutput);

  //Sorting the solutions points and appending in proper order.
  //helps when we want to create a spline using these points.
  void SortAndAppendSolutionPts(double iStepValue);

  //While computing the 3d distance on output points, selects proper Output pts
  //from two sets of solution pts. Ensures that proper pair of points is 
  //selected for distance computations.
  void GetEquivalentPoints(CATMathSetOfPointsND * iPrevSolPts,
                           CATMathSetOfPointsND * iSolPts,
                           CATMathPoint & ioPrevPtOnOutput,
                           CATMathPoint & ioCurPtOnOutput);
  
  CATBoolean DensityIsSufficient(CATMathSetOfPointsND * iPrevSolPts,
                                                                CATMathSetOfPointsND * iCurSolPts,
                                                                CATMathSetOfPointsND * iPrevGeometryData,
                                                                CATMathSetOfPointsND * iCurGeometryData);
  void InsertDenserPoint(double iStart, double iEnd,
                         CATMathSetOfPointsND * iPrevSolPts,
                         CATMathSetOfPointsND * iCurSolPts,
                         CATMathSetOfPointsND * iStartGeometryData,
                         CATMathSetOfPointsND * iEndGeometryData, int depth);
  void InsertDenserPointLeft(double iStart, double iEnd,
                             CATMathSetOfPointsND * iStartSolPtsRightLeft,
                              CATMathSetOfPointsND * &iEndSolPtsLeft,
                             CATMathSetOfPointsND * iStartGeometryDataLeft,
                             CATMathSetOfPointsND * &ioEndGeometryDataLeft, int depth);
  void InsertDenserPointRight(double iStart, double iEnd,
                              CATMathSetOfPointsND * iStartSolPtsRightRight,
                              CATMathSetOfPointsND * iEndSolPtsRight,
                              CATMathSetOfPointsND * iStartGeometryDataRight,
                              CATMathSetOfPointsND * iEndGeometryDataRight, int depth);

  
  //ST5 wk17: Applications LEVEL set
  void SetAutoParallelLevel (short &iAutoParallelLevel);

private:
  CATCrvLimits _Limits1;
  CATGeoFactory *_Factory;
  CATSoftwareConfiguration * _Config;
  CATCurve * _Curve;
  CATSurface * _Surface;
  int _OriEdge, _OriSurface;
  CATParallelConnectTool * _ParConnectTool;
  CATMathQuickDiscretizeFunctionX * _ExplicitFunction ;
  CATListOfDouble _ListOfOffsets, _ListOfParams, _ListOfInitParams;
  CATLISTP(CATMathSetOfPointsND) _ListOfListOfSolutionPoints, _ListOfCloseSolutionPoints;
  CATLISTP(CATMathSetOfPointsND) _ListOfListOfGeometryData, _ListOfCloseGeometryData;
  double _minStepValue, _Resolution;
  const double _Threshold1, _Threshold2;
  CATLISTP(CATFace) _ListOfSupportFaces;

  //ST5 wk17: AutoParallel Versionning
  short _AutoParallelLevel;  
};

#endif

