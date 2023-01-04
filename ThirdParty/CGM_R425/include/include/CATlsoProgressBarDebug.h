/* -*-C++-*- */

#ifndef CATlsoProgressBarDebug_H
#define CATlsoProgressBarDebug_H

/*  
=============================================================================

RESPONSABLE  : ZUT

DESCRIPTION  : A utility class to help for progress bars debugging

Debug is piloted by environment variables :

set CATlsoProgressBar_Debug=1 : Activates ProgressBars debug
set CATlsoProgressBar_ActivateTraces=1 : Activates traces
set CATlsoProgressBar_TraceOutputPath=E:\tmp\ProgressBarManager_traces.txt,2 :
  Indicates the path to a debug output file for traces.
  If none, traces will be displayed in the default output stream
set CATlsoProgressBar_ForceProgressBarCreation=1 : A progress bar will be created if absent
set CATlsoProgressBar_ForceInterruptId=312,2 : Indicates an interrupt Id and its iteration number for which interruption will be forced
set CATlsoProgressBar_FilteredIds=39001,37201 : Indicates a list of interrupt ids that will not be displayed in traces
set CATlsoProgressBar_KeptIds=39001,37201 : Indicates the list of interrupt ids that will be displayed in traces
set CATlsoProgressBar_ForceInterruptCPUTime=1000 : Indicates a timeout (in milliseconds) for which interruption will be forced

CREATION     : 02 September 2009 by ZUT

=============================================================================
*/

// ++++ Includes ++++
#include "CATCGMVirtual.h"
#include "PersistentCell.h"
#include "CATBoolean.h"
#include "ListVOfLong.h"
#include "CATDataType.h"
#include "CATUnicodeString.h"
#include "CATLib.h"
#include "CATMathInline.h"

#ifndef MaxCPUTime
#define MaxCPUTime 0xffffffffu
#endif

class CATCGMOutput;

class ExportedByPersistentCell CATlsoProgressBarDebug : public CATCGMVirtual
{

public:

  //---------------------------------------------------------------------------
  // CONSTRUCTOR(S) / DESTRUCTORS
  //---------------------------------------------------------------------------

  CATCGMNewClassArrayDeclare;

  //---------------------------------------------------------------------------
  // METHODS
  //---------------------------------------------------------------------------
  
  static CATlsoProgressBarDebug & GetInstance();
  
  static void Kill();

  CATCGMOutput & GetOutput();

  void Inform( CATLONG32 iPassedProgressId, const char * iFileName = NULL );

  CATBoolean IsInterruptIdFiltered( CATLONG32 iInterruptId ) const;

  // Fonction d'interruption pilotable
  // _ForceInterruptCPUTime : Temps CPU correspondant a une simulation de demande d'interruption
  // _ForceInterrupt : Force l'interruption au prochain appel de la fonction d'interruption
  static CATBoolean InterruptFunction( int iProgressValue, int iProgressRange );

  void SetOutputFileName( const char * iFileName, unsigned int iFileOpenMode = 0 );

  void DumpProgressSteps( CATCGMOutput* oOStream ) const;
  void DumpElapsedTimes( CATCGMOutput* oOStream ) const;
  void DumpSourceFiles( CATCGMOutput* oOStream ) const;

  //---------------------------------------------------------------------------
  // INLINE METHODS
  //---------------------------------------------------------------------------
  
  static CATBoolean GetDebugMode();
  CATBoolean GetForceProgressBarCreation() const;
  CATBoolean GetActivateTraces() const;
  CATBoolean GetForceInterruptFctCall() const;
  CATLONG32  GetForceInterruptId() const;
  CATLONG32  GetForceInterruptIdNumPass() const;
  CATBoolean GetForceInterrupt() const;
  CATULONG32 GetForceInterruptCPUTime()const;
  CATTimerId GetTimer() const;
  CATBoolean GetInterruptionRequested() const;
  CATULONG32 GetCPUDetectionTime() const;
  
  void SetForceProgressBarCreation( CATBoolean iForceProgressBarCreation );
  void SetActivateTraces( CATBoolean iActivateTraces );
  void SetForceInterruptFctCall( CATBoolean iForceInterruptFctCall );
  void SetForceInterruptId( CATLONG32 iForceInterruptId, CATLONG32 iNumPass = 1 );
  void SetForceInterrupt( CATBoolean iForceInterrupt);
  void SetForceInterruptCPUTime( CATULONG32 iForceInterruptCPUTime );
  void SetTimer( const CATTimerId iTimerId );
  void SetInterruptionRequested( CATBoolean iInterruptionRequested, CATULONG32 iCPUDetectionTime = MaxCPUTime );

  void AppendIdToFilter( CATLONG32 iInterruptId );

private:

  struct ProgressStep
  {
    CATLONG32  _ProgressId;
    CATULONG32 _CPUTime;
    CATULONG32 _Elapsed;
    CATULONG32 _SourceFileIndex;

    ProgressStep( CATLONG32 iProgressId, CATULONG32 iCPUTime, CATULONG32 iElapsed, CATULONG32 iSourceFileIndex )
    : _ProgressId(iProgressId)
    , _CPUTime(iCPUTime)
    , _Elapsed(iElapsed)
    , _SourceFileIndex(iSourceFileIndex)
    {}
  };

  struct SourceFile
  {
    CATLONG32        _FileId;
    CATUnicodeString _FileName;

    SourceFile( CATLONG32 iFileId, const char * iFileName )
    : _FileId(iFileId)
    , _FileName("Unknown")
    {
      if ( ( iFileId >= 0 ) && iFileName )
        _FileName = CATUnicodeString(iFileName);
    }
  };

  //---------------------------------------------------------------------------
  // PRIVATE METHODS
  //---------------------------------------------------------------------------
  
  CATULONG32 AddProgressStep( CATLONG32 iProgressId, CATULONG32 iCPUTime, CATULONG32 iElapsed, const char * iFileName = NULL );
  CATULONG32 AddSourceFile( CATLONG32 iFileId, const char * iFileName );

  //---------------------------------------------------------------------------
  // MEMBER DATA
  //---------------------------------------------------------------------------
  static CATlsoProgressBarDebug * _Instance;
  static CATBoolean               _DebugMode;
  
  CATBoolean             _ForceProgressBarCreation; // Forcer la creation d'une progress bar si _ProgressBar == NULL
  CATBoolean             _ActivateTraces;           // Activation des traces
  CATBoolean             _ForceInterruptFctCall;    // Forcer l'appel a la fonction d'interruption
  CATLONG32              _ForceInterruptId;         // ProgressId pour lequel on force l'interruption
  CATLONG32              _ForceInterruptIdNumPass;  // Iteration(ProgressId) pour laquelle s'arreter
  CATLONG32              _InterruptIdCurPass;
  CATListOfLong          _ListOfFilteredIds;        // Liste d'Ids a filtrer dans les traces
  CATListOfLong          _ListOfKeptIds;            // Liste d'Ids a afficher dans les traces
  CATBoolean             _ForceInterrupt;           // Forcer l'interruption
  CATULONG32             _ForceInterruptCPUTime;    // Temps CPU correspondant a une simulation de demande d'interruption
  
  CATBoolean             _InterruptionRequested;
  CATULONG32             _CPUDetectionTime;

  CATCGMOutput         * _Output;
  CATUnicodeString     * _OutputFileName;
  unsigned int           _FileOpenMode;
  CATTimerId             _TimerId;

  ProgressStep        ** _ProgressSteps;
  CATULONG32             _ProgressStepsSize;
  CATULONG32             _NbProgressSteps;
  
  SourceFile          ** _SourceFiles;
  CATULONG32             _SourceFilesSize;
  CATULONG32             _NbSourceFiles;

  CATlsoProgressBarDebug();
  ~CATlsoProgressBarDebug();
};

//-----------------------------------------------------------------------------
// INLINE METHODS IMPLEMENTATION
//-----------------------------------------------------------------------------

INLINE CATBoolean CATlsoProgressBarDebug::GetDebugMode() {
  return _DebugMode; }

INLINE CATBoolean CATlsoProgressBarDebug::GetForceProgressBarCreation() const {
  return _ForceProgressBarCreation; }

INLINE void CATlsoProgressBarDebug::SetForceProgressBarCreation( CATBoolean iForceProgressBarCreation ) {
  _ForceProgressBarCreation = iForceProgressBarCreation; }
  
INLINE CATBoolean CATlsoProgressBarDebug::GetActivateTraces() const {
  return _ActivateTraces; }

INLINE void CATlsoProgressBarDebug::SetActivateTraces( CATBoolean iActivateTraces ) {
  _ActivateTraces = iActivateTraces; }
  
INLINE CATBoolean CATlsoProgressBarDebug::GetForceInterruptFctCall() const {
  return _ForceInterruptFctCall; }

INLINE void CATlsoProgressBarDebug::SetForceInterruptFctCall( CATBoolean iForceInterruptFctCall ) {
  _ForceInterruptFctCall = iForceInterruptFctCall; }

INLINE CATLONG32 CATlsoProgressBarDebug::GetForceInterruptId() const {
  return _ForceInterruptId; }

INLINE void CATlsoProgressBarDebug::SetForceInterruptId( CATLONG32 iForceInterruptId, CATLONG32 iNumPass ) {
  _ForceInterruptId        = iForceInterruptId;
  _ForceInterruptIdNumPass = iNumPass; }

INLINE CATLONG32 CATlsoProgressBarDebug::GetForceInterruptIdNumPass() const {
  return _ForceInterruptIdNumPass; }
  
INLINE CATBoolean CATlsoProgressBarDebug::GetForceInterrupt() const {
  return _ForceInterrupt; }

INLINE void CATlsoProgressBarDebug::SetForceInterrupt( CATBoolean iForceInterrupt ) {
  _ForceInterrupt = iForceInterrupt; }
  
INLINE CATULONG32 CATlsoProgressBarDebug::GetForceInterruptCPUTime() const {
  return _ForceInterruptCPUTime; }

INLINE void CATlsoProgressBarDebug::SetForceInterruptCPUTime( CATULONG32 iForceInterruptCPUTime ) {
  _ForceInterruptCPUTime = iForceInterruptCPUTime; }

INLINE CATTimerId CATlsoProgressBarDebug::GetTimer() const {
  return _TimerId; }

INLINE void CATlsoProgressBarDebug::SetTimer( const CATTimerId iTimerId ) {
  _TimerId = iTimerId; }

INLINE CATBoolean CATlsoProgressBarDebug::GetInterruptionRequested() const {
  return _InterruptionRequested; }

INLINE void CATlsoProgressBarDebug::SetInterruptionRequested( CATBoolean iInterruptionRequested, CATULONG32 iCPUDetectionTime ) {
  _InterruptionRequested = iInterruptionRequested;
  _CPUDetectionTime = iCPUDetectionTime; }

INLINE CATULONG32 CATlsoProgressBarDebug::GetCPUDetectionTime() const {
  return _CPUDetectionTime; }

INLINE void CATlsoProgressBarDebug::AppendIdToFilter( CATLONG32 iInterruptId ) {
  _ListOfFilteredIds.Append(iInterruptId); }


#endif /* CATlsoProgressBarDebug_H */
