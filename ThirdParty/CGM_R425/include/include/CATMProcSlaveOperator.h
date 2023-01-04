
// COPYRIGHT DASSAULT SYSTEMES 2004
//=============================================================================
// Mar. 09  Creation                                                    VUC
//=============================================================================


#ifndef CATMProcSlaveOperator_H
#define CATMProcSlaveOperator_H

#include "MPROCTools.h"
#include "CATErrorDef.h" // Build KO sur UNIX
#include "CATBoolean.h"
#ifndef NULL
#define NULL 0 // Build KO Unix
#endif

#include "IUnknown.h"
#ifndef _WINDOWS_SOURCE
#include "string.h"
#include "stdio.h"
#endif

class CATMathStream;

/*
*	Operator used in a SlaveFunction (see MProcTools Documentation)
*	Used for computing an operation on a slave process with a lasting context
*	Meaning that you can keep information from one run to another on the same slave process
*
* The child class CATMProcSlaveOperatorStream (as well as the CATMProcAppliManagerStream
* class) is designed to propagate the CATSoftwareConfiguration data between the master
* and slave processes
*/

class CATMProcFunctionManager;
class CATMProcTraceSlave;
class CATMProcAppliOperator;

class ExportedByMPROCTools CATMProcSlaveOperator
{
public:
	CATMProcSlaveOperator();
	virtual ~CATMProcSlaveOperator();

	static CATMProcSlaveOperator* GetOperator();
	static void RemoveCurrent();
	static HRESULT ProcessDataBuffer(char* iBuffer,
		unsigned int  iBufferLength,
		unsigned int &ioUsedLength);
	static char* GetSlaveName();

	static void SetSlaveName(char* iSlaveId);//char* representing the slave
private:
	static HRESULT SetDataBuffer(char*         iDataBuffer,
                               unsigned int  iBufferLength,
                               unsigned int  iDataLength);
  static CATBoolean HasDataBufferBeenSet();

	

	static CATMProcSlaveOperator*	_CurrentOperator;

public:
  static int RunSlaveProcess(int argc, char* argv[]);
  static HRESULT RunSlaveTask(char                     *iFunctionCode,
                              char                    *&ioBuffer,
                              unsigned int             &ioLgBuffer,
                              unsigned int             &ioLgData,
                              CATMProcFunctionManager  *iFunctionManager = 0,
                              CATBoolean                iMProcPerfoTrace = FALSE,
                              CATMProcTraceSlave       *iTraceSlave      = 0,
                              int                       iTaskId          = 0);
  static HRESULT SetNbCurrentOperators(unsigned int iNbCurrentOperators);
  static HRESULT SetCurrentOperatorIndex(unsigned int iCurrentOperatorIndex);

  static HRESULT SetDataBufferHasBeenSet(CATBoolean iDataBufferHasBeenSet);

  // In case of non-optimized stream, clear the stream optimization
  // data of the slave operator after having completed the task
  virtual HRESULT ClearStreamOptimizationData();

  // MProc Interface Simplification - jkj 2011
  // The Run method is not called by the new interface.
  virtual HRESULT Run( void *&ioBuffer, unsigned int &ioLgAllocated, unsigned int &ioLgData);
  // Base class stub methods.
  virtual HRESULT ProcessDataBuffer(void* iBuffer, unsigned int iBufferLength, unsigned int &ioUsedLength);
  virtual short ReadData(CATMathStream &iStream);
  virtual HRESULT RunRawTask( char* iFunctionCode, void*& ioBuffer, unsigned int& ioLgBuffer, unsigned int& ioLgData);

protected:
  static CATBoolean HasDataBufferBeenRead();
  static HRESULT SetDataBufferHasBeenRead(CATBoolean iDataBufferHasBeenRead);

protected:
  static char*        _DataBuffer;
  static unsigned int _BufferLength;
  static unsigned int _DataLength;
  static char*        _SlaveId;

  static CATMProcSlaveOperator** _CurrentOperatorArray;
  static unsigned int            _NbCurrentOperators;
  static unsigned int            _CurrentOperatorIndex;

	struct InnerData
	{
		CATBoolean BufferHasBeenSet;
		CATBoolean BufferHasBeenRead;
		char* SlaveName;
		InnerData() : BufferHasBeenSet(0), BufferHasBeenRead(0), SlaveName(NULL) {}
	};
	static InnerData* _InnerData;

private:
  static CATBoolean   _DataBufferHasBeenSet;
  static CATBoolean   _DataBufferHasBeenRead;

private:

	static CATMProcAppliOperator* _AppliOperator;

public:

	// Methods to get and set the client AppliOperator.
	CATMProcAppliOperator* GetAppliOperator() const { return _AppliOperator; }
	void SetAppliOperator( CATMProcAppliOperator* iAppliOperator) { _AppliOperator = iAppliOperator; }


    //--------------------------------------------------------------------------------------
    // Cancel Tasks
    //--------------------------------------------------------------------------------------
private:
	static CATBoolean _CancelTasks;

public:
	static void CancelTasks();
	CATBoolean TasksCancelled();

};

#endif

