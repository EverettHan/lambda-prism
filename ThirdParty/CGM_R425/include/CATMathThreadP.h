//_________________________________________________________________________
// P REISS   01/06
// CATMathThreadP.h
// objet transmis a un thread

#ifdef _WINDOWS_SOURCE
// typedef void* HANDLE;             // evite windows.h
#define PAGESIZE 0x1000              // 4 Ko
#include "CATMathInline.h"
#include "CATIACGMLevel.h"
class CATMathPoolThread;

class CATMathThreadP
  {
  public:
    friend CATMathPoolThread;    // accede aux donnees membres de CMThread
    friend DWORD CATMathThreadStart  ( void *iPThread );
    friend DWORD CATMathDormeurStart ( void *iPThread );
     CATMathThreadP ()
       : _Debut (-1), _Fin (-1), _Alloc (0), _SizeAlloc (0) {}
    ~CATMathThreadP ();
    INLINE DWORD  GetThreadId ();

  protected:
#if defined CATIACGMR421CAA && !defined _AIX_SOURCE
           int    SetHThread ( silla iTid,         silla iCores,
                               silla iLogiProcs,   silla iHyperThread,
                               int iPriority );
           void   SetDormeur ( silla iTid,         silla iHyperThread,
                               int iPriority);
#else
           int    SetHThread ( silla iTid,         silla iClusters,
                               silla iPhysiPacks,  silla iCores,
                               silla iLogiProcs,   silla iHyperThread,
                               silla iContiguous,  int iPriority );
           void   SetDormeur ( silla iTid,         silla iHyperThread,
                               silla iContiguous,  int iPriority );
#endif
           void*  Reserve    ( ulla  iSizeof );
                                     // pour Rajout sous Vastob
             HANDLE _HThread;        // handle de thread
             HANDLE _HSem;           // handle de semaphore associe
             DWORD  _ThreadId;       // thread id au sens systeme
             char  *_Alloc;          // pour Vastob
             ulla   _SizeAlloc;      // pour Vastob
             int    _Avant[0x10];    // memoire jamais accedee (64 octets)

    // 3 entites _Tid, _Debut, _Fin contigues, dans cet ordre
    // pour SpinSuisse (3*4/3*8 octets selon 32/64 bits)

             silla  _Tid;            // thread id au sens Open MP
    volatile silla  _Debut;          // iters sur [_Debut, _Fin[
    volatile silla  _Fin;
             int    _Apres[0x10];    // memoire jamais accedee (64 octets)
             int    _NormalPriority; // celle du master avant le ct
             int    _BetterPriority; // +1
    static   silla  _Master;         // master thread affinity mask =
                                     // 1 << (_Master << (Hyper & Contig))
  };
//_________________________________________________________________________
INLINE DWORD CATMathThreadP::GetThreadId ()
  { return _ThreadId; }
#endif                               // _WINDOWS_SOURCE
