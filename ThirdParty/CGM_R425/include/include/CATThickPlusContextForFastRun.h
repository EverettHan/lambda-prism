#ifndef CATThickPlusContextForFastRun_h
#define CATThickPlusContextForFastRun_h
/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2009
// 
//==========================================================================
// Jun. 10  Creation                                   JJ3
//==========================================================================
#include "CATGMOperatorsInterfaces.h"
#include "CATContextForFastRun.h"


class ExportedByCATGMOperatorsInterfaces CATThickPlusContextForFastRun: public CATContextForFastRun
{
public:
  /**
   * Constructor
   */
  CATThickPlusContextForFastRun();

  //virtual CATBody * GetOldInput() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATThickPlusContextForFastRun(); // -> delete can't be called
};

#endif /* CATThickPlusContextForFastRun_h_ */
