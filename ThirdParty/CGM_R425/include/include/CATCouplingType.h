// COPYRIGHT DASSAULT SYSTEMES  1998
//=======================================================================
//
// CATCouplingType :
//   definition options for coupling
//
//=======================================================================
// Usage Notes :
//
//=======================================================================
// Nov 98   Creation                                   jbx
//=======================================================================
#ifndef CATCouplingType_H
#define CATCouplingType_H
typedef enum
{
  PARAMETRIC ,
  CCV_PARAMETRIC,
  INTERSECT,
  CURVILINEAR,
  IMPOSED_POINTS,
  INDIRECT
} CATCouplingType;
#endif




