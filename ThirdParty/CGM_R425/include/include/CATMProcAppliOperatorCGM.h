// COPYRIGHT DASSAULT SYSTEMES 2004

#ifndef CATMProcAppliOperatorCGM_H
#define CATMProcAppliOperatorCGM_H

#include "CATIACGMLevel.h" // automatic treatment EB_2014_04_16
#include "ExportedByCATGeometricObjects_MProc.h"
#include "CATMProcAppliOperator.h"
#include "CATBoolean.h"
#include "CATCGMStream.h"

class CATGeoFactory;
class CATCGMOperator;
class CATMProcAppliManagerStream;
class CATMProcAppliManagerCGM;
class CATMProcAppliOperatorCGM;
class CATMProcAppliDataCGM;
class CATMProcSlaveOperatorStream;
class CATMProcSlaveOperatorCGM;
class CATExtCGMReplayForMProc;
class CATCGMJournal;

class ExportedByCATGeometricObjects_MProc CATMProcOperatorStreamingSupport
{
	static CATMProcAppliOperatorCGM* _AppliOperator;
	static CATMProcSlaveOperatorCGM* _SlaveOperator;
	CATExtCGMReplayForMProc* _ReplayForMProc;

public:

	CATMProcOperatorStreamingSupport();
	~CATMProcOperatorStreamingSupport();

	static CATBoolean IsActive();
	static CATGeoFactory* GetFactory();
	static HRESULT WriteGeometry( CATCGMStream& iStream, CATLISTP(CATICGMObject)& iListToWrite);
	static HRESULT ReadGeometry( CATCGMStream& iStream, CATLISTP(CATICGMObject)& oListToRead);

private:

	HRESULT WriteOperator( CATCGMStream& iStream, CATCGMOperator* iOperator, CATMProcAppliOperatorCGM* AppliOp, CATMProcSlaveOperatorCGM* SlaveOp );
	CATCGMOperator* ReadOperator( CATCGMStream& iStream, CATMProcAppliOperatorCGM* AppliOp, CATMProcSlaveOperatorCGM* SlaveOp );
	void Clear();

	friend class CATMProcAppliOperatorCGM;
	friend class CATMProcSlaveOperatorCGM;
};


/**
 * Class representing one operation or task to be computed using the MProc system.
 * <b>Note:</b> Clients should derive their custom tasks from this class.
 * <b>Role:</b> This class contains operational data, the inputs and outputs of a task,
 * as well as methods to simplify the streaming of CGM objects and methods to
 * facilitate the transfer of operational data between processes.
 * <br> Clients add data members and overload the transfer methods in custom
 * derived implementations.
 * <br> In sequential mode, only one task container per task is instantiated in the 
 * master process in the NextOperator method of the task manager. 
 * When multiple processes are utilized, a duplicate is created in the slave process, 
 * and the streaming methods are used to transmit the operational data between them.
 * It's up to the custom implementation to delete the object in the master process,
 * which typically occurs in the custom EndOperator method.
 * Whereas the copy in the slave process is deleted automatically.
 * <br> This class works in conjunction with the CATMProcAppliManagerCGM class.
 * <br> See the MProc System technical article for more information.
 * @see CATMProcAppliManagerCGM
 */
class ExportedByCATGeometricObjects_MProc CATMProcAppliOperatorCGM : public CATMProcAppliOperator
{
public:

  /**
   * Default constructor.
   * <br> The default implementation initializes base class data.
   */  
  CATMProcAppliOperatorCGM();

  /**
   * Default destructor.
   * <br> The default implementation releases base class resources.
   */  
  virtual ~CATMProcAppliOperatorCGM();

public:

  /**
   * Retrieve the CATGeoFactory from this operator.
   * @return
   *  The CATGeoFactory object.
   */
  CATGeoFactory* GetFactory();

  /**
   * Retrieve the implicit CATGeoFactory from this operator.
   * @return
   *  The implicit CATGeoFactory object.
   */
  CATGeoFactory* GetImplicitFactory();
  
  /**
   * Get the CATSoftwareConfiguration associated with this operator.
   * <b>Role:</b> To properly support operator versioning, use the 
   * Set and GetSoftwareConfiguration methods to retain only one copy 
   * of a CATSoftwareConfiguration object.
   * @return
   *  The CATSoftwareConfiguration object.
   * @see SetSoftwareConfiguration
   */
  CATSoftwareConfiguration* GetSoftwareConfiguration();

  /**
   * Set the CATSoftwareConfiguration associated with this operator.
   * <b>Role:</b> To properly support operator versioning, use the 
   * Set and GetSoftwareConfiguration methods to retain only one copy 
   * of a CATSoftwareConfiguration object.
   * @see CATSoftwareConfiguration
   * @param iConfig
   *  The configuration to set.
   */
  void SetSoftwareConfiguration(CATSoftwareConfiguration* iConfig);

 /**
  * Stream a list of CGMObjects to a CATCGMStream.
  * <b>Role</b>: Use this method to add CGMObjects to the stream used
  * for inter-process communication. The underlying functionality additionally
  * keeps track of the objects for optimization purposes.
  * <br> See topic "stream optimization" in the MProc System technical article.
  * @param oStream
  *  The output stream.
  * @param iCGMObjectList
  *  The list of objects to stream.
  * @return
  *  <tt>S_OK</tt> if the operation succeeded, otherwise <tt>E_FAIL</tt>.
  */
  HRESULT WriteGeometry(CATCGMStream& oStream, CATLISTP(CATICGMObject)& iCGMObjectList);

 /**
  * Stream a CGMObject to a CATCGMStream.
  * <b>Role</b>: Use this method to add a CGMObject to the stream used
  * for inter-process communication. The underlying functionality additionally
  * keeps track of the objects for optimization purposes.
  * <br> See topic "stream optimization" in the MProc System technical article.
  * @param oStream
  *  The output stream.
  * @param iCGMObject
  *  The object to stream.
  * @return
  *  <tt>S_OK</tt> if the operation succeeded, otherwise <tt>E_FAIL</tt>.
  */
  HRESULT WriteGeometry(CATCGMStream& oStream, CATICGMObject* iCGMObject);

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
  HRESULT ReadGeometry(CATCGMStream& iStream, CATLISTP(CATICGMObject)& oCGMObjectList);

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
  * Stream a CGMJournal to a CATCGMStream.
  * <b>Role</b>: Use this method to add a CGMJournal to the stream used
  * for inter-process communication. 
  * @param oStream
  *  The output stream.
  * @param iJournal
  *  The journal to stream.
  * @return
  *  <tt>S_OK</tt> if the operation succeeded, otherwise <tt>E_FAIL</tt>.
  */
  HRESULT WriteJournal(CATCGMStream& ioStream, CATCGMJournal * iJournal);

  /**
  * Unstream a CGMJournal from a CATCGMStream.
  * <b>Role</b>: Use this method to retrieve a CGMJournal from the stream used
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
  * Stream a CATCGMOperator to a CATCGMStream.
  * @param iStream
  *  The output stream.
  * @param iOperator
  *  The operator to stream.
  * @return
  *  <tt>S_OK</tt> if the operation succeeded, otherwise <tt>E_FAIL</tt>.
  */
  HRESULT WriteOperator( CATCGMStream& iStream, CATCGMOperator* iOperator);

/**
  * Unstream a CATCGMOperator from a CATCGMStream.
  * @param iStream
  *  The output stream.
  * @return
  *  The unstreamed operator.
  */
  CATCGMOperator* ReadOperator( CATCGMStream& iStream);

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
  virtual HRESULT StreamInput(CATCGMStream& oStream);

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
  virtual HRESULT UnstreamInput(CATCGMStream& iStream);

 /**
  * Stream the outputs of an operation to a CATCGMStream.
  * <b>Role</b>: Use this method to add all output data to the stream used
  * for inter-process communication.
  * <br> This method is called on a slave process after completing the 
  * operation, before transmitting the result data to the master process.
  * @param oStream
  *  The output stream.
  * @param iResult
  *  The result of the operational task.
  * @return
  *  <tt>S_OK</tt> if the operation succeeded, otherwise <tt>E_FAIL</tt>.
  */
  virtual HRESULT StreamOutput(CATCGMStream& oStream, HRESULT iResult);

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
  virtual HRESULT UnstreamOutput(CATCGMStream& iStream, HRESULT iResult);


public:

  ////////////////////////////////////////////////////////////////
  // The remainder of this class is for internal purposes only. //
  ////////////////////////////////////////////////////////////////

  /** @nodoc  internal functionality */
  virtual HRESULT StreamInput(void*& ioBuffer, unsigned int& ioLgBuffer, unsigned int& oLgData);

  /** @nodoc  internal functionality */
  virtual HRESULT UnstreamInput(void*& iBuffer, unsigned int& iLgBuffer, unsigned int& iLgData);

  /** @nodoc  internal functionality */
  virtual HRESULT StreamOutput(void*& ioBuffer, unsigned int& ioLgBuffer, unsigned int& oLgData, HRESULT iResult);

  /** @nodoc  internal functionality */
  virtual HRESULT UnstreamOutput(void* iBuffer, unsigned int iLgData);

  //creates an operator and defining it's run protocol(sequential or parallel)
  /** @nodoc  internal functionality */
  CATMProcAppliOperatorCGM(CATBoolean iIsSequential,CATMProcAppliManagerCGM* iAppliManager,CATMProcAppliDataCGM * iAppliData);

  // creates an operator for use in slave process
  /** @nodoc  internal functionality */
  CATMProcAppliOperatorCGM(CATMProcSlaveOperatorCGM* iSlaveOperatorCGM);

protected:
  /** @nodoc  internal functionality */
  void SetFactory( CATGeoFactory* iFactory);
  /** @nodoc  internal functionality */
  CATMProcAppliManagerCGM*  GetAppliManagerCGM();
  /** @nodoc  internal functionality */
  CATMProcSlaveOperatorCGM* GetSlaveOperatorCGM();

private:
  CATMProcOperatorStreamingSupport OperatorStreamingSupport;
};

/*
* Legacy comments:
*	class representing one operator , one task to be executed using the mproctools
* this operator can be runned either way in parallel on another process a slave,
* or on the master depending on the boolean attribute is sequential
*/

#endif
