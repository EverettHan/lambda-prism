// COPYRIGHT DASSAULT SYSTEMES 2004

#ifndef CATMProcAppliManagerCGM_H
#define CATMProcAppliManagerCGM_H

#include "CATIACGMLevel.h" // automatic treatment EB_2014_04_16
#include "ExportedByCATGeometricObjects_MProc.h"
#include "CATMProcAppliManager.h"
#include "CATCGMStream.h"

class CATMProcAppliTask;
class CATMProcAppliDataCGM;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATCGMSafeHashTable;
class CATCGMJournal;

/**
 * Class that manages the operations or tasks to be computed using the MProc system.
 * <b>Role:</b> This class provides functionality for creating new tasks and for processing completed tasks. 
 * It also contains the CATGeoFactory to be used for all operations. 
 * Custom implementations derive from this class to add task division and accumulation logic,
 * as well as data members to track the over-all progress of the parallel transaction.
 * New tasks are created in the virtual NextOperator method and completed tasks
 * are processed in the EndOperator method.
 * <br> This class works in conjunction with the CATMProcAppliOperatorCGM class.
 * <br> See the MProc System technical article for more information.
 * @see CATMProcAppliOperatorCGM
 */
class ExportedByCATGeometricObjects_MProc CATMProcAppliManagerCGM : public CATMProcAppliManager
{
public:

 /**
  * Overloaded constructor with arguments to reference derived class functionality.
  * <br> This constructor records the MProcRelation name,
  * used to establish the relationship between the task manager and task container,
  * and the library in which the custom implemantation can be found.
  * <b>Note:</b> The MProcRelation name must begin with "MProcRelationCGM" when
  * deriving from the CGM level of the MProc class structure.
  * @param iRelationName
  *  Client implementation object relationship name.
  * @param iFunctionLibrary
  *  The name of the library containing the client implementation.
  */  
  CATMProcAppliManagerCGM(const char* iRelationName, const char* iFunctionLibrary, CATGeoFactory* iFactory);

 /**
  * Default destructor.
  * <br> The default implementation releases base class data.
  */  
  virtual ~CATMProcAppliManagerCGM();

 public:

  /**
   * Get the current factory.
   * @return
   *  The CATGeoFactory object.
   */  
  CATGeoFactory* GetFactory();

  /**
   * Get the current implicit factory.
   * @return
   *  The implicit CATGeoFactory object.
   */  
  CATGeoFactory* GetImplicitFactory();

  /**
   * Set the CATSoftwareConfiguration associated with this task manager.
   * <b>Role:</b> To properly support operator versioning, use the 
   * Set and GetSoftwareConfiguration methods to retain only one copy 
   * of a CATSoftwareConfiguration object.
   * @param iConfig
   *  The configuration to set.
   * @return
   *  <tt>S_OK</tt> if the operation succeeded, otherwise <tt>E_FAIL</tt>.
   * @see SetSoftwareConfiguration
   */
  HRESULT SetSoftwareConfiguration(CATSoftwareConfiguration *iConfig);

  /**
   * Get the CATSoftwareConfiguration associated with this task manager.
   * <b>Role:</b> To properly support operator versioning, use the 
   * Set and GetSoftwareConfiguration methods to retain only one copy 
   * of a CATSoftwareConfiguration object.
   * @return
   *  The CATSoftwareConfiguration object.
   * @see SetSoftwareConfiguration
   */
  CATSoftwareConfiguration *GetSoftwareConfiguration();

public:

  ////////////////////////////////////////////////////////////////
  // The remainder of this class is for internal purposes only. //
  ////////////////////////////////////////////////////////////////

  //Writes a list of CGM Geometry into the stream using the context of the AppliDataCGM object 
  // meaning that it doesn't stream already streamed objects to the same slave
  // The resulting stream MUST be read by the CATMProcSlaveOperatorCGM ReadGeometry function
  /** @nodoc  internal functionality */
  HRESULT WriteGeometry(CATCGMStream & ioStream,CATLISTP(CATICGMObject)& iGeometry, CATMProcAppliDataCGM*& ioData);

  //Reads a list of new CGM Geometry from the stream 
  // The input stream MUST have been written by the CATMProcSlaveOperatorCGM WriteGeometry function
  /** @nodoc  internal functionality */
  HRESULT ReadGeometry(CATCGMStream & ioStream,CATMProcAppliTask* iTaskToEnd, CATLISTP(CATICGMObject)& oGeometry);

#ifdef CATIACGMR217CAA
  //Writes a journal into the stream using the context of the AppliDataCGM object
  // meaning that it doesn't stream already streamed journals to the same slave
  /** @nodoc  internal functionality */
  HRESULT WriteJournal(CATCGMStream & ioStream,CATCGMJournal*& iJournal, CATMProcAppliDataCGM*& ioData);
  
  //Reads a new CGM journal from the stream 
  // The input stream MUST have been written by the CATMProcSlaveOperatorCGM WriteJournal function
  /** @nodoc  internal functionality */
  HRESULT ReadJournal(CATCGMStream & iStream,CATMProcAppliTask* iTaskToEnd, CATCGMJournal*& oJournal);
#endif

  /** @nodoc  internal functionality */
  CATMProcAppliManagerCGM();

  /** @nodoc  internal functionality */
  void SetFactory( CATGeoFactory* iFactory) { _Factory = iFactory; }

protected:
  // Write processing data (factory scale) to the buffer stream
  /** @nodoc  internal functionality */
  virtual void WriteData(CATMathStream &iStream);

  /** @nodoc  internal functionality */
  virtual void WriteData(void              *&ioBuffer,
                         unsigned int       &ioLgBuffer,
                         unsigned int       &ioLgDataIn,
                         int                 iSlaveId);

protected:
  // Get data buffer code
  // Please note: 0 - no data buffer
  //              1 - Config only
  //              2 - Factory unit only
  //              3 - Config & Factory unit
  //              etc.
  /** @nodoc  internal functionality */
  virtual short GetDataBufferCode();

  private:
  CATSoftwareConfiguration *_Config;
  CATGeoFactory* _Factory;
  CATCGMSafeHashTable* _CompleteAlreadySent;
  unsigned int _TotalLength;
  unsigned int _TotalBestLength;
};

/*
* Legacy comments:
*	Class used with the CGM MPROCTools for the optimization of the stream and unstream between the processes
*	This class is virtual and grants access to cgm optimized partial stream functions in the form of the two functions below.
*	an implementation of this class must be used with an implementation of the CATMProcSlaveOperatorCGM for the stream capabilities to function correctly
*/

#endif
