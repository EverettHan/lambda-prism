// COPYRIGHT DASSAULT SYSTEMES 1998
//=============================================================================
//
// CATBooleanOperation :
// type enumere 
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// May 98  Creation                                                    L. Laloy
//=============================================================================
#ifndef CATBooleanOperation_H
#define CATBooleanOperation_H

typedef enum
{
   CATBooleanOperationIntersection = 1,
   CATBooleanOperationUnion = 2,
   CATBooleanOperationDifference = 3,
   CATBooleanOperationUnset = 4
} 
CATBooleanOperation;

#endif
