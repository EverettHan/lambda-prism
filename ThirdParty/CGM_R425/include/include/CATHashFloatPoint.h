//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATHashFloatPoint.h
//
//===================================================================
// April 2010 Creation: ndo
//===================================================================
#ifndef CATHashFloatPoint_H
#define CATHashFloatPoint_H

#include "PolyMathArithmetic.h"


/*
 * Function that compute an unsigned int from a point of coordinates (x, y, z) in floating point numbers.
 */
class ExportedByPolyMathArithmetic CATHashFloatPoint
{

public:

  CATHashFloatPoint () {}
  ~CATHashFloatPoint () {}

public:

  /*
   * Compute an unsigned int from a float point of coordinates (d[0], d[1], d[2]).
   */
  static unsigned int Hash (const float* d);

};

#endif // !CATHashFloatPoint_H
