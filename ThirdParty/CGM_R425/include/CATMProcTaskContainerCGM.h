// COPYRIGHT DASSAULT SYSTEMES 2011

#ifndef CATMProcTaskContainerCGM_H
#define CATMProcTaskContainerCGM_H

#include "CATIACGMLevel.h"
#ifdef CATIACGMV5R23

/**
 * @CAA2Level L0
 * @CAA2Usage U2
 */

#include "ExportedByCATGeometricObjects_MProc.h"
#include "CATCGMStream.h"
#include "CATErrorDef.h"

class CATGeoFactory;
class CATMProcTaskContainerCGMImpl;
class CATCGMJournal;

/**
 * Class representing one operation or task to be computed using the MProc system.
 * <b>Note:</b> Clients should derive their custom tasks from this class.
 * <b>Role:</b> This class contains operational data, the inputs and outputs of a task,
 * as well as methods to simplify the streaming of CGM objects and methods to
 * facilitate the transfer of operational data between processes.
 * <br> Clients add data members and overload the transfer methods in custom
 * derived implementations.
 * <br> In sequential mode, only one task container per task is instantiated in the 
 * master process in the NextTask method of the task manager. 
 * When multiple processes are utilized, a duplicate is created in the slave process, 
 * and the streaming methods are used to transmit the operational data between them.
 * It's up to the custom implementation to delete the object in the master process,
 * which typically occurs in the custom EndTask method.
 * Whereas the copy in the slave process is deleted automatically.
 * <br> This class works in conjunction with the CATMProcTaskManagerCGM class.
 * <br> See the MProc System technical article for more information.
 * @see CATMProcTaskManagerCGM
 */
class ExportedByCATGeometricObjects_MProc CATMProcTaskContainerCGM
{
public:

 /**
  * Default constructor initializes member data.
  */
  CATMProcTaskContainerCGM();

 /**
  * Virtual destructor.
  * <br> The default implementation releases base class data.
  */  
  virtual ~CATMProcTaskContainerCGM();

 /**
  * Method called by the MProc system to compute the operational task.
  * <b>Role:</b> The Run method uses the computational data of the class
  * to compute the task. Using the inputs for the operation to compute 
  * the outputs (i.e. the results).
  * @return
  *  <tt>S_OK</tt> if the operation succeeded, otherwise <tt>E_FAIL</tt>.
  */
  virtual HRESULT Run() = 0;

 /**
  * Stream the inputs of an operation to a CATCGMStream.
  * <b>Role</b>: Use this method to add all input data to the stream used
  * for inter-process communication.
  * <br> This method is called on the master process before 
  * the operational data is transmitted to a slave process.
  * @param iStream
  *  The output stream.
  * @return
  *  <tt>S_OK</tt> if the operation succeeded, otherwise <tt>E_FAIL</tt>.
  */
  virtual HRESULT StreamInput( CATCGMStream& iStream) = 0;

 /**
  * Unstream the inputs of an operation from a CATCGMStream.
  * <b>Role</b>: Use this method to retrieve all input data from the stream used
  * for inter-process communication.
  * <br> This method is called on a slave process after 
  * the operational data has been transmitted from the master process.
  * @param iStream
  *  The input stream.
  * @return
  *  <tt>S_OK</tt> if the operation succeeded, otherwise <tt>E_FAIL</tt>.
  */
  virtual HRESULT UnstreamInput( CATCGMStream& iStream) = 0;

 /**
  * Stream the outputs of an operation to a CATCGMStream.
  * <b>Role</b>: Use this method to add all output data to the stream used
  * for inter-process communication.
  * <br> This method is called on a slave process after completing the 
  * operation, before transmitting the result data to the master process.
  * @param iStream
  *  The output stream.
  * @param iResult
  *  The result of the operational task.
  * @return
  *  <tt>S_OK</tt> if the operation succeeded, otherwise <tt>E_FAIL</tt>.
  */
  virtual HRESULT StreamOutput( CATCGMStream& iStream, HRESULT iResult) = 0;

 /**
  * Unstream the outputs of an operation from a CATCGMStream.
  * <b>Role</b>: Use this method to retrieve results from the stream used
  * for inter-process communication.
  * <br> This method is called on the master process after 
  * the operational data has been received from a slave process.
  * @param iStream
  *  The input stream.
  * @param iResult
  *  The result of the operational task.
  * @return
  *  <tt>S_OK</tt> if the operation succeeded, otherwise <tt>E_FAIL</tt>.
  */
  virtual HRESULT UnstreamOutput( CATCGMStream& iStream, HRESULT iResult) = 0;

 /**
  * Method called by the MProc system to release unnecessary resources.
  * <b>Role:</b> The Release method is called after the operational task
  * has completed. Its main purpose is to help keep the factory container
  * clean in slave processes. Here newly created CGMObjects should not be
  * kept after operational results have been transmitted to the master process
  * because of potential internal issues related to identifiers.
  * It is therefore imperative that all newly created objects be removed from the 
  * factory container, leaving only objects that were originally transmitted
  * from the master process. It is important to keep the inputs around
  * because they may be used in subsequent operations.
  * See topic "stream optimization" for more details.
  * @param iResult
  *  The result of the computational task.
  * @param iCalledOnSlave
  *  Flag to identify if the method is called on a slave process.
  */
  virtual void Release( HRESULT iResult, CATBoolean iCalledOnSlave);

 /**
  * Stream a list of CGMObjects to a CATCGMStream.
  * <b>Role</b>: Use this method to add CGMObjects to the stream used
  * for inter-process communication. The underlying functionality additionally
  * keeps track of the objects for optimization purposes.
  * <br> See topic "stream optimization" in the MProc System technical article.
  * @param iStream
  *  The output stream.
  * @param iCGMObjectList
  *  The list of objects to stream.
  * @return
  *  <tt>S_OK</tt> if the operation succeeded, otherwise <tt>E_FAIL</tt>.
  */
  HRESULT WriteGeometry( CATCGMStream& iStream, CATLISTP(CATICGMObject)& iCGMObjectList);

 /**
  * Stream a CGMObject to a CATCGMStream.
  * <b>Role</b>: Use this method to add a CGMObject to the stream used
  * for inter-process communication. The underlying functionality additionally
  * keeps track of the objects for optimization purposes.
  * <br> See topic "stream optimization" in the MProc System technical article.
  * @param iStream
  *  The output stream.
  * @param iCGMObject
  *  The object to stream.
  * @return
  *  <tt>S_OK</tt> if the operation succeeded, otherwise <tt>E_FAIL</tt>.
  */
  HRESULT WriteGeometry( CATCGMStream& iStream, CATICGMObject* iCGMObject);

 /**
  * Unstream multiple CGMObjects from a CATCGMStream and add them to a list.
  * <b>Role</b>: Use this method to retrieve CGMObjects from the stream used
  * for inter-process communication. 
  * @param iStream
  *  The input stream.
  * @param oCGMObjectList
  *  The list of unstreamed objects.
  * @return
  *  <tt>S_OK</tt> if the operation succeeded, otherwise <tt>E_FAIL</tt>.
  */
  HRESULT ReadGeometry( CATCGMStream& iStream, CATLISTP(CATICGMObject)& oCGMObjectList);

 /**
  * Unstream a CGMObject from a CATCGMStream.
  * <b>Role</b>: Use this method to retrieve a CGMObject from the stream used
  * for inter-process communication. 
  * @param iStream
  *  The input stream.
  * @param oCGMObject
  *  The unstreamed object.
  * @return
  *  <tt>S_OK</tt> if the operation succeeded, otherwise <tt>E_FAIL</tt>.
  */
  HRESULT ReadGeometry(CATCGMStream& iStream, CATICGMObject*& oCGMObject);

#ifdef CATIACGMR217CAA
  /**
  * Stream a journal to a CATCGMStream.
  * <b>Role</b>: Use this method to add journal to the stream used
  * for inter-process communication. 
  * <br> See topic "stream optimization" in the MProc System technical article.
  * @param iStream
  *  The output stream.
  * @param iJournal
  *  The journal to stream.
  * @return
  *  <tt>S_OK</tt> if the operation succeeded, otherwise <tt>E_FAIL</tt>.
  */
  HRESULT WriteJournal( CATCGMStream& iStream, CATCGMJournal* iJournal);

  /**
  * Unstream a journal from a CATCGMStream.
  * <b>Role</b>: Use this method to retrieve a journal from the stream used
  * for inter-process communication. 
  * @param iStream
  *  The input stream.
  * @param oJournal
  *  The unstreamed journal.
  * @return
  *  <tt>S_OK</tt> if the operation succeeded, otherwise <tt>E_FAIL</tt>.
  */
  HRESULT ReadJournal(CATCGMStream& iStream, CATCGMJournal*& oJournal);
#endif

 /**
  * Retrieve the CATGeoFactory from this task.
  * @return
  *  The CATGeoFactory object.
  */
  CATGeoFactory* GetFactory();

 /**
  * Retrieve the implicit CATGeoFactory from this task.
  * @return
  *  The implicit CATGeoFactory object.
  */
  CATGeoFactory* GetImplicitFactory();

 /**
  * Get the CATSoftwareConfiguration associated with this task.
  * <b>Role:</b> To properly support operator versioning, use the 
  * Set and GetSoftwareConfiguration methods to retain only one copy 
  * of a CATSoftwareConfiguration object.
  * @return
  *  The CATSoftwareConfiguration object.
  * @see SetSoftwareConfiguration
  */
  CATSoftwareConfiguration* GetSoftwareConfiguration();

 /**
  * Set the CATSoftwareConfiguration associated with this task.
  * <b>Role:</b> To properly support operator versioning, use the 
  * Set and GetSoftwareConfiguration methods to retain only one copy 
  * of a CATSoftwareConfiguration object.
  * <b>Note:</b> The CATSoftwareConfiguration object is actually stored
  * in the task manager so all tasks can utilize only one copy.
  * @see CATSoftwareConfiguration
  * @param iConfig
  *  The configuration to set.
  */
  void SetSoftwareConfiguration( CATSoftwareConfiguration* iConfig);

  /** @nodoc  internal functionality */
  CATMProcTaskContainerCGMImpl* Impl() const { return _Impl; }

private:

  CATMProcTaskContainerCGMImpl* _Impl;

  CATMProcTaskContainerCGM(const CATMProcTaskContainerCGM& iOneOf);
  CATMProcTaskContainerCGM& operator =(const CATMProcTaskContainerCGM& iOneOf);
};

#endif

#endif
