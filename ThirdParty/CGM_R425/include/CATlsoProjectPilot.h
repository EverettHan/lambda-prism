/* -*-C++-*- */

#ifndef CATlsoProjectPilot_H
#define CATlsoProjectPilot_H
/*  
=============================================================================

RESPONSABLE  : L Marini

DESCRIPTION  : class to pilot - project on Live Shape Operator
                              - temporary code for test
                              
               
=============================================================================
*/
// --------------------------------------------------------
/* Exemple of code:

// Return a boolean
// ----------------
#include "CATlsoProjectPilot.h"
CATBoolean ok = GetLSOProjectStatus(CATlsoProjectPilot::DEFORMFACE_NEWRUN);

// Return an interger
// ------------------
#include "CATlsoProjectPilot.h"
int g1g2Level = GetLSOProjectLevel(CATlsoProjectPilot::REMOVEFACEG1G2);


// For temporary code
// ------------------
#include "CATlsoProjectPilot.h"
CATBoolean ok = GetLSOOnlyForTestStatus("LAP");          // use your trigram as filter or any other string
int level     = GetLSOOnlyForTestLevel("LAPTest1");      // use your trigram as filter or any other string

// For temporary code : pilot a tolerance
// --------------------------------------
#include "CATlsoProjectPilot.h"
double tolerance = 0.001;
int    level     = GetLSOOnlyForTestLevel("LAP");
if (level)
  tolerance = pow((double)10.,-level);

*/
// --------------------------------------------------------

#include "PersistentCell.h"
#include "CATBoolean.h"

//--------------------------------------------------------------------------


class CATlsoProjectPilot
{

public:

  enum  ProjectName { ONLY_FOR_TEST=0,
                      ONLY_FOR_TEST_2,
                      REMOVEFACEG1G2,
                      NO_REMOVE_BODY,
                      CALL_FACEREPLACESURFACE,
                      DREP_CHECKER,
                      DREP_SYNTHESISDUMP,
                      INCREMENTAL_MULTIRUN_START,
                      DICHOTOMY_FOR_EXTRAPOL,
                      CHECK_JOURNAL,
                      XTRIM_DEBUG_BODIES,
                      LSO_INTERRUPT_TRACES,
                      LSO_INTERRUPT_STAGE,
                      LSOTRACE_SHORTMODE,
                      PERFO_CREATEPB,
                      NEW_CANONIC_DREP,
                      CHANGE_DREPBEHAVIOR,
                      RFO_JOINTS_ONLY_PROTO,
                      NRF,
                      NRF_LOGOSANDEXTRUSIONS,
                      TF_XTRIM_INPUTJOURNAL,
                      DEFEATURE_PAIRING_FACES_PROTO,
                      ODTLIVE_BREPTODREP_FIRST,
                      DEFEATURE_SINGLE_CMMANAGER,
                      MSO_INDUS_N_DEBUG,
                      MSO_CHECK_DEBUGMODE,
                      POLYMORPHING_POINT_FILTER,
                      POLYMORPHING_GROUPING_MODE,
                      CGMREPLAY_PREFIX,
                      DISPATCH_NOPREVIEW_2,
                      TRANSFERT_ACTIVATE,
                      LOCAL_BUILD,
                      DRAFTCOLOR_R,
                      DRAFTCOLOR_G,
                      DRAFTCOLOR_B,
                      LSO_FPS,
                      LSO_ONEFPS,
                      AVOID_UNIONPCELL,
                      MPRUNNER_DEBUG,
                      GTA_EDGECOUPLE_DEBUG,
                      GTA_PAIRINGTHICKNESS_DEBUG,
                      AUTOPARTITIONING_SIMULIACHECKERCONSISTENCY,
                      AUTOPARTITIONING_ROLLBACKMODE,
                      POLYMORPHING_ONLY_AREA,
                      POLYMORPH_CHECK_NEEDDEFORM,
                      POLYMORPH_ADAPT_ATTENUATION,
                      POLYMORPH_SHOW_FIELD,
                      //  /\
                      //  ||   Insert the new debug project above
                      //  ||                                                                                                   
                      // Add line in cpp file in the methode: SetProjectNameAndStatus()
                      // Add line in cpp file for the variable : static CATLONG32 _ProjectDefaultValue[CATlsoProjectPilot::NB_PROJECTS+2]=
                      NB_DEBUG_PROJECTS,
                      // -----------------------------------------------------------------
                      TRANSFORMFACE_FLEXIBLE,
                      TRANSFORMFACE_XTRIM,
                      STEP3_USERPCELLS,
                      VARIATIONAL,
                      DEFORMFACE_NEWSEW,
                      DREP_OFFSET,
                      MIRROR,
                      PATTERN_LIMITATION,
                      NO_SPLIT_IN_DOMAINS,
                      CLASH_STATUS_NEWSPEC,
                      JOURNAL_BASED_PATTERN_CREATION,
                      MSO_ALGO_SEQUENCE,
                      //FEATURECOGNITION_DROP_0,
                      FILTERBEFORETRIMSEW,
                      LIVESINGLEBOOLEAN,
                      PATTERNREPLICATOR,
                      PLANNURBS,
                      ISOPATTERN,
                      AUTOMIRROR,
                      PROTOCARTON,
                      POWER_REVOLPRISM,
                      //MANIFOLD_PROPAGATION,
                      VARIABLE_RADIUS_FILLET_RECOGNITION,
                      NOTUPTODATE_PATTERN_IMPROVEMENT,
                      DREP_OFFSET_CREATOR,
                      APTRACKER_NEWTIMER,
                      FACE_ANALYZER_ENHANCEMENT,
                      EDITOR_UXDREP,
                      MSO_ZONING,
                      CREATE_BORDER_FACES,
                      DISPATCH_DEL_PREVIEWMODE,
                      FILLETSCAR_PERSISTENTEDGE,
                      CONTEXTUAL_DEPENDENCY,
                      EXTRUDE_DRAFT_NEWSPEC,
                      CONTEXTUAL_DEPENDENCY_RIBBON_PROPAGATION,
                      AUTOPARTITIONING_CSV,
                      AUTOPARTITIONING_DEFEATURING,
                      DEFEATURE_DRAFT_GROUPING,
                      DIRECT_MOVE_DRAFT,
                      NEW_NEUTRAL_DRAFT_MOVE,
                      AUTOPARTITIONING_GRIDPATTERN,
                      AUTOPARTITIONING_TARGETLIMITATIONS,
                      GTA_PAIRINGTHICKNESS,
                      AUTOPARTITIONING_CONFIGURATIONFILE,
                      KEEPTOP,
                      //  /\
                      //  ||   Insert the new project above
                      //  ||                                                                                                   
                      // Add line in cpp file in the methode: SetProjectNameAndStatus()
                      NB_PROJECTS};

  static short SetProjectNameAndStatus();

  static int ReadVariableEnvWithoutCATDevelopmentStage(int iDefaultValue, char * iVarName);

private:
  static int ReadVariableEnv(int iDefaultValue, char * iVarName);
};

//-----------------------------------------------------------------------------
// Get and Set ProjectStatus(ON/OFF) ou level [-1,0,1,2,3,..]
//-----------------------------------------------------------------------------
ExportedByPersistentCell CATBoolean   GetLSOProjectStatus(CATlsoProjectPilot::ProjectName iProjectName);
ExportedByPersistentCell int          GetLSOProjectLevel(CATlsoProjectPilot::ProjectName iProjectName);
ExportedByPersistentCell int          GetLSOProjectDefaultLevel(CATlsoProjectPilot::ProjectName iProjectName);
ExportedByPersistentCell CATBoolean   GetLSOOnlyForTestStatus(const char * iUserNameFilter);
ExportedByPersistentCell CATBoolean   GetLSOOnlyForTestStatus2(const char * iUserNameFilter);
ExportedByPersistentCell int          GetLSOOnlyForTestLevel(const char * iUserNameFilter);
ExportedByPersistentCell int          GetLSOOnlyForTestLevel2(const char * iUserNameFilter);

//-----------------------------------------------------------------------------
// METHODES FOR PANEL
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Set ProjectStatus(ON/OFF) ou level [-1,0,1,2,3,..]
//-----------------------------------------------------------------------------
ExportedByPersistentCell void         SetLSOProjectStatus(CATlsoProjectPilot::ProjectName iProjectName,CATBoolean iStatus);
ExportedByPersistentCell void         SetLSOProjectLevel(CATlsoProjectPilot::ProjectName iProjectName,int iLevel);
ExportedByPersistentCell void         SetLSOProjectToDefaultLevel(CATlsoProjectPilot::ProjectName iProjectName);

//-----------------------------------------------------------------------------
// GetLSOProjectName
//-----------------------------------------------------------------------------
ExportedByPersistentCell const char * GetLSOProjectName(CATlsoProjectPilot::ProjectName iProjectName);

//-----------------------------------------------------------------------------
// GetLSOProjectNumber
//-----------------------------------------------------------------------------
ExportedByPersistentCell int          GetLSOProjectNumber();

//-----------------------------------------------------------------------------
// SetLSOProjectUserNameFilter
//-----------------------------------------------------------------------------
ExportedByPersistentCell void         SetLSOProjectUserNameFilter(const char* iUserNameFilter);

// SetLSOProjectUserNameFilter2
//-----------------------------------------------------------------------------
ExportedByPersistentCell void         SetLSOProjectUserNameFilter2(const char* iUserNameFilter);

#endif
