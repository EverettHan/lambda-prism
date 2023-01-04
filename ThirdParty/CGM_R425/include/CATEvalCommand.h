#ifndef CATEVALCOMMAND_H
#define CATEVALCOMMAND_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/** @CAA2Required */
#include "CATDataType.h"

typedef CATLONG32  CATEvalCommand;

const CATEvalCommand Cxyz = 0;
const CATEvalCommand CATDeriv0 = 1;
const CATEvalCommand CATDeriv1 = 2;
const CATEvalCommand CATDeriv2 = 4;
const CATEvalCommand CATDeriv3 = 8;
const CATEvalCommand CATDerivUV = 32;

#endif
