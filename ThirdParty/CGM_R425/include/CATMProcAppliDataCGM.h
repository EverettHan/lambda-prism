// COPYRIGHT DASSAULT SYSTEMES 2004

#ifndef CATMProcAppliDataCGM_H
#define CATMProcAppliDataCGM_H

#include "CATMProcAppliData.h"
#include "ExportedByCATGeometricObjects_MProc.h"

class CATMProcAppliTask;
class CATCGMSafeHashTable;

/**
 * Class defining a process specific container class.
 * <b>Role:</b> Class used for sharing information between tasks 
 * running on the same slave process. Clients can derive from this class to associate
 * data with specific slave processes for the duration of the parallel transaction.
 * This class supports stream optimizations. It contains a hash table used to track
 * CGMobjects that have been streamed to the associated slave process. 
 * With this information, duplicate transmissions can be avoided.
 */
class ExportedByCATGeometricObjects_MProc CATMProcAppliDataCGM : public CATMProcAppliData
{
public:

 /**
  * Default constructor initializes member data.
  */
  CATMProcAppliDataCGM();

 /**
  * Default destructor releases member data.
  */
  virtual ~CATMProcAppliDataCGM();

  ////////////////////////////////////////////////////////////////
  // The remainder of this class is for internal purposes only. //
  ////////////////////////////////////////////////////////////////

  // Get the list of already streamed CGM objects.
  /** @nodoc  internal functionality */
  CATCGMSafeHashTable* GetAlreadySent();

 // Clear the list of already streamed CGM objects.
  /** @nodoc  internal functionality */
  virtual HRESULT ClearStreamOptimizationData();

private:
	CATCGMSafeHashTable* _AlreadySent;
};

// Legacy comments:
/*
*	Class used with the CGM MPROCTools for the optimization of the stream and unstream between the processes
*	Concretly, this class keeps the alreadysent hashtable between a Manager process and a slave process
*	to see an use example see the ODT TestMPROCCGM in NewTopologicalObjects.tst
*/

#endif

