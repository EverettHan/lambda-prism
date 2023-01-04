#ifndef CATEvent_H
#define CATEvent_H

// COPYRIGHT DASSAULT SYSTEMES 2010

/* 
	A CATEvent object is a synchronization object whose state can be explicitly set to signaled by use of the SetEvent method.
*/

#include "CATConstantsForThreads.h"

#define Event_Signaled    			0
#define Event_WaitFailed       		1000
#define Event_TimeOut          		1001

class ExportedByJS0MT CATEvent
{
  public:	  	 
  
  // Destructor
  virtual ~CATEvent() {};
  
  // The state is set to signaled
  virtual void SetEvent() = 0;
    
  // The state is reset to non signaled.
  virtual void ResetEvent() = 0;  
  
  protected :	  
    // Constructor not available, use instead the global method CreateCATEvent
	CATEvent() {};		
	
  private :	  	
	// Not implemented.
	CATEvent(const  CATEvent &iSrc);
	CATEvent& operator= (const CATEvent &iSrc);	
};

// Waits until the CATEvent is signaled
// iEvent is the CATEvent to wait on its signaled state.
// If iTimeOut is -1, the function will return only when iEvent is signaled.  
// else iTimeOut is the time-out interval in milliseconds, the function waits until iEvent is signaled or the interval elapses.   
// This function does not guarantee that the signaled CATEvent is in signaled state when it returns, it only guarantees that it was signaled at some point.
// Possible return value : 
// - Event_Signaled : the state of the specified object is signaled. 
// - Event_TimeOut       : The time-out interval elapsed and the object's state is nonsignaled.
// - Event_WaitFailed    : The function has failed. 
ExportedByJS0MT int WaitForSingleEvent(CATEvent * iEvent, int iTimeOut=-1);

// The maximun size for a CATEvent list as input parameter of the following method WaitForMultipleEvents
extern ExportedByJS0MT const int CAT_MAXIMUM_WAIT_EVENTS;

// Waits until any or all CATEvents are signaled. iEvents are the CATEvents to wait on their signaled state.
// If iWaitall==0 then the method will return when any of the CATEvents is signaled. If iWaitall!=0 then the method will return when all CATEvents are signaled at the same time.
// If iTimeOut is -1, the function will return only when CATEvents are signaled else iTimeOut is the time-out interval in milliseconds and the function waits 
// until CATEvents are signaled or the interval elapses.
// This function does not guarantee that the signaled CATEvent(s) are in signaled state when it returns, it only guarantees that they were signaled at some point.
// Possible return values: 
// - Event_Signaled to Event_Signaled + iNbEvents - 1 : If iWaitAll!=0, the return value indicates that the state of all specified objects is signaled. 
//       If iWaitAll==0, the return value minus Event_Signaled indicates the iEvents array index of one object that satisfied the wait.
// - Event_TimeOut    : The time-out interval elapsed and the conditions specified by the iWaitAll parameter are not satisfied.
// - Event_WaitFailed : The function has failed. For example the number of CATEvents to wait on is bigger than CAT_MAXIMUM_WAIT_EVENTS.
ExportedByJS0MT int WaitForMultipleEvents(int iNbEvents, CATEvent ** iEvents, int iWaitAll=0, int iTimeOut=-1);   

// The factory method.
// If iInitiallySignaled==0 then the CATEvent is initialized in a non signaled state else in a signaled state.
ExportedByJS0MT CATEvent * CreateCATEvent(int iInitiallySignaled=1);

#endif
