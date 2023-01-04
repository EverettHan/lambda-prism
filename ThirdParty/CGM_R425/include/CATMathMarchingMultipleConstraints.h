//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2002
//=============================================================================

#ifndef CATMathMarchingMultipleConstraints_H  
#define CATMathMarchingMultipleConstraints_H  

#include "CATMathImplicitSystem.h"
#include "CATListOfInt.h"
#include "YN000FUN.h"

class CATSoftwareConfiguration;
class CATMathAttrList;

class ExportedByYN000FUN CATMathMarchingMultipleConstraints : public CATMathImplicitSystem
{ 
public: 
//Do not use
// NLD240512 CATMathMarchingMultipleConstraints(CATLONG32 iN, CATLONG32 iNumberOfConstraints, const CATTolerance & iTolObject=CATGetDefaultTolerance(), const CATMathAttrList * iAttributes=NULL);

CATMathMarchingMultipleConstraints(      CATSoftwareConfiguration *  iConfig,
                                         CATLONG32                   iN,
                                         CATLONG32                   iNumberOfConstraints,
                                   const CATTolerance              & iTolObject          = CATGetDefaultTolerance(),
                                   const CATMathAttrList          *  iAttributes         = NULL);
~CATMathMarchingMultipleConstraints();

virtual void EvalOneConstraint        (CATLONG32 iConstraintIndex, const double * iX, double & oGX) = 0;
virtual void EvalOneConstraintJacobian(CATLONG32 iConstraintIndex, const double * iX, double * ioJacobianGX);
virtual void EvalOneConstraint        (CATLONG32 iConstraintIndex, const double * iX, double & oGX, double * ioJacobianGX);
virtual CATLONG32 GetNumberOfConstraints();
virtual void GetStopConstraintIndices(CATListOfInt & oStopConstraintIndices);
virtual void GetStartListOfCstrns(CATLONG32 iNumSol, CATListOfInt & oStartCstrn);
virtual void GetEndListOfCstrns(CATLONG32 iNumSol, CATListOfInt & oEndCstrn);

/**
 * iConstraintIndex == -1: All constraints are active (default)
 * -1 < iConstraintIndex < NumberOfConstraints : only one constraint is active
 */
virtual void ActivateConstraint(CATLONG32 iConstraintIndex);
   CATLONG32 GetConstraintIndex();
virtual void EvalConstraint         (const double * iX, double & oGX);
virtual void EvalConstraintJacobian (const double * iX, double * ioJacobianGX);
virtual void EvalConstraint         (const double * iX, double & oGX, double * ioJacobianGX);

protected:

CATLONG32 _NumberOfConstraints;
CATLONG32 _CurrentConstraintsIndex;
CATBoolean _IsNbConstraints;       //Extreme Scale(IEY/07:03:05) 

virtual CATMathMarchingDiagnostic * GetBranchDiagnostic();
virtual CATMathDiagnostic Run(const CATMathIntervalND & Domain,const double *StartPoint,
                              double *StartTangent,CATMathSetOfPointsND & SetOfPoints);
        void ScaleOneConstraint        (CATLONG32 iConstraintIndex, double * iGx, double * oGx);
        void ScaleOneConstraintJacobian(CATLONG32 iConstraintIndex, double * iJacobianGX, double *oJacobianGX);

double * _TMP;

private :
CATListOfInt _StopConstraintIndices;
CATMathMarchingMultipleConstraints();
CATMathMarchingMultipleConstraints(const CATMathMarchingMultipleConstraints &);
void operator = (const CATMathMarchingMultipleConstraints &);

        int OKConstraintIndex(CATLONG32 iConstraintIndex);
};  
#endif  
