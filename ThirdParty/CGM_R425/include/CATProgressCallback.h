//=============================================================================
// COPYRIGHT Dassault Systemes 2016
//=============================================================================
//
// CATProgressCallback.h
// This class is inspired from CATCGMProgressBar, with those changes:
// - Get rid of thread-unsafe CATBaseUnknown derivation.
// - Addref and Release const and thread-safe.
// - No more static members.
// - No more thread-unsafe static C-style interruption functions.
// - Applications should use only derivation and Callback method.
//
//=============================================================================
// 2016-02-16   JXO
//      * New
//=============================================================================

#ifndef CATProgressCallback_h
#define CATProgressCallback_h


#include "ExportedByCATMathStream.h"

// System
#include "CATBoolean.h"


/**
* Class to track the progress of a task.
* This object can be used in the <tt>Run</tt> of an operator to specify an estimated progress rate for different steps
* of the algorithm. A progress bar can be assigned an interruption function which is to be written by the calling application. 
* A progress bar indicator is incremented between 0 and 100. 
* Progress bars can be nested which is useful if an operator calls other operators which may themselves call other operators.
* With this mecanism, progress can be tracked linearly between 0 and 100 regardless of the nesting depth.<br>
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
*    CATProgressCallback operB_CB (_operA_CB, 0.0, 30.0);     // 30%
*    b.SetProgressBar (&operB_CB);
*    okToContinue = operB.Run ();
*
*    if (okToContinue)
*    {
*      CATProgressCallback operC_CB (_cb, 30.0, 80.0);        // 50%
*      c.SetProgressBar (&cCB);
*      okToContinue = operC.Run ();
*    }
*
*    if (okToContinue)
*    {
*      CATProgressCallback fooCB (_cb, 80.0, 100.0);          // 20%
*      okToContinue = Foo (&fooCB);
*    }
*    
*    return okToContinue;
*  }
*
*  okToContinue = A::Foo (CATProgressCallback* fooCB)
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
class ExportedByCATMathStream CATProgressCallback
{
public :
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
  * The parent progress bar. If set to null ptr, then it is not nested.
  * @param iStartPercentage
  * A value between 0.0 and 100.0 to which a progress of 0% will be mapped.
  * @param iEndPercentage
  * A value between 0.0 and 100.0 to which a progress of 100% will be mapped. 
  * The iEndPercentage must be greater or equal to the iStartPercentage.
  */
  CATProgressCallback (CATProgressCallback * iParentProgressBar = 0, const double iStartPercentage = 0.0, const double iEndPercentage = 100.0);

  /** Destructor */
  virtual ~CATProgressCallback ();

  /**
  * May be implemented by application, and will be called back by the SetProgress method with the right value (nested context.)
  * DO NOT call this method inside your operator. Call SetProgress instead.
  * @return
  *         Should return TRUE if operator can continue, FALSE if operator is to be stopped.
  *         (This is the opposite of the CGM interruption function.)
  */
  virtual CATBoolean Callback (const double iProgressPercentage = 0.);

  /**
  * Set the minimum percent step required for calling the Callback method.
  * The default is 0%. It means every time SetProgress is called by the operator, the Callback method is called.
  * If set to 1%, it means that the progress must have been superior or equal to 1% before the Callback method is called.
  */
  void SetMinimumStep (const double iMinimumStep);

  /**
  * Sets the progress. Called by the operator during progress.
  * <ul>
  * <li>If iValue is outside progress range, the real progress value won't change.
  * <li>An internal test avoid any progress back if iValue is lesser than current progress value.
  * </ul>
  * @param iValue
  * The value currently reached (between 0 and iTotalValue if iTotalValue>0.)
  * @param iTotalValue
  * The value that is reached when 100% progress is achieved.
  * @return
  * A boolean to specify whether computation should continue (TRUE) or stop (FALSE.)
  */
  virtual CATBoolean SetProgress (const double       iValue,
                                  const double       iTotalValue         = 100.0);

  /** AddRef */
  void AddRef () const;
  /** Release */
  void Release () const;

private:
  /**
  * @nodoc
  * Internal usage only : Sets the progress.
  * @param iPercentage
  * A percentage value (between 0 and 100) to specify the progress currently made.
  * @return
  * A boolean to specify whether computation should continue (TRUE) or stop (FALSE.)
  */
  CATBoolean SetPercentageProgress (const double iPercentage);


private:
  CATProgressCallback * m_ParentProgressBar;

  double m_Start;     // The value to which 0% progress will be mapped inside its parent progress bar.
  double m_End;       // The value to which 100% progress will be mapped inside its parent progress bar.

  double m_Progress;  // The progress made (between 0 and 100.)
  double m_MinimumStep;

  mutable int m_Ref;
  CATBoolean m_ContinueToCompute;
};

#endif
