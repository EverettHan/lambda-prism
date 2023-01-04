//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================

#ifndef _CATApproxFunctionXByPiecewisePol_HeaderFile
#define _CATApproxFunctionXByPiecewisePol_HeaderFile

#include "CATGMModelInterfaces.h" 
#include "CATCGMVirtual.h"
#include "CATCreateApproxFunctionXByPiecewisePol.h" //EAB - 27/11/03

class CATMathInterval;
class CATMathFunctionX;
class CATMathPiecewiseXDel;
class CATSoftwareConfiguration;
/**
 *This operator converts a CATMathFunctionX into a CATMathPiecewiseXDel at a given tolerance.
 */
class ExportedByCATGMModelInterfaces CATApproxFunctionXByPiecewisePol  : public CATCGMVirtual
{
public:

/**
 *Run the operator.
 */
virtual int Run() = 0;

/**
 *Retrieves the result.
 *@return
 *The result curve.
 */
virtual CATMathPiecewiseXDel * GetResult() const = 0;
    
/**
 *Retrieves the maximum deviation between the input curve and the result.
 *
 *@return
 *The maximum deviation.
 */
virtual double GetMaxDeviation() const =0;

virtual int GetDiagnostic() const = 0;

virtual ~CATApproxFunctionXByPiecewisePol();
    
/**
 *@nodoc
 */
virtual void SetSideContinuity(int iSideContinuity) = 0;

/**
 *@nodoc
 */
virtual void SetInternalContinuity(int iInternalContinuity) = 0;

/**
 *@nodoc
 */
virtual void SetInternalMinLength(double iInternalMinLength) = 0;

/**
 *@nodoc
 */
virtual void SetMaxArcs(int iMaxArcs) = 0;

/**
 *@nodoc
 */
virtual void SetMaxDegree(int iMaxDegree) = 0;

protected:

CATApproxFunctionXByPiecewisePol();

private:

CATApproxFunctionXByPiecewisePol(const CATApproxFunctionXByPiecewisePol &);
void operator = (const CATApproxFunctionXByPiecewisePol &);

};

#endif
