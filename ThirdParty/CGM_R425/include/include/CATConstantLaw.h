#ifndef CATConstantLaw_h
#define CATConstantLaw_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATLaw.h"

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATConstantLaw ;
#else
extern "C" const IID IID_CATConstantLaw ;
#endif

/**
 * Interface representing a linear law.
 *<br>A law is a function <tt>L</tt> of one parameter <tt>iT</tt> on a given 1D interval
 * <tt>[iTmin,iTmax]</tt>. A constant law is such that <tt>L(iT)=iConstant</tt> on the
 * definition interval.
 */
class ExportedByCATGMGeometricInterfaces CATConstantLaw : public CATLaw
{
  CATDeclareInterface;

public:

  //-------------------------------------------------------------------------
  //- Read the Law Value.
  //-------------------------------------------------------------------------
/**
 * Returns the constant value of <tt>this</tt> CATConstantLaw.
 * @return
 * The constant value.
 */
  virtual double GetValue () const = 0 ;

/**
 * Modifies the constant value of <tt>this</tt> CATConstantLaw.
 * @param iNewValue
 * The new constant value.
 */
  virtual void SetValue (const double iNewValue) = 0 ;

};
CATDeclareHandler(CATConstantLaw,CATLaw);

#endif

