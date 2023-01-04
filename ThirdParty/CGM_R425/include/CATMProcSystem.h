// COPYRIGHT DASSAULT SYSTEMES 2011

#ifndef CATMProcSystem_H
#define CATMProcSystem_H

#include "CATIACGMLevel.h"
#ifdef CATIACGMV5R23

/**
 * @CAA2Level L0
 * @CAA2Usage U1
 */

#include "MPROCTools.h"
#include "CATBoolean.h"

/**
 * Class to control the behavior of the MProc system.
 */
class ExportedByMPROCTools CATMProcSystem
{
public:
	/**
	 * Method to enable or disable the MProc system.
	 * <b>Role:</b> Use this method to specify the number of processes to use
	 * in parallel regions. By default, it will enable a number of processes
	 * equal to the number of processors. Specifing 1 will disable the MProc system.
	 * Otherwise the spefified number will be used, maxing out at the number of processors.
	 * @param iNumProcesses
	 *  The number of processes to use.
	 * @return
	 *  <tt>TRUE</tt> if the operation was successful, otherwise <tt>FALSE</tt>.
	 */
	static CATBoolean EnableMProc( unsigned int iNumProcesses = 0);

	/**
	 * Method to retrieve the number of physical processors in the system.
	 * @return
	 *  The number of processors found in the system.
	 */
	static unsigned int NumberPhysicalProcessors();

	/**
	 * Option to aid in debugging of custom MProc implementations.
	 * <b>Role:</b> When this mode is enabled, all code that is 
	 * typically only exercised in slave processes, such as the streaming
	 * and unstreaming methods, is executed in the master process. 
	 * This makes it easier to assure code correctness, without the 
	 * complexities of multiple processes.
	 * <b>Note:</b> This is for debugging purposes only. Once enabled,
	 *  this option cannot be disabled in the same session.
	 */
	static void EnableMonoProcMode();

};

#endif

#endif
