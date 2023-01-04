#ifndef CATDiagOfPersistence_h
#define CATDiagOfPersistence_h
/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2009
// 
//==========================================================================
// Oct. 09  Rearchitecture du FastRun Booleen                            WQO
//==========================================================================
typedef enum
{
   CATDiagIsNonPersistent = -1,
   CATDiagIsUnknown       =  0, //contient a priori du NonPersistent et du Persistent
   CATDiagIsPersistent    =  1,
   CATDiagIsUnset         =  2
} 
CATDiagOfPersistence;
#endif
