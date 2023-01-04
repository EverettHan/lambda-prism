// COPYRIGHT DASSAULT SYSTEMES 2004

#ifndef CATMProcAppliData_H
#define CATMProcAppliData_H

#include "MPROCTools.h"
#include "CATErrorDef.h"

/**
 * Base class in the derivation chain of classes defining a process specific container class.
 * <b>Role:</b> Class used for sharing information between tasks 
 * running on the same slave process. Clients can derive from this class to associate
 * data with a slave process for the duration of the application.
 * This base class does not contain support for stream optimizations.
 * <b>Note:</b> This base class is best used for basic MProc implementations.
 * Clients should derive from CATMProcAppliDataCGM when CGM objects are used.
 * @see CATMProcAppliDataCGM
 */
class ExportedByMPROCTools CATMProcAppliData   
{
public:
 /**
  * Default constructor initializes base class data.
  */
  CATMProcAppliData();

 /**
  * Virtual destructor releases base class data.
  */
  virtual ~CATMProcAppliData();

  /** @nodoc  internal functionality */
  virtual HRESULT ClearStreamOptimizationData();

private:
	CATMProcAppliData(const CATMProcAppliData& iOneOf);
	CATMProcAppliData& operator=(const CATMProcAppliData& iOneOf);
};

#endif

