#ifndef CATSysLMdefine_h
#define CATSysLMdefine_h

#include "CATSysDataType.h"
#include "CATIAV5ReleaseInfo.h"
#include "CATIAV5Level.h"

#define CATLM_DEFAULT_PRDID 1
#define CATLM_DEF_CMPD_VERSION 99

#define CATLM_CURRENT_TIME_FILTER       0xfffffffe
#define CATLM_NO_CURRENT_TIME_FILTER    0xffffffff
#define CATLM_COMPUTER_ID_MAX_LEN       128

#ifdef CATIAR210
#define UKU_PHASE_2 
#define SIMPLE_RETENTION    1
#define LOGON_RETENTION     2

#define LEGACY_MODE            0
#define CONCURRENT_MODE        1
#define NAMED_USER_MODE        2
#define KERNEL_NAMED_USER_MODE 4
#define CONNECTED_BATCH_SHAREABLE_MODE 8

#define CATNodelockPathEnvVar    "CATNodelockPath"
#define CATLM_DEFAULT_VERSION CATIA_RDK_NUMBER

#else
#define UKU_PHASE_1
#define UKU_RELEASE_DATE 1567036800 // Aug 29 2019 00:00:00
#define CATNodelockPathEnvVar    "NODELOCK_PATH"
#define CATLM_DEFAULT_VERSION 10
#define KERNEL_NAMED_USER_MODE 4
#endif

#define CATLM_USERNAME_LEN 256
#define CATLM_HOSTNAME_LEN 256
#define CATLM_DISPLAY_LEN  32 

#define CATLM_MAX_ADDON_NB       640
#define CATLM_ADDON_LEN          3
#define CATLM_MAX_ADDONS_LEN     (CATLM_ADDON_LEN*CATLM_MAX_ADDON_NB)
#define CATLM_MAX_BASE_LEN       12
#define CATLM_MAX_DES_LEN        512
#define CATLM_MAX_PRD_NAME_LEN   (CATLM_MAX_BASE_LEN + 1 + CATLM_MAX_ADDONS_LEN + 1)
#define CATLM_MAX_NAME_LEN       (CATLM_MAX_BASE_LEN + 1 + CATLM_MAX_ADDONS_LEN + 1)
#define CATLM_MAX_SRV_NAME_LEN   3*(256+1+5)+2 // 3 * (MAX_FQDN_LENTH + : + Port number) + 2 failover member separator 
#define CATLM_MAX_SRV_NB         20
#define CATLM_MAX_NB_INCLUD_PRD  10
#define CATLM_MAX_FEATURE_LEN    512 // LUM_FEATURES_LEN

#define LICENSE_MAX_NAME_SIZE           12
#define LICENSE_MAX_VERSION_SIZE        12
#define LICENSE_MAX_ANNOT_SIZE          255
#define LICENSE_VERSION_SN_LENGTH       7 /* truncated by WKMS */
#define LICENSE_SERIAL_NUMBER_LENGTH    11
#define LICENSE_ADD_ON_NAME_LENGTH      3
#define LICENSE_ADD_ON_DELIMITER        '-'
#define LICENSE_MAX_ADD_ON_LENGTH       (LICENSE_MAX_ANNOT_SIZE -\
                                         LICENSE_SERIAL_NUMBER_LENGTH-1)
#define NODELOCK_NAME            "nodelock"
#define CATOverrideLicenseEnvVar "CATOverrideLicense"

#define DSL_MAX_PATH_SIZE 1024


#ifdef _WINDOWS_SOURCE
    #define PRE_FMTLONGI64 "I64"
    #define CATLM_TARGETID_FMT "%016" "I64" "X"
    #define CATLM_VERSION_FMT  "%"    "I64" "d"
#else
    #define PRE_FMTLONGI64 "ll"
    #define CATLM_TARGETID_FMT "%016" "ll" "X"
    #define CATLM_VERSION_FMT  "%"    "ll" "d"
#endif

#ifdef UKU_PHASE_2
typedef char          lm_prd_name[CATLM_MAX_PRD_NAME_LEN];
typedef lm_prd_name   lm_prd_name_tab[CATLM_MAX_NB_INCLUD_PRD];
typedef char          lm_prd_alias[300];
typedef char          lm_prd_desc[CATLM_MAX_DES_LEN];
typedef char          lm_base[CATLM_MAX_BASE_LEN];
typedef char          lm_addons[CATLM_MAX_ADDONS_LEN];
#if !defined(_WINDOWS_SOURCE) && defined (PLATEFORME_DS64)
typedef CATLONGINT    lm_timestamp;
typedef CATLONGINT    lm_version;
typedef CATULONGINT   lm_target_id;
#else
typedef CATLONG64     lm_timestamp;
typedef CATLONG64     lm_version;
typedef CATULONG64    lm_target_id;
#endif
typedef char          lm_licenser_name[33]; // LUM
typedef char          lm_licenser_id[33];   // targetId
typedef char          lm_features[CATLM_MAX_FEATURE_LEN];

typedef char          lm_server[CATLM_MAX_SRV_NAME_LEN];
typedef lm_server     lm_server_tab[CATLM_MAX_SRV_NB];
typedef char          lm_user_name[32];  //LUM_USER_NAME_LEN
#endif
typedef enum {
/*    NODELOCKED          = 1  << 0,
    OFFLINE_NODELOCKED  = 1  << 1,
    CONCURRENT_USER     = 1  << 2,
    NAMED_USER          = 1  << 3,
    TOKEN               = 1  << 4*/
    LICTYPE_TOOLS       = 1  << 8,
    LICTYPE_INCLUDED    = 1  << 9,
} dsl_lic_model_internal;

typedef enum {
    DSLDefaultProcessGroup=0,
    DSLSwymProcessGroup
}dsl_process_group;

#define ALL_OFFLINE       (dsl_lic_model) (OFFLINE_CONCURRENT_USER | OFFLINE_NAMED_USER) 
#define ALL_CONCURRENT    (dsl_lic_model) (CONCURRENT_USER | NAMED_USER | TOKEN | CREDIT)
#define ALL_NODELOCKED    (dsl_lic_model) (NODELOCKED      | OFFLINE_CONCURRENT_USER | OFFLINE_NAMED_USER) 
#define ALL_BUT_TOKEN     (dsl_lic_model) (NODELOCKED      | OFFLINE_CONCURRENT_USER | OFFLINE_NAMED_USER | CONCURRENT_USER | NAMED_USER )
#define ANY_LIC_TYPE      (dsl_lic_model) (NODELOCKED      | OFFLINE_CONCURRENT_USER | OFFLINE_NAMED_USER | CONCURRENT_USER | NAMED_USER | TOKEN | CREDIT)
#define NO_LIC_TYPE       (dsl_lic_model) (0)
#ifdef UKU_PHASE_2
class PKGEnum {
    public :
        // Some enum imported from CATLM have been moved here 
        typedef enum {
            ChassisUndefined = 0,
            ChassisP,
            ChassisP2,
            ChassisP3
        } ChassisLevel;

        typedef enum {
            standAlone        = 0x000001,
            configuration     = 0x000002,
            customConfig      = 0x000004,
            customConfigAlias = 0x000008,
            userExperience    = 0x000010,
            app               = 0x000020,
            technicalProduct  = 0x000040,
            commercialProduct = 0x000080,
            allProductTypes   = 0x0000ff,

            // flags for external use
            licensedFlag      = 0x000100,
            shareableFlag     = 0x000200,
            addonFlag         = 0x000400,
            richClientPart    = 0x000800,

            // client/server type
            whereUsedNamedUser    = 0x001000,
            whereAccessedNamedUser= 0x002000,

            // flags for internal use only
            anyProductAttr    = 0x0000000,
            allProductAttrs   = 0xfff0000,
            visible           = 0x0010000,
            licensed          = 0x0020000,
            addon             = 0x0040000,
            shareable         = 0x0080000,
            representation    = 0x0100000,
            delegation        = 0x0200000,
            token             = 0x0400000,
            namedUser         = 0x0800000,
            credit            = 0x1000000 
        } ProductType;

        typedef struct {
            const char *name;
            unsigned int id;
            char authLevel;
            char hasChangedFlag;
        } FrameworkInfo;
};


#endif

#endif
