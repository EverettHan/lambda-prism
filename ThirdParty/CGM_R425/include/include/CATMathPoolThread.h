#ifndef CATMathPoolThread_h
#define CATMathPoolThread_h
//___________________________________________________________________________
// P REISS   01/06
// CATMathPoolThread.h
// gestion en pool de microthreads equilibres, de duree courte, sans mutex
// et en phase les uns avec les autres
//
//*** Documentation:
//   #include "CATMathematics.h"
//   #include "CATMathPoolThread.h"
//   CATMathPoolThread* _TheThreadPool = CATMathPoolThread::Get ();
//   MaxThreads = _TheThreadPool->GetMaxThreads ();
//     en debut de session
//   il existe alors des threads dormants de Tid = [0, MaxThreads[
//
//   debut de zone parallele: (code initial = boucle for sur [0, NbIters[)
//     _TheThreadPool->Dispatcher ( (silla) nombre d' iters );
//   le contenu de la boucle parallelisee sera dans la methode:
//     void Talgo ( (silla) Tid, (silla) Debut, (silla) Fin );
//     avec une boucle locale sur [Debut, Fin[
//   Contexte pointe un objet ou vous logez toutes les variables de la
//     zone non parallele et dont la boucle parallelisee a besoin en
//     lecture
//
//   un ensemble de zones paralleles rapprochees pourra etre encadre
//   avec profit par les 2 calls
//     _TheThreadPool->RedOrange (); et
//     _TheThreadPool->ReturnToRed ();
//   (dans cet intervalle, le sommeil des MaxThreads-1 threads dans
//    WaitForSingleObject est remplace par des "spin wait loops")
//
//   avant l' execution, faire
//     "set OMP_NUM_THREADS = mmm", mmm limite a 64, 1 par defaut
//   qui pilote _MaxThreads
//   _NbThreads <= _MaxThreads
//
//*** UNIQUE OBJET CATMathPoolThread
// GetMaxThreads = nombre de threads de zone parallele
// _RelaisSem dans zone de 128 octets ( alignee sur 128 octets ) jamais
//   accedee sauf pour ses 2 semaphores ( cf doc Intel System programming
//   "Place locks and semaphores in aligned 128-byte blocks of memory" )
//
// Dispatcher depend de la taille des entites manipulees par les algos:
//   (un registre XMM sous SSE2 contient 0x10 octets)
// OwordDispatcher sur algos manipulant des complexes de 0x10 octets   |C|
// QwordDispatcher sur algos manipulant des doubles                    |R|
// DwordDispatcher sur algos manipulant des floats ou des entiers      |R|Z|
// WordDispatcher  sur algos manipulant des shorts                     |Z|
// ByteDispatcher  sur algos manipulant des octets                     |Z|
// CacheDispatcher sur algos manipulant des doubles
//
// alors, QwordDispatcher par exemple, favorise une distribution des
// iterations, thread par thread, avec un maximum de nombres pairs, pour
// eviter de casser l' avantage des registres xmm
// de meme, DwordDispatcher distribue avec un maximum de nombres 4*N, etc...
//
// exigence de commutation rapide entre master et esclaves:
//   _RelaisSem     (char)   autant que de cores
//   _Debut         (silla)  autant que de cores
//   _Fin           (silla)  autant que de cores
// SetStobAlgo agit suffisamment tot pour eviter cette exigence sur:
//   _Contexte[Tid] (void*)
//   _StobAlgo      (void*)
// Definition:
//   _CommutRead est le nombre de cycles qui s' ecoulent
//   entre l' instant ou un thread ecrit un semaphore et
//   celui ou un autre thread lit cette information a jour
//   _CommutWrite designe le temps, un peu plus long, pour que
//   l' autre thread reecrive le semaphore
//   (voir utilisation dans main.cpp de TestStobT.sh)
//
// Astob = ASynchronous Tiny Operating Block, version degradee
//
// utilisation de _Sortie:
//   CATMathPoolThread* ThePool = CATMathPoolThread::Get ();
//   FILE *Sortie = <FILE*>;
//   ThePool->SetSortie ( Sortie );
//   ...
//   FILE *Sortie = ThePool->GetSortie ();
//   fprintf ( Sortie, "<format>", <liste de variables> );
//
// usage de volatile:
//   volatile   int *P;          P = pointeur sur int volatile
//   int*  volatile  P;          P = pointeur volatile sur int
//   void* volatile *P;          P = pointeur sur pointeur volatile sur void
//                               ( exemple: P = cast sur &_StobAlgo )
//   volatile Objet* volatile P; P = pointeur volatile sur objet volatile

class CATMathPoolMT;

// #ifdef _WINDOWS_SOURCE
#if defined(_MSC_VER) && _MSC_VER>=1400

#include "omp.h"                   // pour OpenMP
#include "stdio.h"
#include "stdlib.h"                // pour malloc
#include "string.h"                // pour memcpy
#include "windows.h"

#if !defined(_WIN64) && defined(_PIERRE)
typedef  DWORD      DWORD_PTR;     // en mode 32 bits
#endif

#include "CATMathematics.h"
#include "CATMathInline.h"
#include "CATArithTypes.h"
#include "CATBaseComputation.h"
#include "CATStobUtilAsm.h"        // utilitaires en asm
#define  MILLISEC   400            // laps de 400 ms pour Windows
#define  LAPS       125            // laps de 125 ms pour Catia

// STOB     synchrone
// ASTOB    asynchrone avec contexte dans meme classe
// VASTOB   asynchrone avec contexte dans differentes classes

enum { STOB, ASTOB, VASTOB };
enum { CATTHREADUSE, CATTHREADVOID, CATTHREADCOMPUTE, CATTHREADOPTIM = 4,
       CATTHREADWAIT = 8 };
//___________________________________________________________________________
class CATMathThreadP;
extern "C" ExportedByCATMathematics void CATBestTimeMeasure
  ( ulla Mesure, ulla* Best );

class ExportedByCATMathematics CATMathPoolThread
  {
  public:
     CATMathPoolThread ();
    ~CATMathPoolThread ();
    INLINE int   GetMaxThreads   ();  // nb cores * nb processeurs
    INLINE int   GetNbThreads    ();  // nb de threads effectifs
    INLINE silla GetLogThreads   ();  // log base 2 du nb de threads
    INLINE int   GetCommutRead   ();  // nb de cycles par commutation (read)
    INLINE int   GetCommutWrite  ();  // nb de cycles par commutation (write)
    INLINE int   GetVoid         ();  // tare sur mesure de commutation
    INLINE volatile ulla* GetPThreadCase ();
                                      // pointeur sur _ThreadCase
    INLINE int   IsInParallel    ();  // est-on deja en zone parallele?
    INLINE int   RetrieveTid     ();  // donne le ThreadId au sens OMP
    INLINE int   RedOrange       ();  // debut de macrozone de calculs
    INLINE int   ReturnToRed     ();  // fin   de macrozone de calculs
    INLINE void  NormalPriority  ();  // pas de changement de priorite
    INLINE void  BetterPriority  ();  // par defaut
    INLINE void  ResetMaxThreads ();  // remise de _NbThreads a _MaxThreads
    INLINE void  SetLogThreads   ( silla iLogThreads );
                                      // reduit localement les threads dispo
    // definition d' un algo par sa methode iStobAlgo et par son
    // environnement iContexte ( lot des variables passees de l'
    // exterieur vers l' interieur de la boucle parallelisee )

           void  SetStobAlgo     ( CATBaseComputation *iContexte,
                                   CATThreadRun iStobAlgo );
           void  Cleaner         ();  // reserve aux codes sales

    // distributeurs de taches paralleles EQUILIBREES, dans master
    //   iNbIters = nombre d' iters de la boucle 'for' a paralleliser
    //              iters sur [0, iNbIters[

    silla        OwordDispatcher  ( silla iNbIters );
    silla        QwordDispatcher  ( silla iNbIters );
    silla        DwordDispatcher  ( silla iNbIters );
    silla        WordDispatcher   ( silla iNbIters );
    silla        ByteDispatcher   ( silla iNbIters );

    // distributeur de taches paralleles garantissant
    // la non-interference entre lignes de cache de la zone d' ecriture
    //   iNbIters = nombre d' iters de la boucle 'for' a paralleliser
    //              iters sur [0, iNbIters[
    //   iArea    = zone d' ecriture des calculs
    //   iStride  = nombre d' octets entre debuts de zones ecrites
    //              par 2 iters consecutives
    //   iVide    = nombre d' octets non ecrits a la fin d' un stride
    //
    // Exemple: iStride=40, iVide=16
    //          iArea est une matrice double precision ecrite par
    //          colonnes, chaque colonne contenant 5 doubles, mais
    //          seuls les 3 premiers de chaque colonne sont utiles
    //          iNbIters est le nombre de colonnes

    silla        CacheDispatcher  ( silla iNbIters, double *iArea,
                                    silla iStride,  silla iVide );

    // Launcher    pour Astob
    // VarLauncher pour Vastob
    // Barrier     pour Astob et Vastob
    // lanceur Launcher de tache ASYNCHRONE en parallele, dans master
    // attente de synchronisation par Barrier
    //   son oubli est catastrophique
    // ( iNbIters appels a Launcher + 1 appel a Barrier
    //   equivalent a 1 SetStobAlgo + 1 Dispatcher )
    // ( moins performant )

    silla        Launcher         ( CATBaseComputation *iContexte,
                                    ulla iSizeof,
                                    CATThreadAstob iAstobAlgo );
    silla        VarLauncher      ( CATBaseComputation *iContexte,
                                    ulla iSizeof,
                                    CATThreadAstob iAstobAlgo );
    void         Barrier          ();

    static CATMathPoolThread* Get (); // donne @ du pool de threads
    static FILE* GetSortie        (); // fichier a vocation fprintf
    static void  SetSortie        ( FILE *Sortie );

  protected:
    // main de chaque thread esclave de calcul

    friend DWORD CATMathThreadStart  ( void *iPThread );

    // main du thread dormeur, prepose au reveil/sommeil des esclaves

    friend DWORD CATMathDormeurStart ( void *iPThread );
    friend       CATMathPoolMT;
    void         Init          (); // init des threads
    void         Etalon        (); // etalonnage des cores
    void         RougeOrange   (); // debut de macrozone de calculs
    void         RetourAuRouge (); // fin   de macrozone de calculs
    INLINE void  ListInit      ();                  // pour (V)Astob
    INLINE void  Rajout        ( CATBaseComputation *iContexte, ulla iSizeof );
                                                    // pour (V)Astob
    INLINE void  Menage        ( ulla iNbCores );   // pour (V)Astob
    void         (*_Delete)    ( void* &iData );    // service de liberation
                                                    // de _PData
    static   FILE  *_Sortie;       // fichier de sortie
    CATMathThreadP *_PThread;      // les threads geres
    void           *_PData;        // vers gestion de memoire, throws,...

    static   silla  _MaxThreads;   // nb cores * nb processeurs
    static   silla  _Clusters;     // nb clusters
    static   silla  _PhysiPacks;   // nb physical packages
    static   silla  _Cores;        // nb cores
    static   silla  _LogiProcs;    // nb processeurs logiques
    static   silla  _IsHyperThread;// presence d' hyperthreading
    static   silla  _IsContiguous; // _ApicId contigus
    static   silla  _LogMax;       // log binaire de _MaxThreads
    static   silla  _IsMaxPowerOf2;// nb cores == puissance de 2

             silla  _NbThreads;    // utilise pour zone parallele
             silla  _LogThreads;   // log binaire de _NbThreads
             silla  _IsPowerOf2;   // nb threads == puissance de 2

             silla  _IsParallel;   // indique si zone parallele en cours
             silla  _IsMemoryApi;  // gestion de memoire et throws activee
             ulla   _Frequency;    // (ticks de puce par seconde) >> 10
             ulla   _CommutRead;   // nb de cycles par commutation en lecture
             ulla   _CommutWrite;  // nb de cycles par commutation en ecriture
             ulla   _Void;         // pour double pesee sur commutation
             ulla   _Priority;     // delta sur priorite du process pere

    // 1 liste _Busy doublement chainee (esclaves) + 1 pile _Free pour Astob

             ulla   _Busy[0x40][2];// (2**P-1) cores actifs en (Next, Prec)
                                   // first et last en _Busy[0]
             ulla   _Free[0x40];   // pile de (2**P-1) cores libres
                                   // taille de pile en _Free[0]
             char  *_Alloc;        // pour Astob, mais pas pour Vastob
             ulla   _SizeAlloc;    // pour Astob, mais pas pour Vastob

             int    _Avant0[0x20]; // memoire jamais accedee (128 octets)
    //_______________________________________________________________________
    // 3 entites _SynchroLevel, _StobAlgo, _AstobAlgo contigues,
    // dans cet ordre pour SpinSuisse (3*4/3*8 octets selon 32/64 bits)
    // _SynchroLevel indique si zone Stob, Astob ou Vastob en cours
    // 2 pointeurs de fonction membre:
    //   _StobAlgo  pour Stob         synchrone
    //   _AstobAlgo pour Astob/Vastob asynchrone

    volatile silla  _SynchroLevel;
    volatile CATThreadRun   _StobAlgo;
    volatile CATThreadAstob _AstobAlgo;
    //_______________________________________________________________________
    // _Contexte[Tid] = variables shared de la zone parallele
    // seul _Contexte[0] est utilise en cas de Stob
    // si Astob, les _Contexte pointent dans une zone unique geree par _Alloc
    // si Vastob, chaque _Contexte[Tid] est gere par un malloc/realloc

    volatile CATBaseComputation* volatile _Contexte[0x40];
    volatile ulla   _ThreadCase;   // pour etalonnage initial
             int    _Avant1[0x20]; // memoire jamais accedee (128 octets)
    volatile silla  _Already;      // niveau cumulatif de RougeOrange
             int    _Avant2[0x20]; // memoire jamais accedee (128 octets)
    volatile char   _RelaisSem[0x40][0x80]; // _Relais et _AttendFin
    volatile char   _CalculSem [0x40];      // 4 semaphores pour Dormeur,
    volatile char   _DormeurSem[0x40];      // chacun dans 64 octets alignes
    volatile char   _SpinSem   [0x40];
    volatile char   _RetourSem [0x40];
    volatile silla  _Laps;         // date de fin de laps de LAPS ms
             int    _Apres[0x20];  // memoire jamais accedee (128 octets)
    static   char   _Sequence[4 + 0x10 + 0x100][0x0A];
  };                               // pour CacheDispatcher
//___________________________________________________________________________
#include "CATMathThreadP.h"

INLINE int   CATMathPoolThread::GetMaxThreads ()
  { return (int) _MaxThreads; }

INLINE int   CATMathPoolThread::GetNbThreads ()
  { return (int) _NbThreads; }

INLINE silla CATMathPoolThread::GetLogThreads ()
  { return _LogThreads; }

INLINE int   CATMathPoolThread::GetCommutRead ()
  { return (int) _CommutRead; }

INLINE int   CATMathPoolThread::GetCommutWrite ()
  { return (int) _CommutWrite; }

INLINE int   CATMathPoolThread::GetVoid ()
  { return (int) _Void; }

INLINE volatile ulla* CATMathPoolThread::GetPThreadCase ()
  { return &_ThreadCase; }

INLINE int   CATMathPoolThread::IsInParallel ()
  {                                // attention aux API inconnus...
  if ( _NbThreads <= 1 )   return 1;
  return GetCurrentThreadId () != _PThread[0].GetThreadId () ||
         _IsParallel || omp_in_parallel ();
  }

INLINE void  CATMathPoolThread::NormalPriority ()
  {
  _Priority = 0;
  for ( silla Tid=_MaxThreads; Tid>=0; Tid-- )
    SetThreadPriority
      ( _PThread[Tid]._HThread, _PThread[Tid]._NormalPriority );
  }

INLINE void  CATMathPoolThread::BetterPriority ()
  {
  _Priority = 1;
  for ( silla Tid=_MaxThreads; Tid>=0; Tid-- )
    SetThreadPriority
      ( _PThread[Tid]._HThread, _PThread[Tid]._BetterPriority );
  }

INLINE void  CATMathPoolThread::ResetMaxThreads ()
  {
  _NbThreads  = _MaxThreads;
  _LogThreads = _LogMax;
  _IsPowerOf2 = _IsMaxPowerOf2;
  }

INLINE void  CATMathPoolThread::SetLogThreads ( silla iLogThreads )
  {
  if ( iLogThreads < _LogMax )
    {
    _NbThreads  = silla(1) << iLogThreads;
    _LogThreads = iLogThreads;
    _IsPowerOf2 = 1;
    }
  else
    ResetMaxThreads ();
  }
//___________________________________________________________________________
// retrouve le Tid du thread courant
// le jour ou _NbThreads sera grand, envisager dans le ct une table triee
//   selon _ThreadId de tous les couples (_ThreadId, _Tid), de sorte que
//   RetrieveTid n' ait plus qu' a faire un search dichotomique pour y
//   positionner CurThread (evitera le scan de tous les _ThreadId...)

INLINE int CATMathPoolThread::RetrieveTid ()
  {
  int Tid = omp_get_thread_num ();
  if ( Tid )   return Tid;         // Open MP a parallelise
  if ( _NbThreads <= 1 )   return 0;
                                   // Stob a parallelise
  DWORD CurThread = GetCurrentThreadId ();
  for ( Tid=int(_MaxThreads)-1; Tid>0; Tid-- )
    if ( _PThread[Tid].GetThreadId () == CurThread )   return Tid;
  return 0;                        // peut-etre API inconnu...
  }
//___________________________________________________________________________
// debut de macrozone de calculs
// a ne pas appeler si IsInParallel: pas de nesting
//   donc si IsInParallel, passer en mode mono-thread-safe

INLINE int CATMathPoolThread::RedOrange ()
  {
#ifndef _NO_WFSO
  //*** if ( IsInParallel () )   return -1;

  if ( CATTestDateAndInc ( &_Already, 0, _Laps )   &&   _NbThreads > 1 )
    RougeOrange ();                // reveille Dormeur
#endif                             // _NO_WFSO
  return 0;
  }
//___________________________________________________________________________
// fin de macrozone de calculs
// a ne pas appeler si IsInParallel

INLINE int CATMathPoolThread::ReturnToRed ()
  {
  int Code;
#ifndef _NO_WFSO
  //*** if ( IsInParallel () )   return -1;

  Code = CATTestDateAndDec ( &_Already, 0, _Laps );
  if ( Code > 0   &&   _NbThreads > 1 )
    RetourAuRouge ();              // partie non inline
#else
  Code = 0;
#endif                             // _NO_WFSO
  return Code;
  }
//___________________________________________________________________________
// init de liste double _Busy + pile _Free

INLINE void CATMathPoolThread::ListInit ()
  {
  _Busy[0][0] = 0;                 // NULL = 0
  _Busy[0][1] = 0;
  _Free[0] = _MaxThreads - 1;      // _MaxThreads = 4, par exemple
  for ( ulla Idx=_Free[0]; Idx>0; Idx-- )
    _Free[Idx] = Idx;
  }
//___________________________________________________________________________
// rajout d' un core actif dans liste double _Busy
// gel de l' etat de this au moment de l' appel a Launcher/VarLauncher
// par memcpy

INLINE void CATMathPoolThread::Rajout
  ( CATBaseComputation *iContexte, ulla iSizeof )
  {
  ulla Tid, First, Last;

  Tid = _Free[_Free[0]--];         // depile
  if ( _SynchroLevel == VASTOB )
    _Contexte[Tid] = (CATBaseComputation*) _PThread[Tid].Reserve ( iSizeof );
  memcpy ( (void*) _Contexte[Tid], iContexte, iSizeof );
  _RelaisSem[Tid][0] = 2;          // lancement AstobAlgo ( Tid );
                                   // limites d' iters sans objet, donc = 0
  First = _Busy[0][0];
  Last  = _Busy[0][1];
  _Busy[Last][0] = Tid;
  _Busy[0][1]    = Tid;
  _Busy[Tid][0]  = 0;
  _Busy[Tid][1]  = Last;
  }
//___________________________________________________________________________
// menage partiel dans liste double _Busy: libere iNbCores maximum
// scan privilegie les + vieux actifs

INLINE void CATMathPoolThread::Menage ( ulla iNbCores )
  {
  ulla Fini = 0, Next, Prec;

  while ( (Fini = _Busy[Fini][0])   &&   iNbCores )
    if ( !(_RelaisSem[Fini][0] & 2) )
      {                            // a fini
      _Free[++_Free[0]] = Fini;    // empile
      iNbCores--;
      Next = _Busy[Fini][0];       // supprime Fini
      Prec = _Busy[Fini][1];
      _Busy[Prec][0] = Next;
      _Busy[Next][1] = Prec;
      }
  }
//___________________________________________________________________________
#else                              // UNIX, Linux, Windows ancien
                                   //   = monothread (multi non implemente)
#include "stdio.h"
#include "CATMathematics.h"
#include "CATMathInline.h"
#include "CATArithTypes.h"
#include "CATBaseComputation.h"

class ExportedByCATMathematics CATMathPoolThread
  {
  public:
     CATMathPoolThread () : _PData (0), _Delete (0)   {}
    ~CATMathPoolThread () {}
    INLINE int   GetMaxThreads    ();
    INLINE int   GetNbThreads     ();
    INLINE silla GetLogThreads    ();
    INLINE int   IsInParallel     ();
    INLINE int   RetrieveTid      ();
    INLINE int   RedOrange        ();
    INLINE int   ReturnToRed      ();
           void  NormalPriority   () {}
           void  BetterPriority   () {}
           void  ResetMaxThreads  () {}
           void  SetLogThreads    ( silla iLogThreads ) {}
    INLINE void  SetStobAlgo      ( CATBaseComputation *iContexte,
                                    CATThreadRun iStobAlgo );
    INLINE silla OwordDispatcher  ( silla iNbIters );
    INLINE silla QwordDispatcher  ( silla iNbIters );
    INLINE silla DwordDispatcher  ( silla iNbIters );
    INLINE silla WordDispatcher   ( silla iNbIters );
    INLINE silla ByteDispatcher   ( silla iNbIters );
    INLINE silla CacheDispatcher  ( silla iNbIters, double *iArea,
                                    silla iStride,  silla iVide );
    INLINE silla Launcher         ( CATBaseComputation *iContexte,
                                    ulla iSizeof,
                                    CATThreadAstob iAstobAlgo );
    INLINE silla VarLauncher      ( CATBaseComputation *iContexte,
                                    ulla iSizeof,
                                    CATThreadAstob iAstobAlgo );
    INLINE void  Barrier          ();
    INLINE void  SetSortie        ( FILE *Sortie );
    static CATMathPoolThread* Get (); // donne @ du pool de threads

  protected:
    friend class        CATMathPoolMT;
    void              (*_Delete) ( void*& iData );
    void               *_PData;
    CATThreadRun        _StobAlgo;
    CATBaseComputation *_Contexte;
    FILE               *_Sortie;
  };

INLINE int CATMathPoolThread::GetMaxThreads ()
  { return 1; }

INLINE int CATMathPoolThread::GetNbThreads ()
  { return 1; }

INLINE silla CATMathPoolThread::GetLogThreads ()
  { return 0; }

INLINE int CATMathPoolThread::IsInParallel ()
  { return 1; }

INLINE int CATMathPoolThread::RetrieveTid ()
  { return 0; }

INLINE int CATMathPoolThread::RedOrange ()
  { return 0; }

INLINE int CATMathPoolThread::ReturnToRed ()
  { return 0; }

INLINE void CATMathPoolThread::SetStobAlgo
  ( CATBaseComputation *iContexte, CATThreadRun iStobAlgo )
  {
  _Contexte = iContexte;
  _StobAlgo = iStobAlgo;
  }

INLINE silla CATMathPoolThread::OwordDispatcher ( silla iNbIters )
  {
  ( (CATBaseComputation*)_Contexte->*((CATThreadRun)_StobAlgo) )
    ( 0, 0, iNbIters );
  return 1;
  }

INLINE silla CATMathPoolThread::QwordDispatcher ( silla iNbIters )
  {
  ( (CATBaseComputation*)_Contexte->*((CATThreadRun)_StobAlgo) )
    ( 0, 0, iNbIters );
  return 1;
  }

INLINE silla CATMathPoolThread::DwordDispatcher ( silla iNbIters )
  {
  ( (CATBaseComputation*)_Contexte->*((CATThreadRun)_StobAlgo) )
    ( 0, 0, iNbIters );
  return 1;
  }

INLINE silla CATMathPoolThread::WordDispatcher  ( silla iNbIters )
  {
  ( (CATBaseComputation*)_Contexte->*((CATThreadRun)_StobAlgo) )
    ( 0, 0, iNbIters );
  return 1;
  }

INLINE silla CATMathPoolThread::ByteDispatcher  ( silla iNbIters )
  {
  ( (CATBaseComputation*)_Contexte->*((CATThreadRun)_StobAlgo) )
    ( 0, 0, iNbIters );
  return 1;
  }

INLINE silla CATMathPoolThread::CacheDispatcher
  ( silla iNbIters, double *iArea, silla iStride, silla iVide )
  {
  ( (CATBaseComputation*)_Contexte->*((CATThreadRun)_StobAlgo) )
    ( 0, 0, iNbIters );
  return 1;
  }

INLINE silla CATMathPoolThread::Launcher
  ( CATBaseComputation *iContexte, ulla iSizeof, CATThreadAstob iAstobAlgo )
  {
  ( (CATBaseComputation*)iContexte->*((CATThreadAstob)iAstobAlgo) ) ( 0 );
  return 1;
  }

INLINE silla CATMathPoolThread::VarLauncher
  ( CATBaseComputation *iContexte, ulla iSizeof, CATThreadAstob iAstobAlgo )
  {
  ( (CATBaseComputation*)iContexte->*((CATThreadAstob)iAstobAlgo) ) ( 0 );
  return 1;
  }

INLINE void CATMathPoolThread::Barrier () {}

INLINE void CATMathPoolThread::SetSortie ( FILE *iSortie )
  { _Sortie = iSortie; }
#endif                             // _MSC_VER>=1400
//___________________________________________________________________________
#endif                             // CATMathPoolThread_h
