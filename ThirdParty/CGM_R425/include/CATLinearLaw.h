#ifndef CATLinearLaw_h
#define CATLinearLaw_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATLaw.h"

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATLinearLaw ;
#else
extern "C" const IID IID_CATLinearLaw ;
#endif

/**
 * Interface representing a linear law.
 *<br>A law is a function <tt>L</tt> of one parameter <tt>iT</tt> on a given 1D interval
 * <tt>[iTmin,iTmax]</tt>.  A linear law is line segment between <tt>L(iTmin)=iValueAtTMin</tt>
 * and <tt>L(iTmax)=iValueAtTMax</tt>.
 */
class ExportedByCATGMGeometricInterfaces CATLinearLaw : public CATLaw
{
  CATDeclareInterface;

public:

/**
 * Retrieves the coefficient of the law equation.
 * <br><tt>L(iT)= ioSlope*iT + ioValueAtZero</tt>.
 */
  virtual void GetLawEquation (double & ioSlope,
			       double & ioValueAtZero) const = 0 ;

/**
 * Retrieves the limits constraints.
 * @param ioTMin
 * The lower bound of the definition interval.
 * @param ioValueAtTMin
 * The law value on the lower bound of the definition interval.
 * @param ioTMax
 * The upper bound of the definition interval.
 * @param ioValueAtTMax
 * The law value on the upper bound of the definition interval.
 */
  virtual void GetLimitConstraints (double & ioTMin,
				    double & ioValueAtTMin,
				    double & ioTMax,
				    double & ioValueAtTMax) const = 0 ;

/**
 * Modifies the law definition by its the equation coefficients.
 * <br><tt>L(iT)= iNewSlope*iT + iNewValueAtZero</tt>.
 */
  virtual void SetLawEquation (const double iNewSlope,
			       const double iNewValueAtZero) = 0 ;

 /**
 * Modifies the limits constraints.
 * @param iTMin
 * The lower bound of the definition interval.
 * @param iValueAtTMin
 * The law value on the lower bound of the definition interval.
 * @param iTMax
 * The upper bound of the definition interval.
 * @param iValueAtTMax
 * The law value on the upper bound of the definition interval.
 */
  virtual void SetLimitConstraints (const double iNewTMin,
				    const double iNewValueAtTMin,
				    const double iNewTMax,
				    const double iNewValueAtTMax) = 0 ;
};
CATDeclareHandler(CATLinearLaw,CATLaw);

#endif

