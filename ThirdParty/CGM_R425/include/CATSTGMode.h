#ifndef __STGMODE
#define __STGMODE
/** @CAA2Required */
/**********************************************************************/
/* DON T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS */
/* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPEAR AT ANY TIME */
/**********************************************************************/


// COPYRIGHT DASSAULT SYSTEMES 2000

#ifdef _WINDOWS_SOURCE
#else

/* Storage instantiation modes */
#define STGM_DIRECT			0x00000000
#define STGM_TRANSACTED			0x00010000
#define STGM_SIMPLE			0x08000000

#define STGM_READ			0x00000000
#define STGM_WRITE			0x00000001
#define STGM_READWRITE			0x00000002

#define STGM_SHARE_DENY_NONE		0x00000040
#define STGM_SHARE_DENY_READ		0x00000030
#define STGM_SHARE_DENY_WRITE		0x00000020
#define STGM_SHARE_EXCLUSIVE		0x00000010

#define STGM_PRIORITY			0x00040000
#define STGM_DELETEONRELEASE		0x04000000

#define STGM_NOSCRATCH			0x00100000


#define STGM_CREATE			0x00001000
#define STGM_CONVERT			0x00020000
#define STGM_FAILIFTHERE		0x00000000

#define STGM_NOSNAPSHOT			0x00200000

/*  flags for internet asynchronous and layout docfile */
#define ASYNC_MODE_COMPATIBILITY	0x00000001
#define ASYNC_MODE_DEFAULT		0x00000000

#define STGTY_REPEAT			0x00000100
#define STG_TOEND			0xFFFFFFFF

#define STG_LAYOUT_SEQUENTIAL		0x00000000
#define STG_LAYOUT_INTERLEAVED		0x00000001

#endif
#define CATSTGM_ZIPALL			0x40000000

// DS specifics
#define CATSTGM_NONAMECTRL      0x80000000
#define CATSTGM_FULLSAVE        0x10000000
#define CATSTGM_DIRECTWRITE     0x00000002
#define CATSTGM_TMPCOPY         0x00000001
#define CATSTGM_NOFLUSH         0x00800000
#define CATSTGM_NOCRYPT         0x00000800
#define CATSTGM_LARGEFILE       0x00008000
#define CATSTGM_NOLF            0x00004000
#define CATSTGM_MAPPEDFILE      0x20000000
#define CATSTGM_PREAD           0x40000000
#define CATSTGM_NODRMUSE        0x00000080
#endif
