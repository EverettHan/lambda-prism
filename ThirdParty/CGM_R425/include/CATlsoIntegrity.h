/* -*-C++-*- */
#ifndef CATlsoIntegrity_H
#define CATlsoIntegrity_H
/*  
=============================================================================

RESPONSABLE  : E. De Roquefeuil

DESCRIPTION  : Class to check the data integrity
               
=============================================================================

-- Code Example --

  LSOMACRO_IsIntegrityActive("JournalTranslation","EYL")
  {
     ... check code ...
    if (error)
      LSOMACRO_DumpIntegrityError("EmptyJournal")
     or       
      LSOMACRO_DumpIntegrityWarning("EmptyJournal")
  }
  LSOMACRO_EndIntegrityCheck

-- Use Example 1 --
  set CATlsoIntegrityChecker=1
  mkodt -s odtname
  grep LSO_INTEGRITY_ERROR odtname.*

-- Use Example 2 --
  set CATlsoIntegrityChecker=1
  set CATlsoIntegritySubChecker=JournalTranslation
  mkodt -s odtname
  grep LSO_INTEGRITY_ERROR odtname.*

-- Use Example 3 --
  lsoodt -i                           (It replays all ODT and return a txt file)

-- Use Example 4 --
  lsoodt -i  JournalTranslation       (It replays all ODT and return a txt file)
=============================================================================
*/
#include "PersistentCell.h"
#include "CATBoolean.h"

//--------------------------------------------------------------------------
// LSO_MACRO
// ----------------------------------------------------------------------------
// @nocgmitf
#define LSOMACRO_IsIntegrityActive(iCharSubCheckName, iCharTrigram)  {                                               \
                                                                    const char * pSubCheckName = iCharSubCheckName;  \
                                                                    const char * pTrigram      = iCharTrigram;       \
                                                                    if (IsIntegrityActive(pSubCheckName, pTrigram))  \
                                                                    { 
// @nocgmitf
#define LSOMACRO_DumpIntegrityError(iCharErrorMessage )            { DumpIntegrityError(pSubCheckName, pTrigram, iCharErrorMessage,1); }
// @nocgmitf
#define LSOMACRO_DumpIntegrityWarning(iCharErrorMessage )            { DumpIntegrityError(pSubCheckName, pTrigram, iCharErrorMessage,2); }

// @nocgmitf
#define LSOMACRO_EndIntegrityCheck                                }}

//-----------------------------------------------------------------------------
// Methods - Do not use, call the LSOMACRO
//-----------------------------------------------------------------------------
ExportedByPersistentCell CATBoolean IsIntegrityActive (const char * iSubCheckName, const char * iTrigram);
ExportedByPersistentCell void       DumpIntegrityError(const char * iSubCheckName, const char * iTrigram, const char * iErrorMessage,const int iSeveriy);

#endif
