// =====================================================================
//  Copyright Dassault Systemes 2004
// =====================================================================
//  Computes a mapping between the parameterizations of two curves
//  by projecting orthogonally the first one on the second one.
//  The result must not go through the center of curvature of the curve
//  to project.
//  Two corresponding initial parameters should be given to the
//  operator.
//  The result is given as a set of parameters on each curve that
//  correspond 2 by 2.
// =====================================================================
//
#ifndef CATProjectionCrvCrv_h
#define CATProjectionCrvCrv_h

#include "CATCGMOperator.h"
#include "Y30C3XGG.h"
#include "CATBoolean.h"

class CATGeoFactory;
class CATSoftwareConfiguration;
class CATCurve;
class CATCrvLimits;
class CATCrvParam;
class CATMathSetOfPointsND;
class CATMathFunctionX;
class CATMathImplicitSystem;

// CGMReplay 
#include "CATString.h"
#include "CATGeoOpTimer.h"
class CATCGMOutput;
class CATCGMStream;



class ExportedByY30C3XGG CATProjectionCrvCrv : public CATCGMOperator
{
  public :

    CATProjectionCrvCrv (CATGeoFactory * iFactory, CATSoftwareConfiguration * iConfig,
                         CATCurve * iCurveToProject, CATCrvLimits & iLimitsToProject,
                         CATCurve * iTargetCurve,    CATCrvLimits & iTargetLimits, CATMathDirection *iDirection = NULL);

    ~CATProjectionCrvCrv ();

    void SetInitParams (CATCrvParam & iParam, CATCrvParam & iTargetParam);

/**
 * Specifies that the left (or the right) extremity of the target curve is at the extremity
 * of the wire. In that case, if the theoretical projection lies outside of the limit of the
 * targeted curve, but not farer than the resolution, we will try to compute it.
 */
   void SetAreWireLimits (CATBoolean iLeft = TRUE, CATBoolean iRight = TRUE);

   void SetLimitsToProjects(CATCrvLimits & iLimitsToProject);

	 void SetLimitsOnTarget(CATCrvLimits & iLimitsOnTarget);	 
 
 /**
 * Allows to not take into account the maximum curvature constraint.
 */
   void DisableConstraint();


/**
 * Return Codes
 *  -2 - Bad inputs (null pointers, ...)
 *  -1 - Bad init params
 *   0 - No solution found
 *   1 - Ok
 **/
    virtual int RunOperator();


    enum Diagnostic { Unset, OutOfCurve, OutOfTarget, MaxCurvatureReached };

    void GetDiagnostics (Diagnostic & oStartDiag, Diagnostic & oEndDiag);

    // Careful : the caller must delete the pointer.
    void GetResult (CATMathSetOfPointsND *& oResult);

    virtual CATSoftwareConfiguration* GetSoftwareConfiguration() const;

/**
 * Return Codes
 *  -2 - Bad inputs (null pointers, ...)
 *  -1 - Internal problem (parameters out of domain, unable to converge...)
 *   1 - Ok
 **/
    int ComputeImages (CATMathSetOfPointsND & iParams, CATMathSetOfPointsND & oParams);

    CATLONG32 GetInitIndex ();

  protected :

    CATSoftwareConfiguration * _Config;
    CATCurve * _Curve1, * _Curve2;
    const CATMathFunctionX * _X1, * _Y1, * _Z1;
    const CATMathFunctionX * _X2, * _Y2, * _Z2;
    double _Domain [4], _Init [2];
    Diagnostic _StartDiag, _EndDiag;
    CATMathSetOfPointsND * _SetOfPoints;
    CATLONG32 _InitIndex, _ResultRetrieved;
    CATBoolean _LftWireLimit, _RgtWireLimit;
    CATBoolean _ConstraintEnabled;
    CATMathDirection *_Direction;

    Diagnostic GetDiagnostic (CATMathImplicitSystem & iEquation, CATLONG32 iMarchDiag, CATMathSetOfPointsND & iSet,
                              CATLONG32 iSide, double * oTolPoint);
    CATLONG32 GetConfusion (CATCurve * iCurve, double iParRef, double * iPar, CATLONG32 iNbPar,
                            double iTol = -1., CATLONG32 * oCloserPoint = NULL);
    CATLONG32 InsertOnArc (CATMathImplicitSystem & iEquation, CATLONG32 iArc, double iRatio);

    void Reset();
//-----------------------------------------------------------------------
//- CGMReplay VSJ Creation Feb 2005
//-----------------------------------------------------------------------  

protected:
	friend class CATGeoStreamFactory;
	
	// private static data
	static CATString _OperatorId;
  static CATGeoOpTimer _Timer;
	
public:
	
	const CATString * GetOperatorId();
//-----------------------------------------------------------------------
//- Gestion timer
//-----------------------------------------------------------------------  
	CATGeoOpTimer * GetTimer();
	
//-----------------------------------------------------------------------
//- Gestion Mode Record 
//-----------------------------------------------------------------------  
	CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
	virtual void WriteInput(CATCGMStream  & Str);
	virtual void WriteOutput(CATCGMStream & Str);
	virtual CATBoolean ValidateOutput(CATCGMStream& Str,  CATCGMOutput & os,int VersionNumber=1);
	virtual void Dump( CATCGMOutput& os ) ;
	virtual void DumpOutput(CATCGMStream& Str, CATCGMOutput& os,int VersionNumber=1);
  virtual void DumpOutput(CATCGMOutput& os);	
	virtual CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & os);
};

#endif
