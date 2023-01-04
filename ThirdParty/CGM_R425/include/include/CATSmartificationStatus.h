#ifndef __CATSmartificationStatus_H__
#define __CATSmartificationStatus_H__
/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2012
// 
//==========================================================================
// Jun. 12  Technologie FastRun                                          WQO
//==========================================================================

// Status de Smartification, technologie correlee au Fast Update
typedef enum
{
  CATSmartificationUnset      = -1, // valeur par defaut et d initialisation
  CATSmartificationImpossible =  0, // smartification impossible car interdite ou config non traitable
  CATSmartificationDone       =  1  // la smartification a ete faite
}
CATSmartificationStatus;

#endif

