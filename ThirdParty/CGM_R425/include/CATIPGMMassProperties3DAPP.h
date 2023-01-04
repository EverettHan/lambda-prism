#ifndef CATIPGMMassProperties3DAPP_h_
#define CATIPGMMassProperties3DAPP_h_

// COPYRIGHT DASSAULT SYSTEMES 2013

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMDynMassProperties3D.h"

class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMMassProperties3DAPP;

//-----------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATIPGMMassProperties3DAPP: public CATIPGMDynMassProperties3D
{
public:
  /**
   * Constructor
   */
  CATIPGMMassProperties3DAPP();

  /**
  * Set the tolerance value
  * The algorism does not guarenty the convergence under 0.1% (especially for complex/thin models).
  */
  virtual void SetTolerance(double tol = 1.e-2) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMMassProperties3DAPP(); // -> delete can't be called
};

/**
 * Constructs an operator that computes geometric characteristics of a body.
 * @param iToAnalyze
 * The pointer to the body to analyze.
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMMassProperties3DAPP *CATPGMCreateMassProperties3DAPP(
  class CATTopData *iTopData,
  const CATBody *iToAnalyze);

/**
 * Constructs an operator that computes geometric characteristics of a face.
 * @param iFaceToAnalyze
 * The pointer to the face to analyze.
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMMassProperties3DAPP *CATPGMCreateMassProperties3DAPP(
  class CATTopData *iTopData,
  const CATFace *iFaceToAnalyze);

/**
 * Constructs an operator that computes geometric characteristics of a edge.
 * @param iEdgeToAnalyze
 * The pointer to the edge to analyze.
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMMassProperties3DAPP *CATPGMCreateMassProperties3DAPP(
  class CATTopData *iTopData,
  const CATEdge *iEdgeToAnalyze);

#endif /* CATIPGMMassProperties3DAPP_h_ */
