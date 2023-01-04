#ifndef CATIPGMTopMakeManifold_h_
#define CATIPGMTopMakeManifold_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopMakeManifold;

// COPYRIGHT DASSAULT SYSTEMES  2001
/**
 * Class representing the topological operator that transform a non manifold body 
 * into a manifold a body.
 * Definition :
 * - In a non manifold body , a edge can be bound by more than two faces.
 * - In a manifold body , a edge can not bound by more than two two faces.
 * To use it :
 * - Create it with the CATPGMCreateTopMakeManifold global function.
 * - Run it
 * - Get the resulting body with the GetResult method.
 * If the input body was already manifold , it return the input body.
 * - Release the operator with the <tt>Release</tt> method after use. 
 * -----------------------------------------------------------------------------------
 * Oct. 01     Creation FDS 
 * -----------------------------------------------------------------------------------
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMTopMakeManifold: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopMakeManifold();

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopMakeManifold(); // -> delete can't be called
};

/**
 * Creates a CATIPGMTopMakeManifold operator.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled.
 * @param iBodyToMakeManifold
 * The pointer to the body to make manifold
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 * @see CATIPGMTopMakeManifold
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopMakeManifold *CATPGMCreateTopMakeManifold(
  CATGeoFactory *iGeoFactory,
  CATTopData *iData,
  CATBody *iBodyToMakeManifold);

#endif /* CATIPGMTopMakeManifold_h_ */
