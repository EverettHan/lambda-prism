/* -*-c++-*-*/
// COPYRIGHT DASSAULT SYSTEMES 1997
//===================================================================
//
/**
 * Interface representing the confusion operator of two points on a CATEdgeCurve.
 *<ul>
 *<li>The CATConfusionPtOnPCrvPtOnPCrv operator is designed to be open to external 
 * implementations.
 *<li>It is created with the <tt>CreateConfusionOnSurface</tt> method within a 
 *<tt>CATGeoFactory</tt>, but is not streamable. 
 *<li>In case of <tt>BASIC</tt>
 * mode, the operation is automatically performed. 
 *<li>In case of <tt>ADVANCED</tt>
 * mode, the user may precise options with the <tt>SetXxx</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method.
 *<li>The result is accessed thanks to the <tt>GetConfusion</tt> method.
 *<li> The operator is removed from the memory with the <tt>Remove</tt> method.
 *</ul>
 */
//
//===================================================================
// Feb. 97    Creation                         X. Gourdon
// Aug. 97    Interface creation               X. Gourdon
// Dec. 97    Documentation                    C. Keribin
//===================================================================

#ifndef CATConfusionPtOnPCrvPtOnPCrv_H
#define CATConfusionPtOnPCrvPtOnPCrv_H

#include "CreateConfusionPtOnPCrvPtOnPCrv.h"
#include "CATCreateConfusionPtOnPCrvPtOnPCrv.h"
#include "CATCGMOperator.h"

#include "CATMathDef.h"

class CATConfusionPtOnPCrvPtOnPCrv: public CATCGMOperator
{
 public:
/**
 * Destructor.
 */
  virtual ~CATConfusionPtOnPCrvPtOnPCrv();
/**
 * Constructor.
 */
  CATConfusionPtOnPCrvPtOnPCrv(CATGeoFactory * factory);

/**
 * Returns the result of a CATConfusionPtOnPCrvPtOnPCrv operator.
 * @return
 *<dl>
 * <dt><tt>1</tt> <dd> if the distance between the two CATPointOnEdgeCurves
 * is less than <tt>tol</tt> (given at the operator creation).
 *    <dt><tt>0</tt> <dd> otherwise.  </dl> 
 */
  virtual CATBoolean GetConfusion() = 0;

  virtual void SetParameters(const CATCrvParam & param1, const CATCrvParam & param2) = 0;

};

#endif
