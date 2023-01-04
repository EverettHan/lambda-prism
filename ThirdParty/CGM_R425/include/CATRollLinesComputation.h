/* -*-c++-*-*/
//=============================================================================
//
// CATRollLinesComputation 
//  Class to construct roll lines : specific operator for shipbuilding 
//  application that permits to trace roll lines on a flat tole in order
//  to deform it.
//=============================================================================
// Usage notes:
//
//=============================================================================
//   /10/04     Creation                                        X. Gourdon
// 12/03/20 Q48 Headers etc for math versioning
//=============================================================================
#ifndef CATRollLinesComputation_H 
#define CATRollLinesComputation_H 

// ExportedBy
#include "Y30UIUTI.h"

// Base class
#include "CATGeoOperator.h"

// C++11
#include "CATGeoOpVirtual.h"

#include "CATMathSetOfPointsND.h"
#include "CATMathPoint2D.h"
#include "CATMathVector2D.h"
#include "CATMathFunctionXY.h"
#include "CATMathFunctionRN.h"

#include "CATString.h"
#include "CATGeoOpTimer.h"
#include "CATMathConstant.h"

class CATRollLinesEnergieFunctionXY;
//-------------------------------------------------------------------------
class ExportedByY30UIUTI CATRollLinesComputation : public CATGeoOperator
  {
  CATCGMVirtualDeclareClass(CATRollLinesComputation);
  public:

    //-----------------------------------------------------------------------
    //- Object management
    //-----------------------------------------------------------------------

    /**
    * Constructor
    */

    CATRollLinesComputation(CATGeoFactory * iFactory, CATSoftwareConfiguration * iConfig);
    virtual ~CATRollLinesComputation();

    /**
    * AddPointData : should be called n times to specify n points, before calling the Run()
    * Specify one by one the points to add. The data (L,M,N) represents the second fundamental form
    * (in the way returned by the CATLocalAnalysis2D class), Point2D represents the image of the
    * 3D point in the flat view (expressed in the plane coordinates), DU2D and DV2D the images
    * on the 3D vectors DU and DV in the flat view (expressed in the plane coordinates)
    */
    void AddPointData(double L, double M, double N,
      const CATMathPoint2D & Point2D, const CATMathVector2D & DU2D, const CATMathVector2D & DV2D,CATBoolean *Valid=NULL);

    /*
    * Specify the number of rolllines to be computed. Should be called before the Run()
    */
    void SetNumberOfRollLines(int iNumberOfRollLines);

    /*
    * Specify energy type to be minimized to find RollLines.
    * iEnergyType=0 means that energy is minimization of twists along rolllines
    * iEnergyType=1 means that energy is minimization of curvature 
    *   (twists+longitudinal curvature) along rolllines
    * Default value is iEnergyType=0
    */
    void SetEnergyType(int iEnergyType);


    /**
    * Return TRUE in case of success, FALSE otherwise. Should be called after the Run()
    * NEW ! Optional Argument oPreciseDiag give Info 
    * = CATMathOK : no problem
    * = CATMathConstantFunction : Too Smal Energie: Check that input is not on a plane. 
    */
    CATBoolean GetDiagnostic(CATMathDiagnostic *oPreciseDiag=NULL);

    /**
    * Retrieve the rollline of index iRollLineIndex, with 0<= iRollLineIndex < iNumberOfRollLines;
    * Should be called after the Run() call.
    * TransversalCurvature contains the mean value of curvature of the RollLine (a sort of energy).
    * (Important : TransversalCurvature may be positive or negative)
    * RollLineRelativeEnergy is between 0 and 1. It contains the relative "energy" of the RollLine compared
    * to the set of all RollLines.
    */
    void GetRollLine(int iRollLineIndex, CATMathPoint2D & oStart, CATMathPoint2D & oEnd, 
      double & TransversalCurvature, double & RollLineRelativeEnergy);

    //=======================================================================
    //- Protected Methods
    //=======================================================================
  protected:
    /**
    * Run method
    */
    virtual int RunOperator();

    double InitializeMeanDirection(double & xMin, double & xMax, double & yMin, double & yMax);
    double EvalTotalEnergy(double Theta0, double xMid, double yMid, double D, double a, double b);
    void ComputeRollLines(double Theta0, double xMid, double yMid, double D, double a, double b,
      double xMin, double xMax, double yMin, double yMax);
    double ComputeRollLineTransversalCurvature(CATMathPoint2D & Start, CATMathPoint2D & End);


    //-----------------------------------------------------------------------
    // CGMReplay methods
    //-----------------------------------------------------------------------
    const CATString * GetOperatorId();
    //- Gestion timer 
    CATGeoOpTimer * GetTimer();


    CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
    void WriteInput(CATCGMStream  & os);
    void WriteOutput(CATCGMStream & os);
    CATBoolean ValidateOutput(CATCGMStream& ioStream, CATCGMOutput & os,int VersionNumber=1);
    void Dump( CATCGMOutput& os ) ;
    void DumpOutput(CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
    CATCGMOperator::CATCheckDiagnostic CheckOutput (CATCGMOutput & os);

    //=======================================================================
    //- Data
    //=======================================================================
  protected :

    // Input data
    CATSoftwareConfiguration * _Config;
    CATLONG32 _CGMLevel;

    CATMathSetOfPointsND _OriginalData;
    CATMathSetOfPointsND _PointData;
    int _NumberOfRollLines;
    int _EnergyType;

    // Internal data
    CATMathPoint2D * _RollLineExtremities;
    double * _RollLineTransversalCurvature;
    double _SeuilD; // distance relative du point focal au domaine
    
      // Output data
    CATBoolean _Success;
    CATMathDiagnostic _DiagOfMinimization;

    // data for CGMReplay functionnality
    friend class CATGeoStreamFactory; // pour gestion du mode Record Automatique

    // private static data
    static CATString _OperatorId;
    static CATGeoOpTimer _Timer;


    friend class CATRollLinesEnergieFunctionXY;
  };


/**
 * Creates an operator for computing RollLines
 * Use ALWAYS  : 
 *     * Set methods (if needed) of the class to specify optional parameters
 *     * the Run method of the CATRollLinesComputation class to run the operator
 */
ExportedByY30UIUTI
CATRollLinesComputation * CATCreateRollLinesComputation(CATGeoFactory  *iWhere, CATSoftwareConfiguration * iConfig);

/**
 * Removes the operator
 */
ExportedByY30UIUTI void Remove(CATRollLinesComputation *iRollLinesComputationOperator);


;

#endif
