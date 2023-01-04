//___________________________________________________________________________
// P REISS   03/07
// CATStobUtilAsm.h
// utilitaires en asm pour CATMathPoolThread
// Contexte = ptr sur ptr volatile sur objet volatile

#include "CATArithTypes.h"
// #include "CATMathematics.h"

extern "C" ExportedByCATMathematics ulla CATCpuSpeed ();
extern "C" ExportedByCATMathematics int  CATTestDateAndInc
  ( volatile silla *Already, silla Bid, volatile silla Laps );
extern "C" ExportedByCATMathematics int  CATTestDateAndDec
  ( volatile silla *Already, silla Bid, volatile silla Laps );
extern "C" void  SpinSuisse
  ( volatile char  *Sem, volatile CATBaseComputation* volatile *Contexte,
    volatile silla *Tid, volatile silla *pSynchroLevel );
extern "C" void  SpinSuisseA
  ( volatile char  *Sem, volatile CATBaseComputation* volatile *Contexte,
    volatile silla *Tid, volatile silla *pSynchroLevel );
extern "C" void  SpinSuisseI
  ( volatile char  *Sem, volatile CATBaseComputation* volatile *Contexte,
    volatile silla *Tid, volatile silla *pSynchroLevel );
extern "C" void  SpinLoop      ( volatile silla *Cnt );
extern "C" void  SpinLoopA     ( volatile silla *Cnt );
extern "C" void  SpinLoopI     ( volatile silla *Cnt );
extern "C" void  SpinWaitSem   ( volatile char  *Sem, silla iBit );
extern "C" void  SpinWaitSemA  ( volatile char  *Sem, silla iBit );
extern "C" void  SpinWaitSemI  ( volatile char  *Sem, silla iBit );
extern "C" void  LibereSem     ( volatile char  *Sem, silla iTid );
extern "C" void  LockSem       ( volatile char  *Sem, silla iTid );
extern "C" void  CriticalAdd   ( volatile silla *Cnt, silla iInc );
extern "C" void  CriticalXchg  ( volatile silla *Cnt, silla iNewValue );
extern "C" void  ClflushMfence ( volatile silla *Cnt );
extern "C" void  UpdateStop    ( volatile silla *Laps, ulla Frequency );
extern "C" silla GetDate       ();

extern "C" unsigned long EtalonStartA       ( volatile ulla *iCase );
extern "C" unsigned long EtalonStartI       ( volatile ulla *iCase );
extern "C" unsigned long EtalonCalculStartA ( volatile ulla *iCase );
extern "C" unsigned long EtalonCalculStartI ( volatile ulla *iCase );
extern "C" unsigned int  EtalonVectorielLoopA       ();
extern "C" unsigned int  EtalonVectorielLoopI       ();
extern "C" unsigned int  EtalonVectorielCalculLoopA ();
extern "C" unsigned int  EtalonVectorielCalculLoopI ();
extern "C" unsigned int  EtalonScalaireLoop         ();
extern "C" unsigned int  EtalonScalaireCalculLoop   ();
extern "C" void          CATThreadEtalon            ();
//___________________________________________________________________________
