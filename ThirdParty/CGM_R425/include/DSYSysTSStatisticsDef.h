# ifndef _DSYSYSTSSTATDEF
# define _DSYSYSTSSTATDEF

// COPYRIGHT DASSAULT SYSTEMES 2008


/************************************************************************/
/* Thematics name definitions                                           */
/************************************************************************/
/** Thematics identifiers */
enum
{
  COMMAND_THEM_ID = 0   /* 0 */
, WORKBENCH_THEM_ID     /* 1 */
, NETWORK_THEM_ID       /* 2 */
, SESSION_THEM_ID       /* 3 */
, PCS_THEM_ID           /* 4 */
, AUDIT_THEM_ID         /* 5 */
, ACTIVITY_THEM_ID      /* 6 */
, ERRORLOG_THEM_ID      /* 7 */
, DEBUG_THEM_ID         /* 8 */
, S_ActiveThematicsNamesCount
};

/** Array of active thematics names */
static const char* const S_pActiveThematicsNames[] =
{
  "COMMAND"   /* 0 */
, "WORKBENCH" /* 1 */
, "NETWORK"   /* 2 */
, "SESSION"   /* 3 */
, "PCS"       /* 4 */
, "AUDIT"     /* 5 */
, "ACTIVITY"  /* 6 */
, "ERRORLOG"  /* 7 */
, "DEBUG"     /* 8 */
};

/** Thematics name defines */
#define CMD_THEMATIC_CONST_NAME    S_pActiveThematicsNames[COMMAND_THEM_ID]
#define WKB_THEMATIC_CONST_NAME    S_pActiveThematicsNames[WORKBENCH_THEM_ID]
#define NET_THEMATIC_CONST_NAME    S_pActiveThematicsNames[NETWORK_THEM_ID]
#define SES_THEMATIC_CONST_NAME    S_pActiveThematicsNames[SESSION_THEM_ID]
#define PCS_THEMATIC_CONST_NAME    S_pActiveThematicsNames[PCS_THEM_ID]
#define AUD_THEMATIC_CONST_NAME    S_pActiveThematicsNames[AUDIT_THEM_ID]
#define ACT_THEMATIC_CONST_NAME    S_pActiveThematicsNames[ACTIVITY_THEM_ID]
#define ERR_THEMATIC_CONST_NAME    S_pActiveThematicsNames[ERRORLOG_THEM_ID]
#define DBG_THEMATIC_CONST_NAME    S_pActiveThematicsNames[DEBUG_THEM_ID]

/************************************************************************/
/* Thematics statistics field definitions                               */
/************************************************************************/
/** Thematic statistics identifier */
enum
{
  THEM_ID = 0         /*  0 */
, TIME_ID             /*  1 */
, ENDTIME_ID          /*  2 */
, ELPS_ID             /*  3 */
, RTIME_ID            /*  4 */
, CPUS_ID             /*  5 */
, USER_ID             /*  6 */
, HOST_ID             /*  7 */
, UPID_ID             /*  8 */
, WRKB_ID             /*  9 */
, CMD_ID              /* 10 */
, CMDSTART_ID         /* 11 */
, MEMORYSTART_ID      /* 12 */
, MEMORYEND_ID        /* 13 */
, MEMORYSTARTMAX_ID   /* 14 */
, MEMORYENDMAX_ID     /* 15 */
, LEVEL_ID            /* 16 */
, GROUPMETHOD_ID      /* 17 */
, GROUPCOUNT_ID       /* 18 */
, BEGINEVENT_ID       /* 19 */
, ENDEVENT_ID         /* 20 */
};

/** Array of statistics tag name for each thematic */
static const char* const S_pThemStatisticsFieldName[] =
{
  "them"      /*  0 */
, "time"      /*  1 */
, "end_time"  /*  2 */
, "elps"      /*  3 */
, "rtim"      /*  4 */
, "cpus"      /*  5 */
, "user"      /*  6 */
, "host"      /*  7 */
, "upid"      /*  8 */
, "wkb"       /*  9 */
, "cmd"       /* 10 */
, "cmdstart"  /* 11 */
, "start_mem" /* 12 */
, "end_mem"   /* 13 */
, "start_max" /* 14 */
, "end_max"   /* 15 */
, "level"     /* 16 */
, "method"    /* 17 */
, "nb_iter"   /* 18 */
, "bevt"      /* 19 */
, "eevt"      /* 20 */
};

/** Thematic statistics defines */
#define THEM_THEMATIC_FIELDNAME             S_pThemStatisticsFieldName[THEM_ID]
#define TIME_THEMATIC_FIELDNAME             S_pThemStatisticsFieldName[TIME_ID]
#define ENDTIME_THEMATIC_FIELDNAME          S_pThemStatisticsFieldName[ENDTIME_ID]
#define ELPS_THEMATIC_FIELDNAME             S_pThemStatisticsFieldName[ELPS_ID]
#define RTIME_THEMATIC_FIELDNAME            S_pThemStatisticsFieldName[RTIME_ID]
#define CPUS_THEMATIC_FIELDNAME             S_pThemStatisticsFieldName[CPUS_ID]
#define USER_THEMATIC_FIELDNAME             S_pThemStatisticsFieldName[USER_ID]
#define HOST_THEMATIC_FIELDNAME             S_pThemStatisticsFieldName[HOST_ID]
#define UPID_THEMATIC_FIELDNAME             S_pThemStatisticsFieldName[UPID_ID]
#define WRKB_THEMATIC_FIELDNAME             S_pThemStatisticsFieldName[WRKB_ID]
#define CMD_THEMATIC_FIELDNAME              S_pThemStatisticsFieldName[CMD_ID]
#define CMDSTART_THEMATIC_FIELDNAME         S_pThemStatisticsFieldName[CMDSTART_ID]
#define MEMORYSTART_THEMATIC_FIELDNAME      S_pThemStatisticsFieldName[MEMORYSTART_ID]
#define MEMORYEND_THEMATIC_FIELDNAME        S_pThemStatisticsFieldName[MEMORYEND_ID]
#define MEMORYSTARTMAX_THEMATIC_FIELDNAME   S_pThemStatisticsFieldName[MEMORYSTARTMAX_ID]
#define MEMORYENDMAX_THEMATIC_FIELDNAME     S_pThemStatisticsFieldName[MEMORYENDMAX_ID]
#define LEVEL_THEMATIC_FIELDNAME            S_pThemStatisticsFieldName[LEVEL_ID]
#define GROUPMETHOD_THEMATIC_FIELDNAME      S_pThemStatisticsFieldName[GROUPMETHOD_ID]
#define GROUPCOUNT_THEMATIC_FIELDNAME       S_pThemStatisticsFieldName[GROUPCOUNT_ID]
#define BEGINEVENT_THEMATIC_FIELDNAME       S_pThemStatisticsFieldName[BEGINEVENT_ID]
#define ENDEVENT_THEMATIC_FIELDNAME         S_pThemStatisticsFieldName[ENDEVENT_ID]

/************************************************************************/
/* Current statistics field definitions                                 */
/************************************************************************/
/** Current statistics tag identifier */
enum
{
  COMMAND_TAG_ID = 0        /* 0 */
, WORKBENCH_TAG_ID          /* 1 */
, CURRENTWORKBENCH_TAG_ID   /* 2 */
};

/** Array of current statistics field name */
static const char* const S_pCurrentThemStatisticsTagName[] = 
{
  "Command"           /* 0 */
, "Workbench"         /* 1 */
, "CurrentWorkbench"  /* 2 */
};

/** Current statistics tag defines */
#define COMMAND_TAGNAME             S_pCurrentThemStatisticsTagName[COMMAND_TAG_ID]
#define WORKBENCH_TAGNAME           S_pCurrentThemStatisticsTagName[WORKBENCH_TAG_ID]
#define CURRENT_WORKBENCH_TAGNAME   S_pCurrentThemStatisticsTagName[CURRENTWORKBENCH_TAG_ID]


# endif /* _DSYSYSTSSTATDEF */
