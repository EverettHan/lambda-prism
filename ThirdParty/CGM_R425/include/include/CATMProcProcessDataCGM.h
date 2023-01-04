// COPYRIGHT DASSAULT SYSTEMES 2011

#ifndef CATMProcProcessDataCGM_H
#define CATMProcProcessDataCGM_H

#include "CATIACGMLevel.h"
#ifdef CATIACGMV5R23

/**
 * @CAA2Level L0
 * @CAA2Usage U2
 */

#include "ExportedByCATGeometricObjects_MProc.h"

class CATMProcProcessDataCGMImpl;

/**
 * Class defining a process specific container.
 * <b>Role:</b> Class used for sharing information between tasks 
 * running on the same slave process. Clients can derive from this class to associate
 * data with specific slave processes for the duration of the parallel transaction.
 * This class additionally supports stream optimizations. It contains a hash table used 
 * to track CGMobjects that have been streamed to the associated slave process. 
 * With this information, duplicate transmissions can be avoided.
 */
class ExportedByCATGeometricObjects_MProc CATMProcProcessDataCGM
{
public:

 /**
  * Default constructor initializes member data.
  */
  CATMProcProcessDataCGM();

 /**
  * Virtual destructor.
  * <br> The default implementation releases base class data.
  */  
  virtual ~CATMProcProcessDataCGM();

  /** @nodoc  internal functionality */
  CATMProcProcessDataCGMImpl* Impl() const { return _Impl; }

private:

  CATMProcProcessDataCGMImpl* _Impl;

  CATMProcProcessDataCGM(const CATMProcProcessDataCGM& iOneOf);
  CATMProcProcessDataCGM& operator =(const CATMProcProcessDataCGM& iOneOf);
};

#endif

#endif
