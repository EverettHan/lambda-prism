// COPYRIGHT DASSAULT SYSTEMES 2004
//=============================================================================
// Feb. 09  Creation                                                    VUC
//=============================================================================

#ifndef CATMProcSlaveOperatorCGM_H
#define CATMProcSlaveOperatorCGM_H

#include "CATIACGMLevel.h" // automatic treatment EB_2014_04_16
#include "ExportedByCATGeometricObjects_MProc.h"

#include "IUnknown.h"
#include "CATGeoFactory.h"
#include "CATMProcSlaveOperator.h"
#include "CATMProcAppliOperatorCGM.h"
#include "CATCGMSafeHashTable.h"

#include "CATICGMObject.h"
#include "CATCGMStream.h"


/*
 * Class used with the CGM MPROCTools for the optimization of the
 * stream and unstream between the processes This class is virtual and
 * grants access to cgm optimized partial stream functions in the form
 * of the two functions below.
 *
 * an implementation of this class must be used with an implementation
 * of the CATMProcAppliManagerCGM for the stream capabilities to
 * function correctly.
 */

class CATMProcAppliTask;
class CATMProcAppliDataCGM;
class CATMathStream;

class CATMProcTaskContainerCGM;
typedef CATMProcTaskContainerCGM* (CATMProcTaskContainerCGMFactory)(void);


class ExportedByCATGeometricObjects_MProc CATMProcSlaveOperatorCGM : public CATMProcSlaveOperator
{
 public:

  CATMProcSlaveOperatorCGM();

  virtual ~CATMProcSlaveOperatorCGM();

  CATMProcSlaveOperatorCGM& operator =(const CATMProcSlaveOperatorCGM& iOneOf);

  public:
  CATSoftwareConfiguration *GetConfig();
  void SetConfig(CATSoftwareConfiguration* iConfig);

  CATGeoFactory* GetFactory();
  CATGeoFactory* GetImplicitFactory();

  void SetFactory( CATGeoFactory* iFactory) { _Factory = iFactory; }

  HRESULT InitFactory();

public:
  //Reads the stream and produces a list of CGM Geometry using the hashtable for searching already received objects
  // The input stream MUST have been written by the CATMProcAppliManagerCGM WriteGeometry function
  HRESULT ReadGeometry(CATCGMStream& Stream,CATLISTP(CATICGMObject)& oListRead);


  //Writes a list of CGM Geometry into the stream
  // The resulting stream MUST be read by the CATMProcAppliManagerCGM ReadGeometry function
  HRESULT WriteGeometry(CATCGMStream& Stream,CATLISTP(CATICGMObject)& iListToWrite);


#ifdef CATIACGMR217CAA
  //Writes a CGM journal into the stream
  // The resulting stream MUST be read by the CATMProcAppliManagerCGM ReadJournal function
  /** @nodoc  internal functionality */
  HRESULT WriteJournal(CATCGMStream& ioStream,CATCGMJournal*& iJournal);

  //Reads the a CGM journal
  // The input stream MUST have been written by the CATMProcAppliManagerCGM WriteJournal function
  /** @nodoc  internal functionality */
  HRESULT ReadJournal(CATCGMStream& iStream,CATCGMJournal*& oJournal);
#endif

/**
  * Unstream a CATCGMOperator from a CATCGMStream.
  * @param iStream
  *  The output stream.
  * @return
  *  The unstreamed operator.
  */
  CATCGMOperator* ReadOperator( CATCGMStream& iStream);

  virtual HRESULT ProcessDataBuffer(void* iBuffer, unsigned int iBufferLength, unsigned int &ioUsedLength);

  virtual HRESULT RunRawTask( char* iFunctionCode, void*& ioBuffer, unsigned int& ioLgBuffer, unsigned int& ioLgData);

  // In case of non-optimized stream, clear the stream optimization
  // data of the slave operator after having completed the task
  virtual HRESULT ClearStreamOptimizationData();


  // Read data from data buffer
  // Please note: the method returns a buffer code, that identifies the
  //              contents of the data buffer:
  //              0 - no data buffer
  //              1 - Config only
  //              2 - Factory unit only
  //              3 - Config & Factory unit
  //              etc.
 protected:
  virtual short ReadData(CATMathStream &iStream);

  // Get software configuration
private:
  double GetFactoryUnit();

private:
  CATSoftwareConfiguration *_Config;
  CATGeoFactory* _Factory;
  double  _FactoryUnit;


protected:

  CATCGMSafeHashTable _Received;

protected:
  CATMProcTaskContainerCGMFactory* _TaskContainerFactory;

  // Methods to get and set client operator factory.
  CATMProcTaskContainerCGMFactory* GetTaskContainerFactory() const { return _TaskContainerFactory; }
  void SetTaskContainerFactory( CATMProcTaskContainerCGMFactory* iTaskContainerFactory)
  {
    _TaskContainerFactory = iTaskContainerFactory;
  }

  // For testing purposes
 protected:
  double TestFactoryUnit() const { return _FactoryUnit; }

private:
  CATMProcOperatorStreamingSupport OperatorStreamingSupport;
};

#endif
