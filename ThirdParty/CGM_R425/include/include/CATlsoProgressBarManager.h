/* -*-C++-*- */

#ifndef CATlsoProgressBarManager_H
#define CATlsoProgressBarManager_H

/*  
=============================================================================

RESPONSABLE  : ZUT

DESCRIPTION  : A progress bar manager for topological operators

CREATION     : 31 july 2009 by ZUT

=============================================================================
*/

// ++++ Includes ++++
#include "ListPOfCATCGMProgressBar.h"
#include "CATBoolean.h"
#include "CATString.h"
#include "PersistentCell.h"
#include "CATCGMVirtual.h"
#include "CATLib.h"
#include "CATMathInline.h"

class CATCGMProgressBar;
class CATSoftwareConfiguration;
class CATTopOperator;

class ExportedByPersistentCell CATlsoProgressBarManager :  public  CATCGMVirtual 
{

public:

  //---------------------------------------------------------------------------
  // CONSTRUCTOR(S) / DESTRUCTORS
  //---------------------------------------------------------------------------

  CATCGMNewClassArrayDeclare;

  CATlsoProgressBarManager ( CATTopOperator           * iTopOpe ); // New method (LAP) :  You don't have to call SetProgressBar(...)
  CATlsoProgressBarManager ( CATSoftwareConfiguration * iConfig ); // Old Methode

  ~CATlsoProgressBarManager ();

  //---------------------------------------------------------------------------
  // METHODS
  //---------------------------------------------------------------------------

  /*  
  * Sets the Parent ProgressBar.
  * @param   iProgressBar  The parent ProgressBar
  * @param   iOperatorName The name of the running topological operator (for debug)
  */
  void SetProgressBar ( CATCGMProgressBar * iProgressBar, const CATString * iOperatorName = NULL );

  /*  
  * Sets the progress.
  * @param   iValue      The value currently reached (between 0 and iTotalValue if iTotalValue>0.)  
  * @param   iTotalValue The value that is reached when 100% progress is achieved.  
  * @param   iThrowIfInterrupted Indicates if an error "MathInteruptedOperator_ERR_110" has to be raised in case of interruption
  * @param   iProgressID (Debug) A unique ID for the current SetProgress call
  * @param   iFileName   (Debug) The name of the source file where SetProgress was called
  * @return  A boolean to specify whether computation should continue (TRUE) or stop (FALSE).
  *  
  * Important notes : 
  * - If iValue=0 and iTotal value=0, interrupt function is called to check if "stop" is requested.
  * - If iValue is outside progress range, the real progress value won't change.
  * - An internal test avoid any progress back if iValue is lesser than current progress value.
  */
  CATBoolean SetProgress ( const double       iValue,
                           const double       iTotalValue = 100.0,
                           const CATBoolean   iThrowIfInterrupted = FALSE,
                           const CATLONG32    iProgressID = -1,
                           const char       * iFileName = NULL );

  /*  
  * Sets the progress.
  * @param   iProgressBar The progress bar to update
  * @param   iValue       The value currently reached (between 0 and iTotalValue if iTotalValue>0.)  
  * @param   iTotalValue  The value that is reached when 100% progress is achieved.  
  * @param   iThrowIfInterrupted Indicates if an error "MathInterruptedOperator_ERR_110" has to be raised in case of interruption
  * @param   iProgressID  (Debug) A unique ID for the current SetProgress call
  * @param   iFileName    (Debug) The name of the source file where SetProgress was called
  * @return  A boolean to specify whether computation should continue (TRUE) or stop (FALSE).
  *  
  * Important notes : 
  * - If iValue=0 and iTotal value=0, interrupt function is called to check if "stop" is requested.
  * - If iValue is outside progress range, the real progress value won't change.
  * - An internal test avoid any progress back if iValue is lesser than current progress value.
  */
  static CATBoolean SetProgress ( CATCGMProgressBar * iProgressBar,
                                  const double        iValue,
                                  const double        iTotalValue = 100.0,
                                  const CATBoolean    iThrowIfInterrupted = FALSE,
                                  const CATLONG32     iProgressID = -1,
                                  const char        * iFileName = NULL );

  /*
  * Returns the progress currently made.
  * @return A double between 0 and 100.
  */
  double GetProgress () const;

  /*
  * Returns the main progress bar.
  * @return The main progress bar.
  */
  CATCGMProgressBar * GetProgressBar ();

  /*  
  * Constructs a nested progress bar with current progress bar as the parent.
  * The two arguments are the mapped starting and end percentage values respectively:
  *   - A call to SetProgress (0) will map the progress to the iStartPercentage value and will call
  *     parent->SetProgress (startPercentage).
  *   - A call to SetProgress (100) will map the progress to the iEndPercentage value and will call
  *     parent->SetProgress (endPercentage).
  * 
  * @param iStartPercentage A value between 0 and 100 to which a progress of 0% will be mapped.
  * @param iEndPercentage   A value between 0 and 100 to which a progress of 100% will be mapped.
  *                         The iEndPercentage must be greater or equal to the iStartPercentage.
  * @return A pointer to the created progress bar.
  * 
  * Note : Don't delete the created progress bar. That will be done when deleting current progress manager.
  */
  CATCGMProgressBar * CreateAChildProgressBar ( const double iStartPercentage = 0.0, const double iEndPercentage = 100.0 );

  //static version of previous method
  static void CreateAChildProgressBar (CATTopOperator * iParentTopOpe, CATTopOperator * iChildTopOpe, const double iStartPercentage = 0.0, const double iEndPercentage = 100.0 );

  /*
  * Indicates if an interruption has been requested
  * @param iThrowIfInterrupted Indicates if an error "MathInterruptedOperator_ERR_110" has to be raised in case of interruption
  * @return TRUE if an interruption has been requested, FALSE otherwise
  */
  CATBoolean GetInterruptionRequested( const CATBoolean iThrowIfInterrupted ) const;

  //---------------------------------------------------------------------------
  // INLINE METHODS
  //---------------------------------------------------------------------------

  /*
  * Indicates if an interruption has been requested
  * @return TRUE if an interruption has been requested, FALSE otherwise
  */
  INLINE CATBoolean GetInterruptionRequested() const;
  void SetInterruptionRequested(CATBoolean iInterruptionRequested);

private:

  //---------------------------------------------------------------------------
  // PRIVATE METHODS
  //---------------------------------------------------------------------------

  // Method shared by constructors for initialization
  void Initialize();

  // Checks if enougth time has passed between two calls to real progress bar
  // Returns TRUE if enough time has passed
  static CATBoolean CheckMinTime();

  // debug only
  CATBoolean DebugInterrupt_StepAndTraces() const;

  //---------------------------------------------------------------------------
  // MEMBER DATA
  //---------------------------------------------------------------------------

  CATCGMProgressBar           * _ProgressBar;
  CATLISTP(CATCGMProgressBar)   _ListOfChildProgressBars;
  CATBoolean                    _InterruptionRequested;

  CATBoolean                    _InterruptEnabled;
  CATSoftwareConfiguration    * _Config;

  static CATTimeValue           _GoalTime;
  static const CATULONG32       _MinTime;

  // Debug
  CATString                     _OperatorName;
  CATLONG32                     _Id;
  CATBoolean                    _DeleteParentProgressBar;
  static CATLONG32              _InterruptStage;

  static CATLONG32            * _NextId;
  static CATLONG32            * _NbInstances;
};

//-----------------------------------------------------------------------------
// INLINE METHODS IMPLEMENTATION
//-----------------------------------------------------------------------------

INLINE CATBoolean CATlsoProgressBarManager::GetInterruptionRequested() const {
  return _InterruptionRequested; }

#endif /* CATlsoProgressBarManager_H */
