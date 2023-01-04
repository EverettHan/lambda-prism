#ifndef CATGeoOperator_h
#define CATGeoOperator_h

// COPYRIGHT DASSAULT SYSTEMES  2000

/**
 * @level Protected
 * @usage U1
 */ 

#include "Y3DYNOPE.h"
#include "CATCGMOperator.h"

class CATGeoOpTimer;
/**
*  ***********************************************************************
*  *******                         WARNING                         *******
*  ***********************************************************************
*  *******
*  *******  This class is Not supported any longer.
*  *******  it has been replaced by CATICGMGeoOperator
*  *******
*  *******
*  ***********************************************************************
*  ***********************************************************************
*
*  CATGeoOperator class has been removed from CAA in 3DEXPERIENCE level and
*  has been replaced by CATICGMGeoOperator.
*  We recommend you to use only CATICGMGeoOperator, in order you will  be
*  able to easily migrate your CAA code from  V5 to 3DEXPERIENCE level.
*
*  **************************************************************************
 * Base class for the geometric operators.
 * <br>To use a geometric operator:
 *<ul><li>Create it with the corresponding <tt>CreateXxx</tt> global method
 * <li>Tune some parameters if needed
 * <li>Run it
 * <li>Read the results
 * <li>Delete it with the usual C++ delete operator.
 *</ul>
 */
class ExportedByY3DYNOPE CATGeoOperator : public CATCGMOperator {
  CATCGMVirtualDeclareClass(CATGeoOperator);
public:
    /** @nodoc */
  CATGeoOperator(CATGeoFactory * iFactory);

  virtual ~CATGeoOperator();
  /**
  * Runs <tt>this</tt> operator.
  */
  virtual int Run();
  
  /** @nodoc  */
  virtual CATGeoOpTimer * GetTimer();

public:

  /** @nodoc */
  CATTopOperator *IsTopological();
};


#endif 
