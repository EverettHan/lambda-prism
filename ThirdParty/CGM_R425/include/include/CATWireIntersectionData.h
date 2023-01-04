#ifndef CATWireIntersectionData_h
#define CATWireIntersectionData_h

#include "CATBody.h"

struct CATWireIntersectionData
{
  CATBody * _pOperand_1;
  CATBody * _pOperand_2;

  CATWireIntersectionData(CATBody* ipOp1=NULL, CATBody* ipOp2=NULL) :
    _pOperand_1(ipOp1),
    _pOperand_2(ipOp2)
  {
  }
 ~CATWireIntersectionData()
 {
   _pOperand_1 = NULL;
   _pOperand_2 = NULL;
 }
};

#endif
