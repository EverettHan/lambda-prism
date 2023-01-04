#ifndef CATCGMProgressBar_h
#define CATCGMProgressBar_h

// COPYRIGHT DASSAULT SYSTEMES  2010

/**
* @CAA2Level L1
* @CAA2Usage U1
*/ 

#include "ExportedByCATMathStream.h"
#include "CATBaseUnknown.h"
#include "CATBoolean.h"
#include "CATDataType.h"
#include "CATLib.h"
#include "CATIACGMLevel.h"
 
#include "CATCGMInterruptDef.h"
#include "CATErrorMacros.h" 
class CATCGMProgressBarDebug;
class CATCGMProgressBarTimeData;
 

typedef CATBoolean (*CATCGMProgressBarInterruptFunction) (void* ioData, int iProgressValue, int iProgressRange);

/**
* Class to track the progress of a task.
* This object can be used in the <tt>Run</tt> of an operator to specify an estimated progress rate for different steps
* of the algorithm. A progress bar can be assigned an interruption function which is to be written by the calling application. 
* A progress bar indicator is incremented between 0 and 100. 
* Progress bars can be nested
* which is useful if an operator calls other operators which may themselves call other operators.  With this
* mecanism, progress can be tracked linearly between 0 and 100 regardless of the nesting depth.<br>
* <b>Example</b>
* If Operator A calls Operators B and C, 
* it can assign to them the progress bars and sets arbitrary proportions.  For instance, assume that the Run method 
* from A calls sequentially the Run methods from B and C and finally a Foo method from A.  Furthermore,
* assume that on average 30% of the time is spent in B::Run, 50% in C::Run and 20% in A::Foo. 
* The three operators have a SetProgressBar method that sets the callback in the operator; <br>
* Let _operA_CB be a pointer to a progress bar instance set in A. Then, the A::Run and A::Foo would be implemented 
* as follows:
* <pre>
*  CATBoolean A::Run ()
*  {
*    CATBoolean okToContinue = TRUE;
*
*    B operB;
*    C operC;
*
*    // _operA_CB is the progress bar that is set in Class A.
*
*    CATCGMProgressBar operB_CB (_operA_CB, 0.0, 30.0);     // 30%
*    b.SetProgressBar (&operB_CB);
*    okToContinue = operB.Run ();
*
*    if (okToContinue)
*    {
*      CATCGMProgressBar operC_CB (_cb, 30.0, 80.0);        // 50%
*      c.SetProgressBar (&cCB);
*      okToContinue = operC.Run ();
*    }
*
*    if (okToContinue)
*    {
*      CATCGMProgressBar fooCB (_cb, 80.0, 100.0);          // 20%
*      okToContinue = Foo (&fooCB);
*    }
*    
*    return okToContinue;
*  }
*
*  okToContinue = A::Foo (CATCGMProgressBar* fooCB)
*  {
*    CATBoolean okToContinue = TRUE;
*
*    if (fooCB)
*      okToContinue = fooCB->SetProgress (0.0);
*    +++
*
*    if (fooCB && okToContinue)
*      okToContinue = fooCB->SetProgress (50.0);
*    +++
*
*    if (okToContinue)
*      okToContinue = fooCB->SetProgress (100.0);
*    +++
*     
*  }
* </pre>
*/
class ExportedByCATMathStream CATCGMProgressBar : public CATBaseUnknown
{
  CATDeclareClass;

  friend class CATCGMProgressBarDebug;
public :
  CATCGMProgressBar ();
  /**
  * Constructs a nested progress bar.
  * The two arguments are the mapped starting and end percentage values respectively:
  * <ul>
  * <li>A call to SetProgress (0.0) will map the progress to the iStartPercentage value and will call
  * callback->SetProgress (startPercentage).
  * <li>A call to SetProgress (100.0) will map the progress to the iEndPercentage value and will call
  * callback->SetProgress (endPercentage).
  * </ul>
  * @param iParentProgressBar
  * The parent progress bar.
  * @param iStartPercentage
  * A value between 0.0 and 100.0 to which a progress of 0% will be mapped.
  * @param iEndPercentage
  * A value between 0.0 and 100.0 to which a progress of 100% will be mapped. 
  * The iEndPercentage must be greater or equal to the iStartPercentage.
  */
  CATCGMProgressBar (CATCGMProgressBar* iParentProgressBar, const double iStartPercentage = 0.0, const double iEndPercentage = 100.0);

  virtual ~CATCGMProgressBar ();

  /**
  * Sets the progress bar display and interrupt function. The progress bar function cannot be specified twice.
  * If a parent progress bar is specified, its interrupt function is used,
  * even if  an other interrupt function is set by SetProgressBarFunction.
  * @param ipInterruptFunction
  * The interruption function to be written by the calling application.
  */
  void SetProgressBarFunction (CATCGMInterruptFunction ipInterruptFunction);

  /**
  * @nodoc
  * same as above; temporary or future interface
  */
  void SetProgressBarInterruptFunction(CATCGMProgressBarInterruptFunction ipProgressBarInterruptFunction, void* ipInterruptData);

  /**
  * Sets the progress.
  * <ul>
  * <li>If iValue=0 and iTotal value=0, interrupt function is called to check if "stop" is requested.
  * <li>If iValue is outside progress range, the real progress value won't change.
  * <li>An internal test avoid any progress back if iValue is lesser than current progress value.
  * </ul>
  * @param iValue
  * The value currently reached (between 0 and iTotalValue if iTotalValue>0.)
  * @param iTotalValue
  * The value that is reached when 100% progress is achieved.
  * @param iThrowIfInterrupted
  * Indicates if an error "MathInterruptedOperator_ERR_110" has to be raised in case of interruption
  * @param iStaticConstLabel
  *    This value is usefull for debugging purpose.
  *    if not NULL, to avoid memory lifecycle and invalid pointer, it MUST refers something such as :
  *     <pre> 
  *        static const char MyOperationLabel[] = "IntersectionFaceFace"; 
  *        const char* iStaticConstLabel = MyOperationLabel; 
  *     </pre>
  * @return
  * A boolean to specify whether computation should continue (TRUE) or stop (FALSE.)
  */
  CATBoolean SetProgress (const double       iValue,
                          const double       iTotalValue         = 100.0, 
                          CATBoolean         iThrowIfInterrupted = FALSE,
                          const char*        iStaticConstLabel   = NULL);

  /**
  * Returns the progress currently made.
  * @return
  * A double between 0 and 100.
  */
  double GetProgress () const;

  /**
  *  Returns the external interrupt function (NULL if none)
  */
  CATCGMInterruptFunction GetInterruptFunction ();

  /**
  * @nodoc
  *  same as above; temporary or future interface
  */
  CATCGMProgressBarInterruptFunction GetProgressBarInterruptFunction(void*& oProgressBarInterruptData);

  /**
  * @nodoc
  */
  virtual CATBoolean Callback (const int iProgressPercentage = 0) const;


  /**
  * @nodoc
  */
  void SetMinTime(CATULONG32 iMinTime);// (internal use?) Sets minimum time in microseconds between 2 calls to interrupt function

private:

  /**
  * @nodoc
  * Internal usage only : Initialization.
  */
  void Init();

  /**
  * @nodoc
  * Internal usage only : Sets the progress.
  * @param iPercentage
  * A percentage value (between 0 and 100) to specify the progress currently made.
  * @param ForceInterruptCall
  * Indicates if interrupt has to be checked, even if progress is null
  * @param iThrowIfInterrupted
  * Indicates if an error "MathInterruptedOperator_ERR_110" has to be raised in case of interruption
  * @param iCheckMinTime
  * Indicates whether minimum time must be checked
  * @return
  * A boolean to specify whether computation should continue (TRUE) or stop (FALSE.)
  */
  CATBoolean SetPercentageProgress (const double       iPercentage,
                                    CATBoolean         iForceInterruptCall,
                                    CATBoolean         iThrowIfInterrupted = FALSE,
                                    CATBoolean         iCheckMinTime=TRUE,
                                    const char*        iStaticConstLabel = NULL);


  /**
  * @nodoc
  * Internal usage only : Checks if enough time has passed between two calls to real progress bar
  * Return : TRUE if enough time has passed
  * This is used to avoid too numeral number of interrupt calls
  */
  CATBoolean CheckMinTime();

  /**
  * @nodoc
  * Internal usage only : Updates target time
  */
  void UpdateTargetTime();

  /**
  * @nodoc
  */

  CATCGMProgressBar (const CATCGMProgressBar & rhs);
  /**
  * @nodoc
  */
  CATCGMProgressBar& operator = (const CATCGMProgressBar & rhs);

  CATCGMProgressBar* _ParentProgressBar;
  CATCGMProgressBar* _RootProgressBar;

  double _Start;     // The value to which 0% progress will be mapped inside its parent progress bar.
  double _End;       // The value to which 100% progress will be mapped inside its parent progress bar.

  double _Progress;  // The progress made (between 0 and 100.)

  CATCGMInterruptFunction _pInterruptionFunction; // External interruption function eventually given
  CATCGMProgressBarInterruptFunction _pProgressBarInterruptFunction;
  void*                              _pProgressBarInterruptData;

  CATCGMProgressBarDebug* _Debug;
  CATCGMProgressBarTimeData* _RootTimer;
};

#endif
