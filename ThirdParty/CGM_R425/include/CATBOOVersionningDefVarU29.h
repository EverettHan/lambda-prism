// COPYRIGHT DASSAULT SYSTEMES 2019
//=============================================================================
//
// CATBOOVersionningDefVarU29
//
//
//=============================================================================
//
// Usage notes:
//   - Usuage non standard et unique pour U29. 
//   - Permet d'eviter les impacts build inutiles de DefVar6
//   - Ne doit pas etre inclus dans DefVar 6 ou autre  
//=============================================================================
//  Feb 2019  Creation											       U29
//=============================================================================

#include "CATCGMVersionningDefVar6.h"

#ifndef CATBOOVersionningDefVarU29_h
#define CATBOOVersionningDefVarU29_h

//###################################################################################################
//                             BOO VERSIONNINGS
//###################################################################################################

//*******************************************************************
//                  Maintenance
//*******************************************************************
//BOO_VERSIONNING_FUNCTION(PatternFaces_AdditionalFacesToTransfo); // RI-639978

//*******************************************************************
//                  COMPATIBLE
//*******************************************************************

// Activate the imprint
#ifndef CGM_Versionning_Compatible_Journal_Imprint
#define CGM_Versionning_Compatible_Journal_Imprint 32000
#endif
BOO_VERSIONNING_FUNCTION(Compatible_Journal_Imprint);


BOO_VERSIONNING_FUNCTION(Compatible_Journal_ImprintPrereq);

//*******************************************************************
//                  Test imprint
//*******************************************************************
#ifndef CGM_Versionning_Imprint_DecorateCGMReplayInputs
#define CGM_Versionning_Imprint_DecorateCGMReplayInputs 32000
#endif
BOO_VERSIONNING_FUNCTION(Imprint_DecorateCGMReplayInputs);

//*******************************************************************
//                   DOCO
//*******************************************************************

// Activate the imprint
#ifndef CGM_Versionning_DOCO_Journal_Imprint
#define CGM_Versionning_DOCO_Journal_Imprint 32000
#endif
BOO_VERSIONNING_FUNCTION(DOCO_Journal_Imprint);

//Special activation for selection for non manifold project
//@Ask a variable to activate for GA CXR30
//#ifdef CATIACGMR422CAA
//#undef CGM_Versionning_DOCO_3D_Journal_UnablePostProcessing
//#define CGM_Versionning_DOCO_3D_Journal_UnablePostProcessing 8369
//#endif

// Journal processing
BOO_VERSIONNING_FUNCTION(DOCO_3D_Journal_UnablePostProcessing);
BOO_VERSIONNING_FUNCTION(DOCO_Journal_UnablePostProcessing);


//*******************************************************************
//                  MultiTrim
//*******************************************************************

// Activate the imprint
#ifndef CGM_Versionning_MultiTrim_Journal_Imprint
#define CGM_Versionning_MultiTrim_Journal_Imprint 32000
#endif
BOO_VERSIONNING_FUNCTION(MultiTrim_Journal_Imprint);

// Prerequis for the imprint
BOO_VERSIONNING_FUNCTION(MultiTrim_Journal_ImprintPrereq);

//*******************************************************************
//                  Disconnect
//*******************************************************************

// Activate the imprint
#ifndef CGM_Versionning_DisconnectShell_Journal_Imprint
#define CGM_Versionning_DisconnectShell_Journal_Imprint 32000
#endif
BOO_VERSIONNING_FUNCTION(DisconnectShell_Journal_Imprint);


//*******************************************************************
//                  CATTopJournalTools
//*******************************************************************
#ifndef CGM_Versionning_JournalTools_CellsToFollow_FixForFullJournal
#define CGM_Versionning_JournalTools_CellsToFollow_FixForFullJournal 32000
#endif
BOO_VERSIONNING_FUNCTION(JournalTools_CellsToFollow_FixForFullJournal);

#endif
