#ifndef CATSTACKTRACE_INCLUDE
#define CATSTACKTRACE_INCLUDE


// COPYRIGHT DASSAULT SYSTEMES 2000

#include "JT0TRCBK.h"
#include <stdio.h>
#ifdef _IRIX_SOURCE
#include <exception.h>
#elif _SUNOS_SOURCE
#include <sys/frame.h>
#endif

#ifdef _IRIX_SOURCE
#define CATSTACKTRACE_INIT	int __CATStackTraceDummy__ = PSIZE
#else
#define CATSTACKTRACE_INIT
#endif
#ifdef _WINDOWS_SOURCE
#include <windows.h>
#endif

// ++vxg - 10:05:06 - Do buffer enlargement on WINDOWS for JRZ.
#ifdef _WINDOWS_SOURCE
# undef VXG_CATSTACKTRACE_BUFFER_ENLARGEMENT
#else
# define VXG_CATSTACKTRACE_BUFFER_ENLARGEMENT
#endif  // _WINDOWS_SOURCE
// --vxg - 10:05:06

// ++vxg - 10:05:06
#ifdef VXG_CATSTACKTRACE_BUFFER_ENLARGEMENT
#define CATSTACKTRACE_PROCNAME_MAXLEN	64 /* Long enough for JJA? */
#define CATSTACKTRACE_MAXDEPTH		40
#else // VXG_CATSTACKTRACE_BUFFER_ENLARGEMENT
# define CATSTACKTRACE_PROCNAME_MAXLEN      128 /* Long enough for JRZ? */
# define CATSTACKTRACE_MAXDEPTH             60
# define CATSTACKTRACE_FILENAME_MAXLEN      96
#endif  // VXG_CATSTACKTRACE_BUFFER_ENLARGEMENT
// --vxg - 10:05:06
#define CATSTACKTRACE_UNKNOWN_PROCNAME	"?Unknown?"

/** obtains a stack based upon iThreadContext and put it in iIPVector table */
/** do not try to get the symbols. Only obtains the IP table                */
ExportedByJT0TRCBK int  CATSysGetIPStack( void *iThreadContext, int iFrom, int iTo, void **iIPVector, int iIPVectorSize );

/** obtains the symbols corresponding to the IP store in iIPVector table */
/** and generate the stack symbols on the given stream                   */
ExportedByJT0TRCBK int CATSysDecodeIPStack( void **iIPVector,int iNb  , FILE *oFile);

/** obtains a symbol corresponding to a given instruction pointer  */
/** if  iToFile is  not NULL output it into iToFile                */
/** if  iBuffer is  not NULL store the symbol into iBuffer         */
ExportedByJT0TRCBK int CATSysGetSymbol(void *iPc, FILE *iToFile=NULL, char *iBuffer=NULL, int iLenBuff=0,int ilowRessource=0);


class ExportedByJT0TRCBK CATBasicStackTrace {

public:
    CATBasicStackTrace () { depth = 0; }
    virtual int GetTrace () = 0;
    virtual int GetTrace (void *) = 0;
    int GetDepth ();
    void Print (FILE *out = stdout, int fromDepth = 0, int toDepth = 0);
    void Print (void(*ipPrintFunc)(void*, const char*, const char*, const char*, const int), void* ipUserObj);
    void Read (int level, char *procName, int nameSize);

protected:
    int depth;
    typedef   struct  _StackElem {
        void *pc;
        char procName[CATSTACKTRACE_PROCNAME_MAXLEN];
#ifdef _WINDOWS_SOURCE
        char symName[CATSTACKTRACE_PROCNAME_MAXLEN];
        char modName[CATSTACKTRACE_PROCNAME_MAXLEN];
        DWORD64 _Addr;
        DWORD64 _Displacement;
        DWORD  _Size;
#endif  // _WINDOWS_SOURCE
    } StackElem;
    StackElem level[CATSTACKTRACE_MAXDEPTH];
};

class ExportedByJT0TRCBK CATStackTrace : public CATBasicStackTrace {

public:
    int GetTrace ();
    // The arguments are 'void *' because we don't want to pull in
    // too many system dependent definitions.
    int GetTrace (void *);
    int DirectTrace (FILE *iFic,void *, int iFrom=0, int iTo=99);
    int GetIPStack(void *);
    void PrintIPStack(FILE *out = stdout, int fromDepth = 0, int toDepth = 99);

private:
#ifdef _AIX_SOURCE
    int GetTraceInternal (void *, void *, int iN=-1, FILE *iFic=NULL, int iFr=0, int iTo=99);
#elif _SUNOS_SOURCE
    int GetTraceInternal (void *, void *, int iN=-1, FILE *iFic=NULL, int iFr=0, int iTo=99);
    void GetProcNames (FILE *iFic=NULL, int iFrom=0, int iTo=99);
#elif _HPUX_SOURCE
    void GetProcNames (FILE *iFic=NULL, int iFrom=0, int iTo=99);
    int GetTraceInternal (void *,int iN=-1,FILE *iFic=NULL, int iFr=0, int iTo=99);
#elif _WINDOWS_SOURCE
    long GetTraceInternal (  void *  ilpep ,int iN=-1,FILE *iFic=NULL, int iFr=0, int iTo=99);
#endif
};

#endif
