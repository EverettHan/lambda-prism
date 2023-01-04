#ifndef CATIPGMTopPointOperator_h_
#define CATIPGMTopPointOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATDataType.h"
#include "CatTopPointLMode.h"

class CATMathVector;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopPointOperator;

/**
 * Class defining a topological operator that creates a point Body.
 *<br> 
 * Use directly the global functions
 * <tt>CATCreateTopPointxxx</tt>, that directly return the resulting body.
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMTopPointOperator: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopPointOperator();

  //
  // ADVANCED : Set Methods
  //
  /** @nodoc */
  virtual CATLONG32 SetDirection(const CATMathVector &iVector) = 0;

  /** @nodoc */
  virtual CATLONG32 SetLength(const double iLength) = 0;

  /** @nodoc */
  virtual CATLONG32 SetLengthMode(const CatTopPointLMode iMode) = 0;

  /** @nodoc */
  virtual CATLONG32 SetRefPoint(CATBody *iRefPoint) = 0;

  /** @nodoc */
  virtual CATLONG32 SetSupport(CATBody *iSupport) = 0;

  /** @nodoc */
  virtual CATLONG32 SetUV(const double U, const double V) = 0;

  /** @nodoc */
  virtual CATLONG32 SetXYZ(const double X, const double Y, const double Z) = 0;

  // ADVANCED : Run() : compute result after settings and before GetResult()
  /** @nodoc */
  virtual int Run() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopPointOperator(); // -> delete can't be called
};

/**
 * Default constructor of an operator of topological point.
 * <br>To be used in advanced mode: after the operator creation, you have to
 * set the parameters, rnus the operator, reads then resulting body and delete the operator.
 * @param iFactory
 * The factory that creates the resulting body.
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iTopData</tt> 
 * is <tt>NULL</tt>, it is not filled. 
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopPointOperator *CATPGMCreateTopPointOperator(
  CATGeoFactory *iFactory,
  CATTopData *iTopData);

#endif /* CATIPGMTopPointOperator_h_ */
