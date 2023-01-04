#ifndef CATFastRunBlackBoxOperatorContextForFastRun_h
#define CATFastRunBlackBoxOperatorContextForFastRun_h
/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2009
// 
//==========================================================================
// Apr. 10  Creation                                   JJ3
//==========================================================================
#include "CATGMOperatorsInterfaces.h"
#include "CATContextForFastRun.h"


class ExportedByCATGMOperatorsInterfaces CATFastRunBlackBoxOperatorContextForFastRun: public CATContextForFastRun
{
public:
  /**
   * Constructor
   */
  CATFastRunBlackBoxOperatorContextForFastRun();

protected:
  /**
   * Destructor
   */
  virtual ~CATFastRunBlackBoxOperatorContextForFastRun(); // -> delete can't be called
};

#endif /* CATFastRunBlackBoxOperatorContextForFastRun_h_ */
