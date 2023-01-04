#ifndef __CATFastRunStatus_H__
#define __CATFastRunStatus_H__
/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2009
// 
//==========================================================================
// Apr. 09  Rearchitecture du FastRun                                    WQO
//==========================================================================

// Status Fast Update en sortie d une operation topologique ayant un context pour Fast Run
typedef enum
{
  CATFastRunUnset      = -1, // valeur par defaut et d initialisation
  CATFastRunImpossible =  0, // aucune optimisation Fast Run n a pu etre faite
  CATFastRunPossible   =  1  // des optimisations Fast Run ont ete faites
}
CATFastRunStatus;

// Potentiel Fast Update selon l operation et le niveau de code
typedef enum
{
  CATUpgradeUseless     = -1, // Fast Run non instrumente
  CATUpgradeAlreadyDone =  0, // niveau d Upgrade suffisant, inutile d en faire plus
  CATUpgradeMandatory   =  1, // Upgrade obligatoire pour profiter du Fast Run
  CATUpgradeUseful      =  2  // niveau suffisant pour Fast Run, mais un Upgrade offrira un meilleur niveau d optimisation
}
CATUpgradeForFastRun;

#endif

