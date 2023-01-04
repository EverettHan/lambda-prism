// COPYRIGHT DASSAULT SYSTEMES  2000

#ifndef CATDeviationLnCrv_h
#define CATDeviationLnCrv_h

#include "Y30A3HGG.h"
#include "CATGeoOperator.h"
#include "CATSkillValue.h"
#include "CATCreateDeviationLnCrv.h"

class CATMathLine;
class CATCrvLimits;
class CATCrvParam;
class CATGeoFactory;
class CATCurve;

/**
 * Class defining the operator of maximum deviation between an infinite line
 * and a curve. It returning the maximum length between the curve and the line.
 */
class ExportedByY30A3HGG CATDeviationLnCrv : public CATGeoOperator
{
  CATCGMVirtualDeclareClass(CATDeviationLnCrv);
  public :
/**
 * @nodoc
 * Use the <tt>CreateDeviationLnCrv</tt> global function.
 */
    CATDeviationLnCrv(CATGeoFactory * factory);
 
/**
 * Destructor.
 */
    virtual ~CATDeviationLnCrv();
 /**
 * Specify limits to work on
 */
 virtual void SetLimits(const CATCrvLimits & iLimits)=0;

/**
 * Returns the maximum distance between the CATCurve and the 
 * CATMathLine.
 * @return
 * The distance.
 */  
 virtual double GetDistance()   const=0;


 /**
 * Returns a param on the Curve which realized the
 * maximum distance between the CATCurve and the CATMathLine.
 * @return
 * The curve parameter.
 */  
 virtual void GetCrvParam(CATCrvParam & oParam) const=0;
};


ExportedByY30A3HGG
CATDeviationLnCrv * CreateDeviationLnCrv(CATGeoFactory  *iWhere,
																				 const CATMathLine & iLine,
																				 CATCurve * iCurve,
                                         CATSkillValue iMode = BASIC);
   

ExportedByY30A3HGG void Remove(CATDeviationLnCrv * Dev);
#endif

