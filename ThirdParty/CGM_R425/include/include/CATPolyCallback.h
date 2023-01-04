// COPYRIGHT DASSAULT SYSTEMES 2005, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyCallback.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// Aug 2005 Creation: ndo
// Nov 2005 Migration (>=R17) sur CATCGMProgressBar : fdn
//===================================================================
#ifndef CATPolyCallback_h
#define CATPolyCallback_h

#include "CATIACGMLevel.h"

#ifndef CATIACGMV5R17

#include "PolyhedralCallbacks.h"
#include "CATBaseUnknown.h"
#include "CATBoolean.h"


/**
* Class managing callbacks for operators.  The callback is a virtual function, Callback (), which can be 
* overriden in a derived class. The default implementation of this method in this class always returns TRUE.
* Typically, the callbacks are made incrementally in unit steps between 0 and 100. To signal an interruption,
* the callback method should return FALSE.
*
* In a typical use, this class is used to track progress during computation.  The class supports nested callbacks
* which is useful if an operator calls other operators which may themselves call other operators.  With this
* callback mecanism, progress can be tracked linearly between 0 and 100 regardless of the nesting depth.
*
* Let us illustrate the nested callback mechanism with an example. If Operator A calls Operators B and C, 
* it can assign to them the callbacks and sets arbitrary proportions.  For instance, assume that the Run method 
* from A calls sequentially the Run methods from B and C and finally a Foo method from A.  Furthermore,
* assume that on average 30% of the time is spent in B::Run, 50% in C::Run and 20% in A::Foo. 
* The three operators have a SetCallback method that sets the callback in the operator; let _operA_CB
* be a pointer to a callback instance set in A. Then, the A::Run and A::Foo would be implemented 
* as follows:
*
*  CATBoolean A::Run ()
*  {
*    CATBoolean okToContinue = TRUE;
*
*    B operB;
*    C operC;
*
*    // _operA_CB is the callback that is set in Class A.
*
*    CATPolyCallback operB_CB (_operA_CB, 0, 30);     // 30%
*    b.SetCallback (&operB_CB);
*    okToContinue = operB.Run ();
*
*    if (okToContinue)
*    {
*      CATPolyCallback operC_CB (_cb, 30, 80);        // 50%
*      c.SetCallback (&cCB);
*      okToContinue = operC.Run ();
*    }
*
*    if (okToContinue)
*    {
*      CATPolyCallback fooCB (_cb, 80, 100);          // 20%
*      okToContinue = Foo (&fooCB);
*    }
*    
*    return okToContinue;
*  }
*
*  okToContinue = A::Foo (CATPolyCallback* fooCB)
*  {
*    CATBoolean okToContinue = TRUE;
*
*    if (fooCB)
*      okToContinue = fooCB->SetProgress (0);
*    +++
*
*    if (fooCB && okToContinue)
*      okToContinue = fooCB->SetProgress (50);
*    +++
*
*    if (okToContinue)
*      okToContinue = fooCB->SetProgress (100);
*    +++
*     
*  }
*
* Each call to SetProgress () will call the virtual function Callback () when there is a change in the 
* value of the progress made.  The value returned by SetProgress () is the same as the returned value from 
* Callback (); it should be used to stop computation when it is FALSE. Of course, the operators B and C can
* follow the same mechanism and call other operators if needed.
*
*/
class ExportedByPolyhedralCallbacks CATPolyCallback : public CATBaseUnknown
{
  
  CATDeclareClass;
  
public :
  
  CATPolyCallback ();

  /*
  * Constructs a nested callback.
  * The two integer arguments are the mapped starting and end percentage values respectively:
  *   - A call to SetProgress (0) will map the progress to the startPercentage value and will call
  *     callback->SetProgress (startPercentage).
  *   - A call to SetProgress (100) will map the progress to the endPercentage value and will call
  *     callback->SetProgress (endPercentage).
  * 
  * @param callback
  *   The parent callback.
  * @param startPercentage
  *   A value between 0 and 100 to which a progress of 0% will be mapped.
  * @param endPercentage
  *   A value between 0 and 100 to which a progress of 100% will be mapped. 
  *   The endPercentage must be greater or equal to the startPercentage.
  */
  CATPolyCallback (CATPolyCallback* callback, const int startPercentage = 0, const int endPercentage = 100);

  virtual ~CATPolyCallback ();

  /*
  * Sets the progress.
  * @param value
  *   The value currently reached (between 0 and totalValue.)
  * @param totalValue
  *   The value that is reached when 100% progress is achieved.
  * @return
  *   A boolean to specify whether computation should continue (TRUE) or stop (FALSE.)
  */
  CATBoolean SetProgress (const double value, const double totalValue);

  /*
  * Sets the progress.
  * @param progressPercentage
  *   A percentage value (between 0 and 100) to specify the progress currently made.
  * @return
  *   A boolean to specify whether computation should continue (TRUE) or stop (FALSE.)
  */
  CATBoolean SetProgress (const int progressPercentage);

  /*
  * Returns the progress currently made.
  * @return
  *   An integer between 0 and 100.
  */
  int GetProgress () const;

  /*
  * A callback that is made when SetProgress (...) is called.  This method can be overriden to
  * implement a specific callback.  The returned value becomes the returned value of the SetProgress 
  * method.  By default this method always returns TRUE and does not do anything.
  * @param progressPercentage
  *   A percentage value (between 0 and 100) to specify the progress currently made.
  * @return
  *   A boolean to specify whether computation should continue (TRUE) or stop (FALSE.)
  */
  virtual CATBoolean Callback (const int progressPercentage) const;

private:
  
  CATPolyCallback (const CATPolyCallback & rhs);
  CATPolyCallback& operator = (const CATPolyCallback & rhs);

  CATPolyCallback* _Callback;

  int _Start;     // The value to which 0% progress will be mapped.
  int _End;       // The value to which 100% progress will be mapped.

  int _Progress;  // The progress made (between 0 and 100.)

};

#endif

#endif
