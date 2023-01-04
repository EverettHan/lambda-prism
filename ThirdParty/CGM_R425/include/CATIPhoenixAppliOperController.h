#ifndef CATIPhoenixAppliOperController_h
#define CATIPhoenixAppliOperController_h

// @COPYRIGHT DASSAULT SYSTEMES 2013
//-------------------------------------------------------------------------------------------------
// CATIPhoenixAppliOperController : Interface which provides support to replay a phoenix file in 
// an interactive mode by allowing extensions and the interactive application to communicate.
// It's up to the interactive application to implement this interface and to set the implementation 
// in the phoenix extension. Once set, the application and extension can interact with eachother
// for providing the interactive behavior(play, pause, next, prev)
//-------------------------------------------------------------------------------------------------

class CAT3DRep;
class CAT3DBagRep;
class CATCGMOutput;
class CATUnicodeString;
class CATMathTransformation;

class CATIPhoenixAppliOperController
{
public:

  /*
  * virtual destructor
  */
  virtual ~CATIPhoenixAppliOperController() 
  {
  }
 
  //-----------------------------------------------------------------------------------------------
  // Methods For synchronizing multithreaded execution of a phoenix transaction 
  // in the phoenix debug application
  //-----------------------------------------------------------------------------------------------

  /**
  * Phoenix extension should wait for this waiting point after every unary operation.
  * By releasing the flow cleverly, the implementation of CATIPhoenixAppliOperController 
  * controls the way the operator is replayed.
  * @param iRunPoint
  *  Tells the controller what runpoint has been reached.
  *  If set, it should incremented
  * @return
  *  0: Everything is OK
  *  1: Replay has been canceled. You can choose to finish your redo or not.
  */
  virtual int WaitAfterOperation(int iRunPoint = -1) = 0;

  //-----------------------------------------------------------------------------------------------
  // Methods For Visualization Management
  // The subsequent methods are related to proper management of data to be visualized(CATRep's).
  // All visualization events should be processed in the Main thread. When the phoenix transaction
  // is executing in a Worker thread, these methods allow the extension to set the reps to be 
  // processed(add to viewer, remove from viewer, add to container, destroy) into lists which are
  // then processed at a later time in the Main thread when a call back for visualization event
  // is recieved in the main thread.
  //-----------------------------------------------------------------------------------------------

  /**
  * The phoenix extension can :
  * - Update existing input reps using this method. The passed index corresponds to
  *   to the order in which the input data appears in the phoenix XML. 
  *   Index values start from 1...(1,2,3...N)
  * - Additionally add any new reps created during replay in this viewer for
  *   interactive display of the phoenix result. For such reps the index value
  *   to be passed is -1
  * Don't forget to call the Draw method on the viewer to update the view.
  * The lifecycle of the rep's added here is to be managed by the extension.
  */
  virtual void AddRepToViewer(CAT3DRep * ipRep, int iIndex) = 0;

  /**
  * Remove the representations added to the controller using the 
  * AddRepToViewer method
  */
  virtual void RemoveRepFromViewer(CAT3DRep * pRep) = 0;

  /**
  * Removing representations from containers during the replay should be
  * delegated to the controller. This is done so that actual removal of 
  * reps happens always in the main thread
  */
  virtual void RemoveRepFromContainer(CAT3DBagRep * iopContainer, CAT3DRep * ipRep) = 0;

  /**
  * Destruction of representations during the replay should be
  * delegated to the controller. This is done so that actual destruction of 
  * reps happens always in the main thread
  */
  virtual void DestroyRep(CAT3DRep * pRep) = 0;

  /**
  * Ask for a redraw of the viewer.
  */
  virtual void Draw() = 0;

  /*
  * Hide the input at the passed index
  */
  virtual void HideInput(int iIndex) = 0;

  /*
  * Show the input at the passed index
  */
  virtual void ShowInput(int iIndex) = 0;

  /*
  * Translate the position of the input corresponding to the passed index
  */
  virtual void ChangeInputPosition(const CATMathTransformation & iTransformation,
                                   int                           iIndex) = 0;

  //-----------------------------------------------------------------------------------------------
  // Traces management
  //-----------------------------------------------------------------------------------------------

  /**
  * Interactive display of the passed CATUnicodeString. It should not be too long
  * so that it can be displayed properly in the application window.
  * Can pass the RGB values for colored traces, default is black color
  */
  virtual void SetInteractiveTrace(const CATUnicodeString & iTraceStr,
                                   float                    iRed    = float(0), 
                                   float                    iGreen  = float(0),
                                   float                    iBlue   = float(0)) = 0;
};

#endif

