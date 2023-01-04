#ifndef CATCGMVersionningDefVarBOO_h
#define CATCGMVersionningDefVarBOO_h


// Max possible value for versionning variable
#define Version_Lvl_MaxValue 32000


#include "BOO_VERSIONNING_FUNCTION.h"

//-------------------------------------------------------------------------------------
// Pour definir une nouvelle variable de versionning, decommenter les lignes suivantes
//-------------------------------------------------------------------------------------
// Ligne 1 : Verifie que la variable n'est pas declaree en officiel
// Ligne 2 : Definition de la variable et affectation (Version_Lvl_MaxValue non activee)

// Never created - Begin
#ifndef CGM_Versionning_Projection_CellOperator
#define CGM_Versionning_Projection_CellOperator Version_Lvl_MaxValue
#endif

#ifndef CGM_Versionning_Boolean_NoHomogenizeWithConfusedFace
#define CGM_Versionning_Boolean_NoHomogenizeWithConfusedFace Version_Lvl_MaxValue
#endif

#ifndef CGM_Versionning_Intersect_DisActivateBodies
#define CGM_Versionning_Intersect_DisActivateBodies Version_Lvl_MaxValue
#endif

#ifndef CGM_Versionning_SweepOffsetLimitBeforeRelimitation
#define CGM_Versionning_SweepOffsetLimitBeforeRelimitation Version_Lvl_MaxValue
#endif
// Never created - END

#include "CATCGMVersionningDefVarJHN.h"
#include "CATCGMVersionningDefVarTHM.h"
#include "CATCGMVersionningDefVarG5S.h"


// WQO was here (my section to facilitate merges)
#ifndef CGM_Versionning_Projection_EdgeOnFaceClass
#define CGM_Versionning_Projection_EdgeOnFaceClass Version_Lvl_MaxValue
#endif
// WQO was here

// FDS was here
#ifndef CGM_Versionning_General_Perfo_R28SP3
#define CGM_Versionning_General_Perfo_R28SP3 Version_Lvl_MaxValue
#endif
// FDS was here

#include "CATCGMVersionningDefVarDLR6.h"
#include "CATCGMVersionningDefVarLD2.h"
#include "CATCGMVersionningDefVarQCN5.h"

// NTH1 was here
#ifndef CGM_Versionning_NonManifold_Propagation_NewApproach
#define CGM_Versionning_NonManifold_Propagation_NewApproach Version_Lvl_MaxValue
#endif
// NTH1 was here

#endif
