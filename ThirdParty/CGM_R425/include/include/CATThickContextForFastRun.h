#ifndef CATThickContextForFastRun_h
#define CATThickContextForFastRun_h
/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2009
// 
//==========================================================================
// Jul. 10  Creation                                   JJ3
//==========================================================================
#include "CATGMOperatorsInterfaces.h"
#include "CATContextForFastRun.h"


class ExportedByCATGMOperatorsInterfaces CATThickContextForFastRun: public CATContextForFastRun
{
public:
  /**
   * Constructor
   */
  CATThickContextForFastRun();

protected:
  /**
   * Destructor
   */
  virtual ~CATThickContextForFastRun(); // -> delete can't be called
};

#endif /* CATThickContextForFastRun_h_ */
