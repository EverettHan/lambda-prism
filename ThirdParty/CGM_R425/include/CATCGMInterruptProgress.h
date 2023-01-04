#ifndef CATCGMInterruptProgress_H
#define CATCGMInterruptProgress_H
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2011
//==========================================================================
/*
   Stochastic counter of interrupt integrated with reproductible management
     (stochastic : operators' delivery may change the history of points of interruption)

   According to kernel capture of point of interruption, here comes an associated procedural integration :

     automatic management

        X) reset is done at the beginning of first level of operator->RunOperator()
           (counter set to zero and history unset) 

        X) counter is incremented done a each event (CATCGMProgressBar->SetProgress)
        X) if an interruption occurs and if history is unset, history is set to counter  

     integration of RunOperator 

        X) after run,  save the counter and history of interruption  

      integration of PlayBack/CGMReplay

         MANDATORY prerequisite define an Interrupt transaction 
              (see GMModelInterfaces\ProtectedInterfaces\CATCGMOperatorRunTransaction.h )
 
         during a replay reload
             transfert History as Trigger on CATExtGeoOperator * extensible
             (both integration CATPlayBack and Reload of a Replay with referentiel) 
 
         during a monitored operation,
 
          Before the begin of operation 
             X) generate if necessary the CATCGMProgressBar
             X) activate the trigger
          After
             X) reset the trigger 
              
         under each event (CATCGMProgressBar->SetProgress)
             X) if trigger is activated and if counter reach the trigger then interrupt is thrown

 //==========================================================================

 Sample of Integration for CLS  Replay (And customised CATlsoProgressBarDebug )

 CATPlayBack -> needing a customised executable (TopologicalOperators.tst\CATPlayBackCLS.m)

  Recover Data on 
      set PlayBack_zip=1
      mkodt -s TestLiveTransformFaceInterrupt.sh

 CACGMReplay -> needing a customised executable (TopologicalOperators.tst\CATCGMReplayCLS.m)

   By specification, only available when referential of output is saved 
   Recover Data on 
      set CATCGMReplay=2,FirstLevel,Home=E:\WS\modeltcx\TopologicalOperators.tst\FunctionTests\Output\win_b64
      mkodt -s TestLiveTransformFaceInterrupt.sh






*/
//==========================================================================
#include "ExportedByCATTechTools.h"
#include "CATMathInline.h"
#include "CATDataType.h"
#include "CATechMeta.h"
#include "CATCGMHashDico.h"
#include "CATBoolean.h"
 
class CATUnicodeString;
class CATCGMOperator;
class CATCGMOutput;


class ExportedByCATTechTools CATCGMInterruptProgress 
{
public :

  /** 
  *  Singleton management of interruption progress.
  */
  INLINE static CATCGMInterruptProgress & GetSingleton();

  INLINE void                             ResetCounterAndHistory(CATCGMOperator *iContext);

  /** 
  *  Counter : interruption checkpoint.
  */
  INLINE CATLONG32  IncrementCounter(const char *  iStaticConstLabel);
  INLINE CATLONG32  GetCounter(const char * & oStaticConstLabel);

  /** 
  *  History : interruption detected.
  */
  INLINE void       SetHistory(CATLONG32 iHistory, const char *  iStaticConstLabel);
  INLINE CATLONG32  GetHistory(const char * & oStaticConstLabel);

  /** 
  *  Trigger : simulation of interruption thrown.
  */
  INLINE void       ActivateTrigger(CATLONG32 iTrigger, const char *  iStaticConstLabel, CATBoolean ToDeleteConstLabel);
  INLINE CATLONG32  GetTrigger(const char *  iStaticConstLabel);
  INLINE void       ResetTrigger(const short iWithCopy = 0);



   /** 
  *  PlayBack integration.
  */
  INLINE static const CATechMeta &  Interrupt_Counter();
  INLINE static const CATechMeta &  Interrupt_History();
  INLINE static const CATechMeta &  Interrupt_HistoryLabel();
 

   void DumpOutput(CATCGMOperator *iContext, CATCGMOutput& os);


protected :

  CATCGMInterruptProgress() ;
  ~CATCGMInterruptProgress() ;


private :

  //------------------------------------------------------------------------
  // Forbidden (Declared, Not Defined) : Constructor by copy  et   operator =
  //------------------------------------------------------------------------
  CATCGMInterruptProgress(const CATCGMInterruptProgress &iCopy);
  CATCGMInterruptProgress& operator=(const CATCGMInterruptProgress &iCopy);

  CATLONG32       _Counter;
  CATCGMHashDico * _CounterLabel;
  const char    * _CounterStaticConstLabel;

  CATLONG32      _History;
  const char  *  _HistoryStaticConstLabel;

  CATLONG32     _Trigger;
  const char *  _TriggerStaticConstLabel;
  CATBoolean    _TriggerToDeleteConstLabel;

  CATLONG32     _CopyTrigger;
  CATBoolean    _CopyTriggerWithLABEL;

  CATBoolean _WithLabel;

  CATCGMOperator  *_Context;

  static CATCGMInterruptProgress  _Singleton;
};

/** 
*  Singleton management of interruption progress.
*/

INLINE  CATCGMInterruptProgress & CATCGMInterruptProgress::GetSingleton()
{ return _Singleton ;}



INLINE  void CATCGMInterruptProgress::ResetCounterAndHistory(CATCGMOperator *iContext)
{ 
  _Counter=0;  
  if ( _CounterLabel ) { _CounterLabel->RemoveAll();  }
  _CounterStaticConstLabel=NULL;  

  _History=0;
  _HistoryStaticConstLabel=NULL;  

  _Context = iContext;
}

 


INLINE  CATLONG32 CATCGMInterruptProgress::IncrementCounter(const char *  iStaticConstLabel)
{ 
  if ( iStaticConstLabel && (iStaticConstLabel[0] != '\0') && _WithLabel )
  {
    if ( ! _CounterLabel ) _CounterLabel = new CATCGMHashDico(32);
    if ( _CounterLabel )
    {
      void* ipAssoc = NULL;
      int   iPos    = _CounterLabel->LocateItem( (void *)iStaticConstLabel,&ipAssoc);
      CATLONG32 count = iPos ? CATPtrToLONG32(ipAssoc) : 0;
      ++count; 
      if ( iPos )
        _CounterLabel->SetAssoc( (void *)iStaticConstLabel, (void *)count);
      else
        _CounterLabel->Insert(iStaticConstLabel, (void *)count);
      _CounterStaticConstLabel=iStaticConstLabel;  
      return count; 
    }
  }
  _CounterStaticConstLabel=NULL;  
  return ++_Counter; 
}

INLINE  CATLONG32 CATCGMInterruptProgress::GetCounter(const char * & oStaticConstLabel)
{ 
  oStaticConstLabel =_CounterStaticConstLabel ;
  return _Counter;
}
 
/** 
*  History : interruption detected.
*/
INLINE  void CATCGMInterruptProgress::SetHistory(CATLONG32 iHistory, const char *  iStaticConstLabel)
{ 
  _History=iHistory; 
  _HistoryStaticConstLabel = iStaticConstLabel;
}
INLINE  CATLONG32 CATCGMInterruptProgress::GetHistory(const char * & oStaticConstLabel)
{
  oStaticConstLabel =_HistoryStaticConstLabel ;
  return _History; 
}


/** 
*  Trigger : simulation of interruption thrown.
*/
void       CATCGMInterruptProgress::ActivateTrigger(CATLONG32 iTrigger, const char *  iStaticConstLabel, CATBoolean ToDeleteConstLabel)
{ 
  _Trigger = iTrigger; 
  _TriggerStaticConstLabel = iStaticConstLabel;
  _TriggerToDeleteConstLabel = ToDeleteConstLabel;
}

CATLONG32  CATCGMInterruptProgress::GetTrigger(const char *  iStaticConstLabel)
{ 
  if ( ! _Trigger )  
    return 0;

  // Identity des valeurs de Const char Label
  if ( iStaticConstLabel && (*iStaticConstLabel != '\0') )
  {
    if ( ! _TriggerStaticConstLabel )
      return 0;

    int idx=0; 
    for ( ;_TriggerStaticConstLabel[idx] && (_TriggerStaticConstLabel[idx] == iStaticConstLabel[idx]); idx++ )
      ;

    if (  _TriggerStaticConstLabel[idx] || iStaticConstLabel[idx] )
      return 0;
  }
  else
  {
    if ( _TriggerStaticConstLabel && (*_TriggerStaticConstLabel != '\0') )
      return 0;
  }

 // Valid
  return _Trigger; 
}

void       CATCGMInterruptProgress::ResetTrigger(const short iWithCopy)
{ 
  if ( iWithCopy )
  {
    _CopyTrigger = _Trigger;
    _CopyTriggerWithLABEL = _TriggerStaticConstLabel ? TRUE :  FALSE;
  }

  _Trigger=0; 
  if ( _TriggerStaticConstLabel )
  { if ( _TriggerToDeleteConstLabel ) { delete [] (char *)_TriggerStaticConstLabel; }  _TriggerStaticConstLabel=0;  }
  _TriggerToDeleteConstLabel = FALSE;


}

/** 
*  CATCGMInterruptProgress : simulation of interruption thrown.
*/
INLINE const CATechMeta & CATCGMInterruptProgress::Interrupt_Counter()  { static const CATechMeta _Dummy("Interrupt_Counter",CATechFormat_Int32); return _Dummy;}
INLINE const CATechMeta & CATCGMInterruptProgress::Interrupt_History()  { static const CATechMeta _Dummy("Interrupt_History",CATechFormat_Int32); return _Dummy;}
INLINE const CATechMeta & CATCGMInterruptProgress::Interrupt_HistoryLabel()  { static const CATechMeta _Dummy("Interrupt_HistoryLabel",CATechFormat_CATUnicode); return _Dummy;}
 

#endif

